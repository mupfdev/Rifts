/*
TAGMA.H

Copyright (C) 1999 Symbian Ltd. All rights reserved.
*/

/*
The main header file for TAGMA, the low-level text formatting engine for EPOC.
'Tm' stands for 'TAGMA' and is the standard prefix for TAGMA classes, after
the C, T, or whatever.
*/

#ifndef __TAGMA_H__
#define __TAGMA_H__ 1

#include <e32base.h>
#include <openfont.h>
#include <txtfrmat.h>
#include <txtstyle.h>

// forward declarations
class TTmLineInfo;
class CTmTextImp;
class RWindow;
class RWsSession;
class RParagraphStyleInfo;
class CStyleList;

// constants and characters for additional Avkon specific styles.
const TInt KUnknownInlineFepTextStyle=0x1000000;
_LIT(KTextForUnknownInlineFepTextStyle,"?");

/**
A bit mask for selecting one or more attributes of a TTmCharFormat object.
*/
class TTmCharFormatMask
	{
public:
	/** Constants, that are also bit assignments, representing character format attributes */
	enum TAttrib
		{
		EFontName = 0x1,
		EFontCoverage = 0x2,
		EBold = 0x4,
		EItalic = 0x8,
		ESerif = 0x10,
		EMonoWidth = 0x20,
		EHeight = 0x40,
		EPrintPosition = 0x80,
		ETextColor = 0x100,
		EBackgroundColor = 0x200,
		EBackground = 0x400,
		EUnderline = 0x800,
		EStrikethrough = 0x1000,
		EShadow = 0x2000,
		EUserDefinedEffects = 0x4000,
		ELanguage = 0x8000,
		EPictureAlignment = 0x10000
		};

	inline TTmCharFormatMask();
	IMPORT_C TTmCharFormatMask(const TCharFormatMask& aMask);
	IMPORT_C void GetTCharFormatMask(TCharFormatMask& aMask) const;
	inline void Clear(TAttrib aAttrib);
	inline void Set(TAttrib aAttrib);
	inline TBool IsSet(TAttrib aAttrib); 

	TUint iFlags;
	};

/**
A character format; all dimensions are in twips. A character format object stores all text style
attributes that can differ from any one character to the next. Attributes that affect an entire
paragraph only are kept in RTmParFormat objects.
*/
class TTmCharFormat
	{
public:
	/** Bit assignments for effects */
	enum
		{
		EBackground = 1,				// draw the background in the background colour
		ERounded = 2,					// draw the background if any with rounded corners
		EUnderline = 4,					// underline the text
		EStrikethrough = 8,				// draw a line through the text
		EShadow = 16,					// draw a drop shadow
		EUserDefinedMask = 0xFF000000,	// the top 8 bits are reserved for user-defined effects
		EUserDefinedShift = 24			// shift user-defined effects by this
		};

	/** Picture alignment */
	enum TPictureAlignment
		{
		EPictureAlignBaseline,
		EPictureAlignTop,
		EPictureAlignBottom,
		EPictureAlignCenter
		};

	IMPORT_C TTmCharFormat();
	IMPORT_C TTmCharFormat(const TDesC& aFontName,TInt aFontHeight);
	IMPORT_C void operator=(const TCharFormat& aFormat);
	inline TTmCharFormat(const TCharFormat& aFormat);
	IMPORT_C void GetTCharFormat(TCharFormat& aFormat) const;
	IMPORT_C TBool operator==(const TTmCharFormat& aFormat) const;
	inline TBool operator!=(const TTmCharFormat& aFormat) const;

	TOpenFontSpec iFontSpec;
	TLogicalRgb iTextColor;
	TLogicalRgb iBackgroundColor;		// used only when EBackground flag is set in iEffects
	TUint iEffects;						// bit flags as defined above;
										// note that effects NEVER change character metrics and so can
										// be ignored when measuring text
	TUint iLanguage;					// language used for proofing
	TPictureAlignment iPictureAlignment;// vertical alignment of embedded objects
	TUint iTag;							// tag for use by URL parsers, etc.; a way of marking a range of
										// text without using any typographic attributes
	};

/**
A tabulation position, measured from the start of the line, which will be the left end
for paragraphs with a left-to-right base direction, and vice versa.
*/
class TTmTab
	{
public:
	/** Tab type */
	enum TType
		{
		EStandardTab,	// text is placed after the tab, in the current paragraph direction
		ECenterTab,		// text is centred around the tab
		EReverseTab		// text is placed before the tab, in the current paragraph direction
		};

	inline TTmTab();
	inline TTmTab(const TTabStop& aTab);
	IMPORT_C void operator=(const TTabStop& aTab);
	IMPORT_C void GetTTabStop(TTabStop& aTab) const;
	IMPORT_C TBool operator==(const TTmTab& aTab) const;
	inline TBool operator!=(const TTmTab& aTab) const;

	TInt iPosition;
	TType iType;
	};

/**
A bullet or other label inserted automatically at the start of a paragraph. As well as an
actual bullet, it can be a number or a letter.
*/
class TTmBullet
	{
public:
	/** Bullet style */
	enum TStyle
		{
		EBulletStyle,
		EArabicNumberStyle,
		ESmallRomanNumberStyle,
		ECapitalRomanNumberStyle,
		ESmallLetterStyle,
		ECapitalLetterStyle
		};

	/** The alignment within the margin of bullets or other text used in TTmBullet objects */
	enum TAlignment
		{
		ELeftAlign,
		ECenterAlign,
		ERightAlign
		};

	IMPORT_C TTmBullet();
	IMPORT_C void operator=(const TBullet& aBullet);
	inline TTmBullet(const TBullet& aBullet);
	IMPORT_C void GetTBullet(TBullet& aBullet) const;
	IMPORT_C TBool operator==(const TTmBullet& aBullet) const;
	inline TBool operator!=(const TTmBullet& aBullet) const;

	TChar iCharacterCode;		// the bullet or other symbol used if iStyle is EBulletStyle
	TOpenFontSpec iFontSpec;
	TBool iHangingIndent;
	TLogicalRgb iColor;
	TStyle iStyle;				// is this a bullet or a number or a letter?
	TInt iStartNumber;			// the number of the first paragraph in a run of paragraphs in this style
	TAlignment iAlignment;		// alignment of the bullet or number within the margin
	};


/**
A specification of a paragraph border rule: that is, a line or lines drawn above, below, to the left, or to the right
of a paragraph.
*/
class TTmParBorder
	{
public:
	/** Paragraph border style */
	enum TStyle
		{
		ESolidStyle,
		EDoubleStyle,
		EDotStyle,
		EDashStyle,
		EDotDashStyle,
		EDotDotDashStyle
		};

	IMPORT_C TTmParBorder();
	IMPORT_C void operator=(const TParaBorder& aBorder);
	inline TTmParBorder(const TParaBorder& aBorder);
	IMPORT_C void GetTParaBorder(TParaBorder& aBorder) const;
	IMPORT_C TBool operator==(const TTmParBorder& aBorder) const;
	inline TBool operator!=(const TTmParBorder& aBorder) const;

	TStyle iStyle;
	TInt iWeight;
	TLogicalRgb iColor;
	TBool iAutoColor;
	};

/**
A bit mask for selecting one or more attributes of an RTmParFormat.
*/
class TTmParFormatMask
	{
public:
	/** Constants, that are also bit assignments, representing paragraph format attributes */
	enum TAttrib
		{
		EAlignment = 0x1,
		EDirection = 0x2,
		EKeepTogether = 0x4,
		EKeepWithNext = 0x8,
		EStartNewPage = 0x10,
		EWidowOrphan = 0x20,
		ENoWrap = 0x40,
		EExactLineSpacing = 0x80,
		EPixelLineSpacing = 0x100,
		ELeadingMargin = 0x200,
		ETrailingMargin = 0x400,
		EFirstLineIndent = 0x800,
		ELineSpacing = 0x1000,
		ESpaceAbove = 0x2000,
		ESpaceBelow = 0x4000,
		ETabSize = 0x8000,
		EBorderMargin = 0x10000,
		ETabList = 0x20000,
		EBullet = 0x40000,
		EBorder = 0x80000
		};

	inline TTmParFormatMask();
	IMPORT_C TTmParFormatMask(const TParaFormatMask& aMask);
	IMPORT_C void GetTParaFormatMask(TParaFormatMask& aMask) const;
	inline void Clear(TAttrib aAttrib);
	inline void Set(TAttrib aAttrib);
	inline TBool IsSet(TAttrib aAttrib);

	TUint iFlags;
	};

/**
Paragraph format; all dimensions are in twips unless otherwise specified.
*/
class RTmParFormat
	{
public:
	/** Index used to select one of the four borders of a paragraph */
	enum TBorderIndex
		{
		ETopBorder = 0,
		EBottomBorder = 1,
		ELeadingBorder = 2,
		ETrailingBorder = 3,
		};

	/** Bit assignments for RTmParFormat::iFlags */
	enum
		{
		ERightToLeft = 1,				// the base direction is right to left (as for Arabic and Hebrew)
		EKeepTogether = 2,				// page breaks are not allowed in the paragraph
		EKeepWithNext = 4,				// no page break can occur between a paragraph of this type and the next
		EStartNewPage = 8,				// insert a page break before the paragraph
		EWidowOrphan = 16,				// suppress widows and orphans
		ENoWrap = 32,					// suppress wrapping
		EExactLineSpacing = 64,			// line spacing is exact (as opposed to 'at least')
		EPixelLineSpacing = 128			// line spacing is in pixels (as opposed to twips)
		};

	/** The aligment of a paragraph's text. */
	enum TAlignment
		{
		EAlignNormal,
		EAlignCenter,
		EAlignReverse,
		EAlignJustify
		};

	IMPORT_C RTmParFormat();
	IMPORT_C void Close();
#ifdef _DEBUG
	inline ~RTmParFormat();
#endif
	IMPORT_C void CopyL(const RTmParFormat& aFormat);
	IMPORT_C void CopyL(const CParaFormat& aFormat);
	IMPORT_C void GetCParaFormatL(CParaFormat& aFormat) const;
	IMPORT_C TBool operator==(const RTmParFormat& aFormat) const;
	inline TBool operator!=(const RTmParFormat& aFormat) const;
	IMPORT_C TInt Tabs() const;
	inline const TTmTab& Tab(TInt aIndex) const;
	inline const TTmBullet* Bullet() const;
	inline const TTmParBorder* Border(TBorderIndex aIndex) const;
	IMPORT_C TBool HaveBorders() const;
	inline TBool RightToLeft() const;

	TAlignment iAlignment;
	TUint iFlags;						// bit flags as defined above
	TInt iLeadingMargin;				// left margin, or right if right-to-left
	TInt iTrailingMargin;				// right margin, or left if right-to-left
	TInt iFirstLineIndent;				// added to first line leading margin
	TInt iLineSpacing;					// distance between baselines
	TInt iSpaceAbove;					// space above the paragraph
	TInt iSpaceBelow;					// space below the paragraph
	TInt iTabSize;						// default size of tabs
	TInt iBorderMargin;					// distance between the text and the border if any
	TLogicalRgb iBackgroundColor;		// paragraph background colour

private:
	RTmParFormat(const RTmParFormat& aFormat);	// deliberately unimplemented
	void operator=(const RTmParFormat& aFormat);// deliberately unimplemented

	RArray<TTmTab>* iTabList;			// custom tabs if any
	TTmBullet* iBullet;					// bullet if any
	TTmParBorder* iBorder[4];			// borders if any
	};

/**
The text customization interface. You can customize the colors, word spacing, line breaking,
line height calculation, background drawing, and text appearance, of a text object by supplying
an implementation of the MTmCustom class, either directly (as in CTmText::CustomizeL, which takes
a pointer to MTmCustom) or indirectly, making use of the fact that MTmSource is derived from MTmCustom
(as in CTmTextLayout::SetTextL, which takes a reference to MTmSource).
*/
class MTmCustom
	{
public:
	class TLineHeightParam
		{
	public:
		inline TLineHeightParam();

		TInt iMaxCharHeight;			// height of the highest character in the line
		TInt iMaxCharDepth;				// depth of the deepest character in the line
		TInt iMaxTopPictureHeight;		// height plus depth of the tallest top-aligned picture
		TInt iMaxBottomPictureHeight;	// height plus depth of the tallest bottom-aligned picture
		TInt iMaxCenterPictureHeight;	// height plus depth of the tallest centred picture
		TInt iFontMaxCharHeight;		// height of the tallest character of any in the fonts in the line
		TInt iFontMaxCharDepth;			// depth of the deepest character of any in the fonts in the line
		TInt iFontMaxAscent;			// maximum ascent of the fonts in the line
		TInt iFontMaxDescent;			// maximum descent of the fonts in the line
		TInt iDesiredLineHeight;		// desired precise or minimum line height
		TBool iExactLineHeight;			// true if the line height must be precise
		};

	/**
	The Unicode line breaking classes; see Unicode Technical Report 14.
	Not a named enumerated type, so that overriding applications can add new
	line breaking classes freely.
	*/
	enum
		{
		EOpLineBreakClass,
		EClLineBreakClass,
		EQuLineBreakClass,
		EGlLineBreakClass,
		ENsLineBreakClass,
		EExLineBreakClass,
		ESyLineBreakClass,
		EIsLineBreakClass,
		EPrLineBreakClass,
		EPoLineBreakClass,
		ENuLineBreakClass,
		EAlLineBreakClass,
		EIdLineBreakClass,
		EInLineBreakClass,
		EHyLineBreakClass,
		EBaLineBreakClass,
		EBbLineBreakClass,
		EB2LineBreakClass,
		EZwLineBreakClass,
		ECmLineBreakClass,
		EBkLineBreakClass,
		ECrLineBreakClass,
		ELfLineBreakClass,
		ESgLineBreakClass,
		ECbLineBreakClass,

		/** Space; intervening characters of class Sp are indicated by aHaveSpaces in LineBreakPossible. */
		ESpLineBreakClass, 

		/** Needs context; runs of characters of class Sa are passed to GetLineBreakInContext. */
		ESaLineBreakClass,

		EAiLineBreakClass,

		/** The Xx class is used when the class is unknown; e.g.; outside the provided context. */
		EXxLineBreakClass,

		/** The number of Unicode line break classes. */
		ELineBreakClasses
		};

	IMPORT_C virtual TRgb SystemColor(TUint aColorIndex,TRgb aDefaultColor) const;
	IMPORT_C virtual TInt Stretch(TUint aChar) const;
	IMPORT_C virtual TUint Map(TUint aChar) const;
	IMPORT_C virtual void SetLineHeight(const TLineHeightParam& aParam,TInt& aAscent,TInt& aDescent) const;
	IMPORT_C virtual void DrawBackground(CGraphicsContext& aGc,const TPoint& aTextLayoutTopLeft,const TRect& aRect,
										 const TLogicalRgb& aBackground,TRect& aRectDrawn) const;
	IMPORT_C virtual void DrawLineGraphics(CGraphicsContext& aGc,const TPoint& aTextLayoutTopLeft,const TRect& aRect,
										   const TTmLineInfo& aLineInfo) const;
	IMPORT_C virtual void DrawText(CGraphicsContext& aGc,const TPoint& aTopLeft,const TRect& aRect,
								   const TTmLineInfo& aLineInfo,const TTmCharFormat& aFormat,
								   const TDesC& aText,const TPoint& aTextOrigin,TInt aExtraPixels) const;
	IMPORT_C virtual void DrawPicture(CGraphicsContext& aGc,
		const TPoint& aTextLayoutTopLeft, const TRect& aRect,
		MGraphicsDeviceMap& aDevice, const CPicture& aPicture) const;
	IMPORT_C virtual TUint LineBreakClass(TUint aCode,TUint& aRangeStart,TUint& aRangeEnd) const;
	IMPORT_C virtual TBool LineBreakPossible(TUint aPrevClass,TUint aNextClass,TBool aHaveSpaces) const;
	IMPORT_C virtual TBool GetLineBreakInContext(const TDesC& aText,TInt aMinBreakPos,TInt aMaxBreakPos,
												 TBool aForwards,TInt& aBreakPos) const;
	IMPORT_C virtual TBool IsHangingCharacter(TUint aChar) const;

	// non-virtuals
	IMPORT_C void SetPenColor(CGraphicsContext& aGc,TLogicalRgb aColor) const;
	IMPORT_C void SetBrushColor(CGraphicsContext& aGc,TLogicalRgb aColor) const;
	IMPORT_C TRgb SystemColor(TLogicalRgb aColor) const;

private:
	IMPORT_C void MTmSource_Reserved_1();
	IMPORT_C void MTmSource_Reserved_2();
	};

/**
MTmSource is an interface class that must be implemented by users of CTmTextLayout to provide text content and
attributes. MTmSource is derived from MTmCustom, which contains the functions to customise the layout and display,
so that this can be done in CTmText without affecting the content. 
*/
class MTmSource: public MTmCustom
	{
public:
	/** Label type used in SelectLabelMode */
	enum TLabelType
		{
		/** Not a label; used for TLabelTypes not yet assigned. */
		ENoLabel,

		/** Paragraph label of the type supported by FORM. */
		EParLabel
		};

	enum
		{
		/**
		The maximum number of characters supplied to GetLineBreak, after aMaxBreakPos,
		and after trailing whitespace, to provide context for line breaking decisions.
		*/
		ELineBreakContext = 32
		};

	// pure virtuals
	
	/** Return the device used to format the text. */
	virtual MGraphicsDeviceMap& FormatDevice() const = 0;

	/**
	Return the device used to draw the text and when converting between x-y coordinates and document positions.
	If the formatting and interpreting devices are different, text is scaled appropriately when it is drawn;
	this allows text to be formatted for printer fonts and displayed on the screen, giving a wysiwyg print preview.
	*/
	virtual MGraphicsDeviceMap& InterpretDevice() const = 0;

	/** Return the length of the document in characters. */
	virtual TInt DocumentLength() const = 0;

	/**
	Return at least one character of text, but preferably as many as possible, starting at aPos. Put its character
	format in aFormat. The text must be a run of characters sharing the same character format.
	*/
	virtual void GetText(TInt aPos,TPtrC& aText,TTmCharFormat& aFormat) const = 0;

	/**
	Return the paragraph format of the paragraph containing aPos. End-of-paragraph characters belong to the preceding
	paragraph.
	*/
	virtual void GetParagraphFormatL(TInt aPos,RTmParFormat& aFormat) const = 0;

	/**
	Return the document position of the start of the paragraph containing aPos. End-of-paragraph characters belong to
	the preceding paragraph.
	*/
	virtual TInt ParagraphStart(TInt aPos) const = 0;

	// ordinary virtuals
	IMPORT_C virtual CPicture* PictureL(TInt aPos) const;
	IMPORT_C virtual TInt GetPictureSizeInTwipsL(TInt aPos,TSize& aSize) const;
	IMPORT_C virtual TBool SelectLabelMode(TLabelType aType,TInt aPos);
	IMPORT_C virtual void CancelLabelMode();
	IMPORT_C virtual void GetLabelMetrics(TLabelType aType,TSize& aLabelSize,TInt& aMarginSize) const;
	IMPORT_C virtual TBool PageBreakInRange(TInt aStartPos,TInt aEndPos) const;

	// non-virtuals
	IMPORT_C TInt ParagraphEnd(TInt aPos) const;
	IMPORT_C TBool GetLineBreakL(const TDesC& aText,TInt aDocPos,TInt aMinBreakPos,TInt aMaxBreakPos,TBool aForwards,
								 TInt& aBreakPos,TInt& aHangingChars,TInt& aBreakPosAfterSpaces) const;
	IMPORT_C static void GetStandardLineBreak(const TDesC& aText,TInt aMinBreakPos,TInt aMaxBreakPos,
											  TInt& aBreakPos,TInt& aNextLineStart);
	};

/**
@internal
*/
class CTmBufSeg: public CBufSeg
	{
public:
	inline CTmBufSeg(TInt aExpandSize);
	TInt MemoryUsed() const;
	};

/**
@internal
*/
class CTmCode: public CBase
	{
public:
	inline ~CTmCode();
	void InsertByteL(TUint8 aByte,TInt aPos);
	TInt InsertNumberL(TInt aNumber,TInt aPos);
	TInt InsertRectL(const TRect& aRect,TInt aPos);
	void AppendByteL(TUint8 aByte);
	TInt AppendNumberL(TInt aNumber);
	TInt AppendRectL(const TRect& aRect);
	void ChangeL(TInt aStart,TInt aEnd,CTmCode& aNewCode);
	TInt MemoryUsed() const;
	TInt Size() const;
	void Delete(TInt aPos,TInt aLength);
	void Reset();
	inline TPtr8 Ptr(TInt aPos);
	void CreateBufferL();
	inline CBufBase* Buffer();
	inline const CBufBase* Buffer() const;

private:
	enum
		{
		EExpandSize = 512
		};
	TInt WriteNumber(TInt aNumber,TUint8* aBuffer);

	CTmBufSeg* iBuffer;
	};

/**
Formatting parameters used when formatting part of a layout object.
*/
class TTmFormatParamBase
	{
public:
	enum
		{
		EWrap = 1,							// wrap the text at iWrapWidth
		EAtLeastMaxHeight = 2,				// stop adding text only when iMaxHeight has been reached or exceeded
		ETruncateWithEllipsis = 4,			// truncate any text that sticks out; see iEllipsis below
		ELegalLineBreaksOnly = 8			// break only at allowed line breaks, even if that
											// results in the text not fitting the measure
		};

	IMPORT_C TTmFormatParamBase();
	inline TBool IsWrapping() const;
	inline TBool IsTruncatingWithEllipsis() const;
	inline TBool LegalLineBreaksOnly() const;

	TInt iWrapWidth;					// wrapping width of the text including margins and indents, if wrapping is on
	TInt iMaxHeight;					// maximum height of the text
	TInt iMaxLines;						// maximum number of lines to be formatted
	TInt iFlags;						// flags defined above
	TChar iEllipsis;					// if truncating and not 0xFFFF, insert this ellipsis char (defaults to '...').
	};

/**
Formatting parameters used when formatting an entire layout object or creating a section of format code.
*/
class TTmFormatParam: public TTmFormatParamBase
	{
public:
	IMPORT_C TTmFormatParam();
	IMPORT_C TTmFormatParam(const TTmFormatParamBase& aBase);

	TInt iStartChar;					// first character position to be formatted
	TInt iEndChar;						// last character position to be formatted
	TInt iLineInPar;					// starting line number in the paragraph
	};

/**
Additional parameters used when reformatting.
*/
class TTmReformatParam
	{
public:
	IMPORT_C TTmReformatParam();

	TInt iStartChar;					// start of changed text
	TInt iOldLength;					// length of text before the change
	TInt iNewLength;					// length of text after the change
	TBool iMaxExtraLines;				// maximum lines in the partial paragraph after the end of the changed text
										// to format in one go; the remainder can be handled by background formatting
	TBool iParFormatChanged;			// TRUE if the paragraph format of the changed text has changed
	TBool iParInvalid;					// format to the end of the paragraph
	};

/**
Information returned when reformatting
*/
class TTmReformatResult
	{
public:
	IMPORT_C TTmReformatResult();

	TRect iRedrawRect;					// rectangle to be redrawn
	TInt iHeightChange;					// change in height of the reformatted text
	TInt iUnchangedTop;					// y coordinate, before formatting, of the top of text needing no change,
										// including text in any section not yet formatted by this call
	TInt iUnformattedStart;				// start of any unformatted section; KMaxTInt if none
	};

/**
A structure for returning information about a line. One of these is returned by all hit-detection functions. Typically,
after finding the position in the document that corresponds to given x-y coordinates, you will want some more information
like the line's bounding rectangle. When you call, for example, CTmTextLayout::FindXyPos you will receive a	TTmLineInfo
object that will tell you this, and much more.
*/
class TTmLineInfo
	{
public:
	// bit values for iFlags
	enum
		{
		EParStart = 1,
		EParEnd = 2
		};

	inline TTmLineInfo();

	TRect iOuterRect;	// outer enclosing rectangle including margins
	TRect iInnerRect;	// inner enclosing rectangle: the text only
	TInt iBaseline;		// y coordinate of the baseline
	TInt iStart;		// start document position
	TInt iEnd;			// end document position
	TInt iLineNumber;	// line number
	TInt iParNumber;	// paragraph number
	TInt iLineInPar;	// line number in the paragraph
	TInt iParTop;		// y coordinate of the top of the paragraph
	TUint iFlags;		// start of paragraph, end of paragraph, etc.
	};

/**
A structure for holding a document position that can be converted to or from an x-y position.
Leading edges are distinguished from trailing edges so that bidirectional hit testing
and cursor positioning can distinguish between 'after character N', and 'before character
N + 1', which may be some distance apart if N and N + 1 are in runs of opposite directionality.
*/
class TTmDocPos
	{
public:
	inline TTmDocPos();
	inline TTmDocPos(TInt aPos,TBool aLeadingEdge);
	IMPORT_C TBool operator==(const TTmDocPos& aPos) const;
	inline TBool operator!=(const TTmDocPos& aPos) const;
	IMPORT_C TBool operator>(const TTmDocPos& aPos) const;
	IMPORT_C TBool operator>=(const TTmDocPos& aPos) const;
	inline TBool operator<(const TTmDocPos& aPos) const;
	inline TBool operator<=(const TTmDocPos& aPos) const;

	TInt iPos;			// the edge position in the document; 0 ... document length
	TBool iLeadingEdge;	// true if the position is a leading edge
	};

/**
A structure for returning information about a position in a line.
*/
class TTmPosInfo
	{
public:
	TTmDocPos iDocPos;		// the document position
	TPoint iEdge;			// intersection of the character edge at iDocPos with the baseline	
	};

class TTmHighlightExtensions
	{
public:
	inline TTmHighlightExtensions();
	inline void SetAll(TInt aExtension);
	inline void SetLeftExtension(TInt aExtension);
	inline void SetRightExtension(TInt aExtension);
	inline void SetTopExtension(TInt aExtension);
	inline void SetBottomExtension(TInt aExtension);
	inline TInt LeftExtension() const;
	inline TInt RightExtension() const;
	inline TInt TopExtension() const;
	inline TInt BottomExtension() const;
	inline TBool Extends() const;
	inline void ExtendRect(TRect& aRect) const;
	inline void AdjustRect(TRect& aRect) const;
public:
	TInt iLeftExtension;
	TInt iRightExtension;
	TInt iTopExtension;
	TInt iBottomExtension;
	};

/**
 *
 * Cursor placement.
 *
 * Used as an argument to <code>CTextView::SetCursorPlacement()</code>.
 *  */

// CTmTextLayout can return a suggested position and size for a cursor (also known as a caret).
enum TTmCursorPlacement
	{
	/** The text cursor is a vertical line at the insertion position, with its
	height and depth based on the metrics of the previous character in the
	paragraph or if none, the next character.
	 */
	ECursorVertical,		
	/** The text cursor is an underline below the character logically after
	the insertion position.
	 */
	ECursorUnderlineNext,
	/** The text cursor is an underline below the character logically before
	the insertion position.
	 */
	ECursorUnderlinePrev
	};

/**
The text layout for a single rectangular piece of text. The object does not own its text or format attributes but
gets them from an interface class called MTmSource.

There are functions for setting the text, drawing it, and converting between x-y coordinates and document positions.

Ranges

All ranges of character positions and pixels include the start but not the end. This means that if a line is described
by a TTmLineInfo object as starting at document position 345 and ending at 389, character positions 345 to 388 are in
the line; 389 is in the next line if any.

Coordinates and units

All coordinates used in TAGMA classes and function arguments are in pixels and are relative to the origin of the object,
which is the top left corner of the ordinary text, not including paragraph labels. Vertical coordinates increase from
top to bottom.

Document format and positions

A TAGMA document, as supplied by the MTmSource interface, has a length as returned by MTmSource::DocumentLength of
zero or more characters. It consists of Unicode text split into paragraphs by standard Unicode paragraph delimiters
(character value 0x2029), so the number of paragraphs in the entire document is one more than the number of
paragraph delimiters. A document position is a value in the range 0 to one more than the document length.
Lines contain all document positions from their start to one less than their end position. These conventions allow
all lines to end in a delimiter; the last line contains an imaginary paragraph end, which need not be supplied by
the MTmSource interface, at a position equal to the document length. A CTmTextLayout object formatted for an
empty document will thus have a start position (returned by StartChar) of 0 and an end position
(returned by EndChar) of 1.
*/
class CTmTextLayout: public CBase
	{
public:
	IMPORT_C CTmTextLayout();
	IMPORT_C ~CTmTextLayout();
	IMPORT_C void SetTextL(MTmSource& aSource,const TTmFormatParam& aParam);
	IMPORT_C void FormatL(const TTmFormatParamBase& aParam,const TTmReformatParam& aReformatParam,
						  TTmReformatResult& TTmReformatResult);
	IMPORT_C TBool AddParL(const TTmFormatParamBase& aParam,TBool aAtStart,TInt& aHeightIncrease,TInt& aParagraphsIncrease);
	IMPORT_C TBool DeletePar(const TTmFormatParamBase& aParam,TBool aAtStart,TInt aMaxDeletedHeight,TInt& aHeightDecrease);
	IMPORT_C void Clear();
	IMPORT_C void DrawLayout(CGraphicsContext& aGc,const TPoint& aTopLeft,const TRect& aClipRect,
							 const TLogicalRgb* aDocBackground,TBool aDrawParBackground) const;
	IMPORT_C void DrawBackground(CGraphicsContext& aGc,const TPoint& aTopLeft,const TRect& aClipRect,
								 const TLogicalRgb& aBackground) const;
	// deprecated
	IMPORT_C void InvertLayout(CGraphicsContext& aGc, const TPoint& aTopLeft,
		TInt aStartDocPos, TInt aEndDocPos) const;
	IMPORT_C void HighlightSection(CGraphicsContext& aGc, const TPoint& aTopLeft,
		TInt aStartDocPos, TInt aEndDocPos, const TRect& aClipRect) const;
	IMPORT_C void DrawSection(CGraphicsContext& aGc, const TPoint& aTopLeft,
		TInt aStartDocPos, TInt aEndDocPos, const TRect& aClipRect) const;
	// deprecated
	IMPORT_C void InvertLayout(CGraphicsContext& aGc,
		const TPoint& aTopLeft, TInt aStartDocPos,TInt aEndDocPos, const TTmHighlightExtensions& aHighlightExtensions,
		TInt aHighlightStartDocPos, TInt aHighlightEndDocPos) const;
	IMPORT_C void HighlightSection(CGraphicsContext& aGc, const TPoint& aTopLeft,
		TInt aStartDocPos, TInt aEndDocPos, const TRect& aClipRect, const TTmHighlightExtensions& aHighlightExtensions,
		TInt aHighlightStartDocPos, TInt aHighlightEndDocPos) const;
	IMPORT_C void DrawSection(CGraphicsContext& aGc, const TPoint& aTopLeft,
		TInt aStartDocPos, TInt aEndDocPos, const TRect& aClipRect, const TTmHighlightExtensions& aHighlightExtensions,
		TInt aHighlightStartDocPos, TInt aHighlightEndDocPos) const;
	IMPORT_C TBool FindDocPos(const TTmDocPos& aDocPos,TTmPosInfo& aPosInfo,TTmLineInfo& aLineInfo) const;
	IMPORT_C TBool FindXyPos(const TPoint& aXyPos,TTmPosInfo& aPosInfo,TTmLineInfo& aLineInfo) const;
	IMPORT_C TInt Lines() const;
	IMPORT_C TInt Paragraphs() const;
	IMPORT_C TBool DocPosToLine(const TTmDocPos& aDocPos,TTmLineInfo& aLineInfo) const;
	IMPORT_C TBool LineNumberToLine(TInt aLineNumber,TTmLineInfo& aLineInfo) const;
	IMPORT_C TBool ParNumberToLine(TInt aParNumber,TInt aLineInPar,TTmLineInfo& aLineInfo) const;
	IMPORT_C TBool YPosToLine(TInt aYPos,TTmLineInfo& aLineInfo) const;
	// deprecated 7.0
	IMPORT_C TBool GetDisplayedText(TInt aLineNumber,TDes& aText,TInt& aNeeded) const;
	IMPORT_C TBool GetDisplayedTextL(TInt aLineNumber,TDes& aText,TInt& aNeeded) const;
	IMPORT_C void GetMinimumLayoutSizeL(TInt aWrapWidth,TSize& aSize) const;
	IMPORT_C TInt WidthOfWidestLine(TInt aTop = 0,TInt aBottom = KMaxTInt) const;
	IMPORT_C TBool GetNextVisualCursorPos(const TTmDocPos& aDocPos,TTmPosInfo& aInfo,TBool aToLeft) const;
	IMPORT_C TBool GetCursor(const TTmDocPos& aDocPos,TTmCursorPlacement aPlacement,
							 TTmLineInfo& aLineInfo,TPoint& aOrigin,TInt& aWidth,TInt& aAscent,TInt& aDescent) const;
	IMPORT_C TInt MemoryUsed() const;
	inline const TInt StartChar() const;
	inline const TInt EndChar() const;
	inline const TInt LayoutWidth() const;
	inline const TInt LayoutHeight() const;
	inline MTmSource* Source();
	inline const CTmCode& Code() const;
private:
	CTmTextLayout(const CTmTextLayout&); // deliberately unimplemented
	void operator=(const CTmTextLayout&); // deliberately unimplemented

#ifdef _DEBUG
	void Invariant() const;
#else
	void Invariant() const { }
#endif
	void AdjustWidth(const TTmFormatParamBase& aParam,TInt aWidthOfNewText);
	void InvertLayout(CGraphicsContext& aGc, const TPoint& aTopLeft, const TRect& aClipRect, const TTmHighlightExtensions& aHighlightExtensions, TInt aStartDocPos,TInt aEndDocPos, TInt aHighlightStartDocPos, TInt aHighlightEndDocPos) const;
	void InvertRect(CGraphicsContext& aGc, const TPoint& aTopLeft, const TTmHighlightExtensions& aHighlightExtensions, const TRect& aInvertRect,TInt aOriginalHighlightStartPos,TInt aOriginalHighlightEndPos, TInt aNewHighlightStartPos,TInt aNewHighlightEndPos) const;
	void HighlightRect(CGraphicsContext& aGc, const TPoint& aTopLeft, const TRect& aClipRect, const TTmHighlightExtensions& aHighlightExtensions, const TRect& aRect) const;
	void DrawRect(CGraphicsContext& aGc, const TPoint& aTopLeft, const TRect& aClipRect, const TTmHighlightExtensions& aHighlightExtensions, const TRect& aRect) const;
	void DrawRectExcludingHighlight(CGraphicsContext& aGc, const TPoint& aTopLeft, const TRect& aClipRect, const TTmHighlightExtensions& aHighlightExtensions, TInt aHighlightStartPos,TInt aHighlightEndPos, const TRect& aRect) const;
	TBool FindOverlapRect(const TPoint& aTopLeft, const TTmHighlightExtensions& aHighlightExtensions, const TRect& aRect, TInt aHighlightStartPos,TInt aHighlightEndPos, TRect& aOverlapRect) const;

	MTmSource* iSource;				// source of text and text attributes; not owned
	CTmCode iCode;					// the layout bytecode
	TInt iWidth;					// width in pixels
	TInt iHeight;					// height in pixels
	TInt iStartChar;				// start character position in the document
	TInt iEndChar;					// end character position in the document
	};

/**
A mixin class to make it easy for higher-level classes that own a CTmTextLayout object to have enquiry functions
without it being necessary to implement them all as forwarding functions. The owner class just
implements TextLayout and overrides GetOrigin if necessary.

Non-const CTmTextLayout functions like Clear are not included because allowing them to be called on owner classes
would probably put the owner class into an inconsistent state.

The word Layout is prefixed, suffixed or infixed to functions with names that would usually
conflict with owner class names. For example, we have DrawLayout, not Draw, and GetMinimumLayoutSizeL, not
GetMinimumSizeL.
*/
class MTmTextLayoutForwarder
	{
public:
	IMPORT_C void DrawLayout(CGraphicsContext& aGc,const TPoint& aTopLeft,const TRect& aClipRect,
							 const TLogicalRgb* aDocBackground,TBool aDrawParBackground) const;
	IMPORT_C void DrawBackground(CGraphicsContext& aGc,const TPoint& aTopLeft,const TRect& aClipRect,
								 const TLogicalRgb& aBackground) const;
	IMPORT_C void InvertLayout(CGraphicsContext& aGc,const TPoint& aTopLeft,TInt aStartDocPos,TInt aEndDocPos);
	IMPORT_C TBool FindDocPos(const TTmDocPos& aDocPos,TTmPosInfo& aPosInfo,TTmLineInfo& aLineInfo) const;
	IMPORT_C TBool FindXyPos(const TPoint& aXyPos,TTmPosInfo& aPosInfo,TTmLineInfo& aLineInfo) const;
	IMPORT_C TBool DocPosToLine(const TTmDocPos& aDocPos,TTmLineInfo& aLineInfo) const;
	IMPORT_C TBool LineNumberToLine(TInt aLineNumber,TTmLineInfo& aLineInfo) const;
	IMPORT_C TBool ParNumberToLine(TInt aParNumber,TInt aLineInPar,TTmLineInfo& aLineInfo) const;
	IMPORT_C TBool YPosToLine(TInt aYPos,TTmLineInfo& aLineInfo) const;
	IMPORT_C TInt WidthOfWidestLine(TInt aTop = 0,TInt aBottom = KMaxTInt) const;
	IMPORT_C TBool GetNextVisualCursorPos(const TTmDocPos& aDocPos,TTmPosInfo& aInfo,TBool aToLeft) const;
	IMPORT_C TBool GetCursor(const TTmDocPos& aDocPos,TTmCursorPlacement aPlacement,
							 TTmLineInfo& aLineInfo,TPoint& aOrigin,TInt& aWidth,TInt& aAscent,TInt& aDescent) const;

	IMPORT_C TInt Lines() const;
	IMPORT_C TInt Paragraphs() const;
	IMPORT_C TBool GetDisplayedText(TInt aLineNumber,TDes& aText,TInt& aNeeded) const;
	IMPORT_C void GetMinimumLayoutSizeL(TInt aWrapWidth,TSize& aSize) const;
	IMPORT_C const TInt StartChar() const;
	IMPORT_C const TInt EndChar() const;
	IMPORT_C const TInt LayoutWidth() const;
	IMPORT_C const TInt LayoutHeight() const;

private:
	/**
	Return a reference to the CTmTextLayoutObject this MTmTextLayoutForwarder forwards inquiries to.
	*/
	virtual const CTmTextLayout& TextLayout() const = 0;
	
	/**
	The origin is subtracted from coordinates passed in and added to those passed out.
	Return FALSE if the origin is 0,0.
	*/
	virtual TBool GetOrigin(TPoint& aPoint) const;

	void FixUpLineInfo(TTmLineInfo& aInfo,const TPoint* aOrigin = NULL) const;
	};

/**
A character format layer. Unmasked attributes are transparent.
*/
class TTmCharFormatLayer
	{
public:
	inline TTmCharFormatLayer();
	IMPORT_C TTmCharFormatLayer(const CCharFormatLayer& aFormat);

	TTmCharFormat iFormat;
	TTmCharFormatMask iMask;
	};

/**
A paragraph format layer. Unmasked attributes are transparent.
*/
class RTmParFormatLayer
	{
public:
	inline void Close();
	IMPORT_C void CopyL(const CParaFormatLayer& aFormat);

	RTmParFormat iFormat;
	TTmParFormatMask iMask;
	};

/**
A style.
*/
class RTmStyle
	{
public:
	enum
		{
		EMaxName = KMaxParagraphStyleName
		};

	inline void Close();
	IMPORT_C void CopyL(const RParagraphStyleInfo& aStyle);
	IMPORT_C void GetRParagraphStyleInfoL(RParagraphStyleInfo& aStyle,
		const CParaFormatLayer& aGlobalParaFormatLayer,const CCharFormatLayer& aGlobalCharFormatLayer,
		const CStyleList& aList) const;

	TBuf<KMaxName> iName;
	TBuf<KMaxName> iNextStyleName;
	TTmCharFormatLayer iCharFormat;
	RTmParFormatLayer iParFormat;
	TInt iOutlineLevel;
	};

/**
A self-contained text object. It owns both layout and content. It is intended for labels and the general display of
small-to-medium-sized amounts of text.
*/
class CTmText: public CBase, public MTmTextLayoutForwarder
	{
public:
	IMPORT_C static CTmText* NewL(MGraphicsDeviceMap& aDevice,const TTmFormatParamBase& aFormatParam);
	IMPORT_C static CTmText* NewL(MGraphicsDeviceMap& aDevice,TInt aWrapWidth,TInt aFlags);
	IMPORT_C ~CTmText();
	IMPORT_C void InsertL(TInt aPos,const TDesC& aText,
						  const TTmCharFormat* aCharFormat = NULL,const RTmParFormat* aParFormat = NULL,
						  TRect* aRedrawRect = NULL,TInt* aScroll = NULL);
	IMPORT_C void GetFormat(TTmFormatParamBase& aFormatParam) const;
	IMPORT_C void SetWrapWidthL(TInt aWrapWidth);
	IMPORT_C void ChangeFormatL(const TTmFormatParamBase& aFormatParam);
	IMPORT_C void Clear();
	IMPORT_C void CustomizeL(const MTmCustom* aCustom);
	IMPORT_C TInt MemoryUsed() const;
	inline void Draw(CGraphicsContext& aGc,const TPoint& aTopLeft,const TRect& aClipRect,
					 const TLogicalRgb* aDocBackground,TBool aDrawParBackground);

private:
	CTmText();
	IMPORT_C void Spare1();

	// implementations of MTmTextLayoutForwarder virtual functions
	const CTmTextLayout& TextLayout() const;

	CTmTextImp* iImp;		// the implementation
	};

// inline functions

/**
Construct a TTmCharFormatMask. Turn all the flags on.
*/
TTmCharFormatMask::TTmCharFormatMask(): iFlags(0xFFFFFFFF)
	{
	}

/**
Clear the selected flag.
*/
void TTmCharFormatMask::Clear(TAttrib aAttrib)
	{
	iFlags &= ~aAttrib;
	}

/**
Set the selected flag.
*/
void TTmCharFormatMask::Set(TAttrib aAttrib)
	{
	iFlags |= aAttrib;
	}

/**
Return a boolean value indicating whether the selected attribute is set.
*/
TBool TTmCharFormatMask::IsSet(TAttrib aAttrib)
	{
	return iFlags & aAttrib;
	}

/**
Construct a TTmCharFormat by converting the information in a TCharFormat.
*/
TTmCharFormat::TTmCharFormat(const TCharFormat& aFormat)
	{
	*this = aFormat;
	}

/**
The inequality operator. Return TRUE if this object and aFormat differ in any way.
*/
TBool TTmCharFormat::operator!=(const TTmCharFormat& aFormat) const
	{
	return !operator==(aFormat);
	}

/**
Construct a TTmTab and set it to a standard tab stop with a position of 0.
*/
TTmTab::TTmTab():
	iPosition(0),
	iType(EStandardTab)
	{
	}

/**
Construct a TTmTab by converting the information in a TTabStop.
*/
TTmTab::TTmTab(const TTabStop& aTab)
	{
	*this = aTab;
	}

/**
The inequality operator. Return TRUE if this object and aTab differ in any way.
*/
TBool TTmTab::operator!=(const TTmTab& aTab) const
	{
	return !operator==(aTab);
	}

/**
Construct a TTmBullet by converting the information in a TBullet.
*/
TTmBullet::TTmBullet(const TBullet& aBullet)
	{
	*this = aBullet;
	}

/**
The inequality operator. Return TRUE if this object and aBullet differ in any way.
*/
TBool TTmBullet::operator!=(const TTmBullet& aBullet) const
	{
	return !operator==(aBullet);
	}

/**
Construct a TTmParBorder by converting the information in a TParaBorder.
*/
TTmParBorder::TTmParBorder(const TParaBorder& aBorder)
	{
	*this = aBorder;
	}

/**
The inequality operator. Return TRUE if this object and aBorder differ in any way.
*/
TBool TTmParBorder::operator!=(const TTmParBorder& aBorder) const
	{
	return !operator==(aBorder);
	}

/**
Construct a TTmParFormatMask. Turn all the flags on.
*/
TTmParFormatMask::TTmParFormatMask():
	iFlags(0xFFFFFFFF)
	{
	}

/**
Clear the selected flag.
*/
void TTmParFormatMask::Clear(TAttrib aAttrib)
	{
	iFlags &= ~aAttrib;
	}

/**
Set the selected flag.
*/
void TTmParFormatMask::Set(TAttrib aAttrib)
	{
	iFlags |= aAttrib;
	}

/**
Return TRUE if the selected flag is Set.
*/
TBool TTmParFormatMask::IsSet(TAttrib aAttrib)
	{
	return iFlags & aAttrib;
	}

#ifdef _DEBUG
RTmParFormat::~RTmParFormat()
	{
	ASSERT(!iTabList && !iBullet && !HaveBorders());
	}
#endif

/**
The inequality operator. Return TRUE if this object and aFormat differ in any way.
*/
TBool RTmParFormat::operator!=(const RTmParFormat& aFormat) const
	{
	return !operator==(aFormat);
	}

/**
Return a reference to the tab selected by aIndex.
*/
const TTmTab& RTmParFormat::Tab(TInt aIndex) const
	{
	return (*iTabList)[aIndex];
	}

/**
Return a pointer to the TTmBullet object if any. Return null if the RTmParFormat does
not contain a TTmBullet.
*/
const TTmBullet* RTmParFormat::Bullet() const
	{
	return iBullet;
	}

/**
Return a pointer to the border selected by aIndex. Return NULL if the selected
border is not present.
*/
const TTmParBorder* RTmParFormat::Border(TBorderIndex aIndex) const
	{
	return iBorder[aIndex];
	}

/**
Return TRUE if the paragraph's base direction is right-to-left. Return FALSE if it is left-to-right. 
*/
TBool RTmParFormat::RightToLeft() const
	{
	return iFlags & ERightToLeft;
	}

/**
Construct a line height parameter structure. Set all the data members to zero.
*/
MTmCustom::TLineHeightParam::TLineHeightParam()
	{
	Mem::FillZ(this,sizeof(*this));
	}

CTmBufSeg::CTmBufSeg(TInt aExpandSize):
	CBufSeg(aExpandSize)
	{
	}

CTmCode::~CTmCode()
	{
	delete iBuffer;
	}

TPtr8 CTmCode::Ptr(TInt aPos)
	{
	return iBuffer->Ptr(aPos);
	}

CBufBase* CTmCode::Buffer()
	{
	return iBuffer;
	}

const CBufBase* CTmCode::Buffer() const
	{
	return iBuffer;
	}

/**
Return TRUE if wrapping is turned on.
*/
TBool TTmFormatParamBase::IsWrapping() const
	{
	return iFlags & EWrap;
	}

/**
Return TRUE if truncation with ellipsis is turned on.
*/
TBool TTmFormatParamBase::IsTruncatingWithEllipsis() const
	{
	return iFlags & ETruncateWithEllipsis;
	}

/**
Return TRUE if line breaking can only occur at legal line breaks, even if the line cannot legally be broken
at the desired wrap width.
*/
TBool TTmFormatParamBase::LegalLineBreaksOnly() const
	{
	return iFlags & ELegalLineBreaksOnly;
	}

/**
Construct a TTmLineInfo object, setting all data members to 0.
*/
TTmLineInfo::TTmLineInfo()
	{
	Mem::FillZ(this,sizeof(*this));
	}

/**
Construct a TTmDocPos object, setting iPos to 0 and iLeadingEdge to FALSE. This is the lowest legal
value for a TTmDocPos object. A trailing edge comes before a leading edge because it is the trailing edge of the
character before the position, while the leading edge is that of the character after the position. ('Leading' means
the first to be encountered when traversing the document in logical order).
*/
TTmDocPos::TTmDocPos():
	iPos(0),
	iLeadingEdge(FALSE)
	{
	}

/**
Construct a TTmDocPos object, setting iPos to aPos and iLeadingEdge to aLeadingEdge.
*/
TTmDocPos::TTmDocPos(TInt aPos,TBool aLeadingEdge):
	iPos(aPos),
	iLeadingEdge(aLeadingEdge)
	{
	}

/**
The inquality operator. Return TRUE if this object differs from aPos.
*/
TBool TTmDocPos::operator!=(const TTmDocPos& aPos) const
	{
	return !operator==(aPos);
	}

/**
Return TRUE if this object is less than aPos. Less means before in logical order.
*/
TBool TTmDocPos::operator<(const TTmDocPos& aPos) const
	{
	return !operator>=(aPos);
	}

/**
Return TRUE if this object is less than or equal to aPos. Less means before in logical order.
*/
TBool TTmDocPos::operator<=(const TTmDocPos& aPos) const
	{
	return !operator>(aPos);
	}

/**
Return the first formatted character.
*/
const TInt CTmTextLayout::StartChar() const
	{
	return iStartChar;
	}

/**
Return the character after the last formatted character.
*/
const TInt CTmTextLayout::EndChar() const
	{
	return iEndChar;
	}

/**
Return the width in pixels of the formatted text, not including paragraph labels if present.
*/
const TInt CTmTextLayout::LayoutWidth() const
	{
	return iWidth;
	}

/**
Return the height in pixels of the formatted text.
*/
const TInt CTmTextLayout::LayoutHeight() const
	{
	return iHeight;
	}

/**
Return a pointer to to the MTmSource object, if any, that provides text and formatting to this object. Return NULL
if no source object has been set.
*/
MTmSource* CTmTextLayout::Source()
	{
	return iSource;
	}

/**
@internal

Return a reference to the CTmCode object containing the bytecode representing the text layout.
*/
const CTmCode& CTmTextLayout::Code() const
	{
	return iCode;
	}

/**
Construct a TTmCharFormatLayer object containing default TTmCharFormat and TTmCharFormatMask objects.
*/
TTmCharFormatLayer::TTmCharFormatLayer()
	{
	}

/**
Close an RTmParFormatLayer object by freeing any objects allocated on the heap.
*/
void RTmParFormatLayer::Close()
	{
	iFormat.Close();
	}

/**
Close an RTmStyle object by freeing any objects allocated on the heap.
*/
void RTmStyle::Close()
	{
	iParFormat.Close();
	}

/**
Draw text. This inline function just calls CTmText::DrawLayout and is identical to it. It is provided
for coding convenience because of the expectation that a drawing function called Draw exists.
*/
void CTmText::Draw(CGraphicsContext& aGc,const TPoint& aTopLeft,const TRect& aClipRect,
				   const TLogicalRgb* aDocBackground,TBool aDrawParBackground)
	{
	DrawLayout(aGc,aTopLeft,aClipRect,aDocBackground,aDrawParBackground);
	}

TTmHighlightExtensions::TTmHighlightExtensions()
	{
	}

void TTmHighlightExtensions::SetAll(TInt aExtension)
	{
	iLeftExtension=iRightExtension=iTopExtension=iBottomExtension=aExtension;
	}

void TTmHighlightExtensions::SetLeftExtension(TInt aExtension)
	{
	iLeftExtension=aExtension;
	}

void TTmHighlightExtensions::SetRightExtension(TInt aExtension)
	{
	iRightExtension=aExtension;
	}

void TTmHighlightExtensions::SetTopExtension(TInt aExtension)
	{
	iTopExtension=aExtension;
	}

void TTmHighlightExtensions::SetBottomExtension(TInt aExtension)
	{
	iBottomExtension=aExtension;
	}

TInt TTmHighlightExtensions::LeftExtension() const
	{
	return iLeftExtension;
	}

TInt TTmHighlightExtensions::RightExtension() const
	{
	return iRightExtension;
	}

TInt TTmHighlightExtensions::TopExtension() const
	{
	return iTopExtension;
	}

TInt TTmHighlightExtensions::BottomExtension() const
	{
	return iBottomExtension;
	}

TBool TTmHighlightExtensions::Extends() const
	{
	if (iTopExtension>0 || iBottomExtension>0 || iLeftExtension>0 || iRightExtension>0)
		return ETrue;
	else
		return EFalse;
	}

inline void TTmHighlightExtensions::ExtendRect(TRect& aRect) const
	{
	if (iLeftExtension>0)
		aRect.iTl.iX-=iLeftExtension;
	if (iRightExtension>0)
		aRect.iBr.iX+=iRightExtension;
	if (iTopExtension>0)
		aRect.iTl.iY-=iTopExtension;
	if (iBottomExtension>0)
		aRect.iBr.iY+=iBottomExtension;
	}

inline void TTmHighlightExtensions::AdjustRect(TRect& aRect) const
	{
	aRect.iTl.iX-=iLeftExtension;
	aRect.iTl.iY-=iTopExtension;
	aRect.iBr.iX+=iRightExtension;
	aRect.iBr.iY+=iBottomExtension;
	}

#endif // __TAGMA_H__
