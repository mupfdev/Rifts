/*
* ============================================================================
*  Name     : CAknExPopListContainer from CCoeControl, MCoeControlObserver
*  Part of  : AknExPopList
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include    "AknExPopListContainer.h"
#include    <eiklabel.h>  // for example label control

// CONSTANTS
const TInt KNumberOfControls = 0;

// ================= MEMBER FUNCTIONS =======================

// ---------------------------------------------------------
// CAknExPopListContainer::ConstructL(const TRect& aRect)
// EPOC two phased constructor
// 
// ---------------------------------------------------------
//
void CAknExPopListContainer::ConstructL(const TRect& aRect)
    {
    CreateWindowL();

    SetRect(aRect);
    ActivateL();
    }

// Destructor
CAknExPopListContainer::~CAknExPopListContainer()
    {
    }

// ---------------------------------------------------------
// CAknExPopListContainer::SizeChanged()
// Called by framework when the view size is changed
//  
// ---------------------------------------------------------
//
void CAknExPopListContainer::SizeChanged()
    {
    }

// ---------------------------------------------------------
// CAknExPopListContainer::CountComponentControls() const
//
//  
// ---------------------------------------------------------
//
TInt CAknExPopListContainer::CountComponentControls() const
    {
    return KNumberOfControls; // return nbr of controls inside this container
    }

// ---------------------------------------------------------
// CAknExPopListContainer::ComponentControl(TInt aIndex) const
//
// ---------------------------------------------------------
//
CCoeControl* CAknExPopListContainer::ComponentControl(TInt /*aIndex*/) const
    {
    return NULL;
    }

// ---------------------------------------------------------
// CAknExPopListContainer::Draw(const TRect& aRect) const
// 
// ---------------------------------------------------------
//
void CAknExPopListContainer::Draw(const TRect& aRect) const
    {
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle(CGraphicsContext::ENullPen);
#define KRgbColorGray TRgb(0xaaaaaa)
    gc.SetBrushColor(KRgbColorGray);
    gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
    gc.DrawRect(aRect);
    }

// ---------------------------------------------------------
// CAknExPopListContainer::HandleControlEventL(
//     CCoeControl* aControl,TCoeEvent aEventType)
// ---------------------------------------------------------
//
void CAknExPopListContainer::HandleControlEventL(
    CCoeControl* /*aControl*/,TCoeEvent /*aEventType*/)
    {
    }

// End of File  
