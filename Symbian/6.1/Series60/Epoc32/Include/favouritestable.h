/*
* ============================================================================
*  Name     : FavouritesTable.h
*  Part of  : Favourites Engine
*
*  Description:
*      Declaration of class RFavouritesTable.
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

#ifndef FAVOURITES_TABLE_H
#define FAVOURITES_TABLE_H

//  INCLUDES

#include <e32base.h>
#include <d32dbms.h>
#include <FavouritesItem.h>

class MFavouritesItemData;

// CLASS DECLARATION

/**
* Database table for favourites data.
* This class provides the way to access / manipulate database tables, which
* store favourites data in the table structure defined by the FavouritesEngine.
* Its purpose is to hide the underlying table structure.
* It does not provide data validation or sanity checks, and is not intended
* to be used by users.
*/
class RFavouritesTable: public RDbTable
    {

    public:     // opening / closing with cleanup support

        /**
        * Open the table on this database, push a Close on the
        * cleanup stack.
        * @param aDb Open table on this database.
        * @param aAccess Access mode.
        * @return Error code.
        */
        TInt OpenL
            (
            RDbNamedDatabase& aDb,
            RDbRowSet::TAccess aAccess = RDbRowSet::EUpdatable
            );

        /**
        * Close the table, pop the cleanup item.
        */
        void Close();

    public:     // update with cleanup support

        /**
        * Begin insertion, push a Cancel on the cleanup stack.
        */
        void InsertL();

        /**
        * Begin update, push a Cancel on the cleanup stack.
        */
        void UpdateL();

        /**
        * Apply changes to database, pop the cleanup item.
        */
        void PutL();

        /**
        * Cancel changes to database, pop the cleanup item.
        */
        void Cancel();

    public:     // Navigation, filtering

        /**
        * Set filters.
        * @param aParentFolderFilter Uid value to filter. KFavouritesNullUid
        * clears (all accepted).
        * @param aTypeFilter EItem or EFolder to use filter; ENone to clear
        * filter (all accepted).
        * @param aNameFilter wildcard pattern to be used for name matching.
        * NULL clears (all accepted).
        */
        void SetFiltersL
            (
            TInt aParentFolderFilter,
            CFavouritesItem::TType aTypeFilter,
            const TDesC* aNameFilter
            );

        /**
        * Clear filters (all records accepted).
        */
        void ClearFilters();

        /**
        * Goto next record. If filtering is on, filters are considered.
        * Otherwise it is eqivalent to base class method.
        * @return ETrue if positioned on a record.
        */
        TBool NextL();

        /**
        * Goto record having this Uid. Filters are not considered.
        * @param aUid Uid of record to go to.
        * @return ETrue if positioned on a record.
        */
        TBool GotoToUidL( TInt aUid );

    public:     // data retrieval

        /**
        * Read the data from the current row to aItem. Row data must have
        * been gotten; no validation or sanity check is performed.
        * @param aItem This item is filled with data from the
        * current row.
        */
        void ReadItemDataL( CFavouritesItem& aItem ) const;

        /**
        * Get Uid from the current row. Row data must have been retrieved;
        * no sanity check.
        * @return The Uid in the current row.
        */
        TInt Uid() const;

        /**
        * Get Parent Folder Uid from the current row. Row data must have
        * been retrieved; no sanity check.
        * @return Parent Folder's Uid in the current row.
        */
        TInt ParentFolder() const;

        /**
        * Get type from the current row. Row data must have
        * been retrieved; no sanity check.
        * @return Type in the current row.
        */
        CFavouritesItem::TType Type() const;

        /**
        * Get name from the current row. Row data must have been retrieved;
        * no sanity check.
        * @return Pointer containing the name in the current row.
        */
        TPtrC Name() const;

        /**
        * Get URL from the current row. Row data must have been retrieved;
        * no sanity check.
        * @return Buffer containing the URL in the current row. Owner is
        * the caller.
        */
        HBufC* UrlLC() const;

        /**
        * Get Wap AP from the current row. Row data must have been retrieved;
        * no sanity check.
        * @return WAP AP in the current row.
        */
        TFavouritesWapAp WapAp() const;

        /**
        * Get username from the current row. Row data must have been retrieved;
        * no sanity check.
        * @return Pointer containing the name in the current row.
        */
        TPtrC Username() const;

        /**
        * Get password from the current row. Row data must have been retrieved;
        * no sanity check.
        * @return Pointer containing the name in the current row.
        */
        TPtrC Password() const;

        /**
        * Get extra data from the current row. Row data must have been
        * retrieved; no sanity check.
        * @param aData Data object, which receives the data.
        */
        void GetExtraDataL( MFavouritesItemData& aData );

        /**
        * Get "factory item" flag from the current row. Row data must have
        * been retrieved; no sanity check.
        * @return "Factory item" flag.
        */
        TBool FactoryItem() const;

    public:     // data update

        /**
        * Write the data from aItem to the current row. The table must be
        * inserting or updating a row; no validation or sanity check is
        * performed.
        * @param aItem Data from this item (except Uid) will be written
        * to the current row.
        */
        void WriteItemDataL( const CFavouritesItem& aItem );

        /**
        * Set Uid to the current row. The table must be
        * updating or inserting a row. No sanity check.
        * @param aUid Uid to be written to the current row.
        */
        void SetUidL( TInt aUid );

        /**
        * Set Parent Folder Uid to the current row. The table must be
        * updating or inserting a row. No sanity check.
        * @param aUid Parent Folder's Uid to be written to the current row.
        */
        void SetParentFolderL( TInt aUid );

        /**
        * Set type to the current row. The table must be
        * updating or inserting a row. No sanity check.
        * @param aType Type be written to the current row.
        */
        void SetTypeL( CFavouritesItem::TType aType );

        /**
        * Set name to the current row. The table must be
        * updating or inserting a row. No sanity check.
        * @param aName Name to be written to the current row.
        */
        void SetNameL( const TDesC& aName );

        /**
        * Set URL to the current row. The table must be
        * updating or inserting a row. No sanity check.
        * @param aUrl URL to be written to the current row.
        */
        void SetUrlL( const TDesC& aUrl );

        /**
        * Set WAP AP to the current row. The table must be
        * updating or inserting a row. No sanity check.
        * @param aWapAp WAP AP to be written to the current row.
        */
        void SetWapApL( const TFavouritesWapAp& aWapAp );

        /**
        * Set username to the current row. The table must be
        * updating or inserting a row. No sanity check.
        * @param aUsername Username to be written to the current row.
        */
        void SetUsernameL( const TDesC& aUsername );

        /**
        * Set password to the current row. The table must be
        * updating or inserting a row. No sanity check.
        * @param aPassword Password to be written to the current row.
        */
        void SetPasswordL( const TDesC& aPassword );

        /**
        * Set extra data to the current row. The table must be
        * updating or inserting a row. No sanity check.
        * @param aData Extra data to be written to the current row.
        */
        void SetExtraDataL( const MFavouritesItemData& aData );

        /**
        * Set "factory item" flag. The table must be
        * updating or inserting a row. No sanity check.
        * @param aFactoryItem "Factory item" flag to be written to the current
        * row.
        */
        void SetFactoryItemL( TBool aFactoryItem );

    public:     // utility

        /**
        * Place a write-lock. The cursor is positioned on an invalid row.
        * @return
        *   - KErrNone if successul.
        *   - KErrLocked if could not place write-lock.
        */
        TInt PutWriteLockL();

    public:     // creating database structure

        /**
        * Create the appropriate structure (table, columns, indexes) in aDb.
        * @param aDb The database to be used. Must be open.
        */
        static void CreateStructureL( RDbNamedDatabase& aDb );

    public:     // debugging

        /**
        * Dump the database to aStream. Only the debug version does
        * a real dump.
        * @param aStream the stream to dump to.
        */
        void DumpL( RWriteStream& aStream );

    private:    // implementation details

        /**
        * Get the ordinal numbers for database columns.
        * Expects the table be open.
        */
        void GetColumnNumbersL();

        /**
        * Place a write-lock, leave if unsuccessful.
        */
        void DoPutWriteLockL();

        /**
        * Cancel changes to database; called in leave processing.
        * @param aTable The table (RFavouritesTable*) as TAny*.
        */
        static void CancelOnLeave( TAny* aTable );

        /**
        * Close table; called in leave processing.
        * @param aTable The table (RFavouritesTable*) as TAny*.
        */
        static void CloseOnLeave( TAny* aTable );

    private:        // Data

        TDbColNo iColNoUid;             ///< Column ordinal for Uid.
        TDbColNo iColNoParentFolder;    ///< Column ordinal for parent folder.
        TDbColNo iColNoType;            ///< Column ordinal for type.
        TDbColNo iColNoName;            ///< Column ordinal for name.
        TDbColNo iColNoUrl;             ///< Column ordinal for URL.
        TDbColNo iColNoUserName;        ///< Column ordinal for username.
        TDbColNo iColNoPassword;        ///< Column ordinal for password.
        TDbColNo iColNoWapApId;         ///< Column ordinal for WAP AP id.
        TDbColNo iColNoWapApValueKind;  ///< Column ordinal for WAP AP kind.
        TDbColNo iColNoExtraData;       ///< Column ordinal for derived classes' data.
        TDbColNo iColNoFactoryItem;     ///< Column ordinal for factory item flag.

        TBool iFiltering;               ///< ETrue if filtering is on.
        RDbRowConstraint iFilter;       ///< Constraint when filtering.

    };

#endif
            
// End of File
