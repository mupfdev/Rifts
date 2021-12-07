/*
* ============================================================================
*  Name     : CAknExScrollerAppUi from CAknViewAppUi
*  Part of  : AknExScroller
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/


// INCLUDE FILES
#include <akntitle.h>
#include <aknnavi.h>
#include <akncontext.h>
#include <barsread.h>
#include <avkon.hrh>

#include <AknExScroller.rsg>
#include "AknExScroller.hrh"
#include "AknExScrollerAppUi.h"
#include "AknExScrollerView.h"
#include "AknExScrollerView2.h"
#include "AknExScrollerView3.h"
#include "AknExScrollerView4.h"


// ================= MEMBER FUNCTIONS =======================
// ----------------------------------------------------------
// CAknExScrollerAppUi::CAknExScrollerAppUi()
// C++ default constructor.
// ----------------------------------------------------------
//
CAknExScrollerAppUi::CAknExScrollerAppUi()
    {
    }


// ----------------------------------------------------------
// CAknExScrollerAppUi::ConstructL()
// EPOC default constructor
// ----------------------------------------------------------
//
void CAknExScrollerAppUi::ConstructL()
    {
    BaseConstructL();

    // Show tabs for main views from resources
    CEikStatusPane* sp = StatusPane();

    // Fetch pointer to the default navi pane control
    iNaviPane = ( CAknNavigationControlContainer* )sp->ControlL( 
        TUid::Uid( EEikStatusPaneUidNavi ) );

    // Activate tab. It can be done also in tabgroup resource.
    // iTabGroup->SetActiveTabById(EStatusTitleViewId); 

    // Tabgroup has been read from resource and 
    // it were pushed to the navi pane. 
    // Get pointer to the navigation decorator 
    // with the ResourceDecorator() function. 
    // Application owns the decorator and 
    // it has responsibility to delete the object.
    iDecoratedTabGroup = iNaviPane->ResourceDecorator();
    if ( iDecoratedTabGroup )
        {
        iTabGroup = ( CAknTabGroup* ) iDecoratedTabGroup->DecoratedControl();
        }

    CAknExScrollerView* view1 = new( ELeave ) CAknExScrollerView;

    CleanupStack::PushL( view1 );
    view1->ConstructL();
    AddViewL( view1 );      // transfer ownership to CAknViewAppUi
    CleanupStack::Pop();    // view1

    CAknExScrollerView2* view2 = new( ELeave ) CAknExScrollerView2;

    CleanupStack::PushL( view2 );
    view2->ConstructL();
    AddViewL( view2 );      // transfer ownership to CAknViewAppUi
    CleanupStack::Pop();    // view2

    CAknExScrollerView3* view3 = new( ELeave ) CAknExScrollerView3;

    CleanupStack::PushL( view3 );
    view3->ConstructL();
    AddViewL( view3 );      // transfer ownership to CAknViewAppUi
    CleanupStack::Pop();    // view3

    CAknExScrollerView4* view4 = new( ELeave ) CAknExScrollerView4;

    CleanupStack::PushL( view4 );
    view4->ConstructL();
    AddViewL( view4 );      // transfer ownership to CAknViewAppUi
    CleanupStack::Pop();    // view4

    ActivateLocalViewL( view1->Id() );
    }

// ----------------------------------------------------
// CAknExScrollerAppUi::~CAknExScrollerAppUi()
// Destructor
// ----------------------------------------------------
//
CAknExScrollerAppUi::~CAknExScrollerAppUi()
    {
    delete iDecoratedTabGroup;
    }


// ----------------------------------------------------
// CAknExScrollerAppUi::HandleCommandL( TInt aCommand )
// akes care of command handling
// ----------------------------------------------------
//
void CAknExScrollerAppUi::HandleCommandL( TInt aCommand )
    {
    TInt active = -1;

    switch ( aCommand )
        {
        case EAknCmdExit:
        case EEikCmdExit:
            Exit();
            break;
        case EAknExScrollerView1:
            active = 0;
            break;
        case EAknExScrollerView2:
            active = 1;
            break;
        case EAknExScrollerView3:
            active = 2;
            break;
        case EAknExScrollerView4:
            active = 3;
            break;
        default:
            break;
        }

    if ( active > -1 )
        {
        iTabGroup->SetActiveTabByIndex( active );
        ActivateLocalViewL( TUid::Uid( iTabGroup->TabIdFromIndex(
                                                  active ) ) );
        }
    }


// ----------------------------------------------------
// CAknExScrollerAppUi::HandleKeyEventL(
//     const TKeyEvent& aKeyEvent,
//     TEventCode /*aType*/ )
// handles key events
// ----------------------------------------------------
//
TKeyResponse CAknExScrollerAppUi::HandleKeyEventL(
    const TKeyEvent& aKeyEvent,
    TEventCode /*aType*/ )
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
                ActivateLocalViewL( TUid::Uid( iTabGroup->TabIdFromIndex( 
                                                          active ) ) );
                }
            break;
        case EKeyRightArrow:
            if ( ( active + 1 ) < count )
                {
                active++;
                iTabGroup->SetActiveTabByIndex( active );
                ActivateLocalViewL( TUid::Uid( iTabGroup->TabIdFromIndex(
                                                          active ) ) );
                }
            break;
        
        case EKeySpace:
            if ( ( active + 1 ) == count )
                {
                active = 0;
                iTabGroup->SetActiveTabByIndex( active );
                ActivateLocalViewL( TUid::Uid( iTabGroup->TabIdFromIndex(
                                                          active ) ) );
                }
            else
                {
                active++;
                iTabGroup->SetActiveTabByIndex( active );
                ActivateLocalViewL( TUid::Uid( iTabGroup->TabIdFromIndex(
                                                          active ) ) );
                }
            break;

        default:
            return EKeyWasNotConsumed;
            break;
        }

    return EKeyWasConsumed;
    }


// End of File  
