/*
* ============================================================================
*  Name     : CAknExGridViewAsGMS from CAknView
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
#include "AknExGridViewAsGMS.h"
#include "AknExGridContainerAsGMS.h" 
#include "AknExGrid.hrh"

const TInt KLengthOfTempString = 100;

// ================= MEMBER FUNCTIONS =======================

// EPOC default constructor can leave.
void CAknExGridViewAsGMS::ConstructL()
    {
    BaseConstructL( R_AKNEXGRID_VIEW_GMS );
    }

// destructor
CAknExGridViewAsGMS::~CAknExGridViewAsGMS()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }

    delete iContainer;
    }

// ---------------------------------------------------------
// TUid CAknExGridViewAsGMS::Id()
// return view ID
// ---------------------------------------------------------
TUid CAknExGridViewAsGMS::Id() const
    {
    return KViewGMSId;
    }

// ---------------------------------------------------------
// CAknExGridViewAsGMS::HandleCommandL(TInt aCommand)
// handles command and calls appropriate functions
// ---------------------------------------------------------
void CAknExGridViewAsGMS::HandleCommandL( TInt aCommand )
    {   
    switch ( aCommand )
        {
        case EAknSoftkeyBack:
        case EAknExGridCmdClose:
            {
            CEikStatusPane *sp = ((CAknAppUi*)iEikonEnv->EikAppUi())->StatusPane();
            CAknTitlePane* titlePane = (CAknTitlePane *)sp->ControlL(TUid::Uid(EEikStatusPaneUidTitle));
            titlePane->SetTextToDefaultL();
            STATIC_CAST( CAknExGridAppUi*, AppUi() )
                ->ChangeActiveViewAndTabL( KViewId, EAknExGridViewTab );
            break;
            }

        case EAknExGridCmdShowPopupGMS:
            iContainer->ShowPopupGMSGridL();
            break;

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
            AppUi()->HandleCommandL( aCommand );
            break;
        }
    }

// ---------------------------------------------------------
// CAknExGridViewAsGMS::HandleClientRectChange()
// 
// ---------------------------------------------------------
void CAknExGridViewAsGMS::HandleClientRectChange()
    {
    if ( iContainer )
        {
        iContainer->SetRect( ClientRect() );
        }
    }

// ---------------------------------------------------------
// CAknExGridViewAsGMS::DoActivateL(...)
// create a container object.
// ---------------------------------------------------------
void CAknExGridViewAsGMS::DoActivateL(
    const TVwsViewId& /*aPrevViewId*/, TUid /*aCustomMessageId*/,
    const TDesC8& /*aCustomMessage*/ )
    {
    iContainer = new( ELeave ) CAknExGridContainerAsGMS;
    iContainer->ConstructL( ClientRect() );
    AppUi()->AddToStackL( *this, iContainer );
   }

// ---------------------------------------------------------
// CAknExGridViewAsGMS::HandleCommandL( TInt aCommand )
// destroy the container object.
// ---------------------------------------------------------
void CAknExGridViewAsGMS::DoDeactivate()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    
    delete iContainer;
    iContainer = NULL;
    }

// End of File

