/*
* =============================================================================
*  Name     : AknExListSetPage.cpp
*  Part of  : AknExList
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

// INCLUDE FILES
#include <AknExList.rsg>

#include "AknExList.hrh"
#include "AknExListSetPage.h"

// CONSTANTS

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExListSetPage::NewL
// 2-phase constructor.
// ----------------------------------------------------------------------------
//
CAknExListSetPage* CAknExListSetPage::NewL(TInt aResourceId)
    {
    CAknExListSetPage* self = new (ELeave) CAknExListSetPage();
    CleanupStack::PushL(self);
    self->ConstructL(aResourceId);
    CleanupStack::Pop();
    return self;
    }

// ----------------------------------------------------------------------------
// CAknExListSetPage::~CAknExListSetPage
// Deststructor.
// ----------------------------------------------------------------------------
//
CAknExListSetPage::~CAknExListSetPage()
    {
    }

// ----------------------------------------------------------------------------
// CAknExListSetPage::CAknExListSetPage
// Default constructor
// ----------------------------------------------------------------------------
//
CAknExListSetPage::CAknExListSetPage()
    {
    }

// ----------------------------------------------------------------------------
// CAknExListSetPage::ConstructL
// Second phase constructor.
// ----------------------------------------------------------------------------
//
void CAknExListSetPage::ConstructL(TInt aResourceId)
    {
    CAknSettingItemList::ConstructFromResourceL(aResourceId);
    }

// ----------------------------------------------------------------------------
// CAknExListSetPage::CreateSettingItemL
// Create items of the list.
// Called when create setting page.
// ----------------------------------------------------------------------------
//
CAknSettingItem* CAknExListSetPage::CreateSettingItemL(TInt aSettingId)
    {
    CAknSettingItem* settingItem = NULL;

    if (aSettingId == EAknExListEmptyItem)
        {
        settingItem = new (ELeave) CAknEnumeratedTextPopupSettingItem(
            aSettingId, iValue);
        }
    return settingItem;
    }
    
// End of File
