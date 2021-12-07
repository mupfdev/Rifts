/*
* ============================================================================
*  Name     : CAknExFormDocument
*  Part of  : AknExForm
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include "AknExFormDocument.h"
#include "AknExFormAppUi.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExFormDocument* CAknExFormDocument::NewL( CEikApplication& )
// EPOC two-phased constructor.
// ----------------------------------------------------------------------------
//
CAknExFormDocument* CAknExFormDocument::NewL( CEikApplication& aApp )
    {
    CAknExFormDocument* self = new( ELeave ) CAknExFormDocument( aApp );
    return self;
    }

// ----------------------------------------------------------------------------
// CAknExFormDocument::~CAknExFormDocument()
// Destructor.
// ----------------------------------------------------------------------------
//
CAknExFormDocument::~CAknExFormDocument()
    {
    }

// ----------------------------------------------------------------------------
// CAknExFormDocument::CAknExFormDocument( CEikApplication& )
// Overload constructor.
// ----------------------------------------------------------------------------
//
CAknExFormDocument::CAknExFormDocument( CEikApplication& aApp )
:   CEikDocument( aApp )
    {
    }

// ----------------------------------------------------------------------------
// CEikAppUi* CAknExFormDocument::CreateAppUiL()
// Constructs CAknExFormAppUi.
// ----------------------------------------------------------------------------
//
CEikAppUi* CAknExFormDocument::CreateAppUiL()
    {
    return new( ELeave ) CAknExFormAppUi;
    }

// End of File
