// BitmapSprite.CPP
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//


// This file contains implementations of derived class 
// functions for client and windows.
//
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
// PROJECT: BitmapSprite
// --------------
//
// CREATE A SPRITE USING BITMAPS LOADED FROM FILE
//
// PROJECT OVERVIEW
// ----------------
//
// Creates a sprite using bitmaps loaded from file.
// A hatched background has been drawn on the window to illustrate
// the fact that the sprite does not overlay a rectangular area, like 
// window, but only the area specified by the bitmap mask.
// The animation of the sprite does not cause a redraw event for the 
// window beneath it.
//
// The sprite can be moved around the screen using the arrow keys.
//
// Functions introduced in this project include:
//          RWsSprite::Construct()
//          RWsSpriteBase::AppendMember()
//          RWsSpriteBase::Activate()
//          RWsSpriteBase::Close()
//
// STRUCTURE
// ---------
//
// To create a sprite, an application must set up sprite members to
// contain bitmaps, and add the sprite members to the sprite. The 
// bitmaps can either be read in from files, or created using 
// off-screen bitmaps which can be drawn to via a graphics context
// in a similar way to a window. This example project uses the former
// method. 

#include <eikenv.h>
#include <w32std.h>
#include "Base.h"
#include "BitmapSprite.h"
#include <BitmapSprite.mbg>

CSprite::CSprite(CWsClient *aClient) : iClient(aClient), iSpritePos(80, 75)
	{
	}

CSprite::~CSprite()
	{
	for (TInt i=0; i<8; i++)
		{
		delete iSpriteMember[i].iBitmap;
		delete iSpriteMember[i].iMaskBitmap;
		}
	iSprite.Close();
	}

void CSprite::UpdatePos(TPoint aAdjust)
	{
	iSpritePos += aAdjust;
	iSprite.SetPosition(iSpritePos);
	}

void CSprite::ConstructL(CWindow* aWindow)
	{
	CEikonEnv* eikenv=CEikonEnv::Static();
	iSprite = RWsSprite(iClient->iWs);
	User::LeaveIfError(iSprite.Construct(aWindow->Window(), iSpritePos, 0));
	// Initialize sprite members
	_LIT(KStar,"*"); // "*" means "the <app-name>.mbm file in the app directory"
	for (TInt i=0; i<8; i++)
		{
		iSpriteMember[i].iInvertMask = EFalse;
		iSpriteMember[i].iOffset = TPoint (0,0);
		iSpriteMember[i].iInterval = TTimeIntervalMicroSeconds32 (200000);
		iSpriteMember[i].iBitmap = eikenv->CreateBitmapL(KStar, i);
		if (i%2 == 0)
			{
			iSpriteMember[i].iMaskBitmap=eikenv->CreateBitmapL(KStar, EMbmBitmapspriteMil1mask);
			}
		else
			{
			iSpriteMember[i].iMaskBitmap=eikenv->CreateBitmapL(KStar, EMbmBitmapspriteMil2mask);
			}
		User::LeaveIfError(iSprite.AppendMember(iSpriteMember[i]));
		}

	// Activate the sprite
	User::LeaveIfError(iSprite.Activate());
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
	// Draw a hatched pattern to illustrate that sprite is drawn only 
	// where its bitmap mask is 0
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

void CMainWindow::HandlePointerEvent (TPointerEvent& /*aPointerEvent*/)
	{	
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
|				Gets the key code from the key event.  Exits on 'Escape'
\****************************************************************************/
void CExampleWsClient::HandleKeyEventL (TKeyEvent& aKeyEvent)
	{
	TUint	code = aKeyEvent.iCode;
	switch (code)
		{
		case EKeyLeftArrow:
			iSprite->UpdatePos(TPoint(-2,0));
			break;
		case EKeyRightArrow:
			iSprite->UpdatePos(TPoint(2,0));
			break;
		case EKeyUpArrow:
			iSprite->UpdatePos(TPoint(0,-2));
			break;
		case EKeyDownArrow:
			iSprite->UpdatePos(TPoint(0,2));
			break;
		}
	}

