// TLS1dll.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.

// DLL example program (1) to demonstrate Thread Local Storage (TLS).

// This DLL implements the two classes CSetter and CGeneral
// 
// CSetter is used to set up the static text string, delete it, change it and display
// its content.
//
// CGeneral can show the content.
//
// The point being made here is that the text string is, effectively, static writeable data.
// It is accessible by all classes implemented in the DLL.
//
// CSetter is the only class which sets the static data in this example but, in general,
// any class implemented in the DLL can change/delete/fetch the data
// through the pointer in thread local storage - it is a matter of application design.
// 
// 

#include "TLS1dll.h"

#include <e32uid.h>

_LIT(KTxt1,"<>\n");
_LIT(KFormat1,"<%S>\n");

///////////////////////////////////////////////////////////////////////
//
// Class CSetter implementation
//
///////////////////////////////////////////////////////////////////////	

	// C++ constructor sets reference to the console in the
	// initializer list.
    // Body of constructor is empty.
    // Constructor is exported because it is non-trivial
EXPORT_C CSetter::CSetter(CConsoleBase& aConsole)
	: iConsole(aConsole)
	{
	}


	// Destructor, deletes the static string
CSetter::~CSetter()
	{
	delete (HBufC*)Dll::Tls();
	Dll::SetTls(NULL);
	}


	// Delete any existing static string; allocates a new HBufC
	// and sets thread local storage to point to the HBufC.
EXPORT_C void CSetter::SetStaticTextL(const TDesC& aString)
	{
	delete (HBufC*)Dll::Tls();
	HBufC* pD = aString.AllocL();
	Dll::SetTls(pD);
	}


	// Show static text
EXPORT_C void  CSetter::ShowStaticText() const
	{
	TDesC* text = ((TDesC*)Dll::Tls());
	
	if (text)
		iConsole.Printf(KFormat1, text);
	else
		iConsole.Printf(KTxt1);
	}



///////////////////////////////////////////////////////////////////////
//
// Class CGeneral implementation
//
///////////////////////////////////////////////////////////////////////	

	// C++ constructor sets refrence to the console in the
	// initializer list.
    // Body of constructor is empty.
    // Constructor is exported because it is non-trivial
EXPORT_C CGeneral::CGeneral(CConsoleBase& aConsole)
	: iConsole(aConsole)
	{
	}


	// Show static text
EXPORT_C void  CGeneral::ShowStaticText() const
	{
	TDesC* text = ((TDesC*)Dll::Tls());
	
	if (text)
		iConsole.Printf(KFormat1, text);
	else
		iConsole.Printf(KTxt1);
	}


///////////////////////////////////////////////////////////////////////
//
// DLL entry point
//
// The reason code is of no interest here and it is ignored
///////////////////////////////////////////////////////////////////////
GLDEF_C TInt E32Dll(TDllReason /*aReason*/)
	{
	return KErrNone;
	}
