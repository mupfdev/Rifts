// TwoPhaseOOM.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
//
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
// -----> CCompound (definition)
//
//////////////////////////////////////////////////////////////////////////////
class CCompound : public CBase
  	{
public :
	virtual  ~CCompound();
	void     Display();
	static   CCompound* NewL(TInt aRoot,TInt aChild);
	static   CCompound* NewLC(TInt aRoot,TInt aChild);
private:
	void     ConstructL(TInt aRoot,TInt aChild);
private:
	TInt     iRoot;
	CSimple* iChild;
    };

//////////////////////////////////////////////////////////////////////////////
//
// -----> CCompound (implementation)
//
//////////////////////////////////////////////////////////////////////////////

				// Use two stage construction technique to 
				// prevent alloc heaven.
				// NB. due to use of cleanup stack, NewLC is
				// now the primitive, rather than NewL

				// NewLC with two stage construct
CCompound* CCompound::NewLC(TInt aRoot,TInt aChild) 
		{		// get new, leave if can't	
		CCompound* self=new (ELeave) CCompound;
		CleanupStack::PushL(self);
				// push onto cleanup stack (in 
				// case self->ConstructL leaves).
				// Use two-stage construct
 		self->ConstructL(aRoot,aChild);
		return self;
		}
				// version of NewLC which leaves 
				// nothing on the cleanup stack
CCompound* CCompound::NewL(TInt aRoot,TInt aChild) 
		{
		CCompound* self=NewLC(aRoot,aChild);
		CleanupStack::Pop();
		return self;
		}
				// NB. function may leave, 
				// as CSimple::NewL may leave
void CCompound::ConstructL(TInt aRoot,TInt aChild) 
		{
		iRoot = aRoot;
		iChild = CSimple::NewL(aChild);	 
		iChild->iVal = aChild;
		}				

void CCompound::Display() 
	{
	  // Display class member data on the console
	_LIT(KFormat4,"Root=%d. Child=%d.\n");
    console->Printf(KFormat4,iRoot,iChild->iVal);
	}
				
CCompound::~CCompound() 
	{
	_LIT(KMsgDestCCompound,"Destructing CCompound\n");
	console->Printf(KMsgDestCCompound);
	delete iChild;
	}


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
// Example to check robustness of class on OOM and attempt to provoke
// memory leaks (orphans).
//////////////////////////////////////////////////////////////////////////////
void doExampleL()
	{
	#if defined(_DEBUG)  //only ever used in debug mode
	TInt failValue = 5;
	#endif

	  // Startup the alloc failure tool to fail in the third cycle.
	  // To test for alloc heaven:
	  //
	  // An even value for 'failValue' should provoke memory leak,
	  // an odd value should not.
	__UHEAP_SETFAIL(RHeap::EDeterministic,failValue);
	
	for(TInt ii=1;ii<4;ii++)
		{
		  // Display status information
		_LIT(KFormat3,"Cycle %d.\n");
	   	console->Printf(KFormat3,ii);
		  // Create new instance 
		CCompound* myCompoundExample = CCompound::NewL(1,2);
		  // Display the instance
		myCompoundExample->Display();
		  // Destroy the instance
		delete myCompoundExample;
		} 
	}


