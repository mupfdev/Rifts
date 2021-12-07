/*
* ============================================================================
*  Name     : CAknExScrollerCbaHandler from MEikCommandObserver
*  Part of  : AknExScroller
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include <eikenv.h>

#include <aknexScroller.rsg>
#include "AknExScroller.hrh"
#include "AknExScrollerCbaHandler.h"
#include "AknExScrollerContainer2.h"


// ================= MEMBER FUNCTIONS =========================================
// ----------------------------------------------------------------------------
// CAknExScrollerCbaHandler::CAknExScrollerCbaHandler()
// C++ default constructor.
// ----------------------------------------------------------------------------
//
CAknExScrollerCbaHandler::CAknExScrollerCbaHandler()
    {
    }


// ----------------------------------------------------------------------------
// CAknExScrollerCbaHandler::CAknExScrollerCbaHandler( CAknExScrollerHandler* )
// Overload constructor.
// ----------------------------------------------------------------------------
//
CAknExScrollerCbaHandler::CAknExScrollerCbaHandler(
                          CAknExScrollerContainer2* aContainer )
                        :iContainer( aContainer )
    {
    }

// ----------------------------------------------------------------------------
// CAknExScrollerCbaHandler::ProcessCommandL( TInt )
// Handles the commands.
// ----------------------------------------------------------------------------
void CAknExScrollerCbaHandler::ProcessCommandL( TInt aCommand )
    {
    switch ( aCommand )
        {
        case EAknExScrollerCBACommnadAdd: // In case "Add"
            iContainer->AddItemToListBoxL();
            break;
        case EAknExScrollerCBACommnadDel: // In case "Del".
            iContainer->RemoveItemFromListBox();
            break;
        default:
            break;
        }
    }


// End of File

