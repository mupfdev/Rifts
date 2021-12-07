/*
* ============================================================================
*  Name     : CAknExEditorDocument from CEikDocument
*  Part of  : AknExEditor
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include "AknExEditorDocument.h"
#include "AknExEditorAppUi.h"

// ================= MEMBER FUNCTIONS =======================

// EPOC default constructor can leave.
void CAknExEditorDocument::ConstructL()
    {
    }

// Two-phased constructor.
CAknExEditorDocument* CAknExEditorDocument::NewL(
        CEikApplication& aApp)     // CAknExEditorApp reference
    {
    CAknExEditorDocument* self = new (ELeave) CAknExEditorDocument(aApp);
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop();
    return self;
    }

// destructor
CAknExEditorDocument::~CAknExEditorDocument()
    {
    }

// ----------------------------------------------------
// CAknExEditorDocument::CreateAppUiL()
// constructs CAknExEditorAppUi
//
// ----------------------------------------------------
CEikAppUi* CAknExEditorDocument::CreateAppUiL()
    {
    return new (ELeave) CAknExEditorAppUi;
    }

// End of File  
