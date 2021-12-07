/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __MESSAGECLIENT_H__
#define __MESSAGECLIENT_H__

#include <e32base.h>
#include <es_sock.h>

#include <bt_sock.h>
#include <BTextNotifiers.h>
#include <BtSdp.h>

class CMessageServiceSearcher;
class MLog;

/*! 
  @class CMessageClient
  
  @discussion Connects and sends messages to a remote machine using bluetooth
  */
class CMessageClient : public CActive
    {
public:
/*!
  @function NewL
  
  @discussion Construct a CMessageClient
  @param aLog the log to send output to
  @result a pointer to the created instance of CMessageClient
  */
    static CMessageClient* NewL(MLog& aLog);

/*!
  @function NewLC
  
  @discussion Construct a CMessageClient
  @param aLog the log to send output to
  @result a pointer to the created instance of CMessageClient
  */
    static CMessageClient* NewLC(MLog& aLog);

/*!
  @function ~CMessageClient
  
  @discussion Destroy the object and release all memory objects. Close any open sockets
  */
    ~CMessageClient();

/*!
  @function IsConnected
  
  @result ETrue if the client is fully connected to the server.
  */
    TBool IsConnected();

/*!
  @function IsConnected
  
  @result ETrue if the client is establishing a connection to the server.
  */
    TBool IsConnecting();

/*!
  @function IsConnected
  
  @result ETrue if the client is connected.
  */
    TBool IsSendingMessage();


/*!
  @function IsReadyToSendMessage
  
  @result ETrue if the client can send a message.
  */
    TBool IsReadyToSendMessage();

/*!
  @function ConnectL

  @discussion Connect to an available service on a remote machine
  */
    void ConnectL();

/*!
  @function DisconnectL

  @discussion Disconnect from remote machine
  */
    void DisconnectL();

/*!
  @function SendMessageL

  @discussion Sends a message to a service on a remote machine.
  */    
    void SendMessageL();

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
  @function ConnectToServerL

  @discussion Connects to the service
  */    
    void ConnectToServerL();

/*!
  @function ConnectToServerL

  @discussion Connects to the service
  */    
    void DisconnectFromServerL();

/*!
  @function WaitOnConnectionL()

  @discussion Wait for data or disconnection
  */
    void WaitOnConnectionL();

/*!
  @function CMessageClient

  @discussion Constructs this object
  */
    CMessageClient(MLog& aLog);

/*!
  @function ConstructL

  @discussion Performs second phase construction of this object
  @param aMessage the message to be sent to the remote machine
  */
    void ConstructL(const TDesC8& aMessage);


private:

    /*!
      @enum TState
  
      @discussion The state of the active object, determines behaviour within
      the RunL method.
      @value EWaitingToGetDevice waiting for the user to select a device
      @value EGettingDevice searching for a device
      @value EGettingService searching for a service
      @value EGettingConnection connecting to a service on a remote machine
	  @value EConnected connected to a service on a remote machine
      @value ESendingMessage sending a message to the remote machine

      */
    enum TState 
        {
        EWaitingToGetDevice,
        EGettingDevice,
        EGettingService,
        EGettingConnection,
		EConnected,
        ESendingMessage,
		EDisconnecting
        };
    
    /*! @var iState the current state of the client */
    TState iState;

    /*! @var iServiceSearcher searches for service this client can connect to */
    CMessageServiceSearcher* iServiceSearcher;

    /*! @var iLog the log to send output to */
    MLog& iLog;

    /*! @var iMessage a copy of the message to send */
    HBufC8* iMessage;

    /*! @var iSocketServer a connection to the socket server */
    RSocketServ iSocketServer;

    /*! @var iSendingSocket a socket to connect with */
    RSocket iSendingSocket;

    /*! @var iServiceClass the service class UUID to search for */
    TUUID iServiceClass;

	/*! @var iDummyBuffer buffer needed for read on connection to server */
	TBuf8 <1>  iDummyBuffer;

    };

#endif // __MESSAGECLIENT_H__

