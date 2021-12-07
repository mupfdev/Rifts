/*
* ============================================================================
*  Name     : CAknGMSStyleGrid.h
*  Part of  : Avkon
*
*  Description:
*       Contains the View and the Component of the photoalbum picture grid
*       component.
*
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef __CAknGMSStyleGrid_h
#define __CAknGMSStyleGrid_h

#include <AknGrid.h>
#include <aknpopup.h>
#include <aknlists.h>

class CGulIcon;

// ============================================================================
// CAknGMSStyleGridView
// ============================================================================

/**
	 the view for the grid component.
*/
class CAknGMSStyleGridView : public CAknGridView
	{
public: // from CAknGridView
	IMPORT_C CAknGMSStyleGridView();
public: // from	CAknGridView
	/**
		draws the hor. and vert. lines.
	*/
	IMPORT_C void Draw(const TRect* aClipRect = NULL) const;
public: // new methods
	/**
	 sets the rectangle for the drawing operations.
	 This method is called when the grid is constructed.
	 */
	IMPORT_C void SetupLayout(const TRect& aRect, TBool aIsPopup = EFalse, TInt aNum = -1);
private: // overridden from CListBoxView
	IMPORT_C virtual TAny* Reserved_1();
private: // data
	TAknLayoutRect iHorLine[5];
	TAknLayoutRect iVerLine[3];
	const TRect* iRect;
	};


// ============================================================================
// CAknGMSStyleGrid
// ============================================================================
/**
	implements the grid for the PhotoAlbum
	A markable grid_large_graphic_pane, with 2 columns. The cell displays
	80x32 bitmaps.
*/

class CAknGMSStyleGrid : public CAknSelectionGridTypedef
    {
public:
    /**
     * Creates a gms grid
     * @param aParent A parent used to find a window for the grid.
     * @param aIsPopup Whether a popup layout or main pane layout is used
     */
    IMPORT_C static CAknGMSStyleGrid* NewL(const CCoeControl* aParent, TBool aIsPopup = EFalse);
    /**
       do not use this, use NewL
       aIsPopup = EFalse is default.
    */
    IMPORT_C CAknGMSStyleGrid(); 
    /**
     * @param aIsPopup Whether a popup layout is used or not
     */
    IMPORT_C CAknGMSStyleGrid(TBool aIsPopup);
    /**
	 * 2nd phase of construction.
	 * @param aParent the parent compound control
	 * @param aRows desired rows of grid
	 * @param aCols desired cols of grid
	*/
	IMPORT_C void ConstructL(const CCoeControl* aParent, TInt aRows=4, TInt aCols=2);

	/**
		the destructor
	*/
	IMPORT_C ~CAknGMSStyleGrid();

    /**
     * Sets the layout of the grid view
     */
    IMPORT_C void SetupLayout();
public: // from CAknGrid
	/**
	 *	layouts and repaints the grid
	 */
	IMPORT_C void SizeChanged();
         
        /**
         * Decides size of the grid for dialogs.
         */
        IMPORT_C TSize MinimumSize();

	/**
	 * Offers key events to parent class.
	 * @param aKeyEvent kind of key event
	 * @param aType key typed
	 */
	IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);

	/**
	 * Defines a grid cell size
	 * @return size of a grid cell
	 */
    static TSize KCELL_SIZE();

	/**
	 * Redraw the grid.
	 * @param aRect the rectangle to draw.
	 */
	IMPORT_C void Draw(const TRect& aRect) const;
	
	/**
	 * Overriden from CAknGrid. Create the grid view for thus grid class.
	 * @ return the grid view
	 */ 
        IMPORT_C CListBoxView* MakeViewClassInstanceL();

protected:
    /**
     * Are we a popup window or main pane window, ETrue = popup window.
     */
    TBool iIsPopup;

private:
	/**
	 *	a helper method for logging calls
	 */	
	static void _LOG(const TDesC& aText);

private: // data

};

/** 
 * The window part of a gms grid.
 */
class CAknGMSPopupGrid : public CAknPopupList
    {
public:
    /**
     * Creates a window for the grid.
     * @param aListBox The grid used.
     * @param aCbaResource The softkeys used.
     * @param aType The layout used
     */
    IMPORT_C static CAknGMSPopupGrid* NewL(CEikListBox* aListBox, TInt aCbaResource, AknPopupLayouts::TAknPopupLayouts aType=AknPopupLayouts::EMenuWindow);
public:
    /**
     * Setup the whole window layout; window position, grid and heading position, shadow for the window.
     * @param aLayoutId A choice of layout -- not used by the implementation.
     */
    IMPORT_C void SetupWindowLayout(AknPopupLayouts::TAknPopupLayouts);
    /**
     * Calculate grid window position
     */
    IMPORT_C static void CalcPopupGridLargeGraphicWindow(TAknPopupWindowLayoutDef &aDef, TRect aClientRect, TInt aNumberOfLinesInListBox);
    /**
     * Calculate grid and heading position
     */
    IMPORT_C static void SetupPopupGridLargeGraphicWindow(TAknPopupWindowLayoutDef &aDef, 
				     TInt aNumberOfLinesInListBox, 
				     TBool aHeading);
    /**
     * Setup shadow for the window.
     */
    IMPORT_C static void PopupGridLargeGraphicGraphics(TAknPopupWindowLayoutDef &aDef);

    };

#endif // __CAknGMSStyleGrid_h
