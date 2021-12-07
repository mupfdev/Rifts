/*
* ============================================================================
*  Name     : CAknExGridView from CAknView
*  Part of  : AknExGrid
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include <aknviewappui.h>
#include <avkon.hrh>

#include <AknExGrid.rsg>
#include "AknExGridAppUi.h"
#include "AknExGridView.h"
#include "AknExGridViewAsSelection.h"
#include "AknExGridViewAsMenu.h"
#include "AknExGridViewAsMarkableSelection.h"
#include "AknExGridContainer.h" 
#include "AknExGrid.hrh"
#include "AknExGridViewAsGMS.h"

#include <akntitle.h>

const TInt KLengthOfTitleTempString = 80;

// ================= MEMBER FUNCTIONS =======================

// EPOC default constructor can leave.
void CAknExGridView::ConstructL()
    {
    iTestNumber=1;
    BaseConstructL( R_AKNEXGRID_VIEW_MAIN );
    }

// Destructor
CAknExGridView::~CAknExGridView()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }

    delete iContainer;
    }

// ---------------------------------------------------------
// TUid CAknExGridView::Id()
// Returns View Id.
// ---------------------------------------------------------
//
TUid CAknExGridView::Id() const
    {
    return KViewId;
    }

// ---------------------------------------------------------
// CAknExGridView::HandleCommandL( TInt aCommand )
// Handle the commands.
// ---------------------------------------------------------
//
void CAknExGridView::HandleCommandL( TInt aCommand )
    {   
    CEikStatusPane *sp = StatusPane();
    CAknTitlePane* titlePane = (CAknTitlePane *)sp->ControlL(TUid::Uid(EEikStatusPaneUidTitle));

    switch ( aCommand )
        {
        // handle softkeys
        case EAknSoftkeyBack:
            ( ( MEikCommandObserver* )AppUi() )->ProcessCommandL( EEikCmdExit );
            break;

        // switch the grid view
        case EAknExGridCmdSelection:
            titlePane->SetTextToDefaultL();
            STATIC_CAST( CAknExGridAppUi*, AppUi() )->SetShortcutFlag( EFalse );
            STATIC_CAST( CAknExGridAppUi*, AppUi() )
                ->ChangeActiveViewAndTabL( KViewSelectionId, EAknExGridViewSelectionTab );
            break;

        case EAknExGridCmdMenu:
            titlePane->SetTextToDefaultL();
            STATIC_CAST( CAknExGridAppUi*, AppUi() )
                ->ChangeActiveViewAndTabL( KViewMenuId, EAknExGridViewMenuTab );
            break;

        case EAknExGridCmdMarkableSelection:
            titlePane->SetTextToDefaultL();
            STATIC_CAST( CAknExGridAppUi*, AppUi() )->SetShortcutFlag( EFalse );
            STATIC_CAST( CAknExGridAppUi*, AppUi() )
                ->ChangeActiveViewAndTabL( KViewMarkableSelectionId, EAknExGridViewMarkableSelectionTab );
            break;

        case EAknExGridCmdGMSGrid:
            titlePane->SetTextToDefaultL();
            STATIC_CAST( CAknExGridAppUi*, AppUi() )
                ->ChangeActiveViewAndTabL( KViewGMSId, EAknExGridViewGMSTab );
            break;

        case ESGridSoftKeyNext:
            AutoTestL();
            break;

        default:
            AppUi()->HandleCommandL( aCommand );
            break;
        }
    }

// ---------------------------------------------------------
// CAknExGridView::HandleClientRectChange()
// Handle the clientrect.
// ---------------------------------------------------------
//
void CAknExGridView::HandleClientRectChange()
    {
    if ( iContainer )
        {
        iContainer->SetRect( ClientRect() );
        }
    }

// ---------------------------------------------------------
// CAknExGridView::DoActivateL(...)
// Creates the Container class object.
// ---------------------------------------------------------
//
void CAknExGridView::DoActivateL(
    const TVwsViewId& /*aPrevViewId*/, TUid /*aCustomMessageId*/,
    const TDesC8& /*aCustomMessage*/ )
    {
    iContainer = new( ELeave ) CAknExGridContainer;
    iContainer->SetMopParent(this);
    iContainer->ConstructL( ClientRect() );
    AppUi()->AddToStackL( *this, iContainer );
    }

// ---------------------------------------------------------
// CAknExGridView::HandleCommandL( TInt aCommand )
// Deleats the Container class object.
// ---------------------------------------------------------
//
void CAknExGridView::DoDeactivate()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    
    delete iContainer;
    iContainer = NULL;
    }

void CAknExGridView::AutoTestL()
    {
    iTestNumber++;
    switch(iTestNumber)
        {
        case EAknExGridViewSelectionTab:
            STATIC_CAST( CAknExGridAppUi*, AppUi() )->SetShortcutFlag( EFalse );
            STATIC_CAST( CAknExGridAppUi*, AppUi() )
                ->ChangeActiveViewAndTabL( KViewSelectionId, EAknExGridViewSelectionTab );
            break;
        case EAknExGridViewMenuTab:
            STATIC_CAST( CAknExGridAppUi*, AppUi() )
                ->ChangeActiveViewAndTabL( KViewMenuId, EAknExGridViewMenuTab );
            break;
        case EAknExGridViewMarkableSelectionTab:
            STATIC_CAST( CAknExGridAppUi*, AppUi() )->SetShortcutFlag( EFalse );
            STATIC_CAST( CAknExGridAppUi*, AppUi() )
                ->ChangeActiveViewAndTabL( KViewMarkableSelectionId, EAknExGridViewMarkableSelectionTab );
            break;
        default:
        case EAknExGridViewGMSTab:
            STATIC_CAST( CAknExGridAppUi*, AppUi() )
                ->ChangeActiveViewAndTabL( KViewGMSId, EAknExGridViewGMSTab );
            iTestNumber=1;
            break;
        }
    }

// End of File

