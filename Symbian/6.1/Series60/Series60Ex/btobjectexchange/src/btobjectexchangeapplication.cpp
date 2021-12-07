/* Copyright (c) 2002, Nokia. All rights reserved */

#include "BTObjectExchangeDocument.h"
#include "BTObjectExchangeApplication.h"
#include "ObjectExchangeProtocolConstants.h"

CApaDocument* CBTObjectExchangeApplication::CreateDocumentL()
    {  
    // Create an BTObjectExchange document, and return a pointer to it
    CApaDocument* document = CBTObjectExchangeDocument::NewL(*this);
    return document;
    }

TUid CBTObjectExchangeApplication::AppDllUid() const
    {
    // Return the UID for the BTObjectExchange application
    return KUidBTObjectExchangeApp;
    }

