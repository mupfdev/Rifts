// DBSTD.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __DBSTD_H
#define __DBSTD_H

#include <e32cons.h>
#include <s32file.h>
#include <d32dbms.h>

// public
LOCAL_D CConsoleBase* console; // write all your messages to this
LOCAL_C void doExampleL(); // code this function for the real example
LOCAL_D RFs fsSession;

// private
LOCAL_C void callExampleL(); // initialize with cleanup stack, then do example

GLDEF_C TInt E32Main() // main function called by E32
    {
	_LIT(KDbmsExample,"DBMS-Example");
	CTrapCleanup* cleanup=CTrapCleanup::New(); // get clean-up stack
	TRAPD(error,callExampleL()); // more initialization, then do example
	__ASSERT_ALWAYS(!error,User::Panic(KDbmsExample,error));
	delete cleanup; // destroy clean-up stack
	return 0; // and return
    }

LOCAL_C void callExampleL() // initialize and call example code under cleanup stack
    {
	_LIT(KDbmsSdkExampleCode,"Symbian OS Example Code");
	_LIT(KFileSessionConnectFailed,"file session connect failed: return code=%d");
	_LIT(KFailed,"failed: leave code=%d");
	_LIT(KOk,"ok");
	_LIT(KPressAnyKey," [press any key]");

	console=Console::NewL(KDbmsSdkExampleCode,
		TSize(KConsFullScreen,KConsFullScreen));
	CleanupStack::PushL(console);
	TInt fsret = fsSession.Connect(); // start a file session
	if (fsret != KErrNone)
		{
		console->Printf(KFileSessionConnectFailed,fsret);
		User::Leave(fsret);
		}
	TRAPD(error,doExampleL()); // perform example function
	if (error) console->Printf(KFailed, error);
	else console->Printf(KOk);
	console->Printf(KPressAnyKey);
	console->Getch(); // get and ignore character
	fsSession.Close(); // close the file session
	CleanupStack::Pop(); // close console
    }

#endif
