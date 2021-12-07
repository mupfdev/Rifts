// Fonts.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.

#include "FontsGraphicsControl.h"
#include <coemain.h>

CFontControl::CFontControl() {
	// find the number of typefaces
	iNumTypefaces = iCoeEnv->ScreenDevice()->NumTypefaces();
	// set the number of phases to the number of typefaces
	SetMaxPhases(iNumTypefaces);
}

void CFontControl::UpdateModelL()
	{
	// set up zoom factor & graphics device map for getting fonts and drawing text
	iZoomFactor.SetGraphicsDeviceMap(iCoeEnv->ScreenDevice());
	iZoomFactor.SetZoomFactor(TZoomFactor::EZoomOneToOne);
	iDeviceMap = &iZoomFactor;

	// find the font to display this phase
	TTypefaceSupport* myTypefaceSupport = new TTypefaceSupport;
	iCoeEnv->ScreenDevice()->TypefaceSupport(*myTypefaceSupport,Phase());
	iCurrentFont = myTypefaceSupport->iTypeface.iName.Des();

	// set up descriptor for commentary area
	_LIT(KFormat,"Typeface index=%d. Name=%S. Num heights=%d. (Num typefaces=%d)");
	TBuf<128> commentaryText;
	commentaryText.Format(KFormat,Phase(),&iCurrentFont,myTypefaceSupport->iNumHeights,iNumTypefaces);
	iGraphObserver->NotifyStatus(commentaryText);
	delete myTypefaceSupport;
	};

void CFontControl::Draw(const TRect& /* aRect */) const
	{
	// setup screen for example
	CWindowGc& gc=SystemGc();
	gc.Clear();	
	
	// create a centered rectangle of the default size
	TRect screenRect=Rect();

	// set up absolute font-spec and text box for 300 twip Roman font
	TFontSpec fontSpec(iCurrentFont,300);
	// find the nearest font to the specified one
	CFont* screenFont;										
	iDeviceMap->GetNearestFontInTwips(screenFont,fontSpec);
	// use it for this graphics context
	gc.UseFont(screenFont);

	// get height of screen box
    TInt screenHeight=screenRect.Height();
	// get font height
    TInt textHeight = screenFont->HeightInPixels();

	// set up the positioning of the character set rows
	TInt exampleMargin = 0;
	TInt currentOffset = ((screenHeight+textHeight)/2) - (TInt)(textHeight*2.4);

	// set up descriptors for each row of the ASCII character set
	TBuf<50> buffer;
	TInt endPoint[6] = {64,96,138,182,216,255};
	TInt count = 32;
	for(TInt pass=0;pass<=5;pass++) {
		while (count<=endPoint[pass]) {
			buffer.Append((TUint)count);
			count++;
		}
		// draw the row in the current font
		gc.DrawText(buffer,screenRect,currentOffset,CGraphicsContext::ECenter,exampleMargin);	
		currentOffset = currentOffset + (TInt)(textHeight*1.2);
		buffer.Zero();
	}

	// discard and release font
	gc.DiscardFont();
	iDeviceMap->ReleaseFont(screenFont);	
	}
