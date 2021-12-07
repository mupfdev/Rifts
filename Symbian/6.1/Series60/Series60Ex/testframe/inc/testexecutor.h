/* Copyright (c) 2001, Nokia. All rights reserved */

#ifndef __TESTEXECUTOR_H__
#define __TESTEXECUTOR_H__

#include <e32base.h>
#include "staticoverridehandler.h"

class MTestLogger;

/*! 
  @class CTestExecutor
  
  @discussion An instance of CTestExecutor is a test controller
  */
class CTestExecutor : public CBase, public MStaticOverrideHandler
	{
public:
/*!
  @function NewL
   
  @discussion Create a CTestExecutor object
  @param aTestLogger an object which can log test results
  @result a pointer to the created instance of CTestExecutor
  */
	static CTestExecutor* NewL(MTestLogger& aTestLogger);

/*!
  @function NewLC
   
  @discussion Create a CTestExecutor object and leave it on the cleanup stack
  @param aTestLogger an object which can log test results
  @result a pointer to the created instance of CTestExecutor
  */
	static CTestExecutor* NewLC(MTestLogger& aTestLogger);

/*!
  @function ~CTestExecutor
  
  @discussion Destroy the object and release all memory objects
  */
	~CTestExecutor();

public:  //from MStaticOverrideHandler

/*!
  @function OnPanicL
   
  @discussion Called when a panic occurs
  @param aCategory panic category
  @param aReason panic reason
  */
	void OnPanicL(const TDesC& aCategory, TInt aReason);

/*!
  @function OnInvariantL
   
  @discussion Called when an invariant is bad
  */
	void OnInvariantL();

private:
/*!
  @function CTestExecutor
  
  @discussion Perform the first phase of two phase construction 
  @param aTestLogger an object which can log test results
  */
	CTestExecutor(MTestLogger& aTestLogger);

/*!
  @function ConstructL
  
  @discussion  Perform the second phase construction of a CTestExecutor object
  */
	void ConstructL();

/*!
  @function RunTestsL
  
  @discussion Run the tests
  */
	void RunTestsL();

/*!
  @function NoPanicPass
  
  @discussion Log that a no panic check has passed
  */
	void NoPanicPass();

/*!
  @function NoPanicFail
  
  @discussion Log that a no panic check has failed
  */
	void NoPanicFail();

/*!
  @function NoPanicLeave
  
  @discussion Log that a no panic check has caused a leave to occur
  */
	void NoPanicLeave();

/*!
  @function PanicPass
  
  @discussion Log that a panic check has passed
  */
	void PanicPass();

/*!
  @function PanicFail
  
  @discussion Log that a panic check has failed
  */
	void PanicFail();

/*!
  @function NoLeaveFail
  
  @discussion Log that a no leave check has failed
  @param aReason The Leave reason
  */
	void NoLeaveFail(TInt aReason);

/*!
  @function NoLeavePass
  
  @discussion Log that a no leave check has passed
  */
	void NoLeavePass();

/*!
  @function LeaveFail
  
  @discussion Log that a leave check has failed
  @param aReason The Leave reason, different to the expected
  */
	void LeaveFail(TInt aReason);

/*!
  @function LeavePass
  
  @discussion Log that a leave check has passed
  */
	void LeavePass();

/*!
  @function OkInvariantPass
  
  @discussion Log that an ok invariant check has passed
  */
	void OkInvariantPass();

/*!
  @function OkInvariantFail
  
  @discussion Log that an ok invariant check has failed
  */
	void OkInvariantFail();

/*!
  @function BadInvariantPass
  
  @discussion Log that a bad invariant check has passed
  */
	void BadInvariantPass();

/*!
  @function BadInvariantFail
  
  @discussion Log that a bad invariant check has failed
  */
	void BadInvariantFail();

private:
	
	enum
	    {
		KMaxPanicCharacters = 50
	    };


private:
    /*! @var iTestLogger The test logger*/
	MTestLogger& iTestLogger;

    /*! @var iPanicCategory The most recent panic category*/
	TBuf<KMaxPanicCharacters> iPanicCategory;

    /*! @var iPanicReason The most recent panic reason*/
	TInt iPanicReason;

	};

#endif // __TESTEXECUTOR_H__

