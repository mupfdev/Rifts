/*
* ============================================================================
*  Name     : CAknExMenuAppUi from CAknViewAppUi
*  Part of  : AknExMenu
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#include <avkon.hrh>
#include <barsread.h>
#include <akntitle.h>
#include <aknnavi.h>
#include <akncontext.h>
#include <eikmenub.h>

#include <AknExMenu.rsg>
#include "AknExMenu.hrh"
#include "AknExMenuAppUi.h"
#include "AknExMenuView.h"
#include "AknExMenuContainer.h" 
#include "AknExMenuSubView.h"
#include "AknExMenuSubContainer.h" 
#include "AknExMenuOkView.h"

// ================= MEMBER FUNCTIONS =======================

// EPOC default constructor can leave.
void CAknExMenuAppUi::ConstructL()
    {
    BaseConstructL();

    // Show tabs for main views from resources
    CEikStatusPane *sp = StatusPane();

    iTitlePane = STATIC_CAST(CAknTitlePane*, sp->ControlL(TUid::Uid(EEikStatusPaneUidTitle)));

    // Fetch pointer to the default navi pane control
    iNaviPane = (CAknNavigationControlContainer*)sp->ControlL(
        TUid::Uid(EEikStatusPaneUidNavi));

    iDecoratedTabGroup = iNaviPane->ResourceDecorator();
    if (iDecoratedTabGroup)
        {
        iTabGroup = (CAknTabGroup*) iDecoratedTabGroup->DecoratedControl();
        }

    CAknExMenuView* view1 = new(ELeave) CAknExMenuView;

    CleanupStack::PushL(view1);
    view1->ConstructL(R_AKNEXMENU_NO_SUB_MENU);
    CleanupStack::Pop();    // view1
    AddViewL(view1);        // transfer ownership to CAknViewAppUi

    CAknExMenuSubView* view2 = new(ELeave) CAknExMenuSubView;

    CleanupStack::PushL(view2);
    view2->ConstructL(R_AKNEXMENU_SUB_MENU);
    CleanupStack::Pop();    // view1
    AddViewL(view2);        // transfer ownership to CAknViewAppUi

    CAknExMenuOkView* view3 = new(ELeave) CAknExMenuOkView;

    CleanupStack::PushL(view3);
    view3->ConstructL(R_AKNEXMENU_OK_MENU);
    CleanupStack::Pop();    // view1
    AddViewL(view3);        // transfer ownership to CAknViewAppUi

    ActivateLocalViewL(view1->Id());
    }

// Destructor
CAknExMenuAppUi::~CAknExMenuAppUi()
    {
    delete iDecoratedTabGroup;
    delete iAppContainer;
    }

// ------------------------------------------------------------------------------
// CAknExMenuAppUi::::DynInitMenuPaneL(TInt aResourceId,CEikMenuPane* aMenuPane)
//  This function is called by the EIKON framework just before it displays
//  a menu pane. Its default implementation is empty, and by overriding it,
//  the application can set the state of menu items dynamically according
//  to the state of application data.
//
// ------------------------------------------------------------------------------
void CAknExMenuAppUi::DynInitMenuPaneL(
    TInt /*aResourceId*/,CEikMenuPane* /*aMenuPane*/)
    {
    }

// ----------------------------------------------------
// CAknExMenuAppUi::HandleCommandL(TInt aCommand)
// takes care of command handling.
// ----------------------------------------------------
void CAknExMenuAppUi::HandleCommandL(TInt aCommand)
    {
    switch (aCommand)
        {
        case EEikCmdExit:
        case EAknCmdExit:
            Exit();
            break;

        // TODO: Add Your command handling code here

        default:
            break;      
        }
    }

// ----------------------------------------------------
// CAknExMenuAppUi::HandleKeyEventL(
//     const TKeyEvent& aKeyEvent,TEventCode /*aType*/)
// handles key events.
// ----------------------------------------------------
TKeyResponse CAknExMenuAppUi::HandleKeyEventL(
    const TKeyEvent& aKeyEvent,TEventCode /*aType*/)
    {
    iTabGroup = (CAknTabGroup*)iDecoratedTabGroup->DecoratedControl();
    if (iTabGroup == NULL)
        {
        return EKeyWasNotConsumed;
        }

    TInt active = iTabGroup->ActiveTabIndex();
    TInt count = iTabGroup->TabCount();

    switch (aKeyEvent.iCode)
        {
        case EKeyLeftArrow:
            if (active > 0)
                {
                active--;
                iTabGroup->SetActiveTabByIndex(active);
                ActivateLocalViewL(TUid::Uid(iTabGroup->TabIdFromIndex(active)));
                }
            break;
        case EKeyRightArrow:
            if((active + 1) < count)
                {
                active++;
                iTabGroup->SetActiveTabByIndex(active);
                ActivateLocalViewL(TUid::Uid(iTabGroup->TabIdFromIndex(active)));
                }
            break;
        default:
            return EKeyWasNotConsumed;
            break;
        }

    return EKeyWasConsumed;
    }

// End of File  
