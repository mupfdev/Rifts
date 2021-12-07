/* Copyright (c) 2001, Nokia. All rights reserved */
#include "serverdll.h"
#include "serverimage.h"

// Epoc DLL entry point, return that everything is ok
GLDEF_C TInt E32Dll(TDllReason)
    {
    return KErrNone;
    }

// The only exported function in the server DLL is the createCAnimDllL function
// this is called for us by the windows server framework to create an instance of
// the animation server dll
EXPORT_C CAnimDll* CreateCAnimDllL()
    {
    return (new (ELeave) CServerDll);
    }


// Call the base class constructor
CServerDll::CServerDll() 
    : CAnimDll()
    {
    }

// Used to create an instance of animation server object
CAnim* CServerDll::CreateInstanceL(TInt /* aType */)
    {
    // Nb the aType variable can be used to set what type of animation object should be
    // created but this example only has 1 type so it is ignored
    return (new (ELeave) CImage);
    }




