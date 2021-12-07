/* Copyright (c) 2002, Nokia. All rights reserved */

#include "HelloWorldPlusDocument.h"
#include "HelloWorldPlusApplication.h"

// local constants
static const TUid KUidHelloWorldPlusApp = {0x10005b95}; 

CApaDocument* CHelloWorldPlusApplication::CreateDocumentL()
    {  
    // Create an HelloWorldPlus document, and return a pointer to it
    CApaDocument* document = CHelloWorldPlusDocument::NewL(*this);
    return document;
    }

TUid CHelloWorldPlusApplication::AppDllUid() const
    {
    // Return the UID for the HelloWorldPlus application
    return KUidHelloWorldPlusApp;
    }

