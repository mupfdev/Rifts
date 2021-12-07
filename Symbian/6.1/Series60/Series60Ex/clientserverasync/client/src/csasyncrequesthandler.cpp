/* Copyright (c) 2001, Nokia. All rights reserved */
#include <e32svr.h>

#include "CSAsyncRequestHandler.h"
#include "ClientServerCommon.h"

CCSAsyncRequestHandler* CCSAsyncRequestHandler::NewL(MAsyncTimeObserver& aObserver)
    {
    CCSAsyncRequestHandler* self = NewLC(aObserver);
    CleanupStack::Pop();
    return(self) ;
    }

CCSAsyncRequestHandler* CCSAsyncRequestHandler::NewLC(MAsyncTimeObserver& aObserver)
    {
    CCSAsyncRequestHandler* self = new (ELeave) CCSAsyncRequestHandler(aObserver);
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

void CCSAsyncRequestHandler::ConstructL()
    {
    User::LeaveIfError(iSession.Connect());
    }

CCSAsyncRequestHandler::CCSAsyncRequestHandler(MAsyncTimeObserver& aObserver)
:   CActive(EPriorityStandard),
    iObserver(aObserver)
    {
    CActiveScheduler::Add(this);
    }

CCSAsyncRequestHandler::~CCSAsyncRequestHandler()
    {
    Cancel(); // Causes call to DoCancel()
    iSession.Close();
    }

void CCSAsyncRequestHandler::RequestTime()
    {
    if (!IsActive())
        {
        iSession.RequestTime(iTime, iStatus);
        SetActive();
        }
    }

void CCSAsyncRequestHandler::CancelRequest()
    {
    Cancel() ; // Causes call to DoCancel()
    }

void CCSAsyncRequestHandler::RunL()
    {
    switch (iStatus.Int())
        {
        case ETimeServRequestTimeComplete:
            // The server has completed the request, signalled the client
            // thread and the clients active scheduler runs the active object
            // now do something with it
            iObserver.HandleTimeUpdate();
            RequestTime();   // Add this line to make the clock keep ticking
            break ;

        case KErrCancel:
            // The request was canceled
            break ;

        case KErrNotReady:
            // We requested a new time before completing the previous request                   
        default:
            ASSERT(0) ; // Unexpected error
            break ;
        }
    }

void CCSAsyncRequestHandler::DoCancel()
    {
    iSession.CancelRequestTime();
    }

TTime CCSAsyncRequestHandler::Time() const
    {
    return iTime;
    }
 