/*
* =============================================================================
*  Name     : CAknExQueryApplication
*  Part of  : AknExQuery
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

// INCLUDE FILES
#include "AknExQueryApp.h"
#include "AknExQueryDocument.h"

// FUNCTION PROTOTYPES
EXPORT_C CApaApplication* NewApplication();
GLDEF_C TInt E32Dll( TDllReason );

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExQueryApp::CreateDocumentL()
// Creates CAknExQueryDocument object
// ----------------------------------------------------------------------------
//
CApaDocument* CAknExQueryApp::CreateDocumentL()
    {
    return CAknExQueryDocument::NewL( *this );
    }

// ----------------------------------------------------------------------------
// CAknExQueryApp::AppDllUid()
// Returns application UID
// ----------------------------------------------------------------------------
//
TUid CAknExQueryApp::AppDllUid() const
    {
    return KUidAknExQuery;
    }

// ================= OTHER EXPORTED FUNCTIONS =================================
//
// ----------------------------------------------------------------------------
// NewApplication()
// Constructs CAknExQueryApp
// Returns: CApaDocument*: created application object
// ----------------------------------------------------------------------------
//
EXPORT_C CApaApplication* NewApplication()
    {
    return new CAknExQueryApp;
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
