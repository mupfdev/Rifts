/*
* =============================================================================
*  Name     : CAknExPopFieldTextValueDialog
*  Part of  : AknExPopField
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

// INCLUDE FILES
#include <eikenv.h>
#include <avkon.hrh>
#include <aknpopupfield.h>
#include <aknpopupfieldtext.h>
#include <aknqueryvaluetext.h>
#include <AknExPopField.rsg>
#include "AknExPopField.hrh"
#include "AknExPopFieldTextValueDialog.h"

// MACROS

// CONSTANTS
const TInt KAknExPopFieldIndexInitialize = 0;
const TInt KAknExPopFieldCountInitialize = 0;
const TInt KAknExPopFieldControlIdInitialize = 0;

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExPopFieldTextValueDialog* CAknExPopFieldTextValueDialog::NewLC()
// EPOC two-phase constructor.
// ----------------------------------------------------------------------------
//
CAknExPopFieldTextValueDialog* CAknExPopFieldTextValueDialog::NewLC()
    {
    CAknExPopFieldTextValueDialog* self =
        new( ELeave ) CAknExPopFieldTextValueDialog;
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }

// ----------------------------------------------------------------------------
// CAknExPopFieldTextValueDialog::~CAknExPopFieldTextValueDialog()
// Destructor.
// ----------------------------------------------------------------------------
//
CAknExPopFieldTextValueDialog::~CAknExPopFieldTextValueDialog()
    {
    DiscardTextArray();
    }

// ----------------------------------------------------------------------------
// CAknExPopFieldTextValueDialog::CAknExPopFieldTextValueDialog()
// Constructor.
// ----------------------------------------------------------------------------
//
CAknExPopFieldTextValueDialog::CAknExPopFieldTextValueDialog()
:   iTextArray( NULL ),
    iValueTextArray( NULL )
    {
    TInt index( KAknExPopFieldIndexInitialize );
    for ( index = KAknExPopFieldIndexInitialize;
          index < KAknExPopFieldMaxTextValueField; index++ )
        {
        iTextValues[index] = NULL;
        }
    }

// ----------------------------------------------------------------------------
// void CAknExPopFieldTextValueDialog::DiscardTextArray()
// Discard text array in popup field object.
// ----------------------------------------------------------------------------
//
void CAknExPopFieldTextValueDialog::DiscardTextArray()
    {
    TInt index( KAknExPopFieldIndexInitialize );
    for ( index = KAknExPopFieldIndexInitialize;
          index < KAknExPopFieldMaxTextValueField; index++ )
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
// TBool CAknExPopFieldTextValueDialog::OkToExitL( TInt aButtonId )
// Implemented to test PopupFieldText API's.
// ----------------------------------------------------------------------------
//
TBool CAknExPopFieldTextValueDialog::OkToExitL( TInt aButtonId )
    {
    switch(aButtonId)
        {
        case EAknSoftkeyBack:
            {
            CAknPopupFieldText* popupFieldText[KAknExPopupFieldTextMaxValues];
            TBuf<256> textbuf;
            for(TInt i = 0; i < KAknExPopupFieldTextMaxValues; i++)
                {
                // Get the proper control
                popupFieldText[i] = (CAknPopupFieldText*) ControlOrNull(EAknExPopFieldDlgCtrlIdText01+i);
                if(popupFieldText[i])
                    {
                    // Perform the calls on the API provided by CAknPopupFieldText
                    HBufC* text = popupFieldText[i]->CurrentValueTextLC();
                    TInt value = popupFieldText[i]->CurrentValueIndex();
                    popupFieldText[i]->SetCurrentValueIndex(i);
                    popupFieldText[i]->SetAutoAppend(ETrue);
                    popupFieldText[i]->SetAllowsUserDefinedEntry(ETrue);
                    const MDesCArray* array = popupFieldText[i]->MdcArray();
                    TInt mdcaCount = array->MdcaCount();

                    // Print results to Debug 
                    textbuf.Format(_L("PopupFieldText Control Vals -> Number %d, Value %d, Text : "),i,value);
                    textbuf.Append(*text);
                    RDebug::Print(textbuf);
                    textbuf.Format(_L("... MdcaCount = %d."), mdcaCount);
                    RDebug::Print(textbuf);

                    // Clean up text
                    CleanupStack::PopAndDestroy(); // text
                    }
                }
            break;
            }
        default:
            break;
        }
    return CAknExPopFieldBaseDialog::OkToExitL( aButtonId );
    }

// ----------------------------------------------------------------------------
// void CAknExPopFieldTextValueDialog::ConfigurePopfieldValueL()
// Configuration values (text) into Popup Fields.
// ----------------------------------------------------------------------------
//
void CAknExPopFieldTextValueDialog::ConfigurePopfieldValueL()
    {
    // Discard textarray.
    DiscardTextArray();

    // Calculate number of pop-up field.
    TInt index( KAknExPopFieldIndexInitialize );
    TInt count( KAknExPopFieldCountInitialize );
    TInt controlId( KAknExPopFieldControlIdInitialize );
    CAknPopupField* popup[KAknExPopFieldMaxTextValueField];
    for ( index = KAknExPopFieldIndexInitialize;
          index < KAknExPopFieldMaxTextValueField; index++ )
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
        R_AKNEXPOPFIELD_FIVE_TEXT_ARRAY );
    iValueTextArray = CAknQueryValueTextArray::NewL();
    iValueTextArray->SetArray( *iTextArray );

    // Set the same textarray into all the values, and initial value index.
    for ( index = KAknExPopFieldIndexInitialize; index < count; index++ )
        {
        iTextValues[index] = CAknQueryValueText::NewL();
        iTextValues[index]->SetArrayL( iValueTextArray );
        iTextValues[index]->SetCurrentValueIndex( 0 );
        iTextValues[index]->SetQueryCaption( R_AKNEXPOPFIELD_QUERY_PROMPT );
        // Set values into popup fields.
        popup[index]->SetQueryValueL( iTextValues[index] ); // Moved up from below.
        }

    // Set values into popup fields.
    /*for ( index = KAknExPopFieldIndexInitialize; index < count; index++ )
        {
        popup[index]->SetQueryValueL( iTextValues[index] );
        }*/
    }

// ----------------------------------------------------------------------------
// CAknExPopFieldTextValueDialog::SaveFormDataL()
// Save form data.
// ----------------------------------------------------------------------------
//
TBool CAknExPopFieldTextValueDialog::SaveFormDataL()
    {
    for(TInt i = KAknExPopFieldIndexInitialize;
             i < KAknExPopFieldMaxTextValueField; i++)
        {
        if(ControlOrNull(EAknExPopFieldDlgCtrlIdPop01+i))
            {
            iIndexValue[i] = iTextValues[i]->CurrentValueIndex();
            }
        }

    return ETrue;
    }

// ----------------------------------------------------------------------------
// CAknExPopFieldTextValueDialog::DoNotSaveFormDataL()
// Does not save form data.
// ----------------------------------------------------------------------------
//
void CAknExPopFieldTextValueDialog::DoNotSaveFormDataL()
    {
    for(TInt i = KAknExPopFieldIndexInitialize;
             i < KAknExPopFieldMaxTextValueField; i++)
        {
        if(ControlOrNull(EAknExPopFieldDlgCtrlIdPop01+i))
            {
            iTextValues[i]->SetCurrentValueIndex(iIndexValue[i]);
            }
        }
    }

// End of File
