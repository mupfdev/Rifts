/*
* ============================================================================
*  Name     : CAknExPbarApp from CEikApplication
*  Part of  : AknExPbar
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/


// INCLUDE FILES
#include "AknExPbarApp.h"
#include "AknExPbarDocument.h"


// ================= MEMBER FUNCTIONS =======================

// ---------------------------------------------------------
// CAknExPbarApp::AppDllUid()
// Returns application UID
// ---------------------------------------------------------
//
TUid CAknExPbarApp::AppDllUid() const
    {
    return KUidAknExPbar;
    }

// ---------------------------------------------------------
// CAknExPbarApp::CreateDocumentL()
// Creates CAknExPbarDocument object
// ---------------------------------------------------------
//
CApaDocument* CAknExPbarApp::CreateDocumentL()
    {
    return CAknExPbarDocument::NewL( *this );
    }

// ================= OTHER EXPORTED FUNCTIONS ==============
//
// ---------------------------------------------------------
// NewApplication() 
// Constructs CAknExPbarApp
// Returns: CApaDocument*: created application object
// ---------------------------------------------------------
//
EXPORT_C CApaApplication* NewApplication()
    {
    return new CAknExPbarApp;
    }

// ---------------------------------------------------------
// E32Dll( TDllReason ) 
// Entry point function for EPOC Apps
// Returns: KErrNone: No error
// ---------------------------------------------------------
//
GLDEF_C TInt E32Dll( TDllReason )
    {
    return KErrNone;
    }

// End of File  

