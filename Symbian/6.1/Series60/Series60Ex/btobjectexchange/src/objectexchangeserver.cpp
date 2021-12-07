/* Copyright (c) 2002, Nokia. All rights reserved */

#include <es_sock.h>
#include "ObjectExchangeServer.h"
#include "ObjectExchangeServiceAdvertiser.h"
#include "ObjectExchangeProtocolConstants.h"
#include "Log.h"
#include "BTObjectExchange.pan"

static const TInt KBufferSize = 1024;

CObjectExchangeServer* CObjectExchangeServer::NewL(MLog& aLog)
    {
    CObjectExchangeServer* self = CObjectExchangeServer::NewLC(aLog);
    CleanupStack::Pop(self);
    return self;
    }
    
CObjectExchangeServer* CObjectExchangeServer::NewLC(MLog& aLog)
    {
    CObjectExchangeServer* self = new (ELeave) CObjectExchangeServer(aLog);
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

CObjectExchangeServer::CObjectExchangeServer(MLog& aLog)
:  iLog(aLog)
    {
    }

void CObjectExchangeServer::ConstructL()
    {
    // create OBEX object to receive obex transfer
    iObexBufData = CBufFlat::NewL(KBufferSize);
    iObexBufObject = CObexBufObject::NewL(iObexBufData);

    iAdvertiser = CObjectExchangeServiceAdvertiser::NewL();
    }

CObjectExchangeServer::~CObjectExchangeServer()
    {
    if (iObexServer && iObexServer->IsStarted())
        {
        iObexServer->Stop();
        }

    delete iObexServer;
    iObexServer = NULL;

    delete iObexBufData;
    iObexBufData = NULL;

    delete iObexBufObject;
    iObexBufObject = NULL;

    delete iAdvertiser;
    iAdvertiser = NULL;
    }

void CObjectExchangeServer::ErrorIndication(TInt aError)
    {
    iLog.LogL(_L("Error "), aError);
    }

void CObjectExchangeServer::TransportUpIndication()
    {
    iLog.LogL(_L("Connected"));
    }

void CObjectExchangeServer::TransportDownIndication()
    {
    iLog.LogL(_L("Disconnected"));
    }

TInt CObjectExchangeServer::ObexConnectIndication(
    const TObexConnectInfo& /*aRemoteInfo*/,
    const TDesC8& /*aInfo*/
)
    {
    return KErrNone;
    }

void CObjectExchangeServer::ObexDisconnectIndication(const TDesC8& /*aInfo*/)
    {
    }

CObexBufObject* CObjectExchangeServer::PutRequestIndication()
    {
    return iObexBufObject;
    }

TInt CObjectExchangeServer::PutPacketIndication()
    {
    return KErrNone;
    }

TInt CObjectExchangeServer::PutCompleteIndication()
    {
    iLog.LogL(iObexBufObject->Name());
    return KErrNone;
    }

CObexBufObject* CObjectExchangeServer::GetRequestIndication(CObexBaseObject* /*aRequiredObject*/)
    {
    return NULL;
    }

TInt CObjectExchangeServer::GetPacketIndication()
    {
    return KErrNone;
    }

TInt CObjectExchangeServer::GetCompleteIndication()
    {
    return KErrNone;
    }

TInt CObjectExchangeServer::SetPathIndication(const CObex::TSetPathInfo& /*aPathInfo*/, 
                                              const TDesC8& /*aInfo*/)
    {
    return KErrNone;
    }

void CObjectExchangeServer::AbortIndication()
    {
    }

void CObjectExchangeServer::DisconnectL()
    {
    if (iObexServer && iObexServer->IsStarted())
        {
        iObexServer->Stop();
        }

    delete iObexServer;
    iObexServer = NULL;

    if (iAdvertiser->IsAdvertising())
        {
        iAdvertiser->StopAdvertisingL();
        }

    iLog.LogL(_L("Server stoped"));
    }

void CObjectExchangeServer::StartL()
    {
    TRAPD(err,InitialiseServerL());
    if (err != KErrNone)
        {
        iLog.LogL(_L("Failed "),err);
        DisconnectL();
        }
    }

void CObjectExchangeServer::InitialiseServerL()
    {
    if (iObexServer)
        { 
        ASSERT(IsConnected()); // server already running
        return;
        }

    //  Get a port to listen on
    TInt channel = AvailableServerChannelL();
        
    SetSecurityOnChannelL(EFalse, EFalse, ETrue, channel);

    // start the OBEX server    
    TObexBluetoothProtocolInfo obexProtocolInfo;
    obexProtocolInfo.iTransport.Copy(KServerTransportName);
    obexProtocolInfo.iAddr.SetPort(channel);

    iObexServer = CObexServer::NewL(obexProtocolInfo);
    iObexServer->Start(this);
    
    // advertise this service
    iAdvertiser->StartAdvertisingL(channel);
    iAdvertiser->UpdateAvailabilityL(ETrue);

    iLog.LogL(_L("Server started"));
    }

TInt CObjectExchangeServer::AvailableServerChannelL()
    {
    RSocketServ socketServer;
    User::LeaveIfError(socketServer.Connect());
    CleanupClosePushL(socketServer);

    RSocket socket;
    User::LeaveIfError(socket.Open(socketServer, _L("RFCOMM")));
    CleanupClosePushL(socket);

    TInt channel;
    User::LeaveIfError(
        socket.GetOpt(KRFCOMMGetAvailableServerChannel, KSolBtRFCOMM, channel)
    );
    
    // found the port can now close the socket and the socket server
    CleanupStack::PopAndDestroy();  //  socket
    CleanupStack::PopAndDestroy();  //  socketServer
        
    return channel;
    }

void CObjectExchangeServer::SetSecurityOnChannelL(TBool aAuthentication,
                                                  TBool aEncryption, 
                                                  TBool aAuthorisation,
                                                  TInt aChannel)
    {
    // a connection to the security manager
    RBTMan secManager;

    // a security session
    RBTSecuritySettings secSettingsSession;

    // define the security on this port
    User::LeaveIfError(secManager.Connect());
    CleanupClosePushL(secManager);
    User::LeaveIfError(secSettingsSession.Open(secManager));
    CleanupClosePushL(secSettingsSession);

    // the security settings 
    TBTServiceSecurity serviceSecurity(KUidBTObjectExchangeApp, KSolBtRFCOMM, 0);

    //Define security requirements
    serviceSecurity.SetAuthentication(aAuthentication);
    serviceSecurity.SetEncryption(aEncryption); 
    serviceSecurity.SetAuthorisation(aAuthorisation);

    serviceSecurity.SetChannelID(aChannel);
    TRequestStatus status;
    secSettingsSession.RegisterService(serviceSecurity, status);
    
    User::WaitForRequest(status); // wait until the security settings are set
    User::LeaveIfError(status.Int());
    
    CleanupStack::PopAndDestroy();  //  secManager
    CleanupStack::PopAndDestroy();  //  secSettingsSession
    }

TBool CObjectExchangeServer::IsConnected()
    {
    return iObexServer != NULL;
    }
