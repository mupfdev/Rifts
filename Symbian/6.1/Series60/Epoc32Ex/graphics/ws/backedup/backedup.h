// BackedUp.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//


#if !defined(__WSBACKD1_H__)
#define __WSBACKD1_H__

#include "Base.h"

//////////////////////////////////////////////////////////////////////////
//						Derived window classes
//////////////////////////////////////////////////////////////////////////
// CNumberedWindow displays a number in its center and supports drag and drop
class CNumberedWindow : public CWindow
	{
public:
	CNumberedWindow (CWsClient* aClient);
	~CNumberedWindow ();
	void Draw (const TRect& aRect);
	void HandlePointerEvent (TPointerEvent& aPointerEvent);
	void HandlePointerMoveBufferReady () {}
private:
	TInt iCount;
	TInt	iNumber;	// Number displayed in window
	TPoint	iOldPos;	// Position is required for drag and drop
	};

class CMainWindow : public CBackedUpWindow
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
	CNumberedWindow* iWindow1;
	const TRect& iRect;
	};


#endif
