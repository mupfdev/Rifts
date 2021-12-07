// BasicTimer.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.

//	Show how RTimer, the basic timer class, works

#include "CommonFramework.h"


void showTime(TTime aTime)
	{
		// Format time, using system default locale settings
		// and then print the time using system default time
		// separator character (':') in 24 hour clock format.

	TBuf<40> timeString; // Holds the formatted date and time
	_LIT(KFormat1,"%:0%H%:1%T%:2%S%:3");
	aTime.FormatL(timeString,KFormat1);
	_LIT(KFormat2,"(24 hr clock) = %S\n");
	console->Printf(KFormat2, &timeString);
	}


void WaitForKey()
	{
	_LIT(KTxtPressAnyKey,"Press any key to continue\n\n");
	console->Printf(KTxtPressAnyKey);
	console->Getch();
	}


LOCAL_C void doExampleL()
    {
	RTimer timer;				 // The asynchronous timer and ...
	TRequestStatus timerStatus;  // ... its associated request status
	timer.CreateLocal();         // Always created for this thread.

		// do some After() requests
	_LIT(KTxt1,"Doing 10 after requests\n");
	console->Printf(KTxt1);
	for (TInt i=0; i<10; i++)
		{
			// issue and wait for single request
		timer.After(timerStatus,1000000);  // wait 1 second
		User::WaitForRequest(timerStatus); // wait for request to complete
			// display the tick count
		_LIT(KFormat3,"Tick %d\n");
		console->Printf(KFormat3, i);
		}

    WaitForKey(); // wait until a key is pressed

		// do an At() request
	TTime time; // time in microseconds since 0AD nominal Gregorian
	_LIT(KTxt2,"The time now is, ");
	console->Printf(KTxt2);
		// set and print current time
	time.HomeTime(); 
	showTime(time); 
		// add 10 seconds to the time
	TTimeIntervalSeconds timeIntervalSeconds(10);
	time += timeIntervalSeconds;
	_LIT(KTxt3,"Doing a request ten seconds from now at, ");
	console->Printf(KTxt3);
	showTime(time); // print the time the request should complete
		// issue and wait for single request
	timer.At(timerStatus,time); // set timer to go off in 10 seconds
	User::WaitForRequest(timerStatus); // wait for request to complete
		// say it's over, and set and print the time again
	_LIT(KTxt4,"Your 10 seconds are up\nThe time now is, ");
	console->Printf(KTxt4);
	time.HomeTime(); // set time to now
	showTime(time); // print the time
		// close timer
	timer.Close(); // close timer
	}

