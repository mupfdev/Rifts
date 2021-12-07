// AcceptPrintInput.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.

// Asynchronous keyboard processing with messenger program.
// A single CWriteKeyProcessor active object (derived from 
// class CActiveConsole) which accepts and prints keyboard
// input to a console.

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
// -----> CActiveConsole (definition)
//
// An abstract class which provides the facility to issue key requests. 
//
//////////////////////////////////////////////////////////////////////////////
class CActiveConsole : public CActive
	{
public:
	  // Construction
	CActiveConsole(CConsoleBase* aConsole);
	void ConstructL();

	  // Destruction
	~CActiveConsole();

	  // Issue request
	void RequestCharacter();
	
	  // Cancel request.
	  // Defined as pure virtual by CActive;
	  // implementation provided by this class.
	void DoCancel();

	  // Service completed request.
	  // Defined as pure virtual by CActive;
	  // implementation provided by this class,
	void RunL();

	  // Called from RunL() - an implementation must be provided
	  // by derived classes to handle the completed request
	virtual void ProcessKeyPress(TChar aChar) = 0; 
	  
protected:
	  // Data members defined by this class
	CConsoleBase* iConsole; // A console for reading from
	};


//////////////////////////////////////////////////////////////////////////////
//
// -----> CWriteKeyProcessor (definition)
//
// This class is derived from CActiveConsole. 
// Request handling: accepts input from the keyboard and outputs it 
// to the console.
//
//////////////////////////////////////////////////////////////////////////////
class CWriteKeyProcessor : public CActiveConsole
	{
public:
	  // Construction
	CWriteKeyProcessor(CConsoleBase* aConsole);

public:
	  // Static constuction
	static CWriteKeyProcessor *NewLC (CConsoleBase* aConsole);
	static CWriteKeyProcessor *NewL(CConsoleBase* aConsole);

public:
	  // Service request
	void ProcessKeyPress(TChar aChar);
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
	_LIT(KFormatString1,"%S \n");
	console->Printf(KFormatString1,&iGreeting);
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
// -----> CActiveConsole (implementation)
//
//////////////////////////////////////////////////////////////////////////////
CActiveConsole::CActiveConsole( CConsoleBase* aConsole) 
	: CActive(CActive::EPriorityUserInput)
	  // Construct high-priority active object
	{
	iConsole = aConsole;
	}

void CActiveConsole::ConstructL()
	{
	  // Add to active scheduler
	CActiveScheduler::Add(this);
	}

CActiveConsole::~CActiveConsole()
	{
	// Make sure we're cancelled
	Cancel();
	}

void  CActiveConsole::DoCancel()
	{
	iConsole->ReadCancel();
	}

void  CActiveConsole::RunL()
	{
	  // Handle completed request
	ProcessKeyPress(TChar(iConsole->KeyCode()));
	}

void CActiveConsole::RequestCharacter()
	{
	  // A request is issued to the CConsoleBase to accept a
	  // character from the keyboard.
	iConsole->Read(iStatus); 
	SetActive();
	}


//////////////////////////////////////////////////////////////////////////////
//
// -----> CWriteKeyProcessor (implementation)
//
//////////////////////////////////////////////////////////////////////////////
CWriteKeyProcessor::CWriteKeyProcessor(CConsoleBase* aConsole)
	: CActiveConsole(aConsole)
	  
	{};

CWriteKeyProcessor* CWriteKeyProcessor::NewLC(CConsoleBase* aConsole)
	{
	CWriteKeyProcessor* self=new (ELeave) CWriteKeyProcessor(aConsole);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CWriteKeyProcessor* CWriteKeyProcessor::NewL(CConsoleBase* aConsole)
	{
	CWriteKeyProcessor* self=NewLC(aConsole);
	CleanupStack::Pop();
	return self;
	}

void CWriteKeyProcessor::ProcessKeyPress(TChar aChar)
	{
	  // "Esc" character prints a new line and stops the scheduler
	_LIT(KTextEsc,"\n");
	if (aChar == EKeyEscape)
		{
		iConsole->Printf(KTextEsc);
		CActiveScheduler::Stop();
		return;
		}

	  // "Enter" prints a new line character
	  // An alphabetic or space is printed as a character;
	  // anything else is printed as an integer.
	if (aChar == EKeyEnter)
		iConsole->Printf(KTextEsc);
	else
		{
		_LIT(KFormatString2,"%c");
		_LIT(KFormatString3,"%d");
		if (aChar.IsAlphaDigit()|| aChar.IsSpace())
			iConsole->Printf(KFormatString2,TUint(aChar));
		else
			iConsole->Printf(KFormatString3,TUint(aChar));
		}

	  // Issue another request 
	RequestCharacter();
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

	  // Create a CWriteKeyProcessor active object
	_LIT(KTitleMsg,"A single CWriteKeyProcessor active object.\nIt accepts and prints keyboard input to the console.\nPress ESC to end.\n\n");
	console->Printf(KTitleMsg);
	CWriteKeyProcessor* keyProcesser = CWriteKeyProcessor::NewLC(console);

	  // Issue the first request
	keyProcesser->RequestCharacter();

	  // Main part of program is a wait loop
	  // This function completes when the scheduler stops
	CActiveScheduler::Start();

	  // Remove from the cleanup stack and destroy:
	  // 1. the CWriteKeyProcessor active object
	  // 2. exampleScheduler
	CleanupStack::PopAndDestroy(2); 
	}

