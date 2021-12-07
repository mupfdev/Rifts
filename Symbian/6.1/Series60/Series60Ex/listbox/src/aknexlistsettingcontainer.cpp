/*
* =============================================================================
*  Name     : CAknExListSettingContainer
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
#include "AknExListConst.h" // for bitmap file name
#include "AknExListSettingView.h"
#include "AknExListSettingContainer.h"

// CONSTANTS
const TInt KAknExListInitCount = 0; // for initialization.

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExListSettingContainer::CAknExListSettingContainer(
//  CAknExListSettingView* )
// Copy constructor.
// ----------------------------------------------------------------------------
//
CAknExListSettingContainer::CAknExListSettingContainer(
    CAknExListSettingView* aView )
:   iListBox( NULL ),
    iView( aView ),
    iOutlineId( KAknExListInitOutlineId )
    {
    }

// ----------------------------------------------------------------------------
// void CAknExListSettingContainer::ConstructL( const TRect& )
// EPOC two phased constructor.
// ----------------------------------------------------------------------------
//
void CAknExListSettingContainer::ConstructL( const TRect& aRect )
    {
    CreateWindowL(); // Creates window.
    SetRect( aRect ); // Sets rectangle of frame.
    ActivateL(); // Activates window. (Ready to draw)
    }

// ----------------------------------------------------------------------------
// CAknExListSettingContainer::~CAknExListSettingContainer()
// Destructor.
// ----------------------------------------------------------------------------
//
CAknExListSettingContainer::~CAknExListSettingContainer()
    {
    delete iListBox; // Deletes listbox object.
    }

// ----------------------------------------------------------------------------
// void CAknExListSettingContainer::DisplayListBoxL( const TInt )
// Displays listbox.
// ----------------------------------------------------------------------------
//
void CAknExListSettingContainer::DisplayListBoxL( const TInt aOutlineId )
    {
    // Sets outlineId.
    iOutlineId = aOutlineId;

    // Deletes listbox object.
    if ( iListBox )
        {
        delete iListBox;
        iListBox = NULL;
        }

    TInt resourceId( KAknExListInitListResourceId ); // For listbox.
    TInt emptyResourceId( KAknExListInitEmptyResourceId ); // For empty text.
    TInt messageId( KAknExListMessageInitId ); // For displaying message.
    TBool flagsOfNumber( EFalse ); // Flag for auto numbering.
    TBool flagsOfGraphic( EFalse ); // Flag for graphic.

    // Creates ListBox control object and sets resource ID.
    switch ( iOutlineId ) // Outlind ID is...
        {
        case EAknExListCmdOutline22: // OUTLINE22 screen.
            resourceId = R_AKNEXLIST_SETTING;
            flagsOfGraphic = ETrue;
            iListBox = new( ELeave ) CAknSettingStyleListBox();
            break;
        case EAknExListCmdOutline23: // OUTLINE23 screen.
            resourceId = R_AKNEXLIST_SETTING_NUMBER;
            flagsOfGraphic = ETrue;
            messageId = R_AKNEXLIST_USER_DEFINED_NUMBERING_MSG;
            iListBox = new( ELeave ) CAknSettingNumberStyleListBox();
            break;
        case EAknExListCmdOutline59: // OUTLINE59 screen.
            resourceId = R_AKNEXLIST_SETTING_NUMBER;
            flagsOfNumber = ETrue;
            flagsOfGraphic = ETrue;
            iListBox = new( ELeave ) CAknSettingNumberStyleListBox();
            break;
        case EAknExListCmdOutline74: // OUTLINE74 screen.
            resourceId = R_AKNEXLIST_SETTING;
            flagsOfGraphic = ETrue;
            iListBox = new( ELeave ) CAknSettingStyleListBox();
            break;
        case EAknExListCmdOutline75: // OUTLINE75 screen.
            flagsOfGraphic = ETrue;
            iListBox = new( ELeave ) CAknSettingStyleListBox();
            break;
        case EAknExListCmdOutline76: // OUTLINE76 screen.
            emptyResourceId = R_AKNEXLIST_TWO_LINES_EMPTY_LABEL;
            flagsOfGraphic = ETrue;
            iListBox = new( ELeave ) CAknSettingStyleListBox();
            break;
        case EAknExListCmdOutline79: // OUTLINE79 screen.
            resourceId = R_AKNEXLIST_SETTING;
            flagsOfGraphic = ETrue;
            iListBox = new( ELeave ) CAknSettingStyleListBox();
            break;
        default:
            break;
        }

    if ( iListBox )
        {
        // Sets ListBox.
        if ( resourceId )
            {
            SetListBoxFromResourceL( iListBox, resourceId );
            }
        else
            {
            SetListBoxFromInnerDescriptionL( iListBox );
            }

        SizeChanged();

        if ( flagsOfNumber )
            {
            // Automatic numbering.
            AutoNumberingL( iListBox );
            }

        if ( flagsOfGraphic )
            {
            // Creates graphic.
            SetGraphicIconL( iListBox );
            }

        if ( emptyResourceId )
            {
            // Sets empty text.
            SetEmptyListL( iListBox, emptyResourceId );
            }

        iListBox->ActivateL();
        // Update scrollbar in order to draw correct scroll bar.
        UpdateScrollBar(iListBox);

        // erase the bitmap in cell
        switch ( iOutlineId ) // Outlind ID is...
            {
            case EAknExListCmdOutline22: // OUTLINE22 screen.
            case EAknExListCmdOutline74: // OUTLINE74 screen.
            case EAknExListCmdOutline75: // OUTLINE75 screen.
            case EAknExListCmdOutline76: // OUTLINE76 screen.
            case EAknExListCmdOutline79: // OUTLINE79 screen.
            case EAknExListCmdOutline23: // OUTLINE23 screen.
            case EAknExListCmdOutline59: // OUTLINE59 screen.
               
                iListBox->ItemDrawer()->FormattedCellData()->SetGraphicsSubCellL(2,EFalse);
                break;
            }
        }

    DrawNow();

    if ( messageId )
        {
        InfoMessage( messageId ); // Displays information message.
        }
    }

// ----------------------------------------------------------------------------
// TKeyResponse CAknExListSettingContainer::OfferKeyEventL( const TKeyEvent&,
//  TEventCode )
// Handles the key events.
// ----------------------------------------------------------------------------
//
TKeyResponse CAknExListSettingContainer::OfferKeyEventL(
    const TKeyEvent& aKeyEvent,
    TEventCode aType )
    {
    if ( aType != EEventKey ) // Is not key event?
        {
        return EKeyWasNotConsumed;
        }

    CAknTabGroup* tabGroup = iView->TabGroup();
    TChar charCode(aKeyEvent.iCode);

    switch ( charCode ) // The code of key event is...
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
                    iView->SwitchDisplayOutlineL(
                        tabGroup->TabIdFromIndex(
                            tabGroup->ActiveTabIndex() ) );
                    return EKeyWasConsumed;
                    }
                }
            break;
        default:
            {
            break;
            }

        }

    switch (iOutlineId)
        {
        case EAknExListCmdOutline74:
            {
            if (charCode == AKNEXLIST_ADDINGTYPE1_KEY || 
                charCode == AKNEXLIST_ADDINGTYPE2_KEY ||
                charCode == AKNEXLIST_ADDINGTYPE3_KEY ||
                charCode == AKNEXLIST_ADDINGTYPE4_KEY ||
                charCode == AKNEXLIST_ADDINGTYPE5_KEY)
                {
                SetCountAndAddItemL( aKeyEvent ); // Adds list item.
                return EKeyWasConsumed;
                }
            else if (charCode == AKNEXLIST_REMOVINGTYPE1_KEY || 
                charCode == AKNEXLIST_REMOVINGTYPE2_KEY ||
                charCode == AKNEXLIST_REMOVINGTYPE3_KEY ||
                charCode == AKNEXLIST_REMOVINGTYPE4_KEY ||
                charCode == AKNEXLIST_REMOVINGTYPE5_KEY)
                {
                SetCountAndRemoveItemL( aKeyEvent ); // Removes list item.
                return EKeyWasConsumed;
                }
            break;
            }
        case EAknExListCmdOutline23:
            {
            if (charCode == AKNEXLIST_AUTONUMBERING_KEY) 
                {
                // Automatic numbering.
                AutoNumberingL( iListBox );
                // Updates listbox.
                iListBox->DrawNow();
                // Displays information message.
                InfoMessage( R_AKNEXLIST_AUTO_NUMBERING_MSG );
                return EKeyWasConsumed;
                }
            break;
            }
        default:
            {
            break;
            }
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
// void CAknExListSettingContainer::GraphicIconL( CArrayPtr<CGulIcon>* )
// Appends graphics data.
// ----------------------------------------------------------------------------
//
void CAknExListSettingContainer::GraphicIconL( CArrayPtr<CGulIcon>* aIcons )
    {
    if ( aIcons )
        {
        // Graphics for marking.
        aIcons->AppendL( iEikonEnv->CreateIconL( KAknExListMbmFileName,
                                                 EMbmAknexlistProp_group_small,
                                                 EMbmAknexlistProp_group_small_m));
                                                 //EMbmAknexlistM,
                                                 //    EMbmAknexlistMm ) );
        }
    }

// ----------------------------------------------------------------------------
// void CAknExListSettingContainer::SetCountAndAddItemL( const TKeyEvent& )
// Sets count of added list items and calls AddItemL().
// ----------------------------------------------------------------------------
//
void CAknExListSettingContainer::SetCountAndAddItemL(
    const TKeyEvent& aKeyEvent )
    {
    if ( iListBox )
        {
        TInt addCount( KAknExListAddInitCount );

        // Sets number(addCount) of adding list items
        switch ( aKeyEvent.iCode )
            {
            case AKNEXLIST_ADDINGTYPE1_KEY: // 'a' key.
                addCount = KAknExListNumberOfItemType1;
                break;
            case AKNEXLIST_ADDINGTYPE2_KEY: // 'z' key.
                addCount = KAknExListNumberOfItemType2;
                break;
            case AKNEXLIST_ADDINGTYPE3_KEY: // 'x' key.
                addCount = KAknExListNumberOfItemType3;
                break;
            case AKNEXLIST_ADDINGTYPE4_KEY: // 'c' key.
                addCount = KAknExListNumberOfItemType4;
                break;
            case AKNEXLIST_ADDINGTYPE5_KEY: // 'v' key.
                addCount = KAknExListNumberOfItemType5;
                break;
            default:
                break;
            }

        if ( addCount )
            {
            // Adds list items.
            CTextListBoxModel* model = iListBox->Model();
            AddItemL(
                iListBox, model, addCount, R_AKNEXLIST_ADD_ITEM_SETTING );

            // Displays information for total number of list items.
            CountMessage( model );
            }
        }
    }

// ----------------------------------------------------------------------------
// void CAknExListSettingContainer::SetCountAndRemoveItemL( const TKeyEvent& )
// Sets count of removed list items and calls RemoveItemL().
// ----------------------------------------------------------------------------
//
void CAknExListSettingContainer::SetCountAndRemoveItemL(
    const TKeyEvent& aKeyEvent )
    {
    if ( iListBox )
        {
        TInt removeCount( KAknExListRemoveInitCount );

        // Sets number(removeCount) of removing list items.
        switch ( aKeyEvent.iCode )
            {
            case AKNEXLIST_REMOVINGTYPE1_KEY: // 'd' key.
                removeCount = KAknExListNumberOfItemType1;
                break;
            case AKNEXLIST_REMOVINGTYPE2_KEY: // 'p' key.
                removeCount = KAknExListNumberOfItemType2;
                break;
            case AKNEXLIST_REMOVINGTYPE3_KEY: // 'o' key.
                removeCount = KAknExListNumberOfItemType3;
                break;
            case AKNEXLIST_REMOVINGTYPE4_KEY: // 'i' key.
                removeCount = KAknExListNumberOfItemType4;
                break;
            case AKNEXLIST_REMOVINGTYPE5_KEY: // 'u' key.
                removeCount = KAknExListNumberOfItemType5;
                break;
            default:
                break;
            }

        if ( removeCount )
            {
            // Removes list items.
            CTextListBoxModel* model = iListBox->Model();
            RemoveItemL( iListBox, model, removeCount );

            // Displays information for total number of list items.
            CountMessage( model );
            }
        }
    }

// ----------------------------------------------------------------------------
// void CAknExListSettingContainer::SizeChanged()
// Called by framework when the view size is changed.
// ----------------------------------------------------------------------------
//
void CAknExListSettingContainer::SizeChanged()
    {
    if ( iListBox )
        {
        iListBox->SetRect( Rect() ); // Sets rectangle of lstbox.
        }
    }

// ----------------------------------------------------------------------------
// TInt CAknExListSettingContainer::CountComponentControls() const
// Returns number of components.
// ----------------------------------------------------------------------------
//
TInt CAknExListSettingContainer::CountComponentControls() const
    {
    TInt count( KAknExListInitCount );

    if ( iListBox )
        {
        count++;
        }

    return count; // Returns number of controls inside this container.
    }

// ----------------------------------------------------------------------------
// CCoeControl* CAknExListSettingContainer::ComponentControl( TInt ) const
// Returns pointer to particular component.
// ----------------------------------------------------------------------------
//
CCoeControl* CAknExListSettingContainer::ComponentControl( TInt aIndex ) const
    {
    switch ( aIndex )
        {
        case EKAknExListComponentListBox:
            return iListBox; // Returns the pointer to listbox object.
        default:
            return NULL; // Exception : Returns NULL.
        }
    }

// End of File
