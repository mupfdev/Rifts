 // Fibonacci2.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.

// Example wraps a console in an active object and performs the 
// Fibonacci calculation in a separate thread.
//
// This is NOT the recommended way and serves only to compare with the 
// Fibonacci3 example which performs the calculation as
// a background active object.
//


#include <e32std.h>
#include <e32cons.h>
#include <e32base.h>

//
// Common literals
//
_LIT(KTxtFibThread,"FibThread");


LOCAL_D CConsoleBase* console;

_LIT(KTxtMainInstructions,"\n\nPress 'F' to start\n      'ESC' to exit\n      'C' to cancel, anytime\n");

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
// -----> CExampleScheduler (definition)
//
//////////////////////////////////////////////////////////////////////////////

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
// -----> TFibonacciEngine (definition)
//
// This class provides the fibonacci calculation engine
//
//////////////////////////////////////////////////////////////////////////////

class TFibonacciEngine
	{
public:
	void Calculate (TInt aTerms) ;

	TUint iResult ;
	} ;


//////////////////////////////////////////////////////////////////////////////
//
// -----> TFibonacciParameters (definition)
//
// This class provides for passing parameters to the thread 
//
//////////////////////////////////////////////////////////////////////////////

class TFibonacciParameters
	{
public:
	TInt iVar1 ;
	TAny* iVar2 ;
	TUint iResult ;
	} ;


//////////////////////////////////////////////////////////////////////////////
//
// -----> CFibonacciThreadHandler (definition)
//
// This class encapsulates the fibonacci thread that runs the fibonacci engine
//
//////////////////////////////////////////////////////////////////////////////

class CFibonacciThreadHandler : public CActive
	{
public:
	CFibonacciThreadHandler(CConsoleBase* aConsole, TFibonacciEngine* aFibonacciEngine) ;
	CFibonacciThreadHandler::~CFibonacciThreadHandler() ;

	void CalculateFibonacci(TInt aIterations) ;

private:
	void DoCancel() ;
	void RunL() ;
	static TInt FibonacciThread(TAny* aParameters) ;

private:
	CConsoleBase* iConsole ;
	TFibonacciParameters iFibonacciParameters ;
	TFibonacciEngine* iFibonacciEngine ;
	};


//////////////////////////////////////////////////////////////////////////////
//
// -----> CFibonacciKeyHandler (definition)
//
// This class encapsulates the fibonacci keyboard handler
//
//////////////////////////////////////////////////////////////////////////////

class CFibonacciKeyHandler : public CActiveConsole
	{
public:
	CFibonacciKeyHandler(	CConsoleBase* aConsole, 
							CFibonacciThreadHandler* iThreadHandler) ;
	void ConstructL();

	  // Static construction
	static CFibonacciKeyHandler* NewLC(CConsoleBase* aConsole, CFibonacciThreadHandler* aHandler) ;

	  // service request
	void ProcessKeyPress(TChar aChar) ;

private:
	CConsoleBase* iConsole ;
	CFibonacciThreadHandler* iThreadHandler ;
	};




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
	__DECLARE_NAME(_S("CActiveConsole"));

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





/////////////////////////////////////////////////////////////////////////////////
// CFibonacciKeyHandler support routine
//   uses up arrow & down arrow to change number, Enter to select
/////////////////////////////////////////////////////////////////////////////////

TInt GetValueFromKeyboard (TInt aInitial, TInt aStep, TInt lowerLimit, TInt upperLimit, const TDesC& aPrompt, CConsoleBase* aConsole)
	{
	TChar input ;
	TInt value = aInitial ;

	aConsole->Printf(aPrompt) ;
	do
		{
		aConsole->SetPos(0);
		_LIT(KFormat1,"%d  ");
		aConsole->Printf(KFormat1, value);
		input = aConsole->Getch() ;
		if (input == EKeyUpArrow && value < upperLimit) value = value + aStep ;
		if (input == EKeyDownArrow && value > lowerLimit) value = value - aStep ;
		}
	while (input != EKeyEnter) ;

	return value ;
	}


//////////////////////////////////////////////////////////////////////////////
//
// -----> CFibonacciKeyHandler (implementation)
//
//////////////////////////////////////////////////////////////////////////////


CFibonacciKeyHandler::CFibonacciKeyHandler(CConsoleBase* aConsole, CFibonacciThreadHandler* aThreadHandler )
	: CActiveConsole(aConsole)
	  // construct zero-priority active object
	{
	iConsole = aConsole ;
	iThreadHandler = aThreadHandler ;
	__DECLARE_NAME(_S("CFibonacciApplication"));
	  // Add to active scheduler
	CActiveScheduler::Add(this);
	  // Make this the active object
	((CExampleScheduler*)(CActiveScheduler::Current()))->SetActiveObject(this);
	} 


void CFibonacciKeyHandler::ProcessKeyPress(TChar aChar)
	{
	  // if key is ESC 
	  //   cancel any outstanding request
	  //   stop the scheduler
	if (aChar == EKeyEscape)
		{
		CActiveScheduler::Stop();
		return;
		}

	  // If key is "f" or "F"
	  //   cancel any outstanding request
	  //   issue a fibonacci request.
	if (aChar == 'f' || aChar == 'F') 
		{
		_LIT(KTxtStartingFibonacci,"\nStarting Fibonacci....  \n");
		iConsole->Printf(KTxtStartingFibonacci);
		_LIT(KTxtReturnTermNumber,"\nENTER selects num\nUP    arrow increases num\nDOWN  arrow decreases num\n\n");
		TInt iterations = GetValueFromKeyboard(5,1,2,46, KTxtReturnTermNumber, iConsole) ;
		iThreadHandler->CalculateFibonacci(iterations);
		return;
		}

      // If key is "c" or "C" 
	  //    cancel any outstanding request	
	if (aChar == 'c' || aChar == 'C')
		{
		_LIT(KTxtCancelFibonacci,"\nCancelling Fibonacci....  \n");
		iConsole->Printf(KTxtCancelFibonacci);
		iThreadHandler->Cancel();
		iConsole->Printf(KTxtMainInstructions);
		return;
		}

	_LIT(KTxtNotRecognised,"\nUnwanted key pressed");
	iConsole->Printf(KTxtNotRecognised);
	iConsole->Printf(KTxtMainInstructions);
	}


//////////////////////////////////////////////////////////////////////////////
//
// -----> CFibonacciThreadHandler (implementation)
//
//////////////////////////////////////////////////////////////////////////////

CFibonacciThreadHandler::CFibonacciThreadHandler(CConsoleBase* aConsole, TFibonacciEngine* aFibonacciEngine)
//
// Constructor
//
	: CActive(EPriorityStandard)
	{
	iConsole = aConsole ;
	iFibonacciEngine = aFibonacciEngine ;
	CActiveScheduler::Add(this);
	__DECLARE_NAME(_S("CFibonacciThreadHandler"));
	};


// destructor
CFibonacciThreadHandler::~CFibonacciThreadHandler() 
	{
	// cancel any requests and tell server 
	Cancel() ;
	}


void CFibonacciThreadHandler::DoCancel() 
	{
	// cancel the active object request 
	RThread thread ;
	thread.Open(KTxtFibThread) ;
	thread.Kill(KErrCancel) ;
	thread.Close() ;
	}


void CFibonacciThreadHandler::RunL() 
	{
	// handle requests - print out result and flag as handled (ie not cancelled)
	_LIT(KFormat2,"    Result : %u \n");  //not used
	iConsole->Printf(KFormat2, iFibonacciParameters.iResult) ;
	iConsole->Printf(KTxtMainInstructions);
	}


// initiate a request
void CFibonacciThreadHandler::CalculateFibonacci(TInt aIterations)
	{
	const KHeapSize = 0x800 ;
	
	_LIT(KTxtFibRequested,"\nFibonacci requested ...  ");
	iConsole->Printf(KTxtFibRequested);


	RThread thread ;

	// set up parameters to thread

	iFibonacciParameters.iVar1 = aIterations ;
	iFibonacciParameters.iVar2 = iFibonacciEngine ;

	// generate thread, leave if fails
	
  	TInt result = thread.Create(KTxtFibThread,(TThreadFunction)FibonacciThread, KDefaultStackSize,
  								KMinHeapSize, KHeapSize, &iFibonacciParameters, EOwnerThread) ;
  	User::LeaveIfError(result) ;

	// log on to thread -	sets iStatus to KRequestPending 
	//						requests notification of thread completion
	thread.Logon(iStatus) ;

	// give thread low priority 
	thread.SetPriority(EPriorityMuchLess) ;

	// resume thread (wake it up sometime after this function returns)
  	thread.Resume() ;

  	thread.Close() ;

	// ensure scheduler checks status 
	SetActive() ;
	
	_LIT(KTxtOK,"OK  \n");
	iConsole->Printf(KTxtOK);
	}


/////////////////////////////////////////////////////////////////////////////////
//  Thread routine that sorts out parameters & calls engine
/////////////////////////////////////////////////////////////////////////////////

TInt CFibonacciThreadHandler::FibonacciThread(TAny* aParameters)
	{
	// cast the parameters pointer
	TFibonacciParameters* parameters = (TFibonacciParameters*) aParameters ;

	// get variables from parameters class
	TInt iterations = parameters->iVar1 ;
	TFibonacciEngine* fibonacciEngine = (TFibonacciEngine*)parameters->iVar2 ;

	// call the engine
	fibonacciEngine->Calculate(iterations) ;

	// store result
	parameters->iResult = fibonacciEngine->iResult ;

	return KErrNone ;
}


//////////////////////////////////////////////////////////////////////////////
//
// -----> TFibonacciEngine (implementation)
//
//////////////////////////////////////////////////////////////////////////////

void TFibonacciEngine::Calculate (TInt aTerms) 
	{
	TInt iterations = aTerms ;

	TInt currentTotal = 1 ;
	TInt previousTotal = 0 ;
	_LIT(KTxtTooManyIterations,"Too many iterations");
	__ASSERT_ALWAYS(iterations<47,User::Panic(KTxtTooManyIterations,iterations));


	// if limit not yet reached
	while (iterations-- > 0)	
		{
		// calculate next number in series
		TInt newTotal = currentTotal + previousTotal ;

		// update variables
		previousTotal = currentTotal ;
		currentTotal = newTotal ;

		// introduce a delay
		User::After(1000000) ;
		}  

	iResult = currentTotal ;

//UserHal::ModifyLedMask(1,2);
	} 


/////////////////////////////////////////////////////////////////////////////////
// This section deals with initialisation and ensuring we have a console active
/////////////////////////////////////////////////////////////////////////////////

void doExampleL () ;

void SetupConsoleL();

GLDEF_C TInt E32Main()				// main function called by E32
    {
	CTrapCleanup* cleanup=CTrapCleanup::New();		// get clean-up stack
	TRAPD(error,SetupConsoleL());					// more initialization, then do example
	_LIT(KTxtFibonacciExampleError,"Fibonacci example error");
	__ASSERT_ALWAYS(!error,User::Panic(KTxtFibonacciExampleError,error));
	delete cleanup;									// destroy clean-up stack
	return 0;										// and return
    }

void SetupConsoleL()				 // initialize and call example code under cleanup stack
    {
	_LIT(KTxtFibActObjInThread,"Active Object and thread");
	console=Console::NewL(KTxtFibActObjInThread,TSize(KConsFullScreen,KConsFullScreen));
	CleanupStack::PushL(console);
	console->Printf(KTxtMainInstructions) ;
	TRAPD(error, doExampleL());							// perform example function
	if (error)
		{
		_LIT(KFormat3,"failed: leave code=%d");
		console->Printf(KFormat3, error);
		}
	_LIT(KTxtPressAnyKey,"[Press any key to exit]");
	console->Printf(KTxtPressAnyKey);
	console->Getch();								// get and ignore character
	CleanupStack::PopAndDestroy();					// close console
    }


//////////////////////////////////////////////////////////////////////////////
//
// Do the example
//
//////////////////////////////////////////////////////////////////////////////
void doExampleL()
    {
	  // Construct and install the active scheduler
	CExampleScheduler*  exampleScheduler = new (ELeave) CExampleScheduler;

	  // Push onto the cleanup stack
	CleanupStack::PushL(exampleScheduler);
	 
	  // Install as the active scheduler
	CActiveScheduler::Install(exampleScheduler);


	// Create TFibonacciEngine active object.
	TFibonacciEngine* fibEngine = new TFibonacciEngine ;

	  // Create CFibonacciThreadHandler active object.
	CFibonacciThreadHandler* fibThreadHandler = new CFibonacciThreadHandler(console, fibEngine);

	  // Create CFibonacciKeyHandler active object.
	CFibonacciKeyHandler* fibKeyHandler = new CFibonacciKeyHandler(console, fibThreadHandler);

	  // issue initial request
	fibKeyHandler->RequestCharacter() ;
			
	// Main part of the program:
	//    wait loop that cycles until ActiveScheduler::Stop called
	CActiveScheduler::Start();

	// Remove from the cleanup stack and destroy:
	CleanupStack::PopAndDestroy(); 
	}




