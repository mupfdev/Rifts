/*
* =============================================================================
*  Name     : CAknExListAppUi
*  Part of  : AknExList
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

#include <avkon.hrh>
#include "AknExList.hrh"
#include "AknExListAppUi.h"
#include "AknExListBaseView.h"
#include "AknExListColumnView.h"
#include "AknExListFormView.h"
#include "AknExListSettingView.h"
#include "AknExListMarkView.h"
#include "AknExListFlagTestView.h"
#include "AknExListSetPageView.h"


// ================= MEMBER FUNCTIONS =========================================
//
// ----------------------------------------------------------------------------
// CAknExListAppUi::CAknExListAppUi()
// Default constructor.
// ----------------------------------------------------------------------------
//
CAknExListAppUi::CAknExListAppUi()
:   iCurrentOutline( EAknExListCmdEmptyOutline )
    {
    }

// ----------------------------------------------------------------------------
// void CAknExListAppUi::ConstructL()
// EPOC constructor.
// Creates view class object.
// ----------------------------------------------------------------------------
void CAknExListAppUi::ConstructL()
    {
    BaseConstructL();

    // Creates CAknExListColumnView class objects.
    CAknExListColumnView* columnView = new( ELeave ) CAknExListColumnView;
    CleanupStack::PushL( columnView );
    columnView->ConstructL();
    AddViewL( columnView ); // transfer ownership to CAknViewAppUi
    CleanupStack::Pop(); // columnView

    // Creates CAknExListFormView class objects.
    CAknExListFormView* formView = new( ELeave ) CAknExListFormView;
    CleanupStack::PushL( formView );
    formView->ConstructL();
    AddViewL( formView ); // transfer ownership to CAknViewAppUi
    CleanupStack::Pop(); // formView

    // Creates CAknExListSettingView class objects.
    CAknExListSettingView* settingView = new( ELeave ) CAknExListSettingView;
    CleanupStack::PushL( settingView );
    settingView->ConstructL();
    AddViewL( settingView ); // transfer ownership to CAknViewAppUi
    CleanupStack::Pop(); // settingView

    // Creates CAknExListMarkView class objects.
    CAknExListMarkView* markView = new( ELeave ) CAknExListMarkView;
    CleanupStack::PushL( markView );
    markView->ConstructL();
    AddViewL( markView ); // transfer ownership to CAknViewAppUi
    CleanupStack::Pop(); // markView

    // Creates CAknExListFlagTestView class objects.
    CAknExListFlagTestView* flagTestView =
        new( ELeave ) CAknExListFlagTestView;
    CleanupStack::PushL( flagTestView );
    flagTestView->ConstructL();
    AddViewL( flagTestView ); // transfer ownership to CAknViewAppUi
    CleanupStack::Pop(); // flagTestView

    CAknExListSetPageView* setPageView = CAknExListSetPageView::NewLC();
    AddViewL(setPageView); // transfer ownership to CAknViewAppUi
    CleanupStack::Pop(); // setPageView

    ActivateLocalViewL( columnView->Id() ); // Activates column view.
    }

// ----------------------------------------------------------------------------
// CAknExListAppUi::~CAknExListAppUi()
// Destructor
// Frees reserved resources.
// ----------------------------------------------------------------------------
CAknExListAppUi::~CAknExListAppUi()
    {
    }

// ----------------------------------------------------------------------------
// void CAknExListAppUi::SetOutlineId( const TInt )
// Sets current outline ID.
// ----------------------------------------------------------------------------
//
void CAknExListAppUi::SetOutlineId( const TInt aOutlineId )
    {
    iCurrentOutline = aOutlineId;
    }

// ----------------------------------------------------------------------------
// TInt CAknExListAppUi:OutlineId() const
// Returns current outline ID.
// ----------------------------------------------------------------------------
//
TInt CAknExListAppUi::OutlineId() const
    {
    return iCurrentOutline;
    }

// ----------------------------------------------------------------------------
// void CAknExListAppUi::HandleCommandL( TInt )
// Handles the commands.
// ----------------------------------------------------------------------------
void CAknExListAppUi::HandleCommandL( TInt aCommand )
    {
    switch ( aCommand ) // Command is...
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
