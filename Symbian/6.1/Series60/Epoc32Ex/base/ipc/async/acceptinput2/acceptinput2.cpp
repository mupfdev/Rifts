// AcceptInput2.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.

// Asynchronous keyboard processing with messenger program.
// A single CKeyMessengerProcessor active object (derived from
// class CActiveConsole) which accepts input from keyboard, but does not
// print it.
// This object contains a CMessageTimer object which it activates if the
// user inputs the character "m" and cancelled if the user inputs "c" .
// All keyboard requests are issued from the active scheduler.


#include "CommonFramework.h"

//
// Common literal text
//
_LIT(KTxtNewLine,"\n");


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
class CActiveConsole;
class CExampleScheduler : public CActiveScheduler
	{
public:
	void Error (TInt aError) const;
	void WaitForAnyRequest();
	void SetActiveObject(CActiveConsole* aActiveConsole);
private:
	  // data members defined for this class
	CActiveConsole* iActiveConsole;
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
	_LIT(KTxtOutMessReqCancelled,"Outstanding Messenger request cancelled\n");
	console->Printf(KTxtOutMessReqCancelled); 
	}

void CTimedMessenger::IssueRequest()
	{
	  // There should never be an outstanding request at this point.
	_LIT(KTxtIsAlreadyActive,"Is already Active");
	__ASSERT_ALWAYS(!IsActive(),User::Panic(KTxtIsAlreadyActive,EPanicAlreadyActive));
	  // Request another wait
	CTimer::After( iTicksInterval*1000000);
	}

void CTimedMessenger::RunL()
	{
	  // Handle request completion
	  // One more tick done
	iTicksDone++;
	  // Print greeting
	_LIT(KFormat1,"%S \n");
	console->Printf(KFormat1,&iGreeting);
	  // Issue new request, or stop if we have reached the limit
	if (iTicksDone  < iTicksRequested)
		{
		IssueRequest();
		}
	else
		{
		_LIT(KTxtMessengerFinished,"Messenger finished \n");
		console->Printf(KTxtMessengerFinished);
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
	_LIT(KTxtSchedulerError,"CExampleScheduler - error");
	User::Panic(KTxtSchedulerError,aError);
	}


void CExampleScheduler::WaitForAnyRequest()
	{
	if (!(iActiveConsole->IsActive()))
		iActiveConsole->RequestCharacter();	
	CActiveScheduler::WaitForAnyRequest();
	}

void CExampleScheduler::SetActiveObject(CActiveConsole* aActiveConsole)
	{
	iActiveConsole = aActiveConsole;
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
	  // Construct zero-priority active object
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
	if (aChar == EKeyEscape)
		{
		iConsole->Printf(KTxtNewLine);
		CActiveScheduler::Stop();
		return;
		}

	  // "Enter" prints a new line character
	  // An alphabetic or space is printed as a character;
	  // anything else is printed as an integer.
	if (aChar == EKeyEnter)
		iConsole->Printf(KTxtNewLine);
	else
		{
		_LIT(KFormat2,"%c");
		_LIT(KFormat3,"%d");
		if (aChar.IsAlphaDigit()|| aChar.IsSpace())
			
			iConsole->Printf(KFormat2,TUint(aChar));
		else
			iConsole->Printf(KFormat3,TUint(aChar));
		}

	  // Issue another request 
	RequestCharacter();
	}


//////////////////////////////////////////////////////////////////////////////
//
// -----> CMessageKeyProcessor (definition)
//
// This class is derived from CActiveConsole. 
// Request handling:
//   if key is "m", a message timer request is issued.
//   if key is "c", any outstanding message timer request is cancelled.
//   If key is ESC, the wait loop is terminated.
//
//////////////////////////////////////////////////////////////////////////////
class CMessageKeyProcessor : public CActiveConsole
	{
public:
	  // Construction
	CMessageKeyProcessor(CConsoleBase* aConsole, CTimedMessenger* iMessenger);
	void ConstructL();

public:
	  // Static construction
	static CMessageKeyProcessor* NewLC(CConsoleBase* aConsole,
		                               CTimedMessenger* iMessenger
									  );
	static CMessageKeyProcessor* NewL(CConsoleBase* aConsole,
		                              CTimedMessenger* iMessenger
									 );

public:
	  // service request
	void ProcessKeyPress(TChar aChar);

private:
	  // Data members defined by this class
	CTimedMessenger* iMessenger;
	};

//////////////////////////////////////////////////////////////////////////////
//
// -----> CMessageKeyProcessor (implementation)
//
//////////////////////////////////////////////////////////////////////////////
CMessageKeyProcessor::CMessageKeyProcessor(CConsoleBase* aConsole,
										   CTimedMessenger* aMessenger
										  )
	: CActiveConsole(aConsole)
	  // construct zero-priority active object
	{
	iMessenger = aMessenger;
	} 

CMessageKeyProcessor* CMessageKeyProcessor::NewLC(CConsoleBase* aConsole,
												  CTimedMessenger* aMessenger
												 )
	{
	CMessageKeyProcessor* self=new (ELeave) CMessageKeyProcessor(aConsole,
		                                                         aMessenger
																);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CMessageKeyProcessor* CMessageKeyProcessor::NewL(CConsoleBase* aConsole,
												 CTimedMessenger* aMessenger
												)
	{
	CMessageKeyProcessor* self = NewLC(aConsole, aMessenger);
	CleanupStack::Pop();
	return self;
	}

void CMessageKeyProcessor::ConstructL()
	{
	  // Add to active scheduler
	CActiveScheduler::Add(this);
	  // Make this the active object
	((CExampleScheduler*)(CActiveScheduler::Current()))->SetActiveObject(this);
	}

void CMessageKeyProcessor::ProcessKeyPress(TChar aChar)
	{
	  // if key is ESC 
	  //   cancel any outstanding request
	  //   stop the scheduler
	if (aChar == EKeyEscape)
		{
		iMessenger->Cancel();
		CActiveScheduler::Stop();
		return;
		}

	  // If key is "m" or "M"
	  //   cancel any outstanding request
	  //   reset the tick counter
	  //   issue a message timer request.
	if (aChar == 'm' || aChar == 'M') 
		{
		_LIT(KTxtStartingMess,"Starting Messenger....  \n");
		iConsole->Printf(KTxtStartingMess);
		iMessenger->Cancel();
		iMessenger ->IssueRequest();
		}

      // If key is "c" or "C" 
	  //    cancel any outstanding request	
	if (aChar == 'c' || aChar == 'C')
		iMessenger->Cancel();
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

	  // Create a CTimedMessenger active object which will emit
	  // 3 messages with an interval of 2 seconds between messages.
	_LIT(KTxtGoodMorning,"Good Morning!");
	CTimedMessenger* messenger = CTimedMessenger::NewLC(KTxtGoodMorning, 3, 2);

	  // Create aCMessageKeyProcessor active object.
	_LIT(KTxtMain1,"A single CKeyMessengerProcessor active object ");
	_LIT(KTxtMain2,"Active scheduler renews request.\n");
	_LIT(KTxtMain3,"Press 'm' to activate messenger; Press 'c' to cancel it.\n");
	_LIT(KTxtMain4,"Press ESC to end.\n\n");
	console->Printf(KTxtMain1);
	console->Printf(KTxtMain2);
	console->Printf(KTxtMain3);
	console->Printf(KTxtMain4);
	CMessageKeyProcessor::NewLC(console,messenger);
			
	  // Main part of the program is a wait loop
	CActiveScheduler::Start();

	// Remove from the cleanup stack and destroy:
	// 1. the CTimedMessenger active object
	// 2. the CMessageKeyProcessor active object.
	// 3. exampleScheduler
	CleanupStack::PopAndDestroy(3); 
	}



