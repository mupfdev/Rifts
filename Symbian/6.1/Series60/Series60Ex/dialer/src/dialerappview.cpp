/* Copyright (c) 2001, Nokia. All rights reserved */

#include "DialerAppView.h"

// Standard Epoc construction sequence
CDialerAppView* CDialerAppView::NewL(const TRect& aRect)
    {
    CDialerAppView* self = CDialerAppView::NewLC(aRect);
    CleanupStack::Pop();
    return self;
    }

CDialerAppView* CDialerAppView::NewLC(const TRect& aRect)
    {
    CDialerAppView* self = new (ELeave) CDialerAppView;
    CleanupStack::PushL(self);
    self->ConstructL(aRect);
    return self;
    }

void CDialerAppView::ConstructL(const TRect& aRect)
    {
    // Create a window for this application view
    CreateWindowL();

    // Set the windows size
    SetRect(aRect);

    // Activate the window, which makes it ready to be drawn
    ActivateL();
    }

CDialerAppView::CDialerAppView()
    {
    }


CDialerAppView::~CDialerAppView()
    {
    }

// Draw this application's view to the screen
void CDialerAppView::Draw(const TRect& /*aRect*/) const
    {
    // Clear the screen
    CWindowGc& gc = SystemGc();
    gc.Clear(Rect());
    }


