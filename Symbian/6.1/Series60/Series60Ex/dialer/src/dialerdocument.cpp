/* Copyright (c) 2001, Nokia. All rights reserved */

#include "DialerAppUi.h"
#include "DialerDocument.h"


// Standard Epoc construction sequence
CDialerDocument* CDialerDocument::NewL(CEikApplication& aApp)
    {
    CDialerDocument* self = NewLC(aApp);
    CleanupStack::Pop();
    return self;
    }

CDialerDocument* CDialerDocument::NewLC(CEikApplication& aApp)
    {
    CDialerDocument* self = new (ELeave) CDialerDocument(aApp);
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

void CDialerDocument::ConstructL()
    {
    // Add any construction that can leave here
    }    

CDialerDocument::CDialerDocument(CEikApplication& aApp) : CEikDocument(aApp) 
    {
    // Add any construction that can not leave here
    }   

CDialerDocument::~CDialerDocument()
    {
    // Any any destruction code here
    }

CEikAppUi* CDialerDocument::CreateAppUiL()
    {
    // Create the application user interface, and return a pointer to it
    CEikAppUi* appUi = new (ELeave) CDialerAppUi;
    return appUi;
    }

