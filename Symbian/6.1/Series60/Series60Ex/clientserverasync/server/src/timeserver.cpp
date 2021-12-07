/* Copyright (c) 2001, Nokia. All rights reserved */
#include <e32svr.h>
#include <e32math.h>
#include "timeserver.h"
#include "clientservercommon.h"
#include "timesession.h"


CTimeServer::CTimeServer(TInt aPriority)
: CServer(aPriority)
    {
    // Implementation not required
    }

CTimeServer::~CTimeServer()
    {
    delete iHeartbeat;
    iHeartbeat = NULL;
    }

CTimeServer* CTimeServer::NewL()
    {
    CTimeServer* timeServer = CTimeServer::NewLC();
    CleanupStack::Pop(timeServer) ;
    return timeServer;
    }

CTimeServer* CTimeServer::NewLC()
    {
	CTimeServer* timeServer = new (ELeave) CTimeServer(EPriorityNormal);
    CleanupStack::PushL(timeServer) ;
    timeServer->ConstructL() ;
    return timeServer;
    }

void CTimeServer::ConstructL()
    {
    StartL(KTimeServerName) ;
    }

CSharableSession* CTimeServer::NewSessionL(const TVersion& aVersion) const
    {
	// check we're the right version
	if (!User::QueryVersionSupported(TVersion(KTimeServMajorVersionNumber,
                                              KTimeServMinorVersionNumber,
                                              KTimeServBuildVersionNumber),
                                     aVersion))
        {
		User::Leave(KErrNotSupported);
        }

	// make new session
	RThread client = Message().Client();
	return CTimeServerSession::NewL(client, *const_cast<CTimeServer*> (this));
    }

void CTimeServer::IncrementSessions()
    {
    iSessionCount++;
    }

void CTimeServer::DecrementSessions()
    {
    iSessionCount--;
    if (iSessionCount <= 0)
        {
        CActiveScheduler::Stop();
        }    
    }


TInt CTimeServer::RunError(TInt aError)
    {
	if (aError == KErrBadDescriptor)
        {
        // A bad descriptor error implies a badly programmed client, so panic it;
        // otherwise report the error to the client
        PanicClient(Message(), EBadDescriptor);
        }
	else
        {
		Message().Complete(aError);
        }

	//
	// The leave will result in an early return from CServer::RunL(), skipping
	// the call to request another message. So do that now in order to keep the
	// server running.
	ReStart();

	return KErrNone;	// handled the error fully
    }


void CTimeServer::PanicClient(const RMessage& aMessage, TTimeServPanic aPanic)
    {
    aMessage.Panic(KCSAsyncServer, aPanic);
    }

void CTimeServer::PanicServer(TTimeServPanic aPanic)
    {
    User::Panic(KCSAsyncServer, aPanic);
    }

void CTimeServer::WaitForTickL()
    {
    if (!iHeartbeat)
        {
        iHeartbeat = CHeartbeat::NewL(EPriorityHigh);
        iHeartbeat->Start(ETwelveOClock, this);
        }
    }

void CTimeServer::Beat()
    {
    SendTimeToSessions();
    }

void CTimeServer::Synchronize()
    {
    SendTimeToSessions();
    }

void CTimeServer::SendTimeToSessions()
    {
    iSessionIter.SetToFirst();
    for (;;)
        {
        CTimeServerSession* session;
        session = reinterpret_cast<CTimeServerSession*>(iSessionIter++);
        if (!session)
            {
            break;
            }

        session->SendTimeToClient();
        }
    }

void CTimeServer::ThreadFunctionL()
    {
    // Construct active scheduler
    CActiveScheduler* activeScheduler = new (ELeave) CActiveScheduler;
    CleanupStack::PushL(activeScheduler) ;

    // Install active scheduler
    // We don't need to check whether an active scheduler is already installed
    // as this is a new thread, so there won't be one
    CActiveScheduler::Install(activeScheduler);

    // Construct our server
    CTimeServer::NewLC();    // anonymous

	RSemaphore semaphore;
	User::LeaveIfError(semaphore.OpenGlobal(KTimeServerSemaphoreName));

	// Semaphore opened ok
	semaphore.Signal();
	semaphore.Close();

	// Start handling requests
	CActiveScheduler::Start();

    CleanupStack::PopAndDestroy(2, activeScheduler);    //  anonymous CTimeServer
    }

TInt CTimeServer::ThreadFunction(TAny* /*aNone*/)
    {
    CTrapCleanup* cleanupStack = CTrapCleanup::New();
	if (cleanupStack == NULL)
	    {
        PanicServer(ECreateTrapCleanup);
	    }

    TRAPD(err, ThreadFunctionL());
    if (err != KErrNone)
        {
        PanicServer(ESrvCreateServer);
        }

    delete cleanupStack;
    cleanupStack = NULL;

    return KErrNone;
    }


#ifdef __WINS__

IMPORT_C TInt WinsMain();
EXPORT_C TInt WinsMain()
    {
	return reinterpret_cast<TInt>(&CTimeServer::ThreadFunction);
    }


GLDEF_C TInt E32Dll(TDllReason)
    {
	return KErrNone;
    }

#else  // __ARMI__


TInt E32Main()
    {
	return CTimeServer::ThreadFunction(NULL);
    }

#endif
