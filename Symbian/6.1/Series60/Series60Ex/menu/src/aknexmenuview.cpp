/*
* ============================================================================
*  Name     : CAknExMenuView from CAknView
*  Part of  : AknExMenu
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include <eiklabel.h>  // for example label control
#include <eikmenub.h>
#include <aknviewappui.h>
#include <avkon.hrh>

#include <AknExMenu.rsg>
#include "AknExMenuView.h"
#include "AknExMenuContainer.h" 
#include "AknExMenu.hrh"
#include "AknExMenuappui.h"

// ================= MEMBER FUNCTIONS =======================

// EPOC default constructor can leave.
void CAknExMenuView::ConstructL(TInt aResId)
    {
    BaseConstructL(aResId);
    iState = EAknExMenuStateLast;
    iCoeEnv->ReadResource(iUpperMsg, R_AKNEXMENU_NO_SUB_UP_TEXT);
    iCoeEnv->ReadResource(iLowerMsg, R_AKNEXMENU_NO_SUB_LOW_TEXT);
    iCoeEnv->ReadResource(iTitleMsg, R_AKNEXMENU_NO_SUB_TITLE);
    }

// Destructor
CAknExMenuView::~CAknExMenuView()
    {
    if (iContainer)
        {
        AppUi()->RemoveFromStack(iContainer);
        }

    delete iContainer;
    }

// ---------------------------------------------------------
// TUid CAknExMenuView::Id()
// return Uid
// ---------------------------------------------------------
TUid CAknExMenuView::Id() const
    {
    return KViewId;
    }

// ---------------------------------------------------------
// CAknExMenuView::HandleCommandL(TInt aCommand)
// takes care of command handling.
// ---------------------------------------------------------
void CAknExMenuView::HandleCommandL(TInt aCommand)
    {   

    TBuf< KLengthOfMsgStringInView > msgString;
    TBuf< KLengthOfMsgStringInView > msgFormat;
    iCoeEnv->ReadResource( msgFormat, R_AKNEXMENU_MESSAGE_FORMAT );
    //iEikonEnv->InfoMsgWithDuration(msgString, (TTimeIntervalMicroSeconds32) KMsgDisplayTimeInView);
    msgString.Format(msgFormat, aCommand);
    iEikonEnv->AlertWin(msgString);

    switch (aCommand)
        {
        case EAknExMenuCtxCmd1:
            {
            if (EAknExMenuStateDim1 == iState)
                {
                iState = EAknExMenuStateDim2;
                }
            else if (EAknExMenuStateDim2 == iState)
                {
                iState = EAknExMenuStateLast;
                }
            else
                {
                iState = EAknExMenuStateDim1;
                }
            break;
            }
        case EAknExMenuCtxCmd2:
            {
            if (EAknExMenuStateLast == iState)
                {
                iState = EAknExMenuStateNo;
                }
            break;
            }
        case EAknExMenuCtxCmd3:
            {
            if (EAknExMenuStateNo == iState)
                {
                iState = EAknExMenuStateLast;
                }
            break;
            }
        case EAknSoftkeyBack:
            {
            AppUi()->HandleCommandL(EAknCmdExit);
            break;
            }
        default:
            {
            AppUi()->HandleCommandL(aCommand);
            break;
            }
        }
    }

// ------------------------------------------------------------------------------
// CAknExMenuView::DynInitMenuPaneL(TInt aResourceId,CEikMenuPane* aMenuPane)
//  This function is called by the EIKON framework just before it displays
//  a menu pane. Its default implementation is empty, and by overriding it,
//  the application can set the state of menu items dynamically according
//  to the state of application data.
//
// ------------------------------------------------------------------------------
void CAknExMenuView::DynInitMenuPaneL(
    TInt aResourceId,CEikMenuPane* aMenuPane)
    {
    if (R_AKNEXMENU_NO_SUB_STATE_MENU == aResourceId)
        {
        if (EAknExMenuStateNo == iState)
            {
            aMenuPane->DeleteMenuItem(EAknExMenuStateCmd1);
            aMenuPane->DeleteMenuItem(EAknExMenuStateCmd2);
            }
        }
    if (R_AKNEXMENU_NO_SUB_APP_MENU == aResourceId)
        {
        if (EAknExMenuStateDim1 == iState)
            {
            aMenuPane->SetItemDimmed(EAknExMenuAppCmd1, ETrue);
            aMenuPane->SetItemDimmed(EAknExMenuAppCmd2, EFalse);
            }
        if (EAknExMenuStateDim2 == iState)
            {
            aMenuPane->SetItemDimmed(EAknExMenuAppCmd1, EFalse);
            aMenuPane->SetItemDimmed(EAknExMenuAppCmd2, ETrue);
            }
        }
    if (R_AKNEXMENU_NO_SUB_CONTEXT_MENU == aResourceId)
        {
        if (EAknExMenuStateLast == iState)
            {
            aMenuPane->DeleteMenuItem(EAknExMenuCtxCmd3);
            }
        if (EAknExMenuStateNo == iState)
            {
            aMenuPane->DeleteMenuItem(EAknExMenuCtxCmd1);
            aMenuPane->DeleteMenuItem(EAknExMenuCtxCmd2);
            }
        if (EAknExMenuStateDim1 == iState || EAknExMenuStateDim2 == iState)
            {
            aMenuPane->DeleteMenuItem(EAknExMenuCtxCmd2);
            aMenuPane->DeleteMenuItem(EAknExMenuCtxCmd3);
            }
        }
            
    }

// ---------------------------------------------------------
// CAknExMenuView::DoActivateL(...)
// activate an AknView
// ---------------------------------------------------------
void CAknExMenuView::DoActivateL(const TVwsViewId& /*aPrevViewId*/,TUid /*aCustomMessageId*/,const TDesC8& /*aCustomMessage*/)
    {
    iContainer = new(ELeave) CAknExMenuContainer;
    iContainer->SetMopParent(this);
    iContainer->ConstructL(ClientRect(), this);
    STATIC_CAST(CAknExMenuAppUi*, AppUi())->iTitlePane->SetTextL(iTitleMsg);
    AppUi()->AddToStackL(*this, iContainer);
    }

// ---------------------------------------------------------
// CAknExMenuView::DoDeactivate(TInt aCommand)
// deactivate an AknView
// ---------------------------------------------------------
void CAknExMenuView::DoDeactivate()
    {
    if (iContainer)
        {
        AppUi()->RemoveFromStack(iContainer);
        }
    
    delete iContainer;
    iContainer = NULL;
    }

// End of File

