/* Copyright (c) 2001, Nokia. All rights reserved */

#include "CSAsyncAppUi.h"
#include "CSAsyncDocument.h"
#include "CSAsyncRequestHandler.h"


// Standard Epoc construction sequence
CCSAsyncDocument* CCSAsyncDocument::NewL(CEikApplication& aApp)
    {
    CCSAsyncDocument* self = NewLC(aApp);
    CleanupStack::Pop();
    return self;
    }

CCSAsyncDocument* CCSAsyncDocument::NewLC(CEikApplication& aApp)
    {
    CCSAsyncDocument* self = new (ELeave) CCSAsyncDocument(aApp);
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

void CCSAsyncDocument::ConstructL()
    {
    // No implementation required
    }    

CCSAsyncDocument::CCSAsyncDocument(CEikApplication& aApp) : CEikDocument(aApp) 
    {
    // No implementation required
    }   

CCSAsyncDocument::~CCSAsyncDocument()
    {
    delete iHandler;
    iHandler = NULL ;
    }

CEikAppUi* CCSAsyncDocument::CreateAppUiL()
    {
    // Create the application user interface, and return a pointer to it
    CCSAsyncAppUi* appUi = new (ELeave) CCSAsyncAppUi;
    CleanupStack::PushL(appUi);
    iHandler = CCSAsyncRequestHandler::NewL(*appUi);
    CleanupStack::Pop(appUi) ;
    return appUi;
    }

void CCSAsyncDocument::UpdateTime()
    {
    iHandler->RequestTime();
    }

void CCSAsyncDocument::StopClock()
    {
    if (ClockActive())
        {
        iHandler->CancelRequest() ;
        }
    }

TTime CCSAsyncDocument::Time() const
    {
    return iHandler->Time();
    }

TBool CCSAsyncDocument::ClockActive() const
    {
    return iHandler->IsActive();
    }


