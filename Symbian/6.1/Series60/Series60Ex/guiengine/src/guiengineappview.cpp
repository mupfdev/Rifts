/* Copyright (c) 2001, Nokia. All rights reserved */
#include <coemain.h>
#include <eikenv.h>
#include "GuiEngine.pan"
#include "GuiEngineAppView.h"
#include "GuiEngineDocument.h"
#include "Circle.h"
#include "Rectangle.h"

using namespace NShapes;

static const TInt KBlackPointer = 1;
static const TInt KBrushRadius = 5;
static const TInt KBrushHeight = 10;
static const TInt KBrushWidth = 10;

CGuiEngineAppView* CGuiEngineAppView::NewLC(const TRect& aRect, CGuiEngineDocument* aDocument)
	{
    CGuiEngineAppView* self = new (ELeave) CGuiEngineAppView(aDocument);

    CleanupStack::PushL(self);
    self->ConstructL(aRect);

    return self;
	}

CGuiEngineAppView* CGuiEngineAppView::NewL(const TRect& aRect, CGuiEngineDocument* aDocument)
	{
    CGuiEngineAppView* self = NewLC(aRect, aDocument);

    CleanupStack::Pop(self);

    return self;
	}

void CGuiEngineAppView::ConstructL(const TRect& aRect)
	{
    // Create a window for this application view
    CreateWindowL();

    // Set the windows size
    SetRect(aRect);

    // Activate the window, which makes it ready to be drawn
    ActivateL();

    Window().SetPointerCursor(KBlackPointer);
	}

void CGuiEngineAppView::Draw(const TRect& /*aRect*/) const
	{
	CWindowGc& graphicsContext = SystemGc();

	// Clear the application view
	graphicsContext.Clear();

	// draw the 'cursor' crosshair, size 10 pixels by 10 pixels
	graphicsContext.SetPenSize(TSize(1,1));
    graphicsContext.SetPenColor(KRgbBlack);
	graphicsContext.DrawLine ( TPoint(iPosition.iX - 10, iPosition.iY), TPoint(iPosition.iX + 10, iPosition.iY));
	graphicsContext.DrawLine ( TPoint(iPosition.iX, iPosition.iY - 10), TPoint(iPosition.iX, iPosition.iY + 10));

	// draw all the current shapes
    TShape* shape = iDocument->Model()->GetNextShape();
    while (shape != NULL) 
		{
        shape->Draw(graphicsContext);
        shape = iDocument->Model()->GetNextShape();
		}
	}

CGuiEngineAppView::CGuiEngineAppView(CGuiEngineDocument* aDocument)
:	iDocument(aDocument),
    iPosition (10, 10)
	{
    // No implementation required
	}


CGuiEngineAppView::~CGuiEngineAppView()
	{
    iDocument = NULL;	//	Not the owner
	}

void CGuiEngineAppView::Clear()
    {
    iDocument->Model()->Clear();
    DrawNow();
    }


void CGuiEngineAppView::SetBrushShapeType(TBrushShapeType aShapeType)
    {
    iBrushShapeType = aShapeType;
    }

CGuiEngineAppView::TBrushShapeType CGuiEngineAppView::BrushShapeType() const
    {
    return iBrushShapeType;
    }

void CGuiEngineAppView::ExternalizeL(RWriteStream& aStream) const
    {
    aStream.WriteInt8L((TInt8)iBrushShapeType);
    }

void CGuiEngineAppView::InternalizeL(RReadStream& aStream)
    {
    iBrushShapeType = (TBrushShapeType)aStream.ReadInt8L();
    }


TKeyResponse CGuiEngineAppView::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
	{	
	if(aType != EEventKey)
		{
		return EKeyWasNotConsumed;
		}

	// move left
	if (aKeyEvent.iScanCode == EStdKeyLeftArrow)
		{
		if (iPosition.iX >  (Rect().iTl.iX + 10))
			{
			--iPosition.iX;
			DrawNow();
			}
		return EKeyWasConsumed;
		}

	// move right
	else if (aKeyEvent.iScanCode == EStdKeyRightArrow)
		{
		if (iPosition.iX < (Rect().iBr.iX - 10))
			{
			++iPosition.iX;
			DrawNow();
			}
		return EKeyWasConsumed;
		}

	// move up
	else if (aKeyEvent.iScanCode == EStdKeyUpArrow)
		{
		if (iPosition.iY > (Rect().iTl.iY + 10))
			{
			--iPosition.iY;
			DrawNow();
			}
		return EKeyWasConsumed;
		}

	// move down
	else if (aKeyEvent.iScanCode == EStdKeyDownArrow)
		{
		if (iPosition.iY < (Rect().iBr.iY - 10))
			{
			++iPosition.iY;
			DrawNow();
			}
		return EKeyWasConsumed;
		}


	// place a shape
	else if (aKeyEvent.iScanCode == EStdKeyDevice3)
		{
        TShape* newShape = NULL;
	    // Update the co-ordinates in the model to the position at which the
	    // pointer event occurred.

        switch (iBrushShapeType) 
            {
            case ECircle :
                newShape = new (ELeave) TCircle(iPosition, KBrushRadius);
	            iDocument->Model()->AddShapeL(newShape);		//	Takes ownership
                break;
            case ERectangle :
                newShape = new (ELeave) TRectangle(iPosition, KBrushHeight, KBrushWidth);
	            iDocument->Model()->AddShapeL(newShape);		//	Takes ownership
                break;
            default :
				User::Panic(KGuiEnginePanicName, EGuiEngineInvalidBrushType);
            }
        DrawNow();
		return EKeyWasConsumed;
		}

	return EKeyWasNotConsumed;
	}
