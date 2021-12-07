/* Copyright (c) 2001, Nokia. All rights reserved */

#include "BmpmanipAppUi.h"
#include "BmpmanipDocument.h"


// Standard Epoc construction sequence
CBmpmanipDocument* CBmpmanipDocument::NewL(CEikApplication& aApp)
    {
    CBmpmanipDocument* self = NewLC(aApp);
    CleanupStack::Pop();
    return self;
    }

CBmpmanipDocument* CBmpmanipDocument::NewLC(CEikApplication& aApp)
    {
    CBmpmanipDocument* self = new (ELeave) CBmpmanipDocument(aApp);
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

void CBmpmanipDocument::ConstructL()
    {
    // Add any construction that can leave here
    }    

CBmpmanipDocument::CBmpmanipDocument(CEikApplication& aApp) : CEikDocument(aApp) 
    {
    // Add any construction that can not leave here
    }   

CBmpmanipDocument::~CBmpmanipDocument()
    {
    // Any any destruction code here
    }

CEikAppUi* CBmpmanipDocument::CreateAppUiL()
    {
    // Create the application user interface, and return a pointer to it
    CEikAppUi* appUi = new (ELeave) CBmpmanipAppUi;
    return appUi;
    }

