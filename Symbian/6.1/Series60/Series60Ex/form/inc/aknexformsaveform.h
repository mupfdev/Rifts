/*
* ============================================================================
*  Name     : CAknExFormSaveForm.h
*  Part of  : AknExForm
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNEXFORMSAVETESTFORM_H
#define AKNEXFORMSAVETESTFORM_H

// INCLUDES
#include <aknform.h>
#include "AknExForm.hrh"

// CONSTANTS

// CLASS DECLARATION

/**
* CAknExFormApplication application class.
* Provides factory to create concrete document object.
*/
class CAknExFormSaveForm : public CAknForm
    {
    public:  // Constructor and destructor  
        /**
        * Two-phased constructor.
        */
        static CAknExFormSaveForm* NewL();

        /**
        * Destructor.
        */
        virtual ~CAknExFormSaveForm();

        TInt ExecuteLD( TInt aResourceId ); 
        void PrepareLC( TInt aResourceId ); 

    private:  // Constructor
        /**
        * Default constructor.
        */
        CAknExFormSaveForm();

        /**
        * Second-phase constructor.
        */
        void ConstructL();
    
    private:  // Functions from base class
        /**
        * From CEikDialog 
        * Set default field value to member data.
        */
        void PostLayoutDynInitL();

        /**
        * From CAknForm 
        * Show save query. If user answers "No" to this query.
        * return field value to the value which is before editing.
        */
        TBool QuerySaveChangesL();

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

    private:
        TBuf<EAknExFormEdwinMaxLength> iEdwinData1;
        TBuf<EAknExFormEdwinMaxLength> iEdwinData2;
        TBuf<EAknExFormEdwinMaxLength> iEdwinData3;
        TBuf<EAknExFormEdwinMaxLength> iEdwinData4;
        TBuf<EAknExFormEdwinMaxLength> iEdwinData5;
        TBuf<EAknExFormEdwinMaxLength> iEdwinData6;
        TBuf<EAknExFormEdwinMaxLength> iEdwinData7;
        TBuf<EAknExFormEdwinMaxLength> iEdwinData8;
        TBuf<EAknExFormEdwinMaxLength> iEdwinData9;
        TBuf<EAknExFormEdwinMaxLength> iEdwinData10;
        TBuf<EAknExFormEdwinMaxLength> iEdwinData11;
        TBuf<EAknExFormEdwinMaxLength> iEdwinData12;
        TBuf<EAknExFormEdwinMaxLength> iEdwinData13;
        TBuf<EAknExFormEdwinMaxLength> iEdwinData14;
        TBuf<EAknExFormEdwinMaxLength> iEdwinData15;
        TBuf<EAknExFormEdwinMaxLength> iEdwinData16;
        TBuf<EAknExFormEdwinMaxLength> iEdwinData17;
        TInt                           iNumberData1;
        TInt                           iNumberData2;
        TInt                           iNumberData3;
        TInt                           iNumberData4;
        TInt                           iNumberData5;
        TInt                           iNumberData6;
        TTime                          iDateData1;
        TTime                          iDateData2;
        TTime                          iDateData3;
        TTime                          iDateData4;
        TTime                          iDateData5;
        TTime                          iDateData6;
        TTime                          iTimeData1;
        TTime                          iTimeData2;
        TTime                          iTimeData3;
        TTime                          iTimeData4;
        TTime                          iTimeData5;
        TTime                          iTimeData6;
        TTimeIntervalSeconds           iDurationData1;
        TTimeIntervalSeconds           iDurationData2;
        TTimeIntervalSeconds           iDurationData3;
        TTimeIntervalSeconds           iDurationData4;
        TTimeIntervalSeconds           iDurationData5;
        TTimeIntervalSeconds           iDurationData6;
        TBuf<EAknExFormEdwinMaxLength> iSecretData1;
        TBuf<EAknExFormEdwinMaxLength> iSecretData2;
        TBuf<EAknExFormEdwinMaxLength> iSecretData3;
        TBuf<EAknExFormEdwinMaxLength> iSecretData4;
        TBuf<EAknExFormEdwinMaxLength> iSecretData5;
        TBuf<EAknExFormEdwinMaxLength> iSecretData6;
        TInt                           iSliderData1;
        TInt                           iSliderData2;
        TInt                           iSliderData3;
        TBuf<EAknExFormLabelMaxLength> iEdwinLabel1;
        TBuf<EAknExFormLabelMaxLength> iEdwinLabel2;
        TBuf<EAknExFormLabelMaxLength> iEdwinLabel3;
        TBuf<EAknExFormLabelMaxLength> iEdwinLabel4;
        TBuf<EAknExFormLabelMaxLength> iEdwinLabel5;
        TBuf<EAknExFormLabelMaxLength> iEdwinLabel6;
        TBuf<EAknExFormLabelMaxLength> iEdwinLabel7;
        TBuf<EAknExFormLabelMaxLength> iEdwinLabel8;
        TBuf<EAknExFormLabelMaxLength> iEdwinLabel9;
        TBuf<EAknExFormLabelMaxLength> iEdwinLabel10;
        TBuf<EAknExFormLabelMaxLength> iEdwinLabel11;
        TBuf<EAknExFormLabelMaxLength> iEdwinLabel12;
        TBuf<EAknExFormLabelMaxLength> iEdwinLabel13;
        TBuf<EAknExFormLabelMaxLength> iEdwinLabel14;
        TBuf<EAknExFormLabelMaxLength> iEdwinLabel15;
        TBuf<EAknExFormLabelMaxLength> iEdwinLabel16;
        TBuf<EAknExFormLabelMaxLength> iEdwinLabel17;
        TBuf<EAknExFormLabelMaxLength> iNumberLabel1;
        TBuf<EAknExFormLabelMaxLength> iNumberLabel2;
        TBuf<EAknExFormLabelMaxLength> iNumberLabel3;
        TBuf<EAknExFormLabelMaxLength> iNumberLabel4;
        TBuf<EAknExFormLabelMaxLength> iNumberLabel5;
        TBuf<EAknExFormLabelMaxLength> iNumberLabel6;
        TBuf<EAknExFormLabelMaxLength> iDateLabel1;
        TBuf<EAknExFormLabelMaxLength> iDateLabel2;
        TBuf<EAknExFormLabelMaxLength> iDateLabel3;
        TBuf<EAknExFormLabelMaxLength> iDateLabel4;
        TBuf<EAknExFormLabelMaxLength> iDateLabel5;
        TBuf<EAknExFormLabelMaxLength> iDateLabel6;
        TBuf<EAknExFormLabelMaxLength> iTimeLabel1;
        TBuf<EAknExFormLabelMaxLength> iTimeLabel2;
        TBuf<EAknExFormLabelMaxLength> iTimeLabel3;
        TBuf<EAknExFormLabelMaxLength> iTimeLabel4;
        TBuf<EAknExFormLabelMaxLength> iTimeLabel5;
        TBuf<EAknExFormLabelMaxLength> iTimeLabel6;
        TBuf<EAknExFormLabelMaxLength> iDurationLabel1;
        TBuf<EAknExFormLabelMaxLength> iDurationLabel2;
        TBuf<EAknExFormLabelMaxLength> iDurationLabel3;
        TBuf<EAknExFormLabelMaxLength> iDurationLabel4;
        TBuf<EAknExFormLabelMaxLength> iDurationLabel5;
        TBuf<EAknExFormLabelMaxLength> iDurationLabel6;
        TBuf<EAknExFormLabelMaxLength> iSecretLabel1;
        TBuf<EAknExFormLabelMaxLength> iSecretLabel2;
        TBuf<EAknExFormLabelMaxLength> iSecretLabel3;
        TBuf<EAknExFormLabelMaxLength> iSecretLabel4;
        TBuf<EAknExFormLabelMaxLength> iSecretLabel5;
        TBuf<EAknExFormLabelMaxLength> iSecretLabel6;
        TBuf<EAknExFormLabelMaxLength> iSliderLabel1;
        TBuf<EAknExFormLabelMaxLength> iSliderLabel2;
        TBuf<EAknExFormLabelMaxLength> iSliderLabel3;
        TInt                           iCurrentId;

    };

#endif  // AKNEXFORMSAVETESTFORM_H

// End of File
