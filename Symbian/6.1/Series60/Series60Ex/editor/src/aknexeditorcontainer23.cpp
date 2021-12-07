/*
* ============================================================================
*  Name     : CAknExEditorContainer23 from CCoeControl, MCoeControlObserver
*  Part of  : AknExEditor
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include <eiklabel.h>       // for example label control
#include <barsread.h>       // for resource reader
#include <coemain.h>
#include <eikenv.h>
#include <AknNumSecEd.h>    // for numeric secret editor
#include <eikseced.h>       // for secret editor

#include <AknExEditor.rsg>
#include "aknexeditor.hrh"
#include "AknExEditorContainer23.h"
#include "AknExEditorDialog.h"

// Definitions
#define TOP_POSITION        TPoint(10,10)
#define ROW_SIZE            TSize(0, 20)

// Constants
const TInt KNumberOfControls    = 4;

// Enumarations
enum TControls
    {
    ENumSecretPrompt,
    ESecretPrompt,
    ENumSecretEditor,
    ETASecretEditor
    };


// ================= MEMBER FUNCTIONS =======================

// C++ default constructor can NOT contain any code, that
// might leave.
//
CAknExEditorContainer23::CAknExEditorContainer23()
        :   iLabel1(NULL), iLabel2(NULL),
            iNumSecretEditor(NULL), iSecretEditor(NULL)
    {
    }

// EPOC default constructor can leave.
void CAknExEditorContainer23::ConstructL(const TRect& aRect)
    {
    CreateWindowL();

    TBuf<KBufLength> text;
    TPoint position = TOP_POSITION;

    // Create labels
    iCoeEnv->ReadResource(text, R_AKNEXEDITOR_VIEW23_LABEL1);
    iLabel1 = new (ELeave) CEikLabel;
    iLabel1->SetContainerWindowL(*this);
    iLabel1->SetTextL(text);
    iLabel1->SetExtent(position, iLabel1->MinimumSize());

    position = position + ROW_SIZE + ROW_SIZE;
    iCoeEnv->ReadResource(text, R_AKNEXEDITOR_VIEW23_LABEL2);
    iLabel2 = new (ELeave) CEikLabel;
    iLabel2->SetContainerWindowL(*this);
    iLabel2->SetTextL(text);
    iLabel2->SetExtent(position, iLabel2->MinimumSize());

    // Create editors.
    position = TOP_POSITION + ROW_SIZE;
    TResourceReader reader;

    iCoeEnv->CreateResourceReaderLC(reader,
                                    R_AKNEXEDITOR_VIEW23_NUMSECRET_EDITOR);
    iNumSecretEditor = new (ELeave) CAknNumericSecretEditor();
    iNumSecretEditor->SetContainerWindowL(*this);
    iNumSecretEditor->ConstructFromResourceL(reader);
    CleanupStack::PopAndDestroy();  // Resource reader
    iNumSecretEditor->SetExtent(position, iNumSecretEditor->MinimumSize());
//  ?? Set Default ??

    position = position + ROW_SIZE + ROW_SIZE;
    iCoeEnv->CreateResourceReaderLC(reader,
                                        R_AKNEXEDITOR_VIEW23_SECRET_EDITOR);
    iSecretEditor = new (ELeave) CEikSecretEditor;
    iSecretEditor->SetContainerWindowL(*this);
    iSecretEditor->ConstructFromResourceL(reader);
    CleanupStack::PopAndDestroy();  // Resource reader
    iSecretEditor->SetExtent(position, iSecretEditor->MinimumSize());
// ?? Set default ??

    iNumSecretEditor->SetFocus(ETrue);
    iFocusedControl = iNumSecretEditor;

    SetRect(aRect);
    ActivateL();
    }

// Destructor
CAknExEditorContainer23::~CAknExEditorContainer23()
    {
    delete iLabel1;
    delete iLabel2;
    delete iNumSecretEditor;
    delete iSecretEditor;
    // NEVER DELETE iFocusedControl.
    }

// ---------------------------------------------------------
// CAknExEditorContainer::FocusTo(TInt aCommand)
// Change foccused control and select part/all of it.
// (other items were commented in a header).
// ---------------------------------------------------------
//
void CAknExEditorContainer23::FocusTo(TInt aCommand)
    {
    switch(aCommand)
        {
        case EAknExEditorCmdSelectNumSecretEditor:
            iSecretEditor->SetFocus(EFalse);
            iNumSecretEditor->SetFocus(ETrue);
            iFocusedControl = iNumSecretEditor;
            break;

        case EAknExEditorCmdSelectSecretEditor:
            iNumSecretEditor->SetFocus(EFalse);
            iSecretEditor->SetFocus(ETrue);
            iFocusedControl = iSecretEditor;
            break;

        default:
            break;
        }
    }

// ---------------------------------------------------------
// CAknExEditorContainer23::SizeChanged()
// Called by framework when the view size is changed
// (other items were commented in a header).
// ---------------------------------------------------------
//
void CAknExEditorContainer23::SizeChanged()
    {
    }

// ---------------------------------------------------------
// CAknExEditorContainer23::CountComponentControls() const
// (other items were commented in a header).
// ---------------------------------------------------------
//
TInt CAknExEditorContainer23::CountComponentControls() const
    {
    return KNumberOfControls; // return nbr of controls inside this container
    }

// ---------------------------------------------------------
// CAknExEditorContainer23::ComponentControl(TInt aIndex) const
// (other items were commented in a header).
// ---------------------------------------------------------
//
CCoeControl* CAknExEditorContainer23::ComponentControl(TInt aIndex) const
    {
    switch (aIndex)
        {
        case ENumSecretPrompt:
            return iLabel1;

        case ESecretPrompt:
            return iLabel2;

        case ENumSecretEditor:
            return iNumSecretEditor;

        case ETASecretEditor:
            return iSecretEditor;

        default:
            return NULL;
        }
    }

// ---------------------------------------------------------
// CAknExEditorContainer23::ShowFormL()
// Show form.
// (other items were commented in a header).
// ---------------------------------------------------------
//
void CAknExEditorContainer23::ShowFormL()
    {
    CAknExEditorDialog* dialog = new (ELeave) CAknExEditorDialog();
    dialog->ExecuteLD(R_AKNEXEDITOR_VIEW23_DIALOG);
    }

// ---------------------------------------------------------
// CAknExEditorContainer23::ShowEditorText()
// Show text of editor which has focus.
// (other items were commented in a header).
// ---------------------------------------------------------
//
void CAknExEditorContainer23::ShowEditorText()
    {
    TBuf<KBufLength> text;

    if (iFocusedControl == iNumSecretEditor)
        {
        iNumSecretEditor->GetText(text);
        }
    else if (iFocusedControl == iSecretEditor)
        {
        iSecretEditor->GetText(text);
        }
        iEikonEnv->AlertWin(text);
    }


// ---------------------------------------------------------
// CAknExEditorContainer23::Draw(const TRect& aRect) const
// (other items were commented in a header).
// ---------------------------------------------------------
//
void CAknExEditorContainer23::Draw(const TRect& aRect) const
    {
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle(CGraphicsContext::ENullPen);
    gc.SetBrushColor(KRgbGray);
    gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
    gc.DrawRect(aRect);
    }

// ---------------------------------------------------------
// CAknExEditorContainer23::HandleControlEventL(
//     CCoeControl* aControl,TCoeEvent aEventType)
// (other items were commented in a header).
// ---------------------------------------------------------
//
void CAknExEditorContainer23::HandleControlEventL(
    CCoeControl* /*aControl*/,TCoeEvent /*aEventType*/)
    {
    }

// ---------------------------------------------------------
// CAknExEditorContainer23::OfferKeyEventL(...)
// (other items were commented in a header).
// ---------------------------------------------------------
//
TKeyResponse CAknExEditorContainer23::OfferKeyEventL(
    const TKeyEvent& aKeyEvent, TEventCode aType)
    {
    return iFocusedControl->OfferKeyEventL(aKeyEvent, aType);
    }


void CAknExEditorContainer23::TestSelectedAPIL(TInt aCommand)
    {
    TBuf<5> setText;
    TPoint position = TOP_POSITION;
    position = position + ROW_SIZE + ROW_SIZE+ ROW_SIZE;
    iNumSecretEditor->SetFocus(EFalse);
    iSecretEditor->SetFocus(ETrue);
    iFocusedControl = iSecretEditor;

    switch(aCommand)
        {
        case EAknExEditorCmdView23InitializeDisplay5:
        iSecretEditor->InitializeDisplay(5);
        break;

        case EAknExEditorCmdView23InitializeDisplay10:
        iSecretEditor->InitializeDisplay(10);
        break;

        case EAknExEditorCmdView23Reset:
        iSecretEditor->Reset();
        break;

        case EAknExEditorCmdView23SetMaxLength5:
        iSecretEditor->SetMaxLength(5);
        break;

        case EAknExEditorCmdView23SetMaxLength10:
        iSecretEditor->SetMaxLength(10);
        break;

        case EAknExEditorCmdView23SetText:
        iCoeEnv->ReadResource(setText, R_AKNEXEDITOR_VIEW23_SETTEXT_PIN);
        iSecretEditor->SetText(setText);
        break;
        }

    }
// End of File  
