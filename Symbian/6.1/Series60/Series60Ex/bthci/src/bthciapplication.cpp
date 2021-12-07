/* Copyright (c) 2002, Nokia. All rights reserved */

#include "BTHCIDocument.h"
#include "BTHCIApplication.h"

// local constants
static const TUid KUidBTHCIApp = {0x10005B97};

CApaDocument* CBTHCIApplication::CreateDocumentL()
    {  
    // Create a BTHCI document, and return a pointer to it
    CApaDocument* document = CBTHCIDocument::NewL(*this);
    return document;
    }

TUid CBTHCIApplication::AppDllUid() const
    {
    // Return the UID for the BTHCI application
    return KUidBTHCIApp;
    }

