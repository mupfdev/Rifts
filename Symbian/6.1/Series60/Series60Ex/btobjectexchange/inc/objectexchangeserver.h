/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __BTOBJECTEXCHANGE_SERVER__
#define __BTOBJECTEXCHANGE_SERVER__

#include <e32base.h>
#include <obex.h>
#include <btsdp.h>
#include <btmanclient.h>

class CObjectExchangeServiceAdvertiser;
class MLog;

/*! 
  @class CObjectExchangeServer
  
  @discussion Handles the server interactions with the remote client, namely
  the connection, receiving of messages and disconnection.
  */
class CObjectExchangeServer : public CBase, public MObexServerNotify
    {
public:
/*!
  @function NewL
  
  @discussion Construct a CObjectExchangeServer
  @param aLog the log to send output to
  @result a pointer to the created instance of CObjectExchangeServer
  */
    static CObjectExchangeServer* NewL(MLog& aLog);

/*!
  @function NewLC
  
  @discussion Construct a CObjectExchangeServer
  @param aLog the log to send output to
  @result a pointer to the created instance of CObjectExchangeServer
  */
    static CObjectExchangeServer* NewLC(MLog& aLog);

/*!
  @function ~CObjectExchangeServer
  
  @discussion Destroy the object and release all memory objects
  */
    ~CObjectExchangeServer();

/*!
  @function StartL
  
  @discussion Starts the server
  */
    void StartL();

/*!
  @function DisconnectL
  
  @discussion Disconnects the server
  */    
    void DisconnectL();
    
/*!
  @function IsConnected
  
  @result ETrue if the server is connected.
  */    
    TBool IsConnected();

private:
/*!
  @function CObjectExchangeServer
  
  @param aLog the log to send output to
  @discussion Constructs this object
  */
    CObjectExchangeServer(MLog& aLog);

/*!
  @function ConstructL
  
  @discussion 2nd phase construction of this object
  */
    void ConstructL();

/*!
  @function UpdateAvailabilityL
  
  @discussion Update the service availability field of the service record
  @param aIsAvailable ETrue is the service is not busy.
  */
    void UpdateAvailabilityL(TBool aIsAvailable);

/*!
  @function InitialiseServerL
  
  @discussion Initialises the server
  */
    void InitialiseServerL();

/*!
  @function AvailableServerChannelL

  @result an available channel
  */
    static TInt AvailableServerChannelL();

/*!
  @function SetSecurityOnChannelL

  @disussion Sets the security on the channel port
  */
    static void SetSecurityOnChannelL(TBool aAuthentication,
                                      TBool aEncryption, 
                                      TBool aAuthorisation,
                                      TInt aPort);

private: // from MObexServerNotify (these methods are defined as private in MObexServerNotify)
/*!
  @function ErrorIndication

  @discussion Receive error indication
  @param aError the error code
  */
    void ErrorIndication(TInt aError);

/*!
  @function TransportUpIndication

  @discussion Called when the underlying socket transport connection is made from
  a remote client to the server
  */
    void TransportUpIndication();

/*!
  @function TransportDownIndication

  @discussion Transport connection is dropped
  */
    void TransportDownIndication();

/*!
  @function ObexConnectIndication

  @discussion Invoked when an OBEX connection is made from a remote client
  @param aRemoteInfo connection information supplied by the remote machine
  @param aInfo holds further information about the requested connection
  @result system wide error code 
  */
    TInt ObexConnectIndication(const TObexConnectInfo& aRemoteInfo, const TDesC8& aInfo);

/*!
  @function ObexDisconnectIndication

  @discussion OBEX server has been disconnected
  @param aInfo contains information about the disconnection
  */
    void ObexDisconnectIndication(const TDesC8& aInfo);

/*!
  @function UpdateAvailabilityL

  @result the CObexBufObject in which to store the transferred object
  */
    CObexBufObject* PutRequestIndication();
    
/*!
  @function PutPacketIndication

  @result system wide error code 
  */
    TInt PutPacketIndication();
    
/*!
  @function PutCompleteIndication

  @result system wide error code 
  */    
    TInt PutCompleteIndication();
    
/*!
  @function GetRequestIndication

  @discussion Called when a full get request has been received from the client
  @param aRequestedObject holds details about the requested object
  @result the CObexBufObject in which return to the client
  */    
    CObexBufObject* GetRequestIndication(CObexBaseObject* aRequestedObject);

/*!
  @function GetPacketIndication

  @result system wide error code 
  */
    TInt GetPacketIndication();

/*!
  @function GetCompleteIndication

  @result system wide error code 
  */
    TInt GetCompleteIndication();

/*!
  @function SetPathIndication

  @param aPathInfo the information received in a SETPATH command
  @result system wide error code 
  */
    TInt SetPathIndication(const CObex::TSetPathInfo& aPathInfo, const TDesC8& aInfo);

/*!
  @function AbortIndication

  @discussion Server has been aborted
  */
    void AbortIndication();

private:

    /*! @var iLog the log to send output to */
    MLog& iLog;

    /*! @var iObexServer manages the OBEX client connection */
    CObexServer* iObexServer;

    /*! @var iObexBufData the raw data that has been transferred */
    CBufFlat* iObexBufData;

    /*! @var iCurrObject the OBEX object that has been transferred*/
    CObexBufObject* iObexBufObject;

    /*! @var iAdvertiser used to advertise this service */
    CObjectExchangeServiceAdvertiser* iAdvertiser;
    };

#endif // __BTOBJECTEXCHANGE_SERVER__

