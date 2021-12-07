/* Copyright (c) 2001, Nokia. All rights reserved */
#include "TestframeAppUi.h"
#include "TestframeDocument.h"


CTestframeDocument* CTestframeDocument::NewL(CEikApplication& aApp)
	{
    CTestframeDocument* self = CTestframeDocument::NewLC(aApp);
    CleanupStack::Pop(self);
    return self;
	}


CTestframeDocument* CTestframeDocument::NewLC(CEikApplication& aApp)
	{
    CTestframeDocument* self = new (ELeave) CTestframeDocument(aApp);
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
	}

CTestframeDocument::CTestframeDocument(CEikApplication& aApp) : CEikDocument(aApp)
	{
    // No implementation required
	}


void CTestframeDocument::ConstructL()
	{
    // No implementation required
	}    

CTestframeDocument::~CTestframeDocument()
	{
    // No implementation required
	}

CEikAppUi* CTestframeDocument::CreateAppUiL()
	{
    // Create the application user interface, and return a pointer to it
    CEikAppUi* appUi = new (ELeave) CTestframeAppUi();
    return appUi;
	}

