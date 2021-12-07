/* Copyright (c) 2002, Nokia. All rights reserved */

#include "BTPointToPointAppUi.h"
#include "BTPointToPointDocument.h"


// Standard Symbian construction sequence
CBTPointToPointDocument* CBTPointToPointDocument::NewL(CEikApplication& aApp)
    {
    CBTPointToPointDocument* self = NewLC(aApp);
    CleanupStack::Pop(self);
    return self;
    }

CBTPointToPointDocument* CBTPointToPointDocument::NewLC(CEikApplication& aApp)
    {
    CBTPointToPointDocument* self = new (ELeave) CBTPointToPointDocument(aApp);
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

void CBTPointToPointDocument::ConstructL()
    {
    // no implementation required
    }    

CBTPointToPointDocument::CBTPointToPointDocument(CEikApplication& aApp) 
: CAknDocument(aApp) 
    {
    // no implementation required
    }   

CBTPointToPointDocument::~CBTPointToPointDocument()
    {
    // no implementation required
    }

CEikAppUi* CBTPointToPointDocument::CreateAppUiL()
    {
    // Create the application user interface, and return a pointer to it
    CEikAppUi* appUi = new (ELeave) CBTPointToPointAppUi;
    return appUi;
    }

