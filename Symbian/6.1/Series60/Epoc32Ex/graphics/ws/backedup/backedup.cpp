// BackedUp.CPP
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#include <w32std.h>
#include "Base.h"
#include "BackedUp.h"

_LIT(KString1,"1");
_LIT(KString2,"2");
_LIT(KString3,"3");
_LIT(KString4,"4");
_LIT(KString5,"5");

enum TBackedUpPanic
	{
	EConnectPanicRedrawToBackedUpWindow,
	};


//////////////////////////////////////////////////////////////////////////////
//					 CNumberedWindow implementation
//////////////////////////////////////////////////////////////////////////////

/****************************************************************************\
|	Function:	Constructor/Destructor for CNumberedWindow
|	Input:		aClient		Client application that owns the window
\****************************************************************************/
CNumberedWindow::CNumberedWindow (CWsClient* aClient)
: CWindow (aClient), iOldPos(0,0)
	{
	// iNumber is displayed on front of window.
	iNumber = iCount;
	iCount++;
	}


CNumberedWindow::~CNumberedWindow ()
	{
	}


/****************************************************************************\
|	Function:	CNumberedWindow::Draw
|	Purpose:	Redraws the contents of CNumberedWindow within a given
|				rectangle.  CNumberedWindow displays a number in the window.
|	Input:		aRect	Rectangle that needs redrawing
|	Output:		None
\****************************************************************************/
void CNumberedWindow::Draw(const TRect& aRect)
	{
	const TBufC<1> strings[5] = { *&KString1,
							  *&KString2,
							  *&KString3,
							  *&KString4,
					          *&KString5
							};

	CWindowGc* gc=SystemGc(); // get a graphics context
	gc->SetClippingRect(aRect); // clip outside the redraw area
	gc->Clear(aRect); // clear the redraw area
	TSize size=iWindow.Size();
	TInt height=size.iHeight; // Need window height to calculate vertical text offset
	TInt ascent = Font()->AscentInPixels();
	TInt descent = Font()->DescentInPixels();
	TInt offset = (height + (ascent + descent)) / 2; // Calculate vertical text offset
 	gc->SetPenColor(TRgb(0,0,0)); // Set pen to black
	gc->UseFont(Font());
	gc->DrawText(strings[iNumber], TRect(TPoint(0,0), size), offset, CGraphicsContext::ECenter);
	gc->DiscardFont();
	}

/****************************************************************************\
|	Function:	CNumberedWindow::HandlePointerEvent
|	Purpose:	Handles pointer events for CNumberedWindow.
|	Input:		aPointerEvent	The pointer event
|	Output:		None
\****************************************************************************/
void CNumberedWindow::HandlePointerEvent (TPointerEvent& aPointerEvent)
	{	
	switch (aPointerEvent.iType)
		{
		case TPointerEvent::EDrag:
			{
			TPoint point = aPointerEvent.iParentPosition;
			TPoint distToMove = point - iOldPos;
			TPoint position = Window().Position();
			Window().SetPosition (position + distToMove);
			iOldPos = point;
			break;
			}
		case TPointerEvent::EButton1Down:
			{
			// Request drag events 
			Window().PointerFilter (EPointerFilterDrag,	0);
			Window().SetOrdinalPosition (0);
			iOldPos = aPointerEvent.iParentPosition;
			break;
			}
		case TPointerEvent::EButton1Up:
			{
			// Cancel the request for drag events.
			Window().PointerFilter (EPointerFilterDrag,	EPointerFilterDrag);
			break;
			}
		default:
			break;
		}
	}


//////////////////////////////////////////////////////////////////////////////
//					 CMainWindow implementation
//////////////////////////////////////////////////////////////////////////////


/****************************************************************************\
|	Function:	Constructor/Destructor for CMainWindow
|	Input:		aClient		Client application that owns the window
\****************************************************************************/
CMainWindow::CMainWindow (CWsClient* aClient)
: CBackedUpWindow (aClient)
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

void CMainWindow::Draw(const TRect& /*aRect*/)
	{
	_LIT(KPanicMsg,"BACKEDUP");
	User::Panic(KPanicMsg,EConnectPanicRedrawToBackedUpWindow);
	}

void CMainWindow::HandlePointerMoveBufferReady ()
	{		
	TPoint pnts[KPointerMoveBufferSize];
	TPtr8 ptr((TUint8 *)&pnts,sizeof(pnts));
	TInt numPnts=Window().RetrievePointerMoveBuffer(ptr);
	CWindowGc* gc=SystemGc();
	gc->Activate(Window());
	for(TInt index=0;index<numPnts;index++) gc->DrawLineTo(pnts[index]);
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
			Window().SetShadowDisabled(EFalse);
			Window().EnablePointerMoveBuffer();
			CWindowGc* gc = SystemGc();
			gc->Activate(Window());
			gc->MoveTo(aPointerEvent.iPosition);
			gc->Deactivate();
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
	delete iWindow1;
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
	iMainWindow->ConstructL(iRect);
	iWindow1  = new (ELeave) CNumberedWindow (this);
	iWindow1->ConstructL (TRect (TPoint (100, 100), TSize (100, 100)), TRgb (100, 100, 100),
		iMainWindow);
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
		break;
	case EEventKey:
		{
		TKeyEvent& keyEvent=*iWsEvent.Key(); // get key event
		HandleKeyEventL (keyEvent);
		break;
		}
	case EEventKeyUp:
	case EEventModifiersChanged:
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

/****************************************************************************\
|	Function:	CExampleWsClient::HandleKeyEventL()
|	Purpose:	Processes key events for CExampleWsClient
\****************************************************************************/
void CExampleWsClient::HandleKeyEventL (TKeyEvent& /*aKeyEvent*/)
	{
	}


