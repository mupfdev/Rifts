/*
* ============================================================================
*  Name     : CAknExScrollerContainer4 from CCoeControl, MCoeControlObserver
*  Part of  : AknExScroller
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include <coemain.h>   // CoeEnv
#include <eiklabel.h>  // for label control
#include <barsread.h>  // for resource reader
#include <eikedwin.h>  // for CEikEdwin

#include <aknenv.h>
#include <AknExScroller.rsg>
#include "AknExScrollerContainer4.h"
#include "AknExScrollerView4.h"  // for Form


// CONSTANTS
#define KAknExScrollerGray TRgb(0xaaaaaa)

#define VIEW4_LABEL_POINT   TPoint( 10, 10 )
#define VIEW4_DOLABEL_POINT TPoint( 10, 100 )
#define VIEW4_EDWIN_POS     TPoint( 10, 25 )
#define VIEW4_EDWIN_SIZE    TSize( 160, 64 )

const TInt KNumberOfComponent = 3;
const TInt KBufferLength = 256;

const TInt KTempBufferLength = 64;

// Enumeration
enum TPointerToComponetView4
    {
    ELabel = 0,
    EDoLabel,
    EEditor
    };


// ================= MEMBER FUNCTIONS =======================
// C++ default constructor can NOT contain any code, that
// might leave.
//
CAknExScrollerContainer4::CAknExScrollerContainer4()
                       : iLabel( NULL ), iDoLabel( NULL ), iEdwin( NULL ), iItems(NULL)
    {
    }


// ---------------------------------------------------------
// CAknExScrollerContainer4::ConstructL( const TRect& aRect )
// EPOC two phased constructor
// ---------------------------------------------------------
//
void CAknExScrollerContainer4::ConstructL( const TRect& aRect )
    {
    CreateWindowL();

    // Make listitems. and PUSH it
    iItems = iCoeEnv->ReadDesCArrayResourceL(R_AKNEXSCROLLER_VIEW4_ITEMS);

    TBuf<KBufferLength> label;
    TBuf<KBufferLength> dolabel;

    iLabel = new ( ELeave ) CEikLabel;
    iLabel->SetContainerWindowL( *this );
    iCoeEnv->ReadResource( label, R_AKNEXSCROLLER_LABEL_VIEW4 );
    iLabel->SetTextL( label );

    iDoLabel = new ( ELeave ) CEikLabel;
    iDoLabel->SetContainerWindowL( *this );
    iCoeEnv->ReadResource( dolabel, R_AKNEXSCROLLER_DOLABEL_VIEW4 );
    iDoLabel->SetTextL( dolabel );

    TResourceReader reader;
    iCoeEnv->CreateResourceReaderLC(reader, R_AKNEXSCROLLER_VIEW4_EDITOR);
    iEdwin = new (ELeave) CEikEdwin;
    iEdwin->SetAknEditorFlags(EAknEditorFlagEnableScrollBars);
    iEdwin->SetContainerWindowL(*this);
    iEdwin->ConstructFromResourceL(reader);
    CleanupStack::PopAndDestroy();  // Resource reader
    iEdwin->SetObserver(this);
    iEdwin->SetBorder(TGulBorder::ESingleBlack);
    iEdwin->SetExtent( VIEW4_EDWIN_POS, VIEW4_EDWIN_SIZE );

    iEdwin->SetFocus(ETrue);

    SetRect( aRect );

    ActivateL();
    }


// Destructor
CAknExScrollerContainer4::~CAknExScrollerContainer4()
    {
    delete iLabel;
    delete iDoLabel;
    delete iEdwin;
    delete iItems;

    iLabel = NULL;
    iDoLabel = NULL;
    iEdwin = NULL;
    }

// ---------------------------------------------------------
// CAknExScrollerContainer4::SizeChanged()
// Called by framework when the view size is changed
// ---------------------------------------------------------
//
void CAknExScrollerContainer4::SizeChanged()
    {
    // TODO: Add here control resize code etc.
    iLabel->SetExtent( VIEW4_LABEL_POINT, iLabel->MinimumSize() );
    iDoLabel->SetExtent( VIEW4_DOLABEL_POINT, iDoLabel->MinimumSize() );
    iEdwin->SetExtent( VIEW4_EDWIN_POS, VIEW4_EDWIN_SIZE );
    }

// ---------------------------------------------------------
// CAknExScrollerContainer4::CountComponentControls() const
// Returns number of component.
// ---------------------------------------------------------
//
TInt CAknExScrollerContainer4::CountComponentControls() const
    {
    return KNumberOfComponent; // return nbr of controls inside this container
    }

// ---------------------------------------------------------
// CAknExScrollerContainer4::ComponentControl( TInt aIndex ) const
// Returns pointer to particular component.
// ---------------------------------------------------------
//
CCoeControl* CAknExScrollerContainer4::ComponentControl( TInt aIndex ) const
    {
    switch ( aIndex )
        {
        case ELabel:
            return iLabel;
        case EDoLabel:
            return iDoLabel;
        case EEditor:
            return iEdwin;
        default:
            return NULL;
        }
    }

// ---------------------------------------------------------
// CAknExScrollerContainer4::Draw( const TRect& aRect ) const
// Draw function
// ---------------------------------------------------------
//
void CAknExScrollerContainer4::Draw( const TRect& aRect ) const
    {
    CWindowGc& gc = SystemGc();

    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KAknExScrollerGray );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.DrawRect( aRect );
    }

// ---------------------------------------------------------
// CAknExScrollerContainer4::HandleControlEventL(
//                        CCoeControl* /* aControl */,
//                        TCoeEvent /* aEventType */ )
// Handles an event of type aEventType reported
// by the control aControl to this observer.
// ---------------------------------------------------------
//
void CAknExScrollerContainer4::HandleControlEventL(
                              CCoeControl* /* aControl */,
                              TCoeEvent /* aEventType */ )
    {
    }

// ---------------------------------------------------------
// CAknExScrollerContainer4::OfferKeyEventL(...)
// Notify key events to editors.
// (other items were commented in a header).
// ---------------------------------------------------------
//
TKeyResponse CAknExScrollerContainer4::OfferKeyEventL(
    const TKeyEvent& aKeyEvent, TEventCode aType)
    {
    if (iEdwin)
        {
        if (iEdwin->IsFocused())
            {
            return iEdwin->OfferKeyEventL(aKeyEvent, aType);
            }
        }
    return EKeyWasNotConsumed;
    }

TBool CAknExScrollerContainer4::RunNextTestL()
    {
    if (iTestNumber < 0)
        {
        iTestNumber = 0;
        }

    if (iTestNumber >= ENumberOfOtherTests)
        {
        iTestNumber = 0;
        return EFalse;
        }

    RunTestL(iTestNumber);
    iTestNumber++;

    return ETrue;
    }

void CAknExScrollerContainer4::RunTestL(TInt aTestId)
    {
    iDoLabel->SetTextL((*iItems)[aTestId]);

    switch (aTestId)
        {
        case EView4DeleteString1:
        case EView4DeleteString2:
            {
            TBuf<KTempBufferLength> string(_L(""));
            iEdwin->SetTextL(&string);
            break;
            }

        case EView4SetString1:
        case EView4SetString2:
            {
            TBuf<KBufferLength> string;
            iCoeEnv->ReadResource(string, R_AKNEXSCROLLER_VIEW4_STRING);
            iEdwin->SetTextL(&string);
            SetCursorPosL(0);
            break;
            }

        case EView4CursorPosition10:
            {
            SetCursorPosL(10);
            break;
            }

        case EView4CursorPosition20:
            {
            SetCursorPosL(20);
            break;
            }

        case EView4CursorPosition30:
            {
            SetCursorPosL(30);
            break;
            }

        case EView4CursorPosition40:
            {
            SetCursorPosL(40);
            break;
            }

        case EView4CursorPosition50:
            {
            SetCursorPosL(50);
            break;
            }

        case EView4CursorPosition60:
            {
            SetCursorPosL(60);
            break;
            }

        case EView4CursorPosition70:
            {
            SetCursorPosL(70);
            break;
            }

        case EView4CursorPosition80:
            {
            SetCursorPosL(80);
            break;
            }

        case EView4CursorPosition90:
            {
            SetCursorPosL(90);
            break;
            }

        case EView4CursorPosition100:
            {
            SetCursorPosL(100);
            break;
            }

        case EView4CursorPosition110:
            {
            SetCursorPosL(110);
            break;
            }

        case EView4CursorPosition120:
            {
            SetCursorPosL(120);
            break;
            }

        case EView4CursorPosition130:
            {
            SetCursorPosL(130);
            break;
            }

        case EView4CursorPosition140:
            {
            SetCursorPosL(140);
            break;
            }

        case EView4CursorPosition150:
            {
            SetCursorPosL(150);
            break;
            }

        case EView4CursorPosition160:
            {
            SetCursorPosL(160);
            break;
            }

        case EView4CursorPosition170:
            {
            SetCursorPosL(170);
            break;
            }

        case EView4CursorPosition180:
            {
            SetCursorPosL(180);
            break;
            }

        case EView4CursorPosition190:
            {
            SetCursorPosL(190);
            break;
            }

        case EView4CursorPosition200:
            {
            SetCursorPosL(200);
            break;
            }

        case ESetScrollBarVisibilityOn:
            {
            iEdwin->ScrollBarFrame()->SetScrollBarVisibilityL(CEikScrollBarFrame::EOn, CEikScrollBarFrame::EOn);
            iEdwin->UpdateScrollBarsL();
            break;
            }

        case ESetScrollBarVisibilityAuto:
            {
            iEdwin->ScrollBarFrame()->SetScrollBarVisibilityL(CEikScrollBarFrame::EAuto, CEikScrollBarFrame::EAuto);
            iEdwin->UpdateScrollBarsL();
            break;
            }

        case EScrollBarExists1:
            {
            iEdwin->ScrollBarFrame()->ScrollBarExists(CEikScrollBar::EHorizontal);
            iEdwin->ScrollBarFrame()->DrawScrollBarsNow();
            break;
            }

        case EScrollBarExists2:
            {
            iEdwin->ScrollBarFrame()->ScrollBarExists(CEikScrollBar::EVertical);
            iEdwin->ScrollBarFrame()->DrawScrollBarsNow();
            break;
            }

        case EOperatorTest:
            {
            CEikScrollBar* bar1 = iEdwin->ScrollBarFrame()->VerticalScrollBar();
            CEikScrollBar* bar2 = new(ELeave) CEikScrollBar;
            TBool flag1 = (bar1->Model() == bar1->Model());
            TBool flag2 = (bar1->Model() != bar1->Model());
            TBool flag3 = (bar1->Model() == bar2->Model());
            TBool flag4 = (bar1->Model() != bar2->Model());
            delete bar2;
            TBuf< KTempBufferLength > string;
            TBuf< KTempBufferLength > format;
            iCoeEnv->ReadResource(format, R_AKNEXSCROLLER_FORMATSTRING_OPERATORTEST);
            string.Format(format, flag1, flag2, flag3, flag4);
            iEikonEnv->AlertWin( string );
            break;
            }

        case EScrollbarUseful:
            {
            TEikScrollBarModel model1(1, 2, 0);
            TEikScrollBarModel model2(2, 1, 0);
            TBool flag1 = model1.ScrollBarUseful();
            TBool flag2 = model2.ScrollBarUseful();
            TBuf< KTempBufferLength > format;
            TBuf< KTempBufferLength > string;
            iCoeEnv->ReadResource(format, R_AKNEXSCROLLER_FORMATSTRING_SCROLLBARUSEFUL);
            string.Format(format, flag1, flag2);
            iEikonEnv->AlertWin( string );
            break;
            }

        case EScrollbarUseful2:
            {
            TEikScrollBarModel model1(-2, -1, 0);
            TEikScrollBarModel model2(-1, -2, 0);
            TBool flag1 = model1.ScrollBarUseful();
            TBool flag2 = model2.ScrollBarUseful();
            TBuf< KTempBufferLength > format;
            TBuf< KTempBufferLength > string;
            iCoeEnv->ReadResource(format, R_AKNEXSCROLLER_FORMATSTRING_SCROLLBARUSEFUL);
            string.Format(format, flag1, flag2);
            iEikonEnv->AlertWin( string );
            break;
            }

        case EMaxThumbPos:
            {
            TEikScrollBarModel model1(1, 2, 0);
            TEikScrollBarModel model2(2, 1, 0);
            TInt pos1 = model1.MaxThumbPos();
            TInt pos2 = model2.MaxThumbPos();
            TBuf< KTempBufferLength > string;
            TBuf< KTempBufferLength > format;
            iCoeEnv->ReadResource(format, R_AKNEXSCROLLER_FORMATSTRING_MAXTHUMBPOS);
            string.Format(format, pos1, pos2);
            iEikonEnv->AlertWin( string );
            break;
            }

        case ECheckBounds:
            {
            TEikScrollBarModel model1(2, 0, 2);
            TEikScrollBarModel model2(3, 0, 1);
            TEikScrollBarModel model3(0, 0, -1);
            TBuf< KTempBufferLength > string;
            TBuf< KTempBufferLength > format;
            iCoeEnv->ReadResource(format, R_AKNEXSCROLLER_FORMATSTRING_CHECKBOUNDS);
            string.Format(format, model1.iThumbPosition, model2.iThumbPosition, model3.iThumbPosition);
            iEikonEnv->AlertWin( string );
            break;
            }

        case EThumbPosition:
            {
            TInt pos = iEdwin->ScrollBarFrame()->VerticalScrollBar()->ThumbPosition();
            TBuf< KTempBufferLength > string;
            TBuf< KTempBufferLength > format;
            iCoeEnv->ReadResource(format, R_AKNEXSCROLLER_FORMATSTRING_THUMBPOSITION);
            string.Format(format, pos);
            iEikonEnv->AlertWin( string );
            break;
            }

        case EIncreaseNudgeButton:
            {
            CAknScrollButton* btn = iEdwin->ScrollBarFrame()->VerticalScrollBar()->IncreaseNudgeButton();
            TBuf< KTempBufferLength > string;
            TBuf< KTempBufferLength > format;
            iCoeEnv->ReadResource(format, R_AKNEXSCROLLER_FORMATSTRING_INCREASENUDGEBUTTON);
            string.Format(format, btn->Type(), btn->IsNormalScrollBarUsingButton());
            iEikonEnv->AlertWin( string );
            break;
            }

        case EDecreaseNudgeButton:
            {
            CAknScrollButton* btn = iEdwin->ScrollBarFrame()->VerticalScrollBar()->DecreaseNudgeButton();
            TBuf< KTempBufferLength > string;
            TBuf< KTempBufferLength > format;
            iCoeEnv->ReadResource(format, R_AKNEXSCROLLER_FORMATSTRING_DECREASENUDGEBUTTON);
            string.Format(format, btn->Type(), btn->IsNormalScrollBarUsingButton());
            iEikonEnv->AlertWin( string );
            break;
            }

        case ESetScrollBarVisibilityOff:
            {
            iEdwin->ScrollBarFrame()->SetScrollBarVisibilityL(CEikScrollBarFrame::EOff, CEikScrollBarFrame::EOff);
            iEdwin->UpdateScrollBarsL();
            break;
            }
        }

    DrawNow();
    }

void CAknExScrollerContainer4::SetCursorPosL(TInt aPos)
    {
    if(iEdwin->TextLength() < aPos)
        {
        TBuf< KTempBufferLength > string;
        iCoeEnv->ReadResource(string, R_AKNEXSCROLLER_NOT_ENOUGH_STRING);
        iEikonEnv->AlertWin( string );
        }
    else
        {
        iEdwin->SetCursorPosL(aPos, EFalse);
        }
    }
// End of File
