/* 
* ============================================================================
*  Name     : CAknExSpaneApp from CAknApplication
*  Part of  : AknExSpane
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include    "AknExSpaneApp.h"
#include    "AknExSpaneDocument.h"

// ================= MEMBER FUNCTIONS =======================

// ---------------------------------------------------------
// CAknExSpaneApp::AppDllUid()
// Returns application UID
// ---------------------------------------------------------
//
TUid CAknExSpaneApp::AppDllUid() const
    {
    return KUidAknExSpane;
    }

// ---------------------------------------------------------
// CAknExSpaneApp::CreateDocumentL()
// Creates CAknExSpaneDocument object
// ---------------------------------------------------------
//
CApaDocument* CAknExSpaneApp::CreateDocumentL()
    {
    return CAknExSpaneDocument::NewL(*this);
    }

// ================= OTHER EXPORTED FUNCTIONS ==============
//
// ---------------------------------------------------------
// NewApplication() 
// Constructs CAknExSpaneApp
// Returns: CApaDocument*: created application object
// ---------------------------------------------------------
//
EXPORT_C CApaApplication* NewApplication()
    {
    return new CAknExSpaneApp;
    }

// ---------------------------------------------------------
// E32Dll(TDllReason) 
// Entry point function for EPOC Apps
// Returns: KErrNone: No error
// ---------------------------------------------------------
//
GLDEF_C TInt E32Dll(TDllReason)
    {
    return KErrNone;
    }

// End of File  

