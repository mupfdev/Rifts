/*
* =============================================================================
*  Name     : CAknExPopupFieldBaseDialog
*  Part of  : AknExPopField
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

#ifndef AKNEXPOPFIELDBASEDIALOG_H
#define AKNEXPOPFIELDBASEDIALOG_H

// INCLUDES
#include <aknform.h>

// CONSTANTS

// FORWARD DECLARATIONS

// CLASS DECLARATION

/**
* CAknExPopFieldDialog
*/
class CAknExPopFieldBaseDialog : public CAknForm
    {
    public: // Constructors and destructor

        /**
        * Destructor.
        */
        virtual ~CAknExPopFieldBaseDialog();

    protected: // Constructors.

        /**
        * Constructor.
        */
        CAknExPopFieldBaseDialog();

    public: // From CAknDialog

        /**
        * From CAknDialog, DynInitMenuPaneL.
        * Dims "Label", "Add" and "Delete" menu items.
        * @param aResourceId 
        * @param aMenuPane Pointer to menu-pane object.
        */
        virtual void DynInitMenuPaneL( TInt aResourceId, CEikMenuPane* aMenuPane );

        /**
        * From CAknDialog, ProcessCommandL.
        * @param aResourceId
        */
        virtual void ProcessCommandL( TInt aCommandId );

	protected: // From CAknDialog

        /**
        * From CAknDialog, OkToExitL.
        * @param aButtonId 
        */
        virtual TBool OkToExitL( TInt aButtonId );

    private: // New functions

        /**
        * Configuration values into Popup Fields.
        * This is pure virtual function.
        */
        virtual void ConfigurePopfieldValueL() = NULL;

    private: // From CEikDialog

        /**
        * From CEikDialog, PreLayoutDynInitL.
        * Initialises the dialog's controls before the dialog is sized 
        * and layed out.
        */
        void PreLayoutDynInitL();

        /**
        * From CEikDialog, PostLayoutDynInitL.
        * Initialises the dialog's controls after the dialog has been sized
        * but before it has been activated.
        */
        void PostLayoutDynInitL();

    };

#endif

// End of File
