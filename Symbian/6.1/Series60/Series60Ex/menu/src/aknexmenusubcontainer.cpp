/*
* ============================================================================
*  Name     : CAknExMenuSubContainer from CCoeControl, MCoeControlObserver
*  Part of  : AknExMenu
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include <barsread.h>

#include <AknExMenu.rsg>
#include "AknExMenuSubContainer.h"
#include "AknExMenusubview.h"

// CONSTANTS
const TInt KNumberOfComponentSubView = 2;

//ENUMERATION
enum TPointerToComponentSubView
    {
    EUpperTextSubView = 0,
    ELowerTextSubView
    };

#define KAknExMenuWhite TRgb(0xffffff)

// ================= MEMBER FUNCTIONS =======================

// EPOC default constructor can leave.
void CAknExMenuSubContainer::ConstructL(const TRect& aRect, CAknExMenuSubView* aParent)
    {
    CreateWindowL();
    
    TResourceReader reader;
    iUpperText = new(ELeave) CEikEdwin;
    iUpperText->SetContainerWindowL(*this);
    iCoeEnv->CreateResourceReaderLC(reader, R_AKNEXMENU_TEXT_VIEW);
    iUpperText->ConstructFromResourceL(reader);
    CleanupStack::PopAndDestroy();
//    iUpperText->SetNonFocusing();
    iUpperText->SetTextL(&(aParent->iUpperMsg));
    
    iLowerText = new(ELeave) CEikEdwin;
    iLowerText->SetContainerWindowL(*this);
    iCoeEnv->CreateResourceReaderLC(reader, R_AKNEXMENU_TEXT_VIEW);
    iLowerText->ConstructFromResourceL(reader);
    CleanupStack::PopAndDestroy();
//    iLowerText->SetNonFocusing();
    iLowerText->SetTextL(&(aParent->iLowerMsg));

    SetRect(aRect);
    ActivateL();
    }

// Destructor
CAknExMenuSubContainer::~CAknExMenuSubContainer()
    {
    delete iUpperText;
    delete iLowerText;
    }

// ---------------------------------------------------------
// CAknExMenuSubContainer::SizeChanged()
// Called by framework when the view size is changed
//  
// ---------------------------------------------------------
//
void CAknExMenuSubContainer::SizeChanged()
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
// CAknExMenuSubContainer::CountComponentControls() const
// return nbr of controls inside this container.
//  
// ---------------------------------------------------------
//
TInt CAknExMenuSubContainer::CountComponentControls() const
    {
    return KNumberOfComponentSubView; // return nbr of controls inside this container
    }

// ---------------------------------------------------------
// CAknExMenuSubContainer::ComponentControl(TInt aIndex) const
// return pointer of controls inside this container
// ---------------------------------------------------------
//
CCoeControl* CAknExMenuSubContainer::ComponentControl(TInt aIndex) const
    {
    switch (aIndex)
        {
        case EUpperTextSubView:
            return iUpperText;
        case ELowerTextSubView:
            return iLowerText;
        default:
            return NULL;
        }
    }

// ---------------------------------------------------------
// CAknExMenuSubContainer::HandleControlEventL(
//     CCoeControl* aControl,TCoeEvent aEventType)
// ---------------------------------------------------------
//
void CAknExMenuSubContainer::HandleControlEventL(
    CCoeControl* /*aControl*/,TCoeEvent /*aEventType*/)
    {
    // TODO: Add your control event handler code here
    }

// ---------------------------------------------------------
// CAknExMenuContainer::Draw( const TRect& aRect ) const
// Draw function
// ---------------------------------------------------------
//
void CAknExMenuSubContainer::Draw( const TRect& aRect ) const
    {
    CWindowGc& gc = SystemGc();

    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KAknExMenuWhite );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.DrawRect( aRect );
    }

// End of File  
