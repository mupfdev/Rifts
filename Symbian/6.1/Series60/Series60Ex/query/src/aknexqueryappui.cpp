/*
* =============================================================================
*  Name     : CAknExQueryAppUi
*  Part of  : AknExQuery
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

// INCLUDE FILES
#include <Avkon.hrh>
#include "AknExQueryAppUi.h"
#include "AknExQueryView.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExQueryAppUi::CAknExQueryAppUi()
// Default constructor.
// ----------------------------------------------------------------------------
//
CAknExQueryAppUi::CAknExQueryAppUi()
    {
    }

// ----------------------------------------------------------------------------
// CAknExQueryAppUi::ConstructL()
// Constructor.
// ----------------------------------------------------------------------------
//
void CAknExQueryAppUi::ConstructL()
    {
    BaseConstructL();

    CAknExQueryView* view = new( ELeave ) CAknExQueryView;
    CleanupStack::PushL( view );
    AddViewL( view ); // transfer ownership to CAknViewAppUi
    CleanupStack::Pop();

    ActivateLocalViewL( view->Id() );
    }

// ----------------------------------------------------------------------------
// CAknExQueryAppUi::~CAknExQueryAppUi()
// Destructor
// Frees reserved resources
// ----------------------------------------------------------------------------
//
CAknExQueryAppUi::~CAknExQueryAppUi()
    {
    }

// ----------------------------------------------------------------------------
// CAknExQueryAppUi::HandleCommandL( TInt aCommand )
// Handles the commands.
// ----------------------------------------------------------------------------
//
void CAknExQueryAppUi::HandleCommandL( TInt aCommand )
    {
    switch ( aCommand )
        {
        case EEikCmdExit:
        case EAknCmdExit:
            Exit();
            break;
        default:
            break;
        }
    }

// End of File
