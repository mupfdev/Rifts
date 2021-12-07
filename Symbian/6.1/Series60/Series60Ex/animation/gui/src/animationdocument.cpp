/* Copyright (c) 2001, Nokia. All rights reserved */
#include "animationappui.h"
#include "animationdocument.h"


// Standard Epoc construction sequence
CAnimationDocument* CAnimationDocument::NewL(CEikApplication& aApp)
    {
    CAnimationDocument* self = NewLC(aApp);
    CleanupStack::Pop();
    return self;
    }

CAnimationDocument* CAnimationDocument::NewLC(CEikApplication& aApp)
    {
    CAnimationDocument* self = new (ELeave) CAnimationDocument(aApp);
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

void CAnimationDocument::ConstructL()
    {
    }    

CAnimationDocument::~CAnimationDocument()
    {
    }


CEikAppUi* CAnimationDocument::CreateAppUiL()
    {
    // Create the application user interface, and return a pointer to it
    CEikAppUi* appUi = new (ELeave) CAnimationAppUi(CCoeEnv::Static()->WsSession());
    return appUi;
    }

