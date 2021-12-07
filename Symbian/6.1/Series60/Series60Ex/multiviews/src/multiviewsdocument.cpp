/* Copyright (c) 2002, Nokia. All rights reserved */

#include "MultiViewsAppUi.h"
#include "MultiViewsDocument.h"


// Standard Symbian OS construction sequence
CMultiViewsDocument* CMultiViewsDocument::NewL(CEikApplication& aApp)
    {
    CMultiViewsDocument* self = NewLC(aApp);
    CleanupStack::Pop(self);
    return self;
    }

CMultiViewsDocument* CMultiViewsDocument::NewLC(CEikApplication& aApp)
    {
    CMultiViewsDocument* self = new (ELeave) CMultiViewsDocument(aApp);
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

void CMultiViewsDocument::ConstructL()
    {
    // no implementation required
    }    

CMultiViewsDocument::CMultiViewsDocument(CEikApplication& aApp) : CAknDocument(aApp) 
    {
    // no implementation required
    }   

CMultiViewsDocument::~CMultiViewsDocument()
    {
    // no implementation required
    }

CEikAppUi* CMultiViewsDocument::CreateAppUiL()
    {
    // Create the application user interface, and return a pointer to it
    CEikAppUi* appUi = new (ELeave) CMultiViewsAppUi;
    return appUi;
    }

