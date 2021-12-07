/* Copyright (c) 2002, Nokia. All rights reserved */

#include "BTPointToPointDocument.h"
#include "BTPointToPointApplication.h"
#include "MessageProtocolConstants.h"


CApaDocument* CBTPointToPointApplication::CreateDocumentL()
    {  
    // Create an BTPointToPoint document, and return a pointer to it
    CApaDocument* document = CBTPointToPointDocument::NewL(*this);
    return document;
    }

TUid CBTPointToPointApplication::AppDllUid() const
    {
    // Return the UID for the BTPointToPoint application
    return KUidBTPointToPointApp;
    }

