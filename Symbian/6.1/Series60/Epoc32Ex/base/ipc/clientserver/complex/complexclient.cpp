// ComplexClient.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.


#include "ComplexClientAndServer.h"
#include "ComplexClient.h"
#include "CommonFramework.h"

//
// Common format strings
//
_LIT(KCommonFormat1,"counterA value: %d \n");
_LIT(KCommonFormat2,"counterB value: %d \n");

// number of message slots.
const TUint kDefaultMessageSlots=4;



//********************************
//RCountServ
//********************************


RCountServ::RCountServ()
	{
	}


// Connect to the  server - default number of message slots is four
TInt RCountServ::Connect()
	{
	TInt r=StartThread();
	if (r==KErrNone)
		r=CreateSession(KCountServerName,Version(),kDefaultMessageSlots);
	return(r); 
	}
	

// Return the version number
TVersion RCountServ::Version(void) const
	{
	return(TVersion(KCountServMajorVersionNumber,KCountServMinorVersionNumber,KCountServBuildVersionNumber));
	}


// Close the session; makes call to server which deletes the object container and object index
// for this session
void RCountServ::Close()
	{
	TAny *p[KMaxMessageArguments];
	SendReceive(ECountServCloseSession,&p[0]);
	RHandleBase::Close();
	}


 // Mark start of resource count check.
void RCountServ::ResourceCountMarkStart()
	{
	SendReceive(ECountServResourceCountMarkStart,NULL);
	}


// Check for resource count heaven.
void RCountServ::ResourceCountMarkEnd()
	{
	SendReceive(ECountServResourceCountMarkEnd,NULL);
	}


// Return the number of subsession in this session
TInt RCountServ::ResourceCount()
	{
	//previously not initialised
	TInt count=0;
	TPckgBuf<TInt> pckg(count);
	TAny* p[KMaxMessageArguments];
	p[0]=&pckg;
	SendReceive(ECountServResourceCount,&p[0]);
	return pckg();
	}


//********************************
//RCounter
//********************************


//  create new subsession with the count server
TInt RCounter::Open(RCountServ &aServer )
    {
	TAny *p[KMaxMessageArguments];
	return CreateSubSession(aServer,ECountServCreateSubSession,&p[0]);
	}

// close a subsession
void RCounter::Close()
	{
	RSubSessionBase::CloseSubSession(ECountServCloseSubSession);
	}

// initialize the subsession counter using a descriptor (e.g passing the text "12"); this demonstrates reading from
// the client address space.
TInt RCounter::SetFromString(const TDesC& aString)
	{
	TAny *p[KMaxMessageArguments];
	p[0]= (TAny*)(&aString);
	return SendReceive(ECountServInitSubSession,&p[0]);
	}


// increase by default, 1
void RCounter::Increase()  
	{
	if (SubSessionHandle())
		{
		TAny *p[KMaxMessageArguments];
		SendReceive(ECountServIncrease,&p[0]);
		}
	}


// increase by an integer
void RCounter::IncreaseBy(TInt anInt)
	{
	if (SubSessionHandle())
		{
		TAny *p[KMaxMessageArguments];
		p[0]= (TAny*) anInt;
		SendReceive(ECountServIncreaseBy,&p[0]);
		}
	}


// decrease by default, 1
void RCounter::Decrease() 
	{
	if (SubSessionHandle())
		{
		TAny *p[KMaxMessageArguments];
		SendReceive(ECountServDecrease,&p[0]);
		}
	}


// decrease by an integer
void RCounter::DecreaseBy(TInt anInt)
	{
	if (SubSessionHandle())
		{
		TAny *p[KMaxMessageArguments];
		p[0]= (TAny*) anInt;
		SendReceive(ECountServDecreaseBy,&p[0]);
		}
	}


// reset the count server to 0
void RCounter::Reset()
	{
	if (SubSessionHandle())
		{
		TAny *p[KMaxMessageArguments];
		SendReceive(ECountServReset,&p[0]);
		}
	}


// get the count server value
TInt RCounter::CounterValue()
	{
	TInt res=0;
	TPckgBuf<TInt> pckg;
	if (SubSessionHandle())
		{
		TAny *p[KMaxMessageArguments];
		p[0]=(TAny *) &pckg;
		SendReceive(ECountServValue,&p[0]);
		res = pckg();
		}
	return res;
	}


//
// Client program
//

LOCAL_C void doExampleL()
	{
	_LIT(KTxt1,"count server test with 2 client subsessions; independent counters \n");
	console->Printf(KTxt1);
    RCountServ countserv;

		// set up a session with the count server
	User::LeaveIfError(countserv.Connect());

		// mark start of operations
	countserv.ResourceCountMarkStart();

		// set up subsessions with the count server; initialize
		// subsesssion counter values.
	RCounter counterA;
	counterA.Open(countserv);
	_LIT(KTxt2,"Initialize counter A with ");
	console->Printf(KTxt2);
	_LIT(KTxtIllegalString,"2a");
	console->Printf(KTxtIllegalString);
	TInt ret = counterA.SetFromString(KTxtIllegalString);
	_LIT(KTxt3,"\nSetting counter from string failed: non-numeric character detected\n");
	if (ret==ENonNumericString)
		console->Printf(KTxt3);
	
	RCounter counterB;
	counterB.Open(countserv);
	_LIT(KTxt4,"Initialize counter B with ");
	console->Printf(KTxt4);
	_LIT(KTxtLegalString,"100");
	console->Printf(KTxtLegalString);
	counterB.SetFromString(KTxtLegalString);

		// get initial counter values for both subsessions
	_LIT(KTxt5,"\nDefault increase/decrease is 1\n");
	console->Printf(KTxt5);
	console->Printf(KCommonFormat1, counterA.CounterValue());
	console->Printf(KCommonFormat2, counterB.CounterValue());

		// increase and decrease counters in both subsessions
	_LIT(KTxt6,"Increase counterA..\n");
	console->Printf(KTxt6);
	counterA.Increase();

	_LIT(KTxt7,"Increase counterA by 2..\n");
	console->Printf(KTxt7);
	counterA.IncreaseBy(2);
	
	_LIT(KTxt8,"Increase counterB..\n");
	console->Printf(KTxt8);
	counterB.Increase();
	
	_LIT(KTxt9,"Increase counterA by 7..\n");
	console->Printf(KTxt9);
	counterA.IncreaseBy(7);
	
	_LIT(KTxt10,"Increase counterB by 5..\n");
	console->Printf(KTxt10);
	counterB.IncreaseBy(5);
	
	_LIT(KTxt11,"Decrease counterA..\n");
	console->Printf(KTxt11);
	counterA.Decrease();
	
	_LIT(KTxt12,"Decrease counterB by 3..\n");
	console->Printf(KTxt12);
	counterB.DecreaseBy(3);

		// print final counter values.
		// Note counters are totally independent; increasing/decreasing 
	    // one has no effect on the other.
	console->Printf(KCommonFormat1, counterA.CounterValue());
	console->Printf(KCommonFormat2, counterB.CounterValue());
	TInt iSubsessions = countserv.ResourceCount();
	_LIT(KFormat3,"Resource count is.. %d \n");
    console->Printf(KFormat3, iSubsessions);

		//close subsessions
	_LIT(KTxt13,"Closing counterA..\n");
	console->Printf(KTxt13);
	counterA.Close();
	
		// If the user presses the end key here, the second counter subsession
		// will not be closed before the session is closed.
		// As a result the server panics the client.
	_LIT(KTxt14,"Press END to see what happens when a subsession is left open \n");
	console->Printf(KTxt14);
	_LIT(KTxtPressAnotherKey,"[press another key to continue normally]");
	console->Printf(KTxtPressAnotherKey);
	TKeyCode code =console->Getch();
	_LIT(KTxtNewLine,"\n");
	console->Printf(KTxtNewLine);
	if (code != EKeyEnd)
		{
		counterB.Close();
		}

		// close session with server
	countserv.ResourceCountMarkEnd();
	countserv.Close();
	}

