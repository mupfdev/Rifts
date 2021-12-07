/*
* ============================================================================
*  Name     : CAknExEditorContainer9 from CCoeControl, MCoeControlObserver
*  Part of  : AknExEditor
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include <eiklabel.h>  // for example label control
#include <barsread.h>  // for resource reader
#include <eikedwin.h>  // for CEikEdwin
#include <eikgted.h>   // for CEikGlobalTextEditor

#include <aknenv.h>
#include <avkon.hrh>

#include <AknExEditor.rsg>
#include "aknexeditor.hrh"
#include "AknExEditorContainer9.h"
#include "AknExEditorDialog.h"

// Definitions
#define EDWIN_LABEL_POS     TPoint(10, 0)
#define EDWIN_POS           TPoint(10, 15)
#define GTEXTED_LABEL_POS   TPoint(10, 70)
#define GTEXTED_POS         TPoint(10, 85)


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
CAknExEditorContainer9::CAknExEditorContainer9()
                        :iLabel1(NULL), iLabel2(NULL),
                         iEdwin(NULL), iGTextEd(NULL)
    {
    }

// EPOC default constructor can leave.
void CAknExEditorContainer9::ConstructL(const TRect& aRect)
    {
    CreateWindowL();

    TBuf<KBufLength> text;

    iCoeEnv->ReadResource(text, R_AKNEXEDITOR_VIEW9_LABEL1);
    iLabel1 = new (ELeave) CEikLabel;
    iLabel1->SetContainerWindowL(*this);
    iLabel1->SetTextL(text);
    iLabel1->SetExtent(EDWIN_LABEL_POS, iLabel1->MinimumSize());

    iCoeEnv->ReadResource(text, R_AKNEXEDITOR_VIEW9_LABEL2);
    iLabel2 = new (ELeave) CEikLabel;
    iLabel2->SetContainerWindowL(*this);
    iLabel2->SetTextL(text);
    iLabel2->SetExtent(GTEXTED_LABEL_POS, iLabel1->MinimumSize());

    TResourceReader reader;
    iCoeEnv->CreateResourceReaderLC(reader, R_AKNEXEDITOR_VIEW9_EDWIN);
    iEdwin = new (ELeave) CEikEdwin;
    iEdwin->SetContainerWindowL(*this);
    iEdwin->ConstructFromResourceL(reader);
    CleanupStack::PopAndDestroy();  // Resource reader
    iEdwin->SetExtent(EDWIN_POS, iEdwin->MinimumSize());

    iCoeEnv->CreateResourceReaderLC(reader, R_AKNEXEDITOR_VIEW9_GTEXTED);
    iGTextEd = new (ELeave) CEikGlobalTextEditor;
    iGTextEd->SetContainerWindowL(*this);
    iGTextEd->ConstructFromResourceL(reader);
    CleanupStack::PopAndDestroy();  // Resource reader
    iGTextEd->SetExtent(GTEXTED_POS, iGTextEd->MinimumSize());

//    iEdwin->SetFocus(ETrue);
    FocusTo(EAknExEditorCmdSelectEdwin1);

    SetRect(aRect);
    ActivateL();
    }

// Destructor
CAknExEditorContainer9::~CAknExEditorContainer9()
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
void CAknExEditorContainer9::FocusTo(TInt aCommand)
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
// CAknExEditorContainer9::ShowFormL()
// Show form.
// (other items were commented in a header).
// ---------------------------------------------------------
//
void CAknExEditorContainer9::ShowFormL()
    {
    CAknExEditorDialog* dialog = new (ELeave) CAknExEditorDialog();
    dialog->ExecuteLD(R_AKNEXEDITOR_VIEW9_DIALOG);
    }


// ---------------------------------------------------------
// CAknExEditorContainer9::SizeChanged()
// Called by framework when the view size is changed
// (other items were commented in a header).
// ---------------------------------------------------------
//
void CAknExEditorContainer9::SizeChanged()
    {
    }

// ---------------------------------------------------------
// CAknExEditorContainer9::CountComponentControls() const
// (other items were commented in a header).
// ---------------------------------------------------------
//
TInt CAknExEditorContainer9::CountComponentControls() const
    {
    return KNumberOfControls; // return nbr of controls inside this container
    }

// ---------------------------------------------------------
// CAknExEditorContainer9::ComponentControl(TInt aIndex) const
// (other items were commented in a header).
// ---------------------------------------------------------
//
CCoeControl* CAknExEditorContainer9::ComponentControl(TInt aIndex) const
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
// CAknExEditorContainer9::Draw(const TRect& aRect) const
// (other items were commented in a header).
// ---------------------------------------------------------
//
void CAknExEditorContainer9::Draw(const TRect& aRect) const
    {
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle(CGraphicsContext::ENullPen);
    gc.SetBrushColor(KRgbGray);
    gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
    gc.DrawRect(aRect);
    }

// ---------------------------------------------------------
// CAknExEditorContainer9::OfferKeyEventL(...)
// Notify key events to editors.
// (other items were commented in a header).
// ---------------------------------------------------------
//
TKeyResponse CAknExEditorContainer9::OfferKeyEventL(
    const TKeyEvent& aKeyEvent, TEventCode aType)
    {
    TKeyResponse ret = EKeyWasNotConsumed;

    if (iEdwin)
        {
        if (iEdwin->IsFocused())
            {
            ret =  iEdwin->OfferKeyEventL(aKeyEvent, aType);
            return ret;
            }
        }
    if (iGTextEd)
        {
        if (iGTextEd->IsFocused())
            {
            ret =  iGTextEd->OfferKeyEventL(aKeyEvent, aType);
            return ret;
            }
        }
    return EKeyWasNotConsumed;
    }


// ---------------------------------------------------------
// CAknExEditorContainer9::HandleControlEventL(
//     CCoeControl* aControl,TCoeEvent aEventType)
// (other items were commented in a header).
// ---------------------------------------------------------
//
void CAknExEditorContainer9::HandleControlEventL(
    CCoeControl* /*aControl*/,TCoeEvent /*aEventType*/)
    {
    }

// End of File  
