/* Copyright (c) 2001, Nokia. All rights reserved */

#include "GraphicsAppUi.h"
#include "GraphicsDocument.h"


// Standard Epoc construction sequence
CGraphicsDocument* CGraphicsDocument::NewL(CEikApplication& aApp)
    {
    CGraphicsDocument* self = NewLC(aApp);
    CleanupStack::Pop();
    return self;
    }

CGraphicsDocument* CGraphicsDocument::NewLC(CEikApplication& aApp)
    {
    CGraphicsDocument* self = new (ELeave) CGraphicsDocument(aApp);
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

void CGraphicsDocument::ConstructL()
    {
    // Add any construction that can leave here
    }    

CGraphicsDocument::CGraphicsDocument(CEikApplication& aApp) : CEikDocument(aApp) 
    {
    // Add any construction that can not leave here
    }   

CGraphicsDocument::~CGraphicsDocument()
    {
    // Any any destruction code here
    }

CEikAppUi* CGraphicsDocument::CreateAppUiL()
    {
    // Create the application user interface, and return a pointer to it
    CEikAppUi* appUi = new (ELeave) CGraphicsAppUi;
    return appUi;
    }

