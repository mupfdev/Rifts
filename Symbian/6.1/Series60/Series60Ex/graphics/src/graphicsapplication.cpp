/* Copyright (c) 2001, Nokia. All rights reserved */

#include "GraphicsDocument.h"
#include "GraphicsApplication.h"

// local constants
static const TUid KUidGraphicsApp = {0x10005B81};

CApaDocument* CGraphicsApplication::CreateDocumentL()
    {  
    // Create an Graphics document, and return a pointer to it
    CApaDocument* document = CGraphicsDocument::NewL(*this);
    return document;
    }

TUid CGraphicsApplication::AppDllUid() const
    {
    // Return the UID for the Graphics application
    return KUidGraphicsApp;
    }

