// S32PAGE.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//
#if !defined(__S32PAGE_H__)
#define __S32PAGE_H__
#if !defined(__S32STRM_H__)
#include <s32strm.h>
#endif

const TInt KPoolPageSize=512;
//
const TUint32 KNullPageRefValue=0;
//
class TPageRef
	{
public:
	inline TPageRef() {}
	inline TPageRef(TUint32 aValue);
//
	inline TBool operator==(TPageRef aRef) const;
	inline TBool operator!=(TPageRef aRef) const;
//
	inline void ExternalizeL(RWriteStream& aStream) const;
	inline void InternalizeL(RReadStream& aStream);
//
	inline TUint32 Value() const;
private:
	TUint32 iVal;
	};
#if defined(__NO_CLASS_CONSTS__)
#define KNullPageRef TPageRef(KNullPageRefValue)
#else
const TPageRef KNullPageRef=TPageRef(KNullPageRefValue);
#endif
//
class MPagePool;
typedef void (*TPageAbandonFunction)(MPagePool& aPool);
enum TPageReclamation {EPageDeleteOnly,EPageReclaimable};
enum TPageChange {EPageNoChange,EPageDirty,EPageUpdate,EPageAbandon=-1};
//
class MPagePool
	{
public:
	IMPORT_C void PushL();
	inline void Pop();
	virtual TPageAbandonFunction AcquireL()=0;
//
	virtual TAny* AllocL()=0;
	virtual TAny* LockL(TPageRef aRef)=0;
//
	virtual TPageRef AssignL(const TAny* aPage,TPageReclamation aReclamation=EPageDeleteOnly)=0;
	virtual void UpdateL(const TAny* aPage)=0;
	virtual void Unlock(const TAny* aPage,TPageChange aChange=EPageNoChange)=0;
//
	IMPORT_C void Delete(TPageRef aRef);
	IMPORT_C void DeleteL(TPageRef aRef);
protected:
	virtual void DoDeleteL(TPageRef aRef)=0;
	};
//
class CMemPagePool : public CBase,public MPagePool
	{
public:
	IMPORT_C static CMemPagePool* NewL();
	IMPORT_C static CMemPagePool* NewLC();
	IMPORT_C CMemPagePool();
	IMPORT_C ~CMemPagePool();
//
	IMPORT_C TPageAbandonFunction AcquireL();
	IMPORT_C TAny* AllocL();
	IMPORT_C TAny* LockL(TPageRef aRef);
	IMPORT_C TPageRef AssignL(const TAny* aPage,TPageReclamation aReclamation=EPageDeleteOnly);
	IMPORT_C void UpdateL(const TAny* aPage);
	IMPORT_C void Unlock(const TAny* aPage,TPageChange aChange=EPageNoChange);
protected:
	IMPORT_C void DoDeleteL(TPageRef aRef);
private:
	TAny*& PageL(TPageRef aRef);
	static void DoAbandon(MPagePool& aPool);
private:
	CArrayFixSeg<TAny*> iPages;
	};
//
#if defined(_DEBUG)&&!defined(__PAGE_CACHE_STATS)
//#define __PAGE_CACHE_STATS
#endif
//
class TCachePage;
struct SCachePage;
class TCachePagePool;
class CPageCache : public CBase
	{
public:
	enum {EDefaultPages=20};
#if defined(__PAGE_CACHE_STATS)
	class TStats
		{
	public:
		inline TInt Requests() const;
		inline TInt Hits() const;
		inline TInt Misses() const;
		inline void Reset();
	private:
		inline void Hit();
		inline void Miss();
	private:
		TInt iRequests;
		TInt iMisses;
	private:
		friend class CPageCache;
		};
#endif
public:
	IMPORT_C static CPageCache* NewL(TInt aPages=EDefaultPages);
	IMPORT_C static CPageCache* NewLC(TInt aPages=EDefaultPages);
	IMPORT_C CPageCache();
	IMPORT_C void ConstructL(TInt aPages=EDefaultPages);
	IMPORT_C ~CPageCache();
//
#if defined(__PAGE_CACHE_STATS)
	inline TStats& Stats();
	inline const TStats& Stats() const;
#endif
private:
	TCachePage* Find(TCachePagePool* aPool,TPageRef aRef);
private:
	SCachePage* iPages;
	SCachePage* iEnd;
	TDblQue<TCachePage> iFree;
#if defined(__PAGE_CACHE_STATS)
	TStats iStats;
#endif
private:
	friend class TCachePagePool;
	};
class TCachePagePool : public MPagePool
	{
public:
	inline void Set(CPageCache& aCache);
//
	IMPORT_C TPageAbandonFunction AcquireL();
	IMPORT_C TAny* AllocL();
	IMPORT_C TAny* LockL(TPageRef aRef);
	IMPORT_C TPageRef AssignL(const TAny* aPage,TPageReclamation aReclamation=EPageDeleteOnly);
	IMPORT_C void UpdateL(const TAny* aPage);
	IMPORT_C void Unlock(const TAny* aPage,TPageChange aChange=EPageNoChange);
//
	IMPORT_C TInt Flush();
	IMPORT_C void FlushL();
	IMPORT_C void Purge();
protected:
	inline TCachePagePool();
	inline TCachePagePool(CPageCache& aCache);
	IMPORT_C void DoDeleteL(TPageRef aRef);
private:
	virtual TPageRef ExtendL(const TAny* aPage,TPageReclamation aReclamation)=0;
	virtual void WriteL(TPageRef aRef,const TAny* aPage,TPageChange aChange)=0;
	virtual void ReadL(TPageRef aRef,TAny* aPage)=0;
//
	static void DoAbandon(MPagePool& aPool);
	static TCachePage* DoAllocL(CPageCache& aCache);
private:
	CPageCache* iCache;
	};

#include <s32page.inl>
#endif
