/* Copyright (c) 2001, Nokia. All rights reserved */

#include "DialerDocument.h"
#include "DialerApplication.h"

// local constants
static const TUid KUidDialerApp = {0x10005B82};

CApaDocument* CDialerApplication::CreateDocumentL()
    {  
    // Create an Dialer document, and return a pointer to it
    CApaDocument* document = CDialerDocument::NewL(*this);
    return document;
    }

TUid CDialerApplication::AppDllUid() const
    {
    // Return the UID for the Dialer application
    return KUidDialerApp;
    }

