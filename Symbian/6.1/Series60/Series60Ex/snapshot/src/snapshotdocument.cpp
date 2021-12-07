/* Copyright (c) 2001, Nokia. All rights reserved */

#include "SnapShotAppUi.h"
#include "SnapShotDocument.h"


// Standard Epoc construction sequence
CSnapShotDocument* CSnapShotDocument::NewL(CEikApplication& aApp)
    {
    CSnapShotDocument* self = NewLC(aApp);
    CleanupStack::Pop();
    return self;
    }

CSnapShotDocument* CSnapShotDocument::NewLC(CEikApplication& aApp)
    {
    CSnapShotDocument* self = new (ELeave) CSnapShotDocument(aApp);
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

void CSnapShotDocument::ConstructL()
    {
    // Add any construction that can leave here
    }    

CSnapShotDocument::CSnapShotDocument(CEikApplication& aApp) : CEikDocument(aApp) 
    {
    // Add any construction that can not leave here
    }   

CSnapShotDocument::~CSnapShotDocument()
    {
    // Any any destruction code here
    }

CEikAppUi* CSnapShotDocument::CreateAppUiL()
    {
    // Create the application user interface, and return a pointer to it
    CEikAppUi* appUi = new (ELeave) CSnapShotAppUi;
    return appUi;
    }

