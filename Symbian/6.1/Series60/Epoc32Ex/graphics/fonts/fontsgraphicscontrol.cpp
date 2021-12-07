// FontsGraphicsControl.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.

#include "FontsGraphicsControl.h"

#include <coemain.h>
#include <coeaui.h>

_LIT(KtxtSwiss,"Swiss");

void CGraphicExampleControl::ConstructL(const TRect& aRect, MGraphicsExampleObserver* aGraphObserver, const CCoeControl& aParent)
	{
	// remember the graphics observer
	iGraphObserver=aGraphObserver;
	// create window
	CreateWindowL(&aParent);
	// construct font for messages
    TFontSpec spec(KtxtSwiss,213);
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
	iGraphObserver->NotifyGraphicExampleFinished();
	}

void CGraphicExampleControl::NextPhaseL()
	{
	if (++iPhase >= iMaxPhases)
		Quit();
	else
		{
		UpdateModelL();
		DrawNow();
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

