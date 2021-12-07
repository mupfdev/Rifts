/*
* =============================================================================
*  Name     : CAknExListMarkContainer
*  Part of  : AknExList
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

// INCLUDE FILES
#include <aknlists.h> // for avrell style listbox
#include <akntabgrp.h>
#include <aknsfld.h>
#include <aknexlist.rsg>
#include <aknexlist.mbg>
#include "AknExList.hrh"
#include "AknExListConst.h"
#include "AknExListMarkView.h"
#include "AknExListMarkContainer.h"

// CONSTANTS
// for initialization.
const TInt KAknExListInitCount = 0;
// Key for re-opehing outline 83.
#define REOPENOUTLINE83LISTKEY '0'

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExListMarkContainer::CAknExListMarkContainer( CAknExListMarkView* )
// Copy constructor.
// ----------------------------------------------------------------------------
//
CAknExListMarkContainer::CAknExListMarkContainer(
    CAknExListMarkView* aView )
:   iListBox( NULL ),
    iView( aView ),
    iOutlineId( KAknExListInitOutlineId )
    {
    }

// ----------------------------------------------------------------------------
// void CAknExListMarkContainer::ConstructL( const TRect& )
// EPOC constructor.
// ----------------------------------------------------------------------------
//
void CAknExListMarkContainer::ConstructL( const TRect& aRect )
    {
    CreateWindowL(); // Creates window.
    SetRect( aRect ); // Sets rectangle of frame.
    ActivateL(); // Activates window. (Ready to draw)
    }

// ----------------------------------------------------------------------------
// CAknExListMarkContainer::~CAknExListMarkContainer()
// Destructor.
// ----------------------------------------------------------------------------
//
CAknExListMarkContainer::~CAknExListMarkContainer()
    {
    delete iListBox; // Deletes listbox object.
    delete iFindBox;
    }

// ----------------------------------------------------------------------------
// void CAknExListMarkContainer::DisplayListBoxL( const TInt )
// Displays listbox or start screen.
// ----------------------------------------------------------------------------
//
void CAknExListMarkContainer::DisplayListBoxL( const TInt aOutlineId )
    {
    // Sets outlineId.
    iOutlineId = aOutlineId;

    // Deletes listbox object.
    if ( iListBox )
        {
        delete iListBox;
        iListBox = NULL;
        }

    delete iFindBox;
    iFindBox = NULL;

    TInt resourceId( KAknExListInitListResourceId ); // For listbox.
    TBool isNeedFindBox(EFalse);

    // Creates ListBox control object and sets resource ID.
    switch ( iOutlineId ) // Outline ID is...
        {
        case EAknExListCmdOutline32: // OUTLINE32 screen.
        case EAknExListCmdOutline81: // OUTLINE81 screen.
        case EAknExListCmdOutline82: // OUTLINE82 screen.
        case EAknExListCmdOutline83: // OUTLINE83 screen.
        case EAknExListCmdOutline87: // OUTLINE87 screen.
            resourceId = R_AKNEXLIST_SINGLE_4;
            iListBox = new( ELeave ) CAknSingleStyleListBox();
            break;
        default:
            break;
        }

    if ( iListBox )
        {
        SetListBoxFromResourceL( iListBox, resourceId );

        //SizeChanged();

        // Creates graphic.
        SetGraphicIconL( iListBox );

        //iListBox->ActivateL();
        // Update scrollbar in order to draw correct scroll bar.
        UpdateScrollBar(iListBox);
        
        }

    if (isNeedFindBox)
        {
        iFindBox = CreateFindBoxL(iListBox, iListBox->Model(),
                                  CAknSearchField::ESearch);
        }

    SizeChanged();
    iListBox->ActivateL();
    DrawNow();
    }

// ----------------------------------------------------------------------------
// CEikListBox* CAknExListMarkContainer::ListBox()
// Returns pointer to listbox object.
// ----------------------------------------------------------------------------
//
CEikListBox* CAknExListMarkContainer::ListBox()
    {
    return iListBox;
    }

// ----------------------------------------------------------------------------
// TKeyResponse CAknExListMarkContainer::OfferKeyEventL( const TKeyEvent&,
//  TEventCode )
// Handles the key events.
// ----------------------------------------------------------------------------
//
TKeyResponse CAknExListMarkContainer::OfferKeyEventL(
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
            iView->DisplayNextOutlineL();
            return EKeyWasConsumed;
        case REOPENOUTLINE83LISTKEY:
            {
            if (iOutlineId == EAknExListCmdOutline83)
                {
                DisplayListBoxL(EAknExListCmdOutline83);
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
                                                    iListBox, iFindBox,
                                                    EFalse,
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
// void CAknExListColumnContainer::SizeChangedForFindBox()
// Called by framework when the view size is changed for creating listbox with
// findbox.
// ----------------------------------------------------------------------------
//
void CAknExListMarkContainer::SizeChangedForFindBox()
    {
    if ( iListBox && iFindBox )
        {
        CAknColumnListBox* aknListBox = STATIC_CAST(CAknColumnListBox*, iListBox);
        AknFind::HandleFixedFindSizeChanged(this, aknListBox, iFindBox);
        }
    }


// ----------------------------------------------------------------------------
// void CAknExListMarkContainer::GraphicIconL( CArrayPtr<CGulIcon>* )
// Appends graphics data.
// ----------------------------------------------------------------------------
//
void CAknExListMarkContainer::GraphicIconL( CArrayPtr<CGulIcon>* aIcons )
    {
    if ( aIcons )
        {
        // Appends icon according to iOutlineId.
        switch ( iOutlineId )
            {
            case EAknExListCmdOutline32:
            case EAknExListCmdOutline81:
            case EAknExListCmdOutline82:
            case EAknExListCmdOutline83:
            case EAknExListCmdOutline87:
                aIcons->AppendL( iEikonEnv->CreateIconL( KAknExListMbmFileName,
                                                         EMbmAknexlistMarked_add,
                                                         EMbmAknexlistMarked_add_m ) );
                break;
            default:
                break;
            }
        }
    }

// ----------------------------------------------------------------------------
// void CAknExListMarkContainer::SizeChanged()
// Called by framework when the view size is changed.
// ----------------------------------------------------------------------------
//
void CAknExListMarkContainer::SizeChanged()
    {
    if (iListBox)
        {
        if (iFindBox)
            {
            SizeChangedForFindBox();
            }
        else
            {
            iListBox->SetRect(Rect()); // Sets rectangle of lstbox.
            }
        }
    }

// ----------------------------------------------------------------------------
// TInt CAknExListMarkContainer::CountComponentControls() const
// Returns number of components.
// ----------------------------------------------------------------------------
//
TInt CAknExListMarkContainer::CountComponentControls() const
    {
    TInt count( KAknExListInitCount );

    if ( iListBox )
        {
        count++;
        }
    if (iFindBox)
        {
        count++;
        }

    return count; // Returns number of controls inside this container.
    }

// ----------------------------------------------------------------------------
// CCoeControl* CAknExListMarkContainer::ComponentControl( TInt ) const
// Returns pointer to particular component.
// ----------------------------------------------------------------------------
//
CCoeControl* CAknExListMarkContainer::ComponentControl( TInt aIndex ) const
    {
    switch ( aIndex )
        {
        case EAknExListDefaultComponent:
            return iListBox; // Returns the pointer to listbox object.
        case EAknExListFindBox:
            return iFindBox;
        default:
            return NULL; // Exception : Returns NULL.
        }
    }

// End of File
