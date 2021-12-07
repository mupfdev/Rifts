/* Copyright (c) 2002, Nokia. All rights reserved */

#include "HelloWorldDocument.h"
#include "HelloWorldApplication.h"

// UID for the application, this should correspond to the uid defined in the mmp file
static const TUid KUidHelloWorldApp = {0x10005B91};

CApaDocument* CHelloWorldApplication::CreateDocumentL()
    {  
    // Create an HelloWorld document, and return a pointer to it
    CApaDocument* document = CHelloWorldDocument::NewL(*this);
    return document;
    }

TUid CHelloWorldApplication::AppDllUid() const
    {
    // Return the UID for the HelloWorld application
    return KUidHelloWorldApp;
    }

