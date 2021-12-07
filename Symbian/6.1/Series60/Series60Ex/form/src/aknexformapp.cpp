/*
* ============================================================================
*  Name     : CAknExFormApplication
*  Part of  : AknExForm
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include "AknExFormApp.h"
#include "AknExFormDocument.h"

// FUNCTION PROTOTYPES
EXPORT_C CApaApplication* NewApplication();
GLDEF_C TInt E32Dll( TDllReason );

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// TUid CAknExFormApplication::AppDllUid()
// Returns application UID.
// ----------------------------------------------------------------------------
//
TUid CAknExFormApplication::AppDllUid() const
    {
    return KUidAknExForm;
    }

// ----------------------------------------------------------------------------
// CApaDocument* CAknExFormApplication::CreateDocumentL()
// Creates CAknExFormDocument object.
// ----------------------------------------------------------------------------
//
CApaDocument* CAknExFormApplication::CreateDocumentL()
    {
    return CAknExFormDocument::NewL( *this );
    }

// ================= OTHER EXPORTED FUNCTIONS =================================

// ----------------------------------------------------------------------------
// CApaApplication* NewApplication()
// Constructs CAknExFormApplication.
// Returns: CApaDocument*: created application object
// ----------------------------------------------------------------------------
//
EXPORT_C CApaApplication* NewApplication()
    {
    return new CAknExFormApplication;
    }

// ----------------------------------------------------------------------------
// TInt E32Dll(TDllReason)
// Entry point function for EPOC Apps.
// Returns: KErrNone: No error
// ----------------------------------------------------------------------------
//
GLDEF_C TInt E32Dll( TDllReason )
    {
    return KErrNone;
    }

// End of File
