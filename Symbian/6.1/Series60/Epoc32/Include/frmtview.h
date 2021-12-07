// FRMTVIEW.H
//
// Copyright (c) 1997-1999 Symbian Ltd. All rights reserved.
//

#ifndef __FRMTVIEW_H__
#define __FRMTVIEW_H__

#include <e32std.h>
#include <e32base.h>
#include <w32std.h>
#include <frmtlay.h>
#include <frmframe.h>

// Internal class - not part of interface
class RScreenDisplay
	{
public:
	enum TClippingRects
		{
		EFClipTextArea = 0x0001,
		EFClipLineCursor = 0x0002,
		EFClipExtendedTextArea = 0x0004,
		EFClipViewRect = 0x0008,
		EFClipExtendedViewRect = 0x0010,
		EFClipInvalid = 0x0200,
		EFClipAllFlags = 0xFFFF
		};
public:
	RScreenDisplay(TDrawTextLayoutContext* const aDrawTextLayoutContext); 
	void Close();
	void Destroy();
	inline void SetWindowsServer(RWsSession *aSession) { iSession = aSession; }
	inline void SetWindowGroup(RWindowGroup *aWin) { iGroupWin = aWin; }
	void SetWindow(RWindow *aWin);
	RWindow* Window() const { return iWin; }
	void SetBitmapContext(CBitmapContext* aGc) { iGc = aGc; }
	CBitmapContext* BitmapContext() const { return iGc; }
	RWsSession* WindowServerSession() { return iSession; }
	void SetGraphicsDeviceL(CBitmapDevice *aGd);
	void CreateContextL();
	void SetInvalidRect(const TRect& aRect);
	void SetInvalidRect(TInt aHeight);
	void SetInvalidRectHorizontal(TInt aWidth);
	void SetRects(TUint aRects);
	inline TRect LineCursorMargin() const;
	inline TPoint TopLeftTextArea() const;
	inline TBool IsLineCursor() const;
	void AddRects(TUint aRects);
	void SubRects(TUint aRects);
	TRect ClippingRect();	
	void ResetClippingRect();	
	void Scroll(TRect aRect,const TPoint& aBy,TBool aScrollBackground);
	void Flush();
	void ClearRect(const TRect& aRect);
	void InvertRect(TRect aRect,const TRgb aInvertColor);
	void SetTextCursor(TPoint aPos, const TTextCursor &aCursor);
	void RemoveTextCursor();
	void BlastBitmap(const TPoint& aPoint,const CFbsBitmap* aBitmap,const TRect& aRect);
	void DrawPictureFrame(TFrameOverlay* aPictureFrame,const TRect& aLineRect);
	void Invalidate(TRect aRect);
	void ActivateContext();
	void ActivateContext(CGraphicsContext *aGc);
	void DeactivateContext();
	void DeactivateContext(CGraphicsContext *aGc);
	inline void SetLayout(const CTextLayout* aLayout);
private:
	void DestroyContexts();
#if defined(TIMING_CODE)
public:
	class TTestTimingCode* iTestTimingCode;
#endif
private:
	RWsSession *iSession;
	RWindowGroup *iGroupWin;
	RWindow *iWin;
	CBitmapContext *iGc;
	CBitmapDevice *iGd;
	TDrawTextLayoutContext* const iDrawTextLayoutContext;
	TUint iRects;
	TRect iInvalidRect;
	TLogicalRgb iBackground;
	const CTextLayout* iTextLayout;
#ifdef TIMING_CODE
public:
	inline void SetTimingFlags(TUint aFlags) { iTimingFlags = aFlags; }
	TUint iTimingFlags;
	inline void SetHandle(CWindowGc *aGc,RWsSession *aWs) { iTGc = aGc; iWs = aWs; }
	CWindowGc *iTGc;
	RWsSession *iWs;
#endif
	};

// Internal class - not part of interface

/**
 *
 * Visibility of line and text cursor.
 *
 * The <code>TVisibility</code> enumeration defined in this class is used
 * in calls to <code>CTextView::SetCursorVisibilityL()</code>. The
 * remainder of this class does not form part of the API.
 *
 * @since 5.0
 * @lib "N/A"
 */

class TCursor
	{
	public:
	enum TCursors
		{
		EFNeitherCursor = 0,
		EFTextCursor = 1,
		EFLineCursor = 2,
		EFBothCursors = EFTextCursor | EFLineCursor
		};
	
	/**
	 *
	 * Cursor visibility.
	 * @since 
	 */

	enum TVisibility
		{
		/** Indicates that the cursor should be invisible. */
		EFCursorInvisible = 0,
		/** Indicates that the cursor should be visible. */
		EFCursorVisible,
		/** Indicates a flashing text cursor. When specified for the line cursor,
		is equivalent to <code>EFCursorVisible</code>, as the line cursor
		cannot flash. Note that a non-flashing text cursor should only be used
		when there is to be no editing, reformatting, scrolling or cursor
		movement.
		 */
		EFCursorFlashing
		};

	inline TCursor(TCursorPosition& aCursorPos,RScreenDisplay& aDisplay);
	void SetLineCursorBitmap(const CFbsBitmap* aLineCursorBitmap);
	inline TUint LineCursorVisibility();
	inline TUint TextCursorVisibility();
	void Draw(TUint aCursors);

	void SetVisibility(TVisibility aLineCursor,TVisibility aTextCursor);
	void SetType(TTextCursor::EType aType);
	void SetPlacement(TTmCursorPlacement aPlacement);
	void SetAscentAndDescent(TInt aAscent,TInt aDescent);
	void SetWeight(TInt aWeight);
	void SetFlash(TBool aEnabled);
	void SetXorColor(TRgb aColor);
	void MatchCursorHeightToAdjacentChar();
	void SetExtensions(TInt aFirstExtension, TInt aSecondExtension);


	private:
	enum
		{
		ELineCursorToLabelGap = 2,
		ETextCursorWeight = 3,
		ETextCursorInvertColor = 0xFFFFFF
		};

	void DrawLineCursor(TInt aHeight);
	void RemoveLineCursor();
	void DrawTextCursor(TPoint aOrigin,TInt aWidth,TInt aAscent,TInt aDescent);
	void RemoveTextCursor();

	RScreenDisplay& iDisplay;				// a reference to the object controlling drawing
	TCursorPosition& iCursorPos;			// a reference to the object holding the cursor's document position
	TBool iVisible;							// TRUE if the text cursor is currently visible in the displayed text
	TBool iFlash;							// TRUE if the text cursor should flash
	TVisibility iLineCursor;				// line cursor state
	TVisibility iTextCursor;				// text cursor state
	const CFbsBitmap* iLineCursorBitmap;	// if non-null, points to a non-owned bitmap representing the line cursor
	TInt iAscent;							// if non-negative, ascent used for vertical cursors
	TInt iDescent;							// if non-negative, descent used for vertical cursors
	TInt iWeight;							// width of vertical cursors, height of horizontal ones
	TTextCursor::EType iType;				// filled or hollow rectangle, etc.
	TRgb iXorColor;							// colour XORed with the background when the cursor is drawn
	TTmCursorPlacement iPlacement;			// vertical, underline, etc.
	TInt iFirstExtension;					// customise the cursor, extends vertical cursors upwards, horizontal cursors leftwards
	TInt iSecondExtension;					// customise the cursor, extends vertical cursors downwards, horizontal cursors rightwards
	TInt iReserved[2];
	};

/**
 *
 * Lays out formatted text for display.
 *
 * The class provides functions to:
 * convert between document positions and x,y coordinates
 * set the dimensions of the rectangle in which text can
 * be viewed (the view rectangle)set margin widths
 * do horizontal and vertical scrolling
 * do text selectionset the cursor position and appearance
 *
 * After a change has been made to the text layout, a reformat
 * and redraw should normally take place. <code>CTextView</code> provides
 * functions which are optimised to reformat the minimum amount
 * necessary. For example, when a global formatting parameter is changed
 * (e.g. the wrap width), the whole document's layout needs to be
 * recalculated, so <code>HandleGlobalChangeL()</code> should be called.
 * If the change involves the insertion or deletion of a single
 * character, only a single line may be affected; for this,
 * <code>HandleCharEditL()</code> is appropriate. Most
 * <code>CTextView</code> reformatting functions do scrolling (using
 * block transfer), if necessary, and a redraw.For maximum
 * responsiveness, <code>CTextView</code> uses an active object to carry
 * out reformatting as a background task, so that the application can
 * continue to receive user input. Many <code>CTextView</code> functions
 * force background formatting to complete before they take effect.When
 * scrolling vertically, positive numbers of pixels, lines, paragraphs,
 * pages, etc., mean that the text moves down, and vice versa. When
 * scrolling horizontally, positive numbers of pixels mean that the text
 * moves left and vice versa.A text view can display up to two cursors
 * and up to three margins. The cursors are the text cursor and the line
 * cursor. The purpose of the line cursor is to make it easier to see
 * which line the text cursor (or the selection extension point) is on.
 * The three margins are the label margin (for paragraph labels), the
 * line cursor margin (for the line cursor) and the left text margin (the
 * gap between the edge of the page and the text). All are optional, but
 * if present, they appear in that order, starting at the left edge of
 * the view rectangle.An object of class <code>CTextLayout</code> is used
 * by the text view to calculate changes to the layout. This object must
 * be specified when constructing the text view. It is also used to set
 * layout attributes, including the wrap width, the height of the visible
 * portion of the document (the "band"), whether formatting is set to the
 * band or to the whole document and the text object which is the source
 * of the text and formatting information.The x-y pixel coordinates used
 * by <code>CTextView</code> are called window coordinates. Window
 * coordinates have their origin at the top left corner of the view
 * window (unlike class <code>CTextLayout</code> whose coordinates have
 * their origin at the top left corner of the area within the view
 * rectangle in which text can appear). As in most bitmap graphics
 * systems, x coordinates increase rightwards and y coordinates increase
 * downwards.
 *
 * @since 5.0
 * @lib " form.lib "
 */

class CTextView : public CBase
	{
friend class CTestTextView;
public:
	enum TPriorities
		{
		EFBackgroundFormattingPriority = (CActive::EPriorityIdle + CActive::EPriorityLow) / 2
		};

	// sentinel values for x coord passed to XyPosToDocPosL
	enum
		{
		EFFirstCharOnLine = TCursorPosition::EFFirstCharOnLine,
		EFLastCharOnLine = TCursorPosition::EFLastCharOnLine
		};


	/**
	 *
	 * Cursor height matching.
	 
	 *
	 * Passed as an argument to
	 * <code>MatchCursorHeightToAdjacentChar()</code>.
	 * * @since 
	 */

	enum TBeforeAfter
		{
		/** Text cursor height is matched to preceding character. */
		EFCharacterBefore = ETrue,
		/** Text cursor height is matched to following character. */
		EFCharacterAfter = EFalse
		};

	
	/**
	 *
	 * Whether to reformat and redraw.
	 
	 *
	 * Argument to <code>SetViewL()</code>.
	 * * @since 
	 */

	enum TDiscard
		{
		/** Discard all formatting; redraw. */
		EFViewDiscardAllFormat,
		/** Do not discard all formatting; redraw. */
		EFViewDontDiscardFormat,
		/** Discard all formatting; no redraw. */
		EFViewDiscardAllNoRedraw,
		/** Do not discard all formatting; redraw. */
		EFViewDontDiscardFullRedraw
		};
	
	/**
	 *
	 * Provides notification to the owner of the text view object of changes
	 * to the formatting.
	 *
	 * Its <code>OnReformatL()</code> function is called after reformatting
	 * but before redisplay, so that edit windows etc. can be resized.
	 *
	 * @since 6.0
	 * @lib " form.lib "
	 */

	// An observer class allowing owners of CTextView objects to receive notification of changes.
	class MObserver
		{
		public:

		/**
		 *
		 * Called after reformatting but before redisplay, so that edit windows,
		 * etc. can be resized.
		 *
		 * @param     " const CTextView* aTextView "
		 *            A pointer to the current text view object.
		 */

		virtual void OnReformatL(const CTextView* aTextView) = 0;
		};

	// argument to SetViewL
	enum TDoHorizontalScroll
		{
		EFNoHorizontalScroll = EFalse,
		EFCheckForHorizontalScroll = ETrue
		};

private:
	enum TDrawParameters
		{
		EFDrawAllWindow = CLayoutData::EFLargeNumber // must be larger than the pixel height of any window.
		};

	// bit values used in iFlags
	enum
		{
		EFSelectionVisible = 1,
		EFPictureFrameEnabled = 2,
		EFEverythingVisible = 3,
		EFFlickerFreeRedraw = 4
		};

	// horizontal scroll jump in pixels
	enum THorizontalScrollJump
		{
		EFDefaultHorizontalScrollJump = 20
#ifdef _DEBUG
		,EFUnreasonablyLargeHorizontalScrollJump = 10000
#endif
		};

	// picture frame blob widths in pixels
	enum TPictureFrameBlobWidths
		{
		EFFrameVisibleBlobWidth = 10,
		EFFrameActiveBlobWidth = 20
		};

	enum THorizontalScroll
		{
		EFNoPreviousHorizontalScroll = 0,
		EFPreviousHorizontalScroll
		};

	enum TMemoryStatus
		{
		EFMemoryOK,
		EFOutOfMemory,
		EFRecovering
		};

	enum TExtendedHighlightRedraw
		{
		EFTopEdge = 0x0001,
		EFBottomEdge = 0x0002
		};
public:
	IMPORT_C static CTextView *NewL(CTextLayout* aLayout,const TRect &aDisplay,CBitmapDevice* aGd,
									MGraphicsDeviceMap* aDeviceMap,RWindow* aWin,RWindowGroup* aGroupWin,
									RWsSession* aSession);
	IMPORT_C ~CTextView();
	IMPORT_C void SetDisplayContextL(CBitmapDevice* aGd,RWindow* aWin,RWindowGroup* aGroupWin,RWsSession* aSession);
	IMPORT_C void SetLayout(CTextLayout* aLayout);
	inline const CTextLayout* Layout() const;
	IMPORT_C void SetViewRect(const TRect& aDisplay);
	// deprecated, to be removed
	IMPORT_C void AlterViewRect(const TRect &aViewRect);
	IMPORT_C void SetMarginWidths(TInt aLabels,TInt aLineCursor);
	IMPORT_C void SetHorizontalScrollJump(TInt aScrollJump);
	IMPORT_C void SetLineCursorBitmap(const CFbsBitmap* aLineCursorBitmap);
	IMPORT_C void SetHighlightExtensions(TInt aLeftExtension, TInt aRightExtension, TInt aTopExtension, TInt aBottomExtension);
	IMPORT_C void SetBackgroundColor(TRgb aColor);
	IMPORT_C void SetTextColorOverride(const TRgb* aOverrideColor = NULL);
	IMPORT_C void SetCursorVisibilityL(TUint aLineCursor,TUint aTextCursor);
	IMPORT_C void SetSelectionVisibilityL(TBool aSelectionVisible);
	IMPORT_C TBool SelectionVisible() const;
	IMPORT_C void EnablePictureFrameL(TBool aEnabled);
	IMPORT_C const TRect& ViewRect() const;
	/* 
	Use the AlteredViewRect method to obtain the view Rect only if a clipping rect has been set 
	to reduce edwin view area.  If unset, or disabled, the Rect will have height 0.
	*/
	// deprecated, to be removed
	IMPORT_C const TRect& AlteredViewRect() const;
	IMPORT_C void MarginWidths(TInt& aLabels,TInt& aLineCursor) const;
	IMPORT_C TInt HorizontalScrollJump() const;
	IMPORT_C TInt LeftTextMargin() const;
 	IMPORT_C void SetLatentXPosition(TInt aLatentX);
	IMPORT_C void SetParagraphFillTextOnly(TBool aFillTextOnly);
	IMPORT_C void SetCursorWidthTypeL(TTextCursor::EType aType,TInt aWidth = 0);
	IMPORT_C void SetCursorPlacement(TTmCursorPlacement aPlacement);
	IMPORT_C void SetCursorWeight(TInt aWeight);
	IMPORT_C void SetCursorExtensions(TInt aFirstExtension, TInt aSecondExtension);
	IMPORT_C void SetCursorFlash(TBool aEnabled);
	IMPORT_C void SetCursorXorColor(TRgb aColor);
	IMPORT_C TCursorSelection Selection() const;
	IMPORT_C TBool IsPictureFrameSelected(TRect& aPictureFrameRect,TInt& aDocPos) const;
	IMPORT_C TBool GetPictureRectangleL(TInt aDocPos,TRect& aPictureRect,TBool* aCanScaleOrCrop = NULL) const;
	IMPORT_C TBool GetPictureRectangleL(TPoint aXyPos,TRect& aPictureRect,TBool* aCanScaleOrCrop = NULL);
	IMPORT_C TInt XyPosToDocPosL(TPoint& aPoint);
	IMPORT_C TBool DocPosToXyPosL(TInt aDocPos,TPoint& aPoint);
	IMPORT_C TRect ParagraphRectL(TInt aDocPos) const;
	IMPORT_C void CalculateHorizontalExtremesL(TInt& aLeftX,TInt& aRightX,TBool aOnlyVisibleLines);
	IMPORT_C void MatchCursorHeightL(const TFontSpec& aFontSpec);
	IMPORT_C void MatchCursorHeightToAdjacentChar(TBeforeAfter aBasedOn = EFCharacterBefore);
	IMPORT_C TPoint SetSelectionL(const TCursorSelection& aSelection);
	IMPORT_C void CancelSelectionL();
	IMPORT_C void ClearSelectionL();
	IMPORT_C TPoint SetDocPosL(TInt aDocPos,TBool aDragSelectOn = EFalse);
	IMPORT_C TPoint SetXyPosL(TPoint aPos,TBool aDragSelectOn,TRect*& aPictureRect,TInt& aPictureFrameEdges);
	IMPORT_C TPoint MoveCursorL(TCursorPosition::TMovementType& aMovement,TBool aDragSelectOn);
	IMPORT_C TInt ScrollDisplayL(TCursorPosition::TMovementType aMovement,
		CTextLayout::TAllowDisallow aScrollBlankSpace=CTextLayout::EFDisallowScrollingBlankSpace);
	IMPORT_C TPoint SetViewLineAtTopL(TInt aLineNo);
	IMPORT_C void ScrollDisplayPixelsL(TInt& aDeltaY);
	IMPORT_C TInt ScrollDisplayLinesL(TInt& aDeltaLines,
		CTextLayout::TAllowDisallow aScrollBlankSpace = CTextLayout::EFDisallowScrollingBlankSpace);
	IMPORT_C TInt ScrollDisplayParagraphsL(TInt& aDeltaParas,
		CTextLayout::TAllowDisallow aScrollBlankSpace = CTextLayout::EFDisallowScrollingBlankSpace);
	IMPORT_C TPoint SetViewL(TInt aDocPos,TInt& aYPos,TViewYPosQualifier aYPosQualifier = TViewYPosQualifier(),
		TDiscard aDiscardFormat = EFViewDontDiscardFormat,
		TDoHorizontalScroll aDoHorizontalScroll = EFCheckForHorizontalScroll);
 	IMPORT_C void SetLeftTextMargin(TInt aLeftMargin);
	IMPORT_C void DrawL(TRect aRect);
	IMPORT_C void DrawL(TRect aRect,CBitmapContext& aGc);
	inline void SetObserver(MObserver* aObserver);
	IMPORT_C void SetPendingSelection(const TCursorSelection& aSelection);
	inline void EnableFlickerFreeRedraw();
	inline void DisableFlickerFreeRedraw();
	inline TBool FlickerFreeRedraw() const;

	// reformatting after changes to the content
 	IMPORT_C void FormatTextL();
	IMPORT_C TInt HandleCharEditL(TUint aType = CTextLayout::EFCharacterInsert,TBool aFormatChanged = EFalse);
	IMPORT_C TPoint HandleRangeFormatChangeL(TCursorSelection aSelection,TBool aFormatChanged = EFalse);
	IMPORT_C TPoint HandleInsertDeleteL(TCursorSelection aSelection,TInt aDeletedChars,TBool aFormatChanged = EFalse);
	IMPORT_C void HandleGlobalChangeL(TViewYPosQualifier aYPosQualifier = TViewYPosQualifier());
	IMPORT_C void HandleGlobalChangeNoRedrawL(TViewYPosQualifier aYPosQualifier = TViewYPosQualifier());
	IMPORT_C void HandleAdditionalCharactersAtEndL();
	IMPORT_C void FinishBackgroundFormattingL();

private:
	IMPORT_C static TInt IdleL(TAny *aSelf);
	IMPORT_C CTextView();
	IMPORT_C void ConstructL(CTextLayout* aLayout,const TRect &aDisplay,CBitmapDevice* aGd,MGraphicsDeviceMap* aDeviceMap,
							 RWindow* aWin,RWindowGroup* aGroupWin,RWsSession* aSession);
	inline TInt TopViewRect() const;
	inline TBool IsFormatting() const;
	TBool NoMemoryCheckL();
	void StartIdleObject();
	inline void DrawWithPreviousHighlight();
	inline void DrawWithCurrentHighlight();
	TInt CalculateBaseLinePos(TInt& aDocPos);
	TInt DrawAfterCursorMoveL(TInt aScrollBy);
	TBool NextLineL();
	void ClearRectAtBottom(TInt aHeight);
	void DrawTextL(TInt aFromHeight = 0,TInt aToHeight = EFDrawAllWindow);
	void DisplayNewLinesL(TInt aFrom,TInt aTo);
	void DrawCursor(TUint aCursors = TCursor::EFBothCursors);
	TPoint DoMoveCursorL(TBool aDragSelectOn,TCursorPosition::TMovementType& aMovement,TBool aAllowPictureFrame);
	void ScrollTextL(TInt aScrollY,TInt aFrom,TInt aScrollX,TBool aScrollBackground);
	void ScrollRect(TRect& aRect,TInt aScrollY,TInt aFrom,TInt aScrollX,TBool aScrollBackground);
	void ScrollRect(TInt aScrollY,TInt& aFrom,TInt& aTo);
	TPoint HandleBlockChangeL(TCursorSelection aSelection,TInt aOldCharsChanged,TBool aFormatChanged);
	void CheckScrollUpL();
	TInt CheckHorizontalScroll(TInt aDocPos);
	TInt DoHorizontalScrollDisplayL(TCursorPosition::TMovementType aMovement,
		CTextLayout::TAllowDisallow aScrollBlankSpace);
	TInt DoScrollDisplayL(TCursorPosition::TMovementType aMovement,CTextLayout::TAllowDisallow aScrollBlankSpace);
	void ScrollDisplayL(TInt aPixels,TInt aHorizPixels = 0,TInt aYScrollLimit = EFDrawAllWindow);
	void ScrollUpperDisplayL(TInt aPixels);
	TPoint ViewTopOfLineL(TInt aDocPos,TInt& aYPos,CTextView::TDiscard aDiscardFormat = EFViewDontDiscardFormat,
		TDoHorizontalScroll aHorizontalScroll = EFCheckForHorizontalScroll);
	TPoint ViewL(TInt aDocPos,TInt& aYPos,TViewYPosQualifier aYPosQualifier = TViewYPosQualifier(),
		CTextView::TDiscard aDiscardFormat = EFViewDontDiscardFormat,
		TDoHorizontalScroll aHorizontalScroll = EFCheckForHorizontalScroll);
	TPoint DoHandleGlobalChangeL(TViewYPosQualifier aYPosQualifier,CTextView::TDiscard aDiscard);
	void UpdateHighlightL();
	void Highlight(CTextLayout::TRangeChange aRange);
	void HighlightUsingExtensions(CTextLayout::TRangeChange aOptimizedRange, CTextLayout::TRangeChange aOriginalRange);
	void InvertPictureFrameL(TInt aPos,TRect* aDrawRect = NULL);
	void DestroyWindowServerObjects();
	void NoMemoryL(TInt aErr);
	void RecoverNoMemoryL();
	void RecreateWindowServerObjectsL();
	void DrawTextSupportL(const TRect& aRect,const TCursorSelection* aHighlight);
	void DisplayLineRangeL(TInt aFrom,TInt aTo);
	inline void NotifyReformatL();
	void CalculateHorizontalExtremes(TInt& aLeftX,TInt& aRightX,TBool aOnlyVisibleLines);
	void DoClearSelectionL(const TCursorSelection& aSelection, TBool aIsPictureFrame);
	TBool ExtendedHighlightExists() const;
	void ClearHighlightRemnantsForScroll(const TRect& aScrollRect,TInt aScrollY, TInt aScrollX);
	void AdjustRectForScrolling(TRect &aRect, TInt aScrollY, TInt aScrollX) const;
	void UpdateExtendedHighlightL();

#ifdef TIMING_CODE
public:
	TTestTimingCode* iTestTimingCode;
#endif
private:
	CTextView(const CTextView&); // deliberately unimplemented
	CTextView& operator=(const CTextView&); // deliberately unimplemented

	CIdle* iWrap;
	RScreenDisplay iDisplay;
	CTextLayout* iLayout;
	TDrawTextLayoutContext iDrawTextLayoutContext;
	TCursor iCursor;
	TCursorPosition iCursorPos;
	TFrameOverlay* iPictureFrame;
	TMemoryStatus iNoMemory;
	TUint iFlags;
	TUint iHorizontalScroll;
	TInt iGood;
	TInt iFormattedUpTo;
	TInt iHorizontalScrollJump;
	TInt iHeightNotDrawn;
	MObserver* iObserver;
	// deprecated, planning to remove
	TRect iReducedDrawingAreaRect;
	TUint iRedrawExtendedHighlight;
#ifdef TIMING_CODE
public:
	inline void SetTimingFlags(TUint aFlags) 
		{ iDisplay.SetTimingFlags(aFlags); iLayout->SetTimingFlags(aFlags); iTimingFlags = aFlags; }
	TUint iTimingFlags;
	inline void SetHandle(CWindowGc* aGc,RWsSession* aWs)
			{ iDisplay.SetHandle(aGc,iWs); iLayout->SetHandle(aGc,iWs); iGc = aGc; iWs = aWs;}
	inline void SetCallBack(TCallBack aCallBack) { iLayout->SetCallBack(aCallBack); }
	CWindowGc* iGc;
	RWsSession* iWs;
#endif
	};

inline TBool RScreenDisplay::IsLineCursor() const
	{
	return iDrawTextLayoutContext->IsGutterMargin();
	}

inline TRect RScreenDisplay::LineCursorMargin() const
	{
	return iDrawTextLayoutContext->GutterMargin();
	}

inline TPoint RScreenDisplay::TopLeftTextArea() const
	{
	return iDrawTextLayoutContext->TopLeftTextArea();
	}

inline void RScreenDisplay::SetLayout(const CTextLayout* aLayout)
	{
	iTextLayout = aLayout;
	}

inline TCursor::TCursor(TCursorPosition& aCursorPos,RScreenDisplay& aDisplay):
	iDisplay(aDisplay),
	iCursorPos(aCursorPos),
	iVisible(FALSE),
	iFlash(TRUE),
	iLineCursor(EFCursorInvisible),
	iTextCursor(EFCursorInvisible),
	iLineCursorBitmap(NULL),
	iAscent(-1),
	iDescent(-1),
	iWeight(ETextCursorWeight),
	iType(TTextCursor::ETypeRectangle),
	iXorColor(ETextCursorInvertColor),
	iPlacement(ECursorVertical)
	{
	}

inline TUint TCursor::LineCursorVisibility()
	{
	return iLineCursor;
	}

inline TUint TCursor::TextCursorVisibility()
	{
	return iTextCursor;
	}

/**
 *
 * Returns a pointer to the text layout object used by the text view.
 *
 * @since     6.0
 * @returns   " CTextLayout* "
 *            A pointer to the text layout object used by the text
 *            view.
 */

inline const CTextLayout* CTextView::Layout() const
	{
	return iLayout;
	}

/**
 *
 * Sets a text view observer.
 *
 * This provides notification to the owner of the text view object of
 * changes to the formatting. Its <code>OnReformatL()</code> function is
 * called after reformatting but before redisplay, so that edit windows
 * etc. can be resized.
 *
 * @since     6.0
 * @param     " MObserver* aObserver "
 *            Pointer to text view observer object.
 */

inline void CTextView::SetObserver(MObserver* aObserver)
	{
	iObserver = aObserver;
	}

inline void CTextView::EnableFlickerFreeRedraw()
	{
	iFlags |= EFFlickerFreeRedraw;
	}

inline void CTextView::DisableFlickerFreeRedraw()
	{
	iFlags &= ~EFFlickerFreeRedraw;
	}

inline TBool CTextView::FlickerFreeRedraw() const
	{
	return iFlags & EFFlickerFreeRedraw;
	}

inline void CTextView::NotifyReformatL()
	{
	if (iObserver)
		{
		ASSERT(iNoMemory!=EFOutOfMemory);
		iObserver->OnReformatL(this);
		if (iNoMemory==EFOutOfMemory)
			User::Leave(KErrNoMemory);
		}
	}

inline TBool CTextView::IsFormatting() const
	{
	return iLayout->IsBackgroundFormatting();
	}

inline TInt CTextView::TopViewRect() const
	{
	return iDrawTextLayoutContext.iViewRect.iTl.iY;
	}

inline void CTextView::DrawWithPreviousHighlight()
	{
	iCursorPos.SetToPreviousHighlight();
	}

inline void CTextView::DrawWithCurrentHighlight()
	{
	iCursorPos.SetToCurrentHighlight();
	}

#endif
