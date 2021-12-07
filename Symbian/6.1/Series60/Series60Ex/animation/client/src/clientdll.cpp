/* Copyright (c) 2001, Nokia. All rights reserved */
#include "clientdll.h"

// Epoc DLL entry point, return that everything is ok
GLDEF_C TInt E32Dll(TDllReason)
    {
    return KErrNone;
    }

// Animation client dll construction code all encapsulated in original class
EXPORT_C RClientDll::RClientDll(RWsSession& aSession) 
    : RAnimDll(aSession)
    {
    }
