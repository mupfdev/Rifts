/*
* ============================================================================
*  Name     : AknExSettingListAppUi.cpp
*  Part of  : AknExSettingList
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include <avkon.hrh>
#include "AknExSettingListAppUi.h"
#include "AknExSettingListView.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExSettingListAppUi::CAknExSettingListAppUi()
// Default constructor.
// ----------------------------------------------------------------------------
//
CAknExSettingListAppUi::CAknExSettingListAppUi()
    {
    }

// ----------------------------------------------------------------------------
// void CAknExSettingListAppUi::ConstructL()
// EPOC constructor.
// ----------------------------------------------------------------------------
//
void CAknExSettingListAppUi::ConstructL()
    {
    BaseConstructL();

    // Creates CAknExSettingListView class object.
    CAknExSettingListView* view = new( ELeave ) CAknExSettingListView;

    CleanupStack::PushL( view );
    AddViewL( view ); // transfer ownership to CAknViewAppUi
    CleanupStack::Pop(); // view

    ActivateLocalViewL( view->Id() );
    }

// ----------------------------------------------------------------------------
// CAknExSettingListAppUi::~CAknExSettingListAppUi()
// Destructor.
// ----------------------------------------------------------------------------
//
CAknExSettingListAppUi::~CAknExSettingListAppUi()
    {
    }

// ----------------------------------------------------------------------------
// void CAknExSettingListAppUi::HandleCommandL( TInt )
// Takes care of command handling.
// ----------------------------------------------------------------------------
//
void CAknExSettingListAppUi::HandleCommandL( TInt aCommand )
    {
    switch ( aCommand )
        {
        case EEikCmdExit:
            {
            Exit();
            break;
            }
        default:
            break;
        }
    }

// End of File
