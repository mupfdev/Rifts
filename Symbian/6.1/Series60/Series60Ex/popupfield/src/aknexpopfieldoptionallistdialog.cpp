/*
* =============================================================================
*  Name     : CAknExPopFieldOptionalListDialog
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
#include "AknExPopFieldOptionalListDialog.h"

// MACROS

// CONSTANTS
const TInt KAknExPopFieldIndexInitialize = 0;
const TInt KAknExPopFieldCountInitialize = 0;
const TInt KAknExPopFieldControlIdInitialize = 0;
const TInt KAknExPopFieldEmptyFieldIndex = 0;
const TInt KAknExPopFieldInitialArrayElementCount = 4;

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExPopFieldOptionalListDialog* CAknExPopFieldOptionalListDialog::NewLC()
// EPOC two-phase constructor.
// ----------------------------------------------------------------------------
//
CAknExPopFieldOptionalListDialog* CAknExPopFieldOptionalListDialog::NewLC()
    {
    CAknExPopFieldOptionalListDialog* self =
        new( ELeave ) CAknExPopFieldOptionalListDialog;
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }

// ----------------------------------------------------------------------------
// CAknExPopFieldOptionalListDialog::~CAknExPopFieldOptionalListDialog()
// Destructor.
// ----------------------------------------------------------------------------
//
CAknExPopFieldOptionalListDialog::~CAknExPopFieldOptionalListDialog()
    {
    DiscardTextArray();
    }

// ----------------------------------------------------------------------------
// CAknExPopFieldOptionalListDialog::CAknExPopFieldOptionalListDialog()
// Constructor.
// ----------------------------------------------------------------------------
//
CAknExPopFieldOptionalListDialog::CAknExPopFieldOptionalListDialog()
    {
    TInt index( KAknExPopFieldIndexInitialize );
    for ( index = KAknExPopFieldIndexInitialize;
          index < KAknExPopFieldMaxOLTextValueField; index++ )
        {
        iTextArray[index] = NULL;
        iValueTextArray[index] = NULL;
        iTextValues[index] = NULL;
        }
    }

// ----------------------------------------------------------------------------
// void CAknExPopFieldOptionalListDialog::DiscardTextArray()
// Discard text array in popup field object.
// ----------------------------------------------------------------------------
//
void CAknExPopFieldOptionalListDialog::DiscardTextArray()
    {
    TInt index( KAknExPopFieldIndexInitialize );
    for ( index = KAknExPopFieldIndexInitialize;
          index < KAknExPopFieldMaxOLTextValueField; index++ )
        {
        if ( iTextValues[index] )
            {
            delete iTextValues[index];
            iTextValues[index] = NULL;
            }
        if ( iValueTextArray[index] )
            {
            delete iValueTextArray[index];
            iValueTextArray[index] = NULL;
            }
        if ( iTextArray[index] )
            {
            delete iTextArray[index];
            iTextArray[index] = NULL;
            }
        }
    }

// ----------------------------------------------------------------------------
// void CAknExPopFieldOptionalListDialog::ConfigurePopfieldValueL()
// Configuration values (text) into Popup Fields.
// ----------------------------------------------------------------------------
//
void CAknExPopFieldOptionalListDialog::ConfigurePopfieldValueL()
    {
    // Discard textarray.
    DiscardTextArray();

    // Calculate number of pop-up field.
    TInt index( KAknExPopFieldIndexInitialize );
    TInt count( KAknExPopFieldCountInitialize );
    TInt controlId( KAknExPopFieldControlIdInitialize );
    CAknPopupField* popup[KAknExPopFieldMaxOLTextValueField];
    for ( index = KAknExPopFieldIndexInitialize;
          index < KAknExPopFieldMaxOLTextValueField; index++ )
        {
        popup[index] = NULL;
        controlId = EAknExPopFieldDlgCtrlIdPop00 + index;
        CCoeControl* control = ControlOrNull( controlId );
        if ( control )
            {
            popup[count] = STATIC_CAST( CAknPopupField*, control );
            count++;
            }
        }

    // Create textarray.
    iTextArray[EAknExPopFieldTextArrayIndex0] =
        new( ELeave ) CDesCArrayFlat( KAknExPopFieldInitialArrayElementCount );
    iTextArray[EAknExPopFieldTextArrayIndex1] =
        iCoeEnv->ReadDesCArrayResourceL( R_AKNEXPOPFIELD_ONE_TEXT_ARRAY );
    iTextArray[EAknExPopFieldTextArrayIndex2] =
        iCoeEnv->ReadDesCArrayResourceL( R_AKNEXPOPFIELD_TWO_TEXT_ARRAY );
    iTextArray[EAknExPopFieldTextArrayIndex3] =
        iCoeEnv->ReadDesCArrayResourceL( R_AKNEXPOPFIELD_THREE_TEXT_ARRAY );
    iTextArray[EAknExPopFieldTextArrayIndex4] =
        iCoeEnv->ReadDesCArrayResourceL( R_AKNEXPOPFIELD_FOUR_TEXT_ARRAY );
    iTextArray[EAknExPopFieldTextArrayIndex5] =
        iCoeEnv->ReadDesCArrayResourceL( R_AKNEXPOPFIELD_FIVE_TEXT_ARRAY );
    iTextArray[EAknExPopFieldTextArrayIndex6] =
        iCoeEnv->ReadDesCArrayResourceL( R_AKNEXPOPFIELD_SIX_TEXT_ARRAY );
    iTextArray[EAknExPopFieldTextArrayIndex7] =
        iCoeEnv->ReadDesCArrayResourceL( R_AKNEXPOPFIELD_SEVEN_TEXT_ARRAY );
    iTextArray[EAknExPopFieldTextArrayIndex8] =
        iCoeEnv->ReadDesCArrayResourceL( R_AKNEXPOPFIELD_EIGHT_TEXT_ARRAY );
    iTextArray[EAknExPopFieldTextArrayIndex9] =
        iCoeEnv->ReadDesCArrayResourceL( R_AKNEXPOPFIELD_NINE_TEXT_ARRAY );
    iTextArray[EAknExPopFieldTextArrayIndex10] =
        iCoeEnv->ReadDesCArrayResourceL( R_AKNEXPOPFIELD_TEN_TEXT_ARRAY );
    iTextArray[EAknExPopFieldTextArrayIndex11] =
        iCoeEnv->ReadDesCArrayResourceL( R_AKNEXPOPFIELD_ELEVEN_TEXT_ARRAY );
    iTextArray[EAknExPopFieldTextArrayIndex12] =
        iCoeEnv->ReadDesCArrayResourceL( R_AKNEXPOPFIELD_TWELVE_TEXT_ARRAY );

    for ( index = KAknExPopFieldIndexInitialize; index < count; index++ )
        {
        iValueTextArray[index] = CAknQueryValueTextArray::NewL();
        iValueTextArray[index]->SetArray( *iTextArray[index] );
        }

    // Set the same textarray into all the values, and initial value index.
    for ( index = KAknExPopFieldIndexInitialize; index < count; index++ )
        {
        iTextValues[index] = CAknQueryValueText::NewL();
        iTextValues[index]->SetArrayL( iValueTextArray[index] );
        if ( index != KAknExPopFieldEmptyFieldIndex ) // array is no empty
            {
            iTextValues[index]->SetCurrentValueIndex( NULL );
            iTextValues[index]->SetQueryCaption( R_AKNEXPOPFIELD_QUERY_PROMPT );
            }
        }

    // Set values into popup fields.
    for ( index = KAknExPopFieldIndexInitialize; index < count; index++ )
        {
        popup[index]->SetQueryValueL( iTextValues[index] );
        }
    }

// ----------------------------------------------------------------------------
// CAknExPopFieldOptionalListDialog::SaveFormDataL()
// Save form data.
// ----------------------------------------------------------------------------
//
TBool CAknExPopFieldOptionalListDialog::SaveFormDataL()
    {
    for(TInt i = KAknExPopFieldIndexInitialize;
             i < KAknExPopFieldMaxOLTextValueField; i++)
        {
        if(ControlOrNull(EAknExPopFieldDlgCtrlIdPop00+i))
            {
            if (i != KAknExPopFieldEmptyFieldIndex) // array is no empty
                {
                iIndexValue[i] = iTextValues[i]->CurrentValueIndex();
                }
            }
        }

    return ETrue;
    }

// ----------------------------------------------------------------------------
// CAknExPopFieldOptionalListDialog::DoNotSaveFormDataL()
// Does not save form data.
// ----------------------------------------------------------------------------
//
void CAknExPopFieldOptionalListDialog::DoNotSaveFormDataL()
    {
    for(TInt i = KAknExPopFieldIndexInitialize;
             i < KAknExPopFieldMaxOLTextValueField; i++)
        {
        if(ControlOrNull(EAknExPopFieldDlgCtrlIdPop00+i))
            {
            if (i != KAknExPopFieldEmptyFieldIndex) // array is no empty
                {
                iTextValues[i]->SetCurrentValueIndex(iIndexValue[i]);
                }
            }
        }
    }

// End of File
