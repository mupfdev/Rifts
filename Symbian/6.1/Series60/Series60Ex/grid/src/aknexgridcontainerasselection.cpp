/*
* ============================================================================
*  Name     : CAknExGridContainerAsSelection 
*             from CCoeControl, MCoeControlObserver
*  Part of  : AknExGrid
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES

#include <eiklabel.h>    // for example label control
#include <gulicon.h>
#include <aknutils.h>    // definition of AKN_LAF_COLOR()
#include <AknForm.h>
#include <AknGrid.h>
#include <AknGridView.h>
#include <AknGridM.h>
#include <avkon.hrh>
#include <aknlists.h>
#include <akntitle.h>
#include <AknQueryDialog.h>

#include <AknIconArray.h>

#include <AknExGrid.rsg>    // Dialog
#include <AknExGrid.mbg>    // Bitmap

#include "AknExGridContainerAsSelection.h"
#include "AknExGridDialogFillingOrder.h"
//#include "AknExGridDialogChangeSize.h"
//#include "AknExGridDialogNumberOfItems.h"

// ================= MEMBER FUNCTIONS =======================

// C++ default constructor can NOT contain any code, that
// might leave.
//
CAknExGridContainerAsSelection::CAknExGridContainerAsSelection()
    : iGrid( NULL ), iGridType( EAknExGridSelectionGrid ),
      iLabel( NULL ), iToDoLabel( NULL )

    {
    }

// EPOC default constructor can leave.
void CAknExGridContainerAsSelection::ConstructL(
        const TRect& aRect, TAknExGridGridType aGridType )
    {
    CreateWindowL();

    TBuf< KLengthOfLabel > label;
    iLabel = new( ELeave ) CEikLabel;
    iLabel->SetContainerWindowL( *this );
    iCoeEnv->ReadResource( label, R_AKNEXGRID_LABEL_VIEW_AS_SELECTION );
    iLabel->SetTextL( label );

    TBuf< KLengthOfDoLabel > dolabel;
    iToDoLabel = new( ELeave ) CEikLabel;
    iToDoLabel->SetContainerWindowL( *this );
    iCoeEnv->ReadResource( dolabel, R_AKNEXGRID_DOLABEL_VIEW_AS_SELECTION );
    iToDoLabel->SetTextL( dolabel );

    iTestNumber = 0;
    
    // create a grid
    iGrid = new( ELeave ) CAknGrid;
    iGrid->SetContainerWindowL( *this );

    iGridM = new( ELeave ) CAknGridM;

    iGridType = aGridType;
    iGrid->SetModel( iGridM );
    if ( iGridType == EAknExGridSelectionGrid )
        {
        iGrid->ConstructL( this, EAknListBoxSelectionGrid );
        iTitles = iCoeEnv->ReadDesCArrayResourceL(R_AKNEXGRID_TITLE_SELECTION);
        CEikStatusPane* sp = iEikonEnv->AppUiFactory()->StatusPane();
        CAknTitlePane* titlePane = (CAknTitlePane *)sp->ControlL(TUid::Uid(EEikStatusPaneUidTitle));
        titlePane->SetTextL((*iTitles)[ESelectionTest1]);
        }
    else
        {
        iGrid->ConstructL( this, EAknListBoxMarkableGrid );
        iTitles = iCoeEnv->ReadDesCArrayResourceL(R_AKNEXGRID_TITLE_MARKABLE);
        CEikStatusPane* sp = iEikonEnv->AppUiFactory()->StatusPane();
        CAknTitlePane* titlePane = (CAknTitlePane *)sp->ControlL(TUid::Uid(EEikStatusPaneUidTitle));
        titlePane->SetTextL((*iTitles)[EMarkableTest1]);
        }

    // set initial params for the grid
    iVerticalOrientation = ETrue;
    iTopToBottom = ETrue;
    iLeftToRight = ETrue;
    iNumOfColumns = KNumOfColumns;
    iNumOfRows = KNumOfRows;
    iContentType = EContainBoth;
    iNumOfItems = KInitialNumOfItems;

    iVerticalScrollingType = CAknGridView::EScrollIncrementLineAndLoops;
    iHorizontalScrollingType = CAknGridView::EScrollIncrementLineAndLoops;

    // set empty text
    TBuf< KLengthOfEmptyText > emptyText;
    iCoeEnv->ReadResource( emptyText, R_AKNEXGRID_TEXT_EMPTY_SELECTION_GRID );
    //iGrid->SetEmptyGridTextL( emptyText,iCoeEnv->NormalFont(),
    //    CGraphicsContext::ELeft, KMarginEmptyText );
    iGrid->SetEmptyGridTextL( emptyText );

    // set layout
    iGrid->SetRect( aRect );
    iSizeOfItems.iWidth = ( aRect.iBr.iX - aRect.iTl.iX ) / iNumOfColumns;
    iSizeOfItems.iHeight = ( aRect.iBr.iY - aRect.iTl.iY ) / iNumOfRows;
    SetGridLayoutL();

    // create resouce for grid (do not load from the HRH file)
    CreateGridResourceL();

    iInstantsCreated = ETrue;

    // activate view
    SetRect( aRect );
    ActivateL();

    // activate the grid
    iGrid->MakeVisible( ETrue );
    iGrid->SetFocus( ETrue );
    iGrid->ActivateL();
    iGrid->DrawNow();
    }

// destructor
CAknExGridContainerAsSelection::~CAknExGridContainerAsSelection()
    {
    if ( iInstantsCreated )
        {
        delete iLabel;
        delete iToDoLabel;
        delete iGrid;
        }
    delete iTitles;
    }

// ---------------------------------------------------------
// CAknExGridContainerAsSelection::InsertDataL( TInt aNum )
// Insert items to the current index.
// ---------------------------------------------------------
//
void CAknExGridContainerAsSelection::InsertDataL( TInt aNum )
    {
    // Number of Grids.
    TInt numberOfData = iGrid->GridModel()->NumberOfData();
    
    // If there is no item in grid 
    if ( numberOfData < 1 )
        {
        AddDataL( aNum );
        return;
        }

    MDesCArray *array = iGrid->Model()->ItemTextArray();
    CDesCArray *cArray = ( CDesCArray* )array;

    // Makes text which is added to.
    TBuf< KLengthOfItemResourceString > number;
    TBuf< KLengthOfItemResourceString > format;
    if ( iGridType == EAknExGridMarkableGrid )
        {
        iCoeEnv->ReadResource( format,
                               R_AKNEXGRID_FORMATSTRING_MARKABLEITEM );
        }
    else
        {
        iCoeEnv->ReadResource( format,
                               R_AKNEXGRID_FORMATSTRING_SELECTIONITEM );
        }

    // This shows current index item.
    TInt oldCurrIndex = iGrid->CurrentDataIndex();

    // If the number of Grids is more than zero 
    for ( TInt loop = numberOfData + aNum; loop > numberOfData; loop-- )
        {
        number.Format( format, loop );
        // insert the data to the current index.
        cArray->InsertL( oldCurrIndex , number );
        }

    // Inform list box that added data.
    iGrid->HandleItemAdditionL();

    // If item size changes, need to alter the item style
    ApplySelGridGraphicStyleL();

    }

// ---------------------------------------------------------
// CAknExGridContainerAsSelection::AddDataL( TInt aNum )
// Add items to the last.
// ---------------------------------------------------------
//
void CAknExGridContainerAsSelection::AddDataL( TInt aNum )
    {
    MDesCArray* array = iGrid->Model()->ItemTextArray();
    CDesCArray* cArray = ( CDesCArray* )array;

    // Makes text which is added to.
    TBuf< KLengthOfItemResourceString > number;
    TBuf< KLengthOfItemResourceString > format;
    if ( iGridType == EAknExGridMarkableGrid )
        {
        iCoeEnv->ReadResource( format,
                               R_AKNEXGRID_FORMATSTRING_MARKABLEITEM );
        }
    else
        {
        iCoeEnv->ReadResource( format,
                               R_AKNEXGRID_FORMATSTRING_SELECTIONITEM );
        }


    // The number of Grids.
    TInt numberOfData = iGrid->GridModel()->NumberOfData() ;
    
    // Add the data to the last
    for ( TInt loop = numberOfData; loop < aNum + numberOfData ; loop++ )
        {
        number.Format( format, loop + 1 );
        cArray->AppendL( number );
        }

    // Inform list box that data added
    iGrid->HandleItemAdditionL();

    // If item size changes, need to alter the item style
    ApplySelGridGraphicStyleL();

    }

// ---------------------------------------------------------
// CAknExGridContainerAsSelection::RemoveDataL( TInt aNum , TBool aWhere )
// Remove data from the current index.
// ---------------------------------------------------------
//
void CAknExGridContainerAsSelection::RemoveDataL( TInt aNum, TBool aWhere )
    {    
    MDesCArray *array = iGrid->Model()->ItemTextArray();
    CDesCArray *cArray = ( CDesCArray* )array;
  
    // The number of Grid.
    TInt numberOfData = iGrid->GridModel()->NumberOfData();

    // In the case that there is no item in grid.
    if ( numberOfData < 1 )
        {
        TBuf< KLengthOfAboutString > noItem;
        iCoeEnv->ReadResource( noItem, R_AKNEXGRID_TEXT_NO_ITEM );
        iEikonEnv->AlertWin( noItem );
        return;
        }

    // This shows current index item.
    TInt oldCurrIndex = iGrid->CurrentItemIndex();

    // This shows current index which is delete point.
    TInt newCurrIndex = oldCurrIndex;

    // Delete from the current and the number of items to delete is more than the number of items of existing. 
    if ( aWhere )
        {
        if ( numberOfData - oldCurrIndex < aNum )
            {
            aNum = numberOfData - oldCurrIndex;
            }

        newCurrIndex = oldCurrIndex;
        }   
    // In the case that delete all items.
    // Delete from the last and the number of items to delete is more than the number of items of existing.
    else
        {
        if ( ( numberOfData < aNum ) || ( aNum < 0 ) )
            {
            aNum = numberOfData;
            }

        newCurrIndex = numberOfData - aNum;
        }  

    // Delete Items.
    cArray->Delete( newCurrIndex, aNum );
    iGrid->HandleItemRemovalL();

    // Which old current index was deleted or not.
    // Delete from the last and old current index was not deleted. 
    TBool oldCurrIndexWasRemoved = ETrue;
    if ( aWhere && ( oldCurrIndex < numberOfData - aNum ) )
        {
        oldCurrIndexWasRemoved = EFalse;
        }

//    AknListBoxUtils::HandleItemRemovalAndPositionHighlightL( iGrid, oldCurrIndex, oldCurrIndexWasRemoved );

    // If item size changes, need to alter the item style
    ApplySelGridGraphicStyleL();
    }

// ---------------------------------------------------------
// CAknExGridContainerAsSelection::SetVerticalScrollingType( 
//      CAknGridView::TScrollingType aScrollingType )
// set vertical scrolling type to member variables
// ---------------------------------------------------------
//
void CAknExGridContainerAsSelection::SetVerticalScrollingTypeL( 
    CAknGridView::TScrollingType aScrollingType )
    {
    iVerticalScrollingType = aScrollingType;

    SetGridLayoutL();
    }

// ---------------------------------------------------------
// CAknExGridContainerAsSelection::SetHorizontalScrollingType( 
//      CAknGridView::TScrollingType aScrollingType )
// set horizontal scrolling type to member variables
// ---------------------------------------------------------
//
void CAknExGridContainerAsSelection::SetHorizontalScrollingTypeL( 
    CAknGridView::TScrollingType aScrollingType )
    {
    iHorizontalScrollingType = aScrollingType;

    SetGridLayoutL();

    }

// ---------------------------------------------------------
// CAknExGridContainerAsSelection::SetOrientation( 
//      TBool aVerticalOrientation, 
//      TBool aToRight, TBool aToBottom )
// set orientation to member variables
// ---------------------------------------------------------
//
void CAknExGridContainerAsSelection::SetOrientation( 
    TBool aVerticalOrientation, 
    TBool aToRight, TBool aToBottom )
    {
    iVerticalOrientation = aVerticalOrientation;
    iLeftToRight = aToRight;
    iTopToBottom = aToBottom;
    }

// ---------------------------------------------------------
// CAknExGridContainerAsSelection::GetOrientation( 
//      TBool& aVerticalOrientation, 
//      TBool& aToRight, TBool& aToBottom )
// get orientation from member variables
// ---------------------------------------------------------
//
void CAknExGridContainerAsSelection::GetOrientation( 
    TBool& aVerticalOrientation, 
    TBool& aToRight, TBool& aToBottom )
    {
    aVerticalOrientation = iVerticalOrientation;
    aToRight = iLeftToRight;
    aToBottom = iTopToBottom;
    }

// ---------------------------------------------------------
// CAknExGridContainerAsSelection::DetermineFillingOrderL( void )
// show a dialog to determine filling order
// ---------------------------------------------------------
//
void CAknExGridContainerAsSelection::DetermineFillingOrderL( void )
    {
//  // Create the custom dialog
//  CEikDialog* dialog = new ( ELeave ) CAknExGridDialogFillingOrder( this );
//
//  // Launch the dialog
//  if ( dialog->ExecuteLD( R_AKNEXGRID_DIALOG_FILLINGORDER ) )

    // Create the custom dialog
    CEikDialog* dialog = new ( ELeave ) CAknExPopFieldFillingOrder( this );

    // Launch the dialog
    if ( dialog->ExecuteLD( R_POPFIELD_THREE_TEXT_FIELD_DIALOG ) )
        {
        // Redraw the application view with the new co-ordinates.
        SetGridLayoutL();
        }

    }

// ---------------------------------------------------------
// CAknExGridContainerAsSelection::NumberOfColumns()
// get the number of columns and set the number of columns to ChangeSize dialog.
// ---------------------------------------------------------
//
TInt CAknExGridContainerAsSelection::NumberOfColumns()
{
    TInt aNumberOfColumns = iNumOfColumns;

    return aNumberOfColumns;
}

// ---------------------------------------------------------
// CAknExGridContainerAsSelection::NumberOfRows()
// get the number of rows and set the number of rows to ChangeSize dialog.
// ---------------------------------------------------------
//
TInt CAknExGridContainerAsSelection::NumberOfRows()
    {
    TInt aNumberOfRows = iNumOfRows;
    
    return aNumberOfRows;
    }

// ---------------------------------------------------------
// CAknExGridContainerAsSelection::SetNumberOfColumns( TInt iNumberOfColumns )
// Updata the number of columns of Selection Grid with the number of columns in ChangeSize dialog.
// ---------------------------------------------------------
//
void CAknExGridContainerAsSelection::SetNumberOfColumns( TInt aNumberOfColumns )
    {
    iNumOfColumns = aNumberOfColumns;
    }

// ---------------------------------------------------------
// CAknExGridContainerAsSelection::SetNumberOfRows( TInt iNumberOfRows )
// updata the number of rows of Selection Grid with the number of rows in ChangeSize dialog.
// ---------------------------------------------------------
//
void CAknExGridContainerAsSelection::SetNumberOfRows( TInt aNumberOfRows )
    {
    iNumOfRows = aNumberOfRows;
    }

// ---------------------------------------------------------
// CAknExGridContainerAsSelection::DetermineChangeSizeL( void )
// show a dialog to determine Change Size
// ---------------------------------------------------------
//
void CAknExGridContainerAsSelection::DetermineChangeSizeL( void )
    {
    TInt numberOfColumns = NumberOfColumns();
    TInt numberOfRows = NumberOfRows();
    CAknMultiLineDataQueryDialog* dlg = 
        CAknMultiLineDataQueryDialog::NewL(numberOfColumns, numberOfRows);

    if(dlg->ExecuteLD(R_AKNEXGRID_DIALOG_CHANGE_SIZE) == EAknSoftkeyOk)
        {   
        SetNumberOfColumns( numberOfColumns );
        SetNumberOfRows( numberOfRows );
        TRect rect = Rect();
        iSizeOfItems.iWidth = ( rect.iBr.iX - rect.iTl.iX ) / iNumOfColumns;
        iSizeOfItems.iHeight = ( rect.iBr.iY - rect.iTl.iY ) / iNumOfRows;
        SetGridLayoutL();
        
        // If item size changes, need to alter the item style
        ApplySelGridGraphicStyleL();
        }

    }

// ---------------------------------------------------------
// CAknExGridContainerAsSelection::SelectContents( TInt aContents )
// select a kind of contents.
// ---------------------------------------------------------
//
void CAknExGridContainerAsSelection::SelectContents( TInt aContents )
    {
    iContentType = aContents;
    ApplySelGridGraphicStyleL();
    }

// ---------------------------------------------------------
// CAknExGridContainerAsSelection::NumberOfItems()
// Get the number of item in Grid.
// ---------------------------------------------------------
//
TInt CAknExGridContainerAsSelection::NumberOfItems()
    {
    TInt aNumberOfItems = iNumOfItems;
    return aNumberOfItems;
    
    }

// ---------------------------------------------------------
// CAknExGridContainerAsSelection::SetNumberOfitems( TInt iNumberOfColumns )
// update member variables of CAknExGridContainerAsSelection
// ---------------------------------------------------------
//
void CAknExGridContainerAsSelection::SetNumberOfItems( TInt aNumberOfItems )
    {
    iNumOfItems = aNumberOfItems;
    
    }

// ---------------------------------------------------------
// CAknExGridContainerAsSelection::EnterNumberOfItemsL( void )
// show dialog to enter the number of items.
// ---------------------------------------------------------
//
void CAknExGridContainerAsSelection::EnterNumberOfItemsL( void )
    {
    TInt number = NumberOfItems();
    CAknNumberQueryDialog* dlg =
                new (ELeave) CAknNumberQueryDialog(
                                    number,CAknQueryDialog::ENoTone);
    dlg->SetEmergencyCallSupport( EFalse );
    if(dlg->ExecuteLD(R_AKNEXGRID_DIALOG_NUMBEROFITEMS) == EAknSoftkeyOk)
        {
        SetNumberOfItems( number );
        }

    }

// ---------------------------------------------------------
// CAknExGridContainerAsSelection::CreateGridResourceL( void )
// prepare resources for the grid
// ---------------------------------------------------------
//
void CAknExGridContainerAsSelection::CreateGridResourceL( void )
    {

    // load graphics
    LoadGraphicsL();

    // create data
    AddDataL( iNumOfItems );

    }

// ---------------------------------------------------------
// CAknExGridContainerAsSelection::LoadGraphicsL( void )
// load bitmap resources 
// ---------------------------------------------------------
//
void CAknExGridContainerAsSelection::LoadGraphicsL( void )
    {
    TBuf< KLengthOfPathEikonMbm > pathAppMbm;
    iCoeEnv->ReadResource( pathAppMbm, R_AKNEXGRID_PATH_AKNEXGRID_MBM );
//    TBuf< KLengthOfPathEikonMbm > pathAppZMbm;
//    iCoeEnv->ReadResource( pathAppZMbm, R_AKNEXGRID_PATH_AKNEXGRID_MBM_Z_DRIVE );

    CArrayPtr< CGulIcon >* icons
        = new(ELeave) CAknIconArray(KNumberOfBitmap);
    CleanupStack::PushL( icons );

    // Create icon bitmap and mask.
    if ( iGridType == EAknExGridMarkableGrid )
        {
        CFbsBitmap* bitmap = iEikonEnv->CreateBitmapL( pathAppMbm, EMbmAknexgridGriditem );
        CleanupStack::PushL( bitmap );

        CFbsBitmap* mask = iEikonEnv->CreateBitmapL( pathAppMbm, EMbmAknexgridGriditemm );
        CleanupStack::PushL( mask );
        icons->AppendL( CGulIcon::NewL( bitmap, mask ) );

        CleanupStack::Pop(); // mask
        CleanupStack::Pop(); // bitmap
        }
    else
        {
        CFbsBitmap* bitmap = iEikonEnv->CreateBitmapL( pathAppMbm, EMbmAknexgridGriditem );
        CleanupStack::PushL( bitmap );

        CFbsBitmap* mask = iEikonEnv->CreateBitmapL( pathAppMbm, EMbmAknexgridGriditemm );
        CleanupStack::PushL( mask );
        icons->AppendL( CGulIcon::NewL( bitmap, mask ) );

        CleanupStack::Pop(); // mask
        CleanupStack::Pop(); // bitmap
        }

    // If markable grid, add marks (on/off)
    if ( iGridType == EAknExGridMarkableGrid )
        {
        // mark (off)
        CFbsBitmap* bitmap2 = iEikonEnv->CreateBitmapL( pathAppMbm, EMbmAknexgridMarkoff );
        CleanupStack::PushL( bitmap2 );
        CFbsBitmap* mask2 = iEikonEnv->CreateBitmapL( pathAppMbm, EMbmAknexgridMarkm );
        CleanupStack::PushL( mask2 );
        icons->AppendL(CGulIcon::NewL( bitmap2, mask2 ));
        CleanupStack::Pop(); // mask
        CleanupStack::Pop(); // bitmap

        // mark (on)
        CFbsBitmap* bitmap3 = iEikonEnv->CreateBitmapL( pathAppMbm, EMbmAknexgridMarkon );
        CleanupStack::PushL( bitmap3 );
        CFbsBitmap* mask3 = iEikonEnv->CreateBitmapL( pathAppMbm, EMbmAknexgridMarkm );
        CleanupStack::PushL( mask3 );
        icons->AppendL(CGulIcon::NewL( bitmap3, mask3 ));
        CleanupStack::Pop(); // mask
        CleanupStack::Pop(); // bitmap
        }

    // Set icon array.
    iGrid->ItemDrawer()->FormattedCellData()->SetIconArrayL( icons );
    CleanupStack::Pop(); // icons array

    }

// ---------------------------------------------------------
// CAknExGridContainerAsSelection::SetGridLayoutL( void )
// set layout to the grid
// ---------------------------------------------------------
//
void CAknExGridContainerAsSelection::SetGridLayoutL( void )
    {
    // If the grid is created as a menu, iGrid may be NULL.
    if ( iGrid )
        {
        if ( iVerticalOrientation )
            {
            iGrid->SetLayoutL( iVerticalOrientation, iLeftToRight, iTopToBottom, 
                iNumOfRows, iNumOfColumns, iSizeOfItems );
            iGrid->SetPrimaryScrollingType( iVerticalScrollingType );
            iGrid->SetSecondaryScrollingType( iHorizontalScrollingType );
            }
        else
            {
            iGrid->SetLayoutL( iVerticalOrientation, iLeftToRight, iTopToBottom, 
                iNumOfColumns, iNumOfRows, iSizeOfItems );
            iGrid->SetPrimaryScrollingType( iHorizontalScrollingType );
            iGrid->SetSecondaryScrollingType( iVerticalScrollingType );
            }

        iGrid->SetCurrentDataIndex( 0 );

        DrawNow();
        }
    }

// ---------------------------------------------------------
// CAknExGridContainerAsSelection::ApplySelGridGraphicStyleL( void )
// set layout to cells in the grid
// ---------------------------------------------------------
//
void CAknExGridContainerAsSelection::ApplySelGridGraphicStyleL( void )
    {

    if ( !iGrid ) 
        {
        return;
        }

    //AknListBoxLayouts::SetupStandardFormListbox( iGrid->ItemDrawer() );
    AknListBoxLayouts::SetupStandardGrid( *iGrid );

    TInt grWidth = 0;
    TInt txWidth = 0;

    switch ( iContentType )
        {
        case EContainText :
            txWidth = iGrid->ColumnWidth();
            break;

        case EContainGraphic :
            grWidth = iGrid->ColumnWidth();
            break;

        case EContainBoth :
            grWidth = iGrid->ColumnWidth() / KTextAreaRatio;
            txWidth = iGrid->ColumnWidth() - grWidth;
            break;
            
        default :
            break;
        }

    // layout of the graphic
    // If markable grid
    if ( iGridType == EAknExGridMarkableGrid )
        {
        TInt markTop ( iGrid->ItemHeight() - KAknExGridMarkSize );
        
        // Setup cell for showing icon.
        AknListBoxLayouts::SetupFormGfxCell(
            *iGrid, iGrid->ItemDrawer(),
            KAknExGridMarkableIconPosition, // index of "Icon" in icon array.
            KAknExGridItemLeft, KAknExGridItemTop,
            0, 0, // these arguments are "Reserved"
            grWidth, markTop,
            TPoint( KAknExGridItemLeft, KAknExGridItemTop),
            TPoint ( grWidth, markTop )
            );

        // Setup cell for showing mark.
        AknListBoxLayouts::SetupFormGfxCell(
            *iGrid, iGrid->ItemDrawer(),
            KAknExGridMarkableMarkPosition, // index of "Mark(off)" in array.
            KAknExGridItemLeft, markTop,    // left/top in drawing area.
            0, 0, // these arguments are "Reserved"
            KAknExGridMarkSize, KAknExGridMarkSize,
            TPoint( KAknExGridItemLeft, markTop),
            TPoint ( grWidth, iGrid->ItemHeight())
            );

        // Setup in order to mark on/off
        iGrid->ItemDrawer()->SetItemMarkPosition(
                                        KAknExGridMarkableMarkPosition);
        iGrid->ItemDrawer()->SetItemMarkReplacement(
                                        KAknExGridMarkableMarkReplace);
        iGrid->ItemDrawer()->SetItemMarkReverse(ETrue);
        }
    // else
    else
        {
        AknListBoxLayouts::SetupFormGfxCell( *iGrid, iGrid->ItemDrawer(),
            KIndexOfGraphic, 0, 0, 0, 0,  grWidth, iGrid->ItemHeight(), 
            TPoint( 0, 0 ), TPoint( grWidth, iGrid->ItemHeight() ));
        }

    const CFont* fontText = LatinBold12();
    // layout of text
    if ( iGridType == EAknExGridMarkableGrid )
        {
        AknListBoxLayouts::SetupFormTextCell(
                *iGrid, iGrid->ItemDrawer(),
                KAknExGridMarkableTextPosition, fontText, 
                KDefaultTextColor, 
                grWidth, 0, 
                fontText->HeightInPixels(),
                txWidth, 
                CGraphicsContext::ELeft,
                TPoint( grWidth, 0 ), 
                TPoint( iGrid->ColumnWidth(), iGrid->ItemHeight() )
                );
        }
    else
        {
        AknListBoxLayouts::SetupFormTextCell( *iGrid, iGrid->ItemDrawer(),
                KIndexOfText, fontText, 
                KDefaultTextColor, 
                grWidth, 0, 
                fontText->HeightInPixels(),
                txWidth, 
                CGraphicsContext::ELeft,
                TPoint( grWidth, 0 ), 
                TPoint( iGrid->ColumnWidth(), iGrid->ItemHeight() )
                );
        }

    DrawNow();
    }

// ---------------------------------------------------------
// CAknExGridContainerAsSelection::CheckIndex( void )
// show current index
// ---------------------------------------------------------
//
void CAknExGridContainerAsSelection::CheckIndex( void )
    {
    // Counter of the number of marked item
    TInt selectedItemCount = 0;

    // Load message.
    TBuf< KLengthOfStringToShowIndex > number;
    TBuf< KLengthOfStringToShowIndex > format;
    iCoeEnv->ReadResource( format, R_AKNEXGRID_FORMATSTRING_CURRENTINDEX );

    if ( iGridType == EAknExGridMarkableGrid )
        {
        // The number of items.
        TInt numberOfData = iGrid->GridModel()->NumberOfData();

        // Check marked item. And if the item is marked,display dialog. 
        for ( TInt checkData = 0; checkData < numberOfData; checkData++ )
            {
            CListBoxView* view = iGrid->View();
     
            if ( view->ItemIsSelected( checkData ) )
                {
                selectedItemCount++;

                // display dialog.
                number.Format( format, checkData );
                iEikonEnv->AlertWin( number );
                }
            }
        if (selectedItemCount == 0)
            {
            number.Format( format, -1 );
            iEikonEnv->AlertWin( number );
            }
        return;
        }
    
    // if "Selection Grid",
    // display the result of current index.
    else if ( iGridType == EAknExGridSelectionGrid )
        {
        // we do a check of the position and index functions here
        // as well as giving the current index
        TInt currentIndex = iGrid->CurrentDataIndex();
        TPoint currentPos = iGrid->PositionAtIndex( currentIndex );
        TInt index = iGrid->IndexOfPosition( currentPos );
        if ( index == currentIndex )
            {
            number.Format( format, currentIndex );
            iEikonEnv->AlertWin( number );
            }
        }


    }

// ---------------------------------------------------------
// CAknExGridContainerAsSelection::MarkAllItems(TInt aCommand )
// Select/Deselect/Toggle selection of all items.
// ---------------------------------------------------------
//
void CAknExGridContainerAsSelection::MarkAllItemsL( TInt aCommand )
    {

    if ( iGridType == EAknExGridMarkableGrid )
        {
        // Get number of items.
        TInt numberOfData = iGrid->GridModel()->NumberOfData();
        CListBoxView* gridView = iGrid->View();

        // execute specified method of each items.
        for ( TInt index = 0; index < numberOfData; index++ )
            {
            switch ( aCommand )
                {
                case EAknExGridCmdSelectAll:    // Select the item
                    gridView->SelectItemL( index );
                    break;

                case EAknExGridCmdDeselectAll:  // Do not select the item
                    gridView->DeselectItem( index );
                    break;

                case EAknExGridCmdToggle:   // toggle selection
                    gridView->ToggleItemL( index );
                    break;
                }
            }
        }
    }



// ---------------------------------------------------------
// CAknExGridContainerAsSelection::SizeChanged()
// Called by framework when the view size is changed
// ---------------------------------------------------------
//
void CAknExGridContainerAsSelection::SizeChanged()
    {
    if ( iGrid )
        {
        iGrid->SetRect( Rect() );
        }
    }

// ---------------------------------------------------------
// CAknExGridContainerAsSelection::CountComponentControls() const
// return the number of controls
// ---------------------------------------------------------
//
TInt CAknExGridContainerAsSelection::CountComponentControls() const
    {
    // return number of controls inside this container
    return KNumberOfComponentSelection; 
    }

// ---------------------------------------------------------
// CAknExGridContainerAsSelection::ComponentControl(TInt aIndex) const
// return the pointer to specified control.
// ---------------------------------------------------------
//
CCoeControl* CAknExGridContainerAsSelection::ComponentControl( TInt aIndex ) const
    {
    switch ( aIndex )
        {
        case ELabel:
            return iLabel;
        case EDoLabel:
            return iToDoLabel;
        case EGrid:
            return iGrid;
        default:
            return NULL;
        }
    }

// ---------------------------------------------------------
// CAknExGridContainerAsSelection::Draw(const TRect& aRect) const
// handle the message when client region must be redrawn.
// ---------------------------------------------------------
//
void CAknExGridContainerAsSelection::Draw( const TRect& /*aRect*/ ) const
    {
    }

// ---------------------------------------------------------
// CAknExGridContainer::OfferKeyEventL(
//           const TKeyEvent& aKeyEvent, TEventCode aType )
// Handles the key events.
// ---------------------------------------------------------
//
TKeyResponse CAknExGridContainerAsSelection::OfferKeyEventL(
        const TKeyEvent& aKeyEvent, TEventCode aType )
    {
    TInt code = aKeyEvent.iCode;

    if ( iGrid ) 
        {
        if ( code == EKeyEnter || code == EKeyOK )
            {
            TBool shiftKeyPressed = (aKeyEvent.iModifiers & EModifierShift);
            if (!shiftKeyPressed)
                {
                CheckIndex();   // show the current index
                return( EKeyWasConsumed );
                }
            else
                {
                return iGrid->OfferKeyEventL( aKeyEvent, aType );
                }
            }
        else
            {
            return iGrid->OfferKeyEventL( aKeyEvent, aType );
            }
        }

    return( EKeyWasNotConsumed );
    }

// ---------------------------------------------------------
// CAknExGridContainerAsSelection::HandleControlEventL(
//     CCoeControl* aControl,TCoeEvent aEventType)
// handle event from observed control.
// ---------------------------------------------------------
//
void CAknExGridContainerAsSelection::HandleControlEventL(
    CCoeControl* /*aControl*/, TCoeEvent /*aEventType*/ )
    {
    }

TBool CAknExGridContainerAsSelection::AutoTestL()
    {
    CEikStatusPane* sp = iEikonEnv->AppUiFactory()->StatusPane();
    CAknTitlePane* titlePane = (CAknTitlePane *)sp->ControlL(TUid::Uid(EEikStatusPaneUidTitle));

    iTestNumber++;

    switch(iTestNumber)
        {
        case ESelectionTest1:
            titlePane->SetTextL((*iTitles)[ESelectionTest1]);
            break;

        case ESelectionTest2:
            {
            titlePane->SetTextL((*iTitles)[ESelectionTest2]);
            TBuf< KLengthOfAboutString > aboutString;
            iCoeEnv->ReadResource( aboutString, R_AKNEXGRID_TEXT_ABOUT_SELECTION );
            iEikonEnv->AlertWin( aboutString );
            break;
            }

        case ESelectionTest3:
            titlePane->SetTextL((*iTitles)[ESelectionTest3]);
            InsertDataL( 1 );
            break;

        case ESelectionTest4:
            titlePane->SetTextL((*iTitles)[ESelectionTest4]);
            AddDataL( 5 );
            break;

        case ESelectionTest5:
            titlePane->SetTextL((*iTitles)[ESelectionTest5]);
            RemoveDataL( 1 , KRemoveFromCurrent);
            break;

        case ESelectionTest6:
            titlePane->SetTextL((*iTitles)[ESelectionTest6]);
            RemoveDataL( 5 , KRemoveFromLast );
            break;

        case ESelectionTest7:
            titlePane->SetTextL((*iTitles)[ESelectionTest7]);
            RemoveDataL( KRemoveAllItems , KRemoveFromLast);
            break;

        case ESelectionTest8:
            titlePane->SetTextL((*iTitles)[ESelectionTest8]);
            AddDataL( iNumOfItems );
            iVerticalOrientation = EFalse;
            iTopToBottom = EFalse;
            iLeftToRight = EFalse;
            SetGridLayoutL();
            break;

        case ESelectionTest9:
            titlePane->SetTextL((*iTitles)[ESelectionTest9]);
            iVerticalOrientation = ETrue;
            iTopToBottom = ETrue;
            iLeftToRight = ETrue;
            SetGridLayoutL();
            SetVerticalScrollingTypeL( CAknGridView::EScrollIncrementLineAndLoops );
            SetHorizontalScrollingTypeL( CAknGridView::EScrollIncrementLineAndLoops );
            break;

        case ESelectionTest10:
            titlePane->SetTextL((*iTitles)[ESelectionTest10]);
            SetVerticalScrollingTypeL( CAknGridView::EScrollIncrementLineAndStops );
            SetHorizontalScrollingTypeL( CAknGridView::EScrollIncrementLineAndStops );
            break;

        case ESelectionTest11:
            titlePane->SetTextL((*iTitles)[ESelectionTest11]);
            SetVerticalScrollingTypeL( CAknGridView::EScrollFollowsGrid );
            SetHorizontalScrollingTypeL( CAknGridView::EScrollFollowsGrid );
            break;

        case ESelectionTest12:
            titlePane->SetTextL((*iTitles)[ESelectionTest12]);
            SetVerticalScrollingTypeL( CAknGridView::EScrollStops );
            SetHorizontalScrollingTypeL( CAknGridView::EScrollStops );
            break;

        case ESelectionTest13:
            titlePane->SetTextL((*iTitles)[ESelectionTest13]);
            SetVerticalScrollingTypeL( CAknGridView::EScrollIncrementLineAndLoops );
            SetHorizontalScrollingTypeL( CAknGridView::EScrollIncrementLineAndLoops );
            SelectContents( EContainText );
            break;

        case ESelectionTest14:
            titlePane->SetTextL((*iTitles)[ESelectionTest14]);
            SelectContents( EContainGraphic );
            break;

        case ESelectionTest15:
            titlePane->SetTextL((*iTitles)[ESelectionTest15]);
            SelectContents( EContainBoth );
            break;

        case ESelectionTest16:
            {
            titlePane->SetTextL((*iTitles)[ESelectionTest16]);
            SetNumberOfColumns( 3 );
            SetNumberOfRows( 3 );
            TRect rect = Rect();
            iSizeOfItems.iWidth = ( rect.iBr.iX - rect.iTl.iX ) / iNumOfColumns;
            iSizeOfItems.iHeight = ( rect.iBr.iY - rect.iTl.iY ) / iNumOfRows;
            SetGridLayoutL();
            ApplySelGridGraphicStyleL();
            break;
            }

        case ESelectionTest17:
            {
            titlePane->SetTextL((*iTitles)[ESelectionTest17]);
            SetNumberOfColumns( 5 );
            SetNumberOfRows( 5 );
            TRect rect = Rect();
            iSizeOfItems.iWidth = ( rect.iBr.iX - rect.iTl.iX ) / iNumOfColumns;
            iSizeOfItems.iHeight = ( rect.iBr.iY - rect.iTl.iY ) / iNumOfRows;
            SetGridLayoutL();
            ApplySelGridGraphicStyleL();
            break;
            }

        case ESelectionTest18:
            {
            titlePane->SetTextL((*iTitles)[ESelectionTest18]);
            SetNumberOfColumns( 10 );
            SetNumberOfRows( 10 );
            TRect rect = Rect();
            iSizeOfItems.iWidth = ( rect.iBr.iX - rect.iTl.iX ) / iNumOfColumns;
            iSizeOfItems.iHeight = ( rect.iBr.iY - rect.iTl.iY ) / iNumOfRows;
            SetGridLayoutL();
            ApplySelGridGraphicStyleL();
            break;
            }

        default:
            return ETrue;
        }

    return EFalse;
    }

// End of File  
