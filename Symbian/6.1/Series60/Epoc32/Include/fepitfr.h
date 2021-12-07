// FEPITFR.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// the class for inline-text format retrieval - in its own header file to prevent low-level components dependent on this class from gaining unnecessary (and undesirable) dependencies on high-level components

#if !defined(__FEPITFR_H__)
#define __FEPITFR_H__

#if !defined(__E32STD_H__)
#include <E32STD.H>
#endif

class TCharFormat;

class MFepInlineTextFormatRetriever // to be overridden by inline-editing front-end processors
	{
public:
	virtual void GetFormatOfFepInlineText(TCharFormat& aFormat, TInt& aNumberOfCharactersWithSameFormat, TInt aPositionOfCharacter) const=0;
private:
	IMPORT_C virtual void MFepInlineTextFormatRetriever_Reserved_1();
	IMPORT_C virtual void MFepInlineTextFormatRetriever_Reserved_2();
	};

#endif

