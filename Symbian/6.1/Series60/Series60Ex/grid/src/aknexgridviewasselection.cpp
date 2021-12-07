/*
* ============================================================================
*  Name     : CAknExGridViewAsSelection from CAknView
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
#include "AknExGridView.h"
#include "AknExGridAppUi.h"
#include "AknExGridViewAsSelection.h"
#include "AknExGridContainerAsSelection.h" 
#include "AknExGrid.hrh"

const TInt KLengthOfSelectionAboutString = 40;

// ================= MEMBER FUNCTIONS =======================

// EPOC default constructor can leave.
void CAknExGridViewAsSelection::ConstructL()
    {
    BaseConstructL( R_AKNEXGRID_VIEW_SELECTION );
    }

// destructor
CAknExGridViewAsSelection::~CAknExGridViewAsSelection()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }

    delete iContainer;
    }

// ---------------------------------------------------------
// TUid CAknExGridViewAsSelection::Id()
// return view ID
// ---------------------------------------------------------
TUid CAknExGridViewAsSelection::Id() const
    {
    return KViewSelectionId;
    }

// ---------------------------------------------------------
// CAknExGridViewAsSelection::HandleCommandL( TInt aCommand )
// handles command and calls appropriate functions
// ---------------------------------------------------------
void CAknExGridViewAsSelection::HandleCommandL( TInt aCommand )
    {   
    TBuf< KLengthOfAboutString > aboutString;
    switch ( aCommand )
        {
        case EAknSoftkeyBack: // return to main view
            {
            CEikStatusPane *sp = ((CAknAppUi*)iEikonEnv->EikAppUi())->StatusPane();
            CAknTitlePane* titlePane = (CAknTitlePane *)sp->ControlL(TUid::Uid(EEikStatusPaneUidTitle));
            titlePane->SetTextToDefaultL();
            STATIC_CAST( CAknExGridAppUi*, AppUi() )
                ->ChangeActiveViewAndTabL( KViewId, EAknExGridViewTab );
            break;
            }

        case EAknExGridCmdAddOneItemInsert:
            iContainer->InsertDataL( 1 );
            break;

        case EAknExGridCmdAddFiveItemsInsert:
            iContainer->InsertDataL( 5 );
            break;

        case EAknExGridCmdAddOneItemToTheLast:
             iContainer->AddDataL( 1 );
             break;

        case EAknExGridCmdAddFiveItemsToTheLast:
            iContainer->AddDataL( 5 );
             break;

        case EAknExGridCmdRemoveOneItemFromCurrent:
            iContainer->RemoveDataL( 1 , KRemoveFromCurrent);
            break;

        case EAknExGridCmdRemoveFiveItemsFromCurrent:
            iContainer->RemoveDataL( 5 , KRemoveFromCurrent );
            break;

        case EAknExGridCmdRemoveOneItemFromLast:
            iContainer->RemoveDataL( 1 , KRemoveFromLast );
            break;

        case EAknExGridCmdRemoveFiveItemsFromLast:
            iContainer->RemoveDataL( 5 , KRemoveFromLast );
            break;

        case EAknExGridCmdRemoveAllItems:
            iContainer->RemoveDataL( KRemoveAllItems , KRemoveFromLast);
            break;

        case EAknExGridCmdFillingOrder:
            iContainer->DetermineFillingOrderL();
            break;

        case EAknExGridCmdLoopingVertFollowLoop:
            iContainer->SetVerticalScrollingTypeL( 
//                CAknGridView::EScrollFollowsItemsAndLoops );
                CAknGridView::EScrollIncrementLineAndLoops );
            break;

        case EAknExGridCmdLoopingVertFollowStop:
            iContainer->SetVerticalScrollingTypeL( 
//                CAknGridView::EScrollFollowsItemsAndStops );
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
//                CAknGridView::EScrollFollowsItemsAndLoops );
                CAknGridView::EScrollIncrementLineAndLoops );
            break;

        case EAknExGridCmdLoopingHorizFollowStop:
            iContainer->SetHorizontalScrollingTypeL( 
//                CAknGridView::EScrollFollowsItemsAndStops );
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

        case EAknExGridCmdChangeSize:
            iContainer->DetermineChangeSizeL();
            break;

        case EAknExGridCmdContaionText:
            iContainer->SelectContents( EContainText );
            break;

        case EAknExGridCmdContainGraphic:
            iContainer->SelectContents( EContainGraphic );
            break;

        case EAknExGridCmdContainBoth:
            iContainer->SelectContents( EContainBoth );
            break;

        case EAknExGridCmdAbout:
            iCoeEnv->ReadResource( 
                    aboutString, R_AKNEXGRID_TEXT_ABOUT_SELECTION );
            iEikonEnv->AlertWin( aboutString );
            break;

        case EAknExGridCmdClose: // return to main view
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
// CAknExGridViewAsSelection::HandleClientRectChange()
// 
// ---------------------------------------------------------
void CAknExGridViewAsSelection::HandleClientRectChange()
    {
    if ( iContainer )
        {
        iContainer->SetRect( ClientRect() );
        }
    }

// ---------------------------------------------------------
// CAknExGridViewAsSelection::DoActivateL(...)
// create a container object.
// ---------------------------------------------------------
void CAknExGridViewAsSelection::DoActivateL(
    const TVwsViewId& /*aPrevViewId*/, TUid /*aCustomMessageId*/,
    const TDesC8& /*aCustomMessage*/ )
    {
    iContainer = new( ELeave ) CAknExGridContainerAsSelection;
    iContainer->SetMopParent(this);
    iContainer->ConstructL( ClientRect(), EAknExGridSelectionGrid );
    AppUi()->AddToStackL( *this, iContainer );
   }

// ---------------------------------------------------------
// CAknExGridViewAsSelection::DoDeactivate()
// destroy the container object.
// ---------------------------------------------------------
void CAknExGridViewAsSelection::DoDeactivate()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    
    delete iContainer;
    iContainer = NULL;
    }

// End of File

