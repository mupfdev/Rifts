/* Copyright (c) 2002, Nokia. All rights reserved */

#include "ObjectExchangeClient.h"
#include "ObjectExchangeServiceSearcher.h"
#include "BTObjectExchange.pan"
#include "Log.h"

CObjectExchangeClient* CObjectExchangeClient::NewL(MLog& aLog)
    {
    CObjectExchangeClient* self = NewLC(aLog);
    CleanupStack::Pop(self);
    return self;
    }
    
CObjectExchangeClient* CObjectExchangeClient::NewLC(MLog& aLog)
    {
    CObjectExchangeClient* self = new (ELeave) CObjectExchangeClient(aLog);
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

CObjectExchangeClient::CObjectExchangeClient(MLog& aLog)
: CActive(CActive::EPriorityStandard),
  iState(EWaitingToGetDevice),
  iLog(aLog)
    {
    CActiveScheduler::Add(this);
    }

void CObjectExchangeClient::ConstructL()
    {
    iServiceSearcher = CObjectExchangeServiceSearcher::NewL(iLog);

    iCurrObject = CObexNullObject::NewL();
    iCurrObject->SetNameL(_L("Hello World"));
    }

CObjectExchangeClient::~CObjectExchangeClient()
    {

    if (iState != EWaitingToGetDevice && iClient)
    {
        iClient->Abort();
		iStatus = KErrNone;
    }

    Cancel();
    
    delete iCurrObject;
    iCurrObject = NULL;

    delete iServiceSearcher;
    iServiceSearcher = NULL;

    delete iClient;
    iClient = NULL;
    }

void CObjectExchangeClient::DoCancel()
    {
    }


void CObjectExchangeClient::RunL()
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
            case EDisconnecting:
                iLog.LogL(_L("Connection error "), iStatus.Int());
                iState = EWaitingToGetDevice;
                break;
            case EWaitingToSend:
                iLog.LogL(_L("Send error "), iStatus.Int());
                iState = EWaitingToGetDevice;
                break;
            default:
                Panic(EBTObjectExchangeUnexpectedLogicState);
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
                iState = EWaitingToSend;
                break;

            case EWaitingToSend:
                iLog.LogL(_L("Sent object"));
                break;

            case EDisconnecting:
                iLog.LogL(_L("Disconnected"));
                iState = EWaitingToGetDevice;
                break;

            default:
                Panic(EBTObjectExchangeSdpRecordDelete);
                break;
            };
        }
    }


void CObjectExchangeClient::ConnectL()
    {
    if (iState == EWaitingToGetDevice && !IsActive())
        {
        iServiceSearcher->SelectDeviceByDiscoveryL(iStatus);
        iState = EGettingDevice;
        SetActive();
        }
    else
        {
        iLog.LogL(_L("Client busy"));
        User::Leave(KErrInUse);
        }
    }

void CObjectExchangeClient::ConnectToServerL()
    {
    TObexBluetoothProtocolInfo protocolInfo;

    protocolInfo.iTransport.Copy(KServerTransportName);
    protocolInfo.iAddr.SetBTAddr(iServiceSearcher->BTDevAddr());
    protocolInfo.iAddr.SetPort(iServiceSearcher->Port());

    if (iClient)
        {
        delete iClient;
        iClient = NULL;
        }
    iClient = CObexClient::NewL(protocolInfo);
    
    iClient->Connect(iStatus);
    SetActive();
    }

void CObjectExchangeClient::SendObjectL()
    {
    if (iState != EWaitingToSend)
        {
        User::Leave(KErrDisconnected);
        }
    else if (IsActive()) 
        {
        User::Leave(KErrInUse);
        }

    iClient->Put(*iCurrObject, iStatus);
    SetActive();
    }

void CObjectExchangeClient::StopL()
    {
    if (iClient && iClient->IsConnected())
        {
        iClient->Abort();
        iState = EWaitingToGetDevice;
        }
    }

void CObjectExchangeClient::DisconnectL()
    {
    if (iState == EWaitingToGetDevice)
        {
        return;
        }
    if (iState == EWaitingToSend)
        {
        iLog.LogL(_L("Disconnecting"));
        iState = EDisconnecting;
        iClient->Disconnect(iStatus);
        SetActive();
        }
    else 
        {
        User::Leave(KErrInUse);
        }
    }

TBool CObjectExchangeClient::IsBusy()
    {
    return IsActive();
    }

TBool CObjectExchangeClient::IsConnected()
    {
    return iState == EWaitingToSend;
    }

