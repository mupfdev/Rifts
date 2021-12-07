// SimpleServer.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.

#include "ClientServer.h"
#include "SimpleServer.h"
#include <e32svr.h>
#include <e32math.h>
#include <e32uid.h>


//**********************************
//CCountServServer
//**********************************


CCountServServer::CCountServServer(TInt aPriority)
	: CServer(aPriority)
	{
	__DECLARE_NAME(_S("CCountServer"));
	}


// Create and start a new count server.
void CCountServServer::New()
	{
	CCountServServer *pS=new CCountServServer(EPriority);
	__ASSERT_ALWAYS(pS!=NULL,PanicServer(ESvrCreateServer));
	pS->StartL(KCountServerName);
	}


// Create a new server session.
CSharableSession *CCountServServer::NewSessionL(const TVersion &aVersion) const
	{
	// check we're the right version
	TVersion v(KCountServMajorVersionNumber,KCountServMinorVersionNumber,KCountServBuildVersionNumber);
	if (!User::QueryVersionSupported(v,aVersion))
		User::Leave(KErrNotSupported);
	// make new session
	RThread aClient = Message().Client();
	return CCountServSession::NewL(aClient, (CCountServServer*)this);
	}


//**********************************
//CCountServSession
//**********************************


// constructor - must pass client to CSession
CCountServSession::CCountServSession(RThread &aClient, CCountServServer * aServer)
	: CSession(aClient)
	{
	__DECLARE_NAME(_S("CCountServSession"));
	iCountSvr=aServer;
	}

CCountServSession* CCountServSession::NewL(RThread &aClient, CCountServServer * aServer)
	{
	return new(ELeave) CCountServSession(aClient,aServer);
	}


void CCountServSession::ServiceL(const RMessage& aMessage)
	{
	TRAPD(err,DispatchMessageL(aMessage));
	aMessage.Complete(err);
	}



// service a client request; test the opcode and then do appropriate servicing
void CCountServSession::DispatchMessageL(const RMessage &aMessage)
	{
	switch (aMessage.Function())
        {
	case ECountServSetFromString:
		SetFromStringL();
		return;
	case ECountServIncrease:
		Increase();
		return;
	case ECountServIncreaseBy:
		IncreaseBy();
		return;
	case ECountServDecrease:
		Decrease();
		return;
	case ECountServDecreaseBy:
		DecreaseBy();
		return;
	case ECountServReset:
		Reset();
		return;
	case ECountServValue:
		CounterValue();
		return;
	// we know about the stop request, but don't support it,
	// so return KErrNotSupported here
	case ECountServStop:
		return;
	// requests we don't understand at all are a different thing,
	// so panic the client here, this function also completes the message
	default:
		PanicClient(EBadRequest);
		return;
        }
	}


// Initialize the counter with the numeric equivalent of the descriptor contents
// This function is here to demonstrate reading from the client address space.
void CCountServSession::SetFromStringL()
	{
	TInt res;
	TReal decplaces = 0.0; // 0, 10, 100 etc,
	TInt32 decplacesAsInt;
	TInt adigit = 0; // next digit from string
	TInt digitvalue=0;// digit as integer
	TInt power = 0; // power of 10
	TInt initvalue =0; // value to initialize counter with
	const TAny* pD=Message().Ptr0();
	TInt desLen=Message().Client().GetDesLength(pD);
	HBufC* writeBuf=HBufC::New(desLen);
	TPtr initptr = writeBuf->Des();
	// read the contents of the client pointer into a TPtr.
	TRAP(res,Message().ReadL(pD,initptr));
	if (res!=KErrNone)
		PanicClient(EBadDescriptor);
	TInt i;
	//convert the descriptor into its numeric equivalent
	for( i = desLen -1; i >= 0; i-- )
		{
		adigit = initptr[i];
		if ((adigit <= '9') && (adigit >= '0'))
			{
			digitvalue = (adigit - '0');
			Math::Pow10(decplaces, power);
			Math::Int(decplacesAsInt, decplaces);
			initvalue +=(digitvalue*decplacesAsInt);
			power++;
			}
		else
			// leave if the descriptor contains non-numeric characters
			User::Leave(ENonNumericString);
		}
	// initialize the counter with the numeric value of the descriptor
	iCount = initvalue;
	}



// increase the session counter by default (1)
void CCountServSession::Increase()
	{
	iCount++;
	}

// increase the session counter by an integer
void CCountServSession::IncreaseBy()
	{
	iCount = iCount + Message().Int0();
	}


// decrease the session counter by default (1)
void CCountServSession::Decrease()
	{
	iCount--;
	}


// decrease the session counter by an integer
void CCountServSession::DecreaseBy()
	{
	iCount = iCount - Message().Int0();
	}


// reset the session counter
void CCountServSession::Reset()
	{
	iCount=0;
	}


// write the counter value to a descriptor in the client address space
// This function demonstrates writing to the client.
void CCountServSession::CounterValue()
	{
	TPckgBuf<TInt> p(iCount);
	Write(Message().Ptr0(),p);
	}


// panic the client
void CCountServSession::PanicClient(TInt aPanic) const
	{
	_LIT(KTxtServer,"CountServ server");
	Panic(KTxtServer,aPanic);
	}


// write to the client thread; if unsuccessful, panic the client
void CCountServSession::Write(const TAny* aPtr,const TDesC8& aDes,TInt anOffset)
	{
	TRAPD(ret,WriteL(aPtr,aDes,anOffset);)
	if (ret!=KErrNone)
		PanicClient(EBadDescriptor);
	}



//**********************************
//Global functions
//**********************************


// The count server thread.
GLDEF_C TInt CCountServServer::ThreadFunction(TAny* anArg)
	{
	
	// convert argument into semaphore reference
	RSemaphore& semaphore=*(RSemaphore *)anArg;

	// start scheduler and server
	CActiveScheduler *pA=new CActiveScheduler;
	__ASSERT_ALWAYS(pA!=NULL,PanicServer(EMainSchedulerError));
	CActiveScheduler::Install(pA);
	CCountServServer::New();
	// signal that we've started
	semaphore.Signal();
	// start fielding requests from clients
	CActiveScheduler::Start();
	// finished
	return(KErrNone);
	}


// DLL entry point
GLDEF_C TInt E32Dll(TDllReason /*aReason*/)
	{
	return(KErrNone);
   	}


// Panic the server
GLDEF_C void PanicServer(TCountServPanic aPanic)
	{
	_LIT(KTxtServerPanic,"Count server panic");
	User::Panic(KTxtServerPanic,aPanic);
	}


// Create the server thread
// This function is exported from the DLL and called from the client 
EXPORT_C TInt StartThread()
    {
	TInt res=KErrNone;
	// create server - if one of this name does not already exist
	TFindServer findCountServer(KCountServerName);
	TFullName name;
	if (findCountServer.Next(name)!=KErrNone) // we don't exist already
		{
		RThread thread;
		RSemaphore semaphore;
		semaphore.CreateLocal(0); // create a semaphore so we know when thread finished
		res=thread.Create(KCountServerName,   // create new server thread
			CCountServServer::ThreadFunction, // thread's main function
			KDefaultStackSize,
			KDefaultHeapSize,
			KDefaultHeapSize,
			&semaphore // passed as TAny* argument to thread function
			);

		if (res==KErrNone) // thread created ok - now start it going
			{
			thread.SetPriority(EPriorityNormal);
			thread.Resume(); // start it going
			semaphore.Wait(); // wait until it's initialized
			thread.Close(); // we're no longer interested in the other thread
			}
		else // thread not created ok
			{
			thread.Close(); // therefore we've no further interest in it
			}

		semaphore.Close();
		}
	// notify the kernel that a server has started.
	#if defined (__WINS__)
	UserSvr::ServerStarted();
	#endif

    return res;
    }
    
