/* Copyright (c) 2001, Nokia. All rights reserved */

#include <coemain.h>
#include <eikenv.h>
#include "CSAsyncAppView.h"
#include "CSAsyncDocument.h"

// Standard Epoc construction sequence
CCSAsyncAppView* CCSAsyncAppView::NewL(const TRect& aRect, CCSAsyncDocument& aDocument)
    {
    CCSAsyncAppView* self = CCSAsyncAppView::NewLC(aRect, aDocument);
    CleanupStack::Pop();
    return self;
    }

CCSAsyncAppView* CCSAsyncAppView::NewLC(const TRect& aRect, CCSAsyncDocument& aDocument)
    {
    CCSAsyncAppView* self = new (ELeave) CCSAsyncAppView(aDocument);
    CleanupStack::PushL(self);
    self->ConstructL(aRect);
    return self;
    }

void CCSAsyncAppView::ConstructL(const TRect& aRect)
    {
    // Create a window for this application view
    CreateWindowL();

    // Set the windows size
    SetRect(aRect);

    // Activate the window, which makes it ready to be drawn
    ActivateL();
    }

CCSAsyncAppView::CCSAsyncAppView(CCSAsyncDocument& aDocument)
    : iDocument(aDocument)
    {
    // No implementation required
    }


CCSAsyncAppView::~CCSAsyncAppView()
    {
    // No implementation required
    }

// Draw this application's view to the screen
void CCSAsyncAppView::Draw(const TRect& /*aRect*/) const
    {
    _LIT(KHoursMinsSecs, "%-B%:0%J%:1%T%:2%S%:3%+B");

    // Clear the screen
    CWindowGc& gc = SystemGc();
    gc.Clear(Rect());

    TBuf<30> des;
    const TTime& time = iDocument.Time();
    TRAPD(err, time.FormatL(des, KHoursMinsSecs));

    if (err == KErrNone)
        {
        const CFont* font = iEikonEnv->NormalFont();
        gc.UseFont(font);
        gc.DrawText(des, TPoint(10,20));
        }
    }


