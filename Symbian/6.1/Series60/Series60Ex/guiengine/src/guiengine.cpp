/* Copyright (c) 2001, Nokia. All rights reserved */
#include <e32std.h>
#include <eikapp.h>
#include "GuiEngineApplication.h"

// Epoc DLL entry point, return that everything is ok
GLDEF_C TInt E32Dll(TDllReason)
	{
    return KErrNone;
	}


// Create an GuiEngine application, and return a pointer to it
EXPORT_C CApaApplication* NewApplication()
	{
    return (new CGuiEngineApplication);
	}

