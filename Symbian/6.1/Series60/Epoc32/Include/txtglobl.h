// TXTGLOBL.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __TXTGLOBL_H__
#define __TXTGLOBL_H__

#include <e32std.h>
#include <e32base.h>
#include <txtlaydc.h>
#include <txtmfmtx.h>
#include <txtetext.h>


// forward declarations
class CParaFormatLayer;
class CCharFormatLayer;
class TCharFormatX;
class TCharFormatXMask;


// Globally formatted text.
// Uses one instance of each a paragraph format and character format class; Each presents
// the formatting applied to the total document contents.  Both of the format classes used
// may utilise layering of formats through 'based on' links to achieve full format specification.
// These global layers are *never* owned by global text, merely referenced.

class CGlobalText : public CPlainText,public MLayDoc,public MFormatText
	{
public:
//	Special member functions
	// Create new global text component whose sole content is an end-of-document character.	
	IMPORT_C static CGlobalText* NewL(const CParaFormatLayer* aGlobalParaLayer,const CCharFormatLayer* aGlobalCharLayer,
									 TDocumentStorage aStorage=ESegmentedStorage,TInt aDefaultTextGranularity=EDefaultTextGranularity);
	// Restore a new global text, that uses the specified global layers.
	IMPORT_C static CGlobalText* NewL(const CStreamStore& aStore,TStreamId aStreamId,
									  const CParaFormatLayer* aGlobalParaLayer,const CCharFormatLayer* aGlobalCharLayer,
									  MTextFieldFactory* aFieldFactory=NULL,
									  TDocumentStorage=ESegmentedStorage);
	IMPORT_C ~CGlobalText();
//	Global Format Layers
	IMPORT_C void SetGlobalParaFormat(const CParaFormatLayer* aParaFormatLayer);
	IMPORT_C void SetGlobalCharFormat(const CCharFormatLayer* aCharFormatLayer);
	inline const CParaFormatLayer* GlobalParaFormatLayer()const;
	inline const CCharFormatLayer* GlobalCharFormatLayer()const;
//	MLayDoc implementation
	IMPORT_C virtual TInt LdDocumentLength()const;
	IMPORT_C virtual TInt LdToParagraphStart(TInt& aCurrentPos)const;
	IMPORT_C virtual void GetParagraphFormatL(CParaFormat* aFormat,TInt aPos)const;
	IMPORT_C virtual void GetChars(TPtrC& aView,TCharFormat& aFormat,TInt aStartPos)const;
	IMPORT_C virtual TInt GetPictureSizeInTwips(TSize& aSize, TInt aPos)const;
	IMPORT_C virtual CPicture* PictureHandleL(TInt aPos,MLayDoc::TForcePictureLoad aForceLoad)const;
	IMPORT_C virtual TBool EnquirePageBreak(TInt aPos,TInt aLength=0)const;
	IMPORT_C virtual TBool SelectParagraphLabel(TInt aPos);
	IMPORT_C virtual void CancelSelectLabel();
//  MFormatText implementation	
	IMPORT_C virtual void GetParaFormatL(CParaFormat* aFormat,TParaFormatMask& aVaries,TInt aPos,TInt aLength,
										CParaFormat::TParaFormatGetMode aMode=CParaFormat::EAllAttributes)const;
	IMPORT_C virtual void ApplyParaFormatL(const CParaFormat* aFormat,const TParaFormatMask& aMask,TInt aPos,TInt aLength);
	IMPORT_C virtual void GetCharFormat(TCharFormat& aFormat,TCharFormatMask& aVaries,TInt aPos,TInt aLength)const;
	IMPORT_C virtual void ApplyCharFormatL(const TCharFormat& aFormat,const TCharFormatMask& aMask,TInt aPos,TInt aLength);
protected:
	IMPORT_C CGlobalText();
	IMPORT_C CGlobalText(const CParaFormatLayer* aGlobalParaLayer,
						 const CCharFormatLayer* aGlobalCharLayer);
private:
	CGlobalText(const CGlobalText& aGlobalText);
	CGlobalText& operator=(const CGlobalText& aGlobalText);
protected:
	const CParaFormatLayer* iGlobalParaFormatLayer;  // the global paragraph format layer; not owned
	const CCharFormatLayer* iGlobalCharFormatLayer;  // the global character format layer; not owned
	__DECLARE_TEST;
private:
	void* iReserved_2;
	};


#include <txtglobl.inl>


#endif
