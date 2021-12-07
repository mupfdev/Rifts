/*
* ============================================================================
*  Name     : CAknExGridContainerAsMenu from CAknExGridContainerAsSelection
*  Part of  : AknExGrid
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES

#include <eiklabel.h>       // for example label control
#include <aknutils.h>       // definition of AKN_LAF_COLOR()
#include <coemain.h>        // to use iCoeEnv
#include <aknlists.h>
#include <AknGrid.h>
#include <aknPopup.h>       // PopupList
#include <gulicon.h>
#include <akntitle.h>

#include <AknQueryDialog.h>
#include <AknExGrid.rsg>    // Dialog
#include "AknExGridContainerAsMenu.h"
#include "AknExGrid.hrh"
#include "AknExGridDialogFillingOrder.h"
#include "AknExGridDialogChangeSize.h"

// CONSTANTS
const TInt KGridViewWidth = 169;     // grid view width
const TInt KGridViewHeight = 103;    // grid view height

const TInt KLengthOfMenuAboutString = 40;

// ================= MEMBER FUNCTIONS =======================

// C++ default constructor can NOT contain any code, that
// might leave.
//
CAknExGridContainerAsMenu::CAknExGridContainerAsMenu()
                        : iLabel( NULL ), iToDoLabel( NULL )
    {
    }



// EPOC default constructor can leave.
void CAknExGridContainerAsMenu::ConstructL( const TRect& aRect )
    {
    CreateWindowL();

    TBuf< KLengthOfLabel > label;
    iLabel = new( ELeave ) CEikLabel;
    iLabel->SetContainerWindowL( *this );
    iCoeEnv->ReadResource( label, R_AKNEXGRID_LABEL_VIEW_AS_MENU );
    iLabel->SetTextL( label );

    TBuf< KLengthOfDoLabel > dolabel;
    iToDoLabel = new( ELeave ) CEikLabel;
    iToDoLabel->SetContainerWindowL( *this );
    iCoeEnv->ReadResource( dolabel, R_AKNEXGRID_DOLABEL_VIEW_AS_MENU );
    iToDoLabel->SetTextL( dolabel );

    iTestNumber = 0;

    iTitles = iCoeEnv->ReadDesCArrayResourceL(R_AKNEXGRID_TITLE_MENU);
    CEikStatusPane* sp = iEikonEnv->AppUiFactory()->StatusPane();
    CAknTitlePane* titlePane = (CAknTitlePane *)sp->ControlL(TUid::Uid(EEikStatusPaneUidTitle));
    titlePane->SetTextL((*iTitles)[EMenuTest1]);

    // set initial params for the grid
    iVerticalOrientation = EFalse;
    iTopToBottom = ETrue;
    iLeftToRight = ETrue;
    iNumOfColumns = KNumOfColumnsInMenu;
    iNumOfRows = KNumOfRowsInMenu;
    iNumOfItems = KInitialNumOfItemsInMenu;
    iContentType = EContainGraphic;

    iVerticalScrollingType = CAknGridView::EScrollIncrementLineAndLoops;
    iHorizontalScrollingType = CAknGridView::EScrollIncrementLineAndLoops;

    SetRect( aRect );
    ActivateL();
    }

// destructor
CAknExGridContainerAsMenu::~CAknExGridContainerAsMenu()
    {
    delete iLabel;
    delete iToDoLabel;
    //delete iGrid;
    delete iTitles;
    }

// ---------------------------------------------------------
// CAknExGridContainerAsMenu::ShowGridInMenuL( void )
// create a grid in the menu and show it.
// ---------------------------------------------------------
//
void CAknExGridContainerAsMenu::ShowGridInMenuL( void )
    {

    iGrid = new( ELeave ) CAknGrid;

    CAknPopupList* popupList = CAknPopupList::NewL( iGrid, R_AVKON_SOFTKEYS_SELECT_BACK );
    CleanupStack::PushL(popupList); 
    
    iGrid->ConstructL( popupList, CEikListBox::ELeftDownInViewRect );

    // adjust the size of cells to the number of columns.
//    TRect rect = Rect();
//    iSizeOfItems.iWidth = ( rect.iBr.iX - rect.iTl.iX ) / iNumOfColumns; 
//    iSizeOfItems.iHeight =  iSizeOfItems.iWidth;
    iSizeOfItems.iWidth = KGridViewWidth / iNumOfColumns; 
    iSizeOfItems.iHeight = KGridViewHeight / iNumOfRows;
    SetGridLayoutL();

    CreateGridResourceL();

    // add title
    TBuf< KLengthOfTitle > title;
    iCoeEnv->ReadResource( title, R_AKNEXGRID_TEXT_MENUGRID_TITLE );
    popupList->SetTitleL( title );

    TInt popupOk = popupList->ExecuteLD();
    CleanupStack::Pop();            // popupList
    if (popupOk)
        {
        CheckIndex();
        }

    delete iGrid;
    iGrid = NULL;
    }

// ---------------------------------------------------------
// CAknExGridContainerAsMenu::SizeChanged()
// Called by framework when the view size is changed
// ---------------------------------------------------------
//
void CAknExGridContainerAsMenu::SizeChanged()
    {
    iLabel->SetExtent( VIEW_MENU_LABEL_POINT, iLabel->MinimumSize() );
    iToDoLabel->SetExtent( VIEW_MENU_DOLABEL_POINT, iToDoLabel->MinimumSize() );
    }

// ---------------------------------------------------------
// CAknExGridContainerAsMenu::CountComponentControls() const
// return the number of controls
// ---------------------------------------------------------
//
TInt CAknExGridContainerAsMenu::CountComponentControls() const
    {
    // return number of controls inside this container
    return KNumberOfComponentMenu; 
    }

// ---------------------------------------------------------
// CAknExGridContainerAsMenu::ComponentControl(TInt aIndex) const
// return the pointer to specified control.
// ---------------------------------------------------------
//
CCoeControl* CAknExGridContainerAsMenu::ComponentControl( TInt aIndex ) const
    {
    switch ( aIndex )
        {
        case ELabel:
            return iLabel;
        case EDoLabel:
            return iToDoLabel;
        default:
            return NULL;
        }
    }

// ---------------------------------------------------------
// CAknExGridContainerAsMenu::Draw(const TRect& aRect) const
// handle the message when client region must be redrawn.
// ---------------------------------------------------------
//
void CAknExGridContainerAsMenu::Draw( const TRect& aRect ) const
    {
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KRgbDarkCyan );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.DrawRect( aRect );
    }


// ---------------------------------------------------------
// CAknExGridContainerAsMenu::HandleControlEventL(
//     CCoeControl* aControl,TCoeEvent aEventType)
// handle event from observed control.
// ---------------------------------------------------------
//
void CAknExGridContainerAsMenu::HandleControlEventL(
    CCoeControl* /*aControl*/, TCoeEvent /*aEventType*/ )
    {
    }

// ---------------------------------------------------------
// CAknExGridContainerAsMenu::DetermineChangeSizeL( void )
// show a dialog to determine Change Size
// ---------------------------------------------------------
//
void CAknExGridContainerAsMenu::DetermineChangeSizeL( void )
    {
    TInt numberOfColumns = NumberOfColumns();
    TInt numberOfRows = NumberOfRows();
    CAknMultiLineDataQueryDialog* dlg = 
    CAknMultiLineDataQueryDialog::NewL(numberOfColumns, numberOfRows);

    if(dlg->ExecuteLD(R_AKNEXGRID_DIALOG_CHANGE_SIZE) == EAknSoftkeyOk)
        {   
        SetNumberOfColumns( numberOfColumns );
        SetNumberOfRows( numberOfRows );
        iSizeOfItems.iWidth = KGridViewWidth / iNumOfColumns; 
        iSizeOfItems.iHeight = KGridViewHeight / iNumOfRows;
        SetGridLayoutL();
        
        // If item size changes, need to alter the item style
        ApplySelGridGraphicStyleL();
        }

    }

TBool CAknExGridContainerAsMenu::AutoTestL()
    {
    CEikStatusPane* sp = iEikonEnv->AppUiFactory()->StatusPane();
    CAknTitlePane* titlePane = (CAknTitlePane *)sp->ControlL(TUid::Uid(EEikStatusPaneUidTitle));

    iTestNumber++;

    switch(iTestNumber)
        {
        case EMenuTest1:
            titlePane->SetTextL((*iTitles)[EMenuTest1]);
            break;

        case EMenuTest2:
            {
            titlePane->SetTextL((*iTitles)[EMenuTest2]);
            TBuf< KLengthOfMenuAboutString > aboutString;

            iCoeEnv->ReadResource( aboutString, R_AKNEXGRID_TEXT_ABOUT_MENU );
            iEikonEnv->AlertWin( aboutString );
            break;
            }

        case EMenuTest3:
            {
            titlePane->SetTextL((*iTitles)[EMenuTest3]);
            ShowGridInMenuL();
            break;
            }

        case EMenuTest4:
            {
            titlePane->SetTextL((*iTitles)[EMenuTest4]);
            SetNumberOfItems( 45 );
            ShowGridInMenuL();
            break;
            }

        case EMenuTest5:
            {
            titlePane->SetTextL((*iTitles)[EMenuTest5]);
            SetNumberOfItems( 2 );
            ShowGridInMenuL();
            break;
            }

        case EMenuTest6:
            {
            titlePane->SetTextL((*iTitles)[EMenuTest6]);
            SetNumberOfItems( 27 );
            SetNumberOfColumns( 3 );
            SetNumberOfRows( 3 );
            iSizeOfItems.iWidth = KGridViewWidth / iNumOfColumns; 
            iSizeOfItems.iHeight = KGridViewHeight / iNumOfRows;
            SetGridLayoutL();
            ShowGridInMenuL();
            break;
            }

        case EMenuTest7:
            {
            titlePane->SetTextL((*iTitles)[EMenuTest7]);
            SetNumberOfColumns( 9 );
            SetNumberOfRows( 5 );
            iSizeOfItems.iWidth = KGridViewWidth / iNumOfColumns; 
            iSizeOfItems.iHeight = KGridViewHeight / iNumOfRows;
            SetGridLayoutL();
            ShowGridInMenuL();
            break;
            }

        case EMenuTest8:
            {
            titlePane->SetTextL((*iTitles)[EMenuTest8]);
            SetNumberOfColumns( 9 );
            SetNumberOfRows( 3 );
            iSizeOfItems.iWidth = KGridViewWidth / iNumOfColumns; 
            iSizeOfItems.iHeight = KGridViewHeight / iNumOfRows;
            SetGridLayoutL();
            ShowGridInMenuL();
            break;
            }

        case EMenuTest9:
            {
            titlePane->SetTextL((*iTitles)[EMenuTest9]);
            SetNumberOfItems( 10 );
            SetNumberOfColumns( 4 );
            SetNumberOfRows( 3 );
            iVerticalOrientation = ETrue;
            iTopToBottom = EFalse;
            iLeftToRight = EFalse;
            SetGridLayoutL();
            ShowGridInMenuL();
            break;
            }

        case EMenuTest10:
            {
            titlePane->SetTextL((*iTitles)[EMenuTest10]);
            SetNumberOfItems( 27 );
            SetNumberOfColumns( 9 );
            SetNumberOfRows( 3 );
            iVerticalOrientation = EFalse;
            iTopToBottom = ETrue;
            iLeftToRight = ETrue;
            SetVerticalScrollingTypeL( CAknGridView::EScrollIncrementLineAndLoops );
            SetHorizontalScrollingTypeL( CAknGridView::EScrollIncrementLineAndLoops );
            ShowGridInMenuL();
            break;
            }

        case EMenuTest11:
            {
            titlePane->SetTextL((*iTitles)[EMenuTest11]);
            SetVerticalScrollingTypeL( CAknGridView::EScrollIncrementLineAndStops );
            SetHorizontalScrollingTypeL( CAknGridView::EScrollIncrementLineAndStops );
            ShowGridInMenuL();
            break;
            }

        case EMenuTest12:
            {
            titlePane->SetTextL((*iTitles)[EMenuTest12]);
            SetVerticalScrollingTypeL( CAknGridView::EScrollFollowsGrid );
            SetHorizontalScrollingTypeL( CAknGridView::EScrollFollowsGrid );
            ShowGridInMenuL();
            break;
            }

        case EMenuTest13:
            {
            titlePane->SetTextL((*iTitles)[EMenuTest13]);
            SetVerticalScrollingTypeL( CAknGridView::EScrollStops );
            SetHorizontalScrollingTypeL( CAknGridView::EScrollStops );
            ShowGridInMenuL();
            break;
            }

        default:
            return ETrue;
        }

    return EFalse;
    }

// End of File  
