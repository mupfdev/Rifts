/*
* ============================================================================
*  Name     : CAknExMenuApp from CEikApplication
*  Part of  : AknExMenu
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include    "AknExMenuApp.h"
#include    "AknExMenuDocument.h"

// ================= MEMBER FUNCTIONS =======================

// ---------------------------------------------------------
// CAknExMenuApp::CreateDocumentL()
// Creates CAknExMenuDocument object
// ---------------------------------------------------------
//
CApaDocument* CAknExMenuApp::CreateDocumentL()
    {
    return CAknExMenuDocument::NewL(*this);
    }

// ---------------------------------------------------------
// CAknExMenuApp::AppDllUid()
// Returns application UID
// ---------------------------------------------------------
//
TUid CAknExMenuApp::AppDllUid() const
    {
    return KUidAknExMenu;
    }

// ================= OTHER EXPORTED FUNCTIONS ==============
//
// ---------------------------------------------------------
// NewApplication() 
// Constructs CAknExMenuApp
// Returns: CApaDocument*: created application object
// ---------------------------------------------------------
//
EXPORT_C CApaApplication* NewApplication()
    {
    return new CAknExMenuApp;
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

