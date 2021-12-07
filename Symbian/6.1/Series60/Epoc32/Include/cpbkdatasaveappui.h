/*
* ============================================================================
*  Name     : CPbkDataSaveAppUi from CPbkDataSaveAppUi.h
*  Part of  : PbkView.dll
*
*  Description:
*    Phonebook Data Save service helper. Implements "Save to phonebook" 
*    menu functionality for external applications.
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

#ifndef __CPbkDataSaveAppUi_H__
#define __CPbkDataSaveAppUi_H__

//  INCLUDES
#include <e32base.h>

// FORWARD DECLARATIONS
class CEikMenuPane;
class CPbkContactEngine;
class CPbkContactItem;
class CPbkFieldInfo;
class MPbkDataSaveCallback;
class CPbkFFSCheck;


// CLASS DECLARATION

/**
 * Phonebook Data Save service helper. Implements "Save to phonebook" 
 * menu functionality for external applications.
 */
class CPbkDataSaveAppUi : public CBase
    {
    public:  // Interface
        /**
         * Creates an instance of this class.
         *
         * @param aEngine   Phonebook engine instance.
         */
        IMPORT_C static CPbkDataSaveAppUi* NewL(CPbkContactEngine& aEngine);

        /**
         * Destructor. Destroys this object and cancels any open dialogs.
         */
        ~CPbkDataSaveAppUi();

        /**
         * Adds Phonebook data save menu items to a menu pane. Called from 
         * applications DynInitMenuPaneL. This call is not mandatory: 
         * if the application provides its own menus it may call
         * HandleCommandL directly from menu's command handler.
         *
         * @param aMenuPane     menu pane where to add the menu items.
         * @param aCommandId    id of command which to replace with Phonebook
         *                      data save menu items. This command id is stored
         *                      into this object as the base id after which are
         *                      app-specific command Ids reserved for Phonebook
         *                      data save API usage.
         * @see DynInitMenuPaneL
         * @see HandleCommandL
         */
        IMPORT_C void AddMenuItemsL(CEikMenuPane* aMenuPane, TInt aCommandId);

        /**
         * Updates Phonebook data save menu items. Called from applications 
         * DynInitMenuPaneL. This call is not mandatory: if the application 
         * provides its own menus it may call HandleCommandL directly 
         * from menu's command handler.
         *
         * @param aResourceId   resource id of the menu pane as passed to 
         *                      MEikMenuObserver::DynInitMenuPaneL. If this 
         *                      resource id does not match with Phonebook data
         *                      save submenu this function does nothing.
         * @param aMenuPane     menu pane as passed to 
         *                      MEikMenuObserver::DynInitMenuPaneL.
         * @see AddMenuItemL
         */
        IMPORT_C void DynInitMenuPaneL(TInt aResourceId, CEikMenuPane* aMenuPane);

        /**
         * Handles a menu command inserted by AddMenuItemsL.
         *
         * @param aCommandId        command to execute. iBaseCommandId+1 is
         *                          Create New Entry and iBaseCommandId+2 is
         *                          Add to Existing Entry. Use directly 
         *                          EPbkCmdDataSaveCreateNew or EPbkCmdDataSaveAddToExisting
         *                          if AddMenuItemsL is not called.
         * @param aFieldTypes       field types where the user can select from.
         *                          If there is only one field type selection
         *                          list is not displayed.
         * @param aText             text to put to the selected field.
         * @param aCallback         Calls back to this object if there are 
         *                          problems in adding the field. See 
         *                          MPbkDataSaveCallback class for details.
         * @return  ETrue if the command was executed and the data added, 
         *          EFalse if the operation was canceled in any stage.
         * @see AddMenuItemsL
         * @see MPbkDataSaveCallback
         * @see TPbkDataSaveCommandId
         */
        IMPORT_C TBool HandleCommandL
            (TInt aCommandId, 
            CArrayPtr<CPbkFieldInfo>& aFieldTypes,
            const TDesC& aText,
            MPbkDataSaveCallback* aCallback=NULL);

        /**
         * Handles a menu command inserted by AddMenuItemsL.
         *
         * @param aCommandId        command to execute. iBaseCommandId+1 is
         *                          Create New Entry and iBaseCommandId+2 is
         *                          Add to Existing Entry. Use directly 
         *                          EPbkCmdDataSaveCreateNew or EPbkCmdDataSaveAddToExisting
         *                          if AddMenuItemsL is not called.
         * @param aFieldTypes       field types where the user can select from.
         *                          If there is only one field type selection
         *                          list is not displayed.
         * @param aDate             date to put to the selected field.
         * @param aCallback         Calls back to this object if there are 
         *                          problems in adding the field. See 
         *                          MPbkDataSaveCallback class for details.
         * @return  ETrue if the command was executed and the data added, 
         *          EFalse if the operation was canceled in any stage.
         * @see AddMenuItemsL
         * @see MPbkDataSaveCallback
         * @see TPbkDataSaveCommandId
         */
        IMPORT_C TBool HandleCommandL
            (TInt aCommandId, 
            CArrayPtr<CPbkFieldInfo>& aFieldTypes,
            const TTime& aDate,
            MPbkDataSaveCallback* aCallback=NULL);

        /**
         * Hides the "Exit" command from contact editor's options menu.
         * Call this function after creating this object.
         */
        IMPORT_C void HideEditorExitCommand();
        
    private:  // Implementation
        class MFieldData;
        class CTextFieldData;
        class CDateFieldData;
        class CCommandBase;
        class CCreateNewCommand;
        class CAddToExistingCommand;
        CPbkDataSaveAppUi(CPbkContactEngine& aEngine);
        void ConstructL();
        TBool DoHandleCommandL
            (TInt aCommandId, 
            CArrayPtr<CPbkFieldInfo>& aFieldTypes,
            MFieldData& aFieldData,
            MPbkDataSaveCallback* aCallback);

    private:  // Data
        /// Ref: Phonebook engine instance
        CPbkContactEngine* iEngine;
        /// Own: FFS space checker
        CPbkFFSCheck* iFFSCheck;
        /// Own: base command id
        TInt iBaseCommandId;
        /// Own: the currently executing command
        CCommandBase* iExecutingCommand;
        /// Own: flags
        TUint iFlags;
    };


/**
 * Callback interface for CPbkDataSaveAppUi::HandleCommandL.
 */
class MPbkDataSaveCallback
    {
    public:  // Interface
        /**
         * Called by CPbkDataSaveAppUi::HandleCommandL if there is no field
         * available where to save the data and no new field could be added.<br>
         * Default implementation does nothing.
         *
         * @param aContact  contact where the field cannot be added.
         */
        IMPORT_C virtual void PbkDataSaveNoFieldL(CPbkContactItem& aContact);

        /**
         * Called from CPbkDataSaveAppUi::HandleCommandL if the aText is too 
         * long to fit into field.<p>
         * Default implementation clips aText from the end. If an empty 
         * string is returned the field addition is canceled.
         *
         * @param aText         the original text.
         * @param aFieldInfo    the type of field where the text should be 
         *                      inserted.
         * @return  a substring of aText so that the substring's length is 
         *          <=aFieldInfo.MaxLength().<br> 
         */
        IMPORT_C virtual TPtrC PbkDataSaveClipTextL
            (const TDesC& aText, CPbkFieldInfo& aFieldInfo);
    };

#endif // __CPbkDataSaveAppUi_H__

// End of File
