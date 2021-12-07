// BitmapSprite.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//


#if !defined(__WSPRIT21_H__)
#define __WSPRIT21_H__

#include "Base.h"

class CMainWindow : public CWindow
	{
public:
	CMainWindow (CWsClient* aClient);
	~CMainWindow ();
	void Draw (const TRect& aRect);
	void HandlePointerEvent (TPointerEvent& aPointerEvent);
	void HandlePointerMoveBufferReady ();
	};

//////////////////////////////////////////////////////////////////////////
//						Derived client class
//////////////////////////////////////////////////////////////////////////

class CSprite;
class CPointerCursor;
class CExampleWsClient : public CWsClient
	{
public:
	static CExampleWsClient* NewL(const TRect& aRect);
private:
	CExampleWsClient (const TRect& aRect);
	void ConstructMainWindowL();
	~CExampleWsClient ();
	void RunL ();
	void HandleKeyEventL (TKeyEvent& aKeyEvent);
private:
	CMainWindow* iMainWindow;
	CSprite*	iSprite;
	const TRect& iRect;
	};


class CSprite : public CBase
	{
public:
	CSprite (CWsClient* aClient);
	~CSprite ();
	void ConstructL(CWindow* aWindow);
	void UpdatePos(TPoint aAdjust);
private:
	CWsClient*	iClient;
	RWsSprite	iSprite;
	TPoint		iSpritePos;
	TSpriteMember	iSpriteMember[8];
	};

#endif
