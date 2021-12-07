/*
* ============================================================================
*  Name     : CAknExGridContainer from CCoeControl, MCoeControlObserver
*  Part of  : AknExGrid
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include <eiklabel.h>          // for example label control]
#include <coemain.h>           //CoeEnv
#include <AknLists.h>
//#include <EIKON.mbg>
#include <Gulicon.h>
#include <AknGrid.h>
#include <AknSFld.h>

#include <AknExGrid.rsg>
#include "AknExGridContainer.h"

// ================= MEMBER FUNCTIONS =======================

// C++ default constructor can NOT contain any code, that
// might leave.
//
void CAknExGridContainer::ConstructL( const TRect& aRect )
    {
    CreateWindowL();

    TBuf< KLengthOfLabelString > label;
    TBuf< KLengthOfToDoLabelString > todolabel;

    iLabel = new( ELeave ) CEikLabel;
    iLabel->SetContainerWindowL( *this );
    iCoeEnv->ReadResource( label, R_AKNEXGRID_LABEL_VIEW_AS_MAIN );
    iLabel->SetTextL( label );

    iToDoLabel = new( ELeave ) CEikLabel;
    iToDoLabel->SetContainerWindowL( *this );
    iCoeEnv->ReadResource( todolabel, R_AKNEXGRID_TODOLABEL_VIEW_AS_MAIN );
    iToDoLabel->SetTextL( todolabel );

    SetRect( aRect );
    ActivateL();
    }


// Destructor
CAknExGridContainer::~CAknExGridContainer()
    {
    delete iLabel;
    delete iToDoLabel;
    }

// ---------------------------------------------------------
// CAknExGridContainer::SizeChanged()
// Called by framework when the view size is changed.
// ---------------------------------------------------------
//
void CAknExGridContainer::SizeChanged()
    {
    // TODO: Add here control resize code etc.
    iLabel->SetExtent( VIEW_MAIN_LABEL_POINT, iLabel->MinimumSize() );
    iToDoLabel->SetExtent( VIEW_MAIN_DOLABEL_POINT, iToDoLabel->MinimumSize() );
    }

// ---------------------------------------------------------
// CAknExGridContainer::CountComponentControls() const
// Returns number of component.
// ---------------------------------------------------------
//
TInt CAknExGridContainer::CountComponentControls() const
    {
    return KNumberOfComponentMain;   //return nbr of controls inside this container
    }

// ---------------------------------------------------------
// CAknExGridContainer::ComponentControl( TInt aIndex ) const
// Returns pointer to particular component.
// ---------------------------------------------------------
//
CCoeControl* CAknExGridContainer::ComponentControl( TInt aIndex ) const
    {
    switch ( aIndex )
        {
        case ELabel:
            return iLabel;
        
        case EToDoLabel:
            return iToDoLabel;
        
        default:
            return NULL;
        }
    }

// ---------------------------------------------------------
// CAknExGridContainer::Draw( const TRect& aRect ) const
// Draw function.
// ---------------------------------------------------------
//
void CAknExGridContainer::Draw( const TRect& aRect ) const
    {
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KRgbGray );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.DrawRect( aRect );
    }

// ---------------------------------------------------------
// CAknExGridContainer::HandleControlEventL(
//     CCoeControl* aControl, TCoeEvent aEventType)
// Handles an event of type aEventType reported
// by the control aControl to this observer.
// ---------------------------------------------------------
//
void CAknExGridContainer::HandleControlEventL(
    CCoeControl* /*aControl*/, TCoeEvent /*aEventType*/ )
    {
    }

// End of File  
