/*
* ============================================================================
*  Name     : CAknExMenuSubView from CAknView
*  Part of  : AknExMenu
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include <eikmenub.h>
#include <aknviewappui.h>
#include <avkon.hrh>

#include <AknExMenu.rsg>
#include "AknExMenuSubView.h"
#include "AknExMenuSubContainer.h" 
#include "AknExMenu.hrh"
#include "AknExMenuappui.h"

// ================= MEMBER FUNCTIONS =======================

// EPOC default constructor can leave.
void CAknExMenuSubView::ConstructL(TInt aResId)
    {
    BaseConstructL(aResId);
    iState = EAknExMenuStateLast;
    iCoeEnv->ReadResource(iUpperMsg, R_AKNEXMENU_SUB_UP_TEXT);
    iCoeEnv->ReadResource(iLowerMsg, R_AKNEXMENU_SUB_LOW_TEXT);
    iCoeEnv->ReadResource(iTitleMsg, R_AKNEXMENU_SUB_TITLE);
    }

// Destructor
CAknExMenuSubView::~CAknExMenuSubView()
    {
    if (iContainer)
        {
        AppUi()->RemoveFromStack(iContainer);
        }

    delete iContainer;
    }

// ---------------------------------------------------------
// TUid CAknExMenuSubView::Id()
// return Uid
// ---------------------------------------------------------
TUid CAknExMenuSubView::Id() const
    {
    return KSubViewId;
    }

// ---------------------------------------------------------
// CAknExMenuSubView::HandleCommandL(TInt aCommand)
// takes care of command handling.
// ---------------------------------------------------------
void CAknExMenuSubView::HandleCommandL(TInt aCommand)
    {   
    TBuf< KLengthOfMsgStringInSubView > msgFormat;
    TBuf< KLengthOfMsgStringInSubView > msgString;
    iCoeEnv->ReadResource( msgFormat, R_AKNEXMENU_MESSAGE_FORMAT );
    //iEikonEnv->InfoMsgWithDuration(msgString, (TTimeIntervalMicroSeconds32) KMsgDisplayTimeInSubView);
    msgString.Format(msgFormat, aCommand);
    iEikonEnv->AlertWin(msgString);

    switch (aCommand)
        {
        case EAknExMenuCmdSubMoreItems:
            {
            iState = EAknExMenuStateMoreItems;
            break;
            }
        case EAknExMenuCmdSubLessItems:
            {
            iState = EAknExMenuStateLessItems;
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
// CAknExMenuSubView::DynInitMenuPaneL(TInt aResourceId,CEikMenuPane* aMenuPane)
//  This function is called by the EIKON framework just before it displays
//  a menu pane. Its default implementation is empty, and by overriding it,
//  the application can set the state of menu items dynamically according
//  to the state of application data.
//
// ------------------------------------------------------------------------------
void CAknExMenuSubView::DynInitMenuPaneL(
    TInt aResourceId,CEikMenuPane* aMenuPane)
    {

    if (R_AKNEXMENU_TEST_SUB_MENU1 == aResourceId)
        {
        if (EAknExMenuStateMoreItems == iState)
            {
            TBuf< KLengthOfMsgStringInSubView > format;
            CEikMenuPaneItem::SData item;

            // read out then new menu text str
            iCoeEnv->ReadResource( format, R_AKNEXMENU_NEW_ITEM );
            
            item.iCommandId = EAknExMenuCmdSub1;
            item.iFlags = 0;
            item.iCascadeId = 0;
            for (TInt i = 1; i <=100; i++)
                {
                // add 100 items to submenu pane
                item.iText.Format(format, i);
                aMenuPane->AddMenuItemL(item,EAknExMenuCmdSubMoreItems);
                }
            }
        }

    if (EAknExMenuStateLessItems == iState)
        {
        iState = EAknExMenuStateLast;
        }

    if (EAknExMenuStateLast == iState)
        {
        return;
        }

    }


// ---------------------------------------------------------
// CAknExMenuSubView::DoActivateL(...)
// activate an AknView
// ---------------------------------------------------------
void CAknExMenuSubView::DoActivateL(const TVwsViewId& /*aPrevViewId*/,TUid /*aCustomMessageId*/,const TDesC8& /*aCustomMessage*/)
    {
    iContainer = new(ELeave) CAknExMenuSubContainer;
    iContainer->SetMopParent(this);
    iContainer->ConstructL(ClientRect(), this);
    STATIC_CAST(CAknExMenuAppUi*, AppUi())->iTitlePane->SetTextL(iTitleMsg);

    AppUi()->AddToStackL(*this, iContainer);
   }

// ---------------------------------------------------------
// CAknExMenuSubView::HandleCommandL(TInt aCommand)
// deactivate an AknView
// ---------------------------------------------------------
void CAknExMenuSubView::DoDeactivate()
    {
    if (iContainer)
        {
        AppUi()->RemoveFromStack(iContainer);
        }
    
    delete iContainer;
    iContainer = NULL;
    }

// End of File

