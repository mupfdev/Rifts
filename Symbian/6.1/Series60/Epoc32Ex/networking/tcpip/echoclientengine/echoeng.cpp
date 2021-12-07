// Echoeng.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.


// Defines CEchoEngine, CEchoRead, CEchoWrite, CTimeOutTimer

#include "echoeng.h"

const TInt KTimeOut = 30000000; // 30 seconds time-out
					 
//
// CEchoEngine: main engine class for connection and shutdown
//

EXPORT_C CEchoEngine::CEchoEngine() : CActive(EPriorityStandard)
	{
	}

EXPORT_C CEchoEngine* CEchoEngine::NewL(MUINotify* aConsole)
	{
	CEchoEngine* self = NewLC(aConsole);
	CleanupStack::Pop();
	return self;
	}

EXPORT_C CEchoEngine* CEchoEngine::NewLC(MUINotify* aConsole)
	{
	CEchoEngine* self = new(ELeave) CEchoEngine;
	CleanupStack::PushL(self);
	self->ConstructL(aConsole);
	return self;
	}

EXPORT_C void CEchoEngine::ConstructL(MUINotify* aConsole)
// Construct object, and open a socket 
	{
	iConsole = aConsole;
	iEngineStatus = EComplete;

	iTimeOut = KTimeOut; 
	iTimer = CTimeOutTimer::NewL(EPriorityHigh, *this);
	CActiveScheduler::Add(this); 

	// Open channel to Socket Server
	User::LeaveIfError(iSocketServ.Connect());
	// Open a TCP socket
	User::LeaveIfError(iEchoSocket.Open(iSocketServ, KAfInet, KSockStream, KProtocolInetTcp));
	
	iEchoRead = CEchoRead::NewL(&iEchoSocket, aConsole);
	iEchoWrite = CEchoWrite::NewL(&iEchoSocket, aConsole);
	}

void CEchoEngine::DoCancel()
// Cancel asychronous requests
	{
	iTimer->Cancel();

	// Cancel appropriate request to socket
	switch (iEngineStatus)
		{
	case EConnecting:
		iEchoSocket.CancelConnect();
		break;
	case ELookingUp:
		// Cancel look up attempt
		iResolver.Cancel();
		iResolver.Close();
		break;
	default:;
		}
	}

EXPORT_C void CEchoEngine::ConnectL(TUint32 aAddr)
// Connect to an Echo Socket by IP address	
	{
	iAddress.SetPort(7);
	iAddress.SetAddress(aAddr);
	iEchoSocket.Connect(iAddress, iStatus);
	iEngineStatus = EConnecting;
	SetActive();
	iTimer->After(iTimeOut);
	}

EXPORT_C void CEchoEngine::ConnectL(const TDesC& aServerName)
// Connect to an Echo socket by hostname
	{
	// Initiate DNS
	User::LeaveIfError(iResolver.Open(iSocketServ, KAfInet, KProtocolInetUdp));
	// DNS request for name resolution
	iResolver.GetByName(aServerName, iNameEntry, iStatus);
	
	iEngineStatus=ELookingUp;
	// Request time out
	iTimer->After(iTimeOut);
	SetActive();
	}

EXPORT_C void CEchoEngine::TestGetByAddr(TUint32 aAddr)
// Looks up hostname, and then connects to an Echo socket 
	{
	// Initiate DNS
	User::LeaveIfError(iResolver.Open(iSocketServ, KAfInet, KProtocolInetUdp));
	// DNS request for address lookup
	iAddress.SetAddress(aAddr);
	iResolver.GetByAddress(iAddress, iNameEntry, iStatus);

	iEngineStatus=ELookingUp;
	// Request time out
	iTimer->After(iTimeOut);
	SetActive();
	}

EXPORT_C void CEchoEngine::Write(TChar aChar)
// Exported function wrapping call to CEchoWrite: writes character to socket
	{
	//In this simple implementation, if iEchoWrite is already active, ignore call.
	//Full implementation would buffer data 
	if ((iEngineStatus == EConnected) && !iEchoWrite->IsActive())
		iEchoWrite->IssueWrite(aChar);
	}
	
EXPORT_C void CEchoEngine::Read()
// Exported function wrapping call to CEchoRead: reads character from socket
	{
	if ((iEngineStatus == EConnected)&&(!iEchoRead->IsActive())) 
		iEchoRead->IssueRead();
	}

void CEchoEngine::RunL()
// Active object request complete handler.
// iEngineStatus flags what request was made, so its
// completion can be handled appropriately
	{
	iTimer->Cancel(); // Cancel TimeOut timer before completion
	_LIT(KConnecting,"\n<CEchoEngine> Connecting\n");
	_LIT(KConnectionFailed,"\n<CEchoEngine> Connection failed");
	_LIT(KDNSFailed,"\n<CEchoEngine> DNS lookup failed");
	_LIT(KTimedOut,"\n<CEchoEngine> Timed out\n");
	_LIT(KDomainName,"\nDomain name = ");
	_LIT(KIPAddress,"\nIP address = ");

	TBuf<15> ipAddr;

	switch(iEngineStatus)
		{
	case EConnecting:
		// IP connection request
		if (iStatus == KErrNone)
		// Connection completed sucessfully
			{
			iConsole->PrintNotify(KConnecting);
			iEngineStatus = EConnected;
			Read(); //Start CEchoRead Active object
			}
		else
			{
			iEngineStatus = EConnectFailed;
			iConsole->ErrorNotify(KConnectionFailed, iStatus.Int());
			}
		break;
	case ETimedOut:
		// Timeout request
		iConsole->ErrorNotify(KTimedOut, KErrTimedOut);
		break;
	case ELookingUp:
		iResolver.Close();
		if (iStatus == KErrNone)
		// DNS look up successful
			{
			iNameRecord = iNameEntry();
			// Extract domain name and IP address from name record
			iConsole->PrintNotify(KDomainName);
			iConsole->PrintNotify(iNameRecord.iName);
			TInetAddr::Cast(iNameRecord.iAddr).Output(ipAddr);
			iConsole->PrintNotify(KIPAddress);
			iConsole->PrintNotify(ipAddr);
			// And connect to the IP address
			ConnectL(TInetAddr::Cast(iNameRecord.iAddr).Address());
			}
		else
			{	
			iStatus = ELookUpFailed;
			iConsole->ErrorNotify(KDNSFailed, iStatus.Int());
			}
		break;

	default:;
		};
	}

CEchoEngine::~CEchoEngine()
	{
	delete iEchoRead;
	delete iEchoWrite;
	delete iTimer;
	iEchoSocket.Close();
	iSocketServ.Close();
	}

void CEchoEngine::TimerExpired()
// Implements MTimeOutNotify: called when timeout expired
	{
	Cancel();
	iEngineStatus = ETimedOut;
	TRequestStatus* p=&iStatus;		
	// Signal CEchoEngine::RunL() imediately
	SetActive();
	User::RequestComplete(p, ETimedOut);
	}

EXPORT_C void CEchoEngine::Stop()
// Shutdown connection request
	{
	_LIT(KETerminate,"\n<CEchoEngine> Terminating\n");

	iConsole->PrintNotify(KETerminate);

	switch (iEngineStatus)
		{
	case EConnected:
		// Stop live connection
		iEchoRead->Cancel();
		iEchoWrite->Cancel();
		break;
	case EConnecting:
	case ELookingUp:
		// if request to CEchoEngine, then stop it
		Cancel();
		break;
	default:;
		}
	}

//
// CEchoRead: active object wrapping comms read requests
//

// Construction functions
CEchoRead::CEchoRead() : CActive(EPriorityStandard)
	{
	}

CEchoRead* CEchoRead::NewL(RSocket* aSocket, MUINotify* aConsole)
	{
	CEchoRead* self = NewLC(aSocket, aConsole);
	CleanupStack::Pop();
	return self;
	}

CEchoRead* CEchoRead::NewLC(RSocket* aSocket, MUINotify* aConsole)
	{
	CEchoRead* self = new(ELeave) CEchoRead;
	CleanupStack::PushL(self);
	self->ConstructL(aSocket, aConsole);
	return self;
	}

void CEchoRead::ConstructL(RSocket* aSocket, MUINotify* aConsole)
	{
	iEchoSocket = aSocket;
	iConsole = aConsole;
	CActiveScheduler::Add(this);
	}

void CEchoRead::DoCancel()
// Cancel asychronous read request
	{
	iEchoSocket->CancelRead();
	}

void CEchoRead::RunL()
// Active object request complete handler
	{
	if (iStatus == KErrNone)
		// Character has been read from socket
		{
		_LIT(KDot,".");
		iConsole->PrintNotify(KDot);
		TBuf16<1> Buffer;
		Buffer.Copy(iBuffer);
		iConsole->PrintNotify(Buffer);
		IssueRead();
		}
	else
		{
		// Error: pass it up to user interface
		_LIT(KCEchoReadError,"\nCEchoRead error");
		iConsole->ErrorNotify(KCEchoReadError, iStatus.Int());
		}	
	}

void CEchoRead::IssueRead()
// Read data from a stream socket
	{
	if (!IsActive())
		{
		iEchoSocket->Recv(iBuffer, 0, iStatus);
		SetActive();
		}
	}

void CEchoRead::IssueRecvFrom(TInetAddr &aAddr)
// This function is not actually used -
// it shows how to read data from a datagram socket 
	{
	iEchoSocket->RecvFrom(iBuffer,aAddr,NULL,iStatus);
	SetActive();
	};

//
// CEchoWrite: active object wrapping comms write requests
//

// Construction functions
CEchoWrite::CEchoWrite() : CActive(EPriorityStandard)
	{
	};

CEchoWrite* CEchoWrite::NewL(RSocket* aSocket, MUINotify* aConsole)
	{
	CEchoWrite* self = NewLC(aSocket, aConsole);
	CleanupStack::Pop();
	return self;
	};

CEchoWrite* CEchoWrite::NewLC(RSocket* aSocket, MUINotify* aConsole)
	{
	CEchoWrite* self = new(ELeave) CEchoWrite;
	CleanupStack::PushL(self);
	self->ConstructL(aSocket, aConsole);
	return self;
	};

void CEchoWrite::ConstructL(RSocket* aSocket, MUINotify* aConsole)
	{
	iEchoSocket = aSocket;
	iConsole = aConsole;
	CActiveScheduler::Add(this);

	iTimeOut = KTimeOut; 
	iTimer = CTimeOutTimer::NewL(10, *this);
	iWriteStatus = EWaiting;
	};

CEchoWrite::~CEchoWrite()
	{
	delete iTimer;
	}

void CEchoWrite::DoCancel()
// Cancel asychronous write request
	{	
	iEchoSocket->CancelWrite();
	};

void CEchoWrite::TimerExpired()
// Implements MTimeOutNotify: called when timeout expired
	{
	Cancel();
	iWriteStatus = ETimedOut;
	TRequestStatus* p=&iStatus;		// Signal RunL()
	SetActive();
	User::RequestComplete(p, ETimedOut);
	}

void CEchoWrite::RunL()
// Active object request complete handler
	{
	if (iStatus == KErrNone)
		{
		_LIT(KWriteOperationTimedOut,"\nWrite operation timed out");
		switch(iWriteStatus)
			{
		// Character has been written to socket
		case ESending:
			iTimer->Cancel(); // Cancel TimeOut timer
			iWriteStatus = EWaiting;
			break;
		// Request timed out
		case ETimedOut:
			iConsole->ErrorNotify(KWriteOperationTimedOut, KErrTimedOut);
			break;
		default:;
			};
		}
	else 
		{
		// Error: pass it up to user interface
		_LIT(KCEchoWriteError,"\nCEchoWrite error");
		iConsole->ErrorNotify(KCEchoWriteError, iStatus.Int());
		}
	}

void CEchoWrite::IssueWrite(const TChar &aChar)
// Write a data to a stream socket
	{
	// Set up buffer
	iBuffer.SetLength(0);
	iBuffer.Append(aChar);
	iEchoSocket->Write(iBuffer, iStatus);
	// Request timeout
	iTimer->After(iTimeOut);
	SetActive();
	iWriteStatus = ESending;
	};

void CEchoWrite::IssueSendTo(TInetAddr &aAddr, const TChar &aChar)
// This function is not actually used -
// it shows how to write data to a datagram socket 
	{
	// Set up buffer
	iBuffer.SetLength(0);
	iBuffer.Append(aChar);
	iEchoSocket->SendTo(iBuffer,aAddr,NULL,iStatus);
	iTimer->After(iTimeOut);
	SetActive();
	iWriteStatus = ESending;
	};

//
// CTimeOutTimer: timer for comms time-outs
//

CTimeOutTimer::CTimeOutTimer(const TInt aPriority)
    : CTimer(aPriority)
    {
    }

CTimeOutTimer::~CTimeOutTimer()
    {
	Cancel();
    }

CTimeOutTimer* CTimeOutTimer::NewL(const TInt aPriority, MTimeOutNotify& aTimeOutNotify)
    {
    CTimeOutTimer *p = new (ELeave) CTimeOutTimer(aPriority);
    CleanupStack::PushL(p);
	p->ConstructL(aTimeOutNotify);
	CleanupStack::Pop();
    return p;
    }

void CTimeOutTimer::ConstructL(MTimeOutNotify &aTimeOutNotify)
    {
	iNotify=&aTimeOutNotify;
	CTimer::ConstructL();
	CActiveScheduler::Add(this);
    }

void CTimeOutTimer::RunL()
// Timer request has completed, so notify the timer's owner
    {
	iNotify->TimerExpired();
	}

// DLL entry point
GLDEF_C TInt E32Dll(TDllReason /*aReason*/)
	{
	return(KErrNone);
	}
