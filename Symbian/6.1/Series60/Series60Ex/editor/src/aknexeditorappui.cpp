/*
* ============================================================================
*  Name     : CAknExEditorAppUi from CAknViewAppUi
*  Part of  : AknExEditor
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#include <avkon.hrh>
#include <barsread.h>
#include <akntitle.h>
#include <aknnavi.h>
#include <akncontext.h>
#include <akntabgrp.h>
#include <aknnavide.h>

#include <AknExEditor.rsg>
#include "aknexeditor.hrh"
#include "AknExEditorScenarioManager.h"
#include "AknExEditorAppUi.h"
#include "AknExEditorView1.h"
#include "AknExEditorView4.h"
#include "AknExEditorView5.h"
#include "AknExEditorView6.h"
#include "AknExEditorView7.h"
#include "AknExEditorView9.h"
#include "AknExEditorView21.h"
#include "AknExEditorView22.h"
#include "AknExEditorView23.h"
#include "AknExEditorView25.h"
#include "AknExEditorView30.h"
#include "AknExEditorView33.h"

// ================= MEMBER FUNCTIONS =======================


// C++ default constructor can NOT contain any code, that
// might leave.
//
CAknExEditorAppUi::CAknExEditorAppUi()
                    :iDecoratedTabGroup(NULL), iScenarioManager(NULL)
    {
    }

// EPOC default constcuctor can leave.
void CAknExEditorAppUi::ConstructL()
    {
    BaseConstructL();

    // Show tabs for main views from resources
    CEikStatusPane *sp = StatusPane();

    // Title
    iTitlePane = STATIC_CAST(CAknTitlePane*,
                        sp->ControlL(TUid::Uid(EEikStatusPaneUidTitle)));

    // Fetch pointer to the default navi pane control
    iNaviPane = (CAknNavigationControlContainer*)sp->ControlL(
        TUid::Uid(EEikStatusPaneUidNavi));

    // Create tabs.
    iDecoratedTabGroup = iNaviPane->ResourceDecorator();
    if (iDecoratedTabGroup)
        {
        iTabGroup = (CAknTabGroup*) iDecoratedTabGroup->DecoratedControl();
        }

    // Create ScenarioManager
    iScenarioManager = new (ELeave) CAknExEditorScenarioManager;

    // Create and add views.
    CAknExEditorView1* view1 = new (ELeave) CAknExEditorView1;
    CleanupStack::PushL(view1);
    view1->ConstructL();
    CleanupStack::Pop();    // view1
    AddViewL(view1);        // transfer ownership to CAknViewAppUi

    CAknExEditorView4* view4 = new (ELeave) CAknExEditorView4;
    CleanupStack::PushL(view4);
    view4->ConstructL();
    CleanupStack::Pop();    // view4
    AddViewL(view4);        // transfer ownership to CAknViewAppUi

    CAknExEditorView5* view5 = new (ELeave) CAknExEditorView5;
    CleanupStack::PushL(view5);
    view5->ConstructL();
    CleanupStack::Pop();    // view5
    AddViewL(view5);        // transfer ownership to CAknViewAppUi

    CAknExEditorView6* view6 = new (ELeave) CAknExEditorView6;
    CleanupStack::PushL(view6);
    view6->ConstructL();
    CleanupStack::Pop();    // view6
    AddViewL(view6);        // transfer ownership to CAknViewAppUi

    CAknExEditorView7* view7 = new (ELeave) CAknExEditorView7;
    CleanupStack::PushL(view7);
    view7->ConstructL();
    CleanupStack::Pop();    // view7
    AddViewL(view7);        // transfer ownership to CAknViewAppUi

    CAknExEditorView9* View9 = new (ELeave) CAknExEditorView9;
    CleanupStack::PushL(View9);
    View9->ConstructL();
    CleanupStack::Pop();    // View9
    AddViewL(View9);        // transfer ownership to CAknViewAppUi

    CAknExEditorView21* View21 = new (ELeave) CAknExEditorView21;
    CleanupStack::PushL(View21);
    View21->ConstructL();
    CleanupStack::Pop();    // view21
    AddViewL(View21);        // transfer ownership to CAknViewAppUi

    CAknExEditorView22* View22 = new (ELeave) CAknExEditorView22;
    CleanupStack::PushL(View22);
    View22->ConstructL();
    CleanupStack::Pop();    // view22
    AddViewL(View22);        // transfer ownership to CAknViewAppUi

    CAknExEditorView23* View23 = new (ELeave) CAknExEditorView23;
    CleanupStack::PushL(View23);
    View23->ConstructL();
    CleanupStack::Pop();    // view23
    AddViewL(View23);        // transfer ownership to CAknViewAppUi

    CAknExEditorView25* View25 = new (ELeave) CAknExEditorView25;
    CleanupStack::PushL(View25);
    View25->ConstructL();
    CleanupStack::Pop();    // view25
    AddViewL(View25);        // transfer ownership to CAknViewAppUi

    CAknExEditorView30* View30 = new (ELeave) CAknExEditorView30;
    CleanupStack::PushL(View30);
    View30->ConstructL();
    CleanupStack::Pop();    // view30
    AddViewL(View30); 

    CAknExEditorView33* View33 = new (ELeave) CAknExEditorView33;
    CleanupStack::PushL(View33);
    View33->ConstructL();
    CleanupStack::Pop();    // view33
    AddViewL(View33);

    ActivateViewL(view1->Id());
    }

// Destructor
CAknExEditorAppUi::~CAknExEditorAppUi()
    {
    delete iDecoratedTabGroup;
    delete iScenarioManager;
//  delete iAppContainer;
    }

// ----------------------------------------------------------------------------
// CAknExEditorAppUi::DynInitMenuPaneL
//                                  (TInt aResourceId,CEikMenuPane* aMenuPane)
//  This function is called by the EIKON framework just before it displays
//  a menu pane. Its default implementation is empty, and by overriding it,
//  the application can set the state of menu items dynamically according
//  to the state of application data.
// ----------------------------------------------------------------------------
void CAknExEditorAppUi::DynInitMenuPaneL(
    TInt /*aResourceId*/,CEikMenuPane* /*aMenuPane*/)
    {
    }

// ----------------------------------------------------
// CAknExEditorAppUi::HandleCommandL(TInt aCommand)
// takes care of command handling.
// ----------------------------------------------------
//
void CAknExEditorAppUi::HandleCommandL(TInt aCommand)
    {
    switch (aCommand)
        {
        case EAknCmdExit:
        case EEikCmdExit:   // Exit application
            Exit();
            break;

        case EAknExEditorCmdNext:
            ActivateNextViewL();
            break;

        case EAknExEditorCmdPrev:
            ActivatePrevViewL();
            break;

        default:
            break;
        }
    }

// ----------------------------------------------------
// CAknExEditorAppUi::HandleKeyEventL
// Handles key events.
// (other items were commented in a header).
// ----------------------------------------------------
//
TKeyResponse CAknExEditorAppUi::HandleKeyEventL(
    const TKeyEvent& /*aKeyEvent*/,TEventCode /*aType*/)
    {
    return EKeyWasNotConsumed;
    }

// ----------------------------------------------------
// CAknExEditorAppUi::ActivateNextViewL
// Activates next view.
// (other items were commented in a header).
// ----------------------------------------------------
//
void CAknExEditorAppUi::ActivateNextViewL()
    {
    TUid viewId = iScenarioManager->NextViewTo(iCurrentViewId);
    if (viewId == TUid::Uid(KScenarioNotFound))
        {
        viewId = iScenarioManager->FirstViewId();
        }
    ActivateViewL(viewId);
    }

// ----------------------------------------------------
// CAknExEditorAppUi::ActivatePrevViewL
// Activates previous view.
// (other items were commented in a header).
// ----------------------------------------------------
//
void CAknExEditorAppUi::ActivatePrevViewL()
    {
    TUid viewId = iScenarioManager->PrevViewTo(iCurrentViewId);
    if (viewId == TUid::Uid(KScenarioNotFound))
        {
        viewId = iScenarioManager->LastViewId();
        }
    ActivateViewL(viewId);
    }

// ----------------------------------------------------
// CAknExEditorAppUi::ActivatePrevViewL
// Activates specified view and shows title.
// (other items were commented in a header).
// ----------------------------------------------------
//
void CAknExEditorAppUi::ActivateViewL(TUid aViewId)
    {
    ActivateLocalViewL(aViewId);
    iCurrentViewId = aViewId;

    TBuf<KTitleBufLength> newTitle;
    iScenarioManager->GetTitle(aViewId, &newTitle);
    iTitlePane->SetTextL(newTitle);
    }
// End of File  
