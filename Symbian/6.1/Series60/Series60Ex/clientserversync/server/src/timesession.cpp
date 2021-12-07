/* Copyright (c) 2001, Nokia. All rights reserved */
#include <e32svr.h>
#include "TimeSession.h"
#include "clientservercommon.h"

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
            RequestTimeL();
            break ;

        default :
            PanicClient(EBadRequest);
            break;
        }
    aMessage.Complete(KErrNone);
    }

void CTimeServerSession::RequestTimeL()
    {
    const TAny* clientsDescriptor = Message().Ptr0();
    TTime time;
    time.HomeTime();

    TPtr8 ptr(reinterpret_cast<TUint8*>(&time), sizeof(time), sizeof(time));
    
    Message().WriteL(clientsDescriptor, ptr);
    }


void CTimeServerSession::PanicClient(TInt aPanic) const
	{
	Panic(KCSSyncServer,aPanic) ; // Note: this panics the client thread, not server
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
