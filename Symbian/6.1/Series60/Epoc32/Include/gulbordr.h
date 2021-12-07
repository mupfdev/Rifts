// GULBORDR.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__GULBORDR_H__)
#define __GULBORDR_H__

#if !defined(__E32DEF_H__)
#include <e32def.h>
#endif

#if !defined(__GULDEF_H__)
#include <guldef.h>
#endif

#if !defined(__GDI_H__)
#include <gdi.h>
#endif


/**
  * The TGulBorder class draws a border around a rectangular containing area in a graphics context.
  *	The rectangluar areas enclosed by borders are typically working areas of the context
  * so the class supplies a number of methods which describe how it occupies the area.
  *
  * A distinction between descriptive and logical borders is made.
  *
  * For descriptive borders the appearance of the border is known and fixed.
  * The type of border drawn is determined by setting flags which describe how it is to
  * be constructed. These flags can be combined to achieve many different effects and
  * standard combinations have been supplied.
  *
  * For logical borders the use of the border is known and fixed but the appearance is not specified.
  * The appearance and sizing functions must be supplied in custom written code.
  *
  * @since ER5U
  */
class TGulBorder
    {
public:
	class TColors
		{
	public:
		IMPORT_C TColors();
	public:	
		TRgb iLine;
		TRgb iBack;
		TRgb iLight;
		TRgb iMidlight;
		TRgb iMid;
		TRgb iDark;
		TRgb iInternalBack;
		};

public:
	enum TOutlineStyle
		{
		EWithOutline=0x01,
		EDottedOutline=0x02
		};

	enum TInlineStyle
		{
		EWithInline=0x04
		};

	enum T3DStyle
		{
		EFlat=0x10,
		ESunken=0x20,
		ERaised=0x40
		};

	enum TConstructionStyle
		{
		EOneStep=0x100,
		ETwoStep=0x200,
		EThreeStep=0x400,
		EInvertedTwoStep=0x800
		};

	enum TThickness
		{
		EAddOnePixel=0x1000,
		EAddTwoPixels=0x2000,
		EAddFourPixels=0x4000
		};

	enum TRounding
		{
		EAddOneRoundingPixel=0x10000,
		EAddTwoRoundingPixels=0x20000,
		EAddFourRoundingPixels=0x40000
		};
private:
	enum TNull
		{
		ENoBorder=0x00
		};

	enum TLegacyStyle
		{
		EShallow=EAddOnePixel,
		EDeep=EAddTwoPixels,
		EThick=EAddFourPixels,
		EHorizontal=0x100000,
		EWithOverlap=0x200000,
		EGray=0x400000,
		EBlack=0x80000
		};

	enum TLogicalStyle
		{
		ELogical=0x800000
		};
public:
	enum TLogicalFamily
		{
		EWindowFamily=ELogical|0x1,
		EContainerFamily=ELogical|0x2,
		EControlFamily=ELogical|0x3
		};
public:
	enum TBorderType
		{
		ENone=ENoBorder,
		ESingleGray=EWithOutline|EGray,
		ESingleBlack=EWithOutline|EBlack,
		ESingleDotted=EWithOutline|EDottedOutline,
		EShallowRaised=ERaised|EOneStep|EAddOnePixel,
		EShallowSunken=ESunken|EOneStep|EAddOnePixel,
		EDeepRaised=EWithOutline|ERaised|EOneStep|EAddTwoPixels,
		EDeepRaisedWithOutline=EWithOutline|ERaised|EOneStep|EAddTwoPixels,
		EDeepSunken=EWithOutline|ESunken|EOneStep|EAddTwoPixels,
		EDeepSunkenWithOutline=EWithOutline|ESunken|EOneStep|EAddTwoPixels,
		EThickDeepRaisedWithOutline=EWithOutline|ERaised|EOneStep|EAddOnePixel|EAddTwoPixels, 
		EVerticalBar=ERaised|EOneStep|EAddTwoPixels|EWithOverlap,
		EHorizontalBar=ERaised|EOneStep|EAddTwoPixels|EHorizontal|EWithOverlap
		};

	enum TLogicalType
		{
		// Window family
		EWindow=EWindowFamily|ERaised,
		// Container family
		EFlatContainer=EContainerFamily|EFlat,
		ERaisedContainer=EContainerFamily|ERaised,
		ESunkenContainer=EContainerFamily|ESunken,
		// Control Family
		EFlatControl=EControlFamily|EFlat,
		ERaisedControl=EControlFamily|ERaised,
		ESunkenControl=EControlFamily|ESunken,
		EFocusedRaisedControl=EControlFamily|ERaised|0x100,
		EFocusedSunkenControl=EControlFamily|ESunken|0x100
		};

public:
    IMPORT_C TGulBorder();
    IMPORT_C TGulBorder(TBorderType aType);
    IMPORT_C TGulBorder(TBorderType aType,TGulAdjacent aAdjacent);
	IMPORT_C TGulBorder(TInt aType);
    IMPORT_C TGulBorder(TInt aType,TGulAdjacent aAdjacent);
	IMPORT_C void Draw(CGraphicsContext& aGc,const TRect& aRect,const TColors& aBorderColors) const;
   	IMPORT_C void Draw(CGraphicsContext& aGc,const TRect& aRect) const;
	IMPORT_C TRect InnerRect(const TRect& aOuterRect) const;
   	IMPORT_C TRect OuterRect(const TRect& aInnerRect) const;
	IMPORT_C void SetType(TInt aType);
	IMPORT_C void SetAdjacent(TInt aAdjacent);
	IMPORT_C TSize SizeDelta() const;
   	IMPORT_C TMargins Margins() const;
	IMPORT_C TBool HasBorder() const;
	IMPORT_C TInt Adjacent() const;	
	IMPORT_C TInt Type() const;
public:	// Internal to Symbian
	IMPORT_C TInt Thickness() const;
	IMPORT_C TInt Rounding() const;
private:
	TBool IsSunken() const;
	TInt Depth() const;
	void DrawOutline(CGraphicsContext& aGc,const TRect& aRect,TRgb aColor) const;
	void DrawRectOutline(CGraphicsContext& aGc,const TRect& aRect) const;
	void DrawInline(CGraphicsContext& aGc,const TRect& aRect,TRgb aColor) const;
	TMargins OutlineMargins() const;
	TMargins BorderMargins() const;
	TMargins InlineMargins() const;
	TRect OutlineInnerRect(const TRect& aOuterRect) const;
	TRect BorderInnerRect(const TRect& aOuterRect) const;
	TInt BorderRounding() const;
	TInt InlineRounding() const;
	void DrawOneStep(CGraphicsContext& aGc,const TRect& aRect,TRgb aMidlight,TRgb aMid) const;
	void DrawTwoStep(CGraphicsContext& aGc,const TRect& aRect,TRgb aLight,TRgb aMidlight,TRgb aMid,TRgb aDark) const;
	void DrawInvertedTwoStep(CGraphicsContext& aGc,const TRect& aRect,TRgb aLight,TRgb aMidlight,TRgb aMid,TRgb aDark) const;
	void DrawThreeStep(CGraphicsContext& aGc,const TRect& aRect,TRgb aBack,TRgb aLight,TRgb aMidlight,TRgb aMid,TRgb aDark) const;
	void DrawTopLeft(CGraphicsContext& aGc,const TRect& aRect,TRgb aColor,const TInt aRounding) const;
	void DrawRoundedTopLeft(CGraphicsContext& aGc,const TRect& aRect,const TInt aRounding) const;
	void DrawBottomRight(CGraphicsContext& aGc,const TRect& aRect,TRgb aColor,const TInt aRounding) const;
	void DrawRoundedBottomRight(CGraphicsContext& aGc,const TRect& aRect,const TInt aRounding) const;
	void DrawRoundedCorner(CGraphicsContext& aGc,const TPoint& aStart,const TInt aRoundedLength, const TBool aUp, const TBool aRight) const;
	TInt RoundingMargin(const TInt aRoundedLength) const;
	inline TInt InternalType() const;
	void TranslateLegacyTypes();
private:
    TInt iType;
    };

/**
 * The MGulLogicalBorder class specifices an interface for logical borders.
 *
 * @since Uikon1.2
 */
class MGulLogicalBorder
	{
public:
	virtual void Draw(const TGulBorder& aBorder,CGraphicsContext& aGc, const TRect& aRect, const TGulBorder::TColors& aBorderColors) const=0;
	virtual TMargins Margins(const TGulBorder& aBorder) const=0;
private:
	IMPORT_C virtual void MGulLogicalBorderReserved();
	};

/**
 * The GulTls class sets and gets the thread local storage for EGul.
 *
 * @internal
 * @since Uikon1.2
 */
class GulTls
	{
public:
	IMPORT_C static void SetLogicalBorder(MGulLogicalBorder* aLogicalBorder);
	IMPORT_C static const MGulLogicalBorder* LogicalBorder();
	};

#endif
