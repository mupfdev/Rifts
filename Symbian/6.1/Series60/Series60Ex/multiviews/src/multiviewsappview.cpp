/* Copyright (c) 2002, Nokia. All rights reserved */

#include "MultiViewsAppView.h"

// Standard construction sequence
CMultiViewsAppView* CMultiViewsAppView::NewL(const TRect& aRect)
    {
    CMultiViewsAppView* self = CMultiViewsAppView::NewLC(aRect);
    CleanupStack::Pop(self);
    return self;
    }

CMultiViewsAppView* CMultiViewsAppView::NewLC(const TRect& aRect)
    {
    CMultiViewsAppView* self = new (ELeave) CMultiViewsAppView;
    CleanupStack::PushL(self);
    self->ConstructL(aRect);
    return self;
    }

void CMultiViewsAppView::ConstructL(const TRect& aRect)
    {
    // Create a window for this application view
    CreateWindowL();

    // Set the windows size
    SetRect(aRect);

    // Activate the window, which makes it ready to be drawn
    ActivateL();
    }

CMultiViewsAppView::CMultiViewsAppView()
    {
    // Add any construction code that can not leave here
    }


CMultiViewsAppView::~CMultiViewsAppView()
    {
    // Add any destruction code here
    }

// Draw this application's view to the screen
void CMultiViewsAppView::Draw(const TRect& /*aRect*/) const
    {
    // Clear the screen
    CWindowGc& gc = SystemGc();
    gc.Clear(Rect());
    }


