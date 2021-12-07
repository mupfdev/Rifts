// BANDDEV.H
//
// Copyright (c) 1997-2000 Symbian Ltd.  All rights reserved.
//

#ifndef BANDDEV_H
#define BANDDEV_H

#include <e32std.h>
#include <gdi.h>

class CFbsBitmapDevice;
class CFbsBitGc;

enum TBandingDirection
	{
	EBandingTopToBottom,
	EBandingBottomToTop,
	EBandingLeftToRight,
	EBandingRightToLeft
	};

/**
 * @internal
 * Internal to Symbian
 */
class CBandedDevice : public CGraphicsDevice
	{
public:
	IMPORT_C ~CBandedDevice();
	IMPORT_C static CBandedDevice* NewL(TRect aRectInPixels, TSize aKPixelSizeInTwips, TDisplayMode aDisplayMode, TBandingDirection aBandingDirection = EBandingTopToBottom, TInt aScanLinesPerBand = 0);

	IMPORT_C TInt HorizontalTwipsToPixels(TInt aTwips) const;
	IMPORT_C TInt VerticalTwipsToPixels(TInt aTwips) const;
	IMPORT_C TInt HorizontalPixelsToTwips(TInt aPixels) const;
	IMPORT_C TInt VerticalPixelsToTwips(TInt aPixels) const;
	IMPORT_C TInt GetNearestFontInTwips(CFont*& aFont, const TFontSpec& aFontSpec);
	IMPORT_C void ReleaseFont(CFont* aFont);

	IMPORT_C TDisplayMode DisplayMode() const;
	IMPORT_C TSize SizeInPixels() const;
	IMPORT_C TSize SizeInTwips() const;
	IMPORT_C TInt CreateContext(CGraphicsContext*& aGC);
	IMPORT_C TInt NumTypefaces() const;
	IMPORT_C void TypefaceSupport(TTypefaceSupport& aTypefaceSupport, TInt aTypefaceIndex) const;
	IMPORT_C TInt FontHeightInTwips(TInt aTypefaceIndex, TInt aHeightIndex) const;
	IMPORT_C void PaletteAttributes(TBool& aModifiable, TInt& aNumEntries) const;
	IMPORT_C void SetPalette(CPalette* aPalette);
	IMPORT_C TInt GetPalette(CPalette*& aPalette) const;

	IMPORT_C TInt NumBands() const;
	IMPORT_C TInt NextBand();
	IMPORT_C TRect BandRect() const;
	IMPORT_C TPoint FullOriginToBandOrigin(const TPoint& aPoint) const;
	IMPORT_C void Reset();

	inline TBandingDirection BandingDirection() const {return iBandingDirection;}
	inline CFbsBitmap* BandBitmap() const {return iBandBitmap;}

private:
	CBandedDevice(TRect aRectInPixels, TBandingDirection aBandingDirection, TInt aScanLinesPerBand);
	void ConstructL(TDisplayMode aDisplayMode, TSize aKPixelSizeInTwips);

private:
	TRect iFullRectInPixels;
	TInt iScanLinesPerBand;
	TInt iBandIndex;
	CFbsBitmap* iBandBitmap;
	CFbsBitmapDevice* iBandBitmapDevice;
	CFbsBitGc* iClearGc;
	TBandingDirection iBandingDirection;
	};

#endif
