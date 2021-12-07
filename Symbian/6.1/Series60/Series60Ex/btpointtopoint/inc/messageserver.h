
/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __MESSAGESERVER_H__
#define __MESSAGESERVER_H__

#include <e32base.h>
#include <es_sock.h>

#include <btsdp.h>
#include <btmanclient.h>

class CMessageServiceAdvertiser;
class MLog;

/*! 
  @class CMessageServer
  
  @discussion Provides a simple messaging service.
  */
class CMessageServer : public CActive
    {
public:

/*!
  @enum
  
  @discussion The maximum length of any message that can be read
  */    
    enum { KMaximumMessageLength = 32 };
/*!
  @function NewL
  
  @discussion Construct a CMessageServer
  @param aLog the log to send output to
  @result a pointer to the created instance of CMessageServer
  */
    static CMessageServer* NewL(MLog& aLog);

/*!
  @function NewLC
  
  @discussion Construct a CMessageServer
  @param aLog the log to send output to
  @result a pointer to the created instance of CMessageServer
  */
    static CMessageServer* NewLC(MLog& aLog);

/*!
  @function ~CMessageServer
  
  @discussion Destroy the object and release all memory objects. Close any open sockets
  */
    ~CMessageServer();

/*!
  @function IsConnected
  
  @discussion Determines whether the server is connected
  @result ETrue if the server is connected
  */
    TBool IsConnected();

/*!
  @function StartL
  
  @discussion Start the server
  */
    void StartL();

/*!
  @function StopL
  
  @discussion Stop the server
  */
    void StopL();

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
  @function CMessageServer

  @discussion Constructs this object
  */
    CMessageServer(MLog& aLog);

/*! 
  @function ConstructL

  @discussion 2nd phase construction of this object
  */
    void ConstructL();

/*! 
  @function RequestData

  @discussion Request data from the client, this object is notified when data becomes
  available
  */
    void RequestData();

/*!
  @function SetSecurityOnChannelL

  @disussion Sets the security on the channel port
  */
    static void SetSecurityOnChannelL(TBool aAuthentication,
                                      TBool aEncryption, 
                                      TBool aAuthorisation,
                                      TInt aChannel);

private:
    /*! @var iLog the log to send output to */
    MLog& iLog;

    /*! @var iAdvertiser used to advertise this service */
    CMessageServiceAdvertiser* iAdvertiser;

    /*! @var iSocketServer a connection to the socket server */
    RSocketServ iSocketServer;

    /*! @var iListeningSocket the listening socket */
    RSocket iListeningSocket;

    /*! @var iAcceptedSocket the socket that connections are accepted to */
    RSocket iAcceptedSocket;

    /*! @var iLen length of data read */
    TSockXfrLength iLen;

    /*! @var iBuffer the buffer to read data to */
    TBuf8<KMaximumMessageLength> iBuffer;

    /*! @var iSecManager a connection to the security manager */
    RBTMan iSecManager;

/*!
  @enum TReceiverState
  
  @discussion The current state of the receiver
  @value EDisconnected server not connected
  @value EConnecting not fully constructed
  @value EWaitingForMessage connected to a client and waiting for data
  */
    enum TState
        {
        EDisconnected,
        EConnecting,
        EWaitingForMessage
        };

    /*! @var iReceiverState the state of the server */
    TState iState;

    };

#endif // __MESSAGESERVER_H__

