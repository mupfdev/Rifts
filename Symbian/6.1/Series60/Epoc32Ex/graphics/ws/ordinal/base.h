// Base.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//



#if !defined(__WSWINORD_H__)
#define __WSWINORD_H__

// Forward declarations
class CWsRedrawer;
class CWindow;


/////////////////////////////////////////////////////////////////////////
//						Declaration of CWsClient
/////////////////////////////////////////////////////////////////////////

class CWsClient : public CActive
	{
public:
	void ConstructL();
	// destruct
	~CWsClient();
	// main window
	virtual void ConstructMainWindowL();
	// terminate cleanly
	void Exit();
	// active object protocol
	void IssueRequest(); // request an event
	void DoCancel(); // cancel the request
	virtual void RunL() = 0; // handle completed request
	virtual void HandleKeyEventL (TKeyEvent& aKeyEvent) = 0;
protected:
	//construct
	CWsClient();
	CWsScreenDevice* iScreen;
	CWsRedrawer* iRedrawer;
	RWsSession iWs;
	TWsEvent iWsEvent;
private:
	RWindowGroup iGroup;
	CWindowGc* iGc;
	friend class CWsRedrawer; // needs to get at session
	friend class CWindow; // needs to get at session
	};



////////////////////////////////////////////////////////////////////////////
//						CWsRedrawer declaration
////////////////////////////////////////////////////////////////////////////

class CWsRedrawer : public CActive
	{
public:
	// construct/destruct
	CWsRedrawer();
	void ConstructL(CWsClient* aClient);
	~CWsRedrawer();
	// drawing
	void IssueRequest();
	void DoCancel();
	void RunL();
protected:
	CWsClient* iClient;
	};


//////////////////////////////////////////////////////////////////////////////
//							CWindow declaration
//////////////////////////////////////////////////////////////////////////////

class CWindow : public CBase
	{
public:
	CWindow(CWsClient* aClient);
	void ConstructL (const TRect& aRect, const TRgb& aColor, CWindow* aParent=0);
	~CWindow();
	// access
	RWindow& Window(); // our own window
	CWindowGc* SystemGc(); // system graphics context
	CWsScreenDevice* Screen();
	CFont* Font();
	// drawing
	virtual void Draw(const TRect& aRect) = 0;
	virtual void HandlePointerEvent (TPointerEvent& aPointerEvent) = 0;
protected:
	RWindow iWindow; // window server window
	TRect iRect; // window's extent
private:
	CWsClient* iClient; // client including session and group
	CFont*	iFont;
	};


#endif