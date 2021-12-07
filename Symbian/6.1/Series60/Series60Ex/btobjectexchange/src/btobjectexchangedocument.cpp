/* Copyright (c) 2002, Nokia. All rights reserved */

#include "BTObjectExchangeAppUi.h"
#include "BTObjectExchangeDocument.h"


// Standard Symbian OS construction sequence
CBTObjectExchangeDocument* CBTObjectExchangeDocument::NewL(CEikApplication& aApp)
    {
    CBTObjectExchangeDocument* self = NewLC(aApp);
    CleanupStack::Pop(self);
    return self;
    }

CBTObjectExchangeDocument* CBTObjectExchangeDocument::NewLC(CEikApplication& aApp)
    {
    CBTObjectExchangeDocument* self = new (ELeave) CBTObjectExchangeDocument(aApp);
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

void CBTObjectExchangeDocument::ConstructL()
    {
    // no implementation required
    }    

CBTObjectExchangeDocument::CBTObjectExchangeDocument(CEikApplication& aApp)
: CAknDocument(aApp) 
    {
    // no implementation required
    }   

CBTObjectExchangeDocument::~CBTObjectExchangeDocument()
    {
    // no implementation required
    }

CEikAppUi* CBTObjectExchangeDocument::CreateAppUiL()
    {
    // Create the application user interface, and return a pointer to it
    CEikAppUi* appUi = new (ELeave) CBTObjectExchangeAppUi;
    return appUi;
    }

