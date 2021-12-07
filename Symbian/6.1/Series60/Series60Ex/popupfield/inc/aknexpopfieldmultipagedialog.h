/*
* =============================================================================
*  Name     : CAknExPopupFieldMultiPageDialog
*  Part of  : AknExPopField
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

#ifndef AKNEXPOPFIELDMULTIPAGEDIALOG_H
#define AKNEXPOPFIELDMULTIPAGEDIALOG_H

// INCLUDES
#include "AknExPopFieldBaseDialog.h"
#include <AknQueryValueNumber.h>
#include <AknQueryValuePhone.h>
#include <AknQueryValueTime.h>
#include <AknQueryValueDate.h>
#include <AknQueryValueDuration.h>

// CONSTANTS
const TInt KAknExPopFieldMaxMultiPageValueField = 6;

// FORWARD DECLARATIONS
class CAknQueryValueTextArray;
class CAknQueryValueNumberArray;
class CAknQueryValuePhoneArray;
class CAknQueryValueTimeArray;
class CAknQueryValueDateArray;
class CAknQueryValueDurationArray;
class CAknQueryValueText;
class CAknQueryValueNumber;
class CAknQueryValuePhone;
class CAknQueryValueTime;
class CAknQueryValueDate;
class CAknQueryValueDuration;

// CLASS DECLARATION

/**
* CAknExPopFieldMultiPageDialog
*/
class CAknExPopFieldMultiPageDialog : public CAknExPopFieldBaseDialog
    {
    public: // Constructors and destructor

        /**
        * EPOC two-phase constructor.
        */
        static CAknExPopFieldMultiPageDialog* NewLC();

        /**
        * Destructor.
        */
        virtual ~CAknExPopFieldMultiPageDialog();

    private: // Constructors.

        /**
        * Constructor.
        */
        CAknExPopFieldMultiPageDialog();

    private: // New functions

        /**
        * Discard array in popup field object.
        */
        void DiscardArray();

    private: // From CAknExPopFieldBaseDialog

        /**
        * From CAknExPopFieldBaseDialog, ConfigurePopfieldTextL
        * Configuration values into Popup Fields.
        */
        void ConfigurePopfieldValueL();

    private: // New functions
        /**
        * Configuration values (text) into Popup Fields.
        */
        void ConfigurePageTextL();

        /**
        * Configuration values (number) into Popup Fields.
        */
        void ConfigurePageNumberL();

        /**
        * Configuration values (phone) into Popup Fields.
        */
        void ConfigurePagePhoneL();

        /**
        * Configuration values (time) into Popup Fields.
        */
        void ConfigurePageTimeL();

        /**
        * Configuration values (date) into Popup Fields.
        */
        void ConfigurePageDateL();

        /**
        * Configuration values (duration) into Popup Fields.
        */
        void ConfigurePageDurationL();

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

        // For text array
        CDesCArray* iTextArray;
        CAknQueryValueTextArray* iValueTextArray;
        CAknQueryValueText* iTextValues[KAknExPopFieldMaxMultiPageValueField];

        // For number array
        CArrayFixFlat<TInt>* iNumberArray;
        CAknQueryValueNumberArray* iValueNumberArray;
        CAknQueryValueNumber* 
            iNumberValues[KAknExPopFieldMaxMultiPageValueField];

        // For phone array
        CDesCArray* iPhoneArray;
        CAknQueryValuePhoneArray* iValuePhoneArray;
        CAknQueryValuePhone*
            iPhoneValues[KAknExPopFieldMaxMultiPageValueField];

        // For time array
        CArrayFixFlat<TTime>* iTimeArray;
        CAknQueryValueTimeArray* iValueTimeArray;
        CAknQueryValueTime* iTimeValues[KAknExPopFieldMaxMultiPageValueField];

        // For date array
        CArrayFixFlat<TTime>* iDateArray;
        CAknQueryValueDateArray* iValueDateArray;
        CAknQueryValueDate* iDateValues[KAknExPopFieldMaxMultiPageValueField];

        // For duration array
        CArrayFixFlat<TTimeIntervalSeconds>* iDurationArray;
        CAknQueryValueDurationArray* iValueDurationArray;
        CAknQueryValueDuration* 
            iDurationValues[KAknExPopFieldMaxMultiPageValueField];
        TInt iIndexValueText[KAknExPopFieldMaxMultiPageValueField];
        TInt iIndexValueNumber[KAknExPopFieldMaxMultiPageValueField];
        TInt iIndexValuePhone[KAknExPopFieldMaxMultiPageValueField];
        TInt iIndexValueTime[KAknExPopFieldMaxMultiPageValueField];
        TInt iIndexValueDate[KAknExPopFieldMaxMultiPageValueField];
        TInt iIndexValueDuration[KAknExPopFieldMaxMultiPageValueField];
    };

#endif

// End of File
