// Utilities.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.

#include "CommonFramework.h"

//
// Definition of the CTestOne class
//
class CTestOne : public CBase
	{	
public:
	~CTestOne();
	void     SetTextL(const TDesC& aData);
private :
	HBufC*   iText;
	};


//
// Implementation of the CTestOne class
//
_LIT(KTxtInsideDestructor,"Executing the CTestOne destructor\n");
CTestOne::~CTestOne()
	{
	delete iText;
	console->Printf(KTxtInsideDestructor);
	}

void CTestOne::SetTextL(const TDesC& aData)
	{
	if (iText)
		{
		delete iText;
		iText = NULL;
		}
	iText = aData.AllocL();	
	}



//
// Definition of the RTestTwo class
//
class RTestTwo
	{	
public:
	RTestTwo(TInt aValue);
	void     Close();
private :
	TInt     iX;
	};

//
// Implementation of the RTestTwo class
//
RTestTwo::RTestTwo(TInt aValue)
	: iX(aValue)
	{
	}


_LIT(KTxtCloseRTestTwo,"RTestTwo closing\n");

void RTestTwo::Close()
	{
	console->Printf(KTxtCloseRTestTwo);
	}



//
// Definition of the RTestThree class
//
class RTestThree
	{	
public:
	RTestThree(TInt aValue);
	void     Release();
private :
	TInt     iY;
	};

//
// Implementation of the RTestThree class
//
RTestThree::RTestThree(TInt aValue)
	: iY(aValue)
	{
	}


_LIT(KTxtReleaseRTestThree,"RTestThree releasing\n");

void RTestThree::Release()
	{
	console->Printf(KTxtReleaseRTestThree);
	}

//
// main body of the example
//
_LIT(KTxtHelloWorld,"Hello World!");
LOCAL_C void doExampleL()
    {
		// Construct a CTestOne object on the heap
	CTestOne* one = new (ELeave) CTestOne;
	
		// Use the CleanupDeletePushL() function to put a TCleanUpItem
		// on the cleanup stack
	CleanupDeletePushL(one);

		// Exercise the CTestOne object (just to show it doing something
	one->SetTextL(KTxtHelloWorld);

		// Pop and destroy the cleanup item off the cleanup stack.
		// The cleanup operation deletes the CTestOne object
	CleanupStack::PopAndDestroy();


		// Construct a RTestTwo object on the program stack.
		//
		// The value passed is of no significance; it is just
		// to show that the class is not trivial.
	RTestTwo  two(2);
		
		// Use the CleanupClosePushL() function to put a TCleanUpItem
		// on the cleanup stack
	CleanupClosePushL(two);

		// Pop and destroy the cleanup item off the cleanup stack.
		// The cleanup operation calls the Close() member function of
		// the RTestTwo object
	CleanupStack::PopAndDestroy();
				

		// Construct a RTestThree object on the program stack.
		//
		// The value passed is of no significance; it is just
		// to show that the class is not trivial.
	RTestThree  three(3);
		
		// Use the CleanupClosePushL() function to put a TCleanUpItem
		// on the cleanup stack
	CleanupReleasePushL(three);

		// Pop and destroy the cleanup item off the cleanup stack.
		// The cleanup operation calls the Release() member function of
		// the RTestThree object
	CleanupStack::PopAndDestroy();
	}
