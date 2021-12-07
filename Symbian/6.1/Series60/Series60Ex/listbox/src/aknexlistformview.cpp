/*
* =============================================================================
*  Name     : CAknExListFormView
*  Part of  : AknExList
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

// INCLUDE FILES
#include <aknviewappui.h>
#include <aknexlist.rsg>
#include "AknExList.hrh"
#include "AknExListFormView.h"
#include "AknExListFormContainer.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExListFormnView::CAknExListFormView()
// Defalut constructor.
// ----------------------------------------------------------------------------
//
CAknExListFormView::CAknExListFormView()
:   iContainer( NULL )
    {
    }

// ----------------------------------------------------------------------------
// void CAknExListFormView::ConstructL()
// EPOC constructor.
// ----------------------------------------------------------------------------
//
void CAknExListFormView::ConstructL()
    {
    BaseConstructL( R_AKNEXLIST_VIEW_FORMVIEW );
    }

// ----------------------------------------------------------------------------
// CAknExListFormView::~CAknExListFormView()
// Destructor.
// ----------------------------------------------------------------------------
CAknExListFormView::~CAknExListFormView()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }

    delete iContainer;
    }

// ----------------------------------------------------------------------------
// TUid CAknExListFormView::Id()
// Returns ID of view.
// ----------------------------------------------------------------------------
TUid CAknExListFormView::Id() const
    {
    return KAknExListFormViewId; // Returns ID of FormView.
    }

// ----------------------------------------------------------------------------
// void CAknExListFormView::SetTitlePaneL( const TInt )
// Sets text of title pane.
// ----------------------------------------------------------------------------
//
void CAknExListFormView::SetTitlePaneL( const TInt aOutlineId )
    {
    TInt resourceId( KAknExListInitTitleId );

    // Sets resource Id for title.
    switch ( aOutlineId ) // Outline ID is...
        {
        case EAknExListCmdOutline16: // OUTLINE16 screen.
            resourceId = R_AKNEXLIST_OUTLINE16;
            break;
        case EAknExListCmdOutline17: // OUTLINE17 screen.
            resourceId = R_AKNEXLIST_OUTLINE17;
            break;
        case EAknExListCmdOutline18:  // OUTLINE18 screen.
            resourceId = R_AKNEXLIST_OUTLINE18;
            break;
        case EAknExListCmdOutline19: // OUTLINE19 screen.
            resourceId = R_AKNEXLIST_OUTLINE19;
            break;
        case EAknExListCmdOutline20: // OUTLINE20 screen.
            resourceId = R_AKNEXLIST_OUTLINE20;
            break;
        case EAknExListCmdOutline21: // OUTLINE21 screen.
            resourceId = R_AKNEXLIST_OUTLINE21;
            break;
        case EAknExListCmdOutline53: // OUTLINE53 screen.
            resourceId = R_AKNEXLIST_OUTLINE53;
            break;
        case EAknExListCmdOutline54: // OUTLINE54 screen.
            resourceId = R_AKNEXLIST_OUTLINE54;
            break;
        case EAknExListCmdOutline55: // OUTLINE55 screen.
            resourceId = R_AKNEXLIST_OUTLINE55;
            break;
        case EAknExListCmdOutline57: // OUTLINE57 screen.
            resourceId = R_AKNEXLIST_OUTLINE57;
            break;
        case EAknExListCmdOutline58: // OUTLINE58 screen.
            resourceId = R_AKNEXLIST_OUTLINE58;
            break;
        case EAknExListCmdOutline67: // OUTLINE67 screen.
            resourceId = R_AKNEXLIST_OUTLINE67;
            break;
        case EAknExListCmdOutline68: // OUTLINE69 screen.
            resourceId = R_AKNEXLIST_OUTLINE68;
            break;
        case EAknExListCmdOutline71: // OUTLINE71 screen.
            resourceId = R_AKNEXLIST_OUTLINE71;
            break;
        default:
            break;
        }

    IndicateTitlePaneTextL( resourceId ); // Sets text in title pane.
    }

// ----------------------------------------------------------------------------
// void CAknExListFormView::DisplayListBoxL( const TInt )
// Displays the listbox by outline ID.
// ----------------------------------------------------------------------------
void CAknExListFormView::DisplayListBoxL( const TInt aOutlineId )
    {
    if ( iContainer ) // Is container object created?
        {
        iContainer->DisplayListBoxL( aOutlineId );
        }
    }

// ----------------------------------------------------------------------------
// void CAknExListFormView::DoActivateL( const TVwsViewId&, TUid,
//  const TDesC8& )
// Creates container class object.
// ----------------------------------------------------------------------------
void CAknExListFormView::DoActivateL(
   const TVwsViewId& /*aPrevViewId*/,
   TUid /*aCustomMessageId*/,
   const TDesC8& /*aCustomMessage*/)
    {
    // Creates container class object.
    if ( !iContainer )
        {
        iContainer = new( ELeave ) CAknExListFormContainer( this ) ;
        iContainer->SetMopParent(this);
        iContainer->ConstructL( ClientRect() );

        // Adds container to view control stack.
        AppUi()->AddToStackL( *this, iContainer );

        // Displays outline.
        DisplayInitOutlineL();

        iContainer->MakeVisible( ETrue );
        }
   }

// ----------------------------------------------------------------------------
// void CAknExListFormView::DoDeactivate()
// Deletes container class object.
// ----------------------------------------------------------------------------
void CAknExListFormView::DoDeactivate()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }

    delete iContainer;
    iContainer = NULL;
    }

// End of File
