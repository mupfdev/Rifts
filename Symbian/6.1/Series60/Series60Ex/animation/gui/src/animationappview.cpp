/* Copyright (c) 2001, Nokia. All rights reserved */
#include <coemain.h>
#include <eikenv.h>
#include "animationappview.h"

CAnimationAppView* CAnimationAppView::NewL(const TRect& aRect)
    {
    CAnimationAppView* self = CAnimationAppView::NewLC(aRect);
    CleanupStack::Pop();
    return self;
    }

CAnimationAppView* CAnimationAppView::NewLC(const TRect& aRect)
    {
    CAnimationAppView* self = new (ELeave) CAnimationAppView();
    CleanupStack::PushL(self);
    self->ConstructL(aRect);
    return self;
    }

void CAnimationAppView::ConstructL(const TRect& aRect)
    {
    // Create a window for this application view
    CreateWindowL();

    // Set the windows size
    SetRect(aRect);

    // Activate the window, which makes it ready to be drawn
    ActivateL();
    }

void CAnimationAppView::Draw(const TRect& /*aRect*/) const
    {
    // clear the screen
    CWindowGc& gc = SystemGc();
    TRect drawRect=Rect();
    gc.Clear(drawRect);
    }

CAnimationAppView::CAnimationAppView()
    {
    }


CAnimationAppView::~CAnimationAppView()
    {
    }
