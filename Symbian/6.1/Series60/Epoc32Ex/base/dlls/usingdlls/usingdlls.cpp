// UsingDLLs.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.

// A program which uses dynamically linked DLLs.

// standard example header
#include "CommonFramework.h"
// f32 header needed for loading dlls.
#include <f32file.h>

#include "UsingDLLs.h"

_LIT(KTxtHarry,"Harry");
_LIT(KTxtSally,"Sally");
_LIT(KTxtDr1,"PolymorphicDLL1.DLL");
_LIT(KTxtDr2,"PolymorphicDLL2.DLL");

_LIT(KTxt1,"dynamically linked DLL example \n\n");
_LIT(KTxt2,"checking UID\n");
_LIT(KTxt3,"DLL has incorrect UID... \n");

void UseDllL(const TFileName& aDllName, const TDesC& aName);

LOCAL_C void doExampleL()
    {
	// open file server session.
	RFs fs;
	User::LeaveIfError(fs.Connect());
	console->Printf(KTxt1);
	// use each DLL in turn
	TFileName  dll;
	dll = KTxtDr1;
	UseDllL(dll, KTxtHarry);
	dll = KTxtDr2;
	UseDllL(dll, KTxtSally);
	// close the file server session.
	fs.Close();
	}

// how to use a DLL

void UseDllL(const TFileName& aLibraryName, const TDesC& aName)
	{
		// Use RLibrary object to interface to the DLL
	RLibrary library;
		// Dynamically load DLL
	User::LeaveIfError(library.Load(aLibraryName));
		// Check second UID is as expected; leave if not
	console->Printf(KTxt2);
	
	if (library.Type()[1] != KMessengerUid)
		{
		console->Printf(KTxt3);
		User::Leave(KErrGeneral);
		}
		// Function at ordinal 1 creates  new CMessenger
	TLibraryFunction entry=library.Lookup(1);
		// Call the function to create new CMessenger
	CMessenger* messenger=(CMessenger*) entry();
		// Push pointer to CMessenger onto the cleanup stack
	CleanupStack::PushL(messenger);
		// Second-phase constructor for CMessenger
	messenger->ConstructL(console, aName);
		// Use CMessenger object to issue greeting
	messenger->ShowMessage();
		// Pop CMessenger object off cleanup stack and destroy
	CleanupStack::PopAndDestroy();
		// Finished with the DLL
	library.Close();
	}
