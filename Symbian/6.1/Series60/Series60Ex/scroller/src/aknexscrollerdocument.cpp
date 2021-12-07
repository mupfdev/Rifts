/*
* ============================================================================
*  Name     : CAknExScrollerDocument from CEikDocument
*  Part of  : AknExScroller
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include "AknExScrollerDocument.h"
#include "AknExScrollerAppUi.h"

// ================= MEMBER FUNCTIONS =======================

// Two-phased constructor.
CAknExScrollerDocument* CAknExScrollerDocument::NewL(
        CEikApplication& aApp )     // CAknExScrollerApp reference
    {
    CAknExScrollerDocument* self =
                             new ( ELeave ) CAknExScrollerDocument( aApp );

    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();

    return self;
    }


// destructor
CAknExScrollerDocument::~CAknExScrollerDocument()
    {
    }


// C++ default constructor can NOT contain any code, that
// might leave.
//
CAknExScrollerDocument::CAknExScrollerDocument( CEikApplication& aApp )
                      : CEikDocument( aApp )
    {
    }


// EPOC default constructor can leave.
void CAknExScrollerDocument::ConstructL()
    {
    }

    
// ----------------------------------------------------
// CAknExScrollerDocument::CreateAppUiL()
// constructs CAknExScrollerAppUi
// ----------------------------------------------------
//
CEikAppUi* CAknExScrollerDocument::CreateAppUiL()
    {
    return new ( ELeave ) CAknExScrollerAppUi;
    }

// End of File  
