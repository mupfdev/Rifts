/*
* ============================================================================
*  Name     : AknListQueryDialog.h
*  Part of  : Avkon
*
*  Description:
*   Implementation of CAknListQueryDialog
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNLISTQUERYDIALOG_H
#define AKNLISTQUERYDIALOG_H

#include <aknquerydialog.h>

/**
* List query class
*   This class should be using List or multiselectionlist query
*/
class CAknListQueryDialog : public CAknQueryDialog,public MEikListBoxObserver, public MAknIntermediateState
	{
    public:
        /**
        * Constructor
        * @param aIndex After the query is dismissed, the index will hold
        *               the value of selected item.
        */
	    IMPORT_C CAknListQueryDialog(TInt* aIndex);

        /**
        * Constructor
        * @param aSelectionIndexArray Will hold the values of selected
        *                               items (in multiselectionlist).
        */
        IMPORT_C CAknListQueryDialog(CListBoxView::CSelectionIndexArray* aSelectionIndexArray);

        /**
        * Destructor
        */
	    IMPORT_C virtual ~CAknListQueryDialog();

        /**
        * From CEikdialog   EIKON provides an implementation of this function, 
        *                   which positions the dialog in the centre of the screen. 
        *                   However, it can be overridden by derived classes..
        * @param aSize      The size for the dialog.
        */
        IMPORT_C void SetSizeAndPosition(const TSize &aSize);

        /**
        * From CCoeControl  Handle key events. When a key event occurs, 
        *                   CONE calls this function for each control on the control stack, 
        *                   until one of them returns EKeyWasConsumed to indicate that it processed the key event.  
        * @param aKeyEvent  The key event.
        * @param aType      The type of the event: EEventKey, EEventKeyUp or EEventKeyDown.
        * @return           Indicates whether or not the key event was used by this control.
        */
	    IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);
	    
	    /**
        * From MEikListBoxObserver Handles events from listbox.
        * @param aListBox   The listbox which caused the event
        * @param aEventType Type of the event
        */
        IMPORT_C void HandleListBoxEventL(CEikListBox* aListBox, TListBoxEvent aEventType);

        /**
        * Sets item text array to the listbox
        * @param aItemTextArray Item text array to be added
        */
	    IMPORT_C void SetItemTextArray(MDesCArray* aItemTextArray);

        /**
        * Sets ownership type of the item array
        * @param TListBoxModelItemArrayOwnership Type of ownership
        */
	    IMPORT_C void SetOwnershipType(TListBoxModelItemArrayOwnership aOwnershipType);

        /**
        * SetIconArrayL() destroys possible old icon array 
        *   in the listbox and installs new one and 
        *   takes ownership of the new icon array.
        * @param aIcons Icon pointer which will be installed
        */
	    IMPORT_C void SetIconArrayL(CArrayPtr<CGulIcon>* aIcons);

        /**
        * Returns list query's listbox
        * @return Listbox
        */
	    IMPORT_C CEikListBox *ListBox() const;

		/**
		* Returns pointer to list query control or NULL
		*/
		IMPORT_C CAknListQueryControl* ListControl() const;

		/**
		* Return pointer to query heading or NULL
		*
		*/
		IMPORT_C CAknPopupHeadingPane* QueryHeading() const;

        /**
        * Marks control "ready to draw"
        */
	    IMPORT_C void ActivateL();

    protected:
        /**
        * From CEikdialog   This function is called by the EIKON dialog framework just
        *                   before the dialog is activated, but before it is sized,
        *                   and before PostLayoutDynInitL() is called.
        */
	    IMPORT_C void PreLayoutDynInitL(void);

        /**
        * From CEikdialog   This function is called by the EIKON dialog framework 
        *                   just before the dialog is activated, after it has called
        *                   PreLayoutDynInitL() and the dialog has been sized.
        */
        IMPORT_C void PostLayoutDynInitL();

        /**
        * From CEikdialog   This function is called by the EIKON framework 
        *                   if the user activates a button in the button panel. 
        *                   It is not called if the Cancel button is activated, 
        *                   unless the EEikDialogFlagNotifyEsc flag is set.
        * @param aButtonId  The ID of the button that was activated
        * @return           Should return ETrue if the dialog should exit, and EFalse if it should not.
        */
        IMPORT_C TBool OkToExitL(TInt aButtonId);

        /**
        * Returns border style of the list query
        * @return Border style (AknBorderId type)
        */
	    IMPORT_C TInt BorderStyle();

    protected:
        /*
        * From MAknIntermediateState
        *   Tries to close the query with non-leaving way
        */
	    IMPORT_C void CloseState();

    private:
        /**
        * Closes the dialog
        *   Gets called by iIdle
        */
	    static TInt ClosePopup(TAny *aObj);

	private: 
		IMPORT_C virtual void CEikDialog_Reserved_1();
		IMPORT_C virtual void CEikDialog_Reserved_2();	
	private: 
		IMPORT_C virtual void CAknDialog_Reserved();
	private:
		IMPORT_C virtual void CAknQueryDialog_Reserved();
    private:
        // Will hold the index of the selected item
        TInt *iIndex;
        // Will hold the selected items' indexes
        CListBoxView::CSelectionIndexArray *iSelectionIndexArray;
        // Was the enter key pressed
	    TBool iEnterKeyPressed;
        // Idle object to close the query if it there's no items to show
	    CIdle *iIdle;
        // Layout for List query control
	    TAknPopupWindowLayoutDef iLayout;
	};

#endif