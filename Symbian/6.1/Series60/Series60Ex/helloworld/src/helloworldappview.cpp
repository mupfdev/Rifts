/* Copyright (c) 2002, Nokia. All rights reserved */

#include <coemain.h>

#include "HelloWorldAppView.h"

// Standard construction sequence
CHelloWorldAppView* CHelloWorldAppView::NewL(const TRect& aRect)
    {
    CHelloWorldAppView* self = CHelloWorldAppView::NewLC(aRect);
    CleanupStack::Pop(self);
    return self;
    }

CHelloWorldAppView* CHelloWorldAppView::NewLC(const TRect& aRect)
    {
    CHelloWorldAppView* self = new (ELeave) CHelloWorldAppView;
    CleanupStack::PushL(self);
    self->ConstructL(aRect);
    return self;
    }

CHelloWorldAppView::CHelloWorldAppView()
    {
	// no implementation required
    }

CHelloWorldAppView::~CHelloWorldAppView()
    {
	// no implementation required
    }

void CHelloWorldAppView::ConstructL(const TRect& aRect)
    {
    // Create a window for this application view
    CreateWindowL();

    // Set the windows size
    SetRect(aRect);

    // Activate the window, which makes it ready to be drawn
    ActivateL();
    }

// Draw this application's view to the screen
void CHelloWorldAppView::Draw(const TRect& /*aRect*/) const
    {
    // Get the standard graphics context 
    CWindowGc& gc = SystemGc();
    
    // Gets the control's extent
    TRect rect = Rect();
    
    // Clears the screen
    gc.Clear(rect);
    }


