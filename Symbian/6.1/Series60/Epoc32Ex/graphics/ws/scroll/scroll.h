// WSSCROL1.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//


#if !defined(__WSSCROL1_H__)
#define __WSSCROL1_H__

#include "Base.h"

//////////////////////////////////////////////////////////////////////////
//						Derived window classes
//////////////////////////////////////////////////////////////////////////
// CNumberedWindow displays a number in its center and supports drag and drop
class CNumberedWindow : public CWindow
	{
public:
	enum EScrollDir {Up, Down};
	CNumberedWindow (CWsClient* aClient, TInt aNum);
	~CNumberedWindow ();
	void Draw (const TRect& aRect);
	void HandlePointerEvent (TPointerEvent& aPointerEvent);
	void HandlePointerMoveBufferReady () {}
private:
	static TInt iCount;
	TInt	iNumber;	// Number displayed in window
	TPoint	iOldPos;	// Position is required for drag and drop
	TPoint	iOffset;	// Used for scrolling
	TRect	iRepeatRect;	// Boundary for pointer repeat events
	EScrollDir	iScrollDir;	// Scroll direction for pointer repeat events
	};

// CMainWindow is a plain window that just acts as a container for the
// other windows
class CMainWindow : public CWindow
	{
public:
	CMainWindow (CWsClient* aClient);
	~CMainWindow ();
	void Draw (const TRect& aRect);
	void HandlePointerEvent (TPointerEvent& aPointerEvent);
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
