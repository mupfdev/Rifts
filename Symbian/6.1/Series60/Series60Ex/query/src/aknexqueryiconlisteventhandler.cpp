/*
* =============================================================================
*  Name     : CAknExQueryIconListEventHandler
*  Part of  : AknExQuery
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

// INCLUDE FILES
#include <AknExQuery.rsg>
#include "AknExQuery.hrh"
#include "AknExQueryContainer.h"
#include "AknExQueryIconListEventHandler.h"

// MACROS

// CONSTANTS

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExQueryIconListEventHandler::CAknExQueryIconListEventHandler()
// Default constructor.
// ----------------------------------------------------------------------------
//
CAknExQueryIconListEventHandler::CAknExQueryIconListEventHandler(
    CAknExQueryContainer* aContainer )
:   CAknExQueryBaseListEventHandler( aContainer )
    {
    }

// ----------------------------------------------------------------------------
// CAknExQueryIconListEventHandler::~CAknExQueryIconListEventHandler()
// Destructor.
// ----------------------------------------------------------------------------
//
CAknExQueryIconListEventHandler::~CAknExQueryIconListEventHandler()
    {
    }

// ----------------------------------------------------------------------------
// CAknExQueryIconListEventHandler::HandleSelectedListItemL( TInt aCommand )
//
// ----------------------------------------------------------------------------
//
void CAknExQueryIconListEventHandler::HandleSelectedListItemL( TInt aCommand )
    {
    switch ( aCommand )
        {
        case EAknExQueryListBoxCmdData1:
            iContainer->ShowDataQueryL( R_AKNEXQUERY_DATA_QUERY );
            break;
        case EAknExQueryListBoxCmdData2:
            iContainer->ShowCodeQueryL();
            break;
        default:
            break;
        }
    }

// End of File
