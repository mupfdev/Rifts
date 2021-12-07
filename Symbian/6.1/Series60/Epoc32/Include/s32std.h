// S32STD.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//
#if !defined(__S32STD_H__)
#define __S32STD_H__
#if !defined(__S32STRM_H__)
#include <s32strm.h>
#endif

const TUint32 KNullStreamIdValue=0;
const TUint32 KMaxStreamIdValue=0xfffffff;
const TUint32 KMaskStreamIdValue=0xfffffff;
const TInt KShiftStreamIdValue=28;
//
class TStreamId
	{
public:
	TStreamId() {}
	inline TStreamId(TUint32 aValue);
//
	inline TBool operator==(TStreamId anId) const;
	inline TBool operator!=(TStreamId anId) const;
//
	inline void ExternalizeL(RWriteStream& aStream) const;
	IMPORT_C void InternalizeL(RReadStream& aStream);
//
	inline TUint32 Value() const;
private:
	TUint32 iVal;
private:
	IMPORT_C static void __DbgChkRange(TUint32 aValue);
	};
#if defined(__NO_CLASS_CONSTS__)
#define KNullStreamId TStreamId(KNullStreamIdValue)
#else
const TStreamId KNullStreamId=TStreamId(KNullStreamIdValue);
#endif
//
class CStreamStore;
class RStoreReadStream : public RReadStream
	{
public:
	IMPORT_C void OpenL(const CStreamStore& aStore,TStreamId anId);
	IMPORT_C void OpenLC(const CStreamStore& aStore,TStreamId anId);
	};
class RStoreWriteStream : public RWriteStream
	{
public:
	RStoreWriteStream() {}
	inline RStoreWriteStream(const MExternalizer<TStreamRef>& anExter);
	IMPORT_C TStreamId CreateL(CStreamStore& aStore);
	IMPORT_C TStreamId CreateLC(CStreamStore& aStore);
	IMPORT_C void OpenL(CStreamStore& aStore,TStreamId anId);
	IMPORT_C void OpenLC(CStreamStore& aStore,TStreamId anId);
	IMPORT_C void ReplaceL(CStreamStore& aStore,TStreamId anId);
	IMPORT_C void ReplaceLC(CStreamStore& aStore,TStreamId anId);
	IMPORT_C void AppendL(CStreamStore& aStore,TStreamId anId);
	IMPORT_C void AppendLC(CStreamStore& aStore,TStreamId anId);
	};
//
class TSwizzleCBase
	{
public:
	inline TBool operator==(const TSwizzleCBase& aSwizzle) const;
	inline TBool operator==(const TAny* aPtr) const;
	inline TBool operator!=(const TSwizzleCBase& aSwizzle) const;
	inline TBool operator!=(const TAny* aPtr) const;
//
	inline TBool IsPtr() const;
	inline TBool IsId() const;
	IMPORT_C TStreamId AsId() const;
	IMPORT_C void InternalizeL(RReadStream& aStream);
protected:
	TSwizzleCBase() {}
	inline TSwizzleCBase(const TAny* aPtr);
	IMPORT_C TSwizzleCBase(TStreamId anId);
	inline TSwizzleCBase(TStreamRef aRef);
	inline const TAny* Ptr() const;
	IMPORT_C void DoExternalizeL(RWriteStream& aStream,TExternalizer<TAny> anExter) const;
private:
	IMPORT_C static TBool IsPtrRep(const TAny* aPtr);
	IMPORT_C static TBool IsIdRep(const TAny* aPtr);
private:
	const TAny* iPtr;
private:
	IMPORT_C static void __DbgChkPtr(const TAny* aPtr);
	IMPORT_C static void __DbgChkRef(TStreamRef aRef);
	};
inline TBool operator==(const TAny* aPtr,const TSwizzleCBase& aSwizzle);
inline TBool operator!=(const TAny* aPtr,const TSwizzleCBase& aSwizzle);
class TSwizzleBase : public TSwizzleCBase
	{
protected:
	TSwizzleBase() {}
	inline TSwizzleBase(TAny* aPtr);
	inline TSwizzleBase(TStreamId anId);
	inline TAny* Ptr() const;
	};
//
template <class T>
class TSwizzle : public TSwizzleBase
	{
public:
	TSwizzle() {}
	inline TSwizzle(T* aPtr);
	inline TSwizzle(TStreamId anId);
	inline TSwizzle<T>& operator=(T* aPtr);
	inline T* AsPtr() const;
	inline operator T*() const;
	inline T& operator*() const;
	inline T* operator->() const;
	inline void ExternalizeL(RWriteStream& aStream) const;
	};
TEMPLATE_SPECIALIZATION class TSwizzle<TAny> : public TSwizzleBase
	{
public:
	TSwizzle() {}
	inline TSwizzle(TAny* aPtr);
	inline TSwizzle(TStreamId anId);
	inline TSwizzle(const TSwizzleBase& aSwizzle);
	inline TSwizzle<TAny>& operator=(TAny* aPtr);
	inline TSwizzle<TAny>& operator=(const TSwizzleBase& aSwizzle);
	inline TAny* AsPtr() const;
	inline operator TAny*() const;
	};
template <class T>
class TSwizzleC : public TSwizzleCBase
	{
public:
	TSwizzleC() {}
	inline TSwizzleC(const T* aPtr);
	inline TSwizzleC(TStreamId anId);
	inline TSwizzleC(TSwizzle<T> aSwizzle);
	inline TSwizzleC<T>& operator=(const T* aPtr);
	inline const T* AsPtr() const;
	inline operator const T*() const;
	inline const T& operator*() const;
	inline const T* operator->() const;
	inline void ExternalizeL(RWriteStream& aStream) const;
	};
TEMPLATE_SPECIALIZATION class TSwizzleC<TAny> : public TSwizzleCBase
	{
public:
	TSwizzleC() {}
	inline TSwizzleC(const TAny* aPtr);
	inline TSwizzleC(TStreamId anId);
	inline TSwizzleC(const TSwizzleCBase& aSwizzle);
	inline TSwizzleC(TStreamRef aRef);
	inline TSwizzleC<TAny>& operator=(const TAny* aPtr);
	inline TSwizzleC<TAny>& operator=(const TSwizzleCBase& aSwizzle);
	inline const TAny* AsPtr() const;
	inline operator const TAny*() const;
	};
//
class CStoreMap : public CBase,public MExternalizer<TStreamRef>
	{
public:
	struct TEntry {TSwizzleC<TAny> swizzle;TStreamId id;};
	typedef const TEntry* TIterator;
public:
	IMPORT_C static CStoreMap* NewL(CStreamStore& aStore);
	IMPORT_C static CStoreMap* NewLC(CStreamStore& aStore);
	IMPORT_C CStoreMap(CStreamStore& aStore);
	IMPORT_C ~CStoreMap();
//
	IMPORT_C void BindL(TSwizzleC<TAny> aSwizzle,TStreamId anId);
	IMPORT_C void Unbind(TSwizzleC<TAny> aSwizzle);
	IMPORT_C void Forget(TStreamId anId);
	IMPORT_C void Reset();
	IMPORT_C void ResetAndDestroy();
//
	IMPORT_C TStreamId At(TSwizzleC<TAny> aSwizzle) const;
	IMPORT_C TSwizzleC<TAny> Label(TStreamId anId) const;
	IMPORT_C TIterator Begin() const;
	IMPORT_C TIterator End() const;
private:
	void ExternalizeL(const TStreamRef& aRef,RWriteStream& aStream) const;
private:
	CArrayFixFlat<TEntry> iArray;
	TStreamId iFree;
	CStreamStore* iStore;
	};
//
class CStreamDictionary : public CBase
	{
public:
	IMPORT_C static CStreamDictionary* NewL();
	IMPORT_C static CStreamDictionary* NewLC();
	IMPORT_C CStreamDictionary();
	IMPORT_C ~CStreamDictionary();
//
	IMPORT_C void AssignL(TUid aUid,TStreamId anId);
	IMPORT_C void Remove(TUid aUid);
	IMPORT_C TStreamId At(TUid aUid) const;
	IMPORT_C TBool IsNull() const;
	//
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	IMPORT_C void InternalizeL(RReadStream& aStream);
private:
	class TEntry
		{
	public:
		TEntry() {}
		inline TEntry(TUid aUid,TStreamId anId);
		void ExternalizeL(RWriteStream& aStream) const;
		void InternalizeL(RReadStream& aStream);
	public:
		TUid iUid;
		TStreamId iId;
		};
private:
	CArrayFixSeg<TEntry> iArray;
	};

#include <s32std.inl>
#endif
