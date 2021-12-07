/*
* =============================================================================
*  Name     : CAknExPopupFieldManyLineDialog
*  Part of  : AknExPopField
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

#ifndef AKNEXPOPFIELDMANYLINEDIALOG_H
#define AKNEXPOPFIELDMANYLINEDIALOG_H

// INCLUDES
#include "AknExPopFieldBaseDialog.h"

// CONSTANTS
const TInt KAknExPopFieldMaxMLTextValueField = 4;

// FORWARD DECLARATIONS
class CAknQueryValueTextArray;
class CAknQueryValueText;

// CLASS DECLARATION

/**
* CAknExPopFieldManyLineDialog
*/
class CAknExPopFieldManyLineDialog : public CAknExPopFieldBaseDialog
    {
    public: // Constructors and destructor

        /**
        * EPOC two-phase constructor.
        */
        static CAknExPopFieldManyLineDialog* NewLC();

        /**
        * Destructor.
        */
        virtual ~CAknExPopFieldManyLineDialog();

    private: // Constructors.

        /**
        * Constructor.
        */
        CAknExPopFieldManyLineDialog();

    private: // New functions

        /**
        * Discard text array in popup field object.
        */
        void DiscardTextArray();

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
        CAknQueryValueText* iTextValues[KAknExPopFieldMaxMLTextValueField];
        TInt iIndexValue[KAknExPopFieldMaxMLTextValueField];

    };

#endif

// End of File
