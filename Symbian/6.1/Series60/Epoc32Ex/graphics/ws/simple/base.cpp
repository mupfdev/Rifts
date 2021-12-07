// Base.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.

#include <w32std.h>
#include "Base.h"

///////////////////////////////////////////////////////////////////////////////
////////////////////////// CWindow implementation /////////////////////////////
///////////////////////////////////////////////////////////////////////////////

CWindow::CWindow(CWsClient* aClient)
	: iClient(aClient)
	{
	}

void CWindow::ConstructL (const TRect& aRect, CWindow* aParent)
	{
	// If a parent window was specified, use it; if not, use the window group
	// (aParent defaults to 0).
	RWindowTreeNode* parent= aParent ? (RWindowTreeNode*) &(aParent->Window()) : &(iClient->iGroup);
	iWindow=RWindow(iClient->iWs); // use app's session to window server
	User::LeaveIfError(iWindow.Construct(*parent,(TUint32)this));
	iRect = aRect;
	iWindow.SetExtent(iRect.iTl, iRect.Size()); // set extent relative to group coords
	iWindow.Activate(); // window is now active
	}


CWindow::~CWindow()
	{
	iWindow.Close(); // close our window
	}

RWindow& CWindow::Window()
	{
	return iWindow;
	}

CWindowGc* CWindow::SystemGc()
	{
	return iClient->iGc;
	}


///////////////////////////////////////////////////////////////////////////////
////////////////////////// CWsRedrawer implementation /////////////////////////
///////////////////////////////////////////////////////////////////////////////

CWsRedrawer::CWsRedrawer()
	: CActive(CActive::EPriorityLow)
	{
	}

void CWsRedrawer::ConstructL(CWsClient* aClient)
	{
	iClient=aClient; // remember WsClient that owns us
	CActiveScheduler::Add(this); // add ourselves to the scheduler
	IssueRequest(); // issue request to draw
	}

CWsRedrawer::~CWsRedrawer()
	{
	Cancel();
	}

void CWsRedrawer::IssueRequest()
	{
	iClient->iWs.RedrawReady(&iStatus);
	SetActive();
	}

void CWsRedrawer::DoCancel()
	{
	iClient->iWs.RedrawReadyCancel();
	}

void CWsRedrawer::RunL()
	{	
	// find out what needs to be done
	TWsRedrawEvent redrawEvent;
    iClient->iWs.GetRedraw(redrawEvent); // get event
	CWindow* window=(CWindow*)(redrawEvent.Handle()); // get window
	if (window)
		{
		TRect rect=redrawEvent.Rect(); // and rectangle that needs redrawing
		// now do drawing
		iClient->iGc->Activate(window->Window());
		window->Window().BeginRedraw(rect);
		window->Draw(rect);
		window->Window().EndRedraw();
		iClient->iGc->Deactivate();
		}
	// maintain outstanding request
	IssueRequest();
	}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////// CWsClient implementation ////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
CWsClient::CWsClient()
	: CActive(CActive::EPriorityHigh)
	{
	}

void CWsClient::ConstructL()
	{
	// add ourselves to active scheduler
	CActiveScheduler::Add(this);
	// get a session going
	User::LeaveIfError(iWs.Connect());
	// construct our one and only window group
	iGroup=RWindowGroup(iWs);
	User::LeaveIfError(iGroup.Construct(2,ETrue)); // meaningless handle; enable focus
	// construct screen device and graphics context
	iScreen=new (ELeave) CWsScreenDevice(iWs); // make device for this session
	User::LeaveIfError(iScreen->Construct()); // and complete its construction
	User::LeaveIfError(iScreen->CreateContext(iGc)); // create graphics context
	// construct redrawer
	iRedrawer=new (ELeave) CWsRedrawer;
	iRedrawer->ConstructL(this);
	// construct main window
	ConstructMainWindowL();
	// request first event and start scheduler
	IssueRequest();
	}

CWsClient::~CWsClient()
	{
	// neutralize us as an active object
	Deque(); // cancels and removes from scheduler
	// get rid of everything we allocated
	delete iGc;
	delete iScreen;
	delete iRedrawer;
	// destroy window group
	iGroup.Close();
	// finish with window server
	iWs.Close();
	}

void CWsClient::IssueRequest()
	{
	iWs.EventReady(&iStatus); // request an event
	SetActive(); // so we're now active
	}

void CWsClient::DoCancel()
	{
	iWs.EventReadyCancel(); // cancel event request
	}

void CWsClient::ConstructMainWindowL()
	{
	}

