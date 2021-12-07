// UseStaticDLL.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.

// A simple program which uses the statically linked dll  "eulibd1b.dll"

// standard example header
#include "CommonFramework.h"
#include "CreateStaticDLL.h"

_LIT(KTxt1,"statically linked DLL example \n\n");
_LIT(KTxt2,"Hello!");
_LIT(KTxtNewLine,"\n");

LOCAL_C void doExampleL()
    {
	console->Printf(KTxt1);
	CMessenger* myMessage = CMessenger::NewLC(*console, KTxt2);
	myMessage->ShowMessage();
	console->Printf(KTxtNewLine);
	CleanupStack::PopAndDestroy(); 
	}


