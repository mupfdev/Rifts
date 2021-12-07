/*
* ============================================================================
*  Name     : CAknExEditorContainer33 from CCoeControl, MCoeControlObserver
*  Part of  : AknExEditor
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES

#include <barsread.h>  // for resource reader
#include <eikedwin.h>  // for CEikEdwin

#include <AknExEditor.rsg>
#include "aknexeditor.hrh"
#include "AknExEditorContainer33.h"
#include <eikenv.h>

// Definitions

#define EDWIN1_POS   TPoint(10,25)
#define EDWIN2_POS   TPoint(10,85)

#define KDefaultWidth 10
#define KDefaultTextLimit 200
#define KDefaultNumberOfLines 2

// Constants

const TInt KNumberOfControls    = 2;

// Enumarations

enum TControls
    {
    EView33Edwin1,
    EView33Edwin2
    };

// ================= MEMBER FUNCTIONS =======================

// C++ default constructor can NOT contain any code, that
// might leave.
//
CAknExEditorContainer33::CAknExEditorContainer33() 
    {
    }

// EPOC default constructor can leave.

void CAknExEditorContainer33::ConstructL(const TRect& aRect)
    {
    CreateWindowL();

    iEdwin1 = new (ELeave) CEikEdwin;
    iEdwin1->ConstructL(EEikEdwinNoWrap,KDefaultWidth,KDefaultTextLimit,KDefaultNumberOfLines);
    iEdwin1->SetContainerWindowL(*this);
    iEdwin1->SetExtent(EDWIN1_POS, iEdwin1->MinimumSize());

    iEdwin2 = new (ELeave) CEikEdwin;
    iEdwin2->ConstructL(0,KDefaultWidth,KDefaultTextLimit,KDefaultNumberOfLines);
    iEdwin2->SetContainerWindowL(*this);
    iEdwin2->SetExtent(EDWIN2_POS, iEdwin2->MinimumSize());

    iEdwin1->SetFocus(ETrue);

    SetRect(aRect);
    ActivateL();
    }

// Destructor
CAknExEditorContainer33::~CAknExEditorContainer33()
    {
    delete iEdwin1;
    delete iEdwin2;
    }

// ---------------------------------------------------------
// CAknExEditorContainer33::SizeChanged()
// Called by framework when the view size is changed
// (other items were commented in a header).
// ---------------------------------------------------------
//
void CAknExEditorContainer33::SizeChanged()
    {
    }

// ---------------------------------------------------------
// CAknExEditorContainer33::CountComponentControls() const
// (other items were commented in a header).
// ---------------------------------------------------------
//
TInt CAknExEditorContainer33::CountComponentControls() const
    {
    return KNumberOfControls;
    }

//---------------------------------------------------------
// CAknExEditorContainer33::TestSelectedCase(TInt aCommand)
//---------------------------------------------------------
//

void CAknExEditorContainer33::TestSelectedCase(TInt aCommand)
{
    switch (aCommand)
    {
        case EAknExEditorSetWordWrapTrue:
             CallSetWordWrapL(ETrue);
             break;

        case EAknExEditorSetWordWrapFalse:
             CallSetWordWrapL(EFalse);
             break;
        default:
             break;
    }
}

// ---------------------------------------------------------
// CAknExEditorContainer33::CallSetWordWrapL(TBool aBool) 
// (other items were commented in a header).
// ---------------------------------------------------------
//

void CAknExEditorContainer33::CallSetWordWrapL(TBool aWrapIsOn)
{
    if((iEdwin1) && (iEdwin1->IsFocused()))

        aWrapIsOn ? iEdwin1->SetWordWrapL(ETrue):iEdwin1->SetWordWrapL(EFalse);

    else if((iEdwin2) && (iEdwin2->IsFocused()))

        aWrapIsOn ? iEdwin2->SetWordWrapL(ETrue):iEdwin2->SetWordWrapL(EFalse);

}

// ---------------------------------------------------------
// CAknExEditorContainer33::ComponentControl(TInt aIndex) const
// (other items were commented in a header).
// ---------------------------------------------------------
//

CCoeControl* CAknExEditorContainer33::ComponentControl(TInt aIndex) const
    {
    switch(aIndex)
        {
    case EView33Edwin1:
        return iEdwin1;
    case EView33Edwin2:
        return iEdwin2;
    default:
        return NULL;
        }
    }

// ---------------------------------------------------------
// CAknExEditorContainer33::Draw(const TRect& aRect) const
// (other items were commented in a header).
// ---------------------------------------------------------
//
void CAknExEditorContainer33::Draw(const TRect& aRect) const
    {
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle(CGraphicsContext::ENullPen);
    gc.SetBrushColor(KRgbGray);
    gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
    gc.DrawRect(aRect);

    TBuf <40> buf; 
    gc.UseFont(iEikonEnv->AnnotationFont());
    iCoeEnv->ReadResource(buf, R_AKNEXEDITOR_VIEW33_FLAGSET);
    gc.DrawText(buf,TPoint(10,20));
    iCoeEnv->ReadResource(buf, R_AKNEXEDITOR_VIEW33_FLAGNOTSET);
    gc.DrawText(buf,TPoint(10,80));
    }

// ---------------------------------------------------------
// CAknExEditorContainer33::OfferKeyEventL(...)
// Move focus with up/down key.
// (other items were commented in a header).
// ---------------------------------------------------------
//

TKeyResponse CAknExEditorContainer33::OfferKeyEventL(
    const TKeyEvent& aKeyEvent, TEventCode aType)
    {
      if (iEdwin1)
        {
            if (iEdwin1->IsFocused())
            {
                if((aType == EEventKey) && (aKeyEvent.iCode == EKeyDownArrow))
                {
                iEdwin1->SetFocus(EFalse);
                iEdwin2->SetFocus(ETrue);
                return EKeyWasConsumed;
                }
            return iEdwin1->OfferKeyEventL(aKeyEvent, aType);
            }
        }
       if (iEdwin2)
        {
            if (iEdwin2->IsFocused())
            {
                if ((aType == EEventKey) && (aKeyEvent.iCode == EKeyUpArrow))
                {
                iEdwin2->SetFocus(EFalse);
                iEdwin1->SetFocus(ETrue);
                return EKeyWasConsumed;
                }
            return iEdwin2->OfferKeyEventL(aKeyEvent, aType);
            }
        }
       return EKeyWasNotConsumed;
    }

// ---------------------------------------------------------
// CAknExEditorContainer33::HandleControlEventL(
//     CCoeControl* aControl,TCoeEvent aEventType)
// (other items were commented in a header).
// ---------------------------------------------------------
//

void CAknExEditorContainer33::HandleControlEventL(
    CCoeControl* /*aControl*/,TCoeEvent /*aEventType*/)
    {
    }

// End of File  
