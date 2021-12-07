/*
* =============================================================================
*  Name     : CAknExQueryTextAndTimeListEventHandler
*  Part of  : AknExQuery
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

// INCLUDE FILES
#include "AknExQuery.hrh"
#include "AknExQueryContainer.h"
#include "AknExQueryTextAndTimeListEventHandler.h"
#include <aknexquery.rsg>
// MACROS

// CONSTANTS

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExQueryTextAndTimeListEventHandler::
//     CAknExQueryTextAndTimeListEventHandler()
// Default constructor.
// ----------------------------------------------------------------------------
//
CAknExQueryTextAndTimeListEventHandler::
    CAknExQueryTextAndTimeListEventHandler(
        CAknExQueryContainer* aContainer )
:   CAknExQueryBaseListEventHandler( aContainer )
    {
    }

// ----------------------------------------------------------------------------
// CAknExQueryTextAndTimeListEventHandler::
//     ~CAknExQueryTextAndTimeListEventHandler()
// Destructor.
// ----------------------------------------------------------------------------
//
CAknExQueryTextAndTimeListEventHandler::
    ~CAknExQueryTextAndTimeListEventHandler()
    {
    }

// ----------------------------------------------------------------------------
// CAknExQueryTextAndTimeListEventHandler::HandleSelectedListItemL(
//     TInt aCommand )
// ----------------------------------------------------------------------------
//
void CAknExQueryTextAndTimeListEventHandler::HandleSelectedListItemL(
    TInt aCommand )
    {
    switch ( aCommand )
        {
        case EAknExQueryListBoxCmdData1:
            iContainer->ShowMultiLineTextAndTimeLayoutL(
                R_AKNEXQUERY_MULTI_LINE_DATA_AND_DATE_LAYOUT,
                R_AKNEXQUERY_DATE_INITIAL_VALUE);
            break;
        case EAknExQueryListBoxCmdData2:
            iContainer->ShowMultiLineTextAndTimeLayoutL(
                R_AKNEXQUERY_MULTI_LINE_DATA_AND_TIME_LAYOUT,
                R_AKNEXQUERY_TIME_INITIAL_VALUE);
            break;
        case EAknExQueryListBoxCmdData3:
            iContainer->ShowMultiLineTextAndTimeLayoutL(
                R_AKNEXQUERY_MULTI_LINE_CODE_AND_DATE_LAYOUT,
                R_AKNEXQUERY_DATE_INITIAL_VALUE);
            break;
        case EAknExQueryListBoxCmdData4:
            iContainer->ShowMultiLineTextAndTimeLayoutL(
                R_AKNEXQUERY_MULTI_LINE_CODE_AND_TIME_LAYOUT,
                R_AKNEXQUERY_TIME_INITIAL_VALUE);
            break;
        default:
            break;
        }
    }

// End of File
