// Hello.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.


#include "FontsGraphicsControl.h"

_LIT(KTxtUpdateModelEnglish,"English");
_LIT(KTxtUpdateModelFrench,"French");
_LIT(KTxtUpdateModelGerman,"German");
_LIT(KTxtUpdateModelItalian,"Italian");
_LIT(KTxtUpdateModelTurkish,"Turkish");
_LIT(KTxtUpdateModelJapanese,"Japanese");
_LIT(KTxtUpdateModelShakespearian,"Shakespearian");
_LIT(KTxtUpdateModelOverrun,"overrun!");

void CHelloControl::UpdateModelL()
	{
	switch(Phase())
		{
	case 0:
		iGraphObserver->NotifyStatus(KTxtUpdateModelEnglish);
		break;
	case 1:
		iGraphObserver->NotifyStatus(KTxtUpdateModelFrench);
		break;
	case 2:
		iGraphObserver->NotifyStatus(KTxtUpdateModelGerman);
		break;
	case 3:
		iGraphObserver->NotifyStatus(KTxtUpdateModelItalian);
		break;
	case 4:
		iGraphObserver->NotifyStatus(KTxtUpdateModelTurkish);
		break;
	case 5:
		iGraphObserver->NotifyStatus(KTxtUpdateModelJapanese);
		break;
	case 6:
		iGraphObserver->NotifyStatus(KTxtUpdateModelShakespearian);
		break;
	default:
		iGraphObserver->NotifyStatus(KTxtUpdateModelOverrun);
		break;
		};
	}

//Text literals
_LIT(KTxtDrawCase0,"Hello world!");
_LIT(KTxtDrawCase1,"Bonjour tout le monde!");
_LIT(KTxtDrawCase2,"Hallo aller Welt!");
_LIT(KTxtDrawCase3,"Buongiorno tutto il mondo!");
_LIT(KTxtDrawCase4,"Merhaba Dunyaya!");
_LIT(KTxtDrawCase5,"Ohayo gozaimasu!");
_LIT(KTxtDrawCase6,"Friends, Romans, Countrymen!");

void CHelloControl::Draw(const TRect& /* aRect */) const
	{
	// draw surrounding rectangle
	SystemGc().DrawRect(Rect());
	// calculate rectangle to draw into
	TRect rect=Rect();
	rect.Shrink(1,1);
	// calculate vertical centering
	CFont *font=iMessageFont;
	TInt ascent=
			(rect.Height() - font->HeightInPixels())/2 +
				font->AscentInPixels();
	// draw text in rectangle
	CWindowGc& gc=SystemGc();
   	gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
    gc.UseFont(iMessageFont);
	switch(Phase())
		{
	case 0:
		gc.DrawText(KTxtDrawCase0,rect,ascent, CGraphicsContext::ECenter, 0);
		break;
	case 1:
		gc.DrawText(KTxtDrawCase1,rect,ascent, CGraphicsContext::ECenter, 0);
		break;
	case 2:
		gc.DrawText(KTxtDrawCase2,rect,ascent, CGraphicsContext::ECenter, 0);
		break;
	case 3:
		gc.DrawText(KTxtDrawCase3,rect,ascent, CGraphicsContext::ECenter, 0);
		break;
	case 4:
		gc.DrawText(KTxtDrawCase4,rect,ascent, CGraphicsContext::ECenter, 0);
		break;
	case 5:
		gc.DrawText(KTxtDrawCase5,rect,ascent, CGraphicsContext::ECenter, 0);
		break;
	case 6:
		gc.DrawText(KTxtDrawCase6,rect,ascent, CGraphicsContext::ECenter, 0);
		break;
	default:
		break;
		};
   	}
