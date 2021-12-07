/* Copyright (c) 2002, Nokia. All rights reserved */

#include "BTDiscoveryDocument.h"
#include "BTDiscoveryApplication.h"

// local constants
static const TUid KUidBTDiscoveryApp = {0x10005B8D};

CApaDocument* CBTDiscoveryApplication::CreateDocumentL()
    {  
    // Create an BTDiscovery document, and return a pointer to it
    CApaDocument* document = CBTDiscoveryDocument::NewL(*this);
    return document;
    }

TUid CBTDiscoveryApplication::AppDllUid() const
    {
    // Return the UID for the BTDiscovery application
    return KUidBTDiscoveryApp;
    }

