/* Copyright (c) 2002, Nokia. All rights reserved */

#include "MultiViewsContainer1.h"

CMultiViewsContainer1* CMultiViewsContainer1::NewL(const TRect& aRect)
    {
    CMultiViewsContainer1* self = CMultiViewsContainer1::NewLC(aRect);
    CleanupStack::Pop(self);
    return self;
    }

CMultiViewsContainer1* CMultiViewsContainer1::NewLC(const TRect& aRect)
    {
    CMultiViewsContainer1* self = new (ELeave) CMultiViewsContainer1;
    CleanupStack::PushL(self);
    self->ConstructL(aRect);
    return self;
    }

void CMultiViewsContainer1::ConstructL(const TRect& aRect)
    {
    CreateWindowL();
    SetRect(aRect);
    ActivateL();
    }

TInt CMultiViewsContainer1::CountComponentControls() const
    {
    return 0;
    }

void CMultiViewsContainer1::Draw(const TRect& aRect) const
    {    
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle(CGraphicsContext::ENullPen);
    gc.SetBrushColor(KRgbBlue);
    gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
    gc.DrawRect(aRect);
    }

CCoeControl* CMultiViewsContainer1::ComponentControl(TInt /*aIndex*/) const
    {
    return NULL;
    }
