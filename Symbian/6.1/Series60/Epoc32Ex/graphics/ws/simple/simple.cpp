// Simple.CPP
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#include <w32std.h>
#include "Base.h"
#include "Simple.h"


//////////////////////////////////////////////////////////////////////////////
//				Implementation for derived window classes
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//					 CMainWindow implementation							//
//////////////////////////////////////////////////////////////////////////////

/****************************************************************************\
|	Function:	Constructor/Destructor for CMainWindow
|				Doesn't do much, as most initialisation is done by the
|				CWindow base class.
|	Input:		aClient		Client application that owns the window
\****************************************************************************/
CMainWindow::CMainWindow (CWsClient* aClient)
: CWindow (aClient)
	{
	}


CMainWindow::~CMainWindow ()
	{
	}


/****************************************************************************\
|	Function:	CMainWindow::Draw
|	Purpose:	Redraws the contents of CMainWindow within a given
|				rectangle. As CMainWindow has no contents, it simply
|				clears the redraw area. A blank window could be used here
|				instead. The Clear() is needed because a redraw should
|				always draw to every pixel in the redraw rectangle.
|	Input:		aRect	Rectangle that needs redrawing
|	Output:		None
\****************************************************************************/
void CMainWindow::Draw(const TRect& aRect)
	{
	CWindowGc* gc=SystemGc(); // get a gc
	gc->SetClippingRect(aRect); // clip outside this rect
	gc->Clear(aRect); // clear
	}

/****************************************************************************\
|	Function:	CMainWindow::HandlePointerEvent
|	Purpose:	Handles pointer events for CMainWindow.  Doesn't do 
|				anything here.
|	Input:		aPointerEvent	The pointer event
|	Output:		None
\****************************************************************************/
void CMainWindow::HandlePointerEvent (TPointerEvent& /*aPointerEvent*/)
	{	
	}


//////////////////////////////////////////////////////////////////////////////
//					 CSmallWindow implementation
//////////////////////////////////////////////////////////////////////////////


/****************************************************************************\
|	Function:	Constructor/Destructor for CSmallWindow
|				Doesn't do much, as most initialisation is done by the
|				CWindow base class.									
|	Input:		aClient		Client application that owns the window
\****************************************************************************/

CSmallWindow::CSmallWindow (CWsClient* aClient)
: CWindow (aClient)
	{
	}


CSmallWindow::~CSmallWindow ()
	{
	iWindow.Close();
	}

/****************************************************************************\
|	Function:	CSmallWindow::Draw
|	Purpose:	Redraws the contents of CSmallWindow within a given
|				rectangle.  CSmallWindow displays a square border around
|				the edges of the window, and two diagonal lines between the
|				corners.
|	Input:		aRect	Rectangle that needs redrawing
|	Output:		None
\****************************************************************************/
void CSmallWindow::Draw(const TRect& aRect)
	{
	// Drawing to a window is done using functions supplied by
	// the graphics context (CWindowGC), not the window.
	CWindowGc* gc=SystemGc(); // get a gc
	gc->SetClippingRect(aRect); // clip outside this rect
	gc->Clear(aRect); // clear
	TSize size=iWindow.Size();
	TInt width=size.iWidth;
	TInt height=size.iHeight;
	// Draw a square border
	gc->DrawLine(TPoint(0,0),TPoint(0,height-1));
	gc->DrawLine (TPoint (0, height-1), TPoint (width-1, height-1)); 
	gc->DrawLine(TPoint(width-1,height-1),TPoint(width-1,0));
	gc->DrawLine (TPoint (width-1, 0), TPoint (0, 0));
	// Draw a line between the corners of the window
	gc->DrawLine(TPoint(0,0),TPoint(width, height));
	gc->DrawLine (TPoint (0, height), TPoint (width, 0)); 
	}

/****************************************************************************\
|	Function:	CSmallWindow::HandlePointerEvent
|	Purpose:	Handles pointer events for CSmallWindow.  Doesn't do 
|				anything here.
|	Input:		aPointerEvent	The pointer event
|	Output:		None
\****************************************************************************/

void CSmallWindow::HandlePointerEvent (TPointerEvent& /*aPointerEvent*/)
	{
	}

//////////////////////////////////////////////////////////////////////////////
//					 CExampleWsClient implementation						//
//////////////////////////////////////////////////////////////////////////////

CExampleWsClient* CExampleWsClient::NewL(const TRect& aRect)
	{
	// make new client
	CExampleWsClient* client=new (ELeave) CExampleWsClient(aRect); 
	CleanupStack::PushL(client); // push, just in case
	client->ConstructL(); // construct and run
	CleanupStack::Pop();
	return client;
	}

/****************************************************************************\
|	Function:	Constructor/Destructor for CExampleWsClient
|				Destructor deletes everything that was allocated by
|				ConstructMainWindowL()
\****************************************************************************/

CExampleWsClient::CExampleWsClient(const TRect& aRect)
:iRect(aRect)
	{
	}

CExampleWsClient::~CExampleWsClient ()
	{
	delete iMainWindow;
	delete iSmallWindow;
	}


/****************************************************************************\
|	Function:	CExampleWsClient::ConstructMainWindowL()
|				Called by base class's ConstructL
|	Purpose:	Allocates and creates all the windows owned by this client
|				(See list of windows in CExampleWsCLient declaration).
\****************************************************************************/

void CExampleWsClient::ConstructMainWindowL()
	{
	iMainWindow=new (ELeave) CMainWindow(this);
	iMainWindow->ConstructL(iRect);
	iSmallWindow  = new (ELeave) CSmallWindow (this);
	iSmallWindow->ConstructL (TRect (TPoint (100, 75), TSize (50, 50)), iMainWindow);
		}


/****************************************************************************\
|	Function:	CExampleWsClient::RunL()
|				Called by active scheduler when an even occurs
|	Purpose:	Processes events according to their type
|				For key events: calls HandleKeyEventL() (global to client)
|				For pointer event: calls HandlePointerEvent() for window
|                                  event occurred in.
\****************************************************************************/
void CExampleWsClient::RunL()
	{
	// get the event
	iWs.GetEvent(iWsEvent);
	TInt eventType=iWsEvent.Type();
	// take action on it
	switch (eventType)
		{
	// window-group related event types
	case EEventNull:
		break;
	case EEventKey:
		{
		TKeyEvent& keyEvent=*iWsEvent.Key(); // get key event
		HandleKeyEventL (keyEvent);
		break;
		}
	case EEventKeyUp:
	case EEventKeyDown:
	case EEventModifiersChanged:
	case EEventFocusLost:
	case EEventFocusGained:
	case EEventSwitchOn:
	case EEventPassword:
	case EEventWindowGroupsChanged:
	case EEventErrorMessage:
		break;
	// window related events
	case EEventPointer:
		{
		CWindow* window=(CWindow*)(iWsEvent.Handle()); // get window
		TPointerEvent& pointerEvent=*iWsEvent.Pointer();
		window->HandlePointerEvent (pointerEvent);

		break;
		}
	case EEventPointerEnter:
	case EEventPointerExit:
	case EEventPointerBufferReady:
	case EEventDragDrop:
		break;
	default:
		break;
		}
	IssueRequest(); // maintain outstanding request
	}

void CExampleWsClient::HandleKeyEventL(struct TKeyEvent& /*aKeyEvent*/)
	{
	}