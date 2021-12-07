/* Copyright (c) 2001, Nokia. All rights reserved */

#include "BmpmanipDocument.h"
#include "BmpmanipApplication.h"

// local constants
static const TUid KUidBmpmanipApp = {0x10005B80};

CApaDocument* CBmpmanipApplication::CreateDocumentL()
    {  
    // Create an Bmpmanip document, and return a pointer to it
    CApaDocument* document = CBmpmanipDocument::NewL(*this);
    return document;
    }

TUid CBmpmanipApplication::AppDllUid() const
    {
    // Return the UID for the Bmpmanip application
    return KUidBmpmanipApp;
    }

