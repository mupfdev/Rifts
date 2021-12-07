/*
* ============================================================================
*  Name     : CAknExPopListView8 from CAknView
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
#include  "AknExPopListView8.h"
#include  "AknExPopListContainer.h" 

// ================= MEMBER FUNCTIONS =======================

// ---------------------------------------------------------
// CAknExPopListView8::ConstructL(const TRect& aRect)
// EPOC two-phased constructor
// ---------------------------------------------------------
void CAknExPopListView8::ConstructL()
    {
    BaseConstructL(R_AKNEXPOPLIST_VIEW8);
    }

// ---------------------------------------------------------
// CAknExPopListView8::~CAknExPopListView8()
// Destructor
// ---------------------------------------------------------
CAknExPopListView8::~CAknExPopListView8()
    {
    if (iContainer)
        {
        AppUi()->RemoveFromStack(iContainer);
        }
    delete iContainer;

    }

// ---------------------------------------------------------
// TUid CAknExPopListView8::Id()
// returns view id
// ---------------------------------------------------------
TUid CAknExPopListView8::Id() const
    {
    return KView8Id;
    }

// ---------------------------------------------------------
// CAknExPopListView8::HandleCommandL(TInt aCommand)
// handles commands to be handled.
// ---------------------------------------------------------
void CAknExPopListView8::HandleCommandL(TInt aCommand)
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
// CAknExPopListView8::HandleClientRectChange()
// 
// ---------------------------------------------------------
void CAknExPopListView8::HandleClientRectChange()
    {
    if (iContainer)
        {
        iContainer->SetRect(ClientRect());
        }
    }

// ---------------------------------------------------------
// CAknExPopListView8::DoActivateL(...)
// 
// ---------------------------------------------------------
void CAknExPopListView8::DoActivateL(
   const TVwsViewId& /*aPrevViewId*/,TUid /*aCustomMessageId*/,
   const TDesC8& /*aCustomMessage*/)
    {
    iContainer = new(ELeave) CAknExPopListContainer;
    iContainer->SetMopParent(this);
    iContainer->ConstructL(ClientRect());
    AppUi()->AddToStackL(*this, iContainer);
   }

// ---------------------------------------------------------
// CAknExPopListView8::HandleCommandL(TInt aCommand)
// 
// ---------------------------------------------------------
void CAknExPopListView8::DoDeactivate()
    {
    if (iContainer)
        {
        AppUi()->RemoveFromStack(iContainer);
        }
    
    delete iContainer;
    iContainer = NULL;
    }

// End of File