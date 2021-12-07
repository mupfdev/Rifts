//TLS1exe.cpp

// Copyright (c) 2000 Symbian Ltd.  All rights reserved.

// An example to demonstrate Thread Local Storage (TLS)
//
// (See also the DLL implementation in TLS1dll.cpp)

	// standard example header
#include "CommonFramework.h"
	// dll header file
#include "TLS1dll.h"

//
// Common literal text
//

_LIT(KTxtNewLines,"\n\n");


	// This function uses a statically loaded DLL to create a new CSetter object.
	// It then uses this object to set up some static data accessed through 
    // thread-local storage.
	// Thex example then shows how the static data can be accessed through
	// the member functions of another class (CGeneral).
	// All implementation code for these two classes is provided in the DLL
LOCAL_C void doExampleL()
    {
		// Introduction
	_LIT(KTxtIntro,"Thread local storage example (1) \n\n");
	console->Printf(KTxtIntro);
	
		// Construct CSetter object, set up some static data via the
		// thread local storage and use CSetter to show it.
	CSetter* theSetter = new (ELeave) CSetter(*console);
	CleanupStack::PushL(theSetter);
	
	_LIT(KTxt1,"SOME STATIC TEXT");
	theSetter->SetStaticTextL(KTxt1);
	_LIT(KTxt2,"Static data set by CSetter object\n");
	console->Printf(KTxt2);
	_LIT(KTxt3,"Static data displayed by CSetter object...\n");
	console->Printf(KTxt3);
	theSetter->ShowStaticText();

		// Construct a CGeneral object and see that it can show 
	    // this static data. CGeneral knows nothing about the CSetter object
	CGeneral* theGeneral = new  (ELeave) CGeneral(*console);
	CleanupStack::Pop();
	_LIT(KTxt4,"Static data now accessed by CGeneral object...\n");
	console->Printf(KTxt4);
	theGeneral->ShowStaticText();
	console->Printf(KTxtNewLines);

		// Delete the CSetter object and then use the CGeneral object to
	    // try and show static data - there should be none.
	delete theSetter;
	_LIT(KTxt5,"Static data accessed again by CGeneral object...\n");
	console->Printf(KTxt5);
	theGeneral->ShowStaticText();
	console->Printf(KTxtNewLines);

		// tidy up before finishing the example
	delete theGeneral;
	}


