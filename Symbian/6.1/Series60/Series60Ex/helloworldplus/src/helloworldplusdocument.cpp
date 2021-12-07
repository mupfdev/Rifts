/* Copyright (c) 2002, Nokia. All rights reserved */

#include "HelloWorldPlusAppUi.h"
#include "HelloWorldPlusDocument.h"


// Standard Symbian OS construction sequence
CHelloWorldPlusDocument* CHelloWorldPlusDocument::NewL(CEikApplication& aApp)
    {
    CHelloWorldPlusDocument* self = NewLC(aApp);
    CleanupStack::Pop(self);
    return self;
    }

CHelloWorldPlusDocument* CHelloWorldPlusDocument::NewLC(CEikApplication& aApp)
    {
    CHelloWorldPlusDocument* self = new (ELeave) CHelloWorldPlusDocument(aApp);
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

void CHelloWorldPlusDocument::ConstructL()
    {
    // Add any construction that can leave here
    }    

CHelloWorldPlusDocument::CHelloWorldPlusDocument(CEikApplication& aApp) : CAknDocument(aApp) 
    {
    // Add any construction that can not leave here
    }   

CHelloWorldPlusDocument::~CHelloWorldPlusDocument()
    {
    // Any destruction code here
    }

CEikAppUi* CHelloWorldPlusDocument::CreateAppUiL()
    {
    // Create the application user interface, and return a pointer to it
    CEikAppUi* appUi = new (ELeave) CHelloWorldPlusAppUi;
    return appUi;
    }

