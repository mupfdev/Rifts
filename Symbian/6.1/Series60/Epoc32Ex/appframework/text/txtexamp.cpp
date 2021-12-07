// TXTEXAMP.CPP
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#include "txtexamp.h"

#include <coemain.h>
#include <coeaui.h>

void CGraphicExampleControl::ConstructL(const TRect& aRect, MGraphicsExampleObserver* aFormObserver,
			const CCoeControl& aParent)
	{
	_LIT(KFont,"Swiss");
	// remember observer
	iFormObserver=aFormObserver;
	// create window
	CreateWindowL(&aParent);
	// construct font for messages
    TFontSpec spec(KFont,213);
    iMessageFont=iCoeEnv->CreateScreenFontL(spec);
	// set rectangle to prescription
	SetRect(aRect);
	// go for it
	ActivateL();
	UpdateModelL(); // phase 0
	}

CGraphicExampleControl::~CGraphicExampleControl()
	{
	iCoeEnv->ReleaseScreenFont(iMessageFont);
	}

void CGraphicExampleControl::Quit()
	{
	iFormObserver->NotifyGraphicExampleFinished();
	}

void CGraphicExampleControl::NextPhaseL()
	{
	if (++iPhase >= iMaxPhases)
		Quit();
	else
		{
		UpdateModelL();
		if (!iUpdateModelDoesRedraw) DrawNow();
		}
	}

void CGraphicExampleControl::HandlePointerEventL(const TPointerEvent& aPointerEvent)
	{
	if (aPointerEvent.iType==TPointerEvent::EButton1Down) NextPhaseL();
	}

TKeyResponse CGraphicExampleControl::OfferKeyEventL(
			const TKeyEvent& aKeyEvent,TEventCode aType
			)
	{
	if (aType!=EEventKey) return EKeyWasNotConsumed;
	TInt code=aKeyEvent.iCode;
	switch (code)
		{
		case ' ':
			NextPhaseL();
			break;
		default:
			return EKeyWasNotConsumed;
		}
	return EKeyWasConsumed;
	}

