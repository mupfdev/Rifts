#include "SystemApp.h"

#include <libc/sys/reent.h>

const TUid KUIDRIFTS = { UID3 };

CSystemApp::~CSystemApp()
{
    CloseSTDLIB();
}

TUid CSystemApp::AppDllUid() const
{
    return KUIDRIFTS;
}

CApaDocument* CSystemApp::CreateDocumentL()
{
    return new (ELeave) CSystemDocument(*this);
}

#include <aknkeylock.h>
EXPORT_C CApaApplication* NewApplication()
{
    RAknKeyLock objKeyLock;
    objKeyLock.Connect();
    if(objKeyLock.IsKeyLockEnabled())
    {
        objKeyLock.Close();
        User::Exit(0);
        return NULL;
    }
    objKeyLock.Close();
    return new CSystemApp;
}

GLDEF_C TInt E32Dll( TDllReason )
{
    return KErrNone;
}
