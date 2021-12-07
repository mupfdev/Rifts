/*
* ============================================================================
*  Name     : CAknExPopListView10 from CAknView
*  Part of  : AknExPopList
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include  <aknviewappui.h>
#include  <avkon.hrh>

#include <AknPopup.h>
#include <AknLists.h>

#include <BarsRead.h>
//#include <eikon.mbg>
#include <eikdef.h>

#include <GulIcon.h>
#include <EikClbd.h>

#include  "AknExPopList.hrh"
#include  <AknExPopList.rsg>
#include  "AknExPopListView10.h"
#include  "AknExPopListContainer.h" 

// ================= MEMBER FUNCTIONS =======================

// ---------------------------------------------------------
// CAknExPopListView10::ConstructL(const TRect& aRect)
// EPOC two-phased constructor
// ---------------------------------------------------------
void CAknExPopListView10::ConstructL()
    {
    BaseConstructL(R_AKNEXPOPLIST_VIEW10);
    }

// ---------------------------------------------------------
// CAknExPopListView10::~CAknExPopListView10()
// Destructor
// ---------------------------------------------------------
CAknExPopListView10::~CAknExPopListView10()
    {
    if (iContainer)
        {
        AppUi()->RemoveFromStack(iContainer);
        }
    delete iContainer;

    }

// ---------------------------------------------------------
// TUid CAknExPopListView10::Id()
// returns view id
// ---------------------------------------------------------
TUid CAknExPopListView10::Id() const
    {
    return KView10Id;
    }

// ---------------------------------------------------------
// CAknExPopListView10::HandleCommandL(TInt aCommand)
// handles commands to be handled.
// ---------------------------------------------------------
void CAknExPopListView10::HandleCommandL(TInt aCommand)
    {   
    switch (aCommand)
        {
        case EAknSoftkeyBack:
            AppUi()->HandleCommandL(EAknCmdExit);
            break;

        default:
            AppUi()->HandleCommandL(aCommand);
            break;
        }
    }

// ---------------------------------------------------------
// CAknExPopListView10::HandleClientRectChange()
// 
// ---------------------------------------------------------
void CAknExPopListView10::HandleClientRectChange()
    {
    if (iContainer)
        {
        iContainer->SetRect(ClientRect());
        }
    }

// ---------------------------------------------------------
// CAknExPopListView10::DoActivateL(...)
// 
// ---------------------------------------------------------
void CAknExPopListView10::DoActivateL(
   const TVwsViewId& /*aPrevViewId*/,TUid /*aCustomMessageId*/,
   const TDesC8& /*aCustomMessage*/)
    {
    iContainer = new(ELeave) CAknExPopListContainer;
    iContainer->SetMopParent(this);
    iContainer->ConstructL(ClientRect());
    AppUi()->AddToStackL(*this, iContainer);
   }

// ---------------------------------------------------------
// CAknExPopListView10::HandleCommandL(TInt aCommand)
// 
// ---------------------------------------------------------
void CAknExPopListView10::DoDeactivate()
    {
    if (iContainer)
        {
        AppUi()->RemoveFromStack(iContainer);
        }
    
    delete iContainer;
    iContainer = NULL;
    }

// End of File