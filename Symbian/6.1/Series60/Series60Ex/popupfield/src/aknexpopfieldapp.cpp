/*
* =============================================================================
*  Name     : CAknExPopFieldApplication
*  Part of  : AknExPopField
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

// INCLUDE FILES
#include "AknExPopFieldApp.h"
#include "AknExPopFieldDocument.h"

// FUNCTION PROTOTYPES
EXPORT_C CApaApplication* NewApplication();
GLDEF_C TInt E32Dll( TDllReason );

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// TUid CAknExPopFieldApplication::AppDllUid()
// Returns application UID.
// ----------------------------------------------------------------------------
//
TUid CAknExPopFieldApplication::AppDllUid() const
    {
    return KUidAknExPopField;
    }

// ----------------------------------------------------------------------------
// CApaDocument* CAknExPopFieldApplication::CreateDocumentL()
// Creates CAknExPopFieldDocument object.
// ----------------------------------------------------------------------------
//
CApaDocument* CAknExPopFieldApplication::CreateDocumentL()
    {
    return CAknExPopFieldDocument::NewL( *this );
    }

// ================= OTHER EXPORTED FUNCTIONS =================================

// ----------------------------------------------------------------------------
// CApaApplication* NewApplication()
// Constructs CAknExPopFieldApplication.
// Returns: CApaDocument*: created application object
// ----------------------------------------------------------------------------
//
EXPORT_C CApaApplication* NewApplication()
    {
    return new CAknExPopFieldApplication;
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
