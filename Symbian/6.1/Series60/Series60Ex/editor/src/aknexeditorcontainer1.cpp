/*
* ============================================================================
*  Name     : CAknExEditorContainer1 from CCoeControl, MCoeControlObserver
*  Part of  : AknExEditor
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include <eiklabel.h>  // for example label control
#include <barsread.h>  // for resource reader
#include <eikedwin.h>  // for CEikEdwin
#include <eikgted.h>   // for CEikGlobalTextEditor

#include <AknExEditor.rsg>
#include "aknexeditor.hrh"
#include "AknExEditorContainer1.h"

// Definitions
#define EDWIN_LABEL_POS     TPoint(10, 10)
#define EDWIN_POS           TPoint(10, 25)
#define GTEXTED_LABEL_POS   TPoint(10, 60)
#define GTEXTED_POS         TPoint(10, 75)


// Constants
const TInt KNumberOfControls    = 4;
const TInt KBufLength           = 64;

// Enumarations
enum TControls
    {
    EEdwinPrompt,
    EEdwin,
    EGTextEdPrompt,
    EGTextEd
    };


// ================= MEMBER FUNCTIONS =======================

// C++ default constructor can NOT contain any code, that
// might leave.
//
CAknExEditorContainer1::CAknExEditorContainer1()
                        :iLabel1(NULL), iLabel2(NULL),
                         iEdwin(NULL), iGTextEd(NULL)
    {
    }

// EPOC default constructor can leave.
void CAknExEditorContainer1::ConstructL(const TRect& aRect)
    {
    CreateWindowL();

    TBuf<KBufLength> text;

    iCoeEnv->ReadResource(text, R_AKNEXEDITOR_VIEW1_LABEL1);
    iLabel1 = new (ELeave) CEikLabel;
    iLabel1->SetContainerWindowL(*this);
    iLabel1->SetTextL(text);
    iLabel1->SetExtent(EDWIN_LABEL_POS, iLabel1->MinimumSize());

    iCoeEnv->ReadResource(text, R_AKNEXEDITOR_VIEW1_LABEL2);
    iLabel2 = new (ELeave) CEikLabel;
    iLabel2->SetContainerWindowL(*this);
    iLabel2->SetTextL(text);
    iLabel2->SetExtent(GTEXTED_LABEL_POS, iLabel1->MinimumSize());

    TResourceReader reader;
    iCoeEnv->CreateResourceReaderLC(reader, R_AKNEXEDITOR_VIEW1_EDWIN);
    iEdwin = new (ELeave) CEikEdwin;
    iEdwin->SetContainerWindowL(*this);
    iEdwin->ConstructFromResourceL(reader);
    CleanupStack::PopAndDestroy();  // Resource reader
    iEdwin->SetExtent(EDWIN_POS, iEdwin->MinimumSize());

    iCoeEnv->CreateResourceReaderLC(reader, R_AKNEXEDITOR_VIEW1_GTEXTED);
    iGTextEd = new (ELeave) CEikGlobalTextEditor;
    iGTextEd->SetContainerWindowL(*this);
    iGTextEd->ConstructFromResourceL(reader);
    CleanupStack::PopAndDestroy();  // Resource reader
    iGTextEd->SetExtent(GTEXTED_POS, iGTextEd->MinimumSize());

    iEdwin->SetFocus(ETrue);

    SetRect(aRect);
    ActivateL();
    }

// Destructor
CAknExEditorContainer1::~CAknExEditorContainer1()
    {
    delete iLabel1;
    delete iLabel2;
    delete iEdwin;
    delete iGTextEd;
    }

// ---------------------------------------------------------
// CAknExEditorContainer::FocusTo(TInt aCommand)
// Change foccused control.
// (other items were commented in a header).
// ---------------------------------------------------------
//

void CAknExEditorContainer1::FocusTo(TInt aCommand)
    {
    switch(aCommand)
        {
        case EAknExEditorCmdSelectEdwin1:
            iGTextEd->SetFocus(EFalse);
            iEdwin->SetFocus(ETrue);
            break;
        case EAknExEditorCmdSelectGTextEd1:
            iEdwin->SetFocus(EFalse);
            iGTextEd->SetFocus(ETrue);
            break;
        default:
            break;
        }
    }

// ---------------------------------------------------------
// CAknExEditorContainer1::SizeChanged()
// Called by framework when the view size is changed
// (other items were commented in a header).
// ---------------------------------------------------------
//
void CAknExEditorContainer1::SizeChanged()
    {
    }

// ---------------------------------------------------------
// CAknExEditorContainer1::CountComponentControls() const
// (other items were commented in a header).
// ---------------------------------------------------------
//
TInt CAknExEditorContainer1::CountComponentControls() const
    {
    return KNumberOfControls; // return nbr of controls inside this container
    }

// ---------------------------------------------------------
// CAknExEditorContainer1::ComponentControl(TInt aIndex) const
// (other items were commented in a header).
// ---------------------------------------------------------
//
CCoeControl* CAknExEditorContainer1::ComponentControl(TInt aIndex) const
    {
    switch (aIndex)
        {
        case EEdwinPrompt:
            return iLabel1;
        case EEdwin:
            return iEdwin;
        case EGTextEdPrompt:
            return iLabel2;
        case EGTextEd:
            return iGTextEd;
        default:
            return NULL;
        }
    }

// ---------------------------------------------------------
// CAknExEditorContainer1::Draw(const TRect& aRect) const
// (other items were commented in a header).
// ---------------------------------------------------------
//
void CAknExEditorContainer1::Draw(const TRect& aRect) const
    {
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle(CGraphicsContext::ENullPen);
    gc.SetBrushColor(KRgbGray);
    gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
    gc.DrawRect(aRect);
    }

// ---------------------------------------------------------
// CAknExEditorContainer1::OfferKeyEventL(...)
// Notify key events to editors.
// (other items were commented in a header).
// ---------------------------------------------------------
//
TKeyResponse CAknExEditorContainer1::OfferKeyEventL(
    const TKeyEvent& aKeyEvent, TEventCode aType)
    {
    if (iEdwin)
        {
        if (iEdwin->IsFocused())
            {
            return iEdwin->OfferKeyEventL(aKeyEvent, aType);
            }
        }
    if (iGTextEd)
        {
        if (iGTextEd->IsFocused())
            {
            return iGTextEd->OfferKeyEventL(aKeyEvent, aType);
            }
        }
    return EKeyWasNotConsumed;
    }


// ---------------------------------------------------------
// CAknExEditorContainer1::HandleControlEventL(
//     CCoeControl* aControl,TCoeEvent aEventType)
// (other items were commented in a header).
// ---------------------------------------------------------
//
void CAknExEditorContainer1::HandleControlEventL(
    CCoeControl* /*aControl*/,TCoeEvent /*aEventType*/)
    {
    }

// End of File  
