/* Copyright (c) 2001, Nokia. All rights reserved */

#include "ClientServerCommon.h"
#include "TimeServerSession.h"
#include <e32math.h>

// Number of message slots to reserve for this client server session.
// In this example we can have one asynchronous request outstanding 
// and one synchronous request in progress.
static const TUint KDefaultMessageSlots = 2;

static const TUid KServerUid3 = {0x10005B7C};

_LIT(KTimeServerFilename, "CSAsyncServer");
#ifdef __WINS__
static const TUint KServerMinHeapSize =  0x1000;  //  4K
static const TUint KServerMaxHeapSize = 0x10000;  // 64K
#endif

static TInt StartServer();
static TInt CreateServerProcess();

RTimeServerSession::RTimeServerSession()
:   RSessionBase(), iTimeBuffer(NULL, 0, 0)
    {
    // No implementation required
    }


TInt RTimeServerSession::Connect()
    {
    TInt error = ::StartServer();

    if (KErrNone == error)
        {
        error = CreateSession(KTimeServerName,
                              Version(),
                              KDefaultMessageSlots);
        }
    return error;
    }


TVersion RTimeServerSession::Version() const
    {
	return(TVersion(KTimeServMajorVersionNumber,
                    KTimeServMinorVersionNumber,
                    KTimeServBuildVersionNumber));
    }


void RTimeServerSession::RequestTime(TTime& aTime, TRequestStatus& aStatus) 
    {
    TAny* messageParameters[KMaxMessageArguments];

    iTimeBuffer.Set(reinterpret_cast<TUint8*>(&aTime), sizeof(aTime), sizeof(aTime));
    messageParameters[0] = static_cast<TAny*>(&iTimeBuffer);

    // This call completes immediately, however the server will not
    // complete the request until later, so don't pass any local
    // descriptors as they will be out of scope by the time the server
    // attempts to write to them
    SendReceive(ETimeServRequestTime, &messageParameters[0], aStatus);
    }


void RTimeServerSession::CancelRequestTime() const
    {
    SendReceive(ETimeServCancelRequestTime, NULL);
    }

static TInt StartServer()
    {
    TInt result;

    TFindServer findTimeServer(KTimeServerName);
    TFullName name;

	result = findTimeServer.Next(name);
	if (result == KErrNone)
        {
		// Server already running
		return KErrNone;
	    }

	RSemaphore semaphore;		
	result = semaphore.CreateGlobal(KTimeServerSemaphoreName, 0);
    if (result != KErrNone)
        {
        return  result;
        }

    result = CreateServerProcess();
    if (result != KErrNone)
        {
        return  result;
        }

	semaphore.Wait();
	semaphore.Close();       

    return  KErrNone;
    }

static TInt CreateServerProcess()
    {
    TInt result;

	const TUidType serverUid(KNullUid, KNullUid, KServerUid3);

#ifdef __WINS__

	RLibrary lib;
	result = lib.Load(KTimeServerFilename, serverUid);
    if (result != KErrNone)
        {
        return  result;
        }

    //  Get the WinsMain function
	TLibraryFunction functionWinsMain = lib.Lookup(1);

    //  Call it and cast the result to a thread function
	TThreadFunction serverThreadFunction = reinterpret_cast<TThreadFunction>(functionWinsMain());

	TName threadName(KTimeServerName);

	// Append a random number to make it unique
	threadName.AppendNum(Math::Random(), EHex);

	RThread server;

	result = server.Create(threadName,   // create new server thread
							 serverThreadFunction, // thread's main function
							 KDefaultStackSize,
							 NULL,
							 &lib,
							 NULL,
							 KServerMinHeapSize,
							 KServerMaxHeapSize,
							 EOwnerProcess);

	lib.Close();	// if successful, server thread has handle to library now

    if (result != KErrNone)
        {
        return  result;
        }

	server.SetPriority(EPriorityMore);


#else

	RProcess server;

	result = server.Create(KTimeServerFilename, _L(""), serverUid);
    if (result != KErrNone)
        {
        return  result;
        }

#endif

	server.Resume();
    server.Close();

    return  KErrNone;
    }
