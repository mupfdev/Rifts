/*
* ============================================================================
*  Name     : CAknExMenuOkView from CAknView
*  Part of  : AknExMenu
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include <eikmenub.h>
#include <aknviewappui.h>
#include <avkon.hrh>

#include <AknExMenu.rsg>
#include "AknExMenuOkView.h"
#include "AknExMenuOkContainer.h" 
#include "AknExMenu.hrh"
#include "AknExMenuappui.h"

// ================= MEMBER FUNCTIONS =======================

// EPOC default constructor can leave.
void CAknExMenuOkView::ConstructL(TInt aResId)
    {
    BaseConstructL(aResId);
    iCoeEnv->ReadResource(iUpperMsg, R_AKNEXMENU_OK_UP_TEXT);
    iCoeEnv->ReadResource(iLowerMsg, R_AKNEXMENU_OK_LOW_TEXT);
    iCoeEnv->ReadResource(iTitleMsg, R_AKNEXMENU_OK_TITLE);
    }

// Destructor
CAknExMenuOkView::~CAknExMenuOkView()
    {
    if (iContainer)
        {
        AppUi()->RemoveFromStack(iContainer);
        }

    delete iContainer;
    }

// ---------------------------------------------------------
// TUid CAknExMenuOkView::Id()
// return Uid
// ---------------------------------------------------------
TUid CAknExMenuOkView::Id() const
    {
    return KOkViewId;
    }


// ---------------------------------------------------------
// CAknExMenuOkView::HandleCommandL(TInt aCommand)
// takes care of command handling.
// ---------------------------------------------------------
void CAknExMenuOkView::HandleCommandL(TInt aCommand)
    {
    TBuf<KLengthOfMsgStringInOkView> message;

    switch (aCommand)
        {
        case EAknExMenuCmdOkMenuItem1:
            iCoeEnv->ReadResource(message, R_AKNEXMENU_OK_MENU_ITEM1);
            iEikonEnv->AlertWin(message);
            break;
        
        case EAknExMenuCmdOkMenuItem2:
            iCoeEnv->ReadResource(message, R_AKNEXMENU_OK_MENU_ITEM2);
            iEikonEnv->AlertWin(message);
            break;

        case EAknSoftkeyBack:
            {
            AppUi()->HandleCommandL(EAknCmdExit);
            break;
            }
        default:
            {
            AppUi()->HandleCommandL(aCommand);
            }
        }
    }


// ---------------------------------------------------------
// CAknExMenuOkView::DoActivateL(...)
// activate an AknView
// ---------------------------------------------------------
void CAknExMenuOkView::DoActivateL(const TVwsViewId& /*aPrevViewId*/,TUid /*aCustomMessageId*/,const TDesC8& /*aCustomMessage*/)
    {
    iContainer = new(ELeave) CAknExMenuOkContainer;
    iContainer->SetMopParent(this);
    iContainer->ConstructL(ClientRect(), this);
    STATIC_CAST(CAknExMenuAppUi*, AppUi())->iTitlePane->SetTextL(iTitleMsg);

    AppUi()->AddToStackL(*this, iContainer);
   }

// ---------------------------------------------------------
// CAknExMenuOkView::HandleCommandL(TInt aCommand)
// deactivate an AknView
// ---------------------------------------------------------
void CAknExMenuOkView::DoDeactivate()
    {
    if (iContainer)
        {
        AppUi()->RemoveFromStack(iContainer);
        }
    
    delete iContainer;
    iContainer = NULL;
    }

// End of File

