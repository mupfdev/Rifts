/* Copyright (c) 2002, Nokia. All rights reserved */

#include "MultiViewsContainer2.h"

CMultiViewsContainer2* CMultiViewsContainer2::NewL(const TRect& aRect)
    {
    CMultiViewsContainer2* self = CMultiViewsContainer2::NewLC(aRect);
    CleanupStack::Pop(self);
    return self;
    }

CMultiViewsContainer2* CMultiViewsContainer2::NewLC(const TRect& aRect)
    {
    CMultiViewsContainer2* self = new (ELeave) CMultiViewsContainer2;
    CleanupStack::PushL(self);
    self->ConstructL(aRect);
    return self;
    }

void CMultiViewsContainer2::ConstructL(const TRect& aRect)
    {
    CreateWindowL();
    SetRect(aRect);
    ActivateL();
    }

TInt CMultiViewsContainer2::CountComponentControls() const
    {
    return 0;
    }

void CMultiViewsContainer2::Draw(const TRect& aRect) const
    {    
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle(CGraphicsContext::ENullPen);
    gc.SetBrushColor(KRgbRed);
    gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
    gc.DrawRect(aRect);
    }

CCoeControl* CMultiViewsContainer2::ComponentControl(TInt /*aIndex*/) const
    {
    return NULL;
    }
