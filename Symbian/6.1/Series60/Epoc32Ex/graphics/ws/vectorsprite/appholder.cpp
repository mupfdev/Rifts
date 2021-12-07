// AppHolder.cpp
//


#include "AppHolder.h"
#include "VectorSprite.h"

//
// EXPORTed functions
//

EXPORT_C CApaApplication* NewApplication()
	{
	return new CAppholderApplication;
	}

GLDEF_C TInt E32Dll(TDllReason)
	{
	return KErrNone;
	}


////////////////////////////////////////////////////////////////
//
// Application class, CAppholderApplication
//
////////////////////////////////////////////////////////////////

TUid CAppholderApplication::AppDllUid() const
	{
	return KUidAppholder;
	}

CApaDocument* CAppholderApplication::CreateDocumentL()
	{
	// Construct the document using its NewL() function, rather 
	// than using new(ELeave), because it requires two-phase
	// construction.
	return new (ELeave) CAppholderDocument(*this);
	}


////////////////////////////////////////////////////////////////
//
// Document class, CAppholderDocument
//
////////////////////////////////////////////////////////////////

// C++ constructor
CAppholderDocument::CAppholderDocument(CEikApplication& aApp)
		: CEikDocument(aApp)
	{
	}

CEikAppUi* CAppholderDocument::CreateAppUiL()
	{
    return new(ELeave) CAppholderAppUi;
	}

CAppholderDocument::~CAppholderDocument()
	{
	}

////////////////////////////////////////////////////////////////
//
// App UI class, CAppholderAppUi
//
////////////////////////////////////////////////////////////////

void CAppholderAppUi::ConstructL()
    {
    BaseConstructL();
	iClient=CExampleWsClient::NewL(ClientRect());
    }

CAppholderAppUi::~CAppholderAppUi()
	{
	delete iClient;
	}

void CAppholderAppUi::HandleCommandL(TInt aCommand)
	{
	switch (aCommand)
		{
	case EEikCmdExit: 
		Exit();
		break;
		}
	}
