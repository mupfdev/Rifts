// Bitmap.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.

#include "BitmapsGraphicsControl.h"

// header for multi-bitmap file grbitmap.mbm containing 2 bitmaps to use
#include <grbmap.mbg>

_LIT(KTxtCDrive,"C:");
_LIT(KTxtZDrive,"Z:");

void CBitmapControl::LoadBitmapL(CFbsBitmap* aBitMap,const TDesC& aPathAndFile,TInt aId,TBool aShareIfLoaded)
	{
	TParse mbfn;
	
	mbfn.Set(aPathAndFile,&KTxtCDrive,NULL);
	if (!aBitMap->Load(mbfn.FullName(),aId,aShareIfLoaded))
		return;

	mbfn.Set(aPathAndFile,&KTxtZDrive,NULL);
	User::LeaveIfError(aBitMap->Load(mbfn.FullName(),aId,aShareIfLoaded));
	return;
	}

	
	// Text printed to the console
_LIT(KTxtCase0,"draw bitmap, centered on screen using block transfer");
_LIT(KTxtCase1,"draw piece of bitmap using block transfer");
_LIT(KTxtCase2,"draw bitmap described in twips using DrawBitmap()");
_LIT(KTxtCase3,"draw stretched bitmap");
_LIT(KTxtCase4,"tile rectangle, using bitmap as the brush pattern");
_LIT(KTxtCase5,"tile rectangle, tiling around center of screen");
_LIT(KTxtCase6,"masks: the problem of drawing a bitmap on different backgrounds");
_LIT(KTxtCase7,"masks: using a mask to give a bitmap a transparent background");

	// The name of the multi-bitmap file containing the bitmap
	// and bitmap mask files.
_LIT(KTxtMBMname,"\\system\\apps\\BitmapsShell\\grbmap.mbm");

void CBitmapControl::UpdateModelL()
	{
		// set up name for bitmap sharing
	TBool shareIfLoaded(ETrue);
	
		switch (Phase())
		{
		case 0:
			// load the bitmap and mask bitmap
			iBitmap = new (ELeave) CFbsBitmap();
			LoadBitmapL(iBitmap,KTxtMBMname,EMbmGrbmapSmiley,shareIfLoaded);
			iMaskBitmap = new (ELeave) CFbsBitmap();
			LoadBitmapL(iMaskBitmap,KTxtMBMname,EMbmGrbmapSmilmask,shareIfLoaded);
			iGraphObserver->NotifyStatus(KTxtCase0);
			break;
		case 1:
			iGraphObserver->NotifyStatus(KTxtCase1);
			break;
		case 2:
			iGraphObserver->NotifyStatus(KTxtCase2);
			break;
		case 3:
			iGraphObserver->NotifyStatus(KTxtCase3);
			break;
		case 4:
			iGraphObserver->NotifyStatus(KTxtCase4);
			break;
		case 5:
			iGraphObserver->NotifyStatus(KTxtCase5);
			break;
		case 6:
			iGraphObserver->NotifyStatus(KTxtCase6);
			break;
		case 7:
			iGraphObserver->NotifyStatus(KTxtCase7);
			break;
		}
	}

void CBitmapControl::Draw(const TRect& /* aRect */) const
	{
	// draw surrounding rectangle
	CWindowGc& gc=SystemGc(); // graphics context we draw to
	gc.UseFont(iMessageFont); // use the system message font
	gc.Clear(); // clear the area to be drawn to
	SystemGc().DrawRect(Rect()); // surrounding rectangle to draw into
	TRect rect=Rect(); // a centered rectangle of the default size
	TRect bmpPieceRect=Rect(); // a rectangle to define a piece of bitmap
	TInt xDelta=0; // for x coordinates
	TInt yDelta=0; // for y coordinates
	TPoint screenCenterPoint=rect.Center(); // the center of the screen
	
	// decide what to do, and do it
	switch (Phase())
		{
		case 0:
			// draw a whole bitmap centered on the screen,
			// using bitmap block transfer
			{
			// calculate position for top left of bitmap so it is centered
			TSize bmpSizeInPixels=iBitmap->SizeInPixels();
			xDelta=(rect.Width()-bmpSizeInPixels.iWidth)/2;
			yDelta=(rect.Height()-bmpSizeInPixels.iHeight)/2;
			TPoint pos=TPoint(xDelta,yDelta); // displacement vector
			pos+=rect.iTl; // bitmap top left corner position
			gc.BitBlt(pos, iBitmap); // CWindowGc member function
			}
			break;
		case 1:
			// draw a rectangular piece of a bitmap, centered on the screen,
			// using bitmap block transfer
			{
			// calculate bitmap piece, half size from center of source bitmap
			TSize bmpSizeInPixels=iBitmap->SizeInPixels();
			TSize bmpPieceSize(bmpSizeInPixels.iWidth*2/3,bmpSizeInPixels.iHeight*2/3);
			TPoint bmpPieceTopLeft(0,0); 
			bmpPieceRect.SetRect(bmpPieceTopLeft,bmpPieceSize); 
			// calculate position for top left of bitmap piece so it is centered
			xDelta=(rect.Width()-bmpPieceRect.Width())/2;
			yDelta=(rect.Height()-bmpPieceRect.Height())/2;
			TPoint pos=TPoint(xDelta,yDelta); // displacement vector
			pos+=rect.iTl; // bitmap piece top left corner position
			gc.BitBlt(pos, iBitmap, bmpPieceRect); // using bitmap piece
			}
			break;
		case 2:
			// draw a bitmap to a defined size in twips
			// in the top left corner the rectangle,
			// using the GDI DrawBitmap() function
			{
			TSize bmpSizeInTwips(600,600); // must set twips size, default (0,0)
			iBitmap->SetSizeInTwips(bmpSizeInTwips);
			gc.DrawBitmap(rect.iTl, iBitmap);
			}
			break;
		case 3:
			// draw a stretched bitmap inside the rectangle,
			// using the GDI DrawBitmap() function
			{
			gc.DrawBitmap(rect, iBitmap);
			}
			break;
		case 4:
			{
			// use bitmap as brush pattern, tiling from top left of rectangle
			// set brush pattern and style to use the bitmap
			gc.UseBrushPattern(iBitmap);
			gc.SetBrushStyle(CGraphicsContext::EPatternedBrush);
			gc.DrawRect(rect);
			gc.DiscardBrushPattern();
			}
			break;
		case 5:
			{
			// use bitmap as brush pattern, tiling around center of screen
			// set brush pattern and style to use the bitmap
			gc.SetBrushOrigin(screenCenterPoint);
			gc.UseBrushPattern(iBitmap);
			gc.SetBrushStyle(CGraphicsContext::EPatternedBrush);
			gc.DrawRect(rect);
			gc.DiscardBrushPattern();
			}
			break;
		case 6:
			// bisect screen into two different coloured rects
			{
			TRect screenRect=Rect();
			TInt bisect = (screenRect.iBr.iX-screenRect.iTl.iX)/2 + screenRect.iTl.iX;
			TRect leftRect(screenRect.iTl,TPoint(bisect,screenRect.iBr.iY));
			TRect rightRect(TPoint(bisect,screenRect.iTl.iY),screenRect.iBr);
			TRgb darkGray(85,85,85);
			gc.SetBrushColor(darkGray);
			gc.Clear(leftRect);
			TRgb black(0,0,0);
			gc.SetBrushColor(black);
			gc.Clear(rightRect);

			TSize bmpSizeInPixels=iBitmap->SizeInPixels();
			TSize bmpPieceSize(bmpSizeInPixels.iWidth,bmpSizeInPixels.iHeight);
			TPoint bmpPieceTopLeft(0,0); 
			bmpPieceRect.SetRect(bmpPieceTopLeft,bmpPieceSize); 
			
			// center bitmap on left
			xDelta=(leftRect.Width()-bmpPieceRect.Width())/2;
			yDelta=(leftRect.Height()-bmpPieceRect.Height())/2;
			TPoint pos=TPoint(xDelta,yDelta); // displacement vector
			pos += leftRect.iTl; // bitmap piece top left corner position
			gc.BitBlt(pos,iBitmap);

			// center bitmap on right
			xDelta=(rightRect.Width()-bmpPieceRect.Width())/2;
			yDelta=(rightRect.Height()-bmpPieceRect.Height())/2;
			TPoint pos2=TPoint(xDelta,yDelta); // displacement vector
			pos2 += rightRect.iTl; // bitmap piece top left corner position
			gc.BitBlt(pos2,iBitmap);
			}
			break;
		case 7:
			// bisect screen into two different coloured rects
			{
			TRect screenRect=Rect();
			TInt bisect = (screenRect.iBr.iX-screenRect.iTl.iX)/2 + screenRect.iTl.iX;
			TRect leftRect(TPoint(screenRect.iTl.iX,screenRect.iTl.iY+50),TPoint(bisect,screenRect.iBr.iY));
			TRect rightRect(TPoint(bisect,screenRect.iTl.iY+50),screenRect.iBr);
			TRgb darkGray(85,85,85);
			gc.SetBrushColor(darkGray);
			gc.Clear(leftRect);
			TRgb black(0,0,0);
			gc.SetBrushColor(black);
			gc.Clear(rightRect);

			TSize bmpSizeInPixels=iBitmap->SizeInPixels();
			TSize bmpPieceSize(bmpSizeInPixels.iWidth,bmpSizeInPixels.iHeight);
			TPoint bmpPieceTopLeft(0,0); 
			bmpPieceRect.SetRect(bmpPieceTopLeft,bmpPieceSize); 
			
			// center bitmap on left
			xDelta=(leftRect.Width()-bmpPieceRect.Width())/2;
			yDelta=(leftRect.Height()-bmpPieceRect.Height())/2;
			TPoint pos=TPoint(xDelta,yDelta); // displacement vector
			pos += leftRect.iTl; // bitmap piece top left corner position
			gc.BitBltMasked(pos,iBitmap,bmpPieceRect,iMaskBitmap,EFalse); // CWindowGc member function

			// center bitmap on right
			xDelta=(rightRect.Width()-bmpPieceRect.Width())/2;
			yDelta=(rightRect.Height()-bmpPieceRect.Height())/2;
			TPoint pos2=TPoint(xDelta,yDelta); // displacement vector
			pos2 += rightRect.iTl; // bitmap piece top left corner position
			gc.BitBltMasked(pos2,iBitmap,bmpPieceRect,iMaskBitmap,EFalse); // CWindowGc member function
			
			_LIT(KTxtTheBitmap,"The bitmap:");
			_LIT(KTxtBitmapMask,"The bitmap's mask:");

			gc.DrawText(KTxtTheBitmap,TPoint(5,20));
			gc.BitBlt(TPoint(130,0),iBitmap);
			gc.DrawText(KTxtBitmapMask,TPoint(197,20));
			gc.BitBlt(TPoint(400,0),iMaskBitmap);
			}
			break;
		default:
			break;
		}
   	}
