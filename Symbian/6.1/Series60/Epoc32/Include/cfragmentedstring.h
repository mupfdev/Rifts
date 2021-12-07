// CFragmentedString.h
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved. 
//

// A string class implementation which allows quick addition of partial strings
// (no copying) by using an internal array of fragmented strings.
// The class allows comprehensive character based matching functionality 
// along with infinite depth marking.

#ifndef __CFRAGMENTEDSTRING_H__
#define __CFRAGMENTEDSTRING_H__

// includes
#include <e32base.h>
#include <CStack.h>


//
// CFragmentedString
//

class CFragmentedString : protected CArrayPtrFlat<HBufC>
	{
protected:
	class TStringMark
		{
	public:
		TStringMark(TInt aIndex, TInt aCharacter)
		: iMarkIndex(aIndex), iMarkCharacter(aCharacter)
		{
		}

	public:
		TInt iMarkIndex;
		TInt iMarkCharacter;
		};

	typedef CStack<TStringMark, ETrue> CMarkStack;

public:
	enum TStringMatch 
		{ 
		ENoMatch, 
		EMatch,
		EInsufficientData
		};

public:
	IMPORT_C CFragmentedString();
	IMPORT_C ~CFragmentedString();

	IMPORT_C void AddStringL(HBufC* aString); // this version is more efficient
	IMPORT_C void AddStringL(const TDesC& aString);
	
	IMPORT_C TInt Length() const;
	IMPORT_C HBufC* StringL() const;
	IMPORT_C HBufC* ContentL() const;
	IMPORT_C void Reset();

	IMPORT_C TStringMatch Match(const TDesC& aString);
	IMPORT_C TStringMatch MatchRange(const TUint aLower, const TUint aUpper);
	IMPORT_C TStringMatch MatchSelect(const TDesC& aSelection);
	IMPORT_C TStringMatch MatchNotSelect(const TDesC& aSelection);
	IMPORT_C void ConsumeMatched();

	IMPORT_C HBufC* MarkedL();
	IMPORT_C HBufC* MarkedWithInitialTextL(const TDesC& aInitialText);
	IMPORT_C void Mark(); // Mark can leave
	IMPORT_C void DeleteMark();
	IMPORT_C void ResetToMark();

	IMPORT_C void ReplaceMarkedL(HBufC* aString);
	IMPORT_C void ReplaceMarkedAndSkipL(HBufC* aString);
	IMPORT_C void InsertStringL(HBufC* aString);

protected:
	IMPORT_C void DeleteToMark(const TStringMark& aStringMark);
	IMPORT_C void InsertStringToL(HBufC* aString, TInt aStringIndex, TInt aLengthIntoString);
	HBufC* StringL(TInt aStartIndex, TInt aStartCharacter, TInt aEndIndex, TInt aEndCharacter, const TDesC* aInitialText=NULL) const;
	void StartMatch();
	CFragmentedString::TStringMatch DoMatchSelect(const TDesC& aSelection, TBool aInSelection);
	TBool FindNextMatchChar(TUint& aChar);

protected:
	TStringMatch iMatched;

	TInt iMatchedToIndex;
	TInt iMatchedToCharacter;
	TInt iCurrentIndex;
	TInt iCurrentCharacter;
	CMarkStack iMarkStack;
	};

#endif // __CFRAGMENTEDSTRING_H__
