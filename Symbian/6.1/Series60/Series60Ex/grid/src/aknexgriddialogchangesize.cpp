/*
* ============================================================================
*  Name     : CAknExGridDialogChangeSize from CAknDialog
*  Part of  : AknExGrid
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include "AknExGridDialogChangesize.h"
#include "AknExGridContainerAsSelection.h"
#include "AknExGrid.hrh"

// ================= MEMBER FUNCTIONS =======================

// C++ default constructor can NOT contain any code, that
// might leave.
//
CAknExGridDialogChangeSize::CAknExGridDialogChangeSize(
        CAknExGridContainerAsSelection* aContainer )
        : iContainer( aContainer )
    {
    }

// ---------------------------------------------------------
// CAknExGridDialogChangeSize::PreLayoutDynInitL( void )
// set params before showing dialog
// ---------------------------------------------------------
//
void CAknExGridDialogChangeSize::PreLayoutDynInitL( void )
    {
    // Get the number editor value of columns and rows setted now in Selection Grid.
    TInt numberOfColumns = iContainer->NumberOfColumns();
    TInt numberOfRows = iContainer->NumberOfRows();

    // Set the number editor values to ChangeSize dialog.
    SetNumberEditorValue( EAknExGridDialogChangeSizeColumns , numberOfColumns );
    SetNumberEditorValue( EAknExGridDialogChangeSizeRows , numberOfRows );
    }

// ---------------------------------------------------------
// CAknExGridDialogChangeSize::OkToExitL( TInt /*aKeycode*/ )
// update member variables of CAknExGridContainerAsSelection
// ---------------------------------------------------------
//
TBool CAknExGridDialogChangeSize::OkToExitL( TInt /*aKeycode*/ )
    {
    // the number editor value of columns and rows setted in dialog
    TInt numberOfColumns = NumberEditorValue( EAknExGridDialogChangeSizeColumns );
    TInt numberOfRows = NumberEditorValue( EAknExGridDialogChangeSizeRows );

    // Updata the number of columns and rows in Sellection Grid
    //with the number of columns and rows in ChangeSize dialog.
    iContainer->SetNumberOfColumns( numberOfColumns );
    iContainer->SetNumberOfRows( numberOfRows );

    return ETrue;

    }

// End of File  
