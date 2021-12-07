// RealLifeWaitLoop.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.

/*
	Show asynchronous programming (without active objects)
	Example introduces the "complications" involved in real-life
	wait loops, which always deal with multiple asynchronous
	service providers
*/


#include "CommonFramework.h"
#include <e32math.h>

//
// Common literal text
//

_LIT(KMsgQuickCancelled,"Quick service request canceled\n");

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
	RTimer heartbeat;               // Heartbeat timer.
	TRequestStatus heartbeatStatus; // Request status associated with it.
	heartbeat.CreateLocal();        // Always created for this thread.

	  // create stuff for secondary timer
	RTimer quickService;                    // A quick service.
	TRequestStatus quickServiceStatus;      // Ccorresponding status.
	TBool quickServiceRequestIssued=EFalse; // Whether request issued.
	quickService.CreateLocal();             // Create timer.

	  // issue first heartbeat request
	heartbeat.After(heartbeatStatus,1000000); // Request completion
	                                          // after 1 second.
	TInt heartbeatTick=0;                     // Ccounts heartbeat ticks.

	  // wait loop
	for (;;)
		{
		  // Wait for any request
		User::WaitForAnyRequest();
		  // find out which request completed, and handle it
		if (heartbeatStatus!=KRequestPending)
			{ 
			  // heartbeat completed so service request
			_LIT(KMsgServicing,"Servicing heartbeat tick %d ...\n");
			console->Printf(KMsgServicing,heartbeatTick);
			  // take some time over it
			sleep(smallRand());

			if (smallRand() < 5)
				{ 
				  // issue a quick request 50% of the time
				  // cancel any outstanding quick request
				if (quickServiceRequestIssued)
					{
					quickService.Cancel();            // cancel request
					User::WaitForRequest(quickServiceStatus); // wait
					quickServiceRequestIssued=EFalse; // indicate not issued
					console->Printf(KMsgQuickCancelled);
					}
				  // issue new quick request
				quickService.After(quickServiceStatus,(smallRand()*2)*100000);
				  // request an event after 0 .. 1.8 seconds
				quickServiceRequestIssued=ETrue; // indicate request issued
				_LIT(KMsgQuickIssued,"Quick service request issued\n");
				console->Printf(KMsgQuickIssued);
				}

			_LIT(KMsgServiced,"... heartbeat tick %d serviced\n");
			console->Printf(KMsgServiced, heartbeatTick);
			  // test whether processing should finish
			if (heartbeatTick >= 10)
				{ 
				  // 10 heart-beats: processing finished
				_LIT(KMsgFinishing,"Finishing\n");
				console->Printf(KMsgFinishing);

				  // cancel quick request, if outstanding
				if (quickServiceRequestIssued)
					{
					  // only relevant if request issued
					quickService.Cancel(); // request early completion
					User::WaitForRequest(quickServiceStatus); // wait
					quickServiceRequestIssued=EFalse;
					  // request no longer issued
					console->Printf(KMsgQuickCancelled);
					}

				break; // finish wait loop
				}
			  // re-issue request
			heartbeatTick++; // increment tick counter
			heartbeat.After(heartbeatStatus,1000000); // another second
			}

		else if (quickServiceRequestIssued && quickServiceStatus!=KRequestPending)
			{ // if quick service request issued, and completed, then service it
			_LIT(KMsgQuickCompleted,"Quick request completed\n");
			console->Printf(KMsgQuickCompleted);
			quickServiceRequestIssued=EFalse; // indicate request not issued
			}

		else
			{ // stray signal
			_LIT(KMsgStraySignal,"Stray signal\n");
			User::Panic(KMsgStraySignal, 1); // panic!
			}
		}

	// close quick service
	quickService.Close(); // close

	// close timer
	heartbeat.Close(); // close timer
	}
