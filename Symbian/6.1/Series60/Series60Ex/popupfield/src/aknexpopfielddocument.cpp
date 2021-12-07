/*
* =============================================================================
*  Name     : CAknExPopFieldDocument
*  Part of  : AknExPopField
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

// INCLUDE FILES
#include "AknExPopFieldDocument.h"
#include "AknExPopFieldAppUi.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExPopFieldDocument* CAknExPopFieldDocument::NewL( CEikApplication& )
// EPOC two-phased constructor.
// ----------------------------------------------------------------------------
//
CAknExPopFieldDocument* CAknExPopFieldDocument::NewL( CEikApplication& aApp )
    {
    CAknExPopFieldDocument* self = new( ELeave ) CAknExPopFieldDocument( aApp );
    return self;
    }

// ----------------------------------------------------------------------------
// CAknExPopFieldDocument::~CAknExPopFieldDocument()
// Destructor.
// ----------------------------------------------------------------------------
//
CAknExPopFieldDocument::~CAknExPopFieldDocument()
    {
    }

// ----------------------------------------------------------------------------
// CAknExPopFieldDocument::CAknExPopFieldDocument( CEikApplication& )
// Overload constructor.
// ----------------------------------------------------------------------------
//
CAknExPopFieldDocument::CAknExPopFieldDocument( CEikApplication& aApp )
:   CEikDocument( aApp )
    {
    }

// ----------------------------------------------------------------------------
// CEikAppUi* CAknExPopFieldDocument::CreateAppUiL()
// Constructs CAknExPopFieldAppUi.
// ----------------------------------------------------------------------------
//
CEikAppUi* CAknExPopFieldDocument::CreateAppUiL()
    {
    return new( ELeave ) CAknExPopFieldAppUi;
    }

// End of File
