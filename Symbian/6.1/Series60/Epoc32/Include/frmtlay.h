// FRMTLAY.H
//
// Copyright (c) 1997-1999 Symbian Ltd. All rights reserved.
//

#ifndef __FRMTLAY_H__
#define __FRMTLAY_H__

#include <e32std.h>
#include <e32base.h>
#include <gdi.h>
#include <txtfrmat.h>
#include <txtetext.h>
#include <frmlaydt.h>
#include <frmparam.h>
#include <tagma.h>

// forward declarations
class CWindowGc;


/**
 *
 * Parameter used to control which part of a line (top, baseline or
 * bottom) should be scrolled to a certain vertical position in a view
 * rectangle.
 *
 * Used as a parameter in functions like
 * <code>CTextView::HandleGlobalChangeL()</code> and
 * <code>CTextLayout::SetViewL()</code>. The selected part of the line is
 * called the hotspot.
 *
 * @since 5.0
 * @lib "form.lib"
 */

class TViewYPosQualifier
	{
friend class CTextLayout;
friend class CTextView;
public:
	
	/**
	 *
	 * Which part of a line (top, baseline or bottom) should appear at a
	 * vertical pixel position.
	 * @since 
	 */

	enum TPartOfLine
		{
		/** The top pixel is placed at the specified vertical point. */
		EFViewTopOfLine = 1,
		/** The baseline is placed at the specified vertical point. */
		EFViewBaseLine = 0,
		/** The bottom pixel is placed at the specified vertical point. */
		EFViewBottomOfLine = 2	
		};
	
	/**
	 *
	 * Whether the top line in the view should be fully visible.
	 * @since 
	 */

	enum TFullyVisible
		{
		/** Force a partially visible top line to be fully visible. */
		EFViewForceLineFullyVisible = ETrue,		
		/** Do not force a partially visible top line to be fully visible. */
		EFViewDontForceLineFullyVisible = EFalse
		};
public:
	inline TViewYPosQualifier();
	IMPORT_C void SetHotSpot(TPartOfLine aHotSpot);
	IMPORT_C void SetFillScreen(TBool aFillScreen = ETrue);
	IMPORT_C void SetMakeLineFullyVisible(TFullyVisible aMakeLineFullyVisible = EFViewForceLineFullyVisible);
private:
	TPartOfLine iHotSpot;
	TBool iFillScreen;
	TFullyVisible iFullyVisible;
	};

/**
 *
 * A structure used to return the results of a reformatting operation.
 * @since 5.0
 * @lib ""
 */

class TViewRectChanges
	{
public:
	inline TViewRectChanges();
	void AdjustAll(TInt aDelta);
public:
	TInt iFormattedFrom;
	TInt iFormattedTo;
	TInt iScrollAtTop;
	TInt iScrollAtBottom;
	};


/**
 *
 * The cursor or cursor selection within a document.
 *
 * If the cursor and anchor position differ, the selection covers the
 * text from the lower to the higher position, not including the
 * character after the higher position. If the selection is changed (by
 * shift plus arrow keys in many UIs) the cursor position changes and the
 * anchor remains the same.
 *
 * @since 5.0
 * @lib ""
 */

class TCursorSelection
	{
public:
	inline TCursorSelection();
	inline TCursorSelection(TInt aCursorPos,TInt aAnchorPos);
	inline void SetSelection(TInt aCursorPos,TInt aAnchorPos);
	inline TInt LowerPos() const;
	inline TInt HigherPos() const;
	inline TInt Length() const;
public:
	TInt iCursorPos;
	TInt iAnchorPos;
	};


/**
 *
 * Parameters used by functions that draw text.
 *
 * An object of this class is passed to <code>CTextLayout::DrawL()</code>
 * and to <code>InvertRangeL()</code>. The draw context includes the view
 * rectangle, the graphics context, the background colour and the margin
 * widths.You only need to use this class directly when you are using a
 * <code>CTextLayout</code> object which is not owned by a
 * <code>CTextView</code> object.
 *
 * @since 5.0
 * @lib "form.lib"
 */

class TDrawTextLayoutContext
	{
private:
	enum TDrawMode
		{
		EFDrawText=0x001,
		EFDrawGraphics=0x002,
		EFUseClippingRect=0x004,
		EFUseWindowGc=0x008,
		EFUseGcClear=0x020,
		EFUseBackgroundColor=0x040,
		EFUseOverrideTextColor=0x080,
		EFParagraphFillTextOnly=0x100,
		EFAllFlags=0xfff
		};
public:
	IMPORT_C TDrawTextLayoutContext();

// Setting functions
	IMPORT_C void SetGc(CGraphicsContext* aGc,CGraphicsContext* aPictureGc=NULL);
	IMPORT_C void SetBitmapGc(CBitmapContext* aGc,CBitmapContext* aPictureGc=NULL);
	IMPORT_C void SetWindowGc(CWindowGc* aGc,CWindowGc* aPictureGc=NULL);
	IMPORT_C void SetDrawToEveryPixel(TBool aDrawToEveryPixel);
	IMPORT_C void SetTextColorOverride(const TRgb *aOverrideColor);
	IMPORT_C void SetDrawTextOnly();
	IMPORT_C void SetDrawGraphicsOnly();
	IMPORT_C void SetDrawTextAndGraphics();
	IMPORT_C void SetClipping(TBool aClipping);
	IMPORT_C void SetParagraphFillTextOnly(TBool aFillTextOnly);

//Enquiry functions
	IMPORT_C const TRgb* TextOverrideColor() const;
	IMPORT_C CGraphicsContext* PrimaryGc() const;
	IMPORT_C CGraphicsContext* PictureGc() const;
	IMPORT_C TBool UseClippingRect() const;
	IMPORT_C TBool UseGcClear() const;
	IMPORT_C TBool DrawText() const;
	IMPORT_C TBool DrawGraphics() const;
	IMPORT_C TBool UseBackgroundColor() const;
	IMPORT_C TBool ParagraphFillTextOnly() const;

//Physical dimensions
	IMPORT_C TRect TextArea() const;
	IMPORT_C TInt DisplayHeight() const;
	IMPORT_C TPoint TopLeftTextArea() const;
	IMPORT_C TRect TotalMargin() const;
	IMPORT_C TRect LabelMargin() const;
	IMPORT_C TBool IsLabelMargin() const;
	IMPORT_C TRect GutterMargin() const;
	IMPORT_C TBool IsGutterMargin() const;
	IMPORT_C TPoint TopLeftText() const;
	IMPORT_C void WindowToText(TPoint& aWinPos) const;
	IMPORT_C void WindowToText(TRect& aRect) const;
	IMPORT_C void TextToWindow(TPoint& aTextAreaPos) const;
	IMPORT_C void TextToWindow(TRect& aRect) const;
public:
	TRect iViewRect;
	TInt iLabelMarginWidth;
	TInt iGutterMarginWidth;
	TInt iTextStartX;
	TLogicalRgb iBackgroundColor;
private:
	CGraphicsContext* iGc;
	CGraphicsContext* iPictureGc;
	TLogicalRgb iOverrideTextColor;
	TUint iDrawMode;
	};

/**
 *
 * An abstract class which specifies the protocol for customising the way
 * the text and its background are drawn.
 *
 * Common uses for this are to implement custom highlighting or to draw a
 * background bitmap. You must create an object of a class derived from
 * this class and call <code>CTextLayout::SetCustomDraw()</code>, passing
 * a pointer to the object. All of these functions have default
 * implementations. Your class can override any of the virtual functions
 * listed below.
 *
 * @since 6.0
 * @lib ""
 */

class MFormCustomDraw
	{
	public:

	
	/**
	 *
	 * Contains the drawing parameters used by all custom draw functions.
	 * @lib ""
	 */

	// Parameters used by several custom draw functions
	class TParam
		{
		public:
		TParam(CGraphicsContext& aGc,MGraphicsDeviceMap& aMap,const TPoint& aTextLayoutTopLeft,const TRect& aDrawRect):
			iGc(aGc), iMap(aMap), iTextLayoutTopLeft(aTextLayoutTopLeft), iDrawRect(aDrawRect) { }

		CGraphicsContext& iGc;
		MGraphicsDeviceMap& iMap;
		const TPoint& iTextLayoutTopLeft;
		const TRect& iDrawRect;
		};

	
	
	/**
	 *
	 * Contains the line metrics.
	 * @lib ""
	 */

	// Information about a line.
	class TLineInfo
		{
		public:
		TLineInfo(const TRect& aOuterRect,const TRect& aInnerRect,TInt aBaseline):
			iOuterRect(aOuterRect), iInnerRect(aInnerRect), iBaseline(aBaseline) { }

		const TRect& iOuterRect;
		const TRect& iInnerRect;
		TInt iBaseline;
		};
	
	IMPORT_C virtual void DrawBackground(const TParam& aParam,const TRgb& aBackground,TRect& aDrawn) const;
	IMPORT_C virtual void DrawLineGraphics(const TParam& aParam,const TLineInfo& aLineInfo) const;
	IMPORT_C virtual void DrawText(const TParam& aParam,const TLineInfo& aLineInfo,const TCharFormat& aFormat,
								   const TDesC& aText,const TPoint& aTextOrigin,TInt aExtraPixels) const;
	IMPORT_C virtual TRgb SystemColor(TUint aColorIndex,TRgb aDefaultColor) const;

	IMPORT_C virtual void MFormCustomDraw_Reserved_1();
	IMPORT_C virtual void MFormCustomDraw_Reserved_2();
	};

/**
@since 6.2
The MFormCustomWrap interface.

This interface class allows you to implement custom line breaking. 
All you have to do is create an object of a class derived from MFormCustomWrap 
and call CTextLayout::SetCustomWrap, passing a pointer to the object. 

*/
class MFormCustomWrap
	{
public:
	IMPORT_C virtual TUint LineBreakClass(TUint aCode,TUint& aRangeStart,TUint& aRangeEnd) const;
	IMPORT_C virtual TBool LineBreakPossible(TUint aPrevClass,TUint aNextClass,TBool aHaveSpaces) const;
	IMPORT_C virtual TBool GetLineBreakInContext(const TDesC& aText,TInt aMinBreakPos,TInt aMaxBreakPos,
												 TBool aForwards,TInt& aBreakPos) const;
	IMPORT_C virtual TBool IsHangingCharacter(TUint aChar) const;
private:
	IMPORT_C virtual void MFormCustomWrap_Reserved_1();
	IMPORT_C virtual void MFormCustomWrap_Reserved_2();	
	};

/**
@internal
Internal to Symbian
*/
class TLayDocTextSource: public MTmSource
	{
	public:

	enum
		{
		EDefaultFontHeightIncreaseFactor = 7,
		EDefaultMinimumLineDescent = 3
		};

	TLayDocTextSource();

	// overrides for MTmSource pure virtual functions
	MGraphicsDeviceMap& FormatDevice() const;
	MGraphicsDeviceMap& InterpretDevice() const;
	TInt DocumentLength() const;
	void GetText(TInt aPos,TPtrC& aText,TTmCharFormat& aFormat) const;
	void GetParagraphFormatL(TInt aPos,RTmParFormat& aFormat) const;
	TInt ParagraphStart(TInt aPos) const;

	// overrides for other MTmSource virtual functions
	TRgb SystemColor(TUint aColorIndex,TRgb aDefaultColor) const;
	CPicture* PictureL(TInt aPos) const;
	TInt GetPictureSizeInTwipsL(TInt aPos,TSize& aSize) const;
	TBool SelectLabelMode(TLabelType aType,TInt aPos);
	void CancelLabelMode();
	void GetLabelMetrics(TLabelType aType,TSize& aLabelSize,TInt& aMarginSize) const;
	TUint Map(TUint aChar) const;
	void SetLineHeight(const TLineHeightParam& aParam,TInt& aAscent,TInt& aDescent) const;
	TBool PageBreakInRange(TInt aStartPos,TInt aEndPos) const;
	void DrawBackground(CGraphicsContext& aGc,const TPoint& aTextLayoutTopLeft,const TRect& aRect,
						const TLogicalRgb& aBackground,TRect& aRectDrawn) const;
	void DrawLineGraphics(CGraphicsContext& aGc,const TPoint& aTextLayoutTopLeft,const TRect& aRect,
						  const TTmLineInfo& aLineInfo) const;
	void DrawText(CGraphicsContext& aGc,const TPoint& aTextLayoutTopLeft,const TRect& aRect,
				  const TTmLineInfo& aLineInfo,const TTmCharFormat& aFormat,
				  const TDesC& aText,const TPoint& aTextOrigin,TInt aExtraPixels) const;
	
	// overrides for the MTmSource virtual functions which implements the MFormCustomWrap
	// if iCustomWrap is set. 
	TBool LineBreakPossible(TUint aPrevClass,TUint aNextClass,TBool aHaveSpaces) const;
	TUint LineBreakClass(TUint aCode,TUint& aRangeStart,TUint& aRangeEnd) const;
	TBool GetLineBreakInContext(const TDesC& aText,TInt aMinBreakPos,TInt aMaxBreakPos,
												 TBool aForwards,TInt& aBreakPos) const;
	TBool IsHangingCharacter(TUint aChar) const;
	
	// other functions
	TBool CanMap() const;

	// flags
	enum
		{
		EWrap = 1,
		ETruncateWithEllipsis = 2,
		EUseLabelsDevice = 4
		};

	MLayDoc* iLayDoc;
	TUint iFlags;								// wrap, truncate, etc.
	TInt iWidth;								// wrapping width
	TChar iEllipsis;							// ellipsis character (or none if 0xFFFF) used if truncating
	TInt iLabelsWidth;
	TInt iLabelsGutter;
	CLayoutData::TFormatMode iFormatMode;
	MGraphicsDeviceMap* iImageDevice;			// device map used for drawing text
	MGraphicsDeviceMap* iLabelsDevice;			// device map used for labels
	MGraphicsDeviceMap* iFormatDevice;			// device map used for formatting
	TInt iFontHeightIncreaseFactor;				// percentage automatically added to font heights
	TInt iMinimumLineDescent;					// minimum line descent in pixels
	TNonPrintingCharVisibility iNonPrintingCharVisibility;
	const MFormParam* iFormParam;				// if non-null, points to the object that supplies system colours
	const MFormCustomDraw* iCustomDraw;			// if non-null, points to custom drawing routines
	const MFormCustomWrap* iCustomWrap;			// if non-null, points to custom wrapping routines 
 
	};

/**
CTextLayout is the lowest-level text formatting class provided by FORM. It obtains text and formatting attributes
via the MLayDoc interface class and formats the text to a certain width. It has functions for drawing the text and
performing hit-detection - that is, converting x-y coordinates to document positions, and vice versa. It has many
public functions that are not generally useful, but are called by the higher-level CTextView class.

The white-box interface

CTextLayout cannot be used as a black box. In other words it is not possible to call any public function at any time
without regard to what has gone before.

Functions that raise out-of-memory exceptions can leave the object in an inconsistent state; it is then necessary to
discard the formatting information by calling DiscardFormat; these functions can be identified as usual by their
trailing L.

Some functions change formatting parameters like the wrap width or band height, but do not reformat to reflect the
change. These functions are identified in their documentation by the text ‘Reformat needed’.

Formatting and scrolling functions must not be called if a CTextView object owns the CTextLayout object, because the
CTextView object may be reformatting the CTextLayout object asynchronously by means of an active object, or may hold
some state information about the CTextLayout object that would be invalidated by reformatting. These functions are
identified by the text ‘Do not use if a CTextView object owns this CTextLayout object.’.

Coordinates

The x-y pixel coordinates used by CTextLayout functions like DocPosToXyPosL have their origin at the top-left corner of
the visible area of the body text, to the right of the paragraph label area if any. As in most bitmap graphics systems,
x coordinates increase rightwards and y coordinates increase downwards. The first visible line contains y coordinate 0,
and the left edge of a non-indented line is at x coordinate 0. Coordinates in this system are called layout coordinates.

Scrolling polarity

The scrolling functions use the convention that positive numbers of pixels, lines, paragraphs, pages, etc., mean that
the text moves down, and vice versa.

Drawing and scrolling

CTextLayout does no redrawing automatically. When the text has changed you have to redraw it by calling
CTextLayout::DrawL. If reformatting or making a desired position visible causes a scroll, any intelligent scrolling using
block transfer (blit) operations has to be done by the user. If you need automatic drawing and scrolling you should use
the higher-level CTextView class.

Functions not generally useful

There are several public functions that exist only for the convenience of closely associated classes like the printing
and pagination systems. These are identified by the text ‘not generally useful’.
*/
class CTextLayout: public CBase
	{
public:
	
	/**
	 *
	 * Flags used by <code>CTextLayout::SetViewL()</code>.
	 * @since 
	 */

	enum TDiscard
		{
		/** Discard all the formatting. */
		EFViewDiscardAllFormat = TRUE,	
		/** Do not discard formatting until it is known that it is not needed. */
		EFViewDontDiscardFormat = FALSE	
		};
	
	/**
	 *
	 * Indicates whether blank space should scroll.
	 
	 *
	 * Used by several <code>CTextView</code> and <code>CTextLayout</code>
	 * scrolling functions.
	 * * @since 
	 */

	enum TAllowDisallow
		{
		/** Allow blank space to scroll. */
		EFAllowScrollingBlankSpace = TRUE,
		/** Disallow blank space from scrolling. */
		EFDisallowScrollingBlankSpace = FALSE
		};
	

	

	enum									// flags for HandleCharEditL
		{
		/** Insert a character, (not a paragraph delimiter). */
		EFCharacterInsert,
		/** Insert a paragraph delimiter. */
		EFParagraphDelimiter,
		/** Delete single character to the left. */
		EFLeftDelete,
		/** Delete single character to the right. */
		EFRightDelete				
		};
	
	enum
		{
		/** A value greater than any possible display height indicates that the
		entire visible area, at least, was scrolled, and so there is no point
		in blitting text; a full redraw is needed.
		 */
		EFScrollRedrawWholeScreen = CLayoutData::EFLargeNumber,
		/** The maximum line width when wrapping is unset. */
		EFMaximumLineWidth = CLayoutData::EFBodyWidthForNoWrapping,
		};


	enum
		{
		/** Wrapping off; overrides the paragraph format. */
		EFAllParagraphsNotWrapped = TRUE,
		/** Wrapping on, unless <code>CParaFormat::iWrap</code> is false. */
		EFParagraphsWrappedByDefault = FALSE
		};
	
	/**
	 *
	 * Amount to format.
	 
	 *
	 * Used by <code>CTextLayout::SetAmountToFormat()</code>.
	 * * @since 
	 */

	enum TAmountFormatted
		{
		/** Format the whole document. */
		EFFormatAllText = FALSE,
		/** Format the visible band only. */
		EFFormatBand = TRUE,
		};
	
	/**
	 *
	 * Formatting information.
	 * @since 
	 */

	enum TCurrentFormat
		{
		/** Returned by some <code>CTextLayout</code> enquiry functions to
		indicate that no formatting has taken place so that the requested
		value cannot be calculated.
		 */
		EFNoCurrentFormat = -1,
		/** Returned by <code>CTextLayout::ParagraphHeight()</code> when the
		paragraph is not formatted.
		 */
		EFNotInCurrentFormat = 0
		};

	enum TScrollFlags
		{
		EFScrollOnlyToTopsOfLines = 1
		};
public:
	/** Holds a start position, end position and whether the range should
	 * be set or cleared. */
	class TRangeChange
		{
	public:
		enum TChangeType { ESet, EClear };
		IMPORT_C TRangeChange(TInt aStart, TInt aEnd, TChangeType aChange);
		IMPORT_C TRangeChange();
		IMPORT_C void Set(TInt aStart, TInt aEnd, TChangeType aChange);
		IMPORT_C TChangeType Get(TInt& aStart, TInt& aEnd) const;
		/** Try to cancel out sections of the ranges that overlap */
		IMPORT_C void OptimizeWith(TRangeChange& aBuddy);
		IMPORT_C TBool NonNull() const;
		IMPORT_C TBool Clip(TInt aMin, TInt aMax);
	private:
		TInt iA;
		TInt iB;
		};

public:
	IMPORT_C static CTextLayout *NewL(MLayDoc *aDoc,TInt aWrapWidth);
	IMPORT_C ~CTextLayout();
	IMPORT_C void DiscardFormat();
	IMPORT_C void SetLayDoc(MLayDoc *aDoc);
	IMPORT_C void SetWrapWidth(TInt aWrapWidth);
	IMPORT_C void SetBandHeight(TInt aHeight);
	IMPORT_C TInt BandHeight() const;
	IMPORT_C void SetImageDeviceMap(MGraphicsDeviceMap *aGd);
	IMPORT_C void SetLabelsDeviceMap(MGraphicsDeviceMap *aDeviceMap);
	IMPORT_C void SetAmountToFormat(TAmountFormatted aAmountOfFormat = EFFormatBand);
	IMPORT_C TBool IsFormattingBand() const;
	IMPORT_C void SetFormatMode(CLayoutData::TFormatMode aFormatMode,TInt aWrapWidth,MGraphicsDeviceMap* aFormatDevice);
	IMPORT_C void ForceNoWrapping(TBool aNoWrapping = EFAllParagraphsNotWrapped);
	IMPORT_C TBool IsWrapping() const;
	IMPORT_C void SetTruncating(TBool aOn);
	IMPORT_C TBool Truncating() const;
	IMPORT_C void SetTruncatingEllipsis(TChar aEllipsis);
	IMPORT_C TChar TruncatingEllipsis() const;
	IMPORT_C void SetLabelsMarginWidth(TInt aWidth);
	IMPORT_C void SetNonPrintingCharsVisibility(TNonPrintingCharVisibility aVisibility);
	IMPORT_C TNonPrintingCharVisibility NonPrintingCharsVisibility() const;
	IMPORT_C TBool IsBackgroundFormatting() const;
	IMPORT_C void NotifyTerminateBackgroundFormatting();
	/** deprecated 7.0 */
	IMPORT_C void SetExcludePartialLines(TBool aExcludePartialLines = TRUE);
	/** deprecated 7.0 */
	IMPORT_C TBool ExcludingPartialLines() const;
	IMPORT_C void SetFontHeightIncreaseFactor(TInt aPercentage);
	IMPORT_C TInt FontHeightIncreaseFactor() const;
	IMPORT_C void SetMinimumLineDescent(TInt aPixels);
	IMPORT_C TInt MinimumLineDescent() const;
	IMPORT_C TInt DocumentLength() const;
	IMPORT_C TInt ToParagraphStart(TInt& aDocPos) const;
	IMPORT_C TInt PixelsAboveBand() const;
	IMPORT_C TInt YBottomLastFormattedLine() const;
	IMPORT_C TInt FormattedHeightInPixels() const;
	IMPORT_C TInt PosRangeInBand(TInt& aDocPos) const;
	IMPORT_C TBool PosInBand(TInt aDocPos,TPoint& aXyPos) const;
	IMPORT_C TBool PosIsFormatted(TInt aDocPos) const;
	IMPORT_C TInt FirstCharOnLine(TInt aLineNo) const;
	IMPORT_C TInt FormattedLength() const;
	IMPORT_C TInt FirstFormattedPos() const;
	IMPORT_C TInt NumFormattedLines() const;
	IMPORT_C TInt FirstLineInBand() const;
	IMPORT_C TInt GetLineRect(TInt aYPos,TRect& aLine) const;
	IMPORT_C TInt ParagraphHeight(TInt aDocPos) const;
	IMPORT_C TRect ParagraphRectL(TInt aDocPos) const;
	IMPORT_C TBool CalculateHorizontalExtremesL(TInt& aLeftX,TInt& aRightX,TBool aOnlyVisibleLines,
												TBool aIgnoreWrapCharacters = FALSE) const;
	IMPORT_C void GetCharacterHeightAndAscentL(TInt aDocPos,TInt& aHeight,TInt& aAscent) const;
	IMPORT_C void GetFontHeightAndAscentL(const TFontSpec& aFontSpec,TInt& aHeight,TInt& aAscent) const;
	IMPORT_C TInt XyPosToDocPosL(TPoint &aPos, TUint aFlags = 0) const;
	IMPORT_C TBool DocPosToXyPosL(TInt aDocPos, TPoint& aPos, TUint aFlags = 0) const;
	IMPORT_C TRect GetLineRectL(TInt aDocPos1,TInt aDocPos2) const;
	IMPORT_C TBool PictureRectangleL(TInt aDocPos,TRect& aPictureRect,TBool* aCanScaleOrCrop = NULL) const;
	IMPORT_C TBool PictureRectangleL(const TPoint& aXyPos,TRect& aPictureRect,TBool* aCanScaleOrCrop = NULL) const;
	IMPORT_C TInt FirstDocPosFullyInBand() const;
	IMPORT_C void GetMinimumSizeL(TInt aWrapWidth,TSize& aSize);
	IMPORT_C TInt MajorVersion() const;
	IMPORT_C TInt SetViewL(TInt aDocPos,TInt& aYPos,TViewYPosQualifier aYPosQualifier,
						   TDiscard aDiscardFormat = EFViewDontDiscardFormat);
	IMPORT_C void FormatBandL();
	IMPORT_C void FormatCharRangeL(TInt aStartDocPos,TInt aEndDocPos);
	void FormatCharRangeL(TInt aStartDocPos,TInt aEndDocPos,TInt aPixelOffset);
	IMPORT_C TBool FormatNextLineL(TInt& aBotPixel);
	IMPORT_C TBool FormatLineL(CParaFormat* aParaFormat,TInt& aDocPos,TInt& aHeight,TBool& aPageBreak);
	IMPORT_C TInt ScrollParagraphsL(TInt& aNumParas,TAllowDisallow aScrollBlankSpace);
	IMPORT_C TInt ScrollLinesL(TInt& aNumLines,TAllowDisallow aScrollBlankSpace = EFDisallowScrollingBlankSpace);
	IMPORT_C TInt ChangeBandTopL(TInt& aPixels,TAllowDisallow aScrollBlankSpace = EFDisallowScrollingBlankSpace);
	IMPORT_C void PageUpL(TInt& aYCursorPos,TInt& aPixelsScrolled);
	IMPORT_C void PageDownL(TInt& aYCursorPos,TInt& aPixelsScrolled);
	IMPORT_C TBool HandleCharEditL(TUint aType,TInt& aCursorPos,TInt& aGood,TInt& aFormattedUpTo,
								   TInt& aFormattedFrom,TInt& aScroll,TBool aFormatChanged);
	IMPORT_C void HandleBlockChangeL(TCursorSelection aSelection,TInt aOldCharsChanged,TViewRectChanges& aViewChanges,
									 TBool aFormatChanged);
	IMPORT_C void HandleAdditionalCharactersAtEndL(TInt& aFirstPixel,TInt& aLastPixel);
	IMPORT_C void ReformatVerticalSpaceL();
	IMPORT_C void AdjustVerticalAlignment(CParaFormat::TAlignment aVerticalAlignment);
	IMPORT_C static void DrawBorders(const MGraphicsDeviceMap* aGd,CGraphicsContext& aGc,const TRect& aRect,
									 const TParaBorderArray& aBorder,const TRgb* aBackground = NULL,
									 TRegion* aClipRegion = NULL,const TRect* aDrawRect = NULL);
	IMPORT_C void DrawL(const TRect& aDrawRect,const TDrawTextLayoutContext* aDrawTextLayoutContext,
						const TCursorSelection* aHighlight = NULL);
	/**
	 * Highlight the specified range. Deprecated - use Highlight instead.
	 * @deprecated 7.0
	 * @see Highlight
	 */
	IMPORT_C void InvertRangeL(const TCursorSelection& aHighlight,const TRect& aDrawRect,
							   const TDrawTextLayoutContext* aDrawTextLayoutContext);
	IMPORT_C void Highlight(const TRangeChange& aHighlight,const TRect& aDrawRect,
		const TDrawTextLayoutContext* aDrawTextLayoutContext);
	IMPORT_C void SetCustomDraw(const MFormCustomDraw* aCustomDraw);
	IMPORT_C const MFormCustomDraw* CustomDraw() const;
	// deprecated
	IMPORT_C TInt GetLineNumber(TInt aDocPos);
	IMPORT_C void SetHighlightExtensions(TInt aLeftExtension, TInt aRightExtension, TInt aTopExtension, TInt aBottomExtension);
	IMPORT_C void SetCustomWrap(const MFormCustomWrap* aCustomWrap);
	IMPORT_C const MFormCustomWrap* CustomWrap() const;


	/**
	 * Dangerous function. Makes scroll operations set the top of the screen
	 * flush to the top of a line. In general this might scroll the cursor off
	 * the screen.
	 */
	inline void RestrictScrollToTopsOfLines(TBool aRestrict);

	// Non-exported public functions: used in the implementation of CTextView
	void DrawBackground(CGraphicsContext& aGc,const TPoint& aTopLeft,const TRect& aClipRect,
						const TLogicalRgb& aBackground) const;
	TBool DocPosToXyPos(TInt aDocPos,TBool aLeadingEdge,TPoint& aPos) const;
	TInt XyPosToDocPos(TPoint &aPos,TBool& aLeadingEdge,TUint aFlags = CLayoutData::EFIndividualChars) const;
	TBool CalculateHorizontalExtremes(TInt& aLeftX,TInt& aRightX,TBool aOnlyVisibleLines) const;
	TBool GetCursor(const TTmDocPos& aDocPos,TTmCursorPlacement aPlacement,
				    TRect& aLineRect,TPoint& aOrigin,TInt& aWidth,TInt& aAscent,TInt& aDescent);
	TBool NeedsNoHorizontalScroll(TInt aWidthInPixels) const;
	TInt ScrollDocPosIntoViewL(TInt aDocPos);
	void HighlightUsingExtensions(const CTextLayout::TRangeChange& aChangeHighlight,const TRangeChange& aFullHighlight,
		const TRect& aDrawRect,	const TDrawTextLayoutContext* aDrawTextLayoutContext);
	inline const TTmHighlightExtensions& HighlightExtensions() const;
	void GetHighlightRemnants(const TRect& aRect, const TDrawTextLayoutContext& aDrawTextLayoutContext, TRect* aRemainderRects) const;
	IMPORT_C void ExtendFormattingToCoverYL(TInt aYPos);
	IMPORT_C void ExtendFormattingToCoverPosL(TInt aDocPos);

	
#ifdef _DEBUG
	TBool __DbgIsFormattingUpToDate();
#endif

	enum TPanicNumber
		{
		EUnimplemented,
		ENoMemory,
		EDrawingBorderError,
		EFormatDeviceNotSet,
		EImageDeviceNotSet,
		EPixelNotInFormattedLine,
		EInvalidDocPos,
		ENoCharRangeToFormat,
		ECharacterNotFormatted,
		EPrintPreviewModeError,
		EBadCharacterEditType,
		EInvalidLineNumber,
		EPosNotFormatted,
		EMustFormatAllText,
		EPageScrollError
		};
	static void Panic(TPanicNumber aNumber);

private:
	IMPORT_C CTextLayout();
 	IMPORT_C void ConstructL(MLayDoc *aDoc,TInt aWrapWidth);
	CTextLayout(const CTextLayout&); // unimplemented
	void operator=(const CTextLayout&); // unimplemented
	void InitFormatParam(TTmFormatParamBase& aParam);
	void GetParagraphRect(TInt aDocPos,TRect& aRect) const;
	TInt ScrollL(TInt aDy,TAllowDisallow aScrollBlankSpace);
	void FormatBandL(TInt aStartDocPos,TInt aEndDocPos);
	void PruneFormat(TBool aFromStart);
	TInt VisibleHeightInPixels() const;
	TInt BandHeightInPixels() const;
	TInt SuggestCursorPos(TInt aCurrentCursorPos) const;
	TInt SetBandTop();
	void ClearHighlightRemnants(const TRect& aDrawRect, const TDrawTextLayoutContext& aDrawTextLayoutContext);

	CTmTextLayout iText;		// the TAGMA object that contains the text layout
	TLayDocTextSource iSource;	// the source of the text
	TInt iBandTop;		// effectively, scroll position: subtract this from CTmTextLayout y position
						// to give CTextLayout y position
	TInt iVisibleHeight;// in pixels if iFormatMode is EFScreenMode or EFWysiwygMode, otherwise twips
	TInt iBandHeight;	// in pixels if iFormatMode is EFScreenMode or EFWysiwygMode, otherwise twips

	TInt iScrollFlags;		// from CTextLayout::TScrollFlags
	TInt iUnformattedStart; // document position of the start of any unformatted text;
							// if < KMaxTInt, background formatting can be used
							// (by calling FormatNextLine) to format the remainder
	TBool iParInvalid;		// if true and background formatting is happening, the remainder of the paragraph
							// containing iUnformattedStart is invalid and must be reformatted;
							// otherwise, formatting stops when line ends match
	TTmHighlightExtensions iHighlightExtensions;
	};


/**
 *
 * Cursor position.
 *
 * The <code>TMovementType</code> enum defined in this class is used to
 * indicate the direction of a scroll or cursor movement. The remainder
 * of this class does not form part of the API.
 *
 * @internal
 * Internal to Symbian
 *
 * @since 5.0
 * @lib "N/A"
 */

class TCursorPosition
	{
public:
	
	/**
	 *
	 * Direction of cursor movement.
	 * @since 
	 */

	enum TMovementType
		{
		/** No cursor movement */
		EFNoMovement,
		/** Single character cursor movement to the left */
		EFLeft,
		/** Single character cursor movement to the right */
		EFRight,
		/** Line up cursor movement */
		EFLineUp,
		/** Line down cursor movement */
		EFLineDown,
		/** Page up cursor movement */
		EFPageUp,
		/** Page down cursor movement */
		EFPageDown,
		/** Cursor movement to line start */
		EFLineBeg,
		/** Cursor movement to line end */
		EFLineEnd
		};
	enum TDrawSelectionFlags
		{
		EFDrawNone=0x00,			//Must be zero (that is false)
		EFDrawHighlight=0x01,
		EFDrawOldPictureFrame=0x02,
		EFDrawNewPictureFrame=0x04
		};
	enum		//Values for doing LineBeg and LineEnd
		{
		EFFirstCharOnLine=(-CLayoutData::EFLargeNumber),
		EFLastCharOnLine=CLayoutData::EFLargeNumber
		};
private:
	enum
		{
		EFAbove=-1,
		EFInside=0,
		EFBelow=1
		};
public:
	inline TCursorPosition();
	inline void SetLayout(CTextLayout *aLayout);
	inline TBool IsSelection() const;
	inline TBool IsSelectionToDraw() const;
	TBool IsPictureFrame() const;
	TBool IsNewPictureFrame() const;
	inline TInt LatentX();
	inline void UpdateLatentX(TInt aX);
	inline void SetToPreviousHighlight();
	inline void SetToCurrentHighlight();
	TBool CancelHighlight();
	TInt SetSelectionL(const TCursorSelection& aSelection);
	void SetPendingSelection(const TCursorSelection& aSelection);
	void GetOldSelection(TCursorSelection& aSelection) const;
	void GetSelection(TCursorSelection& aSelection) const;
	TInt SetDocPosL(TBool aDragSelectOn,TInt aDocPos);
	TInt SetXyPosL(TBool aDragSelectOn,TPoint aPos,TBool aAllowPictureFrame);
	TInt MoveL(TBool aDragSelectOn,TMovementType& aMovement,TBool aAllowPictureFrame);
	void UpdateLatentPosition();
	void TextMoveVertically();
	TBool GetCursor(TTmCursorPlacement aPlacement,TPoint& aOrigin,TInt& aWidth,TInt& aAscent,TInt& aDescent);
public:
	TInt iDocPos;
	TInt iAnchor;
	TUint iDrawSelectionFlags;
private:
	enum TMode
		{
		EFReturnCurrentHighlight,
		EFReturnPreviousHighlight
		};
	enum
		{
		EFUseCurrentDocumentPosition=CLayoutData::EFLargeNumber
		};
private:
	TInt ViewTopOfLineL(TInt aDocPos,TInt& aYPos);
	void CheckSelection(TBool aSelect);
	void CheckNullSelection();
	inline void UpdateLatentY(TInt aY);
	TInt BringCursorOnScreenL(TInt aDocPos=EFUseCurrentDocumentPosition);
	TInt StayL();
	TInt RightL(TMovementType& aMovement,TBool aAllowPictureFrame);
	TInt LeftL(TMovementType& aMovement,TBool aAllowPictureFrame);
	TInt StartOfLineL();
	void DoStartOfLineL();
	TInt EndOfLineL();
	void DoEndOfLineL();
	TInt UpL(TMovementType& aMove);
	TInt DownL(TMovementType& aMove);
	TInt PageScrollL(TMovementType& aMove);
	TInt DoSetDocPosL(TInt aDocPos);
	TInt DoSetVisibleDocPosL(TInt aDocPos);
	void DoSetXyPosL(TPoint& aXy);
	void SelectPictureFrameByXyPosL(TInt aOldDocPos);
	void SetPictureFrame(TInt aDocPos,TInt aAnchor,const TRect& aPictureRect);
	inline TBool CalculateCursorPos(TPoint& aCurPos);
private:
	CTextLayout *iLayout;
	TBool iSelected;
	TInt iOldAnchor;
	TInt iOldDocPos;
	TMode iMode;
	TInt iLatentX;
	TInt iLatentY;
	};

void CTextLayout::RestrictScrollToTopsOfLines(TBool a)
	{
	if (a)
		iScrollFlags |= EFScrollOnlyToTopsOfLines;
	else
		iScrollFlags &= ~EFScrollOnlyToTopsOfLines;
	}

inline const TTmHighlightExtensions& CTextLayout::HighlightExtensions() const
	{
	return iHighlightExtensions;
	}

/**
 *
 * Default C++ constructor.
 *
 * Constructs a fully initialized <code>TViewYPosQualifier</code> object.
 * The hotspot is initialized to be the baseline of the line, the screen
 * is not filled, and the top line is not forced to be fully visible.
 *
 */

inline TViewYPosQualifier::TViewYPosQualifier():
	iHotSpot(EFViewBaseLine),
	iFillScreen(EFalse),
	iFullyVisible(EFViewDontForceLineFullyVisible)
	{
	}

/**
 *
 * Default C++ constructor.
 *
 * Constructs a <code>TViewRectChanges</code> object, initializing its
 * <code>iScrollAtTop</code> and <code>iScrollAtBottom</code> members to
 * zero.
 *
 */
	
inline TViewRectChanges::TViewRectChanges():
	iScrollAtTop(0),
	iScrollAtBottom(0)
	{
	}

/**
 *
 * Constructs the <code>TCursorSelection</code> object initialising the
 * cursor and anchor positions to zero.
 *
 */

inline TCursorSelection::TCursorSelection():
	iCursorPos(0),
	iAnchorPos(0)
	{
	}

inline TCursorSelection::TCursorSelection(TInt aCursorPos,TInt aAnchorPos):
	iCursorPos(aCursorPos),
	iAnchorPos(aAnchorPos)
	{
	}

/**
 *
 * Sets the cursor and anchor positions for the selection.
 *
 * @param     "TInt aCursorPos"
 *            The new cursor position.
 * @param     "TInt aAnchorPos"
 *            The new anchor position.
 */

inline void TCursorSelection::SetSelection(TInt aCursorPos,TInt aAnchorPos)
	{
	iCursorPos = aCursorPos;
	iAnchorPos = aAnchorPos;
	}

/**
 *
 * Gets the lesser of the cursor and anchor positions.
 *
 * @returns   "TInt"
 *            The lesser of the cursor and anchor positions.
 */

inline TInt TCursorSelection::LowerPos() const 
	{
	return Min(iCursorPos,iAnchorPos);
	}

/**
 *
 * Gets the greater of the cursor and anchor positions.
 *
 * @returns   "TInt"
 *            The greater of the cursor and anchor positions.
 */

inline TInt TCursorSelection::HigherPos() const
	{
	return Max(iCursorPos,iAnchorPos);
	}

/**
 *
 * Returns the number of characters in the selected range.
 *
 * @returns   "TInt"
 *            The length of the selection.
 */

inline TInt TCursorSelection::Length() const
	{
	return Abs(iCursorPos - iAnchorPos);
	}

inline TCursorPosition::TCursorPosition():
	iDocPos(0),
	iAnchor(0),
	iOldDocPos(0),
	iMode(EFReturnCurrentHighlight)
	{
	}

inline void TCursorPosition::SetLayout(CTextLayout *aLayout)
	{
	iLayout = aLayout;
	}

inline TBool TCursorPosition::IsSelection() const
	{
	return iSelected;
	}

inline TBool TCursorPosition::IsSelectionToDraw() const
	{
	return iDrawSelectionFlags;
	}

inline void TCursorPosition::SetToPreviousHighlight()
	{
	iMode = EFReturnPreviousHighlight;
	}

inline void TCursorPosition::SetToCurrentHighlight()
	{
	iMode = EFReturnCurrentHighlight;
	}

inline void TCursorPosition::UpdateLatentX(TInt aX)
	{
	iLatentX = aX;
	}

inline TInt TCursorPosition::LatentX()
	{
	return iLatentX;
	}

inline void TCursorPosition::UpdateLatentY(TInt aY)
	{
	iLatentY = aY;
	}

inline TBool TCursorPosition::CalculateCursorPos(TPoint& aPos)
	{
	return iLayout->DocPosToXyPos(iDocPos,TRUE,aPos);
	}

#endif
