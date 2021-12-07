/*
* ============================================================================
*  Name     : CAknExGridApp from CAknApplication
*  Part of  : AknExGrid
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include    "AknExGridApp.h"
#include    "AknExGridDocument.h"

// ================= MEMBER FUNCTIONS =======================

// ---------------------------------------------------------
// CAknExGridApp::CreateDocumentL()
// Creates CAknExGridDocument object
// ---------------------------------------------------------
//
CApaDocument* CAknExGridApp::CreateDocumentL()
    {
    return CAknExGridDocument::NewL( *this );
    }

// ---------------------------------------------------------
// CAknExGridApp::AppDllUid()
// Returns application UID
// ---------------------------------------------------------
//
TUid CAknExGridApp::AppDllUid() const
    {
    return KUidAknExGrid;
    }

// ================= OTHER EXPORTED FUNCTIONS ==============
//
// ---------------------------------------------------------
// NewApplication() 
// Constructs CAknExGridApp
// Returns: CApaDocument*: created application object
// ---------------------------------------------------------
//
EXPORT_C CApaApplication* NewApplication()
    {
    return new CAknExGridApp;
    }

// ---------------------------------------------------------
// E32Dll(TDllReason) 
// Entry point function for EPOC Apps
// Returns: KErrNone: No error
// ---------------------------------------------------------
//
GLDEF_C TInt E32Dll( TDllReason )
    {
    return KErrNone;
    }

// End of File  

