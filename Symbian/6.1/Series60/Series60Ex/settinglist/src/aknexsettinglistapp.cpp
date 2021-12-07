/*
* =============================================================================
*  Name     : CAknExSettingListApp
*  Part of  : AknExSettingList
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include "AknExSettingListApp.h"
#include "AknExSettingListDocument.h"

// FUNCTION PROTOTYPE
EXPORT_C CApaApplication* NewApplication();
GLDEF_C TInt E32Dll( TDllReason );

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CApaDocument* CAknExSettingListApp::CreateDocumentL()
// Creates CAknExSettingListDocument object.
// ----------------------------------------------------------------------------
//
CApaDocument* CAknExSettingListApp::CreateDocumentL()
    {
    return CAknExSettingListDocument::NewL( *this );
    }

// ----------------------------------------------------------------------------
// TUid CAknExSettingListApp::AppDllUid()
// Returns application UID.
// ----------------------------------------------------------------------------
//
TUid CAknExSettingListApp::AppDllUid() const
    {
    return KUidAknExSettingList;
    }

// ================= OTHER EXPORTED FUNCTIONS =================================
//
// ----------------------------------------------------------------------------
// EXPORT_C CApaApplication* NewApplication()
// Constructs CAknExSettingListApp.
// Returns: CApaDocument*: created application object.
// ----------------------------------------------------------------------------
//
EXPORT_C CApaApplication* NewApplication()
    {
    return new CAknExSettingListApp;
    }

// ----------------------------------------------------------------------------
// GLDEF_C TInt E32Dll( TDllReason )
// Entry point function for EPOC Apps.
// Returns: KErrNone: No error.
// ----------------------------------------------------------------------------
//
GLDEF_C TInt E32Dll( TDllReason )
    {
    return KErrNone;
    }

// End of File
