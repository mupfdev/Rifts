/*
* ============================================================================
*  Name     : CAknExPopListView4 from CAknView
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
#include  "AknExPopListView4.h"
#include  "AknExPopListContainer.h" 

// ================= MEMBER FUNCTIONS =======================

// ---------------------------------------------------------
// CAknExPopListView4::ConstructL(const TRect& aRect)
// EPOC two-phased constructor
// ---------------------------------------------------------
void CAknExPopListView4::ConstructL()
    {
    BaseConstructL(R_AKNEXPOPLIST_VIEW4);
    }

// ---------------------------------------------------------
// CAknExPopListView4::~CAknExPopListView4()
// Destructor
// ---------------------------------------------------------
CAknExPopListView4::~CAknExPopListView4()
    {
    if (iContainer)
        {
        AppUi()->RemoveFromStack(iContainer);
        }
    delete iContainer;

    }

// ---------------------------------------------------------
// TUid CAknExPopListView4::Id()
// returns view id
// ---------------------------------------------------------
TUid CAknExPopListView4::Id() const
    {
    return KView4Id;
    }

// ---------------------------------------------------------
// CAknExPopListView4::HandleCommandL(TInt aCommand)
// handles commands to be handled.
// ---------------------------------------------------------
void CAknExPopListView4::HandleCommandL(TInt aCommand)
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
// CAknExPopListView4::HandleClientRectChange()
// 
// ---------------------------------------------------------
void CAknExPopListView4::HandleClientRectChange()
    {
    if (iContainer)
        {
        iContainer->SetRect(ClientRect());
        }
    }

// ---------------------------------------------------------
// CAknExPopListView4::DoActivateL(...)
// 
// ---------------------------------------------------------
void CAknExPopListView4::DoActivateL(
   const TVwsViewId& /*aPrevViewId*/,TUid /*aCustomMessageId*/,
   const TDesC8& /*aCustomMessage*/)
    {
    iContainer = new(ELeave) CAknExPopListContainer;
    iContainer->SetMopParent(this);
    iContainer->ConstructL(ClientRect());
    AppUi()->AddToStackL(*this, iContainer);
   }

// ---------------------------------------------------------
// CAknExPopListView4::HandleCommandL(TInt aCommand)
// 
// ---------------------------------------------------------
void CAknExPopListView4::DoDeactivate()
    {
    if (iContainer)
        {
        AppUi()->RemoveFromStack(iContainer);
        }
    
    delete iContainer;
    iContainer = NULL;
    }

// End of File