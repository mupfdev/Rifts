// Copyright (c) 2001, Nokia. All rights reserved.

#include "SoundApp.h"
#include "SoundDoc.h"


const TUid KUidSoundApp = { 0x10005b87 };

TUid CSoundApplication::AppDllUid() const
    {
    // Return the UID for the CSoundApplication application
    return KUidSoundApp;
    }


CApaDocument* CSoundApplication::CreateDocumentL()
    {
    // Create an CSoundDocument document, and return a pointer to it
    CSoundDocument* document = CSoundDocument::NewL(*this);
    return document;
    }


// Create an Sound application, and return a pointer to it
EXPORT_C CApaApplication* NewApplication()
    {
    return (new CSoundApplication);
    }


// Epoc DLL entry point, return that everything is ok
GLDEF_C TInt E32Dll(TDllReason)
    {
    return KErrNone;
    }

