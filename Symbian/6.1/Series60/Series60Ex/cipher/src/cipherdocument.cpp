/* Copyright (c) 2002, Nokia. All rights reserved */

#include "CipherAppUi.h"
#include "CipherDocument.h"

// Standard Symbian OS construction sequence
CCipherDocument* CCipherDocument::NewL(CEikApplication& aApp)
    {
    CCipherDocument* self = NewLC(aApp);
    CleanupStack::Pop(self);
    return self;
    }

CCipherDocument* CCipherDocument::NewLC(CEikApplication& aApp)
    {
    CCipherDocument* self = new (ELeave) CCipherDocument(aApp);
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

void CCipherDocument::ConstructL()
    {
    // No implementation required
    }    

CCipherDocument::CCipherDocument(CEikApplication& aApp) : CAknDocument(aApp) 
    {
    // No implementation required
    }   

CCipherDocument::~CCipherDocument()
    {
    // No implementation required
    }

CEikAppUi* CCipherDocument::CreateAppUiL()
    {
    // Create the application user interface, and return a pointer to it,
    // the framework takes ownership of this object
    CEikAppUi* appUi = new (ELeave) CCipherAppUi;
    return appUi;
    }

