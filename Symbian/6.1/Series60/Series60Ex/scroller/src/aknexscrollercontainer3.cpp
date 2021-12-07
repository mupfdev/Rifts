/*
* ============================================================================
*  Name     : CAknExScrollerContainer3 from CCoeControl, MCoeControlObserver
*  Part of  : AknExScroller
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include <coemain.h>   // CoeEnv
#include <eiklabel.h>  // for label control
#include <AknExScroller.rsg>
#include "AknExScrollerContainer3.h"


// CONSTANTS
#define KAknExScrollerRed TRgb(0x0000ff)

#define VIEW3_LABEL_POINT   TPoint( 10, 10 )
#define VIEW3_DOLABEL_POINT TPoint( 10, 100 )

const TInt KNumberOfComponent = 2;
const TInt KBufferLength = 256;

// Enumeration
enum TPointerToComponetView3
    {
    ELabel = 0,
    EDoLabel
    };


// ================= MEMBER FUNCTIONS =======================
// C++ default constructor can NOT contain any code, that
// might leave.
//
CAknExScrollerContainer3::CAknExScrollerContainer3()
                        : iLabel( NULL ), iDoLabel( NULL )
    {
    }


// ---------------------------------------------------------
// CAknExScrollerContainer3::ConstructL( const TRect& aRect )
// EPOC two phased constructor
// ---------------------------------------------------------
//
void CAknExScrollerContainer3::ConstructL( const TRect& aRect )
    {
    CreateWindowL();

    TBuf<KBufferLength> label;
    TBuf<KBufferLength> dolabel;

    iLabel = new ( ELeave ) CEikLabel;
    iLabel->SetContainerWindowL( *this );
    iCoeEnv->ReadResource( label, R_AKNEXSCROLLER_LABEL_VIEW3 );
    iLabel->SetTextL( label );

    iDoLabel = new ( ELeave ) CEikLabel;
    iDoLabel->SetContainerWindowL( *this );
    iCoeEnv->ReadResource( dolabel, R_AKNEXSCROLLER_DOLABEL_VIEW3 );
    iDoLabel->SetTextL( dolabel );

    SetRect( aRect );

    ActivateL();
    }

// ---------------------------------------------------------
// Destructor
// ---------------------------------------------------------
//
CAknExScrollerContainer3::~CAknExScrollerContainer3()
    {
    delete iLabel;
    delete iDoLabel;

    iLabel = NULL;
    iDoLabel = NULL;

    }


// ---------------------------------------------------------
// CAknExScrollerContainer3::SizeChanged()
// Called by framework when the view size is changed
// ---------------------------------------------------------
//
void CAknExScrollerContainer3::SizeChanged()
    {
    // TODO: Add here control resize code etc.
    iLabel->SetExtent( VIEW3_LABEL_POINT, iLabel->MinimumSize() );
    iDoLabel->SetExtent( VIEW3_DOLABEL_POINT, iDoLabel->MinimumSize() );
    }

// ---------------------------------------------------------
// CAknExScrollerContainer3::CountComponentControls() const
// Returns number of component.
// ---------------------------------------------------------
//
TInt CAknExScrollerContainer3::CountComponentControls() const
    {
    return KNumberOfComponent; // return nbr of controls inside this container
    }

// ---------------------------------------------------------
// CAknExScrollerContainer3::ComponentControl( TInt aIndex ) const
// Returns pointer to particular component.
// ---------------------------------------------------------
//
CCoeControl* CAknExScrollerContainer3::ComponentControl( TInt aIndex ) const
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
// CAknExScrollerContainer3::Draw( const TRect& aRect ) const
// Draw function
// ---------------------------------------------------------
//
void CAknExScrollerContainer3::Draw( const TRect& aRect ) const
    {
    CWindowGc& gc = SystemGc();

    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KAknExScrollerRed );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.DrawRect( aRect );
    }

// ---------------------------------------------------------
// CAknExScrollerContainer3::HandleControlEventL(
//                        CCoeControl* /* aControl */,
//                        TCoeEvent /* aEventType */ )
// Handles an event of type aEventType reported
// by the control aControl to this observer.
// ---------------------------------------------------------
//
void CAknExScrollerContainer3::HandleControlEventL(
                              CCoeControl* /* aControl */,
                              TCoeEvent /* aEventType */ )
    {
    }


// End of File
