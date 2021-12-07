// Zoom.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.

#include "GraphicsControl.h"
// header for multi-bitmap file grbitmap.mbm containing 2 bitmaps to use
#include <grbmap2.mbg>

#include <coemain.h>

_LIT(KTxtCDrive,"C:");
_LIT(KTxtZDrive,"Z:");

void CZoomControl::LoadBitmapL(CFbsBitmap* aBitMap,const TDesC& aPathAndFile,TInt aId,TBool aShareIfLoaded)
	{
	TParse mbfn;
	
	mbfn.Set(aPathAndFile,&KTxtCDrive,NULL);
	if (!aBitMap->Load(mbfn.FullName(),aId,aShareIfLoaded))
		return;

	mbfn.Set(aPathAndFile,&KTxtZDrive,NULL);
	User::LeaveIfError(aBitMap->Load(mbfn.FullName(),aId,aShareIfLoaded));
	return;
	}

// Name of the multi-bitmap file containing the bitmap
// and bitmap mask files
_LIT(KTxtFileName,"\\system\\apps\\GraphicsShell\\grbmap2.mbm");

void CZoomControl::UpdateModelL()
	{
	// set up name for bitmap sharing
	TBool shareIfLoaded(ETrue);

	// set up two zoom factor objects (one for examples, one for commentary)
	iLeftZf.SetGraphicsDeviceMap(iCoeEnv->ScreenDevice());
	iRightZf.SetGraphicsDeviceMap(iCoeEnv->ScreenDevice());
	//iLeftZf.SetDevice(iCoeEnv->ScreenDevice());
	//iRightZf.SetDevice(iCoeEnv->ScreenDevice());
	
	// set the zoom factor of the objects (example is dependent on phase of example, commentary is fixed)
	iLeftZf.SetZoomFactor(TZoomFactor::EZoomOneToOne*2*(Phase()+1)/5);
	iRightZf.SetZoomFactor(TZoomFactor::EZoomOneToOne*2*(5-Phase())/5);

	// use graphics device maps for drawing and getting fonts
	iLeftMap=&iLeftZf;
	iRightMap=&iRightZf;

	if (Phase()==0) {
		iBitmap = new (ELeave) CFbsBitmap();
		LoadBitmapL(iBitmap,KTxtFileName,EMbmGrbmap2Smiley,shareIfLoaded);
	}
	
	// set up descriptor for commentary area
	_LIT(KFormat1,"Left zoom factor=%1.1f:1  Right zoom factor=%1.1f:1");
	TBuf<128> commentaryText;
	TReal leftValue = 2*(Phase()+1)/5.0;
	TReal rightValue = 2*(5-Phase())/5.0;
	commentaryText.Format(KFormat1,leftValue,rightValue);
	iGraphObserver->NotifyStatus(commentaryText);
	};

void CZoomControl::Draw(const TRect& /* aRect */) const
	{
	// setup screen for example: get graphics context and draw surrounding rectangle
	CWindowGc& gc=SystemGc();
	gc.Clear();	
	
	// create a centered rectangle of the default size
	TRect screenRect=Rect();
	TInt bisect = (screenRect.iBr.iX-screenRect.iTl.iX)/2 + screenRect.iTl.iX;
	TRect leftRect(screenRect.iTl,TPoint(bisect,screenRect.iBr.iY));
	TRect rightRect(TPoint(bisect,screenRect.iTl.iY),screenRect.iBr);

	DrawLeft(leftRect,gc);
	DrawRight(rightRect,gc);
   	}


	_LIT(KTxtTimesNewRoman,"Times New Roman");
	_LIT(KTxtGrzoomExampleText,"grzoom example text");

void CZoomControl::DrawLeft(TRect screenRect,CWindowGc& SystemGc) const
	{
	// set up absolute font-spec and text box for 200 twip Times font
	TFontSpec fontSpec(KTxtTimesNewRoman,200);
	// find the nearest font to the specified one
	CFont* screenFont;										
	iLeftMap->GetNearestFontInTwips(screenFont,fontSpec);
	// use it for this graphics context
	SystemGc.UseFont(screenFont);
	// get height of screen box
    TInt screenHeight=screenRect.Height();
	// get font height
    TInt textHeight = screenFont->HeightInPixels();
	// 1/2 font height below halfway down box
    TInt exampleOffset=(screenHeight+textHeight)/2;
    TInt exampleMargin=0;
    SystemGc.DrawText(KTxtGrzoomExampleText,screenRect,exampleOffset,CGraphicsContext::ECenter,exampleMargin);
	// discard and release font
	SystemGc.DiscardFont();
	iLeftMap->ReleaseFont(screenFont);	
	
	// set up example box in twips
	TRect boxInTwips(TPoint(0,0),TPoint(500,300));
	// convert rectangle co-ordinates into pixels
	TRect boxInPixels = iLeftMap->TwipsToPixels(boxInTwips);
	SystemGc.DrawRect(boxInPixels);

	// set up rectangle for bitmap to be stretched into
	TRect bitmapRectInTwips(TPoint(0,0),TPoint(500,500));
	TRect bitmapRectInPixels = iLeftMap->TwipsToPixels(bitmapRectInTwips);
	bitmapRectInPixels.iTl.iY+=125;
	bitmapRectInPixels.iBr.iY+=125;
	bitmapRectInPixels.iTl.iX+=100;
	bitmapRectInPixels.iBr.iX+=100;
	// draw the bitmap, stretched into the rectangle
	SystemGc.DrawBitmap(bitmapRectInPixels, iBitmap);
	}

void CZoomControl::DrawRight(TRect screenRect,CWindowGc& SystemGc) const
	{
	// set up colors: black and a white RGB color
	TRgb black(0,0,0);
	TRgb white(255,255,255); // appears as blank screen gray-green color
    SystemGc.SetBrushStyle(CGraphicsContext::ESolidBrush);
    SystemGc.SetBrushColor(black);
    SystemGc.SetPenColor(white);

	// set up absolute font-spec and text box for 200 twip Times font
	TFontSpec fontSpec(KTxtTimesNewRoman,200);
	// find the nearest font to the specified one
	CFont* commentFont;
	iRightMap->GetNearestFontInTwips(commentFont,fontSpec);
	// use it for this graphics context
	SystemGc.UseFont(commentFont);
	// get font height
    TInt textHeight = commentFont->HeightInPixels();
    // get height of text box
    TInt boxHeight=screenRect.Height();
	// 1/2 font height below halfway down box
    TInt commentOffset=(boxHeight+textHeight)/2;
    TInt commentMargin=0;
	// draw text
    SystemGc.DrawText(KTxtGrzoomExampleText,screenRect,commentOffset,CGraphicsContext::ECenter,commentMargin);
	// discard and release font
	SystemGc.DiscardFont();
	iRightMap->ReleaseFont(commentFont);
	
	// set up example box in twips
	TRect boxInTwips(TPoint(0,0),TPoint(500,300));
	// convert rectangle co-ordinates into pixels
	TRect boxInPixels = iRightMap->TwipsToPixels(boxInTwips);
	boxInPixels.Move(screenRect.iTl);
	SystemGc.DrawRect(boxInPixels);

	// set up rectangle for bitmap to be stretched into
	TRect bitmapRectInTwips(TPoint(0,0),TPoint(500,500));
	TRect bitmapRectInPixels = iRightMap->TwipsToPixels(bitmapRectInTwips);
	bitmapRectInPixels.Move(screenRect.iTl);
	bitmapRectInPixels.iTl.iY+=125;
	bitmapRectInPixels.iBr.iY+=125;
	bitmapRectInPixels.iTl.iX+=100;
	bitmapRectInPixels.iBr.iX+=100;
	// draw the bitmap, stretched into the rectangle
	SystemGc.DrawBitmap(bitmapRectInPixels, iBitmap);
	}
