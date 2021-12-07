/*
* ============================================================================
*  Name     : CAknExFormContainer
*  Part of  : AknExForm
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include <aknutils.h> // for AKN_LAF_COLOR
#include <eikenv.h>
#include <eiklabel.h> // for label
#include <aknform.h>  // for form control
#include <eikseced.h> // for secret editor
#include <eikedwin.h> // for edwins
#include <aknexform.rsg>
#include "AknExForm.hrh"
#include "AknExFormView.h"
#include "AknExFormContainer.h"
#include "AknExFormSaveForm.h"

// MACROS
#define AKNEXFORM_BACKGROUND_COLOR AKN_LAF_COLOR( 219 )

// CONSTANTS
const TInt KAknExFormCountComponent = 1;
const TInt KAknExFormMessageBufLength = 256;

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExFormContainer::CAknExFormContainer( CAknExFormView* )
// Overload constructor.
// ----------------------------------------------------------------------------
//
CAknExFormContainer::CAknExFormContainer( CAknExFormView* aView )
:   iView( aView ),
    iLabel( NULL )
    {
    }

// ----------------------------------------------------------------------------
// void CAknExFormContainer::ConstructL( const TRect& )
// EPOC constructor.
// ----------------------------------------------------------------------------
//
void CAknExFormContainer::ConstructL( const TRect& aRect )
    {
    // Creates window.
    CreateWindowL();

    // Creates label object.
    CreateLabelL();

    SetRect( aRect ); // Sets rectangle of frame.
    ActivateL(); // Activates the window. (Ready to draw)
    }

// ----------------------------------------------------------------------------
// CAknExFormContainer::~CAknExFormContainer()
// Destructor.
// ----------------------------------------------------------------------------
//
CAknExFormContainer::~CAknExFormContainer()
    {
    delete iLabel;
    }

// ----------------------------------------------------------------------------
// void CAknExFormContainer::SetTextToLabelL( TInt )
//
// ----------------------------------------------------------------------------
//
void CAknExFormContainer::SetTextToLabelL( TInt aResourceId )
    {
    TBuf<KAknExFormMessageBufLength> messageString( NULL );
    iCoeEnv->ReadResource( messageString, aResourceId );
    iLabel->SetTextL( messageString );
    }

// ----------------------------------------------------------------------------
// void CAknExFormContainer::DisplayFormL( TInt )
//
// ----------------------------------------------------------------------------
//
void CAknExFormContainer::DisplayFormL( TInt aResourceId )
    {
    CAknExFormSaveForm* form = CAknExFormSaveForm::NewL();
    if ( aResourceId == R_AKNEXFORM_DOUBLE_AND_SINGLE_LINE_FORM)
        {
        form->PrepareLC( aResourceId );
        TBuf<KAknExFormMessageBufLength> edwinString( NULL );
        iCoeEnv->ReadResource( edwinString, R_AKNEXFORM_TEXT_EDWIN_TEXT );
        CEikEdwin* myEdwin = STATIC_CAST(CEikEdwin*,form->ControlOrNull(EAknExFormDlgCtrlIdEdwin01)) ;
        if ( myEdwin )
            myEdwin->SetTextL(&edwinString);
        myEdwin = STATIC_CAST(CEikEdwin*,form->ControlOrNull(EAknExFormDlgCtrlIdEdwin11)) ;
        if ( myEdwin )
            myEdwin->SetTextL(&edwinString);
        form->RunLD();
        }
    else
        {
        form->ExecuteLD( aResourceId );
        }
    }

// ----------------------------------------------------------------------------
// void CAknExFormContainer::CreateLabelL()
// Creates label object.
// ----------------------------------------------------------------------------
//
void CAknExFormContainer::CreateLabelL()
    {
    if ( !iLabel )
        {
        iLabel = new( ELeave ) CEikLabel;
        iLabel->SetContainerWindowL( *this );
        iLabel->SetAlignment( EHCenterVCenter );
#ifdef __AVKON_APAC__
        iLabel->SetFont( ApacPlain16() );
#else
        iLabel->SetFont( LatinBold19() );
#endif
        }
    SetTextToLabelL( R_AKNEXFORM_TEXT_LABEL_TITLE );
    }

// ----------------------------------------------------------------------------
// TKeyResponse CAknExFormContainer::OfferKeyEventL( const TKeyEvent&,
//  TEventCode )
// Handles the key events.
// ----------------------------------------------------------------------------
//
TKeyResponse CAknExFormContainer::OfferKeyEventL(
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
// void CAknExFormContainer::SizeChanged()
// Called by framework when the view size is changed
// ----------------------------------------------------------------------------
//
void CAknExFormContainer::SizeChanged()
    {
    iLabel->SetRect( Rect() );
    }

// ----------------------------------------------------------------------------
// TInt CAknExFormContainer::CountComponentControls() const
// Returns number of component.
// ----------------------------------------------------------------------------
//
TInt CAknExFormContainer::CountComponentControls() const
    {
    // returns nbr of controls inside this container
    return KAknExFormCountComponent;
    }

// ----------------------------------------------------------------------------
// CCoeControl* CAknExFormContainer::ComponentControl( TInt ) const
// Returns pointer to particular component.
// ----------------------------------------------------------------------------
//
CCoeControl* CAknExFormContainer::ComponentControl( TInt aIndex ) const
    {
    switch ( aIndex ) // Component is...
        {
        case EAknExFormComponentLabel: // Label object.
            return iLabel;
        default: // Exception : returns NULL value.
            return NULL;
        }
    }

// ----------------------------------------------------------------------------
// void CAknExFormContainer::Draw( const TRect& ) const
// Clears the window's rectangle.
// ----------------------------------------------------------------------------
//
void CAknExFormContainer::Draw( const TRect& aRect ) const
    {
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( AKNEXFORM_BACKGROUND_COLOR );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.DrawRect( aRect );
    }

// End of File
