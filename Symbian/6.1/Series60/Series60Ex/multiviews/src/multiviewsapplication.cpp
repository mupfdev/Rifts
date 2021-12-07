/* Copyright (c) 2002, Nokia. All rights reserved */

#include "MultiViewsDocument.h"
#include "MultiViewsApplication.h"

// local constants
static const TUid KUidMultiViewsApp = {0x10005B92};

CApaDocument* CMultiViewsApplication::CreateDocumentL()
    {  
    // Create an MultiViews document, and return a pointer to it
    CApaDocument* document = CMultiViewsDocument::NewL(*this);
    return document;
    }

TUid CMultiViewsApplication::AppDllUid() const
    {
    // Return the UID for the MultiViews application
    return KUidMultiViewsApp;
    }

