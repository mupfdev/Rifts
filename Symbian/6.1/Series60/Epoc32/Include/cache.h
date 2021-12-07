// 
// cache.h
// Copyright (C) 1997-2000 Symbian Ltd. All rights reserved.
// 
// Created at: 07-Sep-99 5:18:30 PM

//
// Comments: Client side cache server class
//			Intended for by a client of the cache server
//			to control storage and retrieval of cached items.
//

#if !defined(__CACHE_H__)
#define __CACHE_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

#if !defined (__APMSTD_H__)
#include <ApmStd.h>
#endif

#if !defined (__F32FILE_H__)
#include <f32file.h>
#endif

#if !defined(__BADESCA_H__)
#include <BADESCA.H>			// For CDesCArray
#endif

#if !defined (__CACHEI_H__)
#include "CacheI.h"
#endif

#if !defined (__CACHECMD_H__)
#include "CacheCmd.h"
#endif

// The enumeration of all 
// the cache configuration parameters
enum TConfig
	{
	EMaxMemory = 0xBDE,	// Maximum cache memory usage
	EBufferPreserve,	// Memory exclusion from cache
	EForceSpace,		// Memory space reserved in cache for forced caching
	EDriveLetter,		// Drive to store the cache data
	EDirectoryPath		// Directory path to the cache data
	};

// The enumeration of the cache storage mode operations
enum TStorageMode
	{
	ECacheItemNone = 0,	// Default
	ECacheItemRead,		// Read storage
	ECacheItemWrite		// Write storage
	};

// Forward declarations of required classes
class CCacheServerItem;
class RFs;

////////////////////////////////////////////////////////////////////////////////////////////////
//
// This class is an abstract to define the methods provided
// by an observer of a cache item.
class MCacheServerItemObserver
	{
public:
	virtual void NotificationMessage(TInt aStatus) = 0;	// Recieve a notification status

private:
	// Reserved for future expansion
	IMPORT_C virtual void MCacheServerItemObserverReserved1();
	IMPORT_C virtual void MCacheServerItemObserverReserved1() const;
	};

/////////////////////////////////////////////////////////////////////////////// 
// CCacheActiveObserver is the active object class supporting the
// notification messages 
//
class CCacheActiveObserver : public CActive
	{
public:
	// Create a new CCacheActiveObserver on the heap
	// returns a fully initialised class.
	// Leaves on error.
	// Requires a reference to a fully initialised CCacheServerItem
	static CCacheActiveObserver* NewL(CCacheServerItem& aCacheServer, TPriority aPriority = EPriorityHigh);

	// D'tor
	~CCacheActiveObserver();

	// Called to make the observer active
	void Activate();

protected:
	// CActive methods
	// Called from CActive::Cancel() is called,
	// allowing this object to provide specific cleanup activity.
	void DoCancel();

	// Called when the CNotificationObserver activates
	// leaving upon any error.
	// Calls the CCacheServerItem::CacheChanged() method passing the status of the object
	// which contains the notification reason.
	void RunL();

private:
	// Default c'tor
	CCacheActiveObserver(CCacheServerItem& aCacheServer, TPriority aPriority);

	// Complete the instantiation of the instance.
	// Leave upon any error.
	void ConstructL();

private:
	CCacheServerItem* iCacheServer;	// Reference to the owning factory
	};

/////////////////////////////////////////////////////////////////////////////// 
//
class RCacheSession : public RSessionBase		// For the Client side session on the Cache Server
    {
	friend class CCacheServerItem;				// To allow access to the SendRecieve method
public:
    IMPORT_C TInt Connect();					//	Connect with the cache server
	IMPORT_C void Close();						//	Break the server connection.

    IMPORT_C static TVersion Version();			// Give the current version number of the cache client side

private:
	};
//
//	class RCacheSession


//
class CCacheServerItem : public CBase
// The client object that manages all access to the cache server
    {
	friend class CCacheActiveObserver;

public:
	// Create an instance of this object upon the heap
	// and return it fully initialised.
	// Leave if there is an error.
	IMPORT_C static CCacheServerItem* NewL();

	// Create an instance of this object upon the heap
	// and return it fully initialised, with an open
	// connection to the cache server.
	// Leave if there is an error.
	//
	// Note that the UID is the identifier for
	// the cache upon which operations are performed.
	// This is usually an application UID.
	IMPORT_C static CCacheServerItem* NewL(const TUid& aUid);	// Constructs and connects

	// D'tor
	IMPORT_C ~CCacheServerItem();

	// Connect to the cache server.
	// return an error code to indicate success.
	//
	// Note that the UID is the identifier for
	// the cache upon which operations are performed.
	// This is usually an application UID.
    IMPORT_C TInt Connect(const TUid& aUid);
	// Close the connection to the cache server
	IMPORT_C void Close();

	// Return the version number of the cache server
    IMPORT_C TVersion Version();

	// Return the UID that this client side object
	// considers identifies it's cache for operations.
	// This is usually an application UID.
	IMPORT_C TUid Uid () const;

	// Check if an item identified by a descriptor exists.
	IMPORT_C TBool Exists (const TDesC& aItemId);

	// Begin a storage operation upon the item identified with 
	// the supplied descriptor.
	IMPORT_C void InitiateStorageL(const TDesC& aItemId);
	// Store a buffer of data which forms a part of the cached data
	// for an 'open' storage item.
	IMPORT_C void StorePartL (const TDesC8& aBuffer);
	// Finish the storage of the data for an item and clean up.
	IMPORT_C TInt CommitStorage();

	// Begin a forced storage operation upon the item identified with 
	// the supplied descriptor.
	IMPORT_C void InitiateForcedStorageL(const TDesC& aItemId);

	// Store the data contained within the buffer immediately
	// Initiates, stores, and commits in a single operation
	// Will leave if the buffer contains too big an item with 
	// KErrOverflow. (The limit is KDbStoreMaxColumnLength).
	IMPORT_C void StoreImmediateL(const TDesC8& aBuffer);

	// Store the data contained within the buffer immediately for the item
	// identified by a descriptor
	// Initiates, stores, and commits in a single operation.
	// Will leave if the buffer contains too big an item with 
	// KErrOverflow. (The limit is KDbStoreMaxColumnLength).
	IMPORT_C void StoreImmediateL(const TDesC& aItemId, const TDesC8& aBuffer);

	// Begin a retrieval operation upon the item identified with 
	// the supplied descriptor.
	IMPORT_C void InitiateRetrievalL(const TDesC& aItemId);

	// Retrieve a buffer of data that forms part of the data
	// cached for the item.
	IMPORT_C TInt RetrieveData (TDes8& aBuffer);

	// Move to a specific position within the stored data
	// currently open for retrieval.
	// Pre-Condition : InitiateRetrievalL MUST have been called successfully.
	IMPORT_C TInt Seek(TSeek aMode, TInt aPosition);

	// Signal that retrieval is complete
	IMPORT_C void EndRetrieval();

	// Request asynchronous cache change notification via the supplied
	// observer.
	IMPORT_C void NotifyOnChange(MCacheServerItemObserver* aObserver);
	// Cancel any extant change notification request.
	IMPORT_C void NotifyOnChangeCancel();

	// Abort any synchronous cache operation immediately
	// discarding any changes which may have been made.
	IMPORT_C void Abort ();
	
	// Delete a cache item
	IMPORT_C TInt DeleteItem ();
	// Delete a cache item identified with 
	// the supplied descriptor.
	IMPORT_C TInt DeleteItemL (const TDesC& aItemId);

	// Obtain the item id of the 'current' cache item. 
	IMPORT_C const TDesC& ItemId () const;
	
	// Obtain the expiry time of the current cache item
	IMPORT_C const TInt64 ExpiryTime () const;
	// Set the expiry time of the current cache item.
	IMPORT_C void SetExpiryTime(const TInt64& aExpiryTime);
	
	// Get the expiry policy for the current cache item
	IMPORT_C TCachePolicy ExpiryPolicy () const;
	// Set the cache policy for the current cache item.
	IMPORT_C void SetExpiryPolicy(const TCachePolicy& aExpiryPolicy);
	// Update the current cache items expiry details
	IMPORT_C TInt UpdateExpiryDetails();
	
	// Get the data type for the current cache item
	IMPORT_C TDesC& Type () const;
	// Set the data type for the current cache item
	IMPORT_C void SetTypeL(const TDesC& aType);

	// Search for and construct an array of all those cache items which
	// correspond to a particular item id (which may be partial).
	IMPORT_C CDesCArray& RetrieveItemsL (const TDesC& aItemPartialId);

	// Empty any current iteration array
	IMPORT_C void ClearIteration ();

	// Remove ALL items from the cache
	IMPORT_C TInt ClearCache();

	// Set a configuration item for the cache.
	IMPORT_C void SetCacheConfigurationL (TConfig aConfigItem, TInt aConfigValue);
	IMPORT_C void SetCacheConfigurationL (TConfig aConfigItem, const TDesC& aConfigValue);
	// Retrieve the value of a cache configuration item.
	IMPORT_C void CacheConfigurationL (TConfig aConfigItem, TInt& aConfigValue);
	IMPORT_C void CacheConfigurationL (TConfig aConfigItem, const TDesC& aConfigValue);

private:
	// Default c'tor
	CCacheServerItem();

	// Complete the initialisation of this instance.
	// Leave if there is any error.
	void ConstructL();

	// Complete the initialisation of this instance, and connect to the cache server.
	// Leave if there is any error.
	void ConstructL(const TUid& aUid);				// Constructs and connects
	
	// As it says open up a storage space for cache storage
	TInt OpenStorageLocation();
	// Close the opened cache storage space
	void CloseStorageLocation();
	
	// The method which reecieves the change notification status from 
	// CCacheActiveObserver
	void CacheChanged(TRequestStatus& aStatus);
	
	// Helper method which talks to the server to initiate a storage operation
	TInt InitStorageL(TCacheServerFunction aMode);

	// Helper method which talks to the server to initiate a retrieval operation
	TInt InitiateRetrievalL();

	// Set the item to be considered as the current cache item.
	void SetItemIdL(const TDesC& aItemId);

private:
	// Item variables
	CCacheItem* iCacheItem;							// The currently 'live' cache item
	
	TInt iStoragePos;								// The position within local storage.
	TStorageMode iStorageMode;						// The mode of storage in use (Read/Write)

	// Connection variables
	TUid iUid;										// The UID identifying the cache to connect to
	RCacheSession* iCacheSession;					// The current session with the Cache server
	RFs iFs;										// The file session object
	RFile iFile;									// The file object for local cache storage

	CDesCArray* iItemIds;							// The array of iterated cached ids

	CCacheActiveObserver* iCacheObserver;			// Recieving notifications from the cache;
	MCacheServerItemObserver* iItemObserver;		// Sending notifications ot our observer

	TAny* iMessageArgs[KMaxMessageArguments];		// The argument buffer for the Inter-Process Request transfer

#if defined _DEBUG
	TInt __DbgMarkEnd();							// Methods defined for debug test of heap for leakage
	TInt __DbgMarkHeap();
	TInt __DbgFailNext(TInt aCount);
	void __DbgTestInvariant() const;				// Debug method definition to allow class invariant testing
#endif
	};
//
//	class CCacheServerItem

#endif
