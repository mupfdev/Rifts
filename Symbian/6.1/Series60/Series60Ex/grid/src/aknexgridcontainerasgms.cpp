/*
* ============================================================================
*  Name     : CAknExGridContainerAsGMS from CAknExGridContainerAsSelection
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

#include <AknIconArray.h>

#include <AknExGrid.rsg>    // Dialog
#include <AknExGrid.mbg>    // Bitmap

#include "AknGMSStyleGrid.h"
#include "AknExGridContainerAsGMS.h"
#include "AknExGrid.hrh"
#include "AknExGridDialogFillingOrder.h"
#include "AknExGridDialogChangeSize.h"

// ================= MEMBER FUNCTIONS =======================

// C++ default constructor can NOT contain any code, that
// might leave.
//
CAknExGridContainerAsGMS::CAknExGridContainerAsGMS()
                        : iGridGMS( NULL )
    {
    }

// EPOC default constructor can leave.
void CAknExGridContainerAsGMS::ConstructL( const TRect& aRect )
    {
    CreateWindowL();

    iTestNumber = 0;

    iTitles = iCoeEnv->ReadDesCArrayResourceL(R_AKNEXGRID_TITLE_GMS);
    CEikStatusPane* sp = iEikonEnv->AppUiFactory()->StatusPane();
    CAknTitlePane* titlePane = (CAknTitlePane *)sp->ControlL(TUid::Uid(EEikStatusPaneUidTitle));
    titlePane->SetTextL((*iTitles)[EGMSTest1]);

    iGridGMS = CAknGMSStyleGrid::NewL(this);
    iGridGMS->SetContainerWindowL(*this);

    TBuf< KLengthOfPathEikonMbm > pathAppMbm;
    iCoeEnv->ReadResource( pathAppMbm, R_AKNEXGRID_PATH_AKNEXGRID_MBM );

    CArrayPtr<CGulIcon>* icons = 
            new(ELeave) CAknIconArray(KInitialNumOfItemsInGMS);
    CleanupStack::PushL(icons);

    CGulIcon* newIcon1 = CEikonEnv::Static()->CreateIconL(
                                pathAppMbm,
                                EMbmAknexgridGriditem, 
                                EMbmAknexgridGriditemm);
    CleanupStack::PushL(newIcon1);

    CGulIcon* newIcon2 = CEikonEnv::Static()->CreateIconL(
                                pathAppMbm,
                                EMbmAknexgridBlacktextonwhite_wbmp);
    CleanupStack::PushL(newIcon2);

    CGulIcon* newIcon3 = CEikonEnv::Static()->CreateIconL(
                                pathAppMbm,
                                EMbmAknexgridWhitetextonblack_wbmp);
    CleanupStack::PushL(newIcon3);

    CGulIcon* newIcon4 = CEikonEnv::Static()->CreateIconL(
                                pathAppMbm,
                                EMbmAknexgridBlacktextonwhite_ota);
    CleanupStack::PushL(newIcon4);

    CGulIcon* newIcon5 = CEikonEnv::Static()->CreateIconL(
                                pathAppMbm,
                                EMbmAknexgridWhitetextonblack_ota);
    CleanupStack::PushL(newIcon5);

    CGulIcon* onImage = CEikonEnv::Static()->CreateIconL(
                                pathAppMbm,
                                EMbmAknexgridMarkon, 
                                EMbmAknexgridMarkm);
    CleanupStack::PushL(onImage);

    CGulIcon* offImage = CEikonEnv::Static()->CreateIconL(
                                pathAppMbm,
                                EMbmAknexgridMarkoff, 
                                EMbmAknexgridMarkm);
    CleanupStack::PushL(offImage);

    icons->AppendL( onImage );
    icons->AppendL( offImage );
    icons->AppendL( newIcon1 );
    icons->AppendL( newIcon2 );
    icons->AppendL( newIcon3 );
    icons->AppendL( newIcon4 );
    icons->AppendL( newIcon5 );

    iGridGMS->ItemDrawer()->FormattedCellData()->SetIconArrayL(icons);

    CleanupStack::Pop(); // offImage
    CleanupStack::Pop(); // onImage
    CleanupStack::Pop(); // newIcon5
    CleanupStack::Pop(); // newIcon4
    CleanupStack::Pop(); // newIcon3
    CleanupStack::Pop(); // newIcon2
    CleanupStack::Pop(); // newIcon1
    CleanupStack::Pop(); // icons
   
    TBuf< KLengthOfItemResourceString > format;
    iCoeEnv->ReadResource( format, R_AKNEXGRID_FORMATSTRING_GMSGRID );

    CDesCArray* array = new (ELeave) CDesCArrayFlat(KInitialNumOfItemsInGMS);
    for (TInt loop = 0; loop < KInitialNumOfItemsInGMS; loop ++)
        {
        TBuf< KLengthOfItemResourceString > string;
        if (loop<4)
            string.Format(format, loop+3);
        else
            string.Format(format, 2);
        array->AppendL(string);
        }
    iGridGMS->Model()->SetItemTextArray(array); // OWNS
      
    iGridGMS->SetupLayout();

    SetRect(aRect);
    ActivateL();

    iGridGMS->HandleItemAdditionL();          // Update the grid size

    }

// destructor
CAknExGridContainerAsGMS::~CAknExGridContainerAsGMS()
    {
    delete iGridGMS;
    delete iTitles;
    }

// ---------------------------------------------------------
// CAknExGridContainerAsGMS::ShowPopupGMSGridL( void )
// create a popup GMS grid and show it.
// ---------------------------------------------------------
//
void CAknExGridContainerAsGMS::ShowPopupGMSGridL( void )
    {

    CAknGMSStyleGrid* aGMSGrid = new (ELeave)CAknGMSStyleGrid(ETrue);
    CleanupStack::PushL(aGMSGrid);   
    CAknGMSPopupGrid* popupGMSGrid = CAknGMSPopupGrid::NewL(aGMSGrid,
                                        R_AVKON_SOFTKEYS_SELECT_CANCEL);
    CleanupStack::PushL(popupGMSGrid); 
    aGMSGrid->ConstructL(popupGMSGrid, KRows, KColumns);

        
    MDesCArray* itemList = aGMSGrid->Model()->ItemTextArray();
    CDesCArray* itemArray = (CDesCArray*) itemList;
      
    TBuf < KLengthOfItemResourceString > format;
    iCoeEnv->ReadResource( format, R_AKNEXGRID_FORMATSTRING_GMSGRID );
    for(TInt i=0;i<KInitialNumOfItemsInGMS;i++) 
        {
        TBuf< KLengthOfItemResourceString > string;
        if (i<4)
            string.Format(format, i+3);
        else
            string.Format(format, 2);
        itemArray->AppendL(string);
        }

    TBuf< KLengthOfPathEikonMbm > pathAppMbm;
    iCoeEnv->ReadResource( pathAppMbm, R_AKNEXGRID_PATH_AKNEXGRID_MBM );

    CArrayPtr<CGulIcon>* icons = 
            new(ELeave) CAknIconArray(KInitialNumOfItemsInGMS);
    CleanupStack::PushL(icons);

    // load bitmap resources
    CGulIcon* newIcon1 = CEikonEnv::Static()->CreateIconL(
                                pathAppMbm,
                                EMbmAknexgridGriditem, 
                                EMbmAknexgridGriditemm);
    CleanupStack::PushL(newIcon1);

    CGulIcon* newIcon2 = CEikonEnv::Static()->CreateIconL(
                                pathAppMbm,
                                EMbmAknexgridBlacktextonwhite_wbmp);
    CleanupStack::PushL(newIcon2);

    CGulIcon* newIcon3 = CEikonEnv::Static()->CreateIconL(
                                pathAppMbm,
                                EMbmAknexgridWhitetextonblack_wbmp);
    CleanupStack::PushL(newIcon3);

    CGulIcon* newIcon4 = CEikonEnv::Static()->CreateIconL(
                                pathAppMbm,
                                EMbmAknexgridBlacktextonwhite_ota);
    CleanupStack::PushL(newIcon4);

    CGulIcon* newIcon5 = CEikonEnv::Static()->CreateIconL(
                                pathAppMbm,
                                EMbmAknexgridWhitetextonblack_ota);
    CleanupStack::PushL(newIcon5);

    CGulIcon* onImage = CEikonEnv::Static()->CreateIconL(
                                pathAppMbm,
                                EMbmAknexgridMarkon, 
                                EMbmAknexgridMarkm);
    CleanupStack::PushL(onImage);

    CGulIcon* offImage = CEikonEnv::Static()->CreateIconL(
                                pathAppMbm,
                                EMbmAknexgridMarkoff, 
                                EMbmAknexgridMarkm);
    CleanupStack::PushL(offImage);

    icons->AppendL( onImage );
    icons->AppendL( offImage );
    icons->AppendL( newIcon1 );
    icons->AppendL( newIcon2 );
    icons->AppendL( newIcon3 );
    icons->AppendL( newIcon4 );
    icons->AppendL( newIcon5 );

    aGMSGrid->ItemDrawer()->FormattedCellData()->SetIconArrayL(icons);

    CleanupStack::Pop(); // offImage
    CleanupStack::Pop(); // onImage
    CleanupStack::Pop(); // newIcon5
    CleanupStack::Pop(); // newIcon4
    CleanupStack::Pop(); // newIcon3
    CleanupStack::Pop(); // newIcon2
    CleanupStack::Pop(); // newIcon1
    CleanupStack::Pop(); // icons

    TBuf < KLengthOfTitle > text;
    iCoeEnv->ReadResource( text, R_AKNEXGRID_TEXT_POPUPGMS_TITLE );
    popupGMSGrid->SetTitleL(text);
    TInt popupOk = popupGMSGrid->ExecuteLD();
    CleanupStack::Pop();            // popupGMSGrid
    if (popupOk)
        {
        TInt index = aGMSGrid->CurrentItemIndex();
        iCoeEnv->ReadResource( format, R_AKNEXGRID_TEXT_ACT_ONE_ITEM );
        text.Format(format, index);
        iEikonEnv->AlertWin(text);
        }
    else
        {
        iCoeEnv->ReadResource( text, R_AKNEXGRID_TEXT_POPUPGMS_CANCEL );
        iEikonEnv->AlertWin(text);
        }

    CleanupStack::PopAndDestroy();  // aGMSGrid
    
    }

// ---------------------------------------------------------
// CAknExGridContainerAsGMS::CheckIndex( void )
// show current index
// ---------------------------------------------------------
//
void CAknExGridContainerAsGMS::CheckIndex( void )
    {
    // Counter of the number of marked item
    TInt selectedItemCount = 0;

    // Load message.
    TBuf< KLengthOfStringToShowIndex > number;
    TBuf< KLengthOfStringToShowIndex > format;
    iCoeEnv->ReadResource( format, R_AKNEXGRID_FORMATSTRING_CURRENTINDEX );

    // The number of items.
    TInt numberOfData = iGridGMS->GridModel()->NumberOfData();

    // Check marked item. And if the item is marked,display dialog. 
    for ( TInt checkData = 0; checkData < numberOfData; checkData++ )
        {
        CListBoxView* view = iGridGMS->View();
     
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
        number.Format( format, selectedItemCount - 1 );
        iEikonEnv->AlertWin( number );
        }

    }

// ---------------------------------------------------------
// CAknExGridContainerAsGMS::SizeChanged()
// Called by framework when the view size is changed
// ---------------------------------------------------------
//
void CAknExGridContainerAsGMS::SizeChanged()
    {
    if( iGridGMS )
        {
        AknLayoutUtils::LayoutControl(iGridGMS, Rect(), KColorIndex,
            KLeftOfGrid, KTopOfGrid, ELayoutEmpty, ELayoutEmpty,
            KWidthOfGrid, KHightOfGrid);
        }

    }

// ---------------------------------------------------------
// CAknExGridContainerAsGMS::CountComponentControls() const
// return the number of controls
// ---------------------------------------------------------
//
TInt CAknExGridContainerAsGMS::CountComponentControls() const
    {
    // return number of controls inside this container
    return KNumberOfComponentGMS; 
    }

// ---------------------------------------------------------
// CAknExGridContainerAsGMS::ComponentControl(TInt aIndex) const
// return the pointer to specified control.
// ---------------------------------------------------------
//
CCoeControl* CAknExGridContainerAsGMS::ComponentControl( TInt aIndex ) const
    {
    switch ( aIndex )
        {

        case EGmsGrid:
            return iGridGMS;
        default:
            return NULL;
        }
    }

// ---------------------------------------------------------
// CAknExGridContainerAsGMS::Draw(const TRect& aRect) const
// handle the message when client region must be redrawn.
// ---------------------------------------------------------
//
void CAknExGridContainerAsGMS::Draw( const TRect& aRect ) const
    {
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KRgbDarkCyan );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.DrawRect( aRect );
    }


// ---------------------------------------------------------
// CAknExGridContainer::OfferKeyEventL(
//           const TKeyEvent& aKeyEvent, TEventCode aType )
// Handles the key events.
// ---------------------------------------------------------
//
TKeyResponse CAknExGridContainerAsGMS::OfferKeyEventL(
        const TKeyEvent& aKeyEvent, TEventCode aType )
    {
    TInt code = aKeyEvent.iCode;

    if ( iGridGMS ) 
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
                return iGridGMS->OfferKeyEventL( aKeyEvent, aType );
                }
            }
        else
            {
            return iGridGMS->OfferKeyEventL( aKeyEvent, aType );
            }
        }

    return( EKeyWasNotConsumed );
    }

// ---------------------------------------------------------
// CAknExGridContainerAsGMS::HandleControlEventL(
//     CCoeControl* aControl,TCoeEvent aEventType)
// handle event from observed control.
// ---------------------------------------------------------
//
void CAknExGridContainerAsGMS::HandleControlEventL(
    CCoeControl* /*aControl*/, TCoeEvent /*aEventType*/ )
    {
    }


TBool CAknExGridContainerAsGMS::AutoTestL()
    {
    CEikStatusPane* sp = iEikonEnv->AppUiFactory()->StatusPane();
    CAknTitlePane* titlePane = (CAknTitlePane *)sp->ControlL(TUid::Uid(EEikStatusPaneUidTitle));

    iTestNumber++;

    switch(iTestNumber)
        {
        case EGMSTest1:
            titlePane->SetTextL((*iTitles)[EGMSTest1]);
            break;

        case EGMSTest2:
            titlePane->SetTextL((*iTitles)[EGMSTest2]);
            ShowPopupGMSGridL();
            break;

        default:
            return ETrue;
        }

    return EFalse;
    }

// End of File  
