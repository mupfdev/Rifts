/* Copyright (c) 2002, Nokia. All rights reserved */

#include "LanguageDocument.h"
#include "LanguageApplication.h"

// local constants
static const TUid KUidLanguageApp = {0x10005B90};

CApaDocument* CLanguageApplication::CreateDocumentL()
    {  
    // Create a Language document, and return a pointer to it
    CApaDocument* document = CLanguageDocument::NewL(*this);
    return document;
    }

TUid CLanguageApplication::AppDllUid() const
    {
    // Return the UID for the Language application
    return KUidLanguageApp;
    }

