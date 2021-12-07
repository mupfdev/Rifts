/* Copyright (c) 2001, Nokia. All rights reserved */

#include "SnapShotDocument.h"
#include "SnapShotApplication.h"

// local constants
static const TUid KUidSnapShotApp = {0x10005B89};

CApaDocument* CSnapShotApplication::CreateDocumentL()
    {  
    // Create an SnapShot document, and return a pointer to it
    CApaDocument* document = CSnapShotDocument::NewL(*this);
    return document;
    }

TUid CSnapShotApplication::AppDllUid() const
    {
    // Return the UID for the SnapShot application
    return KUidSnapShotApp;
    }

