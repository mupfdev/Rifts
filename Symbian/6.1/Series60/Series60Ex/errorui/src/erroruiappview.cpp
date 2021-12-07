/* Copyright (c) 2002, Nokia. All rights reserved */

#include <errorui.h>

#include "ErrorUiAppView.h"

// Standard construction sequence
CErrorUiAppView* CErrorUiAppView::NewL(const TRect& aRect)
    {
    CErrorUiAppView* self = CErrorUiAppView::NewLC(aRect);
    CleanupStack::Pop(self);
    return self;
    }

CErrorUiAppView* CErrorUiAppView::NewLC(const TRect& aRect)
    {
    CErrorUiAppView* self = new (ELeave) CErrorUiAppView;
    CleanupStack::PushL(self);
    self->ConstructL(aRect);
    return self;
    }

void CErrorUiAppView::ConstructL(const TRect& aRect)
    {
    // Create a window for this application view
    CreateWindowL();

    // Set the windows size
    SetRect(aRect);

    // Activate the window, which makes it ready to be drawn
    ActivateL();
    }

CErrorUiAppView::CErrorUiAppView()
    {
    // no implementation required
    }


CErrorUiAppView::~CErrorUiAppView()
    {
    // no implementation required
    }

// Draw this application's view to the screen
void CErrorUiAppView::Draw(const TRect& /*aRect*/) const
    {
    // Clear the screen
    CWindowGc& gc = SystemGc();
    gc.Clear(Rect());
    }

// Leave with error - used to raise error 
// to demonstrate CErrorUI error dialog
void CErrorUiAppView::ThrowLeaveErrorL(TInt aError)
	{
	User::Leave(aError);
	}

