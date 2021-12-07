// GraphicsControl.h
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.

#ifndef __GraphicsControl_H
#define __GraphicsControl_H

#include <coecntrl.h>
#include <s32file.h>
#include "CommonGraphicsControlFramework.h"

// sundry derived classes


class CDrawControl : public CGraphicExampleControl
	{
public:
	CDrawControl() { SetMaxPhases(26); };
	void UpdateModelL();
	void Draw(const TRect& aRect) const;
	};

class CZoomControl : public CGraphicExampleControl
	{
public:
	CZoomControl() { SetMaxPhases(5); };
	~CZoomControl() { delete(iBitmap); };
	void UpdateModelL();
	void Draw(const TRect& aRect) const;
	void DrawLeft(TRect screenRect,CWindowGc& gc) const;
	void DrawRight(TRect screenRect,CWindowGc& gc) const;
private:
	void LoadBitmapL(CFbsBitmap* aBitMap,const TDesC& aPathAndFile,TInt aId,TBool aShareIfLoaded);
private:
	TZoomFactor iLeftZf;
	TZoomFactor iRightZf;
	MGraphicsDeviceMap* iLeftMap;
	MGraphicsDeviceMap* iRightMap;
	CFbsBitmap* iBitmap;
	};


#endif
