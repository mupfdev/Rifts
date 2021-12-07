// TLS2dll.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.

// DLL example program (2) to demonstrate the use of thread-local storage (TLS).

// This DLL implements the CMessenger class declared in "TLS2dll". 
// Thread local storage is initialized to point to a TlsData object in the DLL
// entry point function E32DLL().
//
// The implementation of the E32DLL() function for the ARM platform is different 
// to that for the WINS platform.
//
// The CMessenger class provides an exported function GetTlsData() which returns
// the content of the location pointed to by thread-local storage; this can be
// called, as needed, by programs which have loaded the DLL and constructed a
// CMessenger object.

	// DLL header
#include "TLS2dll.h"
#include <e32uid.h>


class TlsData
	{
public:
	TInt Data() {return(iData);}
	void SetData(TInt aValue) {iData=aValue;}
public:
	TInt iData;
	};

inline TlsData& Tls()
	{return(*((TlsData*)Dll::Tls()));}



	// Construction
EXPORT_C CMessenger* CMessenger::NewLC(CConsoleBase& aConsole, const TDesC& aString)
	{
	CMessenger* self=new (ELeave) CMessenger(aConsole);
	CleanupStack::PushL(self);
	self->ConstructL(aString);
	return self;
	}

	// Destructor - virtual and class is not intended for derivation, so not exported
CMessenger::~CMessenger()
	{
	delete iString;
	}

EXPORT_C void CMessenger::ShowMessage()
	{
	_LIT(KFormat1,"%S\n");
	iConsole.Printf(KFormat1, iString);
	}

EXPORT_C TInt CMessenger::GetTlsData()
	{
	return((TlsData*)Dll::Tls())->Data();
	}


	// C++ constructor - not exported as it will be called when a new CMessenger 
	// object is constructed by the NewLC() member function implemented in this DLL.
CMessenger::CMessenger(CConsoleBase& aConsole)
	: iConsole(aConsole)
	{
	}

	// 2nd phase construction - not exported as it is called by the NewLC() 
	// function which is implemented in this DLL.
void CMessenger::ConstructL(const TDesC& aString)
	{
	iString=aString.AllocL(); // allocate HBufC and copy given string into it
	}


// DLL entry point function.
// The behaviour on the WINS platform is different to that on the ARM platform.
//
// If the DLL is attaching to a new thread, then a new TlsData object is 
// constructed and initialized with a value of 5;  thread local storage is
// set to point to this TlsData object.
//
// Thread local storage is reset when the DLL detaches from the thread.

#if defined(__MARM__)
GLDEF_C TInt E32Dll(TDllReason aReason)
	{
	TInt res=KErrNone;
	TlsData* pD;
	switch (aReason)
		{
	case EDllThreadAttach:
		pD=new TlsData; 
		Dll::SetTls(pD);
		pD->SetData(5);
		break;
	case EDllThreadDetach:
		delete &Tls();
		Dll::SetTls(NULL);
		break;
	default:
		break;
		}
	return(res);
	}
#endif

// If the DLL is attaching to a new process, then a new TlsData object is 
// constructed and initialized with a value of 5;  thread local storage is
// set to point to this TlsData object.
//
// Under WINS thread local storage cannot be reset when the process detaches from
// the DLL.
//
// Notes:
// 1. In this example, E32Dll is called with EDllThreadAttach after it is called
//    with EDllProcessAttach. Thread local storage for the primary thread should
//    only be set when handling EDllProcessAttach
// 2. E32Dll is never called with EDllThreadAttach 
#if defined(__WINS__)
GLDEF_C TInt E32Dll(TDllReason aReason)
	{
	TInt res=KErrNone;
	TlsData* pD;
	switch (aReason)
		{
	case EDllProcessAttach:
		pD=new TlsData;
		Dll::SetTls(pD);
		pD->SetData(5);
		break;
	case EDllThreadAttach:
		break;
	case EDllThreadDetach:
		break;
	case EDllProcessDetach:
		break;
		}
	return(res);
	}
#endif
