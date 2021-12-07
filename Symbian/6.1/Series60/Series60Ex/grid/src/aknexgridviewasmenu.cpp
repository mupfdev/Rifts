/*
* ============================================================================
*  Name     : CAknExGridViewAsMenu from CAknView
*  Part of  : AknExGrid
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include <aknviewappui.h>
#include <avkon.hrh>
#include <AknGridView.h>
#include <akntitle.h>

#include <AknExGrid.rsg>
#include "AknExGridAppUi.h"
#include "AknExGridView.h"
#include "AknExGridViewAsMenu.h"
#include "AknExGridContainerAsMenu.h" 
#include "AknExGrid.hrh"

// ================= MEMBER FUNCTIONS =======================

// EPOC default constructor can leave.
void CAknExGridViewAsMenu::ConstructL()
    {
    BaseConstructL( R_AKNEXGRID_VIEW_MENU );
    }

// destructor
CAknExGridViewAsMenu::~CAknExGridViewAsMenu()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }

    delete iContainer;
    }

// ---------------------------------------------------------
// TUid CAknExGridViewAsMenu::Id()
// return view ID
// ---------------------------------------------------------
TUid CAknExGridViewAsMenu::Id() const
    {
    return KViewMenuId;
    }

// ---------------------------------------------------------
// CAknExGridViewAsMenu::HandleCommandL(TInt aCommand)
// handles command and calls appropriate functions
// ---------------------------------------------------------
void CAknExGridViewAsMenu::HandleCommandL( TInt aCommand )
    {   
    TBuf< KLengthOfMenuAboutString > aboutString;

    switch ( aCommand )
        {
        case EAknSoftkeyBack:
            {
            CEikStatusPane *sp = ((CAknAppUi*)iEikonEnv->EikAppUi())->StatusPane();
            CAknTitlePane* titlePane = (CAknTitlePane *)sp->ControlL(TUid::Uid(EEikStatusPaneUidTitle));
            titlePane->SetTextToDefaultL();
            STATIC_CAST( CAknExGridAppUi*, AppUi() )
                ->ChangeActiveViewAndTabL( KViewId, EAknExGridViewTab );
            break;
            }

        case EAknExGridCmdShowMenu:
            iContainer->ShowGridInMenuL();
            break;

        case EAknExGridCmdNumOfItems:
            iContainer->EnterNumberOfItemsL();
            break;

        case EAknExGridCmdChangeSize:
            iContainer->DetermineChangeSizeL();
            break;

        case EAknExGridCmdFillingOrder:
            iContainer->DetermineFillingOrderL();
            break;

        case EAknExGridCmdLoopingVertFollowLoop:
            iContainer->SetVerticalScrollingTypeL( 
                CAknGridView::EScrollIncrementLineAndLoops );
            break;

        case EAknExGridCmdLoopingVertFollowStop:
            iContainer->SetVerticalScrollingTypeL( 
                CAknGridView::EScrollIncrementLineAndStops );
            break;

        case EAknExGridCmdLoopingVertFollowGrid:
            iContainer->SetVerticalScrollingTypeL( 
                CAknGridView::EScrollFollowsGrid );
            break;

        case EAknExGridCmdLoopingVertStopEnd:
            iContainer->SetVerticalScrollingTypeL( 
                CAknGridView::EScrollStops );
            break;

        case EAknExGridCmdLoopingHorizFollowLoop:
            iContainer->SetHorizontalScrollingTypeL( 
                CAknGridView::EScrollIncrementLineAndLoops );
            break;

        case EAknExGridCmdLoopingHorizFollowStop:
            iContainer->SetHorizontalScrollingTypeL( 
                CAknGridView::EScrollIncrementLineAndStops );
            break;

        case EAknExGridCmdLoopingHorizFollowGrid:
            iContainer->SetHorizontalScrollingTypeL( 
                CAknGridView::EScrollFollowsGrid );
            break;

        case EAknExGridCmdLoopingHorizStopEnd:
            iContainer->SetHorizontalScrollingTypeL( 
                CAknGridView::EScrollStops );
            break;

        case EAknExGridCmdAbout:
            iCoeEnv->ReadResource( 
                aboutString, R_AKNEXGRID_TEXT_ABOUT_MENU );
            iEikonEnv->AlertWin( aboutString );
            break;

        case EAknExGridCmdClose:
            {
            CEikStatusPane *sp = ((CAknAppUi*)iEikonEnv->EikAppUi())->StatusPane();
            CAknTitlePane* titlePane = (CAknTitlePane *)sp->ControlL(TUid::Uid(EEikStatusPaneUidTitle));
            titlePane->SetTextToDefaultL();
            STATIC_CAST( CAknExGridAppUi*, AppUi() )
                ->ChangeActiveViewAndTabL( KViewId, EAknExGridViewTab );
            break;
            }

        case ESGridSoftKeyNext:
            {
            if(iContainer->AutoTestL())
                {
                CEikStatusPane *sp = ((CAknAppUi*)iEikonEnv->EikAppUi())->StatusPane();
                CAknTitlePane* titlePane = (CAknTitlePane *)sp->ControlL(TUid::Uid(EEikStatusPaneUidTitle));
                titlePane->SetTextToDefaultL();
                STATIC_CAST( CAknExGridAppUi*, AppUi() )
                    ->ChangeActiveViewAndTabL( KViewId, EAknExGridViewTab );
                }
            break;
            }

        default:
            {
            AppUi()->HandleCommandL( aCommand );
            break;
            }
        }
    }

// ---------------------------------------------------------
// CAknExGridViewAsMenu::HandleClientRectChange()
// 
// ---------------------------------------------------------
void CAknExGridViewAsMenu::HandleClientRectChange()
    {
    if ( iContainer )
        {
        iContainer->SetRect( ClientRect() );
        }
    }

// ---------------------------------------------------------
// CAknExGridViewAsMenu::DoActivateL(...)
// create a container object.
// ---------------------------------------------------------
void CAknExGridViewAsMenu::DoActivateL(
    const TVwsViewId& /*aPrevViewId*/, TUid /*aCustomMessageId*/,
    const TDesC8& /*aCustomMessage*/ )
    {
    iContainer = new( ELeave ) CAknExGridContainerAsMenu;
    iContainer->SetMopParent(this);
    iContainer->ConstructL( ClientRect() );
    AppUi()->AddToStackL( *this, iContainer );
   }

// ---------------------------------------------------------
// CAknExGridViewAsMenu::HandleCommandL( TInt aCommand )
// destroy the container object.
// ---------------------------------------------------------
void CAknExGridViewAsMenu::DoDeactivate()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    
    delete iContainer;
    iContainer = NULL;
    }

// End of File

