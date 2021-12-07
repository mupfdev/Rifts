/* Copyright (c) 2001, Nokia. All rights reserved */
#include "CSSyncAppUi.h"
#include "CSSyncDocument.h"


// Standard Epoc construction sequence
CCSSyncDocument* CCSSyncDocument::NewL(CEikApplication& aApp)
    {
    CCSSyncDocument* self = NewLC(aApp);
    CleanupStack::Pop();
    return self;
    }

CCSSyncDocument* CCSSyncDocument::NewLC(CEikApplication& aApp)
    {
    CCSSyncDocument* self = new (ELeave) CCSSyncDocument(aApp);
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

void CCSSyncDocument::ConstructL()
    {
    User::LeaveIfError(iServer.Connect());
    }    

CCSSyncDocument::CCSSyncDocument(CEikApplication& aApp) : CEikDocument(aApp) 
    {
    // No implementation required
    }   

CCSSyncDocument::~CCSSyncDocument()
    {
    iServer.Close();
    }

CEikAppUi* CCSSyncDocument::CreateAppUiL()
    {
    // Create the application user interface, and return a pointer to it
    CEikAppUi* appUi = new (ELeave) CCSSyncAppUi();
    return appUi;
    }

void CCSSyncDocument::UpdateTime()
    {
    iServer.RequestTime(iTime);
    }

const TTime& CCSSyncDocument::GetTime() const
    {
    return iTime;
    }
