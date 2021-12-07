/*
* ============================================================================
*  Name     : AknLists.h
*  Part of  : Avkon
*
*  Description:
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef __AKNLISTS_H__
#define __AKNLISTS_H__

#include <eikclb.h>
#include <eikfrlb.h>
#include <eikslb.h>
#include <AknGrid.h>
#include <aknutils.h>

#include <aknpanic.h>


class TAknTextLineLayout;


/** THIS FILE INCLUDES:
 *  1) All listbox layouts specified in Avkon LAF specification
 *      a) General list pane descendants
 *      b) Pop up window list pane descendants
 *      c) Grid panes
 *  2) Utilities that help building listbox layouts based on LAF specification
 *  3) Other helper classes that handle listbox behavior
 */


//
//
// Helper template definitions.
// (these are before concrete listbox classes because they're needed for inheritance)
//


/**
 * This adds correct horizontal and vertival lines to the listbox and handles empty listbox!
 *
 * This class is only useful if you're writing your own list layout. 
 * Please use the predefined layouts instead, for example CAknSingleStyleListBox.
 */
template<class T>
class AknListBoxLinesTemplate : public T
    {
public:
    /** AknListBoxLinesTemplate
     *
     * Read AVKON_LISTBOX_LINES resources. 
     *
     * The following predefined lines are available:
     * R_LIST_PANE_LINES_A_COLUMN
     * R_LIST_PANE_LINES_AB_COLUMN
     * R_LIST_PANE_LINES_AB_COLUMN_X
     * R_LIST_PANE_LINES_AB_COLUMN_XX
     * R_LIST_PANE_LINES_BC_COLUMN
     * R_LIST_PANE_LINES_BC_COLUMN_X
     * R_LIST_PANE_LINES_BC_COLUMN_XX
     * 
     */
    IMPORT_C AknListBoxLinesTemplate(TInt aResourceId);
    /** SizeChanged()
     * 
     * Determines position of the lines
     */
    IMPORT_C void SizeChanged();
    /** Draw()
     * 
     * Draws the lines
     */
    IMPORT_C void Draw(const TRect& aRect) const;
    /** CountComponentControls()
     * 
     * Choose controls to use as child controls
     */
    IMPORT_C TInt CountComponentControls() const;
    /** CountComponentControls()
     * 
     * Choose controls to use as child controls
     */
    IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;

private:
    TInt iResourceId;
    TAknLayoutRect iVertLine1, iVertLine2;
    TAknLayoutRect iHoriLine;
    TBool iResized;
    };

/**
 * Empty layout for popup lists
 */

template<class T>
class AknPopupListEmpty : public T
    {
   /**
    * Draws empty list when needed. See AknDraw::DrawEmptyList().
    */
    IMPORT_C void Draw(const TRect &aRect) const;
    };


/** 
 * Avkon version of eikon's column listbox.
 *
 * Check also:
 *   CAknSelectionListDialog (aknselectionlist.h)
 *   CAknMarkableListDialog  (aknselectionlist.h)
 *   CEikFormattedCellListBox (eikfrlb.h) 
 *
 * Content for list items are tab-separated strings.
 *
 * See methods 
 *   CEikListBox::ConstructFromResourceL()
 *   CEikListBox::ConstructL()
 *   CEikTextListBox::SetItemArray()
 *   CEikColumnListBoxData::SetIconArray()
 * 
 * Related flags for ConstructL() (avkon.hrh)
 *   EAknListBoxSelectionList
 *   EAknListBoxMenuList
 *   EAknListBoxMarkableList
 *   EAknListBoxMultiselectionList
 *   EAknListBoxViewerFlags
 *
 * Related flags for dialogs (avkon.hrh)
 *   EAknDialogSelectionList
 *   EAknDialogMenuList
 *   EAknDialogMultiselectionList
 *
 */
class CAknColumnListBox : public CEikColumnListBox
    {
public:
    /** Creates CAknColumnListBoxView.
     */
    IMPORT_C virtual CListBoxView* MakeViewClassInstanceL();
    /** Creates CAknFilteredTextListBoxModel
     */
    IMPORT_C virtual void CreateModelL();

    /** Listbox rectangle calculation.
     */
    IMPORT_C virtual TInt AdjustRectHeightToWholeNumberOfItems(TRect& aRect) const;
private: // listbox use only
	IMPORT_C virtual void CEikListBox_Reserved(); 
    };


//
// These defines define what features are needed --> you can remove shortcuts from ALL lists by changing these..
// Templates available: AknListBoxLinesTemplate<> AknListBoxShortCutTemplate<>
typedef AknListBoxLinesTemplate<CAknColumnListBox > CEikColumnListBoxTypedef;
typedef AknListBoxLinesTemplate<CEikFormattedCellListBox > CEikFormattedCellListBoxTypedef;
typedef AknListBoxLinesTemplate<CEikSettingsListBox > CEikSettingsListBoxTypedef;
typedef CAknGrid CAknSelectionGridTypedef;

// Templates available: AknListBoxShortCutTemplate<> AknListBoxLinesTemplate<>
#define AKNCOLUMNLISTBOXNAME(x) AknListBoxLinesTemplate<CAknColumnListBox >(x)
#define AKNDOUBLELISTBOXNAME(x) AknListBoxLinesTemplate<CEikFormattedCellListBox >(x)
#define AKNSETTINGLISTBOXNAME(x) AknListBoxLinesTemplate<CEikSettingsListBox >(x)

// Templates available: AknListBoxLinesTemplate<>, AknListBoxShortCutTemplate<>
#define AKNCOLUMNLISTBOX AknListBoxLinesTemplate<CAknColumnListBox >
#define AKNFORMATTEDLISTBOX AknListBoxLinesTemplate<CEikFormattedCellListBox >
#define AKNSETTINGSLISTBOX AknListBoxLinesTemplate<CEikSettingsListBox >
#define AKNGRID CAknGrid







//
//
// Derived listboxes (Use these in applications!)
// These are only for full screen lists -- the Rect() of the list must be ClientRect()
//
//


/**
 * list_single_pane
 *
 * list item string format: "\tTextLabel\t0\t1"
 * where 0 and 1 are indexes to icon array
 */

class CAknSingleStyleListBox : public CEikColumnListBoxTypedef
    {
public:
    IMPORT_C CAknSingleStyleListBox();
    /** SizeChanged()
     * 
     * Determines layout of the listbox
     */
    IMPORT_C void SizeChanged();
    /** MinimumSize()
     * 
     * Determines size of the listbox for use in dialogs.
     */
    IMPORT_C TSize MinimumSize();
    };

/**
 * list_single_number_pane
 *
 * list item string format: "2\tTextLabel\t0\t1"
 * where 0 and 1 are indexes to icon array
 */

class CAknSingleNumberStyleListBox : public CEikColumnListBoxTypedef
    {
public:
    IMPORT_C CAknSingleNumberStyleListBox();
    /** SizeChanged()
     * 
     * Determines layout of the listbox
     */
    IMPORT_C void SizeChanged();
    /** MinimumSize()
     * 
     * Determines size of the listbox for use in dialogs.
     */
    IMPORT_C TSize MinimumSize();
    };

/**
 * list_single_heading_pane
 *
 * list item string format: "Heading\tTextLabel\t0\t1"
 * where 0 and 1 are indexes to icon array
 *
 */

class CAknSingleHeadingStyleListBox : public CEikColumnListBoxTypedef
    {
public:
    IMPORT_C CAknSingleHeadingStyleListBox();
    /** SizeChanged()
     * 
     * Determines layout of the listbox
     */
    IMPORT_C void SizeChanged();
    /** MinimumSize()
     * 
     * Determines size of the listbox for use in dialogs.
     */
    IMPORT_C TSize MinimumSize();

protected:
    /** CreateItemDrawerL()
     *
     * Chooses which itemdrawer to use.
     */
    IMPORT_C virtual void CreateItemDrawerL();
    
   /** MakeViewClassInstanceL()
    *
    * Chooses which listbox view class to use
    */
    IMPORT_C virtual CListBoxView* MakeViewClassInstanceL();
    };


/**
 * list_single_graphic_pane
 *
 * list item string format: "0\tTextLabel\t1\t2"
 * where 0,1,2 are index to the icon array 
 */

class CAknSingleGraphicStyleListBox : public CEikColumnListBoxTypedef
    {
public: 
    IMPORT_C CAknSingleGraphicStyleListBox();
    /** SizeChanged()
     * 
     * Determines layout of the listbox
     */
    IMPORT_C void SizeChanged();
    /** MinimumSize()
     * 
     * Determines size of the listbox for use in dialogs.
     */
    IMPORT_C TSize MinimumSize();
    };

/**
 * list_single_Graphic_heading_pane
 *
 * list item string format: "0\tHeading\tTextLabel\t1\t2"
 * where 0,1,2 are index to the icon array 
 */

class CAknSingleGraphicHeadingStyleListBox : public CEikColumnListBoxTypedef
    {
public:
    IMPORT_C CAknSingleGraphicHeadingStyleListBox();
    /** SizeChanged()
     * 
     * Determines layout of the listbox
     */
    IMPORT_C void SizeChanged();
    /** MinimumSize()
     * 
     * Determines size of the listbox for use in dialogs.
     */
    IMPORT_C TSize MinimumSize();

protected:
    IMPORT_C virtual void CreateItemDrawerL();
   /** MakeViewClassInstanceL()
    *
    * Chooses which listbox view class to use
    */
    IMPORT_C virtual CListBoxView* MakeViewClassInstanceL();
    };

/**
 * list_single_number_heading_pane
 *
 * list item string format: "1\tHeading\tTextLabel\t2\t3"
 * where 2 and 3 are indexes to icon array
 */

class CAknSingleNumberHeadingStyleListBox : public CEikColumnListBoxTypedef
    {
public:
    IMPORT_C CAknSingleNumberHeadingStyleListBox();
    /** SizeChanged()
     * 
     * Determines layout of the listbox
     */
    IMPORT_C void SizeChanged();
    /** MinimumSize()
     * 
     * Determines size of the listbox for use in dialogs.
     */
    IMPORT_C TSize MinimumSize();

protected:
    IMPORT_C virtual void CreateItemDrawerL();
   /** MakeViewClassInstanceL()
    *
    * Chooses which listbox view class to use
    */
    IMPORT_C virtual CListBoxView* MakeViewClassInstanceL();
    };

/**
 * list_single_large_pane
 *
 * list item string format: "1\tTextLabel\t0"
 * where 0 is an index to icon array
 */

class CAknSingleLargeStyleListBox : public CEikColumnListBoxTypedef
    {
public:
    IMPORT_C CAknSingleLargeStyleListBox();
    /** SizeChanged()
     * 
     * Determines layout of the listbox
     */
    IMPORT_C void SizeChanged();
    /** MinimumSize()
     * 
     * Determines size of the listbox for use in dialogs.
     */
    IMPORT_C TSize MinimumSize();
    };

/**
 * list_double_pane and list_big_single_pane
 *
 * list item string format: " \tFirstLabel\tSecondLabel\t0"
 * where 0 is an index to icon array
 */

class CAknDoubleStyleListBox : public CEikFormattedCellListBoxTypedef
    {
public:
    IMPORT_C CAknDoubleStyleListBox();
    /** SizeChanged()
     * 
     * Determines layout of the listbox
     */
    IMPORT_C void SizeChanged();
    /** MinimumSize()
     * 
     * Determines size of the listbox for use in dialogs.
     */
    IMPORT_C TSize MinimumSize();
    };

/**
 * list_twoline_pane
 *
 * list item string format: " \tFirstLongLabel\t\t0"
 * where 0 is an index to icon array
 */

class CAknDoubleStyle2ListBox : public CAknDoubleStyleListBox
    {
public:
    /** SizeChanged()
     * 
     * Determines layout of the listbox
     */
    IMPORT_C void SizeChanged();
    /** CreateItemDrawerL()
     *
     * Chooses which itemdrawer to use.
     */
    IMPORT_C void CreateItemDrawerL();
    };

 /**
 * list_double_number_pane and list_big_single_number_pane
 *
 * list item string format: "1\tFirstLabel\t\t0"
 * list item string format: "1\tFirstLabel\tSecondLabel\t0"
 * where 0 is an index to icon array
 *
 */

class CAknDoubleNumberStyleListBox : public CEikFormattedCellListBoxTypedef
    {
public:
    IMPORT_C CAknDoubleNumberStyleListBox();
    /** SizeChanged()
     * 
     * Determines layout of the listbox
     */
    IMPORT_C void SizeChanged();
    /** MinimumSize()
     * 
     * Determines size of the listbox for use in dialogs.
     */
    IMPORT_C TSize MinimumSize();
    };

/**
 * list_double_time_pane
 */

class CAknDoubleTimeStyleListBox : public CEikFormattedCellListBoxTypedef
    {
public:
    IMPORT_C CAknDoubleTimeStyleListBox();
    /** SizeChanged()
     * 
     * Determines layout of the listbox
     */
    IMPORT_C void SizeChanged();
    /** MinimumSize()
     * 
     * Determines size of the listbox for use in dialogs.
     */
    IMPORT_C TSize MinimumSize();
    };

/**
 * list_double_large_pane
 *
 * list item string format: "1\tFirstLabel\tSecondLabel\t0"
 *
 * where 0 is an index of small (13x13) icon in icon array
 *   and 1 is an index of a thumbnail image
 *
 * Good thumbnail image sizes for this list are:
 *   30x40, 36x44, 40x30, 40x48, 44x36.
 */

class CAknDoubleLargeStyleListBox : public CEikFormattedCellListBoxTypedef
    {
public:
    IMPORT_C CAknDoubleLargeStyleListBox();
    /** SizeChanged()
     * 
     * Determines layout of the listbox
     */
    IMPORT_C void SizeChanged();
    /** MinimumSize()
     * 
     * Determines size of the listbox for use in dialogs.
     */
    IMPORT_C TSize MinimumSize();
    /** CreateItemDrawerL()
     *
     * Chooses which itemdrawer to use.
     */
    IMPORT_C virtual void CreateItemDrawerL();
    };


/**
 * list_double_graphic_pane
 *
 * list item string format: "0\tFirstLabel\tSecondLabel\t0"
 * where 0 is index to icon array
 *
 */

class CAknDoubleGraphicStyleListBox : public CEikFormattedCellListBoxTypedef
    {
public:
    IMPORT_C CAknDoubleGraphicStyleListBox();
    /** SizeChanged()
     * 
     * Determines layout of the listbox
     */
    IMPORT_C void SizeChanged();
    /** MinimumSize()
     * 
     * Determines size of the listbox for use in dialogs.
     */
    IMPORT_C TSize MinimumSize();
    };

/**
 * list_double2_graphic_pane
 *
 * list item string format: "1\tFirstLabel\tSecondLabel\t0"
 * where 0 is an index to icon array
 *
 */

class CAknFormDoubleGraphicStyleListBox : public CAknDoubleGraphicStyleListBox
    {
public:
    /** SizeChanged()
     * 
     * Determines layout of the listbox
     */
    IMPORT_C void SizeChanged();
    };
typedef CAknFormDoubleGraphicStyleListBox CAknSingleBigHeadingGraphicListBox;

/**
 * list_double2_pane
 *
 * list item string format: " \tFirstLabel\tSecondLabel\t0"
 * where 0 is an index to icon array
 */

class CAknFormDoubleStyleListBox : public CAknDoubleStyleListBox
    {
public:
    /** SizeChanged()
     * 
     * Determines layout of the listbox
     */
    IMPORT_C void SizeChanged();
    };
typedef CAknFormDoubleStyleListBox CAknSingleBigHeadingListBox;


/**
 * list_setting_pane and list_big_single_setting_pane
 *
 * list item string format: "\tFirstLabel\t\tValueText"
 * list item string format: "\tFirstLabel\t0\t"
 * list item string format: "\tFirstLabel\t\tValueText\t*"
 * list item string format: "\tFirstLabel\t\t\t\tSecondLabel"
 * where 0 is an index to icon array
 */

class CAknSettingStyleListBox : public CEikSettingsListBoxTypedef
    {
public:
    IMPORT_C CAknSettingStyleListBox();
    /** SizeChanged()
     * 
     * Determines layout of the listbox
     */
    IMPORT_C void SizeChanged();
    /** MinimumSize()
     * 
     * Determines size of the listbox for use in dialogs.
     */
    IMPORT_C TSize MinimumSize();
    };

/**
 * list_setting_number_pane and list_big_single_setting_number_pane
 *
 * list item string format: "1\tFirstLabel\t\tValueText"
 * list item string format: "2\tFirstLabel\t0\t"
 * list item string format: "3\tFirstLabel\t\tValueText\t*"
 * list item string format: "4\tFirstLabel\t\t\t\tSecondLabel"
 * where 0 is an index to icon array
 * and 1..4 is list item number shown on screen
 */
class CAknSettingNumberStyleListBox : public CEikSettingsListBoxTypedef
    {
public:
    IMPORT_C CAknSettingNumberStyleListBox();
    /** SizeChanged()
     * 
     * Determines layout of the listbox
     */
    IMPORT_C void SizeChanged();
    /** MinimumSize()
     * 
     * Determines size of the listbox for use in dialogs.
     */
    IMPORT_C TSize MinimumSize();
    };


//
// Use the popup styles with CAknPopupList and CAknListQueryDialog
//

/**
 * list_single_popup_menu_pane
 *
 * list item string format: "FirstLabel\t0"
 *
 * where 0 is an index to icon array
 */

class CAknSinglePopupMenuStyleListBox : public AknPopupListEmpty<CEikFormattedCellListBox>
    {
public:
    /** SizeChanged()
     * 
     * Determines layout of the listbox
     */
    IMPORT_C void SizeChanged();
    /** MinimumSize()
     * 
     * Determines size of the listbox for use in dialogs.
     */
    IMPORT_C TSize MinimumSize();
    protected:
    /** CreateItemDrawerL()
     *
     * Chooses which itemdrawer to use.
     */
    IMPORT_C virtual void CreateItemDrawerL();
    };

/**
 * list_single_graphic_popup_menu_pane
 *
 * list item string format: "0\tLabel"
 *
 * where 0 is an index to icon array
 */

class CAknSingleGraphicPopupMenuStyleListBox : public AknPopupListEmpty<CEikFormattedCellListBox>
    {
public:
    /** SizeChanged()
     * 
     * Determines layout of the listbox
     */
    IMPORT_C void SizeChanged();
    /** MinimumSize()
     * 
     * Determines size of the listbox for use in dialogs.
     */
    IMPORT_C TSize MinimumSize();
    protected:
    /** CreateItemDrawerL()
     *
     * Chooses which itemdrawer to use.
     */
    IMPORT_C virtual void CreateItemDrawerL();
    };

/**
 * list_single_graphic_bt_popup_menu_pane
 *
 * list item string format: "0\tLabel"
 *
 * where 0 is an index to icon array
 *
 */

class CAknSingleGraphicBtPopupMenuStyleListBox : public CAknSingleGraphicPopupMenuStyleListBox
    {
public:
    /** SizeChanged()
     * 
     * Determines layout of the listbox
     */
    IMPORT_C void SizeChanged();
    };

/**
 * list_single_heading_popup_menu_pane
 *
 * list item string format: "Heading\tLabel"
 *
 */

class CAknSingleHeadingPopupMenuStyleListBox : public AknPopupListEmpty<CEikFormattedCellListBox>
    {
public:
    IMPORT_C CAknSingleHeadingPopupMenuStyleListBox();
    /** SizeChanged()
     * 
     * Determines layout of the listbox
     */
    IMPORT_C void SizeChanged();
    /** MinimumSize()
     * 
     * Determines size of the listbox for use in dialogs.
     */
    IMPORT_C TSize MinimumSize();
protected:
    /** CreateItemDrawerL()
     *
     * Chooses which itemdrawer to use.
     */
    IMPORT_C virtual void CreateItemDrawerL();
    };


/**
 * list_single_graphic_heading_popup_menu_pane
 *
 * list item string format: "0\tHeading\tLabel"
 *
 * where 0 is an index to icon array
 *
 */

class CAknSingleGraphicHeadingPopupMenuStyleListBox : public AknPopupListEmpty<CEikFormattedCellListBox>

    {
public:
    IMPORT_C CAknSingleGraphicHeadingPopupMenuStyleListBox();
    /** SizeChanged()
     * 
     * Determines layout of the listbox
     */
    IMPORT_C void SizeChanged();
    /** MinimumSize()
     * 
     * Determines size of the listbox for use in dialogs.
     */
    IMPORT_C TSize MinimumSize();
protected:
    /** CreateItemDrawerL()
     *
     * Chooses which itemdrawer to use.
     */
    IMPORT_C virtual void CreateItemDrawerL();
    };

/**
 * list_double_popup_menu_pane
 *
 * list item string format: "FirstLabel\tSecondLabel"
 *
 */

class CAknDoublePopupMenuStyleListBox : public AknPopupListEmpty<CEikFormattedCellListBox>
    {
public:
    /** SizeChanged()
     * 
     * Determines layout of the listbox
     */
    IMPORT_C void SizeChanged();
    /** MinimumSize()
     * 
     * Determines size of the listbox for use in dialogs.
     */
    IMPORT_C TSize MinimumSize();
protected:
    /** CreateItemDrawerL()
     *
     * Chooses which itemdrawer to use.
     */
    IMPORT_C virtual void CreateItemDrawerL();
    };

/**
 * list_single_popup_submenu_pane
 *
 * DO NOT USE
 *
 */

class CAknSinglePopupSubmenuStyleListBox : public AknPopupListEmpty<CEikFormattedCellListBox>
    {
public:
    /** SizeChanged()
     * 
     * Determines layout of the listbox
     */
    IMPORT_C void SizeChanged();
    /** MinimumSize()
     * 
     * Determines size of the listbox for use in dialogs.
     */
    IMPORT_C TSize MinimumSize();
    };


/**
 * list_double_large_graphic_popup_menu_pane
 *
 * list item string format: "0\tFirstLabel\tSecondLabel"
 *
 * where 0 is an index to icon array
 *
 */

class CAknDoubleLargeGraphicPopupMenuStyleListBox : public AknPopupListEmpty<CEikFormattedCellListBox>
    {
public:
    /** SizeChanged()
     * 
     * Determines layout of the listbox
     */
    IMPORT_C void SizeChanged();
    /** MinimumSize()
     * 
     * Determines size of the listbox for use in dialogs.
     */
    IMPORT_C TSize MinimumSize();
protected:
    /** CreateItemDrawerL()
     *
     * Chooses which itemdrawer to use.
     */
    IMPORT_C virtual void CreateItemDrawerL();
    };
// --- end of popup styles



/** list_set_pane
 * Setting Page component uses this
 *
 * list item string format: "1\tShortLabel"
 * list item string format: "\t\tLongLabel"
 *
 */
class CAknSetStyleListBox : public AknPopupListEmpty<CEikFormattedCellListBox>
    {
public:
    IMPORT_C void ConstructWithWindowL(const CCoeControl *aParent, TInt aFlags);
    /** SizeChanged()
     * 
     * Determines layout of the listbox
     */
    IMPORT_C void SizeChanged();
    /** MinimumSize()
     * 
     * Determines size of the listbox for use in dialogs.
     */
    IMPORT_C TSize MinimumSize();
    IMPORT_C void Draw(const TRect& aRect) const;
protected:
    /** CreateItemDrawerL()
     *
     * Chooses which itemdrawer to use.
     */
    IMPORT_C virtual void CreateItemDrawerL();
   /** MakeViewClassInstanceL()
    *
    * Chooses which listbox view class to use
    */
    IMPORT_C CListBoxView *MakeViewClassInstanceL();
    };

/** list_form_graphic_pane
 * Form popup field should use this
 *
 * list item string format: "1\tShortLabel"
 * list item string format: "\t\tLongLabel"
 *
 */
class CAknFormGraphicStyleListBox : public AknPopupListEmpty<CEikFormattedCellListBox>
    {
public:
    IMPORT_C void ConstructWithWindowL(const CCoeControl *aParent, TInt aFlags);
    /** SizeChanged()
     * 
     * Determines layout of the listbox
     */
    IMPORT_C void SizeChanged();
    /** MinimumSize()
     * 
     * Determines size of the grid for use in dialogs.
     */
    IMPORT_C TSize MinimumSize();
    /** CreateItemDrawerL()
     *
     * Chooses which itemdrawer to use.
     */
    IMPORT_C virtual void CreateItemDrawerL();
    /** Listbox rectangle calculation.
     */
    IMPORT_C virtual TInt AdjustRectHeightToWholeNumberOfItems(TRect &aRect) const;
	};

class CAknFormGraphicWideStyleListBox : public CAknFormGraphicStyleListBox
    {
public:
    IMPORT_C void SizeChanged();
    IMPORT_C TSize MinimumSize();
    };


/** grid_app_pane
 * Application shell uses this (note that part of layout needs to be done
 * inside application -- the listbox will not be in correct position on the
 * screen by just using this -- see listapp)
 *
 * list item string format: "1\tLabel"
 * list item string format: "1\tLabel\t1"
 */

/**
 * grid_pinb_pane
 *
 * list item string format: "1"
 * list item string format: "1\t1"
 * list item string format: "1\t1\t1"
 * list item string format: "1\t\t1"
 */

class CAknPinbStyleGrid : public CAknSelectionGridTypedef
    {
public:
    /** SizeChanged()
     * 
     * Determines layout of the grid
     */
    IMPORT_C void SizeChanged();
    /** MinimumSize()
     * 
     * Determines size of the grid for use in dialogs.
     */
    IMPORT_C TSize MinimumSize();
    };


/**
 * grid_qdial_pane
 */

class CAknQdialStyleGrid : public CAknSelectionGridTypedef
    {
public:
    /** SizeChanged()
     * 
     * Determines layout of the grid
     */
    IMPORT_C void SizeChanged();
    /** MinimumSize()
     * 
     * Determines size of the grid for use in dialogs.
     */
    IMPORT_C TSize MinimumSize();
    };

/**
 * grid_cale_month_pane
 */

class CAknCaleMonthStyleGrid : public CAknSelectionGridTypedef
    {
public:
    /** SizeChanged()
     * 
     * Determines layout of the listbox
     */
    IMPORT_C void SizeChanged();
    /** MinimumSize()
     * 
     * Determines size of the grid for use in dialogs.
     */
    IMPORT_C TSize MinimumSize();
    };



//
//
// Here we have itemdrawer/view modifications needed by the lists
//
//

// This class is to keep drawing routines that depend on avkon and which we cannot place to
// eikstd or uikon because of that.

/**
 * A view that provides
 *   * empty lists for use with find pane
 */

class CAknColumnListBoxView : public CColumnListBoxView
    {
public:
    IMPORT_C void EnableFindEmptyList();
    IMPORT_C void SetFindEmptyListState(TBool aUsedWithFind);
    IMPORT_C void DrawEmptyList(const TRect &aClientRect) const;
    IMPORT_C virtual void CalcBottomItemIndex();
private: // overridden from CListBoxView
	IMPORT_C virtual TAny* Reserved_1();
private:
    TBool iEmptyListWithFind;
    };

/**
 * empty list for settings item editing
 */

class CAknSetStyleListBoxView : public CFormattedCellListBoxView
    {
public:
    IMPORT_C void DrawEmptyList(const TRect &aClientRect) const ;
private: // overridden from CListBoxView
	IMPORT_C virtual TAny* Reserved_1();
    };


/**
 * Horizontal lines and empty list support for views
 */

class CSingleHeadingStyleView : public CAknColumnListBoxView
    {
public:
    IMPORT_C void Draw(const TRect* ) const;
    IMPORT_C void DrawEmptyList(const TRect& aClientRect) const;
private: // overridden from CListBoxView
	IMPORT_C virtual TAny* Reserved_1();
    };

/**
 * Horizontal lines support for item drawer.
 */
class CSingleHeadingStyleItemDrawer : public CColumnListBoxItemDrawer 
    {
public:
    IMPORT_C CSingleHeadingStyleItemDrawer(MTextListBoxModel* aTextListBoxModel, const CFont* aFont, CColumnListBoxData* aColumnData);
    IMPORT_C ~CSingleHeadingStyleItemDrawer();

    IMPORT_C virtual void DrawItem(TInt aItemIndex, TPoint aItemRectPos, TBool aItemIsSelected, TBool aItemIsCurrent, TBool aViewIsEmphasized, TBool aViewIsDimmed) const;

public:
    IMPORT_C void SetTopItemIndex(TInt aTop);

private:
    TInt iTopItemIndex;
	CCoeEnv* iCoeEnv;
    };

/**
 * Thumbnail image positioning for double large styles.
 */
class CDoubleLargeStyleItemDrawer : public CFormattedCellListBoxItemDrawer
    {
public:
    IMPORT_C CDoubleLargeStyleItemDrawer(MTextListBoxModel* aTextListBoxModel, const CFont* aFont, CFormattedCellListBoxData* aFormattedCellData, CEikListBox *aListBox);
    IMPORT_C void DrawItem(TInt aItemIndex, TPoint aItemRectPos, TBool aItemIsSelected, TBool aItemIsCurrent, TBool aViewIsEmphasized, TBool aViewIsDimmed) const;
private:
	IMPORT_C void CFormattedCellListBoxItemDrawer_Reserved();
private:
    CEikListBox *iListBox_tmp;
    };


/**
 * Word wrapping for double2 styles
 */
class CWordWrappedFormattedCellItemDrawer : public CFormattedCellListBoxItemDrawer
    {
public:
    IMPORT_C CWordWrappedFormattedCellItemDrawer(MTextListBoxModel* aTextListBoxModel, const CFont* aFont, CFormattedCellListBoxData* aFormattedCellData, CEikListBox *aListBox, TInt aSubCell, TInt aSubCell2);
    IMPORT_C void DrawItemText(TInt aItemIndex,
			       const TRect &aItemTextRect,
			       TBool aItemIsCurrent,
			       TBool,
			       TBool aItemIsSelected) const;
private:
	IMPORT_C void CFormattedCellListBoxItemDrawer_Reserved();
private:
    TInt iSubCell, iSubCell2;
    };

//
//
//  here starts section for building new listboxes.
//

//
// This is helper class that makes the conversion between European LAF and
// different listbox itemdrawer implementations.
//
// Notice, this CEikListBox is a good friend with this class.
//
// 

/** AknListBoxLayouts
 * Building listbox layouts from European Avkon LAF.
 *
 * The LAF specification has 3 kinds of tables:
 *   Graphics tables
 *   Text tables
 *   Pane coordinates
 * The graphics tables map to SetupColumnGfxCell() and SetupFormGfxCell()
 * The text tables map to SetupColumnTextCell() and SetupFormGfxCell()
 * The pane coordinates map to SetupListboxPos().
 *
 * This class is mostly useless if you dont have LAF specification available!
 *
 * You probably want to use predefined layouts; See CAknSingleStyleListBox.
 *
 * NOTE: This class is old design. You should consider looking at aknutils.h: AknLayoutUtils
 *       whenever you want to build things from the LAF specification. 
 */

class AknListBoxLayouts
    {
public:
    /**
     * Setup borders etc.
     */
    IMPORT_C static void SetupStandardListBox(CEikListBox& aListBox);
    /**
     * Setup grid position
     */
    IMPORT_C static void SetupGridPos(CAknGrid& aGrid,
    			     TInt l, 
    			     TInt t, 
    			     TInt /*r*/, 
    			     TInt /*b*/, 
    			     TInt W, 
    			     TInt H);
    /**
     * Setup list position
     */
    IMPORT_C static void SetupListboxPos(CEikListBox& aListBox,
				TInt /*startx*/, 
    				TInt starty, 
    				TInt,
    				TInt, 
    				TInt /*width*/, 
    				TInt height);
    /**
     * Setup text foreground and background colours to default
     */
    IMPORT_C static void SetupStandardColumnListbox(CColumnListBoxItemDrawer* aItemDrawer);	
    /**
     * Setup text foreground and background colours to default
     */
    IMPORT_C static void SetupStandardFormListbox(CFormattedCellListBoxItemDrawer* aItemDrawer);
    /**
     * Setup text foreground and background colours to default
     */
    IMPORT_C static void SetupStandardGrid(CAknGrid& aGrid);
    
    /**
     * Setup a single graphics cell of list item
     */
    IMPORT_C static void SetupColumnGfxCell(CEikListBox& aListBox, 
				   CColumnListBoxItemDrawer* aItemDrawer, 
				   TInt index,
				   TInt l, 
				   TInt t, 
				   TInt r, 
				   TInt b, 
				   TInt W, 
				   TInt H, 
				   TInt startx, 
				   TInt endx);
    
    /**
     * Setup a single text cell of list item
     */
    IMPORT_C static void SetupColumnTextCell(CEikListBox& aListBox, 
				    CColumnListBoxItemDrawer* aItemDrawer, 
				    TInt index,
				    const CFont *font, 
				    TInt /*C*/, 
				    TInt lm, 
				    TInt rm, 
				    TInt B, 
				    TInt /*W*/, 
				    CGraphicsContext::TTextAlign aAlign, 
				    TInt startx, 
				    TInt endx);
    /**
     * Setup a single text cell of list item
     */
    IMPORT_C static void SetupColumnTextCell(CEikListBox& aListBox, 
				    CColumnListBoxItemDrawer* aItemDrawer, 
				    TInt index,
				    const TAknTextLineLayout &aLayout,
				    TInt startx, 
				    TInt endx); // use with aknlayoutcompiler

    /**
     * Setup a single graphics cell of list item
     */
    IMPORT_C static void SetupFormGfxCell(CEikListBox& aListBox, 
				 CFormattedCellListBoxItemDrawer* aItemDrawer, 
				 TInt index,
				 TInt l, 
				 TInt t, 
				 TInt /*r*/, 
				 TInt /*b*/, 
				 TInt W, 
				 TInt H, 
				 TPoint p1, 
				 TPoint p2);


    /**
     * Setup a single graphics cell of list item
     *
     * This version is needed for grid cells. (the FormGfxCell works in
     * most cases, but this is needed if you want exact positioning of
     * the erased area..)
     */
    IMPORT_C static void SetupGridFormGfxCell(CAknGrid& aListBox, 
				 CFormattedCellListBoxItemDrawer* aItemDrawer, 
				 TInt index,
				 TInt l, 
				 TInt t, 
				 TInt /*r*/, 
				 TInt /*b*/, 
				 TInt W, 
				 TInt H, 
				 TPoint p1, 
				 TPoint p2);

    /**
     * Setup a single text cell of list item
     */    
    IMPORT_C static void SetupFormTextCell(CEikListBox& aListBox, 
				  CFormattedCellListBoxItemDrawer* aItemDrawer, 
				  TInt index,
				  const CFont *font, 
				  TInt /*C*/, 
				  TInt lm,
				  TInt /*rm*/, 
				  TInt B, 
				  TInt W, 
				  CGraphicsContext::TTextAlign aAlign, 
				  TPoint p1, 
				  TPoint p2);
    /**
     * Setup a single text cell of list item
     *
     * This is for removing flicker for settings
     *
     */
    IMPORT_C static void SetupFormAntiFlickerTextCell(CEikListBox& aListBox, 
				  CFormattedCellListBoxItemDrawer* aItemDrawer, 
				  TInt index,
				  const CFont *font, 
				  TInt /*C*/, 
				  TInt lm,
				  TInt /*rm*/, 
				  TInt B, 
				  TInt W, 
				  CGraphicsContext::TTextAlign aAlign, 
				  TPoint p1, 
				  TPoint p2);

    /**
     * Setup a single text cell of list item
     */
    IMPORT_C static void SetupFormTextCell(CEikListBox& aListBox, 
				  CFormattedCellListBoxItemDrawer* aItemDrawer, 
				  TInt index,
				  const TAknTextLineLayout &aLayout,
				  const TPoint &p1, 
				  const TPoint &p2); // use with layout compiler
    /**
     * Setup a single text cell of list item
     *
     * This is for removing flicker for settings
     */
    IMPORT_C static void SetupFormAntiFlickerTextCell(CEikListBox& aListBox, 
				  CFormattedCellListBoxItemDrawer* aItemDrawer, 
				  TInt index,
				  const TAknTextLineLayout &aLayout,
				  const TPoint &p1, 
				  const TPoint &p2); // use with layout compiler

    
    };




/** This one reads listbox layout from resource file (DEPRECATED)

    (this cannot be removed from avkon because it is already
     used by some applications)

    Use it like this:
      CAknListBoxReader* iReader;

    Put the following to your listbox's ConstructL():
      iReader = new(ELeave) CAknListBoxReader;
      iReader->ConstructL(R_LIST_SINGLE_NUMBER_PANE);

    Then in SizeChanged():
      iReader->Apply(this, ItemDrawer());
    
    Then in destructor
      delete iReader;
*/
class CAknListBoxReader : public CAknGenericReader
    {
public:
    /** Deprecated
     */
    void Apply(CEikListBox* aListBox, CFormattedCellListBoxItemDrawer* aColumnItemDrawer);
    /** Deprecated
     */
    ~CAknListBoxReader();
    /** Deprecated
     */
    const SAknLayoutPos* Pos() const;

public: // From CAknGenericReader
    /** Deprecated
     */
    virtual void ConstructL(TInt aResourceId);

protected:
    /** Deprecated
     */
    void ApplyGeneric();

    SAknLayoutPos iPos;
    CEikListBox* iListBox; // no ownership of this
    CColumnListBoxItemDrawer* iColumnItemDrawer; // no ownership
    CFormattedCellListBoxItemDrawer* iFormItemDrawer; // no ownership
    };



/**
 * Handles Avkon style item addition and removal
 */
class AknListBoxUtils
    {
public:
    /**
     * Looks like listbox's HandleItemRemoval does nasty things to currentitemindex
     * and topitemindex. This works better for our purposes.
     */
    IMPORT_C static void HandleItemRemovalAndPositionHighlightL(CEikListBox *aListBox, TInt aValueOfCurrentItemIndexBeforeRemoval, TBool aCurrentItemWasRemoved);
    IMPORT_C static void HandleItemRemovalAndPositionHighlightL(CEikListBox *aListBox, TInt aValueOfCurrentItemIndexBeforeRemoval, CArrayFix<TInt> &aIndexesToRemovedItems);
    };



#endif






