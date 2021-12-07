/*
* ============================================================================
*  Name     : CAknExSliderSaveForm.h
*  Part of  : AknExSlider
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNEXSLIDERSAVETESTFORM_H
#define AKNEXSLIDERSAVETESTFORM_H

// INCLUDES
#include <aknform.h>
#include "AknExSlider.hrh"

// CONSTANTS
const TInt KAknExSliderLabelMaxLength = 64;

// CLASS DECLARATION

/**
* CAknExFormApplication application class.
* Provides factory to create concrete document object.
*/
class CAknExSliderSaveForm : public CAknForm
    {
    public:  // Constructor and destructor  
        /**
        * Two-phased constructor.
        */
        static CAknExSliderSaveForm* NewL();

        /**
        * Destructor.
        */
        virtual ~CAknExSliderSaveForm();

    private:  // Constructor
        /**
        * Default constructor.
        */
        CAknExSliderSaveForm();

        /**
        * Second-phase constructor.
        */
        void ConstructL();
    
    private:  // New functons
        /**
        * Set form data.
        */
        void SetFormData();
    
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
        TInt                             iSliderValue;
        TBuf<KAknExSliderLabelMaxLength> iSliderLabel;

    };

#endif  // AKNEXSLIDERSAVETESTFORM_H

// End of File
