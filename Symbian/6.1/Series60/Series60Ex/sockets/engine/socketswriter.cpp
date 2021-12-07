/* Copyright (c) 2001, Nokia. All rights reserved */

#include "SocketsWriter.h"
#include "TimeOutTimer.h"
#include "Sockets.pan"
#include "EngineNotifier.h"

const TInt CSocketsWriter::KTimeOut = 30000000; // 30 seconds time-out

CSocketsWriter* CSocketsWriter::NewL(MEngineNotifier& aEngineNotifier, RSocket& aSocket)
    {
	CSocketsWriter* self = CSocketsWriter::NewLC(aEngineNotifier, aSocket);
	CleanupStack::Pop(self);
	return self;
    }

	
CSocketsWriter* CSocketsWriter::NewLC(MEngineNotifier& aEngineNotifier, RSocket& aSocket)
    {
	CSocketsWriter* self = new (ELeave) CSocketsWriter(aEngineNotifier, aSocket);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
    }


CSocketsWriter::CSocketsWriter(MEngineNotifier& aEngineNotifier, RSocket& aSocket)
: CActive(EPriorityStandard),
  iSocket(aSocket),
  iEngineNotifier(aEngineNotifier)
    {
    }


CSocketsWriter::~CSocketsWriter()
    {
    Cancel();
    delete iTimer;
    iTimer = NULL;
    }

void CSocketsWriter::DoCancel()
    {	
    // Cancel asychronous write request
	iSocket.CancelWrite();
    iTimer->Cancel();
	iWriteStatus = EWaiting;
    }

void CSocketsWriter::ConstructL()
    {
	CActiveScheduler::Add(this);

	iTimeOut = KTimeOut; 
	iTimer = CTimeOutTimer::NewL(CActive::EPriorityUserInput, *this);
	iWriteStatus = EWaiting;
    }

void CSocketsWriter::TimerExpired()
    {
	Cancel();
	iWriteStatus = EWaiting;
    iEngineNotifier.ReportError(MEngineNotifier::ETimeOutOnWrite, KErrTimedOut);
    }

void CSocketsWriter::RunL()
    {
    iTimer->Cancel();

    // Active object request complete handler
	if (iStatus == KErrNone)
	    {
		switch(iWriteStatus)
		    {
		    // Character has been written to socket
		    case ESending:
                SendNextPacket();
			    break;
		    default:
                User::Panic(KPanicSocketsEngineWrite, ESocketsBadStatus);
                break;
		    };
	    }
    else 
	    {
		// Error: pass it up to user interface
        iEngineNotifier.ReportError(MEngineNotifier::EGeneralWriteError, iStatus.Int());
        iWriteStatus = EWaiting;
	    }
    }

void CSocketsWriter::IssueWriteL(const TDesC8& aData)
    {
    if ((iWriteStatus != EWaiting) && (iWriteStatus != ESending))
        {
        User::Leave(KErrNotReady);
        }

    if ((aData.Length() + iTransferBuffer.Length()) > iTransferBuffer.MaxLength())
        {
        // Not enough space in buffer
        User::Leave(KErrOverflow);
        }

	// Add new data to buffer
	iTransferBuffer.Append(aData);

    if (!IsActive())
        {
        SendNextPacket();
        }
    }

void CSocketsWriter::SendNextPacket()
    {
    if (iTransferBuffer.Length() > 0)
        {
        // Move data from transfer buffer to actual write buffer
        iWriteBuffer = iTransferBuffer;
        iTransferBuffer.Zero();
	    iSocket.Write(iWriteBuffer, iStatus); // Initiate actual write
	
        // Request timeout
	    iTimer->After(iTimeOut);
	    SetActive();
	    iWriteStatus = ESending;
        }
    else
        {
	    iWriteStatus = EWaiting;
        }
    }
