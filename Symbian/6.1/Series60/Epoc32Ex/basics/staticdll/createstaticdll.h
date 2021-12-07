// CreateStaticDLL.h
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.

// Statically linked dll example
 

#include <e32cons.h>


class CMessenger : public CBase
  	{
public:
		// Construction
	IMPORT_C static CMessenger* NewLC(CConsoleBase& aConsole, const TDesC& aString);
		// Destructor - virtual and class not intended
		// for derivation, so not exported
	~CMessenger();
		// general functions - exported
	IMPORT_C void ShowMessage();
private:
		// C++ constructor - not exported;
		// implicitly called from NewLC()
	CMessenger(CConsoleBase& aConsole);
		// 2nd phase construction, called by NewLC()
	void ConstructL(const TDesC& aString); // second-phase constructor
private:
	CConsoleBase& iConsole; // Use the console (but not owned)
	HBufC*        iString;  // Allocated container for string data (destructor destroys)
	};
