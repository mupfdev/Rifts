// SimpleOOM.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.

// Example checks the robustness of a simple class on Out Of Memory (OOM)
 
// NOTE: the structure of this example is different to standard E32 examples


#include <e32cons.h>



  // All messages written to this
LOCAL_D CConsoleBase* console;
  
  // Function prototypes
LOCAL_C void doExampleL();      
LOCAL_C void callExampleL();


//////////////////////////////////////////////////////////////////////////////
//
// -----> CSimple (definition)
//
//////////////////////////////////////////////////////////////////////////////
class CSimple : public CBase
  	{
public :
	static CSimple* NewL(TInt aVal);
	static CSimple* NewLC(TInt aVal);
	void   Display();
protected: 
	CSimple(TInt aVal);
public: 
	TInt   iVal;
	};


//////////////////////////////////////////////////////////////////////////////
//
// -----> CSimple (implementation)
//
//////////////////////////////////////////////////////////////////////////////
CSimple* CSimple::NewL(TInt aVal) 
	{
	  // NB The NewL function uses the C++ constructor mechanism.
	CSimple* self=new (ELeave) CSimple(aVal);
	return self;
	}

				
CSimple* CSimple::NewLC(TInt aVal)
	{
	  // NewLC is enriched with a push to the cleanup stack
	CSimple* self=NewL(aVal); 	
	CleanupStack::PushL(self);
	return self;
	}

				
void CSimple::Display() 
	{
	  // Display class data member on the console.
	_LIT(KFormat1,"Value=%d.\n");
	console->Printf(KFormat1,iVal);
	}
 
CSimple::CSimple(TInt aVal) 
	: iVal(aVal)
	{}


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

	  // Mark for alloc heaven tool
	__UHEAP_MARK;			   

	  // Perform the example function under the protection of a 
	  // TRAP harness.
	TRAPD(error,doExampleL());
	
	  // Test the example for alloc heaven
	  __UHEAP_MARKEND;

	  // 
	_LIT(KMsgOK,"ok");
	_LIT(KFormat2,"Overall example Trap Harness failed: leave code=%d");
	if (error)
		console->Printf(KFormat2, error);
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
// Example checks the robustness of class on OOM
//////////////////////////////////////////////////////////////////////////////
void doExampleL()
	{
	  // Start up the allocation failure tool to fail 
	  // in the third cycle (arg=3 as there is 1 new
	  // per cycle)
	__UHEAP_SETFAIL(RHeap::EDeterministic,3);
	
	for(TInt ii=1;ii<4;ii++)
		{
		  // Display status information
		_LIT(KFormat3,"Cycle %d.\n");
		console->Printf(KFormat3,ii);
		  // Create new instance
		CSimple* mySimpleExample = CSimple::NewL(2);
		  // Display the instance
		mySimpleExample->Display();
		  // Destroy the instance
		delete mySimpleExample;
		}
	}



