/*
* =============================================================================
*  Name     : CAknExNoteApplication
*  Part of  : AknExNote
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

// INCLUDE FILES
#include "AknExNoteApp.h"
#include "AknExNoteDocument.h"

EXPORT_C CApaApplication* NewApplication();
GLDEF_C TInt E32Dll( TDllReason );

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExNoteApp::CreateDocumentL()
// Creates CAknExNoteDocument object
// ----------------------------------------------------------------------------
//
CApaDocument* CAknExNoteApp::CreateDocumentL()
    {
    return CAknExNoteDocument::NewL( *this );
    }
// ----------------------------------------------------------------------------
// TUid CAknExNoteApp::AppDllUid()
// Returns application UID
// ----------------------------------------------------------------------------
//
TUid CAknExNoteApp::AppDllUid() const
    {
    return KUidAknExNote;
    }

// ================= OTHER EXPORTED FUNCTIONS =================================

// ----------------------------------------------------------------------------
// EXPORT_C NewApplication()
// Constructs CAknExNoteApplication
// Returns: CApaDocument*: created application object
// ----------------------------------------------------------------------------
//
EXPORT_C CApaApplication* NewApplication()
    {
    return new CAknExNoteApp;
    }

// ----------------------------------------------------------------------------
// GLDEF_C E32Dll( TDllReason )
// Entry point function for EPOC Apps
// Returns: KErrNone: No error
// ----------------------------------------------------------------------------
//
GLDEF_C TInt E32Dll( TDllReason )
    {
    return KErrNone;
    }

// End of File
