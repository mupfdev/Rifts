/*
* =============================================================================
*  Name     : CAknExListFlagTestContainer
*  Part of  : AknExList
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

// INCLUDE FILES
#include <aknlists.h> // for avrell style listbox
#include <akntabgrp.h>
#include <aknexlist.rsg>
#include <aknexlist.mbg>
#include "AknExList.hrh"
#include "AknExListConst.h" // For bitmap file name
#include "AknExListFlagTestView.h"
#include "AknExListFlagTestContainer.h"

// CONSTANTS
// for initialization.
const TInt KAknExListInitTabId = 0;
const TInt KAknExListInitValueOfListFlags = 0;
const TInt KAknExListInitCount = 0;
// for key event.
#define AKNEXLIST_CHANGE_METHOD_KEY '0'

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExListFlagTestContainer::CAknExListFlagTestContainer(
//  CAknExListFlagTestView* )
// Copy constructor.
// ----------------------------------------------------------------------------
//
CAknExListFlagTestContainer::CAknExListFlagTestContainer(
    CAknExListFlagTestView* aView )
:   iListBox( NULL ),
    iView( aView ),
    iOutlineId( KAknExListInitOutlineId ),
    iInternalFlag( EFalse ),
    iKeyEvent( EFalse )
    {
    }

// ----------------------------------------------------------------------------
// void CAknExListFlagTestContainer::ConstructL( const TRect& )
// EPOC constructor.
// ----------------------------------------------------------------------------
//
void CAknExListFlagTestContainer::ConstructL( const TRect& aRect )
    {
    CreateWindowL(); // Creates window.
    SetRect( aRect ); // Sets rectangle of frame.
    ActivateL(); // Activates window. (Ready to draw)
    }

// ----------------------------------------------------------------------------
// CAknExListFlagTestContainer::~CAknExListFlagTestContainer()
// Destructor.
// ----------------------------------------------------------------------------
//
CAknExListFlagTestContainer::~CAknExListFlagTestContainer()
    {
    delete iListBox; // Deletes listbox object.
    }

// ----------------------------------------------------------------------------
// void CAknExListFlagTestContainer::DisplayListBoxL( const TInt )
// Displays listbox.
// ----------------------------------------------------------------------------
//
void CAknExListFlagTestContainer::DisplayListBoxL( const TInt aTabId )
    {
    // Deletes listbox object.
    if ( iListBox )
        {
        delete iListBox;
        iListBox = NULL;
        }

    // Initialize of iInternalFlag except via key event.
    if ( iKeyEvent == EFalse )
        {
        iInternalFlag = EFalse;
        }

    if ( aTabId == EAknExListTabIdType01 ||
         aTabId == EAknExListTabIdType01Withs )
        {
        // Sets outlineId.
        iOutlineId = iView->OutlineId();
        }

    TInt resourceId( KAknExListInitListResourceId ); // For listbox.
    TInt messageId( KAknExListMessageInitId ); // For displaying message.
    TBool flagsOfGraphic( EFalse ); // Flag for graphic.
    TBool flagsOfNumber( EFalse ); // Flag for auto numbering.
    CEikColumnListBox* columnListBox = NULL;
    CEikFormattedCellListBox* formattedListBox = NULL;

    // Creates ListBox control object and sets resource ID.
    switch ( aTabId ) // Tab ID is...
        {
        // Single pane.
        case EAknExListTabIdType01:
        case EAknExListTabIdType01Withs:
            if ( !iInternalFlag )
                {
                resourceId = ResourceIdSingle();
                }
            IsNeedGarphic( flagsOfGraphic );
            columnListBox = new( ELeave ) CAknSingleStyleListBox();
            break;
        // Single number pane.
        case EAknExListTabIdType02:
        case EAknExListTabIdType02Withs:
            if ( !iInternalFlag )
                {
                resourceId = ResourceIdSingleNumber();
                }
            IsNeedGarphic( flagsOfGraphic );
            flagsOfNumber = ETrue;
            columnListBox = new( ELeave ) CAknSingleNumberStyleListBox();
            break;
        // Single heading pane.
        case EAknExListTabIdType03:
        case EAknExListTabIdType03Withs:
            if ( !iInternalFlag )
                {
                resourceId = ResourceIdSingleHeading();
                }
            IsNeedGarphic( flagsOfGraphic );
            columnListBox = new( ELeave ) CAknSingleHeadingStyleListBox();
            break;
        // Single graphic pane.
        case EAknExListTabIdType04:
        case EAknExListTabIdType04Withs:
            if ( !iInternalFlag )
                {
                resourceId = ResourceIdSingleGraphic();
                }
            flagsOfGraphic = ETrue;
            columnListBox = new( ELeave ) CAknSingleGraphicStyleListBox();
            break;
        // Single graphic heading pane.
        case EAknExListTabIdType05:
        case EAknExListTabIdType05Withs:
            if ( !iInternalFlag )
                {
                resourceId = ResourceIdSingleGraphicHeading();
                }
            flagsOfGraphic = ETrue;
            columnListBox =
                new( ELeave ) CAknSingleGraphicHeadingStyleListBox();
            break;
        // Single number heading pane.
        case EAknExListTabIdType06:
        case EAknExListTabIdType06Withs:
            if ( !iInternalFlag )
                {
                resourceId = ResourceIdSingleNumberHeading();
                }
            IsNeedGarphic( flagsOfGraphic );
            flagsOfNumber = ETrue;
            columnListBox =
                new( ELeave ) CAknSingleNumberHeadingStyleListBox();
            break;
        // Single large graphic pane.
        case EAknExListTabIdType07:
        case EAknExListTabIdType07Withs:
            if ( !iInternalFlag )
                {
                resourceId = ResourceIdSingleLargeGraphic();
                }
            flagsOfGraphic = ETrue;
            columnListBox = new( ELeave ) CAknSingleLargeStyleListBox();
            break;
        // Single big pane.
        case EAknExListTabIdType08:
        case EAknExListTabIdType08Withs:
            if ( !iInternalFlag )
                {
                resourceId = ResourceIdBigSingle();
                }
            IsNeedGarphic( flagsOfGraphic );
            formattedListBox = new( ELeave ) CAknDoubleStyleListBox();
            break;
        // Single big number pane.
        case EAknExListTabIdType09:
        case EAknExListTabIdType09Withs:
            if ( !iInternalFlag )
                {
                resourceId = ResourceIdBigSingleNumber();
                }
            IsNeedGarphic( flagsOfGraphic );
            flagsOfNumber = ETrue;
            formattedListBox = new( ELeave ) CAknDoubleNumberStyleListBox();
            break;
        // Single big large graphic pane.
        case EAknExListTabIdType10:
        case EAknExListTabIdType10Withs:
            if ( !iInternalFlag )
                {
                resourceId = ResourceIdBigSingleLargeGraphic();
                }
            flagsOfGraphic = ETrue;
            formattedListBox = new( ELeave ) CAknDoubleLargeStyleListBox();
            break;
        // Double pane.
        case EAknExListTabIdType11:
        case EAknExListTabIdType11Withs:
            if ( !iInternalFlag )
                {
                resourceId = ResourceIdDouble();
                }
            IsNeedGarphic( flagsOfGraphic );
            formattedListBox = new( ELeave ) CAknDoubleStyleListBox();
            break;
        // Double number pane.
        case EAknExListTabIdType12:
        case EAknExListTabIdType12Withs:
            if ( !iInternalFlag )
                {
                resourceId = ResourceIdDoubleNumber();
                }
            IsNeedGarphic( flagsOfGraphic );
            flagsOfNumber = ETrue;
            formattedListBox = new( ELeave ) CAknDoubleNumberStyleListBox();
            break;
        // Double large graphic pane.
        case EAknExListTabIdType13:
        case EAknExListTabIdType13Withs:
            if ( !iInternalFlag )
                {
                resourceId = ResourceIdDoubleLargeGraphic();
                }
            flagsOfGraphic = ETrue;
            formattedListBox = new( ELeave ) CAknDoubleLargeStyleListBox();
            break;
        // Setting pane.
        case EAknExListTabIdType14:
        case EAknExListTabIdType14Withs:
            if ( !iInternalFlag )
                {
                resourceId = ResourceIdSetting();
                }
            flagsOfGraphic = ETrue;
            formattedListBox = new( ELeave ) CAknSettingStyleListBox();
            break;
        // Setting number pane.
        case EAknExListTabIdType15:
        case EAknExListTabIdType15Withs:
            if ( !iInternalFlag )
                {
                resourceId = ResourceIdSettingNumber();
                }
            flagsOfGraphic = ETrue;
            flagsOfNumber = ETrue;
            formattedListBox = new( ELeave ) CAknSettingNumberStyleListBox();
            break;
        // Double graphic pane.
        case EAknExListTabIdType16:
        case EAknExListTabIdType16Withs:
            if ( !iInternalFlag )
                {
                resourceId = ResourceIdDoubleGraphic();
                }
            flagsOfGraphic = ETrue;
            formattedListBox = new( ELeave ) CAknDoubleGraphicStyleListBox();
            break;
        default:
            break;
        }

    if ( columnListBox )
        {
        iListBox = columnListBox;
        // Sets ListBox.
        if ( resourceId )
            {
            // From resource.
            SetListBoxFromResourceL( columnListBox, resourceId );
            // If you show the message("Make from resource"), please delete comment('//');
            // messageId = R_AKNEXLIST_RESOURCE_MSG;
            }
        else
            {
            // From internal(only flag).
            TInt flags( ListFlags() );
            CDesCArray* textArray = ListItemsL( aTabId );
            SetListBoxFromInnerDescriptionL( columnListBox, flags, textArray );
            // If you show the message("Make from code"), please delete comment('//');
            // messageId = R_AKNEXLIST_INTERNAL_MSG;
            }
        if ( flagsOfGraphic )
            {
            // Creates graphic.
            SetGraphicIconL( columnListBox );
            }
        }

    else if ( formattedListBox )
        {
        iListBox = formattedListBox;
        // Sets ListBox.
        if ( resourceId )
            {
            // From resource.
            SetListBoxFromResourceL( formattedListBox, resourceId );
            // If you show the message("Make from resource"), please delete comment('//');
            // messageId = R_AKNEXLIST_RESOURCE_MSG;
            }
        else
            {
            // From internal(only flag).
            TInt flags( ListFlags() );
            CDesCArray* textArray = ListItemsL( aTabId );
            SetListBoxFromInnerDescriptionL(
                formattedListBox, flags, textArray );
            // If you show the message("Make from code"), please delete comment('//');
            // messageId = R_AKNEXLIST_INTERNAL_MSG;
            }

        if ( flagsOfGraphic )
            {
            // Creates graphic.
            SetGraphicIconL( formattedListBox );
            }
        }

    if ( iListBox )
        {
        iListBox->SetListBoxObserver( this );

        SizeChanged();

        if ( flagsOfNumber )
            {
            // Automatic numbering.
            AutoNumberingL( STATIC_CAST( CEikTextListBox*, iListBox ) );
            }

        iListBox->ActivateL();
        // Update scrollbar in order to draw correct scroll bar.
        UpdateScrollBar(iListBox);
        
        }

    DrawNow();

    if ( messageId )
        {
        InfoMessage( messageId ); // Displays information message.
        }
    }

// ----------------------------------------------------------------------------
// TKeyResponse CAknExListFlagTestContainer::OfferKeyEventL( const TKeyEvent&,
//  TEventCode )
// Handles the key events.
// ----------------------------------------------------------------------------
//
TKeyResponse CAknExListFlagTestContainer::OfferKeyEventL(
    const TKeyEvent& aKeyEvent,
    TEventCode aType )
    {
    if ( aType != EEventKey ) // Is not key event?
        {
        return EKeyWasNotConsumed;
        }

    CAknTabGroup* tabGroup = iView->TabGroup();

    switch ( aKeyEvent.iCode ) // The code of key event is...
        {
        case EKeySpace: // Space key.
            iView->DisplayNextOutlineL();
            return EKeyWasConsumed;

        // Switches tab.
        case EKeyLeftArrow: // Left key.
        case EKeyRightArrow: // Right Key.
            if ( tabGroup ) // Is tab group created?
                {
                if ( tabGroup->OfferKeyEventL( aKeyEvent, aType ) ==
                     EKeyWasConsumed )
                    {
                    DisplayListBoxL(
                        tabGroup->TabIdFromIndex(
                            tabGroup->ActiveTabIndex() ) );
                    return EKeyWasConsumed;
                    }
                }
            break;
        case AKNEXLIST_CHANGE_METHOD_KEY:
            if ( iInternalFlag == EFalse )
                {
                // Changes method of creating listbox.
                iKeyEvent = ETrue;
                iInternalFlag = ETrue;
                DisplayListBoxL(
                    tabGroup->TabIdFromIndex( tabGroup->ActiveTabIndex() ) );
                iKeyEvent = EFalse;
                return EKeyWasConsumed;
                }
            break;
        default:
            break;
        }

    if ( iListBox )
        {
        return iListBox->OfferKeyEventL( aKeyEvent, aType );
        }
    else
        {
        return EKeyWasNotConsumed;
        }
    }

// ----------------------------------------------------------------------------
// void CAknExListFlagTestContainer::HandleListBoxEventL( CEikListBox*,
//  TListBoxEvent )
// Handles listbox event.
// ----------------------------------------------------------------------------
void CAknExListFlagTestContainer::HandleListBoxEventL(
    CEikListBox* /*aListBox*/,
    TListBoxEvent aEventType )
    {
    if ( ( aEventType == MEikListBoxObserver::EEventEnterKeyPressed ) ||
         ( aEventType == MEikListBoxObserver::EEventItemClicked ) )
        {
        switch ( iOutlineId )
            {
            case EAknExListCmdOutline89:
            case EAknExListCmdOutline92:
            case EAknExListCmdOutline94:
            case EAknExListCmdOutline96:
            case EAknExListCmdOutline98:
                // This cood prevent to crash on assert.
                iListBox->ShortcutValueForNextList();
                break;
            default:
                break;
            }
        }
    }

// ----------------------------------------------------------------------------
// TInt CAknExListFlagTestContainer::ResourceIdSingle()
// Returns resource ID for CAknSingleStyleListBox.
// ----------------------------------------------------------------------------
//
TInt CAknExListFlagTestContainer::ResourceIdSingle()
    {
    TInt resourceId( KAknExListInitListResourceId );

    switch ( iOutlineId ) // Outline ID is...
        {
        case EAknExListCmdOutline06: // Used EAknListBoxLoopScrolling.
            resourceId = R_AKNEXLIST_LOOP_SINGLE;
            break;
        case EAknExListCmdOutline88: // Used EAknListBoxSelectionList.
            resourceId = R_AKNEXLIST_SELECTIONLIST_SINGLE;
            break;
        case EAknExListCmdOutline89:
            // Used EAknListBoxSelectionListWithShortcuts.
            resourceId = R_AKNEXLIST_SELECTIONLIST_WITHS_SINGLE;
            break;
        case EAknExListCmdOutline90: // Used EAknListBoxMenuList.
            resourceId = R_AKNEXLIST_MENULIST_SINGLE;
            break;
        case EAknExListCmdOutline91: // Used EAknListBoxMarkableList.
            resourceId = R_AKNEXLIST_MARKABLELIST_SINGLE;
            break;
        case EAknExListCmdOutline92:
            // Used EAknListBoxMarkableListWithShortcuts.
            resourceId = R_AKNEXLIST_MARKABLELIST_WITHS_SINGLE;
            break;
        case EAknExListCmdOutline93: // Used EAknListBoxMultiselectionList.
            resourceId = R_AKNEXLIST_MULTISELECTIONLIST_SINGLE;
            break;
        case EAknExListCmdOutline94:
            // Used EAknListBoxMultiselectionListWithShortcuts.
            resourceId = R_AKNEXLIST_MULTISELECTIONLIST_WITHS_SINGLE;
            break;
        case EAknExListCmdOutline95: // Used EAknListBoxSelectionGrid.
            resourceId = R_AKNEXLIST_SELECTIONGRID_SINGLE;
            break;
        case EAknExListCmdOutline96:
            // Used EAknListBoxSelectionGridWithShortcuts.
            resourceId = R_AKNEXLIST_SELECTIONGRID_WITHS_SINGLE;
            break;
        case EAknExListCmdOutline97: // Used EAknListBoxMarkableGrid.
            resourceId = R_AKNEXLIST_MARKABLEGRID_SINGLE;
            break;
        case EAknExListCmdOutline98:
            // Used EAknListBoxMarkableGridWithShortcuts.
            resourceId = R_AKNEXLIST_MARKABLEGRID_WITHS_SINGLE;
            break;
        case EAknExListCmdOutline99: // Used EAknListBoxMenuGrid.
            resourceId = R_AKNEXLIST_MENUGRID_SINGLE;
            break;
        case EAknExListCmdOutline100: // Used EAknDialogSelectionList.
            resourceId = R_AKNEXLIST_DIALOGSELECTION_SINGLE;
            break;
        case EAknExListCmdOutline101: // Used EAknDialogMenuList.
            resourceId = R_AKNEXLIST_DIALOGMENU_SINGLE;
            break;
        case EAknExListCmdOutline102: // Used EAknListBoxViewerFlags.
            resourceId = R_AKNEXLIST_VIEWER_SINGLE;
            break;
        case EAknExListCmdOutline103: // Used EAknDialogMarkableList.
            resourceId = R_AKNEXLIST_DIALOGMARKABLE_SINGLE;
            break;
        case EAknExListCmdOutline104: // Used EAknDialogMultiselectionList.
            resourceId = R_AKNEXLIST_DIALOGMULTI_SINGLE;
            break;
        default:
            break;
        }

    return resourceId;
    }

// ----------------------------------------------------------------------------
// TInt CAknExListFlagTestContainer::ResourceIdSingleNumber()
// Returns resource ID for CAknSingleNumberStyleListBox.
// ----------------------------------------------------------------------------
//
TInt CAknExListFlagTestContainer::ResourceIdSingleNumber()
    {
    TInt resourceId( KAknExListInitListResourceId );

    switch ( iOutlineId ) // Outline ID is...
        {
        case EAknExListCmdOutline06: // Used EAknListBoxLoopScrolling.
            resourceId = R_AKNEXLIST_LOOP_SINGLE_NUMBER;
            break;
        case EAknExListCmdOutline88: // Used EAknListBoxSelectionList.
            resourceId = R_AKNEXLIST_SELECTIONLIST_SINGLE_NUMBER;
            break;
        case EAknExListCmdOutline89:
            // Used EAknListBoxSelectionListWithShortcuts.
            resourceId = R_AKNEXLIST_SELECTIONLIST_WITHS_SINGLE_NUMBER;
            break;
        case EAknExListCmdOutline90: // Used EAknListBoxMenuList.
            resourceId = R_AKNEXLIST_MENULIST_SINGLE_NUMBER;
            break;
        case EAknExListCmdOutline91: // Used EAknListBoxMarkableList.
            resourceId = R_AKNEXLIST_MARKABLELIST_SINGLE_NUMBER;
            break;
        case EAknExListCmdOutline92:
            // Used EAknListBoxMarkableListWithShortcuts.
            resourceId = R_AKNEXLIST_MARKABLELIST_WITHS_SINGLE_NUMBER;
            break;
        case EAknExListCmdOutline93: // Used EAknListBoxMultiselectionList.
            resourceId = R_AKNEXLIST_MULTISELECTIONLIST_SINGLE_NUMBER;
            break;
        case EAknExListCmdOutline94:
            // Used EAknListBoxMultiselectionListWithShortcuts.
            resourceId = R_AKNEXLIST_MULTISELECTIONLIST_WITHS_SINGLE_NUMBER;
            break;
        case EAknExListCmdOutline95: // Used EAknListBoxSelectionGrid.
            resourceId = R_AKNEXLIST_SELECTIONGRID_SINGLE_NUMBER;
            break;
        case EAknExListCmdOutline96:
            // Used EAknListBoxSelectionGridWithShortcuts.
            resourceId = R_AKNEXLIST_SELECTIONGRID_WITHS_SINGLE_NUMBER;
            break;
        case EAknExListCmdOutline97: // Used EAknListBoxMarkableGrid.
            resourceId = R_AKNEXLIST_MARKABLEGRID_SINGLE_NUMBER;
            break;
        case EAknExListCmdOutline98:
            // Used EAknListBoxMarkableGridWithShortcuts.
            resourceId = R_AKNEXLIST_MARKABLEGRID_WITHS_SINGLE_NUMBER;
            break;
        case EAknExListCmdOutline99: // Used EAknListBoxMenuGrid.
            resourceId = R_AKNEXLIST_MENUGRID_SINGLE_NUMBER;
            break;
        case EAknExListCmdOutline100: // Used EAknDialogSelectionList.
            resourceId = R_AKNEXLIST_DIALOGSELECTION_SINGLE_NUMBER;
            break;
        case EAknExListCmdOutline101: // Used EAknDialogMenuList.
            resourceId = R_AKNEXLIST_DIALOGMENU_SINGLE_NUMBER;
            break;
        case EAknExListCmdOutline102: // Used EAknListBoxViewerFlags.
            resourceId = R_AKNEXLIST_VIEWER_SINGLE_NUMBER;
            break;
        case EAknExListCmdOutline103: // Used EAknDialogMarkableList.
            resourceId = R_AKNEXLIST_DIALOGMARKABLE_SINGLE_NUMBER;
            break;
        case EAknExListCmdOutline104: // Used EAknDialogMultiselectionList.
            resourceId = R_AKNEXLIST_DIALOGMULTI_SINGLE_NUMBER;
            break;
        default:
            break;
        }

    return resourceId;
    }

// ----------------------------------------------------------------------------
// TInt CAknExListFlagTestContainer::ResourceIdSingleHeading()
// Returns resource ID for CAknSingleHeadingStyleListBox.
// ----------------------------------------------------------------------------
//
TInt CAknExListFlagTestContainer::ResourceIdSingleHeading()
    {
    TInt resourceId( KAknExListInitListResourceId );

    switch ( iOutlineId ) // Outline ID is...
        {
        case EAknExListCmdOutline06: // Used EAknListBoxLoopScrolling.
            resourceId = R_AKNEXLIST_LOOP_SINGLE_HEADING;
            break;
        case EAknExListCmdOutline88: // Used EAknListBoxSelectionList.
            resourceId = R_AKNEXLIST_SELECTIONLIST_SINGLE_HEADING;
            break;
        case EAknExListCmdOutline89:
            // Used EAknListBoxSelectionListWithShortcuts.
            resourceId = R_AKNEXLIST_SELECTIONLIST_WITHS_SINGLE_HEADING;
            break;
        case EAknExListCmdOutline90: // Used EAknListBoxMenuList.
            resourceId = R_AKNEXLIST_MENULIST_SINGLE_HEADING;
            break;
        case EAknExListCmdOutline91: // Used EAknListBoxMarkableList.
            resourceId = R_AKNEXLIST_MARKABLELIST_SINGLE_HEADING;
            break;
        case EAknExListCmdOutline92:
            // Used EAknListBoxMarkableListWithShortcuts.
            resourceId = R_AKNEXLIST_MARKABLELIST_WITHS_SINGLE_HEADING;
            break;
        case EAknExListCmdOutline93: // Used EAknListBoxMultiselectionList.
            resourceId = R_AKNEXLIST_MULTISELECTIONLIST_SINGLE_HEADING;
            break;
        case EAknExListCmdOutline94:
            // Used EAknListBoxMultiselectionListWithShortcuts.
            resourceId = R_AKNEXLIST_MULTISELECTIONLIST_WITHS_SINGLE_HEADING;
            break;
        case EAknExListCmdOutline95: // Used EAknListBoxSelectionGrid.
            resourceId = R_AKNEXLIST_SELECTIONGRID_SINGLE_HEADING;
            break;
        case EAknExListCmdOutline96:
            // Used EAknListBoxSelectionGridWithShortcuts.
            resourceId = R_AKNEXLIST_SELECTIONGRID_WITHS_SINGLE_HEADING;
            break;
        case EAknExListCmdOutline97: // Used EAknListBoxMarkableGrid.
            resourceId = R_AKNEXLIST_MARKABLEGRID_SINGLE_HEADING;
            break;
        case EAknExListCmdOutline98:
            // Used EAknListBoxMarkableGridWithShortcuts.
            resourceId = R_AKNEXLIST_MARKABLEGRID_WITHS_SINGLE_HEADING;
            break;
        case EAknExListCmdOutline99: // Used EAknListBoxMenuGrid.
            resourceId = R_AKNEXLIST_MENUGRID_SINGLE_HEADING;
            break;
        case EAknExListCmdOutline100: // Used EAknDialogSelectionList.
            resourceId = R_AKNEXLIST_DIALOGSELECTION_SINGLE_HEADING;
            break;
        case EAknExListCmdOutline101: // Used EAknDialogMenuList.
            resourceId = R_AKNEXLIST_DIALOGMENU_SINGLE_HEADING;
            break;
        case EAknExListCmdOutline102: // Used EAknListBoxViewerFlags.
            resourceId = R_AKNEXLIST_VIEWER_SINGLE_HEADING;
            break;
        case EAknExListCmdOutline103: // Used EAknDialogMarkableList.
            resourceId = R_AKNEXLIST_DIALOGMARKABLE_SINGLE_HEADING;
            break;
        case EAknExListCmdOutline104: // Used EAknDialogMultiselectionList.
            resourceId = R_AKNEXLIST_DIALOGMULTI_SINGLE_HEADING;
            break;
        default:
            break;
        }

    return resourceId;
    }

// ----------------------------------------------------------------------------
// TInt CAknExListFlagTestContainer::ResourceIdSingleGraphic()
// Returns resource ID for CAknSingleGraphicStyleListBox.
// ----------------------------------------------------------------------------
//
TInt CAknExListFlagTestContainer::ResourceIdSingleGraphic()
    {
    TInt resourceId( KAknExListInitListResourceId );

    switch ( iOutlineId ) // Outline ID is...
        {
        case EAknExListCmdOutline06: // Used EAknListBoxLoopScrolling.
            resourceId = R_AKNEXLIST_LOOP_SINGLE_GRAPHIC;
            break;
        case EAknExListCmdOutline88: // Used EAknListBoxSelectionList.
            resourceId = R_AKNEXLIST_SELECTIONLIST_SINGLE_GRAPHIC;
            break;
        case EAknExListCmdOutline89:
            // Used EAknListBoxSelectionListWithShortcuts.
            resourceId = R_AKNEXLIST_SELECTIONLIST_WITHS_SINGLE_GRAPHIC;
            break;
        case EAknExListCmdOutline90: // Used EAknListBoxMenuList.
            resourceId = R_AKNEXLIST_MENULIST_SINGLE_GRAPHIC;
            break;
        case EAknExListCmdOutline91: // Used EAknListBoxMarkableList.
            resourceId = R_AKNEXLIST_MARKABLELIST_SINGLE_GRAPHIC;
            break;
        case EAknExListCmdOutline92:
            // Used EAknListBoxMarkableListWithShortcuts.
            resourceId = R_AKNEXLIST_MARKABLELIST_WITHS_SINGLE_GRAPHIC;
            break;
        case EAknExListCmdOutline93: // Used EAknListBoxMultiselectionList.
            resourceId = R_AKNEXLIST_MULTISELECTIONLIST_SINGLE_GRAPHIC;
            break;
        case EAknExListCmdOutline94:
            // Used EAknListBoxMultiselectionListWithShortcuts.
            resourceId = R_AKNEXLIST_MULTISELECTIONLIST_WITHS_SINGLE_GRAPHIC;
            break;
        case EAknExListCmdOutline95: // Used EAknListBoxSelectionGrid.
            resourceId = R_AKNEXLIST_SELECTIONGRID_SINGLE_GRAPHIC;
            break;
        case EAknExListCmdOutline96:
            // Used EAknListBoxSelectionGridWithShortcuts.
            resourceId = R_AKNEXLIST_SELECTIONGRID_WITHS_SINGLE_GRAPHIC;
            break;
        case EAknExListCmdOutline97: // Used EAknListBoxMarkableGrid.
            resourceId = R_AKNEXLIST_MARKABLEGRID_SINGLE_GRAPHIC;
            break;
        case EAknExListCmdOutline98:
            // Used EAknListBoxMarkableGridWithShortcuts.
            resourceId = R_AKNEXLIST_MARKABLEGRID_WITHS_SINGLE_GRAPHIC;
            break;
        case EAknExListCmdOutline99: // Used EAknListBoxMenuGrid.
            resourceId = R_AKNEXLIST_MENUGRID_SINGLE_GRAPHIC;
            break;
        case EAknExListCmdOutline100: // Used EAknDialogSelectionList.
            resourceId = R_AKNEXLIST_DIALOGSELECTION_SINGLE_GRAPHIC;
            break;
        case EAknExListCmdOutline101: // Used EAknDialogMenuList.
            resourceId = R_AKNEXLIST_DIALOGMENU_SINGLE_GRAPHIC;
            break;
        case EAknExListCmdOutline102: // Used EAknListBoxViewerFlags.
            resourceId = R_AKNEXLIST_VIEWER_SINGLE_GRAPHIC;
            break;
        case EAknExListCmdOutline103: // Used EAknDialogMarkableList.
            resourceId = R_AKNEXLIST_DIALOGMARKABLE_SINGLE_GRAPHIC;
            break;
        case EAknExListCmdOutline104: // Used EAknDialogMultiselectionList.
            resourceId = R_AKNEXLIST_DIALOGMULTI_SINGLE_GRAPHIC;
            break;
        default:
            break;
        }

    return resourceId;
    }

// ----------------------------------------------------------------------------
// TInt CAknExListFlagTestContainer::ResourceIdSingleGraphicHeading()
// Returns resource ID for CAknSingleGraphicHeadingStyleListBox.
// ----------------------------------------------------------------------------
//
TInt CAknExListFlagTestContainer::ResourceIdSingleGraphicHeading()
    {
    TInt resourceId( KAknExListInitListResourceId );

    switch ( iOutlineId ) // Outline ID is...
        {
        case EAknExListCmdOutline06: // Used EAknListBoxLoopScrolling.
            resourceId = R_AKNEXLIST_LOOP_SINGLE_GRAPHIC_HEADING;
            break;
        case EAknExListCmdOutline88: // Used EAknListBoxSelectionList.
            resourceId = R_AKNEXLIST_SELECTIONLIST_SINGLE_GRAPHIC_HEADING;
            break;
        case EAknExListCmdOutline89:
            // Used EAknListBoxSelectionListWithShortcuts.
            resourceId =
                R_AKNEXLIST_SELECTIONLIST_WITHS_SINGLE_GRAPHIC_HEADING;
            break;
        case EAknExListCmdOutline90: // Used EAknListBoxMenuList.
            resourceId = R_AKNEXLIST_MENULIST_SINGLE_GRAPHIC_HEADING;
            break;
        case EAknExListCmdOutline91: // Used EAknListBoxMarkableList.
            resourceId = R_AKNEXLIST_MARKABLELIST_SINGLE_GRAPHIC_HEADING;
            break;
        case EAknExListCmdOutline92:
            // Used EAknListBoxMarkableListWithShortcuts.
            resourceId = R_AKNEXLIST_MARKABLELIST_WITHS_SINGLE_GRAPHIC_HEADING;
            break;
        case EAknExListCmdOutline93: // Used EAknListBoxMultiselectionList.
            resourceId = R_AKNEXLIST_MULTISELECTIONLIST_SINGLE_GRAPHIC_HEADING;
            break;
        case EAknExListCmdOutline94:
            // Used EAknListBoxMultiselectionListWithShortcuts.
            resourceId =
                R_AKNEXLIST_MULTISELECTIONLIST_WITHS_SINGLE_GRAPHIC_HEADING;
            break;
        case EAknExListCmdOutline95: // Used EAknListBoxSelectionGrid.
            resourceId = R_AKNEXLIST_SELECTIONGRID_SINGLE_GRAPHIC_HEADING;
            break;
        case EAknExListCmdOutline96:
            // Used EAknListBoxSelectionGridWithShortcuts.
            resourceId =
                R_AKNEXLIST_SELECTIONGRID_WITHS_SINGLE_GRAPHIC_HEADING;
            break;
        case EAknExListCmdOutline97: // Used EAknListBoxMarkableGrid.
            resourceId = R_AKNEXLIST_MARKABLEGRID_SINGLE_GRAPHIC_HEADING;
            break;
        case EAknExListCmdOutline98:
            // Used EAknListBoxMarkableGridWithShortcuts.
            resourceId = R_AKNEXLIST_MARKABLEGRID_WITHS_SINGLE_GRAPHIC_HEADING;
            break;
        case EAknExListCmdOutline99: // Used EAknListBoxMenuGrid.
            resourceId = R_AKNEXLIST_MENUGRID_SINGLE_GRAPHIC_HEADING;
            break;
        case EAknExListCmdOutline100: // Used EAknDialogSelectionList.
            resourceId = R_AKNEXLIST_DIALOGSELECTION_SINGLE_GRAPHIC_HEADING;
            break;
        case EAknExListCmdOutline101: // Used EAknDialogMenuList.
            resourceId = R_AKNEXLIST_DIALOGMENU_SINGLE_GRAPHIC_HEADING;
            break;
        case EAknExListCmdOutline102: // Used EAknListBoxViewerFlags.
            resourceId = R_AKNEXLIST_VIEWER_SINGLE_GRAPHIC_HEADING;
            break;
        case EAknExListCmdOutline103: // Used EAknDialogMarkableList.
            resourceId = R_AKNEXLIST_DIALOGMARKABLE_SINGLE_GRAPHIC_HEADING;
            break;
        case EAknExListCmdOutline104: // Used EAknDialogMultiselectionList.
            resourceId = R_AKNEXLIST_DIALOGMULTI_SINGLE_GRAPHIC_HEADING;
            break;
        default:
            break;
        }

    return resourceId;
    }

// ----------------------------------------------------------------------------
// TInt CAknExListFlagTestContainer::ResourceIdSingleNumberHeading()
// Returns resource ID for CAknSingleNumberHeadingStyleListBox.
// ----------------------------------------------------------------------------
//
TInt CAknExListFlagTestContainer::ResourceIdSingleNumberHeading()
    {
    TInt resourceId( KAknExListInitListResourceId );

    switch ( iOutlineId ) // Outline ID is...
        {
        case EAknExListCmdOutline06: // Used EAknListBoxLoopScrolling.
            resourceId = R_AKNEXLIST_LOOP_SINGLE_NUMBER_HEADING;
            break;
        case EAknExListCmdOutline88: // Used EAknListBoxSelectionList.
            resourceId = R_AKNEXLIST_SELECTIONLIST_SINGLE_NUMBER_HEADING;
            break;
        case EAknExListCmdOutline89:
            // Used EAknListBoxSelectionListWithShortcuts.
            resourceId = R_AKNEXLIST_SELECTIONLIST_WITHS_SINGLE_NUMBER_HEADING;
            break;
        case EAknExListCmdOutline90: // Used EAknListBoxMenuList.
            resourceId = R_AKNEXLIST_MENULIST_SINGLE_NUMBER_HEADING;
            break;
        case EAknExListCmdOutline91: // Used EAknListBoxMarkableList.
            resourceId = R_AKNEXLIST_MARKABLELIST_SINGLE_NUMBER_HEADING;
            break;
        case EAknExListCmdOutline92:
            // Used EAknListBoxMarkableListWithShortcuts.
            resourceId = R_AKNEXLIST_MARKABLELIST_WITHS_SINGLE_NUMBER_HEADING;
            break;
        case EAknExListCmdOutline93: // Used EAknListBoxMultiselectionList.
            resourceId = R_AKNEXLIST_MULTISELECTIONLIST_SINGLE_NUMBER_HEADING;
            break;
        case EAknExListCmdOutline94:
            // Used EAknListBoxMultiselectionListWithShortcuts.
            resourceId =
                R_AKNEXLIST_MULTISELECTIONLIST_WITHS_SINGLE_NUMBER_HEADING;
            break;
        case EAknExListCmdOutline95: // Used EAknListBoxSelectionGrid.
            resourceId = R_AKNEXLIST_SELECTIONGRID_SINGLE_NUMBER_HEADING;
            break;
        case EAknExListCmdOutline96:
            // Used EAknListBoxSelectionGridWithShortcuts.
            resourceId = R_AKNEXLIST_SELECTIONGRID_WITHS_SINGLE_NUMBER_HEADING;
            break;
        case EAknExListCmdOutline97: // Used EAknListBoxMarkableGrid.
            resourceId = R_AKNEXLIST_MARKABLEGRID_SINGLE_NUMBER_HEADING;
            break;
        case EAknExListCmdOutline98:
            // Used EAknListBoxMarkableGridWithShortcuts.
            resourceId = R_AKNEXLIST_MARKABLEGRID_WITHS_SINGLE_NUMBER_HEADING;
            break;
        case EAknExListCmdOutline99: // Used EAknListBoxMenuGrid.
            resourceId = R_AKNEXLIST_MENUGRID_SINGLE_NUMBER_HEADING;
            break;
        case EAknExListCmdOutline100: // Used EAknDialogSelectionList.
            resourceId = R_AKNEXLIST_DIALOGSELECTION_SINGLE_NUMBER_HEADING;
            break;
        case EAknExListCmdOutline101: // Used EAknDialogMenuList.
            resourceId = R_AKNEXLIST_DIALOGMENU_SINGLE_NUMBER_HEADING;
            break;
        case EAknExListCmdOutline102: // Used EAknListBoxViewerFlags.
            resourceId = R_AKNEXLIST_VIEWER_SINGLE_NUMBER_HEADING;
            break;
        case EAknExListCmdOutline103: // Used EAknDialogMarkableList.
            resourceId = R_AKNEXLIST_DIALOGMARKABLE_SINGLE_NUMBER_HEADING;
            break;
        case EAknExListCmdOutline104: // Used EAknDialogMultiselectionList.
            resourceId = R_AKNEXLIST_DIALOGMULTI_SINGLE_NUMBER_HEADING;
            break;
        default:
            break;
        }

    return resourceId;
    }

// ----------------------------------------------------------------------------
// TInt CAknExListFlagTestContainer::ResourceIdSingleLargeGraphic()
// Returns resource ID for CAknSingleLargeStyleListBox.
// ----------------------------------------------------------------------------
//
TInt CAknExListFlagTestContainer::ResourceIdSingleLargeGraphic()
    {
    TInt resourceId( KAknExListInitListResourceId );

    switch ( iOutlineId ) // Outline ID is...
        {
        case EAknExListCmdOutline06: // Used EAknListBoxLoopScrolling.
            resourceId = R_AKNEXLIST_LOOP_SINGLE_LARGE_GRAPHIC;
            break;
        case EAknExListCmdOutline88: // Used EAknListBoxSelectionList.
            resourceId = R_AKNEXLIST_SELECTIONLIST_SINGLE_LARGE_GRAPHIC;
            break;
        case EAknExListCmdOutline89:
            // Used EAknListBoxSelectionListWithShortcuts.
            resourceId = R_AKNEXLIST_SELECTIONLIST_WITHS_SINGLE_LARGE_GRAPHIC;
            break;
        case EAknExListCmdOutline90: // Used EAknListBoxMenuList.
            resourceId = R_AKNEXLIST_MENULIST_SINGLE_LARGE_GRAPHIC;
            break;
        case EAknExListCmdOutline91: // Used EAknListBoxMarkableList.
            resourceId = R_AKNEXLIST_MARKABLELIST_SINGLE_LARGE_GRAPHIC;
            break;
        case EAknExListCmdOutline92:
            // Used EAknListBoxMarkableListWithShortcuts.
            resourceId = R_AKNEXLIST_MARKABLELIST_WITHS_SINGLE_LARGE_GRAPHIC;
            break;
        case EAknExListCmdOutline93: // Used EAknListBoxMultiselectionList.
            resourceId = R_AKNEXLIST_MULTISELECTIONLIST_SINGLE_LARGE_GRAPHIC;
            break;
        case EAknExListCmdOutline94:
            // Used EAknListBoxMultiselectionListWithShortcuts.
            resourceId =
                R_AKNEXLIST_MULTISELECTIONLIST_WITHS_SINGLE_LARGE_GRAPHIC;
            break;
        case EAknExListCmdOutline95: // Used EAknListBoxSelectionGrid.
            resourceId = R_AKNEXLIST_SELECTIONGRID_SINGLE_LARGE_GRAPHIC;
            break;
        case EAknExListCmdOutline96:
            // Used EAknListBoxSelectionGridWithShortcuts.
            resourceId = R_AKNEXLIST_SELECTIONGRID_WITHS_SINGLE_LARGE_GRAPHIC;
            break;
        case EAknExListCmdOutline97: // Used EAknListBoxMarkableGrid.
            resourceId = R_AKNEXLIST_MARKABLEGRID_SINGLE_LARGE_GRAPHIC;
            break;
        case EAknExListCmdOutline98:
            // Used EAknListBoxMarkableGridWithShortcuts.
            resourceId = R_AKNEXLIST_MARKABLEGRID_WITHS_SINGLE_LARGE_GRAPHIC;
            break;
        case EAknExListCmdOutline99: // Used EAknListBoxMenuGrid.
            resourceId = R_AKNEXLIST_MENUGRID_SINGLE_LARGE_GRAPHIC;
            break;
        case EAknExListCmdOutline100: // Used EAknDialogSelectionList.
            resourceId = R_AKNEXLIST_DIALOGSELECTION_SINGLE_LARGE_GRAPHIC;
            break;
        case EAknExListCmdOutline101: // Used EAknDialogMenuList.
            resourceId = R_AKNEXLIST_DIALOGMENU_SINGLE_LARGE_GRAPHIC;
            break;
        case EAknExListCmdOutline102: // Used EAknListBoxViewerFlags.
            resourceId = R_AKNEXLIST_VIEWER_SINGLE_LARGE_GRAPHIC;
            break;
        case EAknExListCmdOutline103: // Used EAknDialogMarkableList.
            resourceId = R_AKNEXLIST_DIALOGMARKABLE_SINGLE_LARGE_GRAPHIC;
            break;
        case EAknExListCmdOutline104: // Used EAknDialogMultiselectionList.
            resourceId = R_AKNEXLIST_DIALOGMULTI_SINGLE_LARGE_GRAPHIC;
            break;
        default:
            break;
        }

    return resourceId;
    }

// ----------------------------------------------------------------------------
// TInt CAknExListFlagTestContainer::ResourceIdBigSingle()
// Returns resource ID for CAknDoubleStyleListBox as single big pane.
// ----------------------------------------------------------------------------
//
TInt CAknExListFlagTestContainer::ResourceIdBigSingle()
    {
    TInt resourceId( KAknExListInitListResourceId );

    switch ( iOutlineId ) // Outline ID is...
        {
        case EAknExListCmdOutline06: // Used EAknListBoxLoopScrolling.
            resourceId = R_AKNEXLIST_LOOP_BIG_SINGLE;
            break;
        case EAknExListCmdOutline88: // Used EAknListBoxSelectionList.
            resourceId = R_AKNEXLIST_SELECTIONLIST_BIG_SINGLE;
            break;
        case EAknExListCmdOutline89:
            // Used EAknListBoxSelectionListWithShortcuts.
            resourceId = R_AKNEXLIST_SELECTIONLIST_WITHS_BIG_SINGLE;
            break;
        case EAknExListCmdOutline90: // Used EAknListBoxMenuList.
            resourceId = R_AKNEXLIST_MENULIST_BIG_SINGLE;
            break;
        case EAknExListCmdOutline91: // Used EAknListBoxMarkableList.
            resourceId = R_AKNEXLIST_MARKABLELIST_BIG_SINGLE;
            break;
        case EAknExListCmdOutline92:
            // Used EAknListBoxMarkableListWithShortcuts.
            resourceId = R_AKNEXLIST_MARKABLELIST_WITHS_BIG_SINGLE;
            break;
        case EAknExListCmdOutline93: // Used EAknListBoxMultiselectionList.
            resourceId = R_AKNEXLIST_MULTISELECTIONLIST_BIG_SINGLE;
            break;
        case EAknExListCmdOutline94:
            // Used EAknListBoxMultiselectionListWithShortcuts.
            resourceId = R_AKNEXLIST_MULTISELECTIONLIST_WITHS_BIG_SINGLE;
            break;
        case EAknExListCmdOutline95: // Used EAknListBoxSelectionGrid.
            resourceId = R_AKNEXLIST_SELECTIONGRID_BIG_SINGLE;
            break;
        case EAknExListCmdOutline96:
            // Used EAknListBoxSelectionGridWithShortcuts.
            resourceId = R_AKNEXLIST_SELECTIONGRID_WITHS_BIG_SINGLE;
            break;
        case EAknExListCmdOutline97: // Used EAknListBoxMarkableGrid.
            resourceId = R_AKNEXLIST_MARKABLEGRID_BIG_SINGLE;
            break;
        case EAknExListCmdOutline98:
            // Used EAknListBoxMarkableGridWithShortcuts.
            resourceId = R_AKNEXLIST_MARKABLEGRID_WITHS_BIG_SINGLE;
            break;
        case EAknExListCmdOutline99: // Used EAknListBoxMenuGrid.
            resourceId = R_AKNEXLIST_MENUGRID_BIG_SINGLE;
            break;
        case EAknExListCmdOutline100: // Used EAknDialogSelectionList.
            resourceId = R_AKNEXLIST_DIALOGSELECTION_BIG_SINGLE;
            break;
        case EAknExListCmdOutline101: // Used EAknDialogMenuList.
            resourceId = R_AKNEXLIST_DIALOGMENU_BIG_SINGLE;
            break;
        case EAknExListCmdOutline102: // Used EAknListBoxViewerFlags.
            resourceId = R_AKNEXLIST_VIEWER_BIG_SINGLE;
            break;
        case EAknExListCmdOutline103: // Used EAknDialogMarkableList.
            resourceId = R_AKNEXLIST_DIALOGMARKABLE_BIG_SINGLE;
            break;
        case EAknExListCmdOutline104: // Used EAknDialogMultiselectionList.
            resourceId = R_AKNEXLIST_DIALOGMULTI_BIG_SINGLE;
            break;
        default:
            break;
        }

    return resourceId;
    }

// ----------------------------------------------------------------------------
// TInt CAknExListFlagTestContainer::ResourceIdBigSingleNumber()
// Returns resource ID for CAknDoubleNumberStyleListBox as single big number
// pane.
// ----------------------------------------------------------------------------
//
TInt CAknExListFlagTestContainer::ResourceIdBigSingleNumber()
    {
    TInt resourceId( KAknExListInitListResourceId );

    switch ( iOutlineId ) // Outline ID is...
        {
        case EAknExListCmdOutline06: // Used EAknListBoxLoopScrolling.
            resourceId = R_AKNEXLIST_LOOP_BIG_SINGLE_NUMBER;
            break;
        case EAknExListCmdOutline88: // Used EAknListBoxSelectionList.
            resourceId = R_AKNEXLIST_SELECTIONLIST_BIG_SINGLE_NUMBER;
            break;
        case EAknExListCmdOutline89:
            // Used EAknListBoxSelectionListWithShortcuts.
            resourceId = R_AKNEXLIST_SELECTIONLIST_WITHS_BIG_SINGLE_NUMBER;
            break;
        case EAknExListCmdOutline90: // Used EAknListBoxMenuList.
            resourceId = R_AKNEXLIST_MENULIST_BIG_SINGLE_NUMBER;
            break;
        case EAknExListCmdOutline91: // Used EAknListBoxMarkableList.
            resourceId = R_AKNEXLIST_MARKABLELIST_BIG_SINGLE_NUMBER;
            break;
        case EAknExListCmdOutline92:
            // Used EAknListBoxMarkableListWithShortcuts.
            resourceId = R_AKNEXLIST_MARKABLELIST_WITHS_BIG_SINGLE_NUMBER;
            break;
        case EAknExListCmdOutline93: // Used EAknListBoxMultiselectionList.
            resourceId = R_AKNEXLIST_MULTISELECTIONLIST_BIG_SINGLE;
            break;
        case EAknExListCmdOutline94:
            // Used EAknListBoxMultiselectionListWithShortcuts.
            resourceId = R_AKNEXLIST_MULTISELECTIONLIST_WITHS_BIG_SINGLE;
            break;
        case EAknExListCmdOutline95: // Used EAknListBoxSelectionGrid.
            resourceId = R_AKNEXLIST_SELECTIONGRID_BIG_SINGLE;
            break;
        case EAknExListCmdOutline96:
            // Used EAknListBoxSelectionGridWithShortcuts.
            resourceId = R_AKNEXLIST_SELECTIONGRID_WITHS_BIG_SINGLE;
            break;
        case EAknExListCmdOutline97: // Used EAknListBoxMarkableGrid.
            resourceId = R_AKNEXLIST_MARKABLEGRID_BIG_SINGLE;
            break;
        case EAknExListCmdOutline98:
            // Used EAknListBoxMarkableGridWithShortcuts.
            resourceId = R_AKNEXLIST_MARKABLEGRID_WITHS_BIG_SINGLE;
            break;
        case EAknExListCmdOutline99: // Used EAknListBoxMenuGrid.
            resourceId = R_AKNEXLIST_MENUGRID_BIG_SINGLE;
            break;
        case EAknExListCmdOutline100: // Used EAknDialogSelectionList.
            resourceId = R_AKNEXLIST_DIALOGSELECTION_BIG_SINGLE;
            break;
        case EAknExListCmdOutline101: // Used EAknDialogMenuList.
            resourceId = R_AKNEXLIST_DIALOGMENU_BIG_SINGLE;
            break;
        case EAknExListCmdOutline102: // Used EAknListBoxViewerFlags.
            resourceId = R_AKNEXLIST_VIEWER_BIG_SINGLE;
            break;
        case EAknExListCmdOutline103: // Used EAknDialogMarkableList.
            resourceId = R_AKNEXLIST_DIALOGMARKABLE_BIG_SINGLE;
            break;
        case EAknExListCmdOutline104: // Used EAknDialogMultiselectionList.
            resourceId = R_AKNEXLIST_DIALOGMULTI_BIG_SINGLE;
        default:
            break;
        }

    return resourceId;
    }

// ----------------------------------------------------------------------------
// TInt CAknExListFlagTestContainer::ResourceIdBigSingleLargeGraphic()
// Returns resource ID for CAknDoubleLargeStyleListBox as single big large
// graphic pane.
// ----------------------------------------------------------------------------
//
TInt CAknExListFlagTestContainer::ResourceIdBigSingleLargeGraphic()
    {
    TInt resourceId( KAknExListInitListResourceId );

    switch ( iOutlineId ) // Outline ID is...
        {
        case EAknExListCmdOutline06: // Used EAknListBoxLoopScrolling.
            resourceId = R_AKNEXLIST_LOOP_BIG_SINGLE_GRAPHIC;
            break;
        case EAknExListCmdOutline88: // Used EAknListBoxSelectionList.
            resourceId = R_AKNEXLIST_SELECTIONLIST_BIG_SINGLE_GRAPHIC;
            break;
        case EAknExListCmdOutline89:
            // Used EAknListBoxSelectionListWithShortcuts.
            resourceId = R_AKNEXLIST_SELECTIONLIST_WITHS_BIG_SINGLE_GRAPHIC;
            break;
        case EAknExListCmdOutline90: // Used EAknListBoxMenuList.
            resourceId = R_AKNEXLIST_MENULIST_BIG_SINGLE_GRAPHIC;
            break;
        case EAknExListCmdOutline91: // Used EAknListBoxMarkableList.
            resourceId = R_AKNEXLIST_MARKABLELIST_BIG_SINGLE_GRAPHIC;
            break;
        case EAknExListCmdOutline92:
            // Used EAknListBoxMarkableListWithShortcuts.
            resourceId = R_AKNEXLIST_MARKABLELIST_WITHS_BIG_SINGLE_GRAPHIC;
            break;
        case EAknExListCmdOutline93: // Used EAknListBoxMultiselectionList.
            resourceId = R_AKNEXLIST_MULTISELECTIONLIST_BIG_SINGLE_GRAPHIC;
            break;
        case EAknExListCmdOutline94:
            // Used EAknListBoxMultiselectionListWithShortcuts.
            resourceId =
                R_AKNEXLIST_MULTISELECTIONLIST_WITHS_BIG_SINGLE_GRAPHIC;
            break;
        case EAknExListCmdOutline95: // Used EAknListBoxSelectionGrid.
            resourceId = R_AKNEXLIST_SELECTIONGRID_BIG_SINGLE_GRAPHIC;
            break;
        case EAknExListCmdOutline96:
            // Used EAknListBoxSelectionGridWithShortcuts.
            resourceId = R_AKNEXLIST_SELECTIONGRID_WITHS_BIG_SINGLE_GRAPHIC;
            break;
        case EAknExListCmdOutline97: // Used EAknListBoxMarkableGrid.
            resourceId = R_AKNEXLIST_MARKABLEGRID_BIG_SINGLE_GRAPHIC;
            break;
        case EAknExListCmdOutline98:
            // Used EAknListBoxMarkableGridWithShortcuts.
            resourceId = R_AKNEXLIST_MARKABLEGRID_WITHS_BIG_SINGLE_GRAPHIC;
            break;
        case EAknExListCmdOutline99: // Used EAknListBoxMenuGrid.
            resourceId = R_AKNEXLIST_MENUGRID_BIG_SINGLE_GRAPHIC;
            break;
        case EAknExListCmdOutline100: // Used EAknDialogSelectionList.
            resourceId = R_AKNEXLIST_DIALOGSELECTION_BIG_SINGLE_GRAPHIC;
            break;
        case EAknExListCmdOutline101: // Used EAknDialogMenuList.
            resourceId = R_AKNEXLIST_DIALOGMENU_BIG_SINGLE_GRAPHIC;
            break;
        case EAknExListCmdOutline102: // Used EAknListBoxViewerFlags.
            resourceId = R_AKNEXLIST_VIEWER_BIG_SINGLE_GRAPHIC;
            break;
        case EAknExListCmdOutline103: // Used EAknDialogMarkableList.
            resourceId = R_AKNEXLIST_DIALOGMARKABLE_BIG_SINGLE_GRAPHIC;
            break;
        case EAknExListCmdOutline104: // Used EAknDialogMultiselectionList.
            resourceId = R_AKNEXLIST_DIALOGMULTI_BIG_SINGLE_GRAPHIC;
            break;
        default:
            break;
        }

    return resourceId;
    }

// ----------------------------------------------------------------------------
// TInt CAknExListFlagTestContainer::ResourceIdDouble()
// Returns resource ID for CAknDoubleStyleListBox.
// ----------------------------------------------------------------------------
//
TInt CAknExListFlagTestContainer::ResourceIdDouble()
    {
    TInt resourceId( KAknExListInitListResourceId );

    switch ( iOutlineId ) // Outline ID is...
        {
        case EAknExListCmdOutline06: // Used EAknListBoxLoopScrolling.
            resourceId = R_AKNEXLIST_LOOP_DOUBLE;
            break;
        case EAknExListCmdOutline88: // Used EAknListBoxSelectionList.
            resourceId = R_AKNEXLIST_SELECTIONLIST_DOUBLE;
            break;
        case EAknExListCmdOutline89:
            // Used EAknListBoxSelectionListWithShortcuts.
            resourceId = R_AKNEXLIST_SELECTIONLIST_WITHS_DOUBLE;
            break;
        case EAknExListCmdOutline90: // Used EAknListBoxMenuList.
            resourceId = R_AKNEXLIST_MENULIST_DOUBLE;
            break;
        case EAknExListCmdOutline91: // Used EAknListBoxMarkableList.
            resourceId = R_AKNEXLIST_MARKABLELIST_DOUBLE;
            break;
        case EAknExListCmdOutline92:
            // Used EAknListBoxMarkableListWithShortcuts.
            resourceId = R_AKNEXLIST_MARKABLELIST_WITHS_DOUBLE;
            break;
        case EAknExListCmdOutline93: // Used EAknListBoxMultiselectionList.
            resourceId = R_AKNEXLIST_MULTISELECTIONLIST_DOUBLE;
            break;
        case EAknExListCmdOutline94:
            // Used EAknListBoxMultiselectionListWithShortcuts.
            resourceId = R_AKNEXLIST_MULTISELECTIONLIST_WITHS_DOUBLE;
            break;
        case EAknExListCmdOutline95: // Used EAknListBoxSelectionGrid.
            resourceId = R_AKNEXLIST_SELECTIONGRID_DOUBLE;
            break;
        case EAknExListCmdOutline96:
            // Used EAknListBoxSelectionGridWithShortcuts.
            resourceId = R_AKNEXLIST_SELECTIONGRID_WITHS_DOUBLE;
            break;
        case EAknExListCmdOutline97: // Used EAknListBoxMarkableGrid.
            resourceId = R_AKNEXLIST_MARKABLEGRID_DOUBLE;
            break;
        case EAknExListCmdOutline98:
            // Used EAknListBoxMarkableGridWithShortcuts.
            resourceId = R_AKNEXLIST_MARKABLEGRID_WITHS_DOUBLE;
            break;
        case EAknExListCmdOutline99: // Used EAknListBoxMenuGrid.
            resourceId = R_AKNEXLIST_MENUGRID_DOUBLE;
            break;
        case EAknExListCmdOutline100: // Used EAknDialogSelectionList.
            resourceId = R_AKNEXLIST_DIALOGSELECTION_DOUBLE;
            break;
        case EAknExListCmdOutline101: // Used EAknDialogMenuList.
            resourceId = R_AKNEXLIST_DIALOGMENU_DOUBLE;
            break;
        case EAknExListCmdOutline102: // Used EAknListBoxViewerFlags.
            resourceId = R_AKNEXLIST_VIEWER_DOUBLE;
            break;
        case EAknExListCmdOutline103: // Used EAknDialogMarkableList.
            resourceId = R_AKNEXLIST_DIALOGMARKABLE_DOUBLE;
            break;
        case EAknExListCmdOutline104: // Used EAknDialogMultiselectionList.
            resourceId = R_AKNEXLIST_DIALOGMULTI_DOUBLE;
            break;
        default:
            break;
        }

    return resourceId;
    }

// ----------------------------------------------------------------------------
// TInt CAknExListFlagTestContainer::ResourceIdDoubleNumber()
// Returns resource ID for CAknDoubleNumberStyleListBox.
// ----------------------------------------------------------------------------
//
TInt CAknExListFlagTestContainer::ResourceIdDoubleNumber()
    {
    TInt resourceId( KAknExListInitListResourceId );

    switch ( iOutlineId ) // Outline ID is...
        {
        case EAknExListCmdOutline06: // Used EAknListBoxLoopScrolling.
            resourceId = R_AKNEXLIST_LOOP_DOUBLE_NUMBER;
            break;
        case EAknExListCmdOutline88: // Used EAknListBoxSelectionList.
            resourceId = R_AKNEXLIST_SELECTIONLIST_DOUBLE_NUMBER;
            break;
        case EAknExListCmdOutline89:
            // Used EAknListBoxSelectionListWithShortcuts.
            resourceId = R_AKNEXLIST_SELECTIONLIST_WITHS_DOUBLE_NUMBER;
            break;
        case EAknExListCmdOutline90: // Used EAknListBoxMenuList.
            resourceId = R_AKNEXLIST_MENULIST_DOUBLE_NUMBER;
            break;
        case EAknExListCmdOutline91: // Used EAknListBoxMarkableList.
            resourceId = R_AKNEXLIST_MARKABLELIST_DOUBLE_NUMBER;
            break;
        case EAknExListCmdOutline92:
            // Used EAknListBoxMarkableListWithShortcuts.
            resourceId = R_AKNEXLIST_MARKABLELIST_WITHS_DOUBLE_NUMBER;
            break;
        case EAknExListCmdOutline93: // Used EAknListBoxMultiselectionList.
            resourceId = R_AKNEXLIST_MULTISELECTIONLIST_DOUBLE_NUMBER;
            break;
        case EAknExListCmdOutline94:
            // Used EAknListBoxMultiselectionListWithShortcuts.
            resourceId = R_AKNEXLIST_MULTISELECTIONLIST_WITHS_DOUBLE_NUMBER;
            break;
        case EAknExListCmdOutline95: // Used EAknListBoxSelectionGrid.
            resourceId = R_AKNEXLIST_SELECTIONGRID_DOUBLE_NUMBER;
            break;
        case EAknExListCmdOutline96:
            // Used EAknListBoxSelectionGridWithShortcuts.
            resourceId = R_AKNEXLIST_SELECTIONGRID_WITHS_DOUBLE_NUMBER;
            break;
        case EAknExListCmdOutline97: // Used EAknListBoxMarkableGrid.
            resourceId = R_AKNEXLIST_MARKABLEGRID_DOUBLE_NUMBER;
            break;
        case EAknExListCmdOutline98:
            // Used EAknListBoxMarkableGridWithShortcuts.
            resourceId = R_AKNEXLIST_MARKABLEGRID_WITHS_DOUBLE_NUMBER;
            break;
        case EAknExListCmdOutline99: // Used EAknListBoxMenuGrid.
            resourceId = R_AKNEXLIST_MENUGRID_DOUBLE_NUMBER;
            break;
        case EAknExListCmdOutline100: // Used EAknDialogSelectionList.
            resourceId = R_AKNEXLIST_DIALOGSELECTION_DOUBLE_NUMBER;
            break;
        case EAknExListCmdOutline101: // Used EAknDialogMenuList.
            resourceId = R_AKNEXLIST_DIALOGMENU_DOUBLE_NUMBER;
            break;
        case EAknExListCmdOutline102: // Used EAknListBoxViewerFlags.
            resourceId = R_AKNEXLIST_VIEWER_DOUBLE_NUMBER;
            break;
        case EAknExListCmdOutline103: // Used EAknDialogMarkableList.
            resourceId = R_AKNEXLIST_DIALOGMARKABLE_DOUBLE_NUMBER;
            break;
        case EAknExListCmdOutline104: // Used EAknDialogMultiselectionList.
            resourceId = R_AKNEXLIST_DIALOGMULTI_DOUBLE_NUMBER;
            break;
        default:
            break;
        }

    return resourceId;
    }

// ----------------------------------------------------------------------------
// TInt CAknExListFlagTestContainer::ResourceIdDoubleLargeGraphic()
// Returns resource ID for CAknDoubleLargeStyleListBox.
// ----------------------------------------------------------------------------
//
TInt CAknExListFlagTestContainer::ResourceIdDoubleLargeGraphic()
    {
    TInt resourceId( KAknExListInitListResourceId );

    switch ( iOutlineId ) // Outline ID is...
        {
        case EAknExListCmdOutline06: // Used EAknListBoxLoopScrolling.
            resourceId = R_AKNEXLIST_LOOP_DOUBLE_LARGE_GRAPHIC;
            break;
        case EAknExListCmdOutline88: // Used EAknListBoxSelectionList.
            resourceId = R_AKNEXLIST_SELECTIONLIST_DOUBLE_LARGE_GRAPHIC;
            break;
        case EAknExListCmdOutline89:
            // Used EAknListBoxSelectionListWithShortcuts.
            resourceId = R_AKNEXLIST_SELECTIONLIST_WITHS_DOUBLE_LARGE_GRAPHIC;
            break;
        case EAknExListCmdOutline90: // Used EAknListBoxMenuList.
            resourceId = R_AKNEXLIST_MENULIST_DOUBLE_LARGE_GRAPHIC;
            break;
        case EAknExListCmdOutline91: // Used EAknListBoxMarkableList.
            resourceId = R_AKNEXLIST_MARKABLELIST_DOUBLE_LARGE_GRAPHIC;
            break;
        case EAknExListCmdOutline92:
            // Used EAknListBoxMarkableListWithShortcuts.
            resourceId = R_AKNEXLIST_MARKABLELIST_WITHS_DOUBLE_LARGE_GRAPHIC;
            break;
        case EAknExListCmdOutline93: // Used EAknListBoxMultiselectionList.
            resourceId = R_AKNEXLIST_MULTISELECTIONLIST_DOUBLE_LARGE_GRAPHIC;
            break;
        case EAknExListCmdOutline94:
            // Used EAknListBoxMultiselectionListWithShortcuts.
            resourceId =
                R_AKNEXLIST_MULTISELECTIONLIST_WITHS_DOUBLE_LARGE_GRAPHIC;
            break;
        case EAknExListCmdOutline95: // Used EAknListBoxSelectionGrid.
            resourceId = R_AKNEXLIST_SELECTIONGRID_DOUBLE_LARGE_GRAPHIC;
            break;
        case EAknExListCmdOutline96:
            // Used EAknListBoxSelectionGridWithShortcuts.
            resourceId = R_AKNEXLIST_SELECTIONGRID_WITHS_DOUBLE_LARGE_GRAPHIC;
            break;
        case EAknExListCmdOutline97: // Used EAknListBoxMarkableGrid.
            resourceId = R_AKNEXLIST_MARKABLEGRID_DOUBLE_LARGE_GRAPHIC;
            break;
        case EAknExListCmdOutline98:
            // Used EAknListBoxMarkableGridWithShortcuts.
            resourceId = R_AKNEXLIST_MARKABLEGRID_WITHS_DOUBLE_LARGE_GRAPHIC;
            break;
        case EAknExListCmdOutline99: // Used EAknListBoxMenuGrid.
            resourceId = R_AKNEXLIST_MENUGRID_DOUBLE_LARGE_GRAPHIC;
            break;
        case EAknExListCmdOutline100: // Used EAknDialogSelectionList.
            resourceId = R_AKNEXLIST_DIALOGSELECTION_DOUBLE_LARGE_GRAPHIC;
            break;
        case EAknExListCmdOutline101: // Used EAknDialogMenuList.
            resourceId = R_AKNEXLIST_DIALOGMENU_DOUBLE_LARGE_GRAPHIC;
            break;
        case EAknExListCmdOutline102: // Used EAknListBoxViewerFlags.
            resourceId = R_AKNEXLIST_VIEWER_DOUBLE_LARGE_GRAPHIC;
            break;
        case EAknExListCmdOutline103: // Used EAknDialogMarkableList.
            resourceId = R_AKNEXLIST_DIALOGMARKABLE_DOUBLE_LARGE_GRAPHIC;
            break;
        case EAknExListCmdOutline104: // Used EAknDialogMultiselectionList.
            resourceId = R_AKNEXLIST_DIALOGMULTI_DOUBLE_LARGE_GRAPHIC;
            break;
        default:
            break;
        }

    return resourceId;
    }

// ----------------------------------------------------------------------------
// TInt CAknExListFlagTestContainer::ResourceIdSetting()
// Returns resource ID for CAknSettingStyleListBox.
// ----------------------------------------------------------------------------
//
TInt CAknExListFlagTestContainer::ResourceIdSetting()
    {
    TInt resourceId( KAknExListInitListResourceId );

    switch ( iOutlineId ) // Outline ID is...
        {
        case EAknExListCmdOutline06: // Used EAknListBoxLoopScrolling.
            resourceId = R_AKNEXLIST_LOOP_SETTING;
            break;
        case EAknExListCmdOutline88: // Used EAknListBoxSelectionList.
            resourceId = R_AKNEXLIST_SELECTIONLIST_SETTING;
            break;
        case EAknExListCmdOutline89:
            // Used EAknListBoxSelectionListWithShortcuts.
            resourceId = R_AKNEXLIST_SELECTIONLIST_WITHS_SETTING;
            break;
        case EAknExListCmdOutline90: // Used EAknListBoxMenuList.
            resourceId = R_AKNEXLIST_MENULIST_SETTING;
            break;
        case EAknExListCmdOutline91: // Used EAknListBoxMarkableList.
            resourceId = R_AKNEXLIST_MARKABLELIST_SETTING;
            break;
        case EAknExListCmdOutline92:
            // Used EAknListBoxMarkableListWithShortcuts.
            resourceId = R_AKNEXLIST_MARKABLELIST_WITHS_SETTING;
            break;
        case EAknExListCmdOutline93: // Used EAknListBoxMultiselectionList.
            resourceId = R_AKNEXLIST_MULTISELECTIONLIST_SETTING;
            break;
        case EAknExListCmdOutline94:
            // Used EAknListBoxMultiselectionListWithShortcuts.
            resourceId = R_AKNEXLIST_MULTISELECTIONLIST_WITHS_SETTING;
            break;
        case EAknExListCmdOutline95: // Used EAknListBoxSelectionGrid.
            resourceId = R_AKNEXLIST_SELECTIONGRID_SETTING;
            break;
        case EAknExListCmdOutline96:
            // Used EAknListBoxSelectionGridWithShortcuts.
            resourceId = R_AKNEXLIST_SELECTIONGRID_WITHS_SETTING;
            break;
        case EAknExListCmdOutline97: // Used EAknListBoxMarkableGrid.
            resourceId = R_AKNEXLIST_MARKABLEGRID_SETTING;
            break;
        case EAknExListCmdOutline98:
            // Used EAknListBoxMarkableGridWithShortcuts.
            resourceId = R_AKNEXLIST_MARKABLEGRID_WITHS_SETTING;
            break;
        case EAknExListCmdOutline99: // Used EAknListBoxMenuGrid.
            resourceId = R_AKNEXLIST_MENUGRID_SETTING;
            break;
        case EAknExListCmdOutline100: // Used EAknDialogSelectionList.
            resourceId = R_AKNEXLIST_DIALOGSELECTION_SETTING;
            break;
        case EAknExListCmdOutline101: // Used EAknDialogMenuList.
            resourceId = R_AKNEXLIST_DIALOGMENU_SETTING;
            break;
        case EAknExListCmdOutline102: // Used EAknListBoxViewerFlags.
            resourceId = R_AKNEXLIST_VIEWER_SETTING;
            break;
        case EAknExListCmdOutline103: // Used EAknDialogMarkableList.
            resourceId = R_AKNEXLIST_DIALOGMARKABLE_SETTING;
            break;
        case EAknExListCmdOutline104: // Used EAknDialogMultiselectionList.
            resourceId = R_AKNEXLIST_DIALOGMULTI_SETTING;
            break;
        default:
            break;
        }

    return resourceId;
    }

// ----------------------------------------------------------------------------
// TInt CAknExListFlagTestContainer::ResourceIdSettingNumber()
// Returns resource ID for CAknSettingNumberStyleListBox.
// ----------------------------------------------------------------------------
//
TInt CAknExListFlagTestContainer::ResourceIdSettingNumber()
    {
    TInt resourceId( KAknExListInitListResourceId );

    switch ( iOutlineId ) // Outline ID is...
        {
        case EAknExListCmdOutline06: // Used EAknListBoxLoopScrolling.
            resourceId = R_AKNEXLIST_LOOP_SETTING_NUMBER;
            break;
        case EAknExListCmdOutline88: // Used EAknListBoxSelectionList.
            resourceId = R_AKNEXLIST_SELECTIONLIST_SETTING_NUMBER;
            break;
        case EAknExListCmdOutline89:
            // Used EAknListBoxSelectionListWithShortcuts.
            resourceId = R_AKNEXLIST_SELECTIONLIST_WITHS_SETTING_NUMBER;
            break;
        case EAknExListCmdOutline90: // Used EAknListBoxMenuList.
            resourceId = R_AKNEXLIST_MENULIST_SETTING_NUMBER;
            break;
        case EAknExListCmdOutline91: // Used EAknListBoxMarkableList.
            resourceId = R_AKNEXLIST_MARKABLELIST_SETTING_NUMBER;
            break;
        case EAknExListCmdOutline92:
            // Used EAknListBoxMarkableListWithShortcuts.
            resourceId = R_AKNEXLIST_MARKABLELIST_WITHS_SETTING_NUMBER;
            break;
        case EAknExListCmdOutline93: // Used EAknListBoxMultiselectionList.
            resourceId = R_AKNEXLIST_MULTISELECTIONLIST_SETTING_NUMBER;
            break;
        case EAknExListCmdOutline94:
            // Used EAknListBoxMultiselectionListWithShortcuts.
            resourceId = R_AKNEXLIST_MULTISELECTIONLIST_WITHS_SETTING_NUMBER;
            break;
        case EAknExListCmdOutline95: // Used EAknListBoxSelectionGrid.
            resourceId = R_AKNEXLIST_SELECTIONGRID_SETTING_NUMBER;
            break;
        case EAknExListCmdOutline96:
            // Used EAknListBoxSelectionGridWithShortcuts.
            resourceId = R_AKNEXLIST_SELECTIONGRID_WITHS_SETTING_NUMBER;
            break;
        case EAknExListCmdOutline97: // Used EAknListBoxMarkableGrid.
            resourceId = R_AKNEXLIST_MARKABLEGRID_SETTING_NUMBER;
            break;
        case EAknExListCmdOutline98:
            // Used EAknListBoxMarkableGridWithShortcuts.
            resourceId = R_AKNEXLIST_MARKABLEGRID_WITHS_SETTING_NUMBER;
            break;
        case EAknExListCmdOutline99: // Used EAknListBoxMenuGrid.
            resourceId = R_AKNEXLIST_MENUGRID_SETTING_NUMBER;
            break;
        case EAknExListCmdOutline100: // Used EAknDialogSelectionList.
            resourceId = R_AKNEXLIST_DIALOGSELECTION_SETTING_NUMBER;
            break;
        case EAknExListCmdOutline101: // Used EAknDialogMenuList.
            resourceId = R_AKNEXLIST_DIALOGMENU_SETTING_NUMBER;
            break;
        case EAknExListCmdOutline102: // Used EAknListBoxViewerFlags.
            resourceId = R_AKNEXLIST_VIEWER_SETTING_NUMBER;
            break;
        case EAknExListCmdOutline103: // Used EAknDialogMarkableList.
            resourceId = R_AKNEXLIST_DIALOGMARKABLE_SETTING_NUMBER;
            break;
        case EAknExListCmdOutline104: // Used EAknDialogMultiselectionList.
            resourceId = R_AKNEXLIST_DIALOGMULTI_SETTING_NUMBER;
            break;
        default:
            break;
        }

    return resourceId;
    }

// ----------------------------------------------------------------------------
// TInt CAknExListFlagTestContainer::ResourceIdDoubleGraphic()
// Returns resource ID for CAknDoubleGraphicStyleListBox.
// ----------------------------------------------------------------------------
//
TInt CAknExListFlagTestContainer::ResourceIdDoubleGraphic()
    {
    TInt resourceId( KAknExListInitListResourceId );

    switch ( iOutlineId ) // Outline ID is...
        {
        case EAknExListCmdOutline06: // Used EAknListBoxLoopScrolling.
            resourceId = R_AKNEXLIST_LOOP_DOUBLE_GRAPHIC;
            break;
        case EAknExListCmdOutline88: // Used EAknListBoxSelectionList.
            resourceId = R_AKNEXLIST_SELECTIONLIST_DOUBLE_GRAPHIC;
            break;
        case EAknExListCmdOutline89:
            // Used EAknListBoxSelectionListWithShortcuts.
            resourceId = R_AKNEXLIST_SELECTIONLIST_WITHS_DOUBLE_GRAPHIC;
            break;
        case EAknExListCmdOutline90: // Used EAknListBoxMenuList.
            resourceId = R_AKNEXLIST_MENULIST_DOUBLE_GRAPHIC;
            break;
        case EAknExListCmdOutline91: // Used EAknListBoxMarkableList.
            resourceId = R_AKNEXLIST_MARKABLELIST_DOUBLE_GRAPHIC;
            break;
        case EAknExListCmdOutline92:
            // Used EAknListBoxMarkableListWithShortcuts.
            resourceId = R_AKNEXLIST_MARKABLELIST_WITHS_DOUBLE_GRAPHIC;
            break;
        case EAknExListCmdOutline93: // Used EAknListBoxMultiselectionList.
            resourceId = R_AKNEXLIST_MULTISELECTIONLIST_DOUBLE_GRAPHIC;
            break;
        case EAknExListCmdOutline94:
            // Used EAknListBoxMultiselectionListWithShortcuts.
            resourceId = R_AKNEXLIST_MULTISELECTIONLIST_WITHS_DOUBLE_GRAPHIC;
            break;
        case EAknExListCmdOutline95: // Used EAknListBoxSelectionGrid.
            resourceId = R_AKNEXLIST_SELECTIONGRID_DOUBLE_GRAPHIC;
            break;
        case EAknExListCmdOutline96:
            // Used EAknListBoxSelectionGridWithShortcuts.
            resourceId = R_AKNEXLIST_SELECTIONGRID_WITHS_DOUBLE_GRAPHIC;
            break;
        case EAknExListCmdOutline97: // Used EAknListBoxMarkableGrid.
            resourceId = R_AKNEXLIST_MARKABLEGRID_DOUBLE_GRAPHIC;
            break;
        case EAknExListCmdOutline98:
            // Used EAknListBoxMarkableGridWithShortcuts.
            resourceId = R_AKNEXLIST_MARKABLEGRID_WITHS_DOUBLE_GRAPHIC;
            break;
        case EAknExListCmdOutline99: // Used EAknListBoxMenuGrid.
            resourceId = R_AKNEXLIST_MENUGRID_DOUBLE_GRAPHIC;
            break;
        case EAknExListCmdOutline100: // Used EAknDialogSelectionList.
            resourceId = R_AKNEXLIST_DIALOGSELECTION_DOUBLE_GRAPHIC;
            break;
        case EAknExListCmdOutline101: // Used EAknDialogMenuList.
            resourceId = R_AKNEXLIST_DIALOGMENU_DOUBLE_GRAPHIC;
            break;
        case EAknExListCmdOutline102: // Used EAknListBoxViewerFlags.
            resourceId = R_AKNEXLIST_VIEWER_DOUBLE_GRAPHIC;
            break;
        case EAknExListCmdOutline103: // Used EAknDialogMarkableList.
            resourceId = R_AKNEXLIST_DIALOGMARKABLE_DOUBLE_GRAPHIC;
            break;
        case EAknExListCmdOutline104: // Used EAknDialogMultiselectionList.
            resourceId = R_AKNEXLIST_DIALOGMULTI_DOUBLE_GRAPHIC;
            break;
        default:
            break;
        }

    return resourceId;
    }

// ----------------------------------------------------------------------------
// void CAknExListFlagTestContainer::IsNeedGarphic( TBool& )
// Sets flag for creating graphic.
// ----------------------------------------------------------------------------
//
void CAknExListFlagTestContainer::IsNeedGarphic( TBool& aFlagsOfGraphic )
    {
    switch ( iOutlineId ) // Outline ID is...
        {
        case EAknExListCmdOutline91:
        case EAknExListCmdOutline92:
        case EAknExListCmdOutline93:
        case EAknExListCmdOutline94:
        case EAknExListCmdOutline97:
        case EAknExListCmdOutline98:
        case EAknExListCmdOutline103:
        case EAknExListCmdOutline104:
            aFlagsOfGraphic = ETrue;
            break;
        default:
            break;
        }
    }

// ----------------------------------------------------------------------------
// TInt CAknExListFlagTestContainer::ListFlags()
// Returns flags of listbox to use ConstructL() of listbox.
// ----------------------------------------------------------------------------
//
TInt CAknExListFlagTestContainer::ListFlags()
    {
    TInt flags( KAknExListInitValueOfListFlags );

    switch ( iOutlineId ) // Outline ID is...
        {
        case EAknExListCmdOutline06:
            flags = EAknListBoxSelectionList | EAknListBoxLoopScrolling;
            break;
        case EAknExListCmdOutline88:
            flags = EAknListBoxSelectionList;
            break;
        case EAknExListCmdOutline89:
            flags = EAknListBoxSelectionListWithShortcuts;
            break;
        case EAknExListCmdOutline90:
            flags = EAknListBoxMenuList;
            break;
        case EAknExListCmdOutline91:
            flags = EAknListBoxMarkableList;
            break;
        case EAknExListCmdOutline92:
            flags = EAknListBoxMarkableListWithShortcuts;
            break;
        case EAknExListCmdOutline93:
            flags = EAknListBoxMultiselectionList;
            break;
        case EAknExListCmdOutline94:
            flags = EAknListBoxMultiselectionListWithShortcuts;
            break;
        case EAknExListCmdOutline95:
            flags = EAknListBoxSelectionGrid;
            break;
        case EAknExListCmdOutline96:
            flags = EAknListBoxSelectionGridWithShortcuts;
            break;
        case EAknExListCmdOutline97:
            flags = EAknListBoxMarkableGrid;
            break;
        case EAknExListCmdOutline98:
            flags = EAknListBoxMarkableGridWithShortcuts;
            break;
        case EAknExListCmdOutline99:
            flags = EAknListBoxMenuGrid;
            break;
        case EAknExListCmdOutline100:
            flags = EAknDialogSelectionList;
            break;
        case EAknExListCmdOutline101:
            flags = EAknDialogMenuList;
            break;
        case EAknExListCmdOutline102:
            flags = EAknListBoxSelectionList | EAknListBoxViewerFlags;
            break;
        case EAknExListCmdOutline103:
            flags = EAknDialogMarkableList;
            break;
        case EAknExListCmdOutline104:
            flags = EAknDialogMultiselectionList;
            break;
        default:
            break;
        }

    return flags;
    }

// ----------------------------------------------------------------------------
// CDesCArray* CAknExListFlagTestContainer::ListItemsL( TInt )
// Returns list items as CDesCArray.
// ----------------------------------------------------------------------------
//
CDesCArray* CAknExListFlagTestContainer::ListItemsL( TInt aTabId )
    {
    CDesCArray* textArray = NULL;

    switch ( aTabId ) // Tab ID is...
        {
        // For outline06, 88, 90, 91, 93, 95, 97, 99, 100, 101, 102, 103, 104.
        case EAknExListTabIdType01:
            // List items for CAknSingleStyleListBox.
            textArray = iCoeEnv->ReadDesCArrayResourceL(
                R_AKNEXLIST_ITEM_SINGLE1 );
            break;
        case EAknExListTabIdType02:
            // List items for CAknSingleNumberStyleListBox.
            textArray = iCoeEnv->ReadDesCArrayResourceL(
                R_AKNEXLIST_ITEM_SINGLE_NUMBER );
            break;
        case EAknExListTabIdType03:
            // List items for CAknSingleHeadingStyleListBox.
            textArray = iCoeEnv->ReadDesCArrayResourceL(
                R_AKNEXLIST_ITEM_SINGLE_HEADING );
            break;
        case EAknExListTabIdType04:
            // List items for CAknSingleGraphicStyleListBox.
            textArray = iCoeEnv->ReadDesCArrayResourceL(
                R_AKNEXLIST_ITEM_SINGLE_GRAPHIC );
            break;
        case EAknExListTabIdType05:
            // List items for CAknSingleGraphicHeadingStyleListBox.
            textArray = iCoeEnv->ReadDesCArrayResourceL(
                R_AKNEXLIST_ITEM_SINGLE_GRAPHIC_HEADING );
            break;
        case EAknExListTabIdType06:
            // List items for CAknSingleNumberHeadingStyleListBox.
            textArray = iCoeEnv->ReadDesCArrayResourceL(
                R_AKNEXLIST_ITEM_SINGLE_NUMBER_HEADING );
            break;
        case EAknExListTabIdType07:
            // List items for CAknSingleLargeStyleListBox.
            textArray = iCoeEnv->ReadDesCArrayResourceL(
                R_AKNEXLIST_ITEM_SINGLE_LARGE_GRAPHIC );
            break;
        case EAknExListTabIdType08:
            // List items for CAknDoubleStyleListBox as single big pane.
            textArray = iCoeEnv->ReadDesCArrayResourceL(
                R_AKNEXLIST_ITEM_BIG_SINGLE );
            break;
        case EAknExListTabIdType09:
            // List items for CAknDoubleNumberStyleListBox as single big number
            // pane.
            textArray = iCoeEnv->ReadDesCArrayResourceL(
                R_AKNEXLIST_ITEM_BIG_SINGLE_NUMBER );
            break;
        case EAknExListTabIdType10:
            // List items for CAknDoubleLargeStyleListBox as single big large
            // graphic pane.
            textArray = iCoeEnv->ReadDesCArrayResourceL(
                R_AKNEXLIST_ITEM_BIG_SINGLE_GRAPHIC );
            break;
        case EAknExListTabIdType11:
            // List items for CAknDoubleStyleListBox.
            textArray = iCoeEnv->ReadDesCArrayResourceL(
                R_AKNEXLIST_ITEM_DOUBLE );
            break;
        case EAknExListTabIdType12:
            // List items for CAknDoubleNumberStyleListBox.
            textArray = iCoeEnv->ReadDesCArrayResourceL(
                R_AKNEXLIST_ITEM_DOUBLE_NUMBER );
            break;
        case EAknExListTabIdType13:
            // List items for CAknDoubleLargeStyleListBox.
            textArray = iCoeEnv->ReadDesCArrayResourceL(
                R_AKNEXLIST_ITEM_DOUBLE_LARGE_GRAPHIC );
            break;
        case EAknExListTabIdType14:
            // List items for CAknSettingStyleListBox.
            textArray = iCoeEnv->ReadDesCArrayResourceL(
                R_AKNEXLIST_ITEM_SETTING );
            break;
        case EAknExListTabIdType15:
            // List items for CAknSettingNumberStyleListBox.
            textArray = iCoeEnv->ReadDesCArrayResourceL(
                R_AKNEXLIST_ITEM_SETTING_NUMBER );
            break;
        case EAknExListTabIdType16:
            // List items for CAknDoubleGraphicStyleListBox.
            textArray = iCoeEnv->ReadDesCArrayResourceL(
                R_AKNEXLIST_ITEM_DOUBLE_GRAPHIC );
            break;
        // For outline89, 92, 94, 96, 98.
        case EAknExListTabIdType01Withs:
            // List items for CAknSingleStyleListBox.
            textArray = iCoeEnv->ReadDesCArrayResourceL(
                R_AKNEXLIST_ITEM_SINGLE_FOR_WITHS );
            break;
        case EAknExListTabIdType02Withs:
            // List items for CAknSingleNumberStyleListBox.
            textArray = iCoeEnv->ReadDesCArrayResourceL(
                R_AKNEXLIST_ITEM_SINGLE_NUMBER_FOR_WITHS );
            break;
        case EAknExListTabIdType03Withs:
            // List items for CAknSingleHeadingStyleListBox.
            textArray = iCoeEnv->ReadDesCArrayResourceL(
                R_AKNEXLIST_ITEM_SINGLE_HEADING_FOR_WITHS );
            break;
        case EAknExListTabIdType04Withs:
            // List items for CAknSingleGraphicStyleListBox.
            textArray = iCoeEnv->ReadDesCArrayResourceL(
                R_AKNEXLIST_ITEM_SINGLE_GRAPHIC_FOR_WITHS );
            break;
        case EAknExListTabIdType05Withs:
            // List items for CAknSingleGraphicHeadingStyleListBox.
            textArray = iCoeEnv->ReadDesCArrayResourceL(
                R_AKNEXLIST_ITEM_SINGLE_GRAPHIC_HEADING_FOR_WITHS );
            break;
        case EAknExListTabIdType06Withs:
            // List items for CAknSingleNumberHeadingStyleListBox.
            textArray = iCoeEnv->ReadDesCArrayResourceL(
                R_AKNEXLIST_ITEM_SINGLE_NUMBER_HEADING_FOR_WITHS );
            break;
        case EAknExListTabIdType07Withs:
            // List items for CAknSingleLargeStyleListBox.
            textArray = iCoeEnv->ReadDesCArrayResourceL(
                R_AKNEXLIST_ITEM_SINGLE_LARGE_GRAPHIC_FOR_WITHS );
            break;
        case EAknExListTabIdType08Withs:
            // List items for CAknDoubleStyleListBox as single big pane.
            textArray = iCoeEnv->ReadDesCArrayResourceL(
                R_AKNEXLIST_ITEM_BIG_SINGLE_FOR_WITHS );
            break;
        case EAknExListTabIdType09Withs:
            // List items for CAknDoubleNumberStyleListBox as single big number
            // pane.
            textArray = iCoeEnv->ReadDesCArrayResourceL(
                R_AKNEXLIST_ITEM_BIG_SINGLE_NUMBER_FOR_WITHS );
            break;
        case EAknExListTabIdType10Withs:
            // List items for CAknDoubleLargeStyleListBox as single big large
            // graphic pane.
            textArray = iCoeEnv->ReadDesCArrayResourceL(
                R_AKNEXLIST_ITEM_BIG_SINGLE_GRAPHIC_FOR_WITHS );
            break;
        case EAknExListTabIdType11Withs:
            // List items for CAknDoubleStyleListBox.
            textArray = iCoeEnv->ReadDesCArrayResourceL(
                R_AKNEXLIST_ITEM_DOUBLE_FOR_WITHS );
            break;
        case EAknExListTabIdType12Withs:
            // List items for CAknDoubleNumberStyleListBox.
            textArray = iCoeEnv->ReadDesCArrayResourceL(
                R_AKNEXLIST_ITEM_DOUBLE_NUMBER_FOR_WITHS );
            break;
        case EAknExListTabIdType13Withs:
            // List items for CAknDoubleLargeStyleListBox.
            textArray = iCoeEnv->ReadDesCArrayResourceL(
                R_AKNEXLIST_ITEM_DOUBLE_LARGE_GRAPHIC_FOR_WITHS );
            break;
        case EAknExListTabIdType14Withs:
            // List items for CAknSettingStyleListBox.
            textArray = iCoeEnv->ReadDesCArrayResourceL(
                R_AKNEXLIST_ITEM_SETTING_FOR_WITHS );
            break;
        case EAknExListTabIdType15Withs:
            // List items for CAknSettingNumberStyleListBox.
            textArray = iCoeEnv->ReadDesCArrayResourceL(
                R_AKNEXLIST_ITEM_SETTING_NUMBER_FOR_WITHS );
            break;
        case EAknExListTabIdType16Withs:
            // List items for CAknDoubleGraphicStyleListBox.
            textArray = iCoeEnv->ReadDesCArrayResourceL(
                R_AKNEXLIST_ITEM_DOUBLE_GRAPHIC_FOR_WITHS );
            break;
        default:
            break;
        }

    return textArray;
    }

// ----------------------------------------------------------------------------
// void CAknExListFlagTestContainer::GraphicIconL( CArrayPtr<CGulIcon>* )
// Appends graphics data.
// ----------------------------------------------------------------------------
//
void CAknExListFlagTestContainer::GraphicIconL( CArrayPtr<CGulIcon>* aIcons )
    {
    if ( aIcons )
        {
        TInt tabId( KAknExListInitTabId );
        CAknTabGroup* tabGroup = iView->TabGroup();

        if ( tabGroup )
            {
            // Gets current tab ID.
            tabId = tabGroup->TabIdFromIndex( tabGroup->ActiveTabIndex() );
            }

        // Appends icon according to tab ID.
        if ( tabId == EAknExListTabIdType14 ||
             tabId == EAknExListTabIdType15 ||
             tabId == EAknExListTabIdType14Withs ||
             tabId == EAknExListTabIdType15Withs )
            {
            // Graphics for marking.
            aIcons->AppendL( iEikonEnv->CreateIconL( KAknExListMbmFileName,
                                                     EMbmAknexlistMarked_add,
                                                     EMbmAknexlistMarked_add_m ) );

            }
        else
            {
            // Graphics for marking.
            aIcons->AppendL( iEikonEnv->CreateIconL( KAknExListMbmFileName,
                                                     EMbmAknexlistMarked_add,
                                                     EMbmAknexlistMarked_add_m ) );

            switch ( tabId )
                {
                case EAknExListTabIdType04:
                case EAknExListTabIdType04Withs:
                case EAknExListTabIdType05:
                case EAknExListTabIdType05Withs:
                case EAknExListTabIdType16:
                case EAknExListTabIdType16Withs:
                    aIcons->AppendL(
                        iEikonEnv->CreateIconL( KAknExListMbmFileName,
                                                EMbmAknexlistGolgo3,
                                                EMbmAknexlistGolgo3m ) );
                    break;
                case EAknExListTabIdType07:
                case EAknExListTabIdType07Withs:
                case EAknExListTabIdType10:
                case EAknExListTabIdType10Withs:
                case EAknExListTabIdType13:
                case EAknExListTabIdType13Withs:
                    aIcons->AppendL(
                        iEikonEnv->CreateIconL( KAknExListMbmFileName,
                                                EMbmAknexlistGolgo2,
                                                EMbmAknexlistGolgo2m ) );
                    break;
                default:
                    break;
                }
            }
        }
    }

// ----------------------------------------------------------------------------
// void CAknExListFlagTestContainer::SizeChanged()
// Called by framework when the view size is changed.
// ----------------------------------------------------------------------------
//
void CAknExListFlagTestContainer::SizeChanged()
    {
    if ( iListBox )
        {
        iListBox->SetRect( Rect() ); // Sets rectangle of lstbox.
        }
    }

// ----------------------------------------------------------------------------
// TInt CAknExListFlagTestContainer::CountComponentControls() const
// Returns number of components.
// ----------------------------------------------------------------------------
//
TInt CAknExListFlagTestContainer::CountComponentControls() const
    {
    TInt count( KAknExListInitCount );

    if ( iListBox )
        {
        count++;
        }

    return count; // Returns number of controls inside this container.
    }

// ----------------------------------------------------------------------------
// CCoeControl* CAknExListFlagTestContainer::ComponentControl( TInt ) const
// Returns pointer to particular component.
// ----------------------------------------------------------------------------
//
CCoeControl* CAknExListFlagTestContainer::ComponentControl( TInt aIndex ) const
    {
    switch ( aIndex )
        {
        case EAknExListDefaultComponent:
            return iListBox; // Returns the pointer to listbox object.
        default:
            return NULL; // Exception : Returns NULL.
        }
    }

// End of File
