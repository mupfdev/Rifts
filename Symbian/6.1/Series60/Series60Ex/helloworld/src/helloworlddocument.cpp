/* Copyright (c) 2002, Nokia. All rights reserved */

#include "HelloWorldAppUi.h"
#include "HelloWorldDocument.h"

// Standard Symbian OS construction sequence
CHelloWorldDocument* CHelloWorldDocument::NewL(CEikApplication& aApp)
    {
    CHelloWorldDocument* self = NewLC(aApp);
    CleanupStack::Pop(self);
    return self;
    }

CHelloWorldDocument* CHelloWorldDocument::NewLC(CEikApplication& aApp)
    {
    CHelloWorldDocument* self = new (ELeave) CHelloWorldDocument(aApp);
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

void CHelloWorldDocument::ConstructL()
    {
	// no implementation required
    }    

CHelloWorldDocument::CHelloWorldDocument(CEikApplication& aApp) : CAknDocument(aApp) 
    {
	// no implementation required
    }

CHelloWorldDocument::~CHelloWorldDocument()
    {
	// no implementation required
    }

CEikAppUi* CHelloWorldDocument::CreateAppUiL()
    {
    // Create the application user interface, and return a pointer to it,
    // the framework takes ownership of this object
    CEikAppUi* appUi = new (ELeave) CHelloWorldAppUi;
    return appUi;
    }

