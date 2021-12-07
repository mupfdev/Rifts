/* Copyright (c) 2001, Nokia. All rights reserved */

#ifndef __EXAMPLETOTEST_H__
#define __EXAMPLETOTEST_H__

#include <e32base.h>

/*! 
  @class CExampleToTest
  
  @discussion An instance of CExampleToTest is a simple class used to show how the test
  framework can be used
  */
class CExampleToTest : public CBase
	{

//Allow the test framework access to private functions
#ifdef __TESTFRAMEWORK__
	ALLOW_TEST_FULL_ACCESS
#endif

public:
/*!
  @function NewL
   
  @discussion Create a CExampleToTest object
  @result a pointer to the created instance of CExampleToTest
  */
	static CExampleToTest* NewL();

/*!
  @function NewL
   
  @discussion Create a CExampleToTest object and leave it on the cleanup stack
  @result a pointer to the created instance of CExampleToTest
  */
	static CExampleToTest* NewLC();

/*!
  @function ~CExampleToTest
  
  @discussion Destroy the object and release all memory objects
  */
	~CExampleToTest();

private:
/*!
  @function CExampleToTest
  
  @discussion Perform the first phase of two phase construction 
  */
	CExampleToTest();

/*!
  @function ConstructL
  
  @discussion  Perform the second phase construction of a CExampleToTest object
  */
	void ConstructL();

/*!
  @function ThisFunctionHasBadInvariants
  
  @discussion The invariants in this function will always fail 
  */
	void ThisFunctionHasBadInvariants();

	/*!
  @function ThisFunctionHasOkInvariants
  
  @discussion The invariants in this function will always pass 
  */
	void ThisFunctionHasOkInvariants();

/*!
  @function ThisFunctionCanPanic
  
  @discussion This function causes a panic depending on the parameter sent to it
  @param aPanic If true this functions panics, if false it does not
  */
	void ThisFunctionCanPanic(TBool aPanic);

/*!
  @function ThisFunctionCanLeaveL
  
  @discussion This function leaves depending on the parameter sent to it
  @param aLeave If true this function leaves, if false it does not
  */
	void ThisFunctionCanLeaveL(TBool aLeave);

/*!
  @function ThisFunctionReturnsFour
  
  @discussion This function returns 4
  @result 4
  */
	TInt ThisFunctionReturnsFour();
	};

#endif // __EXAMPLETOTEST_H__

