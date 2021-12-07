/* Copyright (c) 2001, Nokia. All rights reserved */

#include <coemain.h>
#include <eikenv.h>
#include <hal.h>
#include "TestframeAppView.h"
#include "testexecutor.h"
#include "logfile.h"
#include "eikonenvironment.h"

static const TInt KMaxTextLines = 7;
static const TInt KTextXMargin = 10;
static const TInt KTextMinY = 10;
static const TInt KTextDistanceBetweenLines = 20;
static const TInt KNumberDecimalPlaces = 3;

_LIT(KLogFileName, "c:\\testlog.txt");

_LIT(KStartTestText, "     Starting Test:");
_LIT(KTimeText, " at ");
_LIT(KTestPassed, "     Test passed at ");
_LIT(KTestFailed, "*****Test failed at ");


_LIT(KInfoMargin, "     ");


CTestframeAppView* CTestframeAppView::NewL(const TRect& aRect)
	{
	CTestframeAppView* self = CTestframeAppView::NewLC(aRect);
	CleanupStack::Pop(self);
	return self;
	}


CTestframeAppView* CTestframeAppView::NewLC(const TRect& aRect)
	{
    // Standard Epoc32 construction sequence
    CTestframeAppView* self = new (ELeave) CTestframeAppView;
    CleanupStack::PushL(self);
    self->ConstructL(aRect);
    return self;
	}


void CTestframeAppView::ConstructL(const TRect& aRect)
	{
    // Create a window for this application view
    CreateWindowL();

    // Set the windows size
    SetRect(aRect);

	//Add the first blank line to the array of text lines
	User::LeaveIfError(iTextLines.Append(KNullDesC()));

    // Activate the window, which makes it ready to be drawn
    ActivateL();
	}


void CTestframeAppView::Print(const TDesC& aText)
	{
	if (iLogType.Logging(MTestLogger::ELogTypeFile))
		{
		ASSERT(iLogFile);
		iLogFile->Log(aText);
		}

	if (iLogType.Logging(MTestLogger::ELogTypeScreen))
		{
		ShowTextOnScreen(aText);
		}
	}


void CTestframeAppView::ShowTextOnScreen(const TDesC& aText)
	{
	//Add the text line onto the last line
	
	TInt lastTextLine = iTextLines.Count() - 1;

	//Make sure the text line doesn't get too long for the buffer.
	//This should really clip rather than not do anything if the line is too long.
	if (aText.Length() + iTextLines[lastTextLine].Length() <= KTestFrameworkMaxScreenMessageLength)
		{
		iTextLines[lastTextLine].Append(aText);
		DrawNow();
		}
	}


void CTestframeAppView::PrintNewLineL()
	{
	if (iLogType.Logging(MTestLogger::ELogTypeFile))
		{
		ASSERT(iLogFile);
		iLogFile->LogNewline();
		}

	if (iLogType.Logging(MTestLogger::ELogTypeScreen))
		{
		//Add a new line onto the array

		//If the array is already at the maximum size, delete the first line of text
		if (iTextLines.Count() >= KMaxTextLines)
			{
			iTextLines.Remove(0);
			}

		User::LeaveIfError(iTextLines.Append(KNullDesC()));
		DrawNow();
		}
	}


void CTestframeAppView::PrintTime()
	{
	if (iLogType.Logging(MTestLogger::ELogTypeFile))
		{
		ASSERT(iLogFile);
		iLogFile->LogTime();
		}
	
	if (iLogType.Logging(MTestLogger::ELogTypeScreen))
		{
		TInt period;
		User::LeaveIfError(HAL::Get(HALData::ESystemTickPeriod, period));
		TInt logMillisecsPerTick = period / 1000;
		TBuf<50> text;

		TInt timeInMillisecs = User::TickCount() * logMillisecsPerTick;
		TInt secs = timeInMillisecs / 1000;
		TInt millisecs = timeInMillisecs % 1000;
		text.Num(secs);
		text.Append('.');
		ShowTextOnScreen(text);
		text.Num(millisecs);

		while (text.Length() < KNumberDecimalPlaces)
    		{
			text.Insert(0, _L("0"));
    		}

		text.Append('-');
		ShowTextOnScreen(text);
		}
	}


void CTestframeAppView::Draw(const TRect& /*aRect*/) const
	{
    // clear the screen
    CWindowGc& gc = SystemGc();
    TRect drawRect=Rect();
	gc.UseFont(NEikonEnvironment::EikEnv().AnnotationFont());

    gc.Clear(drawRect);

	if (iLogType.Logging(MTestLogger::ELogTypeScreen))
		{
		//Draw all lines of text
		TInt count;
		for (count = 0; count < iTextLines.Count(); count++)
			{
			gc.DrawText(iTextLines[count],
				TPoint(KTextXMargin, KTextMinY+(count*KTextDistanceBetweenLines)));
			}
		}
	}


CTestframeAppView::CTestframeAppView()
	{
    // No implementation required
	}


CTestframeAppView::~CTestframeAppView()
	{
	delete iLogFile;
	iLogFile = NULL;

	iTextLines.Close();
	}


void CTestframeAppView::RunTestsL()
	{
	CTestExecutor* testExecutor = CTestExecutor::NewLC(*this);
	CleanupStack::PopAndDestroy(testExecutor);
	}


void CTestframeAppView::BeginTest(const TDesC& aTestName)
	{
	iTestName.Zero();
	iTestName.Append(aTestName);

	Print(KStartTestText);
	Print(aTestName);
	Print(KTimeText);
	PrintTime();
	PrintNewLineL();
	}


void CTestframeAppView::SetLogTypeL(TLoggingSelection aLogType)
	{
	iLogType = aLogType;

	if (iLogType.Logging(MTestLogger::ELogTypeFile))
		{
		if (iLogFile == NULL)
			{
			iLogFile = CLogFile::NewL(KLogFileName, TRUE);
			}
		}
	}


void CTestframeAppView::Failed(const TDesC& aReason)
	{
	Print(KTestFailed);
	PrintTime();
	PrintNewLineL();
	Print(aReason);
	PrintNewLineL();
	}


void CTestframeAppView::Passed()
	{
	Print(KTestPassed);
	PrintTime();
	PrintNewLineL();
	}


void CTestframeAppView::Info(const TDesC& aReason)
	{
	Print(KInfoMargin);
	Print(aReason);
	PrintNewLineL();
	}

