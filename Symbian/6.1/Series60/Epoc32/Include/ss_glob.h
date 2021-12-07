// SS_GLOB.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// Socket server global (TLS) data

// Structure of the pseudo statics stored in Dll local storage.

#ifndef __SS_GLOB_H__
#define __SS_GLOB_H__

#include <ss_pman.h>

class CSocketServer;
class CMBufManager;
class CShutdownWatchDog;

class TSockManData
	{
public:
	CSocketServer *iSocketServer;			// Back pointer to the CServer (for shutdown)
	TSglQue<CProtocolRef> *iProtocols;	// List of all socket types available
	TSglQue<CProtocolFamilyRef> *iProtocolFamilies;	// List of all protocol families used
	TUint iNumProtocols;					// Count of protocols.
	RHeap *iSockManHeap;					// The socket servers heap.
	CObjectConIx *iContainer;				// Container for our CObjectIxs
	CObjectCon *iHandles;					// Our handles.
	CMBufManager* iMBufManager;				// The MBuf manager
	CDeltaTimer* iTimer;					// The global delta timer.
	TInt iNumSessions;						// Keep a counter of the sessions
	TInt iNumFamilies;
	CShutdownWatchDog* iShutdownWatchDog;
	TBool iShuttingDown;					// Flag to govern the way protocols are shutdown
	TDblQue<CSocketServExtRef> iExtensions; // List of socket server extensions
public:
	TSockManData();
	};
//

class SockManGlobals
	{
public:
	inline static TSockManData* Get();
	inline static void Set(TSockManData * aGlobals);
	};

#include "ss_glob.inl"

#endif
