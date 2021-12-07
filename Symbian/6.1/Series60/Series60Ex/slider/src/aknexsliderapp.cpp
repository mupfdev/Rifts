/*
* ============================================================================
*  Name     : CAknExSliderApplication
*  Part of  : AknExSlider
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include "AknExSliderApp.h"
#include "AknExSliderDocument.h"

// FUNCTION PROTOTYPES
EXPORT_C CApaApplication* NewApplication();
GLDEF_C TInt E32Dll( TDllReason );

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExSliderApplication::AppDllUid()
// Returns application UID
// ----------------------------------------------------------------------------
//
TUid CAknExSliderApplication::AppDllUid() const
    {
    return KUidAknExSlider;
    }

// ----------------------------------------------------------------------------
// CAknExSliderApplication::CreateDocumentL()
// Creates CAknExSliderDocument object
// ----------------------------------------------------------------------------
//
CApaDocument* CAknExSliderApplication::CreateDocumentL()
    {
    return CAknExSliderDocument::NewL( *this );
    }

// ================= OTHER EXPORTED FUNCTIONS =================================

// ----------------------------------------------------------------------------
// NewApplication()
// Constructs CAknExSliderApplication
// Returns: CApaDocument*: created application object
// ----------------------------------------------------------------------------
//
EXPORT_C CApaApplication* NewApplication()
    {
    return new CAknExSliderApplication;
    }

// ----------------------------------------------------------------------------
// E32Dll(TDllReason)
// Entry point function for EPOC Apps
// Returns: KErrNone: No error
// ----------------------------------------------------------------------------
//
GLDEF_C TInt E32Dll( TDllReason )
    {
    return KErrNone;
    }

// End of File
