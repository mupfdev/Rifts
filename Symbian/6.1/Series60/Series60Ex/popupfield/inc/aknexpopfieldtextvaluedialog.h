/*
* =============================================================================
*  Name     : CAknExPopupFieldTextValueDialog
*  Part of  : AknExPopField
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

#ifndef AKNEXPOPFIELDTEXTVALUEDIALOG_H
#define AKNEXPOPFIELDTEXTVALUEDIALOG_H

// INCLUDES
#include "AknExPopFieldBaseDialog.h"

// CONSTANTS
const TInt KAknExPopFieldMaxTextValueField = 12;
const TInt KAknExPopupFieldTextMaxValues = 2;

// FORWARD DECLARATIONS
class CAknQueryValueTextArray;
class CAknQueryValueText;

// CLASS DECLARATION

/**
* CAknExPopFieldTextValueDialog
*/
class CAknExPopFieldTextValueDialog : public CAknExPopFieldBaseDialog
    {
    public: // Constructors and destructor

        /**
        * EPOC two-phase constructor.
        */
        static CAknExPopFieldTextValueDialog* NewLC();

        /**
        * Destructor.
        */
        virtual ~CAknExPopFieldTextValueDialog();

    private: // Constructors.

        /**
        * Constructor.
        */
        CAknExPopFieldTextValueDialog();

    private: // New functions

        /**
        * Discard text array in popup field object.
        */
        void DiscardTextArray();

    protected: // From CAknExPopFieldBaseDialog
		
        /**
        * From CAknExPopFieldBaseDialog, OkToExitL.
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

        CDesCArray* iTextArray;
        CAknQueryValueTextArray* iValueTextArray;
        CAknQueryValueText* iTextValues[KAknExPopFieldMaxTextValueField];
        TInt iIndexValue[KAknExPopFieldMaxTextValueField];

    };

#endif

// End of File
