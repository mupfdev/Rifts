/*
* ============================================================================
*  Name     : CAknExGridViewAsMarkableSelection from CAknView
*  Part of  : AknExGrid
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include <eikmenub.h>
#include <aknviewappui.h>
#include <avkon.hrh>
#include <AknGridView.h>
#include <akntitle.h>

#include <AknExGrid.rsg>
#include "AknExGridView.h"
#include "AknExGridAppUi.h"
#include "AknExGridViewAsMarkableSelection.h"
#include "AknExGridContainerAsSelection.h" 
#include "AknExGrid.hrh"

const TInt KLengthOfSelectionAboutString = 40;

// ================= MEMBER FUNCTIONS =======================

// EPOC default constructor can leave.
void CAknExGridViewAsMarkableSelection::ConstructL()
    {
    BaseConstructL( R_AKNEXGRID_VIEW_SELECTION );
    }

// destructor
CAknExGridViewAsMarkableSelection::~CAknExGridViewAsMarkableSelection()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }

    delete iContainer;
    }

// ---------------------------------------------------------
// TUid CAknExGridViewAsMarkableSelection::Id()
// return view ID
// ---------------------------------------------------------
TUid CAknExGridViewAsMarkableSelection::Id() const
    {
    return KViewMarkableSelectionId;
    }

// ---------------------------------------------------------
// CAknExGridViewAsMarkableSelection::HandleCommandL( TInt aCommand )
// handles command and calls appropriate functions
// ---------------------------------------------------------
void CAknExGridViewAsMarkableSelection::HandleCommandL( TInt aCommand )
    {   
    TBuf< KLengthOfAboutString > aboutString;
    switch ( aCommand )
        {
        case EAknSoftkeyBack: // return to main view
        case ESGridSoftKeyNext:
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
                aboutString, R_AKNEXGRID_TEXT_ABOUT_MARKABLE );
            iEikonEnv->AlertWin( aboutString );
            break;

        case EAknExGridCmdClose: // return to main view
            STATIC_CAST( CAknExGridAppUi*, AppUi() )
                ->ChangeActiveViewAndTabL( KViewId, EAknExGridViewTab );
            break;


        case EAknExGridCmdSelectAll:
        case EAknExGridCmdDeselectAll:
        case EAknExGridCmdToggle:
            iContainer->MarkAllItemsL( aCommand );
            break;

        default:
            {
            AppUi()->HandleCommandL( aCommand );
            break;
            }
        }
    }


// ----------------------------------------------------------------------------
// CAknExGridViewAsMarkableSelection::DynInitMenuPaneL(
//                              TInt aResourceId,CEikMenuPane* aMenuPane)
//  This function is called by the EIKON framework just before it displays
//  a menu pane. Its default implementation is empty, and by overriding it,
//  the application can set the state of menu items dynamically according
//  to the state of application data.
// ----------------------------------------------------------------------------
//
void CAknExGridViewAsMarkableSelection::DynInitMenuPaneL(
                        TInt aResourceId, CEikMenuPane* aMenuPane)
    {
    if ( aResourceId == R_AKNEXGRID_MENUPANE_SELECTION )
        {
        aMenuPane->SetItemDimmed(EAknExGridCmdSelectAll, EFalse);
        aMenuPane->SetItemDimmed(EAknExGridCmdDeselectAll, EFalse);
        aMenuPane->SetItemDimmed(EAknExGridCmdToggle, EFalse);
        }
    }


// ---------------------------------------------------------
// CAknExGridViewAsMarkableSelection::HandleClientRectChange()
// 
// ---------------------------------------------------------
void CAknExGridViewAsMarkableSelection::HandleClientRectChange()
    {
    if ( iContainer )
        {
        iContainer->SetRect( ClientRect() );
        }
    }

// ---------------------------------------------------------
// CAknExGridViewAsMarkableSelection::DoActivateL(...)
// create a container object.
// ---------------------------------------------------------
void CAknExGridViewAsMarkableSelection::DoActivateL(
    const TVwsViewId& /*aPrevViewId*/, TUid /*aCustomMessageId*/,
    const TDesC8& /*aCustomMessage*/ )
    {
    iContainer = new( ELeave ) CAknExGridContainerAsSelection;
    iContainer->SetMopParent(this);
    iContainer->ConstructL( ClientRect(), EAknExGridMarkableGrid);

    AppUi()->AddToStackL( *this, iContainer );
   }

// ---------------------------------------------------------
// CAknExGridViewAsMarkableSelection::DoDeactivate()
// destroy the container object.
// ---------------------------------------------------------
void CAknExGridViewAsMarkableSelection::DoDeactivate()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    
    delete iContainer;
    iContainer = NULL;
    }

// End of File

