// NewLC.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.

// Example shows use of the NewLC() static function.

// NOTE: the structure of this example is different to standard E32 examples


#include <e32cons.h>

  // All messages written to this
LOCAL_D CConsoleBase* console;
  
  // Flag which determines whether the doSomething() member function
  // of the CExample class should leave when called.
LOCAL_D TBool leaveFlag = ETrue;

  // Parameter for __UHEAP_SETFAIL
  // Allocation guaranteed to fail at this number of allocation attempts;
  // i.e. if set to n, allocation fails on the nth attempt. 
  // NB only used in debug mode
#ifdef _DEBUG
LOCAL_D TInt allocFailNumber = 1;
#endif
  
  // Function prototypes
LOCAL_C void doExampleL();      
LOCAL_C void callExampleL();



//////////////////////////////////////////////////////////////////////////////
//
// -----> CExample (definition)
//
// The class is used by the example code
//
//////////////////////////////////////////////////////////////////////////////
class CExample : public CBase
	{
public :
	static CExample* NewLC(TInt aVal);
	void DoSomethingL();
public :
	TInt iInt;
	};


//////////////////////////////////////////////////////////////////////////////
//
// -----> CExample (implementation)
//
//////////////////////////////////////////////////////////////////////////////
CExample* CExample::NewLC(TInt aVal)
	{
	CExample* self = new (ELeave) CExample;
	CleanupStack::PushL(self);
	self->iInt = aVal;
	return self;
	}


void CExample::DoSomethingL() 
	{
	  // Leave if the global flag is set
	if (leaveFlag)
		{
		_LIT(KMsgLeaving,"DoSomethingL leaving.\n");
		console->Printf(KMsgLeaving);
		User::Leave(KErrGeneral);	 	
		}
	_LIT(KFormat1,"Value of iInt is %d.\n");
	console->Printf(KFormat1,iInt);
	}

//////////////////////////////////////////////////////////////////////////////
//
// Main function called by E32
//
//////////////////////////////////////////////////////////////////////////////
GLDEF_C TInt E32Main()
    {
	  // Get cleanup stack
	CTrapCleanup* cleanup=CTrapCleanup::New();

	  // Some more initialization, then do the example
	TRAPD(error,callExampleL());
	  
	  // callExampleL() should never leave.
	_LIT(KMsgPanicEpoc32ex,"EPOC32EX");
	__ASSERT_ALWAYS(!error,User::Panic(KMsgPanicEpoc32ex,error));

	  // destroy the cleanup stack
	delete cleanup;
	
	  // return
	return 0;
    }


//////////////////////////////////////////////////////////////////////////////
//
//
//
//////////////////////////////////////////////////////////////////////////////
LOCAL_C void callExampleL() 
    {
	  // Initialize and call the example code under cleanup stack.
	_LIT(KMsgExampleCode,"Symbian OS Example Code");
	console = Console::NewL(KMsgExampleCode,TSize(KConsFullScreen,KConsFullScreen));
	  // Put console onto the cleanup stack.
	CleanupStack::PushL(console);

	  // Perform the example function under the protection of a 
	  // TRAP harness.
	TRAPD(error,doExampleL());
	_LIT(KMsgOK,"ok");
	_LIT(KFormat2,"failed: leave code = %d");
	if (error)
		console->Printf(KFormat2,error);
	else
		console->Printf(KMsgOK);
	  
	  // Continue
	_LIT(KMsgPressAnyKey," [press any key]");
	console->Printf(KMsgPressAnyKey);
	console->Getch();

	  // Remove the console object from the cleanupstack
	  // and destroy it. 
	CleanupStack::PopAndDestroy();
    }


//////////////////////////////////////////////////////////////////////////////
//
// Do the example
//
// Enriched example UsingNewL by using NewLC() instead of NewL().
// The function NewLC() both allocates a CExample object and pushes
// the object onto the cleanup stack
//
//////////////////////////////////////////////////////////////////////////////
void doExampleL()
	{
	  // Memory alloc fails on the 'allocFailNumber' attempt. 
	__UHEAP_SETFAIL(RHeap::EDeterministic,allocFailNumber);
	  // Allocate and push onto the cleanup stack - leave if 
	  // allocation fails.
	CExample* myExample = CExample::NewLC(5);
	  // Do something that can leave.
	myExample->DoSomethingL();
	  // Pop from the cleanup stack and destroy
	CleanupStack::PopAndDestroy();
	}








