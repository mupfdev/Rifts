/* Copyright (c) 2001, Nokia. All rights reserved */

#include "DialerApplication.h"

// Epoc DLL entry point, return that everything is ok
GLDEF_C TInt E32Dll(TDllReason)
    {
    return KErrNone;
    }


// Create an Dialer application, and return a pointer to it
EXPORT_C CApaApplication* NewApplication()
    {
    return (new CDialerApplication);
    }

