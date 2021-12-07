/*
* ============================================================================
*  Name     : CAknExScrollerContainer2 from CCoeControl, MCoeControlObserver
*  Part of  : AknExScroller
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include <coemain.h>

#include <eikclb.h>   // list box
#include <eiktxlbm.h> // CTextListBoxModel <- iListBox->Model()
#include <eiklabel.h>  // for example label control
#include <eikclbd.h>
#include <eikbtgpc.h>
#include <eiklbx.h>
#include <aknlists.h>
#include <eikfrlb.h>

#include <avkon.hrh>

#include <AknExScroller.rsg>

#include "AknExScrollerAppUi.h"
#include "AknExScrollerContainer2.h"
#include "AknExScrollerView2.h"
#include "AknExScrollerCbaHandler.h"


// Constants
#define KAknExScrollerYellow TRgb(0x00ffff)

#define VIEW2_LABEL_POINT   TPoint( 10, 10 )
#define VIEW2_DOLABEL_POINT TPoint( 10, 120 )

const TInt  KZero = 0;
const TInt  KOne = 1;

const TInt  KMaxItemOfListBox = 100;
const TInt  KMinItemOfListBox = 3;
const TInt  KAmountOfDeleteItem = 1;

const TInt KNumberOfComponent = 1;
const TInt KBufferLength = 256;
// Enumeration
enum TPointerToComponetView2
    {
    EListBox = 0,
    ECbaContainer
    };


// ================= MEMBER FUNCTIONS =======================
// C++ default constructor can NOT contain any code, that
// might leave.
//
CAknExScrollerContainer2::CAknExScrollerContainer2()
                        : iListBox( NULL )
    {
    }




// ---------------------------------------------------------
// CAknExScrollerContainer2::ConstructL( const TRect& aRect )
// EPOC two phased constructor
// ---------------------------------------------------------
//
void CAknExScrollerContainer2::ConstructL( const TRect& aRect )
    {
    CreateWindowL();

    // List Box set up
    // "CBA set up" must be earlier than ListBox
    // Otherwise, scroller does not show appropriately.
    CreateListBox();

    SetRect(aRect);

    // Activate for Drawing
    ActivateL();
    }

// ----------------------------------------------------------------------------
// Destructor
// ----------------------------------------------------------------------------
//
CAknExScrollerContainer2::~CAknExScrollerContainer2()
    {
    CloseListBox();
    }


// ----------------------------------------------------------------------------
// CAknExScrollerContainer2::AddItemToListBoxL()
// Adds an item to list box.
// ----------------------------------------------------------------------------
//
void CAknExScrollerContainer2::AddItemToListBoxL()
    {
    if ( iListBox ) // Is list box created?
        {
        // Gets current number of list box items.
        TInt numberOfItems( iListBox->Model()->NumberOfItems() );
        // If the current number is less than defined maximum number,
        // adds one item to list box.
        if ( numberOfItems < KMaxItemOfListBox )
            {
            // Makes text which is added to list box.
            TBuf<KBufferLength> itemText;
            iCoeEnv->ReadResource( itemText, R_AKNEXSCROLLER_ITEM_LIST_BOX );
            TBuf<KBufferLength> listItemFormat ( itemText );
            TBuf<KBufferLength> listItem;
            listItem.Format( listItemFormat, numberOfItems );
            // Adds one item and reset the size of list box.
            CDesCArray* itemArray = STATIC_CAST( CDesCArray*,
                iDoubleListBox->Model()->ItemTextArray() );
            itemArray->AppendL( listItem );
            iListBox->HandleItemAdditionL();
            iListBox->DrawDeferred();

            // Zang's advice
            // Update scroller's shape immediately
            TInt currentItem = iListBox->CurrentItemIndex();
            if ( iListBox->ScrollBarFrame() )
                {
                iListBox->ScrollBarFrame()->MoveVertThumbTo( currentItem );
                }
            }
        }
    }

// ----------------------------------------------------------------------------
// CAknExScrollerContainer2::RemoveItemFromListBox()
// Removes an item from list box.
// ----------------------------------------------------------------------------
//
void CAknExScrollerContainer2::RemoveItemFromListBox()
    {
    if ( iListBox ) // Is list box created?
        {
        // Gets current number of list box items.
        TInt numberOfItems( iListBox->Model()->NumberOfItems() );
        // If the current number is more than defined minimum number,
        // removes one item from list box.
        if ( numberOfItems > KMinItemOfListBox )
            {
            // If the line which is chosen in list box is bottom line
            // moves up current line.
            TInt currentListItem( iListBox->View()->CurrentItemIndex() );
            TInt bottomListItem( iListBox->View()->BottomItemIndex() );
            if ( currentListItem == bottomListItem )
                {
                // Changes current line which is chosen in list box.
                iListBox->View()->SetCurrentItemIndex( bottomListItem -
                                                        KAmountOfDeleteItem );
                }
            // Removes one item and reset the size of list box.
            CDesCArray* itemArray = STATIC_CAST( CDesCArray*,
                iDoubleListBox->Model()->ItemTextArray() );
            itemArray->Delete( numberOfItems - KAmountOfDeleteItem );
            iListBox->HandleItemRemovalL();
            iListBox->DrawDeferred();


            // Zang's advice
            // Update scroller's shape immediately
            TInt currentItem = iListBox->CurrentItemIndex();
            if ( iListBox->ScrollBarFrame() )
                {
                iListBox->ScrollBarFrame()->MoveVertThumbTo( currentItem );
                }

            } // End "if ( numberOfItems > KMinItemOfListBox )"
        } // End "if ( iListBox )"
        DrawDeferred();
    }


// ---------------------------------------------------------
// CAknExScrollerContainer2::SizeChanged()
// Called by framework when the view size is changed
// ---------------------------------------------------------
//
void CAknExScrollerContainer2::SizeChanged()
    {
    // TODO: Add here control resize code etc.
    iListBox->SetRect( Rect() );
    }

// ---------------------------------------------------------
// CAknExScrollerContainer2::CountComponentControls() const
// Returns number of component.
// ---------------------------------------------------------
//
TInt CAknExScrollerContainer2::CountComponentControls() const
    {
    return KNumberOfComponent; // return nbr of controls inside this container
    }

// ---------------------------------------------------------
// CAknExScrollerContainer2::ComponentControl( TInt aIndex ) const
// Returns pointer to particular component.
// ---------------------------------------------------------
//
CCoeControl* CAknExScrollerContainer2::ComponentControl( TInt aIndex ) const
    {
    switch ( aIndex )
        {
        case EListBox:
            return iListBox;
        default:
            return NULL;
        }
    }

// ---------------------------------------------------------
// CAknExScrollerContainer2::Draw(const TRect& aRect) const
// Draw function
// ---------------------------------------------------------
//
void CAknExScrollerContainer2::Draw( const TRect& aRect ) const
    {
    CWindowGc& gc = SystemGc();
    // TODO: Add your drawing code here
    // example code...
    gc.SetPenStyle(CGraphicsContext::ENullPen);
    gc.SetBrushColor(KAknExScrollerYellow);
    gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
    gc.DrawRect(aRect);
    }


// ---------------------------------------------------------
// CAknExScrollerContainer2::OfferKeyEventL(
//                           const TKeyEvent& aKeyEvent,
//                           TEventCode aType )
// Handles the key events.
// ---------------------------------------------------------
//
TKeyResponse CAknExScrollerContainer2::OfferKeyEventL(
                                       const TKeyEvent& aKeyEvent,
                                       TEventCode aType )
    {
    if ( aType != EEventKey )
        {
        return EKeyWasNotConsumed;
        }

    switch ( aKeyEvent.iCode )
        {
        // Up & Down arrow key's event transfer to list box
        case EKeyUpArrow:
        case EKeyDownArrow:
            if ( iListBox )
                {
                return iListBox->OfferKeyEventL( aKeyEvent, aType );
                }
            break;
        default:
            break;
        }

    return EKeyWasNotConsumed;
    }


// ---------------------------------------------------------
// CAknExScrollerContainer::HandleControlEventL(
//                        CCoeControl* /* aControl */,
//                        TCoeEvent /* aEventType */ )
// Handles an event of type aEventType reported
// by the control aControl to this observer.
// ---------------------------------------------------------
//
void CAknExScrollerContainer2::HandleControlEventL(
                               CCoeControl* /* aControl */,
                               TCoeEvent /* aEventType */ )
    {
    }


// ---------------------------------------------------------
// CAknExScrollerContainer2::CreateListBox()
// Creates list box
// ---------------------------------------------------------
//
void CAknExScrollerContainer2::CreateListBox()
    {
    CloseListBox();

    iListBox = iDoubleListBox = new( ELeave ) CAknDoubleStyleListBox();
    iDoubleListBox->ConstructL( this, EAknListBoxSelectionList );
    iListBox->CreateScrollBarFrameL( ETrue );
    iListBox->ScrollBarFrame()->SetScrollBarVisibilityL (
                                                 CEikScrollBarFrame::EOff,
                                                 CEikScrollBarFrame::EAuto );

    iListBox->SetListBoxObserver( this );
    iListBox->SetRect( Rect() );

    CDesCArray* itemArray = STATIC_CAST( CDesCArray*,
                                        iDoubleListBox->Model()->ItemTextArray() );
    TBuf<KBufferLength> itemText;
    iCoeEnv->ReadResource( itemText, R_AKNEXSCROLLER_ITEM_LIST_BOX );
    TBuf<KBufferLength> listItemFormat ( itemText );

    for (TInt i = KZero; i < KMinItemOfListBox; i++)
        {
        TBuf<KBufferLength> listItem;
        listItem.Format( listItemFormat, i );
        itemArray->AppendL( listItem );
        }

    iListBox->HandleItemAdditionL();

    // Sets rectangle of list box and activate.
    iListBox->ActivateL();
    iListBox->DrawNow();
    }


// ---------------------------------------------------------
// CAknExScrollerContainer2::CloseListBox()
// Closes list box
// ---------------------------------------------------------
//
void CAknExScrollerContainer2::CloseListBox()
    {
    if (iListBox )
        {
        delete iListBox;
        iListBox = NULL;
        }
    }


void CAknExScrollerContainer2::HandleListBoxEventL(
    CEikListBox* /*aListBox*/,
    TListBoxEvent /*aEventType*/ )
    {

    }

// End of File
