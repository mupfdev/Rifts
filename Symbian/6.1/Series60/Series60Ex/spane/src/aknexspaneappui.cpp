/* 
* ============================================================================
*  Name     : CAknExSpaneAppUi from CAknViewAppUi
*  Part of  : AknExSpane
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES

#include <eikspane.h>
#include <e32std.h>
#include <avkon.hrh>
#include <barsread.h>
#include <akntitle.h>
#include <aknnavi.h>
#include <akncontext.h>
#include <avkon.rsg>

#include <AknExSpane.rsg>
#include "AknExSpane.hrh"
#include "AknExSpaneAppUi.h"
#include "AknExSpaneContextView.h"
#include "AknExSpaneContextViewContainer.h" 
#include "AknExSpaneNaviView.h"
#include "AknExSpaneNaviViewContainer.h" 
#include "AknExSpanePopupView.h"
#include "AknExSpanePopupViewContainer.h" 
#include "AknExSpaneTitleView.h"
#include "AknExSpaneTitleViewContainer.h" 

// ================= MEMBER FUNCTIONS =======================

// C++ default constructor can NOT contain any code, that
// might leave.
//
CAknExSpaneAppUi::CAknExSpaneAppUi() :
    iLayout(EFalse),
    iVisible(ETrue),
    iNaviPane(NULL),
    iTabGroup(NULL),
    iDecoratedTabGroup(NULL)
    {
    }

// EPOC default constructor can leave.
void CAknExSpaneAppUi::ConstructL()
    {
    BaseConstructL();
  
    CAknExSpaneTitleView* titleView = new(ELeave) CAknExSpaneTitleView;
    CleanupStack::PushL(titleView);
    titleView->ConstructL();
    CleanupStack::Pop();    // titleView
    AddViewL(titleView);    // transfer ownership to CAknViewAppUi
    
    CAknExSpaneContextView* contextView = new(ELeave) CAknExSpaneContextView;
    CleanupStack::PushL(contextView);
    contextView->ConstructL();
    CleanupStack::Pop();    // contextView
    AddViewL(contextView);  // transfer ownership to CAknViewAppUi
    
    CAknExSpaneNaviView* naviView = new(ELeave) CAknExSpaneNaviView;
    CleanupStack::PushL(naviView);
    naviView->ConstructL();
    CleanupStack::Pop();    // naviView
    AddViewL(naviView);     // transfer ownership to CAknViewAppUi
    
    CAknExSpanePopupView* popupView = new(ELeave) CAknExSpanePopupView;
    CleanupStack::PushL(popupView);
    popupView->ConstructL();
    CleanupStack::Pop();    // popupView
    AddViewL(popupView);    // transfer ownership to CAknViewAppUi
    
    // Show tabs for main views from resources
    CEikStatusPane* sp = StatusPane();
    iNaviPane = (CAknNavigationControlContainer *)sp->ControlL(TUid::Uid(EEikStatusPaneUidNavi));
    sp->SetDimmed(ETrue);

    // Tabgroup has been read from resource and it were pushed to the navi pane. 
    // Get pointer to the navigation decorator with the ResourceDecorator() function. 
    // Application owns the decorator and it has responsibility to delete the object.
    iDecoratedTabGroup = iNaviPane->ResourceDecorator();

    if (iDecoratedTabGroup)
        {
        iTabGroup = (CAknTabGroup*) iDecoratedTabGroup->DecoratedControl();
        }

    if (iTabGroup)
        {
        ActivateLocalViewL(TUid::Uid(iTabGroup->ActiveTabId()));
        }
    else  // just in case
        {
        ActivateLocalViewL(titleView->Id());
        }

    }

// Destructor
CAknExSpaneAppUi::~CAknExSpaneAppUi()
    {
    delete iDecoratedTabGroup;
    }

// ------------------------------------------------------------------------------
// CAknExSpaneAppUi::DynInitMenuPaneL(TInt aResourceId,CEikMenuPane* aMenuPane)
//  This function is called by the EIKON framework just before it displays
//  a menu pane. Its default implementation is empty, and by overriding it,
//  the application can set the state of menu items dynamically according
//  to the state of application data.
//
// ------------------------------------------------------------------------------
void CAknExSpaneAppUi::DynInitMenuPaneL(
    TInt /*aResourceId*/, CEikMenuPane* /*aMenuPane*/)
    {
    }

// ----------------------------------------------------
// CAknExSpaneAppUi::HandleKeyEventL(
//     const TKeyEvent& aKeyEvent,TEventCode /*aType*/)
// handle key events
// ----------------------------------------------------
TKeyResponse CAknExSpaneAppUi::HandleKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
    {
    if (aType == EEventKey)
        {
        
        if (iTabGroup == NULL)
            {
            return EKeyWasNotConsumed;
            }
        
        TInt active = iTabGroup->ActiveTabIndex();
        TInt count = iTabGroup->TabCount();
        
        switch (aKeyEvent.iCode)
            {
            case EKeySpace:
                ProcessCommandL(EAknExSpaneCmdNextTest);
                return EKeyWasConsumed;

            case EKeyLeftArrow:
                if (active > 0)
                    {
                     // Change to usual layout
                    TRect cr = ClientRect();  
                    if (cr.iTl.iY == Kqpn_height_status_pane_idle)
                        {
                        StatusPane()->SwitchLayoutL(R_AVKON_STATUS_PANE_LAYOUT_USUAL);
                        iLayout = !iLayout;
                        }

                    active--;
                    iTabGroup->SetActiveTabByIndex(active);
                    ActivateLocalViewL(TUid::Uid(iTabGroup->TabIdFromIndex(active)));
                    return EKeyWasConsumed;
                    }
                break;

            case EKeyRightArrow:
                if((active + 1) < count)
                    {
                    TRect cr = ClientRect();  
                    if (cr.iTl.iY == Kqpn_height_status_pane_idle)
                        {
                        StatusPane()->SwitchLayoutL(R_AVKON_STATUS_PANE_LAYOUT_USUAL);
                        iLayout = !iLayout;
                        }

                    active++;
                    iTabGroup->SetActiveTabByIndex(active);
                    ActivateLocalViewL(TUid::Uid(iTabGroup->TabIdFromIndex(active)));
                    return EKeyWasConsumed;
                    }
                break;

            default:
                break;
            }        
        }

    return EKeyWasNotConsumed;
    }
// ----------------------------------------------------
// CAknExSpaneAppUi::HandleCommandL(TInt aCommand)
// handles the commands
// ----------------------------------------------------
void CAknExSpaneAppUi::HandleCommandL(TInt aCommand)
    {
    switch (aCommand)
        {
        case EAknSoftkeyBack:
        case EEikCmdExit:   // EEikCmdExit and EAknSoftkeyBack have same functionality
        case EAknCmdExit:
            {
            Exit();
            break;
            }

        case EAknExSpaneCmdSwitchSpLayout:
            {
            if (iLayout)
                {
                StatusPane()->SwitchLayoutL(R_AVKON_STATUS_PANE_LAYOUT_USUAL);
                }
            else
                {
                StatusPane()->SwitchLayoutL(R_AVKON_STATUS_PANE_LAYOUT_EMPTY);
                StatusPane()->SwitchLayoutL(R_AVKON_STATUS_PANE_LAYOUT_IDLE);
                }

            iLayout = !iLayout;
            break;            
            }

        case EAknExSpaneCmdSwitchSpVisible:
            {
            iVisible = !iVisible;
            StatusPane()->MakeVisible(iVisible);
            break;
            }
        case EAknExSpaneSoftkeyNext:
            ProcessCommandL(EAknExSpaneCmdNextTest);
            break;

        default:
            {
            break;
            }
        }
    }

// End of File  
