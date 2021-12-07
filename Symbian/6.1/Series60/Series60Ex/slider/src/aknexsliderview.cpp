/*
* ============================================================================
*  Name     : CAknExSliderView
*  Part of  : AknExSlider
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include <aknviewappui.h>
#include <avkon.hrh>
#include <akntitle.h>
#include <AknExSlider.rsg>
#include "AknExSliderView.h"
#include "AknExSliderContainer.h" 
#include "AknExSlider.hrh"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExSliderView::CAknExSliderView()
// Default constructor.
// ----------------------------------------------------------------------------
//
CAknExSliderView::CAknExSliderView()
:   iContainer( NULL )
    {
    }

// ----------------------------------------------------------------------------
// CAknExSliderView::~CAknExSliderView()
// Destructor.
// ----------------------------------------------------------------------------
//
CAknExSliderView::~CAknExSliderView()
    {
    CloseContainer(); // Deletes container object.
    }

// ----------------------------------------------------------------------------
// TUid CAknExSliderView::Id()
// Returns ID of view.
// ----------------------------------------------------------------------------
//
TUid CAknExSliderView::Id() const
    {
    return KViewId;
    }

// ----------------------------------------------------------------------------
// CAknExSliderView::HandleCommandL( TInt )
// Handles the commands.
// ----------------------------------------------------------------------------
//
void CAknExSliderView::HandleCommandL( TInt aCommand )
    {
    switch ( aCommand )
        {
        case EAknSoftkeyBack:
            AppUi()->ProcessCommandL( EEikCmdExit );
            break;
        case EAknCmdExit:
            AppUi()->HandleCommandL( aCommand );
            break;
        case EAknExSliderCbaCmdNext:
            iContainer->DisplayNextFeature();
            break;
        default:
            iContainer->HandleCommandL( aCommand );
            break;
        }
    }

// ----------------------------------------------------------------------------
// CAknExSliderView::CloseContainer()
// Deletes container class object.
// ----------------------------------------------------------------------------
//
void CAknExSliderView::CloseContainer()
    {
    // Deletes CAknExSliderContainer object.
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );            // Removes container
                                                           //- from view
                                                           //- control stack.
        delete iContainer;
        iContainer = NULL;
        }
    }

// ----------------------------------------------------------------------------
// CAknExSliderView::DoActivateL( const TVwsViewId&, TUid, const TDesC8& )
// Creates container class object.
// ----------------------------------------------------------------------------
//
void CAknExSliderView::DoActivateL(
    const TVwsViewId& /*aPrevViewId*/,
    TUid /*aCustomMessageId*/,
    const TDesC8& /*aCustomMessage*/ )
    {
    if ( !iContainer )
        {
        // Create CAknExSliderContainer object.
        iContainer = new( ELeave ) CAknExSliderContainer(this);
        iContainer->SetMopParent(this);
        iContainer->ConstructL( ClientRect() );
        AppUi()->AddToStackL( *this, iContainer );     // Adds container to view
                                                       //- control stack.
        }
    }

// ----------------------------------------------------------------------------
// CAknExSliderView::DoDeactivate()
// Deletes container class object.
// ----------------------------------------------------------------------------
//
void CAknExSliderView::DoDeactivate()
    {
    CloseContainer(); // Deletes container class object.
    }

// ----------------------------------------------------------------------------
// void CAknExSliderView::SetTitleL(const TInt aResouceId)
// Set Title and Show Outline Number
// ----------------------------------------------------------------------------
//
void CAknExSliderView::SetTitleL(const TInt aResouceId)
    {
    // Fetches pointer to the default title pane control.
    CAknTitlePane* titlePane = STATIC_CAST(CAknTitlePane*,
        StatusPane()->ControlL( TUid::Uid( EEikStatusPaneUidTitle ) ) );
        

    TBuf<128> MessageText;
    iCoeEnv->ReadResource( MessageText, aResouceId );
    titlePane->SetTextL( MessageText );

    }

// End of File
