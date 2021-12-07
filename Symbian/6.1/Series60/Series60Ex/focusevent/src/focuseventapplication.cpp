/* Copyright (c) 2001, Nokia. All rights reserved */
#include "FocusEventDocument.h"
#include "FocusEventApplication.h"

// local constants
static const TUid KUidFocusEventApp = {0x10005B6E};

CApaDocument* CFocusEventApplication::CreateDocumentL()
    {  
    // Create a FocusEvent document, and return a pointer to it
    CApaDocument* document = CFocusEventDocument::NewL(*this);
    return document;
    }

TUid CFocusEventApplication::AppDllUid() const
    {
    // Return the UID for the FocusEvent application
    return KUidFocusEventApp;
    }

