/*
* ============================================================================
*  Name     : CAknExMenuDocument from CEikDocument
*  Part of  : AknExMenu
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include "AknExMenuDocument.h"
#include "AknExMenuAppUi.h"

// ================= MEMBER FUNCTIONS =======================

// C++ default constructor can not contain any code, that 
// might leave.
//
CAknExMenuDocument::CAknExMenuDocument(CEikApplication& aApp)
                       : CEikDocument(aApp)
    {
    }

// EPOC default constructor can leave.
void CAknExMenuDocument::ConstructL()
    {
    }

// Two-phased constructor.
CAknExMenuDocument* CAknExMenuDocument::NewL(CEikApplication& aApp)     // CAknExMenuApp reference
    {
    CAknExMenuDocument* self = new (ELeave) CAknExMenuDocument(aApp);
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop();
    return self;
    }
    
// destructor
CAknExMenuDocument::~CAknExMenuDocument()
    {
    }

// ----------------------------------------------------
// CAknExMenuDocument::CreateAppUiL()
// constructs CAknExMenuAppUi
//
// ----------------------------------------------------
CEikAppUi* CAknExMenuDocument::CreateAppUiL()
    {
    return new(ELeave) CAknExMenuAppUi;
    }

// End of File  
