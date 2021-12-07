/* Copyright (c) 2002, Nokia. All rights reserved */

#include "LanguageApplication.h"

// Symbian OS DLL entry point, return that everything is ok
GLDEF_C TInt E32Dll(TDllReason)
    {
    return KErrNone;
    }


// Create a Language application, and return a pointer to it
EXPORT_C CApaApplication* NewApplication()
    {
    return (new CLanguageApplication);
    }

