/* Copyright (c) 2001, Nokia. All rights reserved */
#include <coemain.h>
#include <eikenv.h>
#include "CSSyncAppView.h"
#include "CSSyncDocument.h"

// Standard Epoc construction sequence
CCSSyncAppView* CCSSyncAppView::NewL(const TRect& aRect, CCSSyncDocument& aDocument)
    {
    CCSSyncAppView* self = CCSSyncAppView::NewLC(aRect, aDocument);
    CleanupStack::Pop();
    return self;
    }

CCSSyncAppView* CCSSyncAppView::NewLC(const TRect& aRect, CCSSyncDocument& aDocument)
    {
    CCSSyncAppView* self = new (ELeave) CCSSyncAppView(aDocument);
    CleanupStack::PushL(self);
    self->ConstructL(aRect);
    return self;
    }

void CCSSyncAppView::ConstructL(const TRect& aRect)
    {
    // Create a window for this application view
    CreateWindowL();

    // Set the windows size
    SetRect(aRect);

    // Activate the window, which makes it ready to be drawn
    ActivateL();
    }

CCSSyncAppView::CCSSyncAppView(CCSSyncDocument& aDocument)
    : iDocument(aDocument)
    {
    // No implementation required
    }

CCSSyncAppView::~CCSSyncAppView()
    {
    // No implementation required
    }

// Draw this application's view to the screen
void CCSSyncAppView::Draw(const TRect& /*aRect*/) const
    {
    _LIT(KHoursMinsSecs, "%-B%:0%J%:1%T%:2%S%:3%+B");

    // Clear the screen
    CWindowGc& gc = SystemGc();
    gc.Clear(Rect());

    TBuf<30> des;
    const TTime& time = iDocument.GetTime();
    TRAPD(err, time.FormatL(des, KHoursMinsSecs));

    if (err == KErrNone)
        {
        const CFont* font = iEikonEnv->NormalFont();
        gc.UseFont(font);
        gc.DrawText(des, TPoint(10,20));
        }
    }

