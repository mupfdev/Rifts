// S32PAGE.INL
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//

// Class TPageRef
inline TPageRef::TPageRef(TUint32 aValue)
	: iVal(aValue)
	{}
inline TBool TPageRef::operator==(TPageRef aRef) const
	{return iVal==aRef.iVal;}
inline TBool TPageRef::operator!=(TPageRef aRef) const
	{return iVal!=aRef.iVal;}
inline void TPageRef::ExternalizeL(RWriteStream& aStream) const
	{aStream<<iVal;}
inline void TPageRef::InternalizeL(RReadStream& aStream)
	{aStream>>iVal;}
inline TUint32 TPageRef::Value() const
	{return iVal;}

// Class MPagePool
inline void MPagePool::Pop()
	{CleanupStack::Pop();}

// Class CPageCache::TStats
#if defined(__PAGE_CACHE_STATS)
inline TInt CPageCache::TStats::Requests() const
	{return iRequests;}
inline TInt CPageCache::TStats::Hits() const
	{return iRequests-iMisses;}
inline TInt CPageCache::TStats::Misses() const
	{return iMisses;}
inline void CPageCache::TStats::Reset()
	{iRequests=0;iMisses=0;}
#endif

// Class CPageCache
#if defined(__PAGE_CACHE_STATS)
inline CPageCache::TStats& CPageCache::Stats()
	{return iStats;}
inline const CPageCache::TStats& CPageCache::Stats() const
	{return iStats;}
#endif

// Class TCachePagePool
inline void TCachePagePool::Set(CPageCache& aCache)
	{iCache=&aCache;}
inline TCachePagePool::TCachePagePool()
	: iCache(NULL)
	{}
inline TCachePagePool::TCachePagePool(CPageCache& aCache)
	: iCache(&aCache)
	{}

