/* Copyright (c) 2002, Nokia. All rights reserved */

#include "BTHCIAppUi.h"
#include "BTHCIDocument.h"

CBTHCIDocument* CBTHCIDocument::NewL(CEikApplication& aApp)
    {
    CBTHCIDocument* self = NewLC(aApp);
    CleanupStack::Pop(self);
    return self;
    }

CBTHCIDocument* CBTHCIDocument::NewLC(CEikApplication& aApp)
    {
    CBTHCIDocument* self = new (ELeave) CBTHCIDocument(aApp);
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

void CBTHCIDocument::ConstructL()
    {
    }    

CBTHCIDocument::CBTHCIDocument(CEikApplication& aApp) : CAknDocument(aApp) 
    {
    // no implementation required
    }   

CBTHCIDocument::~CBTHCIDocument()
    {
    }

CEikAppUi* CBTHCIDocument::CreateAppUiL()
    {
    // Create the application user interface, and return a pointer to it
    CEikAppUi* appUi = new (ELeave) CBTHCIAppUi;
    return appUi;
    }

