// Copyright c 2000, Nokia. All rights reserved.

#include "SoundApp.h"
#include "SoundDoc.h"


const TUid KUidSoundApp = { 0x100008f5 };

TUid CSoundApplication::AppDllUid() const
    {
    return KUidSoundApp;
    }


CApaDocument* CSoundApplication::CreateDocumentL()
    {
    CSoundDocument* document = new (ELeave) CSoundDocument(*this);
    return document;
    }


EXPORT_C CApaApplication* NewApplication()
    {
    return (new CSoundApplication);
    }


GLDEF_C TInt E32Dll(TDllReason)
    {
    return KErrNone;
    }

