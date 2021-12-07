/* Copyright (c) 2002, Nokia. All rights reserved */

#include "ErrorUiAppUi.h"
#include "ErrorUiDocument.h"


// Standard Symbian OS construction sequence
CErrorUiDocument* CErrorUiDocument::NewL(CEikApplication& aApp)
    {
    CErrorUiDocument* self = NewLC(aApp);
    CleanupStack::Pop(self);
    return self;
    }

CErrorUiDocument* CErrorUiDocument::NewLC(CEikApplication& aApp)
    {
    CErrorUiDocument* self = new (ELeave) CErrorUiDocument(aApp);
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

void CErrorUiDocument::ConstructL()
    {
    }    

CErrorUiDocument::CErrorUiDocument(CEikApplication& aApp) : CAknDocument(aApp) 
    {
    }   

CErrorUiDocument::~CErrorUiDocument()
    {
    }

CEikAppUi* CErrorUiDocument::CreateAppUiL()
    {
    // Create the application user interface, and return a pointer to it,
    // the framework takes ownership of this object
    CEikAppUi* appUi = new (ELeave) CErrorUiAppUi;
    return appUi;
    }

