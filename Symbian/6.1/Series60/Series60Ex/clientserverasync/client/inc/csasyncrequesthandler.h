/* Copyright (c) 2001, Nokia. All rights reserved */
#ifndef __CCSASYNCREQUESTHANDLER_H
#define __CCSASYNCREQUESTHANDLER_H

#include <e32base.h>
#include "TimeServerSession.h"
#include "AsyncTimeObserver.h"

/*! 
  @class CCSAsyncRequestHandler
  
  @discussion An instance of the request handler object for the ClientServerAsync 
  example application
  */
class CCSAsyncRequestHandler : public CActive
	{
public:

/*!
  @function NewL
   
  @discussion Create a CCSAsyncRequestHandler object using two phase construction, 
              and return a pointer to the created object
  @param aObserver the object to be used to handle updates from the server
  @result a pointer to the created instance of CCSAsyncRequestHandler
  */
    static CCSAsyncRequestHandler* NewL(MAsyncTimeObserver& aObserver) ;

/*!
  @function NewLC
   
  @discussion Create a CCSAsyncRequestHandler object using two phase construction, 
              and return a pointer to the created object
  @param aObserver the object to be used to handle updates from the server
  @result a pointer to the created instance of CCSAsyncRequestHandler
  */
    static CCSAsyncRequestHandler* NewLC(MAsyncTimeObserver& aObserver) ;

/*!
  @function ~CCSAsyncRequestHandler
  
  @discussion Destroy the object and release all memory objects
  */
	~CCSAsyncRequestHandler();

/*!
  @function RequestTime
  
  @discussion Send a request to the server for an update to the time
  */
    void RequestTime();

/*!
  @function CancelRequest
  
  @discussion Cancel an outstanding request
  */
    void CancelRequest() ;

/*!
  @function Time
  
  @discussion Get a copy of the last time received from the server
  */
    TTime Time() const;

protected: // from CActive

/*!
  @function RunL
  
  @discussion Callback function. Invoked to handle responses from the server
  */
	void RunL();

/*!
  @function DoCancel
  
  @discussion Cancel any outstanding operation
  */
	void DoCancel();

private:
/*!
  @function ConstructL
  
  @discussion Perform the second phase construction of a CCSAsyncRequestHandler object
  */
    void ConstructL();

/*!
  @function CCSAsyncRequestHandler
   
  @discussion Perform the first phase of two phase construction
  @param aSession the session to be used to communicate with the server
  @param aObserver the object to be used to handle updates from the server
  */
	CCSAsyncRequestHandler(MAsyncTimeObserver& aObserver);

private: // data
    
    enum TPhase
        {
        EPhaseIdle,
        EPhaseWaitingForTime
        } ;

    RTimeServerSession  iSession;
    TTime               iTime;
    MAsyncTimeObserver& iObserver;
	};

#endif