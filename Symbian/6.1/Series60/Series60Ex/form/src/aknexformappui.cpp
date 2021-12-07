/*
* ============================================================================
*  Name     : CAknExFormAppUi
*  Part of  : AknExForm
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#include <avkon.hrh>
#include "AknExFormAppUi.h"
#include "AknExFormView.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExFormAppUi::CAknExFormAppUi()
// Default constructor.
// ----------------------------------------------------------------------------
//
CAknExFormAppUi::CAknExFormAppUi()
    {
    }

// ----------------------------------------------------------------------------
// void CAknExFormAppUi::ConstructL()
// EPOC constructor.
// ----------------------------------------------------------------------------
//
void CAknExFormAppUi::ConstructL()
    {
    BaseConstructL();

    // Creates CAknExFormView class object.
    CAknExFormView* view = new( ELeave ) CAknExFormView;
    CleanupStack::PushL( view );
    view->ConstructL();
    AddViewL( view ); // transfer ownership to CAknViewAppUi.
    CleanupStack::Pop(); // view

    ActivateLocalViewL( view->Id() );
    }

// ----------------------------------------------------------------------------
// CAknExFormAppUi::~CAknExFormAppUi()
// Destructor.
// ----------------------------------------------------------------------------
//
CAknExFormAppUi::~CAknExFormAppUi()
    {
    }

// ----------------------------------------------------------------------------
// void CAknExFormAppUi::HandleCommandL( TInt )
// Handles the commands.
// ----------------------------------------------------------------------------
//
void CAknExFormAppUi::HandleCommandL( TInt aCommand )
    {
    switch ( aCommand )
        {
        case EAknSoftkeyBack:
        case EEikCmdExit:
            Exit();
            break;
        default:
            break;
        }
    }

// End of File
