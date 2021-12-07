// Simple.h
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//


#if !defined(__WSWIN1_H__)
#define __WSWIN1_H__

#include "Base.h"

//////////////////////////////////////////////////////////////////////////
//						Derived window classes							//
//////////////////////////////////////////////////////////////////////////
class CMainWindow : public CWindow
	{
public:
	CMainWindow (CWsClient* aClient);
	~CMainWindow ();
	void Draw (const TRect& aRect);
	void HandlePointerEvent (TPointerEvent& aPointerEvent);
	};

class CSmallWindow : public CWindow
	{
public:
	CSmallWindow (CWsClient* aClient);
	~CSmallWindow ();
	void Draw (const TRect& aRect);
	void HandlePointerEvent (TPointerEvent& aPointerEvent);
	};


//////////////////////////////////////////////////////////////////////////
//						Derived client class							//
//////////////////////////////////////////////////////////////////////////

class CExampleWsClient : public CWsClient
	{
public:
	static CExampleWsClient* NewL(const TRect& aRect);
	void HandleKeyEventL(struct TKeyEvent &aKeyEvent);
private:
	// constructor
	CExampleWsClient (const TRect& aRect);
	void ConstructMainWindowL();
	~CExampleWsClient ();
	void RunL ();
private:
	CMainWindow* iMainWindow;	// main window
	CMainWindow* iAnotherWindow;
	CSmallWindow* iSmallWindow;
	const TRect& iRect;
	};

#endif
