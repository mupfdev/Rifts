/*
* =============================================================================
*  Name     : CAknExListFlagTestView
*  Part of  : AknExList
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

// INCLUDE FILES
#include <aknviewappui.h>
#include <aknexlist.rsg>
#include "AknExList.hrh"
#include "AknExListAppUi.h"
#include "AknExListFlagTestView.h"
#include "AknExListFlagTestContainer.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExListFlagTestView::CAknExListFlagTestView()
// Defalut constructor.
// ----------------------------------------------------------------------------
//
CAknExListFlagTestView::CAknExListFlagTestView()
:   iContainer( NULL )
    {
    }

// ----------------------------------------------------------------------------
// void CAknExListFlagTestView::ConstructL()
// EPOC constructor.
// ----------------------------------------------------------------------------
//
void CAknExListFlagTestView::ConstructL()
    {
    BaseConstructL( R_AKNEXLIST_VIEW_COLUMNVIEW );
    }

// ----------------------------------------------------------------------------
// CAknExListFlagTestView::~CAknExListFlagTestView()
// Destructor.
// ----------------------------------------------------------------------------
CAknExListFlagTestView::~CAknExListFlagTestView()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }

    delete iContainer; // Deletes container class object.
    }

// ----------------------------------------------------------------------------
// TInt CAknExListFlagTestView::OutlineId() const
// Returns current outline ID.
// ----------------------------------------------------------------------------
//
TInt CAknExListFlagTestView::OutlineId() const
    {
    return STATIC_CAST( CAknExListAppUi*, AppUi() )->OutlineId();
    }

// ----------------------------------------------------------------------------
// TUid CAknExListFlagTestView::Id()
// Returns ID of view.
// ----------------------------------------------------------------------------
TUid CAknExListFlagTestView::Id() const
    {
    return KAknExListFlagTestViewId; // Returns ID of FlagTestView.
    }

// ----------------------------------------------------------------------------
// void CAknExListFlagTestView::SetTitlePaneL( const TInt )
// Sets text of title pane.
// ----------------------------------------------------------------------------
//
void CAknExListFlagTestView::SetTitlePaneL( const TInt aOutlineId )
    {
    TInt resourceId = KAknExListInitTitleId;

    // Sets resource Id for title.
    switch ( aOutlineId ) // Outline ID is...
        {
        case EAknExListCmdOutline06: // OUTLINE06 screen.
            resourceId = R_AKNEXLIST_OUTLINE6;
            break;
        case EAknExListCmdOutline88: // OUTLINE88 screen.
            resourceId = R_AKNEXLIST_OUTLINE88;
            break;
        case EAknExListCmdOutline89: // OUTLINE89 screen.
            resourceId = R_AKNEXLIST_OUTLINE89;
            break;
        case EAknExListCmdOutline90: // OUTLINE90 screen.
            resourceId = R_AKNEXLIST_OUTLINE90;
            break;
        case EAknExListCmdOutline91: // OUTLINE91 screen.
            resourceId = R_AKNEXLIST_OUTLINE91;
            break;
        case EAknExListCmdOutline92: // OUTLINE92 screen.
            resourceId = R_AKNEXLIST_OUTLINE92;
            break;
        case EAknExListCmdOutline93: // OUTLINE93 screen.
            resourceId = R_AKNEXLIST_OUTLINE93;
            break;
        case EAknExListCmdOutline94: // OUTLINE94 screen.
            resourceId = R_AKNEXLIST_OUTLINE94;
            break;
        case EAknExListCmdOutline95: // OUTLINE95 screen.
            resourceId = R_AKNEXLIST_OUTLINE95;
            break;
        case EAknExListCmdOutline96: // OUTLINE96 screen.
            resourceId = R_AKNEXLIST_OUTLINE96;
            break;
        case EAknExListCmdOutline97: // OUTLINE97 screen.
            resourceId = R_AKNEXLIST_OUTLINE97;
            break;
        case EAknExListCmdOutline98: // OUTLINE98 screen.
            resourceId = R_AKNEXLIST_OUTLINE98;
            break;
        case EAknExListCmdOutline99: // OUTLINE99 screen.
            resourceId = R_AKNEXLIST_OUTLINE99;
            break;
        case EAknExListCmdOutline102: // OUTLINE102 screen.
            resourceId = R_AKNEXLIST_OUTLINE102;
            break;
        default:
            break;
        }

    IndicateTitlePaneTextL( resourceId ); // Sets text in title pane.
    }

// ----------------------------------------------------------------------------
// void CAknExListFlagTestView::DisplayListBoxL( const TInt )
// Displays the listbox by outline ID.
// ----------------------------------------------------------------------------
void CAknExListFlagTestView::DisplayListBoxL( const TInt aOutlineId )
    {
    if ( iContainer ) // Is container object created?
        {
        iContainer->DisplayListBoxL( aOutlineId );
        }
    }

// ----------------------------------------------------------------------------
// void CAknExListFlagTestView::DoActivateL( const TVwsViewId&, TUid,
//  const TDesC8& )
// Creates container class object.
// ----------------------------------------------------------------------------
void CAknExListFlagTestView::DoActivateL(
   const TVwsViewId& /*aPrevViewId*/,
   TUid /*aCustomMessageId*/,
   const TDesC8& /*aCustomMessage*/)
    {
    // Creates container class object.
    if ( !iContainer )
        {
        iContainer = new( ELeave ) CAknExListFlagTestContainer( this ) ;
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
// void CAknExListFlagTestView::DoDeactivate()
// Deletes container class object.
// ----------------------------------------------------------------------------
void CAknExListFlagTestView::DoDeactivate()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }

    delete iContainer; // Deletes the container class object.
    iContainer = NULL;
    }

// End of File
