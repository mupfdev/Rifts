/*
* =============================================================================
*  Name     : CAknExSettingListContainer
*  Part of  : AknExSettingList
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include <barsread.h>
#include <eiklabel.h>
#include <avkon.hrh>
#include <aknlists.h>
#include <aknexsettinglist.rsg>
#include <aknquerydialog.h>
#include "aknexsettinglist.hrh"
#include "aknexsettinglistview.h"
#include "aknexsettinglistcontainer.h"

// CONSTANTS

// for array
const TInt KAknExSettingListGranularityInitial = 1;

// for ID of resource
const TInt KAknExSettingListResourceInitial = 0;

// for Text Setting Page
const TInt KAknExSettingListMaxLength10 = 10;
const TInt KAknExSettingListMaxLength30 = 30;

// for Slider Setting Page
const TInt KAknExSettingListDefaultSliderValue = 67;

// for Volume Setting Page
const TInt KAknExSettingListDefaultVolumeValue = 5;

// for Duration Setting Page
const TInt KAknExSettingListInitialDuration = 0;

// for count component
const TInt KAknExSettingListCountInitial = 0;



// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExSettingListContainer::CAknExSettingListContainer( CAknExSettingListView* )
// Copy constructor.
// ----------------------------------------------------------------------------
//
CAknExSettingListContainer::CAknExSettingListContainer( CAknExSettingListView* aView )
:   iLabel( NULL ),
    iView( aView ),
    iCurrentOutlineId( EAknExSettingListCmdEmptyOutline )
    {
    }

// ----------------------------------------------------------------------------
// void CAknExSettingListContainer::ConstructL( const TRect& )
// EPOC constructor.
// ----------------------------------------------------------------------------
//
void CAknExSettingListContainer::ConstructL( const TRect& aRect )
    {
    CreateWindowL(); // Creates window.
    SetRect( aRect ); // Sets rectangle of frame.
    ActivateL(); // Activates the window. (Ready to draw)
    }

// ----------------------------------------------------------------------------
// CAknExSettingListContainer::~CAknExSettingListContainer()
// Destructor.
// ----------------------------------------------------------------------------
//
CAknExSettingListContainer::~CAknExSettingListContainer()
    {
    delete iLabel; // Deletes the label object.
    }

// ----------------------------------------------------------------------------
// void CAknExSettingListContainer::SetCurrentOutlineId( const TInt )
// Sets ID of current outline.
// ----------------------------------------------------------------------------
//
void CAknExSettingListContainer::SetCurrentOutlineId( const TInt aOutlineId )
    {
    iCurrentOutlineId = aOutlineId; // Sets ID of current outline.
    }

// ----------------------------------------------------------------------------
// void CAknExSettingListContainer::DisplayLabelL( const TInt )
// Displays the label by ID of resource.
// ----------------------------------------------------------------------------
//
void CAknExSettingListContainer::DisplayLabelL( const TInt aResourceId )
    {
    // Creates the label object.
    if ( !iLabel )
        {
        iLabel = new( ELeave ) CEikLabel;
        iLabel->SetContainerWindowL( *this );
        iLabel->SetFont( LatinBold19() );
        iLabel->SetAlignment( EHCenterVCenter );
        }

    TBuf<KAknExSettingListTextBufLength> labelText( NULL );
    iCoeEnv->ReadResource( labelText, aResourceId );
    iLabel->SetTextL( labelText );

    SizeChanged();
    DrawNow();
    }

// ----------------------------------------------------------------------------
// TKeyResponse CAknExSettingListContainer::OfferKeyEventL( const TKeyEvent&,
//  TEventCode )
// Handles the key events.
// ----------------------------------------------------------------------------
//
TKeyResponse CAknExSettingListContainer::OfferKeyEventL(
    const TKeyEvent& aKeyEvent,
    TEventCode aType )
    {
    if ( aType != EEventKey ) // Is not key event?
        {
        return EKeyWasNotConsumed;
        }

    switch ( aKeyEvent.iCode ) // The code of key event is...
        {
        case EKeySpace: // Space key.
        case EKeyRightArrow:
            // Requires to display next outline screen.
            iView->SetCurrentOutlineId( iCurrentOutlineId );
            iView->DisplayNextOutlineL();
            break;
        case EKeyLeftArrow:
            // Display the previous outline.
            iView->SetCurrentOutlineId( iCurrentOutlineId );
            iView->DisplayPreviousOutlineL();
        default:
            return EKeyWasNotConsumed;
        }
    return EKeyWasConsumed;
    }

// ----------------------------------------------------------------------------
// void CAknExSettingListContainer::SizeChanged()
// Called by framework when the view size is changed.
// ----------------------------------------------------------------------------
//
void CAknExSettingListContainer::SizeChanged()
    {
    // Sets rectangle of label.
    if ( iLabel )
        {
        iLabel->SetRect( Rect() );
        }
    }

// ----------------------------------------------------------------------------
// TInt CAknExSettingListContainer::CountComponentControls() const
// Returns number of component.
// ----------------------------------------------------------------------------
//
TInt CAknExSettingListContainer::CountComponentControls() const
    {
    TInt count( KAknExSettingListCountInitial );

    if ( iLabel )
        {
        count++;
        }

    return count; // Returns number of component.
    }

// ----------------------------------------------------------------------------
// CCoeControl* CAknExSettingListContainer::ComponentControl( TInt ) const
// Returns pointer to particular component.
// ----------------------------------------------------------------------------
//
CCoeControl* CAknExSettingListContainer::ComponentControl( TInt aIndex ) const
    {
    switch ( aIndex ) // Component is ...
        {
        case EAknExSettingListComponentLabel:
            if ( iLabel )
                {
                return iLabel; // Returns the pointer to label object.
                }
        default:
            return NULL; // Exception: Returns NULL value.
        }
    }

// ----------------------------------------------------------------------------
// void CAknExSettingListContainer::Draw( const TRect& ) const
// Fills the window's rectangle.
// ----------------------------------------------------------------------------
//
void CAknExSettingListContainer::Draw( const TRect& aRect ) const
    {
    // (Re)draw the rectangle of frame.
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KRgbGray );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.DrawRect( aRect );
    }

// End of File
