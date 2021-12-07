/*
* ============================================================================
*  Name     : CAknExSliderDocument
*  Part of  : AknExSlider
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include "AknExSliderDocument.h"
#include "AknExSliderAppUi.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExSliderDocument::NewL( CEikApplication& )
// EPOC two-phased constructor.
// ----------------------------------------------------------------------------
//
CAknExSliderDocument* CAknExSliderDocument::NewL( CEikApplication& aApp )
    {
    CAknExSliderDocument* self = new( ELeave ) CAknExSliderDocument( aApp );
    return self;
    }

// ----------------------------------------------------------------------------
// CAknExSlinder::~CAknExSlider()
// Destructor.
// ----------------------------------------------------------------------------
//
CAknExSliderDocument::~CAknExSliderDocument()
    {
    }

// ----------------------------------------------------------------------------
// CAknExSlinderDocument::CAknExSlinderDocument( CEikApplication& )
// Overload constructor.
// ----------------------------------------------------------------------------
//
CAknExSliderDocument::CAknExSliderDocument( CEikApplication& aApp )
: CEikDocument( aApp )
    {
    }

// ----------------------------------------------------------------------------
// CAknExSliderDocument::CreateAppUiL()
// Creates AppUi class object, and returns pointer to object.
// ----------------------------------------------------------------------------
//
CEikAppUi* CAknExSliderDocument::CreateAppUiL()
    {
    return new( ELeave ) CAknExSliderAppUi;
    }

// End of File
