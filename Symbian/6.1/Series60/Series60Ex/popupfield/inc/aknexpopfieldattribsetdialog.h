/*
* =============================================================================
*  Name     : CAknExPopFieldAttribSetDialog
*  Part of  : AknExPopField
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

#ifndef AKNEXPOPFIELDATTRIBSETDIALOG_H
#define AKNEXPOPFIELDATTRIBSETDIALOG_H

// INCLUDES
#include <eikmenub.h>
#include "AknExPopFieldBaseDialog.h"

// CONSTANTS
const TInt KAknExPopFieldAttribSetControlCount = 2;
const TInt KAknExPopFieldTextMaxValues = 2;

// FORWARD DECLARATIONS
class CAknQueryValueTextArray;
class CAknQueryValueText;

// CLASS DECLARATION

/**
* CAknExPopFieldAttribSetDialog
*/
class CAknExPopFieldAttribSetDialog : public CAknExPopFieldBaseDialog
    {
    public: // Constructors and destructor

        /**
        * EPOC two-phase constructor.
        */
        static CAknExPopFieldAttribSetDialog* NewLC();

        /**
        * Destructor.
        */
        virtual ~CAknExPopFieldAttribSetDialog();

    private: // Constructors.

        /**
        * Constructor.
        */
        CAknExPopFieldAttribSetDialog();

    private: // New functions

        /**
        * Discard text array in popup field object.
        */
        void DiscardTextArray();

        /**
        * Set flag to indicate if we are in the save menu.
        * @param aVal
        */
        void SetIsSaveMenu( TBool aVal );

        /**
        * Check if we are in the save menu.
        */
        TBool IsSaveMenu();

    public: // From CAknDialog

        /**
        * From CAknExPopfieldBaseDialog, DynInitMenuPaneL.
        * Dims "Label", "Add" and "Delete" menu items.
        * @param aResourceId 
        * @param aMenuPane Pointer to menu-pane object.
        */
        void DynInitMenuPaneL( TInt aResourceId, CEikMenuPane* aMenuPane );

        /**
        * From CAknDialog, ProcessCommandL.
        * @param aResourceId
        */
        void ProcessCommandL( TInt aCommandId );

    protected: // From CAknDialog
        
        /**
        * From CAknDialog, OkToExitL.
        * @param aButtonId 
        */
        TBool OkToExitL( TInt aButtonId );

    private: // From CAknExPopFieldBaseDialog

        /**
        * From CAknExPopFieldBaseDialog, ConfigurePopfieldTextL
        * Configuration values (text) into Popup Fields.
        */
        void ConfigurePopfieldValueL();

        /**
        * From CAknForm 
        * Save the contents of the form.
        */
        TBool SaveFormDataL();

        /**
        * From CAknForm 
        * Does not save the contents of the form.
        */
        void DoNotSaveFormDataL();



    private: // Data

        CDesCArray* iTextEmptyArray[KAknExPopFieldAttribSetControlCount]; 
        CAknQueryValueTextArray* iValueTextArrayWithNoElements[KAknExPopFieldAttribSetControlCount];
        //CAknQueryValueTextArray* iValueTextArrayWithFourElements;
        CAknQueryValueText* iTextValues[KAknExPopFieldAttribSetControlCount];
        TBool iIsSaveMenuFlag;
        TInt iIndexValue[KAknExPopFieldAttribSetControlCount];

    };

#endif

// End of File
