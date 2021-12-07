/*
*	Name	:AknSelectionList.h
*	Part of	:Avkon
*
*    Version:
*
*  Copyright © 2002 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing,  adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
* ============================================================================
*/

#ifndef __AKNSELECTIONLIST_H__
#define __AKNSELECTIONLIST_H__


/* Dialogs for selection service implementation.
 *
 */

#include <aknform.h>
#include <aknview.h>
#include <aknutils.h>
#include <aknpopup.h>
#include <avkon.rsg>


/** CAknSelectionListDialog is the actual interface to the applications.
 *
 * Use this class to get a full screen list.
 *
 * This class only works in whole main pane. Do not try to use
 * this directly for other places. 
 *  
 * resource definition for this class:
 * RESOURCE DIALOG r_res_id_for_a_dialog
 *   {
 *   flags = EAknDialogSelectionList;
 *   buttons = R_AVKON_SOFTKEYS_OPTIONS_BACK;
 *   items =
 *	{
 *	DLG_LINE
 *	    {
 *	    type = EAknCtSingleGraphicListBox;
 *	    id = ESelectionListControl;
 *	    control = LISTBOX
 *		{
 *		flags = EAknListBoxSelectionList;
 *		};
 *	    }
 *     // the next dlg line is optional.
 *	,
 *	DLG_LINE
 *	    {
 * 	    itemflags = EEikDlgItemNonFocusing;
 *	    id = EFindControl;
 *	    type = EAknCtSelectionListFixedFind;
 *	    }
 *	};
 *   }
 *
 * The listbox type can be one of the following: (avkon.hrh and aknlists.h)
 *   EAknCtSingleListBox                (See CAknSingleStyleListBox)
 *   EAknCtSingleNumberListBox          (See CAknSingleNumberStyleListBox)
 *   EAknCtSingleHeadingListBox         (See CAknSingleHeadingStyleListBox)
 *   EAknCtSingleGraphicListBox         (See CAknSingleGraphicStyleListBox)
 *   EAknCtSingleGraphicHeadingListBox  (See CAknSingleGraphicHeadingStyleListBox)
 *   EAknCtSingleNumberHeadingListBox   (See CAknSingleNumberHeadingStyleListBox)
 *   EAknCtSingleLargeListBox           (See CAknSingleLargeStyleListBox)
 *   EAknCtDoubleListBox                (See CAknDoubleStyleListBox)
 *   EAknCtDoubleNumberListBox          (See CAknDoubleNumberStyleListBox)
 *   EAknCtDoubleTimeListBox            (See CAknDoubleTimeStyleListBox)
 *   EAknCtDoubleLargeListBox           (See CAknDoubleLargeStyleListBox)
 *   EAknCtDoubleGraphicListBox         (See CAknDoubleGraphicStyleListBox)
 *
 * The type field while defining find can be one of the following:
 *   EAknCtSelectionListFixedFind
 *   EAknCtSelectionListPopupFind
 *
 * The menubar you give for selection list dialog should have
 * one of the following as one of its menu panes: (avkon.hrh)
 *    R_AVKON_MENUPANE_SELECTION_LIST
 *    R_AVKON_MENUPANE_SELECTION_LIST_WITH_FIND_POPUP
 *
 * RESOURCE MENU_BAR r_res_id_for_a_menubar
 * {
 * titles =
 *     {
 *     MENU_TITLE { menu_pane = R_AVKON_MENUPANE_SELECTION_LIST; } 
 *     };
 * };
 *
 * C++ Usage:
 *    TInt openedItem = 0;
 *    MDesCArray *array = ...;
 *    CAknSelectionListDialog *dialog = CAknSelectionListDialog::NewL(openedItem, array, R_RES_ID_FOR_A_MENUBAR);
 *    TInt result = dialog->ExecuteLD(R_RES_ID_FOR_A_DIALOG);
 *    if (result) { ...use openeditem here... } else { ...canceled... }
 *
 * Alternatively, you can use:
 *    TInt openedItem = 0;
 *    MDesCArray *array = ...;
 *    CAknSelectionListDialog *dialog = CAknSelectionListDialog::NewL(openedItem, array, R_RES_ID_FOR_A_MENUBAR);
 *    dialog->PrepareLC(R_RES_ID_FOR_A_DIALOG);
 *    // do some operations here, for example fill icon array 
 *    TInt result = dialog->RunLD();
 *    if (result) { ... } else { ... }
 */
class CAknSelectionListDialog : public CAknDialog, public MEikListBoxObserver
    {

public: // operands for selection lists
    /** CAknSelectionListDialog::NewL()
     *
     * aOpenedItem   Variable to be modified when user selects a list item.
     * aArray        Content of list items; A tab-separated string with texts and indexes to icon array
     * aMenuBarResourceId Menu items to be shown in options menu
     * aCommand      Callback for state changes. EAknCmdOpen command is send by listbox. Options menu commands come here too.
     */
    IMPORT_C static CAknSelectionListDialog *NewL( TInt &aOpenedItem, MDesCArray *aArray, TInt aMenuBarResourceId, MEikCommandObserver *aCommand = 0 );
    IMPORT_C static CAknSelectionListDialog *NewLC( TInt &aOpenedItem, MDesCArray *aArray, TInt aMenuBarResourceId, MEikCommandObserver *aCommand = 0 );

public: // different options
    enum TFindType
	{
	ENoFind,
	EFixedFind,
	EPopupFind
	};
    /** SetupFind() provides a way to enable and disable find and find popup
     *  on runtime.
     * 
     * You still need entry with id EFindControl to resource file for the find, this is only for disabling
     * existing find element.
     */
    IMPORT_C void SetupFind(TFindType aType);

    /** Icons: IconArray(), SetIconArrayL()
     *
     * Icons, images and thumbnails are in this array.
     *
     * The list items are tab separated strings with fixed format. Some of the numbers
     * in the list item strings are indexes to this array.
     *
     * This array can be modified by MDesCArray::MdcaPoint() method or at construction of
     * dialog; after PrepareLC() call.
     */
    IMPORT_C CArrayPtr<CGulIcon>* IconArray() const;
    IMPORT_C void SetIconArrayL(CArrayPtr<CGulIcon>* aIcons);
protected:
    IMPORT_C CAknSelectionListDialog( TInt &aIndex, MDesCArray *aArray, MEikCommandObserver *aCommand );
    IMPORT_C ~CAknSelectionListDialog();
protected: // Customisation from derived classes
    /** SelectionListProcessCommandL() handles selection list and markable list
     *  default commands.
     *
     *  For markable lists, this method handles EAknCmdMark, EAknCmdUnmark, EAknMarkAll, EAknUnmarkAll
     *  defined in options menu pane R_AVKON_MENUPANE_MARKABLE_LIST.
     */
    IMPORT_C virtual void SelectionListProcessCommandL(TInt aCommand);

    /** IsAcceptableListType(): Detection of list and grid layouts
     *
     * The CAknSelectionList only works with certain list and grid
     * layouts.
     *
     * You will get Panic() if you use your own list/grid layouts and
     * you do not have this method implemented!
     *
     * If you add new list layouts, you should implement this method to
     * publish the type of the layout using this method. This is especially
     * the case where you use CAknSelectionGrid with your own grid layout.
     * (as there are no predefined grid layouts, you need to do this
     * every time you use a selection grid)
     *
     * The following aControlTypes are already implemented and requires
     * no action:
     * EAknCtSingleListBox
     * EAknCtSingleNumberListBox
     * EAknCtSingleHeadingListBox
     * EAknCtSingleGraphicListBox
     * EAknCtSingleGraphicHeadingListBox
     * EAknCtSingleNumberHeadingListBox
     * EAknCtSingleLargeListBox
     * EAknCtDoubleListBox
     * EAknCtDoubleNumberListBox
     * EAknCtDoubleTimeListBox
     * EAknCtDoubleLargeListBox
     * EAknCtDoubleGraphicListBox
     * EAknCtSettingListBox
     * EAknCtSettingNumberListBox
     *
     * Any other layout requires you to inherit from CAknSelectionList
     * and implement the following methods:
     * TBool IsAcceptableListBoxType(TInt aControlType, TBool &aIsFormattedCellList)
     * {
     *   if (aControlType == EMyCtGridLayout)
     *   {
     *      // CAknGrid is-a formattedcelllistbox.
     *      aIsFormattedCellList = ETrue;
     *      return ETrue;
     *   }
     *   else
     *      return EFalse;
     * }
     * 
     * See also CreateCustomControlL(). IsAcceptableListType() and CreateCustomControlL() forms a pair that should
     * be implemented together.
     */
    IMPORT_C virtual TBool IsAcceptableListBoxType(TInt aControlType, TBool &aIsFormattedCellList) const;
protected:
    IMPORT_C void ProcessCommandL( TInt aCommandId );
    IMPORT_C void PreLayoutDynInitL();
    IMPORT_C void PostLayoutDynInitL();
    IMPORT_C void SetSizeAndPosition(const TSize &aSize);
    IMPORT_C TBool OkToExitL( TInt aButtonId );
    IMPORT_C void HandleListBoxEventL( CEikListBox* aListBox, TListBoxEvent aEventType );
    IMPORT_C TInt CountComponentControls() const;
    IMPORT_C CCoeControl* ComponentControl( TInt aIndex ) const;
    IMPORT_C TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType );

    /** CreateCustomControlL() creates own list or grid layouts.
     *
     * Normal implementation of this method is:
     * SEikControlInfo CreateCustomControlL(TInt aControlType)
     * {
     *     CCoeControl *control = NULL;
     *     if (aControlType == EMyCtGridLayout)
     *     {
     *        // CMyOddStyleGrid should be derived from CAknFormattedCellListBox or CEikColumnListBox.
     *        control = new(ELeave)CMyOddStyleGrid;
     *     }
     *     SEikControlInfo info = {control,0,0};
     *     return info;
     * }
     * See also IsAcceptableListType(). CreateCustomControlL() and IsAcceptableListType() forms a pair that should
     * be implemented together.
     */
    IMPORT_C SEikControlInfo CreateCustomControlL(TInt aControlType);
protected:
    IMPORT_C virtual CEikListBox *ListBox() const;
    IMPORT_C CAknSearchField *FindBox() const;
    IMPORT_C TBool IsFormattedCellListBox() const;
    IMPORT_C void Draw(const TRect&) const;
private: 
	IMPORT_C virtual void CEikDialog_Reserved_1();
	IMPORT_C virtual void CEikDialog_Reserved_2();	
private: 
	IMPORT_C virtual void CAknDialog_Reserved();
private: // new function 
	IMPORT_C virtual void CAknSelectionListDialog_Reserved();
protected:
    TBool iEnterKeyPressed;
private:
    CAknSearchField *iFindBox;
    TFindType iFindType;
    TInt *iSelectedItem;
    MDesCArray *iArray;
    MEikCommandObserver *iCmdObserver;
    TInt iDialogResourceId;
	TInt iSpare;
    };

/** CAknMarkableListDialog is an interface for applications
 *
 * The class provides a list with items markable with shift+selection_key.
 *
 * resource definition for this class:
 * RESOURCE DIALOG r_res_id_for_a_dialog
 *   {
 *   flags = EAknDialogMarkableList;
 *   buttons = R_AVKON_SOFTKEYS_OPTIONS_BACK;
 *   items =
 *	{
 *	DLG_LINE
 *	    {
 *	    type = EAknCtSingleGraphicListBox;
 *	    id = ESelectionListControl;
 *	    control = LISTBOX
 *		{
 *		flags = EAknListBoxMarkableList;
 *		};
 *	    }
 *     // the next dlg line is optional.
 *	,
 *	DLG_LINE
 *	    {
 * 	    itemflags = EEikDlgItemNonFocusing;
 *	    id = EFindControl;
 *	    type = EAknCtSelectionListFixedFind;
 *	    }
 *	};
 *   }
 *
 * The listbox type can be one of the following: (avkon.hrh and aknlists.h)
 *   EAknCtSingleListBox                (See CAknSingleStyleListBox)
 *   EAknCtSingleNumberListBox          (See CAknSingleNumberStyleListBox)
 *   EAknCtSingleHeadingListBox         (See CAknSingleHeadingStyleListBox)
 *   EAknCtSingleGraphicListBox         (See CAknSingleGraphicStyleListBox)
 *   EAknCtSingleGraphicHeadingListBox  (See CAknSingleGraphicHeadingStyleListBox)
 *   EAknCtSingleNumberHeadingListBox   (See CAknSingleNumberHeadingStyleListBox)
 *   EAknCtSingleLargeListBox           (See CAknSingleLargeStyleListBox)
 *   EAknCtDoubleListBox                (See CAknDoubleStyleListBox)
 *   EAknCtDoubleNumberListBox          (See CAknDoubleNumberStyleListBox)
 *   EAknCtDoubleTimeListBox            (See CAknDoubleTimeStyleListBox)
 *   EAknCtDoubleLargeListBox           (See CAknDoubleLargeStyleListBox)
 *   EAknCtDoubleGraphicListBox         (See CAknDoubleGraphicStyleListBox)
 * 
 * The type field while defining find can be one of the following:
 *   EAknCtSelectionListFixedFind
 *   EAknCtSelectionListPopupFind
 *
 * The menubar you give for markable list dialog should have
 * one of the following as menu panes:
 *    R_AVKON_MENUPANE_MARKABLE_LIST   to get edit list menu
 *    R_AVKON_MENUPANE_MARKABLE_LIST_WITH_FIND_POPUP to get find and edit list
 * 
 * RESOURCE MENU_BAR r_res_id_for_a_menubar
 * {
 * titles =
 *     {
 *     MENU_TITLE { menu_pane = R_AVKON_MENUPANE_MARKABLE_LIST; }
 *     };
 * };
 *
 * C++ Usage:
 *    TInt openedItem = 0;
 *    MDesCArray *arrayOfItems = ...; 
 *    CArrayFix<TInt> *selectedItems = ...;
 *    CAknMarkableListDialog *dialog = CAknMarkableListDialog::NewL(openedItem, selectedItems, arrayOfItems, R_RES_ID_FOR_A_MENUBAR);
 *    TInt result = dialog->ExecuteLD(R_RES_ID_FOR_A_DIALOG);
 *    if (result) { ... } else { ... }
 *
 * What this class does:
 *   1) Setup listbox for markable list (resource file still needs to be correct for markable lists :)
 *   2) Loading default bitmaps
 *   3) Handles mark/unmark/mark all/unmark all and edit list options menu visibility
 *   4) Handles mark/unmark/mark all/unmark all commands from options menu
 *
 */
class CAknMarkableListDialog : public CAknSelectionListDialog
    {
public:
    IMPORT_C static CAknMarkableListDialog *NewL(TInt &aOpenedItem, CArrayFix<TInt> *aSelectedItems, MDesCArray *aArray, TInt aMenuBarResourceId, TInt aOkMenuBarId, MEikCommandObserver *aObserver =0);
    IMPORT_C static CAknMarkableListDialog *NewLC(TInt &aOpenedItem, CArrayFix<TInt> *aSelectedItems, MDesCArray *aArray, TInt aMenuBarResourceId, TInt aOkMenuBarId, MEikCommandObserver *aObserver =0);
    IMPORT_C ~CAknMarkableListDialog();
protected:
    IMPORT_C CAknMarkableListDialog(TInt &aValue, CArrayFix<TInt> *aSelectedItems, MDesCArray *aArray, TInt aMenuBarResourceId, TInt aOkMenuBarResourceId, MEikCommandObserver *aObserver);
    IMPORT_C void PreLayoutDynInitL();
    IMPORT_C void PostLayoutDynInitL();
    IMPORT_C void SelectionListProcessCommandL(TInt aCommand);
    IMPORT_C void ProcessCommandL(TInt aCommand);
    IMPORT_C void DynInitMenuPaneL(TInt aResourceId, CEikMenuPane *aMenuPane);
    IMPORT_C void HandleListBoxEventL( CEikListBox* aListBox, TListBoxEvent aEventType );
    IMPORT_C TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType );
    IMPORT_C TBool OkToExitL(TInt aButtonId);
private:
    CArrayFix<TInt> *iSelectionIndexArray; // Not owned
protected:
    TInt iMenuBarResourceId;
    TInt iOkMenuBarResourceId;

public: // DEPRECATED METHODS, DO NOT USE
    IMPORT_C static CAknMarkableListDialog *NewL(TInt &aOpenedItem, CArrayFix<TInt> *aSelectedItems, MDesCArray *aArray, TInt aMenuBarResourceId, MEikCommandObserver *aObserver =0);
public: // DEPRECATED METHODS, DO NOT USE
    IMPORT_C static CAknMarkableListDialog *NewLC(TInt &aOpenedItem, CArrayFix<TInt> *aSelectedItems, MDesCArray *aArray, TInt aMenuBarResourceId, MEikCommandObserver *aObserver =0);
protected: // DEPRECATED METHODS, DO NOT USE
    IMPORT_C CAknMarkableListDialog(TInt &aValue, CArrayFix<TInt> *aSelectedItems, MDesCArray *aArray, MEikCommandObserver *aObserver);
private: 
	IMPORT_C virtual void CEikDialog_Reserved_1();
	IMPORT_C virtual void CEikDialog_Reserved_2();	
private: 
	IMPORT_C virtual void CAknDialog_Reserved();
private: 
	IMPORT_C virtual void CAknSelectionListDialog_Reserved();
    };


typedef CAknSelectionListDialog CAknSelectionGridDialog;
typedef CAknMarkableListDialog CAknMarkableGridDialog;


#endif
