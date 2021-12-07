/*
* =============================================================================
*  Name     : CAknExListBaseContainer
*  Part of  : AknExList
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

// INCLUDE FILES
#include <eikclbd.h>
#include <aknlists.h>
#include <barsread.h>
#include <akniconarray.h>
#include <aknexlist.rsg>
#include <aknexlist.mbg>
#include <AknQueryDialog.h>
#include "AknExListBaseContainer.h"
#include "AknExListConst.h" // For name of bitmap file

// CONSTANTS
#define KAknExListGray TRgb(0xaaaaaa)
#define KAknExListTab '\t'

const TInt KAknExListFindBoxTextLength(20); // for findbox.
// for lenght.
const TInt KAknExListEmptyListBufLength(256);
const TInt KAknExListAddItemBufLength(256);
const TInt KAknExListInfoMessageBufLength(256);
const TInt KAknExListCountMessageBufLength(256);
const TInt KAknTAListShowMessageBufLength(256);

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExListBaseContainer::CAknExListBaseContainer()
// Default constructor.
// ----------------------------------------------------------------------------
//
CAknExListBaseContainer::CAknExListBaseContainer()
    {
    }

// ----------------------------------------------------------------------------
// CAknExListBaseContainer::~CAknExListBaseContainer()
// Destructor.
// ----------------------------------------------------------------------------
//
CAknExListBaseContainer::~CAknExListBaseContainer()
    {
    }

// ----------------------------------------------------------------------------
// void CAknExListBaseContainer::SetListBoxFromResourceL( CEikColumnListBox*,
//  const TInt )
// Sets listbox from resource using ConstructFromResourceL() of
// CEikColumnListBox class.
// ----------------------------------------------------------------------------
//
void CAknExListBaseContainer::SetListBoxFromResourceL(
    CEikColumnListBox* aListBox,
    const TInt aResourceId )
    {
    if ( aListBox && aResourceId )
        {
        aListBox->SetContainerWindowL( *this );

        TResourceReader reader;
        CEikonEnv::Static()->CreateResourceReaderLC( reader, aResourceId );
        aListBox->ConstructFromResourceL( reader );
        CleanupStack::PopAndDestroy(); // resource stuffs.

        // Creates scrollbar.
        CreateScrollbarL( aListBox );
        }
    }

// ----------------------------------------------------------------------------
// void CAknExListBaseContainer::SetListBoxFromResourceL(
//  CEikFormattedCellListBox*, const TInt )
// Sets listbox from resource using ConstructFromResourceL() of
// CEikFormattedCellListBox class.
// ----------------------------------------------------------------------------
//
void CAknExListBaseContainer::SetListBoxFromResourceL(
    CEikFormattedCellListBox* aListBox,
    const TInt aResourceId )
    {
    if ( aListBox && aResourceId )
        {
        aListBox->SetContainerWindowL( *this );

        TResourceReader reader;
        CEikonEnv::Static()->CreateResourceReaderLC( reader, aResourceId );
        aListBox->ConstructFromResourceL( reader );
        CleanupStack::PopAndDestroy(); // resource stuffs.

        // Creates scrollbar.
        CreateScrollbarL( aListBox );
        }
    }

// ----------------------------------------------------------------------------
// void CAknExListBaseContainer::SetListBoxFromInnerDescriptionL(
//  CEikColumnListBox*, const TInt, CDesCArray* )
// Sets listbox from inner description using ConstructL() of CEikColumnListBox
// class.
// ----------------------------------------------------------------------------
//
void CAknExListBaseContainer::SetListBoxFromInnerDescriptionL(
    CEikColumnListBox* aListBox,
    const TInt aFlags,
    CDesCArray* textArray )
    {
    if ( aListBox )
        {
        // Constructs listbox.
        aListBox->ConstructL( this, aFlags );

        if ( textArray )
            {
            // Sets list item from resource.
            aListBox->Model()->SetItemTextArray( textArray );
            aListBox->Model()->SetOwnershipType( ELbmOwnsItemArray );
            }

        // Creates scrollbar.
        CreateScrollbarL( aListBox );
        }
    }

// ----------------------------------------------------------------------------
// void CAknExListBaseContainer::SetListBoxFromInnerDescriptionL(
//  CEikFormattedCellListBox*, const TInt, CDesCArray* )
// Sets listbox from inner description using ConstructL() of
// CEikFormattedCellListBox class.
// ----------------------------------------------------------------------------
//
void CAknExListBaseContainer::SetListBoxFromInnerDescriptionL(
    CEikFormattedCellListBox* aListBox,
    const TInt aFlags,
    CDesCArray* textArray )
    {
    if ( aListBox )
        {
        // Constructs listbox.
        aListBox->ConstructL( this, aFlags );

        if ( textArray )
            {
            // Sets list item from resource.
            aListBox->Model()->SetItemTextArray( textArray );
            aListBox->Model()->SetOwnershipType( ELbmOwnsItemArray );
            }

        // Creates scrollbar.
        CreateScrollbarL( aListBox );
        }
    }

// ----------------------------------------------------------------------------
// CAknSearchField* CAknExListBaseContainer::CreateFindBoxL()
// Creates FindBox and returns it's pointer.
// ----------------------------------------------------------------------------
//
CAknSearchField* CAknExListBaseContainer::CreateFindBoxL(
    CEikListBox* aListBox,
    CTextListBoxModel* aModel,
    CAknSearchField::TSearchFieldStyle aStyle )
    {
    CAknSearchField* findbox = NULL;

    if ( aListBox && aModel )
        {
        // Gets pointer of CAknFilteredTextListBoxModel.
        CAknFilteredTextListBoxModel* model =
                STATIC_CAST( CAknFilteredTextListBoxModel*, aModel );
        // Creates FindBox.
        findbox = CAknSearchField::NewL( *this,
                                         aStyle,
                                         NULL,
                                         KAknExListFindBoxTextLength );
        CleanupStack::PushL(findbox);
        // Creates CAknListBoxFilterItems class.
        model->CreateFilterL( aListBox, findbox );
        //Filter can get by model->Filter();
        CleanupStack::Pop(findbox); // findbox
        }

    return findbox;
    }

// ----------------------------------------------------------------------------
// void CAknExListBaseContainer::AutoNumberingL( CEikTextListBox* )
// Automatic numbering of list item.
// ----------------------------------------------------------------------------
//
void CAknExListBaseContainer::AutoNumberingL(
    CEikTextListBox* aListBox )
    {
    // Change it because CListBoxNumbers will be removed on Sw 2.10. 
    // Source is replaced to the copy of Sw 2.05's CListBoxNumbers::UpdateL()
    TInt itemCount(aListBox->Model()->NumberOfItems());
    MDesCArray* itemList = aListBox->Model()->ItemTextArray();
    CDesCArray* itemArray = STATIC_CAST(CDesCArray*, itemList);
    for (TInt i(0); i < itemCount; i++)
        {
        TPtrC item = (*itemArray)[i];
        TInt pos = item.Locate(KAknExListTab);
        TBuf<256> data; 
        data.Num(i + 1);
        data += item.Right(item.Length() - pos);
        itemArray->Delete(i);
        itemArray->InsertL(i, data);
        }   
    }

// ----------------------------------------------------------------------------
// void CAknExListBaseContainer::SetGraphicIconL( CEikColumnListBox* )
// Sets graphic icon using listbox as CEikColumnListBox.
// ----------------------------------------------------------------------------
//
void CAknExListBaseContainer::SetGraphicIconL( CEikColumnListBox* aListBox )
    {
    if ( aListBox )
        {
        // Creates gul icon.
        CArrayPtr<CGulIcon>* icons =
            new( ELeave ) CAknIconArray(
                KAknExListGraphicGulIconIndex );

        CleanupStack::PushL( icons );

        GraphicIconL( icons ); // Appends graphic data.

        // Sets graphics as ListBox icon.
        aListBox->ItemDrawer()->ColumnData()->SetIconArray( icons );

        CleanupStack::Pop();

        }
    }

// ----------------------------------------------------------------------------
// void CAknExListBaseContainer::SetGraphicIconL( CEikFormattedCellListBox* )
// Sets graphic icon using listbox as CEikFormattedCellListBox.
// ----------------------------------------------------------------------------
//
void CAknExListBaseContainer::SetGraphicIconL(
    CEikFormattedCellListBox* aListBox )
    {
    if ( aListBox )
        {
        // Creates gul icon.
        CArrayPtr<CGulIcon>* icons =
            new( ELeave ) CAknIconArray(
                KAknExListGraphicGulIconIndex );

        CleanupStack::PushL( icons );

        GraphicIconL( icons ); // Appends graphic data.

        // Sets graphics as ListBox icon.
        aListBox->ItemDrawer()->FormattedCellData()->SetIconArrayL( icons );
        // Drawing position of icon is left.
        //aListBox->ItemDrawer()->FormattedCellData()->SetSubCellAlignmentL(
        //     2, CGraphicsContext::ELeft);

        CleanupStack::Pop();
        }
    }


// ---------------------------------------------------------------------------
// void CAknExListBaseContainer::SetEmptyListL( CEikListBox*, const TInt )
// Sets empty list for listbox.
// ---------------------------------------------------------------------------
//
void CAknExListBaseContainer::SetEmptyListL(
    CEikListBox* aListBox,
    const TInt aResourceId )
    {
    if ( aListBox && aResourceId )
        {
        CListBoxView* view = aListBox->View();

        if ( view )
            {
            // Sets empty list.
            TBuf<KAknExListEmptyListBufLength> emptyList( 0 );
            iCoeEnv->ReadResource( emptyList, aResourceId );
            aListBox->View()->SetListEmptyTextL( emptyList );
            }
        }
    }

// ----------------------------------------------------------------------------
// void CAknExListBaseContainer::AddItemL( CEikListBox*, CTextListBoxModel*,
//  const TInt, const TInt )
// Adds list item at the bottom of the list.
// ----------------------------------------------------------------------------
//
void CAknExListBaseContainer::AddItemL(
    CEikListBox* aListBox,
    CTextListBoxModel* aModel,
    const TInt aCount,
    const TInt aResourceId )
    {
    if ( aListBox &&  aModel && aCount && aResourceId )
        {
        TInt addCount( aCount );

        MDesCArray *itemList = aModel->ItemTextArray();
        CDesCArray *itemArray = STATIC_CAST( CDesCArray*, itemList );

        TInt itemCount(0);

        TBuf<KAknExListAddItemBufLength> addItem( 0 );
        iCoeEnv->ReadResource( addItem, aResourceId );

        // Adds items at the bottom of the list.
        while ( itemCount < addCount )
            {
            itemArray->AppendL( addItem );
            itemCount++;
            }

        aListBox->HandleItemAdditionL(); // Updates listbox.
        }
    }

// ----------------------------------------------------------------------------
// void CAknExListBaseContainer::RemoveItemL( CEikListBox*, CTextListBoxModel*,
//  const TInt )
// Removes list items.
// ----------------------------------------------------------------------------
//
void CAknExListBaseContainer::RemoveItemL(
    CEikListBox* aListBox,
    CTextListBoxModel* aModel,
    const TInt aCount )
    {
    if ( aListBox && aModel && aCount )
        {
        // Gets max count.
        TInt maxCount( aModel->NumberOfItems() );

        // Gets current item index.
        TInt currentItem( aListBox->CurrentItemIndex() );

        if ( 0 <= currentItem &&
             currentItem < maxCount )
            {
            TInt removeCount( aCount );

            if ( ( removeCount + currentItem ) > maxCount )
                {
                // Resete removeCount.
                removeCount = maxCount - currentItem;
                }

            if ( removeCount )
                {
                MDesCArray *itemList = aModel->ItemTextArray();
                CDesCArray *itemArray = STATIC_CAST( CDesCArray*, itemList );

                // Removes list items.
                itemArray->Delete( currentItem, removeCount );
                AknListBoxUtils::HandleItemRemovalAndPositionHighlightL(
                    aListBox, currentItem, ETrue );

                aListBox->DrawNow(); // Updates listbox.
                }
            }
        }
    }

// ----------------------------------------------------------------------------
// void CAknExListBaseContainer::InfoMessage( const TInt )
// Displays information message.
// ----------------------------------------------------------------------------
//
void CAknExListBaseContainer::InfoMessage( const TInt aMessageId )
    {
    if ( aMessageId )
        {
        TBuf<KAknExListInfoMessageBufLength> message( 0 );
        iCoeEnv->ReadResource( message, aMessageId );
        //CEikonEnv::Static()->InfoMsg( message ); // Displays message.
        ShowMessageL( message );
        }
    }

// ----------------------------------------------------------------------------
// void CAknExListBaseContainer::CountMessage( CTextListBoxModel* )
// Displays information message of total number for list items.
// ----------------------------------------------------------------------------
//
void CAknExListBaseContainer::CountMessage( CTextListBoxModel* aModel )
    {
    if ( aModel )
        {
        TInt maxCount( aModel->NumberOfItems() );  // Gets max count.

        // Displays total number of list items.
        TBuf<KAknExListCountMessageBufLength> countText( 0 );
        iCoeEnv->ReadResource( countText, R_AKNEXLIST_ITEM_COUNT );
        countText.AppendNum( maxCount );
        //CEikonEnv::Static()->InfoMsg( countText );
        ShowMessageL( countText );
        }
    }

// ----------------------------------------------------------------------------
// void CAknExListBaseContainer::ShowMessageL(TDesC &aMessage)
//
// ----------------------------------------------------------------------------
//
void CAknExListBaseContainer::ShowMessageL(const TDesC& aMessage)
    {
    TBuf<KAknTAListShowMessageBufLength> temp(aMessage);
    CAknQueryDialog* dlg = new (ELeave) CAknQueryDialog(temp, CAknQueryDialog::ENoTone);    
    dlg->ExecuteLD(R_AKNEXLIST_CONFIRMATION_QUERY);
    }

// ----------------------------------------------------------------------------
// void CAknExListBaseContainer::InfoMarkedItemIndexL()
// Displays information of marked item index.
// ----------------------------------------------------------------------------
//
void CAknExListBaseContainer::InfoMarkedItemIndexL(
     const CArrayFix<TInt>* aIndexArray)
    {
    TBuf<512> infoText( 0 );

    TBuf<256> information( 0 );
    iCoeEnv->ReadResource( information, R_AKNEXLIST_MARK_INFO );
    infoText.Append( information );

    // Gets marked item index.
    TBuf<256> format( 0 );
    iCoeEnv->ReadResource( format, R_AKNEXLIST_FORMAT );

    TInt itemCount( aIndexArray->Count() );

    for ( TInt ii( 0 ); ii < itemCount; ii++ )
        {
        TBuf<256> index;
        index.Format( format, ( *( aIndexArray ) )[ii] );
        infoText.Append( index );
        }

    if ( itemCount == 0 )
        {
        TBuf<256> non( 0 );
        iCoeEnv->ReadResource( non, R_AKNEXLIST_NO_MARK );
        infoText.Append( non );
        }

    ShowMessageL( infoText );
    }



// ----------------------------------------------------------------------------
// void CAknExListBaseContainer::CreateScrollbarL( CEikListBox* aListBox )
// Creates scrollbar.
// ----------------------------------------------------------------------------
//
void CAknExListBaseContainer::CreateScrollbarL( CEikListBox* aListBox )
    {
    if ( aListBox )
        {
        // Creates scrollbar.
        aListBox->CreateScrollBarFrameL( ETrue );
        aListBox->ScrollBarFrame()->SetScrollBarVisibilityL(
            CEikScrollBarFrame::EOff, CEikScrollBarFrame::EAuto );
        }
    }

// ----------------------------------------------------------------------------
// void CAknExListBaseContainer::UpdateScrollBar
// Update scroll bar.
// ----------------------------------------------------------------------------
//
void CAknExListBaseContainer::UpdateScrollBar(CEikListBox* aListBox)
    {
    if (aListBox)
        {   
        TInt pos(aListBox->View()->CurrentItemIndex());
        if (aListBox->ScrollBarFrame())
            {
            aListBox->ScrollBarFrame()->MoveVertThumbTo(pos);
            }
        }
    }


// ----------------------------------------------------------------------------
// void CAknExListBaseContainer::GraphicIconL( CArrayPtr<CGulIcon>* )
// Appends graphics data.
// ----------------------------------------------------------------------------
//
void CAknExListBaseContainer::GraphicIconL( CArrayPtr<CGulIcon>* aIcons )
    {
    if ( aIcons )
        {
        // Appends icon.
        aIcons->AppendL( iEikonEnv->CreateIconL( KAknExListMbmFileName,
                                                 EMbmAknexlistMarked_add,
                                                 EMbmAknexlistMarked_add_m ) );
        }
    }

// ----------------------------------------------------------------------------
// void CAknExListBaseContainer::Draw( const TRect& aRect ) const
// Fills the window's rectangle.
// ----------------------------------------------------------------------------
//
void CAknExListBaseContainer::Draw( const TRect& aRect ) const
    {
    // (Re)draw the rectangle of frame.
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KAknExListGray );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.DrawRect( aRect );
    }

// End of File
