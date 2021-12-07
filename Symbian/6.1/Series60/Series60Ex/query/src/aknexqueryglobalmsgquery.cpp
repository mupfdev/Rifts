/*
* =============================================================================
*  Name     : CAknExQueryGlobalMsgQuery
*  Part of  : AknExQuery
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

// INCLUDE FILES
#include "AknExQueryGlobalMsgQuery.h"


// MACROS

// CONSTANTS
// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExQueryGlobalMsgQuery::CAknExQueryGlobalMsgQuery()
// Default constructor.
// ----------------------------------------------------------------------------
//
CAknExQueryGlobalMsgQuery::CAknExQueryGlobalMsgQuery() 
                                                
                                                  
    {
    iGlobalMsgQuery = CAknGlobalMsgQuery::NewL();
    }

// ----------------------------------------------------------------------------
// CAknExQueryGlobalMsgQuery::~CAknExQueryGlobalMsgQuery()
// Destructor.
// ----------------------------------------------------------------------------
//
CAknExQueryGlobalMsgQuery::~CAknExQueryGlobalMsgQuery()
    {
    delete iGlobalMsgQuery;
    }
// End of File
