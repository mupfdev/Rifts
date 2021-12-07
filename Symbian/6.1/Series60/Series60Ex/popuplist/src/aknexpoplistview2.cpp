/*
* ============================================================================
*  Name     : CAknExPopListView2 from CAknView
*  Part of  : AknExPopList
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include  <aknviewappui.h>
#include  <avkon.hrh>

#include <AknPopup.h>
#include <AknLists.h>
#include <AknNoteDialog.h>
#include <BarsRead.h>
//#include <eikon.mbg>
#include <eikdef.h>

#include <GulIcon.h>
#include <EikClbd.h>

#include  "AknExPopList.hrh"
#include  <AknExPopList.rsg>
#include  "AknExPopListView2.h"
#include  "AknExPopListContainer.h" 

const TInt KMessageLength = 64;

// ================= MEMBER FUNCTIONS =======================

// ---------------------------------------------------------
// CAknExPopListView2::ConstructL(const TRect& aRect)
// EPOC two-phased constructor
// ---------------------------------------------------------
void CAknExPopListView2::ConstructL()
    {
    BaseConstructL(R_AKNEXPOPLIST_VIEW2);
    }

// ---------------------------------------------------------
// CAknExPopListView2::~CAknExPopListView2()
// Destructor
// ---------------------------------------------------------
CAknExPopListView2::~CAknExPopListView2()
    {
    if (iContainer)
        {
        AppUi()->RemoveFromStack(iContainer);
        }
    delete iContainer;

    }

// ---------------------------------------------------------
// TUid CAknExPopListview2::Id()
// returns view id
// ---------------------------------------------------------
TUid CAknExPopListView2::Id() const
    {
    return KView2Id;
    }

// ---------------------------------------------------------
// CAknExPopListview2::HandleCommandL(TInt aCommand)
// handles commands to be handled.
// ---------------------------------------------------------
void CAknExPopListView2::HandleCommandL(TInt aCommand)
    {   
    switch (aCommand)
        {
        case EAknSoftkeyBack:
            AppUi()->HandleCommandL(EAknCmdExit);
            break;

        case EAknExPopListCmdView2Menu1:
        case EAknExPopListCmdView2Menu2:
        case EAknExPopListCmdView2Menu3:
        case EAknExPopListCmdView2Menu4:
        case EAknExPopListCmdView2Menu5:
        case EAknExPopListCmdView2Menu6:
        case EAknExPopListCmdView2Menu7:
        case EAknExPopListCmdView2Menu8:
        case EAknExPopListCmdView2Menu9:
        case EAknExPopListCmdView2Menu10:
        case EAknExPopListCmdView2Menu11:
        case EAknExPopListCmdView2Menu12:
        case EAknExPopListCmdView2Menu13:
        case EAknExPopListCmdView2Menu14:
        case EAknExPopListCmdView2Menu15:
        case EAknExPopListCmdView2Menu16:
        case EAknExPopListCmdView2Menu17:
            {
            TBuf<KMessageLength> format;
            TBuf<KMessageLength> msg;
            iCoeEnv->ReadResource(format, R_AKNEXPOPLIST_SELECT_MESSAGE);
            msg.Format(format, aCommand - EAknExPopListCmdView2Menu1 + 1);
            CAknNoteDialog* dlg = new( ELeave ) CAknNoteDialog( 
                CAknNoteDialog::ENoTone, CAknNoteDialog::ENoTimeout);
            dlg->PrepareLC( R_AKNEXPOPLIST_SELECT_MESSAGE_NOTE );
            dlg->SetTextPluralityL( EFalse );
            dlg->SetTextL( msg );
            dlg->RunLD();
            break;
            }


        case EAknExPopListCmdCascade1:
        case EAknExPopListCmdCascade2:
        case EAknExPopListCmdCascade3:
        case EAknExPopListCmdCascade4:
        case EAknExPopListCmdCascade5:
        case EAknExPopListCmdCascade6:
        case EAknExPopListCmdCascade7:
        case EAknExPopListCmdCascade8:
        case EAknExPopListCmdCascade9:
        case EAknExPopListCmdCascade10:
        case EAknExPopListCmdCascade11:
        case EAknExPopListCmdCascade12:
        case EAknExPopListCmdCascade13:
        case EAknExPopListCmdCascade14:
        case EAknExPopListCmdCascade15:
        case EAknExPopListCmdCascade16:
        case EAknExPopListCmdCascade17:
            {
            TBuf<KMessageLength> format;
            TBuf<KMessageLength> msg;
            iCoeEnv->ReadResource(format, R_AKNEXPOPLIST_SELECT_MESSAGE);
            msg.Format(format, aCommand - EAknExPopListCmdCascade1 + 1);
            CAknNoteDialog* dlg = new( ELeave ) CAknNoteDialog( 
                CAknNoteDialog::ENoTone, CAknNoteDialog::ENoTimeout);
            dlg->PrepareLC( R_AKNEXPOPLIST_SELECT_MESSAGE_NOTE );
            dlg->SetTextPluralityL( EFalse );
            dlg->SetTextL( msg );
            dlg->RunLD();
            break;
            }

        default:
            AppUi()->HandleCommandL(aCommand);
            break;
        }
    }

// ---------------------------------------------------------
// CAknExPopListview2::HandleClientRectChange()
// 
// ---------------------------------------------------------
void CAknExPopListView2::HandleClientRectChange()
    {
    if (iContainer)
        {
        iContainer->SetRect(ClientRect());
        }
    }

// ---------------------------------------------------------
// CAknExPopListview2::DoActivateL(...)
// 
// ---------------------------------------------------------
void CAknExPopListView2::DoActivateL(
   const TVwsViewId& /*aPrevViewId*/,TUid /*aCustomMessageId*/,
   const TDesC8& /*aCustomMessage*/)
    {
    iContainer = new(ELeave) CAknExPopListContainer;
    iContainer->SetMopParent(this);
    iContainer->ConstructL(ClientRect());
    AppUi()->AddToStackL(*this, iContainer);
   }

// ---------------------------------------------------------
// CAknExPopListview2::HandleCommandL(TInt aCommand)
// 
// ---------------------------------------------------------
void CAknExPopListView2::DoDeactivate()
    {
    if (iContainer)
        {
        AppUi()->RemoveFromStack(iContainer);
        }
    
    delete iContainer;
    iContainer = NULL;
    }

// End of File