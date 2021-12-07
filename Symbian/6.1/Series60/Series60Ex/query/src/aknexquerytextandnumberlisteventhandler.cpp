/*
* =============================================================================
*  Name     : CAknExQueryTextAndNumberListEventHandler
*  Part of  : AknExQuery
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

// INCLUDE FILES
#include "AknExQuery.hrh"
#include "AknExQueryContainer.h"
#include "AknExQueryTextAndNumberListEventHandler.h"
#include <aknexquery.rsg>
// MACROS

// CONSTANTS

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExQueryTextAndNumberListEventHandler::
//     CAknExQueryTextAndNumberListEventHandler()
// Default constructor.
// ----------------------------------------------------------------------------
//
CAknExQueryTextAndNumberListEventHandler::
    CAknExQueryTextAndNumberListEventHandler(
        CAknExQueryContainer* aContainer )
:   CAknExQueryBaseListEventHandler( aContainer )
    {
    }

// ----------------------------------------------------------------------------
// CAknExQueryTextAndNumberListEventHandler::
//     ~CAknExQueryTextAndNumberListEventHandler()
// Destructor.
// ----------------------------------------------------------------------------
//
CAknExQueryTextAndNumberListEventHandler::
    ~CAknExQueryTextAndNumberListEventHandler()
    {
    }

// ----------------------------------------------------------------------------
// CAknExQueryTextAndNumberListEventHandler::HandleSelectedListItemL(
//     TInt aCommand )
// ----------------------------------------------------------------------------
//
void CAknExQueryTextAndNumberListEventHandler::HandleSelectedListItemL(
    TInt aCommand )
    {
    switch ( aCommand )
        {
        case EAknExQueryListBoxCmdData1:
            iContainer->ShowMultiLineTextAndNumberLayoutL(
                R_AKNEXQUERY_MULTI_LINE_DATA_AND_NUMBER_LAYOUT);
            break;
        case EAknExQueryListBoxCmdData2:
            iContainer->ShowMultiLineTextAndNumberLayoutL(
                R_AKNEXQUERY_MULTI_LINE_CODE_AND_NUMBER_LAYOUT);
            break;
        default:
            break;
        }
    }

// End of File
