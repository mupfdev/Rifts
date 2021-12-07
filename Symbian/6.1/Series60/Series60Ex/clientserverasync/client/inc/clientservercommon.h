/* Copyright (c) 2001, Nokia. All rights reserved */

#ifndef __CLIENTSERVERCOMMON_H__
#define __CLIENTSERVERCOMMON_H__

#include <e32base.h>

//server name

_LIT(KTimeServerName,"AsyncTimeServer");
_LIT(KTimeServerSemaphoreName, "AsyncTimeServerSemaphore");

//the server version. A version must be specified when 
//creating a session with the server
const TUint KTimeServMajorVersionNumber=0;
const TUint KTimeServMinorVersionNumber=1;
const TUint KTimeServBuildVersionNumber=1;


//opcodes used in message passing between client and server
enum TTimeServRqst
	{
	ETimeServRequestTime,
    ETimeServCancelRequestTime
    };

//opcodes used by server to indicate which asynchronous service
//has completed
enum TTimeServRqstComplete
	{
	ETimeServRequestTimeComplete = 1
    };
#endif // __CLIENTSERVERCOMMON_H__