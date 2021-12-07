/*
* =============================================================================
*  Name     : CAknExListColumnContainer
*  Part of  : AknExList
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

// INCLUDE FILES
#include <aknlists.h> // for avrell style listbox
#include <akntabgrp.h>
#include <coemain.h>
#include <aknexlist.rsg>
#include <aknexlist.mbg>
#include "AknExList.hrh"
#include "AknExListConst.h" // For bitmap file name
#include "AknExListColumnView.h"
#include "AknExListColumnContainer.h"
#include "AknExListAppUi.h"

// CONSTANTS
// for length.
const TInt KAknExListLabelBufLength = 256;
const TInt KAknExListMarkedIndexBufLength = 256;
const TInt KAknExListInfoTextBufLength =256;
const TInt KAknExListInformationBufLength = 256;
const TInt KAknExListSelectionIndexFormatBufLength = 256;
const TInt KAknExListNonTextBufLength = 256;
const TInt KAknExListTabBufLength = 4;
const TInt KAknExListItemBufLength = 256;
// for initialization.
const TInt KAknExListInitValueOfListFlags = 0;
const TInt KAknExListInitItemCount = 0;
const TInt KAknExListInitTabCount = 0;
const TInt KAknExListInitPosition = 0;
const TInt KAknExListInitCount = 0;
const TInt KAknExListStartCount = 0;
// for key event.
#define AKNEXLIST_ICONPRIORITY_KEY '0'
#define AKNEXLIST_MARKEDINDEX_KEY '0'

#define IAPPUI STATIC_CAST(CAknExListAppUi*, iCoeEnv->AppUi())

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExListColumnContainer::CAknExListColumnContainer(
//  CAknExListColumnView* )
// Copy constructor.
// ----------------------------------------------------------------------------
//
CAknExListColumnContainer::CAknExListColumnContainer(
    CAknExListColumnView* aView )
:   iLabel( NULL ),
    iListBox( NULL ),
    iView( aView ),
    iFindBox( NULL ),
    iOutlineId( KAknExListInitOutlineId )
    {
    }

// ----------------------------------------------------------------------------
// void CAknExListColumnContainer::ConstructL( const TRect& )
// EPOC constructor.
// ----------------------------------------------------------------------------
//
void CAknExListColumnContainer::ConstructL( const TRect& aRect )
    {
    CreateWindowL(); // Creates window.
    SetRect( aRect ); // Sets rectangle of frame.
    ActivateL(); // Activates window. (Ready to draw)
    }

// ----------------------------------------------------------------------------
// CAknExListColumnContainer::~CAknExListColumnContainer()
// Destructor.
// ----------------------------------------------------------------------------
//
CAknExListColumnContainer::~CAknExListColumnContainer()
    {
    delete iLabel; // Deletes label object.
    delete iListBox; // Deletes listbox object.
    delete iFindBox; // Deletes findbox object.
    }

// ----------------------------------------------------------------------------
// void CAknExListColumnContainer::DisplayListBoxL( const TInt )
// Displays listbox or start screen.
// ----------------------------------------------------------------------------
//
void CAknExListColumnContainer::DisplayListBoxL( const TInt aOutlineId )
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

    // Deletes label object.
    if ( iLabel )
        {
        delete iLabel;
        iLabel = NULL;
        }

    TInt resourceId( KAknExListInitListResourceId ); // For listbox.
    TInt emptyResourceId( KAknExListInitEmptyResourceId ); // For empty text.
    TInt messageId( KAknExListMessageInitId ); // For displaying message.
    TBool flagsOfGraphic( EFalse ); // Flag for graphic.
    TBool flagsOfNumber( EFalse ); // Flag for auto numbering.
    TBool flagsOfFindBox( EFalse ); // Flag for findbox.
    TBool flagsOfPopup( EFalse ); // Flag for find popup.
    CAknTabGroup* tabGroup = iView->TabGroup();

    // Creates ListBox control object and sets resource ID.
    switch ( iOutlineId ) // Outline ID is...
        {
        case EAknExListCmdEmptyOutline: // Start screen.
            SetLabelL( R_AKNEXLIST_APP_TITLE );
            break;
        case EAknExListCmdOutline01: // OUTLINE01 screen.
            resourceId = R_AKNEXLIST_SINGLE_1;
            iListBox = new( ELeave ) CAknSingleStyleListBox();
            break;
        case EAknExListCmdOutline02: // OUTLINE02 screen.
            resourceId = R_AKNEXLIST_SINGLE_1;
            iListBox = new( ELeave ) CAknSingleStyleListBox();
            break;
        case EAknExListCmdOutline03: // OUTLINE03 screen.
            resourceId = R_AKNEXLIST_SINGLE_1;
            iListBox = new( ELeave ) CAknSingleStyleListBox();
            break;
        case EAknExListCmdOutline04: // OUTLINE04 screen.
            resourceId = R_AKNEXLIST_SINGLE_1;
            iListBox = new( ELeave ) CAknSingleStyleListBox();
            break;
        case EAknExListCmdOutline05: // OUTLINE05 screen.
            resourceId = R_AKNEXLIST_SINGLE_NUMBER;
            flagsOfNumber = ETrue;
            iListBox = new( ELeave ) CAknSingleNumberStyleListBox();
            break;
        case EAknExListCmdOutline07: // OUTLINE07 screen.
            resourceId = R_AKNEXLIST_SINGLE_NUMBER_INDICATOR;
            flagsOfNumber = ETrue;
            iListBox = new( ELeave ) CAknSingleNumberStyleListBox();
            break;
        case EAknExListCmdOutline08: // OUTLINE08 screen.
            resourceId = R_AKNEXLIST_SINGLE_6;
            iListBox = new( ELeave ) CAknSingleStyleListBox();
            break;
        case EAknExListCmdOutline09: // OUTLINE09 screen.
            resourceId = R_AKNEXLIST_SINGLE_1;
            iListBox = new( ELeave ) CAknSingleStyleListBox();
            break;
        case EAknExListCmdOutline10: // OUTLINE10 screen.
            resourceId = R_AKNEXLIST_SINGLE_NUMBER;
            if ( tabGroup ) // Is tab group created?
                {
                flagsOfNumber = ETrue;
                }
            else
                {
                messageId = R_AKNEXLIST_USER_DEFINED_NUMBERING_MSG;
                }
            iListBox = new( ELeave ) CAknSingleNumberStyleListBox();
            break;
        case EAknExListCmdOutline11: // OUTLINE11 screen.
            resourceId = R_AKNEXLIST_SINGLE_HEADING;
            iListBox = new( ELeave ) CAknSingleHeadingStyleListBox();
            break;
        case EAknExListCmdOutline12: // OUTLINE12 screen.
            resourceId = R_AKNEXLIST_SINGLE_GRAPHIC;
            flagsOfGraphic = ETrue;
            iListBox = new( ELeave ) CAknSingleGraphicStyleListBox();
            break;
        case EAknExListCmdOutline13: // OUTLINE13 screen.
            resourceId = R_AKNEXLIST_SINGLE_GRAPHIC_HEADING;
            flagsOfGraphic = ETrue;
            iListBox = new( ELeave ) CAknSingleGraphicHeadingStyleListBox();
            break;
        case EAknExListCmdOutline14: // OUTLINE14 screen.
            resourceId = R_AKNEXLIST_SINGLE_NUMBER_HEADING;
            if ( tabGroup ) // Is tab group created?
                {
                flagsOfNumber = ETrue;
                }
            else
                {
                messageId = R_AKNEXLIST_USER_DEFINED_NUMBERING_MSG;
                }
            iListBox = new( ELeave ) CAknSingleNumberHeadingStyleListBox();
            break;
        case EAknExListCmdOutline15: // OUTLINE15 screen.
            resourceId = R_AKNEXLIST_SINGLE_LARGE_GRAPHIC;
            flagsOfGraphic = ETrue;
            iListBox = new( ELeave ) CAknSingleLargeStyleListBox();
            break;
        case EAknExListCmdOutline27: // OUTLINE27 screen.
            resourceId = R_AKNEXLIST_SINGLE_1;
            iListBox = new( ELeave ) CAknSingleStyleListBox();
            iListBox->SetListBoxObserver( this );
            break;
        case EAknExListCmdOutline30T1: // Type1 of OUTLINE30 screen.
            resourceId = R_AKNEXLIST_SINGLE_GRAPHIC_MULTI;
            flagsOfGraphic = ETrue;
            iListBox = new( ELeave ) CAknSingleGraphicStyleListBox();
            break;
        case EAknExListCmdOutline30T2: // Type2 of OUTLINE30 screen.
            resourceId = R_AKNEXLIST_SINGLE_GRAPHIC_HEADING_MULTI;
            flagsOfGraphic = ETrue;
            iListBox = new( ELeave ) CAknSingleGraphicHeadingStyleListBox();
            break;
        case EAknExListCmdOutline31: // OUTLINE33 screen.
            resourceId = R_AKNEXLIST_SINGLE_GRAPHIC_MULTI;
            flagsOfGraphic = ETrue;
            iListBox = new( ELeave ) CAknSingleGraphicStyleListBox();
            break;
        case EAknExListCmdOutline33: // OUTLINE33 screen.
            resourceId = R_AKNEXLIST_SINGLE_2;
            flagsOfGraphic = ETrue;
            iListBox = new( ELeave ) CAknSingleStyleListBox();
            break;
        case EAknExListCmdOutline41T1: // Fixed findbox of OUTLINE41 screen.
            resourceId = R_AKNEXLIST_SINGLE_GRAPHIC;
            flagsOfGraphic = ETrue;
            flagsOfFindBox = ETrue;
            iListBox = new( ELeave ) CAknSingleGraphicStyleListBox();
            break;
        case EAknExListCmdOutline41T2: // Popup findbox of OUTLINE41 screen.
            resourceId = R_AKNEXLIST_SINGLE_1;
            flagsOfFindBox = ETrue;
            flagsOfPopup = ETrue;
            iListBox = new( ELeave ) CAknSingleStyleListBox();
            break;
        case EAknExListCmdOutline43: // OUTLINE43 screen.
            resourceId = R_AKNEXLIST_LAYOUT1;
            flagsOfGraphic = ETrue;
            iListBox = new( ELeave ) CAknSingleGraphicHeadingStyleListBox();
            break;
        case EAknExListCmdOutline44: // OUTLINE44 screen.
            resourceId = R_AKNEXLIST_SINGLE_5;
            flagsOfGraphic = ETrue;
            iListBox = new( ELeave ) CAknSingleStyleListBox();
            break;
        case EAknExListCmdOutline45: // OUTLINE45 screen.
            resourceId = R_AKNEXLIST_LAYOUT2;
            flagsOfGraphic = ETrue;
            iListBox = new( ELeave ) CAknSingleGraphicHeadingStyleListBox();
            break;
        case EAknExListCmdOutline46: // OUTLINE46 screen.
            resourceId = R_AKNEXLIST_SINGLE_1;
            iListBox = new( ELeave ) CAknSingleStyleListBox();
            break;
        case EAknExListCmdOutline47: // OUTLINE47 screen.
            resourceId = R_AKNEXLIST_SINGLE_NUMBER;
            flagsOfNumber = ETrue;
            iListBox = new( ELeave ) CAknSingleNumberStyleListBox();
            break;
        case EAknExListCmdOutline48: // OUTLINE48 screen.
            resourceId = R_AKNEXLIST_SINGLE_HEADING;
            iListBox = new( ELeave ) CAknSingleHeadingStyleListBox();
            break;
        case EAknExListCmdOutline49: // OUTLINE49 screen.
            resourceId = R_AKNEXLIST_SINGLE_GRAPHIC;
            flagsOfGraphic = ETrue;
            iListBox = new( ELeave ) CAknSingleGraphicStyleListBox();
            break;
        case EAknExListCmdOutline50: // OUTLINE50 screen.
            resourceId = R_AKNEXLIST_SINGLE_GRAPHIC_HEADING;
            flagsOfGraphic = ETrue;
            iListBox = new( ELeave ) CAknSingleGraphicHeadingStyleListBox();
            break;
        case EAknExListCmdOutline51: // OUTLINE51 screen.
            resourceId = R_AKNEXLIST_SINGLE_NUMBER_HEADING;
            flagsOfNumber = ETrue;
            iListBox = new( ELeave ) CAknSingleNumberHeadingStyleListBox();
            break;
        case EAknExListCmdOutline52: // OUTLINE52 screen.
            resourceId = R_AKNEXLIST_SINGLE_LARGE_GRAPHIC;
            flagsOfGraphic = ETrue;
            iListBox = new( ELeave ) CAknSingleLargeStyleListBox();
            break;
        case EAknExListCmdOutline60: // OUTLINE60 screen.
            resourceId = R_AKNEXLIST_SINGLE_1;
            iListBox = new( ELeave ) CAknSingleStyleListBox();
            break;
        case EAknExListCmdOutline61: // OUTLINE61 screen.
            resourceId = R_AKNEXLIST_SINGLE_1;
            iListBox = new( ELeave ) CAknSingleStyleListBox();
            break;
        case EAknExListCmdOutline62: // OUTLINE62 screen.
            resourceId = R_AKNEXLIST_SINGLE_1;
            iListBox = new( ELeave ) CAknSingleStyleListBox();
            break;
        case EAknExListCmdOutline63: // OUTLINE63 screen.
            resourceId = R_AKNEXLIST_SINGLE_GRAPHIC;
            flagsOfGraphic = ETrue;
            flagsOfFindBox = ETrue;
            iListBox = new( ELeave ) CAknSingleGraphicStyleListBox();
            break;
        case EAknExListCmdOutline64: // OUTLINE64 screen.
            iListBox = new( ELeave ) CAknSingleStyleListBox();
            break;
        case EAknExListCmdOutline66: // OUTLINE66 screen.
            resourceId = R_AKNEXLIST_SINGLE_1;
            iListBox = new( ELeave ) CAknSingleStyleListBox();
            break;
        case EAknExListCmdOutline69: // OUTLINE69 screen.
            emptyResourceId = R_AKNEXLIST_EMPTY_LABEL;
            iListBox = new( ELeave ) CAknSingleStyleListBox();
            break;
        case EAknExListCmdOutline70: // OUTLINE70 screen.
            emptyResourceId = R_AKNEXLIST_TWO_LINES_EMPTY_LABEL;
            iListBox = new( ELeave ) CAknSingleStyleListBox();
            break;
        case EAknExListCmdOutline77: // OUTLINE77 screen.
            resourceId = R_AKNEXLIST_SINGLE_1;
            iListBox = new( ELeave ) CAknSingleStyleListBox();
            break;
        case EAknExListCmdOutline78: // OUTLINE78 screen.
            resourceId = R_AKNEXLIST_SINGLE_GRAPHIC_MULTI;
            flagsOfGraphic = ETrue;
            iListBox = new( ELeave ) CAknSingleGraphicStyleListBox();
            break;
        case EAknExListCmdOutline80: // OUTLINE80 screen.
            resourceId = R_AKNEXLIST_SINGLE_7;
            iListBox = new( ELeave ) CAknSingleStyleListBox();
            iListBox->SetListBoxObserver( this );
            break;
        case EAknExListCmdOutline80Sub: // Sub of OUTLINE80 screen.
            resourceId = R_AKNEXLIST_SINGLE_SUB;
            iListBox = new( ELeave ) CAknSingleStyleListBox();
            iListBox->SetListBoxObserver( this );
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
            // Sets style of findbox.
            CAknSearchField::TSearchFieldStyle style(
                CAknSearchField::ESearch );
            if ( flagsOfPopup )
                {
                style = CAknSearchField::EPopup;
                }

            // Creates FindBox.
            iFindBox = CreateFindBoxL( iListBox, iListBox->Model(), style );

            if ( iFindBox && style == CAknSearchField::EPopup )
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


        //ActivateL();
        iListBox->ActivateL();

        if ( iFindBox && flagsOfPopup )
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
// TKeyResponse CAknExListColumnContainer::OfferKeyEventL( const TKeyEvent&,
//  TEventCode )
// Handles the key events.
// ----------------------------------------------------------------------------
//
TKeyResponse CAknExListColumnContainer::OfferKeyEventL(
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
        case EAknExListCmdOutline66:
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
        case EAknExListCmdOutline44:
            {
            if (charCode == AKNEXLIST_ICONPRIORITY_KEY)
                {
                // Confirms priority of additional icons.
                AdditionalIconPriorityL();
                return EKeyWasConsumed;
                }
            break;
            }
        case EAknExListCmdOutline10:
        case EAknExListCmdOutline14:
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
        case EAknExListCmdOutline30T1:
        case EAknExListCmdOutline30T2:
        case EAknExListCmdOutline31:
            {
            if (charCode == AKNEXLIST_MARKEDINDEX_KEY)
                {
                // Displays message of marked item index.
                if (iListBox)
                    {
                    InfoMarkedItemIndexL(iListBox->SelectionIndexes());
                    }
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
            TBool flagsOfPopup( EFalse );

            if ( iOutlineId == EAknExListCmdOutline41T2 )
                {
                flagsOfPopup = ETrue;
                }

            // Offers the key event to find box.
            if ( AknFind::HandleFindOfferKeyEventL( aKeyEvent, aType, this,
                                                    iListBox, iFindBox,
                                                    flagsOfPopup,
                                                    needRefresh ) ==
                EKeyWasConsumed )
                {
                if ( needRefresh )
                    {
                    SizeChangedForFindBox();
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
// void CAknExListColumnContainer::HandleListBoxEventL( CEikListBox*,
//  TListBoxEvent )
// Handles listbox event.
// ----------------------------------------------------------------------------
void CAknExListColumnContainer::HandleListBoxEventL(
    CEikListBox* /*aListBox*/,
    TListBoxEvent aEventType )
    {
    if ( ( aEventType == MEikListBoxObserver::EEventEnterKeyPressed ) ||
         ( aEventType == MEikListBoxObserver::EEventItemClicked ) )
        {
        if ( iOutlineId == EAknExListCmdOutline27 )
            {
            // Displays information message.
            InfoMessage( R_AKNEXLIST_ITEM_OPEN );
            }
        else if ( iOutlineId == EAknExListCmdOutline80 )
            {
            // Gets current selected item index.
            TInt currentItem( iListBox->CurrentItemIndex() );

            switch ( currentItem )
                {
                case EKAknExListItemIndex0:
                    {
                    // Displays information message.
                    InfoMessage( R_AKNEXLIST_ITEM_OPEN );
                    }
                    break;
                case EKAknExListItemIndex1:
                    // Displays Sub of OUTLINE80 screen.
                    DisplayListBoxL( EAknExListCmdOutline80Sub );
                    break;
                default:
                    break;
                }
            }
        else if ( iOutlineId == EAknExListCmdOutline80Sub )
            {
            // Gets current selected item index.
            TInt currentItem( iListBox->CurrentItemIndex() );

            if ( currentItem == EKAknExListItemIndex0 )
                {
                // Displays OUTLINE80 screen.
                DisplayListBoxL( EAknExListCmdOutline80 );
                }
            }
        }
    }



// ----------------------------------------------------------------------------
// void CAknExListColumnContainer::SetLabelL( const TInt )
// Creates and sets label control object.
// ----------------------------------------------------------------------------
//
void CAknExListColumnContainer::SetLabelL( const TInt aResourceId )
    {
    // Sets start screen label.
    if ( !iLabel )
        {
        TBuf<KAknExListLabelBufLength> initFormat( 0 );
        iCoeEnv->ReadResource( initFormat, aResourceId );
        iLabel = new( ELeave ) CEikLabel();
        iLabel->SetContainerWindowL( *this );
        iLabel->SetTextL( initFormat );
        iLabel->SetFont( LatinBold19() );
        iLabel->SetAlignment( EHCenterVCenter );
        SizeChanged();
        }
    }

// ----------------------------------------------------------------------------
// void CAknExListColumnContainer::GraphicIconL( CArrayPtr<CGulIcon>* )
// Appends graphics data.
// ----------------------------------------------------------------------------
//
void CAknExListColumnContainer::GraphicIconL( CArrayPtr<CGulIcon>* aIcons )
    {
    if ( aIcons )
        {
        // Appends icon according to iOutlineId.
        switch ( iOutlineId )
            {
            case EAknExListCmdOutline12:
            case EAknExListCmdOutline13:
            case EAknExListCmdOutline30T1:
            case EAknExListCmdOutline30T2:
            case EAknExListCmdOutline33:
            case EAknExListCmdOutline41T1:
            case EAknExListCmdOutline45:
            case EAknExListCmdOutline49:
            case EAknExListCmdOutline50:
            case EAknExListCmdOutline63:
            case EAknExListCmdOutline78:
                aIcons->AppendL( iEikonEnv->CreateIconL( KAknExListMbmFileName,
                                                         EMbmAknexlistMarked_add,
                                                         EMbmAknexlistMarked_add_m ) );
                aIcons->AppendL(
                    iEikonEnv->CreateIconL( KAknExListMbmFileName,
                                            EMbmAknexlistGolgo3,
                                            EMbmAknexlistGolgo3m ) );
                break;
            case EAknExListCmdOutline15:
            case EAknExListCmdOutline52:
                aIcons->AppendL( iEikonEnv->CreateIconL( KAknExListMbmFileName,
                                                         EMbmAknexlistMarked_add,
                                                         EMbmAknexlistMarked_add_m ) );
                aIcons->AppendL(
                    iEikonEnv->CreateIconL( KAknExListMbmFileName,
                                            EMbmAknexlistGolgo2,
                                            EMbmAknexlistGolgo2m ) );
                break;
            case EAknExListCmdOutline44:
                aIcons->AppendL( iEikonEnv->CreateIconL( KAknExListMbmFileName,
                                                         EMbmAknexlistMarked_add,
                                                         EMbmAknexlistMarked_add_m ) );
                aIcons->AppendL(
                    iEikonEnv->CreateIconL( KAknExListMbmFileName,
                                            EMbmAknexlistGolgo4,
                                            EMbmAknexlistGolgo4m ) );
                aIcons->AppendL(
                    iEikonEnv->CreateIconL( KAknExListMbmFileName,
                                            EMbmAknexlistGolgo5,
                                            EMbmAknexlistGolgo5m ) );
                aIcons->AppendL(
                    iEikonEnv->CreateIconL( KAknExListMbmFileName,
                                            EMbmAknexlistGolgo6,
                                            EMbmAknexlistGolgo6m ) );
                break;
            case EAknExListCmdOutline43:
                aIcons->AppendL( iEikonEnv->CreateIconL( KAknExListMbmFileName,
                                                         EMbmAknexlistMarked_add,
                                                         EMbmAknexlistMarked_add_m ) );
                aIcons->AppendL(
                    iEikonEnv->CreateIconL( KAknExListMbmFileName,
                                            EMbmAknexlistGolgo3,
                                            EMbmAknexlistGolgo3m ) );
                aIcons->AppendL(
                    iEikonEnv->CreateIconL( KAknExListMbmFileName,
                                            EMbmAknexlistAthene,
                                            EMbmAknexlistAthenem ) );
                break;
            case EAknExListCmdOutline31:
                // Appends icon.
                aIcons->AppendL( iEikonEnv->CreateIconL( KAknExListMbmFileName,
                                                 EMbmAknexlistCheck,
                                                 EMbmAknexlistCheckm ) );
                // Appends icon.
                aIcons->AppendL( iEikonEnv->CreateIconL( KAknExListMbmFileName,
                                                 EMbmAknexlistNon_check,
                                                 EMbmAknexlistNon_checkm ) );
                break;
            default:
                break;
            }
        }
    }

// ----------------------------------------------------------------------------
// void CAknExListColumnContainer::SetCountAndAddItemL( const TKeyEvent& )
// Sets count of added list items and calls AddItemL().
// ----------------------------------------------------------------------------
//
void CAknExListColumnContainer::SetCountAndAddItemL(
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
            AddItemL( iListBox, model, addCount, R_AKNEXLIST_ADD_ITEM_SINGLE );

            // Displays information for total number of list items.
            CountMessage( model );
            }
        }
    }

// ----------------------------------------------------------------------------
// void CAknExListColumnContainer::SetCountAndRemoveItemL( const TKeyEvent& )
// Sets count of removed list items and calls RemoveItemL().
// ----------------------------------------------------------------------------
//
void CAknExListColumnContainer::SetCountAndRemoveItemL(
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
// void CAknExListColumnContainer::AdditionalIconPriorityL()
// Confirms priority of additional icons.
// ----------------------------------------------------------------------------
//
void CAknExListColumnContainer::AdditionalIconPriorityL()
    {
    if ( iListBox )
        {
        // Gets current item.
        TInt currentItem( iListBox->CurrentItemIndex() );
        MDesCArray* itemList = iListBox->Model()->ItemTextArray();
        CDesCArray* itemArray = STATIC_CAST( CDesCArray* ,itemList );
        TPtrC item( ( *itemArray )[currentItem] );

        // Gets position and count of tab.
        TBuf<KAknExListTabBufLength> tab( 0 );
        iCoeEnv->ReadResource( tab, R_AKNEXLIST_TAB );
        TInt oldPosition( item.Find( tab ) );
        TInt count( KAknExListInitTabCount );
        TInt position( KAknExListInitPosition );

        while ( oldPosition != KErrNotFound )
            {
            count++;
            position += oldPosition;
            oldPosition = item.Mid( ++position ).Find( tab );
            }

        // Sets number of additional icons.
        TInt iconNumber( KErrNotFound );

        switch ( count )
            {
            case EKAknExListFirstPriority:
                iconNumber = EKAknExListFirstIconIndex;
                break;
            case EKAknExListSecondPriority:
                iconNumber = EKAknExListSecondIconIndex;
                break;
            case EKAknExListThirdPriority:
                iconNumber = EKAknExListThirdIconIndex;
                break;
            default:
                break;
            }

        if ( iconNumber != KErrNotFound )
            {
            // Update new item.
            TBuf<KAknExListItemBufLength> newItem( 0 );
            newItem.Copy( item );
            newItem.Append( tab );
            newItem.AppendNum( iconNumber );
            itemArray->Delete( currentItem );
            itemArray->InsertL( currentItem, newItem );
            iListBox->View()->DrawItem( currentItem );
            }

        if ( count > EKAknExListSecondPriority )
            {
            InfoMessage( R_AKNEXLIST_MSG ); // Displays information message.
            }
        }
    }


// ----------------------------------------------------------------------------
// void CAknExListColumnContainer::SizeChangedForFindBox()
// Called by framework when the view size is changed for creating listbox with
// findbox.
// ----------------------------------------------------------------------------
//
void CAknExListColumnContainer::SizeChangedForFindBox()
    {
    if ( iListBox && iFindBox )
        {
        // Initialize of resource ID for layout of findbox(These initial
        // values are layout for fixed findbox).
        TInt findWindowResourceId( R_AVKON_FIND_PANE );
        TInt listAreaResourceId( R_AVKON_LIST_GEN_PANE_X );
        TInt findWindowParentId( R_AVKON_MAIN_PANE_PARENT_NONE );
        TBool flagsOfPopup( EFalse ); // Flag for find popup.

        switch ( iOutlineId ) // Outline ID is...
            {
            case EAknExListCmdOutline41T2: // Layout for find popup.
                findWindowResourceId = R_AVKON_POPUP_FIND_WINDOW;
                listAreaResourceId = R_AVKON_LIST_GEN_PANE;
                findWindowParentId = R_AVKON_MAIN_PANE_WITH_STATUS_PANE;
                flagsOfPopup = ETrue;
                break;
            default:
                break;
            }

        // Calls HandleFindSizeChanged after creates findbox.
        AknFind::HandleFindSizeChanged(
            this, iListBox, iFindBox, flagsOfPopup, findWindowResourceId,
            listAreaResourceId, R_AVKON_LIST_GEN_PANE_WITH_FIND_POPUP,
            findWindowParentId );
        }
    }

// ----------------------------------------------------------------------------
// void CAknExListColumnContainer::SizeChanged()
// Called by framework when the view size is changed.
// ----------------------------------------------------------------------------
//
void CAknExListColumnContainer::SizeChanged()
    {
    if ( iLabel )
        {
        iLabel->SetRect( Rect() );
        }

    if ( iListBox )
        {
        if ( iFindBox )
            {
            SizeChangedForFindBox(); // Sets rectangle of listbox with findbox.
            }
        else
            {
            iListBox->SetRect( Rect() ); // Sets rectangle of listbox.
            }
        }
    }

// ----------------------------------------------------------------------------
// TInt CAknExListColumnContainer::CountComponentControls() const
// Returns number of components.
// ----------------------------------------------------------------------------
//
TInt CAknExListColumnContainer::CountComponentControls() const
    {
    TInt count( KAknExListInitCount );

    if ( iLabel )
        {
        count++;
        }

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
// CCoeControl* CAknExListColumnContainer::ComponentControl( TInt ) const
// Returns pointer to particular component.
// ----------------------------------------------------------------------------
//
CCoeControl* CAknExListColumnContainer::ComponentControl( TInt aIndex ) const
    {
    switch ( aIndex )
        {
        case EAknExListDefaultComponent:
            if ( iLabel )
                {
                return iLabel; // Returns the pointer to label object.
                }
            else if ( iListBox )
                {
                return iListBox; // Returns the pointer to listbox object.
                }
            return iFindBox; // Returns the pointer to findbox object.
        case EAknExListComponent1:
            if ( iFindBox )
                {
                return iFindBox; // Returns the pointer to findbox object.
                }
            return iListBox; // Returns the pointer to listbox object.
        case EAknExListComponent2:
            return iListBox; // Returns the pointer to listbox object.
        default:
            return NULL; // Exception : Returns NULL.
        }
    }

// End of File
