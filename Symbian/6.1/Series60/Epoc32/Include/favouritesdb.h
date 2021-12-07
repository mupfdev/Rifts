/*
* ============================================================================
*  Name     : FavouritesDb.h
*  Part of  : Favourites Engine
*
*  Description:
*      Declaration of class CFavouritesDb.
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

#ifndef FAVOURITES_DB_H
#define FAVOURITES_DB_H

//  INCLUDES

#include <e32base.h>
#include <d32dbms.h>
#include <f32file.h>
#include <PinbLnkbase.h>

#include <FavouritesLimits.h>
#include <FavouritesTable.h>

// FORWARD DECLARATIONS

class CFavouritesItem;
class CFavouritesItemList;
class CPinbModel;
class CPinbLinkBase;
class MFavouritesItemData;
class MRfsApMapper;


// CLASS DECLARATION

/**
* Representation of the favourites database.
* This class encapsulates a session with DBMS database server.
* It provides a way to access the database, do administration
* (recovery, compaction) and explicit transaction support.
*/
class CFavouritesDb: public CBase
    {

    public:     // Constructors and destructor
        
        /**
        * Destructor.
        */
        IMPORT_C virtual ~CFavouritesDb();

    protected:      // Constructors

        /**
        * Constructor.
        */
        IMPORT_C CFavouritesDb();

        /**
        * Second-phase constructor.
        * @param aDbPath Path of the database file.
        * @param aDbFile File name of the database file.
        */
        IMPORT_C void ConstructL
            ( const TDesC& aDbPath, const TDesC& aDbFile );

    public:     // Adminstration
        
        /**
        * Get version information.
        * @return Version object of this CFavouritesDb.
        */
        IMPORT_C TVersion Version() const;

        /**
        * Check if the database has to be recovered to be
        * fully functional.
        * @return ETrue if recovery is needed; EFalse otherwise.
        */
        IMPORT_C TBool IsDamagedL();

        /**
        * Perform synchronous recovery. Requires exclusive access
        * to the database.
        * @return Error code.
        */
        IMPORT_C TInt Recover();

        /**
        * Perform synchronous compaction. Requires exclusive access
        * to the database.
        * @return Error code.
        */
        IMPORT_C TInt Compact();

        /**
        * Get available database size.
        * @return Database size.
        */
        IMPORT_C RDbDatabase::TSize Size() const;

        /**
        * Update database statistics.
        * @return Error code.
        */
        IMPORT_C TInt UpdateStats();

        /**
        * Connect to DBMS and open the bookmark database.
        * @return Error code.
        */
        IMPORT_C TInt OpenL();

        /**
        * Close the bookmark database and disconnect from DBMS.
        * Automatic compaction is attempted.
        */
        IMPORT_C void Close();

        /**
        * Close the bookmark database and disconnect from DBMS.
        * Automatic compaction is not attempted.
        */
        IMPORT_C void CloseImmediately();

    public:     // Transaction support

        /**
        * Explicitly begin a transaction.
        * NOTE: this method pushes a Rollback operation on the cleanup stack.
        * Use the BeginL - CommitL/Rollback calls as you would do for any
        * other CleanupStack related calls.
        * @param aWrite If ETrue, write-lock is placed immediately.
        * @return Error code, including:
        *   - KErrLocked If could not start the transaction or could not place
        *     the write-lock.
        */
        IMPORT_C TInt BeginL( TBool aWrite = EFalse );

        /**
        * Commit the transaction and pop off a cleanup item from the Cleanup
        * Stack (pushed in BeginL). Leave on failure.
        */
        IMPORT_C void CommitL();

        /**
        * Roll back the transaction and and pop off a cleanup item from the
        * Cleanup Stack (pushed in BeginL)
        */
        IMPORT_C void Rollback();

    public:     // Pinboard support

        /**
        * Get uid for Pinboard links to items in this database.
        * Derived classes must provide this method.
        * @return Pinboard link uid.
        */
        IMPORT_C virtual TUid PinbLinkUid() const = 0;

        /**
        * Get icon id for Pinboard links to items in this database.
        * Derived classes must provide this method.
        * @return Pinboard link icon id.
        */
        IMPORT_C virtual TPinbDocumentIconId PinbLinkIcon() const = 0;

    public:     // Data access / update / delete

        /**
        * Get the item having this Uid.
        * @param aItem placeholder for the returned item data. Must be of type
        * what is returned by CreateItemL().
        * @return Error code.
        */
        IMPORT_C TInt GetL( TInt aUid, CFavouritesItem& aItem );

        /**
        * Get all items matching the supplied criteria.
        * @param aItemList placeholder for the returned item data. Existing
        * items remain (new ones appended).
        * @param aParentFolderFilter Uid value to filter. KFavouritesNullUid
        * clears (all accepted); this is the default.
        * @param aTypeFilter EItem or EFolder to use filter; ENone to clear
        * filter (all accepted); this is the default.
        * @param aNameFilter wildcard pattern to be used for name matching.
        * NULL clears (all accepted); this is the default.
        * @return Error code.
        */
        IMPORT_C TInt GetAllL
            (
            CFavouritesItemList& aItemList,
            TInt aParentFolderFilter = KFavouritesNullUid,
            CFavouritesItem::TType aTypeFilter = CFavouritesItem::ENone,
            const TDesC* aNameFilter = NULL
            );

        /**
        * Get uids of all items matching the supplied criteria.
        * @param aUids placeholder for the returned item data. Existing
        * items remain (new ones appended).
        * @param aParentFolderFilter Uid value to filter. KFavouritesNullUid
        * clears (all accepted); this is the default.
        * @param aTypeFilter EItem or EFolder to use filter; ENone to clear
        * filter (all accepted); this is the default.
        * @param aNameFilter wildcard pattern to be used for name matching.
        * NULL clears (all accepted); this is the default.
        * @return Error code.
        */
        IMPORT_C TInt GetUidsL
            (
            CArrayFix<TInt>& aUids,
            TInt aParentFolderFilter = KFavouritesNullUid,
            CFavouritesItem::TType aTypeFilter = CFavouritesItem::ENone,
            const TDesC* aNameFilter = NULL
            );

        /**
        * Delete item. If this is a folder, all descendants and the contents
        * of them are deleted. Homepage or root cannot be deleted.
        * Note: this method needs Eikon environment (because invalidating
        * Pinboard links needs it).
        * @param aUid Uid of item to delete.
        * @return Error code, including:
        *   - KErrNotFound if the item is not found.
        *   - KErrAccessDenied if the item's cannot be deleted.
        */
        IMPORT_C TInt DeleteL( TInt aUid );

        /**
        * Update item. Homapage or Last Visited Page cannot be updated using
        * this method.
        * @param aItem Contents from this item (except Uid) will be used to
        * update the item. Must be of type what is returned by CreateItemL().
        * If successful, its Uid (and possibly its name) is updated on return.
        * @param aUid Update this item.
        * @param aAutoRename If this is ETrue, and the name already exists,
        * the item will be renamed to a non-conflicting name.
        * @return Error code, including:
        *   - KErrNotFound if the item is not found.
        *   - KErrArgument if the item's data is invalid (bad name, no URL,
        *     parent folder does not exist etc.).
        *   - KErrAlreadyExists if the name is already in use in that folder.
        */
        IMPORT_C TInt UpdateL
            ( CFavouritesItem& aItem, TInt aUid, TBool aAutoRename );

        /**
        * Add a new item to the database.
        * If successful, its Uid (and possibly its name) is updated on return.
        * @param aItem The item to add.
        * @param aAutoRename If this is ETrue, and the name already exists,
        * the item will be renamed to a non-conflicting name.
        * @return Error code, including:
        *   - KErrArgument if the item's data is invalid (bad name, no URL,
        *     parent folder does not exist etc.).
        *   - KErrAlreadyExists if the name is already in use in that folder.
        */
        IMPORT_C TInt AddL( CFavouritesItem& aItem, TBool aAutoRename );

        /**
        * Update the Homepage item. If does not exist, it is now
        * created. The old Homepage, if any, is overwritten.
        * If successful, its Uid is updated on return.
        * Name needs not be unique.
        * @param aItem Contents from this item (except Uid) will
        * be used to update the Homepage Bookmark.
        * @return Error code, including:
        *   - KErrArgument if the supplied item is not item, or is not in
        *     the root folder.
        */
        IMPORT_C TInt SetHomepageL( CFavouritesItem& aItem );

        /**
        * Update the Last Visited. If does not exist, it is now
        * created. The old Last Visited, if any, is overwritten.
        * If successful, its Uid is updated on return.
        * Name needs not be unique.
        * @param aItem Contents from this item (except Uid) will
        * be used to update the Last Visited Item.
        * @return Error code, including:
        *   - KErrArgument if the supplied item is not item, or is not in
        *     the root folder.
        */
        IMPORT_C TInt SetLastVisitedL( CFavouritesItem& aItem );

        /**
        * Check if we have this item.
        * @param aUid The item to check.
        * @return
        *   - ETrue if we have this item;
        *   - EFalse if no such uid, or in case of any error.
        */
        IMPORT_C TBool ItemExistsL( TInt aUid );

        /**
        * Check if we have this folder.
        * @param aFolder The folder to check.
        * @return
        *   - ETrue if we have this folder;
        *   - EFalse if no such uid; not a folder; or in case of any error.
        */
        IMPORT_C TBool FolderExistsL( TInt aFolder );

        /**
        * Count all items matching the supplied criteria.
        * @param aCount Placeholder for the returned item count. In case of
        * any error, existing value is unchanged.
        * @param aParentFolderFilter Uid value to filter. KFavouritesNullUid
        * clears (all accepted); this is the default.
        * @param aTypeFilter EItem or EFolder to use filter; ENone to clear
        * filter (all accepted); this is the default.
        * @param aNameFilter Wildcard pattern to be used for name matching.
        * NULL clears (all accepted); this is the default.
        * @return Error code.
        */
        IMPORT_C TInt CountL
            (
            TInt& aCount,
            TInt aParentFolderFilter = KFavouritesNullUid,
            CFavouritesItem::TType aTypeFilter = CFavouritesItem::ENone,
            const TDesC* aNameFilter = NULL
            );

    public:     // extra data

        /**
        * Set data associated with an item. Any existing data, belonging to
        * item having aUid, is now replaced. The item itself is not changed.
        * In case of any errors, the data is not saved.
        * @param aUid The uid of the item, to which the data belongs.
        * @param aData Data) which replaces existing data.
        * @return Error code, including:
        *   - KErrNotFound No item is found with aUid.
        */
        IMPORT_C TInt SetDataL( TInt aUid, const MFavouritesItemData& aData );

        /**
        * Get data associated with an item.
        * @param aUid The uid of the item, to which the data belongs.
        * @param aData Data object, which receives the data.
        * @return Error code, including:
        *   - KErrNotFound No item is found with aUid.
        */
        IMPORT_C TInt GetDataL( TInt aUid, MFavouritesItemData& aData );

    public:     // unique name support

        /**
        * Check if aName is unique in aFolder; and if not, change to
        * an unique one, appending a number. In case of any errors, aName is
        * unchanged. Names of special items (Start Page etc.) are not
        * considered (can have conflicting names).
        * @param aName Descriptor containing the original name and receiving
        * the resulting unique name. Must be large enough to accomodate the
        * result. (The appended text is KFavouritesMaxPostfix characters at
        * most; the resulting length is KFavouritesMaxName at most.)
        * @param aFolder Folder to be used for uniqueness-checking.
        * @return Error code, including:
        *   - KErrArgument aFolder is not found.
        *   - KErrBadName aName is empty.
        */
        IMPORT_C TInt MakeUniqueNameL( TDes& aName, TInt aFolder );

        /**
        * Check if aName is unique in its folder; and if not, change to
        * an unique one, appending a number. In case of any errors, aItem is
        * unchanged. Names of special items (Start Page etc.) are not
        * considered (can have conflicting names).
        * @param aItem Item to set unique name for.
        * @return Error code, including:
        *   - KErrArgument aFolder is not found.
        *   - KErrBadName Current name is empty.
        */
        IMPORT_C TInt MakeUniqueNameL( CFavouritesItem& aItem );

    public:     // debugging

        /**
        * Dump the database to aStream. Only the debug version does
        * a real dump.
        * @param aStream the stream to dump to.
        */
        IMPORT_C void DumpL( RWriteStream& aStream );

    public:     // Browser support

        /**
        * Create an empty item with uid KFavouritesStartPageUid. Owner is the
        * caller. Except its uid, the item is uninitialized. The WML Browser
        * needs this. Note that this item does not exist in the database.
        * @return The created item.
        */
        IMPORT_C CFavouritesItem* CreateStartPageItemL();

    protected:  // types

        /**
        * What to do with conflicting names in Add or Update operations.
        */
        enum TRenameType
            {
            EDontRename,    ///< Reject update.
            EAutoRename,    ///< Rename automatically.
            ESuppressCheck  ///< Suppress name conflict checking (accept any).
            };

    protected:  // custom cleanup

        /**
        * Called after items has been deleted from database. Derived classes
        * may override this to add custom cleanup. Current implementation is
        * empty.
        * @param aUids List of uids that were deleted.
        */
        IMPORT_C virtual void ItemsDeletedL( const CArrayFix<TInt>& aUids );

        /**
        * Called when closing the database by calling Close(); not called
        * when calling CloseImmediately(). Derived classes may override this
        * to add custom cleanup. Current implementation is empty.
        */
        IMPORT_C virtual void Closing();

    protected:  // (but not exported)

        /**
        * BeginL an explicit transaction if there is none in progress.
        * @param aWrite If ETrue, write-lock is placed immediately.
        * @param aOwnTransaction Placeholder for result. If the value is
        * ETrue on return, a transaction was started. To be used as the
        * input parameter for the corresponding CommitIfNeeded(...) call.
        * @return Error code.
        */
        TInt BeginIfNeededL( TBool aWrite, TBool& aOwnTransaction );

        /**
        * Commit the transaction if aOwnTransaction is ETrue.
        * @param aOwnTransaction If ETrue, Commit will be performed.
        * @return Error code.
        */
        void CommitIfNeededL( TBool aOwnTransaction );

    private:    // new methods

        /**
        * Create the database file, make the database, and the root
        * folder. If anything goes wrong during this, leave. This method
        * expects everything to exist and be open/ready for use.
        * @param aFs File server session to use.
        * @param aDbFile Parsed filename to use.
        */
        void CreateDatabaseL( RFs& aFs, TParse& aDbFile );

        /**
        * Create the root entry. Expects the database to be
        * open and not used by anyone else.
        */
        void CreateRootFolderL();

        /**
        * Get the used database. Friend classes use this method.
        * @return Reference to the used database.
        */
        inline RDbDatabase& Database();

        /**
        * Delete the item under the cursor. If it is a folder, delete contents
        * also.
        * Expects a transaction; expects a valid row.
        * @param aDeletedUids Uids of deleted items will be appended to this
        * list.
        * @return Error code.
        */
        TInt DeleteCurrentL( CArrayFix<TInt>& aDeletedUids );

        /**
        * Update the item under the cursor.
        * Expects a transaction; expects a valid row. Row data not gotten.
        * @param aItem Contents from this item (except Uid) will be used to
        * update the item. Must be of type what is returned by CreateItemL().
        * If successful, its Uid (and possibly its name) is updated on return.
        * The cursor is left on the updated row.
        * @param aUid Update this item.
        * @param aRenameType What to do in case of name conflict.
        * @return Error code, including:
        *   - KErrArgument if the item's data is invalid (bad name, no URL,
        *     parent folder does not exist etc.).
        *   - KErrAlreadyExists if the name is already in use in that folder.
        */
        TInt UpdateCurrentL
            ( CFavouritesItem& aItem, TRenameType aRenameType );

        /**
        * Add a new item to the database. Expects a transaction.
        * If successful, its Uid (and possibly its name) is updated on return.
        * The cursor is left on the added row.
        * @param aItem The item to add.
        * @param aRenameType What to do in case of name conflict.
        * @param aFactoryItem If ETrue, "Factory item" flag will be set.
        * @return Error code, including:
        *   - KErrArgument if the item's data is invalid (bad name, no URL,
        *     parent folder does not exist etc.).
        *   - KErrAlreadyExists if the name is already in use in that folder.
        */
        TInt DoAddL
            (
            CFavouritesItem& aItem,
            TRenameType aRenameType,
            TBool aFactoryItem = EFalse
            );

        /**
        * Set Homepage / Last Visited Page. Expects a transaction.
        * If successful, its Uid is updated on return. Name needs not be
        * unique. The cursor is left on the added / updated row.
        * @param aItem Item data.
        * @return Error code, including:
        *   - KErrArgument if the item's data is invalid (bad name, no URL,
        *     parent folder does not exist etc.).
        */
        TInt SetSpecialItemL( CFavouritesItem& aItem, TInt aUid );

        /**
        * Check that aName (which has not yet been added/modified in the
        * database) is unique name in aFolder.
        * No sanity check. Expects the folder to exist. Expects a transaction.
        * Overwrites filters.
        * @param aName Name to check. Must be OK.
        * @param aFolder Folder to check in. Must exist.
        * @param aAcceptUid This uid is accepted (in case of update, this is
        * the existing item's own uid).
        * @return KErrAlreadyExists or KErrNone.
        */
        TInt CheckNameUniquenessL
            ( const TDesC& aName, TInt aFolder, TInt aAcceptUid );

        /**
        * Make a unique name. No sanity checks. Expects a transaction.
        * Expects the name be really conflicting (with some item other than
        * aAcceptUid). Overwrites filters.
        * @param aName Descriptor containing the original name and receiving
        * the resulting unique name.
        * @param aFolder Folder to be used for uniqueness-checking. Must exist.
        * @param aAcceptUid Exclude this item from checking (used when
        * updating aAcceptUid).
        */
        void MakeUniqueNameL( TDes& aName, TInt aFolder, TInt aAcceptUid );

        /**
        * Allocate a buffer and make a unique name in it. No sanity checks.
        * Expects a transaction. Expects the name be really conflicting
        * (with some item other than aAcceptUid). Overwrites filters.
        * @param aName Descriptor containing the original name.
        * @param aFolder Folder to be used for uniqueness-checking. Must exist.
        * @param aAcceptUid Exclude this item from checking (used when
        * updating aAcceptUid).
        * @return A newly allocated buffer, containing the new name. Caller
        * must free this.
        */
        HBufC* AllocUniqueNameLC
            ( const TDesC& aName, TInt aFolder, TInt aAcceptUid );

        /**
        * Remove Pinboard link for this uid.
        * @param aUid List of item Uids to unlink from Pinboard.
        */
        void RemovePinbLinksL( CArrayFix<TInt>& aUnlinkUids );

        /**
        * Roll back the transaction; called in leave processing.
        * @param aDb The database (CFavouritesDb*) as TAny*.
        */
        static void RollbackOnLeave( TAny* aDb );

        /**
        * Close on leave; called in leave processing.
        * @param aDb The database (CFavouritesDb*) as TAny*.
        */
        static void CloseOnLeave( TAny* aDb );

        /**
        * Begin a transaction; leave on any error except KErrLocked (that is
        * returned).
        * @return Error code (KErrNone or KErrLocked).
        */
        TInt DoBeginL();

    protected:  // RFS support

        /**
        * User-level Restore Factory Settings operation (implemetation).
        * Delete all items that has "factory item" flag set, then add new
        * ones from reference database. In case of name conflilcts, new
        * names are generated. Leaves on any error.
        * @param RFavouritesTable Reference database table. It must be open
        * and in a transaction (or opened in read-only exclusive mode).
        * @param aApMapper Access Point mapper to be used.
        */
        void RestoreFactorySettingsL
            ( RFavouritesTable& aReferenceTable, MRfsApMapper& aApMapper );

    protected:  // Reserved for future use

        /**
        * Reserved for future use.
        * @param aDummy Dummy argument.
        */
        IMPORT_C virtual void Reserved_1( TAny* aDummy );
    
        /**
        * Reserved for future use.
        * @param aDummy Dummy argument.
        */
        IMPORT_C virtual void Reserved_2( TAny* aDummy );
    
    private:    // friends
        
        /// Access to iDbs is granted for this.
        friend class RFavouritesDbNotifier;
        /// Access to iDbs is granted for this.
        friend class RFavouritesDbIncremental;

    private:        // Data

        /**
        * Handle of DBMS session
        */
        RDbs iDbs;
        /**
        *  Pathname of the used database file.
        */
        HBufC* iDbPath;
        /**
        * Filename of the used database file.
        */
        HBufC* iDbFileName;
        /**
        * Handle to the used database.
        */
        RDbNamedDatabase iDatabase;
        /**
        * Database table used.
        */
        RFavouritesTable iTable;
        /**
        * Version information.
        */
        TVersion iVersion;
        /**
        * ETrue if open.
        */
        TBool iOpen;
        /**
        * ETrue between successful BeginL() and any Commit()/Rollback()
        * calls. Note that the database is not queried!
        */
        TBool iInTransaction;
        /**
        * Count updates since last compaction.
        */
        TInt iUpdatesSinceLastCompact;

    private:    // Reserved for future use.

        /**
        * Reserved for future use.
        */
        TAny* iReserved_1;
    };

#include <FavouritesDb.inl>

#endif
            
// End of File
