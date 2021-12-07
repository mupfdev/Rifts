/*
* =============================================================================
*  Name     : CAknExListMarkView
*  Part of  : AknExList
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

// INCLUDE FILES
#include <eikmenub.h>
#include <aknviewappui.h>
#include <aknutils.h>
#include <aknexlist.rsg>
#include "AknExList.hrh"
#include "AknExListAppUi.h"
#include "AknExListMarkView.h"
#include "AknExListMarkContainer.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExListMarkView::CAknExListMarkView()
// Defalut constructor.
// ----------------------------------------------------------------------------
//
CAknExListMarkView::CAknExListMarkView()
:   iContainer( NULL )
    {
    }

// ----------------------------------------------------------------------------
// void CAknExListMarkView::ConstructL()
// EPOC constructor.
// ----------------------------------------------------------------------------
//
void CAknExListMarkView::ConstructL()
    {
    BaseConstructL( R_AKNEXLIST_VIEW_MARKVIEW );
    }

// ----------------------------------------------------------------------------
// CAknExListMarkView::~CAknExListMarkView()
// Destructor.
// ----------------------------------------------------------------------------
CAknExListMarkView::~CAknExListMarkView()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }

    delete iContainer; // Deletes container class object.
    }

// ----------------------------------------------------------------------------
// TUid CAknExListMarkView::Id()
// Returns ID of view.
// ----------------------------------------------------------------------------
TUid CAknExListMarkView::Id() const
    {
    return KAknExListMarkViewId; // Returns ID of MarkView.
    }

// ----------------------------------------------------------------------------
// void CAknExListMarkView::HandleCommandL( TInt )
// Handles the commands. Commands about marked items is executed. Other
// commands is passed HandleCommandL() of CAknExListBaseView class.
// ----------------------------------------------------------------------------
void CAknExListMarkView::HandleCommandL( TInt aCommand )
    {
    switch ( aCommand ) // Command is...
        {
        case EAknMarkAll:
        case EAknUnmarkAll:
            {
            // Gets pointer of current listbox.
            CEikListBox* listbox = iContainer->ListBox();

            if ( listbox )
                {
                AknSelectionService::HandleMarkableListProcessCommandL(
                    aCommand, listbox );
                }
            }
            break;
        default:
            CAknExListBaseView::HandleCommandL( aCommand );
            break;
        }
    }

// ----------------------------------------------------------------------------
// void CAknExListMarkView::SetTitlePaneL( const TInt )
// Sets text of title pane.
// ----------------------------------------------------------------------------
//
void CAknExListMarkView::SetTitlePaneL( const TInt aOutlineId )
    {
    TInt resourceId( KAknExListInitTitleId );

    // Sets resource Id for title.
    switch ( aOutlineId ) // Outline ID is...
        {
        case EAknExListCmdOutline32: // OUTLINE32 screen.
            resourceId = R_AKNEXLIST_OUTLINE32;
            break;
        case EAknExListCmdOutline81: // OUTLINE81 screen.
            resourceId = R_AKNEXLIST_OUTLINE81;
            break;
        case EAknExListCmdOutline82: // OUTLINE82 screen.
            resourceId = R_AKNEXLIST_OUTLINE82;
            break;
        case EAknExListCmdOutline83: // OUTLINE82 screen.
            resourceId = R_AKNEXLIST_OUTLINE83;
            break;
        case EAknExListCmdOutline87: // OUTLINE87 screen.
            resourceId = R_AKNEXLIST_OUTLINE87;
            break;
        default:
            break;
        }

    IndicateTitlePaneTextL( resourceId ); // Sets text in title pane.
    }

// ----------------------------------------------------------------------------
// void CAknExListMarkView::DisplayListBoxL( const TInt )
// Displays the listbox by outline ID.
// ----------------------------------------------------------------------------
void CAknExListMarkView::DisplayListBoxL( const TInt aOutlineId )
    {
    if ( iContainer ) // Is container object created?
        {
        iContainer->DisplayListBoxL( aOutlineId );
        }
    }

// ----------------------------------------------------------------------------
// void CAknExListMarkView::DoActivateL( const TVwsViewId&, TUid,
//  const TDesC8& )
// Creates container class object.
// ----------------------------------------------------------------------------
void CAknExListMarkView::DoActivateL(
   const TVwsViewId& /*aPrevViewId*/,
   TUid /*aCustomMessageId*/,
   const TDesC8& /*aCustomMessage*/)
    {
    // Creates container class object.
    if ( !iContainer )
        {
        iContainer = new( ELeave ) CAknExListMarkContainer( this ) ;
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
// void CAknExListMarkView::DoDeactivate()
// Deletes container class object.
// ----------------------------------------------------------------------------
void CAknExListMarkView::DoDeactivate()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }

    delete iContainer; // Deletes the container class object.
    iContainer = NULL;
    }

// ----------------------------------------------------------------------------
// void CAknExListMarkView::DynInitMenuPaneL( TInt, CEikMenuPane* )
// This function is called by the EIKON framework just before it displays a
// menu pane.
// ----------------------------------------------------------------------------
//
void CAknExListMarkView::DynInitMenuPaneL(
    TInt aResourceId,
    CEikMenuPane* aMenuPane )
    {
    TInt outlineId( STATIC_CAST( CAknExListAppUi*, AppUi() )->OutlineId() );

    if ( aResourceId == R_AKNEXLIST_MENU_PANE_MARKABLE_LIST )
        {
        if ( outlineId == EAknExListCmdOutline81 )
            {
            // Lifts dimmed of menu for mark all and unmark all.
            aMenuPane->SetItemDimmed( EAknMarkAll, EFalse );
            aMenuPane->SetItemDimmed( EAknUnmarkAll, EFalse );
            }
        }
    }

// End of File
