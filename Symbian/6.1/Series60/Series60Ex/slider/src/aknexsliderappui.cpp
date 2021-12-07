/*
* ============================================================================
*  Name     : CAknExSliderAppUi
*  Part of  : AknExSlider
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#include "AknExSliderAppUi.h"
#include "AknExSliderView.h"
#include <aknviewappui.h>
#include <avkon.hrh>

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExSliderAppUi::CAknExSliderAppUi()
// Default constructor.
// ----------------------------------------------------------------------------
//
CAknExSliderAppUi::CAknExSliderAppUi()
    {
    }

// ----------------------------------------------------------------------------
// CAknExSliderAppUi::ConstructL()
// EPOC constructor.
// Creates view class object.
// ----------------------------------------------------------------------------
//
void CAknExSliderAppUi::ConstructL()
    {
    BaseConstructL();

    // Creates CAknExSliderView object.
    CAknExSliderView* view = new( ELeave ) CAknExSliderView;
    CleanupStack::PushL( view ); // Pushes view to clean-up stack.
    AddViewL( view ); // Transfers ownership to CAknViewAppUi.
    CleanupStack::Pop(); // Pops from clean-up stack. (view)

    ActivateLocalViewL( view->Id() ); // Activates the view.
    }

// ----------------------------------------------------------------------------
// CAknExSliderAppUi::~CAknExSliderAppUi()
// Destructor.
// ----------------------------------------------------------------------------
//
CAknExSliderAppUi::~CAknExSliderAppUi()
    {
    }

// ----------------------------------------------------------------------------
// CAknExSliderAppUi::HandleCommandL( TInt )
// Handles the commands.
// ----------------------------------------------------------------------------
void CAknExSliderAppUi::HandleCommandL( TInt aCommand )
    {
    switch ( aCommand )
        {
        case EAknSoftkeyBack:
        case EEikCmdExit:
            Exit();
            break;
        default:
            break;
        }
    }

// End of File
