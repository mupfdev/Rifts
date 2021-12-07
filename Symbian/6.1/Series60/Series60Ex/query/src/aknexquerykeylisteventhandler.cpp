/*
* =============================================================================
*  Name     : CAknExQueryKeyListEventHandler
*  Part of  : AknExQuery
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

// INCLUDE FILES
#include <AknExQuery.rsg>
#include "AknExQuery.hrh"
#include "AknExQueryContainer.h"
#include "AknExQueryKeyListEventHandler.h"

// MACROS

// CONSTANTS

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExQueryKeyListEventHandler::CAknExQueryKeyListEventHandler()
// Default constructor.
// ----------------------------------------------------------------------------
//
CAknExQueryKeyListEventHandler::CAknExQueryKeyListEventHandler(
    CAknExQueryContainer* aContainer )
:   CAknExQueryBaseListEventHandler( aContainer )
    {
    }

// ----------------------------------------------------------------------------
// CAknExQueryKeyListEventHandler::~CAknExQueryKeyListEventHandler()
// Destructor.
// ----------------------------------------------------------------------------
//
CAknExQueryKeyListEventHandler::~CAknExQueryKeyListEventHandler()
    {
    }

// ----------------------------------------------------------------------------
// CAknExQueryKeyListEventHandler::HandleSelectedListItemL( TInt aCommand )
//
// ----------------------------------------------------------------------------
//
void CAknExQueryKeyListEventHandler::HandleSelectedListItemL( TInt aCommand )
    {
    switch ( aCommand )
        {
        case EAknExQueryListBoxCmdData1:
            iContainer->ShowDataQueryL( R_AKNEXQUERY_ONELINE_DATA_QUERY,
                                        R_AKNEXQUERY_DATA_QUERY_INITIAL_TEXT,
                                        0, 0, EFalse);
            break;
        case EAknExQueryListBoxCmdData2:
            iContainer->ShowDataQueryL(
                R_AKNEXQUERY_DATA_QUERY,
                R_AKNEXQUERY_DATA_QUERY_INITIAL_LONG_TEXT,
                0, 0, EFalse);
            break;
        case EAknExQueryListBoxCmdData3:
            iContainer->ShowMultiLineTextAndTextLayoutL(
                R_AKNEXQUERY_MULTI_LINE_DATA_AND_DATA_LAYOUT,
                R_AKNEXQUERY_MULTILINE_DATA_QUERY_INITIAL_TEXT1,
                R_AKNEXQUERY_MULTILINE_DATA_QUERY_INITIAL_TEXT2,
                EFalse);
            break;
        default:
            break;
        }
    }

// End of File
