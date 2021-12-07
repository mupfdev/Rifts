/*
* ============================================================================
*  Name     : CAknExPbarDocument from CEikDocument
*  Part of  : AknExPbar
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/


// INCLUDE FILES
#include "AknExPbarDocument.h"
#include "AknExPbarAppUi.h"


// ================= MEMBER FUNCTIONS =======================

// C++ default constructor can NOT contain any code, that
// might leave.
//
CAknExPbarDocument::CAknExPbarDocument( CEikApplication& aApp )
                   : CEikDocument( aApp ) 
    {
    }

// Destructor
CAknExPbarDocument::~CAknExPbarDocument()
    {
    }

// EPOC default constructor can leave.
void CAknExPbarDocument::ConstructL()
    {
    }

// Two-phased constructor.
CAknExPbarDocument* CAknExPbarDocument::NewL
                           ( CEikApplication& aApp )
                           // CAknExPbarApp reference
    {
    CAknExPbarDocument* self =
                            new( ELeave ) CAknExPbarDocument( aApp );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();
    return self;
    }
    
// ----------------------------------------------------
// CAknExPbarDocument::CreateAppUiL()
// constructs CAknExPbarAppUi
//
// ----------------------------------------------------
CEikAppUi* CAknExPbarDocument::CreateAppUiL()
    {
    return new( ELeave ) CAknExPbarAppUi;
    }

// End of File  
