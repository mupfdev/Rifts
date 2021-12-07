/*
* ============================================================================
*  Name     : CAknExPopListView3 from CAknView
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
#include  "AknExPopListView3.h"
#include  "AknExPopListContainer.h" 

// ================= MEMBER FUNCTIONS =======================

// ---------------------------------------------------------
// CAknExPopListView3::ConstructL(const TRect& aRect)
// EPOC two-phased constructor
// ---------------------------------------------------------
void CAknExPopListView3::ConstructL()
    {
    BaseConstructL(R_AKNEXPOPLIST_VIEW3);
    }

// ---------------------------------------------------------
// CAknExPopListView3::~CAknExPopListView3()
// Destructor
// ---------------------------------------------------------
CAknExPopListView3::~CAknExPopListView3()
    {
    if (iContainer)
        {
        AppUi()->RemoveFromStack(iContainer);
        }
    delete iContainer;

    }

// ---------------------------------------------------------
// TUid CAknExPopListView3::Id()
// returns view id
// ---------------------------------------------------------
TUid CAknExPopListView3::Id() const
    {
    return KView3Id;
    }

// ---------------------------------------------------------
// CAknExPopListView3::HandleCommandL(TInt aCommand)
// handles commands to be handled.
// ---------------------------------------------------------
void CAknExPopListView3::HandleCommandL(TInt aCommand)
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
// CAknExPopListView3::HandleClientRectChange()
// 
// ---------------------------------------------------------
void CAknExPopListView3::HandleClientRectChange()
    {
    if (iContainer)
        {
        iContainer->SetRect(ClientRect());
        }
    }

// ---------------------------------------------------------
// CAknExPopListView3::DoActivateL(...)
// 
// ---------------------------------------------------------
void CAknExPopListView3::DoActivateL(
   const TVwsViewId& /*aPrevViewId*/,TUid /*aCustomMessageId*/,
   const TDesC8& /*aCustomMessage*/)
    {
    iContainer = new(ELeave) CAknExPopListContainer;
    iContainer->SetMopParent(this);
    iContainer->ConstructL(ClientRect());
    AppUi()->AddToStackL(*this, iContainer);
   }

// ---------------------------------------------------------
// CAknExPopListView3::HandleCommandL(TInt aCommand)
// 
// ---------------------------------------------------------
void CAknExPopListView3::DoDeactivate()
    {
    if (iContainer)
        {
        AppUi()->RemoveFromStack(iContainer);
        }
    
    delete iContainer;
    iContainer = NULL;
    }

// End of File