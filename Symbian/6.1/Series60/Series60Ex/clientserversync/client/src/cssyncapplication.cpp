/* Copyright (c) 2001, Nokia. All rights reserved */
#include "CSSyncDocument.h"
#include "CSSyncApplication.h"

// local constants
static const TUid KUidCSSyncApp = {0x10005B79};

CApaDocument* CCSSyncApplication::CreateDocumentL()
    {  
    // Create an CSSync document, and return a pointer to it
    CApaDocument* document = CCSSyncDocument::NewL(*this);
    return document;
    }

TUid CCSSyncApplication::AppDllUid() const
    {
    // Return the UID for the CSSync application
    return KUidCSSyncApp;
    }

