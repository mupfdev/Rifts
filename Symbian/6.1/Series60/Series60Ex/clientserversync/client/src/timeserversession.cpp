/* Copyright (c) 2001, Nokia. All rights reserved */

#include <E32Math.h>
#include "ClientServerCommon.h"
#include "TimeServerSession.h"


// Number of message slots to reserve for this client server session.
// Since we only communicate synchronously here, we never have any
// outstanding asynchronous requests.
static const TUint KDefaultMessageSlots = 0;

static const TUid KServerUid3 = {0x10005B7A};

_LIT(KTimeServerFilename, "CSSyncServer");
#ifdef __WINS__
static const TUint KServerMinHeapSize =  0x1000;  //  4K
static const TUint KServerMaxHeapSize = 0x10000;  // 64K
#endif

static TInt StartServer();
static TInt CreateServerProcess();


RTimeServerSession::RTimeServerSession()
:   RSessionBase()
    {
	// No implementation required
    }


TInt RTimeServerSession::Connect()
    {
    TInt error = StartServer();

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


void RTimeServerSession::RequestTime(TTime& aTime) const
    {
    TAny* messageParameters[KMaxMessageArguments];

    // Create descriptor to enable copying data between
    // client and server. Note: This can be local since
    // this is a synchronous call.
    // Note : Using TPtr8 since this is binary information
    TPtr8 descriptor(reinterpret_cast<TUint8*>(&aTime),sizeof(aTime),sizeof(aTime));

    // Set the first message parameter to point to the descriptor
    messageParameters[0] = static_cast<TAny*>(&descriptor);

    // This call waits for the server to complete the request before 
    // proceeding. When it returns, the new time will be in aTime.
    SendReceive(ETimeServRequestTime, &messageParameters[0]);
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