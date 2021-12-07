/*
* ============================================================================
*  Name     : CAknExScrollerApp from CEikApplication
*  Part of  : AknExScroller
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include    "AknExScrollerApp.h"
#include    "AknExScrollerDocument.h"

// ================= MEMBER FUNCTIONS =======================

// ---------------------------------------------------------
// CAknExScrollerApp::AppDllUid()
// Returns application UID
// ---------------------------------------------------------
//
TUid CAknExScrollerApp::AppDllUid() const
    {
    return KUidAknExScroller;
    }

// ---------------------------------------------------------
// CAknExScrollerApp::CreateDocumentL()
// Creates CAknExScrollerDocument object
// ---------------------------------------------------------
//
CApaDocument* CAknExScrollerApp::CreateDocumentL()
    {
    return CAknExScrollerDocument::NewL( *this );
    }

// ================= OTHER EXPORTED FUNCTIONS ==============
//
// ---------------------------------------------------------
// NewApplication() 
// Constructs CAknExScrollerApp
// Returns: CApaDocument*: created application object
// ---------------------------------------------------------
//
EXPORT_C CApaApplication* NewApplication()
    {
    return new CAknExScrollerApp;
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
