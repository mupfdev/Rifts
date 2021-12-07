// Draw.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.

#include "GraphicsControl.h"

#include <coemain.h>

// Text printed to the console in UpdateModeL()
_LIT(KTxtUpdateModelCase0,"point in center of screen");
_LIT(KTxtUpdateModelCase1,"bolder point in center of screen");
_LIT(KTxtUpdateModelCase2,"really bold point in center of screen");
_LIT(KTxtUpdateModelCase3,"a line");
_LIT(KTxtUpdateModelCase4,"a thicker line");
_LIT(KTxtUpdateModelCase5,"really thick - note round ends and clipping");
_LIT(KTxtUpdateModelCase6,"dotted line");
_LIT(KTxtUpdateModelCase7,"dot-dash line");
_LIT(KTxtUpdateModelCase8,"triangle using relative drawing");
_LIT(KTxtUpdateModelCase9,"thick triangle - note rounded corners");
_LIT(KTxtUpdateModelCase10,"dotted triangle - note pattern continuation");
_LIT(KTxtUpdateModelCase11,"centered ellipse");
_LIT(KTxtUpdateModelCase12,"arc - part of ellipse");
_LIT(KTxtUpdateModelCase13,"arc - other part - see also construction elements");
_LIT(KTxtUpdateModelCase14,"pie slices");
_LIT(KTxtUpdateModelCase15,"centered rectangle with rounded corners");
_LIT(KTxtUpdateModelCase16,"rounded rectangle showing corner ellipse");
_LIT(KTxtUpdateModelCase17,"polyline");
_LIT(KTxtUpdateModelCase18,"polygon with winding-fill rule");
_LIT(KTxtUpdateModelCase19,"polygon using alternate-fill rule");
_LIT(KTxtUpdateModelCase20,"copying using CopyRect()");
_LIT(KTxtUpdateModelCase21,"left-justified boxed text");
_LIT(KTxtUpdateModelCase22,"centered boxed text");
_LIT(KTxtUpdateModelCase23,"right-justified offset text");
_LIT(KTxtUpdateModelCase24,"cross-hatched box");
_LIT(KTxtUpdateModelCase25,"teeny preview font!");
_LIT(KTxtUpdateModelDefault,"overran!");
	
void CDrawControl::UpdateModelL()
	{
	switch (Phase())
		{
		case 0:
			iGraphObserver->NotifyStatus(KTxtUpdateModelCase0);
			break;
		case 1:
			iGraphObserver->NotifyStatus(KTxtUpdateModelCase1);
			break;
		case 2:
			iGraphObserver->NotifyStatus(KTxtUpdateModelCase2);
			break;
		case 3:
			iGraphObserver->NotifyStatus(KTxtUpdateModelCase3);
			break;
		case 4:
			iGraphObserver->NotifyStatus(KTxtUpdateModelCase4);
			break;
		case 5:
			iGraphObserver->NotifyStatus(KTxtUpdateModelCase5);
			break;
		case 6:
			iGraphObserver->NotifyStatus(KTxtUpdateModelCase6);
			break;
		case 7:
			iGraphObserver->NotifyStatus(KTxtUpdateModelCase7);
			break;
		case 8:
			iGraphObserver->NotifyStatus(KTxtUpdateModelCase8);
			break;
		case 9:
			iGraphObserver->NotifyStatus(KTxtUpdateModelCase9);
			break;
		case 10:
			iGraphObserver->NotifyStatus(KTxtUpdateModelCase10);
			break;
		case 11:
			iGraphObserver->NotifyStatus(KTxtUpdateModelCase11);
			break;
		case 12:
			iGraphObserver->NotifyStatus(KTxtUpdateModelCase12);
			break;
		case 13:
			iGraphObserver->NotifyStatus(KTxtUpdateModelCase13);
			break;
		case 14:
			iGraphObserver->NotifyStatus(KTxtUpdateModelCase14);
			break;
		case 15:
			iGraphObserver->NotifyStatus(KTxtUpdateModelCase15);
			break;
		case 16:
			{
			iGraphObserver->NotifyStatus(KTxtUpdateModelCase16);
			}
			break;
		case 17:
			iGraphObserver->NotifyStatus(KTxtUpdateModelCase17);
			break;
		case 18:
			iGraphObserver->NotifyStatus(KTxtUpdateModelCase18);
			break;
		case 19:
			iGraphObserver->NotifyStatus(KTxtUpdateModelCase19);
			break;
		case 20:
			{
			iGraphObserver->NotifyStatus(KTxtUpdateModelCase20);
			}
			break;
		case 21:
			iGraphObserver->NotifyStatus(KTxtUpdateModelCase21);
			break;
		case 22:
			iGraphObserver->NotifyStatus(KTxtUpdateModelCase22);
			break;
		case 23:
			iGraphObserver->NotifyStatus(KTxtUpdateModelCase23);
			break;
		case 24:
			iGraphObserver->NotifyStatus(KTxtUpdateModelCase24);
			break;
		case 25:
			iGraphObserver->NotifyStatus(KTxtUpdateModelCase25);
			break;
		default:
			iGraphObserver->NotifyStatus(KTxtUpdateModelDefault);
			break;
		}
	}


// Text printed to the console in UpdateModeL()
_LIT(KTxtDrawCase21,"White text left justified in dark gray box");
_LIT(KTxtDrawCase22,"White text centered in black box");
_LIT(KTxtDrawCase23,"Dark gray text right justified in lite gray box");
_LIT(KTxtDrawCase25,"This text overwrites the cleared area");

	
void CDrawControl::Draw(const TRect& /* aRect */) const
	{
	// put the next line back in to see the individual drawing actions
	// (iCoeEnv->WsSession()).SetAutoFlush(ETrue);
	// draw surrounding rectangle
	CWindowGc& gc=SystemGc(); // graphics context we draw to
	gc.UseFont(iMessageFont); // use the system message font
	gc.Clear();
	SystemGc().DrawRect(Rect()); // surrounding rectangle to draw into
	TRect rect=Rect(); // a centered rectangle of the default size
	TRect ellipseRect=Rect(); // for arcs and ellipse
	ellipseRect.Shrink(10,10); // set size so inside the border rectangle
	TRect box=Rect(); // a smaller centered rectangle, for text in a box
	box.Shrink(10,10); // set size of text box
	TRect tinyBox=Rect(); // a tiny box to clear
	tinyBox.Shrink(220,90); // set size of tiny box to clear
	TInt offset=0; // offset, for text in a box
	TPoint screenCenterPoint=rect.Center(); // the center of the screen 
	// set up a pair of construction points for arc and pie slice drawing
	// set up the size for half a screen (divided vertically)
	TPoint constructionPoint1(15,15); // outside the construction ellipse
	TPoint constructionPoint2(200,150); // inside the construction ellipse
	// set up a pair of points for drawing diagonal lines
	TPoint startPoint(50,50);
	TPoint endPoint(590,190);
	// set up an array of points for drawing a polyline and a polygon etc
	// will be used relative to top left of rectangle
	TPoint point1(20,20);
	TPoint point2(100,190);
	TPoint point3(110,90);
	TPoint point4(50,150);
	TPoint point5(200,150);
	CArrayFix<TPoint>* mypoints;
	mypoints = new CArrayFixFlat<TPoint>(5);
	mypoints->AppendL(point1);
	mypoints->AppendL(point2);
	mypoints->AppendL(point3);
	mypoints->AppendL(point4);
	mypoints->AppendL(point5);
	// set up a black, a dark gray, a lite gray and a white RGB color
	TRgb black(0,0,0);
	TRgb darkGray(85,85,85);
	TRgb liteGray(170,170,170);
	TRgb white(255,255,255); // appears as blank screen gray-green color
	// Set up a "bold" size for the pen tip to (default is 1,1)
	TSize penSizeBold(3,3);
	// Set up a "fat" size for the pen tip
	TSize penSizeFat(30,30);
	// decide what to do, and do it
	switch (Phase())
		{
		case 0:
			// draw a single pixel point in the center of the screen
			// it is so small that some text is needed to explain the screen...
			gc.Plot(screenCenterPoint);
			break;
		case 1:
			// draw a "bold" point 3 pixels across
 			gc.SetPenSize(penSizeBold);
			gc.Plot(screenCenterPoint);
			break;
		case 2:
			// draw a "fat" point (circular blob),
			// illustrating the effect of a very wide pen
 			gc.SetPenSize(penSizeFat);
			gc.Plot(screenCenterPoint);
			break;
		case 3:
			// draw a thin line fromtop left to bottom right
			gc.DrawLine(startPoint,endPoint);
			break;
		case 4:
			// draw a "bold" line fromtop left to bottom right
 			gc.SetPenSize(penSizeBold);
			gc.DrawLine(startPoint,endPoint);
			break;
		case 5:
			// draw a rather wide line from top left to bottom right,
			// illustrating rounded ends and their clipping
 			gc.SetPenSize(penSizeFat);
			gc.DrawLine(startPoint,endPoint);
			break;
		case 6:
			// draw a dotted line from top left to bottom right
			gc.SetPenStyle(CGraphicsContext::EDottedPen);
			gc.DrawLine(startPoint,endPoint);
			break;
		case 7:
			// draw a dot-dash line from top left to bottom right
			gc.SetPenStyle(CGraphicsContext::EDotDashPen);
			gc.DrawLine(startPoint,endPoint);
			break;
		case 8:
			// draw a triangle by relative drawing
			gc.MoveTo(TPoint(300,50)); // drawing position (300,50)
			gc.DrawLineBy(TPoint(205,100)); // drawing position (505,150)
			gc.DrawLineBy(TPoint(-410,0)); // drawing position (95,150)
			gc.DrawLineBy(TPoint(205,-100)); // drawing position (300,50)
			break;
		case 9:
 			// draw a triangle, by relative drawing
 			// illustrating rounded ends at corners when using very wide lines
			gc.SetPenSize(penSizeFat);
			gc.MoveTo(TPoint(300,50)); // drawing position (300,50)
			gc.DrawLineBy(TPoint(205,100)); // drawing position (505,150)
			gc.DrawLineBy(TPoint(-410,0)); // drawing position (95,150)
			gc.DrawLineBy(TPoint(205,-100)); // drawing position (300,50)
			break;
		case 10:
			// draw a triangle by sequential drawing between specified points,
			// using dot-dash line style, illustrating line pattern continuation 
			gc.SetPenStyle(CGraphicsContext::EDotDashPen);
			gc.MoveTo(TPoint(300,50)); // drawing position (300,50)
			gc.DrawLineTo(TPoint(505,150)); // drawing position (505,150)
			gc.DrawLineTo(TPoint(95,150)); // drawing position (95,150)
			gc.DrawLineTo(TPoint(300,50)); // drawing position (300,50)
			break;
		case 11:
			// draw an ellipse centered in the rectangle
			gc.DrawEllipse(ellipseRect);
			break;
		case 12:
			// draw an arc centered in the rectangle
			gc.DrawArc(ellipseRect,constructionPoint1,constructionPoint2);
			// gc.Clear();
			break;
		case 13:
			// draw an arc centered in the rectangle that is the other
			// portion of the ellipse (arguments reversed)
			gc.DrawArc(ellipseRect,constructionPoint2,constructionPoint1);
			// draw construction lines and points
			gc.SetPenStyle(CGraphicsContext::EDottedPen);
			gc.MoveTo(constructionPoint1);
			gc.DrawLineTo(screenCenterPoint);
			gc.DrawLineTo(constructionPoint2);
 			gc.SetPenSize(penSizeBold);
			gc.Plot(constructionPoint1);
			gc.Plot(constructionPoint2);
			gc.Plot(screenCenterPoint);
			break;
		case 14:
			// draw a pie slice centered in the rectangle
			gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
			gc.SetBrushColor(white);
			gc.DrawPie(ellipseRect,constructionPoint1,constructionPoint2);
			// draw the other portion of the elliptical disc
			gc.SetBrushStyle(CGraphicsContext::EVerticalHatchBrush);
			gc.DrawPie(ellipseRect,constructionPoint2,constructionPoint1);
			break;
		case 15:
			{
			// draw a rectangle with rounded corners, centered in the rectangle
			TSize cornerSize(20,20); // size of a rounded corner
			gc.DrawRoundRect(box,cornerSize); // same rect as text box
			}
			break;
		case 16:
			{
			// draw a rectangle with rounded corners,
			//centered in the rectangle, showing a corner ellipse
			TSize cornerSize(20,20); // size of a rounded corner
			// rect for corner ellipse is twice the corner size
			TSize cornerEllipseSize(cornerSize.iHeight*2,cornerSize.iWidth*2);
			TRect cornerRectTl(box.iTl,cornerEllipseSize);
			gc.DrawRoundRect(box,cornerSize);
			gc.SetPenStyle(CGraphicsContext::EDottedPen);
			gc.DrawEllipse(cornerRectTl); // corner construction ellipse
			}
			break;
		case 17:
			// draw a polyline
			gc.DrawPolyLine(mypoints);
			break;
		case 18:
			// draw self-crossing polygon using the winding fill rule
			gc.SetBrushStyle(CGraphicsContext::ESquareCrossHatchBrush);
			gc.SetBrushColor(black);
			gc.DrawPolygon(mypoints,CGraphicsContext::EWinding);
			break;
		case 19:
			// draw self-crossing polygon using the alternate fill rule
			gc.SetBrushStyle(CGraphicsContext::EDiamondCrossHatchBrush);
			gc.SetBrushColor(black);
			gc.DrawPolygon(mypoints,CGraphicsContext::EAlternate);
			break;
		case 20:
			{
			// draw self-crossing polygon using the alternate fill rule,
			// and copy the lhs to the rhs of the screen
			gc.SetBrushStyle(CGraphicsContext::EDiamondCrossHatchBrush);
			gc.SetBrushColor(black);
			gc.DrawPolygon(mypoints,CGraphicsContext::EAlternate);
			TPoint screenOrigin(0,0); // top left of the screen
			TSize halfScreenLR(320,240); // size of vertical half of screen
			rect.SetRect(screenOrigin,halfScreenLR); // lhs of screen
			TPoint offset(halfScreenLR.iWidth,0); // half screen width offset
			gc.CopyRect(offset,rect); //  copy lhs of screen to rhs
			}
			break;
		case 21:
			// draw some text left justified in a box,
			// offset so text is just inside top of box
			{
			CFont* font=iMessageFont; // get the system message font
			TInt fontAscent(font->AscentInPixels()); // system message font ascent
			offset=fontAscent+3; // add a 3 pixel text line spacing
			TInt margin=2; // left margin is two pixels
			gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
			gc.SetBrushColor(darkGray);
			gc.SetPenColor(white);
			gc.UseFont(iMessageFont);
			gc.DrawText(KTxtDrawCase21,box,offset,CGraphicsContext::ELeft,margin);
			}
			break;
		case 22:
			// draw some text centered in a box, (margin is zero)
			{
			TInt boxHeight=box.Height(); // get height of text box
			CFont* font=iMessageFont; // get the system message font
			TInt textHeight(font->HeightInPixels()); // system message font height
			offset=(textHeight+boxHeight)/2; // 1/2 font ht below halfway down box
			TInt margin=0; // margin is zero
			gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
			gc.SetBrushColor(black);
			gc.SetPenColor(white);
			gc.UseFont(iMessageFont);
			gc.DrawText(KTxtDrawCase22,box,offset,CGraphicsContext::ECenter,margin);
			}
			break;
		case 23:
			// draw some text right justified in a box,
			// offset so text is just inside bottom of box
			{
			TInt boxHeight=box.Height(); // get height of text box
			CFont* font=iMessageFont; // get the system message font
			TInt fontDescent=font->DescentInPixels(); // system message font descent
			offset=boxHeight-fontDescent-3;// offset, 3 pixel text line spacing 
			TInt margin=2; // right margin is two pixels
			gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
			gc.SetBrushColor(liteGray);
			gc.SetPenColor(darkGray);
			gc.UseFont(iMessageFont);
			gc.DrawText(KTxtDrawCase23,box,offset,CGraphicsContext::ERight,margin);
			}
			break;
		case 24:
			{
			// draw a cross-hatched box
			// then clear a small central rectangle
			gc.SetBrushColor(darkGray);
			gc.SetBrushStyle(CGraphicsContext::ESquareCrossHatchBrush);
			gc.DrawRect(rect);
			// clear a small rectangle
			gc.SetBrushColor(liteGray); // change the brush color
			gc.Clear(tinyBox); // clear to brush color
			}
			break;
		case 25:
			{
			// draw a cross-hatched box
			// then clear a small central rectangle
			// and write some text in it in smallest Swiss font,
			// (which is actually a tiny "block" print-preview font)
			// starting bottom left (illustrating flicker, overlap, mess)
			gc.SetBrushColor(darkGray);
			gc.SetBrushStyle(CGraphicsContext::ESquareCrossHatchBrush);
			gc.DrawRect(rect);
			// clear a small rectangle
			gc.SetBrushColor(liteGray); // change the brush color
			gc.Clear(tinyBox); // clear to brush color
			// get an alternative font
			CFont* myFont;
			_LIT(KTxtArial,"Arial");
			TFontSpec myFontSpec(KTxtArial,1); // to get smallest Arial font
			CGraphicsDevice* screenDevice=(iCoeEnv->ScreenDevice());
			screenDevice->GetNearestFontInTwips(myFont,myFontSpec);
			gc.UseFont(myFont);
			// set the text drawing position & draw (demonstrating flicker)
			TInt fontDescent=myFont->DescentInPixels();
			TPoint pos(0,tinyBox.Height()-fontDescent);
			pos+=tinyBox.iTl;
			gc.DrawText(KTxtDrawCase25,pos);
			// discard and destroy the font
			gc.DiscardFont();
			screenDevice->ReleaseFont(myFont);
			}
			break;
		default:
			break;
		}
	delete mypoints; // an array must be destroyed after use
   	}
