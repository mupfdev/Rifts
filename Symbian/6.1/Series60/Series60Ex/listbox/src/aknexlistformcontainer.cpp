/*
* =============================================================================
*  Name     : CAknExListFormContainer
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
#include "AknExListConst.h"
#include "AknExListFormView.h"
#include "AknExListFormContainer.h"

// CONSTANTS
const TInt KAknExListInitCount = 0; // for initialization.

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExListFormContainer::CAknExListFormContainer( CAknExListFormView* )
// Copy constructor.
// ----------------------------------------------------------------------------
//
CAknExListFormContainer::CAknExListFormContainer( CAknExListFormView* aView )
:   iListBox( NULL ),
    iView( aView ),
    iFindBox( NULL ),
    iOutlineId( KAknExListInitOutlineId )
    {
    }

// ----------------------------------------------------------------------------
// void CAknExListFormContainer::ConstructL( const TRect& )
// EPOC two phased constructor.
// ----------------------------------------------------------------------------
//
void CAknExListFormContainer::ConstructL( const TRect& aRect )
    {
    CreateWindowL(); // Creates window.
    SetRect( aRect ); // Sets rectangle of frame.
    ActivateL(); // Activates window. (Ready to draw)
    }

// ----------------------------------------------------------------------------
// CAknExListFormContainer::~CAknExListFormContainer()
// Destructor.
// ----------------------------------------------------------------------------
//
CAknExListFormContainer::~CAknExListFormContainer()
    {
    delete iListBox; // Deletes listbox object.
    delete iFindBox; // Deletes findbox object.
    }

// ----------------------------------------------------------------------------
// void CAknExListFormContainer::DisplayListBoxL( const TInt )
// Displays listbox.
// ----------------------------------------------------------------------------
//
void CAknExListFormContainer::DisplayListBoxL( const TInt aOutlineId )
    {
    // Sets outlineId.
    iOutlineId = aOutlineId;

    // Deletes listbox object.
    if ( iListBox )
        {
        delete iListBox;
        iListBox = NULL;
        }

    // Deletes findbox object.
    if ( iFindBox )
        {
        delete iFindBox;
        iFindBox = NULL;
        }

    TInt resourceId( KAknExListInitListResourceId ); // For listbox.
    TInt emptyResourceId( KAknExListInitEmptyResourceId ); // For empty text.
    TInt messageId( KAknExListMessageInitId ); // For displaying message.
    TBool flagsOfGraphic( EFalse ); // Flag for graphic.
    TBool flagsOfNumber( EFalse ); // Flag for auto numbering.
    TBool flagsOfFindBox( EFalse ); // Flag for findbox.
    CAknTabGroup* tabGroup = iView->TabGroup();

    // Creates ListBox control object and sets resource ID.
    switch ( iOutlineId ) // Outline ID is...
        {
        case EAknExListCmdOutline16: // OUTLINE16 screen.
            resourceId = R_AKNEXLIST_BIG_SINGLE;
            iListBox = new( ELeave ) CAknDoubleStyleListBox();
            break;
        case EAknExListCmdOutline17: // OUTLINE17 screen.
            resourceId = R_AKNEXLIST_BIG_SINGLE_NUMBER;
            if ( tabGroup )
                {
                flagsOfNumber = ETrue;
                }
            else
                {
                messageId = R_AKNEXLIST_USER_DEFINED_NUMBERING_MSG;
                }
            iListBox = new( ELeave ) CAknDoubleNumberStyleListBox();
            break;
        case EAknExListCmdOutline18: // OUTLINE18 screen.
            resourceId = R_AKNEXLIST_BIG_SINGLE_GRAPHIC;
            iListBox = new( ELeave ) CAknDoubleLargeStyleListBox();
            flagsOfGraphic = ETrue;
            break;
        case EAknExListCmdOutline19: // OUTLINE19 screen.
            resourceId = R_AKNEXLIST_DOUBLE;
            iListBox = new( ELeave ) CAknDoubleStyleListBox();
            break;
        case EAknExListCmdOutline20: // OUTLINE20 screen.
            resourceId = R_AKNEXLIST_DOUBLE_NUMBER;
            if ( tabGroup )
                {
                flagsOfNumber = ETrue;
                }
            else
                {
                messageId = R_AKNEXLIST_USER_DEFINED_NUMBERING_MSG;
                }
            iListBox = new( ELeave ) CAknDoubleNumberStyleListBox();
            break;
        case EAknExListCmdOutline21: // OUTLINE21 screen.
            resourceId = R_AKNEXLIST_DOUBLE_LARGE_GRAPHIC;
            iListBox = new( ELeave ) CAknDoubleLargeStyleListBox();
            flagsOfGraphic = ETrue;
            break;
        case EAknExListCmdOutline41T3: // Popup findbox of OUTLINE41 screen.
            resourceId = R_AKNEXLIST_DOUBLE;
            flagsOfFindBox = ETrue;
            iListBox = new( ELeave ) CAknDoubleStyleListBox();
            break;
        case EAknExListCmdOutline53: // OUTLINE53 screen.
            resourceId = R_AKNEXLIST_DOUBLE_NUMBER;
            flagsOfNumber = ETrue;
            iListBox = new( ELeave ) CAknDoubleNumberStyleListBox();
            break;
        case EAknExListCmdOutline54: // OUTLINE54 screen.
            resourceId = R_AKNEXLIST_BIG_SINGLE_NUMBER;
            flagsOfNumber = ETrue;
            iListBox = new( ELeave ) CAknDoubleNumberStyleListBox();
            break;
        case EAknExListCmdOutline55: // OUTLINE55 screen.
            resourceId = R_AKNEXLIST_DOUBLE_GRAPHIC;
            iListBox = new( ELeave ) CAknDoubleGraphicStyleListBox();
            flagsOfGraphic = ETrue;
            break;
        case EAknExListCmdOutline57: // OUTLINE57 screen.
            resourceId = R_AKNEXLIST_DOUBLE_LARGE_GRAPHIC;
            iListBox = new( ELeave ) CAknDoubleLargeStyleListBox();
            flagsOfGraphic = ETrue;
            break;
        case EAknExListCmdOutline58: // OUTLINE58 screen.
            resourceId = R_AKNEXLIST_BIG_SINGLE_GRAPHIC;
            iListBox = new( ELeave ) CAknDoubleLargeStyleListBox();
            flagsOfGraphic = ETrue;
            break;
        case EAknExListCmdOutline67: // OUTLINE67 screen.
            resourceId = R_AKNEXLIST_DOUBLE;
            iListBox = new( ELeave ) CAknDoubleStyleListBox();
            break;
        case EAknExListCmdOutline68: // OUTLINE68 screen.
            iListBox = new( ELeave ) CAknDoubleStyleListBox();
            break;
        case EAknExListCmdOutline71: // OUTLINE71 screen.
            emptyResourceId = R_AKNEXLIST_TWO_LINES_EMPTY_LABEL;
            iListBox = new( ELeave ) CAknDoubleStyleListBox();
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

        if ( flagsOfFindBox )
            {
            // Creates FindBox as popup.
            iFindBox = CreateFindBoxL(
                iListBox, iListBox->Model(), CAknSearchField::EPopup );

            if ( iFindBox )
                {
                // Popup findbox is not shown when listbox display initial.
                iFindBox->MakeVisible( EFalse );
                }
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

        if ( iFindBox )
            {
            // For window owning overlay control when findbox is popup.
            iFindBox->ActivateL();
            }
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
// TKeyResponse CAknExListFormContainer::OfferKeyEventL( const TKeyEvent&,
//  TEventCode )
// Handles the key events.
// ----------------------------------------------------------------------------
//
TKeyResponse CAknExListFormContainer::OfferKeyEventL(
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
            break;
        }

    switch (iOutlineId)
        {
        case EAknExListCmdOutline67:
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
        case EAknExListCmdOutline17:
        case EAknExListCmdOutline20:
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
        if ( iFindBox )
            {
            TBool needRefresh( EFalse );

            // Offers the key event to find box.
            if ( AknFind::HandleFindOfferKeyEventL( aKeyEvent, aType, this,
                                                    iListBox, iFindBox, ETrue,
                                                    needRefresh ) ==
                EKeyWasConsumed )
                {
                if ( needRefresh )
                    {
                    SizeChanged();
                    DrawNow();
                    }

                return EKeyWasConsumed;
                }
            }

        return iListBox->OfferKeyEventL( aKeyEvent, aType );
        }
    else
        {
        return EKeyWasNotConsumed;
        }
    }

// ----------------------------------------------------------------------------
// void CAknExListFormContainer::GraphicIconL( CArrayPtr<CGulIcon>* )
// Appends graphics data.
// ----------------------------------------------------------------------------
//
void CAknExListFormContainer::GraphicIconL( CArrayPtr<CGulIcon>* aIcons )
    {
    if ( aIcons )
        {
        // Appends icon according to iOutlineId.
        switch ( iOutlineId )
            {
            case EAknExListCmdOutline18:
            case EAknExListCmdOutline21:
            case EAknExListCmdOutline57:
            case EAknExListCmdOutline58:
                aIcons->AppendL( iEikonEnv->CreateIconL( KAknExListMbmFileName,
                                                         EMbmAknexlistMarked_add,
                                                         EMbmAknexlistMarked_add_m ) );
                aIcons->AppendL(
                    iEikonEnv->CreateIconL( KAknExListMbmFileName,
                                            EMbmAknexlistGolgo2,
                                            EMbmAknexlistGolgo2m ) );
                break;
            case EAknExListCmdOutline55:
                aIcons->AppendL( iEikonEnv->CreateIconL( KAknExListMbmFileName,
                                                         EMbmAknexlistMarked_add,
                                                         EMbmAknexlistMarked_add_m ) );
                aIcons->AppendL(
                    iEikonEnv->CreateIconL( KAknExListMbmFileName,
                                            EMbmAknexlistGolgo3,
                                            EMbmAknexlistGolgo3m ) );
                break;
            default:
                break;
            }
        }
    }

// ----------------------------------------------------------------------------
// void CAknExListFormContainer::SetCountAndAddItemL( const TKeyEvent& )
// Sets count of added list items and calls AddItemL().
// ----------------------------------------------------------------------------
//
void CAknExListFormContainer::SetCountAndAddItemL( const TKeyEvent& aKeyEvent )
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
            AddItemL( iListBox, model, addCount, R_AKNEXLIST_ADD_ITEM_DOUBLE );

            // Displays information for total number of list items.
            CountMessage( model );
            }
        }
    }

// ----------------------------------------------------------------------------
// void CAknExListFormContainer::SetCountAndRemoveItemL( const TKeyEvent& )
// Sets count of removed list items and calls RemoveItemL().
// ----------------------------------------------------------------------------
//
void CAknExListFormContainer::SetCountAndRemoveItemL(
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
// void CAknExListFormContainer::SizeChanged()
// Called by framework when the view size is changed.
// ----------------------------------------------------------------------------
//
void CAknExListFormContainer::SizeChanged()
    {
    if ( iListBox )
        {
        if ( iFindBox )
            {
            // Calls HandleFindSizeChanged after creates findbox.
            AknFind::HandlePopupFindSizeChanged(this, iListBox, iFindBox);
            }
        else
            {
            iListBox->SetRect( Rect() ); // Sets rectangle of lstbox.
            }
        }
    }

// ----------------------------------------------------------------------------
// TInt CAknExListFormContainer::CountComponentControls() const
// Returns number of components.
// ----------------------------------------------------------------------------
//
TInt CAknExListFormContainer::CountComponentControls() const
    {
    TInt count( KAknExListInitCount );

    if ( iListBox )
        {
        count++;
        }

    if ( iFindBox )
        {
        count++;
        }

    return count; // Returns number of controls inside this container.
    }

// ----------------------------------------------------------------------------
// CCoeControl* CAknExListFormContainer::ComponentControl( TInt ) const
// Returns pointer to particular component.
// ----------------------------------------------------------------------------
//
CCoeControl* CAknExListFormContainer::ComponentControl( TInt aIndex ) const
    {
    switch ( aIndex )
        {
        case EAknExListComponentListBox:
            return iListBox; // Returns the pointer to listbox object.
        case EAknExListComponentFindBox:
            return iFindBox; // Returns the pointer to findbox object.
        default:
            return NULL; // Exception : Returns NULL.
        }
    }

// End of File
