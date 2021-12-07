// CommonFiles.h
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.


#ifndef __CommonFiles_H
#define __CommonFiles_H

#include <e32cons.h>

// public
LOCAL_D CConsoleBase* console; // write all your messages to this
LOCAL_C void doExampleL(); // code this function for the real example

// private
LOCAL_C void callExampleL(); // initialize with cleanup stack, then do example

GLDEF_C TInt E32Main() // main function called by E32
    {
	_LIT(KEpoch32ex,"EPOC32EX");
	CTrapCleanup* cleanup=CTrapCleanup::New(); // get clean-up stack
	TRAPD(error,callExampleL()); // more initialization, then do example
	__ASSERT_ALWAYS(!error,User::Panic(KEpoch32ex,error));
	delete cleanup; // destroy clean-up stack
	return 0; // and return
    }

LOCAL_C void callExampleL() // initialize and call example code under cleanup stack
    {
	_LIT(KStatus1,"Symbian OS Example Code");
	_LIT(KStatus2,"failed: leave code=%d");
	_LIT(KStatus3,"ok");
	_LIT(KStatus4," [press any key]");

	console=Console::NewL(KStatus1,TSize(KConsFullScreen,KConsFullScreen));
	//console=Console::NewL(KStatus1, TSize(KDefaultConsWidth,KDefaultConsHeight));
	CleanupStack::PushL(console);
	TRAPD(error,doExampleL()); // perform example function
	if (error) console->Printf(KStatus2, error);
	else console->Printf(KStatus3);
	console->Printf(KStatus4);
	console->Getch(); // get and ignore character
	CleanupStack::Pop(); // close console
    }

#endif
