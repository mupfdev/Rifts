/* Copyright (c) 2001, Nokia. All rights reserved */
#ifndef __CTIMESERVER__
#define __CTIMESERVER__

#include <e32base.h>
#include "AsyncServer.pan"

/*! 
  @class CTimeServer
  
  @discussion An instance of class CTimeServer is the main server class
  for the ClientServerAsync example application
  */
class CTimeServer : public CServer, MBeating
    {
public : // New methods

/*!
  @function NewL
  
  @discussion Create a CTimeServer object using two phase construction,
  and return a pointer to the created object
  @result pointer to created CTimeServer object
  */
    static CTimeServer* NewL();

/*!
  @function NewLC
  
  @discussion Create a CTimeServer object using two phase construction,
  and return a pointer to the created object, leaving a pointer to the
  object on the cleanup stack
  @result pointer to created CTimeServer object
  */
    static CTimeServer* NewLC();

/*!
  @function ~CTimeServer
  
  @discussion Destroy the object and release all memory objects
  */
    ~CTimeServer();

/*!
  @function ThreadFunction
  
  @discussion main function for the server thread
  @param semaphore to be flagged when server has been started
  @result error code
  */
    static TInt ThreadFunction(TAny* sStarted);

/*!
  @function IncrementSessions
  
  @discussion Increments the count of the active sessions for this server
  */
	void IncrementSessions();

/*!
  @function DecrementSessions
  
  @discussion Decrements the count of the active sessions for this server. If no more
              sessions are in use the server terminates.
  */
	void DecrementSessions();

/*!
  @function WaitForTickL
  
  @discussion Activates the heartbeat.
  */
    void    WaitForTickL();

public: // from MBeating
/*!
  @functor Beat
  
  @discussion A clock tick has occured
  */
	void Beat();
/*!
  @functor Synchronize
  
  @discussion Several clock ticks have occured
  */
	void Synchronize();


protected:  // From CActive
/*!
  @function RunError
  
  @discussion Process any errors
  @param aError the leave code reported.
  */
	TInt RunError(TInt aError);

private: // New methods

/*!
  @function CTimeServer
 
  @discussion Perform the first phase of two phase construction 
  @param priority for this thread
  */
    CTimeServer(TInt aPriority) ;

/*!
  @function ConstructL
  
  @discussion Perform the second phase construction of a CTimeServer object
  */
    void ConstructL() ;

/*!
  @function PanicClient
  
  @semantics panic the client
  @param aMessage the message channel to the client
  @param aReason the reason code for the panic.
  */
    static void PanicClient(const RMessage& aMessage, TTimeServPanic aReason);
/*!
  @function PanicServer
  
  @semantics panic the server
  @param panic code
  */
    static void PanicServer(TTimeServPanic aPanic);
/*!
  @function ThreadFunctionL
  
  @discussion second stage startup for the server thread
  */
    static void ThreadFunctionL();

/*!
  @function SendTimeToSessions
  
  @discussion informs all the clients that a time change has occured.
  */
    void SendTimeToSessions();

private: // From CServer

/*!
  @function NewSessionL
  
  @discussion Create a time server session, and return a pointer to the created object
  @param version 
  @result pointer to new session
  */
    CSharableSession* NewSessionL(const TVersion &aVersion) const;

private:
    TInt        iSessionCount;
    CHeartbeat* iHeartbeat;
    };


#endif