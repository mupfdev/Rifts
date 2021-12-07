/*
* ============================================================================
*  Name     : CAknExMenuOkContainer from CCoeControl, MCoeControlObserver
*  Part of  : AknExMenu
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include <barsread.h>
#include <eikmenub.h>

#include <AknExMenu.rsg>
#include "AknExMenuOkContainer.h"
#include "AknExMenuOkView.h"

// CONSTANTS
const TInt KNumberOfComponentOkView = 2;
const TInt KNumberOfMargenInScreen = 20;

//ENUMERATION
enum TPointerToComponentOkView
    {
    EUpperTextOkView = 0,
    ELowerTextOkView
    };

#define EDWIN_POS           TPoint(10, 50)

#define KAknExMenuWhite TRgb(0xffffff)

// ================= MEMBER FUNCTIONS =======================

// EPOC default constructor can leave.
void CAknExMenuOkContainer::ConstructL(const TRect& aRect, CAknExMenuOkView* aParent)
    {
    CreateWindowL();
    
    iParent = aParent;

    TResourceReader reader;
    iUpperText = new(ELeave) CEikEdwin;
    iUpperText->SetContainerWindowL(*this);
    iCoeEnv->CreateResourceReaderLC(reader, R_AKNEXMENU_TEXT_VIEW);
    iUpperText->ConstructFromResourceL(reader);
    CleanupStack::PopAndDestroy();
    iUpperText->SetTextL(&(aParent->iUpperMsg));
    
    iLowerText = new(ELeave) CEikEdwin;
    iLowerText->SetContainerWindowL(*this);
    iCoeEnv->CreateResourceReaderLC(reader, R_AKNEXMENU_EDITABLE_VIEW);
    iLowerText->ConstructFromResourceL(reader);
    CleanupStack::PopAndDestroy();
    iLowerText->SetTextL(&(aParent->iLowerMsg));

    SetRect(aRect);
    ActivateL();

    iLowerText->SetFocus(ETrue);
    }

// Destructor
CAknExMenuOkContainer::~CAknExMenuOkContainer()
    {
    delete iUpperText;
    delete iLowerText;
    }

// ---------------------------------------------------------
// CAknExMenuOkContainer::SizeChanged()
// Called by framework when the view size is changed
//  
// ---------------------------------------------------------
//
void CAknExMenuOkContainer::SizeChanged()
    {
    // TODO: Add here control resize code etc.
    TRect rect = Rect();
    TSize size;
    size.iWidth = rect.iBr.iX - rect.iTl.iX;
    size.iHeight = (rect.iBr.iY - rect.iTl.iY) / 2;
    iUpperText->SetExtent(rect.iTl, size);

    // SriniC 18.09.2001: Fixed a minor layout problem. Adding 1 to the height 
    // but also that 1 has to be deducted from the size.iHeight otherwise 
    // it the exceeds the total height. Commented out the following line and
    // added next two lines

    //iLowerText->SetExtent(TPoint(rect.iTl.iX, size.iHeight + 1), size);

    size.iHeight-=1;
    iLowerText->SetExtent(TPoint(rect.iTl.iX, (rect.iBr.iY/2)+1), size);
    }

// ---------------------------------------------------------
// CAknExMenuOkContainer::CountComponentControls() const
// return nbr of controls inside this container.
//  
// ---------------------------------------------------------
//
TInt CAknExMenuOkContainer::CountComponentControls() const
    {
    return KNumberOfComponentOkView;
    }

// ---------------------------------------------------------
// CAknExMenuOkContainer::ComponentControl(TInt aIndex) const
// return pointer of controls inside this container
// ---------------------------------------------------------
//
CCoeControl* CAknExMenuOkContainer::ComponentControl(TInt aIndex) const
    {
    switch (aIndex)
        {
        case EUpperTextOkView:
            return iUpperText;
        case ELowerTextOkView:
            return iLowerText;
        default:
            return NULL;
        }
    }

// ---------------------------------------------------------
// CAknExMenuOkContainer::OfferKeyEventL(...)
// Notify key events to editors.
// (other items were commented in a header).
// ---------------------------------------------------------
//
TKeyResponse CAknExMenuOkContainer::OfferKeyEventL(
    const TKeyEvent& aKeyEvent, TEventCode aType)
    {
    TKeyResponse keyResponce(EKeyWasNotConsumed);

    keyResponce = iLowerText->OfferKeyEventL(aKeyEvent, aType);

    if (keyResponce == EKeyWasNotConsumed)
        {
        if ( (aType == EEventKey) && (aKeyEvent.iCode == EKeyOK) )
            {
            iParent->MenuBar()->SetMenuTitleResourceId(R_AKNEXMENU_MENUBAR_OK_TEST);

            if ( iParent->MenuBar())
                {
                iParent->MenuBar()->StopDisplayingMenuBar();
                }
            if (iParent->MenuBar())
                {
                iParent->MenuBar()->TryDisplayMenuBarL();
                }
            }
        iParent->MenuBar()->SetMenuTitleResourceId(R_AKNEXMENU_MENUBAR_OK_MENU);

        return EKeyWasConsumed;
        }

    return keyResponce;

    }

// ---------------------------------------------------------
// CAknExMenuOkContainer::HandleControlEventL(
//     CCoeControl* aControl,TCoeEvent aEventType)
// ---------------------------------------------------------
//
void CAknExMenuOkContainer::HandleControlEventL(
    CCoeControl* /*aControl*/,TCoeEvent /*aEventType*/)
    {
    // TODO: Add your control event handler code here
    }

// ---------------------------------------------------------
// CAknExMenuContainer::Draw( const TRect& aRect ) const
// Draw function
// ---------------------------------------------------------
//
void CAknExMenuOkContainer::Draw( const TRect& aRect ) const
    {
    CWindowGc& gc = SystemGc();

    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KAknExMenuWhite );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.DrawRect( aRect );
    }

// End of File  
