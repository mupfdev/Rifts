/* Copyright (c) 2002, Nokia. All rights reserved */

#include "MessageClient.h"
#include "MessageServiceSearcher.h"
#include "BTPointToPoint.pan"
#include "Log.h"

_LIT8(KMessage, "Hello world");

CMessageClient* CMessageClient::NewL(MLog& aLog)
    {
    CMessageClient* self = NewLC(aLog);
    CleanupStack::Pop(self);
    return self;
    }
    
CMessageClient* CMessageClient::NewLC(MLog& aLog)
    {
    CMessageClient* self = new (ELeave) CMessageClient(aLog);
    CleanupStack::PushL(self);
    self->ConstructL(KMessage);
    return self;
    }

CMessageClient::CMessageClient(MLog& aLog)
: CActive(CActive::EPriorityStandard),
  iState(EWaitingToGetDevice),
  iLog(aLog)
    {
    CActiveScheduler::Add(this);
    }

CMessageClient::~CMessageClient()
    {

	// Close() will wait forever for Read to complete
	if (iState == EConnected)
	{
		iSendingSocket.CancelRead();
	}
    Cancel();

    iSendingSocket.Close();
    iSocketServer.Close();

    delete iMessage;
    iMessage = NULL;

    delete iServiceSearcher;
    iServiceSearcher = NULL;
    }

void CMessageClient::ConstructL(const TDesC8& aMessage)
    {
    iServiceSearcher = CMessageServiceSearcher::NewL(iLog);

    iMessage = aMessage.AllocL();

	User::LeaveIfError(iSocketServer.Connect());

    }

void CMessageClient::DoCancel()
    {
    // no implementation required
    }

void CMessageClient::RunL()
    {
    if (iStatus != KErrNone)
        {
        switch (iState)
            {
            case EGettingDevice:
                if (iStatus == KErrCancel)
                    {
                    iLog.LogL(_L("No device selected"));
                    }
                iState = EWaitingToGetDevice;
                break;
            case EGettingService:
            case EGettingConnection:
                iLog.LogL(_L("Connection error "), iStatus.Int());
                iState = EWaitingToGetDevice;
                break;
			case EConnected:
                iLog.LogL(_L("Lost connection "), iStatus.Int());
				DisconnectFromServerL();
				iState = EDisconnecting;
				break;
            case ESendingMessage:
                iLog.LogL(_L("Message Failed "), iStatus.Int());
				DisconnectFromServerL();
				iState = EDisconnecting;
                break;
			case EDisconnecting:
				if (iStatus == KErrDisconnected)
				{
					iLog.LogL(_L("Disconnection complete "), iStatus.Int());
					iSendingSocket.Close();
					iState = EWaitingToGetDevice;
				}
				else
				{
					iLog.LogL(_L("Failed to disconnect "), iStatus.Int());
					Panic(EBTPointToPointUnableToDisconnect);
				}
				break;
            default:
                Panic(EBTPointToPointInvalidLogicState);
                break;
            }
        }
    else 
        {
        switch (iState)
            {
            case EGettingDevice:
                // found a device now search for a suitable service
                iLog.LogL(iServiceSearcher->ResponseParams().DeviceName());
                iState = EGettingService;
                iStatus = KRequestPending; // this means that the RunL can not be called until
                                           // this program does something to iStatus
                iServiceSearcher->FindServiceL(iStatus);
                SetActive();
                break;
            case EGettingService:
                iLog.LogL(_L("Found service"));
                iState = EGettingConnection;
                ConnectToServerL();
                break;
            case EGettingConnection:
                iLog.LogL(_L("Connected"));
                iState = EConnected;
				// Catch disconnection event 
				// By waiting to read socket
				WaitOnConnectionL();
                break;
			case EConnected:
                iLog.LogL(_L("Data Recieved"));
				// Just dump data
				iDummyBuffer.Zero();
				// Catch disconnection event 
				// By waiting to read socket
				WaitOnConnectionL();
				break;
            case ESendingMessage:
                iLog.LogL(_L("Sent message"));
                iState = EConnected;
				// Catch disconnection event 
				// By waiting to read socket
				WaitOnConnectionL();
                break;
            case EDisconnecting:
                iLog.LogL(_L("Disconnection complete"));
				iSendingSocket.Close();
                iState = EWaitingToGetDevice;
                break;
            default:
                Panic(EBTPointToPointInvalidLogicState);
                break;
            };
        }
    }

void CMessageClient::ConnectL()
    {
    if (iState == EWaitingToGetDevice && !IsActive())
        {
        iState = EGettingDevice;
        iServiceSearcher->SelectDeviceByDiscoveryL(iStatus);
        SetActive();
        }
    else
        {
        iLog.LogL(_L("Client busy"));
        User::Leave(KErrInUse);
        }
    }

void CMessageClient::DisconnectL()
	{
	if ((iState == EConnected)||(iState == ESendingMessage))
	{
		DisconnectFromServerL();
		iState = EDisconnecting;
	}
	else
	{
        iLog.LogL(_L("No connection!"));
        User::Leave(KErrDisconnected);
	}
	}

void CMessageClient::DisconnectFromServerL()
	{
	// Terminate all operations
	iSendingSocket.CancelAll();
	Cancel();
  
	iLog.LogL(_L("Releasing connection"));
	iSendingSocket.Shutdown(RSocket::ENormal,iStatus);
	SetActive();

	}



void CMessageClient::ConnectToServerL()
    {
    iLog.LogL(_L("Connecting to service"));

	User::LeaveIfError(iSendingSocket.Open(iSocketServer, _L("RFCOMM")));

    TBTSockAddr address;
    address.SetBTAddr(iServiceSearcher->BTDevAddr());
    address.SetPort(iServiceSearcher->Port());

    iSendingSocket.Connect(address, iStatus);

#ifdef __WINS__
    User::After(1);     // Fix to allow emulator client to connect to server
#endif

    SetActive();
    }

void CMessageClient::WaitOnConnectionL()
	{
	if (iState != EConnected)
		{
		User::Leave(KErrDisconnected);
		}
		iSendingSocket.Read(iDummyBuffer, iStatus);
		SetActive();
	}

void CMessageClient::SendMessageL()
    {
    if (iState != EConnected)
        {
        User::Leave(KErrDisconnected);
        }

	// Stop reading socket
	iSendingSocket.CancelRead();
	if (IsActive()) 
    {
        Cancel();
    }
	iState = ESendingMessage;
    iSendingSocket.Write(*iMessage, iStatus);
    SetActive();
    }

TBool CMessageClient::IsReadyToSendMessage()
    {
	return (iState == EConnected);
    }

TBool CMessageClient::IsConnected()
    {
    return ((iState == EConnected)||(iState == ESendingMessage));
    }

TBool CMessageClient::IsConnecting()
    {
    return ((iState == EGettingDevice)
		    ||
			(iState == EGettingService)
			||
			(iState == EGettingConnection));
    }

TBool CMessageClient::IsSendingMessage()
    {
    return (iState == ESendingMessage);
    }
