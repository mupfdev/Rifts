/*
* =============================================================================
*  Name     : CAknExNoteDocument
*  Part of  : AknExNote
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

// INCLUDE FILES
#include "AknExNoteDocument.h"
#include "AknExNoteAppUi.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExNoteDocument* CAknExNoteDocument::NewL( CEikApplication& )
// EPOC two-phased constructor.
// ----------------------------------------------------------------------------
//
CAknExNoteDocument* CAknExNoteDocument::NewL( CEikApplication& aApp )
    {
    CAknExNoteDocument* self = new( ELeave ) CAknExNoteDocument( aApp );
    return self;
    }

// ----------------------------------------------------------------------------
// CAknExNoteDocument::~CAknExNoteDocument()
// Destructor.
// ----------------------------------------------------------------------------
//
CAknExNoteDocument::~CAknExNoteDocument()
    {
    }

// ----------------------------------------------------------------------------
// CAknExNoteDocument::CAknExNoteDocument( CEikApplication& )
// Overload constructor.
// ----------------------------------------------------------------------------
//
CAknExNoteDocument::CAknExNoteDocument( CEikApplication& aApp )
:   CEikDocument( aApp )
    {
    }

// ----------------------------------------------------------------------------
// CEikAppUi* CAknExNoteDocument::CreateAppUiL()
// constructs CAknExNoteAppUi
// ----------------------------------------------------------------------------
//
CEikAppUi* CAknExNoteDocument::CreateAppUiL()
    {
    return new( ELeave ) CAknExNoteAppUi;
    }

// End of File
