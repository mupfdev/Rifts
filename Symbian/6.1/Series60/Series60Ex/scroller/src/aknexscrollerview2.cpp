/*
* ============================================================================
*  Name     : CAknExScrollerView2 from CAknView
*  Part of  : AknExScroller
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/


// INCLUDE FILES
#include  <aknviewappui.h>
#include  <avkon.hrh>
#include  <AknExScroller.rsg>
#include  "AknExScrollerView2.h"
#include  "AknExScrollerContainer2.h" 

#include "AknExScroller.hrh"

// ================= MEMBER FUNCTIONS =======================
// C++ default constructor can NOT contain any code, that
// might leave.
//
CAknExScrollerView2::CAknExScrollerView2()
    {
    }


// ---------------------------------------------------------
// CAknExScrollerView2::ConstructL()
// EPOC two-phased constructor
// ---------------------------------------------------------
//
void CAknExScrollerView2::ConstructL()
    {
    BaseConstructL( R_AKNEXSCROLLER_VIEW2 );
    }


// Destructor
CAknExScrollerView2::~CAknExScrollerView2()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }

    delete iContainer;
    iContainer = NULL;
    }


// ---------------------------------------------------------
// TUid CAknExScrollerView2::Id()
// returns View id
// ---------------------------------------------------------
//
TUid CAknExScrollerView2::Id() const
    {
    return KView2Id;
    }


// ---------------------------------------------------------
// CAknExScrollerView2::HandleCommandL( TInt aCommand )
// handles the commands
// ---------------------------------------------------------
//
void CAknExScrollerView2::HandleCommandL( TInt aCommand )
    {   
    switch ( aCommand )
        {
        case EAknSoftkeyBack:
            AppUi()->HandleCommandL( EAknCmdExit );
            break;
        case EAknExScrollerCBACommnadNext:
            AppUi()->HandleCommandL( EAknExScrollerView3 );
            break;
        case EAknExScrollerCBACommnadAdd:
            iContainer->AddItemToListBoxL();
            break;
        case EAknExScrollerCBACommnadDel:
            iContainer->RemoveItemFromListBox();
            break;
        default:
            AppUi()->HandleCommandL( aCommand );
            break;
        }
    }


// ---------------------------------------------------------
// CAknExScrollerView2::DoActivateL(...)
// Creates the Container class object.
// ---------------------------------------------------------
//
void CAknExScrollerView2::DoActivateL(
                         const TVwsViewId& /*aPrevViewId*/,
                         TUid /*aCustomMessageId*/,
                         const TDesC8& /*aCustomMessage*/ )
    {
    iContainer = new ( ELeave ) CAknExScrollerContainer2();
    iContainer->SetMopParent(this);
    iContainer->ConstructL( ClientRect() );
    AppUi()->AddToStackL( *this, iContainer );
    }

// ---------------------------------------------------------
// CAknExScrollerView2::HandleCommandL(TInt aCommand)
// Deletes the Container class object
// ---------------------------------------------------------
//
void CAknExScrollerView2::DoDeactivate()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    
    delete iContainer;
    iContainer = NULL;
    }

// End of File

