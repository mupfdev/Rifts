// TLS2exe.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.

// A program (2) to demonstrate the use of thread-local storage (TLS)

	// standard example header
#include "CommonFramework.h"

	// DLL header
#include "TLS2dll.h"

_LIT(KTxtIntro,"Thread local storage example \n\n");
_LIT(KTxtHello,"Hello!");
_LIT(KTxtNewLine,"\n");

_LIT(KFormat,"Thread Local Storage: %d \n");

// This function uses a statically loaded DLL to create a new CMessenger object.
// It then accesses the data pointed to by thread-local storage via the 
// CMessenger object and then shows the data.
LOCAL_C void doExampleL()
    {
	console->Printf(KTxtIntro); // start a new "test"
	CMessenger* myMessage = CMessenger::NewLC(*console, KTxtHello);
	myMessage->ShowMessage();
	console->Printf(KFormat,(myMessage->GetTlsData()));
	console->Printf(KTxtNewLine);
	CleanupStack::PopAndDestroy(); 
	}


