// Copyright (c) 2001, Nokia. All rights reserved.

#include <eikenv.h>
#include <eikproc.h>

#include "SoundDoc.h"
#include "SoundAppUI.h"


// Standard Epoc construction sequence
CSoundDocument* CSoundDocument::NewL(CEikApplication& aApp)
    {
    CSoundDocument* self = NewLC(aApp);
    CleanupStack::Pop();
    return self;
    }

CSoundDocument* CSoundDocument::NewLC(CEikApplication& aApp)
    {
    CSoundDocument* self = new (ELeave) CSoundDocument(aApp);
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

void CSoundDocument::ConstructL()
    {
    }
        
CSoundDocument::CSoundDocument(CEikApplication& aApp) : CEikDocument(aApp)
    {
    }

CEikAppUi* CSoundDocument::CreateAppUiL()
    {
    return (new (ELeave) CSoundAppUi);
    }

