// 
// CacheI.h
// Copyright (C) 1997-1999 Symbian Ltd. All rights reserved.
//

// 
// Created at: 16-Jun-99 11:02:43 AM
// Comments: 
// 

#ifndef __CACHEI_H__
#define __CACHEI_H__

#if !defined (__E32BASE_H__)
#include <e32base.h>
#endif
#if !defined (__APMSTD_H__)
#include <ApmStd.h>
#endif

class CCacheSession;
class CCacheServer;
class CCacheDatabaseManager;
class CCacheServerItem;

enum TItemState
	{
	EItemPartial = 0xBDE,
	EItemComplete,
	EItemExpired,
	EItemStateUndefined = -1
	};

enum TCachePolicy
	{
	EExpiryImmediate = 0xBDF,
	EExpireOnTime,
	EExpireNever,
	EExpiryUndefined = -1
	};

_LIT(KCacheItemType,"Unknown");

class CCacheItem : public CBase
//
//	A single item in the cache
//
	{
	friend class CCacheSession;
	friend class CCacheServer;
	friend class CCacheDatabaseManager;
	friend class CCacheServerItem;

public:
	// Define the structure for the control information
	// Handling of this item.
	// Also used in IPC data transfer handling
	struct TControlInfo
	{
	// Give the default constructor
	TControlInfo():iExpiryPolicy(EExpiryImmediate), iPriority(CActive::EPriorityLow), iItemState(EItemPartial){;}

	TCachePolicy iExpiryPolicy;	// The items set expiry policy
	TInt64 iCachedTime;			// The UNC time this item was originally stored.
	TInt64 iExpiryTime;			// The UNC expiry time for this item
	TInt32 iPriority;			// The prioritisation of this item
	TBool  iLocal;				// Is this item stored ENTIRELY within the database
	TInt32 iId;					// The items unique id within its cache
	TInt32 iSize;				// The items size within the cache
	TItemState iItemState;		// The current completion state of the item,
	};

	// Construct a cache item upon the heap
	// Leaving if the instance cannot be fully initialised.
	IMPORT_C static CCacheItem* NewL();

	// Default d'tor
	IMPORT_C ~CCacheItem();

	// Instance accessors
	// Set the descriptor identifier for the item
	// (Note corresponds to the ItemId descriptor).
	IMPORT_C void SetNameL(const TDesC& aName);
	// Return the descriptor identifier for the item
	IMPORT_C TDesC& Name() const;

	// Set the storage location for the item, if it is large (> 255 characters)
	IMPORT_C void SetStorageLocL(const TDesC& aStorageLoc);
	// Return the stroage location of the item
	IMPORT_C TDesC& StorageLoc() const;

	// Set the item type
	IMPORT_C void SetTypeL(const TDesC& aType);
	// Return the item type descriptor
	IMPORT_C TDesC& Type() const;

	// Set the item size
	IMPORT_C void SetSize(TInt aSize);
	// Return the item size
	IMPORT_C TInt Size() const;

	// Set the expiry policy for this cache item
	IMPORT_C void SetExpiryPolicy(TCachePolicy aExpiryPolicy);
	// Return the expiry policy for this cache item
	IMPORT_C TCachePolicy ExpiryPolicy() const;

	// Set the expiry time for this cache item
	IMPORT_C void SetExpiryTime(const TInt64& aExpiryTime);
	// Return the expiry time for this item
	IMPORT_C const TInt64& ExpiryTime() const;

	// Set the UNC cache time for this item
	IMPORT_C void SetCachedTime(const TInt64& aCachedTime);
	// Return the UNC time this item was originally cached
	IMPORT_C const TInt64& CachedTime() const;

	// Is this cache item stored locally or in the database.
	// A return value of True indicates that the cache item resides
	// ENTIRELY within the database. (i.e. is less than 256 characters
	// in length
	IMPORT_C TBool Local() const;

protected:
	// Clears the poiters which hold the allocated
	// descriptors!!! Do not call unless you can deallocate the descriptors
	// yourself
	IMPORT_C void ResetDescriptors();

private:
	// Default construction
	CCacheItem();

	// Complete this instance instantiation here
	// Leave if it fails to instantiate correctly, and fully.
	void ConstructL();

	// Exports from friendly classes
	IMPORT_C void SetItemState(TItemState aItemState);	// Set the Completion state of the item
	IMPORT_C TItemState ItemState() const;				// Return the Completion state of the item

	IMPORT_C void SetPriority(TInt32 aPriority);		// Set cache item prioritisation
	IMPORT_C TInt32 Priority() const;					// Return the cache item prioritisation

	// if aLocal = True, then this cache item resides ENTIRELY
	// within the database. (i.e. is less than 256 characters
	// in length). otherwise it resides in a file somewhere.
	IMPORT_C void SetLocal(TBool aLocal);

	// Set this items unique cache id
	IMPORT_C void SetId(TInt32 aId);
	// Return this cache items unique id
	IMPORT_C TInt32 Id() const;

private:
	HBufC* iName;					// the descriptor identifier for the item	
	HBufC* iStorageLoc;				// the storage location for the item, if it is large (> 255 characters)
	HBufC* iType;					// the item type
	TControlInfo iControlInfo;		// control information of this item. Also used in IPC data transfer handling
	};

#endif	// __CACHEI_H__
