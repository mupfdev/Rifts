/*
* ============================================================================
*  Name     : CAknExEditorContainer30 from CCoeControl, MCoeControlObserver
*  Part of  : AknExEditor
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES


#include <barsread.h>  // for resource reader
#include <eikedwin.h>  // for CEikEdwin

#include <AknExEditor.rsg>
#include "aknexeditor.hrh"
#include "AknExEditorContainer30.h"
#include <eikenv.h>

#include <gulbordr.h>


// Definitions

#define EDWIN1_POS   TPoint(10,25)
#define EDWIN2_POS   TPoint(10,55)
#define EDWIN3_POS   TPoint(10,95)

#define KDefaultWidth 10
#define KDefaultTextLimit 20
#define KDefaultNumberOfLines 1

// Constants

const TInt KNumberOfControls    = 3;

// Enumarations

enum TControls
    {
    EView30Edwin1,
    EView30Edwin2,
    EView30Edwin3
    };


// ================= MEMBER FUNCTIONS =======================

// C++ default constructor can NOT contain any code, that
// might leave.
//
CAknExEditorContainer30::CAknExEditorContainer30()
    {
    }

// EPOC default constructor can leave.

void CAknExEditorContainer30::ConstructL(const TRect& aRect)
    {
    CreateWindowL();

    // Creates controls

//    iEdwin1 = new (ELeave) CEikEdwin;
    iEdwin1 = new (ELeave) CEikEdwin(TGulBorder::ESingleGray);
    iEdwin1->ConstructL(EEikEdwinAutoSelection,KDefaultWidth,KDefaultTextLimit,KDefaultNumberOfLines);
    iEdwin1->SetContainerWindowL(*this);
    TBuf<10> buf1;
    iCoeEnv->ReadResource(buf1, R_AKNEXEDITOR_VIEW30_INPUT);
    iEdwin1->SetTextL(&buf1);
    iEdwin1->SetExtent(EDWIN1_POS, iEdwin1->MinimumSize());
    
    // Enable cut copy support
    iEdwin1->EnableCcpuSupportL(ETrue); 
    iEdwin1->SupportsUndo();
    iEdwin1->SetFocus(ETrue); 

    iEdwin2 = new (ELeave) CEikEdwin;
    iEdwin2->ConstructL(EEikEdwinAutoSelection,KDefaultWidth,KDefaultTextLimit,KDefaultNumberOfLines);
    iEdwin2->SetContainerWindowL(*this);
    TBuf<20> buf2;
    iEdwin1->GetText(buf2); // API Test 
    iEdwin2->SetTextL(&buf2); 
    iEdwin2->SetExtent(EDWIN2_POS, iEdwin2->MinimumSize());

    // Enable cut copy support
    iEdwin2->EnableCcpuSupportL(ETrue);
    

    iEdwin3 = new (ELeave) CEikEdwin;
    iEdwin3->ConstructL(EEikEdwinAutoSelection,KDefaultWidth,KDefaultTextLimit,KDefaultNumberOfLines);
    iEdwin3->SetContainerWindowL(*this);
    HBufC* hbuf = iEdwin1->GetTextInHBufL(); // API Test
    iEdwin3->SetTextL(hbuf);
    iEdwin3->SetExtent(EDWIN3_POS, iEdwin3->MinimumSize());
    
    // Diasble cut copy support
    iEdwin3->EnableCcpuSupportL(EFalse);
    delete hbuf;
    
    SetRect(aRect);
    ActivateL();
    }

// Destructor
CAknExEditorContainer30::~CAknExEditorContainer30()
    {
    delete iEdwin1;
    delete iEdwin2;
    delete iEdwin3;
    }

// ---------------------------------------------------------
// CAknExEditorContainer30::SizeChanged()
// Called by framework when the view size is changed
// (other items were commented in a header).
// ---------------------------------------------------------
//
void CAknExEditorContainer30::SizeChanged()
    {
    }

// ---------------------------------------------------------
// CAknExEditorContainer30::CountComponentControls() const
// (other items were commented in a header).
// ---------------------------------------------------------
//
TInt CAknExEditorContainer30::CountComponentControls() const
    {
    return KNumberOfControls;
    }

//---------------------------------------------------------
// CAknExEditorContainer30::TestSelectedCase(TInt aCommand)
//---------------------------------------------------------
//
void CAknExEditorContainer30::TestSelectedCase(TInt aCommand)
{
    
    CEikEdwin* edwinptr = NULL;
    TBool focus[] = {iEdwin1->IsFocused(),iEdwin2->CcpuIsFocused(),iEdwin3->IsFocused()};

    if(focus[0])
        edwinptr = iEdwin1;
    else if(focus[1])
        edwinptr = iEdwin2;
    else if(focus[2])
        edwinptr = iEdwin3;



    if (aCommand == EAknExEditorSelectText)
    {
        if(edwinptr->TextLength())
            edwinptr->SelectAllL();
    }

    else if(aCommand == EAknExEditorClearSelection)
    {
        if (edwinptr->SelectionLength())
                edwinptr->ClearSelectionL();
    }

    else if(aCommand == EAknExEditorCut)
    {
        if(edwinptr->CcpuCanCut())
            edwinptr->CcpuCutL();
    }

    else if(aCommand == EAknExEditorCopy)
    {
        if(edwinptr->CcpuCanCopy() && edwinptr->TextLength())
            edwinptr->CcpuCopyL();
    }

    else if(aCommand == EAknExEditorPaste)
    {
        if(edwinptr->CcpuCanPaste())
                edwinptr->CcpuPasteL();
    }

    else if(aCommand == EAknExEditorUndo)
    {
        if(edwinptr->CcpuCanUndo())
                edwinptr->CcpuUndoL();
    }
    
} 

// ---------------------------------------------------------
// CAknExEditorContainer30::ComponentControl(TInt aIndex) const
// (other items were commented in a header).
// ---------------------------------------------------------
//

CCoeControl* CAknExEditorContainer30::ComponentControl(TInt aIndex) const
    {
    switch(aIndex)
        {
    case EView30Edwin1:
         return iEdwin1;

    case EView30Edwin2:
         return iEdwin2;

    case EView30Edwin3:
         return iEdwin3;

    default:
         return NULL;
        }
    }

// ---------------------------------------------------------
// CAknExEditorContainer30::Draw(const TRect& aRect) const
// (other items were commented in a header).
// ---------------------------------------------------------
//
void CAknExEditorContainer30::Draw(const TRect& aRect) const
    {
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle(CGraphicsContext::ENullPen);
    gc.SetBrushColor(KRgbGray);
    gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
    gc.DrawRect(aRect);

    TBuf <40> buf; 
    gc.UseFont(iEikonEnv->AnnotationFont());
    iCoeEnv->ReadResource(buf, R_AKNEXEDITOR_VIEW30_ENABLED);
    gc.DrawText(buf,TPoint(10,20));
    iCoeEnv->ReadResource(buf, R_AKNEXEDITOR_VIEW30_DISABLED);
    gc.DrawText(buf,TPoint(10,90));
    }


// ---------------------------------------------------------
// CAknExEditorContainer30::OfferKeyEventL(...)
// Move focus with up/down key.
// (other items were commented in a header).
// ---------------------------------------------------------
//

TKeyResponse CAknExEditorContainer30::OfferKeyEventL(
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
            if ((aType == EEventKey) && (aKeyEvent.iCode == EKeyUpArrow) ||
                (aType == EEventKey) && (aKeyEvent.iCode == EKeyDownArrow))
                {
                iEdwin2->SetFocus(EFalse);
                if(aKeyEvent.iCode == EKeyUpArrow) iEdwin1->SetFocus(ETrue);
                if(aKeyEvent.iCode == EKeyDownArrow)iEdwin3->SetFocus(ETrue);
                return EKeyWasConsumed;
                }
            return iEdwin2->OfferKeyEventL(aKeyEvent, aType);
            }
        }
    if (iEdwin3)
        {
        if (iEdwin3->IsFocused())
            {
            if((aType == EEventKey) && (aKeyEvent.iCode == EKeyUpArrow))
                {
                iEdwin3->SetFocus(EFalse);
                iEdwin2->SetFocus(ETrue);
                return EKeyWasConsumed;
                }
            return iEdwin3->OfferKeyEventL(aKeyEvent, aType);
            }
        }

    return EKeyWasNotConsumed;
    }

   


// ---------------------------------------------------------
// CAknExEditorContainer30::HandleControlEventL(
//     CCoeControl* aControl,TCoeEvent aEventType)
// (other items were commented in a header).
// ---------------------------------------------------------
//
void CAknExEditorContainer30::HandleControlEventL(
    CCoeControl* /*aControl*/,TCoeEvent /*aEventType*/)
    {
    }

// End of File  
