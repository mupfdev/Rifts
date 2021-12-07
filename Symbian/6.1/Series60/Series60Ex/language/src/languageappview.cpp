/* Copyright (c) 2002, Nokia. All rights reserved */

#include "LanguageAppView.h"

// Standard Symbian OS construction sequence
CLanguageAppView* CLanguageAppView::NewL(const TRect& aRect)
    {
    CLanguageAppView* self = CLanguageAppView::NewLC(aRect);
    CleanupStack::Pop(self);
    return self;
    }

CLanguageAppView* CLanguageAppView::NewLC(const TRect& aRect)
    {
    CLanguageAppView* self = new (ELeave) CLanguageAppView;
    CleanupStack::PushL(self);
    self->ConstructL(aRect);
    return self;
    }

void CLanguageAppView::ConstructL(const TRect& aRect)
    {
    // Create a window for this application view
    CreateWindowL();

    // Set the windows size
    SetRect(aRect);

    // Activate the window, which makes it ready to be drawn
    ActivateL();
    }

CLanguageAppView::CLanguageAppView()
    {
    // No implementation required
    }


CLanguageAppView::~CLanguageAppView()
    {
    // No implementation required
    }

// Draw this application's view to the screen
void CLanguageAppView::Draw(const TRect& /*aRect*/) const
    {
    // Clear the screen
    CWindowGc& gc = SystemGc();
    gc.Clear(Rect());
    }


