/*
* ============================================================================
*  Name     : CAknExSpaneDocument from CEikDocument
*  Part of  : AknExSpane
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include "AknExSpaneDocument.h"
#include "AknExSpaneAppUi.h"

// ================= MEMBER FUNCTIONS =======================
// C++ default constructor can NOT contain any code, that
// might leave.
//
CAknExSpaneDocument::CAknExSpaneDocument(CEikApplication& aApp)
                      : CEikDocument(aApp)
    {
    }

// EPOC default constructor can leave.
void CAknExSpaneDocument::ConstructL()
    {
    }

// Two-phased constructor.
CAknExSpaneDocument* CAknExSpaneDocument::NewL(
        CEikApplication& aApp)     // CAknExSpaneApp reference
    {
    CAknExSpaneDocument* self = new (ELeave) CAknExSpaneDocument(aApp);
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop();
    return self;
    }
    
// destructor
CAknExSpaneDocument::~CAknExSpaneDocument()
    {
    }

// ----------------------------------------------------
// CAknExSpaneDocument::CreateAppUiL()
// constructs CAknExSpaneAppUi
//
// ----------------------------------------------------
CEikAppUi* CAknExSpaneDocument::CreateAppUiL()
    {
    return new(ELeave) CAknExSpaneAppUi;
    }

// End of File  
