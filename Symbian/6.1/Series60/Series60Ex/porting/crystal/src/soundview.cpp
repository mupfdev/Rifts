// Copyright c 2000, Nokia. All rights reserved.

#include <eikenv.h>
#include <eikdef.h>
#include <eiklabel.h>
#include <gulcolor.h>

#include "sound.pan"
#include "SoundView.h"
#include "SoundDoc.h"

void CSoundView::ConstructL()
    {
    CreateWindowL();
    iContext=this;
    iBrushStyle=CGraphicsContext::ESolidBrush;

    iBrushColor = iEikonEnv->ControlColor(EColorWindowBackground, *this);

    iLabel = new (ELeave) CEikLabel;
    iLabel->SetContainerWindowL(*this);

    ActivateL();

    __TEST_INVARIANT;
    }


CSoundView::~CSoundView()
    {
    delete iLabel;
    iLabel = NULL;
    }


void CSoundView::Draw(const TRect& /*aRect*/) const
    {
    __TEST_INVARIANT;

    CWindowGc& gc = SystemGc();

    TRect drawRect=Rect();
    drawRect.Shrink(10,10);
    gc.DrawRect(drawRect);

    __TEST_INVARIANT;
    }

TInt CSoundView::CountComponentControls() const
    {
    __TEST_INVARIANT;

    return 1; 
    }

CCoeControl* CSoundView::ComponentControl(TInt aIndex) const
    {

    switch(aIndex)
        {
    case 0:
        return iLabel;
    default:
        __ASSERT_ALWAYS(EFalse, User::Panic(_L("CSoundView"), KSoundPanicBadParameter));
        return 0;
        }
    }

void CSoundView::SizeChanged()
    {
    TRect rect=Rect();

    TSize labelSize=iLabel->MinimumSize();
    rect.iTl.iX+=(rect.Width()-labelSize.iWidth)/2;
    rect.iTl.iY+=(rect.Height()-labelSize.iHeight)/2;
    rect.iBr=rect.iTl+labelSize;

    iLabel->SetRect(rect);

    __TEST_INVARIANT;
    }

void CSoundView::NotifyStatusL(const TDesC& aMessage)
    {
    __TEST_INVARIANT;

    iLabel->SetTextL(aMessage);
    SizeChanged();
    
    __TEST_INVARIANT;
    }

void CSoundView::__DbgTestInvariant() const
    {
    __ASSERT_DEBUG(iLabel, User::Panic(_L("CSoundView"), KSoundPanicInvariant));
    }



