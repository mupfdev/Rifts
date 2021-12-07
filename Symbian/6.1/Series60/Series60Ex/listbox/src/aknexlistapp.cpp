/*
* =============================================================================
*  Name     : CAknExListApplication
*  Part of  : AknExList
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

// INCLUDE FILES
#include "AknExListApp.h"
#include "AknExListDocument.h"

// FUNCTION PROTOTYPES
EXPORT_C CApaApplication* NewApplication();
GLDEF_C TInt E32Dll( TDllReason );

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// TUid CAknExListApp::AppDllUid()
// Returns application UID.
// ----------------------------------------------------------------------------
//
TUid CAknExListApp::AppDllUid() const
    {
    return KUidAknExList;
    }

// ----------------------------------------------------------------------------
// CApaDocument* CAknExListApp::CreateDocumentL()
// Creates CAknExListDocument object.
// ----------------------------------------------------------------------------
//
CApaDocument* CAknExListApp::CreateDocumentL()
    {
    return CAknExListDocument::NewL( *this );
    }

// ================= OTHER EXPORTED FUNCTIONS =================================
//
// ----------------------------------------------------------------------------
// NewApplication()
// Constructs CAknExListApp.
// Returns: CApaDocument*: created application object
// ----------------------------------------------------------------------------
//
EXPORT_C CApaApplication* NewApplication()
    {
    return new CAknExListApp;
    }

// ----------------------------------------------------------------------------
// E32Dll(TDllReason)
// Entry point function for EPOC Apps.
// Returns: KErrNone: No error
// ----------------------------------------------------------------------------
//
GLDEF_C TInt E32Dll( TDllReason )
    {
    return KErrNone;
    }

// End of File
