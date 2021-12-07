/*
* =============================================================================
*  Name     : AknExListSetPageContainer.cpp
*  Part of  : AknExList
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

// INCLUDE FILES
#include "AknExListSetPageContainer.h" 
#include "AknExListSetPage.h"
#include "AknExListSetPageView.h"

// CONSTANTS

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExListSetPageContainer::NewL
// 2-phase constructor.
// ----------------------------------------------------------------------------
//
CAknExListSetPageContainer* CAknExListSetPageContainer::NewL(
                            CAknExListSetPageView* aView)
    {
    CAknExListSetPageContainer* self = 
        new (ELeave) CAknExListSetPageContainer();
    CleanupStack::PushL(self);
    self->ConstructL(aView);
    CleanupStack::Pop();
    return self;
    }

// ----------------------------------------------------------------------------
// CAknExListSetPageContainer::~CAknExListSetPageContainer
// Destructor.
// ----------------------------------------------------------------------------
//
CAknExListSetPageContainer::~CAknExListSetPageContainer()
    {
    delete iSetPage; 
    }

// ----------------------------------------------------------------------------
// CAknExListSetPageContainer::TryDisplaySetPageL
// Try to display setting page.
// ----------------------------------------------------------------------------
//
void CAknExListSetPageContainer::TryDisplaySetPageL(
     TInt aResourceId)
    {
    delete iSetPage;
    iSetPage = NULL;
    
    iSetPage = CAknExListSetPage::NewL(aResourceId);
    
    if (iSetPage)
        {
        iSetPage->SetMopParent(this);
        SizeChanged();
        iSetPage->ActivateL();
        }
    DrawNow();
    }

// ----------------------------------------------------------------------------
// CAknExListSetPageContainer::ConstructL
// Second-phase constructor.
// ----------------------------------------------------------------------------
//
void CAknExListSetPageContainer::ConstructL(
     CAknExListSetPageView* aView)
    {
    iView = aView;
    }

// ----------------------------------------------------------------------------
// CAknExListSetPageContainer::OfferKeyEventL
// Handling key event.
// ----------------------------------------------------------------------------
//
TKeyResponse CAknExListSetPageContainer::OfferKeyEventL(
            const TKeyEvent& aKeyEvent, TEventCode aType)
    {
    TKeyResponse response(EKeyWasNotConsumed); 

    if (aKeyEvent.iCode == EKeySpace)
        {
        iView->DisplayNextOutlineL();
        response = EKeyWasConsumed;
        }
    else if (iSetPage)
        {
        response = iSetPage->OfferKeyEventL(aKeyEvent, aType); 
        }

    return response;
    }

// End of File