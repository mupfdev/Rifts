// ComplexServer.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.

#include "ComplexClientAndServer.h"
#include "ComplexServer.h"
#include <e32svr.h>
#include <e32math.h>
#include <e32uid.h>


// DLL entry point

 GLDEF_C TInt E32Dll(TDllReason /*aReason*/)
	{
	return(KErrNone);
   	}


/*	CCountServServer class

	Represents the server
	Started with the first client connect call.
	Start includes setting up active scheduler, the server active object,
	and the object container index which produces object object containers for each session.
*/


 // utility - panic the server
void CCountServServer::PanicServer(TCountServPanic aPanic)
	{
	_LIT(KTxtCountServer,"CountServer");
	User::Panic(KTxtCountServer,aPanic);
	}


// start the server thread
// This is called from the client.
EXPORT_C TInt StartThread()
	{
	// check server not already started
	TFindServer findCountServer(KCountServerName);
	TFullName name;
	if (findCountServer.Next(name)==KErrNone)
		{ // found server already - bad news
		return KErrGeneral;
		}
	// create server thread
	RThread thread;
	RSemaphore threadStarted;
	threadStarted.CreateLocal(0);
	TInt res=thread.Create(
		KCountServerName, // name of thread
		CCountServServer::ThreadFunction, // thread function
		KDefaultStackSize,KDefaultHeapSize,KDefaultHeapSize,
		&threadStarted // parameter to thread function
		);

	if (res!=KErrNone)
		{
		thread.Close();
		return KErrGeneral;
		}
	// now start thread
	thread.SetPriority(EPriorityMuchMore); // set its priority
	thread.Resume(); // kick it into life
	//
	threadStarted.Wait(); // wait until it's got going
	// tidy up
	thread.Close(); // no longer interested in that thread
	threadStarted.Close(); // or semaphore
	// notify the kernel that a server has started.
	#if defined (__WINS__)
	UserSvr::ServerStarted();
	#endif
	// all well
    return KErrNone;
    }


// thread function; the active scheduler is installed and started here
TInt CCountServServer::ThreadFunction(TAny* aStarted)
	{
	// create cleanup stack
	if (CTrapCleanup::New()==NULL)
		PanicServer(ECreateTrapCleanup);
	// convert argument to semaphore
	RSemaphore& started=*(RSemaphore *)aStarted;
	// construct and install active scheduler
	CActiveScheduler* scheduler=new CActiveScheduler;
	__ASSERT_ALWAYS(scheduler,PanicServer(EMainSchedulerError));
	CActiveScheduler::Install(scheduler);
	// construct server, an active object
	TRAPD(err,CCountServServer::NewL());
	__ASSERT_ALWAYS(!err,PanicServer(ESvrCreateServer));
	// signal everything has started
	started.Signal(); // now started ok
	// start handling requests
	CActiveScheduler::Start();
	// should never get here!
	return KErrNone;
	}


// allocation and construction
CCountServServer* CCountServServer::NewL()
	{
	CCountServServer* self=new (ELeave) CCountServServer;
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop();
	self->StartL(KCountServerName);
	return self;
	}


// return a new object container
CObjectCon* CCountServServer::NewContainerL()
	{
	return iContainerIndex->CreateL();
	}


// C++ constructor - just pass priority to base CServer class
CCountServServer::CCountServServer()
	: CServer(ECountServerPriority)
	{
	__DECLARE_NAME(_S("CCountServServer"));
	}


// second-phase constructor; create the object container index.
void CCountServServer::ConstructL()
	{
	iContainerIndex=CObjectConIx::NewL();
	}


// destruction
CCountServServer::~CCountServServer()
	{
	// delete the object container index.
	delete iContainerIndex; 
	}


// Create a new client session for this server.
CSharableSession* CCountServServer::NewSessionL(const TVersion &aVersion) const
	{
	// check version is ok
	TVersion v(KCountServMajorVersionNumber,KCountServMinorVersionNumber,KCountServBuildVersionNumber);
	if (!User::QueryVersionSupported(v,aVersion))
		User::Leave(KErrNotSupported);
	// make new session
	RThread aClient= Message().Client();
	return CCountServSession::NewL(aClient,(CCountServServer*)this);
	}



/*	CCountServSession class

	Represents a server session
	Contains	a) an object container which provides objects (CCounter instances) with unique ids
				b) an object index which stores the objects for this session.		
*/


//CCountServSession - handles subsession, ie an individual counter
CCountServSession* CCountServSession::NewL(RThread& aClient, CCountServServer* aServer)
	{
	CCountServSession* self=new (ELeave) CCountServSession(aClient);
	CleanupStack::PushL(self);
	self->ConstructL(aServer);
	CleanupStack::Pop();
	return self;
	}


// C++ constructor
CCountServSession::CCountServSession(RThread& aClient)
	: CSession(aClient)
	{
	__DECLARE_NAME(_S("CCountServSession"));
	}


// second-phase C++ constructor
void CCountServSession::ConstructL(CCountServServer* aServer)
	{
	// second-phase construct base class
	CSession::CreateL(*aServer);
	iCountSvr=aServer;
	// create new object index
	iCounters=CObjectIx::NewL();
	// initialize the object container using the object container index in the server.
	iContainer=iCountSvr->NewContainerL();
	}


void CCountServSession::CloseSession() 
	{
	//the things deleted here could alternately be deleted in the destructor - but its probably better to
	//do it here.
	//delete the object index (this stores the objects for this session)
	delete iCounters;
	//delete the object container (this provides unique ids for the objects of this session )
	delete iContainer;
	}


// utility
// return a CCounter given a client's subsession handle
CCounter* CCountServSession::CounterFromHandle(TUint aHandle)
    {
	CCounter* counter = (CCounter*)iCounters->At(aHandle);
	if (counter == NULL)
		PanicClient(EBadSubsessionHandle); 
	return counter;
    }


// Handle messages for this session
// ServiceL() dispatches requests to the appropriate handler
// Some messages are handled by the session itself, and are
// implemented as CCountServSession member functions
// Some messages are handled by the subsession, and are
// implemented as CCounter member functions


// trap harness for dispatcher
void CCountServSession::ServiceL(const RMessage& aMessage)
	{
	TRAPD(err,DispatchMessageL(aMessage));
	aMessage.Complete(err);
	}


// dispatch to right handler
void CCountServSession::DispatchMessageL(const RMessage& aMessage)
	{
	// check for session-relative requests
	switch (aMessage.Function())
		{
	case ECountServCreateSubSession:
		NewCounterL();
		return;
	case ECountServCloseSession:
		CloseSession();
		return;
	case ECountServResourceCountMarkStart:
		ResourceCountMarkStart(); // cannot fail (can panic client!)
		return;
	case ECountServResourceCountMarkEnd:
		ResourceCountMarkEnd(); // cannot fail (can panic client!)
		return;
	case ECountServResourceCount:
		NumResources();
		return; 
		}
	// ok, it must be subsession relative
	CCounter* counter=CounterFromHandle(aMessage.Int3());
	switch (aMessage.Function())
        {
	case ECountServInitSubSession:
		counter->SetFromString(aMessage);
		return; 
	case ECountServCloseSubSession:
		counter->CloseCounter();
		return; 
	case ECountServIncrease:
		counter->Increase();
		return;
	case ECountServIncreaseBy:
		counter->IncreaseBy();
		return;
	case ECountServDecrease:
		counter->Decrease();
		return;
	case ECountServDecreaseBy:
		counter->DecreaseBy();
		return;
	case ECountServReset:
		counter->Reset();
		return;
	case ECountServValue:
		counter->CounterValue();
		return;
	default:
		PanicClient(EBadRequest);
		return;
        }
	}


// handlers for session-relative requests


// Create a new counter; pass back its handle via the message
void CCountServSession::NewCounterL()
	{
	// make a new counter object
	CCounter* counter=CCounter::NewL(this);
	// add object to object container to gererate unique id
	iContainer->AddL(counter);
	// add object to object index; this returns a unique handle so we can get it again
	TInt handle=iCounters->AddL(counter);
	// write the handle to client
	TPckg<TInt> handlePckg(handle);
	TRAPD(res,WriteL(Message().Ptr3(),handlePckg));
	if (res!=KErrNone)
		{
		iCounters->Remove(handle);
		PanicClient(EBadDescriptor);
		return;
		}
	// notch up another resource
	iResourceCount++;
	}


// delete a counter, by handle
void CCountServSession::DeleteCounter(TUint aHandle)
	{
	// panic if bad handle
	CCounter* counter = (CCounter*)iCounters->At(aHandle);
	if (counter == NULL)
		PanicClient(EBadCounterRemove); 
	iCounters->Remove(aHandle);
	// decrement resource count
	iResourceCount--;
	}


// panic the client
void CCountServSession::PanicClient(TInt aPanic) const
	{
	_LIT(KTxtCountServSess,"CCountServSession");
	Panic(KTxtCountServSess,aPanic);
		// CSession::Panic() panics client - we specify category
	}


// return the number of resources owned by the session
// required by CSession if derived class implements resource
// mark-start and mark-end protocol
TInt CCountServSession::CountResources()
	{
	return iResourceCount;
	}


void CCountServSession::NumResources()
	{

	TPckgBuf<TInt> countPckg(iResourceCount);
	TRAPD(r,Message().WriteL(Message().Ptr0(),countPckg));
	if (r!=KErrNone)
		{
		PanicClient(EBadDescriptor);
		}
	}


/*
	CCounter
	The representation of a subsession in the server; an object.
*/


// construction


//  creates a new counter
CCounter * CCounter::NewL(CCountServSession* aSession)
	{
	CCounter* self=new(ELeave) CCounter;
	CleanupStack::PushL(self);
	self->ConstructL(aSession);
	CleanupStack::Pop();
	return self;
	}


// set the counter's session pointer
void CCounter::ConstructL(CCountServSession *aSession)
	{
	iSession=aSession;
	}


// general utility

// Initialize the counter with the numeric equivalent of the descriptor contents
// This function is here to demonstrate reading from the client address space.
void CCounter::SetFromString(const RMessage &aMessage)
	{
	TInt res;
	TReal decplaces = 0.0; // 0, 10, 100 etc,
	TInt32 decplacesAsInt;
	TInt adigit = 0; // next digit from string
	TInt digitvalue=0;// digit as integer
	TInt power = 0; // power of 10
	TInt initvalue =0; // value to initialize counter with
	const TAny* pD=aMessage.Ptr0();
	TInt desLen=aMessage.Client().GetDesLength(pD);
	//HBufC8* writeBuf=HBufC8::New(desLen); 
	HBufC* writeBuf=HBufC::New(desLen);
	TPtr initptr = writeBuf->Des();
	// read the contents of the client pointer into a TPtr.
	TRAP(res,aMessage.ReadL(pD,initptr));
	if (res!=KErrNone)
		iSession->PanicClient(EBadDescriptor);
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


// increase the counter by default (1)
void CCounter::Increase()
	{
	iCount++;
	}


// increase the counter by an integer
void CCounter::IncreaseBy()
	{
	iCount+=Message().Int0();
	}


// decrease the session counter by default (1)
void CCounter::Decrease()
	{
	iCount--;
	}


// decrease the session counter by an integer
void CCounter::DecreaseBy()
	{
	iCount-=Message().Int0();
	}


// reset the session counter
void CCounter::Reset()
	{
	iCount=0;
	}


// write the counter value to a descriptor in the client address space
void CCounter::CounterValue()
	{
	TPckgBuf<TInt> countPckg(iCount);
	TRAPD(r,Message().WriteL(Message().Ptr0(),countPckg));
	if (r!=KErrNone)
		{
		iSession->PanicClient(EBadDescriptor);
		}
	}


// Close counter, delete from session
void CCounter::CloseCounter()
	{
	iSession->DeleteCounter(Message().Int3());
	}


// write to the client thread; if unsuccessful, panic the client
void CCountServSession::Write(const TAny* aPtr,const TDesC8& aDes,TInt anOffset)
	{
	TRAPD(ret,WriteL(aPtr,aDes,anOffset);)
	if (ret!=KErrNone)
		PanicClient(EBadDescriptor);
	}


// utility

// return message - get it from session
const RMessage& CCounter::Message() const
	{
	return iSession->Message();
	}
