// EIKECHO.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// Header file for EIKON interface to ECHOENG

#include <basched.h>
#include <eikenv.h>
#include <coecntrl.h>
#include <eikappui.h>
#include <e32keys.h>
#include <eikconso.h>
#include <eikapp.h>
#include <eikdoc.h>
#include <eikon.rsg>
#include <eikinfo.h>
//#include <eikcmds.hrh>
#include <eikon.hrh>//newly added
#include <eikecho.rsg>

#include "echoeng.h"

#ifndef _EIKECHO_H_
#define _EIKECHO_H_

// App UID
#ifdef _UNICODE
const TUid KUidEikEchoApp = {0x10004851};
#else
const TUid KUidEikEchoApp = {0x10004850};
#endif

// Connection values: substitute alternative values for KInetAddr
// and KInetHostName if you want to use different servers
const TUint32 KInetAddr = INET_ADDR(193,63,255,1); 
_LIT(KInetHostName,"phoenix.doc.ic.ac.uk");

// Integer formatting descriptor
_LIT(KIntFormat,"%d");

// 
// CConsoleControl: console-type control
//

class CConsoleControl : public CCoeControl, public MUINotify
	{
public:
	static CConsoleControl* NewL(CEchoEngine* aEchoEngine);
	~CConsoleControl();
	void ConstructL(CEchoEngine* aEchoEngine);

	// Override CCoeControl 
    TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
    void ActivateL();

	//Implement MUINotify up calls
	void PrintNotify(const TDesC& aDes);
	void PrintNotify(TInt aInt);
	void ErrorNotify(const TDesC& aErrMessage, TInt aErrCode);
protected:
	CConsoleControl() {}
private:
	CEikConsoleScreen* iConsole;	// Standard EIKON console control
	CEchoEngine* iEchoEngine;		// The echo engine
	};

//
// CEchoAppUi: user interface command handling
//

class CEchoAppUi : public CEikAppUi
    {
public:
	CEchoAppUi(CEchoEngine* aEchoEngine);
    void ConstructL();
	void CreateConsoleL();
	~CEchoAppUi();
private: 
	// Override CEikAppUi
    void HandleCommandL(TInt aCommand);
private:
	CConsoleControl* iConsoleControl;
	CEchoEngine* iEchoEngine;
	};

//
// CEchoDocument: document class, which owns the engine
//

class CEchoDocument : public CEikDocument
	{
public:
	CEchoDocument(CEikApplication& aApp);
	static CEchoDocument* NewL(CEikApplication& aApp);
	~CEchoDocument();
	void ConstructL();
private: 
	// Override CApaDocument
	CEikAppUi* CreateAppUiL();
private: 
	CEchoEngine* iEchoEngine; // Document owns the echo engine
	};

//
// CEchoApplication
//

class CEchoApplication : public CEikApplication
	{
private: // from CApaApplication
	CApaDocument* CreateDocumentL();
	TUid AppDllUid() const;
	};
#endif



