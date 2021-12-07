/*
* =============================================================================
*  Name     : CAknExQueryTextAndDurationListEventHandler
*  Part of  : AknExQuery
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

// INCLUDE FILES
#include "AknExQuery.hrh"
#include "AknExQueryContainer.h"
#include "AknExQueryTextAndDurationListEventHandler.h"
#include <aknexquery.rsg>
// MACROS

// CONSTANTS

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExQueryTextAndDurationListEventHandler::
//     CAknExQueryTextAndDurationListEventHandler()
// Default constructor.
// ----------------------------------------------------------------------------
//
CAknExQueryTextAndDurationListEventHandler::
    CAknExQueryTextAndDurationListEventHandler(
        CAknExQueryContainer* aContainer )
:   CAknExQueryBaseListEventHandler( aContainer )
    {
    }

// ----------------------------------------------------------------------------
// CAknExQueryTextAndDurationListEventHandler::
//     ~CAknExQueryTextAndDurationListEventHandler()
// Destructor.
// ----------------------------------------------------------------------------
//
CAknExQueryTextAndDurationListEventHandler::
    ~CAknExQueryTextAndDurationListEventHandler()
    {
    }

// ----------------------------------------------------------------------------
// CAknExQueryTextAndDurationListEventHandler::HandleSelectedListItemL(
//     TInt aCommand )
// ----------------------------------------------------------------------------
//
void CAknExQueryTextAndDurationListEventHandler::HandleSelectedListItemL(
    TInt aCommand )
    {
    switch ( aCommand )
        {
        case EAknExQueryListBoxCmdData1:
            iContainer->ShowMultiLineTextAndLDurationLayoutL(
                R_AKNEXQUERY_MULTI_LINE_DATA_AND_DURATION_LAYOUT);
            break;
        case EAknExQueryListBoxCmdData2:
            iContainer->ShowMultiLineTextAndLDurationLayoutL(
                R_AKNEXQUERY_MULTI_LINE_CODE_AND_DURATION_LAYOUT);
            break;
        default:
            break;
        }
    }

// End of File
