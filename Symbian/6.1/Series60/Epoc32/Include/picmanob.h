// 
// PiCManOb.h
// Copyright (C) 1997-1998 Symbian Ltd. All rights reserved.
// 
// Created at: 16-Jan-99 13:16:34 AM

//
// Comments: Definition of the plugin cache manager observer abstract class
//			 together with the enumeration for notifications from the plugin
//			 server.
// 

#if !defined(__PICMANOB_H__)
#define __PICMANOB_H__

/////////////////////////////////////////////////////////////////////////////// 
// TPluginChange is the enumerator indicating what change has happened
// to prompt the call to the MPluginCacheManagerObserver 
//
enum TPluginChange
	{
	ERemoved = 1000,// A plugin(s) has been removed. (Its DLL is no longer available).
	EAdded,			// "	"		"	"	added.
	EDisabled,		// "	"		"	"	disabled.
	EEnabled,		// "	"		"	"	enabled/re-enabled.
	EDeleted,		// "	"		"	"	deleted. (An individual plugin has been deleted).
	EReIndexed		// "	"		"	"	re-indexed by the server. (Not currently supported).
#ifdef _DEBUG
	,ETestNotification = 0xBDE
#endif
	};

//////////////////////////////////////////////////////////////////////////////
//
// This class is intended to be used to define the interface required to
// provide notification messages to a Plugin Server client of changes
// to the underlying plugin database.
// e.g. for additions, deletions or modifications to the plugins available.
// It is used by the classes defined in PicMan.h
//
class MPluginCacheManagerObserver
	{
public:
	IMPORT_C virtual void DataChanged(TInt aStatus) = 0;

private:
	// Reserved for future expansion
	IMPORT_C virtual void MPluginCacheManagerObserverReserved1();
	IMPORT_C virtual void MPluginCacheManagerObserverReserved1() const;
	};

#endif // __PICMANOB_H__