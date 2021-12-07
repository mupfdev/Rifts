/* Copyright (c) 2002, Nokia. All rights reserved */

#include "ErrorUiDocument.h"
#include "ErrorUiApplication.h"

// UID for the application, this should correspond to the uid defined in the mmp file
static const TUid KUidErrorUiApp = {0x10005b9c};

CApaDocument* CErrorUiApplication::CreateDocumentL()
    {  
    // Create an ErrorUi document, and return a pointer to it
    CApaDocument* document = CErrorUiDocument::NewL(*this);
    return document;
    }

TUid CErrorUiApplication::AppDllUid() const
    {
    // Return the UID for the ErrorUi application
    return KUidErrorUiApp;
    }

