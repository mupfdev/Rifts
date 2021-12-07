/*
* ============================================================================
*  Name     : CAknExPbarAppUi from CAknViewAppUi
*  Part of  : AknExPbar
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/


// INCLUDE FILES
#include <AknExPbar.rsg>
#include <avkon.hrh>

#include "AknExPbarAppUi.h"
#include "AknExPbarContainer.h" 
#include "AknExPbar.hrh"

#include "AknExPbarView.h"


// ================= MEMBER FUNCTIONS =======================

// C++ default constructor
CAknExPbarAppUi::CAknExPbarAppUi()
                    : iNaviPane( NULL ),
                      iTabGroup( NULL ),
                      iDecoratedTabGroup( NULL ),
                      iAppContainer( NULL )
    {
    }

// EPOC default constructor can leave.
void CAknExPbarAppUi::ConstructL()
    {
    BaseConstructL();

    // Create status pane
    CEikStatusPane *sp = StatusPane();
    // Create navi pane
    iNaviPane = ( CAknNavigationControlContainer* )sp->ControlL(
        TUid::Uid( EEikStatusPaneUidNavi ) );

    iDecoratedTabGroup = iNaviPane->ResourceDecorator();
    if ( iDecoratedTabGroup )
        {
        iTabGroup = ( CAknTabGroup* )iDecoratedTabGroup->DecoratedControl();
        }

    CAknExPbarView* view1 = new( ELeave )CAknExPbarView;

    CleanupStack::PushL( view1 );
    view1->ConstructL();
    CleanupStack::Pop();
    AddViewL( view1 );

    ActivateLocalViewL( view1->Id() );

    }

// Destructor
CAknExPbarAppUi::~CAknExPbarAppUi()
    {
    delete iDecoratedTabGroup;
    delete iAppContainer;
    }


// ----------------------------------------------------
// CAknExPbarAppUi::HandleCommandL( TInt aCommand )
// Handle command list
// ----------------------------------------------------
void CAknExPbarAppUi::HandleCommandL( TInt aCommand )
    {
    switch ( aCommand )
        {
        case EAknCmdExit:
        case EEikCmdExit:
            Exit();
            break;
        default:
            break;
        } // End switch ( aCommand )
    }


// ----------------------------------------------------
// CAknExPbarAppUi::HandleKeyEventL(
//     const TKeyEvent& aKeyEvent, TEventCode /*aType*/ )
// Handles key events.
// ----------------------------------------------------
TKeyResponse CAknExPbarAppUi::HandleKeyEventL(
    const TKeyEvent& aKeyEvent, TEventCode /*aType*/ )
    {
    iTabGroup = ( CAknTabGroup* )iDecoratedTabGroup->DecoratedControl();
    if ( iTabGroup == NULL )
        {
        return EKeyWasNotConsumed;
        }
    TInt active = iTabGroup->ActiveTabIndex();
    TInt count = iTabGroup->TabCount();

    switch ( aKeyEvent.iCode )
        {
        case EKeyLeftArrow:
            if ( active > 0 )
            {
            active--;
            iTabGroup->SetActiveTabByIndex( active );
            }
            break;
        case EKeyRightArrow:
            if ( ( active + 1 ) < count )
            {
            active++;
            iTabGroup->SetActiveTabByIndex( active );
            }
            break;
        default:
            return EKeyWasNotConsumed;
            break;
        }

    return EKeyWasConsumed;
    }

// End of File  
