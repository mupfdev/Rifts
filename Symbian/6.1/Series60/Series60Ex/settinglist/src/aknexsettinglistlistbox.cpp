/*
* =============================================================================
*  Name     : CAknExSettingListListbox
*  Part of  : AknExSettingList
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include "AknExSettingListListbox.h"
#include "AknExSettingListItemData.h"
#include "AknExSettingList.hrh"
#include "AknExSettingListView.h"


// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExSettingListListbox::CreateSettingItemL
// Updates descripter array for list box
// ----------------------------------------------------------------------------
//
CAknSettingItem* CAknExSettingListListbox::CreateSettingItemL( TInt aIdentifier )
    {
    CAknSettingItem* settingItem = NULL;

    switch (aIdentifier)
    {
    case EAknExSettingText:
        settingItem = new (ELeave) 
            CAknTextSettingItem(aIdentifier, iData->iTextBuf );
        break;
    case EAknExSettingVolume:
        settingItem = new (ELeave) 
            CAknVolumeSettingItem(aIdentifier, iData->iVolume );
        break;
    case EAknExSettingEnumText:
        settingItem = new (ELeave) CAknEnumeratedTextPopupSettingItem(
            aIdentifier, iData->iLanguageCode );
        break;
    case EAknExSettingSlider:
        settingItem = new (ELeave) 
            CAknSliderSettingItem(aIdentifier, iData->iSliderValue );
        break;
    case EAknExSettingDate:
        settingItem = new (ELeave) CAknTimeOrDateSettingItem(aIdentifier, 
            CAknTimeOrDateSettingItem::EDate, iData->iDate );
        break;
    case EAknExSettingTime:
        settingItem = new (ELeave) CAknTimeOrDateSettingItem(aIdentifier, 
            CAknTimeOrDateSettingItem::ETime, iData->iTime );
        break;
    case EAknExSettingBinary:
        settingItem = new (ELeave) 
            CAknBinaryPopupSettingItem(aIdentifier, iData->iBinary );
        break;
    case EAknExSettingPassAlph:
        settingItem = new (ELeave) CAknPasswordSettingItem(aIdentifier, 
            CAknPasswordSettingItem::EAlpha, iData->iPw );
        break;
    case EAknExSettingPassNumber:
        settingItem = new (ELeave) CAknPasswordSettingItem(aIdentifier, 
            CAknPasswordSettingItem::ENumeric, iData->iPin );
        break;
    case EAknExSettingIpAddress:
        settingItem = new (ELeave) 
            CAknIpFieldSettingItem( aIdentifier, iData->iIpAddress );
        break;
    default:
        break;
        }
    return settingItem;
    }

// ----------------------------------------------------------------------------
// CAknExSettingListListbox::SetData
// 
// ----------------------------------------------------------------------------
//
void CAknExSettingListListbox::SetData(CAknExSettingListItemData* aData)
    {
    iData = aData;
    }

// ----------------------------------------------------------------------------
// CAknExSettingListListbox::SetView
// 
// ----------------------------------------------------------------------------
//
void CAknExSettingListListbox::SetView(CAknExSettingListView* aView)
    {
    iView = aView;
    }

// ----------------------------------------------------------------------------
// TKeyResponse CAknExSettingListListbox::OfferKeyEventL( const TKeyEvent&,
//  TEventCode )
// Handles the key events.
// ----------------------------------------------------------------------------
//
TKeyResponse CAknExSettingListListbox::OfferKeyEventL(
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
        case EKeyRightArrow:
            // Display next outline screen.
            iView->SetCurrentOutlineId ( iView->CurrentOutlineId() ) ;
            iView->DisplayNextOutlineL();
            break;
        case EKeyLeftArrow:
            // Display previous outline screen.
            iView->SetCurrentOutlineId ( iView->CurrentOutlineId() ) ;
            iView->DisplayPreviousOutlineL();
            break;
        default:
            CAknSettingItemList::OfferKeyEventL(aKeyEvent, aType);
            break;
        }
    return EKeyWasConsumed;
    }

// ----------------------------------------------------------------------------
// CAknExSettingListListbox::SizeChanged
// Size changed handler
// ----------------------------------------------------------------------------
//
void CAknExSettingListListbox::SizeChanged()
    {
    if (ListBox()) 
        {
        ListBox()->SetRect(Rect());
        }
    }

// End of File
