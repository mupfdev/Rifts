/*
* =============================================================================
*  Name     : CAknExPopFieldManyLineDialog
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
#include "AknExPopFieldManyLineDialog.h"

// MACROS

// CONSTANTS
const TInt KAknExPopFieldIndexInitialize = 0;
const TInt KAknExPopFieldCountInitialize = 0;
const TInt KAknExPopFieldControlIdInitialize = 0;

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExPopFieldManyLineDialog* CAknExPopFieldManyLineDialog::NewLC()
// EPOC two-phase constructor.
// ----------------------------------------------------------------------------
//
CAknExPopFieldManyLineDialog* CAknExPopFieldManyLineDialog::NewLC()
    {
    CAknExPopFieldManyLineDialog* self =
        new( ELeave ) CAknExPopFieldManyLineDialog;
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }

// ----------------------------------------------------------------------------
// CAknExPopFieldManyLineDialog::~CAknExPopFieldManyLineDialog()
// Destructor.
// ----------------------------------------------------------------------------
//
CAknExPopFieldManyLineDialog::~CAknExPopFieldManyLineDialog()
    {
    DiscardTextArray();
    }

// ----------------------------------------------------------------------------
// CAknExPopFieldManyLineDialog::CAknExPopFieldManyLineDialog()
// Constructor.
// ----------------------------------------------------------------------------
//
CAknExPopFieldManyLineDialog::CAknExPopFieldManyLineDialog()
:   iTextArray( NULL ),
    iValueTextArray( NULL )
    {
    TInt index( KAknExPopFieldIndexInitialize );
    for ( index = KAknExPopFieldIndexInitialize;
          index < KAknExPopFieldMaxMLTextValueField; index++ )
        {
        iTextValues[index] = NULL;
        }
    }

// ----------------------------------------------------------------------------
// void CAknExPopFieldManyLineDialog::DiscardTextArray()
// Discard text array in popup field object.
// ----------------------------------------------------------------------------
//
void CAknExPopFieldManyLineDialog::DiscardTextArray()
    {
    TInt index( KAknExPopFieldIndexInitialize );
    for ( index = KAknExPopFieldIndexInitialize;
          index < KAknExPopFieldMaxMLTextValueField; index++ )
        {
        if ( iTextValues[index] )
            {
            delete iTextValues[index];
            iTextValues[index] = NULL;
            }
        }

    if ( iValueTextArray )
        {
        delete iValueTextArray;
        iValueTextArray = NULL;
        }

    if ( iTextArray )
        {
        delete iTextArray;
        iTextArray = NULL;
        }
    }

// ----------------------------------------------------------------------------
// void CAknExPopFieldManyLineDialog::ConfigurePopfieldValueL()
// Configuration values (text) into Popup Fields.
// ----------------------------------------------------------------------------
//
void CAknExPopFieldManyLineDialog::ConfigurePopfieldValueL()
    {
    // Discard textarray.
    DiscardTextArray();

    // Calculate number of pop-up field.
    TInt index( KAknExPopFieldIndexInitialize );
    TInt count( KAknExPopFieldCountInitialize );
    TInt controlId( KAknExPopFieldControlIdInitialize );
    CAknPopupField* popup[KAknExPopFieldMaxMLTextValueField];
    for ( index = KAknExPopFieldIndexInitialize;
          index < KAknExPopFieldMaxMLTextValueField; index++ )
        {
        popup[index] = NULL;
        controlId = EAknExPopFieldDlgCtrlIdPop01 + index;
        CCoeControl* control = ControlOrNull( controlId );
        if ( control )
            {
            popup[count] = STATIC_CAST( CAknPopupField*, control );
            count++;
            }
        }

    // Create textarray.
    iTextArray = iCoeEnv->ReadDesCArrayResourceL(
        R_AKNEXPOPFIELD_TWELVE_TEXT_ARRAY );
    iValueTextArray = CAknQueryValueTextArray::NewL();
    iValueTextArray->SetArray( *iTextArray );

    // Set the same textarray into all the values, and initial value index.
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
// CAknExPopFieldManyLineDialog::SaveFormDataL()
// Save form data.
// ----------------------------------------------------------------------------
//
TBool CAknExPopFieldManyLineDialog::SaveFormDataL()
    {
    for(TInt i = KAknExPopFieldIndexInitialize;
             i < KAknExPopFieldMaxMLTextValueField; i++)
        {
        if(ControlOrNull(EAknExPopFieldDlgCtrlIdPop01+i))
            {
            iIndexValue[i] = iTextValues[i]->CurrentValueIndex();
            }
        }

    return ETrue;
    }

// ----------------------------------------------------------------------------
// CAknExPopFieldManyLineDialog::DoNotSaveFormDataL()
// Does not save form data.
// ----------------------------------------------------------------------------
//
void CAknExPopFieldManyLineDialog::DoNotSaveFormDataL()
    {
    for(TInt i = KAknExPopFieldIndexInitialize;
             i < KAknExPopFieldMaxMLTextValueField; i++)
        {
        if(ControlOrNull(EAknExPopFieldDlgCtrlIdPop01+i))
            {
            iTextValues[i]->SetCurrentValueIndex(iIndexValue[i]);
            }
        }
    }

// End of File
