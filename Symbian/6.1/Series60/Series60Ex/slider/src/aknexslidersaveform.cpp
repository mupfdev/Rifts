/*
* ============================================================================
*  Name     : CAknExSliderSaveForm.h
*  Part of  : AknExSlider
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#include <eikcapc.h>

// INCLUDE FILES
#include <aknslider.h> // for slider
#include "AknExSliderSaveForm.h"

// FUNCTION PROTOTYPES

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExSliderSaveForm::NewL()
// Two-phased constructor.
// ----------------------------------------------------------------------------
//
CAknExSliderSaveForm* CAknExSliderSaveForm::NewL()
    {
    CAknExSliderSaveForm* self = 
        new (ELeave) CAknExSliderSaveForm();
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop();
    return self;
    }

// ----------------------------------------------------------------------------
// CAknExSliderSaveForm::~CAknExSliderSaveForm()
// Destructor.
// ----------------------------------------------------------------------------
//
CAknExSliderSaveForm::~CAknExSliderSaveForm()
    {
    }


// ----------------------------------------------------------------------------
// CAknExSliderSaveForm::CAknExSliderSaveForm()
// Default constructor.
// ----------------------------------------------------------------------------
//
CAknExSliderSaveForm::CAknExSliderSaveForm()
    {
    }

// ----------------------------------------------------------------------------
// CAknExSliderSaveForm::ConstructL()
// Second-phase constructor.
// ----------------------------------------------------------------------------
//
void CAknExSliderSaveForm::ConstructL()
    {
    CAknForm::ConstructL();
    }

// ----------------------------------------------------------------------------
// CAknExSliderSaveForm::SetFormData()
// Set form data.
// ----------------------------------------------------------------------------
//
void CAknExSliderSaveForm::SetFormData()
    {
    }

// ----------------------------------------------------------------------------
// CAknExSliderSaveForm::SaveFormDataL()
// Save form data.
// ----------------------------------------------------------------------------
//
TBool CAknExSliderSaveForm::SaveFormDataL()
    {
    CAknSlider* slider = (CAknSlider*) ControlOrNull(EAknExSliderDlgId);
    if (slider)
        {
        iSliderValue = slider->Value();

        TPtrC sliderLabel = Line(EAknExSliderDlgId)->GetFullCaptionText();
        iSliderLabel = sliderLabel;
        }

    return ETrue;
    }

// ----------------------------------------------------------------------------
// CAknExSliderSaveForm::DoNotSaveFormDataL()
// Does not save form data.
// ----------------------------------------------------------------------------
//
void CAknExSliderSaveForm::DoNotSaveFormDataL()
    {
    CAknSlider* slider = (CAknSlider*) ControlOrNull(EAknExSliderDlgId);
    if (slider)
        {
        slider->SetValueL(iSliderValue);

        TRAPD(e, Line(EAknExSliderDlgId)->SetCaptionL(iSliderLabel));
        Line(EAknExSliderDlgId)->iCaption->CropText();
        }
    }

// ----------------------------------------------------------------------------
// CAknExSliderSaveForm::PostLayoutDynInitL()
// Set default field value to member data.
// ----------------------------------------------------------------------------
//
void CAknExSliderSaveForm::PostLayoutDynInitL()
    {
    CAknForm::PostLayoutDynInitL();
    SaveFormDataL();
    }

// ----------------------------------------------------------------------------
// CAknExSliderSaveForm::QuerySaveChangesL()
// Show save query. If user answers "No" to this query.
// return field value to the value which is before editing.
// This is called Back-softkey when edit mode.
// ----------------------------------------------------------------------------
//
TBool CAknExSliderSaveForm::QuerySaveChangesL()
    {
    TBool isAnsYes(CAknForm::QuerySaveChangesL());

    if (isAnsYes)
        {
        SaveFormDataL();
        }
    else 
        {
        // Case that answer "No" to query.
        DoNotSaveFormDataL();
        }

    return isAnsYes;
    }

// End of File
