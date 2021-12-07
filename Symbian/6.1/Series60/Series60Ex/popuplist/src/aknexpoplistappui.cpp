/*
* ============================================================================
*  Name     : CAknExPopListAppUi from CAknViewAppUi
*  Part of  : AknExPopList
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES

#include <avkon.hrh>
#include <barsread.h>
#include <akntitle.h>
#include <aknnavi.h>
#include <akncontext.h>

#include <AknExPopList.rsg>
#include "aknexpoplist.hrh"
#include "AknExPopListAppUi.h"
#include "AknExPopListView.h"
#include "AknExPopListView2.h"
/*
*/
#include "AknExPopListContainer.h" 

// ================= MEMBER FUNCTIONS =======================
//
// ----------------------------------------------------------
// CAknExPopListAppUi::ConstructL()
// ?implementation_description
// ----------------------------------------------------------
void CAknExPopListAppUi::ConstructL()
    {
    BaseConstructL();

    // Show tabs for main views from resources
    CEikStatusPane *sp = StatusPane();

    // Fetch pointer to the default navi pane control
    iNaviPane = (CAknNavigationControlContainer*)sp->ControlL(
        TUid::Uid(EEikStatusPaneUidNavi));

    iDecoratedTabGroup = iNaviPane->ResourceDecorator();
    if (iDecoratedTabGroup)
    {
        iTabGroup = (CAknTabGroup*) iDecoratedTabGroup->DecoratedControl();
    }

    CAknExPopListView* view1 = new(ELeave) CAknExPopListView;
    CleanupStack::PushL(view1);
    view1->ConstructL();
    CleanupStack::Pop();    // view1
    AddViewL(view1);        // transfer ownership to CAknViewAppUi

    CAknExPopListView2* view2 = new(ELeave) CAknExPopListView2;
    CleanupStack::PushL(view2);
    view2->ConstructL();
    CleanupStack::Pop();    // view2
    AddViewL(view2);        // transfer ownership to CAknViewAppUi

/*








*/

    // set a view
    if ( iTabGroup )
        {
        ActivateLocalViewL( TUid::Uid( iTabGroup->ActiveTabId() ) );
        }
    else  // just in case
        {
        ActivateLocalViewL( view1->Id() );
        }
    }

// ----------------------------------------------------
// CAknExPopListAppUi::~CAknExPopListAppUi()
// Destructor
// Frees reserved resources
// ----------------------------------------------------
CAknExPopListAppUi::~CAknExPopListAppUi()
    {
    delete iDecoratedTabGroup;
    delete iAppContainer;
   }

// ----------------------------------------------------------------------------
// CAknExPopListAppUi::DynInitMenuPaneL(
//                                  TInt aResourceId,CEikMenuPane* aMenuPane)
//  This function is called by the EIKON framework just before it displays
//  a menu pane. Its default implementation is empty, and by overriding it,
//  the application can set the state of menu items dynamically according
//  to the state of application data.
//
// ----------------------------------------------------------------------------
void CAknExPopListAppUi::DynInitMenuPaneL(
    TInt /*aResourceId*/,CEikMenuPane* /*aMenuPane*/)
    {
    }

// ----------------------------------------------------
// CAknExPopListAppUi::HandleKeyEventL(
//     const TKeyEvent& aKeyEvent,TEventCode /*aType*/)
// ?implementation_description
// ----------------------------------------------------
TKeyResponse CAknExPopListAppUi::HandleKeyEventL(
    const TKeyEvent& aKeyEvent,TEventCode /*aType*/)
    {
    iTabGroup = (CAknTabGroup*)iDecoratedTabGroup->DecoratedControl();
    if (iTabGroup == NULL)
        return EKeyWasNotConsumed;

    TInt active = iTabGroup->ActiveTabIndex();
    TInt count = iTabGroup->TabCount();

    switch (aKeyEvent.iCode)
        {
        case EKeyLeftArrow:
            if (active > 0)
            {
                active--;
                iTabGroup->SetActiveTabByIndex(active);
                ActivateLocalViewL( TUid::Uid( iTabGroup->ActiveTabId() ) );
            }
            break;

        // Press space key and switch to next view.
        case EKeySpace:
            // if current view is last view, switch to first view.
            if ((active + 1) >= count)
                {
                active = -1;
                }
            // break is NOT needed here.
            // GO THROW to "case EKeyRightArrow:" to switch view.

        case EKeyRightArrow:
            if((active + 1) < count)
            {
                active++;
                iTabGroup->SetActiveTabByIndex(active);
                ActivateLocalViewL( TUid::Uid( iTabGroup->ActiveTabId() ) );
            }
            break;
        default:
            return EKeyWasNotConsumed;
            break;
        }

    return EKeyWasConsumed;
    }

// ----------------------------------------------------
// CAknExPopListAppUi::HandleCommandL(TInt aCommand)
// ?implementation_description
// ----------------------------------------------------
void CAknExPopListAppUi::HandleCommandL(TInt aCommand)
    {
    switch (aCommand)
        {
        case EAknCmdExit:
            Exit();
            break;

        default:
            break;      
        }
    }

// End of File  
