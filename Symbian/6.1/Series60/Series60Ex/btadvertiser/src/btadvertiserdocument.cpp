/* Copyright (c) 2002, Nokia. All rights reserved */

#include "BTAdvertiserAppUi.h"
#include "BTAdvertiserDocument.h"


// Standard Symbian construction sequence
CBTAdvertiserDocument* CBTAdvertiserDocument::NewL(CEikApplication& aApp)
    {
    CBTAdvertiserDocument* self = NewLC(aApp);
    CleanupStack::Pop(self);
    return self;
    }

CBTAdvertiserDocument* CBTAdvertiserDocument::NewLC(CEikApplication& aApp)
    {
    CBTAdvertiserDocument* self = new (ELeave) CBTAdvertiserDocument(aApp);
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

void CBTAdvertiserDocument::ConstructL()
    {
    // Add any construction that can leave here
    }    

CBTAdvertiserDocument::CBTAdvertiserDocument(CEikApplication& aApp) : CAknDocument(aApp) 
    {
    // Add any construction that can not leave here
    }   

CBTAdvertiserDocument::~CBTAdvertiserDocument()
    {
    }

CEikAppUi* CBTAdvertiserDocument::CreateAppUiL()
    {
    CEikAppUi* appUi = new (ELeave) CBTAdvertiserAppUi;
    return appUi;
    }

