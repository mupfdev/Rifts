/*
* ============================================================================
*  Name     : CAknExEditorContainer7 from CCoeControl, MCoeControlObserver
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
#include "AknExEditorcontainer7.h"

// Definitions
#define LABEL_POS   TPoint(10, 10)
#define ROW_SIZE    TSize(0, 20)

// Constants
const TInt KBufLength           = 64;

// ================= MEMBER FUNCTIONS =======================

// C++ default constructor can NOT contain any code, that
// might leave.
//
CAknExEditorContainer7::CAknExEditorContainer7()
    {
    TInt iIndex(0);
    for (iIndex = 0; iIndex < KNumberOfLabels; iIndex++)
        {
        iLabel[iIndex] = NULL;
        }
    for (iIndex = 0; iIndex < KNumberOfGTextEds; iIndex++)
        {
        iEditor[iIndex] = NULL;
        }
    }

// EPOC default constructor can leave.
void CAknExEditorContainer7::ConstructL(const TRect& aRect)
    {
    CreateWindowL();

    // load texts for labels
    CDesCArrayFlat* items = 
            iCoeEnv->ReadDesCArrayResourceL(R_AKNEXEDITOR_VIEW7_LABELS);
    CleanupStack::PushL(items);

    // Creates labels.
    TPoint position = LABEL_POS;
    TInt iIndex(0);
    for (iIndex = 0; iIndex < KNumberOfLabels; iIndex++)
        {
        iLabel[iIndex] = new (ELeave) CEikLabel;
        iLabel[iIndex]->SetContainerWindowL(*this);
        iLabel[iIndex]->SetTextL((*items)[iIndex]);
        iLabel[iIndex]->SetExtent(position, iLabel[iIndex]->MinimumSize());
        position = position + ROW_SIZE + ROW_SIZE;
        }

    CleanupStack::Pop();    // items
    delete items;

    // Create CEikGlobalTextEditors.
    position = LABEL_POS + ROW_SIZE;
    TResourceReader reader;
    for (iIndex = 0; iIndex < KNumberOfGTextEds; iIndex++)
        {
        iCoeEnv->CreateResourceReaderLC(reader, R_AKNEXEDITOR_VIEW7_GTEXTED);
        iEditor[iIndex] = new (ELeave) CEikGlobalTextEditor;
        iEditor[iIndex]->SetContainerWindowL(*this);
        iEditor[iIndex]->ConstructFromResourceL(reader);
        CleanupStack::PopAndDestroy();  // Resource reader

        iEditor[iIndex]->SetTextL(iLabel[iIndex]->Text());
        iEditor[iIndex]->SetExtent(position, iEditor[iIndex]->MinimumSize());
        position = position + ROW_SIZE + ROW_SIZE;
        }

    // Set alignment to control.
    CParaFormat     paraFormat;
    TParaFormatMask paraFormatMask;

    paraFormatMask.SetAttrib(EAttAlignment);    // set mask

    paraFormat.iHorizontalAlignment = CParaFormat::ELeftAlign;
    iEditor[0]->ApplyParaFormatL(&paraFormat, paraFormatMask);

    paraFormat.iHorizontalAlignment = CParaFormat::ECenterAlign;
    iEditor[1]->ApplyParaFormatL(&paraFormat, paraFormatMask);

    paraFormat.iHorizontalAlignment = CParaFormat::ERightAlign;
    iEditor[2]->ApplyParaFormatL(&paraFormat, paraFormatMask);


    // Set focus
    iEditor[0]->SetFocus(ETrue);

    SetRect(aRect);

    ActivateL();

    }

// Destructor
CAknExEditorContainer7::~CAknExEditorContainer7()
    {
    TInt iIndex(0);
    for (iIndex = 0; iIndex < KNumberOfLabels; iIndex++)
        {
        delete iLabel[iIndex];
        iLabel[iIndex] = NULL;
        }
    for (iIndex = 0; iIndex < KNumberOfGTextEds; iIndex++)
        {
        delete iEditor[iIndex];
        iEditor[iIndex] = NULL;
        }
    }


// ---------------------------------------------------------
// CAknExEditorContainer7::SizeChanged()
// Called by framework when the view size is changed
// (other items were commented in a header).
// ---------------------------------------------------------
//
void CAknExEditorContainer7::SizeChanged()
    {
    }

// ---------------------------------------------------------
// CAknExEditorContainer7::CountComponentControls() const
// (other items were commented in a header).
// ---------------------------------------------------------
//
TInt CAknExEditorContainer7::CountComponentControls() const
    {
    return KNumberOfLabels + KNumberOfGTextEds;
    }

// ---------------------------------------------------------
// CAknExEditorContainer7::ComponentControl(TInt aIndex) const
// (other items were commented in a header).
// ---------------------------------------------------------
//
CCoeControl* CAknExEditorContainer7::ComponentControl(TInt aIndex) const
    {
    if (aIndex < KNumberOfGTextEds)
        {
        return iEditor[aIndex];
        }
    else if (aIndex < KNumberOfGTextEds + KNumberOfLabels)
        {
        return iLabel[aIndex - KNumberOfGTextEds];
        }
    else
        {
        return NULL;
        }
    }

// ---------------------------------------------------------
// CAknExEditorContainer7::Draw(const TRect& aRect) const
// (other items were commented in a header).
// ---------------------------------------------------------
//
void CAknExEditorContainer7::Draw(const TRect& aRect) const
    {
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle(CGraphicsContext::ENullPen);
    gc.SetBrushColor(KRgbGray);
    gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
    gc.DrawRect(aRect);
    }

// ---------------------------------------------------------
// CAknExEditorContainer7::OfferKeyEventL(...)
// Move focus with up/down key.
// (other items were commented in a header).
// ---------------------------------------------------------
//
TKeyResponse CAknExEditorContainer7::OfferKeyEventL(
    const TKeyEvent& aKeyEvent, TEventCode aType)
    {

    TInt iIndex(0);
    // Find focused control
    for (iIndex = 0; iIndex < KNumberOfGTextEds; iIndex++)
        {
        // found
        if (iEditor[iIndex]->IsFocused())
            {
            // Move focus to previous contorl.
            if ((aType == EEventKey) && (aKeyEvent.iCode == EKeyUpArrow))
                {
                iEditor[iIndex]->SetFocus(EFalse);
                if (iIndex == 0)    // if first control, move focus to last.
                    {
                    iIndex = KNumberOfGTextEds;
                    }
                iEditor[iIndex - 1]->SetFocus(ETrue);
                return EKeyWasConsumed;
                }
            // Move focus to next contorl.
            else if ((aType == EEventKey) && (aKeyEvent.iCode == EKeyDownArrow))
                {
                iEditor[iIndex]->SetFocus(EFalse);
                if (iIndex == KNumberOfGTextEds - 1)
                    {
                    iIndex = -1;    // if last control, move focus to first.
                                    // Index of first control is 0 and
                                    // iIndex is INCLIMENTED after this line, 
                                    // iIndex must be -1
                    }
                iEditor[iIndex + 1]->SetFocus(ETrue);
                return EKeyWasConsumed;
                }

            // default action.
            else
                {
                return iEditor[iIndex]->OfferKeyEventL(aKeyEvent, aType);
                }
            }
        // if the control does not have focus, check next control.
        }

        // if no control has focus, return EKeyWasNotConsumed.
        return EKeyWasNotConsumed;
    }



// ---------------------------------------------------------
// CAknExEditorContainer7::HandleControlEventL(
//     CCoeControl* aControl,TCoeEvent aEventType)
// (other items were commented in a header).
// ---------------------------------------------------------
//
void CAknExEditorContainer7::HandleControlEventL(
    CCoeControl* /*aControl*/,TCoeEvent /*aEventType*/)
    {
    }


// End of File  
