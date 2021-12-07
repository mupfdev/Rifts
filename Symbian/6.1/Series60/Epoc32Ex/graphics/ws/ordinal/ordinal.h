// Ordinal.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//


#if !defined(__WSWNORD1_H__)
#define __WSWNORD1_H__

#include "Base.h"

//////////////////////////////////////////////////////////////////////////
//						Derived window classes
//////////////////////////////////////////////////////////////////////////
// CNumberedWindow displays a number in its center and supports drag and drop
class CNumberedWindow : public CWindow
	{
public:
	CNumberedWindow (CWsClient* aClient, TInt aNum);
	~CNumberedWindow ();
	void Draw (const TRect& aRect);
	void HandlePointerEvent (TPointerEvent& aPointerEvent);
private:
	TInt	iNumber;	// Number displayed in window
	TPoint	iOldPos;	// Position is required for drag and drop
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
	CNumberedWindow* iWindow2;
	CNumberedWindow* iWindow3;
	CNumberedWindow* iWindow4;
	CNumberedWindow* iWindow5;
	const TRect& iRect;
	};

#endif
