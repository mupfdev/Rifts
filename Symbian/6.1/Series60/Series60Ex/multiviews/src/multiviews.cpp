/* Copyright (c) 2002, Nokia. All rights reserved */

#include "MultiViewsApplication.h"

// DLL entry point, return that everything is ok
GLDEF_C TInt E32Dll(TDllReason /*aReason*/)
    {
    return KErrNone;
    }


// Create an application, and return a pointer to it
EXPORT_C CApaApplication* NewApplication()
    {
    return (new CMultiViewsApplication);
    }

