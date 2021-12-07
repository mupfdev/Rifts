// WaitLoop.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.

//	Show asynchronous programming (without active objects)
//	Example shows how a wait loop can be used to identify how a
//	request completed and service its completion
	

#include "CommonFramework.h"
#include <e32math.h>

//
// utility functions
//

LOCAL_D TInt64 smallRandSeed;

LOCAL_C TInt smallRand()
	{ 
	  // produce small random numbers in range 0..9
	TInt bigResult=Math::Rand(smallRandSeed);// result uses full 32-bit range
	return bigResult % 10;                   // return result mod 10
	}

LOCAL_C void sleep(TInt aTenths)
	{ 
	  // sleep for an interval measured in tenths of a second
	User::After(aTenths*100000); // just let the User function do it for us
	}


// Do the example
LOCAL_C void doExampleL()
    {
	  // create and initialize heartbeat timer
	RTimer heartbeat;               // heartbeat timer
	TRequestStatus heartbeatStatus; // request status associated with it
	heartbeat.CreateLocal();        // always created for this thread

	  // issue first heartbeat request
	heartbeat.After(heartbeatStatus,1000000); // request completion
	                                          // after 1 second
	TInt heartbeatTick=0;                     // counts heartbeat ticks

	  // wait loop
	for (;;)
		{
		  // wait for any request
		User::WaitForAnyRequest();
		  // find out which request completed, and handle it
		if (heartbeatStatus!=KRequestPending)
			{
			  // heartbeat completed so service request
			_LIT(KMsgServicing,"Servicing heartbeat tick %d ...\n");
			console->Printf(KMsgServicing,heartbeatTick);
			  // take some time over it
			sleep(smallRand());
			_LIT(KMsgServiced,"... heartbeat tick %d serviced\n");
			console->Printf(KMsgServiced,heartbeatTick);
			  // test whether processing should finish
			if (heartbeatTick >= 10)
				{
				  // 10 heart-beats: processing finished
				_LIT(KMsgFinishing,"Finishing\n");
				console->Printf(KMsgFinishing);
				  // finish wait loop
				break;
				}
			  // re-issue request
			heartbeatTick++;                          // increment tick
			                                          // counter
			heartbeat.After(heartbeatStatus,1000000); // request completion
			                                          // after another second
			}
		else
			{
			  // stray signal
			_LIT(KMsgStraySignal,"Stray signal\n");
			User::Panic(KMsgStraySignal, 1); // panic!
			}
		}

	// close timer
	heartbeat.Close(); // close timer
	}
