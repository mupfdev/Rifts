/*
* =============================================================================
*  Name     : CAknExSettingListDocument
*  Part of  : AknExSettingList
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include "AknExSettingListDocument.h"
#include "AknExSettingListAppUi.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExSettingListDocument* CAknExSettingListDocument::NewL( CEikApplication& )
// EPOC two-phased constructor.
// ----------------------------------------------------------------------------
//
CAknExSettingListDocument* CAknExSettingListDocument::NewL( CEikApplication& aApp )
    {
    CAknExSettingListDocument* self = new( ELeave ) CAknExSettingListDocument( aApp );
    return self;
    }

// ----------------------------------------------------------------------------
// CAknExSettingListDocument::~CAknExSettingListDocument()
// Destructor.
// ----------------------------------------------------------------------------
//
CAknExSettingListDocument::~CAknExSettingListDocument()
    {
    }

// ----------------------------------------------------------------------------
// CAknExSettingListDocument::CAknExSettingListDocument( CEikApplication& )
// Overload constructor.
// ----------------------------------------------------------------------------
//
CAknExSettingListDocument::CAknExSettingListDocument( CEikApplication& aApp )
:   CEikDocument( aApp )
    {
    }

// ----------------------------------------------------------------------------
// CEikAppUi* CAknExSettingListDocument::CreateAppUiL()
// Constructs CAknExSettingListAppUi.
// ----------------------------------------------------------------------------
//
CEikAppUi* CAknExSettingListDocument::CreateAppUiL()
    {
    return new( ELeave ) CAknExSettingListAppUi;
    }

// End of File
