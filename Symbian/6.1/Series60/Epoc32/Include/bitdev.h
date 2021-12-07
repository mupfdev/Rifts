// BITDEV.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __BITDEV_H__
#define __BITDEV_H__

#ifndef __E32STD_H__
#include <e32std.h>
#endif
#ifndef __E32SVR_H__
#include <e32svr.h>
#endif
#ifndef __GDI_H__
#include <gdi.h>
#endif
#ifndef __FNTSTORE_H__
#include <fntstore.h>
#endif
#ifndef __FBS_H__
#include <fbs.h>
#endif
#ifndef __BITBASE_H__
#include <bitbase.h>
#endif
#ifndef __BITSTD_H__
#include <bitstd.h>
#endif

enum {EScanBufSize=0x80}; // used by RectCompare()

class CFbsDrawDevice;

class CFbsDevice : public CBitmapDevice
	{
	friend class CFbsBitGc;
public:
	IMPORT_C ~CFbsDevice();
	IMPORT_C TInt CreateContext(CFbsBitGc*& aGc);
	inline TInt CreateContext(CGraphicsContext*& aGc);
	IMPORT_C TDisplayMode DisplayMode() const;
	IMPORT_C TSize SizeInPixels() const;
	IMPORT_C TBool RectCompare(const TRect& aSourceRect,const CFbsDevice& aDevice,const TRect& aDeviceRect) const;
	IMPORT_C TInt AddFile(const TDesC& aName,TInt& aId);
	IMPORT_C void RemoveFile(TInt aId=0);
	IMPORT_C TInt GetNearestFontInTwips(CFont*& aFont,const TFontSpec& aFontSpec);
	IMPORT_C TInt GetNearestFontInPixels(CFont*& aFont,const TFontSpec& aFontSpec);
	IMPORT_C TInt GetFontById(CFont*& aFont,TUid aFileId,const TAlgStyle& aStyle);
	inline TInt GetNearestFontInTwips(CFbsFont*& aFont,const TFontSpec& aFontSpec);
	inline TInt GetNearestFontInPixels(CFbsFont*& aFont,const TFontSpec& aFontSpec);
	inline TInt GetFontById(CFbsFont*& aFont,TUid aFileId,const TAlgStyle& aStyle);
	IMPORT_C void ReleaseFont(CFont* aFont);
	IMPORT_C TInt FontHeightInTwips(TInt aTypefaceIndex,TInt aHeightIndex) const;
	IMPORT_C TInt FontHeightInPixels(TInt aTypefaceIndex,TInt aHeightIndex) const;
	IMPORT_C TInt NumTypefaces() const;
	IMPORT_C void TypefaceSupport(TTypefaceSupport& aTypefaceSupport,TInt aTypefaceIndex) const;
	IMPORT_C TInt SetCustomPalette(const CPalette* aPalette);
protected:
	CFbsDevice();
	virtual void DrawingBegin(TBool=EFalse) {}
	virtual void DrawingEnd(TBool=EFalse) {}
	virtual void SetBits() {}
	virtual void CancelSprite() const {}
	virtual TSpriteBase* HideSprite() const {return(NULL);}
	virtual TSpriteBase* HideSprite(const TRect&,const TRegion*) const {return(NULL);}
	virtual void ShowSprite(TSpriteBase*) const {}
	virtual void ShowSprite(TSpriteBase*,const TRect&,const TRegion*) const {}
	TInt GetNearestFbsFont(CFbsFont*& aFont,const TFontSpec& aFontSpec);
	void DoGetScanLine(TDes8& aBuf,const TPoint& aPixel,TInt aLength,TDisplayMode aDispMode);
	void ReadLineDiffMode(TInt,TInt,TInt,TAny*,TDisplayMode) const;
	void TruncateRect(TRect& aRect);
protected:
	CFbsDrawDevice* iDrawDevice;
	RFbsSession* iFbs;
	CFbsTypefaceStore* iTypefaceStore;
	TBool iLockHeap;
	TBool iScreenDevice;
	TUint8* iBitBltMaskedBuffer;
	};

class CFbsScreenDevice : public CFbsDevice
	{
public:
	IMPORT_C static CFbsScreenDevice* NewL(const TDesC& aLibname,TDisplayMode aDispMode,TRgb aWhite = KRgbWhite);
	IMPORT_C virtual ~CFbsScreenDevice();
	IMPORT_C void GetScanLine(TDes8& aBuf,const TPoint& aStartPixel,TInt aLength,TDisplayMode aDispMode) const;
	IMPORT_C void GetPixel(TRgb& aColor,const TPoint& aPixel) const;
	IMPORT_C TInt HorizontalPixelsToTwips(TInt aPixels) const;
	IMPORT_C TInt VerticalPixelsToTwips(TInt aPixels) const;
	IMPORT_C TInt HorizontalTwipsToPixels(TInt aTwips) const;
	IMPORT_C TInt VerticalTwipsToPixels(TInt aTwips) const;
	IMPORT_C void SetAutoUpdate(TBool aValue);
	IMPORT_C void DrawSpriteBegin();
	IMPORT_C void DrawSpriteEnd();
	IMPORT_C void CancelSprite() const;
	IMPORT_C TSpriteBase* HideSprite() const;
	IMPORT_C TSpriteBase* HideSprite(const TRect& aRect,const TRegion* aClippingRegion) const;
	IMPORT_C void ShowSprite(TSpriteBase* aSprite) const;
	IMPORT_C void ShowSprite(TSpriteBase* aSprite,const TRect& aRect,const TRegion* aClippingRegion) const;
	IMPORT_C void ChangeScreenDevice(CFbsScreenDevice* aOldDevice);
	IMPORT_C void PaletteAttributes(TBool& aModifiable,TInt& aNumEntries) const;
	IMPORT_C void SetPalette(CPalette* aPalette);
	IMPORT_C TInt GetPalette(CPalette*& aPalette) const;
	IMPORT_C void Update();
	IMPORT_C void Update(const TRegion& aRegion);
	IMPORT_C TSize SizeInTwips() const;
private:
	CFbsScreenDevice();
	void ConstructL(TDisplayMode aDispMode);
private:
	TSpriteBase* iSprite;
	TBool iSpriteDraw;
	};

class CFbsBitmapDevice : public CFbsDevice
	{
public:
	IMPORT_C static CFbsBitmapDevice* NewL(CFbsBitmap* aFbsBitmap);
	IMPORT_C static CFbsBitmapDevice* NewL(CFbsBitmap* aFbsBitmap,const TDesC& aLibname);
	IMPORT_C virtual ~CFbsBitmapDevice();
	IMPORT_C TInt Resize(const TSize& aSize);
	IMPORT_C virtual void GetScanLine(TDes8& aBuf,const TPoint& aStartPixel,TInt aLength,TDisplayMode iDispMode) const;
	IMPORT_C virtual void GetPixel(TRgb& aColor,const TPoint& aPixel) const;
	IMPORT_C virtual TInt HorizontalPixelsToTwips(TInt aPixels) const;
	IMPORT_C virtual TInt VerticalPixelsToTwips(TInt aPixels) const;
	IMPORT_C virtual TInt HorizontalTwipsToPixels(TInt aTwips) const;
	IMPORT_C virtual TInt VerticalTwipsToPixels(TInt aTwips) const;
	IMPORT_C virtual TSize SizeInTwips() const;
	IMPORT_C virtual void PaletteAttributes(TBool& aModifiable,TInt& aNumEntries) const;
	IMPORT_C virtual void SetPalette(CPalette* aPalette);
	IMPORT_C virtual TInt GetPalette(CPalette*& aPalette) const;
	IMPORT_C virtual void DrawingBegin(TBool aAlways);
	IMPORT_C virtual void DrawingEnd(TBool aAlways);
private:
	CFbsBitmapDevice();
	virtual void SetBits();
	void ConstructL(CFbsBitmap* aFbsBitmap);
	void ConstructL(CFbsBitmap* aFbsBitmap,const TDesC& aLibname);
private:
	CFbsBitGcBitmap* iFbsBmp;
	};

#include <bitdev.inl>
#endif
