/*
* ============================================================================
*  Name     : CAknExGridDialogNumberOfItems from CAknDialog
*  Part of  : AknExGrid
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include "AknExGridDialogNumberOfItems.h"
#include "AknExGridContainerAsSelection.h"
#include "AknExGrid.hrh"

// ================= MEMBER FUNCTIONS =======================

// C++ default constructor can NOT contain any code, that
// might leave.
//
CAknExGridDialogNumberOfItems::CAknExGridDialogNumberOfItems(
        CAknExGridContainerAsSelection* aContainer )
        : iContainer( aContainer )
    {
    }

// ---------------------------------------------------------
// CAknExGridDialogNumberOfItems::PreLayoutDynInitL( void )
// set params before showing dialog
// ---------------------------------------------------------
//
void CAknExGridDialogNumberOfItems::PreLayoutDynInitL( void )
    {
    // Get the number of item in Grid.
    TInt numberOfItems = iContainer->NumberOfItems();

    // Set the number of item to dialog.
    SetNumberEditorValue( EAknExGridDialogNumberOfItems , numberOfItems );

    }

// ---------------------------------------------------------
// CAknExGridDialogNumberOfItems::OkToExitL( TInt /*aKeycode*/ )
// update member variables of CAknExGridContainerAsSelection
// ---------------------------------------------------------
//
TBool CAknExGridDialogNumberOfItems::OkToExitL( TInt /*aKeycode*/ )
    {
    // the number of items setted in dialog
    TInt numberOfItems = NumberEditorValue( EAknExGridDialogNumberOfItems );
   
    // Updata the number of items in Grid
    //with the number of items in dialog.
    iContainer->SetNumberOfItems( numberOfItems );

    return ETrue;

    }

// End of File  



