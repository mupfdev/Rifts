/* Copyright (c) 2002, Nokia. All rights reserved */

#include "CipherDocument.h"
#include "CipherApplication.h"

// UID for the application, this should correspond to the uid defined in the mmp file
static const TUid KUidCipherApp = {0x10005C34};

CApaDocument* CCipherApplication::CreateDocumentL()
    {  
    // Create an Cipher document, and return a pointer to it
    CApaDocument* document = CCipherDocument::NewL(*this);
    return document;
    }

TUid CCipherApplication::AppDllUid() const
    {
    // Return the UID for the Cipher application
    return KUidCipherApp;
    }

