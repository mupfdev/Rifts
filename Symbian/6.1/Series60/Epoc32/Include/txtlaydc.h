// TXTLAYDC.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __TXTLAYDC_H__
#define __TXTLAYDC_H__

#include <e32std.h>

class CParaFormat;
class TCharFormat;
class CPicture;

class MLayDoc
	{
	// Defines interface for extracting content & format information from text source.
	// Designed to be 'mixed-in' with other classes.
	//
public:
	enum TForcePictureLoad {EForceLoadFalse,EForceLoadTrue};
public:
	virtual TInt LdDocumentLength()const=0;  // Does not include final document terminator
	virtual TInt LdToParagraphStart(TInt& aCurrentPos)const=0;
	// Modify aCurrentPos to hold the pos of the start of the paragraph containing aCurrentPos
	// and return the number of characters skipped.
	//
	virtual void GetParagraphFormatL(CParaFormat* aFormat,TInt aPos)const=0;
	// Provides values for all the attributes of the paragraph containing aPos
	//
	virtual void GetChars(TPtrC& aView,TCharFormat& aFormat,TInt aStartPos)const=0;	
	// Return a block of (>=1) characters from aStartPos and the attributes that they have.
	//
	virtual TInt GetPictureSizeInTwips(TSize& aSize, TInt aPos)const=0;
	// Set aSize with the TWIPS size of the picture located at character position aPos.
	// If no picture present returns KErrNotFound.
	//
	virtual CPicture* PictureHandleL(TInt aPos,TForcePictureLoad aForceLoad=EForceLoadTrue)const=0;
	// returns the handle of the picture at aPos, or NULL if there is none.
	// By default, (EForceLoadTrue), if the picture is not in memory it is loaded.  This can be overriden.
	//
	virtual TBool EnquirePageBreak(TInt aPos,TInt aLength=0)const=0;
	// returns ETrue if a page break falls within the specified text region.
	//
	virtual TBool SelectParagraphLabel(TInt aPos)=0;
	// Select as the text source the paragraph label associated with the paragraph containing aPos.
	// May return False if the paragraph has no label text and, in which case, the function has no effect.
	// (returns True otherwise).
	//
	virtual void CancelSelectLabel()=0;
	// Cancels any paragraph label select. Harmless if not in label mode.
	//

	IMPORT_C virtual void MLayDoc_Reserved_1();
	};

#endif

