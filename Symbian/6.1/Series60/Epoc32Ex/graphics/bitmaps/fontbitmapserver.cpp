// FontBitmapServer.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.

#include "BitmapsGraphicsControl.h"

// header for multi-bitmap file grbitmap.mbm containing 2 bitmaps to use
#include <grbmap.mbg>


	// The name of the multi-bitmap file containing the bitmap
	// and bitmap mask files.
_LIT(KTxtMBMname,"\\system\\apps\\BitmapsShell\\grbmap.mbm");

CFbsControl::~CFbsControl()
{
	// as the user can exit the example at any phase
	// delete any member data that may cause a memory leak
	if (Phase()==1 || Phase()==7 || Phase()==8) delete(iBitmap1);
	if (Phase()==3 || Phase()==4) delete(iBitmap2);
	if (Phase()==4 || Phase()==5) delete(iBitmap3);
	if (Phase()==8) delete(iBitmap4);
}


	// Text printed to the console
_LIT(KTxtUpdateModelCase0,"Load, draw and delete bitmap");
_LIT(KTxtUpdateModelCase1,"Load and draw bitmap");
_LIT(KTxtUpdateModelCase2,"Delete bitmap");
_LIT(KTxtUpdateModelCase3,"Create bitmap2 and draw");
_LIT(KTxtUpdateModelCase4,"Duplicate bitmap 2 as bitmap 3 and draw both");
_LIT(KTxtUpdateModelCase5,"Delete bitmap 2, draw bitmap 3");
_LIT(KTxtUpdateModelCase6,"Delete bitmap 3");
_LIT(KTxtUpdateModelCase7,"Reload and draw bitmap1");
_LIT(KTxtUpdateModelCase8,"Make bitmap 4 as transposed bitmap 1 and draw both");
_LIT(KTxtUpdateModelCase9,"Delete bitmaps 1 and 4");

void CFbsControl::UpdateModelL()
	{
	// set up name for bitmap sharing
	TBool shareIfLoaded(ETrue);

	// device and context for drawing to the in-memory bitmap
	CFbsBitmapDevice* iBitmapDevice2;
	CGraphicsContext* iBitmapContext2;

		switch (Phase())
		{
		case 0:
			// NB. in this phase, loading of the bitmap occurs in Draw()
			iGraphObserver->NotifyStatus(KTxtUpdateModelCase0);
			break;
		case 1:
			// load bitmap1 from .mbm file
			iBitmap1 = new (ELeave) CFbsBitmap();
            LoadBitmapL(iBitmap1,KTxtMBMname,EMbmGrbmapSmiley,shareIfLoaded);
			iGraphObserver->NotifyStatus(KTxtUpdateModelCase1);
			break;
		case 2:
			// delete bitmap1
			delete iBitmap1;
			iGraphObserver->NotifyStatus(KTxtUpdateModelCase2);
			break;
		case 3:
			// create bitmap 2
			iBitmap2 = new (ELeave) CFbsBitmap();
			iBitmap2->Create(TSize(100,100),EGray4);
			// create a device and gc for it
			iBitmapDevice2 = CFbsBitmapDevice::NewL(iBitmap2);
			iBitmapDevice2->CreateContext(iBitmapContext2);
			// draw to it
 			DrawSmiley(*iBitmapContext2);
			// delete the context and device for bitmap 2
			delete iBitmapContext2;
			delete iBitmapDevice2;
			// and blit it (in the Draw() function)
			iGraphObserver->NotifyStatus(KTxtUpdateModelCase3);
			break;
		case 4:
			// create bitmap 3 as a duplicate of bitmap 2
			iBitmap3 = new (ELeave) CFbsBitmap();
			iBitmap3->Duplicate(iBitmap2->Handle());
			iGraphObserver->NotifyStatus(KTxtUpdateModelCase4);
			break;
		case 5:
			// delete bitmap 2
			delete iBitmap2;
			iGraphObserver->NotifyStatus(KTxtUpdateModelCase5);
			break;
		case 6:
			// delete bitmap 3
			delete iBitmap3;
			iGraphObserver->NotifyStatus(KTxtUpdateModelCase6);
			break;
		case 7:
			// reload bitmap 1 from .mbm file
			iBitmap1 = new (ELeave) CFbsBitmap();
            LoadBitmapL(iBitmap1,KTxtMBMname,EMbmGrbmapSmiley,shareIfLoaded);
			iGraphObserver->NotifyStatus(KTxtUpdateModelCase7);
			break;
		case 8:
			// create bitmap 4 as rotated bitmap 1
			CreateRotatedBitmap();
			iGraphObserver->NotifyStatus(KTxtUpdateModelCase8);
			break;
		case 9:
			// delete remaing bitmaps (1 and 4)
			delete iBitmap1;
			delete iBitmap4;
			iGraphObserver->NotifyStatus(KTxtUpdateModelCase9);
		}
	}

void CFbsControl::Draw(const TRect& /* aRect */) const
	{
	// draw surrounding rectangle
	CWindowGc& gc=SystemGc(); // graphics context we draw to
	gc.UseFont(iMessageFont); // use the system message font
	gc.Clear(); // clear the area to be drawn to
	TRect rect=Rect(); // a centered rectangle of the default size
	gc.DrawRect(rect); // surrounding rectangle to draw into
	TRgb darkGray(85,85,85);

	// decide what to do, and do it
	switch (Phase())
		{
		case 0:
			{
			// perform (leavable) draw function
		    TRAPD(error,MUTABLE_CAST(CFbsControl*,this)->DrawL(gc));
			}
			break;
		case 1:
			// draw bitmap, centered on the screen,
			// using bitmap block transfer
			{
			DrawSingleBitmap(iBitmap1,gc);
			}
			break;
		case 2:
			{
			// no bitmaps are loaded so draw gray screen
			gc.SetBrushColor(darkGray);
			gc.Clear(rect);
			}
			break;
		case 3:
			// draw bitmap2
			{
			DrawSingleBitmap(iBitmap2,gc);
			}
			break;
		case 4:
			// draw bitmap 2 and bitmap3
			{
			DrawTwoBitmaps(iBitmap2,iBitmap3,gc);
			}
			break;
		case 5:
			// draw bitmap3
			{
			DrawSingleBitmap(iBitmap3,gc);
			}
			break;
		case 6:
			{
			// no bitmaps are loaded so draw gray screen
			gc.SetBrushColor(darkGray);
			gc.Clear(rect);
			}
			break;
		case 7:
			{
			DrawSingleBitmap(iBitmap1,gc);
			}
			break;
		case 8:
			// draw bitmap and bitmap4
			{
			DrawTwoBitmaps(iBitmap1,iBitmap4,gc);
			}
			break;
		case 9:
			{
			// no bitmaps are loaded so draw gray screen
			gc.SetBrushColor(darkGray);
			gc.Clear(rect);
			}
			break;
		default:
			break;
		}
   	}


_LIT(KTxtCDrive,"C:");
_LIT(KTxtZDrive,"Z:");

void CFbsControl::LoadBitmapL(CFbsBitmap* aBitMap,const TDesC& aPathAndFile,TInt aId,TBool aShareIfLoaded)
	{
	TParse mbfn;
		
	mbfn.Set(aPathAndFile,&KTxtCDrive,NULL);
	if (!aBitMap->Load(mbfn.FullName(),aId,aShareIfLoaded))
		return;

	mbfn.Set(aPathAndFile,&KTxtZDrive,NULL);
	User::LeaveIfError(aBitMap->Load(mbfn.FullName(),aId,aShareIfLoaded));
	return;
	}


void CFbsControl::DrawL(CWindowGc& aGc)
	// draw a whole bitmap centered on the screen,
	// using bitmap block transfer
	{
	// set up name for bitmap sharing
	TBool shareIfLoaded(ETrue);

	// load the bitmap and mask bitmap
	iBitmap1 = new (ELeave) CFbsBitmap();

    // Load the bitmap
    LoadBitmapL(iBitmap1,KTxtMBMname,EMbmGrbmapSmiley,shareIfLoaded);
	
	// calculate position for top left of bitmap so it is centered
	DrawSingleBitmap(iBitmap1,aGc);

	// delete bitmap from memory
	delete(iBitmap1);
	}

void CFbsControl::DrawSmiley(CGraphicsContext& aGc)
	{
	// setup pens for drawing smiley
	TSize penSizeBold(3,3);
	TSize penSizeFat(5,5);
	aGc.SetPenSize(penSizeFat);

	// setup sizes/offsets for the face
	TInt leftOffset = 22;
	TInt rightOffset = 38;
	TInt circleSize = 50;
	TInt shrinkSize = 10;

	// draw eyes and outline of face (circle)
	TPoint leftEye(leftOffset,21);
	TPoint rightEye(rightOffset,21);
	aGc.Plot(leftEye);
	aGc.Plot(rightEye);
	aGc.SetPenSize(penSizeBold);
	TRect circle(TPoint(10,10),TPoint(circleSize,circleSize));
	aGc.DrawEllipse(circle);

	// draw the smile
	TRect smile = circle;
	smile.Shrink(shrinkSize,shrinkSize);
	aGc.DrawArc(smile,TPoint(10,circleSize-shrinkSize),TPoint(circleSize,circleSize-shrinkSize));
	}

void CFbsControl::CreateRotatedBitmap()
	{
	// create iBitmap4 as the same size as iBitmap, but with the height and width swapped
	iBitmap4 = new (ELeave) CFbsBitmap();
	TSize inSize = iBitmap1->SizeInPixels();
	iBitmap4->Create(TSize(inSize.iHeight,inSize.iWidth),iBitmap1->DisplayMode());

	// create the bitmap utils
	TBitmapUtil* iBitmap1Util = new (ELeave) TBitmapUtil(iBitmap1);
	TBitmapUtil* iBitmap4Util = new (ELeave) TBitmapUtil(iBitmap4);
	
	iBitmap1Util->Begin(TPoint(0,0));	// lock the stack and perform a SetPos(TPoint(0,0)) on iBitmap1Util
	iBitmap4Util->Begin(TPoint(0,0),*iBitmap1Util); // perform a SetPos(TPoint(0,0)) on iBitmap4Util, but does not lock the stack again

	// set the bits of iBitmap4 as iBitmap1, rotated through 90 degrees
	TInt xPos;
	for (TInt yPos=0;yPos<inSize.iHeight;yPos++)
		{
		iBitmap1Util->SetPos(TPoint(0,yPos));
		iBitmap4Util->SetPos(TPoint(yPos,0));
		for (xPos=0;xPos<inSize.iWidth;xPos++) 
			{
			iBitmap4Util->SetPixel(*iBitmap1Util);
			iBitmap1Util->IncXPos();
			iBitmap4Util->IncYPos();
			}
		}

	// each Begin() must have a corresponding End()
	iBitmap1Util->End();
	iBitmap4Util->End();
	
	// delete the bitmap utils
	delete iBitmap1Util;
	delete iBitmap4Util;
  }

void CFbsControl::DrawSingleBitmap(CFbsBitmap* aDrawBitmap,CWindowGc& aGc) const
	{
	// calculate position for top left of bitmap so it is centered
	TSize bmpSizeInPixels=aDrawBitmap->SizeInPixels();
	TRect rect=Rect(); // a centered rectangle of the default size
	TInt xDelta=(rect.Width()-bmpSizeInPixels.iWidth)/2;
	TInt yDelta=(rect.Height()-bmpSizeInPixels.iHeight)/2;
	TPoint pos=TPoint(xDelta,yDelta); // displacement vector
	pos+=rect.iTl; // bitmap top left corner position
	aGc.BitBlt(pos, aDrawBitmap); // CWindowGc member function
	}

void CFbsControl::DrawTwoBitmaps(CFbsBitmap* aBitmap1,CFbsBitmap* aBitmap2,CWindowGc& aGc) const
	{
	// calculate position for top left of bitmap so it is centered
	TSize bmpSizeInPixels=aBitmap1->SizeInPixels();
	TRect rect=Rect(); // a centered rectangle of the default size
	TInt xDelta=(rect.Width()-bmpSizeInPixels.iWidth)/4;
	TInt yDelta=(rect.Height()-bmpSizeInPixels.iHeight)/4;
	TPoint pos=TPoint(xDelta,yDelta); // displacement vector
	TPoint pos2=TPoint(xDelta*3,yDelta);
	pos+=rect.iTl; // bitmap top left corner position
	pos2+=rect.iTl;
	aGc.BitBlt(pos, aBitmap1); // CWindowGc member function
	aGc.BitBlt(pos2, aBitmap2);
	}
