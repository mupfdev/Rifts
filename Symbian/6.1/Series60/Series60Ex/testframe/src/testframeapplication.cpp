/* Copyright (c) 2001, Nokia. All rights reserved */
#include "TestframeDocument.h"
#include "TestframeApplication.h"


// local constants
const TUid KUidtestframeApp = {0x10005B86};

CApaDocument* CTestframeApplication::CreateDocumentL()
	{  
    // Create an testframe document, and return a pointer to it
    CApaDocument* document = CTestframeDocument::NewL(*this);
    return document;
	}

TUid CTestframeApplication::AppDllUid() const
	{
    // Return the UID for the testframe application
    return KUidtestframeApp;
	}

