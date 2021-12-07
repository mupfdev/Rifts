/*
* ============================================================================
*  Name     : CAknExEditorContainer6 from CCoeControl, MCoeControlObserver
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
#include "AknExEditorContainer6.h"

// Definitions
#define EDWIN_LABEL_POS     TPoint(60, 10)
#define GTEXTED_LABEL_POS   TPoint(110, 10)
#define CASE_LABEL_POS      TPoint(10, 35)

#define ROW_SIZE            TSize(0, 25)

// Constants
const TInt KBufLength           = 64;

// Enumarations
enum TControls
    {
    EGTextEdPrompt,
    EGTextEd
    };

// ================= MEMBER FUNCTIONS =======================

// C++ default constructor can NOT contain any code, that
// might leave.
//
CAknExEditorContainer6::CAknExEditorContainer6()
    {
    TInt iIndex(0);
    for (iIndex = 0; iIndex < KNumberOfLabels; iIndex++)
        {
        iLabel[iIndex] = NULL;
        }
    for (iIndex = 0; iIndex < KNumberOfTextEditors; iIndex++)
        {
        iEditor[iIndex] = NULL;
        }
    }

// EPOC default constructor can leave.
void CAknExEditorContainer6::ConstructL(const TRect& aRect)
    {
    CreateWindowL();

    // load texts for labels
    CDesCArrayFlat* items = 
            iCoeEnv->ReadDesCArrayResourceL(R_AKNEXEDITOR_VIEW6_LABELS);
    CleanupStack::PushL(items);

    // Creates labels.
    TPoint position;
    TInt iIndex;
    for (iIndex = 0; iIndex < KNumberOfLabels; iIndex++)
        {
        iLabel[iIndex] = new (ELeave) CEikLabel;
        iLabel[iIndex]->SetContainerWindowL(*this);
        iLabel[iIndex]->SetTextL((*items)[iIndex]);
        switch(iIndex)
            {
            case 0: // Label in title (Left)
                position = EDWIN_LABEL_POS;
                break;
            case 1: // Label in title (Right)
                position = GTEXTED_LABEL_POS;
                break;
            case 2: // Label in first row
                position = CASE_LABEL_POS;
                break;
            default: // Other labels
                position = position + ROW_SIZE + ROW_SIZE;
                break;
            }
            iLabel[iIndex]->SetExtent(position, iLabel[iIndex]->MinimumSize());
        }
    CleanupStack::Pop();    // items
    delete items;


    // Create CEikEdwins.
    position = EDWIN_LABEL_POS;
    TResourceReader reader;
    for (iIndex = 0; iIndex < KNumberOfEdwins; iIndex++)
        {
        iCoeEnv->CreateResourceReaderLC(reader, R_AKNEXEDITOR_VIEW6_EDWIN);
        iEditor[iIndex] = new (ELeave) CEikEdwin;
        iEditor[iIndex]->SetContainerWindowL(*this);
        iEditor[iIndex]->ConstructFromResourceL(reader);
        CleanupStack::PopAndDestroy();  // Resource reader
        position = position + ROW_SIZE + ROW_SIZE;
        iEditor[iIndex]->SetExtent(position, iEditor[iIndex]->MinimumSize());
        }

    // Create CEikGlobalTextEditors.
    position = GTEXTED_LABEL_POS;
    for (iIndex = KNumberOfEdwins; iIndex < KNumberOfTextEditors; iIndex++)
        {
        iCoeEnv->CreateResourceReaderLC(reader, R_AKNEXEDITOR_VIEW6_GTEXTED);
        iEditor[iIndex] = new (ELeave) CEikGlobalTextEditor;
        iEditor[iIndex]->SetContainerWindowL(*this);
        iEditor[iIndex]->ConstructFromResourceL(reader);
        CleanupStack::PopAndDestroy();  // Resource reader
        position = position + ROW_SIZE + ROW_SIZE;
        iEditor[iIndex]->SetExtent(position, iEditor[iIndex]->MinimumSize());
        }

    // Not allow to change case
    iEditor[1]->SetAknEditorFlags(EAknEditorFlagFixedCase); // bottom left
    iEditor[3]->SetAknEditorFlags(EAknEditorFlagFixedCase); // bottom right

    // Set focus
    iEditor[0]->SetFocus(ETrue);

    SetRect(aRect);
    ActivateL();
    }

// Destructor
CAknExEditorContainer6::~CAknExEditorContainer6()
    {
    TInt iIndex(0);
    for (iIndex = 0; iIndex < KNumberOfLabels; iIndex++)
        {
        delete iLabel[iIndex];
        iLabel[iIndex] = NULL;
        }
    for (iIndex = 0; iIndex < KNumberOfTextEditors; iIndex++)
        {
        delete iEditor[iIndex];
        iEditor[iIndex] = NULL;
        }
    }


// ---------------------------------------------------------
// CAknExEditorContainer6::SizeChanged()
// Called by framework when the view size is changed
// (other items were commented in a header).
// ---------------------------------------------------------
//
void CAknExEditorContainer6::SizeChanged()
    {
    }

// ---------------------------------------------------------
// CAknExEditorContainer6::CountComponentControls() const
// (other items were commented in a header).
// ---------------------------------------------------------
//
TInt CAknExEditorContainer6::CountComponentControls() const
    {
    return KNumberOfLabels + KNumberOfEdwins + KNumberOfGTextEds;
    }

// ---------------------------------------------------------
// CAknExEditorContainer6::ComponentControl(TInt aIndex) const
// (other items were commented in a header).
// ---------------------------------------------------------
//
CCoeControl* CAknExEditorContainer6::ComponentControl(TInt aIndex) const
    {
    if (aIndex < KNumberOfTextEditors)
        {
        return iEditor[aIndex];
        }
    else if (aIndex < KNumberOfTextEditors + KNumberOfLabels)
        {
        return iLabel[aIndex - KNumberOfTextEditors];
        }
    else
        {
        return NULL;
        }
    }

// ---------------------------------------------------------
// CAknExEditorContainer6::Draw(const TRect& aRect) const
// (other items were commented in a header).
// ---------------------------------------------------------
//
void CAknExEditorContainer6::Draw(const TRect& aRect) const
    {
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle(CGraphicsContext::ENullPen);
    gc.SetBrushColor(KRgbGray);
    gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
    gc.DrawRect(aRect);
    }

// ---------------------------------------------------------
// CAknExEditorContainer6::OfferKeyEventL(...)
// Move focus with up/down key.
// (other items were commented in a header).
// ---------------------------------------------------------
//
TKeyResponse CAknExEditorContainer6::OfferKeyEventL(
    const TKeyEvent& aKeyEvent, TEventCode aType)
    {

    TInt iIndex(0);
    // Find focused control
    for (iIndex = 0; iIndex < KNumberOfTextEditors; iIndex++)
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
                    iIndex = KNumberOfTextEditors;
                    }
                iEditor[iIndex - 1]->SetFocus(ETrue);
                return EKeyWasConsumed;
                }
            // Move focus to next contorl.
            else if ((aType == EEventKey) && (aKeyEvent.iCode == EKeyDownArrow))
                {
                iEditor[iIndex]->SetFocus(EFalse);
                if (iIndex == KNumberOfTextEditors - 1)
                    {
                    iIndex = -1;    // if last control, move focus to first.
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

        // if no control has control, return EKeyWasNotConsumed.
        return EKeyWasNotConsumed;
    }



// ---------------------------------------------------------
// CAknExEditorContainer6::HandleControlEventL(
//     CCoeControl* aControl,TCoeEvent aEventType)
// (other items were commented in a header).
// ---------------------------------------------------------
//
void CAknExEditorContainer6::HandleControlEventL(
    CCoeControl* /*aControl*/,TCoeEvent /*aEventType*/)
    {
    }


// End of File  
