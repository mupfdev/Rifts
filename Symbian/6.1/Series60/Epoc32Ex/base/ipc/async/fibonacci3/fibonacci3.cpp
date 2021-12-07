// Fibonacci3.CPP
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//


// Example wraps a console in an active object and performs the 
// Fibonacci calculation as a background active object.
//

//
//  Fibonacci Active Objects example
//
#include <e32cons.h>
#include <e32base.h>
#include <e32std.h>

////testing only - can remove this & ModifyLedMask calls
//nclude <e32hal.h>


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
// -----> TFibonacciEngine (definition)
//
// This class provides the fibonacci calculation engine
//
//////////////////////////////////////////////////////////////////////////////

class TFibonacciEngine
	{
public:
	TFibonacciEngine::TFibonacciEngine() ;
	void StartCalculate (TInt aTerms) ;
	void StepCalculate () ;
	
	TUint iResult ;

	enum TEngineState {eInactive, eCalculating, eCompleted}   ;
	TEngineState iState ;

private:
	TUint iCurrentTotal ;
	TUint iPreviousTotal ;
	TInt iTermsLeftToDo ;
	} ;


//////////////////////////////////////////////////////////////////////////////
//
// -----> CFibonacciApplication (definition)
//
// This class encapsulates the fibonacci thread that runs the fibonacci engine
//
//////////////////////////////////////////////////////////////////////////////

class CFibonacciApplication : public CActive
	{
public:
	CFibonacciApplication(CConsoleBase* aConsole, TFibonacciEngine* aFibonacciEngine) ;
	CFibonacciApplication::~CFibonacciApplication() ;

	void CalculateFibonacci(TInt aIterations) ;

private:
	void DoCancel() ;
	void RunL() ;

private:
	CConsoleBase* iConsole ;
	TFibonacciEngine* iFibonacciEngine ;
	} ;


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
	CFibonacciKeyHandler(   CConsoleBase* aConsole, 
							CFibonacciApplication* aApplication) ;
	void ConstructL();

	  // Static construction
	static CFibonacciKeyHandler* NewLC(CConsoleBase* aConsole, CFibonacciApplication* aHandler) ;

	  // service request
	void ProcessKeyPress(TChar aChar) ;

private:
	CConsoleBase* iConsole ;
	CFibonacciApplication* iApplication ;
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

CFibonacciKeyHandler::CFibonacciKeyHandler(CConsoleBase* aConsole, CFibonacciApplication* aApplication)
	: CActiveConsole(aConsole)
	  // construct zero-priority active object
	{
	iConsole = aConsole ;
	iApplication = aApplication ;

	__DECLARE_NAME(_S("CFibonacciApplication"));
	  // Add to active scheduler
	CActiveScheduler::Add(this);
	  // Make this the active object
	((CExampleScheduler*)(CActiveScheduler::Current()))->SetActiveObject(this);
	} 


void CFibonacciKeyHandler::ProcessKeyPress(TChar aChar)
	{
	  // if key is ESC, cancel any outstanding request & stop the scheduler
	if (aChar == EKeyEscape)
		{
		CActiveScheduler::Stop();
		return;
		}

	  // If key is "f" or "F", issue a Fibonacci request if none is in progress
	if (aChar == 'f' || aChar == 'F') 
		{
		if (!(iApplication->IsActive()))
			{
			_LIT(KTxtReturnTermNumber,"\nENTER selects num\nUP    arrow increases num\nDOWN  arrow decreases num\n\n");
			TInt iterations = GetValueFromKeyboard(5,1,2,46, KTxtReturnTermNumber, iConsole) ;
			iApplication->CalculateFibonacci(iterations);
			}
		else
			{
			_LIT(KTxtAlreadyInProgress,"[Already in progress]");
			iConsole->Printf(KTxtAlreadyInProgress);
			}
		return;
		}

      // If key is "c" or "C", cancel any outstanding request   
	if (aChar == 'c' || aChar == 'C')
		{
		_LIT(KTxtCancelFibonacci,"\nCancelling Fibonacci....  \n");
		iConsole->Printf(KTxtCancelFibonacci);
		iApplication->Cancel();
		iConsole->Printf(KTxtMainInstructions);
		return;
		}
	
	_LIT(KTxtNotRecognised,"\nUnwanted key pressed");
	iConsole->Printf(KTxtNotRecognised);
	iConsole->Printf(KTxtMainInstructions);
	}


//////////////////////////////////////////////////////////////////////////////
//
// -----> CFibonacciApplication (implementation)
//
//////////////////////////////////////////////////////////////////////////////

CFibonacciApplication::CFibonacciApplication(CConsoleBase* aConsole, TFibonacciEngine* aFibonacciEngine)
//
// Constructor
//
	: CActive(EPriorityStandard)
	{
	iConsole = aConsole ;
	iFibonacciEngine = aFibonacciEngine ;
	CActiveScheduler::Add(this);
	__DECLARE_NAME(_S("CFibonacciApplication"));
	};


// destructor
CFibonacciApplication::~CFibonacciApplication() 
	{
	// cancel any requests and tell server 
	Cancel() ;
	}


void CFibonacciApplication::DoCancel() 
	{
	// cancel the active object request 
	iFibonacciEngine->iState = TFibonacciEngine::eInactive ;
	}



// initiate a request
void CFibonacciApplication::CalculateFibonacci(TInt aIterations)
	{
	// initialize engine
	// no neeed to set iStatus to KRequestPending, as request completes below
	iFibonacciEngine->StartCalculate(aIterations) ;

	// schedule the request
	SetActive() ;

	// send signal that this request has completed
	TRequestStatus* status = &iStatus ;
	User::RequestComplete(status, KErrNone) ;
	}



void CFibonacciApplication::RunL() 
// implements a simple state engine: {eInactive, eCalculating, eCompleted}
	{
	if (iFibonacciEngine->iState == TFibonacciEngine::eInactive )
		{
		_LIT(KTxtEngineNotInitialized,"Engine not initialized");
		User::Panic(KTxtEngineNotInitialized, KErrNotReady) ;
		}
	else if (iFibonacciEngine->iState == TFibonacciEngine::eCalculating )
		{               
		// unnecessary - just provides feedback on progression of the calculation
		_LIT(KTxtDot,".");
		iConsole->Printf(KTxtDot) ;

		// no neeed to set iStatus to KRequestPending, as request completes below

		// request next step
		iFibonacciEngine->StepCalculate() ;

		// schedule request
		SetActive() ;

		// send signal that this request has completed
		TRequestStatus* status = &iStatus ;
		User::RequestComplete(status, KErrNone) ;
		}
	else if (iFibonacciEngine->iState == TFibonacciEngine::eCompleted )
		{
		// finished calculation: print result and reset state engine
		_LIT(KFormat2,"\n    Result : %u \n");  //not used
		iConsole->Printf(KFormat2, iFibonacciEngine->iResult) ; 
		iConsole->Printf(KTxtMainInstructions) ; 
		iFibonacciEngine->iState = TFibonacciEngine::eInactive ;
		}
	}



//////////////////////////////////////////////////////////////////////////////
//
// -----> TFibonacciEngine (implementation)
//
//////////////////////////////////////////////////////////////////////////////
TFibonacciEngine::TFibonacciEngine() 
	{
	iState = eInactive ;
	}


void TFibonacciEngine::StartCalculate (TInt aTerms) 
	{
	// initialise all internal variables to initial state
	iCurrentTotal = 1 ;
	iPreviousTotal = 0 ;
	iResult = 0 ;
	iTermsLeftToDo = aTerms - 1 ;   // first step completed in variable initialization
	iState = eCalculating ;
	}



void TFibonacciEngine::StepCalculate () 
	{
	// use LEDs to give some feedback on whether calculation steps are running
//UerHal::ModifyLedMask(KLedMaskGreen1,KLedMaskRed1);

	// if full calculation not yet complete, but in progress (i.e. not cancelled)
	if (--iTermsLeftToDo > 0 && iState == eCalculating)     
		{
		// calculate next number in series
		TInt newTotal = iCurrentTotal + iPreviousTotal ;

		// update internal variables
		iPreviousTotal = iCurrentTotal ;
		iCurrentTotal = newTotal ;

		// introduce a delay to make us a long-running service
		User::After(1000000) ;

		// not necessary, but allows running total to be used during the calculation
		// (say for putting values into a chart or graph)
		iResult = iCurrentTotal ;
		}
	else if (iTermsLeftToDo <= 0)
		{
		// flag that calculation has finished and ensure final result is available
		iState = eCompleted ;
		iResult = iCurrentTotal ;
		}

	// use LEDs to give some feedback on whether calculation steps are running
//	UserHal::ModifyLedMask(KLedMaskRed1,KLedMaskGreen1);
	} 



/////////////////////////////////////////////////////////////////////////////////
// This section deals with initialisation and ensuring we have a console active
/////////////////////////////////////////////////////////////////////////////////

void doExampleL () ;

void SetupConsoleL();

GLDEF_C TInt E32Main()                          // main function called by E32
    {
	CTrapCleanup* cleanup=CTrapCleanup::New();              // get clean-up stack
	TRAPD(error,SetupConsoleL());                           // more initialization, then do example
	_LIT(KTxtFibonacciExampleError,"Fibonacci example error");
	__ASSERT_ALWAYS(!error,User::Panic(KTxtFibonacciExampleError,error));
	delete cleanup;                                         // destroy clean-up stack
	return 0;                                                                               // and return
    }

void SetupConsoleL()                             // initialize and call example code under cleanup stack
    {
	_LIT(KTxtFibActObjBackground,"Background Active Object");
	console=Console::NewL(KTxtFibActObjBackground, TSize(KConsFullScreen,KConsFullScreen));
	CleanupStack::PushL(console);
	console->Printf(KTxtMainInstructions) ;
	TRAPD(error, doExampleL());                                                     // perform example function
	if (error)
		{
		_LIT(KFormat3,"failed: leave code=%d");
		console->Printf(KFormat3, error);
		}
	_LIT(KTxtPressAnyKey,"[Press any key to exit]");
	console->Printf(KTxtPressAnyKey);
	console->Getch();                                                               // get and ignore character
	CleanupStack::PopAndDestroy();                                  // close console
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
	CFibonacciApplication* fibApplication = new CFibonacciApplication(console, fibEngine);

	  // Create CFibonacciKeyHandler active object.
	CFibonacciKeyHandler* fibKeyHandler = new CFibonacciKeyHandler(console, fibApplication);

	  // issue initial request
	fibKeyHandler->RequestCharacter() ;
			
	// Main part of the program:
	//    wait loop that cycles until ActiveScheduler::Stop called
	CActiveScheduler::Start();

	// Remove from the cleanup stack and destroy exampleScheduler
	CleanupStack::PopAndDestroy(); 
	}


