// FRMFRAME.H
//
// Copyright (c) 1997-1999 Symbian Ltd. All rights reserved.
//

#ifndef __FRMFRAME_H__
#define __FRMFRAME_H__

#include <w32std.h>

/**
 *
 * A rectangular frame surrounding a picture with eight smaller, square
 * areas (referred to as blobs) for moving and resizing the picture.
 *
 * A blob is located on each corner and at the centre of each side.Each
 * blob has a visible width and an active width. The active width allows
 * easier manipulation of picture frames because the blobs may be small
 * and difficult to manipulate with a pen. The active width should be set
 * to be at least as large as the visible width.A picture frame also has
 * a set of flags which are used when drawing the frame. These control
 * the frame border visibility, whether blobs should be drawn inside or
 * outside the frame and whether the blobs should be filled using a solid
 * brush style or using a NULL brush style, causing them to appear
 * dimmed. For more information on brush styles. see
 * <code>CGraphicsContext::TBrushStyle</code>.
 *
 * @since 5.0
 * @lib "form.lib"
 */

class TFrameOverlay
    {
public:
	
/**
 *
 * This enumeration is used by <code>CTextView::SetXyPosL()</code> and by
 * <code>TFrameOverlay::XyPosToEdges()</code> to identify which active
 * region of the picture frame a pixel position is in.
 * @since 
 */

enum TEdges
	{
	/** Not in an active region. */
	ENoEdges=0x00,
	/** In active region around left edge. */
	EEdgeLeft=0x01,
	/** In active region around right edge. */
	EEdgeRight=0x02,
	/** In active region around top edge. */
	EEdgeTop=0x04,
	/** In active region around bottom edge. */
	EEdgeBottom=0x08
	};

/**
 *
 * Frame appearance flags.
 * @since 
 */

enum TFrameOverlayFlags
	{
	/** Controls whether blobs are drawn inside or outside the frame border. */
	EFrameOverlayFlagBlobsInternal=0x01,
	/** Controls whether the frame border is drawn or not. */
	EFrameOverlayFlagShowBorder=0x02,
	/** Controls whether the three blobs at the top of the frame are drawn dimmed. */
	EFrameOverlayFlagTopBlobsDimmed=0x04,
	/** Controls whether the three blobs at the bottom of the frame are drawn dimmed. */
	EFrameOverlayFlagBottomBlobsDimmed=0x08,
	/** Controls whether the three blobs on the left hand side of the frame are drawn dimmed. */
	EFrameOverlayFlagLeftBlobsDimmed=0x10,
	/** Controls whether the three blobs on the right hand side of the frame
	are drawn dimmed.
	 */
	EFrameOverlayFlagRightBlobsDimmed=0x20
	};
public:
	IMPORT_C TFrameOverlay();
    IMPORT_C void SetBlobWidthInPixels(const TInt aWidth); //sets visible and active blob width
    IMPORT_C void SetVisibleBlobWidthInPixels(const TInt aWidth); //default zero
    IMPORT_C void SetActiveBlobWidthInPixels(const TInt aWidth); // default zero
	IMPORT_C void SetFlags(TInt aFlag);
    IMPORT_C void ClearFlags(TInt aFlag);
    IMPORT_C void SetRect(const TRect& aRect);
    IMPORT_C void XorDraw(CGraphicsContext& aGc) const;
    IMPORT_C TInt XyPosToEdges(const TPoint& aPos) const;
    inline TRect Rect() const;		// deprecated
    inline const TRect& RefRect() const;
    inline TInt Flags() const;
private:
	TInt VisibleBlobWidth() const;
	TInt ActiveMarginWidth() const;
	TBool DrawLeftAndRight() const;
	TBool DrawTopAndBottom() const;
	void DrawDottedRectangle(CGraphicsContext& aGc,const TRect& aRect) const;
private:
    TInt iFlags;
    TInt iVisibleBlobWidth;
	TInt iActiveBlobWidth;
	TRect iRect;
    };

inline TRect TFrameOverlay::Rect() const		// deprecated
	{
	return(iRect);
	}

inline const TRect& TFrameOverlay::RefRect() const
	{
	return(iRect);
	}

TInt TFrameOverlay::Flags() const
	{
	return(iFlags);
	}

#endif
