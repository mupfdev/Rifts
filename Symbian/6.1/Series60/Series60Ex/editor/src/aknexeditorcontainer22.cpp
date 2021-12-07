/*
* ============================================================================
*  Name     : CAknExEditorContainer22 from CCoeControl, MCoeControlObserver
*  Part of  : AknExEditor
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include <eiklabel.h>  // for example label control
#include <barsread.h>  // for resource reader
//#include <eikedwin.h>  // for CEikEdwin
#include <coemain.h>
#include <eikmfne.h>   // for Date, Timer, DateAndTimer editor

#include <AknExEditor.rsg>
#include "aknexeditor.hrh"
#include "AknExEditorContainer22.h"
#include "AknExEditorDialog.h"

// Definitions
#define TOP_POSITION        TPoint(10,5)
#define EDITOR_ROW_SIZE     TSize(0, 17)
#define LABEL_ROW_SIZE      TSize(0, 18)

#define TIME_DATE_DEFAULT_1 TDateTime(2000, EDecember, 6 - 1, 9, 0, 0, 0)
#define TIME_DATE_DEFAULT_2 TDateTime(2000, EDecember, 6 - 1, 0, 0, 0, 0)
#define TIME_DATE_DEFAULT_3 TDateTime(2000, EDecember, 26 - 1, 9, 0, 0, 0)

// Duration default is half an hour
#define DURATION_DEFAULT_1 1800
// Constants
const TInt KNumberOfControls    = 8;

// Enumarations
enum TControls
    {
    ETimePrompt,
    EDatePrompt,
    EDurationPrompt,
    ETimeAndDatePrompt,
    ETATimeEditor,
    ETADateEditor,
    ETADurationEditor,
    ETATimeAndDateEditor
    };


// ================= MEMBER FUNCTIONS =======================

// C++ default constructor can NOT contain any code, that
// might leave.
//
CAknExEditorContainer22::CAknExEditorContainer22()
        :   iLabel1(NULL), iLabel2(NULL), iLabel3(NULL),
            iTimeEditor(NULL), iDateEditor(NULL), iDurationEditor(NULL),
            iFocusedControl(NULL)
    {
    }

// EPOC default constructor can leave.
void CAknExEditorContainer22::ConstructL(const TRect& aRect)
    {
    CreateWindowL();

    TBuf<KBufLength> text;
    TPoint position = TOP_POSITION;

    // Create labels
    iCoeEnv->ReadResource(text, R_AKNEXEDITOR_VIEW22_LABEL1);
    iLabel1 = new (ELeave) CEikLabel;
    iLabel1->SetContainerWindowL(*this);
    iLabel1->SetTextL(text);
    iLabel1->SetExtent(position, iLabel1->MinimumSize());

    position = position + LABEL_ROW_SIZE + LABEL_ROW_SIZE;
    iCoeEnv->ReadResource(text, R_AKNEXEDITOR_VIEW22_LABEL2);
    iLabel2 = new (ELeave) CEikLabel;
    iLabel2->SetContainerWindowL(*this);
    iLabel2->SetTextL(text);
    iLabel2->SetExtent(position, iLabel2->MinimumSize());

    position = position + LABEL_ROW_SIZE + LABEL_ROW_SIZE;
    iCoeEnv->ReadResource(text, R_AKNEXEDITOR_VIEW22_LABEL3);
    iLabel3 = new (ELeave) CEikLabel;
    iLabel3->SetContainerWindowL(*this);
    iLabel3->SetTextL(text);
    iLabel3->SetExtent(position, iLabel3->MinimumSize());

    position = position + LABEL_ROW_SIZE + LABEL_ROW_SIZE;
    iCoeEnv->ReadResource(text, R_AKNEXEDITOR_VIEW22_LABEL4);
    iLabel4 = new (ELeave) CEikLabel;
    iLabel4->SetContainerWindowL(*this);
    iLabel4->SetTextL(text);
    iLabel4->SetExtent(position, iLabel4->MinimumSize());

    // Create editors.
    position = TOP_POSITION + EDITOR_ROW_SIZE;
    TResourceReader reader;

    iCoeEnv->CreateResourceReaderLC(reader, R_AKNEXEDITOR_VIEW22_TIME_EDITOR);
    iTimeEditor = new (ELeave) CEikTimeEditor;
    iTimeEditor->SetContainerWindowL(*this);
    iTimeEditor->ConstructFromResourceL(reader);
    CleanupStack::PopAndDestroy();  // Resource reader
    iTimeEditor->SetExtent(position, iTimeEditor->MinimumSize());

    TDateTime time = TIME_DATE_DEFAULT_1;
    iTimeEditor->SetTime(time);

    position = position + EDITOR_ROW_SIZE + EDITOR_ROW_SIZE;
    iCoeEnv->CreateResourceReaderLC(reader, R_AKNEXEDITOR_VIEW22_DATE_EDITOR);
    iDateEditor = new (ELeave) CEikDateEditor;
    iDateEditor->SetContainerWindowL(*this);
    iDateEditor->ConstructFromResourceL(reader);
    CleanupStack::PopAndDestroy();  // Resource reader
    iDateEditor->SetExtent(position, iDateEditor->MinimumSize());
    time = TIME_DATE_DEFAULT_2;
    iDateEditor->SetDate(time);

    position = position + EDITOR_ROW_SIZE + EDITOR_ROW_SIZE;
    iCoeEnv->CreateResourceReaderLC(reader,
                                    R_AKNEXEDITOR_VIEW22_DURATION_EDITOR);
    iDurationEditor = new (ELeave) CEikDurationEditor;
    iDurationEditor->SetContainerWindowL(*this);
    iDurationEditor->ConstructFromResourceL(reader);
    CleanupStack::PopAndDestroy();  // Resource reader
    iDurationEditor->SetExtent(position, iDurationEditor->MinimumSize());
    TTimeIntervalSeconds duration = DURATION_DEFAULT_1;
    iDurationEditor->SetDuration(duration);

    position = position + EDITOR_ROW_SIZE + EDITOR_ROW_SIZE;
    iCoeEnv->CreateResourceReaderLC(reader,
                                    R_AKNEXEDITOR_VIEW22_TIME_AND_DATE_EDITOR);
    iTimeAndDateEditor = new (ELeave) CEikTimeAndDateEditor;
    iTimeAndDateEditor->SetContainerWindowL(*this);
    iTimeAndDateEditor->ConstructFromResourceL(reader);
    CleanupStack::PopAndDestroy();  // Resource reader
    iTimeAndDateEditor->SetExtent(position, iTimeAndDateEditor->MinimumSize());
    time = TIME_DATE_DEFAULT_3;
    iTimeAndDateEditor->SetTimeAndDate(time);

    iTimeEditor->SetFocus(ETrue);
    iFocusedControl = iTimeEditor;

    SetRect(aRect);
    ActivateL();
    }

// Destructor
CAknExEditorContainer22::~CAknExEditorContainer22()
    {
    delete iLabel1;
    delete iLabel2;
    delete iLabel3;
    delete iLabel4;
    delete iDateEditor;
    delete iTimeEditor;
    delete iDurationEditor;
    delete iTimeAndDateEditor;
    }

// ---------------------------------------------------------
// CAknExEditorContainer::FocusTo(TInt aCommand)
// Change foccused control and select part/all of it.
// (other items were commented in a header).
// ---------------------------------------------------------
//
void CAknExEditorContainer22::FocusTo(TInt aCommand)
    {
    switch(aCommand)
        {
        case EAknExEditorCmdSelectTimeEditor:
            iDateEditor->SetFocus(EFalse);
            iDurationEditor->SetFocus(EFalse);
            iTimeEditor->SetFocus(ETrue);
            iTimeAndDateEditor->SetFocus(EFalse);
            iFocusedControl = iTimeEditor;
            break;

        case EAknExEditorCmdSelectDateEditor:
            iDurationEditor->SetFocus(EFalse);
            iTimeEditor->SetFocus(EFalse);
            iTimeAndDateEditor->SetFocus(EFalse);
            iDateEditor->SetFocus(ETrue);
            iFocusedControl = iDateEditor;
            break;

        case EAknExEditorCmdSelectDurationEditor:
            iTimeEditor->SetFocus(EFalse);
            iDateEditor->SetFocus(EFalse);
            iDurationEditor->SetFocus(ETrue);
            iTimeAndDateEditor->SetFocus(EFalse);
            iFocusedControl = iDurationEditor;
            break;

        case EAknExEditorCmdSelectTimeAndDateEditor:
            iTimeEditor->SetFocus(EFalse);
            iDateEditor->SetFocus(EFalse);
            iDurationEditor->SetFocus(EFalse);
            iTimeAndDateEditor->SetFocus(ETrue);
            iFocusedControl = iTimeAndDateEditor;
            break;

        default:
            break;
        }
    }

// ---------------------------------------------------------
// CAknExEditorContainer22::SizeChanged()
// Called by framework when the view size is changed
// (other items were commented in a header).
// ---------------------------------------------------------
//
void CAknExEditorContainer22::SizeChanged()
    {
    }

// ---------------------------------------------------------
// CAknExEditorContainer22::CountComponentControls() const
// (other items were commented in a header).
// ---------------------------------------------------------
//
TInt CAknExEditorContainer22::CountComponentControls() const
    {
    return KNumberOfControls; // return nbr of controls inside this container
    }

// ---------------------------------------------------------
// CAknExEditorContainer22::ComponentControl(TInt aIndex) const
// (other items were commented in a header).
// ---------------------------------------------------------
//
CCoeControl* CAknExEditorContainer22::ComponentControl(TInt aIndex) const
    {
    switch (aIndex)
        {
        case ETimePrompt:
            return iLabel1;
        case EDatePrompt:
            return iLabel2;
        case EDurationPrompt:
            return iLabel3;
        case ETimeAndDatePrompt:
            return iLabel4;
        case ETATimeEditor:
            return iTimeEditor;
        case ETADateEditor:
            return iDateEditor;
        case ETADurationEditor:
            return iDurationEditor;
        case ETATimeAndDateEditor:
            return iTimeAndDateEditor;
        default:
            return NULL;
        }
    }

// ---------------------------------------------------------
// CAknExEditorContainer22::ShowFormL()
// Show form.
// (other items were commented in a header).
// ---------------------------------------------------------
//
void CAknExEditorContainer22::ShowFormL()
    {
    CAknExEditorDialog* dialog = new (ELeave) CAknExEditorDialog();
    dialog->ExecuteLD(R_AKNEXEDITOR_VIEW22_DIALOG);
    }

// ---------------------------------------------------------
// CAknExEditorContainer22::Draw(const TRect& aRect) const
// (other items were commented in a header).
// ---------------------------------------------------------
//
void CAknExEditorContainer22::Draw(const TRect& aRect) const
    {
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle(CGraphicsContext::ENullPen);
    gc.SetBrushColor(KRgbGray);
    gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
    gc.DrawRect(aRect);
    }

// ---------------------------------------------------------
// CAknExEditorContainer22::HandleControlEventL(
//     CCoeControl* aControl,TCoeEvent aEventType)
// (other items were commented in a header).
// ---------------------------------------------------------
//
void CAknExEditorContainer22::HandleControlEventL(
    CCoeControl* /*aControl*/,TCoeEvent /*aEventType*/)
    {
    }

// ---------------------------------------------------------
// CAknExEditorContainer22::OfferKeyEventL(...)
// (other items were commented in a header).
// ---------------------------------------------------------
//
TKeyResponse CAknExEditorContainer22::OfferKeyEventL(
    const TKeyEvent& aKeyEvent, TEventCode aType)
    {
    return iFocusedControl->OfferKeyEventL(aKeyEvent, aType);
    }


void CAknExEditorContainer22::PrepareForFocusLossL()
    {
    if (iFocusedControl)
        iFocusedControl->PrepareForFocusLossL();
    }

void CAknExEditorContainer22::FocusChanged(TDrawNow aDrawNow)
    {
    if (iFocusedControl)
        iFocusedControl->SetFocus(IsFocused(), aDrawNow);
    }

// End of File  
