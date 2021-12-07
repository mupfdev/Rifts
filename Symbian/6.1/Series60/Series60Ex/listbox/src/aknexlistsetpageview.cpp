/*
* =============================================================================
*  Name     : AknExListSetPageView.cpp
*  Part of  : AknExList
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

// INCLUDE FILES
#include <AknViewAppUi.h>
#include <AknExList.rsg>

#include "AknExList.hrh"
#include "AknExListSetPageView.h" 
#include "AknExListSetPageContainer.h"

// CONSTANTS

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExListSetPage::NewLC
// 2-phase constructor.
// ----------------------------------------------------------------------------
//
CAknExListSetPageView* CAknExListSetPageView::NewLC()
    {
    CAknExListSetPageView* self = 
        new (ELeave) CAknExListSetPageView();
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

// ----------------------------------------------------------------------------
// CAknExListSetPage::~CAknExListSetPageView
// Destructor.
// ----------------------------------------------------------------------------
//
CAknExListSetPageView::~CAknExListSetPageView()
    {
    if (iContainer)
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    delete iContainer;
    }

// ----------------------------------------------------------------------------
// CAknExListSetPage::Id
// Return view ID.
// ----------------------------------------------------------------------------
//
TUid CAknExListSetPageView::Id() const
    {
    return KAknExListSetPageViewId;
    }

// ----------------------------------------------------------------------------
// CAknExListSetPage::CAknExListSetPageView
// Default constructor.
// ----------------------------------------------------------------------------
//
CAknExListSetPageView::CAknExListSetPageView()
    {
    }

// ----------------------------------------------------------------------------
// CAknExListSetPage::ConstructL
// Second phase constructor
// ----------------------------------------------------------------------------
//
void CAknExListSetPageView::ConstructL()
    {
    BaseConstructL(R_AKNEXLIST_VIEW_SETPAGEVIEW);
    }

// ----------------------------------------------------------------------------
// CAknExListSetPage::SetTitlePaneL
// Change text of title pane.
// ----------------------------------------------------------------------------
//
void CAknExListSetPageView::SetTitlePaneL(const TInt aOutlineId)
    {
    TInt resourceId(KAknExListInitTitleId);

    if (aOutlineId == EAknExListCmdOutline85)
        {
        resourceId = R_AKNEXLIST_OUTLINE85;
        }

    IndicateTitlePaneTextL(resourceId);
    }

// ----------------------------------------------------------------------------
// CAknExListSetPage::DisplayListBoxL
// Display setting page of current outline.
// ----------------------------------------------------------------------------
//
void CAknExListSetPageView::DisplayListBoxL(
     const TInt aOutlineId)
    {
    if (aOutlineId == EAknExListCmdOutline85)
        {
        iContainer->TryDisplaySetPageL(R_AKNEXLIST_EMPTY_ITEM_LIST);
        }
    }

// ----------------------------------------------------------------------------
// CAknExListSetPage::DoActivateL
// Called when view becomes active.
// ----------------------------------------------------------------------------
//
void CAknExListSetPageView::DoActivateL(
            const TVwsViewId& /*aPrevViewId*/,
            TUid /*aCustomMessageId*/,
            const TDesC8& /*aCustomMessage*/)
    {
    if ( !iContainer )
        {
        iContainer = CAknExListSetPageContainer::NewL(this);
        iContainer->SetMopParent(this);
        
        // Adds container to view control stack.
        AppUi()->AddToStackL(*this, iContainer);

        // Displays outline.
        DisplayInitOutlineL();

        iContainer->MakeVisible(ETrue);
        }
    }

// ----------------------------------------------------------------------------
// CAknExListSetPage::DoDeactivate
// Called when view becomes deactive.
// ----------------------------------------------------------------------------
//
void CAknExListSetPageView::DoDeactivate()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    delete iContainer; // Deletes the container class object.
    iContainer = NULL;
    }

// End of File

