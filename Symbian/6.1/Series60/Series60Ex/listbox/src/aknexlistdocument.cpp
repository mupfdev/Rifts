/*
* =============================================================================
*  Name     : CAknExListDocument
*  Part of  : AknExList
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

// INCLUDE FILES
#include "AknExListDocument.h"
#include "AknExListAppUi.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExListDocument* CAknExListDocument::NewL( CEikApplication& )
// EPOC two-phased constructor.
// ----------------------------------------------------------------------------
//
CAknExListDocument* CAknExListDocument::NewL( CEikApplication& aApp )
    {
    CAknExListDocument* self = new( ELeave ) CAknExListDocument( aApp );
    CleanupStack::PushL( self ); // Pushes document to clean-up stack.
    self->ConstructL();
    CleanupStack::Pop(); // Pops from clean-up stack.
    return self;
    }

// ----------------------------------------------------------------------------
// CAknExListDocument::~CAknExListDocument()
// Destructor.
// ----------------------------------------------------------------------------
//
CAknExListDocument::~CAknExListDocument()
    {
    }

// ----------------------------------------------------------------------------
// CAknExListDocument::CAknExListDocument( CEikApplication& )
// Overload constructor.
// ----------------------------------------------------------------------------
//
CAknExListDocument::CAknExListDocument( CEikApplication& aApp )
:   CEikDocument( aApp )
    {
    }

// ----------------------------------------------------------------------------
// void CAknExListDocument::ConstructL()
// EPOC constructor.
// ----------------------------------------------------------------------------
//
void CAknExListDocument::ConstructL()
    {
    }

// ----------------------------------------------------------------------------
// CEikAppUi* CAknExListDocument::CreateAppUiL()
// Constructs CAknExListAppUi.
// ----------------------------------------------------------------------------
//
CEikAppUi* CAknExListDocument::CreateAppUiL()
    {
    return new( ELeave ) CAknExListAppUi;
    }

// End of File
