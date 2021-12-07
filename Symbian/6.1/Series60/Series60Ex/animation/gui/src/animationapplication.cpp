/* Copyright (c) 2001, Nokia. All rights reserved */
#include "animationdocument.h"
#include "animationapplication.h"

// local constants
static const TUid KUidAnimationApp = {0x10005B88};

CApaDocument* CAnimationApplication::CreateDocumentL()
    {  
    // Create an Animation document, and return a pointer to it
    CApaDocument* document = CAnimationDocument::NewL(*this);
    return document;
    }

TUid CAnimationApplication::AppDllUid() const
    {
    // Return the UID for the Animation application
    return KUidAnimationApp;
    }

