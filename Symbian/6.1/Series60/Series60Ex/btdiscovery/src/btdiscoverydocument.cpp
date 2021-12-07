/* Copyright (c) 2002, Nokia. All rights reserved */

#include "BTDiscoveryAppUi.h"
#include "BTDiscoveryDocument.h"

CBTDiscoveryDocument* CBTDiscoveryDocument::NewL(CEikApplication& aApp)
    {
    CBTDiscoveryDocument* self = NewLC(aApp);
    CleanupStack::Pop(self);
    return self;
    }

CBTDiscoveryDocument* CBTDiscoveryDocument::NewLC(CEikApplication& aApp)
    {
    CBTDiscoveryDocument* self = new (ELeave) CBTDiscoveryDocument(aApp);
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

void CBTDiscoveryDocument::ConstructL()
    {
    }    

CBTDiscoveryDocument::CBTDiscoveryDocument(CEikApplication& aApp) : CAknDocument(aApp) 
    {
    // no implementation required
    }   

CBTDiscoveryDocument::~CBTDiscoveryDocument()
    {
    }

CEikAppUi* CBTDiscoveryDocument::CreateAppUiL()
    {
    // Create the application user interface, and return a pointer to it
    CEikAppUi* appUi = new (ELeave) CBTDiscoveryAppUi;
    return appUi;
    }

