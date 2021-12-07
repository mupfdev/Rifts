// BASTD.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __BASTD_H
#define __BASTD_H

#include <e32cons.h>
#include <f32file.h>
#include <barsc.h>
#include <barsread.h>


// public
LOCAL_D CConsoleBase* console; // write all your messages to this
LOCAL_D RFs fsSession;
LOCAL_C void doExampleL(); // code this function for the real example

// private
LOCAL_C void callExampleL(); // initialize with cleanup stack, then do example

GLDEF_C TInt E32Main() // main function called by E32
    {
	_LIT(KBaflEx,"BAFLEX");
	__UHEAP_MARK;
	if (fsSession.Connect()!=KErrNone)
		return KErrGeneral;
	CTrapCleanup* cleanup=CTrapCleanup::New(); // get clean-up stack
	TRAPD(error,callExampleL()); // more initialization, then do example
	fsSession.Close();
	__ASSERT_ALWAYS(!error,User::Panic(KBaflEx,error));
	delete cleanup; // destroy clean-up stack
	__UHEAP_MARKEND;
	return 0; // and return
    }

LOCAL_C void callExampleL() // initialize and call example code under cleanup stack
    {
	_LIT(KExampleCode,"Symbian OS Example Code");
	_LIT(KFailedLeave,"failed: leave code=%d");
	_LIT(KOk,"ok");
	_LIT(KPressAnyKey," [press any key]");

	console=Console::NewL(KExampleCode,TSize(KConsFullScreen,KConsFullScreen));
	CleanupStack::PushL(console);
	TRAPD(error,doExampleL()); // perform example function
	if (error)
		console->Printf(KFailedLeave, error);
	else 
		console->Printf(KOk);
	console->Printf(KPressAnyKey);
	console->Getch(); // get and ignore character
	CleanupStack::PopAndDestroy(); // close console
    }

#endif
