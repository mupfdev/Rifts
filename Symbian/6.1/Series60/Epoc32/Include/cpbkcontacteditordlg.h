/*
* ============================================================================
*  Name     : CPbkContactEditorDlg from CPbkContactEditorDlg.h
*  Part of  : PbkView.dll
*
*  Description:
*     Phonebook contact editor dialog.
*  Version:
*
*  Copyright (C) 2002 Nokia Corporation.
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

#ifndef __CPbkContactEditorDlg_H__
#define __CPbkContactEditorDlg_H__

//  INCLUDES
#include <AknForm.h>    // CAknForm
#include <cntdef.h>     // TContactItemId 
#include <eikdef.h>		// TBitFlags


// FORWARD DECLARATIONS
class CAknTitlePane;
class CPbkContextPaneIcon;
class CPbkThumbnailPopup;
class CPbkThumbnailCmd;
class CPbkContactEditorFieldArray;
class CPbkContactEngine;
class CPbkContactItem;
class MPbkContactEditorStrategy;


// CLASS DECLARATION

/**
 * Phonebook Contact editor dialog. 
 */
class CPbkContactEditorDlg : 
        public CAknForm
    {
    public:  // Constructors and destructor
        /**
         * Creates an editor for aContactItem.
         *
         * @param aEngine phonebook engine 
         * @param aContactItem contact item to edit
         * @param aIsNewContact set to true if aContactItem is a new contact
         *        (not yet in the database)
         * @param aFocusIndex index of field to focus initially
         * @param aEdited if true sets the contact initially as "edited".
         *        Use when some data is added to aContactItem
         *        that needs to be saved even if user edits 
         *        nothing.
         * @return new dialog object.
         */
		IMPORT_C static CPbkContactEditorDlg* NewL
            (CPbkContactEngine& aEngine, 
            CPbkContactItem& aContactItem, 
	        TBool aIsNewContact,
            TInt aFocusIndex=-1,
            TBool aEdited=EFalse);

        /**
         * Destructor.
         */
        ~CPbkContactEditorDlg();
		
    public:  // Interface
        /**
         * Sets aSelfPtr to NULL when this dialog is destroyed.
         * @precond !aSelfPtr || *aSelfPtr==this
         */
        IMPORT_C void ResetWhenDestroyed(CPbkContactEditorDlg** aSelfPtr);

		/**
         * Runs the dialog. This object is destroyed when this function
         * returns or leaves.
         *
         * @return  Id of the saved contact. KNullContactId if not saved. 
         *          Please note that the contact item (aContactItem passed
         *          to NewL) might be modified even if it is not saved to the
         *          database.
		 */
		IMPORT_C TContactItemId ExecuteLD();

        /**
         * Hides the 'Exit' command from the options menu. This must be called
         * before calling ExecuteLD.
		 */
        IMPORT_C void HideExitCommand();
        
    private:  // from CCoeControl
	    TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);
        void GetHelpContext(TCoeHelpContext& aContext) const;

    private:  // Command handlers
        void CmdSaveL();
        void CmdDoneL();
        void CmdEditItemLabelL();
        void CmdAddItemL();
        void CmdDeleteItemL();
        void CmdFetchThumbnailL();
        void CmdRemoveThumbnailL();

    private:  // From CAknForm
        void PreLayoutDynInitL();
        void PostLayoutDynInitL();
        void SetInitialCurrentLine();
		void ProcessCommandL(TInt aCommandId);
		void DynInitMenuPaneL(TInt aResourceId, CEikMenuPane* aMenuPane);
	    TBool OkToExitL(TInt aKeycode);
        void HandleControlStateChangeL(TInt aControlId);

	protected:  // Constructors
        CPbkContactEditorDlg
            (CPbkContactEngine& aEngine, 
			CPbkContactItem& aContactItem,
            TInt aFocusIndex);
        void BaseConstructL(TBool aIsNewContact, TBool aEdited);

    protected:  // Implementation
        void StoreTitlePaneTextL();
        void ConstructContextMenuL();
        TBool IsNewContact() const;
        void UpdateTitlePaneL();
        void CloseAllPopups();

        void WriteContactToDbL();

        /// State flag values for CPbkContactEditorDlg
        enum TStateFlag
            {
            EHideExit,
            EEscKeyReceived,
            EUnderDestruction
            };

	protected: // data
		/// Ref: Contact item under editing
        CPbkContactItem& iContactItem;
        /// Own: Contact editor field manager
        CPbkContactEditorFieldArray* iFieldManager;

    private:  // Data
		/// Ref; Contact engine
        CPbkContactEngine& iEngine;
        /// Own: Index of field to focus initially
        TInt iFocusIndex;
        /// Own: state flags
        mutable TBitFlags iStateFlags;
        /// Ref: pointer to ExecuteLD return value
        TContactItemId* iSavedContactPtr;
        /// Ref: application's title pane
        CAknTitlePane* iTitlePane;
        /// Own: Title pane text to restore on exit
        HBufC* iStoredTitlePaneText;
        /// Own: Phonebook context pane icon
        CPbkContextPaneIcon* iContextPaneIcon;
        /// Own: Thumbnail image handler
        CPbkThumbnailPopup* iThumbnailHandler;
        /// Own: context menu bar
        CEikMenuBar* iContextMenuBar;
        /// Own: Thumbnail command handler
        CPbkThumbnailCmd* iThumbnailCmd;
		/// Own: editor dialog strategy
		MPbkContactEditorStrategy* iEditorStrategy;
        /**
         * Ref: self pointer for easier leave handling
         * @invariant !iSelfPtr || *iSelfPtr==this
         */
        CPbkContactEditorDlg** iSelfPtr;
     };

#endif // __CPbkContactEditorDlg_H__
            
// End of File
