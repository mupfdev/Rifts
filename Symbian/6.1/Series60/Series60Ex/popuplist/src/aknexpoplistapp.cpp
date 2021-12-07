/*
* ============================================================================
*  Name     : CAknExPopListApp from %name%
*  Part of  : AknExPopList
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include    "AknExPopListApp.h"
#include    "AknExPopListDocument.h"

// ================= MEMBER FUNCTIONS =======================

// ---------------------------------------------------------
// CAknExPopListApp::AppDllUid()
// Returns application UID
// ---------------------------------------------------------
//
TUid CAknExPopListApp::AppDllUid() const
    {
    return KUidAknExPopList;
    }

// ---------------------------------------------------------
// CAknExPopListApp::CreateDocumentL()
// Creates CAknExPopListDocument object
// ---------------------------------------------------------
//
CApaDocument* CAknExPopListApp::CreateDocumentL()
    {
    return CAknExPopListDocument::NewL(*this);
    }

// ================= OTHER EXPORTED FUNCTIONS ==============
//
// ---------------------------------------------------------
// NewApplication() 
// Constructs CAknExPopListApp
// Returns: CApaDocument*: created application object
// ---------------------------------------------------------
//
EXPORT_C CApaApplication* NewApplication()
    {
    return new CAknExPopListApp;
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

