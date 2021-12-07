/*
* ============================================================================
*  Name     : CAknExFormSaveForm.h
*  Part of  : AknExForm
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include <eikcapc.h>
#include <eikseced.h>  // for secret editor
#include <aknslider.h> // for slider
#include <aknexform.rsg>
#include "AknExFormSaveForm.h"

// FUNCTION PROTOTYPES

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExFormSaveForm::NewL()
// Two-phased constructor.
// ----------------------------------------------------------------------------
//
CAknExFormSaveForm* CAknExFormSaveForm::NewL()
    {
    CAknExFormSaveForm* self = 
        new (ELeave) CAknExFormSaveForm();
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop();
    return self;
    }

// ----------------------------------------------------------------------------
// CAknExFormSaveForm::~CAknExFormSaveForm()
// Destructor.
// ----------------------------------------------------------------------------
//
CAknExFormSaveForm::~CAknExFormSaveForm()
    {
    }


// ----------------------------------------------------------------------------
// CAknExFormSaveForm::CAknExFormSaveForm()
// Default constructor.
// ----------------------------------------------------------------------------
//
CAknExFormSaveForm::CAknExFormSaveForm()
    {
    }

// ----------------------------------------------------------------------------
// CAknExFormSaveForm::ConstructL()
// Second-phase constructor.
// ----------------------------------------------------------------------------
//
void CAknExFormSaveForm::ConstructL()
    {
    CAknForm::ConstructL();
    }

// ----------------------------------------------------------------------------
// CAknExFormSaveForm::ExecuteLD( TInt aResourceId )
// 
// ----------------------------------------------------------------------------
//
TInt CAknExFormSaveForm::ExecuteLD( TInt aResourceId )
    {
    iCurrentId = aResourceId;

    return CAknForm::ExecuteLD( aResourceId );
    }

// ----------------------------------------------------------------------------
// CAknExFormSaveForm::PrepareLC( TInt aResourceId )
// 
// ----------------------------------------------------------------------------
//
void CAknExFormSaveForm::PrepareLC( TInt aResourceId )
    {
    iCurrentId = aResourceId;

    CAknForm::PrepareLC( aResourceId );
    }

// ----------------------------------------------------------------------------
// CAknExFormSaveForm::SaveFormDataL()
// Save form data.
// ----------------------------------------------------------------------------
//
TBool CAknExFormSaveForm::SaveFormDataL()
    {
    switch (iCurrentId)
        {
        case R_AKNEXFORM_TEXT_NUMBER_FIELD_DIALOG:
            {
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin01))
                {
                GetEdwinText(iEdwinData1, EAknExFormDlgCtrlIdEdwin01);
                TPtrC edwinLabel = Line(EAknExFormDlgCtrlIdEdwin01)->GetFullCaptionText();
                iEdwinLabel1 = edwinLabel;
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdNumber01))
                {
                iNumberData1 = NumberEditorValue(EAknExFormDlgCtrlIdNumber01);
                TPtrC numberLabel = Line(EAknExFormDlgCtrlIdNumber01)->GetFullCaptionText();
                iNumberLabel1 = numberLabel;
                }
            }
            break;
        case R_AKNEXFORM_MANY_ROW_FIELD_DIALOG:
            {
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin01))
                {
                GetEdwinText(iEdwinData1, EAknExFormDlgCtrlIdEdwin01);
                TPtrC edwinLabel1 = Line(EAknExFormDlgCtrlIdEdwin01)->GetFullCaptionText();
                iEdwinLabel1 = edwinLabel1;
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin02))
                {
                GetEdwinText(iEdwinData2, EAknExFormDlgCtrlIdEdwin02);
                TPtrC edwinLabel2 = Line(EAknExFormDlgCtrlIdEdwin02)->GetFullCaptionText();
                iEdwinLabel2 = edwinLabel2;
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin03))
                {
                GetEdwinText(iEdwinData3, EAknExFormDlgCtrlIdEdwin03);
                TPtrC edwinLabel3 = Line(EAknExFormDlgCtrlIdEdwin03)->GetFullCaptionText();
                iEdwinLabel3 = edwinLabel3;
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin04))
                {
                GetEdwinText(iEdwinData4, EAknExFormDlgCtrlIdEdwin04);
                TPtrC edwinLabel4 = Line(EAknExFormDlgCtrlIdEdwin04)->GetFullCaptionText();
                iEdwinLabel4 = edwinLabel4;
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin05))
                {
                GetEdwinText(iEdwinData5, EAknExFormDlgCtrlIdEdwin05);
                TPtrC edwinLabel5 = Line(EAknExFormDlgCtrlIdEdwin05)->GetFullCaptionText();
                iEdwinLabel5 = edwinLabel5;
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin06))
                {
                GetEdwinText(iEdwinData6, EAknExFormDlgCtrlIdEdwin06);
                TPtrC edwinLabel6 = Line(EAknExFormDlgCtrlIdEdwin06)->GetFullCaptionText();
                iEdwinLabel6 = edwinLabel6;
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin07))
                {
                GetEdwinText(iEdwinData7, EAknExFormDlgCtrlIdEdwin07);
                TPtrC edwinLabel7 = Line(EAknExFormDlgCtrlIdEdwin07)->GetFullCaptionText();
                iEdwinLabel7 = edwinLabel7;
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin08))
                {
                GetEdwinText(iEdwinData8, EAknExFormDlgCtrlIdEdwin08);
                TPtrC edwinLabel8 = Line(EAknExFormDlgCtrlIdEdwin08)->GetFullCaptionText();
                iEdwinLabel8 = edwinLabel8;
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin09))
                {
                GetEdwinText(iEdwinData9, EAknExFormDlgCtrlIdEdwin09);
                TPtrC edwinLabel9 = Line(EAknExFormDlgCtrlIdEdwin09)->GetFullCaptionText();
                iEdwinLabel9 = edwinLabel9;
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin10))
                {
                GetEdwinText(iEdwinData10, EAknExFormDlgCtrlIdEdwin10);
                TPtrC edwinLabel10 = Line(EAknExFormDlgCtrlIdEdwin10)->GetFullCaptionText();
                iEdwinLabel10 = edwinLabel10;
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin11))
                {
                GetEdwinText(iEdwinData11, EAknExFormDlgCtrlIdEdwin11);
                TPtrC edwinLabel11 = Line(EAknExFormDlgCtrlIdEdwin11)->GetFullCaptionText();
                iEdwinLabel11 = edwinLabel11;
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin12))
                {
                GetEdwinText(iEdwinData12, EAknExFormDlgCtrlIdEdwin12);
                TPtrC edwinLabel12 = Line(EAknExFormDlgCtrlIdEdwin12)->GetFullCaptionText();
                iEdwinLabel12 = edwinLabel12;
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin13))
                {
                GetEdwinText(iEdwinData13, EAknExFormDlgCtrlIdEdwin13);
                TPtrC edwinLabel13 = Line(EAknExFormDlgCtrlIdEdwin13)->GetFullCaptionText();
                iEdwinLabel13 = edwinLabel13;
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin14))
                {
                GetEdwinText(iEdwinData14, EAknExFormDlgCtrlIdEdwin14);
                TPtrC edwinLabel14 = Line(EAknExFormDlgCtrlIdEdwin14)->GetFullCaptionText();
                iEdwinLabel14 = edwinLabel14;
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin15))
                {
                GetEdwinText(iEdwinData15, EAknExFormDlgCtrlIdEdwin15);
                TPtrC edwinLabel15 = Line(EAknExFormDlgCtrlIdEdwin15)->GetFullCaptionText();
                iEdwinLabel15 = edwinLabel15;
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin16))
                {
                GetEdwinText(iEdwinData16, EAknExFormDlgCtrlIdEdwin16);
                TPtrC edwinLabel16 = Line(EAknExFormDlgCtrlIdEdwin16)->GetFullCaptionText();
                iEdwinLabel16 = edwinLabel16;
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin17))
                {
                GetEdwinText(iEdwinData17, EAknExFormDlgCtrlIdEdwin17);
                TPtrC edwinLabel17 = Line(EAknExFormDlgCtrlIdEdwin17)->GetFullCaptionText();
                iEdwinLabel17 = edwinLabel17;
                }
            }
            break;
        case R_AKNEXFORM_NAVIPANE_DIALOG:
            {
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin01))
                {
                GetEdwinText(iEdwinData1, EAknExFormDlgCtrlIdEdwin01);
                TPtrC edwinLabel1 = Line(EAknExFormDlgCtrlIdEdwin01)->GetFullCaptionText();
                iEdwinLabel1 = edwinLabel1;
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin02))
                {
                GetEdwinText(iEdwinData2, EAknExFormDlgCtrlIdEdwin02);
                TPtrC edwinLabel2 = Line(EAknExFormDlgCtrlIdEdwin02)->GetFullCaptionText();
                iEdwinLabel2 = edwinLabel2;
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin03))
                {
                GetEdwinText(iEdwinData3, EAknExFormDlgCtrlIdEdwin03);
                TPtrC edwinLabel3 = Line(EAknExFormDlgCtrlIdEdwin03)->GetFullCaptionText();
                iEdwinLabel3 = edwinLabel3;
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdNumber01))
                {
                iNumberData1 = NumberEditorValue(EAknExFormDlgCtrlIdNumber01);
                TPtrC numberLabel = Line(EAknExFormDlgCtrlIdNumber01)->GetFullCaptionText();
                iNumberLabel1 = numberLabel;
                }
            }
            break;
        case R_AKNEXFORM_TEXT_NUMBER_WITH_ICON_DIALOG:
            {
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin01))
                {
                GetEdwinText(iEdwinData1, EAknExFormDlgCtrlIdEdwin01);
                TPtrC edwinLabel1 = Line(EAknExFormDlgCtrlIdEdwin01)->GetFullCaptionText();
                iEdwinLabel1 = edwinLabel1;
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdNumber01))
                {
                iNumberData1 = NumberEditorValue(EAknExFormDlgCtrlIdNumber01);
                TPtrC numberLabel1 = Line(EAknExFormDlgCtrlIdNumber01)->GetFullCaptionText();
                iNumberLabel1 = numberLabel1;
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin02))
                {
                GetEdwinText(iEdwinData2, EAknExFormDlgCtrlIdEdwin02);
                TPtrC edwinLabel2 = Line(EAknExFormDlgCtrlIdEdwin02)->GetFullCaptionText();
                iEdwinLabel2 = edwinLabel2;
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdNumber02))
                {
                iNumberData2 = NumberEditorValue(EAknExFormDlgCtrlIdNumber02);
                TPtrC numberLabel2 = Line(EAknExFormDlgCtrlIdNumber02)->GetFullCaptionText();
                iNumberLabel2 = numberLabel2;
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin03))
                {
                GetEdwinText(iEdwinData3, EAknExFormDlgCtrlIdEdwin03);
                TPtrC edwinLabel3 = Line(EAknExFormDlgCtrlIdEdwin03)->GetFullCaptionText();
                iEdwinLabel3 = edwinLabel3;
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdNumber03))
                {
                iNumberData3 = NumberEditorValue(EAknExFormDlgCtrlIdNumber03);
                TPtrC numberLabel3 = Line(EAknExFormDlgCtrlIdNumber03)->GetFullCaptionText();
                iNumberLabel3 = numberLabel3;
                }
            }
            break;
        case R_AKNEXFORM_ALL_EDITOR_FIELD_DIALOG:
            {
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin01))
                {
                GetEdwinText(iEdwinData1, EAknExFormDlgCtrlIdEdwin01);
                TPtrC edwinLabel = Line(EAknExFormDlgCtrlIdEdwin01)->GetFullCaptionText();
                iEdwinLabel1 = edwinLabel;
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdNumber01))
                {
                iNumberData1 = NumberEditorValue(EAknExFormDlgCtrlIdNumber01);
                TPtrC numberLabel = Line(EAknExFormDlgCtrlIdNumber01)->GetFullCaptionText();
                iNumberLabel1 = numberLabel;
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdDate01))
                {
                iDateData1 = TTimeEditorValue(EAknExFormDlgCtrlIdDate01);
                TPtrC dateLabel = Line(EAknExFormDlgCtrlIdDate01)->GetFullCaptionText();
                iDateLabel1 = dateLabel;
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdTime01))
                {
                iTimeData1 = TTimeEditorValue(EAknExFormDlgCtrlIdTime01);
                TPtrC timeLabel = Line(EAknExFormDlgCtrlIdTime01)->GetFullCaptionText();
                iTimeLabel1 = timeLabel;
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdDuration01))
                {
                iDurationData1 = DurationEditorValue(EAknExFormDlgCtrlIdDuration01);
                TPtrC durationLabel = Line(EAknExFormDlgCtrlIdDuration01)->GetFullCaptionText();
                iDurationLabel1 = durationLabel;
                }
            CEikSecretEditor* secretEd = (CEikSecretEditor*) ControlOrNull(EAknExFormDlgCtrlIdSecret01);
            if (secretEd)
                {
                secretEd->GetText(iSecretData1);
                TPtrC secretLabel = Line(EAknExFormDlgCtrlIdSecret01)->GetFullCaptionText();
                iSecretLabel1 = secretLabel;
                }
            }
            break;
        case R_AKNEXFORM_SEPARATOR_FIELD_DIALOG:
            {
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin01))
                {
                GetEdwinText(iEdwinData1, EAknExFormDlgCtrlIdEdwin01);
                TPtrC edwinLabel1 = Line(EAknExFormDlgCtrlIdEdwin01)->GetFullCaptionText();
                iEdwinLabel1 = edwinLabel1;
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin02))
                {
                GetEdwinText(iEdwinData2, EAknExFormDlgCtrlIdEdwin02);
                TPtrC edwinLabel2 = Line(EAknExFormDlgCtrlIdEdwin02)->GetFullCaptionText();
                iEdwinLabel2 = edwinLabel2;
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin03))
                {
                GetEdwinText(iEdwinData3, EAknExFormDlgCtrlIdEdwin03);
                TPtrC edwinLabel3 = Line(EAknExFormDlgCtrlIdEdwin03)->GetFullCaptionText();
                iEdwinLabel3 = edwinLabel3;
                }
            }
            break;
        case R_AKNEXFORM_TEXT_FIELD_DIALOG:
            {
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin01))
                {
                GetEdwinText(iEdwinData1, EAknExFormDlgCtrlIdEdwin01);
                TPtrC edwinLabel1 = Line(EAknExFormDlgCtrlIdEdwin01)->GetFullCaptionText();
                iEdwinLabel1 = edwinLabel1;
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin02))
                {
                GetEdwinText(iEdwinData2, EAknExFormDlgCtrlIdEdwin02);
                TPtrC edwinLabel2 = Line(EAknExFormDlgCtrlIdEdwin02)->GetFullCaptionText();
                iEdwinLabel2 = edwinLabel2;
                }
            }
            break;
        case R_AKNEXFORM_THREE_SLIDER_FIELD_DIALOG:
            {
            CAknSlider* slider1 = (CAknSlider*) ControlOrNull(EAknExFormDlgCtrlIdSlider01);
            if (slider1)
                {
                iSliderData1 = slider1->Value();
                TPtrC sliderLabel1 = Line(EAknExFormDlgCtrlIdSlider01)->GetFullCaptionText();
                iSliderLabel1 = sliderLabel1;
                }
            CAknSlider* slider2 = (CAknSlider*) ControlOrNull(EAknExFormDlgCtrlIdSlider02);
            if (slider2)
                {
                iSliderData1 = slider2->Value();
                TPtrC sliderLabel2 = Line(EAknExFormDlgCtrlIdSlider02)->GetFullCaptionText();
                iSliderLabel2 = sliderLabel2;
                }
            CAknSlider* slider3 = (CAknSlider*) ControlOrNull(EAknExFormDlgCtrlIdSlider03);
            if (slider3)
                {
                iSliderData1 = slider3->Value();
                TPtrC sliderLabel3 = Line(EAknExFormDlgCtrlIdSlider03)->GetFullCaptionText();
                iSliderLabel3 = sliderLabel3;
                }
            }
            break;
        case R_AKNEXFORM_NAVIGATE_SIX_PAGES_DIALOG:
            {
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin01))
                {
                GetEdwinText(iEdwinData1, EAknExFormDlgCtrlIdEdwin01);
                TPtrC edwinLabel1 = Line(EAknExFormDlgCtrlIdEdwin01)->GetFullCaptionText();
                iEdwinLabel1 = edwinLabel1;
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin02))
                {
                GetEdwinText(iEdwinData2, EAknExFormDlgCtrlIdEdwin02);
                TPtrC edwinLabel2 = Line(EAknExFormDlgCtrlIdEdwin02)->GetFullCaptionText();
                iEdwinLabel2 = edwinLabel2;
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin03))
                {
                GetEdwinText(iEdwinData3, EAknExFormDlgCtrlIdEdwin03);
                TPtrC edwinLabel3 = Line(EAknExFormDlgCtrlIdEdwin03)->GetFullCaptionText();
                iEdwinLabel3 = edwinLabel3;
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin04))
                {
                GetEdwinText(iEdwinData4, EAknExFormDlgCtrlIdEdwin04);
                TPtrC edwinLabel4 = Line(EAknExFormDlgCtrlIdEdwin04)->GetFullCaptionText();
                iEdwinLabel4 = edwinLabel4;
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin05))
                {
                GetEdwinText(iEdwinData5, EAknExFormDlgCtrlIdEdwin05);
                TPtrC edwinLabel5 = Line(EAknExFormDlgCtrlIdEdwin05)->GetFullCaptionText();
                iEdwinLabel5 = edwinLabel5;
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin06))
                {
                GetEdwinText(iEdwinData6, EAknExFormDlgCtrlIdEdwin06);
                TPtrC edwinLabel6 = Line(EAknExFormDlgCtrlIdEdwin06)->GetFullCaptionText();
                iEdwinLabel6 = edwinLabel6;
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdNumber01))
                {
                iNumberData1 = NumberEditorValue(EAknExFormDlgCtrlIdNumber01);
                TPtrC numberLabel1 = Line(EAknExFormDlgCtrlIdNumber01)->GetFullCaptionText();
                iNumberLabel1 = numberLabel1;
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdNumber02))
                {
                iNumberData2 = NumberEditorValue(EAknExFormDlgCtrlIdNumber02);
                TPtrC numberLabel2 = Line(EAknExFormDlgCtrlIdNumber02)->GetFullCaptionText();
                iNumberLabel2 = numberLabel2;
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdNumber03))
                {
                iNumberData3 = NumberEditorValue(EAknExFormDlgCtrlIdNumber03);
                TPtrC numberLabel3 = Line(EAknExFormDlgCtrlIdNumber03)->GetFullCaptionText();
                iNumberLabel3 = numberLabel3;
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdNumber04))
                {
                iNumberData4 = NumberEditorValue(EAknExFormDlgCtrlIdNumber04);
                TPtrC numberLabel4 = Line(EAknExFormDlgCtrlIdNumber04)->GetFullCaptionText();
                iNumberLabel4 = numberLabel4;
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdNumber05))
                {
                iNumberData5 = NumberEditorValue(EAknExFormDlgCtrlIdNumber05);
                TPtrC numberLabel5 = Line(EAknExFormDlgCtrlIdNumber05)->GetFullCaptionText();
                iNumberLabel5 = numberLabel5;
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdNumber06))
                {
                iNumberData6 = NumberEditorValue(EAknExFormDlgCtrlIdNumber06);
                TPtrC numberLabel6 = Line(EAknExFormDlgCtrlIdNumber06)->GetFullCaptionText();
                iNumberLabel6 = numberLabel6;
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdDate01))
                {
                iDateData1 = TTimeEditorValue(EAknExFormDlgCtrlIdDate01);
                TPtrC dateLabel1 = Line(EAknExFormDlgCtrlIdDate01)->GetFullCaptionText();
                iDateLabel1 = dateLabel1;
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdDate02))
                {
                iDateData2 = TTimeEditorValue(EAknExFormDlgCtrlIdDate02);
                TPtrC dateLabel2 = Line(EAknExFormDlgCtrlIdDate02)->GetFullCaptionText();
                iDateLabel2 = dateLabel2;
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdDate03))
                {
                iDateData3 = TTimeEditorValue(EAknExFormDlgCtrlIdDate03);
                TPtrC dateLabel3 = Line(EAknExFormDlgCtrlIdDate03)->GetFullCaptionText();
                iDateLabel3 = dateLabel3;
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdDate04))
                {
                iDateData4 = TTimeEditorValue(EAknExFormDlgCtrlIdDate04);
                TPtrC dateLabel4 = Line(EAknExFormDlgCtrlIdDate04)->GetFullCaptionText();
                iDateLabel4 = dateLabel4;
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdDate05))
                {
                iDateData5 = TTimeEditorValue(EAknExFormDlgCtrlIdDate05);
                TPtrC dateLabel5 = Line(EAknExFormDlgCtrlIdDate05)->GetFullCaptionText();
                iDateLabel5 = dateLabel5;
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdDate06))
                {
                iDateData6 = TTimeEditorValue(EAknExFormDlgCtrlIdDate06);
                TPtrC dateLabel6 = Line(EAknExFormDlgCtrlIdDate06)->GetFullCaptionText();
                iDateLabel6 = dateLabel6;
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdTime01))
                {
                iTimeData1 = TTimeEditorValue(EAknExFormDlgCtrlIdTime01);
                TPtrC timeLabel1 = Line(EAknExFormDlgCtrlIdTime01)->GetFullCaptionText();
                iTimeLabel1 = timeLabel1;
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdTime02))
                {
                iTimeData2 = TTimeEditorValue(EAknExFormDlgCtrlIdTime02);
                TPtrC timeLabel2 = Line(EAknExFormDlgCtrlIdTime02)->GetFullCaptionText();
                iTimeLabel2 = timeLabel2;
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdTime03))
                {
                iTimeData3 = TTimeEditorValue(EAknExFormDlgCtrlIdTime03);
                TPtrC timeLabel3 = Line(EAknExFormDlgCtrlIdTime03)->GetFullCaptionText();
                iTimeLabel3 = timeLabel3;
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdTime04))
                {
                iTimeData4 = TTimeEditorValue(EAknExFormDlgCtrlIdTime04);
                TPtrC timeLabel4 = Line(EAknExFormDlgCtrlIdTime04)->GetFullCaptionText();
                iTimeLabel4 = timeLabel4;
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdTime05))
                {
                iTimeData5 = TTimeEditorValue(EAknExFormDlgCtrlIdTime05);
                TPtrC timeLabel5 = Line(EAknExFormDlgCtrlIdTime05)->GetFullCaptionText();
                iTimeLabel5 = timeLabel5;
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdTime06))
                {
                iTimeData6 = TTimeEditorValue(EAknExFormDlgCtrlIdTime06);
                TPtrC timeLabel6 = Line(EAknExFormDlgCtrlIdTime06)->GetFullCaptionText();
                iTimeLabel6 = timeLabel6;
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdDuration01))
                {
                iDurationData1 = DurationEditorValue(EAknExFormDlgCtrlIdDuration01);
                TPtrC durationLabel1 = Line(EAknExFormDlgCtrlIdDuration01)->GetFullCaptionText();
                iDurationLabel1 = durationLabel1;
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdDuration02))
                {
                iDurationData2 = DurationEditorValue(EAknExFormDlgCtrlIdDuration02);
                TPtrC durationLabel2 = Line(EAknExFormDlgCtrlIdDuration02)->GetFullCaptionText();
                iDurationLabel2 = durationLabel2;
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdDuration03))
                {
                iDurationData3 = DurationEditorValue(EAknExFormDlgCtrlIdDuration03);
                TPtrC durationLabel3 = Line(EAknExFormDlgCtrlIdDuration03)->GetFullCaptionText();
                iDurationLabel3 = durationLabel3;
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdDuration04))
                {
                iDurationData4 = DurationEditorValue(EAknExFormDlgCtrlIdDuration04);
                TPtrC durationLabel4 = Line(EAknExFormDlgCtrlIdDuration04)->GetFullCaptionText();
                iDurationLabel4 = durationLabel4;
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdDuration05))
                {
                iDurationData5 = DurationEditorValue(EAknExFormDlgCtrlIdDuration05);
                TPtrC durationLabel5 = Line(EAknExFormDlgCtrlIdDuration05)->GetFullCaptionText();
                iDurationLabel5 = durationLabel5;
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdDuration06))
                {
                iDurationData6 = DurationEditorValue(EAknExFormDlgCtrlIdDuration06);
                TPtrC durationLabel6 = Line(EAknExFormDlgCtrlIdDuration06)->GetFullCaptionText();
                iDurationLabel6 = durationLabel6;
                }
            CEikSecretEditor* secretEd1 = (CEikSecretEditor*) ControlOrNull(EAknExFormDlgCtrlIdSecret01);
            if (secretEd1)
                {
                secretEd1->GetText(iSecretData1);
                TPtrC secretLabel1 = Line(EAknExFormDlgCtrlIdSecret01)->GetFullCaptionText();
                iSecretLabel1 = secretLabel1;
                }
            CEikSecretEditor* secretEd2 = (CEikSecretEditor*) ControlOrNull(EAknExFormDlgCtrlIdSecret02);
            if (secretEd2)
                {
                secretEd2->GetText(iSecretData2);
                TPtrC secretLabel2 = Line(EAknExFormDlgCtrlIdSecret02)->GetFullCaptionText();
                iSecretLabel2 = secretLabel2;
                }
            CEikSecretEditor* secretEd3 = (CEikSecretEditor*) ControlOrNull(EAknExFormDlgCtrlIdSecret03);
            if (secretEd3)
                {
                secretEd3->GetText(iSecretData3);
                TPtrC secretLabel3 = Line(EAknExFormDlgCtrlIdSecret03)->GetFullCaptionText();
                iSecretLabel3 = secretLabel3;
                }
            CEikSecretEditor* secretEd4 = (CEikSecretEditor*) ControlOrNull(EAknExFormDlgCtrlIdSecret04);
            if (secretEd4)
                {
                secretEd4->GetText(iSecretData4);
                TPtrC secretLabel4 = Line(EAknExFormDlgCtrlIdSecret04)->GetFullCaptionText();
                iSecretLabel4 = secretLabel4;
                }
            CEikSecretEditor* secretEd5 = (CEikSecretEditor*) ControlOrNull(EAknExFormDlgCtrlIdSecret05);
            if (secretEd5)
                {
                secretEd5->GetText(iSecretData5);
                TPtrC secretLabel5 = Line(EAknExFormDlgCtrlIdSecret05)->GetFullCaptionText();
                iSecretLabel5 = secretLabel5;
                }
            CEikSecretEditor* secretEd6 = (CEikSecretEditor*) ControlOrNull(EAknExFormDlgCtrlIdSecret06);
            if (secretEd6)
                {
                secretEd6->GetText(iSecretData6);
                TPtrC secretLabel6 = Line(EAknExFormDlgCtrlIdSecret06)->GetFullCaptionText();
                iSecretLabel6 = secretLabel6;
                }
            }
            break;
        case R_AKNEXFORM_DOUBLE_AND_SINGLE_LINE_FORM:
            {
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin01))
                {
                GetEdwinText(iEdwinData1, EAknExFormDlgCtrlIdEdwin01);
                TPtrC edwinLabel1 = Line(EAknExFormDlgCtrlIdEdwin01)->GetFullCaptionText();
                iEdwinLabel1 = edwinLabel1;
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin02))
                {
                GetEdwinText(iEdwinData2, EAknExFormDlgCtrlIdEdwin02);
                TPtrC edwinLabel2 = Line(EAknExFormDlgCtrlIdEdwin02)->GetFullCaptionText();
                iEdwinLabel2 = edwinLabel2;
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin03))
                {
                GetEdwinText(iEdwinData3, EAknExFormDlgCtrlIdEdwin03);
                TPtrC edwinLabel3 = Line(EAknExFormDlgCtrlIdEdwin03)->GetFullCaptionText();
                iEdwinLabel3 = edwinLabel3;
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin11))
                {
                GetEdwinText(iEdwinData4, EAknExFormDlgCtrlIdEdwin11);
                TPtrC edwinLabel4 = Line(EAknExFormDlgCtrlIdEdwin11)->GetFullCaptionText();
                iEdwinLabel4 = edwinLabel4;
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdNumber01))
                {
                iNumberData1 = NumberEditorValue(EAknExFormDlgCtrlIdNumber01);
                TPtrC numberLabel1 = Line(EAknExFormDlgCtrlIdNumber01)->GetFullCaptionText();
                iNumberLabel1 = numberLabel1;
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdNumber02))
                {
                iNumberData2 = NumberEditorValue(EAknExFormDlgCtrlIdNumber02);
                TPtrC numberLabel2 = Line(EAknExFormDlgCtrlIdNumber02)->GetFullCaptionText();
                iNumberLabel2 = numberLabel2;
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdNumber03))
                {
                iNumberData3 = NumberEditorValue(EAknExFormDlgCtrlIdNumber03);
                TPtrC numberLabel3 = Line(EAknExFormDlgCtrlIdNumber03)->GetFullCaptionText();
                iNumberLabel3 = numberLabel3;
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdNumber06))
                {
                iNumberData4 = NumberEditorValue(EAknExFormDlgCtrlIdNumber06);
                TPtrC numberLabel4 = Line(EAknExFormDlgCtrlIdNumber06)->GetFullCaptionText();
                iNumberLabel4 = numberLabel4;
                }
            }
            break;
        default:
            break;
        }

    return ETrue;
    }

// ----------------------------------------------------------------------------
// CAknExFormSaveForm::DoNotSaveFormDataL()
// Does not save form data.
// ----------------------------------------------------------------------------
//
void CAknExFormSaveForm::DoNotSaveFormDataL()
    {
    switch (iCurrentId)
        {
        case R_AKNEXFORM_TEXT_NUMBER_FIELD_DIALOG:
            {
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin01))
                {
                SetEdwinTextL(EAknExFormDlgCtrlIdEdwin01, &iEdwinData1);
                Line(EAknExFormDlgCtrlIdEdwin01)->SetCaptionL(iEdwinLabel1);
                Line(EAknExFormDlgCtrlIdEdwin01)->iCaption->CropText();
                }

            if (ControlOrNull(EAknExFormDlgCtrlIdNumber01))
                {
                SetNumberEditorValue(EAknExFormDlgCtrlIdNumber01, iNumberData1);
                Line(EAknExFormDlgCtrlIdNumber01)->SetCaptionL(iNumberLabel1);
                Line(EAknExFormDlgCtrlIdNumber01)->iCaption->CropText();
                }
            }
            break;
        case R_AKNEXFORM_MANY_ROW_FIELD_DIALOG:
            {
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin01))
                {
                SetEdwinTextL(EAknExFormDlgCtrlIdEdwin01, &iEdwinData1);
                Line(EAknExFormDlgCtrlIdEdwin01)->SetCaptionL(iEdwinLabel1);
                Line(EAknExFormDlgCtrlIdEdwin01)->iCaption->CropText();
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin02))
                {
                SetEdwinTextL(EAknExFormDlgCtrlIdEdwin02, &iEdwinData2);
                Line(EAknExFormDlgCtrlIdEdwin02)->SetCaptionL(iEdwinLabel2);
                Line(EAknExFormDlgCtrlIdEdwin02)->iCaption->CropText();
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin03))
                {
                SetEdwinTextL(EAknExFormDlgCtrlIdEdwin03, &iEdwinData3);
                Line(EAknExFormDlgCtrlIdEdwin03)->SetCaptionL(iEdwinLabel3);
                Line(EAknExFormDlgCtrlIdEdwin03)->iCaption->CropText();
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin04))
                {
                SetEdwinTextL(EAknExFormDlgCtrlIdEdwin04, &iEdwinData4);
                Line(EAknExFormDlgCtrlIdEdwin04)->SetCaptionL(iEdwinLabel4);
                Line(EAknExFormDlgCtrlIdEdwin04)->iCaption->CropText();
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin05))
                {
                SetEdwinTextL(EAknExFormDlgCtrlIdEdwin05, &iEdwinData5);
                Line(EAknExFormDlgCtrlIdEdwin05)->SetCaptionL(iEdwinLabel5);
                Line(EAknExFormDlgCtrlIdEdwin05)->iCaption->CropText();
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin06))
                {
                SetEdwinTextL(EAknExFormDlgCtrlIdEdwin06, &iEdwinData6);
                Line(EAknExFormDlgCtrlIdEdwin06)->SetCaptionL(iEdwinLabel6);
                Line(EAknExFormDlgCtrlIdEdwin06)->iCaption->CropText();
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin07))
                {
                SetEdwinTextL(EAknExFormDlgCtrlIdEdwin07, &iEdwinData7);
                Line(EAknExFormDlgCtrlIdEdwin07)->SetCaptionL(iEdwinLabel7);
                Line(EAknExFormDlgCtrlIdEdwin07)->iCaption->CropText();
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin08))
                {
                SetEdwinTextL(EAknExFormDlgCtrlIdEdwin08, &iEdwinData8);
                Line(EAknExFormDlgCtrlIdEdwin08)->SetCaptionL(iEdwinLabel8);
                Line(EAknExFormDlgCtrlIdEdwin08)->iCaption->CropText();
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin09))
                {
                SetEdwinTextL(EAknExFormDlgCtrlIdEdwin09, &iEdwinData9);
                Line(EAknExFormDlgCtrlIdEdwin09)->SetCaptionL(iEdwinLabel9);
                Line(EAknExFormDlgCtrlIdEdwin09)->iCaption->CropText();
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin10))
                {
                SetEdwinTextL(EAknExFormDlgCtrlIdEdwin10, &iEdwinData10);
                Line(EAknExFormDlgCtrlIdEdwin10)->SetCaptionL(iEdwinLabel10);
                Line(EAknExFormDlgCtrlIdEdwin10)->iCaption->CropText();
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin11))
                {
                SetEdwinTextL(EAknExFormDlgCtrlIdEdwin11, &iEdwinData11);
                Line(EAknExFormDlgCtrlIdEdwin11)->SetCaptionL(iEdwinLabel11);
                Line(EAknExFormDlgCtrlIdEdwin11)->iCaption->CropText();
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin12))
                {
                SetEdwinTextL(EAknExFormDlgCtrlIdEdwin12, &iEdwinData12);
                Line(EAknExFormDlgCtrlIdEdwin12)->SetCaptionL(iEdwinLabel12);
                Line(EAknExFormDlgCtrlIdEdwin12)->iCaption->CropText();
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin13))
                {
                SetEdwinTextL(EAknExFormDlgCtrlIdEdwin13, &iEdwinData13);
                Line(EAknExFormDlgCtrlIdEdwin13)->SetCaptionL(iEdwinLabel13);
                Line(EAknExFormDlgCtrlIdEdwin13)->iCaption->CropText();
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin14))
                {
                SetEdwinTextL(EAknExFormDlgCtrlIdEdwin14, &iEdwinData14);
                Line(EAknExFormDlgCtrlIdEdwin14)->SetCaptionL(iEdwinLabel14);
                Line(EAknExFormDlgCtrlIdEdwin14)->iCaption->CropText();
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin15))
                {
                SetEdwinTextL(EAknExFormDlgCtrlIdEdwin15, &iEdwinData15);
                Line(EAknExFormDlgCtrlIdEdwin15)->SetCaptionL(iEdwinLabel15);
                Line(EAknExFormDlgCtrlIdEdwin15)->iCaption->CropText();
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin16))
                {
                SetEdwinTextL(EAknExFormDlgCtrlIdEdwin16, &iEdwinData16);
                Line(EAknExFormDlgCtrlIdEdwin16)->SetCaptionL(iEdwinLabel16);
                Line(EAknExFormDlgCtrlIdEdwin16)->iCaption->CropText();
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin17))
                {
                SetEdwinTextL(EAknExFormDlgCtrlIdEdwin17, &iEdwinData17);
                Line(EAknExFormDlgCtrlIdEdwin17)->SetCaptionL(iEdwinLabel17);
                Line(EAknExFormDlgCtrlIdEdwin17)->iCaption->CropText();
                }
            }
            break;
        case R_AKNEXFORM_NAVIPANE_DIALOG:
            {
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin01))
                {
                SetEdwinTextL(EAknExFormDlgCtrlIdEdwin01, &iEdwinData1);
                Line(EAknExFormDlgCtrlIdEdwin01)->SetCaptionL(iEdwinLabel1);
                Line(EAknExFormDlgCtrlIdEdwin01)->iCaption->CropText();
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin02))
                {
                SetEdwinTextL(EAknExFormDlgCtrlIdEdwin02, &iEdwinData2);
                Line(EAknExFormDlgCtrlIdEdwin02)->SetCaptionL(iEdwinLabel2);
                Line(EAknExFormDlgCtrlIdEdwin02)->iCaption->CropText();
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin03))
                {
                SetEdwinTextL(EAknExFormDlgCtrlIdEdwin03, &iEdwinData3);
                Line(EAknExFormDlgCtrlIdEdwin03)->SetCaptionL(iEdwinLabel3);
                Line(EAknExFormDlgCtrlIdEdwin03)->iCaption->CropText();
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdNumber01))
                {
                SetNumberEditorValue(EAknExFormDlgCtrlIdNumber01, iNumberData1);
                Line(EAknExFormDlgCtrlIdNumber01)->SetCaptionL(iNumberLabel1);
                Line(EAknExFormDlgCtrlIdNumber01)->iCaption->CropText();
                }
            }
            break;
        case R_AKNEXFORM_TEXT_NUMBER_WITH_ICON_DIALOG:
            {
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin01))
                {
                SetEdwinTextL(EAknExFormDlgCtrlIdEdwin01, &iEdwinData1);
                Line(EAknExFormDlgCtrlIdEdwin01)->SetCaptionL(iEdwinLabel1);
                Line(EAknExFormDlgCtrlIdEdwin01)->iCaption->CropText();
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdNumber01))
                {
                SetNumberEditorValue(EAknExFormDlgCtrlIdNumber01, iNumberData1);
                Line(EAknExFormDlgCtrlIdNumber01)->SetCaptionL(iNumberLabel1);
                Line(EAknExFormDlgCtrlIdNumber01)->iCaption->CropText();
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin02))
                {
                SetEdwinTextL(EAknExFormDlgCtrlIdEdwin02, &iEdwinData2);
                Line(EAknExFormDlgCtrlIdEdwin02)->SetCaptionL(iEdwinLabel2);
                Line(EAknExFormDlgCtrlIdEdwin02)->iCaption->CropText();
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdNumber02))
                {
                SetNumberEditorValue(EAknExFormDlgCtrlIdNumber02, iNumberData2);
                Line(EAknExFormDlgCtrlIdNumber02)->SetCaptionL(iNumberLabel2);
                Line(EAknExFormDlgCtrlIdNumber02)->iCaption->CropText();
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin03))
                {
                SetEdwinTextL(EAknExFormDlgCtrlIdEdwin03, &iEdwinData3);
                Line(EAknExFormDlgCtrlIdEdwin03)->SetCaptionL(iEdwinLabel3);
                Line(EAknExFormDlgCtrlIdEdwin03)->iCaption->CropText();
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdNumber03))
                {
                SetNumberEditorValue(EAknExFormDlgCtrlIdNumber03, iNumberData3);
                Line(EAknExFormDlgCtrlIdNumber03)->SetCaptionL(iNumberLabel3);
                Line(EAknExFormDlgCtrlIdNumber03)->iCaption->CropText();
                }
            }
            break;
        case R_AKNEXFORM_ALL_EDITOR_FIELD_DIALOG:
            {
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin01))
                {
                SetEdwinTextL(EAknExFormDlgCtrlIdEdwin01, &iEdwinData1);
                Line(EAknExFormDlgCtrlIdEdwin01)->SetCaptionL(iEdwinLabel1);
                Line(EAknExFormDlgCtrlIdEdwin01)->iCaption->CropText();
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdNumber01))
                {
                SetNumberEditorValue(EAknExFormDlgCtrlIdNumber01, iNumberData1);
                Line(EAknExFormDlgCtrlIdNumber01)->SetCaptionL(iNumberLabel1);
                Line(EAknExFormDlgCtrlIdNumber01)->iCaption->CropText();
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdDate01))
                {
                SetTTimeEditorValue(EAknExFormDlgCtrlIdDate01, iDateData1);
                Line(EAknExFormDlgCtrlIdDate01)->SetCaptionL(iDateLabel1);
                Line(EAknExFormDlgCtrlIdDate01)->iCaption->CropText();
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdTime01))
                {
                SetTTimeEditorValue(EAknExFormDlgCtrlIdTime01, iTimeData1);
                Line(EAknExFormDlgCtrlIdTime01)->SetCaptionL(iTimeLabel1);
                Line(EAknExFormDlgCtrlIdTime01)->iCaption->CropText();
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdDuration01))
                {
                SetDurationEditorValue(EAknExFormDlgCtrlIdDuration01, iDurationData1);
                Line(EAknExFormDlgCtrlIdDuration01)->SetCaptionL(iDurationLabel1);
                Line(EAknExFormDlgCtrlIdDuration01)->iCaption->CropText();
                }
            CEikSecretEditor* secretEd = (CEikSecretEditor*) ControlOrNull(EAknExFormDlgCtrlIdSecret01);
            if (secretEd)
                {
                secretEd->SetText(iSecretData1);
                Line(EAknExFormDlgCtrlIdSecret01)->SetCaptionL(iSecretLabel1);
                Line(EAknExFormDlgCtrlIdSecret01)->iCaption->CropText();
                }
            }
            break;
        case R_AKNEXFORM_SEPARATOR_FIELD_DIALOG:
            {
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin01))
                {
                SetEdwinTextL(EAknExFormDlgCtrlIdEdwin01, &iEdwinData1);
                Line(EAknExFormDlgCtrlIdEdwin01)->SetCaptionL(iEdwinLabel1);
                Line(EAknExFormDlgCtrlIdEdwin01)->iCaption->CropText();
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin02))
                {
                SetEdwinTextL(EAknExFormDlgCtrlIdEdwin02, &iEdwinData2);
                Line(EAknExFormDlgCtrlIdEdwin02)->SetCaptionL(iEdwinLabel2);
                Line(EAknExFormDlgCtrlIdEdwin02)->iCaption->CropText();
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin03))
                {
                SetEdwinTextL(EAknExFormDlgCtrlIdEdwin03, &iEdwinData3);
                Line(EAknExFormDlgCtrlIdEdwin03)->SetCaptionL(iEdwinLabel3);
                Line(EAknExFormDlgCtrlIdEdwin03)->iCaption->CropText();
                }
            }
            break;
        case R_AKNEXFORM_TEXT_FIELD_DIALOG:
            {
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin01))
                {
                SetEdwinTextL(EAknExFormDlgCtrlIdEdwin01, &iEdwinData1);
                Line(EAknExFormDlgCtrlIdEdwin01)->SetCaptionL(iEdwinLabel1);
                Line(EAknExFormDlgCtrlIdEdwin01)->iCaption->CropText();
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin02))
                {
                SetEdwinTextL(EAknExFormDlgCtrlIdEdwin02, &iEdwinData2);
                Line(EAknExFormDlgCtrlIdEdwin02)->SetCaptionL(iEdwinLabel2);
                Line(EAknExFormDlgCtrlIdEdwin02)->iCaption->CropText();
                }
            }
            break;
        case R_AKNEXFORM_THREE_SLIDER_FIELD_DIALOG:
            {
            CAknSlider* slider1 = (CAknSlider*) ControlOrNull(EAknExFormDlgCtrlIdSlider01);
            if (slider1)
                {
                slider1->SetValueL(iSliderData1);
                Line(EAknExFormDlgCtrlIdSlider01)->SetCaptionL(iSliderLabel1);
                Line(EAknExFormDlgCtrlIdSlider01)->iCaption->CropText();
                }
            CAknSlider* slider2 = (CAknSlider*) ControlOrNull(EAknExFormDlgCtrlIdSlider02);
            if (slider2)
                {
                slider2->SetValueL(iSliderData2);
                Line(EAknExFormDlgCtrlIdSlider02)->SetCaptionL(iSliderLabel2);
                Line(EAknExFormDlgCtrlIdSlider02)->iCaption->CropText();
                }
            CAknSlider* slider3 = (CAknSlider*) ControlOrNull(EAknExFormDlgCtrlIdSlider03);
            if (slider3)
                {
                slider3->SetValueL(iSliderData3);
                Line(EAknExFormDlgCtrlIdSlider03)->SetCaptionL(iSliderLabel3);
                Line(EAknExFormDlgCtrlIdSlider03)->iCaption->CropText();
                }
            }
            break;
        case R_AKNEXFORM_NAVIGATE_SIX_PAGES_DIALOG:
            {
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin01))
                {
                SetEdwinTextL(EAknExFormDlgCtrlIdEdwin01, &iEdwinData1);
                Line(EAknExFormDlgCtrlIdEdwin01)->SetCaptionL(iEdwinLabel1);
                Line(EAknExFormDlgCtrlIdEdwin01)->iCaption->CropText();
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin02))
                {
                SetEdwinTextL(EAknExFormDlgCtrlIdEdwin02, &iEdwinData2);
                Line(EAknExFormDlgCtrlIdEdwin02)->SetCaptionL(iEdwinLabel2);
                Line(EAknExFormDlgCtrlIdEdwin02)->iCaption->CropText();
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin03))
                {
                SetEdwinTextL(EAknExFormDlgCtrlIdEdwin03, &iEdwinData3);
                Line(EAknExFormDlgCtrlIdEdwin03)->SetCaptionL(iEdwinLabel3);
                Line(EAknExFormDlgCtrlIdEdwin03)->iCaption->CropText();
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin04))
                {
                SetEdwinTextL(EAknExFormDlgCtrlIdEdwin04, &iEdwinData4);
                Line(EAknExFormDlgCtrlIdEdwin04)->SetCaptionL(iEdwinLabel4);
                Line(EAknExFormDlgCtrlIdEdwin04)->iCaption->CropText();
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin05))
                {
                SetEdwinTextL(EAknExFormDlgCtrlIdEdwin05, &iEdwinData5);
                Line(EAknExFormDlgCtrlIdEdwin05)->SetCaptionL(iEdwinLabel5);
                Line(EAknExFormDlgCtrlIdEdwin05)->iCaption->CropText();
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin06))
                {
                SetEdwinTextL(EAknExFormDlgCtrlIdEdwin06, &iEdwinData6);
                Line(EAknExFormDlgCtrlIdEdwin06)->SetCaptionL(iEdwinLabel6);
                Line(EAknExFormDlgCtrlIdEdwin06)->iCaption->CropText();
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdNumber01))
                {
                SetNumberEditorValue(EAknExFormDlgCtrlIdNumber01, iNumberData1);
                Line(EAknExFormDlgCtrlIdNumber01)->SetCaptionL(iNumberLabel1);
                Line(EAknExFormDlgCtrlIdNumber01)->iCaption->CropText();
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdNumber02))
                {
                SetNumberEditorValue(EAknExFormDlgCtrlIdNumber02, iNumberData2);
                Line(EAknExFormDlgCtrlIdNumber02)->SetCaptionL(iNumberLabel2);
                Line(EAknExFormDlgCtrlIdNumber02)->iCaption->CropText();
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdNumber03))
                {
                SetNumberEditorValue(EAknExFormDlgCtrlIdNumber03, iNumberData3);
                Line(EAknExFormDlgCtrlIdNumber03)->SetCaptionL(iNumberLabel3);
                Line(EAknExFormDlgCtrlIdNumber03)->iCaption->CropText();
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdNumber04))
                {
                SetNumberEditorValue(EAknExFormDlgCtrlIdNumber04, iNumberData4);
                Line(EAknExFormDlgCtrlIdNumber04)->SetCaptionL(iNumberLabel4);
                Line(EAknExFormDlgCtrlIdNumber04)->iCaption->CropText();
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdNumber05))
                {
                SetNumberEditorValue(EAknExFormDlgCtrlIdNumber05, iNumberData5);
                Line(EAknExFormDlgCtrlIdNumber05)->SetCaptionL(iNumberLabel5);
                Line(EAknExFormDlgCtrlIdNumber05)->iCaption->CropText();
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdNumber06))
                {
                SetNumberEditorValue(EAknExFormDlgCtrlIdNumber06, iNumberData6);
                Line(EAknExFormDlgCtrlIdNumber06)->SetCaptionL(iNumberLabel6);
                Line(EAknExFormDlgCtrlIdNumber06)->iCaption->CropText();
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdDate01))
                {
                SetTTimeEditorValue(EAknExFormDlgCtrlIdDate01, iDateData1);
                Line(EAknExFormDlgCtrlIdDate01)->SetCaptionL(iDateLabel1);
                Line(EAknExFormDlgCtrlIdDate01)->iCaption->CropText();
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdDate02))
                {
                SetTTimeEditorValue(EAknExFormDlgCtrlIdDate02, iDateData2);
                Line(EAknExFormDlgCtrlIdDate02)->SetCaptionL(iDateLabel2);
                Line(EAknExFormDlgCtrlIdDate02)->iCaption->CropText();
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdDate03))
                {
                SetTTimeEditorValue(EAknExFormDlgCtrlIdDate03, iDateData3);
                Line(EAknExFormDlgCtrlIdDate03)->SetCaptionL(iDateLabel3);
                Line(EAknExFormDlgCtrlIdDate03)->iCaption->CropText();
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdDate04))
                {
                SetTTimeEditorValue(EAknExFormDlgCtrlIdDate04, iDateData4);
                Line(EAknExFormDlgCtrlIdDate04)->SetCaptionL(iDateLabel4);
                Line(EAknExFormDlgCtrlIdDate04)->iCaption->CropText();
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdDate05))
                {
                SetTTimeEditorValue(EAknExFormDlgCtrlIdDate05, iDateData5);
                Line(EAknExFormDlgCtrlIdDate05)->SetCaptionL(iDateLabel5);
                Line(EAknExFormDlgCtrlIdDate05)->iCaption->CropText();
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdDate06))
                {
                SetTTimeEditorValue(EAknExFormDlgCtrlIdDate06, iDateData6);
                Line(EAknExFormDlgCtrlIdDate06)->SetCaptionL(iDateLabel6);
                Line(EAknExFormDlgCtrlIdDate06)->iCaption->CropText();
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdTime01))
                {
                SetTTimeEditorValue(EAknExFormDlgCtrlIdTime01, iTimeData1);
                Line(EAknExFormDlgCtrlIdTime01)->SetCaptionL(iTimeLabel1);
                Line(EAknExFormDlgCtrlIdTime01)->iCaption->CropText();
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdTime02))
                {
                SetTTimeEditorValue(EAknExFormDlgCtrlIdTime02, iTimeData2);
                Line(EAknExFormDlgCtrlIdTime02)->SetCaptionL(iTimeLabel2);
                Line(EAknExFormDlgCtrlIdTime02)->iCaption->CropText();
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdTime03))
                {
                SetTTimeEditorValue(EAknExFormDlgCtrlIdTime03, iTimeData3);
                Line(EAknExFormDlgCtrlIdTime03)->SetCaptionL(iTimeLabel3);
                Line(EAknExFormDlgCtrlIdTime03)->iCaption->CropText();
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdTime04))
                {
                SetTTimeEditorValue(EAknExFormDlgCtrlIdTime04, iTimeData4);
                Line(EAknExFormDlgCtrlIdTime04)->SetCaptionL(iTimeLabel4);
                Line(EAknExFormDlgCtrlIdTime04)->iCaption->CropText();
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdTime05))
                {
                SetTTimeEditorValue(EAknExFormDlgCtrlIdTime05, iTimeData5);
                Line(EAknExFormDlgCtrlIdTime05)->SetCaptionL(iTimeLabel5);
                Line(EAknExFormDlgCtrlIdTime05)->iCaption->CropText();
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdTime06))
                {
                SetTTimeEditorValue(EAknExFormDlgCtrlIdTime06, iTimeData6);
                Line(EAknExFormDlgCtrlIdTime06)->SetCaptionL(iTimeLabel6);
                Line(EAknExFormDlgCtrlIdTime06)->iCaption->CropText();
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdDuration01))
                {
                SetDurationEditorValue(EAknExFormDlgCtrlIdDuration01, iDurationData1);
                Line(EAknExFormDlgCtrlIdDuration01)->SetCaptionL(iDurationLabel1);
                Line(EAknExFormDlgCtrlIdDuration01)->iCaption->CropText();
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdDuration02))
                {
                SetDurationEditorValue(EAknExFormDlgCtrlIdDuration02, iDurationData2);
                Line(EAknExFormDlgCtrlIdDuration02)->SetCaptionL(iDurationLabel2);
                Line(EAknExFormDlgCtrlIdDuration02)->iCaption->CropText();
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdDuration03))
                {
                SetDurationEditorValue(EAknExFormDlgCtrlIdDuration03, iDurationData3);
                Line(EAknExFormDlgCtrlIdDuration03)->SetCaptionL(iDurationLabel3);
                Line(EAknExFormDlgCtrlIdDuration03)->iCaption->CropText();
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdDuration04))
                {
                SetDurationEditorValue(EAknExFormDlgCtrlIdDuration04, iDurationData4);
                Line(EAknExFormDlgCtrlIdDuration04)->SetCaptionL(iDurationLabel4);
                Line(EAknExFormDlgCtrlIdDuration04)->iCaption->CropText();
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdDuration05))
                {
                SetDurationEditorValue(EAknExFormDlgCtrlIdDuration05, iDurationData5);
                Line(EAknExFormDlgCtrlIdDuration05)->SetCaptionL(iDurationLabel5);
                Line(EAknExFormDlgCtrlIdDuration05)->iCaption->CropText();
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdDuration06))
                {
                SetDurationEditorValue(EAknExFormDlgCtrlIdDuration06, iDurationData6);
                Line(EAknExFormDlgCtrlIdDuration06)->SetCaptionL(iDurationLabel6);
                Line(EAknExFormDlgCtrlIdDuration06)->iCaption->CropText();
                }
            CEikSecretEditor* secretEd1 = (CEikSecretEditor*) ControlOrNull(EAknExFormDlgCtrlIdSecret01);
            if (secretEd1)
                {
                secretEd1->SetText(iSecretData1);
                Line(EAknExFormDlgCtrlIdSecret01)->SetCaptionL(iSecretLabel1);
                Line(EAknExFormDlgCtrlIdSecret01)->iCaption->CropText();
                }
            CEikSecretEditor* secretEd2 = (CEikSecretEditor*) ControlOrNull(EAknExFormDlgCtrlIdSecret02);
            if (secretEd2)
                {
                secretEd2->SetText(iSecretData2);
                Line(EAknExFormDlgCtrlIdSecret02)->SetCaptionL(iSecretLabel2);
                Line(EAknExFormDlgCtrlIdSecret02)->iCaption->CropText();
                }
            CEikSecretEditor* secretEd3 = (CEikSecretEditor*) ControlOrNull(EAknExFormDlgCtrlIdSecret03);
            if (secretEd3)
                {
                secretEd3->SetText(iSecretData3);
                Line(EAknExFormDlgCtrlIdSecret03)->SetCaptionL(iSecretLabel3);
                Line(EAknExFormDlgCtrlIdSecret03)->iCaption->CropText();
                }
            CEikSecretEditor* secretEd4 = (CEikSecretEditor*) ControlOrNull(EAknExFormDlgCtrlIdSecret04);
            if (secretEd4)
                {
                secretEd4->SetText(iSecretData4);
                Line(EAknExFormDlgCtrlIdSecret04)->SetCaptionL(iSecretLabel4);
                Line(EAknExFormDlgCtrlIdSecret04)->iCaption->CropText();
                }
            CEikSecretEditor* secretEd5 = (CEikSecretEditor*) ControlOrNull(EAknExFormDlgCtrlIdSecret05);
            if (secretEd5)
                {
                secretEd5->SetText(iSecretData5);
                Line(EAknExFormDlgCtrlIdSecret05)->SetCaptionL(iSecretLabel5);
                Line(EAknExFormDlgCtrlIdSecret05)->iCaption->CropText();
                }
            CEikSecretEditor* secretEd6 = (CEikSecretEditor*) ControlOrNull(EAknExFormDlgCtrlIdSecret06);
            if (secretEd6)
                {
                secretEd6->SetText(iSecretData6);
                Line(EAknExFormDlgCtrlIdSecret06)->SetCaptionL(iSecretLabel6);
                Line(EAknExFormDlgCtrlIdSecret06)->iCaption->CropText();
                }
            }
            break;
        case R_AKNEXFORM_DOUBLE_AND_SINGLE_LINE_FORM:
            {
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin01))
                {
                SetEdwinTextL(EAknExFormDlgCtrlIdEdwin01, &iEdwinData1);
                Line(EAknExFormDlgCtrlIdEdwin01)->SetCaptionL(iEdwinLabel1);
                Line(EAknExFormDlgCtrlIdEdwin01)->iCaption->CropText();
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin02))
                {
                SetEdwinTextL(EAknExFormDlgCtrlIdEdwin02, &iEdwinData2);
                Line(EAknExFormDlgCtrlIdEdwin02)->SetCaptionL(iEdwinLabel2);
                Line(EAknExFormDlgCtrlIdEdwin02)->iCaption->CropText();
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin03))
                {
                SetEdwinTextL(EAknExFormDlgCtrlIdEdwin03, &iEdwinData3);
                Line(EAknExFormDlgCtrlIdEdwin03)->SetCaptionL(iEdwinLabel3);
                Line(EAknExFormDlgCtrlIdEdwin03)->iCaption->CropText();
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdEdwin11))
                {
                SetEdwinTextL(EAknExFormDlgCtrlIdEdwin11, &iEdwinData4);
                Line(EAknExFormDlgCtrlIdEdwin11)->SetCaptionL(iEdwinLabel4);
                Line(EAknExFormDlgCtrlIdEdwin11)->iCaption->CropText();
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdNumber01))
                {
                SetNumberEditorValue(EAknExFormDlgCtrlIdNumber01, iNumberData1);
                Line(EAknExFormDlgCtrlIdNumber01)->SetCaptionL(iNumberLabel1);
                Line(EAknExFormDlgCtrlIdNumber01)->iCaption->CropText();
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdNumber02))
                {
                SetNumberEditorValue(EAknExFormDlgCtrlIdNumber02, iNumberData2);
                Line(EAknExFormDlgCtrlIdNumber02)->SetCaptionL(iNumberLabel2);
                Line(EAknExFormDlgCtrlIdNumber02)->iCaption->CropText();
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdNumber03))
                {
                SetNumberEditorValue(EAknExFormDlgCtrlIdNumber03, iNumberData3);
                Line(EAknExFormDlgCtrlIdNumber03)->SetCaptionL(iNumberLabel3);
                Line(EAknExFormDlgCtrlIdNumber03)->iCaption->CropText();
                }
            if (ControlOrNull(EAknExFormDlgCtrlIdNumber06))
                {
                SetNumberEditorValue(EAknExFormDlgCtrlIdNumber06, iNumberData4);
                Line(EAknExFormDlgCtrlIdNumber06)->SetCaptionL(iNumberLabel4);
                Line(EAknExFormDlgCtrlIdNumber06)->iCaption->CropText();
                }
            }
            break;
        default:
            break;
        }
    }

// ----------------------------------------------------------------------------
// CAknExFormSaveForm::PostLayoutDynInitL()
// Set default field value to member data.
// ----------------------------------------------------------------------------
//
void CAknExFormSaveForm::PostLayoutDynInitL()
    {
    CAknForm::PostLayoutDynInitL();
    SaveFormDataL();
    }

// ----------------------------------------------------------------------------
// CAknExFormSaveForm::QuerySaveChangesL()
// Show save query. If user answers "No" to this query.
// return field value to the value which is before editing.
// This is called Back-softkey when edit mode.
// ----------------------------------------------------------------------------
//
TBool CAknExFormSaveForm::QuerySaveChangesL()
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
