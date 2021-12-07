/*
* ============================================================================
*  Name     : CAknExEditorApp.cpp from CAknViewAppUi
*  Part of  : AknExEditor
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include    "AknExEditorApp.h"
#include    "AknExEditorDocument.h"

// ================= MEMBER FUNCTIONS =======================

// ---------------------------------------------------------
// CAknExEditorApp::AppDllUid()
// Returns application UID
// ---------------------------------------------------------
//
TUid CAknExEditorApp::AppDllUid() const
    {
    return KUidAknExEditor;
    }

// ---------------------------------------------------------
// CAknExEditorApp::CreateDocumentL()
// Creates CAknExEditorDocument object
// ---------------------------------------------------------
//
CApaDocument* CAknExEditorApp::CreateDocumentL()
    {
    return CAknExEditorDocument::NewL(*this);
    }

// ================= OTHER EXPORTED FUNCTIONS ==============
//
// ---------------------------------------------------------
// NewApplication() 
// Constructs CAknExEditorApp
// Returns: CApaDocument*: created application object
// ---------------------------------------------------------
//
EXPORT_C CApaApplication* NewApplication()
    {
    return new CAknExEditorApp;
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

