/*
* ============================================================================
*  Name     : AknExSettingListListBox.h
*  Part of  : AknExSettingList
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNEXSETTINGLISTLISTBOX_H
#define AKNEXSETTINGLISTLISTBOX_H

// INCLUDES
#include <AknSettingItemList.h>

// FORWARD DECLARATIONS
class CAknExSettingListItemData;
class CAknExSettingListView;

// CLASS DECLARATION

/**
* CAknExSettingListContainer  container control class.
*/
class CAknExSettingListListbox : public CAknSettingItemList 
    {
    public:
        CAknSettingItem* CreateSettingItemL( TInt identifier );
        void SetData(CAknExSettingListItemData* aData);
        void SetView(CAknExSettingListView* aView);
        
    private:
        TKeyResponse OfferKeyEventL(
            const TKeyEvent& aKeyEvent, TEventCode aType );
        void SizeChanged();

    private:
        CAknExSettingListItemData* iData;
        CAknExSettingListView* iView;
    };


#endif

// End of File
