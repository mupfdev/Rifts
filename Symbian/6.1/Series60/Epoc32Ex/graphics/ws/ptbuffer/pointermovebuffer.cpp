// PointerMoveBuffer.CPP
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// Hold down the SHIFT key and drag the mouse (with left mouse button down)
// for freehand drawing.

#include <w32std.h>
#include "Base.h"
#include "PointerMoveBuffer.h"



//////////////////////////////////////////////////////////////////////////////
//					 CMainWindow implementation
//////////////////////////////////////////////////////////////////////////////


/****************************************************************************\
|	Function:	Constructor/Destructor for CMainWindow
|	Input:		aClient		Client application that owns the window
\****************************************************************************/
CMainWindow::CMainWindow (CWsClient* aClient)
: CWindow (aClient)
	{
	}


CMainWindow::~CMainWindow ()
	{
	iWindow.Close();
	}

/****************************************************************************\
|	Function:	CMainWindow::Draw
|	Purpose:	Redraws the contents of CMainWindow within a given
|				rectangle.
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
|	Function:	CMainWindow::HandlePointerBufferReady
\****************************************************************************/

void CMainWindow::HandlePointerMoveBufferReady ()
	{		
	TPoint pnts[KPointerMoveBufferSize];
	TPtr8 ptr((TUint8 *)&pnts,sizeof(pnts));
	TInt numPnts=Window().RetrievePointerMoveBuffer(ptr);
	TSize size = Window().Size();
	TPoint position = Window().Position();
	TRect redrawRect (position, size);
	CWindowGc* gc=SystemGc();
	gc->Activate(Window());
	Window().Invalidate();
	Window().BeginRedraw(redrawRect); // N.B. Redrawer::RunL() gets called with this 
									  // rectangle - must give it a non-zero value
	for(TInt index=0;index<numPnts;index++) gc->DrawLineTo(pnts[index]);
	Window().EndRedraw();
	gc->Deactivate();
	}

/****************************************************************************\
|	Function:	CMainWindow::HandlePointerEvent
|	Purpose:	Handles pointer events for CMainWindow.
|	Input:		aPointerEvent	The pointer event!
|	Output:		None
\****************************************************************************/

void CMainWindow::HandlePointerEvent (TPointerEvent& aPointerEvent)
	{	
	switch (aPointerEvent.iType)
		{
		case TPointerEvent::EButton1Down:
			{
			if (aPointerEvent.iModifiers&EModifierShift)
				{
				Window().EnablePointerMoveBuffer();
				CWindowGc* gc = SystemGc();
				gc->Activate(Window());
				gc->MoveTo(aPointerEvent.iPosition);
				gc->Deactivate();
				}
			break;
			}
		case TPointerEvent::EButton1Up:
			{
			Window().DisablePointerMoveBuffer();
			break;
			}
		default:
			break;
		}
}


//////////////////////////////////////////////////////////////////////////////
//					 CExampleWsClient implementation
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
	}


/****************************************************************************\
|	Function:	CExampleWsClient::ConstructMainWindowL()
|				Called by base class's ConstructL
|	Purpose:	Allocates and creates all the windows owned by this client
|				(See list of windows in CExampleWsCLient declaration).
\****************************************************************************/

void CExampleWsClient::ConstructMainWindowL()
	{
	// Resources allocated in this function are freed in the CExampleWsClient destructor		
	iMainWindow=new (ELeave) CMainWindow(this);
	iMainWindow->ConstructL(iRect, TRgb (255,255,255));
	}

/****************************************************************************\
|	Function:	CExampleWsClient::HandleKeyEventL()
|	Purpose:	Processes key events for CExampleWsClient
\****************************************************************************/
void CExampleWsClient::HandleKeyEventL (TKeyEvent& /*aKeyEvent*/)
	{
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
	// events global within window group
	case EEventNull:
	case EEventKey:
	case EEventModifiersChanged:
	case EEventKeyUp:
	case EEventKeyDown:
	case EEventFocusLost:
	case EEventFocusGained:
	case EEventSwitchOn:
	case EEventPassword:
	case EEventWindowGroupsChanged:
	case EEventErrorMessage:
		break;
	// events local to specific windows
	case EEventPointer:
		{
		CWindow* window=(CWindow*)(iWsEvent.Handle()); // get window
		TPointerEvent& pointerEvent=*iWsEvent.Pointer();
		window->HandlePointerEvent (pointerEvent);
		break;
		}
	case EEventPointerExit:
	case EEventPointerEnter:
		break;
	case EEventPointerBufferReady:
		{
		CWindow* window=(CWindow*)(iWsEvent.Handle()); // get window
		window->HandlePointerMoveBufferReady ();
		break;
		}
	case EEventDragDrop:
		break;
	default:
		break;
		}
	IssueRequest(); // maintain outstanding request
	}