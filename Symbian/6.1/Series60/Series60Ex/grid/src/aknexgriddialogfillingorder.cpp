/*
* ============================================================================
*  Name     : CAknExGridDialogFillingOrder from CAknDialog
*  Part of  : AknExGrid
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include <AknExGrid.rsg> // Dialog

#include <aknpopupfieldText.h>

#include "AknExGridDialogFillingOrder.h"
#include "AknExGridContainerAsSelection.h"
#include "AknExGrid.hrh"

// ================= MEMBER FUNCTIONS =======================

// // C++ default constructor can NOT contain any code, that
// // might leave.
// //
// CAknExGridDialogFillingOrder::CAknExGridDialogFillingOrder(
//         CAknExGridContainerAsSelection* aContainer )
//         : iContainer( aContainer )
//     {
//     }
// 
// // ---------------------------------------------------------
// // AknExGridDialogFillingOrder::PreLayoutDynInitL( void )
// // set params before showing dialog
// // ---------------------------------------------------------
// //
// void CAknExGridDialogFillingOrder::PreLayoutDynInitL( void )
//     {
//     TBool verticalOrientation = ETrue;
//     TBool toRight = ETrue;
//     TBool toBottom = ETrue;
// 
//     iContainer->GetOrientation( verticalOrientation,  toRight, toBottom );
// 
//     SetNumberEditorValue( EAknExGridDialogFillingOrderPrimaryOrientation , 
//         ( verticalOrientation? 
//         EAknExGridDialogFillingOrderVert : EAknExGridDialogFillingOrderHoriz ) );
// 
//     SetNumberEditorValue( EAknExGridDialogFillingOrderVerticalDirection , 
//         ( toBottom?
//         EAknExGridDialogFillingOrderToBottom : EAknExGridDialogFillingOrderToTop ) );
// 
//     SetNumberEditorValue( EAknExGridDialogFillingOrderHorizontalDirection , 
//         ( toRight? 
//         EAknExGridDialogFillingOrderToRight : EAknExGridDialogFillingOrderToLeft ) );
// 
//     }
// 
// 
// // ---------------------------------------------------------
// // CAknExGridDialogFillingOrder::OkToExitL( TInt /*aKeycode*/ )
// // update member variables of CAknExGridContainerAsSelection
// // ---------------------------------------------------------
// //
// TBool CAknExGridDialogFillingOrder::OkToExitL( TInt /*aKeycode*/ )
//     {
// 
//     TBool verticalOrientation = ETrue;
//     TBool toRight = ETrue;
//     TBool toBottom = ETrue;
// 
//     TInt butIdVert = NumberEditorValue( EAknExGridDialogFillingOrderPrimaryOrientation );
//     TInt butIdToBottom = NumberEditorValue( EAknExGridDialogFillingOrderVerticalDirection );
//     TInt butIdToRight = NumberEditorValue( EAknExGridDialogFillingOrderHorizontalDirection );
// 
//     if ( butIdVert == EAknExGridDialogFillingOrderVert )
//         {
//         verticalOrientation = ETrue;
//         }
//     else
//         {
//         verticalOrientation = EFalse;
//         }
// 
//     if ( butIdToBottom == EAknExGridDialogFillingOrderToBottom )
//         {
//         toBottom = ETrue;
//         }
//     else
//         {
//         toBottom = EFalse;
//         }
// 
//     if ( butIdToRight == EAknExGridDialogFillingOrderToRight )
//         {
//         toRight = ETrue;
//         }
//     else
//         {
//         toRight = EFalse;
//         }
// 
//     iContainer->SetOrientation( verticalOrientation, toRight, toBottom );
// 
//     return ETrue;
//     }


// popup field stuff starts from here....Changes done by Srini...


// ----------------------------------------------------------------------------
// CAknExPopFieldFillingOrder::CAknExPopFieldFillingOrder( CAknExGridContainerAsSelection* )
// Overload Constructor.
// ----------------------------------------------------------------------------
//
CAknExPopFieldFillingOrder::CAknExPopFieldFillingOrder
                  ( CAknExGridContainerAsSelection* aContainer )
        : iContainer( aContainer )
    {
    }

// ----------------------------------------------------------------------------
// void CAknExPopFieldFillingOrder::PreLayoutDynInitL()
// Dialog initialize
// ----------------------------------------------------------------------------
//
void CAknExPopFieldFillingOrder::PreLayoutDynInitL()
    {
    TBool verticalOrientation = ETrue;
    TBool toRight = ETrue;
    TBool toBottom = ETrue;
    iContainer->GetOrientation( verticalOrientation,  toRight, toBottom );

    CAknPopupFieldText* popupFieldText1 = (CAknPopupFieldText*) Control(EAknExGridDialogFillingOrderPrimaryOrientation);
    CAknPopupFieldText* popupFieldText2 = (CAknPopupFieldText*) Control(EAknExGridDialogFillingOrderVerticalDirection);
    CAknPopupFieldText* popupFieldText3 = (CAknPopupFieldText*) Control(EAknExGridDialogFillingOrderHorizontalDirection);

    popupFieldText1->SetCurrentValueIndex(verticalOrientation?EAknExGridDialogFillingOrderVert:EAknExGridDialogFillingOrderHoriz);
    popupFieldText2->SetCurrentValueIndex(toBottom?EAknExGridDialogFillingOrderToBottom:EAknExGridDialogFillingOrderToTop);
    popupFieldText3->SetCurrentValueIndex(toRight?EAknExGridDialogFillingOrderToRight:EAknExGridDialogFillingOrderToLeft);

    SetEditableL(ETrue);
    }

// ----------------------------------------------------------------------------
// TBool CAknExPopFieldFillingOrder::OkToExitL( TInt )
// Handles the button event
// ----------------------------------------------------------------------------
//
TBool CAknExPopFieldFillingOrder::OkToExitL( TInt /*aButtonId*/ )
    {
    TBool verticalOrientation = ETrue;
    TBool toRight = ETrue;
    TBool toBottom = ETrue;

    CAknPopupFieldText* popupFieldText1 = (CAknPopupFieldText*) Control(EAknExGridDialogFillingOrderPrimaryOrientation);
    CAknPopupFieldText* popupFieldText2 = (CAknPopupFieldText*) Control(EAknExGridDialogFillingOrderVerticalDirection);
    CAknPopupFieldText* popupFieldText3 = (CAknPopupFieldText*) Control(EAknExGridDialogFillingOrderHorizontalDirection);

    TInt butIdVert =  popupFieldText1->CurrentValueIndex();
    TInt butIdToBottom = popupFieldText2->CurrentValueIndex();
    TInt butIdToRight = popupFieldText3->CurrentValueIndex();

    if ( butIdVert == EAknExGridDialogFillingOrderVert )
        {
        verticalOrientation = ETrue;
        }
    else
        {
        verticalOrientation = EFalse;
        }

    if (butIdToBottom == EAknExGridDialogFillingOrderToBottom )
        {
        toBottom = ETrue;
        }
    else
        {
        toBottom = EFalse;
        }

    if ( butIdToRight == EAknExGridDialogFillingOrderToRight )
        {
        toRight = ETrue;
        }
    else
        {
        toRight = EFalse;
        }

    iContainer->SetOrientation(verticalOrientation, toRight, toBottom);

    return ETrue;
    }

// End of File  
