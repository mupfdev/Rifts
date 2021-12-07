/*
* ============================================================================
*  Name     : CAknExScrollerContainer from CCoeControl, MCoeControlObserver
*  Part of  : AknExScroller
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include <coemain.h>   // CoeEnv
#include <eiklabel.h>  // for label control
#include <AknForm.h>   // for Form

#include <AknExScroller.rsg>
#include "AknExScrollerContainer.h"
#include "AknExScrollerView.h"  // for Form


// CONSTANTS
#define KAknExScrollerBlue TRgb(0xff0000)

#define VIEW1_LABEL_POINT   TPoint( 10, 10 )
#define VIEW1_DOLABEL_POINT TPoint( 10, 100 )

const TInt KNumberOfComponent = 2;
const TInt KBufferLength = 256;

// Enumeration
enum TPointerToComponetView1
    {
    ELabel = 0,
    EDoLabel
    };


// ================= MEMBER FUNCTIONS =======================
// C++ default constructor can NOT contain any code, that
// might leave.
//
CAknExScrollerContainer::CAknExScrollerContainer()
                       : iLabel( NULL ), iDoLabel( NULL )
    {
    }


// ---------------------------------------------------------
// CAknExScrollerContainer::ConstructL( const TRect& aRect )
// EPOC two phased constructor
// ---------------------------------------------------------
//
void CAknExScrollerContainer::ConstructL( const TRect& aRect )
    {
    CreateWindowL();

    TBuf<KBufferLength> label;
    TBuf<KBufferLength> dolabel;

    iLabel = new ( ELeave ) CEikLabel;
    iLabel->SetContainerWindowL( *this );
    iCoeEnv->ReadResource( label, R_AKNEXSCROLLER_LABEL_VIEW1 );
    iLabel->SetTextL( label );

    iDoLabel = new ( ELeave ) CEikLabel;
    iDoLabel->SetContainerWindowL( *this );
    iCoeEnv->ReadResource( dolabel, R_AKNEXSCROLLER_DOLABEL_VIEW1 );
    iDoLabel->SetTextL( dolabel );

    SetRect( aRect );

    ActivateL();
    }


// Destructor
CAknExScrollerContainer::~CAknExScrollerContainer()
    {
    delete iLabel;
    delete iDoLabel;

    iLabel = NULL;
    iDoLabel = NULL;
    }

// ---------------------------------------------------------
// CAknExScrollerContainer::SizeChanged()
// Called by framework when the view size is changed
// ---------------------------------------------------------
//
void CAknExScrollerContainer::SizeChanged()
    {
    // TODO: Add here control resize code etc.
    iLabel->SetExtent( VIEW1_LABEL_POINT, iLabel->MinimumSize() );
    iDoLabel->SetExtent( VIEW1_DOLABEL_POINT, iDoLabel->MinimumSize() );
    }

// ---------------------------------------------------------
// CAknExScrollerContainer::CountComponentControls() const
// Returns number of component.
// ---------------------------------------------------------
//
TInt CAknExScrollerContainer::CountComponentControls() const
    {
    return KNumberOfComponent; // return nbr of controls inside this container
    }

// ---------------------------------------------------------
// CAknExScrollerContainer::ComponentControl( TInt aIndex ) const
// Returns pointer to particular component.
// ---------------------------------------------------------
//
CCoeControl* CAknExScrollerContainer::ComponentControl( TInt aIndex ) const
    {
    switch ( aIndex )
        {
        case ELabel:
            return iLabel;
        case EDoLabel:
            return iDoLabel;
        default:
            return NULL;
        }
    }

// ---------------------------------------------------------
// CAknExScrollerContainer::Draw( const TRect& aRect ) const
// Draw function
// ---------------------------------------------------------
//
void CAknExScrollerContainer::Draw( const TRect& aRect ) const
    {
    CWindowGc& gc = SystemGc();

    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KAknExScrollerBlue );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.DrawRect( aRect );
    }

// ---------------------------------------------------------
// CAknExScrollerContainer::HandleControlEventL(
//                        CCoeControl* /* aControl */,
//                        TCoeEvent /* aEventType */ )
// Handles an event of type aEventType reported
// by the control aControl to this observer.
// ---------------------------------------------------------
//
void CAknExScrollerContainer::HandleControlEventL(
                              CCoeControl* /* aControl */,
                              TCoeEvent /* aEventType */ )
    {
    }


// End of File
