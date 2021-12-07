/* Copyright (c) 2001, Nokia. All rights reserved */

#include "SocketsDocument.h"
#include "SocketsApplication.h"

// local constants
static const TUid KUidSocketsApp = {0x10005B78};

CApaDocument* CSocketsApplication::CreateDocumentL()
    {  
    // Create an Sockets document, and return a pointer to it
    CApaDocument* document = CSocketsDocument::NewL(*this);
    return document;
    }

TUid CSocketsApplication::AppDllUid() const
    {
    // Return the UID for the Sockets application
    return KUidSocketsApp;
    }

