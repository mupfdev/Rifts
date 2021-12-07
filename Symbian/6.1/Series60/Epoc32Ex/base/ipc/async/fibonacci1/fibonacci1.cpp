// Fibonacci1.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.


// Example wraps a console in an active object.
// 
// Calculates Fibonacci number as chosen by the user. Note that, in this
// example, the calculation is done as part of the console active object's 
// RunL() and can take a long time to complete. It also means that nothing
// else can happen (including responding to keyboard events) until the 
// calculation is complete. 
//



#include <e32base.h>
#include <e32cons.h>
#include <e32std.h>


LOCAL_D CConsoleBase* console;

_LIT(KTxtMainInstructions,"\n\nPress 'F' to start\n      'ESC' to exit.\n");

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

	TInt iResult ;
	} ;


//////////////////////////////////////////////////////////////////////////////
//
// -----> CFibonacciApplication (definition)
//
// This class encapsulates the fibonacci calculation engine
//
//////////////////////////////////////////////////////////////////////////////

class CFibonacciApplication : public CActiveConsole
	{
public:
	CFibonacciApplication(CConsoleBase* aConsole) ;
	void ConstructL();

	  // Static construction
	static CFibonacciApplication* NewLC(CConsoleBase* aConsole) ;

	  // service request
	void ProcessKeyPress(TChar aChar) ;

private:
	CConsoleBase* iConsole ;
	TFibonacciEngine iFibonacciEngine ;
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
// CFibonacciApplication support routine
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
		if (input == 'c') value = -1;
		}
	while (input != EKeyEnter && input != 'c') ;

	return value ;
	}


//////////////////////////////////////////////////////////////////////////////
//
// -----> CFibonacciApplication (implementation)
//
//////////////////////////////////////////////////////////////////////////////

CFibonacciApplication::CFibonacciApplication(CConsoleBase* aConsole )
	: CActiveConsole(aConsole)
	  // construct zero-priority active object
	{
	iConsole = aConsole ;
	__DECLARE_NAME(_S("CFibonacciApplication"));
	} 


CFibonacciApplication* CFibonacciApplication::NewLC(CConsoleBase* aConsole )
	{
	CFibonacciApplication* self=new (ELeave) CFibonacciApplication(aConsole);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}


void CFibonacciApplication::ConstructL()
	{
	  // Add to active scheduler
	CActiveScheduler::Add(this);
	  // Make this the active object
	((CExampleScheduler*)(CActiveScheduler::Current()))->SetActiveObject(this);
	}


void CFibonacciApplication::ProcessKeyPress(TChar aChar)
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
		_LIT(KTxtReturnTermNumber,"\nENTER selects num\nUP    arrow increases num\nDOWN  arrow decreases num\nC     cancels\n\n");
		_LIT(KTxtCalculating,"\nCalculating...\n");
		_LIT(KFormat2,"\nResult : %u \n");
		_LIT(KTxtCancelled,"Cancelled");

		iConsole->Printf(KTxtStartingFibonacci);
		
		TInt iterations = GetValueFromKeyboard(5,1,2,46, KTxtReturnTermNumber, iConsole) ;
		if (iterations == -1)  // convenient if awkward but allows us to indicate a request to cancel.
			{
			iConsole->Printf(KTxtCancelled);
			iConsole->Printf(KTxtMainInstructions);
			return;
			}

		iConsole->Printf(KTxtCalculating);
		iFibonacciEngine.Calculate(iterations);
		
		iConsole->Printf(KFormat2, iFibonacciEngine.iResult) ;
		iConsole->Printf(KTxtMainInstructions);
		return;
		}

       // any other key ignore
	_LIT(KTxtNotRecognised,"\nUnwanted key pressed");
	iConsole->Printf(KTxtNotRecognised);
	iConsole->Printf(KTxtMainInstructions);
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
	_LIT(KTxtFibSingActObj,"Single Active Object");
	console=Console::NewL(KTxtFibSingActObj, TSize(KConsFullScreen,KConsFullScreen));
	CleanupStack::PushL(console);

	console->Printf(KTxtMainInstructions) ;
	TRAPD(error, doExampleL());					    // perform example function
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

	  // Create CFibonacciApplication active object.
	CFibonacciApplication* fibonacci = CFibonacciApplication::NewLC(console);

	  // issue initial request
	fibonacci->RequestCharacter() ;
			
	// Main part of the program:
	//    wait loop that cycles until ActiveScheduler::Stop called
	CActiveScheduler::Start();

	// Remove from the cleanup stack and destroy:
	// 1. the CFibonacciApplication active object.
	// 2. exampleScheduler
	CleanupStack::PopAndDestroy(); 
	CleanupStack::PopAndDestroy(); 
	}

