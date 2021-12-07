/*
* =============================================================================
*  Name     : CAknExListColumnView
*  Part of  : AknExList
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

// INCLUDE FILES
#include <aknviewappui.h>
#include <eikbtgpc.h>
#include <aknexlist.rsg>
#include <avkon.rsg>
#include <avkon.hrh>
#include "AknExList.hrh"
#include "AknExListColumnView.h"
#include "AknExListColumnContainer.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExListColumnView::CAknExListColumnView()
// Defalut constructor.
// ----------------------------------------------------------------------------
//
CAknExListColumnView::CAknExListColumnView()
:   iContainer( NULL )
    {
    }

// ----------------------------------------------------------------------------
// void CAknExListColumnView::ConstructL()
// EPOC constructor.
// ----------------------------------------------------------------------------
//
void CAknExListColumnView::ConstructL()
    {
    BaseConstructL( R_AKNEXLIST_VIEW_COLUMNVIEW );
    }

// ----------------------------------------------------------------------------
// CAknExListColumnView::~CAknExListColumnView()
// Destructor.
// ----------------------------------------------------------------------------
CAknExListColumnView::~CAknExListColumnView()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }

    delete iContainer; // Deletes container class object.
    }

// ----------------------------------------------------------------------------
// CAknExListColumnView::UpdateCbaL()
// Update CBA-key
// ----------------------------------------------------------------------------
void CAknExListColumnView::UpdateCbaL(TInt aResourceId)
    {
    TInt resourceId(R_AVKON_SOFTKEYS_OPTIONS_BACK);

    if (aResourceId == R_AVKON_SOFTKEYS_DONE_CANCEL)
        {
        resourceId = R_AVKON_SOFTKEYS_DONE_CANCEL;
        }

    CEikButtonGroupContainer* cba = Cba();
    cba->SetCommandSetL(resourceId);
    cba->DrawDeferred();
    }


// ----------------------------------------------------------------------------
// TUid CAknExListColumnView::Id()
// Returns ID of view.
// ----------------------------------------------------------------------------
TUid CAknExListColumnView::Id() const
    {
    return KAknExListColumnViewId; // Returns ID of ColumnView.
    }

// ----------------------------------------------------------------------------
// void CAknExListColumnView::SetTitlePaneL( const TInt )
// Sets text of title pane.
// ----------------------------------------------------------------------------
//
void CAknExListColumnView::SetTitlePaneL( const TInt aOutlineId )
    {
    TInt resourceId( KAknExListInitTitleId );

    // Sets resource Id for title.
    switch ( aOutlineId ) // Outline ID is...
        {
        case EAknExListCmdOutline01: // OUTLINE1 screen.
            resourceId = R_AKNEXLIST_OUTLINE1;
            break;
        case EAknExListCmdOutline02: // OUTLINE2 screen.
            resourceId = R_AKNEXLIST_OUTLINE2;
            break;
        case EAknExListCmdOutline03: // OUTLINE3 screen.
            resourceId = R_AKNEXLIST_OUTLINE3;
            break;
        case EAknExListCmdOutline04: // OUTLINE4 screen.
            resourceId = R_AKNEXLIST_OUTLINE4;
            break;
        case EAknExListCmdOutline05: // OUTLINE5 screen.
            resourceId = R_AKNEXLIST_OUTLINE5;
            break;
        case EAknExListCmdOutline07: // OUTLINE7 screen.
            resourceId = R_AKNEXLIST_OUTLINE7;
            break;
        case EAknExListCmdOutline08: // OUTLINE8 screen.
            resourceId = R_AKNEXLIST_OUTLINE8;
            break;
        case EAknExListCmdOutline09: // OUTLINE9 screen.
            resourceId = R_AKNEXLIST_OUTLINE9;
            break;
        case EAknExListCmdOutline10: // OUTLINE10 screen.
            resourceId = R_AKNEXLIST_OUTLINE10;
            break;
        case EAknExListCmdOutline11: // OUTLINE11 screen.
            resourceId = R_AKNEXLIST_OUTLINE11;
            break;
        case EAknExListCmdOutline12: // OUTLINE12 screen.
            resourceId = R_AKNEXLIST_OUTLINE12;
            break;
        case EAknExListCmdOutline13: // OUTLINE13 screen.
            resourceId = R_AKNEXLIST_OUTLINE13;
            break;
        case EAknExListCmdOutline14: // OUTLINE14 screen.
            resourceId = R_AKNEXLIST_OUTLINE14;
            break;
        case EAknExListCmdOutline15: // OUTLINE15 screen.
            resourceId = R_AKNEXLIST_OUTLINE15;
            break;
        case EAknExListCmdOutline26: // OUTLINE26 screen.
            resourceId = R_AKNEXLIST_OUTLINE26;
            break;
        case EAknExListCmdOutline27: // OUTLINE27 screen.
            resourceId = R_AKNEXLIST_OUTLINE27;
            break;
        case EAknExListCmdOutline30: // OUTLINE30 screen.
            resourceId = R_AKNEXLIST_OUTLINE30;
            break;
        case EAknExListCmdOutline31: // OUTLINE31 screen.
            resourceId = R_AKNEXLIST_OUTLINE31;
            break;
        case EAknExListCmdOutline33: // OUTLINE33 screen.
            resourceId = R_AKNEXLIST_OUTLINE33;
            break;
        case EAknExListCmdOutline41: // OUTLINE41 screen.
            resourceId = R_AKNEXLIST_OUTLINE41;
            break;
        case EAknExListCmdOutline43: // OUTLINE43 screen.
            resourceId = R_AKNEXLIST_OUTLINE43;
            break;
        case EAknExListCmdOutline44: // OUTLINE44 screen.
            resourceId = R_AKNEXLIST_OUTLINE44;
            break;
        case EAknExListCmdOutline45: // OUTLINE45 screen.
            resourceId = R_AKNEXLIST_OUTLINE45;
            break;
        case EAknExListCmdOutline46: // OUTLINE46 screen.
            resourceId = R_AKNEXLIST_OUTLINE46;
            break;
        case EAknExListCmdOutline47: // OUTLINE47 screen.
            resourceId = R_AKNEXLIST_OUTLINE47;
            break;
        case EAknExListCmdOutline48: // OUTLINE48 screen.
            resourceId = R_AKNEXLIST_OUTLINE48;
            break;
        case EAknExListCmdOutline49: // OUTLINE49 screen.
            resourceId = R_AKNEXLIST_OUTLINE49;
            break;
        case EAknExListCmdOutline50: // OUTLINE50 screen.
            resourceId = R_AKNEXLIST_OUTLINE50;
            break;
        case EAknExListCmdOutline51: // OUTLINE51 screen.
            resourceId = R_AKNEXLIST_OUTLINE51;
            break;
        case EAknExListCmdOutline52: // OUTLINE52 screen.
            resourceId = R_AKNEXLIST_OUTLINE52;
            break;
        case EAknExListCmdOutline60: // OUTLINE60 screen.
            resourceId = R_AKNEXLIST_OUTLINE60;
            break;
        case EAknExListCmdOutline61: // OUTLINE61 screen.
            resourceId = R_AKNEXLIST_OUTLINE61;
            break;
        case EAknExListCmdOutline62: // OUTLINE62 screen.
            resourceId = R_AKNEXLIST_OUTLINE62;
            break;
        case EAknExListCmdOutline63: // OUTLINE63 screen.
            resourceId = R_AKNEXLIST_OUTLINE63;
            break;
        case EAknExListCmdOutline64: // OUTLINE64 screen.
            resourceId = R_AKNEXLIST_OUTLINE64;
            break;
        case EAknExListCmdOutline66: // OUTLINE66 screen.
            resourceId = R_AKNEXLIST_OUTLINE66;
            break;
        case EAknExListCmdOutline69: // OUTLINE69 screen.
            resourceId = R_AKNEXLIST_OUTLINE69;
            break;
        case EAknExListCmdOutline70: // OUTLINE70 screen.
            resourceId = R_AKNEXLIST_OUTLINE70;
            break;
        case EAknExListCmdOutline77: // OUTLINE77 screen.
            resourceId = R_AKNEXLIST_OUTLINE77;
            break;
        case EAknExListCmdOutline78: // OUTLINE78 screen.
            resourceId = R_AKNEXLIST_OUTLINE78;
            break;
        case EAknExListCmdOutline80: // OUTLINE80 screen.
            resourceId = R_AKNEXLIST_OUTLINE80;
            break;
        case EAknExListCmdOutline80Sub: // Sub of OUTLINE80 screen.
            resourceId = R_AKNEXLIST_OUTLINE80SUB;
            break;
        default:
            break;
        }

    IndicateTitlePaneTextL( resourceId ); // Sets text in title pane.
    }

// ----------------------------------------------------------------------------
// void CAknExListColumnView::DisplayListBoxL( const TInt )
// Displays the listbox by outline ID.
// ----------------------------------------------------------------------------
void CAknExListColumnView::DisplayListBoxL( const TInt aOutlineId )
    {
    if ( iContainer ) // Is container object created?
        {
        iContainer->DisplayListBoxL( aOutlineId );
        }
    }


// ----------------------------------------------------------------------------
// void CAknExListColumnView::DoActivateL( const TVwsViewId&, TUid,
//  const TDesC8& )
// Creates container class object.
// ----------------------------------------------------------------------------
void CAknExListColumnView::DoActivateL(
   const TVwsViewId& /*aPrevViewId*/,
   TUid /*aCustomMessageId*/,
   const TDesC8& /*aCustomMessage*/)
    {
    // Creates container class object.
    if ( !iContainer )
        {
        iContainer = new( ELeave ) CAknExListColumnContainer( this ) ;
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
// void CAknExListColumnView::DoDeactivate()
// Deletes container class object.
// ----------------------------------------------------------------------------
void CAknExListColumnView::DoDeactivate()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }

    delete iContainer; // Deletes the container class object.
    iContainer = NULL;
    }

// End of File
