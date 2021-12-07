/*
* =============================================================================
*  Name     : CAknExPopFieldAppUi
*  Part of  : AknExPopField
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

#include <avkon.hrh>
#include "AknExPopFieldAppUi.h"
#include "AknExPopFieldView.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExPopFieldAppUi::CAknExPopFieldAppUi()
// Default constructor.
// ----------------------------------------------------------------------------
//
CAknExPopFieldAppUi::CAknExPopFieldAppUi()
    {
    }

// ----------------------------------------------------------------------------
// void CAknExPopFieldAppUi::ConstructL()
// EPOC constructor.
// ----------------------------------------------------------------------------
//
void CAknExPopFieldAppUi::ConstructL()
    {
    BaseConstructL();

    // Creates CAknExPopFieldView class object.
    CAknExPopFieldView* view = new( ELeave ) CAknExPopFieldView;
    CleanupStack::PushL( view );
    view->ConstructL();
    AddViewL( view ); // transfer ownership to CAknViewAppUi.
    CleanupStack::Pop(); // view

    ActivateLocalViewL( view->Id() );
    }

// ----------------------------------------------------------------------------
// CAknExPopFieldAppUi::~CAknExPopFieldAppUi()
// Destructor.
// ----------------------------------------------------------------------------
//
CAknExPopFieldAppUi::~CAknExPopFieldAppUi()
    {
    }

// ----------------------------------------------------------------------------
// void CAknExPopFieldAppUi::HandleCommandL( TInt )
// Handles the commands.
// ----------------------------------------------------------------------------
//
void CAknExPopFieldAppUi::HandleCommandL( TInt aCommand )
    {
    switch ( aCommand )
        {
        case EEikCmdExit:
            Exit();
            break;
        default:
            break;
        }
    }

// End of File
