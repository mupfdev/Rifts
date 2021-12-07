/*
* =============================================================================
*  Name     : AknExListSetPage.h
*  Part of  : AknExList
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

#ifndef AKNEXLISTSETPAGE_H
#define AKNEXLISTSETPAGE_H

// INCLUDES
#include <AknSettingItemList.h>

// CONSTANTS

// FORWARD DECLARATIONS

// CLASS DECLARATION

/**
* CAknExListSetPage class.
*/
class CAknExListSetPage : public CAknSettingItemList
    {
    public: // Constructors and destructor
        /**
        * 2-phase constructor.
        * @param aResourceId : resource ID of setting page.
        */
        static CAknExListSetPage* NewL(TInt aResourceId);
        
        /**
        * Destructor.
        */
        virtual ~CAknExListSetPage();

    private: // Constructors and destructor
        /**
        * Default constructor.
        */
        CAknExListSetPage();

        /**
        * Second phase constructor.
        * @param aResourceId : resource ID of setting page.
        */
        void ConstructL(TInt aResourceId);
        
    private: // From CAknSettingItemList 
        /**
        * From CAknSettingItemList
        * Create items of setting page.
        * @param aSettingId : item ID.
        */
        CAknSettingItem* CreateSettingItemL(TInt aSettingId);
    
    private:
        TInt iValue;
    };

#endif // AKNEXLISTSETPAGE_H

// End of File
