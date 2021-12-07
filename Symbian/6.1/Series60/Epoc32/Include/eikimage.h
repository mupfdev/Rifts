// EIKIMAGE.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKIMAGE_H__)
#define __EIKIMAGE_H__

#if !defined(__EIKALIGN_H__)
#include <eikalign.h>
#endif

class CFbsBitmap;
class CBitmapContext;

class CEikImage : public CEikAlignedControl
	{
public:
	IMPORT_C CEikImage();
	IMPORT_C ~CEikImage();
public: // framework
	IMPORT_C TSize MinimumSize();
	IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
public: // new functions
	IMPORT_C void CreatePictureFromFileL(const TDesC& aFilename,TInt aMainId,TInt aMaskId=-1);
	IMPORT_C void SetPicture(const CFbsBitmap* aBitmap,const CFbsBitmap* aMaskBitmap=NULL);
	IMPORT_C void SetEmphasis(TBool aEmphasis);
	IMPORT_C void SetPictureOwnedExternally(TBool aOwnership);
	IMPORT_C const CFbsBitmap* Bitmap() const;
	IMPORT_C const CFbsBitmap* Mask() const;
	IMPORT_C void SetBitmap(const CFbsBitmap* aBitmap);
	IMPORT_C void SetMask(const CFbsBitmap* aMaskBitmap);
	IMPORT_C void SetNewBitmaps(const CFbsBitmap* aNewBitmap,const CFbsBitmap* aNewMask);
	IMPORT_C TBool IsPictureOwnedExternally();
	IMPORT_C void SetBrushStyle(CGraphicsContext::TBrushStyle aBrushStyle);
protected: // from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: // from CCoeControl
	IMPORT_C void Draw(const TRect& aRect) const;
	IMPORT_C void Reserved_2();
private:
	const CFbsBitmap* iBitmap;
	const CFbsBitmap* iMaskBitmap;
	TInt iImFlags;
	TInt iSpare;
	CGraphicsContext::TBrushStyle iBrushStyle;
	};

#endif
