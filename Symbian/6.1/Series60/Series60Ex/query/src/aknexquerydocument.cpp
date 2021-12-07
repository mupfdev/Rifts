/*
* =============================================================================
*  Name     : CAknExQueryDocument
*  Part of  : AknExQuery
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

// INCLUDE FILES
#include "AknExQueryDocument.h"
#include "AknExQueryAppUi.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExQueryDocument::NewL()
// Two-phased constructor.
// ----------------------------------------------------------------------------
//
CAknExQueryDocument* CAknExQueryDocument::NewL( CEikApplication& aApp )
    {
    CAknExQueryDocument* self = new( ELeave ) CAknExQueryDocument( aApp );
    return self;
    }

//-----------------------------------------------------------------------------
// CAknExQueryDocument::~CAknExQueryDocument()
// Destructor.
//-----------------------------------------------------------------------------
//
CAknExQueryDocument::~CAknExQueryDocument()
    {
    }

// ----------------------------------------------------------------------------
// CAknExQueryDocument::CAknExQueryDocument( CEikApplication& )
// Overload constructor.
// ----------------------------------------------------------------------------
//
CAknExQueryDocument::CAknExQueryDocument( CEikApplication& aApp )
:   CEikDocument( aApp )
    {
    }

// ----------------------------------------------------------------------------
// CAknExQueryDocument::CreateAppUiL()
// constructs CAknExQueryAppUi
// ----------------------------------------------------------------------------
//
CEikAppUi* CAknExQueryDocument::CreateAppUiL()
    {
    return new( ELeave ) CAknExQueryAppUi;
    }

// End of File
