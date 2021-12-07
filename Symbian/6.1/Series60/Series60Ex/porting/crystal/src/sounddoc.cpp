// Copyright c 2000, Nokia. All rights reserved.

#include <eikenv.h>
#include <eikproc.h>

#include "SoundDoc.h"
#include "SoundAppUI.h"


CSoundDocument::CSoundDocument(CEikApplication& aApp) : CEikDocument(aApp)
    {
    //empty constructor body
    }

CEikAppUi* CSoundDocument::CreateAppUiL()
    {
    return (new (ELeave) CSoundAppUi);
    }

