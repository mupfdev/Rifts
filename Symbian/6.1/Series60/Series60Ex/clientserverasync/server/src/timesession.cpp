/* Copyright (c) 2001, Nokia. All rights reserved */
#include "timesession.h"
#include "clientservercommon.h"
#include <e32svr.h>

CTimeServerSession::CTimeServerSession(RThread& aClient, CTimeServer& aServer)
:   CSession(aClient), iServer(aServer)
    {
    // Implementation not required
    }

CTimeServerSession::~CTimeServerSession()
    {
    iServer.DecrementSessions();
    }

void CTimeServerSession::ServiceL(const RMessage& aMessage)
    {
    switch (aMessage.Function())
        {
        case ETimeServRequestTime :
            RequestTimeL(aMessage);
            break ;

        case ETimeServCancelRequestTime :
            if (iWaitingForTick)
                {
                iMessage.Complete(KErrCancel);
                iWaitingForTick = EFalse;
                }
            aMessage.Complete(KErrNone);
            break ;

        default :
            PanicClient(EBadRequest);
        }
    }

void CTimeServerSession::RequestTimeL(const RMessage& aMessage)
    {
    if (iWaitingForTick)
        {
        // We're already busy
        PanicClient(EReqAlreadyPending);
        }
    else
        {
        // Keep a copy of message - for use later
        iMessage = aMessage ;

        // Start the work performed by the server (just a wait for new second in this case)
        iServer.WaitForTickL();
        iWaitingForTick = ETrue;
        }
    }


void CTimeServerSession::SendTimeToClient()
    {
    if (iWaitingForTick)
        {
        iWaitingForTick = EFalse;
    
        // Get current time to return to client
        TTime time;
        time.HomeTime();

        // Create a descriptor which points to the 'time' structure
        TPtr8 ptr(reinterpret_cast<TUint8*>(&time), sizeof(time), sizeof(time));
    
        // Write the 'time' data back to the client
        TRAPD(res, iMessage.WriteL(iMessage.Ptr0(), ptr));
        if (res != KErrNone)
            {
            PanicClient(EBadDescriptor);
            }

        iMessage.Complete(ETimeServRequestTimeComplete);
        }
    }

void CTimeServerSession::PanicClient(TInt aPanic) const
	{
	Panic(KCSAsyncServer, aPanic) ; // Note: this panics the client thread, not server
	}

CTimeServerSession* CTimeServerSession::NewL(RThread& aClient, CTimeServer& aServer)
    {
    CTimeServerSession* self = CTimeServerSession::NewLC(aClient, aServer) ;
    CleanupStack::Pop(self) ;
    return self ;
    }

CTimeServerSession* CTimeServerSession::NewLC(RThread& aClient, CTimeServer& aServer)
    {
    CTimeServerSession* self = new (ELeave) CTimeServerSession(aClient, aServer);
    CleanupStack::PushL(self) ;
    self->ConstructL() ;
    return self ;
    }

void CTimeServerSession::ConstructL()
    {
    iServer.IncrementSessions();
    }
