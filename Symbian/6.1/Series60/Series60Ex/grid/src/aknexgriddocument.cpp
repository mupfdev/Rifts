/*
* ============================================================================
*  Name     : CAknExGridDocument from CEikDocument
*  Part of  : AknExGrid
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include "AknExGridDocument.h"
#include "AknExGridAppUi.h"

// ================= MEMBER FUNCTIONS =======================
// C++ default constructor can NOT contain any code, that
// might leave.
//
CAknExGridDocument::CAknExGridDocument( CEikApplication& aApp )
    :CEikDocument( aApp )
    {
    }

// destructor
CAknExGridDocument::~CAknExGridDocument()
    {
    }

// EPOC default constructor can leave.
void CAknExGridDocument::ConstructL()
    {
    }

// Two-phased constructor.
CAknExGridDocument* CAknExGridDocument::NewL(
    CEikApplication& aApp )     // CAknExGridApp reference
    {
    CAknExGridDocument* self = new ( ELeave ) CAknExGridDocument( aApp );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();
    return self;
    }
    
// ----------------------------------------------------
// CAknExGridDocument::CreateAppUiL()
// constructs CAknExGridAppUi
//
// ----------------------------------------------------
CEikAppUi* CAknExGridDocument::CreateAppUiL()
    {
    return new( ELeave ) CAknExGridAppUi;
    }

// End of File  
