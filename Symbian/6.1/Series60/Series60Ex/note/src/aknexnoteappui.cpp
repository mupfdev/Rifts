/*
* =============================================================================
*  Name     : CAknExNoteAppUi
*  Part of  : AknExNote
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

// INCLUDE FILES
#include "AknExNoteAppUi.h"
#include "AknExNoteView.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExNoteAppUi::CAknexNoteAppUi()
// Default constructor.
// ----------------------------------------------------------------------------
//
CAknExNoteAppUi::CAknExNoteAppUi()
    {
    }

// ----------------------------------------------------------------------------
// void CAknExNoteAppUi::ConstructL()
// EPOC constructor.
// ----------------------------------------------------------------------------
//
void CAknExNoteAppUi::ConstructL()
    {
    BaseConstructL();
    // Creates CAknExNoteView class object.
    CAknExNoteView* view = new( ELeave ) CAknExNoteView;
    CleanupStack::PushL( view );
    view->ConstructL();
    CleanupStack::Pop(); // view
    AddViewL( view ); // transfer ownership to CAknViewAppUi.
    ActivateLocalViewL( view->Id() );
    }

// ----------------------------------------------------------------------------
// CAknExNoteAppUi::~CAknExNoteAppUi()
// Destructor.
// ----------------------------------------------------------------------------
//
CAknExNoteAppUi::~CAknExNoteAppUi()
    {
    }

// ----------------------------------------------------------------------------
// void CAknExNoteAppUi::HandleCommandL( TInt )
// Handles the commands.
// ----------------------------------------------------------------------------
//
void CAknExNoteAppUi::HandleCommandL( TInt aCommand )
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
