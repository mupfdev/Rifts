/*
* ============================================================================
*  Name     : CAknExSliderContainer
*  Part of  : AknExSlider
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include <aknutils.h>
#include <barsread.h>
#include <e32math.h>
#include <eikappui.h>
#include <eikenv.h>
#include <eiklabel.h> // for label
#include <aknslider.h> // for slider
#include <aknform.h> // for form
#include <aknnotewrappers.h> // for note wrapper
#include <AknExSlider.rsg>
#include <e32math.h>
#include "aknexslider.hrh"
#include "AknExSliderContainer.h"
#include "aknexsliderview.h"
#include "AknExSliderSaveForm.h"

// CONSTANTS
const TInt KSliderInformationOffset = 5;
const TInt KSliderClearValue = 0;
const TInt KSliderInitValue = 40;
const TInt KSliderBaseMinValue = 0;
const TInt KSliderBaseMaxValue = 100;
const TInt KSliderBaseStepSize = 2;
const TInt KSliderCountComponentControls = 1;
// for Range screen
const TInt KSliderMaxChangeRange = 40;
const TInt KSliderChangeRangeValue = 10;
const TInt KSliderTextHeightDivide = 2;
// for Step size screen
const TInt KSliderStepChangeCount = 3;
const TInt KSliderStepChangeSize[KSliderStepChangeCount] = { 2, 5, 10 };
const TInt KSliderInitialStepIndex = 0;
// for Current value screen
const TInt KSliderNormalRemainder = 0;
// for Value type screen
const TInt KSliderInitialValueOfValueTypeScreen = 100;
// for Text appearance screen
const TInt KSliderInitialValueOfTextScreen = 1;
const TInt KSliderMaxValueOfTextScreen = 5;
// for change state of slider
#define AKNEXSLIDER_HEADER_CHANGE_KEY   EKeyEnter
#define AKNEXSLIDER_HEADER_CHANGE_KEY2  EKeyOK
#define AKNEXSLIDER_MINIMUM_CHANGE_KEY  EKeyEnter
#define AKNEXSLIDER_MINIMUM_CHANGE_KEY2 EKeyOK
#define AKNEXSLIDER_MAXIMUM_CHANGE_KEY  EKeyEnter
#define AKNEXSLIDER_MAXIMUM_CHANGE_KEY2 EKeyOK
#define AKNEXSLIDER_RANGE_CHANGE_KEY    EKeyEnter
#define AKNEXSLIDER_RANGE_CHANGE_KEY2   EKeyOK
#define AKNEXSLIDER_VALUE_CHANGE_KEY    EKeyEnter
#define AKNEXSLIDER_VALUE_CHANGE_KEY2   EKeyOK
#define AKNEXSLIDER_STEP_CHANGE_KEY     EKeyEnter
#define AKNEXSLIDER_STEP_CHANGE_KEY2    EKeyOK

#define AKNEXSLIDER_WHITE TRgb(0xFF,0xFF,0xFF)

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExSliderContainer::CAknExSliderContainer()
// Default constructor.
// ----------------------------------------------------------------------------
//
CAknExSliderContainer::CAknExSliderContainer(CAknExSliderView* aView)
:   iSlider( NULL ),
    iLabel( NULL ),
    iLabelFormat( NULL ),
    iCurrentFeature( EAknExSliderCmdEmpty ),
    iCurrentLabel( EAknExSliderChangeLabel1 ),
    iCurrentStep( KSliderInitialStepIndex ),
    iScreenStep( KSliderInitialValueOfTextScreen ),
    iView(aView)
    {
    }

// ----------------------------------------------------------------------------
// CAknExSliderContainer::ConstructL( const TRect& )
// EPOC constructor.
// ----------------------------------------------------------------------------
//
void CAknExSliderContainer::ConstructL( const TRect& aRect )
    {
    // Creates window.
    CreateWindowL();

    // Creates label object.
    iLabel = new( ELeave ) CEikLabel;
    iLabel->SetContainerWindowL( *this );

    // Sets rectangle of window and activates.
    SetRect( aRect );
    ActivateL();

    DisplayFeatureL(); // Displays information.
    }

// ----------------------------------------------------------------------------
// CAknExSliderContainer::~CAknExSliderContainer()
// Destructor.
// ----------------------------------------------------------------------------
//
CAknExSliderContainer::~CAknExSliderContainer()
    {
    StopDisplaySlider(); // Deletes slider control.

    // Deletes label object.
    delete iLabel;
    }

// ----------------------------------------------------------------------------
// CAknExSliderContainer::HandleCommandL( TInt )
// Handles the commands.
// ----------------------------------------------------------------------------
//
void CAknExSliderContainer::HandleCommandL( TInt aCommand )
    {
    iCurrentFeature = aCommand;
    // If the font which is used in label is <legend> font
    // sets font for displaying information to label's font.
    if ( iLabel->Font() == LatinBold19() )
        {
        SetLabelState( EAknExSliderLabelInformation );
        }

    DisplayFeatureL(); // Displays the slider control and information.
    }

// ----------------------------------------------------------------------------
// CAknExSliderContainer::OfferKeyEventL( const TKeyEvent&, TEventCode )
// Handles the key events.
// ----------------------------------------------------------------------------
//
TKeyResponse CAknExSliderContainer::OfferKeyEventL(
    const TKeyEvent& aKeyEvent,
    TEventCode aType )
    {
    if ( aType != EEventKey ) // Is not key event?
        {
        return EKeyWasNotConsumed;
        }
    TBuf<KAknExSliderMessageBufLength> information( 0 );
    TChar charCode(aKeyEvent.iCode);

    TKeyResponse response(EKeyWasConsumed);

    switch( aKeyEvent.iCode ) // The code of key event is...
        {
        case EKeySpace: // Space key.
            DisplayNextFeature(); // Displays next screen.
            break;
        case EKeyUpArrow:
            {
            // If the screen which is displayed is value text screen
            // changes the value type of slider and information.
            if ( iCurrentFeature == EAknExSliderCmdValueText )
                {
                if ( iScreenStep > KSliderInitialValueOfTextScreen &&
                     iScreenStep <= KSliderMaxValueOfTextScreen )
                    {
                    // Sets the index of screen step in order to loop.
                    iScreenStep--; // decrements the index of screen step.
                    }
                else
                    {
                    iScreenStep = KSliderMaxValueOfTextScreen;
                    }
                ChangeScreenOfTextAppearance(); // Changes the display.
                }
            else
                {
                return EKeyWasNotConsumed;
                }
            break;
            }
        case EKeyDownArrow:
            {
            // If the screen which is displayed is value text screen
            // changes the value type of slider and information.
            if ( iCurrentFeature == EAknExSliderCmdValueText )
                {
                if ( iScreenStep >= KSliderInitialValueOfTextScreen &&
                     iScreenStep < KSliderMaxValueOfTextScreen )
                    {
                    iScreenStep++; // Increments the index of screen step.
                    }
                else
                    {
                    // Sets the index of screen step in order to loop.
                    iScreenStep = KSliderInitialValueOfTextScreen;
                    }
                ChangeScreenOfTextAppearance(); // Changes the display.
                }
            else
                {
                return EKeyWasNotConsumed;
                }
            break;
            }
        default:
            {
            response = EKeyWasNotConsumed;
            break;
            }
        }

    if (response == EKeyWasConsumed)
        {
        return response;
        }

    
    switch (iCurrentFeature)
        {
        case EAknExSliderCmdSetMinimum:
            {
            // If the screen which is displayed is minimum screen
            // changes the minimum text of slider control.
            if (charCode == AKNEXSLIDER_MINIMUM_CHANGE_KEY ||
                charCode == AKNEXSLIDER_MINIMUM_CHANGE_KEY2)
                {
                response = EKeyWasConsumed;
                
                // Makes the text which is displayed and sets this to label.
                switch ( iCurrentLabel )
                    {
                    case EAknExSliderChangeLabel1:
                        iCoeEnv->ReadResource( information,
                                               R_AKNEXSLIDER_LABEL_MIN2 );
                        break;
                    case EAknExSliderChangeLabel2:
                        iCoeEnv->ReadResource( information,
                                               R_AKNEXSLIDER_LABEL_LOW1 );
                        break;
                    case EAknExSliderChangeLabel3:
                        iCoeEnv->ReadResource( information,
                                               R_AKNEXSLIDER_LABEL_LOW2 );
                        break;
                    case EAknExSliderChangeLabel4:
                        iCoeEnv->ReadResource( information,
                                               R_AKNEXSLIDER_LABEL_MIN1 );
                        break;
                    default:
                        return EKeyWasNotConsumed;
                    }
                iSlider->SetMinimumTextL( information );
                DrawNow();
                // Increments the index of text which is displaying.
                // If number of index is more than defined maximum number,
                // sets minimum number to number of index.
                if ( ++iCurrentLabel > EAknExSliderChangeLabel4 )
                    {
                    iCurrentLabel = EAknExSliderChangeLabel1;
                    }
                }
            break;
            }
        case EAknExSliderCmdSetMaximum:
            {
            // If the screen which is displayed is maximum screen
            // changes the maximum text of slider control.
            if (charCode == AKNEXSLIDER_MAXIMUM_CHANGE_KEY ||
                charCode == AKNEXSLIDER_MAXIMUM_CHANGE_KEY2)
                {
                response = EKeyWasConsumed;
                
                // Makes the text which is displayed and sets this to label.
                switch ( iCurrentLabel )
                    {
                    case EAknExSliderChangeLabel1:
                        iCoeEnv->ReadResource( information,
                                               R_AKNEXSLIDER_LABEL_MAX2 );
                        break;
                    case EAknExSliderChangeLabel2:
                        iCoeEnv->ReadResource( information,
                                               R_AKNEXSLIDER_LABEL_HIGH1 );
                        break;
                    case EAknExSliderChangeLabel3:
                        iCoeEnv->ReadResource( information,
                                               R_AKNEXSLIDER_LABEL_HIGH2 );
                        break;
                    case EAknExSliderChangeLabel4:
                        iCoeEnv->ReadResource( information,
                                               R_AKNEXSLIDER_LABEL_MAX1 );
                        break;
                    default:
                        return EKeyWasNotConsumed;
                    }
                iSlider->SetMaximumTextL( information );
                DrawNow();
                // Increments the index of text which is displaying.
                // If number of index is more than defined maximum number,
                // sets minimum number to number of index.
                if ( ++iCurrentLabel > EAknExSliderChangeLabel4 )
                    {
                    iCurrentLabel = EAknExSliderChangeLabel1;
                    }
                }
            break;
            }
        case EAknExSliderCmdSetRange:
            {
            if (charCode == AKNEXSLIDER_RANGE_CHANGE_KEY ||
                charCode == AKNEXSLIDER_RANGE_CHANGE_KEY2)
                {
                response = EKeyWasConsumed;
                
                iCurrentLabel += KSliderChangeRangeValue;
                if ( iCurrentLabel > KSliderMaxChangeRange )
                    {
                    iCurrentLabel = KSliderClearValue;
                    }
                // If current value of slider does not range from minimum value
                // to maximum value, corrects the current value.
                if ( iSlider->Value() > ( KSliderBaseMaxValue - iCurrentLabel )
                    )
                    {
                    iSlider->SetValueL( KSliderBaseMaxValue - iCurrentLabel );
                    }
                else if ( iSlider->Value() <
                          ( KSliderBaseMinValue + iCurrentLabel ) )
                    {
                    iSlider->SetValueL( KSliderBaseMinValue + iCurrentLabel );
                    }
                // Sets minimum and maximum values.
                iSlider->SetRange( KSliderBaseMinValue + iCurrentLabel,
                                   KSliderBaseMaxValue - iCurrentLabel);
                ChangeLabelL();
                }
            break;
            }
        case EAknExSliderCmdReturn:
            {
            if (charCode == AKNEXSLIDER_VALUE_CHANGE_KEY ||
                charCode == AKNEXSLIDER_VALUE_CHANGE_KEY2)
                {
                response = EKeyWasConsumed;
                
                ChangeLabelL();
                }
            break;
            }
        case EAknExSliderCmdSetValue:
            {
            if (charCode == AKNEXSLIDER_VALUE_CHANGE_KEY ||
                charCode == AKNEXSLIDER_VALUE_CHANGE_KEY2)
                {
                response = EKeyWasConsumed;
                
                TInt64 randSeed;
                TTime time;
                TInt randValue( KSliderClearValue );

                // Sets random numver to value of slider control.
                time.UniversalTime();
                randSeed = time.Int64();
                randValue = ( Math::Rand( randSeed ) % KSliderBaseMaxValue ) ;
                if ( randValue % KSliderBaseStepSize != KSliderNormalRemainder )
                    {
                    if ( randValue < KSliderBaseStepSize )
                        {
                        randValue += ( KSliderBaseStepSize - randValue ) ;
                        }
                    else
                        {
                        randValue -= ( randValue % KSliderBaseStepSize );
                        }
                    }
                iSlider->SetValueL( randValue );
                ChangeLabelL();
                }
            break;
            }
        case EAknExSliderCmdSetStep:
            {
            // If the screen which is displayed is step size screen
            // changes the step size of slider control.
            if (charCode == AKNEXSLIDER_STEP_CHANGE_KEY ||
                charCode == AKNEXSLIDER_STEP_CHANGE_KEY2)
                {
                response = EKeyWasConsumed;
                
                // Increments the index of step size.
                // If number of index is more than defined maximum number,
                // sets minimum number to number of index.
                if ( ++iCurrentStep >= KSliderStepChangeCount )
                    {
                    iCurrentStep = KSliderInitialStepIndex;
                    }
                iSlider->SetValueL( KSliderClearValue );
                iSlider->SetStepSize( KSliderStepChangeSize[iCurrentStep] );
                ChangeLabelL();
                }
            break;
            }
        default:
            {
            break;
            }
        }

    return response;
    }

// ----------------------------------------------------------------------------
// CAknExSliderContainer::StopDisplaySlider()
// Deletes slider control objects.
// ----------------------------------------------------------------------------
//
void CAknExSliderContainer::StopDisplaySlider()
    {
    // Deletes slider control object.
    if ( iSlider )
        {
        // Removes slider control from control stack.
        iEikonEnv->EikAppUi()->RemoveFromStack( iSlider );
        delete iSlider;
        iSlider = NULL;
        }
    }

// ----------------------------------------------------------------------------
// CAknExSliderContainer::SetLabelState( TAknExSliderLabelState )
// Sets font and alignment of label.
// ----------------------------------------------------------------------------
//
void CAknExSliderContainer::SetLabelState( TAknExSliderLabelState aState )
    {
    if ( aState == EAknExSliderLabelTitle ) // Is label used for title?
        {
        // Uses <legend> font.
        iLabel->SetFont( LatinBold19() );
        // Horizontal : center, Vertical : center
        iLabel->SetAlignment( EHCenterVCenter );
        }
    else
        {
        // Uses <annotation> font.
        iLabel->SetFont( iEikonEnv->AnnotationFont() );
        // Horizontal : left, Vertical : top
        iLabel->SetAlignment( EHLeftVTop );
        }
    }

// ----------------------------------------------------------------------------
// CAknExSliderContainer::DisplayNextFeature()
// Sets ID of feature to displayed next.
// ----------------------------------------------------------------------------
//
void CAknExSliderContainer::DisplayNextFeature()
    {
    switch ( iCurrentFeature ) // Current screen is...
        {
        case EAknExSliderCmdEmpty: // Start screen.
            // Next : Layout1 screen.
            iCurrentFeature = EAknExSliderCmdLayout1;
            SetLabelState( EAknExSliderLabelInformation );
            break;
        case EAknExSliderCmdLayout1: // Layout1 screen.
            // Next : Layout2 screen.
            iCurrentFeature = EAknExSliderCmdLayout2;
            break;
        case EAknExSliderCmdLayout2: // Layout2 screen.
            // Next : Layout3 screen.
            iCurrentFeature = EAknExSliderCmdLayout3;
            break;
        case EAknExSliderCmdLayout3: // Layout3 screen.
            // Next : View mode screen.
            iCurrentFeature = EAknExSliderCmdViewMode;
            break;
        case EAknExSliderCmdViewMode: // View mode screen.
            // Next : Form screen.
            iCurrentFeature = EAknExSliderCmdForm;
            break;
        case EAknExSliderCmdForm: // Form screen.
            // Next : Return value screen.
            iCurrentFeature = EAknExSliderCmdReturn;
            SetLabelState( EAknExSliderLabelInformation );
            break;
        case EAknExSliderCmdReturn: // Return value screen.
            // Next : Minimum screen.
            iCurrentFeature = EAknExSliderCmdSetMinimum;
            break;
        case EAknExSliderCmdSetMinimum: // Minimum screen.
            // Next : Maximum screen.
            iCurrentFeature = EAknExSliderCmdSetMaximum;
            break;
        case EAknExSliderCmdSetMaximum: // Maximum screen.
            // Next : Range screen.
            iCurrentFeature = EAknExSliderCmdSetRange;
            break;
        case EAknExSliderCmdSetRange: // Range screen.
            // Next : Current value screen.
            iCurrentFeature = EAknExSliderCmdSetValue;
            break;
        case EAknExSliderCmdSetValue: // Current value screen.
            // Next : Step size screen.
            iCurrentFeature = EAknExSliderCmdSetStep;
            break;
        case EAknExSliderCmdSetStep: // Step size screen.
            // Next : Value changed screen.
            iCurrentFeature = EAknExSliderCmdValueChanged;
            break;
        case EAknExSliderCmdValueChanged: // Value changed screen.
            // Next : Value type(not shown) screen.
            iCurrentFeature = EAknExSliderCmdTypeNotShown;
            break;
        case EAknExSliderCmdTypeNotShown: // Value type(not shown) screen.
            // Next : Value type(bare) screen.
            iCurrentFeature = EAknExSliderCmdTypeBare;
            break;
        case EAknExSliderCmdTypeBare: // Value type(bare) screen.
            // Next :  Value type(percent) screen.
            iCurrentFeature = EAknExSliderCmdTypePercent;
            break;
        case EAknExSliderCmdTypePercent: // Value type(percent) screen.
            // Next : Value type(fraction) screen.
            iCurrentFeature = EAknExSliderCmdTypeFraction;
            break;
        case EAknExSliderCmdTypeFraction: // Value type(fraction) screen.
            // Next : Value type(decimal) screen.
            iCurrentFeature = EAknExSliderCmdTypeDecimal;
            break;
        case EAknExSliderCmdTypeDecimal: // Value type(decimal) screen.
            // Next : Value text screen.
            iCurrentFeature = EAknExSliderCmdValueText;
            break;
        case EAknExSliderCmdValueText: // Value text screen.
            // Next : Start screen.
            iCurrentFeature = EAknExSliderCmdEmpty;
            break;
        default:
            // Exception : Layout1 screen.
            iCurrentFeature = EAknExSliderCmdLayout1;
            break;
        }

    DisplayFeatureL();
    }

// ----------------------------------------------------------------------------
// CAknExSliderContainer::DisplayFeatureL()
// Displays the slider and label.
// ----------------------------------------------------------------------------
//
void CAknExSliderContainer::DisplayFeatureL()
    {
    switch ( iCurrentFeature ) // Screen which is displayed is...
        {
        case EAknExSliderCmdEmpty: // Start screen.
            // Deletes slider control and displays information.
            StopDisplaySlider();
            SetLabelState( EAknExSliderLabelTitle );
            iView->SetTitleL(R_AKNEXSLIDER_INITAIL);
            DisplayInformationL( R_AKNEXSLIDER_APP_TITLE );
            break;
        case EAknExSliderCmdLayout1: // Layout1 screen.
            // Displays slider control and information.
            DisplaySliderL( R_AKNEXSLIDER_SLIDER_LAYOUT1 );
            DisplayInformationL( R_AKNEXSLIDER_INFO_LAYOUT1 );
            break;
        case EAknExSliderCmdLayout2: // Layout2 screen.
            // Displays slider control and information.
            DisplaySliderL( R_AKNEXSLIDER_SLIDER_LAYOUT2 );
            DisplayInformationL( R_AKNEXSLIDER_INFO_LAYOUT2 );
            break;
        case EAknExSliderCmdLayout3: // Layout3 screen.
            // Displays slider control and information.
            DisplaySliderL( R_AKNEXSLIDER_SLIDER_LAYOUT3 );
            DisplayInformationL( R_AKNEXSLIDER_INFO_LAYOUT3 );
            break;
        case EAknExSliderCmdViewMode: // View mode screen.
            // Displays slider control and information.
            DisplaySliderL( R_AKNEXSLIDER_SLIDER_LAYOUT1 );
            DisplayInformationL( R_AKNEXSLIDER_INFO_VIEWMODE );
            break;
        case EAknExSliderCmdKeyEvent1: // Key event1 screen.
            // Displays slider control and information.
            DisplaySliderL( R_AKNEXSLIDER_SLIDER_LAYOUT1 );
            DisplayInformationL( R_AKNEXSLIDER_INFO_KEYEVENT1 );
            break;
        case EAknExSliderCmdKeyEvent2: // Key even2 screen.
            // Displays slider control and information.
            DisplaySliderL( R_AKNEXSLIDER_SLIDER_LAYOUT1 );
            DisplayInformationL( R_AKNEXSLIDER_INFO_KEYEVENT2 );
            break;
        case EAknExSliderCmdKeyEvent3: // Key event3 screen.
            // Displays slider control and information.
            DisplaySliderL( R_AKNEXSLIDER_SLIDER_LAYOUT1 );
            DisplayInformationL( R_AKNEXSLIDER_INFO_KEYEVENT3 );
            break;
        case EAknExSliderCmdForm: // Form screen.
            {
            // Displays slider control in form.
            StopDisplaySlider();
            if ( iLabel )
                {
                TBuf<KAknExSliderMessageBufLength> information( 0 );
                iLabel->SetTextL( information );
                }
            DrawNow();
            // DisplayMessage( R_AKNEXSLIDER_INFO_FORM );
            DisplayFormL( R_AKNEXSLIDER_SLIDER_FORM_DIALOG );
            SetLabelState( EAknExSliderLabelTitle );
            DisplayInformationL( R_AKNEXSLIDER_INFO_OPERATION );
            break;
            }
        case EAknExSliderCmdReturn: // Return value.
            // Displays slider control and information.
            DisplaySliderL( R_AKNEXSLIDER_SLIDER_LAYOUT1 );
            DisplayInformationL( R_AKNEXSLIDER_INFO_RETURN );
            break;
        case EAknExSliderCmdSetMinimum: // Minimum screen.
            // Displays slider control and information.
            iCurrentLabel = EAknExSliderChangeLabel1;
            DisplaySliderL( R_AKNEXSLIDER_SLIDER_LAYOUT5 );
            DisplayInformationL( R_AKNEXSLIDER_INFO_MINIMUM );
            break;
        case EAknExSliderCmdSetMaximum: // Maximum screen.
            // Displays slider control and information.
            iCurrentLabel = EAknExSliderChangeLabel1;
            DisplaySliderL( R_AKNEXSLIDER_SLIDER_LAYOUT5 );
            DisplayInformationL( R_AKNEXSLIDER_INFO_MAXIMUM );
            break;
        case EAknExSliderCmdSetRange: // Range screen.
            // Displays slider control and information.
            iCurrentLabel = KSliderClearValue;
            DisplaySliderL( R_AKNEXSLIDER_SLIDER_LAYOUT1, KSliderInitValue );
            DisplayInformationL( R_AKNEXSLIDER_INFO_RANGE );
            break;
        case EAknExSliderCmdSetValue: // Current value screen.
            // Displays slider control and information.
            DisplaySliderL( R_AKNEXSLIDER_SLIDER_LAYOUT1 );
            DisplayInformationL( R_AKNEXSLIDER_INFO_VALUE );
            break;
        case EAknExSliderCmdSetStep: // Step size screen.
            // Displays slider control and information.
            iCurrentStep = KSliderInitialStepIndex;
            DisplaySliderL( R_AKNEXSLIDER_SLIDER_LAYOUT1 );
            DisplayInformationL( R_AKNEXSLIDER_INFO_STEP );
            break;
        case EAknExSliderCmdValueChanged: // Value changed screen.
            // Displays slider control and information.
            DisplaySliderL( R_AKNEXSLIDER_SLIDER_LAYOUT1 );
            DisplayInformationL( R_AKNEXSLIDER_INFO_VALUECHANGED );
            break;
        case EAknExSliderCmdTypeNotShown: // Value type(not shown) screen.
            // Displays slider control and information.
            DisplaySliderL( R_AKNEXSLIDER_SLIDER_LAYOUT_VALUE_NOTSHOWN,
                            KSliderInitialValueOfValueTypeScreen );
            DisplayInformationL( R_AKNEXSLIDER_INFO_VALUETYPE );
            break;
        case EAknExSliderCmdTypeBare: // Value type(bare) screen.
            // Displays slider control and information.
            DisplaySliderL( R_AKNEXSLIDER_SLIDER_LAYOUT_VALUE_BARE,
                            KSliderInitialValueOfValueTypeScreen );
            DisplayInformationL( R_AKNEXSLIDER_INFO_VALUETYPE );
            break;
        case EAknExSliderCmdTypePercent: // Value type(percent) screen.
            // Displays slider control and information.
            DisplaySliderL( R_AKNEXSLIDER_SLIDER_LAYOUT_VALUE_PERCENT,
                            KSliderInitialValueOfValueTypeScreen );
            DisplayInformationL( R_AKNEXSLIDER_INFO_VALUETYPE );
            break;
        case EAknExSliderCmdTypeFraction: // Value type(fraction) screen.
            // Displays slider control and information.
            DisplaySliderL( R_AKNEXSLIDER_SLIDER_LAYOUT_VALUE_FRACTION,
                            KSliderInitialValueOfValueTypeScreen );
            DisplayInformationL( R_AKNEXSLIDER_INFO_VALUETYPE );
            break;
        case EAknExSliderCmdTypeDecimal: // Value type(decimal) screen.
            // Displays slider control and information.
            DisplaySliderL( R_AKNEXSLIDER_SLIDER_LAYOUT_VALUE_DECIMAL,
                            KSliderInitialValueOfValueTypeScreen );
            DisplayInformationL( R_AKNEXSLIDER_INFO_VALUETYPE_DECIMAL );
            break;
        case EAknExSliderCmdValueText: // Value text screen.
            // Displays slider control and information.
            iScreenStep = KSliderInitialValueOfTextScreen;
            DisplaySliderL( R_AKNEXSLIDER_SLIDER_LAYOUT_TEXT_VALUE_BARE );
            DisplayInformationL( R_AKNEXSLIDER_INFO_VALUETEXT_BARE );
            break;
        default:
            // Ecepstion : Layout1 screen.
            DisplaySliderL( R_AKNEXSLIDER_SLIDER_LAYOUT1 );
            DisplayInformationL( R_AKNEXSLIDER_INFO_LAYOUT1 );
            break;
        }
    DrawNow();
    }

// ----------------------------------------------------------------------------
// CAknExSliderContainer::DisplaySliderL( TInt, TInt )
// Creates slider control.
// ----------------------------------------------------------------------------
//
void CAknExSliderContainer::DisplaySliderL( TInt aResourceId, TInt aValue )
    {
    StopDisplaySlider(); // Deletes slider control object.

    if ( !iSlider )
        {
        // Creates slider control object.
        TResourceReader reader;
        iCoeEnv->CreateResourceReaderLC( reader, aResourceId );
        iSlider = new( ELeave ) CAknSlider;
        // Sets edit-mode or view-mode.
        if ( iCurrentFeature == EAknExSliderCmdViewMode )
            {
            iSlider->HandleResourceChange(
                KEikMessageCaptionedControlNotEditableStateChange );
            }
        else
            {
            iSlider->HandleResourceChange(
                KEikMessageCaptionedControlEditableStateChange );
            }
        iSlider->ConstructFromResourceL( this, aValue, reader );
        CleanupStack::PopAndDestroy(); // reader

        iSlider->SetObserver( this );

        // Adds slider control to control stack. Slider control can get offered
        // key event.
        iEikonEnv->EikAppUi()->AddToStackL( iSlider );
        }
    }

// ----------------------------------------------------------------------------
// void CAknExSliderContainer::DisplayFormL( TInt )
// Creates and displays form.
// ----------------------------------------------------------------------------
//
void CAknExSliderContainer::DisplayFormL( TInt aResourceId )
    {
    CAknExSliderSaveForm* form = CAknExSliderSaveForm::NewL();
    form->ExecuteLD( aResourceId );
    }

// ----------------------------------------------------------------------------
// CAknExSliderContainer::DisplayInformationL( TInt )
// Displays the information.
// ----------------------------------------------------------------------------
//
void CAknExSliderContainer::DisplayInformationL( TInt aResourceId )
    {
    // Makes text which is displayed from resource.
    TBuf<KAknExSliderMessageBufLength> information( 0 );
    iCoeEnv->ReadResource( information, aResourceId );

    switch ( iCurrentFeature ) // Screen which is displayed is...
        {
        case EAknExSliderCmdReturn: // Return screen.
        case EAknExSliderCmdSetRange: // Range screen.
        case EAknExSliderCmdSetValue: // Current value screen.
        case EAknExSliderCmdSetStep: // Step size screen.
        case EAknExSliderCmdValueChanged: // Value changed screen.
        case EAknExSliderCmdTypeNotShown: // Value type(not shown) screen.
        case EAknExSliderCmdTypeBare: // Value type(bare) screen.
        case EAknExSliderCmdTypePercent: // Value type(percent) screen.
        case EAknExSliderCmdTypeFraction: // Value type(fraction) screen.
        case EAknExSliderCmdTypeDecimal: // Value type(decimal) screen.
            // Sets the value of slider object to text.
            iLabelFormat.SetLength( KSliderClearValue );
            iLabelFormat = information;
            information.SetLength( KSliderClearValue );
            STATIC_CAST( void, SetValueTextL( information ) );
            break;
        default:
            break;
        }

    SetLabelL( information ); // Sets text to label.
    }

/*
// ----------------------------------------------------------------------------
// CAknExSliderContainer::DisplayMessage( TInt )
// Displays the message.
// ----------------------------------------------------------------------------
//
void CAknExSliderContainer::DisplayMessage( TInt aResourceId )
    {
    if ( aResourceId )
    {
        // Makes text which is displayed from resource.
        TBuf<KAknExSliderMessageBufLength> message( 0 );
        iCoeEnv->ReadResource( message, aResourceId );
        CEikonEnv::Static()->InfoMsg( message ); // Displays message.
        }
    }
*/

// ----------------------------------------------------------------------------
// CAknExSliderContainer::SetLabelL( TDesC& aInformation )
// Sets string in the label.
// ----------------------------------------------------------------------------
//
void CAknExSliderContainer::SetLabelL( TDesC& aInformation )
    {
    if ( iLabel ) // Is label object created?
        {
        TPoint labelPosition( KSliderClearValue, KSliderInformationOffset );
        TSize labelSize( Size() );
        if ( iSlider ) // Is slider control object created?
            {
            // Vertical position of label is bottom position of slider control.
            labelPosition  += iSlider->Position();
            labelPosition.iY += iSlider->Size().iHeight;
            labelSize.iHeight -= iSlider->Size().iHeight;
            }
        // Sets rectangle of label and text.
        iLabel->SetExtent( labelPosition, labelSize );
        iLabel->SetTextL( aInformation );
        }
    }

// ----------------------------------------------------------------------------
// CAknExSliderContainer::SetValueTextL( TDes& ) const
// Makes the string which is displayed.
// ----------------------------------------------------------------------------
//
TDesC* CAknExSliderContainer::SetValueTextL( TDes& aTextBuf ) const
    {
    switch ( iCurrentFeature ) // Current screen is...
        {
        case EAknExSliderCmdReturn: // Return value screen.
        case EAknExSliderCmdSetValue: // Current value screen.
        case EAknExSliderCmdValueChanged: // Value changed screen.
        case EAknExSliderCmdTypeNotShown: // Value type(not shown) screen.
        case EAknExSliderCmdTypeBare: // Value type(bare) screen.
        case EAknExSliderCmdTypePercent: // Value type(percent) screen.
        case EAknExSliderCmdTypeFraction: // Value type(fraction) screen.
            // Sets the current value of slider control to text.
            aTextBuf.Format( iLabelFormat, iSlider->Value() );
            break;
        case EAknExSliderCmdSetRange: // Range screen.
            // Sets the range values of slider control to text.
            aTextBuf.Format( iLabelFormat,
                             KSliderBaseMinValue + iCurrentLabel,
                             KSliderBaseMaxValue - iCurrentLabel );
            break;
        case EAknExSliderCmdSetStep: // Step size screen.
            // Sets the step size to control.
            aTextBuf.Format( iLabelFormat,
                             KSliderStepChangeSize[iCurrentStep] ); 
            break;
        case EAknExSliderCmdTypeDecimal: // Value type(decimal) screen.
            {
            // Sets the current value of slider control to text.
            TInt sliderValue(iSlider->Value());
            TInt decimalPlaces(iSlider->DecimalPlaces());
            TReal64 showValue(sliderValue);
            TReal r;
            Math::Pow10(r, decimalPlaces);
            showValue = showValue / r; 
            aTextBuf.Format( iLabelFormat, showValue );
            break;
            }
        default:
            break;
        }
    return &aTextBuf;
    }

// ----------------------------------------------------------------------------
// CAknExSliderContainer::ChangeLabelL()
// Changes the display of the label.
// ----------------------------------------------------------------------------
//
void CAknExSliderContainer::ChangeLabelL()
    {
    // Updates text which is displayed.
    TBuf<KAknExSliderMessageBufLength> information( 0 );
    TDesC* labelString = SetValueTextL( information );
    SetLabelL( *labelString );
    DrawNow(); // Redraws all components in container.
    }

// ----------------------------------------------------------------------------
// CAknExSliderContainer::ChangeScreenOfTextAppearance()
// Changes the display of the value text in slider of each value type.
// ----------------------------------------------------------------------------
//
void CAknExSliderContainer::ChangeScreenOfTextAppearance()
    {
    if ( iSlider )
        {
        // Displays slider control and information according to iScreenStep.
        switch ( iScreenStep )
            {
            // Value text screen.
            case EAknExSliderChangeText1: // Value type is bare figure.
                DisplaySliderL( R_AKNEXSLIDER_SLIDER_LAYOUT_TEXT_VALUE_BARE );
                DisplayInformationL( R_AKNEXSLIDER_INFO_VALUETEXT_BARE );
                DrawNow();
                break;
            case EAknExSliderChangeText2: // Value is not shown.
                DisplaySliderL(
                    R_AKNEXSLIDER_SLIDER_LAYOUT_TEXT_VALUE_NOTSHOWN );
                DisplayInformationL( R_AKNEXSLIDER_INFO_VALUETEXT_NOTSHOWN );
                DrawNow();
                break;
            case EAknExSliderChangeText3: // Value type is percentage.
                DisplaySliderL(
                    R_AKNEXSLIDER_SLIDER_LAYOUT_TEXT_VALUE_PERCENT );
                DisplayInformationL( R_AKNEXSLIDER_INFO_VALUETEXT_PERCENT );
                DrawNow();
                break;
            case EAknExSliderChangeText4: // Value type is fraction.
                DisplaySliderL(
                    R_AKNEXSLIDER_SLIDER_LAYOUT_TEXT_VALUE_FRACTION );
                DisplayInformationL( R_AKNEXSLIDER_INFO_VALUETEXT_FRACTION );
                DrawNow();
                break;
            case EAknExSliderChangeText5: // Value type is decimal.
                DisplaySliderL(
                    R_AKNEXSLIDER_SLIDER_LAYOUT_TEXT_VALUE_DECIMAL );
                DisplayInformationL( R_AKNEXSLIDER_INFO_VALUETEXT_DECIMAL );
                DrawNow();
                break;
            default:
                break;
            }
        }
    }

// ----------------------------------------------------------------------------
// CAknExSliderContainer::CountComponentControls() const
// Returns number of component.
// ----------------------------------------------------------------------------
//
TInt CAknExSliderContainer::CountComponentControls() const
    {
    TInt count( KSliderCountComponentControls );
    // return the number of slider control
    if ( iSlider )
        {
        count++;
        }
    return count;
    }

// ----------------------------------------------------------------------------
// CAknExSliderContainer::ComponentControl( TInt ) const
// Returns pointer to particular component.
// ----------------------------------------------------------------------------
//
CCoeControl* CAknExSliderContainer::ComponentControl( TInt aIndex ) const
    {
    switch ( aIndex )
        {
        case EAknExSliderComponentLabel:
            return iLabel; // Return pointer to label object.
        case EAknExSliderComponentSlider:
            return iSlider; // Return pointer to slider object.
        default:
            return NULL; // Exception : Returns NULL.
        }
    }

// ----------------------------------------------------------------------------
// CAknExSliderContainer::Draw( const TRect& ) const
// Clears the window's rectangle.
// ----------------------------------------------------------------------------
//
void CAknExSliderContainer::Draw( const TRect& aRect ) const
    {
    // (Re)draw the rectangle of frame.
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( AKNEXSLIDER_WHITE );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.DrawRect( aRect );
    }

// ----------------------------------------------------------------------------
// void CAknExSliderContainer::HandleControlEventL( CCoeControl*, TCoeEvent )
// Handles the event when state change.
// ----------------------------------------------------------------------------
//
void CAknExSliderContainer::HandleControlEventL(
    CCoeControl* aControl,
    TCoeEvent aEventType )
    {
    if ( aControl == iSlider && aEventType == EEventStateChanged )
        {
        switch ( iCurrentFeature )
            {
            // Changes label of current value.
            case EAknExSliderCmdValueChanged: // Value changed screen.
            case EAknExSliderCmdTypeNotShown: // Value type(not shown) screen.
            case EAknExSliderCmdTypeBare: // Value type(bare) screen.
            case EAknExSliderCmdTypePercent: // Value type(percent) screen.
            case EAknExSliderCmdTypeFraction: // Value type(fraction) screen.
            case EAknExSliderCmdTypeDecimal: // Value type(decimal) screen.
                ChangeLabelL();
                break;
            default:
                break;
            }
        }
    }

// End of File
