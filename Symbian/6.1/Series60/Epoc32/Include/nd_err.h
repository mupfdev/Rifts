// ND_ERR.H
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
//

// Netdial external errors and error strings

#ifndef __ND_ERR_H__
#define __ND_ERR_H__

#include <e32def.h>

const TInt KNetdialErrorBase=-3000;

// netdial script errors
//
const TInt KErrExitNoModem=KNetdialErrorBase-1;				// Exit Condition - No Modem Response
const TInt KErrExitModemError=KNetdialErrorBase-2;			// Exit Condition - Modem error
const TInt KErrExitLoginFail=KNetdialErrorBase-3;			// Exit Condition - Login Failure
const TInt KErrExitScriptTimeOut=KNetdialErrorBase-4;		// Exit Condition - Script Timed Out
const TInt KErrExitScriptError=KNetdialErrorBase-5;			// Exit Condition - Script Error

// netdial database error
//
const TInt KErrNetDialDatabaseDefaultUndefined=KNetdialErrorBase-6;
const TInt KErrNetDialDatabaseTypeUnknown=KNetdialErrorBase-7;
const TInt KErrNetDialDatabaseNotFound=KNetdialErrorBase-8;
const TInt KErrNetDialHscsdNotSupported=KNetdialErrorBase-9;

// error strings for script
//
#define KErrExitScriptTimeOutString		_S("KErrTimeOut$")
#define KErrExitLoginFailString			_S("KErrLoginFail$")
#define	KErrExitNoModemString			_S("KErrNoModem$")	
#define KErrExitModemErrorString		_S("KErrModemError$")
#define KErrExitNoAnswerString			_S("KErrNoAnswer$")
#define KErrExitNoCarrierString			_S("KErrNoCarrier$")
#define KErrExitNoDialToneString		_S("KErrNoDialTone$")
#define KErrExitBusyString				_S("KErrBusy$")
#define KErrExitModemInitErrorString	_S("KErrModemInitError$")

#endif