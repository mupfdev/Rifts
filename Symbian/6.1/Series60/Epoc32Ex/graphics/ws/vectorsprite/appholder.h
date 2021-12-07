// AppHolder.h
//


#ifndef __APPHOLDER_H
#define __APPHOLDER_H

#include <coeccntx.h>

#include <eikenv.h>
#include <eikappui.h>
#include <eikapp.h>
#include <eikdoc.h>
#include <eikmenup.h>

#include <eikon.hrh>

const TUid KUidAppholder = { 0x100098e7 };

class CWsClient;

//
// CAppholderAppUi
//

class CAppholderAppUi : public CEikAppUi
	{
public:
	void ConstructL();
	~CAppholderAppUi();
private: // from CEikAppUi
	void HandleCommandL(TInt aCommand);
private:
	CWsClient* iClient;
	};


//
// CAppholderDocument
//

class CAppholderDocument : public CEikDocument
	{
public:
	// construct/destruct
	CAppholderDocument(CEikApplication& aApp);
	~CAppholderDocument();
private: // from CEikDocument
	CEikAppUi* CreateAppUiL();
	};


//
// CAppholderApplication
//

class CAppholderApplication : public CEikApplication
	{
private: // from CApaApplication
	CApaDocument* CreateDocumentL();
	TUid AppDllUid() const;
	};

#endif
