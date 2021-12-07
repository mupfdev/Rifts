// CDTDModel.h
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved. 
//

// contains the parser specialisation (BNF grammar) for a DTD parser.
// See CBNFParser for function details

#ifndef __CDTDMODEL_H__
#define __CDTDMODEL_H__

#include <CBNFNode.h>
#include <CBNFParser.h>
#include <CRuleMarkedStack.h>


class CDTDModel : public CBNFParser
	{
public:
    class CDTDElementAttribute : public CBase
		{
	public:
		enum KValueType
			{
			EDefault, 
			ERequired, 
			EImplied, 
			EFixed, 
			EReference
			};

	public:
		virtual ~CDTDElementAttribute() 
			{ 
			delete iType; 
			delete iValue; 
			}

	public:
		CBNFNode*	iType;
        CBNFNode*	iValue;
        KValueType	iValueType;
		};


	enum TRuleMarks 
		{
		ERuleStartMark = 1, 
		EConditionalMark, 
		EGroupMark 
		};

	IMPORT_C static CDTDModel* NewL(CAttributeLookupTable& aLUT);
	IMPORT_C virtual ~CDTDModel();

	// This method MUST be invoked before data can be processed by the parser.
	IMPORT_C virtual void ResetL();

	IMPORT_C CBNFNode* GeneratedTree();

	// Building method for a hard coded WML1.1 DTD tree
	// Input:
	//		aPackageRoot - A root node to which the generated tree is attached
	//
	IMPORT_C void BuildWml11DTDL(CBNFNode& aPackageRootNode);

protected:
    IMPORT_C CDTDModel(CAttributeLookupTable& aLUT);	

	// construct our BNF rule tree
	IMPORT_C virtual CBNFNode* TreeL();
	
	// to control our internal state on conditional rules.
	IMPORT_C virtual void StartConditional(TParserNodeTypes aRuleType); 
	IMPORT_C virtual void EndConditional(TParserNodeTypes aRuleType, TBool aSuccess);

	// rule callbacks to build the DTD Tree
	static void PreRulesL(CBNFParser& aParser);
	static void PostRulesL(CBNFParser& aParser);
	static void PreElementDeclL(CBNFParser& aParser);
	static void PostElementDeclL(CBNFParser& aParser);
	static void PreEntityDeclL(CBNFParser& aParser);
	static void PostEntityDeclL(CBNFParser& aParser);
	static void PreAttlistLineL(CBNFParser& aParser);
	static void PostAttlistLineL(CBNFParser& aParser);
	static void PostAttlistReferenceL(CBNFParser& aParser);
	static void PreAttValueL(CBNFParser& aParser);
	static void PostAttValueL(CBNFParser& aParser);
	static void PostRequiredL(CBNFParser& aParser);
	static void PostFixedL(CBNFParser& aParser);
	static void PostImpliedL(CBNFParser& aParser);
	static void PostAndL(CBNFParser& aParser);
	static void PostOrL(CBNFParser& aParser);
	static void PreGroupL(CBNFParser& aParser);
	static void PostGroupL(CBNFParser& aParser);
	static void PostMatch0PlusL(CBNFParser& aParser);
	static void PostMatch1PlusL(CBNFParser& aParser);
	static void PostOptionalL(CBNFParser& aParser);
	static void PostIdentifierL(CBNFParser& aParser);
	static void PostEntityDeclNameL(CBNFParser& aParser);
	static void PostElementDeclNameL(CBNFParser& aParser);
	static void PostAttlistDeclNameL(CBNFParser& aParser);
	static void PostAttfieldNameL(CBNFParser& aParser);
	static void PostReferenceNameL(CBNFParser& aParser);
	static void PostStringL(CBNFParser& aParser);
	static void PostValidHexCharL(CBNFParser& aParser);
	static void PostValidDecCharL(CBNFParser& aParser);
	static void PrePEDeclL(CBNFParser& aParser);
	static void PostPEDeclL(CBNFParser& aParser);
	static void PostGEDeclL(CBNFParser& aParser);
	static void PreGEContentL(CBNFParser& aParser);
	static void PostGEContentL(CBNFParser& aParser);	

	// utility functions
	static void PostValidCharL(CBNFParser& aParser, TRadix aRadix);
	static void PostRuleL(CBNFParser& aParser, TParserNodeTypes aType, const TDesC* aAttribute);

	void CharRefReplacement(TPtr& aString);

	void DoClear();

	// Help methods for the hardcoded WML 1.1 tree
	void AddNewAttributeL(CBNFNode& aNode, const TDesC* aAttributeId, const TDesC& aAttributeType, CDTDElementAttribute::KValueType aAttributeValueType, CBNFNode* aRootNode);
	void AddNewReferenceAttributeL(CBNFNode& aNode, const TDesC& aAttributeType, CBNFNode* aRootNode);
	void AddNewAttributeWithValueL(CBNFNode& aNode, const TDesC* aAttributeId, const TDesC& aAttributeType, const TDesC& aAttributeDefaultValue, CBNFNode* aRootNode);


protected:
    typedef CRuleMarkedStack<ETrue> COwnerRuleMarkedStack;

protected:
	TBool					iInPEDecl;	
	TBool					iCharRefCheck;
	HBufC*					iGEContent;

	HBufC*					iNewAttfieldName;
	CDTDElementAttribute*	iNewElementAttribute;
	CBNFNode*				iNewRule;
	CBNFNode*				iNewTree;
	COwnerRuleMarkedStack	iNewRuleStack;
	};

#endif // __CDTDMODEL_H__
