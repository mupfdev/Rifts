// RunTillComplete.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.

// Asynchronous keyboard processing with messenger program.
// A single CMessageTimer active object which runs until completion.

#include "CommonFramework.h"

// panics
enum
	{
	EPanicAlreadyActive=1000,
	};


//////////////////////////////////////////////////////////////////////////////
//
// -----> CTimedMessenger (definition)
//
//////////////////////////////////////////////////////////////////////////////
class CTimedMessenger : public CTimer
  	{
public:
	  // Construction
	CTimedMessenger();
      // Destruction
	~CTimedMessenger();

public:
	  // Static construction
	static CTimedMessenger* NewLC(const TDesC& aGreeting,
		                          TInt aTicksRequested,
								  TInt aTicksInterval
								 );
	static CTimedMessenger* NewL(const TDesC& aGreeting,
		                         TInt aTicksRequested,
								 TInt aTicksInterval
								);

public:
	  // Second phase construction
	void ConstructL(const TDesC& aGreeting,
		            TInt aTicksRequested,
					TInt aTicksInterval
				   );

	  // issue request
	void IssueRequest(); 

	  // Cancel request
	  // Defined as pure virtual by CActive;
	  // implementation provided by this class.
	void DoCancel();

	  // service completed request.
	  // Defined as pure virtual by CActive;
	  // implementation provided by this class.
	void RunL();

public:
	  // data members defined by this class
	TBufC<20> iGreeting;   // Text of the greeting.
	TInt iTicksRequested;  // Total number of greetings CTimedMessenger
	                       // will emit.
	TInt iTicksInterval;   // Number of seconds between each greeting.
	TInt iTicksDone;       // Number of greetings issued so far.
	};


//////////////////////////////////////////////////////////////////////////////
//
// -----> CExampleScheduler (definition)
//
//////////////////////////////////////////////////////////////////////////////
class CExampleScheduler : public CActiveScheduler
	{
public:
	void Error (TInt aError) const;
	};


//////////////////////////////////////////////////////////////////////////////
//
// -----> CTimedMessenger (implementation)
//
//////////////////////////////////////////////////////////////////////////////
CTimedMessenger::CTimedMessenger()
	: CTimer(CActive::EPriorityStandard)
	  // Construct standard-priority active object
	{};

CTimedMessenger* CTimedMessenger::NewLC(const TDesC& aGreeting,
										TInt aTicksRequested,
										TInt aTicksInterval
									   )
	{
	CTimedMessenger* self=new (ELeave) CTimedMessenger;
	CleanupStack::PushL(self);
	self->ConstructL(aGreeting,aTicksRequested,aTicksInterval);
	return self;
	}

CTimedMessenger* CTimedMessenger::NewL(const TDesC& aGreeting,
				     				   TInt aTicksRequested,
									   TInt aTicksInterval
									  )
	{
	CTimedMessenger* self = NewLC(aGreeting,aTicksRequested,aTicksInterval);
	CleanupStack::Pop();
	return self;
	}

void CTimedMessenger::ConstructL(const TDesC& aGreeting,
								 TInt aTicksRequested,
								 TInt aTicksInterval
								)
	{
	  // Base class second-phase construction.
	CTimer::ConstructL();
	  // Set members from arguments
	iGreeting       = aGreeting;       // Set greeting text.
	iTicksRequested = aTicksRequested; // Ticks requested
	iTicksInterval  = aTicksInterval;  // Interval between ticks
	  // Add active object to active scheduler
	CActiveScheduler::Add(this); 
	}


CTimedMessenger::~CTimedMessenger()
	{
	  // Make sure we're cancelled
	Cancel();
	}

void CTimedMessenger::DoCancel()
	{
	  // Base class
	CTimer::DoCancel(); 
	  // Reset this variable - needed if the object is re-activated later
	iTicksDone = 0;
	  // Tell user
	_LIT(KMsgCancelled,"Outstanding Messenger request cancelled\n");
	console->Printf(KMsgCancelled); 
	}

void CTimedMessenger::IssueRequest()
	{
	  // There should never be an outstanding request at this point.
	_LIT(KMsgAlreadyActive,"Is already Active");
	__ASSERT_ALWAYS(!IsActive(),User::Panic(KMsgAlreadyActive,EPanicAlreadyActive));
	  // Request another wait
	CTimer::After( iTicksInterval*1000000);
	}

void CTimedMessenger::RunL()
	{
	  // Handle request completion
	  // One more tick done
	iTicksDone++;
	  // Print greeting
	_LIT(KFormatString,"%S \n");
	console->Printf(KFormatString,&iGreeting);
	  // Issue new request, or stop if we have reached the limit
	if (iTicksDone  < iTicksRequested)
		{
		IssueRequest();
		}
	else
		{
		_LIT(KMsgFinished,"Messenger finished \n");
		console->Printf(KMsgFinished);
		  // Reset this variable - needed if the object is re-activated later
		iTicksDone=0;
		  // Can now stop the active scheduler
		CActiveScheduler::Stop();
		}
	}


//////////////////////////////////////////////////////////////////////////////
//
// -----> CExampleScheduler (implementation)
//
//////////////////////////////////////////////////////////////////////////////
void CExampleScheduler::Error(TInt aError) const
	{
	_LIT(KMsgSchedErr,"CExampleScheduler-error");
	User::Panic(KMsgSchedErr,aError);
	}


//////////////////////////////////////////////////////////////////////////////
//
// Do the example
//
//////////////////////////////////////////////////////////////////////////////
LOCAL_C void doExampleL()
    {
	  // Construct and install the active scheduler
	CExampleScheduler*  exampleScheduler = new (ELeave) CExampleScheduler;

	  // Push onto the cleanup stack
	CleanupStack::PushL(exampleScheduler);

	  // Install as the active scheduler
	CActiveScheduler::Install(exampleScheduler); 

      // Create a CTimedMessenger active object which will emit 3 messages
	  // with an interval of 2 seconds between messages
	_LIT(KMsgExplanation,"A single CMessageTimer active object which runs until completion\n\n");
	console->Printf(KMsgExplanation);
	_LIT(KMsgGoodMorning,"Good Morning!");
	CTimedMessenger* myTimedMessage = CTimedMessenger::NewLC(KMsgGoodMorning,3,2);

	  // Issue the first request
	myTimedMessage->IssueRequest();

      // Main part of program is a wait loop
	  // This function completes when the scheduler stops
	CActiveScheduler::Start();

	  // Remove from the cleanup stack and destroy:
	  // 1. the CTimedMessenger active object
	  // 2. exampleScheduler
	CleanupStack::PopAndDestroy(2); 
	}

