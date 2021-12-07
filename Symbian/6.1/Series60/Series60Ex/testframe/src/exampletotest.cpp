/* Copyright (c) 2001, Nokia. All rights reserved */

#include "ExampleToTest.h"
#include "ExampleToTest.pan"

_LIT(KPanicName, "ExamplePanic");

CExampleToTest* CExampleToTest::NewL()
	{
	CExampleToTest* self = CExampleToTest::NewLC();
	CleanupStack::Pop(self);
	return self;
	}

	
CExampleToTest* CExampleToTest::NewLC()
	{
	CExampleToTest* self = new (ELeave) CExampleToTest();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}


CExampleToTest::CExampleToTest()
	{
	//	Implementation not required
	}


CExampleToTest::~CExampleToTest()
	{
	//	Implementation not required
	}


void CExampleToTest::ConstructL()
	{
	//	Implementation not required
	}


void CExampleToTest::ThisFunctionCanPanic(TBool aPanic)
	{
	if (aPanic)
		{
		User::Panic(KPanicName, EExampleToTestPanicFunction);
		}
	}


void CExampleToTest::ThisFunctionCanLeaveL(TBool aLeave)
	{
	if (aLeave)
		{
		User::Leave(2002);
		}
	}


void CExampleToTest::ThisFunctionHasBadInvariants()
	{
	__ASSERT_ALWAYS(1 == 2, User::Invariant());
	}


void CExampleToTest::ThisFunctionHasOkInvariants()
	{
	__ASSERT_ALWAYS(1 == 1, User::Invariant());
	}


TInt CExampleToTest::ThisFunctionReturnsFour()
	{
	return 4;
	}
