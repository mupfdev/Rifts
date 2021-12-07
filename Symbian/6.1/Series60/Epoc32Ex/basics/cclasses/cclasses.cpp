// CClasses.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.

#include "CommonFramework.h"

// start of real example

// #include specific files

// class with single-phase construction, NewL and NewLC

class COnePhaser : public CBase {
public: // data
	TInt iInt1; // one integer
	TInt iInt2; // another integer
public: // functions
	// construct/destruct
	static COnePhaser* NewL()
		{ // construct and leave if error
		return new (ELeave) COnePhaser; // new COnePhaser, C++ constructor
		};
	static COnePhaser* NewLC()
		{ // construct, leave if error, else push to clean-up stack
		COnePhaser* self=COnePhaser::NewL(); // construct
		CleanupStack::PushL(self); // push to clean-up stack
		return self; // and return new object
		};
	// other functions
	void Print()
		{
		_LIT(KFormat1,"COnePhaser {TInt %d, TInt %d}");
		console->Printf(KFormat1, iInt1, iInt2);
		}
protected: // functions
	// construct
	COnePhaser()
		{ // standard C++ constructor, because it cannot leave
		iInt1=3; // set first int to 3
		// iInt2=0; // unnecessary
		}
	};

// class with two-phase construction

class CTwoPhaser : public CBase {
public: // data
	TInt iInt1; // one integer
	TInt iInt2; // another integer
	RTimer iTimer; // a resource
	COnePhaser* iOnePhaser; // another CBase object
public: // functions
	// construct/destruct
	static CTwoPhaser* NewLC(TInt aInt1)
		{ // construct and leave on the clean-up stack
		CTwoPhaser* self=new (ELeave) CTwoPhaser; // new CTwoPhaser, initialized to binary zeroes
		CleanupStack::PushL(self); // push to clean-up stack
		self->ConstructL(aInt1); // construct
		return self; // return new object
		};
	static CTwoPhaser* NewL(TInt aInt1)
		{ // construct and don't leave on clean-up stack
		CTwoPhaser* self=CTwoPhaser::NewLC(aInt1); // construct and leave on clean-up stack
		CleanupStack::Pop(); // pop from clean-up stack
		return self; // return new object
		};
	virtual ~CTwoPhaser()
		{
		delete iOnePhaser; // just destroy anything we point to
		iTimer.Close(); // close timer
		}
	// other functions
	void Print()
		{
		_LIT(KFormat2,"CTwoPhaser {TInt %d, TInt %d, RTimer, ");
		console->Printf(KFormat2, iInt1, iInt2);
		iOnePhaser->Print();
		_LIT(KtxtCloseCurly,"}");
		console->Printf(KtxtCloseCurly);
		}
protected: // functions
	// construct support
	void ConstructL(TInt aInt1)
		{ // do the work involved in construction
		iInt1=aInt1; // assign iInt1 from argument
		User::LeaveIfError(iTimer.CreateLocal()); // initialize timer
		iOnePhaser=COnePhaser::NewL(); // make a new one-phaser
		}
	};

// abstract class derived from CBase

class CAbstract : public CBase
	{
public: // data
	CTwoPhaser* iTwoPhaser; // a contained object
public: // functions
	void SomeFunction(TInt aInt)
		{ // request some function
		_LIT(KTxtbeginSomeFunction,"beginning to do SomeFunction()\n");
		console->Printf(KTxtbeginSomeFunction);
		DoSomeFunction(aInt); // invoke virtual function
		_LIT(KTxtfinishSomeFunction,"finished doing SomeFunction()\n");
		console->Printf(KTxtfinishSomeFunction);
		}
	virtual ~CAbstract()
		{
		delete iTwoPhaser;
		}
protected:
	virtual void DoSomeFunction(TInt aInt) const =0;
		// implement heart of some function, in derived class
	void ConstructL(TInt aInt)
		{ // second phase of constructor
		iTwoPhaser=CTwoPhaser::NewL(aInt);
			// construct embedded object
		}
	};

// class derived from above

class CConcrete : public CAbstract
	{
public: // data
	COnePhaser* iOnePhaser; // some extra data
public: // functions
	// construct/destruct
	static CConcrete* NewLC(TInt aInt)
		{ // construct and leave on the clean-up stack
		CConcrete* self=new (ELeave) CConcrete; // new object, C++ constructor
		CleanupStack::PushL(self); // push to clean-up stack
		self->ConstructL(aInt); // CBase constructor
		return self; // return new object
		};
	static CConcrete* NewL(TInt aInt)
		{ // construct and don't leave on clean-up stack
		CConcrete* self=CConcrete::NewLC(aInt); // construct and leave on clean-up stack
		CleanupStack::Pop(); // pop from clean-up stack
		return self; // return new object
		};
	virtual ~CConcrete()
		{
		delete iOnePhaser; // destroy member
		}
	// protocol
	virtual void DoSomeFunction(TInt aInt) const
		{ // implementation of base class's pure-virtual function
		_LIT(KFormat3,"CConcrete::DoSomething(%d)\n");
		console->Printf(KFormat3, aInt);
		}
protected:
	// construct/destruct
	void ConstructL(TInt aInt)
		{ // second phase of construction
		CAbstract::ConstructL(aInt); // base class constructor
		iOnePhaser=COnePhaser::NewL(); // contained member constructor
		}
	};

// do the example
LOCAL_C void doExampleL()
    {
	// two-phase object
	CTwoPhaser* twoPhaser=CTwoPhaser::NewLC(5);
			// new two-phase object
	twoPhaser->Print(); // print it
	_LIT(KTxtNewLine,"\n");
	console->Printf(KTxtNewLine);  // with trailing new-line
	CleanupStack::PopAndDestroy(); // two-phase object
	// concrete instance of an abstract class
	CAbstract* abstract=CConcrete::NewLC(9);
		// new concrete object, but refer to it with abstract pointer
	abstract->SomeFunction(11); // do something with it
	CleanupStack::PopAndDestroy(); // abstract object
	}
