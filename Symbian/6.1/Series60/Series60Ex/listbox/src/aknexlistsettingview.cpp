/*
* =============================================================================
*  Name     : CAknExListSettingView
*  Part of  : AknExList
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

// INCLUDE FILES
#include <aknviewappui.h>
#include <aknexlist.rsg>
#include "AknExList.hrh"
#include "AknExListSettingView.h"
#include "AknExListSettingContainer.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExListSettingnView::CAknExListSettingView()
// Defalut constructor.
// ----------------------------------------------------------------------------
//
CAknExListSettingView::CAknExListSettingView()
:   iContainer( NULL )
    {
    }

// ----------------------------------------------------------------------------
// void CAknExListSettingView::ConstructL()
// EPOC constructor.
// ----------------------------------------------------------------------------
//
void CAknExListSettingView::ConstructL()
    {
    BaseConstructL( R_AKNEXLIST_VIEW_SETTINGVIEW );
    }

// ----------------------------------------------------------------------------
// CAknExListSettingView::~CAknExListSettingView()
// Destructor.
// ----------------------------------------------------------------------------
CAknExListSettingView::~CAknExListSettingView()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }

    delete iContainer;
    }

// ----------------------------------------------------------------------------
// TUid CAknExListSettingView::Id()
// Returns ID of view.
// ----------------------------------------------------------------------------
TUid CAknExListSettingView::Id() const
    {
    return KAknExListSettingViewId; // Returns ID of SettingView.
    }

// ----------------------------------------------------------------------------
// void CAknExListSettingView::SetTitlePaneL( const TInt )
// Sets text of title pane.
// ----------------------------------------------------------------------------
//
void CAknExListSettingView::SetTitlePaneL( const TInt aOutlineId )
    {
    TInt resourceId( KAknExListInitTitleId );

    // Sets resource Id for title.
    switch ( aOutlineId ) // Outline ID is...
        {
        case EAknExListCmdOutline22: // OUTLINE22 screen.
            resourceId = R_AKNEXLIST_OUTLINE22;
            break;
        case EAknExListCmdOutline23: // OUTLINE23 screen.
            resourceId = R_AKNEXLIST_OUTLINE23;
            break;
        case EAknExListCmdOutline59: // OUTLINE59 screen.
            resourceId = R_AKNEXLIST_OUTLINE59;
            break;
        case EAknExListCmdOutline74: // OUTLINE74 screen.
            resourceId = R_AKNEXLIST_OUTLINE74;
            break;
        case EAknExListCmdOutline75: // OUTLINE75 screen.
            resourceId = R_AKNEXLIST_OUTLINE75;
            break;
        case EAknExListCmdOutline76: // OUTLINE76 screen.
            resourceId = R_AKNEXLIST_OUTLINE76;
            break;
        case EAknExListCmdOutline79: // OUTLINE79 screen.
            resourceId = R_AKNEXLIST_OUTLINE79;
            break;
        default:
            break;
        }

    IndicateTitlePaneTextL( resourceId ); // Sets text in title pane.
    }

// ----------------------------------------------------------------------------
// void CAknExListSettingView::DisplayListBoxL( const TInt )
// Displays the listbox by outline ID.
// ----------------------------------------------------------------------------
void CAknExListSettingView::DisplayListBoxL( const TInt aOutlineId )
    {
    if ( iContainer ) // Is container object created?
        {
        iContainer->DisplayListBoxL( aOutlineId );
        }
    }

// ----------------------------------------------------------------------------
// void CAknExListSettingView::DoActivateL( const TVwsViewId&, TUid,
//  const TDesC8& )
// Creates container class object.
// ----------------------------------------------------------------------------
void CAknExListSettingView::DoActivateL(
   const TVwsViewId& /*aPrevViewId*/,
   TUid /*aCustomMessageId*/,
   const TDesC8& /*aCustomMessage*/)
    {
    // Creates container class object.
    if ( !iContainer )
        {
        iContainer = new( ELeave ) CAknExListSettingContainer( this ) ;
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
// void CAknExListSettingView::DoDeactivate()
// Deletes container class object.
// ----------------------------------------------------------------------------
void CAknExListSettingView::DoDeactivate()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    delete iContainer;
    iContainer = NULL;

    }

// End of File
