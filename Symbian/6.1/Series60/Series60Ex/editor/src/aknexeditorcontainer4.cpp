/*
* ============================================================================
*  Name     : CAknExEditorContainer4 from CCoeControl, MCoeControlObserver
*  Part of  : AknExEditor
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include <eiklabel.h>  // for example label control
#include <barsread.h>  // for resource reader
#include <eikedwin.h>  // for CEikEdwin
#include <eikgted.h>   // for CEikGlobalTextEditor
#include <aknutils.h>  // for Fonts.

#include <AknExEditor.rsg>
#include "aknexeditor.hrh"
#include "AknExEditorContainer4.h"

// Definitions
#define GTEXTED_LABEL_POS   TPoint(10, 10)
#define GTEXTED_POS         TPoint(10, 25)


// Constants
const TInt KNumberOfControls    = 2;
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
CAknExEditorContainer4::CAknExEditorContainer4()
                        :iLabel(NULL), iGTextEd(NULL)
    {
    }

// EPOC default constructor can leave.
void CAknExEditorContainer4::ConstructL(const TRect& aRect)
    {
    CreateWindowL();

    TBuf<KBufLength> text;

    iCoeEnv->ReadResource(text, R_AKNEXEDITOR_VIEW4_LABEL1);
    iLabel = new (ELeave) CEikLabel;
    iLabel->SetContainerWindowL(*this);
    iLabel->SetTextL(text);
    iLabel->SetExtent(GTEXTED_LABEL_POS, iLabel->MinimumSize());

    TResourceReader reader;
    iCoeEnv->CreateResourceReaderLC(reader, R_AKNEXEDITOR_VIEW4_GTEXTED);
    iGTextEd = new (ELeave) CEikGlobalTextEditor;
    iGTextEd->SetContainerWindowL(*this);
    iGTextEd->ConstructFromResourceL(reader);
    CleanupStack::PopAndDestroy();  // Resource reader

    iGTextEd->SetExtent(GTEXTED_POS, iGTextEd->MinimumSize());
    iGTextEd->SetAvkonWrap(ETrue);
    iGTextEd->SetFocus(ETrue);

    SetRect(aRect);
    ActivateL();
    }

// Destructor
CAknExEditorContainer4::~CAknExEditorContainer4()
    {
    delete iLabel;
    delete iGTextEd;
    }

// ---------------------------------------------------------
// void CAknExEditorContainer4::SetSystemFontL(TInt aFontEnum)
// Change font style of CEikGlobalTextEditor using system font.
// (other items were commented in a header).
// ---------------------------------------------------------
//
void CAknExEditorContainer4::SetSystemFontL(TInt aFontEnum)
    {
    const CFont* editorFont;


    switch (aFontEnum)
        {
        case ELatinPlain12:
            editorFont = LatinPlain12();
            break;
        case ELatinBold12:
            editorFont = LatinBold12();
            break;
        case ELatinBold13:
            editorFont = LatinBold13();
            break;
        case ELatinBold17:
            editorFont = LatinBold17();
            break;
        case ELatinBold19:
            editorFont = LatinBold19();
            break;
        case ENumberPlain5:
            editorFont = NumberPlain5();
            break;
        case EClockBold30:
            editorFont = ClockBold30();
            break;
        case ELatinClock14:
            editorFont = LatinClock14();
            break;
        default:
            return;
        }

    TCharFormat     charFormat;
    TCharFormatMask charFormatMask;

    charFormat.iFontSpec = editorFont->FontSpecInTwips();
    charFormatMask.SetAll();

    // Set font to GlobalTextEditor
    iGTextEd->ApplyCharFormatL(charFormat, charFormatMask);

    // Change label text.
    TBuf<KBufLength> sizeText;
    TBuf<KBufLength> formatText;
    iCoeEnv->ReadResource(formatText, R_AKNEXEDITOR_CONTAINER4_LABEL_FORMAT_PT);
    sizeText.Format(formatText,
                     charFormat.iFontSpec.iHeight / KTwipsPerPoint);
    TBuf<KBufLength> labelText = charFormat.iFontSpec.iTypeface.iName;
    labelText.Append(sizeText);
    iLabel->SetTextL(labelText);
    iLabel->SetExtent(GTEXTED_LABEL_POS, iLabel->MinimumSize());
    }


// ---------------------------------------------------------
// void CAknExEditorContainer4::SetFontL(TInt aResourceID)
// Change font style of CEikGlobalTextEditor.
// (other items were commented in a header).
// ---------------------------------------------------------
//
void CAknExEditorContainer4::SetFontL(TInt aResourceID)
    {
    // Create font
    TFontSpec* fontSpec = CreateFontSpecFromResourceL(aResourceID);
    CleanupStack::PushL(fontSpec);

    TCharFormat     charFormat;
    TCharFormatMask charFormatMask;
    CFont*  editorFont = iCoeEnv->CreateScreenFontL(*fontSpec);
    CleanupStack::PushL(editorFont);

    charFormat.iFontSpec = editorFont->FontSpecInTwips();
    charFormatMask.SetAll();

    // Set font to GlobalTextEditor
    iGTextEd->ApplyCharFormatL(charFormat, charFormatMask);

    iCoeEnv->ReleaseScreenFont(editorFont); // Release editorFont
    CleanupStack::Pop();                    // editorFont

    // Change label text.
    TBuf<KBufLength> sizeText;
    TBuf<KBufLength> formatText;
    iCoeEnv->ReadResource(formatText, R_AKNEXEDITOR_CONTAINER4_LABEL_FORMAT_PT);
    sizeText.Format(formatText,fontSpec->iHeight / KTwipsPerPoint);
    TBuf<KBufLength> labelText = fontSpec->iTypeface.iName;
    labelText.Append(sizeText);
    iLabel->SetTextL(labelText);
    iLabel->SetExtent(GTEXTED_LABEL_POS, iLabel->MinimumSize());


    CleanupStack::Pop();  // fontSpec


    delete fontSpec;    // Delete Font
    }

// ---------------------------------------------------------
// CAknExEditorContainer4::CreateFontSpecFromResourceL(TInt aResourceId
// Create fontSpec object
// (other items were commented in a header).
// ---------------------------------------------------------
//
TFontSpec* CAknExEditorContainer4::CreateFontSpecFromResourceL(TInt aResourceId)
    {
    TResourceReader reader;
    iCoeEnv->CreateResourceReaderLC(reader, aResourceId);

    HBufC*   fontName;
    TInt    fontSize;

    fontName = reader.ReadHBufCL();
    fontSize = reader.ReadInt16();

    CleanupStack::PopAndDestroy();  // for reader

    CleanupStack::PushL(fontName);

    TFontSpec* fontSpec = new TFontSpec(*fontName, fontSize);
    CleanupStack::PopAndDestroy();  // for fontName
    return fontSpec;
    }

// ---------------------------------------------------------
// CAknExEditorContainer4::SizeChanged()
// Called by framework when the view size is changed
// (other items were commented in a header).
// ---------------------------------------------------------
//
void CAknExEditorContainer4::SizeChanged()
    {
    }

// ---------------------------------------------------------
// CAknExEditorContainer4::CountComponentControls() const
// (other items were commented in a header).
// ---------------------------------------------------------
//
TInt CAknExEditorContainer4::CountComponentControls() const
    {
    return KNumberOfControls; // return nbr of controls inside this container
    }

// ---------------------------------------------------------
// CAknExEditorContainer4::ComponentControl(TInt aIndex) const
// (other items were commented in a header).
// ---------------------------------------------------------
//
CCoeControl* CAknExEditorContainer4::ComponentControl(TInt aIndex) const
    {
    switch (aIndex)
        {
        case EGTextEdPrompt:
            return iLabel;
        case EGTextEd:
            return iGTextEd;
        default:
            return NULL;
        }
    }

// ---------------------------------------------------------
// CAknExEditorContainer4::Draw(const TRect& aRect) const
// (other items were commented in a header).
// ---------------------------------------------------------
//
void CAknExEditorContainer4::Draw(const TRect& aRect) const
    {
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle(CGraphicsContext::ENullPen);
    gc.SetBrushColor(KRgbGray);
    gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
    gc.DrawRect(aRect);
    }

// ---------------------------------------------------------
// CAknExEditorContainer4::OfferKeyEventL(...)
// Notify key events to the editor.
// (other items were commented in a header).
// ---------------------------------------------------------
//
TKeyResponse CAknExEditorContainer4::OfferKeyEventL(
    const TKeyEvent& aKeyEvent, TEventCode aType)
    {
    return iGTextEd->OfferKeyEventL(aKeyEvent, aType);
    }


// ---------------------------------------------------------
// CAknExEditorContainer4::HandleControlEventL(
//     CCoeControl* aControl,TCoeEvent aEventType)
// (other items were commented in a header).
// ---------------------------------------------------------
//
void CAknExEditorContainer4::HandleControlEventL(
    CCoeControl* /*aControl*/,TCoeEvent /*aEventType*/)
    {
    }


// End of File  
