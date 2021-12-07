// GULUTIL.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__GULUTIL_H__)
#define __GULUTIL_H__

#include <e32std.h>
#include <badesca.h>
#include <gdi.h>
#include <gulbordr.h>
#include <gulftflg.hrh>

const TUint KTextUtilClipEndChar=0x2026;
const TUint KColumnListSeparator='\t';

class CFont;
class CFbsFont;
class CWsScreenDevice;
class TResourceReader;
class CColorArray;
class CGraphicsDevice;
class RWsSession;
class CColorList;
template <class T> class CArrayFix;

class TMargins8
	{
public :
	TInt8 iLeft;
	TInt8 iRight;
	TInt8 iTop;
	TInt8 iBottom;
public :
	IMPORT_C TMargins8();
	IMPORT_C void SetAllValuesTo(TInt aCommonValue);
    IMPORT_C TRect InnerRect(const TRect& aOuterRect) const;
    IMPORT_C TRect OuterRect(const TRect& aInnerRect) const;
	IMPORT_C TSize SizeDelta() const;
	};

class DrawUtils
	{
public:
	IMPORT_C static void DrawText(CGraphicsContext& aGc,const TDesC& aString,const TRect& aBox,TInt aBaseLineOffset,
									CGraphicsContext::TTextAlign aHoriz,TInt aMargin,const CFont* aFont);
    IMPORT_C static void DrawBetweenRects(CGraphicsContext& aGc,const TRect& aOuterRect,const TRect& aInnerRect);
    IMPORT_C static void ClearBetweenRects(CGraphicsContext& aGc,const TRect& aOuterRect,const TRect& aInnerRect);
	};

class TextUtils
	{
public:
	IMPORT_C static void ClipToFit(TDes& aBuffer,const CFont& aFont,TInt aMaxWidthInPixels,TChar aAlternativeEnd=KTextUtilClipEndChar);
	IMPORT_C static TInt ColumnText(TPtrC& aColumnText,TInt aColumn,const TDesC* aSourceText,TChar aColumnSeparator=KColumnListSeparator);
	IMPORT_C static void TruncateToNumChars(TDes& aBuffer, TInt numChars);
	};

class FontUtils
	{
public:
	IMPORT_C static void GetAvailableFontsL(CGraphicsDevice& aDevice,CDesCArray& aFontNameList,
											TInt aFonts=EGulNoSymbolFonts);
	IMPORT_C static TInt TypefaceAttributes(CGraphicsDevice& aDevice,const TDesC& aTypefaceName);
	IMPORT_C static TInt GetAvailableHeightsInTwipsL(CGraphicsDevice& aDevice,const TDesC& aTypefaceName,
													CArrayFix<TInt>& aHeightList);
	IMPORT_C static TInt GetAvailableHeightsInTwipsAndPointsL(CGraphicsDevice& aDevice,const TDesC& aTypefaceName,
															CArrayFix<TInt>& aTwipsList,CDesCArray& aPointsList);
	IMPORT_C static TInt PointsFromTwips(TInt aTwips);
	IMPORT_C static TInt TwipsFromPoints(TInt aPoints);
	IMPORT_C static TInt TwipsFromPoints(const TDesC& aPoints);
	IMPORT_C static TInt IndexOfNearestHeight(CArrayFix<TInt>& aTwipsList,TInt aHeight);
	};

class ResourceUtils
	{
public:
	IMPORT_C static CFbsFont* CreateNamedScreenFontL(TResourceReader& aResourceReader,CWsScreenDevice& aScreenDevice);
	IMPORT_C static CFbsFont* CreateNamedScreenFontInPixelsL(TResourceReader& aResourceReader,CWsScreenDevice& aScreenDevice);
	IMPORT_C static CFbsFont* CreateScreenFontL(TResourceReader& aReader,CWsScreenDevice& aScreenDevice);
	inline static TInt8 ReadTInt8L(TResourceReader& aReader);
	inline static TInt16 ReadTInt16L(TResourceReader& aReader);
	inline static TInt32 ReadTInt32L(TResourceReader& aReader);
	IMPORT_C static void PopulateColorArrayL(CColorArray& aColors,TResourceReader& aReader);
private:
	enum TResourceTypeInt { EResourceInt8,EResourceInt16,EResourceInt32 };
private:
	IMPORT_C static TInt32 ReadResourceIntL(TResourceReader& aReader,TResourceTypeInt aSize);
	};

class ColorUtils
	{
public:
    enum TBitmapOrientation
	    {
	    EBitmapOrientationVertical,
	    EBitmapOrientationHorizontal
	    };
public:
	IMPORT_C static TRgb ColorAdjust(TRgb aColor,TInt aPercentage);
    IMPORT_C static void CreateGradientBitmapL(CFbsBitmap& aBitmap,RWsSession& aWs,TInt aBreadth,
                                       TBitmapOrientation aOrientation,TRgb aStartColor,TRgb aEndColor);
	IMPORT_C static CColorList* CreateSystemColorListL(RFs& aFs);
	IMPORT_C static CColorList* CreateSystemColorListL(RFs& aFs,const CColorList& aColorList);
	IMPORT_C static void UpdateSystemColorListL(RFs& aFs,CColorList& aColorList);
	IMPORT_C static void GetRgbDerivedBorderColors(TGulBorder::TColors& aBorderColors,TRgb aBackgroundColor,TDisplayMode aMode);
	IMPORT_C static TRgb RgbDarkerColor(TRgb aRgb,TDisplayMode aMode);
	IMPORT_C static TRgb RgbMidDarkerColor(TRgb aRgb,TDisplayMode aMode);
	IMPORT_C static TRgb RgbLighterColor(TRgb aRgb,TDisplayMode aMode);
	};

class TFindWidthOfWidestTextItem
	{
protected:
	inline TFindWidthOfWidestTextItem() {}
public:
	IMPORT_C TInt MaximumWidthInPixels(const CFont& aFont) const;
private:
	virtual void GetFirstAndLastIndex(TInt& aFirstIndex, TInt& aLastIndex) const=0;
	virtual void GetTextItem(TDes& aText, TInt aIndex) const=0;
	};

class TFindWidthOfWidestDigit : public TFindWidthOfWidestTextItem
	{
public:
	IMPORT_C TFindWidthOfWidestDigit();
private:
	virtual void GetFirstAndLastIndex(TInt& aFirstIndex, TInt& aLastIndex) const;
	virtual void GetTextItem(TDes& aText, TInt aIndex) const;
	};

class TFindWidthOfWidestAmPmName : public TFindWidthOfWidestTextItem
	{
public:
	IMPORT_C TFindWidthOfWidestAmPmName();
private:
	virtual void GetFirstAndLastIndex(TInt& aFirstIndex, TInt& aLastIndex) const;
	virtual void GetTextItem(TDes& aText, TInt aIndex) const;
	};

class TFindWidthOfWidestAbbreviatedDayName : public TFindWidthOfWidestTextItem
	{
public:
	IMPORT_C TFindWidthOfWidestAbbreviatedDayName();
private:
	virtual void GetFirstAndLastIndex(TInt& aFirstIndex, TInt& aLastIndex) const;
	virtual void GetTextItem(TDes& aText, TInt aIndex) const;
	};

class TFindWidthOfWidestDayName : public TFindWidthOfWidestTextItem
	{
public:
	IMPORT_C TFindWidthOfWidestDayName();
private:
	virtual void GetFirstAndLastIndex(TInt& aFirstIndex, TInt& aLastIndex) const;
	virtual void GetTextItem(TDes& aText, TInt aIndex) const;
	};

class TFindWidthOfWidestAbbreviatedMonthName : public TFindWidthOfWidestTextItem
	{
public:
	IMPORT_C TFindWidthOfWidestAbbreviatedMonthName();
private:
	virtual void GetFirstAndLastIndex(TInt& aFirstIndex, TInt& aLastIndex) const;
	virtual void GetTextItem(TDes& aText, TInt aIndex) const;
	};

class TFindWidthOfWidestMonthName : public TFindWidthOfWidestTextItem
	{
public:
	IMPORT_C TFindWidthOfWidestMonthName();
private:
	virtual void GetFirstAndLastIndex(TInt& aFirstIndex, TInt& aLastIndex) const;
	virtual void GetTextItem(TDes& aText, TInt aIndex) const;
	};

class TFindWidthOfWidestDateSuffix : public TFindWidthOfWidestTextItem
	{
public:
	IMPORT_C TFindWidthOfWidestDateSuffix();
private:
	virtual void GetFirstAndLastIndex(TInt& aFirstIndex, TInt& aLastIndex) const;
	virtual void GetTextItem(TDes& aText, TInt aIndex) const;
	};

//	class ResourceUtils
inline TInt8 ResourceUtils::ReadTInt8L(TResourceReader& aReader)
	{ return((TInt8)ReadResourceIntL(aReader,EResourceInt8)); }
inline TInt16 ResourceUtils::ReadTInt16L(TResourceReader& aReader)
	{ return((TInt16)ReadResourceIntL(aReader,EResourceInt16)); }
inline TInt32 ResourceUtils::ReadTInt32L(TResourceReader& aReader)
	{ return((TInt32)ReadResourceIntL(aReader,EResourceInt32)); }

#endif

