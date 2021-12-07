/* Copyright (c) 2002, Nokia. All rights reserved */

#include "BTHCIApplication.h"

// Epoc DLL entry point, return that everything is ok
GLDEF_C TInt E32Dll(TDllReason)
    {
    return KErrNone;
    }


// Create an BTHCI application, and return a pointer to it
EXPORT_C CApaApplication* NewApplication()
    {
    return (new CBTHCIApplication);
    }

