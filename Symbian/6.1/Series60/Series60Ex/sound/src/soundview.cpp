// Copyright (c) 2001, Nokia. All rights reserved.

#include <eikenv.h>
#include <eikdef.h>
#include <eiklabel.h>
#include <gulcolor.h>

#include "sound.pan"
#include "SoundView.h"
#include "SoundDoc.h"

// Standard Epoc construction sequence
CSoundView* CSoundView::NewL(const TRect& aRect, const TDesC& aMessage)
    {
    CSoundView* self = CSoundView::NewLC(aRect, aMessage);
    CleanupStack::Pop();
    return self;
    }

CSoundView* CSoundView::NewLC(const TRect& aRect, const TDesC& aMessage)
    {
    CSoundView* self = new (ELeave) CSoundView();
    CleanupStack::PushL(self);
    self->ConstructL(aRect, aMessage);
    return self;
    }

void CSoundView::ConstructL(const TRect& aRect, const TDesC& aMessage)
    {
    // Create a window for this application view
    CreateWindowL();

    iContext = this;
    iBrushStyle = CGraphicsContext::ESolidBrush;

    iBrushColor = iEikonEnv->ControlColor(EColorWindowBackground, *this);

    iLabel = new (ELeave) CEikLabel;
    iLabel->SetContainerWindowL(*this);
    iLabel->SetTextL(aMessage);

    // Set the windows size
    SetRect(aRect);

    // Activate the window, which makes it ready to be drawn
    ActivateL();

    }


CSoundView::~CSoundView()
    {
    delete iLabel;
    iLabel = NULL;
    }


CSoundView::CSoundView()
    {
    }


void CSoundView::Draw(const TRect& /*aRect*/) const
    {
    CWindowGc& gc = SystemGc();
    gc.Clear(Rect());
    }

TInt CSoundView::CountComponentControls() const
    {
    return 1; 
    }

CCoeControl* CSoundView::ComponentControl(TInt aIndex) const
    {

    switch(aIndex)
        {
    case 0:
        return iLabel;
    default:
        __ASSERT_ALWAYS(EFalse, User::Panic(KSound, KSoundPanicBadParameter));
        return 0;
        }
    }

void CSoundView::SizeChanged()
    {
    TRect rect = Rect();

    TSize labelSize = iLabel->MinimumSize();
    rect.iTl.iX += (rect.Width() - labelSize.iWidth) / 2;
    rect.iTl.iY += (rect.Height() - labelSize.iHeight) / 2;
    rect.iBr = rect.iTl + labelSize;

    iLabel->SetRect(rect);
    }

void CSoundView::NotifyStatusL(const TDesC& aMessage)
    {
    iLabel->SetTextL(aMessage);
    SizeChanged();
    }


