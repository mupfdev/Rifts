/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __OBJECTEXCHANGECLIENT_H__
#define __OBJECTEXCHANGECLIENT_H__

#include <e32base.h>
#include <obex.h>

class CObjectExchangeServiceSearcher;
class MLog;

/*! 
  @class CObjectExchangeClient
  
  @discussion Handles the client interactions with the remote server, namely
  the connection, sending of messages and disconnection.
  */
class CObjectExchangeClient : public CActive
    {
public:
/*!
  @function NewL
  
  @discussion Construct a CObjectExchangeClient
  @param aLog the log to send output to
  @result a pointer to the created instance of CObjectExchangeClient
  */
    static CObjectExchangeClient* NewL(MLog& aLog);

/*!
  @function NewLC
  
  @discussion Construct a CObjectExchangeClient
  @param aLog the log to send output to
  @result a pointer to the created instance of CObjectExchangeClient
  */
    static CObjectExchangeClient* NewLC(MLog& aLog);

/*!
  @function ~CObjectExchangeClient
  
  @discussion Destroy the object and release all memory objects. Close any open sockets
  */
    ~CObjectExchangeClient();

/*!
  @function ConnectL
  
  @discussion Connect to an OBEX service on a remote machine
  */
    void ConnectL();

/*!
  @function DisconnectL
  
  @discussion Disconnect from the remote machine, by sending an OBEX disconnect, and
  closing the transport on (and regardless of) response from the server.
  */
    void DisconnectL();

/*!
  @function SendObjectL
  
  @discussion Send a message to a service on a remote machine
  */
    void SendObjectL();

/*!
  @function StopL
  
  @discussion Send the OBEX aborts command to the remote machine
  */
    void StopL();

/*!
  @function IsConnected
  
  @result ETrue if the client is connected
  */
    TBool IsConnected();

/*!
  @function IsBusy
  
  @result ETrue if the client is performing some operation.
  */
    TBool IsBusy();

protected:    // from CActive
/*!
  @function DoCancel
  
  @discussion Cancel any outstanding requests
  */
    void DoCancel();

/*!
  @function RunL
  
  @discussion Respond to an event
  */
    void RunL();

private:
/*!
  @function CMessageClient

  @discussion Construct this object
  @param aLog the log to send output to
  */
    CObjectExchangeClient(MLog& aLog);

/*!
  @function ConstructL

  @discussion Perform second phase construction of this object
  */
    void ConstructL();

/*!
  @function ConnectToServerL

  @discussion Connect to the server
  */
    void ConnectToServerL();

private:

    /*!
      @enum TState
  
      @discussion The state of the active object, determines behaviour within
      the RunL method.
      @value EWaitingToGetDevice waiting for the user to select a device
      @value EGettingDevice searching for a device
      @value EGettingService searching for a service
      @value EGettingConnection connecting to a service on a remote machine
      @value EWaitingToSend sending a message to the remote machine
      @value EDisconnecting disconnecting the server
      */

    enum TState 
        {
        EWaitingToGetDevice,
        EGettingDevice,
        EGettingService,
        EGettingConnection,
        EWaitingToSend,
        EDisconnecting
        };

    /*! @var iState the state of the active object, determines behaviour within the RunL method. */
    TState iState;

    /*! @var iServiceSearcher searches for service this client can connect to */
    CObjectExchangeServiceSearcher* iServiceSearcher;

    /*! @var iClient manages the OBEX client connection */
    CObexClient* iClient;

    /*! @var iCurrObject the OBEX object to transfer */
    CObexBaseObject* iCurrObject;

    /*! @var iLog the log to send output to */
    MLog& iLog;
    };

#endif // __OBJECTEXCHANGECLIENT_H__

