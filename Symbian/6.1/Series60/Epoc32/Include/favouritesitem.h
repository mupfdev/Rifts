/*
* ============================================================================
*  Name     : FavouritesItem.h
*  Part of  : Favourites Engine
*
*  Description:
*      Declaration of class CFavouritesItem.
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

#ifndef FAVOURITES_ITEM_H
#define FAVOURITES_ITEM_H

//  INCLUDES

#include <e32base.h>
#include <s32strm.h>
#include <FavouritesLimits.h>
#include <FavouritesWapAp.h>

// CLASS DECLARATION

/**
* Base class for representing one WAP favourites entry (item or folder).
* Instances of this class are used to exchange data between the Favourites
* Engine and clients using it.
*/
class CFavouritesItem: public CBase
    {

    public:     // Data types

        enum TType  /// Type of an item (item or folder).
            {
            ENone,  ///< Invalid value, cannot be set for a CFavouritesItem.
            EItem,  ///< Favourites item.
            EFolder ///< Favourites folder.
            };

    public:     // Constructors and destructor
        
        /**
        * Two-phased constructor. Leaves on failure. Places the instance on the
        * cleanup stack.
        * @return The constructed item.
        */
        IMPORT_C static CFavouritesItem* NewLC();

        /**
        * Two-phased constructor. Leaves on failure.
        * @return The constructed item.
        */
        IMPORT_C static CFavouritesItem* NewL();

        /**
        * Destructor.
        */
        IMPORT_C virtual ~CFavouritesItem();

        /**
        * Assignment operator.
        */
        IMPORT_C CFavouritesItem& operator= ( const CFavouritesItem& );

    protected:      // Constructors
        
        /**
        * C++ constructor.
        */
        IMPORT_C CFavouritesItem();

        /**
        * Second-phase constructor.
        */
        IMPORT_C void ConstructL();

    public:     // Query

        /**
        * Get unique id of the item.
        * @return The unique id.
        */
        IMPORT_C TInt Uid() const;

        /**
        * Get the uid of the parent folder of this item.
        * @return The unique id of the parent folder.
        */
        IMPORT_C TInt ParentFolder() const;

        /**
        * Get type of the item (item or folder).
        * @return The type of the item. It is either EFolder or EItem
        * (never ENone).
        */

        IMPORT_C TType Type() const;

        /**
        * Get the name of this item.
        * @return The name of this item.
        */
        IMPORT_C const TDesC& Name() const;

        /**
        * Get the URL of this item.
        * @return The URL of this item.
        */
        IMPORT_C const TDesC& Url() const;

        /**
        * Get WAP Access Point id associated with this item.
        * @return The WAP Access Point id.
        */
        IMPORT_C TFavouritesWapAp WapAp() const;

        /**
        * Get the username associated with this item.
        * @return The username.
        */
        IMPORT_C const TDesC& UserName() const;

        /**
        * Get password associated with this item.
        * @return The password.
        */
        IMPORT_C const TDesC& Password() const;

        /**
        * Check if this item is the Homepage.
        * @return ETrue if this is the Homepage.
        */
        IMPORT_C TBool IsHomepage() const;

        /**
        * Check if this is the Last Visited one.
        * @return ETrue if this is the Last Visited one.
        */
        IMPORT_C TBool IsLastVisited() const;

        /**
        * Check if this is an item (not folder).
        * @return ETrue if this is an item.
        */
        IMPORT_C TBool IsItem() const;

        /**
        * Check if this is a folder.
        * @return ETrue if this is a folder.
        */
        IMPORT_C TBool IsFolder() const;

    public:     // update

        /**
        * Reset the item to default values.
        */
        IMPORT_C void ClearL();

        /**
        * Set parent folder.
        * @param aId The unique id of the parent folder.
        */
        IMPORT_C void SetParentFolder( TInt aId );

        /**
        * Set item type (item or folder).
        * @param aType The type to be set. ENone cannot be set (if that is
        * specified, it is ignored).
        */
        IMPORT_C void SetType( TType aType );

        /**
        * Set name of the item. Any whitespace character (tabs, newline etc.)
        * is replaced by a space; any leading or trailing whitespace is removed
        * (without returning an error). The the (remaining) name may be
        * truncated if longer than KFavouritesMaxName. 
        * @param aName The name to be set.
        * @return KErrNone on success.
        * KErrOverflow if the name was truncated to KFavouritesMaxName length.
        */
        IMPORT_C TInt SetNameL( const TDesC& aName );

        /**
        * Set URL of the item. The URL may be truncated
        * if longer than KFavouritesMaxURL.
        * @param aUrl The URL to be set.
        * @return KErrNone on success.
        * KErrOverflow if the name was truncated to KFavouritesMaxName length.
        */
        IMPORT_C TInt SetUrlL( const TDesC& aUrl );

        /**
        * Set WAP Access Point of the item.
        * @param aAccessPoint The WAP Access point to be set.
        */
        IMPORT_C void SetWapAp( const TFavouritesWapAp& aAccessPoint );

        /**
        * Set username of the item. The username may be truncated
        * if longer than KFavouritesMaxUserName.
        * @param aUserName The username to be set.
        * @return
        *   - KErrNone on success.
        *   - KErrOverflow if the name was truncated to KFavouritesMaxUserName length.
        */
        IMPORT_C TInt SetUserNameL( const TDesC& aUserName );

        /**
        * Set password. The name may be truncated
        * if longer than KFavouritesMaxPassword.
        * @param aPassword The password to be set.
        * @return
        *   - KErrNone on success.
        *   - KErrOverflow if the name was truncated to
        *     KFavouritesMaxPassword length.
        */
        IMPORT_C TInt SetPasswordL( const TDesC& aPassword );

    private:

        /**
        * Set unique id of the item.
        * @param aUid The unique id to be set.
        */
        void SetUid( TInt aUid );

        /**
        * Validate the item.
        * For all kinds: name must be present.
        * For items: URL must be present.
        * For folders: URL, Username, Password must be empty;
        * WAP Access Point must not be specified.
        * @return ETrue if the item matches the above criteria.
        */
        TBool IsValidL() const;

        /**
        * Create a bookmark name from a string; the resulting name is valid
        * unless empty.
        * Any non-space whitespace character is converted to a space.
        * Leading / trailing whitespace is removed. Note that the resulting
        * name may be zero length (if aSource is made up from whitespace only).
        * In this case the return value is KErrNone, though the name is not
        * valid.
        * @param aSource The string to create name from.
        * @param aTarget Resulting name is placed here. Previous content is
        * overwritten. Must be large enough to hold the result;
        * the result's length equals to or less than aSource length (i.e.
        * aSource.Length() is enough for aTarget).
        * @return
        * - KErrOverflow if name was trimmed (because it was too long);
        * - KErrNone otherwise.
        */
        static TInt MakeName( const TDesC& aSource, TDes& aTarget );

    protected:  // Reserved for future use

        /**
        * Reserved for future use.
        * @param aDummy Dummy argument.
        */
        IMPORT_C void virtual Reserved( TAny* aDummy );
    
    private:      // Data

        TInt iUid;                  ///< Uid of the item.
        TInt iParentFolder;         ///< Uid of the parent folder.
        TType iType;                ///< Favourites type (EFolder or EItem).
        HBufC* iName;               ///< Name, owned. Never NULL.
        HBufC* iUrl;                ///< URL, owned. Never NULL.
        TFavouritesWapAp iWapAp;    ///< WAP Access Point.
        HBufC* iUserName;           ///< Username, owned. Never NULL.
        HBufC* iPassword;           ///< Password, owned. Never NULL.

    public:     // Friend classes

        /// Setting Uid is granted for this.
        friend class CFavouritesDb;
        /// Setting Uid is granted for this.
        friend class RFavouritesTable;

    private:    // Reserved for future use.

        TAny* iReserved;            ///< Reserved for future use.
    };

#endif
            
// End of File
