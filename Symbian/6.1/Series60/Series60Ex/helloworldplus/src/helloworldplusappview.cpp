/* Copyright (c) 2002, Nokia. All rights reserved */

#include <coemain.h>
#include <aknnotewrappers.h>
#include <HelloWorldPlus.rsg>

#include "HelloWorldPlusAppView.h"

// Standard construction sequence
CHelloWorldPlusAppView* CHelloWorldPlusAppView::NewL(const TRect& aRect)
    {
    CHelloWorldPlusAppView* self = CHelloWorldPlusAppView::NewLC(aRect);
    CleanupStack::Pop(self);
    return self;
    }

CHelloWorldPlusAppView* CHelloWorldPlusAppView::NewLC(const TRect& aRect)
    {
    CHelloWorldPlusAppView* self = new (ELeave) CHelloWorldPlusAppView;
    CleanupStack::PushL(self);
    self->ConstructL(aRect);
    return self;
    }

void CHelloWorldPlusAppView::ConstructL(const TRect& aRect)
    {
    // Create a window for this application view
    CreateWindowL();

    // Set the windows size
    SetRect(aRect);

    // Activate the window, which makes it ready to be drawn
    ActivateL();
    }

CHelloWorldPlusAppView::CHelloWorldPlusAppView()
    {
    // Add any construction code that can not leave here
    }


CHelloWorldPlusAppView::~CHelloWorldPlusAppView()
    {
    // Add any destruction code here
    }


// Draw this application's view to the screen
void CHelloWorldPlusAppView::Draw(const TRect& /*aRect*/) const
    {
    // Get the standard graphics context 
    CWindowGc& gc = SystemGc();
    
    // Gets the control's extent
    TRect rect = Rect();
    
    // Clears the screen
    gc.Clear(rect);

	// query what the current time is
	TTime currentTime;
	currentTime.HomeTime();

	// format the time into a descriptor, and handle any errors
	TBuf<32> timeAsText;
	_LIT (KTimeFormat, "%H : %T : %S");
	_LIT (KTimeError, "Error formatting the time!");
	TRAPD (err, 
		   currentTime.FormatL(timeAsText, KTimeFormat););
	if (err != KErrNone)
		{
		timeAsText = KTimeError;
		}

	// write the time to the display
	gc.UseFont(iCoeEnv->NormalFont());
	gc.DrawText(timeAsText, TPoint(30,30));

    }

TKeyResponse CHelloWorldPlusAppView::OfferKeyEventL(
		const TKeyEvent& aKeyEvent,TEventCode aType)
	{
	// we only want the key press, not the key up/down event
	if (aType == EEventKey)
		{
		// check if the 2 key was pressed
		if (aKeyEvent.iCode == '2')
			{
			_LIT(message,"\"2\" key pressed");
            CAknInformationNote* informationNote;
			informationNote = new (ELeave) CAknInformationNote;
            informationNote->ExecuteLD(message);
			return EKeyWasConsumed;
			}
		}

	// return the default functionality
	return CCoeControl::OfferKeyEventL(aKeyEvent, aType);
	}


TCoeInputCapabilities CHelloWorldPlusAppView::InputCapabilities() const
	{
	// this class does not implement any 'unusual' input capabilities
	return TCoeInputCapabilities::ENone;
	}

void CHelloWorldPlusAppView::UserDraw() const
	{
	ActivateGc();
	Draw(Rect());
	DeactivateGc();
	}