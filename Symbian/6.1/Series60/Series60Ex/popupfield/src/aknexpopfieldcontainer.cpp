/*
* =============================================================================
*  Name     : CAknExPopFieldContainer
*  Part of  : AknExPopField
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

// INCLUDE FILES
#include <aknutils.h> // for AKN_LAF_COLOR
#include <eikappui.h>
#include <eikenv.h>
#include <eiklabel.h> // for label
#include <aknform.h>  // for form control
#include <aknexpopfield.rsg>
#include "AknExPopField.hrh"
#include "AknExPopFieldView.h"
#include "AknExPopFieldContainer.h"
#include "AknExPopFieldTextValueDialog.h"
#include "AknExPopFieldOptionalListDialog.h"
#include "AknExPopFieldManyLineDialog.h"
#include "AknExPopFieldMultiPageDialog.h"
#include "AknExPopFieldAttribSetDialog.h"

// MACROS
#define AKNEXPOPFIELD_BACKGROUND_COLOR AKN_LAF_COLOR( 219 )

// CONSTANTS
const TInt KAknExPopFieldCountComponent = 1;
const TInt KAknExPopFieldMessageBufLength = 256;

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExPopFieldContainer::CAknExPopFieldContainer( CAknExPopFieldView* )
// Overload constructor.
// ----------------------------------------------------------------------------
//
CAknExPopFieldContainer::CAknExPopFieldContainer( CAknExPopFieldView* aView )
:   iView( aView ),
    iLabel( NULL )
    {
    }

// ----------------------------------------------------------------------------
// void CAknExPopFieldContainer::ConstructL( const TRect& )
// EPOC constructor.
// ----------------------------------------------------------------------------
//
void CAknExPopFieldContainer::ConstructL( const TRect& aRect )
    {
    // Creates window.
    CreateWindowL();

    // Creates label object.
    CreateLabelL();

    SetRect( aRect ); // Sets rectangle of frame.
    ActivateL(); // Activates the window. (Ready to draw)
    }

// ----------------------------------------------------------------------------
// CAknExPopFieldContainer::~CAknExPopFieldContainer()
// Destructor.
// ----------------------------------------------------------------------------
//
CAknExPopFieldContainer::~CAknExPopFieldContainer()
    {
    delete iLabel;
    }

// ----------------------------------------------------------------------------
// void CAknExPopFieldContainer::SetTextToLabelL( TInt )
//
// ----------------------------------------------------------------------------
//
void CAknExPopFieldContainer::SetTextToLabelL( TInt aResourceId )
    {
    TBuf<KAknExPopFieldMessageBufLength> messageString;
    iCoeEnv->ReadResource( messageString , aResourceId );
    iLabel->SetTextL( messageString );
    }

// ----------------------------------------------------------------------------
// void CAknExPopFieldContainer::DisplayTextPopFieldL( TInt )
//
// ----------------------------------------------------------------------------
//
void CAknExPopFieldContainer::DisplayTextPopFieldL( TInt aResourceId )
    {
    CAknExPopFieldTextValueDialog* dlg =
        CAknExPopFieldTextValueDialog::NewLC();
    ///iEikonEnv->EikAppUi()->AddToStackL( dlg );
    CleanupStack::Pop();
    dlg->ExecuteLD( aResourceId );
    }

// ----------------------------------------------------------------------------
// void CAknExPopFieldContainer::DisplayOptionalTextPopFieldL( TInt )
//
// ----------------------------------------------------------------------------
//
void CAknExPopFieldContainer::DisplayOptionalTextPopFieldL( TInt aResourceId )
    {
    CAknExPopFieldOptionalListDialog* dlg =
        CAknExPopFieldOptionalListDialog::NewLC();
    ///iEikonEnv->EikAppUi()->AddToStackL( dlg );
    CleanupStack::Pop();
    dlg->ExecuteLD( aResourceId );
    }

// ----------------------------------------------------------------------------
// void CAknExPopFieldContainer::DisplayManyLineTextPopFieldL( TInt )
//
// ----------------------------------------------------------------------------
//
void CAknExPopFieldContainer::DisplayManyLineTextPopFieldL( TInt aResourceId )
    {
    CAknExPopFieldManyLineDialog* dlg =
        CAknExPopFieldManyLineDialog::NewLC();
    ///iEikonEnv->EikAppUi()->AddToStackL( dlg );
    CleanupStack::Pop();
    dlg->ExecuteLD( aResourceId );
    }

// ----------------------------------------------------------------------------
// void CAknExPopFieldContainer::DisplayMultiPagePopFieldL( TInt )
//
// ----------------------------------------------------------------------------
//
void CAknExPopFieldContainer::DisplayMultiPagePopFieldL( TInt aResourceId )
    {
    CAknExPopFieldMultiPageDialog* dlg =
        CAknExPopFieldMultiPageDialog::NewLC();
    ///iEikonEnv->EikAppUi()->AddToStackL( dlg );
    CleanupStack::Pop();
    dlg->ExecuteLD( aResourceId );
    }

// ----------------------------------------------------------------------------
// void CAknExPopFieldContainer::DisplaySetAttribsPopFieldL( TInt )
//
// ----------------------------------------------------------------------------
//
void CAknExPopFieldContainer::DisplaySetAttribsPopFieldL( TInt aResourceId )
    {
    CAknExPopFieldAttribSetDialog* dlg =
        CAknExPopFieldAttribSetDialog::NewLC();
    CleanupStack::Pop();
    dlg->ExecuteLD( aResourceId );
    }

// ----------------------------------------------------------------------------
// void CAknExPopFieldContainer::CreateLabelL()
// Creates label object.
// ----------------------------------------------------------------------------
//
void CAknExPopFieldContainer::CreateLabelL()
    {
    if ( !iLabel )
        {
        iLabel = new( ELeave ) CEikLabel;
        iLabel->SetContainerWindowL( *this );
        iLabel->SetAlignment( EHCenterVCenter );
        iLabel->SetFont( LatinBold19() );
        }
    SetTextToLabelL( R_AKNEXPOPFIELD_TEXT_LABEL_TITLE );
    }

// ----------------------------------------------------------------------------
// TKeyResponse CAknExPopFieldContainer::OfferKeyEventL( const TKeyEvent&,
//  TEventCode )
// Handles the key events.
// ----------------------------------------------------------------------------
//
TKeyResponse CAknExPopFieldContainer::OfferKeyEventL(
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
            // Requires to display next outline screen.
            iView->DisplayNextOutlineL();
            DrawNow();
            break;
        default:
            return EKeyWasNotConsumed;
        }
    return EKeyWasConsumed;
    }

// ----------------------------------------------------------------------------
// void CAknExPopFieldContainer::SizeChanged()
// Called by framework when the view size is changed
// ----------------------------------------------------------------------------
//
void CAknExPopFieldContainer::SizeChanged()
    {
    iLabel->SetRect( Rect() );
    }

// ----------------------------------------------------------------------------
// TInt CAknExPopFieldContainer::CountComponentControls() const
// Returns number of component.
// ----------------------------------------------------------------------------
//
TInt CAknExPopFieldContainer::CountComponentControls() const
    {
    // returns nbr of controls inside this container
    return KAknExPopFieldCountComponent;
    }

// ----------------------------------------------------------------------------
// CCoeControl* CAknExPopFieldContainer::ComponentControl( TInt ) const
// Returns pointer to particular component.
// ----------------------------------------------------------------------------
//
CCoeControl* CAknExPopFieldContainer::ComponentControl( TInt aIndex ) const
    {
    switch ( aIndex ) // Component is...
        {
        case EAknExPopFieldComponentLabel: // Label object.
            return iLabel;
        default: // Exception : returns NULL value.
            return NULL;
        }
    }

// ----------------------------------------------------------------------------
// void CAknExPopFieldContainer::Draw( const TRect& ) const
// Clears the window's rectangle.
// ----------------------------------------------------------------------------
//
void CAknExPopFieldContainer::Draw( const TRect& aRect ) const
    {
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( AKNEXPOPFIELD_BACKGROUND_COLOR );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.DrawRect( aRect );
    }

// End of File
