/*
* ============================================================================
*  Name     : CAknExPopListView11 from CAknView
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
#include  "AknExPopListView11.h"
#include  "AknExPopListContainer.h" 

// ================= MEMBER FUNCTIONS =======================

// ---------------------------------------------------------
// CAknExPopListView11::ConstructL(const TRect& aRect)
// EPOC two-phased constructor
// ---------------------------------------------------------
void CAknExPopListView11::ConstructL()
    {
    BaseConstructL(R_AKNEXPOPLIST_VIEW11);
    }

// ---------------------------------------------------------
// CAknExPopListView11::~CAknExPopListView11()
// Destructor
// ---------------------------------------------------------
CAknExPopListView11::~CAknExPopListView11()
    {
    if (iContainer)
        {
        AppUi()->RemoveFromStack(iContainer);
        }
    delete iContainer;

    }

// ---------------------------------------------------------
// TUid CAknExPopListView11::Id()
// returns view id
// ---------------------------------------------------------
TUid CAknExPopListView11::Id() const
    {
    return KView11Id;
    }

// ---------------------------------------------------------
// CAknExPopListView11::HandleCommandL(TInt aCommand)
// handles commands to be handled.
// ---------------------------------------------------------
void CAknExPopListView11::HandleCommandL(TInt aCommand)
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
// CAknExPopListView11::HandleClientRectChange()
// 
// ---------------------------------------------------------
void CAknExPopListView11::HandleClientRectChange()
    {
    if (iContainer)
        {
        iContainer->SetRect(ClientRect());
        }
    }

// ---------------------------------------------------------
// CAknExPopListView11::DoActivateL(...)
// 
// ---------------------------------------------------------
void CAknExPopListView11::DoActivateL(
   const TVwsViewId& /*aPrevViewId*/,TUid /*aCustomMessageId*/,
   const TDesC8& /*aCustomMessage*/)
    {
    iContainer = new(ELeave) CAknExPopListContainer;
    iContainer->SetMopParent(this);
    iContainer->ConstructL(ClientRect());
    AppUi()->AddToStackL(*this, iContainer);
   }

// ---------------------------------------------------------
// CAknExPopListView11::HandleCommandL(TInt aCommand)
// 
// ---------------------------------------------------------
void CAknExPopListView11::DoDeactivate()
    {
    if (iContainer)
        {
        AppUi()->RemoveFromStack(iContainer);
        }
    
    delete iContainer;
    iContainer = NULL;
    }

// End of File