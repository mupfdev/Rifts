/*
* =============================================================================
*  Name     : CAknExQueryTextAndTextListEventHandler
*  Part of  : AknExQuery
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

// INCLUDE FILES
#include "AknExQuery.hrh"
#include "AknExQueryContainer.h"
#include "AknExQueryTextAndTextListEventHandler.h"
#include <aknexquery.rsg>
// MACROS

// CONSTANTS

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExQueryTextAndTextListEventHandler::
//     CAknExQueryTextAndTextListEventHandler()
// Default constructor.
// ----------------------------------------------------------------------------
//
CAknExQueryTextAndTextListEventHandler::
    CAknExQueryTextAndTextListEventHandler(
        CAknExQueryContainer* aContainer )
:   CAknExQueryBaseListEventHandler( aContainer )
    {
    }

// ----------------------------------------------------------------------------
// CAknExQueryTextAndTextListEventHandler::
//     ~CAknExQueryTextAndTextListEventHandler()
// Destructor.
// ----------------------------------------------------------------------------
//
CAknExQueryTextAndTextListEventHandler::
    ~CAknExQueryTextAndTextListEventHandler()
    {
    }

// ----------------------------------------------------------------------------
// CAknExQueryTextAndTextListEventHandler::HandleSelectedListItemL(
//     TInt aCommand )
// ----------------------------------------------------------------------------
//
void CAknExQueryTextAndTextListEventHandler::HandleSelectedListItemL(
    TInt aCommand )
    {
    switch ( aCommand )
        {
        case EAknExQueryListBoxCmdData1:
            iContainer->ShowMultiLineTextAndTextLayoutL(
                R_AKNEXQUERY_MULTI_LINE_DATA_AND_DATA_LAYOUT);
            break;
        case EAknExQueryListBoxCmdData2:
            iContainer->ShowMultiLineTextAndTextLayoutL(
                R_AKNEXQUERY_MULTI_LINE_DATA_AND_CODE_LAYOUT);
            break;
        case EAknExQueryListBoxCmdData3:
            iContainer->ShowMultiLineTextAndTextLayoutL(
                R_AKNEXQUERY_MULTI_LINE_CODE_AND_DATA_LAYOUT);
            break;
        case EAknExQueryListBoxCmdData4:
            iContainer->ShowMultiLineTextAndTextLayoutL(
            R_AKNEXQUERY_MULTI_LINE_CODE_AND_CODE_LAYOUT);
            break;
        default:
            break;
        }
    }

// End of File
