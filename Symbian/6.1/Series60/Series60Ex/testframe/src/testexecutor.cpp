/* Copyright (c) 2001, Nokia. All rights reserved */

#include "TestExecutor.h"
#include "testlogger.h"
#include "staticoverrideaccess.h"
#include "macros.h"

//**** This class should be modified to include all your tests ****


//**** add #includes for you classes under test here

//If this macro is included in the class definition for a class under test,
//this class has access to its private members
#define ALLOW_TEST_FULL_ACCESS friend class CTestExecutor;


//The class under test may need to know whether it is being used in a test
//environment rather than an actual application so __TESTFRAMEWORK__ is defined.
//This can be used in conjuction with ALLOW_TEST_FULL_ACCESS defined above.
#define __TESTFRAMEWORK__
#include "exampletotest.h"

static const TInt KPanicTrapped = 1000;
static const TInt KInvariantTrapped = 1001;
static const TInt KExpectedLeave = 2002;

static const TInt KMaxFailureMessageLength = 100;

_LIT(KNoPanicFailed, "Panic no:%d - ");
_LIT(KPanicFailed, "No panic occurred");

_LIT(KUnhandledTestLeave, "Unhandled Leave Occured no:%d - Tests aborted");

_LIT(KLeaveFailed, "Unexpected leave code: %d");
_LIT(KNoLeaveFailed, "Leave occurred: %d");
_LIT(KNoLeaveOccured, "No Leave occurred");

_LIT(KBadInvariantFailed, "No bad invariants");
_LIT(KOkInvariantFailed, "Bad invariants");




CTestExecutor* CTestExecutor::NewL(MTestLogger& aTestLogger)
	{
	CTestExecutor* self = CTestExecutor::NewLC(aTestLogger);
	CleanupStack::Pop(self);
	return self;
	}

	
CTestExecutor* CTestExecutor::NewLC(MTestLogger& aTestLogger)
	{
	CTestExecutor* self = new (ELeave) CTestExecutor(aTestLogger);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}


CTestExecutor::CTestExecutor(MTestLogger& aTestLogger)
:	iTestLogger(aTestLogger)
	{
	//	Implementation not required
	}


CTestExecutor::~CTestExecutor()
	{
	Dll::FreeTls();
	}


void CTestExecutor::OnInvariantL()
	{
	User::Leave(KInvariantTrapped);
	}


void CTestExecutor::OnPanicL(const TDesC& aCategory, TInt aReason)
	{
	//store reasons for panicing and then leave to return to test execution
	iPanicCategory.Zero();
	iPanicCategory.Append(aCategory);
	iPanicReason = aReason;

	User::Leave(KPanicTrapped);
	}


void CTestExecutor::NoPanicPass()
	{
	iTestLogger.Passed();
	}


void CTestExecutor::NoPanicFail()
	{
	TBuf<KMaxFailureMessageLength> text;
	text.Format(KNoPanicFailed, iPanicReason);
	text.Append(iPanicCategory);
	iTestLogger.Failed(text);
	}


void CTestExecutor::PanicPass()
	{
	iTestLogger.Passed();
	}


void CTestExecutor::PanicFail()
	{
	TBuf<KMaxFailureMessageLength> text;
	text.Format(KPanicFailed);
	text.Append(iPanicCategory);
	iTestLogger.Failed(text);
	}


void CTestExecutor::NoLeaveFail(TInt aReason)
	{
	TBuf<KMaxFailureMessageLength> text;
	text.Format(KNoLeaveFailed, aReason);
	iTestLogger.Failed(text);
	}


void CTestExecutor::NoLeavePass()
	{
	iTestLogger.Passed();
	}


void CTestExecutor::LeaveFail(TInt aReason)
	{
	TBuf<KMaxFailureMessageLength> text;
	if (aReason == KErrNone)
		{
		text.Append(KNoLeaveOccured);
		}
	else
		{
		text.Format(KLeaveFailed, aReason);
		}
	iTestLogger.Failed(text);
	}


void CTestExecutor::LeavePass()
	{
	iTestLogger.Passed();
	}


void CTestExecutor::OkInvariantPass()
	{
	iTestLogger.Passed();
	}


void CTestExecutor::OkInvariantFail()
	{
	TBuf<KMaxFailureMessageLength> text;
	text.Format(KOkInvariantFailed);
	iTestLogger.Failed(text);
	}


void CTestExecutor::BadInvariantPass()
	{
	iTestLogger.Passed();
	}


void CTestExecutor::BadInvariantFail()
	{
	TBuf<KMaxFailureMessageLength> text;
	text.Format(KBadInvariantFailed);
	iTestLogger.Failed(text);
	}


void CTestExecutor::ConstructL()
	{
	NStaticOverrideAccess::SetHandler(*this);

	TRAPD(err, RunTestsL());

	if (err != KErrNone)
		{
		TBuf<KMaxFailureMessageLength> text;
		text.Format(KUnhandledTestLeave, err);
		iTestLogger.Failed(text);
		}
	}

//The actual tests
void CTestExecutor::RunTestsL()
	{
	//In this case log to a file and the screen
	MTestLogger::TLoggingSelection selection;
	selection.TurnOn(MTestLogger::ELogTypeFile);
	selection.TurnOn(MTestLogger::ELogTypeScreen);
	iTestLogger.SetLogTypeL(selection);
	
	//Create an instance of the simple class to test
	CExampleToTest* classUnderTest = CExampleToTest::NewLC();

	//

	iTestLogger.BeginTest(_L("Test_1_1:Check function doesn't panic with valid parameter"));
	CHECK_NO_PANIC(classUnderTest->ThisFunctionCanPanic(FALSE));
	
	//
	
	iTestLogger.BeginTest(_L("Test_1_2:Check function does panic with invalid parameter"));
	CHECK_PANIC(classUnderTest->ThisFunctionCanPanic(TRUE));

	//

	iTestLogger.BeginTest(_L("Test_2_1:Check function doesn't leave"));
	CHECK_NO_LEAVE(classUnderTest->ThisFunctionCanLeaveL(FALSE));

	//

	iTestLogger.BeginTest(_L("Test_2_2:Check function does leave"));
	CHECK_LEAVE(classUnderTest->ThisFunctionCanLeaveL(TRUE), KExpectedLeave);

	//

	iTestLogger.BeginTest(_L("Test_3_1:Check function has ok invariants"));
	CHECK_INVARIANTS_OK(classUnderTest->ThisFunctionHasOkInvariants());

	//

	iTestLogger.BeginTest(_L("Test_3_2:Check function has bad invariants"));
	CHECK_INVARIANTS_BAD(classUnderTest->ThisFunctionHasBadInvariants());

	//

	iTestLogger.BeginTest(_L("Test_4_1:Check function returns 4"));
	TInt testResult = classUnderTest->ThisFunctionReturnsFour();
	if (testResult != 4)
		{
		TBuf<50> reason;
		reason.Format(_L("function did not return 4, actual value:%d"), testResult);
		iTestLogger.Failed(reason);
		}
	else
		{
		iTestLogger.Passed();
		}

	//

	//delete/remove from cleanup stack the class we are testing
	CleanupStack::PopAndDestroy(classUnderTest);

	}

