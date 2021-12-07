// CBNFParser.h
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved. 

//
// This class provides a mechanism to use a BNF tree to parse an input stream.
// The notation of the EBNF is based upon that described in the XML1.0 specification.
// The BNF tree form used is a variation on Extended BNF and has the following rule types,
// where the input stream must:
//	, Exact - match exactly with the provided string.
//	, Range - next character must be in the specified range.
//	, Select - next character must exist in the selected string.
//                 If the select string starts with ^ it is a NOT Select.
//	, And - match all of the given sub rules
//	, Or - match one of the given sub rules
//	, NMore - match N or more times the the SINGLE subrule.
//	, Optional - match 0/1 times to the SINGLE subrule.
//	, Without - match the first subrule but NOT the second.
//	, Reference - match the referred to rule.
//
// The iterative parser not only validates an input stream against the 
// BNF grammer but allows pre/post actions to be performed during the parsing.
// Partial parsing is also allowed in that the input stream does not have to
// completed before parsing can begin. As soon as data is added the parser
// attempts to parse it.
//
// Numerous methods are provided to assist in the building of the BNF Tree this parser uses.
//
// To use this class:
//   Create a derivation and implement the virtual method TreeL() to creat a BNF rule tree
//     (the assistance methods NewBNF/NewRule etc should be used) - see DTDModel 
//   To use your new parser invoke Reset and pass input data using the ProcessData method.
// 
#ifndef __CBNFPARSER_H__
#define __CBNFPARSER_H__

#include <e32std.h>
#include <mdprovob.h>
#include <CStack.h>
#include <CFragmentedString.h>
#include <CBNFNode.h>

//
// forward class declarations
//
class CAttributeLookupTable;


// Rule Tree node type definitions
enum TParserNodeTypes
	{
	ERoot, 
	EIncomplete, 
	EExact, 
	ERange, 
	ESelect, 
	EAnd, 
	EOr, 
	ENMore, 
	EOptional, 
	EWithout, 
	EReference, 
	ELastParserNodeType	
	};

// Parser states
//
// When a parser is running the state is EActive. 
// Setting parser state to something else in some pre-/post-rule callback function
// causes the parser to exit on next loop in ParseL. If the state is set to EStopped
// we have finished the parser operation (e.g. in event of an error), in state EPaused
// we are likely to resume the parser operation after some external operations.
enum TParseState
	{
	EStopped, 
	EActive, 
	EPaused
	};

//
// CBNFParser
//
class CBNFParser : public CBase, public MDataProviderObserver
	{
protected:
	typedef CStack<CBNFNode, EFalse> CRuleStack;

	// Type definition for a callback function pointer
	// Callback functions need to get a reference to the parser as parameter
	// and they need to be static!
	typedef void (TRuleCallback)(CBNFParser&);

public:
	// Constructor for a new parser instance
	//
	// Input:
	// aLUT - reference to attribute lookuptable; used to store all the stuff in the parser rule tree
	//
	IMPORT_C static CBNFParser* NewL(CAttributeLookupTable& aLUT);

	IMPORT_C virtual ~CBNFParser();

	// Prepare the parser to take in fresh stream of data.
	// THIS METHOD MUST BE CALLED BEFORE DATA CAN BE PROCESSED BY THE PARSER!!
	// Calls TreeL in order to create the parsing rule tree if no tree already
	// exists.
	IMPORT_C virtual void ResetL();

	// Check if the input stream was completely processed
	//
	// Return:
	//	TBool - ETrue if all of the data was processed, EFalse if the data didn't match to the parsing rules
	//.
	TBool Valid() const { return iStringComplete && (iString.Length() == 0); }

	// Concatenates the rest of the input stream (which hasn't yet been processed)
	// into a single string. The ownership of the string is given to the caller.
	//
	// Return:
	//	HBufC* - String containing the remaining data to be parsed. OWNERSHIP PASSED TO CALLED!
	HBufC* StringL() const { return iString.StringL(); }

	// Return:
	//	Pointer to the rule node currently being processed
	CBNFNode* CurrentRule() { return iCurrentRule; }

	// Set reference to an attribute lookup table
	void SetAttributeLookupTable(CAttributeLookupTable& aAttributeLookupTable);

	// methods to allow the input stream to be marked so that the callbacks
	// can determine those parts which successfully matched

	// Set a mark to the current position of the input stream 
	// The mark acts as a tag in the stream currently being processed.
	// As we process further along the stream after adding the mark, we can perform
	// a rollback to the most previously set mark and start processing again (e.g. OR rule
	// works this way). The string fragments won't be consumed (deleted) until
	// all the marks on a fragment (and fragments before that) are deleted.
	void Mark() { iString.Mark(); }; // **Mark can leave**

	// Get string between the "cursor position" and the latest mark on the stream.
	//
	// Return:
	//	HBufC* - Pointer to the string from the previous mark on to the current position
	//			 of processed string. OWNERSHIP OF THE STRING GIVEN TO THE CALLER!
	HBufC* MarkedL() { return iString.MarkedL(); };

	// Get the marked string with a string added before the mached string.
	// See also: MarkedL
	//
	// Return:
	//	HBufC* - A string cosisting of aInitialText appended with the marked string.
	//           OWNERSHIP OF THE CONSTRUCTED STRING IS GIVEN TO THE CALLER!
	HBufC* MarkedWithInitialTextL(const TDesC& aInitialText) { return iString.MarkedWithInitialTextL(aInitialText); };

	// Remove the latest mark. All the marks are stored in a stack and this removes
	// the topmost mark.
	void DeleteMark() { iString.DeleteMark(); };

	// methods to determine it the used rule actually matched (typically used in post callbacks)
	TBool RuleMatched() const { return iSubRuleMatched; };
	TBool OptionalMatched() const { return iOptionalMatched; };

	// Create new rule tree root node.
	// This method creates a new single instance of CBNFNode, which shall act as the root
	// node of the rule tree, which implements the BNF rules for parsing the input stream.
	// All the other rules are attached as attributes to this node.
	// The root node should have single child node, which should be a reference to the
	// "logical root" of the rule tree. This can be done be attaching the logical root
	// rule as a component to the root rule.
	IMPORT_C CBNFNode* NewBNFL();

	// Add a new rule to a rule tree.
	//
	// Input:
	//	aRootRule - Pointer to the root bnf node (created with NewBNFL() ).
	//	aRuleName - Reference to a string identifying this rule. The string is used
	//				to make references to this rule from other rule's subtrees.
	//	aData	  - Pointer to a data string; used with EExact and ESelect type rules
	//              to match actual text strings.
	//	aPreRule  - Function pointer to a prerule function that gets called _BEFORE_
	//				we start processing this rule and its children (i.e. the rule subtree)
	//	aPostRule - Function pointer to a postrule function which is called _AFTER_
	//              we have processed this rule (i.e. when we return up from the subtree
	//              and this rule is finished).
	//
	// Return:
	//	CBNFNode& - Reference to the newly created rule node in the rule tree
	//
	IMPORT_C CBNFNode& NewRuleL(CBNFNode* aRootRule, 
					const TDesC& aRuleName, 
					TParserNodeTypes aRuleType, 
					HBufC* aData, 
					TRuleCallback* aPreRule, 
					TRuleCallback* aPostRule);

	// Overridden version of the NewRuleL. Takes reference to the data instead of owning it.
	IMPORT_C CBNFNode& NewRuleL(CBNFNode* aRootRule, 
					const TDesC& aRuleName, 
					TParserNodeTypes aRuleType, 
					const TDesC& aData, 
					TRuleCallback* aPreRule, 
					TRuleCallback* aPostRule);

	// construct a new rule component not attached to a rule.
	IMPORT_C CBNFNode* NewComponentL(TParserNodeTypes aRuleType, const TDesC& aData);
	IMPORT_C CBNFNode* NewComponentL(TParserNodeTypes aRuleType, HBufC* aData = NULL, TRuleCallback* aPreRule = NULL, TRuleCallback* aPostRule = NULL);

	// create a reference component to the rule of the given name
	// which is not attached to any rule.
	IMPORT_C CBNFNode* NewComponentL(CBNFNode* aRootRule, const TDesC& aRuleName);

	// Methods to create a new subrule to the given parent rule.
	// These methods can be used to build the subtrees to the "main rules" attached to the root node.
	//
	// Input:
	//	aParentRule - The rule for which the new rule shall be added as a child
	//  aRuleType - Type of the new rule
	//  aData - Data for the rule; the string to match for an EExact rule, the selection character set for ESelect
	//
	//	aPreRule - Pre rule callback function pointer
	//  aPostRule - Post rule callback function pointer
	// Return:
	//	CBNFNode& - reference to the new rule
	//
	IMPORT_C CBNFNode& NewComponentL(CBNFNode &aParentRule, TParserNodeTypes aRuleType, const TDesC& aData);
	IMPORT_C CBNFNode& NewComponentL(CBNFNode &aParentRule, TParserNodeTypes aRuleType, HBufC* aData = NULL, TRuleCallback* aPreRule = NULL, TRuleCallback* aPostRule = NULL);
	
	// Create a reference to another rule and attach this reference as a child of the given parent.
	// Creates a child node of type EReference for the parent. This reference node
	// hold the pointer to the rule we are refering to.
	// Using references we can link rules to each other and build complex rule trees
	// even though they don't physically form a complete tree.
	// Notice, that the rule we are refering to does not necessarily need to exist, yet!
	//
	// Input:
	//	aRootRule - The Root node to the rule tree (created with NewBNFL). This is needed to
	//				find the rule we are refering to with the string.
	//	aParentRule - The parent rule of the newly created reference 
	//	aRuleName - The "id string" of the rule we are refering to.
	IMPORT_C CBNFNode& NewComponentL(CBNFNode* aRootRule, CBNFNode &aParentRule, const TDesC& aRuleName);
	
	// add additional attributes to components of rules (i.e. range values)
	IMPORT_C void AddComponentAttributeL(CBNFNode& aRule, CBNFNodeAttributeType aAttribute, TInt aInt);
	
	// re-implementations of MDataProviderObserver methods
	IMPORT_C void ProcessDataL(HBufC8& aData);
	IMPORT_C void SetStatus(TInt aStatus = KErrNone);
	IMPORT_C void SetDocumentTypeL(TDesC&);
	IMPORT_C void SetDocumentTypeL(TDesC&, TDesC&);
	IMPORT_C void SetDataExpected(TInt);
	IMPORT_C void SetBaseUrlL(TDesC* aBaseUrl);

	// Tell the parser, that we all the data has been passed in.
	// This method attempts to parse what ever is left of the input stream if it wasn't
	// already finished.
	IMPORT_C void CommitL();

	// Get the current state of the parser 
	TParseState State() const {return(iParsing);};

protected:
	IMPORT_C CBNFParser(CAttributeLookupTable& aLUT);

	// Each of the following functions is a handler method for a specific type of a rule
	// node. For example, ReferenceL handles reference nodes etc.
	// These methods are called by PerformRuleL.
	//
	// Input:
	//	aRule - reference to the rule being processed
	//	aMatched - reference to a CFragmentedString::TStringMatch variable, which holds
	//             the information if the string or character we previously were trying to
	//             match actually matched.
	// Return:
	//	TBool - We return ETrue if we have completed processing this node. If the processing
	//          still continues we return EFalse. For example, an EAnd rule would return
	//          ETrue if all of its chidren had matched or if a rule didn't match. In the first
	//          case the EAnd rule would have turned out to be true (aMatched = EMatched) since
	//          all of its children were true, but in the latter case we can stop processing the
	//          EAnd rule, since a subrule to the And didn't match and this means that the And
	//          expression can not be true. Either way, the processing of the And ends and we
	//          may return ETrue;
	//
    IMPORT_C virtual TBool ReferenceL(CBNFNode& aRule, CFragmentedString::TStringMatch& aMatched);
    IMPORT_C virtual TBool ExactL(CBNFNode& aRule, CFragmentedString::TStringMatch& aMatched);
    IMPORT_C virtual TBool RangeL(CBNFNode& aRule, CFragmentedString::TStringMatch& aMatched);
    IMPORT_C virtual TBool SelectL(CBNFNode& aRule, CFragmentedString::TStringMatch& aMatched);
    IMPORT_C virtual TBool WithoutL(CBNFNode& aRule, CFragmentedString::TStringMatch& aMatched);
    IMPORT_C virtual TBool AndL(CBNFNode& aRule, CFragmentedString::TStringMatch& aMatched);
    IMPORT_C virtual TBool OrL(CBNFNode& aRule, CFragmentedString::TStringMatch& aMatched);
    IMPORT_C virtual TBool OptionalL(CBNFNode& aRule, CFragmentedString::TStringMatch& aMatched);
    IMPORT_C virtual TBool NMoreL(CBNFNode& aRule, CFragmentedString::TStringMatch& aMatched);

	// A method to add a callback to a rule
	//
	// Input:
	//	aRule - The rule to which the callback is to be added
	//	aCallbackID - Either CBNFNode::KPreRuleCallback() or CBNFNode::KPostRuleCallback()
	//                Defines the type of the callback function (i.e. is it to be called before
	//                or after the rule has been processed).
	//	aCallback - The callback function pointer
	//
    IMPORT_C virtual void AddRuleCallbackL(CBNFNode& aRule, const TDesC* aCallbackID, TRuleCallback* aCallback);
    IMPORT_C virtual void ExecutePreRuleCallbackL(CBNFNode& aRule);
    IMPORT_C virtual void ExecutePostRuleCallbackL(CBNFNode& aRule);

	// the method TreeL() should be reimplemented to generate a BNF rule tree and return
	// ownership of it. This is the rule tree which will be to parse the input stream.
	// See XmlPars.cpp or DTDMDL.cpp for example.
	IMPORT_C virtual CBNFNode* TreeL();

	// methods which are invoked when the parser encounters a conditional
	// point in the BNF grammar (i.e. And/Or)
    IMPORT_C virtual void StartConditional(TParserNodeTypes aRuleType);
	IMPORT_C virtual void EndConditional(TParserNodeTypes aRuleType, TBool aSuccess);

	// A callback function to insert a mark to the current position of the stream
	// being processed. Adding mark is a very common callback operation befor starting
	// to process a rule, hence the method is provided by the parser.
	IMPORT_C static void MarkCallback(CBNFParser& aParser);

	// returns the LUT used by this parser.
	IMPORT_C CAttributeLookupTable& AttributeLUT() const;

	// method which does the actual iterative parsing
	IMPORT_C TBool ParseL();

	// A rule to handle a node in the rule tree. This method just calls the appropriate
	// handler method according to the rule type.
    IMPORT_C virtual TBool PerformRuleL(CBNFNode& aRule, CFragmentedString::TStringMatch& aMatched);

	void SetState(TParseState aState) {iParsing=aState;};

protected:
	// Storage object for all the attributes and identifiers in a tree
	CAttributeLookupTable& iLUT;	

	// An utility object which stores all the buffers passed into the parser
	// and represents them as if they would form a single, continuous string.
	// This class also performs the actual physical matching/selection of the strings
	// and holds the marks set onto the string.
	CFragmentedString iString; 
	TBool iStringComplete; // more input stream has completed

	CBNFNode* iTree;        // the BNF tree we are using to parse the input stream

	// a stack of rules from iTree which are waiting to be completed
	// The stack basically holds the path along the rule tree
	CRuleStack iRuleStack;  
	CBNFNode* iCurrentRule; // the BNF rule we are currently using

	// when returning to a rule in the rulestack this indicates 
	// if the child rule matched correctly
	TBool iSubRuleMatched;
	TBool iOptionalMatched;

	// the child rule we are returning from (if any). 
	// if this is NULL we are new to this BNF rule.
	CBNFNode* iSubRule;     

	TParseState iParsing;
    CFragmentedString::TStringMatch iMatched;

	// Storage pointers for strings identifying certain attributes on the rule nodes
	const TDesC* iReferenceString;
	const TDesC* iRangeStart;
	const TDesC* iRangeEnd;
	const TDesC* iMoreMinimum;
	const TDesC* iMoreCount;
	const TDesC* iMoreMaximum;
	const TDesC* iPreRuleCallback;
	const TDesC* iPostRuleCallback;
	};

#endif
