/*
* ============================================================================
*  Name     : CAknExPopListDocument from CEikDocument
*  Part of  : AknExPopList
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include "AknExPopListDocument.h"
#include "AknExPopListAppUi.h"

// ================= MEMBER FUNCTIONS =======================

// constructor
CAknExPopListDocument::CAknExPopListDocument(CEikApplication& aApp)
                            : CEikDocument(aApp)
    {
    }

// destructor
CAknExPopListDocument::~CAknExPopListDocument()
    {
    }

// EPOC default constructor can leave.
void CAknExPopListDocument::ConstructL()
    {
    }

// Two-phased constructor.
CAknExPopListDocument* CAknExPopListDocument::NewL(
        CEikApplication& aApp)     // CAknExPopListApp reference
    {
    CAknExPopListDocument* self = new (ELeave) CAknExPopListDocument(aApp);
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop();
    return self;
    }
    
// ----------------------------------------------------
// CAknExPopListDocument::CreateAppUiL()
// constructs CAknExPopListAppUi
//
// ----------------------------------------------------
CEikAppUi* CAknExPopListDocument::CreateAppUiL()
    {
    return new(ELeave) CAknExPopListAppUi;
    }

// End of File  
