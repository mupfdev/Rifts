/*
* =============================================================================
*  Name     : CAknExQueryTimeAndDurationListEventHandler
*  Part of  : AknExQuery
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

// INCLUDE FILES
#include "AknExQuery.hrh"
#include "AknExQueryContainer.h"
#include "AknExQueryTimeAndDurationListEventHandler.h"
#include <AknExQuery.rsg>
// MACROS

// CONSTANTS

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExQueryTimeAndDurationListEventHandler::
//     CAknExQueryTimeAndDurationListEventHandler()
// Default constructor.
// ----------------------------------------------------------------------------
//
CAknExQueryTimeAndDurationListEventHandler::
    CAknExQueryTimeAndDurationListEventHandler(
        CAknExQueryContainer* aContainer )
:   CAknExQueryBaseListEventHandler( aContainer )
    {
    }

// ----------------------------------------------------------------------------
// CAknExQueryTimeAndDurationListEventHandler::
//     ~CAknExQueryTimeAndDurationListEventHandler()
// Destructor.
// ----------------------------------------------------------------------------
//
CAknExQueryTimeAndDurationListEventHandler::
    ~CAknExQueryTimeAndDurationListEventHandler()
    {
    }

// ----------------------------------------------------------------------------
// CAknExQueryTimeAndDurationListEventHandler::HandleSelectedListItemL(
//     TInt aCommand )
// ----------------------------------------------------------------------------
//
void CAknExQueryTimeAndDurationListEventHandler::HandleSelectedListItemL(
    TInt aCommand )
    {
    switch ( aCommand )
        {
        case EAknExQueryListBoxCmdData1:
           iContainer->ShowMultiLineTimeAndDurationLayoutL(
                R_AKNEXQUERY_MULTI_LINE_DATE_AND_DURATION_LAYOUT,
                R_AKNEXQUERY_DATE_INITIAL_VALUE);
            break;
        case EAknExQueryListBoxCmdData2:
            iContainer->ShowMultiLineTimeAndDurationLayoutL(
                R_AKNEXQUERY_MULTI_LINE_TIME_AND_DURATION_LAYOUT,
                R_AKNEXQUERY_TIME_INITIAL_VALUE );
            break;
        default:
            break;
        }
    }

// End of File
