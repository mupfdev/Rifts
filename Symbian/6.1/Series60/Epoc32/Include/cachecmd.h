//
//	CACHECMD.H
// Copyright (C) 1997-2000 Symbian Ltd. All rights reserved.
//

//
//	Define an enumeration of Op codes for cache server services.
//

#if !defined(__CACHECMD_H__)
#define __CACHECMD_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

// The service op code enumeration
enum TCacheServerFunction
	{
	ECacheUID = 0x1000,							// Identify the cache of interest.
	ECacheExists,								// Check for cache existence
	ECacheImmediateStorage,						// Store the data immediately in the cache. (Limited data storage 255 chars or less).
	ECacheInitiateStorage,						// Begin data storage caching.			(Large amounts of storage).
	ECacheForceStorage,							// Begin forced data storage caching.	(Ignoring cache storage limitations!).
	ECacheInitiateRetrieval,					// Begin data storage retrieval.		(Large amounts of storage).
	ECacheCommit,								// End a cache storage operation.		(Large amounts of storage).
	ECacheDelete,								// Remove an item from the cache.
	ECacheSetAssociatedData,					// Store some subsidiary data to be associated with a cache item.
	ECacheGetAssociatedData,					// Retrieve the subsidiary data associated with a cache item.
	ECacheSetConfiguration,						// Set a cache configuration parameter.
	ECacheGetConfiguration,						// Retrieve a cache configuration parameter.
	ECacheRetrieveItems,						// Retrieve a set of cached items corresponding to a partial id
	ECacheNotifyOnChange,						// Begin asynchronous cache change notification.
	ECacheNotifyOnChangeCancel,					// Cancel asynchronous cache change notification.
	ECacheNotifyOnRetrieveTypedItem,			// Begin asynchronous cache retrieval notification.
	ECacheNotifyOnRetrieveTypedItemCancel,		// Cancel  asynchronous cache retrieval notification.
	ECacheClear,								// Empty the entire cache.
	ECacheExpiryUpdate,							// Update cache item's expiry parameters.
#ifdef _DEBUG
	ECacheDebugMarkEnd,							// Heap checking srvices for debug.
	ECacheDebugMarkHeap,
	ECacheDebugMarkFailNext,
#endif
	};

// Define the name of the cache server.
_LIT(KNameCacheServer,"CacheServer");

// And its semaphore name.
_LIT(KNameStartCacheSemaphore,"StartCacheServer");

// Define the version for the cache server
const TInt KWapCacheServerMajorVN=1;
const TInt KWapCacheServerMinorVN=0;
const TInt KWapCacheServerBuildVN=9;

#endif

