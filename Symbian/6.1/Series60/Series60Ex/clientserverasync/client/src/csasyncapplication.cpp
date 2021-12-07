/* Copyright (c) 2001, Nokia. All rights reserved */

#include "CSAsyncDocument.h"
#include "CSAsyncApplication.h"

// local constants
static const TUid KUidCSAsyncApp = {0x10005B7B};

CApaDocument* CCSAsyncApplication::CreateDocumentL()
    {  
    // Create an CSAsync document, and return a pointer to it
    CApaDocument* document = CCSAsyncDocument::NewL(*this);
    return document;
    }

TUid CCSAsyncApplication::AppDllUid() const
    {
    // Return the UID for the CSAsync application
    return KUidCSAsyncApp;
    }

