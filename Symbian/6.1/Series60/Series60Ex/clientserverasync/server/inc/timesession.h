/* Copyright (c) 2001, Nokia. All rights reserved */
#ifndef __CTIMESESSION__
#define __CTIMESESSION__

#include <e32base.h>
#include "timeserver.h"

/*! 
  @class CTimeServerSession
  
  @discussion An instance of class CTimeServerSession is created for each client
  */
class CTimeServerSession : public CSession
    {

public: // New methods

/*!
  @function NewL
  
  @discussion Create a CTimeServerSession object using two phase construction,
  and return a pointer to the created object
  @param client's thread
  @param the server
  @result pointer to new session
  */
    static CTimeServerSession* NewL(RThread& aClient, CTimeServer& aServer);

/*!
  @function NewLC
  
  @discussion Create a CTimeServerSession object using two phase construction,
  and return a pointer to the created object
  (leaving a pointer to the object on the cleanup stack)
  @param client's thread
  @param the server
  @result pointer to new session
  */
    static CTimeServerSession* NewLC(RThread& aClient, CTimeServer& aServer);

/*!
  @function ~CTimeServerSession
  
  @discussion Destroy the object and release all memory objects
  */
    ~CTimeServerSession();

/*!
  @function SendTimeToClient
  
  @discussion Called from Beat() and Synchronize().
  Sends current time back to requesting client
  */
    void SendTimeToClient() ;

public: // from CSession
/*!
  @functor ServiceL
  
  @discussion Service request from client
  @param message from client (containing requested operation and any data)
  */
    void ServiceL(const RMessage& aMessage);


private: // New methods

/*!
  @function CTimeServerSession
  
  @discussion Perform the first phase of two phase construction 
  @param client's thread
  @param the server
  */
    CTimeServerSession(RThread& aClient, CTimeServer& aServer);

/*!
  @function ConstructL
  
  @discussion Perform the second phase construction of a CTimeServerSession object
  */
    void ConstructL() ;

/*!
  @function PanicClient
  
  @discussion Causes the client thread to panic
  @param panic code
  */
    void PanicClient(TInt aPanic) const;

/*!
  @function RequestTimeL
  
  @discussion Called as a result of the client requesting the time.
  Starts the 'get time' operation
  @param message from client
  */
    void RequestTimeL(const RMessage& aMessage);

private: // Data
    TBool           iWaitingForTick;
    RMessage        iMessage;
    CTimeServer&    iServer;
    };

#endif