// SimpleClient.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.

// needed for client interface
#include "ClientServer.h"

// needed for client (doExampleL)
#include "SimpleClient.h"
#include "CommonFramework.h"

//
// Common format strings
//

_LIT(KCommonFormat1,"counter value: %d \n");

const TUint kDefaultMessageSlots=4;


//**********************************
//RCountServ
//**********************************

RCountServ::RCountServ()
	{
	}


// Connect to the  server - default number of message slots = 4
TInt RCountServ::Connect()
	{
	TInt r=StartThread();
	if (r==KErrNone)
		r=CreateSession(KCountServerName,Version(),kDefaultMessageSlots);
	return(r); 
	}

	
// Return the client side version number.
TVersion RCountServ::Version(void) const
	{
	return(TVersion(KCountServMajorVersionNumber,KCountServMinorVersionNumber,KCountServBuildVersionNumber));
	}

// increase the counter by the default (1)
TInt RCountServ::SetFromString(const TDesC& aString)
	{
	TAny *p[KMaxMessageArguments];
	p[0]= (TAny*)(&aString);
	return SendReceive(ECountServSetFromString,&p[0]);
	}


// increase the counter by the default (1)
void RCountServ::Increase()
	{
	TAny *p[KMaxMessageArguments];
	SendReceive(ECountServIncrease,&p[0]);
	}


// increase the counter by an integer
void RCountServ::IncreaseBy(TInt anInt)
	{
	TAny *p[KMaxMessageArguments];
	p[0]= (TAny*)anInt;
	SendReceive(ECountServIncreaseBy,&p[0]);
	}


// decrease the counter by the default (1)
void RCountServ::Decrease()
	{
	TAny *p[KMaxMessageArguments];
	SendReceive(ECountServDecrease,&p[0]);
	}


// decrease the counter by an integer
void RCountServ::DecreaseBy(TInt anInt)
	{
	TAny *p[KMaxMessageArguments];
	p[0]= (TAny*) anInt;
	SendReceive(ECountServDecreaseBy,&p[0]);
	}


//reset the counter to 0
void RCountServ::Reset()
	{
	TAny *p[KMaxMessageArguments];
	SendReceive(ECountServReset,&p[0]);
	}


//get the server counter value
TInt RCountServ::CounterValue()
	{
	TInt res=0;
	TPckgBuf<TInt> pckg;
	TAny *p[KMaxMessageArguments];
	p[0]=(TAny *) &pckg;
	SendReceive(ECountServValue,&p[0]);
	res = pckg();
	return res;
	}


//stop the server. This is not implemented in the server ; here to demonstrate handling of 
//non-implemented requests.
TInt RCountServ::Stop()
	{
	TAny *p[KMaxMessageArguments];
	return SendReceive(ECountServStop,&p[0]);
	}


// test the count server
LOCAL_C void doExampleL()
	{
	_LIT(KTxt11,"Testing the count server \n\n");
	console->Printf(KTxt11); 
    RCountServ ss;

	// Connect to the count server
	User::LeaveIfError(ss.Connect());

	_LIT(KTxt9,"Initialize counter with ");		

	// set counter value using an illegal string - this will fail
	console->Printf(KTxt9);
	_LIT(KTxtIllegalString,"22h4");
	console->Printf(KTxtIllegalString);
	TInt ret = ss.SetFromString(KTxtIllegalString);
	_LIT(KTxt10,"\nSetting counter from string failed: non-numeric character detected\n");
	if (ret==ENonNumericString)
		console->Printf(KTxt10);
	
	// set counter value using a legal string 
	console->Printf(KTxt9);
	_LIT(KTxtLegalString,"224");
	console->Printf(KTxtLegalString);
	ret = ss.SetFromString(KTxtLegalString);
	_LIT(KFormat2,"\ncounter value: %d \n");
	console->Printf(KFormat2, ss.CounterValue());
	
	// increase/decrease counter value
	_LIT(KTxt8,"Increase counter (default 1)..\n");		
	console->Printf(KTxt8);
	ss.Increase();

	_LIT(KTxt7,"Increase counter by 2..\n");		
	console->Printf(KTxt7);
	ss.IncreaseBy(2);
	
	_LIT(KTxt6,"Decrease counter(default 1)..\n");		
	console->Printf(KTxt6);
	ss.Decrease();

	_LIT(KTxt5,"Increase counter by 7..\n");		
	console->Printf(KTxt5);
	ss.IncreaseBy(7);
	
	_LIT(KTxt4,"Increase counter(default 1)..\n");	
	console->Printf(KTxt4);
	ss.Increase();

	_LIT(KTxt3,"Decrease counter by 3..\n");	
	console->Printf(KTxt3);
	ss.DecreaseBy(3);
	
	console->Printf(KCommonFormat1, ss.CounterValue());
	
	// reset counter value
	_LIT(KTxt12,"Reseting counter value to 0..\n");
	console->Printf(KTxt12);
	ss.Reset();
	console->Printf(KCommonFormat1, ss.CounterValue());
	
	// call API function which is not implemented in the server
	_LIT(KTxt2,"About to call the function Stop()..\n");
	console->Printf(KTxt2);
	ret = ss.Stop();

	_LIT(KTxt1,"Sorry, this function is not supported\n");
	if (ret==KErrNotSupported)
		console->Printf(KTxt1);
	
	// close the count server session
	ss.Close();
	}
