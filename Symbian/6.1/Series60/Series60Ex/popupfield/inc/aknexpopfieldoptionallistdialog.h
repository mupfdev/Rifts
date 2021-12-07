/*
* =============================================================================
*  Name     : CAknExPopupFieldOptionalListDialog
*  Part of  : AknExPopField
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

#ifndef AKNEXPOPFIELDOPTIONALLISTDIALOG_H
#define AKNEXPOPFIELDOPTIONALLISTDIALOG_H

// INCLUDES
#include "AknExPopFieldBaseDialog.h"

// CONSTANTS
const TInt KAknExPopFieldMaxOLTextValueField = 13;

// FORWARD DECLARATIONS
class CAknQueryValueTextArray;
class CAknQueryValueText;

// CLASS DECLARATION

/**
* CAknExPopFieldOptionalListDialog
*/
class CAknExPopFieldOptionalListDialog : public CAknExPopFieldBaseDialog
    {
    private: // Enumerations for Text Array

        enum TAknExPopFieldTextArrayIndex
            {
            EAknExPopFieldTextArrayIndex0,
            EAknExPopFieldTextArrayIndex1,
            EAknExPopFieldTextArrayIndex2,
            EAknExPopFieldTextArrayIndex3,
            EAknExPopFieldTextArrayIndex4,
            EAknExPopFieldTextArrayIndex5,
            EAknExPopFieldTextArrayIndex6,
            EAknExPopFieldTextArrayIndex7,
            EAknExPopFieldTextArrayIndex8,
            EAknExPopFieldTextArrayIndex9,
            EAknExPopFieldTextArrayIndex10,
            EAknExPopFieldTextArrayIndex11,
            EAknExPopFieldTextArrayIndex12
            };

    public: // Constructors and destructor

        /**
        * EPOC two-phase constructor.
        */
        static CAknExPopFieldOptionalListDialog* NewLC();

        /**
        * Destructor.
        */
        virtual ~CAknExPopFieldOptionalListDialog();

    private: // Constructors.

        /**
        * Constructor.
        */
        CAknExPopFieldOptionalListDialog();

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

        CDesCArray* iTextArray[KAknExPopFieldMaxOLTextValueField];
        CAknQueryValueTextArray* 
            iValueTextArray[KAknExPopFieldMaxOLTextValueField];
        CAknQueryValueText* iTextValues[KAknExPopFieldMaxOLTextValueField];
        TInt iIndexValue[KAknExPopFieldMaxOLTextValueField];

    };

#endif

// End of File
