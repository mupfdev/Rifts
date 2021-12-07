/* Copyright (c) 2001, Nokia. All rights reserved */

#ifndef __CLIENTSERVERCOMMON_H__
#define __CLIENTSERVERCOMMON_H__

#include <e32base.h>

//server name
_LIT(KTimeServerName,"SyncTimeServer");
_LIT(KTimeServerSemaphoreName, "TimeServerSemaphore");

//the server version. A version must be specified when 
//creating a session with the server
const TUint KTimeServMajorVersionNumber=0;
const TUint KTimeServMinorVersionNumber=1;
const TUint KTimeServBuildVersionNumber=1;

//opcodes used in message passing between client and server
enum TTimeServRqst
	{
	ETimeServRequestTime
    };

#endif // __CLIENTSERVERCOMMON_H__