// TXTFRMAT.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __TXTFRMAT_H__
#define __TXTFRMAT_H__

#include <e32std.h>
#include <e32base.h>
#include <gdi.h>


// Classes declared in this file:
class TTabStop;
class TParaBorder;
class TBullet;
class TParaBorderArray;
class CParaFormat;
class TParaFormatMask;
class TFontPresentation;
class TCharFormat;
class TCharFormatMask;


/**
 *
 * Provides support for system colours, in addition to literal colours,
 * in text formatting.
 *
 * The base class <code>TRgb</code> stores the 24-bit literal colour
 * value using a <code>TUint32</code>. <code>TLogicalRgb</code> uses the
 * unused (top) byte as an 8-bit index. The purpose of the index is to
 * allow applications to use logical colours. If the index is zero, the
 * value is not a logical colour; it is treated as an ordinary
 * <code>TRgb</code> value. If the index is non zero (1-255), the colour
 * should be translated by the application into a system colour. Indices
 * 254 and 255 are reserved for the system foreground and background
 * colours, respectively and should be translated into them. Translation
 * from index to RGB colour occurs in the implementation of
 * <code>MFormParam::SystemColor()</code>.All colours in the Text and
 * text attributes API are stored using <code>TLogicalRgb</code> values
 * and are initialised to either
 * <code>TLogicalRgb::ESystemForegroundColor</code> or
 * <code>TLogicalRgb::ESystemBackgroundColor</code>.This system allows an
 * application to set its text colours once, perhaps using the
 * system-wide colour scheme, rather than having to set the colours each
 * time a text object is created. It is also compatible with legacy code
 * which expects <code>TRgb</code> rather than <code>TLogicalRgb</code>
 * values for example, the logical foreground and background colours have
 * their bottom three bytes filled with black and white respectively so
 * that code which expects <code>TRgb</code> values can still use them.
 *
 * @since 6.0
 * @lib " etext.lib "
 */

class TLogicalRgb : public TRgb
	{
	public:
	
	/**
	 *
	 * Miscellaneous constants.
	 * @since 
	 */

	/*
	Reserved colour indices for default foreground and background colours,
	and colours for the selection highlight. The top 128 indices (128-255)
	are reserved for future expansion, but the first 126 non-zero indices
	(1-127) can be used by the GUI as convenient.
	*/

	enum
		{
		ESystemSelectionForegroundIndex = 252,
		ESystemSelectionBackgroundIndex = 253,
		/** Index reserved for the system foreground colour (=254). */
		ESystemForegroundIndex = 254,
		/** Index reserved for the system background colour (=255). */
		ESystemBackgroundIndex = 255
		};

	
	/**
	 *
	 * Used to construct <code>TLogicalRgb</code> objects which should use
	 * either the system foreground or background colour.
	 * @since 
	 */

	/*
	Reserved system colours: the low 24 bits are chosen so that code that knows only TRgb values
	can use them in a sensible way.
	*/
	enum TSystemColor
		{
		ESystemSelectionForegroundColor = ESystemSelectionForegroundIndex << 24,
		ESystemSelectionBackgroundColor = ESystemSelectionBackgroundIndex << 24,
		/** The system foreground colour. */
		ESystemForegroundColor = ESystemForegroundIndex << 24,
		/** The system background colour. */
		ESystemBackgroundColor = (ESystemBackgroundIndex << 24) | 0xFFFFFF
		};
	
	
	
	TLogicalRgb() { }
	TLogicalRgb(TUint32 aValue): TRgb(aValue) { }
	TLogicalRgb(TSystemColor aValue): TRgb((TUint32)aValue) { }
	/**
	 *
	 * Constructs a new <code>TLogicalRgb</code> object from an existing one.
	 *
	 */
	TLogicalRgb(const TRgb& aRgb): TRgb(aRgb) { }
	
	/**
	 *
	 * Returns the logical colour's index value.
	 *
	 * Zero indicates that the value is not a logical colour; it is an
	 * ordinary <code>TRgb</code> value. 254 and 255 indicate the system
	 * foreground and background colours, respectively.
	 *
	 * @returns   " TUint "
	 *            The index: between zero and 255 inclusive.
	 */

	TUint SystemColorIndex() const { return Value() >> 24; }
	
	/**
	 *
	 * Sets the logical colour's index value.
	 *
	 * @param     " TUint aIndex "
	 *            The new index value (between 1 and 253 inclusive).
	 */

	void SetSystemColorIndex(TUint aIndex) { *this = (Value() & 0x00FFFFFF) | (aIndex << 24); }
	};

enum TTextFormatAttribute
	{
	// Paragraph format attributes.
	EAttParaLanguage,
	EAttFillColor,
	EAttLeftMargin,
	EAttRightMargin,
	EAttIndent,
	EAttAlignment,
	EAttVerticalAlignment,
	EAttLineSpacing,
	EAttLineSpacingControl,
	EAttSpaceBefore,
	EAttSpaceAfter,
	EAttKeepTogether,
	EAttKeepWithNext,
	EAttStartNewPage,
	EAttWidowOrphan,
	EAttWrap,
	EAttBorderMargin,
	EAttTopBorder,
	EAttBottomBorder,
	EAttLeftBorder,
	EAttRightBorder,
	EAttBullet,
	EAttDefaultTabWidth,
	EAttTabStop,

	// Character format attributes.
	EAttCharLanguage,
	EAttColor,
	EAttFontHighlightColor,
	EAttFontHighlightStyle,
	EAttFontHeight,
	EAttFontPosture,
	EAttFontStrokeWeight,
	EAttFontPrintPos,
	EAttFontUnderline,
	EAttFontStrikethrough,
	EAttFontTypeface,
	EAttFontPictureAlignment,
	EAttFontHiddenText,

	ETextFormatAttributeCount
	};

enum {EVariableLengthValue = 0};

const TInt KMaxStyleName = 0x20;
const TInt KMaxParaAttributes = EAttTabStop;
const TInt KMaxCharAttributes = EAttFontHiddenText - KMaxParaAttributes;
const TInt KTabNotFound = -1;


//
// Tabs are uniquely identified by their twips position.

/**
 *
 * A tab stop is a position on a page used to align columns of text.
 *
 * It has a twips position and an alignment. The twips position is the
 * width in twips (1/1440th of an inch) of the tab stop, i.e. the number
 * of twips from the start of the line at which text can be inserted. It
 * uniquely identifies the tab stop. The alignment (left, right, or
 * centre) indicates how text inserted at the tab stop should be aligned.
 * The twips position and alignment are public data members.Tab stops are
 * paragraph format attributes. They are owned by the
 * <code>CParaFormat</code> class, through which tab stops can be added
 * and removed.
 *
 * @since 5.0
 * @lib " etext.lib "
 */

class TTabStop
	{
public:
	
	/**
	 *
	 * Text alignment at tab stop.
	 * @since 
	 */

	enum TTabType
		{
		/** No tab. */
		ENullTab, 
		/** Text is left aligned at the tab stop. */
		ELeftTab, 
		/** Text is centre aligned at the tab stop. */
		ECenteredTab, 
		/** Text is right aligned at the tab stop. */
		ERightTab
		};
public:
	IMPORT_C TTabStop();
	IMPORT_C TTabStop(const TTabStop& aTabStop);
	IMPORT_C TTabStop& operator=(const TTabStop& aTabStop);
	IMPORT_C TBool operator==(const TTabStop& aTabStop) const;
	inline TBool operator!=(const TTabStop& aTabStop) const;
public:
	TUint32 iTwipsPosition;
	TTabType iType;
	};


// One side (top, bottom, left or right) of a paragraph border.

/**
 *
 * Defines the characteristics of one of the four sides of a paragraph
 * border.
 *
 * These are the line style, thickness and colour. Paragraph borders are
 * paragraph format attributes. They are owned by the
 * <code>CParaFormat</code> class which allows paragraph borders to be
 * added and removed. The <code>CParaFormat::TParaBorderSide</code>
 * enumeration identifies which side of the paragraph the object applies
 * to.
 *
 * @since 5.0
 * @lib " etext.lib "
 */

class TParaBorder
	{
public:
	
	/**
	 *
	 * Line styles.
	 * @since 
	 */

	enum TLineStyle 
		{
		/** No line style. */
		ENullLineStyle, 
		/** Solid line. */
		ESolid, 
		/** Double solid line. */
		EDouble,
		/** Dotted line. */
		EDotted, 
		/** Dashed line. */
		EDashed, 
		/** Alternating dots and dashes. */
		EDotDash, 
		/** Alternating sequence of two dots and a dash. */
		EDotDotDash
		};
	//
	IMPORT_C TParaBorder();
	IMPORT_C TBool operator==(const TParaBorder& aParaBorder) const;
	inline TBool operator!=(const TParaBorder& aParaBorder) const;
public:
	TLineStyle iLineStyle;
	TInt iThickness;
	TLogicalRgb iColor;
	TBool iAutoColor;
	};

/**
 *
 * Stores the four sides of a paragraph border.
 *
 * Each side is a <code>TParaBorder</code>. Paragraph borders sides are
 * set individually using functions provided by class
 * <code>CParaFormat</code>.
 *
 * @since 5.0
 * @lib ""
 */

class TParaBorderArray
	{
public:
	TParaBorder iBorder[4];
	};

// A bullet or paragraph number style defined as a paragraph attribute rather than as content.

/**
 *
 * A bullet point is a paragraph format attribute, stored as the
 * <code>iBullet</code> member of class <code>CParaFormat</code>.
 *
 * Bullet points have a typeface, height, colour and a character code
 * (defines the symbol displayed). Single level bullets only are
 * supported. Bullets may also have a hanging indent. If set, this means
 * that the rest of the paragraph following the line containing the
 * bullet point is indented. The data members of this class are public.
 *
 * @since 5.0
 * @lib " etext.lib "
 */

class TBullet
	{
	public:
	IMPORT_C TBullet();
	IMPORT_C TBool operator ==(const TBullet& aBullet) const;
	inline TBool operator !=(const TBullet& aBullet) const;

	enum TStyle
		{
		ENullStyle,					// used for style layers that override a bullet with the absence of a bullet
		EBulletStyle,
		EArabicNumberStyle,
		ESmallRomanNumberStyle,
		ECapitalRomanNumberStyle,
		ESmallLetterStyle,
		ECapitalLetterStyle
		};

	enum TAlignment
		{
		ELeftAlign,
		ECenterAlign,
		ERightAlign
		};

	TChar iCharacterCode;		// the bullet or other symbol used if iStyle is EBulletStyle
	TUint iHeightInTwips;
	TTypeface iTypeface;
	TBool iHangingIndent;
	TLogicalRgb iColor;
	TStyle iStyle;				// is this a bullet or a number or a letter?
	TInt iStartNumber;			// the number of the first paragraph in a run of paragraphs in this style
	TAlignment iAlignment;		// alignment of the bullet or number within the margin
	};



/**
 *
 * A transient container of paragraph format attributes, including tab
 * stops, bullet points and paragraph borders.
 *
 * Rich and global text objects store paragraph formatting using
 * paragraph format layers (see class <code>CParaFormatLayer</code>). The
 * <code>CParaFormat</code> class is used to store the relevant attribute
 * values when setting or sensing a <code>CParaFormatLayer</code>. It is
 * normally used in combination with a <code>TParaFormatMask</code>, to
 * specify which attributes are relevant to the function concerned.On
 * construction, all <code>CParaFormat</code> member data is initialised.
 * The attributes which are not explicitly set are assigned default
 * values.
 *
 * @since 5.0
 * @lib " etext.lib "
 */

class CParaFormat: public CBase
	{
// Paragraph format attributes 
public:
	
/**
 *
 * Miscellaneous constants.
 * @since 
 */

	enum
		{
		/** The maximum number of paragraph borders (= 4). */
		EMaxParaBorder = 4
		};

/**
 *
 * Paragraph border sides.
 * @since 
 */

	enum TParaBorderSide
		{
		/** The border at the top of the paragraph. */
		EParaBorderTop,
		/** The border at the bottom of the paragraph. */
		EParaBorderBottom,
		/** The border on the left hand side. */
		EParaBorderLeft,
		/** The border on the right hand side. */
		EParaBorderRight
		};

/**
 *
 * Line spacing control.
 * @since 
 */

	enum TLineSpacingControl
		{
/** Twips line spacing must be at least as wide as the
<code>iLineSpacingInTwips</code> value. */
		ELineSpacingAtLeastInTwips,
/** Twips line spacing must be exactly the
<code>iLineSpacingInTwips</code> value. */
		ELineSpacingExactlyInTwips,
/** Pixels line spacing must be at least as wide as the line spacing value
in pixels. */
		ELineSpacingAtLeastInPixels,
/** Pixels line spacing must be exactly the same as the line spacing value
in pixels. */
		ELineSpacingExactlyInPixels
		};

/**
 *
 * Paragraph alignment.
 * @since 
 */

	enum TAlignment
		{
		/** Paragraph top aligned. */
		ELeftAlign,
		ETopAlign = ELeftAlign,
		/** Paragraph centre aligned. */
		ECenterAlign,
		/** Paragraph bottom aligned. */
		ERightAlign,
		EBottomAlign = ERightAlign,
		/** Paragraph justified. */
		EJustifiedAlign,
/** Used by the spreadsheet application. Unlike <code>ETopAlign</code> and
<code>EBottomAlign</code>, provides no default implementation.
 */
		EUnspecifiedAlign,
		/** User-defined paragraph alignment. */
		ECustomAlign
		};

/**
 *
 * Attribute sense mode.
 * @since 
 */

	enum TParaFormatGetMode
		{
/** Indicates that all paragraph format attributes are written to the
result when sensing paragraph format attributes.
 */
		EAllAttributes,
/** Indicates that tabs, bullets and borders are not sensed.
 */
		EFixedAttributes
		};

	IMPORT_C static CParaFormat* NewL();
	IMPORT_C static CParaFormat* NewLC();
	IMPORT_C static CParaFormat* NewL(const CParaFormat& aFormat);
	IMPORT_C CParaFormat();
	IMPORT_C ~CParaFormat();
	IMPORT_C void ResetNonDestructive();  // preserves any allocated tabs, bullets or borders.
	IMPORT_C void Reset();  // full reset, deletes and nulls any allocated tabs, bullets or borders.
	IMPORT_C void CopyL(const CParaFormat& aFormat, const TParaFormatMask& aMask);
	IMPORT_C void CopyL(const CParaFormat& aFormat);
	IMPORT_C void Strip();  // Cleans up this paragraph format.
	IMPORT_C TBool IsEqual(const CParaFormat& aFormat, const TParaFormatMask& aMask) const;
	IMPORT_C TBool IsEqual(const CParaFormat& aFormat) const;
	IMPORT_C void StoreTabL(const TTabStop& aTabStop);
	IMPORT_C void RemoveTab(TInt aTabTwipsPosition);
	inline void RemoveAllTabs();
	IMPORT_C const TTabStop TabStop(TInt aTabIndex) const;
	inline TInt TabCount() const;
	IMPORT_C TInt LocateTab(TInt aTabTwipsPosition) const;
	IMPORT_C void SetParaBorderL(TParaBorderSide aSide, const TParaBorder& aBorder);  // Overwrites any existing border for that side
	IMPORT_C void RemoveAllBorders();
	IMPORT_C const TParaBorder ParaBorder(TParaBorderSide aSide) const;

/**
 *
 * Tests whether any paragraph borders have been set.
 *
 * @returns   " TBool "
 *            <code>ETrue</code> if any paragraph borders have been
 *            set, <code>EFalse</code> if not.
 */

	inline TBool BordersPresent() const { return iParaBorderArray != NULL;}
	
/**
 *
 * Gets a pointer to the paragraph border on the side specified.
 *
 * If no paragraph border array has been allocated, returns NULL.
 *
 * @since     6.0
 * @param     " TParaBorderSide aSide "
 *            The side for the paragraph border.
 * @returns   " TParaBorder* "
 *            Pointer to the paragraph border on the specified side.
 */

	inline TParaBorder* ParaBorderPtr(TParaBorderSide aSide)
		{ return iParaBorderArray ? &iParaBorderArray->iBorder[aSide] : NULL; }
	IMPORT_C TBool AllBordersEqual(const CParaFormat& aFormat) const;
	IMPORT_C TBool IsBorderEqual(TParaBorderSide aSide, const CParaFormat& aFormat) const;
private:
	CParaFormat(const CParaFormat& aFormat);
	void CreateTabListL();
	enum
		{
		ETabStoreGranularity = 2
		};

	CParaFormat& operator=(const CParaFormat& aParaFormat);	// intentionally unimplemented
private:
	CArrayFixFlat<TTabStop>* iTabList;			// ordered list of tab stops; null if none
	TParaBorderArray* iParaBorderArray;			// array of paragraph borders; null if none
public:
	TLogicalRgb iFillColor;						// paragraph background color and default system background colour
	TInt32 iLanguage;							// language code
	TInt32 iLeftMarginInTwips;
	TInt32 iRightMarginInTwips;
	TInt32 iIndentInTwips;						// first line indent, relative to iLeftMarginInTwips
	TAlignment iHorizontalAlignment;
	TAlignment iVerticalAlignment;
	TInt32 iLineSpacingInTwips;					// distance between successive baselines
	TLineSpacingControl iLineSpacingControl;	// whether iLineSpacingInTwips means 'at least' or 'exactly'
	TInt32 iSpaceBeforeInTwips;					// extra space above the paragraph
	TInt32 iSpaceAfterInTwips;					// extra space below the paragraph
	TBool iKeepTogether;						// prevents page break in a paragraph when true
	TBool iKeepWithNext;						// prevents page break between this and next par when true
	TBool iStartNewPage;						// inserts page break before this paragraph when true
	TBool iWidowOrphan;							// suppresses widows and orphans when true
	TBool iWrap;								// suppresses wrapping when false
	TInt32 iBorderMarginInTwips;				// gap between paragraph border and text
	TBullet* iBullet;							// bullet or paragraph number specification; null if none
	TUint32 iDefaultTabWidthInTwips;
	};


/**
 *
 * Used in conjunction with an object of class <code>CParaFormat</code>
 * to mask the paragraph format attributes which are involved when
 * setting and sensing paragraph formatting.
 *
 * When setting formatting, only the attributes which are set in the mask
 * should participate in the relevant function. When sensing formatting,
 * on return, the mask indicates which attributes were sensed from the
 * format layer, and were not taken from the default values.
 *
 * @since 5.0
 * @lib " etext.lib "
 */

class TParaFormatMask
	{
public:
	inline TParaFormatMask();
	inline void SetAttrib(TTextFormatAttribute aAttribute);
	inline void ClearAttrib(TTextFormatAttribute aAttribute);
	IMPORT_C void SetAll();
	IMPORT_C void ClearAll();
	inline TBool AttribIsSet(TTextFormatAttribute aAttribute) const;
	inline TBool IsNull() const;
	IMPORT_C TBool operator==(const TParaFormatMask& aMask) const;
	inline TBool operator!=(const TParaFormatMask& aMask) const;

private:
	TUint32 iGuard;
	};


/**
 *
 * Specifies all font-independent character format attributes, including
 * bold, italics and underlining.
 *
 * An instance of this class is owned by the character formatting
 * container (class <code>TCharFormat</code>).
 *
 * @since 5.0
 * @lib " etext.lib "
 */

class TFontPresentation
	{
public:
	
	/**
	 *
	 * Highlight style.
	 * @since 6.0
	 */

	enum TFontHighlightStyle
		{
		/** No highlighting used. */
		EFontHighlightNone,
		/** Normal (square cornered) highlighting used. */
		EFontHighlightNormal,
		/** Rounded corner highlighting used. */
		EFontHighlightRounded,
		/** Text is drawn offset towards the bottom-right in the highlight colour,
		(<code>iHighlightColor</code>) before being drawn again in the text
		colour, (<code>iTextColor</code>) creating a shadow effect.
		 */
		EFontHighlightShadow,
		/** Placeholder for "unrecognised word" highlighting style for FEPs
		 */
		EFontHighlightNoMatchesIndicator,
		/** First custom highlighting style is used. See
		<code>MFormCustomDraw::DrawText()</code>.
		 */
		EFontHighlightFirstCustomStyle = 128,
		/** Second custom highlighting style is used. See
		<code>MFormCustomDraw::DrawText()</code>.
		 */
		EFontHighlightLastCustomStyle = 255
		};
	
	/**
	 *
	 * Vertical picture alignment.
	 * @since 
	 */

	enum TAlignment
		{
		/** The top of the picture is aligned flush with the top of the font's
		ascent, so that the picture may descend below the line.
		 */
		EAlignTop,
		/** The bottom of the picture is aligned flush with the bottom of the
		font's descent so that the picture may extend above the line.
		*/
		EAlignBottom,
		/** The picture is aligned so that its centre is positioned at the
		baseline of the line.
		 */
		EAlignCentered,
		/** The bottom of the picture is aligned with the baseline of the font.
		This is the default.
		*/
		EAlignBaseLine
		};
	//
	IMPORT_C TFontPresentation();
	//
	// Enquiry function
	IMPORT_C TBool IsEqual(const TFontPresentation& aFontPresentation, const TCharFormatMask& aMask) const;
public:
	TLogicalRgb iTextColor;
	TLogicalRgb iHighlightColor;  // Background color
	TFontHighlightStyle iHighlightStyle;
	TFontStrikethrough iStrikethrough;
	TFontUnderline iUnderline;
	TBool iHiddenText;
	TAlignment iPictureAlignment;
	};


// Specifies all character format attributes.
// Passed out of the LayDoc interface.

/**
 *
 * A transient container of character format attributes, including
 * font-dependent and font-independent attributes.
 *
 * The font-independent attributes are stored in a
 * <code>TFontPresentation</code> object. Rich and global text objects
 * store character formatting using character format layers (see class
 * <code>CCharFormatLayer</code>). The <code>TCharFormat</code> class is
 * used to store the relevant attribute values when setting or sensing a
 * <code>CCharFormatLayer</code>. It is normally used in combination with
 * a <code>TCharFormatMask</code>, to specify which attributes are
 * relevant to the function concerned.
 *
 * @since 5.0
 * @lib " etext.lib "
 */

class TCharFormat
	{
public:
	IMPORT_C TCharFormat();
	IMPORT_C TCharFormat(const TDesC &aTypefaceName, TInt aHeight);
	//
	// Enquiry functions
	IMPORT_C TBool IsEqual(const TCharFormat& aFormat, const TCharFormatMask& aMask) const;
	IMPORT_C TBool IsEqual(const TCharFormat& aFormat) const;
public:
	TInt32 iLanguage;
	TFontPresentation iFontPresentation;  // Font independent character attributes
	TFontSpec iFontSpec;  // Device independant font specification.
	};


// A mask to select character format attributes.

/**
 *
 * Used in conjunction with an object of class <code>TCharFormat</code>
 * to mask the character format attributes which are involved when
 * setting and sensing character formatting.
 *
 * When setting formatting, only the attributes which are set in the mask
 * should participate in the relevant function. When sensing formatting,
 * on return, the mask indicates which attributes were sensed from the
 * format layer, and were not taken from the default values.
 *
 * @since 5.0
 * @lib " etext.lib "
 */

class TCharFormatMask
	{
public:
	inline TCharFormatMask();
	inline void SetAttrib(TTextFormatAttribute aAttribute);
	inline void ClearAttrib(TTextFormatAttribute aAttribute);
	inline TBool AttribIsSet(TTextFormatAttribute aAttribute) const;
	IMPORT_C void SetAll();
	IMPORT_C void ClearAll();
	inline TBool IsNull()const;
	IMPORT_C TBool operator==(const TCharFormatMask& aMask) const;
	inline TBool operator!=(const TCharFormatMask& aMask) const;
	
private:
	TUint32 iGuard;
	};


#include <txtfrmat.inl>


#endif

