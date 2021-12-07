/*
* ============================================================================
*  Name     : FavouritesItemList.h
*  Part of  : WmlBrowser
*
*  Description:
*      Declaration of class CFavouritesItemList.
*      
*  Version:
*
*  Copyright (C) 2002 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing,  adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
*
* ============================================================================
*/

#ifndef FAVOURITES_ITEM_LIST_H
#define FAVOURITES_ITEM_LIST_H

// INCLUDE FILES

#include <e32base.h>

// CONSTANTS

// FORWARD DECLARATION

class CFavouritesItem;

// CLASS DECLARATION

/**
* Array of CFavouritesItem-s. Items are owned and deleted upon destruction.
* Note: using this array downcasted to its base can result in leaks.
* Delete method of base class is not virtual!
*/
class CFavouritesItemList: public CArrayPtrFlat<CFavouritesItem>
    {
    public:     // Construct / destruct

        /**
        * Constructor.
        */
        IMPORT_C CFavouritesItemList();

        /**
        * Destructor. Elements are destroyed.
        */
        IMPORT_C virtual ~CFavouritesItemList();

    public:     // new methods

        /**
        * Remove and destroy an element. Invalid params will Panic.
        * @param aIndex Index of element to delete.
        */
        IMPORT_C void Delete( TInt aIndex );

        /**
        * Remove and destroy elements. Invalid params Panic.
        * @param aIndex Index of start element to delete.
        * &param aCount Number of items to delete.
        */
        IMPORT_C void Delete( TInt aIndex, TInt aCount );

    public:     // Sorting

        /**
        * Comparison function type; compare two items. Should leave in error.
        * @param aLeft item to compare to aRight.
        * @param aRight Item to compare to aLeft.
        * @return
        *   - negative value, if aLeft is less than aRight;
        *   - 0,              if aLeft equals to aRight;
        *   - positive value, if aLeft is greater than aRight.
        */
        typedef TInt (*ComparisonFuncL)
            ( const CFavouritesItem& aLeft, const CFavouritesItem& aRight );

        /**
        * Sort the list using bubble-sort.
        * @param aCompareItemsL Function to be used two elements.
        */
        IMPORT_C void SortL( ComparisonFuncL aCompareItemsL );

    public:     // Uid <--> array index conversion

        /**
        * Convert Uid to index.
        * @param aUid Uid to convert.
        * @return Index for this Uid, or -KErrNotFound if not found.
        */
        IMPORT_C TInt UidToIndex( TInt aUid ) const;

        /**
        * Convert index to Uid.
        * @param aIndex Index to convert.
        * @return Uid for this index, or KFavouritesNullUid if not found.
        */
        IMPORT_C TInt IndexToUid( TInt aIndex ) const;

        /**
        * Get pointer to item having aUid.
        * @param aUid Uid of item to look for.
        * @return Pointer to item having aUid, or NULL if there is no such
        * item. Item is still owned by the list.
        */
        IMPORT_C const CFavouritesItem* ItemByUid( TInt aUid ) const;

    };

#endif

// End of file
