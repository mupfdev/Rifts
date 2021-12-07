// CommonStreamStore.h
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.


#ifndef __CommonStreamStore_H
#define __CommonStreamStore_H

#include <e32cons.h>
#include <f32file.h>

// public
LOCAL_D CConsoleBase* console; // write all your messages to this
LOCAL_C void doExampleL(); // code this function for the real example
LOCAL_D RFs fsSession;

// private
LOCAL_C void callExampleL(); // initialize with cleanup stack, then do example

_LIT(KTxtStore,"STORE");

GLDEF_C TInt E32Main() // main function called by E32
    {
	__UHEAP_MARK;
	CTrapCleanup* cleanup=CTrapCleanup::New(); // get clean-up stack
	TRAPD(error,callExampleL()); // more initialization, then do example
	__ASSERT_ALWAYS(!error,User::Panic(KTxtStore,error));
	delete cleanup; // destroy clean-up stack
	__UHEAP_MARKEND;
	return 0; // and return
    }

_LIT(KTxtExampleCode,"STORES Example Code");
_LIT(KTxtConnectFailed,"file session connect failed: return code=%d");
_LIT(KTxtFailed,"failed: leave code=%d");
_LIT(KTxtOK,"ok");
_LIT(KTxtPressAnyKey," [press any key]");

LOCAL_C void callExampleL() // initialize and call example code under cleanup stack
    {
	console=Console::NewL(KTxtExampleCode,TSize(KConsFullScreen,KConsFullScreen));
	CleanupStack::PushL(console);
	TInt fsret = fsSession.Connect(); // start a file session
	if (fsret != KErrNone)
		{
		console->Printf(KTxtConnectFailed,fsret);
		User::Leave(fsret);
		}
	TRAPD(error,doExampleL()); // perform example function
	if (error) console->Printf(KTxtFailed, error);
	else console->Printf(KTxtOK);
	console->Printf(KTxtPressAnyKey);
	console->Getch(); // get and ignore character
	fsSession.Close(); //close the file session
	CleanupStack::PopAndDestroy(); // close console
    }

#endif
