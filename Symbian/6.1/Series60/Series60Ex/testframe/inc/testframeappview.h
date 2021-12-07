/* Copyright (c) 2001, Nokia. All rights reserved */
#ifndef __TESTFRAMEAPPVIEW_H__
#define __TESTFRAMEAPPVIEW_H__


#include <coecntrl.h>
#include "testlogger.h"

static const TInt KTestFrameworkTestNameMaxLength = 70;

static const TInt KTestFrameworkMaxScreenMessageLength = 100;
typedef TBuf<KTestFrameworkMaxScreenMessageLength> TTextLine;

class CTestExecutor;
class CLogFile;

/*! 
  @class CTestframeAppView
  
  @discussion An instance of the Application View object for the Test Framework 
  example application
  */
class CTestframeAppView : public CCoeControl, public MTestLogger
    {
public:

/*!
  @function NewL
   
  @discussion Create a CTestframeAppView object
  @param aRect the rectangle this view will be drawn to
  @result a pointer to the created instance of CTestframeAppView
  */
    static CTestframeAppView* NewL(const TRect& aRect);

/*!
  @function NewLC
   
  @discussion Create a CTestframeAppView object and leave it on the cleanup stack
  @param aRect the rectangle this view will be drawn to
  @result a pointer to the created instance of CTestframeAppView
  */
    static CTestframeAppView* NewLC(const TRect& aRect);

/*!
  @function ~CTestframeAppView
  
  @discussion Destroy the object and release all memory objects
  */
    ~CTestframeAppView();

/*!
  @function RunTestsL
  
  @discussion Run the tests
  */
	void RunTestsL();


public:  // from CCoeControl

/*!
  @function Draw
  
  @discussion Draw this CTestframeAppView to the screen
  @param aRect the rectangle of this view that needs updating
  */
    void Draw(const TRect& aRect) const;


public:  //from MTestLogger

/*!
  @function SetLogTypeL
  
  @discussion Set which method will be used for logging
  @param The logging required
  */
	void SetLogTypeL(TLoggingSelection aLogType);

/*!
  @function BeginTest
  
  @discussion Log that the test has begun
  @param aTestName name of the test started
  */
	void BeginTest(const TDesC& aTestName);

/*!
  @function Failed
  
  @discussion Log that the test has failed
  @param aReason reason why the test failed
  */
	void Failed(const TDesC& aReason);

/*!
  @function Passed
  
  @discussion Log that the test has passed
  */
	void Passed();

/*!
  @function Info
  
  @discussion Log some information
  @param aReason the information
  */
	void Info(const TDesC& aReason);


private:

/*!
  @function ConstructL
  
  @discussion  Perform the second phase construction of a CTestframeAppView object
  @param aRect the rectangle this view will be drawn to
  */
    void ConstructL(const TRect& aRect);

/*!
  @function CTestframeAppView
  
  @discussion Perform the first phase of two phase construction 
  */
    CTestframeAppView();

/*!
  @function Print
  
  @discussion Display/Write text via the selected methods
  @param aText the text to display
  */
	void Print(const TDesC& aText);

/*!
  @function PrintTime
  
  @discussion Display/Write the time via the selected methods
  */
	void PrintTime();

/*!
  @function PrintNewLineL
  
  @discussion Display/Write a new line via the selected methods
  */
	void PrintNewLineL();

/*!
  @function ShowTextOnScreen
  
  @discussion Display text on the screen
  @param aText the text to display
  */
	void ShowTextOnScreen(const TDesC& aText);

private:
    /*! @var iTestName The current text name*/
	TBuf <KTestFrameworkTestNameMaxLength> iTestName;

    /*! @var iLogType The current method of logging*/
	TLoggingSelection iLogType;
	
    /*! @var iLogFile The log file, if one is being used*/
	CLogFile* iLogFile;

    /*! @var iTextLines The lines of text being displayed on the screen*/
	RArray <TTextLine> iTextLines;
	};


#endif // __TESTFRAMEAPPVIEW_H__
