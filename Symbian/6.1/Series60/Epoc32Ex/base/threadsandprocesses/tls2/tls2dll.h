// TLS2dll.h
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
//

// DLL example program (2) to demonstrate the use of thread-local storage.

// standard example header
#include <e32test.h>


class CMessenger : public CBase
  	{
public:
		// Construction
	IMPORT_C static CMessenger* NewLC(CConsoleBase& aConsole,const TDesC& aString);
		// Destructor - virtual and class not intended
		// for derivation, so not exported
	~CMessenger();
		// general functions - exported
	IMPORT_C void ShowMessage();
	IMPORT_C TInt GetTlsData();
private:
		// C++ constructor - not exported;
		// implicitly called from NewLC() 
	CMessenger(CConsoleBase& aConsole);
		// 2nd phase construction, called by NewLC()
	void ConstructL(const TDesC& aString);
private:
	CConsoleBase& iConsole;  // Use the console (but not owned)
	HBufC*        iString;   // Allocated container for string data (destructor destroys)
	};
