// TAndRClass.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.

#include "CommonFramework.h"

_LIT(KTxtTIntHolderDestructor,"TIntHolder destructor\n");
_LIT(KCommonFormat1,"Int()=%d\n");

// T class

class TIntHolder
	{
public: // data
	TInt iInt;
public: // functions
	TInt Int() { return iInt; }; // get the integer
	void SetInt(TInt aInt) { iInt=aInt; }; // set the integer
	void Double() { iInt *= 2; }; // double the integer
	TBool IsNonZero() { return iInt!=0; }; // check whether zero
	// destructor, coded only to show when taken and when not
	~TIntHolder() { console->Printf(KTxtTIntHolderDestructor); };
	};

void demonstrateTTypeL(); // function to demonstrate T type

// class RTimer - a typical R class

// an R class with added clean-up support

class RTimerWithCleanup : public RTimer
	{
public: // no extra data, just inherit everything from base
public: // functions
	// required for clean-up support
	operator TCleanupItem()
		{ // convert to clean-up item
		return TCleanupItem(Cleanup,this);
				// clean-up = function + object
		}
	static void Cleanup(TAny *aPtr)
		{ // static clean-up function returned by TCleanupItem
		((RTimerWithCleanup*)aPtr) -> DoCleanup();
				// do clean-up neatly, using regular member function
		}
	void DoCleanup()
		{ // do clean-up neatly
		Close(); // close timer
		}
	// helpful for automatically putting onto clean-up stack
	void CreateLocalLC()
		{ // call RTImer::CreateLocal(), and push to clean-up stack
		User::LeaveIfError(CreateLocal()); // create, but leave if couldn't
		CleanupStack::PushL(*this); // push to clean-up stack
		}
	// debug version of RTimer::Close()
	void Close()
		{ // debug version of close
		_LIT(KTxtClosingRTimer,"Closing RTimerWithCleanup\n");
		console->Printf(KTxtClosingRTimer);
		RTimer::Close(); // base call
		}
	};

void demonstrateRTypeL(); // function to demonstrate R type

// Do the example
LOCAL_C void doExampleL()
    {
	demonstrateTTypeL(); // demonstrate T type
	demonstrateRTypeL(); // demonstrate R type
	}

// stuff to demonstrate T type

void useTTypeL(TIntHolder aIntHolder); // function using a T

void demonstrateTTypeL()
	{
	_LIT(KTxtStartingDemoTTypeL,"Starting demonstrateTTypeL()\n");
	console->Printf(KTxtStartingDemoTTypeL);
	TIntHolder t; // declare variable
	// do a few things with it
	t.SetInt(3);
	t.Double();
	TInt i=t.Int();
	console->Printf(KCommonFormat1, i);
	// optionally leave
	//
	// Remove comments on next line to show this
	//User::Leave(KErrGeneral);

	// now use T type
	useTTypeL(t); // pass by value
	// end demo: T will be destructed (for what it's worth)
	_LIT(KTxtFinishingDemoTTypeL,"Finishing demonstrateTTypeL()\n");
	console->Printf(KTxtFinishingDemoTTypeL);
	}

void useTTypeL(TIntHolder aIntHolder)
	{ // function using a T
	_LIT(KTxtStartinguseTTypeL,"Starting useTTypeL()\n");
	console->Printf(KTxtStartinguseTTypeL);
	aIntHolder.Double(); // double the value
	TInt i=aIntHolder.Int(); // get value
	console->Printf(KCommonFormat1, i);
	// optionally leave
	//
	// Remove comments on next line to show this
	//User::Leave(KErrGeneral);

	// now finished
	_LIT(KTxtFinishinguseTTypeL,"Finishing useTTypeL()\n");
	console->Printf(KTxtFinishinguseTTypeL);
	}

// stuff to demonstrate R type

void useRTypeL(RTimerWithCleanup aTimer);

void demonstrateRTypeL()
	{
	_LIT(KTxtStartDemoRTypeL,"Starting demonstrateRTypeL()\n");
	console->Printf(KTxtStartDemoRTypeL);
	// declare R type on the stack, and push to clean-up stack
	RTimerWithCleanup timer; // declare on stack
	timer.CreateLocalLC(); // initialize, push to clean-up stack
	// use the R type
	TRequestStatus status; // needed for asynchronous service
	timer.After(status,1000000); // request completion in 1,000,000 micro seconds
	User::WaitForRequest(status); // wait for completion
	// optionally leave
	//
	// Remove comments on next line to show this
	//User::Leave(KErrGeneral);

	// pass to another function
	useRTypeL(timer); // use in another function
	// now finished
	CleanupStack::PopAndDestroy(); // pop and destroy timer
	_LIT(KTxtFinishDemoRTypeL,"Finishing demonstrateRTypeL()\n");
	console->Printf(KTxtFinishDemoRTypeL);
	}

void useRTypeL(RTimerWithCleanup aTimer)
	{ // use an R type
	_LIT(KTxtStartuseRTypeL,"Starting useRTypeL()\n");
	console->Printf(KTxtStartuseRTypeL);
	// use the R type
	TRequestStatus status; // needed for asynchronous service
	aTimer.After(status,1000000); // request completion in 1000000 micro seconds
	User::WaitForRequest(status); // wait for completion
	// optionally leave
	//
	// Remove comments on next line to show this
	//User::Leave(KErrGeneral);

	// now finished
	_LIT(KTxtFinishuseRTypeL,"Finishing useRTypeL()\n");
	console->Printf(KTxtFinishuseRTypeL);
	}
