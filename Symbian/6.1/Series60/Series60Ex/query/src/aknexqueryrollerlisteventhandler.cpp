/*
* =============================================================================
*  Name     : CAknExQueryRollerListEventHandler
*  Part of  : AknExQuery
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

// INCLUDE FILES
#include "AknExQuery.hrh"
#include "AknExQueryContainer.h"
#include "AknExQueryRollerListEventHandler.h"
#include <AknExQuery.rsg>
// MACROS

// CONSTANTS

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExQueryRollerListEventHandler::CAknExQueryRollerListEventHandler()
// Default constructor.
// ----------------------------------------------------------------------------
//
CAknExQueryRollerListEventHandler::CAknExQueryRollerListEventHandler(
    CAknExQueryContainer* aContainer )
:   CAknExQueryBaseListEventHandler( aContainer )
    {
    }

// ----------------------------------------------------------------------------
// CAknExQueryRollerListEventHandler::~CAknExQueryRollerListEventHandler()
// Destructor.
// ----------------------------------------------------------------------------
//
CAknExQueryRollerListEventHandler::~CAknExQueryRollerListEventHandler()
    {
    }

// ----------------------------------------------------------------------------
// CAknExQueryRollerListEventHandler::HandleSelectedListItemL( TInt aCommand )
//
// ----------------------------------------------------------------------------
//
void CAknExQueryRollerListEventHandler::HandleSelectedListItemL(
    TInt aCommand )
    {
    switch ( aCommand )
        {
        case EAknExQueryListBoxCmdData1:
            iContainer->ShowTimeQueryL(R_AKNEXQUERY_DATE_QUERY, 
                R_AKNEXQUERY_DATE_INITIAL_VALUE);
            break;
        case EAknExQueryListBoxCmdData2:
            iContainer->ShowTimeQueryL(
                R_AKNEXQUERY_TIME_QUERY, 
                R_AKNEXQUERY_TIME_INITIAL_VALUE);
            break;
        default:
            break;
        }
    }

// End of File
