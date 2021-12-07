// Ordinal.CPP
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#include <w32std.h>
#include "Base.h"
#include "Ordinal.h"

_LIT(KString1,"1");
_LIT(KString2,"2");
_LIT(KString3,"3");
_LIT(KString4,"4");
_LIT(KString5,"5");

//////////////////////////////////////////////////////////////////////////////
//					 CNumberedWindow implementation
//////////////////////////////////////////////////////////////////////////////

/****************************************************************************\
|	Function:	Constructor/Destructor for CNumberedWindow
|	Input:		aClient		Client application that owns the window
\****************************************************************************/
CNumberedWindow::CNumberedWindow (CWsClient* aClient, TInt aNum)
: CWindow (aClient), iNumber(aNum), iOldPos(0,0)
	{
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
			// Move the window position as the pointer is dragged.
			TPoint point = aPointerEvent.iParentPosition;
			TPoint distToMove = point - iOldPos;
			TPoint position = Window().Position();
			Window().SetPosition (position + distToMove);
			iOldPos = point;
			break;
			}
		case TPointerEvent::EButton1Down:
			{
			// Move window to front
			Window().SetOrdinalPosition (0);
			// Request drag events 
			Window().PointerFilter (EPointerFilterDrag,	0);
			// Initialize starting point for dragging
			iOldPos = aPointerEvent.iParentPosition;
			break;
			}
		case TPointerEvent::EButton1Up:
			{
			// Cancel the request for drag events.
			Window().PointerFilter (EPointerFilterDrag,	EPointerFilterDrag);
			break;
			}
		case TPointerEvent::EButton3Down:
			{
			// Cascade windows in top left corner.
			// Window at the front should be cascaded last.
			// The window at the front (ordinal position 0) is given by Child(), and 
			// each window behind it is given by NextSibling(). We need to go down
			// the sibling list till we get to the last sibling, and move this to 
			// the top left corner. Then go back up the list and move each previous 
			// sibling on top of the last, displaced by an offset (of TPoint(10,10)).
			TPoint point (0,0);
			TUint32 nextSib, prevSib;
			CWindow* childWindow;
			TInt	numChildren = 0;
			TUint32 child = Window().Child();
			if (child)
				{
				childWindow = (CWindow*)child;
				numChildren++;
				nextSib = childWindow->Window().NextSibling();
				while (nextSib)
					{
					numChildren++;
					childWindow = (CWindow*)nextSib;
					nextSib = childWindow->Window().NextSibling();
					}
				for (TInt i=numChildren; i>0; i--)
					{
					childWindow->Window().SetPosition (point);
					prevSib = childWindow->Window().PrevSibling();
					if (prevSib)
						{
						childWindow = (CWindow*)prevSib;
						point += TPoint(10,10);
						}
					}
				}
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
|	Function:	CMainWindow::HandlePointerEvent
|	Purpose:	Handles pointer events for CMainWindow.
|	Input:		aPointerEvent	The pointer event!
|	Output:		None
\****************************************************************************/

void CMainWindow::HandlePointerEvent (TPointerEvent& aPointerEvent)
	{	
	switch (aPointerEvent.iType)
		{
		case TPointerEvent::EButton3Down:
			{
			// Cascade windows in top left corner
			// Window at the front should be cascaded last.
			// The window at the front (ordinal position 0) is given by Child(), and 
			// each window behind it is given by NextSibling(). We need to go down
			// the sibling list till we get to the last sibling, and move this to 
			// the top left corner. Then go back up the list and move each previous 
			// sibling on top of the last, displaced by an offset (of TPoint(10,10)).
			TPoint point (0,0);
			TUint32 nextSib, prevSib;
			CWindow* childWindow;
			TInt	numChildren = 0;
			TUint32 child = Window().Child();
			if (child)
				{
				childWindow = (CWindow*)child;
				numChildren++;
				nextSib = childWindow->Window().NextSibling();
				while (nextSib)
					{
					numChildren++;
					childWindow = (CWindow*)nextSib;
					nextSib = childWindow->Window().NextSibling();
					}
				for (TInt i=numChildren; i>0; i--)
					{
					childWindow->Window().SetPosition (point);
					prevSib = childWindow->Window().PrevSibling();
					if (prevSib)
						{
						childWindow = (CWindow*)prevSib;
						point += TPoint(10,10);
						}
					}
				}
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
	delete iWindow1;
	delete iWindow2;
	delete iWindow3;
	delete iWindow4;
	delete iWindow5;
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
	TInt count=0;
	TRect rect(0,0,40,40);
	iWindow1  = new (ELeave) CNumberedWindow (this, count++);
	iWindow1->ConstructL (rect, TRgb (50, 50, 50),iMainWindow);
	iWindow2  = new (ELeave) CNumberedWindow (this, count++);
	iWindow2->ConstructL (rect, TRgb (100, 100, 100),iMainWindow);
	iWindow3  = new (ELeave) CNumberedWindow (this, count++);
	iWindow3->ConstructL (rect, TRgb (150, 150, 150),iMainWindow);
	iWindow4  = new (ELeave) CNumberedWindow (this, count++);
	rect.Shrink(10,10);
	iWindow4->ConstructL (rect, TRgb (200, 200, 200),iWindow1);
	iWindow5  = new (ELeave) CNumberedWindow (this, count++);
	iWindow5->ConstructL (rect, TRgb (150, 150, 150),iWindow1);
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
		break;
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
|				Gets the key code from the key event.  Exits on 'Escape'
\****************************************************************************/
void CExampleWsClient::HandleKeyEventL (TKeyEvent& /*aKeyEvent*/)
	{
	}

