/* Copyright (c) 2001, Nokia. All rights reserved */

#include <eiklabel.h>
#include <eikrted.h>
#include <barsread.h>  // for resource reader
#include <sockets.rsg>
#include <aknglobalnote.h>

#include "SocketsAppView.h"
#include "Sockets.pan"

// Standard Epoc construction sequence
CSocketsAppView* CSocketsAppView::NewL(const TRect& aRect)
    {
    CSocketsAppView* self = CSocketsAppView::NewLC(aRect);
    CleanupStack::Pop(self);
    return self;
    }

CSocketsAppView* CSocketsAppView::NewLC(const TRect& aRect)
    {
    CSocketsAppView* self = new (ELeave) CSocketsAppView;
    CleanupStack::PushL(self);
    self->ConstructL(aRect);
    return self;
    }

void CSocketsAppView::ConstructL(const TRect& aRect)
    {
    // Definitions
    const TPoint KLabelPosition  = TPoint(10, 10);
    const TSize  KLabelSize      = TSize(150, 20);
    const TPoint KOutputPosition = TPoint(10, 35);
    const TSize  KOutputSize     = TSize(150, 100);

    CreateWindowL();

    iStatusWindow = new (ELeave) CEikLabel;
    iStatusWindow->SetContainerWindowL(*this);
    iStatusWindow->SetTextL(_L("Uninitialised"));
    iStatusWindow->SetExtent(KLabelPosition, KLabelSize);

    TResourceReader reader;
    iCoeEnv->CreateResourceReaderLC(reader, R_OUTPUT_VIEW_RTEXTED);
	iOutputWindow = new (ELeave) CEikRichTextEditor();

    iOutputWindow->SetContainerWindowL(*this);
    iOutputWindow->ConstructFromResourceL(reader);
    CleanupStack::PopAndDestroy();  // Resource reader
    iOutputWindow->SetFocus(ETrue);

	iOutputWindow->SetExtent(KOutputPosition, KOutputSize); 

    SetRect(aRect);
    ActivateL();
  
    }

CSocketsAppView::CSocketsAppView()
    {
    }


CSocketsAppView::~CSocketsAppView()
    {
    delete iOutputWindow;
    iOutputWindow = NULL;

    delete iStatusWindow;
    iStatusWindow = NULL;
    }


void CSocketsAppView::ClearTextL()
    {
    iOutputWindow->Text()->Reset();
    iOutputWindow->HandleTextChangedL();
    iOutputWindow->SetCursorPosL(0, EFalse);
    iFontStyle = 0;
    }

// Draw this application's view to the screen
void CSocketsAppView::Draw(const TRect& aRect) const
    {
    // Clear the screen
    CWindowGc& gc = SystemGc();
    gc.Clear(aRect);
    }

TInt CSocketsAppView::CountComponentControls() const
    {
    return 2; 
    }

CCoeControl* CSocketsAppView::ComponentControl(TInt aIndex) const
    {

    switch(aIndex)
        {
            case 0:
                return iStatusWindow;
            case 1:
                return iOutputWindow;
 
            default:
                User::Panic (KPanicSockets, ESocketsAppView);
                return 0;
        }
    }



void CSocketsAppView::KeyEventL(TInt aCode)
    {
    // Add this 'keypress' to the main output window
    TKeyEvent event;
    event.iCode = aCode;
    event.iScanCode = aCode;
    iOutputWindow->SetFocus(ETrue);
    iOutputWindow->OfferKeyEventL(event, EEventKey);
    }


 
void CSocketsAppView::PrintNotify(const TDesC& aDes, TUint aFontStyle)
    {
    // Display these characters in the main output window, in the specified style
    SetFontStyle(aFontStyle);

    for (TInt i = 0; i < aDes.Length(); i++)
        {
        TRAPD(error, KeyEventL(aDes[i]));
        if(error != KErrNone)
            {
            User::Panic (KPanicSockets, ESocketsAppView);
            }
        }   
    }

void CSocketsAppView::PrintNotify(const TDesC8& aDes, TUint aFontStyle)
    {
    // Display these characters in the main output window, in the specified style
    SetFontStyle(aFontStyle);

    for (TInt i = 0; i < aDes.Length(); i++)
        {
        TRAPD(error, KeyEventL(aDes[i]));
        if(error != KErrNone)
            {
            User::Panic (KPanicSockets, ESocketsAppView);
            }
        }
    }

void CSocketsAppView::SetFontStyle(TUint aFontStyle)
    {
    // Set current main window style to match that requested
    UpdateFontAttribute(aFontStyle, CEikGlobalTextEditor::EBold);
    UpdateFontAttribute(aFontStyle, CEikGlobalTextEditor::EItalic);
    UpdateFontAttribute(aFontStyle, CEikGlobalTextEditor::EUnderline);
    }

void CSocketsAppView::UpdateFontAttribute(TUint aFontStyle, TInt aAttribute)
    {
    // Ensure an individual attribute is on or off as requested
    if ((aFontStyle & aAttribute) != (iFontStyle & aAttribute))
        {
        // Note: This function 'toggles' styles based on the bits set in supplied mask
        //       i.e. supplying the same bit twice toggles that style on then off again
        TRAPD(error, iOutputWindow->BoldItalicUnderlineEventL(aAttribute));
        if(error != KErrNone)
            {
            User::Panic (KPanicSockets, ESocketsAppView);
            }
        iFontStyle ^= aAttribute;
        }
    }

void CSocketsAppView::ErrorNotify(const TDesC& aErrMessage, TInt aErrCode)
    {
    _LIT(KNewLine, "\n");

    TRAPD(error,

    HBufC* errorTitleCode = HBufC::NewLC(50);
	errorTitleCode->Des().Append(aErrMessage);
    errorTitleCode->Des().Append(KNewLine);
	errorTitleCode->Des().AppendNum(aErrCode);

    CAknGlobalNote* globalNote = CAknGlobalNote::NewLC();
    globalNote->ShowNoteL(EAknGlobalErrorNote, *errorTitleCode); 
    CleanupStack::PopAndDestroy(globalNote);
    CleanupStack::PopAndDestroy(errorTitleCode);
    )

    if(error != KErrNone)
        {
        User::Panic (KPanicSockets, ESocketsAppView);
        }
    }

void CSocketsAppView::SetStatus(const TDesC& aStatus)
    {
    // Update contents of status window
    TRAPD(error, iStatusWindow->SetTextL(aStatus));
    if(error != KErrNone)
        {
        User::Panic (KPanicSockets, ESocketsAppView);
        }

    iStatusWindow->DrawDeferred();
    }

