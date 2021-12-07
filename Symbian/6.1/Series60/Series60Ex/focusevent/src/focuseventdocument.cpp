/* Copyright (c) 2001, Nokia. All rights reserved */
#include "FocusEventAppUi.h"
#include "FocusEventDocument.h"


// Standard Epoc construction sequence
CFocusEventDocument* CFocusEventDocument::NewL(CEikApplication& aApp)
    {
    CFocusEventDocument* self = NewLC(aApp);
    CleanupStack::Pop();
    return self;
    }

CFocusEventDocument* CFocusEventDocument::NewLC(CEikApplication& aApp)
    {
    CFocusEventDocument* self = new (ELeave) CFocusEventDocument(aApp);
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

void CFocusEventDocument::ConstructL()
    {
    // Add any construction that can leave here
    }    

CFocusEventDocument::CFocusEventDocument(CEikApplication& aApp) : CEikDocument(aApp) 
    {
    // Add any construction that can not leave here
    }   

CFocusEventDocument::~CFocusEventDocument()
    {
    // Any any destruction code here
    }

CEikAppUi* CFocusEventDocument::CreateAppUiL()
    {
    // Create the application user interface, and return a pointer to it
    CEikAppUi* appUi = new (ELeave) CFocusEventAppUi;
    return appUi;
    }

