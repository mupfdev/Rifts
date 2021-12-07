// GDI.H
//
// Copyright (c) 1998-2000 Symbian Ltd.  All rights reserved.
//

#ifndef __GDI_H__
#define __GDI_H__

#include <e32base.h>
#include <f32file.h>
#include <s32std.h>

class TOpenFontCharMetrics;

const TInt KTwipsPerInch=1440;
const TInt KTwipsPerPoint=20;
const TInt KPointsPerInch=72;
const TInt KTwipsPerCm=567;
#if defined(__NO_CLASS_CONSTS__)
#define KA4PaperSizeInTwips TSize(11906,16838)
#define KLegalPaperSizeInTwips TSize(12240,20160)
#define KExecutivePaperSizeInTwips TSize(10440,15120)
#define KLetterPaperSizeInTwips TSize(12240,15840)
#define KCom_10PaperSizeInTwips TSize(5940,13680)
#define KMonarchPaperSizeInTwips TSize(5580,10800)
#define KDLPaperSizeInTwips TSize(6236,12472)
#define KC5PaperSizeInTwips TSize(9184,12983)
#else
const TSize KA4PaperSizeInTwips(11906,16838);
const TSize  KLegalPaperSizeInTwips(12240,20160)
const TSize  KExecutivePaperSizeInTwips(10440,15120)
const TSize  KLetterPaperSizeInTwips(12240,15840)
const TSize  KCom_10PaperSizeInTwips(5940,13680)
const TSize  KMonarchPaperSizeInTwips(5580,10800)
const TSize  KDLPaperSizeInTwips(6236,12472)
const TSize  KC5PaperSizeInTwips(9184,12983)
#endif

// TRgb color class for device independent color encoding

class TRgb
	{
public:
	inline TRgb();
	inline TRgb(TUint32 aValue);
	inline TRgb(TInt aRed,TInt aGreen,TInt aBlue);
	inline TInt Red() const;
	inline TInt Green() const;
	inline TInt Blue() const;
	IMPORT_C void SetRed(TInt aRed);
	IMPORT_C void SetGreen(TInt aGreen);
	IMPORT_C void SetBlue(TInt aBlue);
	IMPORT_C static TRgb Gray2(TInt aGray2);
	IMPORT_C static TRgb Gray4(TInt aGray4);
	IMPORT_C static TRgb Gray16(TInt aGray16);
	IMPORT_C static TRgb Gray256(TInt aGray256);
	IMPORT_C static TRgb Color16(TInt aColor16);
	IMPORT_C static TRgb Color256(TInt aColor256);
	IMPORT_C static TRgb Color4K(TInt aColor4K);
	IMPORT_C static TRgb Color64K(TInt aColor64K);
	IMPORT_C static TRgb Color16M(TInt aColor16M);
	IMPORT_C TInt Gray2() const;
	IMPORT_C TInt Gray4() const;
	IMPORT_C TInt Gray16() const;
	IMPORT_C TInt Gray256() const;
	IMPORT_C TInt Color16() const;
	IMPORT_C TInt Color256() const;
	IMPORT_C TInt Color4K() const;
	IMPORT_C TInt Color64K() const;
	IMPORT_C TInt Color16M() const;
	inline TBool operator==(const TRgb& aColor) const;
	inline TBool operator!=(const TRgb& aColor) const;
	inline TRgb operator~() const;
	inline TRgb operator&(const TRgb& aColor);
	inline TRgb operator|(const TRgb& aColor);
	inline TRgb operator^(const TRgb& aColor);
	inline TRgb& operator&=(const TRgb& aColor);
	inline TRgb& operator|=(const TRgb& aColor);
	inline TRgb& operator^=(const TRgb& aColor);
	inline TUint32 Value() const;
	IMPORT_C TInt Difference(const TRgb& aColor) const;
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
private:
	TUint32 iValue;
	};

#define KRgbBlack		TRgb(0x000000)
#define KRgbDarkGray	TRgb(0x555555)
#define KRgbDarkRed		TRgb(0x000080)
#define KRgbDarkGreen	TRgb(0x008000)
#define KRgbDarkYellow	TRgb(0x008080)
#define KRgbDarkBlue	TRgb(0x800000)
#define KRgbDarkMagenta	TRgb(0x800080)
#define KRgbDarkCyan	TRgb(0x808000)
#define KRgbRed			TRgb(0x0000ff)
#define KRgbGreen		TRgb(0x00ff00)
#define KRgbYellow		TRgb(0x00ffff)
#define KRgbBlue		TRgb(0xff0000)
#define KRgbMagenta		TRgb(0xff00ff)
#define KRgbCyan		TRgb(0xffff00)
#define KRgbGray		TRgb(0xaaaaaa)
#define KRgbWhite		TRgb(0xffffff)

enum TDisplayMode
	{
	ENone,
	EGray2,
	EGray4,
	EGray16,
	EGray256,
	EColor16,
	EColor256,
	EColor64K,
	EColor16M,
	ERgb,
	EColor4K
	};

class TDisplayModeUtils
	{
public:
	IMPORT_C static TBool IsDisplayModeColor(TDisplayMode aDispMode);
	IMPORT_C static TInt NumDisplayModeColors(TDisplayMode aDispMode);
	IMPORT_C static TInt NumDisplayModeBitsPerPixel(TDisplayMode aDispMode);
	};

class CPalette : public CBase
	{
public:
	IMPORT_C static CPalette* NewL(TInt aNumberOfEntries);
	IMPORT_C static CPalette* NewDefaultL(TDisplayMode aDispMode);
	IMPORT_C ~CPalette();
	IMPORT_C void Clear();
	inline TInt Entries() const;
	IMPORT_C TRgb GetEntry(TInt aPaletteIndex) const;
	IMPORT_C TRgb NearestEntry(const TRgb& aColor) const;
	IMPORT_C TInt NearestIndex(const TRgb& aColor) const;
	IMPORT_C void SetEntry(TInt aPaletteIndex,const TRgb& aPaletteEntry);
	IMPORT_C void GetDataPtr(TInt aFirstColor,TInt aNumColors,TPtr8& aPtr);
protected:
	IMPORT_C CPalette();
	void ConstructL(TInt aNumberOfEntries);
protected:
	TRgb* iArray;
	TInt iNumEntries;
	};

class TColor256Util
	{
public:
	IMPORT_C void Construct(const CPalette& aPalette);
	IMPORT_C TInt Color256(TRgb aRgb) const;
	IMPORT_C void Color256(TUint8* aDestination,const TRgb* aSource,TInt aNumPixels) const;
	inline TRgb Color256(TInt aColor256) const;
	IMPORT_C static const TColor256Util* Default();
public:
	TUint32	iColorTable[256];
	TUint8	iInverseColorTable[0x1000];
	};

class TLinearDDA
	{
public:
	enum TLineMode
		{
		ECenter,
		ELeft
		};
public:
	IMPORT_C TLinearDDA();
	IMPORT_C TLinearDDA(const TLinearDDA& aLine);
	IMPORT_C void Construct(const TPoint& aStart,const TPoint& aFinish,TLineMode aMode=ECenter);
	IMPORT_C TBool SingleStep(TPoint& aPosition);
	IMPORT_C TBool SingleScanline(TPoint& aStartPosition,TPoint& aEndPosition);
	IMPORT_C TBool NextStep(TPoint& aPosition);
	IMPORT_C void JumpToRect(const TRect& aRect);
	IMPORT_C void JumpToXCoord(const TInt aXCoord,TInt& aYCoord);
	IMPORT_C void JumpToYCoord(TInt& aXCoord,const TInt aYCoord);
private:
	void UpdatePosition();
private:
	enum TLineStatus
		{
		EInitialised,
		ECurrent,
		EComplete
		};
private:
	TInt iCount;
	TSize iDifference;
	TPoint iFinish;
	TInt iGradient;
	TPoint iInc;
	TPoint iPos;
	TPoint iStart;
	TRect iBoundingRect;
	TBool iBoundingRectSet;
	TBool iInside;
	TLineStatus iStatus;
	};

enum TFontPosture
	{
	EPostureUpright,
	EPostureItalic
	};

enum TFontStrokeWeight
	{
	EStrokeWeightNormal,
	EStrokeWeightBold
	};

enum TFontPrintPosition
	{
	EPrintPosNormal,
	EPrintPosSuperscript,
	EPrintPosSubscript
	};

enum TFontUnderline
	{
	EUnderlineOff,
	EUnderlineOn
	};

enum TFontStrikethrough
	{
	EStrikethroughOff,
	EStrikethroughOn
	};

const TInt KMaxTypefaceNameLength=0x18;

// Identifies a typface by name and contains the attributes of that typeface

class TTypeface
    {
public:
	enum
		{
		EProportional=1,
		ESerif=2,
		ESymbol=4
		};
public:
	IMPORT_C TTypeface();
	IMPORT_C TBool operator==(const TTypeface& aTypeface) const;
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	IMPORT_C void SetAttributes(TInt aMask);
	IMPORT_C void SetIsProportional(TBool aIsProportional);
	IMPORT_C void SetIsSerif(TBool aIsSerif);
	IMPORT_C void SetIsSymbol(TBool aIsSymbol);
	IMPORT_C TInt Attributes() const;
	IMPORT_C TBool IsProportional() const;
	IMPORT_C TBool IsSerif() const;
	IMPORT_C TBool IsSymbol() const;
public:
    TBufC<KMaxTypefaceNameLength> iName;
private:
    TUint32 iFlags;
    };

class TFontStyle
	{
public:
	IMPORT_C TFontStyle();
	IMPORT_C TFontStyle(TFontPosture aPost,TFontStrokeWeight aStrWgt,TFontPrintPosition aPrintPos);
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	IMPORT_C TFontPosture Posture() const;
	IMPORT_C TFontStrokeWeight StrokeWeight() const;
	IMPORT_C TFontPrintPosition PrintPosition() const;
	IMPORT_C void SetPosture(TFontPosture aPosture);
	IMPORT_C void SetStrokeWeight(TFontStrokeWeight aStrokeWeight);
	IMPORT_C void SetPrintPosition(TFontPrintPosition aPrintPosition);
	inline TBool operator==(const TFontStyle& aFontStyle) const;
private:
	enum
		{
		EItalic=0x1,
		EBold=0x2,
		ESuper=0x4,
		ESub=0x8
		};
private:
	TUint32 iFlags;
	};

// Specify a desired font in device independent terms

class TFontSpec
	{
public:
	IMPORT_C TFontSpec();
	IMPORT_C TFontSpec(const TDesC& aTypefaceName,TInt aHeight);
	IMPORT_C TBool operator==(const TFontSpec& aFontSpec) const;
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
public:
	TTypeface iTypeface;
	TInt iHeight;
	TFontStyle iFontStyle;
	};

// Defines the typeface name of the nth typeface and
// how many font heights are available in that typeface
// and the min and max heights

class TTypefaceSupport
    {
public:
    TTypeface iTypeface;
    TInt iNumHeights;
    TInt iMinHeightInTwips;
    TInt iMaxHeightInTwips;
    TBool iIsScalable; // supports heights from min to max at fixed interval
    };

const TInt KSuperSubScalingPercentage=67;
const TInt KSuperscriptOffsetPercentage=-28;
const TInt KSubscriptOffsetPercentage=14;

class CFont;
class CTypefaceStore : public CBase
	{
public:
	IMPORT_C ~CTypefaceStore();
	virtual TInt GetNearestFontInTwips(CFont*& aFont,const TFontSpec& aFontSpec)=0;
	virtual TInt NumTypefaces() const=0;
	virtual void TypefaceSupport(TTypefaceSupport& aTypefaceSupport,TInt aTypefaceIndex) const=0;
	virtual TInt FontHeightInTwips(TInt aTypefaceIndex,TInt aHeightIndex) const=0;
	IMPORT_C void ReleaseFont(CFont* aFont);
	IMPORT_C static TInt BaselineOffset(TInt aHeight,TFontPrintPosition aPos);
	IMPORT_C static TInt SuperSubHeight(TInt aHeight,TFontPrintPosition aPos);
protected:
	IMPORT_C CTypefaceStore();
	IMPORT_C void ConstructL();
	IMPORT_C void AddFontL(CFont* aFont);
protected:
	class TFontAccess
		{
	public:
		CFont* iFont;
		TInt iAccessCount;
		};
protected:
	CArrayFixFlat<TFontAccess>* iFontAccess;
	};

const TInt KMaxFontCacheEntries=32;

class CFontCache : public CBase
	{
public:
	IMPORT_C CFontCache();
	IMPORT_C CFontCache(TInt aMaxEntries);
	IMPORT_C ~CFontCache();
	IMPORT_C CFont* Search(const TFontSpec& aFontSpec);
	IMPORT_C CFont* AddEntryL(CFont* aFont,const TFontSpec& aFontSpec);
	IMPORT_C CFont* RemoveFirstEntry();
public:
	TInt iNumHits;
	TInt iNumMisses;
private:
	class CFontCacheEntry : public CBase
		{
	public:
		CFontCacheEntry(CFont* aFont,const TFontSpec& aFontSpec,CFontCacheEntry* aNext);
	public:
		CFont* iFont;
		TFontSpec iSpec;
		CFontCacheEntry* iNext;
		};
private:
	TInt iNumEntries;
	TInt iMaxEntries;
	CFontCacheEntry* iFirst;
	};

// Interface for mapping between twips and device-specific units (pixels) 

class MGraphicsDeviceMap
    {
public:
	IMPORT_C MGraphicsDeviceMap();
	IMPORT_C virtual ~MGraphicsDeviceMap();
	IMPORT_C TPoint TwipsToPixels(const TPoint& aTwipPoint) const;
	IMPORT_C TRect TwipsToPixels(const TRect& aTwipRect) const;
	IMPORT_C TPoint PixelsToTwips(const TPoint& aPixelPoint) const;
	IMPORT_C TRect PixelsToTwips(const TRect& aPixelRect) const;
	virtual TInt HorizontalTwipsToPixels(TInt aTwips) const=0;
	virtual TInt VerticalTwipsToPixels(TInt aTwips) const=0;
	virtual TInt HorizontalPixelsToTwips(TInt aPixels) const=0;
	virtual TInt VerticalPixelsToTwips(TInt aPixels) const=0;
	virtual TInt GetNearestFontInTwips(CFont*& aFont,const TFontSpec& aFontSpec)=0;
	virtual void ReleaseFont(CFont* aFont)=0;
    };

// Information on the capabilities and attributes of a device

class CGraphicsContext;
class CGraphicsDevice : public CBase , public MGraphicsDeviceMap
    {
public:
	virtual TDisplayMode DisplayMode() const=0;
	virtual TSize SizeInPixels() const=0;
	virtual TSize SizeInTwips() const=0;
    virtual TInt CreateContext(CGraphicsContext*& aGC)=0;
    virtual TInt NumTypefaces() const=0;
    virtual void TypefaceSupport(TTypefaceSupport& aTypefaceSupport,TInt aTypefaceIndex) const=0;
	virtual TInt FontHeightInTwips(TInt aTypefaceIndex,TInt aHeightIndex) const=0;
	virtual void PaletteAttributes(TBool& aModifiable,TInt& aNumEntries) const=0;
	virtual void SetPalette(CPalette* aPalette)=0;
	virtual TInt GetPalette(CPalette*& aPalette) const=0;
    };

class TCodeSection
	{
public:
	TInt iStart;
	TInt iEnd;
	};

// Represents a device font as returned from GraphicsDevice::SelectFont
// Used for font metrics and for assigning to a graphics context
class CFont: public CBase
    {
	friend class CTypefaceStore;

public:

	enum TTextDirection
		{
		EHorizontal,
		EVertical
		};

	class TPositionParam
		{
		public:
		TPositionParam():
			iDirection(EHorizontal),
			iPosInText(0),
			iOutputGlyphs(0)
			{
			}

		enum
			{
			EMaxInputChars = 18,	// ligatures cannot be made from more than 18 components
			EMaxOutputGlyphs = 8	// output can consist of up to 8 characters (one base and 7 combining characters)
			};

		// inputs
		TTextDirection iDirection;	// direction to draw the text
		TPtrC iText;				// text containing the characters to be positioned

		// members used for both input and output
		TInt iPosInText;		// position in iText
		TPoint iPen;			// pen position

		// output
		class TOutput
			{
			public:
			TUint iCode;			// character or glyph code
			const TUint8* iBitmap;	// bitmap data for the glyph, if available
			TSize iBitmapSize;		// size of the bitmap before algorithmic bolding, size multiplication, etc.
			TRect iBounds;			// bitmap bounds, relative to the original pen position
			};

		TOutput iOutput[EMaxOutputGlyphs];	// information about the glyphs that were output
		TInt iOutputGlyphs;					// number of glyphs actually output
		};	

	class TMeasureTextInput
		{
		public:
		TMeasureTextInput():
			iStartInputChar(0),
			iEndInputChar(KMaxTInt),
			iDirection(EHorizontal),
			iMaxAdvance(KMaxTInt),
			iMaxBounds(KMaxTInt),
			iCharJustNum(0),
			iCharJustExcess(0),
			iWordJustNum(0),
			iWordJustExcess(0)
			{
			}

		TInt iStartInputChar;	// starting index in iText; together with iMaxInputChars,
		TInt iEndInputChar;		// allows some context before and after the measured text to be supplied
								// so that shaping can work properly.
		TTextDirection iDirection;	// direction text is to be drawn in
		TInt iMaxAdvance;		// maximum advance
		TInt iMaxBounds;		// maximum width (or height if drawing vertically) of bounds
		TInt iCharJustNum;		// number of glyph groups to be letterspaced
		TInt iCharJustExcess;	// amount of space to be used for letterspacing
		TInt iWordJustNum;		// number of spaces to be used for wordspacing
		TInt iWordJustExcess;	// amount of space to be used for wordspacing
		};

	class TMeasureTextOutput
		{
		public:
		TInt iChars;			// number of input characters that would be drawn - this may be less than
								// the length of the text if a maximum advance or bounding box size is specified
		TInt iGlyphs;			// number of glyphs that would be drawn
		TInt iGroups;			// number of groups that would be drawn; a group is a base glyph plus one or more
								// combining characters
		TInt iSpaces;			// number of word spaces (U+0020) that would be drawn
		TRect iBounds;			// bounding box of all the glyphs that would be drawn
		TSize iMaxGlyphSize;	// maximum width and height of any glyph
		};

	enum TCharacterDataAvailability
		{
		ENoCharacterData,
		ECharacterWidthOnly,
		EAllCharacterData
		};

	virtual TUid TypeUid() const=0;
	virtual TInt HeightInPixels() const=0;
	virtual TInt AscentInPixels() const=0;
	IMPORT_C virtual TInt DescentInPixels() const;
	virtual TInt CharWidthInPixels(TChar aChar) const=0;
	virtual TInt TextWidthInPixels(const TDesC& aText) const=0;
	virtual TInt BaselineOffsetInPixels() const=0;
	virtual TInt TextCount(const TDesC& aText,TInt aWidthInPixels) const=0;
	virtual TInt TextCount(const TDesC& aText,TInt aWidthInPixels,TInt& aExcessWidthInPixels) const=0;
	virtual TInt MaxCharWidthInPixels() const=0;
	virtual TInt MaxNormalCharWidthInPixels() const=0;
	virtual TFontSpec FontSpecInTwips() const=0;
	IMPORT_C virtual TCharacterDataAvailability GetCharacterData(TUint aCode,TOpenFontCharMetrics& aMetrics,
			const TUint8*& aBitmap,TSize& aBitmapSize) const;
	IMPORT_C virtual TBool GetCharacterPosition(TPositionParam& aParam) const;
	IMPORT_C virtual void Reserved();

	// non-virtuals
	IMPORT_C TInt WidthZeroInPixels() const;
	IMPORT_C TInt MeasureText(const TDesC& aText,
							  const TMeasureTextInput* aInput = NULL,TMeasureTextOutput* aOutput = NULL) const;

	
protected:
	IMPORT_C virtual ~CFont();
    };

// Used for drawing to a graphics device
// All devices must support drawing bitmaps in the form of CFbsBitmap

class CFbsBitmap;
class CGraphicsContext : public CBase
	{
public:
	enum TTextAlign
		{
		ELeft,
		ECenter,
		ERight
		};
	enum TDrawModeComponents
		{
		EInvertScreen=1,
		EXor=2,
		EOr=4,
		EAnd=8,
		ELogicalOp=14,
		EInvertPen=16,
		EPenmode=32
		};
	enum TDrawMode
		{
		EDrawModeAND=EAnd,
		EDrawModeNOTAND=EInvertScreen|EAnd,
		EDrawModePEN=EPenmode,
		EDrawModeANDNOT=EAnd|EInvertPen,
		EDrawModeXOR=EXor,
		EDrawModeOR=EOr,
		EDrawModeNOTANDNOT=EInvertScreen|EAnd|EInvertPen,
		EDrawModeNOTXOR=EInvertScreen|EXor,
		EDrawModeNOTSCREEN=EInvertScreen,
		EDrawModeNOTOR=EInvertScreen|EOr,
		EDrawModeNOTPEN=EInvertPen|EPenmode,
		EDrawModeORNOT=EOr|EInvertPen,
		EDrawModeNOTORNOT=EInvertScreen|EOr|EInvertPen
		};
	enum TPenStyle
		{
		ENullPen,
		ESolidPen,
		EDottedPen,
		EDashedPen,
		EDotDashPen,
		EDotDotDashPen
		};
	enum TBrushStyle
		{
		ENullBrush,
		ESolidBrush,
		EPatternedBrush,
		EVerticalHatchBrush,
		EForwardDiagonalHatchBrush,
		EHorizontalHatchBrush,
		ERearwardDiagonalHatchBrush,
		ESquareCrossHatchBrush,
		EDiamondCrossHatchBrush
		};
	enum TFillRule
		{
		EAlternate,
		EWinding
		};

	// Parameters for text drawing
	struct TDrawTextParam
		{
		public:
		TDrawTextParam():
			iDirection(CFont::EHorizontal),
			iCharJustNum(0),
			iCharJustExcess(0),
			iWordJustNum(0),
			iWordJustExcess(0)
			{
			}

		CFont::TTextDirection iDirection;	// the direction in which to draw the text
		TInt iCharJustNum;					// number of glyph groups to be letterspaced
		TInt iCharJustExcess;				// amount of space to be used for letterspacing
		TInt iWordJustNum;					// number of spaces to be used for wordspacing
		TInt iWordJustExcess;				// amount of space to be used for wordspacing
		};

	// Parameters for extended text drawing and measuring
	struct TDrawTextExtendedParam: public TDrawTextParam
		{
		public:
		TDrawTextExtendedParam():
			iParRightToLeft(FALSE)
			{
			}

		TBool iParRightToLeft;				// true if the paragraph direction is right to left
		};


public:
	virtual CGraphicsDevice* Device() const=0;
	virtual void SetOrigin(const TPoint& aPos=TPoint(0,0))=0;
	virtual void SetDrawMode(TDrawMode aDrawingMode)=0;
	virtual void SetClippingRect(const TRect& aRect)=0;
	virtual void CancelClippingRect()=0;
	virtual void Reset()=0;

	virtual void UseFont(const CFont* aFont)=0;
	virtual void DiscardFont()=0;
	virtual void SetUnderlineStyle(TFontUnderline aUnderlineStyle)=0;
	virtual void SetStrikethroughStyle(TFontStrikethrough aStrikethroughStyle)=0;

// Justification utilities
	IMPORT_C static TInt JustificationInPixels(TInt aExcessPixels,TInt aTotalUnits,TInt aFirstUnit,TInt aNumUnits);
	IMPORT_C static TInt JustificationInPixels(TInt& aExcessPixels,TInt& aTotalUnits);
// Used to do justified text properly
	virtual void SetWordJustification(TInt aExcessWidth,TInt aNumGaps)=0;
// Used primarily to get accurate WYSIWYG
	virtual void SetCharJustification(TInt aExcessWidth,TInt aNumChars)=0;

	virtual void SetPenColor(const TRgb& aColor)=0;
	virtual void SetPenStyle(TPenStyle aPenStyle)=0;
	virtual void SetPenSize(const TSize& aSize)=0;

	virtual void SetBrushColor(const TRgb& aColor)=0;
	virtual void SetBrushStyle(TBrushStyle aBrushStyle)=0;
	virtual void SetBrushOrigin(const TPoint& aOrigin)=0;
	virtual void UseBrushPattern(const CFbsBitmap* aBitmap)=0;
	virtual void DiscardBrushPattern()=0;
//
// Move the internal position, as used by DrawLineTo & DrawLineBy, and set by MoveTo,
// MoveBy, DrawLine, DrawLineTo, DrawLineBy and DrawPolyline
	virtual void MoveTo(const TPoint& aPoint)=0;
	virtual void MoveBy(const TPoint& aVector)=0;
	virtual void Plot(const TPoint& aPoint)=0;
//
//  Line drawing subject to pen color, width and style and draw mode
	virtual void DrawArc(const TRect& aRect,const TPoint& aStart,const TPoint& aEnd)=0;
	virtual void DrawLine(const TPoint& aPoint1,const TPoint& aPoint2)=0;
	virtual void DrawLineTo(const TPoint& aPoint)=0;
	virtual void DrawLineBy(const TPoint& aVector)=0;
	virtual void DrawPolyLine(const CArrayFix<TPoint>* aPointList)=0;
	virtual void DrawPolyLine(const TPoint* aPointList,TInt aNumPoints)=0;
//
// Filled outlines
// Outlines subject to pen color, width and style and draw mode
// (set pen to ENullPen for no outline)
// Fill subject to brush style (color, hash or pattern) and origin and
// drawing mode (set brush to ENullBrush for no fill)
	virtual void DrawPie(const TRect& aRect,const TPoint& aStart,const TPoint& aEnd)=0;
	virtual void DrawEllipse(const TRect& aRect)=0;
	virtual void DrawRect(const TRect& aRect)=0;
	virtual void DrawRoundRect(const TRect& aRect,const TSize& aCornerSize)=0;
	virtual TInt DrawPolygon(const CArrayFix<TPoint>* aPointList,TFillRule aFillRule=EAlternate)=0;
	virtual TInt DrawPolygon(const TPoint* aPointList,TInt aNumPoints,TFillRule aFillRule=EAlternate)=0;
//
// Uses the bitmap's Twips size and does a "stretch" blit in general
	virtual void DrawBitmap(const TPoint& aTopLeft,const CFbsBitmap* aSource)=0;
	virtual void DrawBitmap(const TRect& aDestRect,const CFbsBitmap* aSource)=0;
	virtual void DrawBitmap(const TRect& aDestRect,const CFbsBitmap* aSource,const TRect& aSourceRect)=0;

	virtual void DrawText(const TDesC& aText,const TPoint& aPosition) = 0;
	virtual void DrawText(const TDesC& aText,const TRect& aBox,TInt aBaselineOffset,TTextAlign aAlignment = ELeft,
						  TInt aLeftMargin = 0) = 0;

	IMPORT_C virtual void DrawText(const TDesC& aText,const TPoint& aPosition,const TDrawTextParam& aParam);
	IMPORT_C virtual void Reserved();
	IMPORT_C TInt DrawTextExtended(const TDesC& aText,const TPoint& aPosition,
								   const TDrawTextExtendedParam& aParam);
	};

// generic bitmap-based classes

class CBitmapContext : public CGraphicsContext
	{
public:
	virtual void Clear()=0;
	virtual void Clear(const TRect& aRect)=0;
	virtual void CopyRect(const TPoint& aOffset,const TRect& aRect)=0;
	virtual void BitBlt(const TPoint& aPoint,const CFbsBitmap* aBitmap)=0;
	virtual void BitBlt(const TPoint& aPoint,const CFbsBitmap* aBitmap,const TRect& aRect)=0;
	virtual void BitBltMasked(const TPoint& aPoint,const CFbsBitmap* aBitmap,const TRect& aSourceRect,const CFbsBitmap* aMaskBitmap,TBool aInvertMask)=0;
	virtual void SetFaded(TBool aFaded)=0;
	virtual void SetFadingParameters(TUint8 aBlackMap,TUint8 aWhiteMap)=0;
	};

class CBitmapDevice : public CGraphicsDevice
	{
public:
	virtual void GetPixel(TRgb& aColor,const TPoint& aPixel) const=0;
	virtual void GetScanLine(TDes8& aBuf,const TPoint& aStartPixel,TInt aLength,TDisplayMode aDispMode) const=0;
	virtual TInt AddFile(const TDesC& aName,TInt& aId)=0;
	virtual void RemoveFile(TInt aId=0)=0;
	virtual TInt GetNearestFontInPixels(CFont*& aFont,const TFontSpec& aFontSpec)=0;
	virtual TInt FontHeightInPixels(TInt aTypefaceIndex,TInt aHeightIndex) const=0;
    inline TInt CreateBitmapContext(CBitmapContext*& aGC);
	};

class TMargins
    {
public:
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	IMPORT_C TBool operator==(const TMargins& aMargins) const;
	IMPORT_C TBool operator!=(const TMargins& aMargins) const;
public:
	TInt iLeft;
	TInt iRight;
    TInt iTop;
	TInt iBottom;
	};

class TPictureCapability
	{
public:
	enum TScalingType
		{
		ENotScaleable,
		EFullyScaleable,
		EScaleableMaintainingAspectRatio
		};
public:
	inline TPictureCapability(TScalingType aScalingType,TBool aCroppable);
public:
	TScalingType iScalingType;
	TBool iIsCroppable;
	};

class CPicture : public CBase
    {
public:
	enum TDetach
		{
		EDetachFull,
		EDetachDraw
		};
public:
	IMPORT_C virtual ~CPicture();
	virtual void Draw(CGraphicsContext& aGc,const TPoint& aTopLeft,const TRect& aClipRect,MGraphicsDeviceMap* aMap) const=0;
	IMPORT_C virtual TStreamId StoreL(CStreamStore& aStore) const; // assumes no sub streams
	virtual void DetachFromStoreL(TDetach /*aDegree*/=EDetachFull) {}
	virtual void ExternalizeL(RWriteStream& aStream) const =0;
	virtual void GetOriginalSizeInTwips(TSize& aSize) const =0;
	IMPORT_C virtual void SetScaleFactor(TInt aScaleFactorWidth,TInt aScaleFactorHeight); // does nothing
	IMPORT_C virtual void SetCropInTwips(const TMargins& aMargins); // does nothing
	IMPORT_C virtual TPictureCapability Capability() const; // no scale, no crop
	IMPORT_C virtual void GetCropInTwips(TMargins& aMargins) const; // returns no crop
	IMPORT_C virtual TInt ScaleFactorWidth() const; // returns no scaling
	IMPORT_C virtual TInt ScaleFactorHeight() const; // returns no scaling
	IMPORT_C virtual TBool LineBreakPossible(TUint aClass,TBool aBeforePicture,TBool aHaveSpaces) const;
	IMPORT_C virtual void Reserved();

	IMPORT_C void GetSizeInPixels(MGraphicsDeviceMap* aMap, TSize& aSize) const;
	IMPORT_C void SetSizeInPixels(MGraphicsDeviceMap* aMap, const TSize& aSize);
	IMPORT_C void AddCropInPixels(MGraphicsDeviceMap* aMap, const TMargins& aMargins);
	IMPORT_C void GetSizeInTwips(TSize& aSize) const;
	IMPORT_C void SetSizeInTwips(const TSize& aSize);
	IMPORT_C void ResetToOriginal();
protected:
	IMPORT_C CPicture();
	};

// Encodes a picture type and the stream ID of the picture body.
// The stream ID can be replaced by a pointer.

class TPictureHeader
	{
public:
	IMPORT_C TPictureHeader();
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	IMPORT_C void DeletePicture();
public:
	TSwizzle<CPicture> iPicture;
	TUid iPictureType;
	TSize iSize;
	};

// An abstract interface for instantiating & restoring new CPicture objects.
// A concrete derived class will create picture of the specific type.

class MPictureFactory
	{
public:
	virtual void NewPictureL(TPictureHeader& aHeader,const CStreamStore& aDeferredPictureStore)const=0;
	};

// printing classes

const TInt KMaxPrinterModelNameLength=0x20;
typedef TBuf<KMaxPrinterModelNameLength> TPrinterModelName;

class TPageSpec
	{
public:
	enum TPageOrientation { EPortrait, ELandscape };
public:
	IMPORT_C TPageSpec();
	IMPORT_C TPageSpec(TPageOrientation aOrientation,const TSize& aSize);
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	IMPORT_C TSize OrientedPageSize() const;
	IMPORT_C TBool operator==(const TPageSpec& aPageSpec) const;
	IMPORT_C TBool operator!=(const TPageSpec& aPageSpec) const;
public:
	TSize iPortraitPageSize;
	TPageOrientation iOrientation;
	};

class TBandAttributes
	{
public:
	TRect iRect;
	TBool iTextIsIgnored; // any text drawing to this band is ignored
	TBool iGraphicsIsIgnored; // any graphics drawing to this band is ignored
	TBool iFirstBandOnPage;
	};

class CPrinterPort : public CBase
	{
public:
	virtual void WriteRequest(const TDesC8& aBuf,TRequestStatus& aRequestStatus)=0;
	virtual void Cancel()=0;
	};

class TPrinterModelEntry
	{
public:
	TPrinterModelName iModelName;
	TBool iRequiresPrinterPort;
	TUid iUid;
public:
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	};

class TPrinterModelHeader
	{
public:
	TPrinterModelEntry iEntry;
	TStreamId iModelDataStreamId;
public:
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	};

class CPrinterControl : public CBase
	{
public:
	enum TMoreOnPage {EMoreOnPage,ENoMoreOnPage};
public:
	IMPORT_C ~CPrinterControl();
	// print control functions
	virtual TInt BandsPerPage()=0;
	virtual TMoreOnPage QueueGetBand(TRequestStatus& aStatus, TBandAttributes& aBand)=0; // returns affirmative if more to print on current page
	virtual void QueueEndPrint(TRequestStatus& aStatus)=0; // Called at finish to flush buffer, tidy up printer etc.
	virtual void AbortPrint()=0; // tidy up synchronously in a short time, return success code
protected:
	IMPORT_C CPrinterControl(CPrinterPort* aPrinterPort);
protected:
	enum TState {ENotPrinting, EPrinting};
	TState iState;
	CPrinterPort* iPrinterPort;
	};

class CDictionaryStore;
class RFs;

class CPrinterDevice : public CGraphicsDevice
	{
public:
	IMPORT_C ~CPrinterDevice();
	inline TPageSpec CurrentPageSpecInTwips() const {return(iCurrentPageSpecInTwips);}
	IMPORT_C virtual void SelectPageSpecInTwips(const TPageSpec& aPageSpec);
	IMPORT_C virtual TRect PrintablePageInPixels() const;
	virtual TPrinterModelEntry Model()const =0;
	virtual TInt SetModel(const TPrinterModelHeader& aModel,CStreamStore& aStore)=0;
	virtual void CreateControlL(CPrinterPort* aPrinterPort)=0;
	IMPORT_C virtual void DeleteControl();
	virtual void InternalizePropertiesL(RReadStream& /*aStream*/) {}
	virtual void ExternalizePropertiesL(RWriteStream& /*aStream*/) const {}
	IMPORT_C void RestorePropertiesL();
	IMPORT_C void StorePropertiesL() const;
protected:
	IMPORT_C CPrinterDevice();
public:
	CPrinterControl* iControl;
protected:
	TPageSpec iCurrentPageSpecInTwips;
	};

class CPrinterModelList : public CBase
	{
public:
    virtual TInt ModelCount() const=0;
    virtual const TPrinterModelEntry operator[](TInt anIndex)=0;
	virtual TInt UidToNum(TUid aModelUid) const=0;
    };

class MPageRegionPrinter
// Subclassed by an application to print the body of each page band by band
	{
public:
	virtual void PrintBandL(CGraphicsDevice* aDevice,TInt aPageNo,const TBandAttributes& aBandInPixels)=0;
	};

const TInt KPdrStoreFileUidVal=268435514;

const TInt KPdlUidVal=268450588;
const TInt KUdlUidVal=268450589;

class CPrinterDriverUI : public CBase
	{
protected:
	IMPORT_C CPrinterDriverUI();
public:
	IMPORT_C virtual TBool BeforePrintL();
	IMPORT_C virtual void AfterPrintL();
	IMPORT_C virtual void SetPropertiesL();
	IMPORT_C virtual TBool CanSetProperties();
	virtual TInt SetPrinterDevice(CPrinterDevice* aPrinterDevice)=0;
	};
								   
class CFileStore;
class CPrinterDriver : public CBase
    {
public:
	IMPORT_C static CPrinterDriver* NewL();
	IMPORT_C ~CPrinterDriver();
	IMPORT_C void OpenPdrL(const TDesC &aName);
	IMPORT_C void Close();
	IMPORT_C TInt NumModels() const;
	IMPORT_C TPrinterModelEntry Model(TInt aNum) const;
	inline CPrinterDevice* PrinterDevice() {return iPrinterDevice;}
	IMPORT_C CPrinterDevice* CreatePrinterDeviceL(TUid aModelUid);
	IMPORT_C CPrinterDriverUI* CreatePrinterDriverUIL();
private:
	CPrinterDriver();
	void DeletePrinterDevice();
	void DoOpenPdrL(const TDesC &aName);
	void DoCreatePrinterDeviceL(TUid aModelUid);
	void LoadLibraryL(RLibrary& aLibrary,const TDesC& aExt,TUid aUid2);
private:
	RFs iFs;
	CFileStore *iPdrStore;
	TInt iNumModels;
	TPrinterModelHeader* iModelList;
	TFileName iPdlName;
	TUid iPdlUid;
	RLibrary iPdlLibrary;
	CPrinterDevice* iPrinterDevice;
	RLibrary iUdlLibrary;
	};

class RResourceFile;
class CPdrModelList : public CPrinterModelList
	{
public:
	IMPORT_C static CPdrModelList* NewL();
	IMPORT_C virtual ~CPdrModelList();
	//
    IMPORT_C TInt ModelCount() const;
    IMPORT_C const TPrinterModelEntry operator [] (TInt anIndex);
	IMPORT_C TInt UidToNum(TUid aModelUid) const;  // returns KErrNotFound the model uid is not matched

	IMPORT_C void AddDirectoryL(const TDesC& aDir);
	IMPORT_C CPrinterModelList* ScanForModelsL();
	IMPORT_C CPrinterDriver* CreatePrinterDriverL(TInt anIndex);
private:
	CPdrModelList();
	void ConstructL();
private:
	class TFileEntry
		{
	public:
		TFileName iFileName;
		TDesC* iDirectory;
		};
	class TModelEntry
		{
	public:
		TPrinterModelEntry iEntry;
		TFileEntry* iFile; 
		};
private:
	void ScanDirectoryL(TInt aDirIndex);
	void ListModelsL(TInt aFileIndex, TParse& aParser, TFileName& aNameOfLoadedResourceFile, TFileName& aTempFileName, RResourceFile& aResourceFile, HBufC8*& aResource);
	HBufC* NewPathBufL(const TFileEntry& aFileEntry);
private:
	CArrayFixSeg<TModelEntry>* iModelArray;
	CArrayFixFlat<TFileEntry>* iFileArray;
	CArrayFixFlat<HBufC*>* iDirectoryArray;
	RFs iFileServer;
	};

class TZoomFactor : public MGraphicsDeviceMap
	{
public:
	IMPORT_C TZoomFactor();
	IMPORT_C ~TZoomFactor();
	inline TZoomFactor(const MGraphicsDeviceMap* aDevice);
	IMPORT_C TInt ZoomFactor() const;
	IMPORT_C void SetZoomFactor(TInt aZoomFactor);
	inline void SetGraphicsDeviceMap(const MGraphicsDeviceMap* aDevice);
	inline const MGraphicsDeviceMap* GraphicsDeviceMap() const;
	IMPORT_C void SetTwipToPixelMapping(const TSize& aSizeInPixels,const TSize& aSizeInTwips);
	IMPORT_C TInt HorizontalTwipsToPixels(TInt aTwipWidth) const;
	IMPORT_C TInt VerticalTwipsToPixels(TInt aTwipHeight) const;
	IMPORT_C TInt HorizontalPixelsToTwips(TInt aPixelWidth) const;
	IMPORT_C TInt VerticalPixelsToTwips(TInt aPixelHeight) const;
	IMPORT_C TInt GetNearestFontInTwips(CFont*& aFont,const TFontSpec& aFontSpec);
	IMPORT_C void ReleaseFont(CFont* aFont);
public:
	enum {EZoomOneToOne=1000};
private:
	TInt iZoomFactor;
	const MGraphicsDeviceMap* iDevice;
	};

#include <gdi.inl>
#endif // __GDI_H__
