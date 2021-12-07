/*
* =============================================================================
*  Name     : CAknExQueryEditorListEventHandler
*  Part of  : AknExQuery
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

// INCLUDE FILES
#include <AknExQuery.rsg>
#include "AknExQuery.hrh"
#include "AknExQueryContainer.h"
#include "AknExQueryEditorListEventHandler.h"

// MACROS

// CONSTANTS

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExQueryEditorListEventHandler::CAknExQueryEditorListEventHandler()
// Default constructor.
// ----------------------------------------------------------------------------
//
CAknExQueryEditorListEventHandler::CAknExQueryEditorListEventHandler(
    CAknExQueryContainer* aContainer )
:   CAknExQueryBaseListEventHandler( aContainer )
    {
    }

// ----------------------------------------------------------------------------
// CAknExQueryEditorListEventHandler::~CAknExQueryEditorListEventHandler()
// Destructor.
// ----------------------------------------------------------------------------
//
CAknExQueryEditorListEventHandler::~CAknExQueryEditorListEventHandler()
    {
    }

// ----------------------------------------------------------------------------
// CAknExQueryEditorListEventHandler::HandleSelectedListItemL( TInt aCommand )
//
// ----------------------------------------------------------------------------
//
void CAknExQueryEditorListEventHandler::HandleSelectedListItemL(
    TInt aCommand )
    {
    switch ( aCommand )
        {
        case EAknExQueryListBoxCmdData1:
            iContainer->ShowDataQueryL(
                R_AKNEXQUERY_DATA_QUERY, 
                R_AKNEXQUERY_DATA_QUERY_INITIAL_TEXT /*0*/ , 0, 0, EFalse);
            break;
        case EAknExQueryListBoxCmdData2:
            {
            TBuf<8> initialPassword;
            CCoeEnv::Static()->ReadResource(
                initialPassword, R_AKNEXQUERY_DATA_QUERY_INITIAL_PASSWORD);
            iContainer->ShowCodeQueryL(0, &initialPassword);
            break;
            }
        case EAknExQueryListBoxCmdData3:
            iContainer->ShowTimeQueryL(R_AKNEXQUERY_DATE_QUERY, 
                R_AKNEXQUERY_DATE_INITIAL_VALUE);
            break;
        case EAknExQueryListBoxCmdData4:
            iContainer->ShowTimeQueryL(R_AKNEXQUERY_TIME_QUERY, 
                R_AKNEXQUERY_TIME_INITIAL_VALUE);
            break;
        case EAknExQueryListBoxCmdData5:
            iContainer->ShowDurationLayoutL();
            break;
        case EAknExQueryListBoxCmdData6:
            iContainer->ShowNumberLayoutL(R_AKNEXQUERY_NUMBER_LAYOUT);
            break;
        default:
            break;
        }
    }

// End of File
