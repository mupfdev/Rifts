// 
// CManOb.h
// Copyright (C) 1997-1998 Symbian Ltd. All rights reserved.
//

// 
// Created at: 16-Jan-99 13:16:34 AM
// Comments: Definition of the cache manager observer abstract class
//			 together with the enumeration for notifications from the cache
//			 server.
// 

#if !defined(__CMANOB_H__)
#define __CMANOB_H__


//////////////////////////////////////////////////////////////////////////////
// This class is intended to be used to provide notification messages to
// a Cache Server client of changes to the underlying cache database.
// e.g. for additions, deletions or modifications to the cache items available.
// It is used by the classes defined in CMan.h
//
class MCacheManagerObserver
	{
	public:
	/////////////////////////////////////////////////////////////////////////////// 
	// TCacheChange is the enumerator indicating what change has happened
	// to prompt the call to the MCacheManagerObserver 
	//
	enum TCacheChange
		{
		ERemoved,		// A cache item has been removed
		EAdded,			// A cache item has been added
		EDisabled,		// A cache item has been disabled
		EEnabled,		// A cache item has been enabled/re-enabled
		EDeleted,		// A cache item has been deleted
		EReIndexed		// A cache item has been re-indexed. (Not supported in this version).
		};
	// The only method on the observer
	virtual void DataChanged(TInt aStatus) = 0;
	
private:
	// Reserved for future expansion
	IMPORT_C virtual void MCacheManagerObserverReserved1();
	IMPORT_C virtual void MCacheManagerObserverReserved1() const;
	};

#endif // __CMANOB_H__