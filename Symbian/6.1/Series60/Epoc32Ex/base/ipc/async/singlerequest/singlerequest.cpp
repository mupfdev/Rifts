// SingleRequest.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
//
//  Shows asynchronous programming (without active objects).
//	Example shows how a single request can be issued, followed
//	by User::WaitForRequest()


#include "CommonFramework.h"



// Do the example
LOCAL_C void doExampleL()
    {
	  // create and initialize heartbeat timer
	RTimer heartbeat;               // heartbeat timer

	TRequestStatus heartbeatStatus; // request status associated with it
	heartbeat.CreateLocal();        // always created for this thread

	  // go round timing loop
	for (TInt i=0; i<10; i++)
		{
		  // issue and wait for single request
		heartbeat.After(heartbeatStatus,1000000); // wait 1 second
		User::WaitForRequest(heartbeatStatus);    // wait for request
		                                          // to complete
		  // say we're here
		_LIT(KFormatString1,"Tick %d\n");
		console->Printf(KFormatString1, i);
		}

	  // close timer
	heartbeat.Close(); // close timer
	}
