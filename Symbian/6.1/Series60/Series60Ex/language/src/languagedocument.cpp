/* Copyright (c) 2002, Nokia. All rights reserved */

#include "LanguageAppUi.h"
#include "LanguageDocument.h"

// Standard Symbian OS construction sequence
CLanguageDocument* CLanguageDocument::NewL(CEikApplication& aApp)
    {
    CLanguageDocument* self = NewLC(aApp);
    CleanupStack::Pop(self);
    return self;
    }

CLanguageDocument* CLanguageDocument::NewLC(CEikApplication& aApp)
    {
    CLanguageDocument* self = new (ELeave) CLanguageDocument(aApp);
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

void CLanguageDocument::ConstructL()
    {
    // No implementation required
    }    

CLanguageDocument::CLanguageDocument(CEikApplication& aApp) : CAknDocument(aApp) 
    {
    // No implementation required
    }   

CLanguageDocument::~CLanguageDocument()
    {
    // No implementation required
    }

CEikAppUi* CLanguageDocument::CreateAppUiL()
    {
    // Create the application user interface, and return a pointer to it
    CEikAppUi* appUi = new (ELeave) CLanguageAppUi;
    return appUi;
    }

