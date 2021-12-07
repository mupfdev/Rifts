/*
* ============================================================================
*  Name     : CAknExScrollerView4 from CAknView
*  Part of  : AknExScroller
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include  <aknviewappui.h>
#include  <avkon.hrh>
#include  <AknExScroller.rsg>
#include  "AknExScrollerView4.h"
#include  "AknExScrollerContainer4.h" 

#include "AknExScroller.hrh"

// ================= MEMBER FUNCTIONS =======================
// C++ default constructor can NOT contain any code, that
// might leave.
//
CAknExScrollerView4::CAknExScrollerView4()
    {
    }


// ---------------------------------------------------------
// CAknExScrollerView4::ConstructL()
// EPOC two-phased constructor
// ---------------------------------------------------------
//
void CAknExScrollerView4::ConstructL()
    {
    BaseConstructL( R_AKNEXSCROLLER_VIEW4 );
    }


// Destructor
CAknExScrollerView4::~CAknExScrollerView4()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }

    delete iContainer;
    iContainer = NULL;
    }

// ---------------------------------------------------------
// TUid CAknExScrollerView4::Id()
// returns View id
// ---------------------------------------------------------
//
TUid CAknExScrollerView4::Id() const
    {
    return KViewId4;
    }

// ---------------------------------------------------------
// CAknExScrollerView4::HandleCommandL( TInt aCommand )
// handles the commands
// ---------------------------------------------------------
//
void CAknExScrollerView4::HandleCommandL( TInt aCommand )
    {   
    switch ( aCommand )
        {
        case EAknSoftkeyBack:
            AppUi()->HandleCommandL( EAknCmdExit );
            break;
        case EAknExScrollerCBACommnadNext:
                    AppUi()->HandleCommandL( EAknExScrollerView1 );
            break;
        default:
            AppUi()->HandleCommandL( aCommand );
            break;
        }
    }


// ---------------------------------------------------------
// CAknExScrollerView4::DoActivateL(...)
// Creates the Container class object.
// ---------------------------------------------------------
//
void CAknExScrollerView4::DoActivateL(
                         const TVwsViewId& /*aPrevViewId*/,
                         TUid /*aCustomMessageId*/,
                         const TDesC8& /*aCustomMessage*/ )
    {
    iContainer = new ( ELeave ) CAknExScrollerContainer4();
    iContainer->SetMopParent(this);
    iContainer->ConstructL( ClientRect() );
    AppUi()->AddToStackL( *this, iContainer );
    }

// ---------------------------------------------------------
// CAknExScrollerView4::DoDeactivate()
// Deletes the Container class object
// ---------------------------------------------------------
//
void CAknExScrollerView4::DoDeactivate()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    
    delete iContainer;
    iContainer = NULL;
    }

// End of File
