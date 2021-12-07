/* Copyright (c) 2001, Nokia. All rights reserved */

#include "SocketsAppUi.h"
#include "SocketsDocument.h"


// Standard Epoc construction sequence
CSocketsDocument* CSocketsDocument::NewL(CEikApplication& aApp)
    {
    CSocketsDocument* self = NewLC(aApp);
    CleanupStack::Pop(self);
    return self;
    }

CSocketsDocument* CSocketsDocument::NewLC(CEikApplication& aApp)
    {
    CSocketsDocument* self = new (ELeave) CSocketsDocument(aApp);
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

void CSocketsDocument::ConstructL()
    {
    }    

CSocketsDocument::CSocketsDocument(CEikApplication& aApp) : CEikDocument(aApp) 
    {
    }   

CSocketsDocument::~CSocketsDocument()
    {
    }

CEikAppUi* CSocketsDocument::CreateAppUiL()
    {
    // Create the application user interface, and return a pointer to it
    CEikAppUi* appUi = new (ELeave) CSocketsAppUi;
    return appUi;
    }

