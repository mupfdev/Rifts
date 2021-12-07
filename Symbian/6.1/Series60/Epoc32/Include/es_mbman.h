// ES_MBMAN.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//
//
// Buffer Manager for Protocols
//

#ifndef __ES_MBMAN_H__
#define __ES_MBMAN_H__

#if !defined(__ES_MBUF_H__)
# include <es_mbuf.h>
#endif

#if !defined(_MBUF_ALONE)
#include <es_prot.h> // for SocketTimer
#endif

// MBuf Private Heap Limits
const TUint KMBufMinHeapSize	    = 4*1024;
const TUint KMBufMaxHeapSize		= 128*1024;

class CMBufPool;
class CMBufManager;

#if defined (_MBUF_ALONE) && !defined(_MBUF_ALONE_AS_DLL)
IMPORT_C TInt MBufManagerInitialise();
IMPORT_C void MBufManagerShutdown();
#endif


#define ALIGN_MASK    0x03
#define ALIGN_UP(n)   (((n)+(ALIGN_MASK)) & ~ALIGN_MASK)
#define ALIGN_DOWN(n) ((n) & ~ALIGN_MASK)
#define IS_ALIGNED(p) ((((TUint32)(p)) & ALIGN_MASK)==0)

////////////////////////////////////////////////////////////////////////////////
// MBUF MANAGER
////////////////////////////////////////////////////////////////////////////////

const TUint KMBufWatchDogTime = 1000000;
const TInt KMBufFreePriority = 20;

class CMBufPoolReaper;
class Nif;
class CMBufManager : public CBase
	{
friend class CMBufPoolReaper;
friend class Nif;
private:
	CMBufManager();
public:
	IMPORT_C ~CMBufManager();
	IMPORT_C static CMBufManager *NewL();
	IMPORT_C void CreateL();
	IMPORT_C static CMBufManager *Context(); // Panics if no context!
//	IMPORT_C RMBuf* AllocL(TInt aSize = 0);
	IMPORT_C RMBuf* AllocL(TInt aSize = KMBufSmallSize);
	IMPORT_C void Free(RMBuf* aChain);
	IMPORT_C static void Panic(TMBufPanic aPanic);
	void StartRequest(RMBufAsyncRequest& aRequest);
	void CancelRequest(RMBufAsyncRequest& aRequest);
	static RHeap& Heap();
	TInt NumBufsToAlloc(TBool aPrimaryPool);
private:
	void MergePool(CMBufPool *aPool);
	void WatchDogReset();
	void WatchDogCancel();
	static TInt WatchDogExpire(TAny* aPtr);
	static TInt FreeCallBack(TAny* aPtr);
	void CompleteSmallRequests();
	void CompleteLargeRequests();
//
private:
	RHeap* iHeap;
	TInt iNumSmallBufs;
	TInt iNumSmallFree;
	TInt iSmallBufSpace;
	TInt iSmallBufTotal;
	RCriticalSection iLock;
	TDblQue<CMBufPool> iPools;
	RMBufQ iSmallBufs;
	TDblQue<RMBufAsyncRequest> iAllocsPending;
	TDeltaTimerEntry iWatchDog;
	TBool iWatchDogIsPending;
	CAsyncCallBack *iFreeCB;
	TCallBack iEnableReaper;
//
public:
	IMPORT_C static void __DbgCheckChain(RMBuf* aChain, TMBufType aType, TInt aLength, TInt aSize);
	IMPORT_C TInt __DbgCheckBuffer(RMBuf* aBuf);
	IMPORT_C static RHeap* __DbgSockServHeap();
	inline RMBuf* __DbgSmallBufChain() { return iSmallBufs.First(); } 
	inline void __DbgSetPoolLimit(TInt aCount=0) { __iPoolLimit = aCount - (aCount%KMBufSmallSize); }
	inline void __DbgSetFailAfter(TInt aCount=0) { __iFailAfter = aCount; }
	inline TInt __DbgGetBufSpace() { return iSmallBufSpace; }
	inline TInt __DbgGetBufTotal() { return iSmallBufTotal; }
private:
	TInt __iPoolLimit;	// Allows Max Size of pool to be set
	TInt __iFailAfter;	// Alloc Failure Request
	};

////////////////////////////////////////////////////////////////////////////////
// MBUF POOLS
////////////////////////////////////////////////////////////////////////////////


class CMBufPool : public CBase
	{
friend class CMBufPoolReaper;
private:
	CMBufPool();
public:
	~CMBufPool();
	static CMBufPool *NewL(TInt aNumBufs);
	void CreateL(TInt aNumBufs);
	void Merge(RMBufQ &aMainPool);
	inline TInt Count();
	static TAny* operator new(TUint aSiz, TLeave aLeave, TUint aExtra);
	static void operator delete(TAny* aPtr);
//
private:
	friend class CMBufManager;  // for access to iLink
	TDblQueLink iLink;
	RMBufQ iList;		// List of mbufs in this pool
	TInt iCount;		// Number of mbufs in this pool
	TUint8 *iPool;		// Allocated memory
//
public:
	IMPORT_C TInt __DbgCheckBuffer(RMBuf* aBuf);
	};

#include "es_mbman.inl"

#endif
