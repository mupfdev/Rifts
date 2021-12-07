// VectorSprite.CPP
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#include <w32std.h>
#include "Base.h"
#include "VectorSprite.h"

CSprite::CSprite(CWsClient *aClient) : iClient(aClient)
	{
	}

CSprite::~CSprite()
	{
	for (TInt i=0; i<4; i++)
		{
		delete iSpriteMember[i].iBitmap;
		delete iSpriteMember[i].iMaskBitmap;
		}
	iSprite.Close();
	}

void CSprite::ConstructL(CWindow* aWindow)
	{
	iSprite = RWsSprite(iClient->iWs);
	User::LeaveIfError(iSprite.Construct(aWindow->Window(), TPoint(100,100), 0));
	for (TInt spriteNum = 0; spriteNum < 4; spriteNum++)
		{
		CreateBitmap(iSpriteMember[spriteNum].iBitmap, spriteNum, EFalse);
		CreateBitmap(iSpriteMember[spriteNum].iMaskBitmap, spriteNum, ETrue);
		iSpriteMember[spriteNum].iInvertMask = EFalse;
		iSpriteMember[spriteNum].iOffset = TPoint (0,0);
		iSpriteMember[spriteNum].iInterval = TTimeIntervalMicroSeconds32 (500000);
		iSpriteMember[spriteNum].iDrawMode = CGraphicsContext::EDrawModePEN;
		User::LeaveIfError(iSprite.AppendMember(iSpriteMember[spriteNum]));
		}
	User::LeaveIfError(iSprite.Activate());
	iSprite.UpdateMember(3);
	}

void CSprite::CreateBitmap(CFbsBitmap* &aBitmap, TInt aSpriteNum, TBool aDoMask)
	{
    // device and context for drawing to the off-screen bitmap
    CFbsBitmapDevice* bitmapDevice;
    CGraphicsContext* bitmapContext;
    
    // create bitmap
	// aBitmap is effectively member data of CSprite, and this function is only
	// called from CSprite's constructor. This means we can be sure aBitmap has 
	// not been new'ed before (if it had, we'd need to do a delete here and set
	// aBitmap to 0.
    aBitmap = new (ELeave) CFbsBitmap();
    aBitmap->Create(TSize(50,50),EGray4);
    // create a device and gc for it
    bitmapDevice = CFbsBitmapDevice::NewL(aBitmap);
    bitmapDevice->CreateContext(bitmapContext);
	// Set up pen color etc.
	bitmapContext->SetBrushColor(aDoMask? TRgb::Gray4(0) : TRgb::Gray4(2));
	bitmapContext->SetBrushStyle(CGraphicsContext::ESolidBrush);
	bitmapContext->SetPenStyle(CGraphicsContext::ENullPen);
	bitmapContext->DrawRect(TRect(TSize(50,50)));
	bitmapContext->SetPenStyle(CGraphicsContext::ESolidPen);
	bitmapContext->SetPenSize(TSize(4,4));
	bitmapContext->SetPenColor(aDoMask? TRgb::Gray4(3) : TRgb::Gray4(0));
    // draw to it
	switch (aSpriteNum)
		{
	case 0:
	    bitmapContext->DrawLine (TPoint(10,10), TPoint(40,40));
		break;
	case 1:
		bitmapContext->DrawLine (TPoint(25,10), TPoint(25,40));
		break;
	case 2:
		bitmapContext->DrawLine (TPoint(40,10), TPoint(10,40));
		break;
	case 3:
		bitmapContext->DrawLine (TPoint(10,25), TPoint(40,25));
		break;
		}
    // delete the context and device
    delete bitmapContext;
    delete bitmapDevice;
	}

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
	gc->SetPenStyle(CGraphicsContext::ESolidPen);
	gc->SetPenColor(TRgb::Gray4(2));
	TSize size = Window().Size();
	TInt width = size.iWidth;
	TInt height = size.iHeight;
	TInt numHoriz=height/5;
	TInt numVert=width/10;
	for (TInt i=numHoriz; i>0; i--)
		{
		gc->DrawLine (TPoint(0,height/numHoriz*i), TPoint(width, height/numHoriz*i));
		}
	for (TInt j=numVert; j>0; j--)
		{
		gc->DrawLine (TPoint(width/numVert*j, 0), TPoint(width/numVert*j, height));
		}
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
		break;
	case TPointerEvent::EButton1Up:
		break;
	case TPointerEvent::EButton3Down:
		break;
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
	delete iSprite;
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
	iMainWindow->ConstructL(iRect, TRgb (255,255,255));
	iSprite=new (ELeave) CSprite (this);
	iSprite->ConstructL(iMainWindow);
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
	case EEventModifiersChanged:
		break;
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
