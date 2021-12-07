/* Copyright (c) 2002, Nokia. All rights reserved */

#include "BTAdvertiserDocument.h"
#include "BTAdvertiserApplication.h"

// local constants
static const TUid KUidBTAdvertiserApp = {0x10005B8C};

CApaDocument* CBTAdvertiserApplication::CreateDocumentL()
    {  
    // Create an BTAdvertiser document, and return a pointer to it
    CApaDocument* document = CBTAdvertiserDocument::NewL(*this);
    return document;
    }

TUid CBTAdvertiserApplication::AppDllUid() const
    {
    // Return the UID for the BTAdvertiser application
    return KUidBTAdvertiserApp;
    }

