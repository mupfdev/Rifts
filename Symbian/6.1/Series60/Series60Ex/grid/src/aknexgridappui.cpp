/*
* ============================================================================
*  Name     : CAknExGridAppUi from CAknViewAppUi
*  Part of  : AknExGrid
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/


#include <avkon.hrh>
#include <barsread.h>
#include <akntitle.h>
#include <aknnavi.h>
#include <akncontext.h>

#include <AknExGrid.rsg>
#include "aknexgrid.hrh"
#include "AknExGridAppUi.h"
#include "AknExGridView.h"
#include "AknExGridViewAsSelection.h"
#include "AknExGridViewAsMenu.h"
#include "AknExGridViewAsMarkableSelection.h"
#include "AknExGridContainer.h" 
#include "AknExGridViewAsGMS.h"

const TInt KLengthOfTitleTempString = 80;


// ================= MEMBER FUNCTIONS =======================

// C++ default constructor can NOT contain any code, that
// might leave.
//
void CAknExGridAppUi::ConstructL()
    {
    BaseConstructL();

    // create a main view
    CAknExGridView* viewMain = new( ELeave ) CAknExGridView;

    CleanupStack::PushL( viewMain );
    viewMain->ConstructL();
    CleanupStack::Pop(); 
    AddViewL( viewMain );        // transfer ownership to CAknViewAppUi

    // create a view for selection grid
    CAknExGridViewAsSelection* viewSel = new( ELeave ) CAknExGridViewAsSelection;

    CleanupStack::PushL( viewSel );
    viewSel->ConstructL();
    CleanupStack::Pop(); 
    AddViewL( viewSel );        // transfer ownership to CAknViewAppUi

    // create a view for menu grid
    CAknExGridViewAsMenu* viewMenu = new( ELeave ) CAknExGridViewAsMenu;

    CleanupStack::PushL( viewMenu );
    viewMenu->ConstructL();
    CleanupStack::Pop();
    AddViewL( viewMenu );        // transfer ownership to CAknViewAppUi

    // create a view for markable selection grid
    CAknExGridViewAsMarkableSelection* viewMarkableSel = new( ELeave ) CAknExGridViewAsMarkableSelection;

    CleanupStack::PushL( viewMarkableSel );
    viewMarkableSel->ConstructL();
    CleanupStack::Pop(); 
    AddViewL( viewMarkableSel );        // transfer ownership to CAknViewAppUi

    // create a view for GMS grid
    CAknExGridViewAsGMS* viewGMS = new( ELeave ) CAknExGridViewAsGMS;

    CleanupStack::PushL( viewGMS );
    viewGMS->ConstructL();
    CleanupStack::Pop();
    AddViewL( viewGMS );        // transfer ownership to CAknViewAppUi

    // Show tabs for main views from resources
    CEikStatusPane *sp = StatusPane();

    // Fetch pointer to the default navi pane control
    iNaviPane = (CAknNavigationControlContainer*)sp->ControlL( 
        TUid::Uid( EEikStatusPaneUidNavi ) );

    // Activate tab. It can be done also in tabgroup resource.
    // iTabGroup->SetActiveTabById( EStatusTitleViewId ); 

    // Tabgroup has been read from resource and it were pushed to the navi pane. 
    // Get pointer to the navigation decorator with the ResourceDecorator() function. 
    // Application owns the decorator and it has responsibility to delete the object.
    iDecoratedTabGroup = iNaviPane->ResourceDecorator();
    if ( iDecoratedTabGroup )
        {
        iTabGroup = ( CAknTabGroup* ) iDecoratedTabGroup->DecoratedControl();
        }

    // set a view
    if ( iTabGroup )
        {
        ActivateLocalViewL( TUid::Uid( iTabGroup->ActiveTabId() ) );
        }
    else  // just in case
        {
        ActivateLocalViewL( viewMain->Id() );
        }

    }

// Destructor
CAknExGridAppUi::~CAknExGridAppUi()
    {
    delete iDecoratedTabGroup;
    delete iAppContainer;
   }

// ----------------------------------------------------
// CAknExGridAppUi::ChangeActiveViewAndTabL
//      ( TUid aViewUid, TInt aTabId )
// Change active views and tabs.
// ----------------------------------------------------
void CAknExGridAppUi::ChangeActiveViewAndTabL( TUid aViewUid, TInt aTabId )
    {
    if ( iTabGroup )
        {
        iTabGroup->SetActiveTabById( aTabId );
        }

    ActivateLocalViewL( aViewUid );
    }

// ----------------------------------------------------
// CAknExGridAppUi::SetShortcutFlag
//      ( EBool aFlag)
// Set iShortcutFlag.
// ----------------------------------------------------
void CAknExGridAppUi::SetShortcutFlag( TBool aFlag )
    {
    iShortcutFlag = aFlag;
    }

// ----------------------------------------------------
// CAknExGridAppUi::GetShortcutFlag
//      ( )
// Get iShortcutFlag.
// ----------------------------------------------------
TBool CAknExGridAppUi::GetShortcutFlag( )
    {
    return iShortcutFlag;
    }

// ------------------------------------------------------------------------------
// CAknExGridAppUi::::DynInitMenuPaneL( TInt aResourceId,CEikMenuPane* aMenuPane )
//  This function is called by the EIKON framework just before it displays
//  a menu pane. Its default implementation is empty, and by overriding it,
//  the application can set the state of menu items dynamically according
//  to the state of application data.
//
// ------------------------------------------------------------------------------
void CAknExGridAppUi::DynInitMenuPaneL(
    TInt /*aResourceId*/, CEikMenuPane* /*aMenuPane*/ )
    {
    }

// ----------------------------------------------------
// CAknExGridAppUi::HandleKeyEventL(
//     const TKeyEvent& aKeyEvent,TEventCode /*aType*/)
//  
// ----------------------------------------------------
TKeyResponse CAknExGridAppUi::HandleKeyEventL(
    const TKeyEvent& /*aKeyEvent*/, TEventCode /*aType*/ )
    {
    return EKeyWasNotConsumed;
    }

// ----------------------------------------------------
// CAknExGridAppUi::HandleCommandL( TInt aCommand )
// Handles the commands.
// ----------------------------------------------------
void CAknExGridAppUi::HandleCommandL( TInt aCommand )
    {
    switch ( aCommand )
        {
        case EEikCmdExit:
        case EAknCmdExit:
            {
            Exit();
            break;
            }

        default:
            break;      
        }
    }

// End of File  
