/*
* =============================================================================
*  Name     : CAknExQueryTimeAndTimeListEventHandler
*  Part of  : AknExQuery
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

// INCLUDE FILES
#include "AknExQuery.hrh"
#include "AknExQueryContainer.h"
#include "AknExQueryTimeAndTimeListEventHandler.h"
#include <aknexquery.rsg>
// MACROS

// CONSTANTS

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExQueryTimeAndTimeListEventHandler::
//     CAknExQueryTimeAndTimeListEventHandler()
// Default constructor.
// ----------------------------------------------------------------------------
//
CAknExQueryTimeAndTimeListEventHandler::
    CAknExQueryTimeAndTimeListEventHandler(
        CAknExQueryContainer* aContainer )
:   CAknExQueryBaseListEventHandler( aContainer )
    {
    }

// ----------------------------------------------------------------------------
// CAknExQueryTimeAndTimeListEventHandler::
//     ~CAknExQueryTimeAndTimeListEventHandler()
// Destructor.
// ----------------------------------------------------------------------------
//
CAknExQueryTimeAndTimeListEventHandler::
    ~CAknExQueryTimeAndTimeListEventHandler()
    {
    }

// ----------------------------------------------------------------------------
// CAknExQueryTimeAndTimeListEventHandler::HandleSelectedListItemL(
//     TInt aCommand )
// ----------------------------------------------------------------------------
//
void CAknExQueryTimeAndTimeListEventHandler::HandleSelectedListItemL(
    TInt aCommand )
    {
    switch ( aCommand )
        {
        case EAknExQueryListBoxCmdData1:
            iContainer->ShowMultiLineTimeAndTimeLayoutL(
                R_AKNEXQUERY_MULTI_LINE_DATE_AND_DATE_LAYOUT,
                R_AKNEXQUERY_DATE_INITIAL_VALUE,
                R_AKNEXQUERY_DATE_INITIAL_VALUE2);
            break;
        case EAknExQueryListBoxCmdData2:
            iContainer->ShowMultiLineTimeAndTimeLayoutL(
                R_AKNEXQUERY_MULTI_LINE_DATE_AND_TIME_LAYOUT,
                R_AKNEXQUERY_DATE_INITIAL_VALUE,
                R_AKNEXQUERY_TIME_INITIAL_VALUE);
            break;
        case EAknExQueryListBoxCmdData3:
            iContainer->ShowMultiLineTimeAndTimeLayoutL(
                R_AKNEXQUERY_MULTI_LINE_TIME_AND_DATE_LAYOUT,
                R_AKNEXQUERY_TIME_INITIAL_VALUE,
                R_AKNEXQUERY_DATE_INITIAL_VALUE);
            break;
        case EAknExQueryListBoxCmdData4:
            iContainer->ShowMultiLineTimeAndTimeLayoutL(
                R_AKNEXQUERY_MULTI_LINE_TIME_AND_TIME_LAYOUT,
                R_AKNEXQUERY_TIME_INITIAL_VALUE,
                R_AKNEXQUERY_TIME_INITIAL_VALUE2);
            break;
        default:
            break;
        }
    }

// End of File
