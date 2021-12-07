/*
* ============================================================================
*  Name     : CAknExScrollerView from CAknView
*  Part of  : AknExScroller
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include  <aknviewappui.h>
#include  <avkon.hrh>
#include  <AknExScroller.rsg>
#include  "AknExScrollerView.h"
#include  "AknExScrollerContainer.h" 

#include "AknExScroller.hrh"


// ================= MEMBER FUNCTIONS =======================
// C++ default constructor can NOT contain any code, that
// might leave.
//
CAknExScrollerView::CAknExScrollerView()
    {
    }


// ---------------------------------------------------------
// CAknExScrollerView::ConstructL()
// EPOC two-phased constructor
// ---------------------------------------------------------
//
void CAknExScrollerView::ConstructL()
    {
    BaseConstructL( R_AKNEXSCROLLER_VIEW1 );
    }


// Destructor
CAknExScrollerView::~CAknExScrollerView()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }

    delete iContainer;
    iContainer = NULL;
    }

// ---------------------------------------------------------
// TUid CAknExScrollerView::Id()
// returns View id
// ---------------------------------------------------------
//
TUid CAknExScrollerView::Id() const
    {
    return KViewId;
    }

// ---------------------------------------------------------
// CAknExScrollerView::HandleCommandL( TInt aCommand )
// handles the commands
// ---------------------------------------------------------
//
void CAknExScrollerView::HandleCommandL( TInt aCommand )
    {   
    switch ( aCommand )
        {
        case EAknSoftkeyBack:
            AppUi()->HandleCommandL( EAknCmdExit );
            break;
        case EAknExScrollerCBACommnadNext:
            AppUi()->HandleCommandL( EAknExScrollerView2 );
            break;
        default:
            AppUi()->HandleCommandL( aCommand );
            break;
        }
    }


// ---------------------------------------------------------
// CAknExScrollerView::DoActivateL(...)
// Creates the Container class object.
// ---------------------------------------------------------
//
void CAknExScrollerView::DoActivateL(
                         const TVwsViewId& /*aPrevViewId*/,
                         TUid /*aCustomMessageId*/,
                         const TDesC8& /*aCustomMessage*/ )
    {
    iContainer = new ( ELeave ) CAknExScrollerContainer();
    iContainer->SetMopParent(this);
    iContainer->ConstructL( ClientRect() );
    AppUi()->AddToStackL( *this, iContainer );
    }

// ---------------------------------------------------------
// CAknExScrollerView::DoDeactivate()
// Deletes the Container class object
// ---------------------------------------------------------
//
void CAknExScrollerView::DoDeactivate()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    
    delete iContainer;
    iContainer = NULL;
    }

// End of File
