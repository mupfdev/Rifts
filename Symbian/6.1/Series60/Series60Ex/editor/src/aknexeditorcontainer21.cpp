/*
* ============================================================================
*  Name     : CAknExEditorContainer21 from CCoeControl, MCoeControlObserver
*  Part of  : AknExEditor
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include <eiklabel.h>  // for example label control
#include <barsread.h>  // for resource reader
#include <eikenv.h>
#include <coemain.h>
#include <aknipfed.h>   // for IP Address Editor
#include <in_sock.h>
#include <aknnotedialog.h>

#include <AknExEditor.rsg>
#include "aknexeditor.hrh"
#include "AknExEditorContainer21.h"
#include "AknExEditorDialog.h"

/*
// Definitions
#define LABEL_POS   TPoint(10, 10)
#define EDITOR_POS  TPoint(10, 25)
*/

// Constants
const TInt KNumberOfControls    = 6;
const TInt KNoOfEditors         = 3;
const TInt KBufLength           = 64;

/*
// Enumarations
enum TControls
    {
    ELabel,
    EEditor
    };
*/

// ================= MEMBER FUNCTIONS =======================

// C++ default constructor can NOT contain any code, that
// might leave.
//
CAknExEditorContainer21::CAknExEditorContainer21()
    :iFocusControl(0)
    {
    }

// EPOC default constructor can leave.
void CAknExEditorContainer21::ConstructL(const TRect& aRect)
    {
    CreateWindowL();
    SetRect(aRect);

    TBuf<KBufLength> text;
    TPoint top(10, 10);
    TPoint next(0, 15);
    TPoint startPoint(top);

    iCoeEnv->ReadResource(text, R_AKNEXEDITOR_VIEW21_LABEL);
    iLabel[0] = new (ELeave) CEikLabel;
    iLabel[0]->SetContainerWindowL(*this);
    iLabel[0]->SetFont(iEikonEnv->SymbolFont());
    iLabel[0]->SetTextL(text);
    iLabel[0]->SetExtent(startPoint, iLabel[0]->MinimumSize());

    TInetAddr lowAdr;
    lowAdr.SetAddress(KInetAddrNone);
    TInetAddr highAdr;
    highAdr.SetAddress(KInetAddrAll);

    startPoint+=next;
    iIpEditor[0] = CAknIpFieldEditor::NewL(lowAdr, highAdr, lowAdr);
    iIpEditor[0]->SetContainerWindowL(*this);
    iIpEditor[0]->SetExtent(startPoint, iIpEditor[0]->MinimumSize());
    iIpEditor[0]->SetNonFocusing();

    iCoeEnv->ReadResource(text, R_AKNEXEDITOR_VIEW21_CREATEDFROMRESOURCE);
    startPoint+=next+TPoint(0,5);
    iLabel[1] = new (ELeave) CEikLabel;
    iLabel[1]->SetContainerWindowL(*this);
    iLabel[1]->SetFont(iEikonEnv->SymbolFont());
    iLabel[1]->SetTextL(text);
    iLabel[1]->SetExtent(startPoint, iLabel[1]->MinimumSize());

    // creating from resource
    TResourceReader reader;
    iCoeEnv->CreateResourceReaderLC(reader, R_IP_FIELD_EDITOR);

    startPoint+=next;
    iIpEditor[1] = CAknIpFieldEditor::NewL();
    iIpEditor[1]->SetContainerWindowL(*this);
    iIpEditor[1]->ConstructFromResourceL(reader);
    iIpEditor[1]->SetExtent(startPoint, iIpEditor[1]->MinimumSize());
    iIpEditor[1]->SetNonFocusing();
    CleanupStack::PopAndDestroy();  // for reader

    iCoeEnv->ReadResource(text, R_AKNEXEDITOR_VIEW21_SETGETMINMAX);
    startPoint+=next+TPoint(0,5);
    iLabel[2] = new (ELeave) CEikLabel;
    iLabel[2]->SetContainerWindowL(*this);
    iLabel[2]->SetFont(iEikonEnv->SymbolFont());
    iLabel[2]->SetTextL(text);
    iLabel[2]->SetExtent(startPoint, iLabel[2]->MinimumSize());

    startPoint+=next;
    iIpEditor[2] = CAknIpFieldEditor::NewL(lowAdr, highAdr, lowAdr);
    iIpEditor[2]->SetContainerWindowL(*this);
    iIpEditor[2]->SetExtent(startPoint, iIpEditor[2]->MinimumSize());
    iIpEditor[2]->SetNonFocusing();
    iIpEditor[1]->GetMinimumAndMaximum(lowAdr, highAdr);
    iIpEditor[2]->SetMinimumAndMaximum(lowAdr, highAdr);

    iIpEditor[0]->SetFocus(ETrue, EDrawNow);
    ActivateL();
    }

// Destructor
CAknExEditorContainer21::~CAknExEditorContainer21()
    {
    for (TInt i=0; i < KNoOfEditors;i++)
        {
        delete iLabel[i];
        delete iIpEditor[i];
        }
    }

// ---------------------------------------------------------
// CAknExEditorContainer21::ShowFormL()
// Show form.
// (other items were commented in a header).
// ---------------------------------------------------------
//
void CAknExEditorContainer21::ShowFormL()
    {
/*
    CAknExEditorDialog* dialog = new (ELeave) CAknExEditorDialog();
    dialog->ExecuteLD(R_AKNEXEDITOR_VIEW21_DIALOG);
*/
    }

// ---------------------------------------------------------
// CAknExEditorContainer21::SizeChanged()
// Called by framework when the view size is changed
// (other items were commented in a header).
// ---------------------------------------------------------
//
void CAknExEditorContainer21::SizeChanged()
    {
    }

// ---------------------------------------------------------
// CAknExEditorContainer21::CountComponentControls() const
// (other items were commented in a header).
// ---------------------------------------------------------
//
TInt CAknExEditorContainer21::CountComponentControls() const
    {
    return KNumberOfControls; // return nbr of controls inside this container
    }

// ---------------------------------------------------------
// CAknExEditorContainer21::ComponentControl(TInt aIndex) const
// (other items were commented in a header).
// ---------------------------------------------------------
//
CCoeControl* CAknExEditorContainer21::ComponentControl(TInt aIndex) const
    {
    CCoeControl* cntl = NULL;

    switch (aIndex)
        {
        case 0:
            cntl=iLabel[0];
            break;
        case 1: 
            cntl=iLabel[1];
            break;
        case 2:
            cntl=iLabel[2];
            break;
        case 3:
            cntl=iIpEditor[0];
            break;
        case 4:
            cntl=iIpEditor[1];
            break;
        case 5:
            cntl=iIpEditor[2];
            break;
        default:
            break;
        }

    return cntl;
    }

// ---------------------------------------------------------
// CAknExEditorContainer21::Draw(const TRect& aRect) const
// (other items were commented in a header).
// ---------------------------------------------------------
//
void CAknExEditorContainer21::Draw(const TRect& aRect) const
    {
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle(CGraphicsContext::ENullPen);
    gc.SetBrushColor(KRgbGray);
    gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
    gc.DrawRect(aRect);
    }

// ---------------------------------------------------------
// CAknExEditorContainer21::OfferKeyEventL(...)
// Move focus with up/down key.
// (other items were commented in a header).
// ---------------------------------------------------------
//
TKeyResponse CAknExEditorContainer21::OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType)
    {
    TKeyResponse response=EKeyWasNotConsumed;

    if (aType == EEventKey)
        {
        switch(aKeyEvent.iCode)
            {
            case EKeyUpArrow:
                if (iIpEditor[iFocusControl]->IsFocused())
                    {
                    iIpEditor[iFocusControl]->SetFocus(EFalse, EDrawNow);
                    iFocusControl--;
                    if (iFocusControl < 0) 
                        iFocusControl=0;
                    iIpEditor[iFocusControl]->SetFocus(ETrue, EDrawNow);
                    }
                break;
            case EKeyDownArrow:
                if (iIpEditor[iFocusControl]->IsFocused())
                    {
                    iIpEditor[iFocusControl]->SetFocus(EFalse, EDrawNow);
                    iFocusControl++;
                    if (iFocusControl >= KNoOfEditors) 
                        iFocusControl=KNoOfEditors-1;
                    iIpEditor[iFocusControl]->SetFocus(ETrue, EDrawNow);
                    }
                break;
            default:
                response = iIpEditor[iFocusControl]->OfferKeyEventL(aKeyEvent, aType);
                break;
            }
        }

    return response;
    }

// ---------------------------------------------------------
// CAknExEditorContainer21::HandleControlEventL(
//     CCoeControl* aControl,TCoeEvent aEventType)
// (other items were commented in a header).
// ---------------------------------------------------------
//
void CAknExEditorContainer21::HandleControlEventL(
    CCoeControl* /*aControl*/,TCoeEvent /*aEventType*/)
    {
    }

void CAknExEditorContainer21::ReadIPAddress()
    {
    TResourceReader reader;
    iCoeEnv->CreateResourceReaderLC(reader, R_AKNEXEDITOR_VIEW21_IPADDRESS);
    iIpEditor[iFocusControl]->SetAddress(iIpEditor[iFocusControl]->ReadIPAddress(reader));
    CleanupStack::PopAndDestroy();
    DrawNow();
    }

// ---------------------------------------------------------
// CAknExEditorContainer21::DisplayIPAddress()
// (other items were commented in a header).
// ---------------------------------------------------------
//
void CAknExEditorContainer21::DisplayIPAddress()
    {
    TBuf <20> buf;
    TInetAddr inetAddr=iIpEditor[iFocusControl]->Address();
    inetAddr.Output(buf);
    CAknNoteDialog* dlg = new (ELeave) CAknNoteDialog(CAknNoteDialog::EConfirmationTone,CAknNoteDialog::EShortTimeout);
    dlg->PrepareLC( R_AKNEXEDITOR_BLANK_NOTE );
    dlg->SetTextL(buf);
    dlg->RunLD();	
    }

// End of File  
