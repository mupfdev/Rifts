/*
* ============================================================================
*  Name     : CAknExEditorContainer25 from CCoeControl, MCoeControlObserver
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
#include "AknExEditorcontainer25.h"
#include "AknExEditorDialog.h"

// Definitions
#define TOP_POSITION        TPoint(10, 10)
#define ROW_SIZE            TSize(0, 20)

#define TIME_12HOURS_DEFAULT_1 TDateTime(2000, EDecember, 6 - 1, 9, 0, 0, 0)
#define TIME_24HOURS_DEFAULT_2 TDateTime(2000, EDecember, 6 - 1, 0, 0, 0, 0)

// Constants
const TInt KNumberOfControls = 4;

// Enumarations
enum TControls
    {
    E12HoursPrompt,
    E24HoursPrompt,
    E12HoursEditor,
    E24HoursEditor
    };


// ================= MEMBER FUNCTIONS =======================

// C++ default constructor can NOT contain any code, that
// might leave.
//
CAknExEditorContainer25::CAknExEditorContainer25()
        :   iLabel1(NULL), iLabel2(NULL),
            i12HoursEditor(NULL), i24HoursEditor(NULL), iFocusedControl(NULL)
    {
    }

// EPOC default constructor can leave.
void CAknExEditorContainer25::ConstructL(const TRect& aRect)
    {
    CreateWindowL();

    TBuf<KBufLength> text;
    TPoint position = TOP_POSITION;

    // Create labels
    iCoeEnv->ReadResource(text, R_AKNEXEDITOR_VIEW25_LABEL1);
    iLabel1 = new (ELeave) CEikLabel;
    iLabel1->SetContainerWindowL(*this);
    iLabel1->SetTextL(text);
    iLabel1->SetExtent(position, iLabel1->MinimumSize());

    position = position + ROW_SIZE + ROW_SIZE;
    iCoeEnv->ReadResource(text, R_AKNEXEDITOR_VIEW25_LABEL2);
    iLabel2 = new (ELeave) CEikLabel;
    iLabel2->SetContainerWindowL(*this);
    iLabel2->SetTextL(text);
    iLabel2->SetExtent(position, iLabel2->MinimumSize());

    // Create editors.
    position = TOP_POSITION + ROW_SIZE;
    TResourceReader reader;

    iCoeEnv->CreateResourceReaderLC(reader, R_AKNEXEDITOR_VIEW25_12HOURS_EDITOR);
    i12HoursEditor = new (ELeave) CEikTimeEditor;
    i12HoursEditor->SetContainerWindowL(*this);
    i12HoursEditor->ConstructFromResourceL(reader);
    CleanupStack::PopAndDestroy();  // Resource reader
    i12HoursEditor->SetExtent(position, i12HoursEditor->MinimumSize());

    TDateTime time = TIME_12HOURS_DEFAULT_1;
    i12HoursEditor->SetTime(time);

    position = position + ROW_SIZE + ROW_SIZE;
    iCoeEnv->CreateResourceReaderLC(reader, R_AKNEXEDITOR_VIEW25_24HOURS_EDITOR);
    i24HoursEditor = new (ELeave) CEikTimeEditor;
    i24HoursEditor->SetContainerWindowL(*this);
    i24HoursEditor->ConstructFromResourceL(reader);
    CleanupStack::PopAndDestroy();  // Resource reader
    i24HoursEditor->SetExtent(position, i24HoursEditor->MinimumSize());
    time = TIME_24HOURS_DEFAULT_2;
    i24HoursEditor->SetTime(time);

    i12HoursEditor->SetFocus(ETrue);
    iFocusedControl = i12HoursEditor;

    SetRect(aRect);
    ActivateL();
    }

// Destructor
CAknExEditorContainer25::~CAknExEditorContainer25()
    {
    delete iLabel1;
    delete iLabel2;
    delete i12HoursEditor;
    delete i24HoursEditor;
    }

// ---------------------------------------------------------
// CAknExEditorContainer::FocusTo(TInt aCommand)
// Change foccused control and select part/all of it.
// (other items were commented in a header).
// ---------------------------------------------------------
//
void CAknExEditorContainer25::FocusTo(TInt aCommand)
    {
    switch(aCommand)
        {
        case EAknExEditorCmdSelect12HoursEditor:
            i24HoursEditor->SetFocus(EFalse);
            i12HoursEditor->SetFocus(ETrue);
            iFocusedControl = i12HoursEditor;
            break;

        case EAknExEditorCmdSelect24HoursEditor:
            i12HoursEditor->SetFocus(EFalse);
            i24HoursEditor->SetFocus(ETrue);
            iFocusedControl = i24HoursEditor;
            break;

        default:
            break;
        }
    }

// ---------------------------------------------------------
// CAknExEditorContainer25::ShowFormL()
// Show form.
// (other items were commented in a header).
// ---------------------------------------------------------
//
void CAknExEditorContainer25::ShowFormL()
    {
    CAknExEditorDialog* dialog = new (ELeave) CAknExEditorDialog();
    dialog->ExecuteLD(R_AKNEXEDITOR_VIEW25_DIALOG);
    }

// ---------------------------------------------------------
// CAknExEditorContainer25::SizeChanged()
// Called by framework when the view size is changed
// (other items were commented in a header).
// ---------------------------------------------------------
//
void CAknExEditorContainer25::SizeChanged()
    {
    }

// ---------------------------------------------------------
// CAknExEditorContainer25::CountComponentControls() const
// (other items were commented in a header).
// ---------------------------------------------------------
//
TInt CAknExEditorContainer25::CountComponentControls() const
    {
    return KNumberOfControls; // return nbr of controls inside this container
    }

// ---------------------------------------------------------
// CAknExEditorContainer25::ComponentControl(TInt aIndex) const
// (other items were commented in a header).
// ---------------------------------------------------------
//
CCoeControl* CAknExEditorContainer25::ComponentControl(TInt aIndex) const
    {
    switch (aIndex)
        {
        case E12HoursPrompt:
            return iLabel1;
        case E24HoursPrompt:
            return iLabel2;
        case E12HoursEditor:
            return i12HoursEditor;
        case E24HoursEditor:
            return i24HoursEditor;
        default:
            return NULL;
        }
    }

// ---------------------------------------------------------
// CAknExEditorContainer25::Draw(const TRect& aRect) const
// (other items were commented in a header).
// ---------------------------------------------------------
//
void CAknExEditorContainer25::Draw(const TRect& aRect) const
    {
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle(CGraphicsContext::ENullPen);
    gc.SetBrushColor(KRgbGray);
    gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
    gc.DrawRect(aRect);
    }

// ---------------------------------------------------------
// CAknExEditorContainer25::OfferKeyEventL(...)
// (other items were commented in a header).
// ---------------------------------------------------------
//
TKeyResponse CAknExEditorContainer25::OfferKeyEventL(
    const TKeyEvent& aKeyEvent, TEventCode aType)
    {
    return iFocusedControl->OfferKeyEventL(aKeyEvent, aType);
    }

// ---------------------------------------------------------
// CAknExEditorContainer25::HandleControlEventL(
//     CCoeControl* aControl,TCoeEvent aEventType)
// (other items were commented in a header).
// ---------------------------------------------------------
//
void CAknExEditorContainer25::HandleControlEventL(
    CCoeControl* /*aControl*/,TCoeEvent /*aEventType*/)
    {
    }

// End of File  
