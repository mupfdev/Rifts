/* Copyright (c) 2001, Nokia. All rights reserved */
#include <coemain.h>
#include <eikenv.h>
#include <hal.h>
#include "FocusEventAppView.h"
#include "..\..\helperfunctions\eikonenvironment.h"

static const TInt KMaxTextLines = 7;
static const TInt KTextXMargin = 10;
static const TInt KTextMinY = 10;
static const TInt KTextDistanceBetweenLines = 20;

// Standard Epoc construction sequence
CFocusEventAppView* CFocusEventAppView::NewL(const TRect& aRect)
    {
    CFocusEventAppView* self = CFocusEventAppView::NewLC(aRect);
    CleanupStack::Pop(self);
    return self;
    }

CFocusEventAppView* CFocusEventAppView::NewLC(const TRect& aRect)
    {
    CFocusEventAppView* self = new (ELeave) CFocusEventAppView;
    CleanupStack::PushL(self);
    self->ConstructL(aRect);
    return self;
    }

void CFocusEventAppView::ConstructL(const TRect& aRect)
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

void CFocusEventAppView::Print(const TDesC& aText)
	{
		ShowTextOnScreen(aText);
	}


void CFocusEventAppView::ShowTextOnScreen(const TDesC& aText)
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


void CFocusEventAppView::PrintNewLineL()
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


CFocusEventAppView::CFocusEventAppView()
    {
    // Add any construction code that can not leave here
    }


CFocusEventAppView::~CFocusEventAppView()
    {
	iTextLines.Close();
    }

// draw this applications vie to the screen
void CFocusEventAppView::Draw(const TRect& /*aRect*/) const
	{
    // clear the screen
    CWindowGc& gc = SystemGc();
    TRect drawRect=Rect();
	gc.UseFont(NEikonEnvironment::EikEnv().AnnotationFont());

    gc.Clear(drawRect);

	//Draw all lines of text
	TInt count;
	for (count = 0; count < iTextLines.Count(); count++)
		{
            gc.DrawText(iTextLines[count],
			TPoint(KTextXMargin, KTextMinY+(count*KTextDistanceBetweenLines)));
		}
	}

