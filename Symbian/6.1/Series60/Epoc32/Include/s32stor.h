// S32STOR.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//
#if !defined(__S32STOR_H__)
#define __S32STOR_H__
#if !defined(__S32STD_H__)
#include <s32std.h>
#endif
#if !defined(__S32SHARE_H__)
#include <s32share.h>
#endif
#if !defined(__S32PAGE_H__)
#include <s32page.h>
#endif

class MIncrementalCollector;
class CStreamStore : public CBase
	{
public:
	inline TStreamId ExtendL();
	IMPORT_C void Delete(TStreamId anId);
	IMPORT_C void DeleteL(TStreamId anId);
//
	IMPORT_C TInt Commit();
	inline void CommitL();
	IMPORT_C void Revert();
	inline void RevertL();
//
	IMPORT_C TInt ReclaimL();
	IMPORT_C TInt CompactL();
private:
	virtual IMPORT_C TStreamId DoExtendL();
	virtual IMPORT_C void DoDeleteL(TStreamId anId);
	virtual MStreamBuf* DoReadL(TStreamId anId) const=0;
	virtual MStreamBuf* DoCreateL(TStreamId& anId)=0;
	virtual IMPORT_C MStreamBuf* DoWriteL(TStreamId anId);
	virtual IMPORT_C MStreamBuf* DoReplaceL(TStreamId anId);
	virtual IMPORT_C void DoCommitL();
	virtual IMPORT_C void DoRevertL();
	virtual IMPORT_C MIncrementalCollector* DoReclaimL();
	virtual IMPORT_C MIncrementalCollector* DoCompactL();
private:
	friend class RStoreReadStream;
	friend class RStoreWriteStream;
	friend class RStoreReclaim;
	};
class CPersistentStore : public CStreamStore
	{
public:
	inline TStreamId Root() const;
	inline void SetRootL(TStreamId anId);
protected:
	inline CPersistentStore();
private:
	virtual IMPORT_C void DoSetRootL(TStreamId anId);
protected:
	TStreamId iRoot;
	};
//
class RStoreReclaim
	{
public:
	inline RStoreReclaim();
	IMPORT_C void OpenL(CStreamStore& aStore,TInt& aCount);
	IMPORT_C void OpenLC(CStreamStore& aStore,TInt& aCount);
	IMPORT_C void CompactL(CStreamStore& aStore,TInt& aCount);
	IMPORT_C void CompactLC(CStreamStore& aStore,TInt& aCount);
	inline void Close();
	IMPORT_C void Release();
//
	IMPORT_C void ResetL(TInt& aCount);
	IMPORT_C void NextL(TInt& aStep);
	IMPORT_C void Next(TPckgBuf<TInt>& aStep,TRequestStatus& aStatus);
	IMPORT_C void NextL(TPckgBuf<TInt>& aStep,TRequestStatus& aStatus);
	IMPORT_C TInt Next(TInt& aStep);
//
	inline TInt Available() const;
private:
	MIncrementalCollector* iCol;
	TPckgBuf<TInt> iAvail;
	};
//
class CEmbeddedStore : public CPersistentStore
	{
public:
	IMPORT_C static CEmbeddedStore* FromL(RReadStream& aHost);
	IMPORT_C static CEmbeddedStore* FromLC(RReadStream& aHost);
	IMPORT_C static CEmbeddedStore* NewL(RWriteStream& aHost);
	IMPORT_C static CEmbeddedStore* NewLC(RWriteStream& aHost);
//
	inline static TStreamPos Position(TStreamId anId);
//
	IMPORT_C void Detach();
	inline void Reattach(MStreamBuf* aHost);
	inline MStreamBuf* Host() const;
	inline TStreamPos Start() const;
//
	IMPORT_C CEmbeddedStore(MStreamBuf* aHost);
	IMPORT_C void MarshalL(RReadStream& aStream);
	IMPORT_C void ConstructL(RWriteStream& aStream);
	IMPORT_C ~CEmbeddedStore();
protected:
	IMPORT_C MStreamBuf* DoReadL(TStreamId anId) const;
	IMPORT_C MStreamBuf* DoCreateL(TStreamId& anId);
private:
	IMPORT_C void DoSetRootL(TStreamId anId);
	IMPORT_C void DoCommitL();
//
	static CEmbeddedStore* DoNewLC(MStreamBuf* aHost);
private:
	__MUTABLE TStreamExchange iHost;
	TStreamPos iStart;
	};
//
class CDictionaryStore : public CBase
	{
public:
	IMPORT_C TBool IsNullL() const;
	IMPORT_C TBool IsPresentL(TUid aUid) const;
	IMPORT_C void Remove(TUid aUid);
	IMPORT_C void RemoveL(TUid aUid);
//
	IMPORT_C TInt Commit();
	IMPORT_C void CommitL();
	IMPORT_C void Revert();
	IMPORT_C void RevertL();
//
	IMPORT_C ~CDictionaryStore();
protected:
	IMPORT_C void ConstructL();
private:
	CStreamDictionary* DictionaryL() const;
	MStreamBuf* GetSourceL(TUid aUid) const;
	MStreamBuf* GetSinkL(TUid aUid);
protected:
	CPersistentStore* iStore;
private:
	__MUTABLE CStreamDictionary* iDictionary;
	TBool iDictionaryHasChanged;
private:
	friend class RDictionaryReadStream;
	friend class RDictionaryWriteStream;
	friend class HDictionaryStoreBuf;
	};
//
const TInt KDictionaryCommitThreshold = 1024;
//
class RDictionaryReadStream : public RReadStream
	{
public:
	IMPORT_C void OpenL(const CDictionaryStore& aDictStore,TUid aUid);
	IMPORT_C void OpenLC(const CDictionaryStore& aDictStore,TUid aUid);
	};
class RDictionaryWriteStream : public RWriteStream
	{
public:
	RDictionaryWriteStream() {}
	inline RDictionaryWriteStream(const MExternalizer<TStreamRef>& anExter);
	IMPORT_C void AssignL(CDictionaryStore& aDictStore,TUid aUid);
	IMPORT_C void AssignLC(CDictionaryStore& aDictStore,TUid aUid);
	};
//
class TStorePagePoolToken
	{
public:
	enum TEmpty {EEmpty};
public:
	TStorePagePoolToken() {}
	inline TStorePagePoolToken(TEmpty);
	inline void Touch();
//
	inline TBool HasAvailable() const;
	inline TBool IsEmpty() const;
//
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	IMPORT_C void InternalizeL(RReadStream& aStream);
private:
	inline TStorePagePoolToken(TStreamId aHead,TPageRef anAvail);
private:
	TStreamId iHead;
	TPageRef iAvail;
private:
	friend class RStorePagePool;
	};
#if defined(__NO_CLASS_CONSTS__)
#define KEmptyStorePagePoolToken TStorePagePoolToken(TStorePagePoolToken::EEmpty)
#else
const TStorePagePoolToken KEmptyStorePagePoolToken=TStorePagePoolToken::EEmpty;
#endif
//
class RStorePagePool : public TCachePagePool
	{
	friend class StorePagePool;
public:
	IMPORT_C RStorePagePool();
	IMPORT_C RStorePagePool(CPageCache& aCache);
	IMPORT_C RStorePagePool(CStreamStore& aStore);
	IMPORT_C RStorePagePool(CStreamStore& aStore,const TStorePagePoolToken& aToken);
	IMPORT_C void Create(CStreamStore& aStore);
	IMPORT_C void Open(CStreamStore& aStore,const TStorePagePoolToken& aToken);
	IMPORT_C TStorePagePoolToken Token() const;
	IMPORT_C void Close();
	inline void Release();
//
	inline TBool IsDirty() const;
	inline void MarkCurrent();
	inline void MarkDirty();
//
	inline TBool HasAvailable() const;
	inline void Discard();
//
	inline TBool IsEmpty() const;
	IMPORT_C TBool ReclaimL();
	IMPORT_C void ReclaimAllL();
protected:
	IMPORT_C TPageRef ExtendL(const TAny* aPage,TPageReclamation aReclamation);
	IMPORT_C void WriteL(TPageRef aRef,const TAny* aPage,TPageChange aChange);
	IMPORT_C void ReadL(TPageRef aRef,TAny* aPage);
	IMPORT_C void DoDeleteL(TPageRef aRef);
private:
	inline void CacheDeleteL(TPageRef aRef);
private:
	CStreamStore* iStore;
	TStreamId iHead;
	TPageRef iAvail;
	TBool iDirty;
	};
//
class MIncrementalCollector
	{
public:
	inline void Close();
	inline void Release();
//
	inline void ResetL(TInt& aCount);
	inline void NextL(TInt& aStep,TInt& aTotal);
	inline void NextL(TPckgBuf<TInt>& aStep,TRequestStatus& aStatus,TPckgBuf<TInt>& aTotal);
protected:
	MIncrementalCollector() {}
private:
	MIncrementalCollector(const MIncrementalCollector&);
	MIncrementalCollector& operator=(const MIncrementalCollector&);
//
	virtual IMPORT_C void DoRelease();
	virtual void DoResetL(TInt& aCount)=0;
	virtual void DoNextL(TInt& aStep,TInt& aTotal)=0;
	virtual IMPORT_C void DoNextL(TPckgBuf<TInt>& aStep,TRequestStatus& aStatus,TPckgBuf<TInt>& aTotal);
	};

#include <s32stor.inl>
#endif
