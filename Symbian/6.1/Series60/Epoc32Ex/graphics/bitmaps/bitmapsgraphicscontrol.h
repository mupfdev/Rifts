// BitmapsGraphicsControl.h
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.

#ifndef __BitmapsGraphicsControl_H
#define __BitmapsGraphicsControl_H

#include <coecntrl.h>
#include <s32file.h>
#include "CommonGraphicsControlFramework.h"
class CBitmapControl : public CGraphicExampleControl
	{
public:
	CBitmapControl() { SetMaxPhases(8); };
	~CBitmapControl() { delete(iBitmap); delete(iMaskBitmap); };
	void UpdateModelL();
	void Draw(const TRect& aRect) const;
private:
	void LoadBitmapL(CFbsBitmap* aBitMap,const TDesC& aPathAndFile,TInt aId,TBool aShareIfLoaded);
private:
	CFbsBitmap* iBitmap;
	CFbsBitmap* iMaskBitmap;
	};


class CFbsControl : public CGraphicExampleControl
	{
public:
	CFbsControl() { SetMaxPhases(10); };
	~CFbsControl();
	void UpdateModelL();
	void Draw(const TRect& aRect) const;
private:
	void DrawL(CWindowGc& aGc);
	void DrawSmiley(CGraphicsContext& aGc);
	void CreateRotatedBitmap();
	void DrawSingleBitmap(CFbsBitmap* aDrawBitmap,CWindowGc& aGc) const;
	void DrawTwoBitmaps(CFbsBitmap* aBitmap1,CFbsBitmap* aBitmap2,CWindowGc& aGc) const;
	void LoadBitmapL(CFbsBitmap* aBitMap,const TDesC& aPathAndFile,TInt aId,TBool aShareIfLoaded);
	CFbsBitmap* iBitmap1;
	CFbsBitmap* iBitmap2;
	CFbsBitmap* iBitmap3;
	CFbsBitmap* iBitmap4;
	};

#endif
