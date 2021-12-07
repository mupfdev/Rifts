/*
* =============================================================================
*  Name     : CAknExPopFieldMultiPageDialog
*  Part of  : AknExPopField
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

// INCLUDE FILES
#include <eikenv.h>
#include <aknpopupfield.h>
#include <aknqueryvaluetext.h>
#include <AknExPopField.rsg>
#include "AknExPopField.hrh"
#include "AknExPopFieldMultiPageDialog.h"

// MACROS

// CONSTANTS
const TInt KAknExPopFieldIndexInitialize = 0;
const TInt KAknExPopFieldCountInitialize = 0;
const TInt KAknExPopFieldControlIdInitialize = 0;
const TInt KAknExPopFieldValueInitialize = 0;
const TInt KAknExPopFieldStepInitialize = 0;
const TInt KAknExPopFieldArrayTextBufLength = 256;
const TInt KAknExPopFieldInitialArrayElementCount = 4;
const TInt KAknExPopFieldNumberArrayMinimumValue = 10;
const TInt KAknExPopFieldNumberArrayMaximumValue = 100;
const TInt KAknExPopFieldNumberArrayStepValue = 10;
const TInt KAknExPopFieldTimeArrayStepNumber = 24;
const TInt KAknExPopFieldDateArrayStepNumber = 31;
const TInt KAknExPopFieldDuraArrayMinimumValue = 600;
const TInt KAknExPopFieldDuraArrayMaximumValue = 6000;
const TInt KAknExPopFieldDuraArrayStepValue = 600;
#define KAknExPopFieldTimeArrayStepHour TTimeIntervalHours( 1 )
#define KAknExPopFieldDateArrayStepDay TTimeIntervalDays( 1 )

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExPopFieldMultiPageDialog* CAknExPopFieldMultiPageDialog::NewLC()
// EPOC two-phase constructor.
// ----------------------------------------------------------------------------
//
CAknExPopFieldMultiPageDialog* CAknExPopFieldMultiPageDialog::NewLC()
    {
    CAknExPopFieldMultiPageDialog* self =
        new( ELeave ) CAknExPopFieldMultiPageDialog;
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }

// ----------------------------------------------------------------------------
// CAknExPopFieldMultiPageDialog::~CAknExPopFieldMultiPageDialog()
// Destructor.
// ----------------------------------------------------------------------------
//
CAknExPopFieldMultiPageDialog::~CAknExPopFieldMultiPageDialog()
    {
    DiscardArray();
    }

// ----------------------------------------------------------------------------
// CAknExPopFieldMultiPageDialog::CAknExPopFieldMultiPageDialog()
// Constructor.
// ----------------------------------------------------------------------------
//
CAknExPopFieldMultiPageDialog::CAknExPopFieldMultiPageDialog()
:   iTextArray( NULL ),
    iValueTextArray( NULL ),
    iNumberArray( NULL ),
    iValueNumberArray( NULL ),
    iPhoneArray( NULL ),
    iValuePhoneArray( NULL ),
    iTimeArray( NULL ),
    iValueTimeArray( NULL ),
    iDateArray( NULL ),
    iValueDateArray( NULL ),
    iDurationArray( NULL ),
    iValueDurationArray( NULL )
    {
    TInt index( KAknExPopFieldIndexInitialize );
    for ( index = KAknExPopFieldIndexInitialize;
          index < KAknExPopFieldMaxMultiPageValueField; index++ )
        {
        iTextValues[index] = NULL;
        iNumberValues[index] = NULL;
        iPhoneValues[index] = NULL;
        iTimeValues[index] = NULL;
        iDateValues[index] = NULL;
        iDurationValues[index] = NULL;
        }
    }

// ----------------------------------------------------------------------------
// void CAknExPopFieldMultiPageDialog::DiscardArray()
// Discard array in popup field object.
// ----------------------------------------------------------------------------
//
void CAknExPopFieldMultiPageDialog::DiscardArray()
    {
    if ( iTextArray )
        {
        delete iTextArray;
        iTextArray = NULL;
        }
    if ( iValueTextArray )
        {
        delete iValueTextArray;
        iValueTextArray = NULL;
        }
    if ( iNumberArray )
        {
        delete iNumberArray;
        iNumberArray = NULL;
        }
    if ( iValueNumberArray )
        {
        delete iValueNumberArray;
        iValueNumberArray = NULL;
        }
    if ( iPhoneArray )
        {
        delete iPhoneArray;
        iPhoneArray = NULL;
        }
    if ( iValuePhoneArray )
        {
        delete iValuePhoneArray;
        iValuePhoneArray = NULL;
        }
    if ( iTimeArray )
        {
        delete iTimeArray;
        iTimeArray = NULL;
        }
    if ( iValueTimeArray )
        {
        delete iValueTimeArray;
        iValueTimeArray = NULL;
        }
    if ( iDateArray )
        {
        delete iDateArray;
        iDateArray = NULL;
        }
    if ( iValueDateArray )
        {
        delete iValueDateArray;
        iValueDateArray = NULL;
        }
    if ( iDurationArray )
        {
        delete iDurationArray;
        iDurationArray = NULL;
        }
    if ( iValueDurationArray )
        {
        delete iValueDurationArray;
        iValueDurationArray = NULL;
        }

    TInt index( KAknExPopFieldIndexInitialize );
    for ( index = KAknExPopFieldIndexInitialize;
          index < KAknExPopFieldMaxMultiPageValueField; index++ )
        {
        if ( iTextValues[index] )
            {
            delete iTextValues[index];
            iTextValues[index] = NULL;
            }
        if ( iNumberValues[index] )
            {
            delete iNumberValues[index];
            iNumberValues[index] = NULL;
            }
        if ( iPhoneValues[index] )
            {
            delete iPhoneValues[index];
            iPhoneValues[index] = NULL;
            }
        if ( iTimeValues[index] )
            {
            delete iTimeValues[index];
            iTimeValues[index] = NULL;
            }
        if ( iDateValues[index] )
            {
            delete iDateValues[index];
            iDateValues[index] = NULL;
            }
        if ( iDurationValues[index] )
            {
            delete iDurationValues[index];
            iDurationValues[index] = NULL;
            }
        }
    }

// ----------------------------------------------------------------------------
// void CAknExPopFieldMultiPageDialog::ConfigurePopfieldValueL()
// Configuration values into Popup Fields.
// ----------------------------------------------------------------------------
//
void CAknExPopFieldMultiPageDialog::ConfigurePopfieldValueL()
    {
    // Discard array.
    DiscardArray();

    ConfigurePageTextL();
    ConfigurePageNumberL();
    ConfigurePagePhoneL();
    ConfigurePageTimeL();
    ConfigurePageDateL();
    ConfigurePageDurationL();
    }

// ----------------------------------------------------------------------------
// void CAknExPopFieldMultiPageDialog::ConfigurePageTextL()
// Configuration values (text) into Popup Fields.
// ----------------------------------------------------------------------------
//
void CAknExPopFieldMultiPageDialog::ConfigurePageTextL()
    {
    // Calculate number of pop-up field.
    TInt index( KAknExPopFieldIndexInitialize );
    TInt count( KAknExPopFieldCountInitialize );
    TInt controlId( KAknExPopFieldControlIdInitialize );
    CAknPopupField* popup[KAknExPopFieldMaxMultiPageValueField];
    for ( index = KAknExPopFieldIndexInitialize;
          index < KAknExPopFieldMaxMultiPageValueField; index++ )
        {
        popup[index] = NULL;
        controlId = EAknExPopFieldDlgCtrlIdText01 + index;
        CCoeControl* control = ControlOrNull( controlId );
        if ( control )
            {
            popup[count] = STATIC_CAST( CAknPopupField*, control );
            count++;
            }
        }

    // Create text array.
    iTextArray = iCoeEnv->ReadDesCArrayResourceL(
        R_AKNEXPOPFIELD_SIX_TEXT_ARRAY );
    iValueTextArray = CAknQueryValueTextArray::NewL();
    iValueTextArray->SetArray( *iTextArray );

    // Set the same array into all the values, and initial value index.
    for ( index = KAknExPopFieldIndexInitialize; index < count; index++ )
        {
        iTextValues[index] = CAknQueryValueText::NewL();
        iTextValues[index]->SetArrayL( iValueTextArray );
        iTextValues[index]->SetCurrentValueIndex( NULL );
        iTextValues[index]->SetQueryCaption( R_AKNEXPOPFIELD_QUERY_PROMPT );
        }

    // Set values into popup fields.
    for ( index = KAknExPopFieldIndexInitialize; index < count; index++ )
        {
        popup[index]->SetQueryValueL( iTextValues[index] );
        }
    }

// ----------------------------------------------------------------------------
// void CAknExPopFieldMultiPageDialog::ConfigurePageNumberL()
// Configuration values (number) into Popup Fields.
// ----------------------------------------------------------------------------
//
void CAknExPopFieldMultiPageDialog::ConfigurePageNumberL()
    {
    // Calculate number of pop-up field.
    TInt index( KAknExPopFieldIndexInitialize );
    TInt count( KAknExPopFieldCountInitialize );
    TInt controlId( KAknExPopFieldControlIdInitialize );
    CAknPopupField* popup[KAknExPopFieldMaxMultiPageValueField];
    for ( index = KAknExPopFieldIndexInitialize;
          index < KAknExPopFieldMaxMultiPageValueField; index++ )
        {
        popup[index] = NULL;
        controlId = EAknExPopFieldDlgCtrlIdNum01 + index;
        CCoeControl* control = ControlOrNull( controlId );
        if ( control )
            {
            popup[count] = STATIC_CAST( CAknPopupField*, control );
            count++;
            }
        }

    // create an array of numbers
    iNumberArray = new( ELeave ) CArrayFixFlat<TInt>(
        KAknExPopFieldInitialArrayElementCount );
    TInt value( KAknExPopFieldValueInitialize );
    for ( value = KAknExPopFieldNumberArrayMinimumValue;
          value < KAknExPopFieldNumberArrayMaximumValue ;
          value += KAknExPopFieldNumberArrayStepValue )
        {
        iNumberArray->AppendL( value );
        }

    // wrap the number array
    iValueNumberArray = CAknQueryValueNumberArray::NewL(
        R_AKNEXPOPFIELD_NUM_FORMAT_STRING_TEXT );
    iValueNumberArray->SetArray( *iNumberArray );

    // set the same array into all the values, and set initial index values
    for ( index = KAknExPopFieldIndexInitialize; index < count; index++)
        {
        iNumberValues[index] = CAknQueryValueNumber::NewL();
        iNumberValues[index]->SetArrayL( iValueNumberArray );
        iNumberValues[index]->SetCurrentValueIndex( NULL );
        iNumberValues[index]->SetQueryCaption( R_AKNEXPOPFIELD_QUERY_PROMPT );
        }

    // set values into popup fields
    for ( index = KAknExPopFieldIndexInitialize; index < count; index++ )
        {
        popup[index]->SetQueryValueL( iNumberValues[index] );
        }
    }

// ----------------------------------------------------------------------------
// void CAknExPopFieldMultiPageDialog::ConfigurePagePhoneL()
// Configuration values (phone) into Popup Fields.
// ----------------------------------------------------------------------------
//
void CAknExPopFieldMultiPageDialog::ConfigurePagePhoneL()
    {
    // Calculate number of pop-up field.
    TInt index( KAknExPopFieldIndexInitialize );
    TInt count( KAknExPopFieldCountInitialize );
    TInt controlId( KAknExPopFieldControlIdInitialize );
    CAknPopupField* popup[KAknExPopFieldMaxMultiPageValueField];
    for ( index = KAknExPopFieldIndexInitialize;
          index < KAknExPopFieldMaxMultiPageValueField; index++ )
        {
        popup[index] = NULL;
        controlId = EAknExPopFieldDlgCtrlIdPhon01 + index;
        CCoeControl* control = ControlOrNull( controlId );
        if ( control )
            {
            popup[count] = STATIC_CAST( CAknPopupField*, control );
            count++;
            }
        }

    // create an array of phone
    iPhoneArray = iCoeEnv->ReadDesCArrayResourceL(
        R_AKNEXPOPFIELD_SIX_PHONE_ARRAY );
    iValuePhoneArray = CAknQueryValuePhoneArray::NewL();
    iValuePhoneArray->SetArray( *iPhoneArray );

    // set the same array into all the values, and set initial index values
    for ( index = KAknExPopFieldIndexInitialize; index < count; index++ )
        {
        iPhoneValues[index] = CAknQueryValuePhone::NewL();
        iPhoneValues[index]->SetArrayL( iValuePhoneArray );
        iPhoneValues[index]->SetCurrentValueIndex( NULL );
        iPhoneValues[index]->SetQueryCaption( R_AKNEXPOPFIELD_QUERY_PROMPT );
        }
    // set values into popup fields
    for ( index = KAknExPopFieldIndexInitialize; index < count; index++ )
        {
        popup[index]->SetQueryValueL( iPhoneValues[index] );
        }
    }

// ----------------------------------------------------------------------------
// void CAknExPopFieldMultiPageDialog::ConfigurePageTimeL()
// Configuration values (time) into Popup Fields.
// ----------------------------------------------------------------------------
//
void CAknExPopFieldMultiPageDialog::ConfigurePageTimeL()
    {
    // Calculate number of pop-up field.
    TInt index( KAknExPopFieldIndexInitialize );
    TInt count( KAknExPopFieldCountInitialize );
    TInt controlId( KAknExPopFieldControlIdInitialize );
    CAknPopupField* popup[KAknExPopFieldMaxMultiPageValueField];
    for ( index = KAknExPopFieldIndexInitialize;
          index < KAknExPopFieldMaxMultiPageValueField; index++ )
        {
        popup[index] = NULL;
        controlId = EAknExPopFieldDlgCtrlIdTime01 + index;
        CCoeControl* control = ControlOrNull( controlId );
        if ( control )
            {
            popup[count] = STATIC_CAST( CAknPopupField*, control );
            count++;
            }
        }

    // create an array of time
    TBuf<KAknExPopFieldArrayTextBufLength> text( NULL );
    iCoeEnv->ReadResource( text, R_AKNEXPOPFIELD_TIME_INITIAL_TEXT );
    iTimeArray = new( ELeave ) CArrayFixFlat<TTime>(
        KAknExPopFieldInitialArrayElementCount );
    TTime value( text );
    TInt step( KAknExPopFieldStepInitialize );
    for ( step = KAknExPopFieldStepInitialize;
          step < KAknExPopFieldTimeArrayStepNumber; step++ )
        {
        iTimeArray->AppendL( value );
        value += KAknExPopFieldTimeArrayStepHour;
        }

    // wrap the time array
    iValueTimeArray = CAknQueryValueTimeArray::NewL(
        R_AKNEXPOPFIELD_TIME_FORMAT_STRING_TEXT );
    iValueTimeArray->SetArray( *iTimeArray );

    // set the same array into all the values, and set initial index values
    for ( index = KAknExPopFieldIndexInitialize; index < count; index++ )
        {
        iTimeValues[index] = CAknQueryValueTime::NewL();
        iTimeValues[index]->SetArrayL( iValueTimeArray );
        iTimeValues[index]->SetCurrentValueIndex( NULL );
        iTimeValues[index]->SetQueryCaption( R_AKNEXPOPFIELD_QUERY_PROMPT );
        }

    // set values into popup fields
    for ( index = KAknExPopFieldIndexInitialize; index < count; index++ )
        {
        popup[index]->SetQueryValueL( iTimeValues[index] );
        }
    }

// ----------------------------------------------------------------------------
// void CAknExPopFieldMultiPageDialog::ConfigurePageDateL()
// Configuration values (date) into Popup Fields.
// ----------------------------------------------------------------------------
//
void CAknExPopFieldMultiPageDialog::ConfigurePageDateL()
    {
    // Calculate number of pop-up field.
    TInt index( KAknExPopFieldIndexInitialize );
    TInt count( KAknExPopFieldCountInitialize );
    TInt controlId( KAknExPopFieldControlIdInitialize );
    CAknPopupField* popup[KAknExPopFieldMaxMultiPageValueField];
    for ( index = KAknExPopFieldIndexInitialize;
          index < KAknExPopFieldMaxMultiPageValueField; index++ )
        {
        popup[index] = NULL;
        controlId = EAknExPopFieldDlgCtrlIdDate01 + index;
        CCoeControl* control = ControlOrNull( controlId );
        if ( control )
            {
            popup[count] = STATIC_CAST( CAknPopupField*, control );
            count++;
            }
        }

    // create an array of date
    TBuf<KAknExPopFieldArrayTextBufLength> text( NULL );
    iCoeEnv->ReadResource( text, R_AKNEXPOPFIELD_DATE_INITIAL_TEXT );
    iDateArray = new( ELeave ) CArrayFixFlat<TTime>(
        KAknExPopFieldInitialArrayElementCount );
    TTime value( text );
    TInt step( KAknExPopFieldStepInitialize );
    for ( step = KAknExPopFieldStepInitialize;
          step < KAknExPopFieldDateArrayStepNumber; step++ )
        {
        iDateArray->AppendL( value );
        value += KAknExPopFieldDateArrayStepDay;
        }

    // wrap the date array
    iValueDateArray = CAknQueryValueDateArray::NewL(
        R_AKNEXPOPFIELD_DATE_FORMAT_STRING_TEXT );
    iValueDateArray->SetArray( *iDateArray );

    // set the same array into all the values, and set initial index values
    for ( index = KAknExPopFieldIndexInitialize; index < count; index++ )
        {
        iDateValues[index] = CAknQueryValueDate::NewL();
        iDateValues[index]->SetArrayL( iValueDateArray );
        iDateValues[index]->SetCurrentValueIndex( NULL );
        iDateValues[index]->SetQueryCaption( R_AKNEXPOPFIELD_QUERY_PROMPT );
        }
    // set values into popup fields
    for ( index = KAknExPopFieldIndexInitialize; index < count; index++ )
        {
        popup[index]->SetQueryValueL( iDateValues[index] );
        }
    }

// ----------------------------------------------------------------------------
// void CAknExPopFieldMultiPageDialog::ConfigurePageDurationL()
// Configuration values (duration) into Popup Fields.
// ----------------------------------------------------------------------------
//
void CAknExPopFieldMultiPageDialog::ConfigurePageDurationL()
    {
    // Calculate number of pop-up field.
    TInt index( KAknExPopFieldIndexInitialize );
    TInt count( KAknExPopFieldCountInitialize );
    TInt controlId( KAknExPopFieldControlIdInitialize );
    CAknPopupField* popup[KAknExPopFieldMaxMultiPageValueField];
    for ( index = KAknExPopFieldIndexInitialize;
          index < KAknExPopFieldMaxMultiPageValueField; index++ )
        {
        popup[index] = NULL;
        controlId = EAknExPopFieldDlgCtrlIdDura01 + index;
        CCoeControl* control = ControlOrNull( controlId );
        if ( control )
            {
            popup[count] = STATIC_CAST( CAknPopupField*, control );
            count++;
            }
        }

    // create an array of duration
    iDurationArray = new( ELeave ) CArrayFixFlat<TTimeIntervalSeconds>(
        KAknExPopFieldInitialArrayElementCount );
    TInt value( KAknExPopFieldValueInitialize ); 
    for ( value = KAknExPopFieldDuraArrayMinimumValue;
          value < KAknExPopFieldDuraArrayMaximumValue;
          value += KAknExPopFieldDuraArrayStepValue )
        {
        TTimeIntervalSeconds interval( value );
        iDurationArray->AppendL( interval );
        }

    // wrap the duration array
    iValueDurationArray = CAknQueryValueDurationArray::NewL(
        R_AKNEXPOPFIELD_DURA_FORMAT_STRING_TEXT );
    iValueDurationArray->SetArray( *iDurationArray );

    // set the same array into all the values, and set initial index values
    for ( index = KAknExPopFieldIndexInitialize; index < count; index++ )
        {
        iDurationValues[index] = CAknQueryValueDuration::NewL();
        iDurationValues[index]->SetArrayL( iValueDurationArray );
        iDurationValues[index]->SetCurrentValueIndex( NULL );
        iDurationValues[index]->SetQueryCaption( R_AKNEXPOPFIELD_QUERY_PROMPT );
        }

    // set values into popup fields
    for ( index = KAknExPopFieldIndexInitialize; index < count; index++ )
        {
        popup[index]->SetQueryValueL( iDurationValues[index] );
        }
    }

// ----------------------------------------------------------------------------
// CAknExPopFieldMultiPageDialog::SaveFormDataL()
// Save form data.
// ----------------------------------------------------------------------------
//
TBool CAknExPopFieldMultiPageDialog::SaveFormDataL()
    {
    for(TInt i = KAknExPopFieldIndexInitialize;
             i < KAknExPopFieldMaxMultiPageValueField; i++)
        {
        if(ControlOrNull(EAknExPopFieldDlgCtrlIdText01+i))
            {
            iIndexValueText[i] = iTextValues[i]->CurrentValueIndex();
            }
        if(ControlOrNull(EAknExPopFieldDlgCtrlIdNum01+i))
            {
            iIndexValueNumber[i] = iNumberValues[i]->CurrentValueIndex();
            }
        if(ControlOrNull(EAknExPopFieldDlgCtrlIdPhon01+i))
            {
            iIndexValuePhone[i] = iPhoneValues[i]->CurrentValueIndex();
            }
        if(ControlOrNull(EAknExPopFieldDlgCtrlIdTime01+i))
            {
            iIndexValueTime[i] = iTimeValues[i]->CurrentValueIndex();
            }
        if(ControlOrNull(EAknExPopFieldDlgCtrlIdDate01+i))
            {
            iIndexValueDate[i] = iDateValues[i]->CurrentValueIndex();
            }
        if(ControlOrNull(EAknExPopFieldDlgCtrlIdDura01+i))
            {
            iIndexValueDuration[i] = iDurationValues[i]->CurrentValueIndex();
            }
        }

    return ETrue;
    }

// ----------------------------------------------------------------------------
// CAknExPopFieldMultiPageDialog::DoNotSaveFormDataL()
// Does not save form data.
// ----------------------------------------------------------------------------
//
void CAknExPopFieldMultiPageDialog::DoNotSaveFormDataL()
    {
    for(TInt i = KAknExPopFieldIndexInitialize;
             i < KAknExPopFieldMaxMultiPageValueField; i++)
        {
        if(ControlOrNull(EAknExPopFieldDlgCtrlIdText01+i))
            {
            iTextValues[i]->SetCurrentValueIndex(iIndexValueText[i]);
            }
        if(ControlOrNull(EAknExPopFieldDlgCtrlIdNum01+i))
            {
            iNumberValues[i]->SetCurrentValueIndex(iIndexValueNumber[i]);
            }
        if(ControlOrNull(EAknExPopFieldDlgCtrlIdPhon01+i))
            {
            iPhoneValues[i]->SetCurrentValueIndex(iIndexValuePhone[i]);
            }
        if(ControlOrNull(EAknExPopFieldDlgCtrlIdTime01+i))
            {
            iTimeValues[i]->SetCurrentValueIndex(iIndexValueTime[i]);
            }
        if(ControlOrNull(EAknExPopFieldDlgCtrlIdDate01+i))
            {
            iDateValues[i]->SetCurrentValueIndex(iIndexValueDate[i]);
            }
        if(ControlOrNull(EAknExPopFieldDlgCtrlIdDura01+i))
            {
            iDurationValues[i]->SetCurrentValueIndex(iIndexValueDuration[i]);
            }
        }
    }

// End of File
