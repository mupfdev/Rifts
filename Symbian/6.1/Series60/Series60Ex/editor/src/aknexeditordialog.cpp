/*
* ============================================================================
*  Name     : CAknExEditorDialog.cpp from CEikDialog
*  Part of  : AknExEditor
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include "AknExEditor.hrh"
#include "AknExEditorDialog.h"

// ================= MEMBER FUNCTIONS =======================

// C++ default constructor can NOT contain any code, that
// might leave.
//
CAknExEditorDialog::CAknExEditorDialog()
    {
    }

// ----------------------------------------------------------
// CAknExEditorDialog::PreLayoutDynInitL()
// Initializing the dialog dynamically
// ----------------------------------------------------------
//
void CAknExEditorDialog::PreLayoutDynInitL()
    {
    SetEditableL(ETrue);
    }

// ----------------------------------------------------------
// CAknExEditorDialog::OkToExitL()
// This function ALWAYS returns ETrue
// ----------------------------------------------------------
//
TBool CAknExEditorDialog::OkToExitL(TInt /*aButtonId*/)
    {
    return ETrue;
    }

// End of File  
