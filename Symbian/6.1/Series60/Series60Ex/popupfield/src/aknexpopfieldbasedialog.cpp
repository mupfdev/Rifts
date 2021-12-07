/*
* =============================================================================
*  Name     : CAknExPopFieldBaseDialog
*  Part of  : AknExPopField
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

// INCLUDE FILES
#include <eikmenub.h>
#include <eikappui.h>
#include <eikenv.h>
#include <avkon.hrh>
#include <avkon.rsg>
#include "AknExPopFieldBaseDialog.h"

// MACROS

// CONSTANTS

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExPopFieldBaseDialog::~CAknExPopFieldBaseDialog()
// Destructor.
// ----------------------------------------------------------------------------
//
CAknExPopFieldBaseDialog::~CAknExPopFieldBaseDialog()
    {
    ///iEikonEnv->EikAppUi()->RemoveFromStack( this );
    }

// ----------------------------------------------------------------------------
// CAknExPopFieldBaseDialog::CAknExPopFieldBaseDialog()
// Constructor.
// ----------------------------------------------------------------------------
//
CAknExPopFieldBaseDialog::CAknExPopFieldBaseDialog()
    {
    }

// ----------------------------------------------------------------------------
// void CAknExPopFieldBaseDialog::DynInitMenuPaneL( TInt, CEikMenuPane* )
// Dims "Label", "Add" and "Delete" menu items.
// ----------------------------------------------------------------------------
//
void CAknExPopFieldBaseDialog::DynInitMenuPaneL(
    TInt aResourceId,
    CEikMenuPane* aMenuPane )
    {
    CAknForm::DynInitMenuPaneL( aResourceId, aMenuPane );
    if ( aResourceId == R_AVKON_FORM_MENUPANE )
        {
        aMenuPane->SetItemDimmed( EAknFormCmdLabel, ETrue );
        aMenuPane->SetItemDimmed( EAknFormCmdAdd, ETrue );
        aMenuPane->SetItemDimmed( EAknFormCmdDelete, ETrue );
        }
    }

// ----------------------------------------------------------------------------
// void CAknExPopFieldBaseDialog::ProcessCommandL( TInt, CEikMenuPane* )
// Overridden to supply a location for calls to PopupField APIs.
// ----------------------------------------------------------------------------
//
void CAknExPopFieldBaseDialog::ProcessCommandL( TInt aCommandId )
	{
	CAknForm::ProcessCommandL( aCommandId );
	}

// ----------------------------------------------------------------------------
// TBool CAknExPopFieldBaseDialog::OkToExitL( TInt aButtonId )
// Overridden to supply a location for the PopupFieldText test.
// ----------------------------------------------------------------------------
//
TBool CAknExPopFieldBaseDialog::OkToExitL( TInt aButtonId )
	{
	return CAknForm::OkToExitL( aButtonId );
	}

// ----------------------------------------------------------------------------
// void CAknExPopFieldPopupFieldDialog::PreLayoutDynInitL()
// Initialises the dialog's controls before the dialog is sized and layed out.
// ----------------------------------------------------------------------------
//
void CAknExPopFieldBaseDialog::PreLayoutDynInitL()
    {
    ConfigurePopfieldValueL();
    }

// ----------------------------------------------------------------------------
// void CAknExPopFieldPopupFieldDialog::PostLayoutDynInitL()
// Initialises the dialog's controls after the dialog has been sized
// but before it has been activated.
// ----------------------------------------------------------------------------
//
void CAknExPopFieldBaseDialog::PostLayoutDynInitL()
    {
    SetEditableL( EFalse );
    SaveFormDataL();
    }

// End of File
