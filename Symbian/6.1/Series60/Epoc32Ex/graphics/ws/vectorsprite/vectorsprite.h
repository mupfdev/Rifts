// VectorSprite.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//


#if !defined(__WSPRIT11_H__)
#define __WSPRIT11_H__

#include "Base.h"

// CMainWindow is a plain window that just acts as a container for the
// other windows
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
	CMainWindow*	iMainWindow;
	CSprite*		iSprite;
	const TRect& iRect;
	};

class CSprite : public CBase
	{
public:
	CSprite (CWsClient* aClient);
	~CSprite ();
	void ConstructL(CWindow* aWindow);
	void CreateBitmap(CFbsBitmap* &aBitmap, TInt aSpriteNum, TBool aDoMask);
private:
	CWsClient*	iClient;
	RWsSprite	iSprite;
	TSpriteMember	iSpriteMember[4];
	};

#endif
