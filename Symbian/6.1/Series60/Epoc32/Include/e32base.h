// E32BASE.H
//
// Copyright (c) 1994-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __E32BASE_H__
#define __E32BASE_H__
#include <e32std.h>

/**
 * Container Base Class
 */
class CBase
	{
public:
	IMPORT_C virtual ~CBase();
	inline TAny* operator new(TUint aSize,TAny *aBase);
	IMPORT_C TAny* operator new(TUint aSize);
	inline TAny* operator new(TUint aSize, TLeave);
	IMPORT_C TAny* operator new(TUint aSize,TUint anExtraSize);
protected:
	IMPORT_C CBase();
private:
	CBase(const CBase&);
	CBase& operator=(const CBase&);
	IMPORT_C static TAny* newL(TUint aSize);
	};
//
class CBufBase : public CBase
	{
public:
	IMPORT_C ~CBufBase();
	inline TInt Size() const;
	IMPORT_C void Reset();
	IMPORT_C void Read(TInt aPos,TDes8& aDes) const;
	IMPORT_C void Read(TInt aPos,TDes8& aDes,TInt aLength) const;
	IMPORT_C void Read(TInt aPos,TAny* aPtr,TInt aLength) const;
	IMPORT_C void Write(TInt aPos,const TDesC8& aDes);
	IMPORT_C void Write(TInt aPos,const TDesC8& aDes,TInt aLength);
	IMPORT_C void Write(TInt aPos,const TAny* aPtr,TInt aLength);
	IMPORT_C void InsertL(TInt aPos,const TDesC8& aDes);
	IMPORT_C void InsertL(TInt aPos,const TDesC8& aDes,TInt aLength);
	IMPORT_C void InsertL(TInt aPos,const TAny* aPtr,TInt aLength);
	IMPORT_C void ExpandL(TInt aPos,TInt aLength);
	IMPORT_C void ResizeL(TInt aSize);
// Pure virtual
    virtual void Compress()=0;
	virtual void Delete(TInt aPos,TInt aLength)=0;
	virtual TPtr8 Ptr(TInt aPos)=0;
	virtual TPtr8 BackPtr(TInt aPos)=0;
private:
	virtual void DoInsertL(TInt aPos,const TAny* aPtr,TInt aLength)=0;
protected:
	IMPORT_C CBufBase(TInt anExpandSize);
protected:
	TInt iSize;
	TInt iExpandSize;
	};
//
class CBufFlat : public CBufBase
	{
public:
	IMPORT_C ~CBufFlat();
	IMPORT_C static CBufFlat* NewL(TInt anExpandSize);
	inline TInt Capacity() const;
	IMPORT_C void SetReserveL(TInt aSize);
	IMPORT_C void Compress();
	IMPORT_C void Delete(TInt aPos,TInt aLength);
	IMPORT_C TPtr8 Ptr(TInt aPos);
	IMPORT_C TPtr8 BackPtr(TInt aPos);
protected:
	IMPORT_C CBufFlat(TInt anExpandSize);
private:
	IMPORT_C void DoInsertL(TInt aPos,const TAny* aPtr,TInt aLength);
private:
	TInt iMaxSize;
	TUint8* iPtr;
	};
//
class TBufSegLink;
class CBufSeg : public CBufBase
	{
public:
	IMPORT_C ~CBufSeg();
	IMPORT_C static CBufSeg* NewL(TInt anExpandSize);
    IMPORT_C void Compress();
	IMPORT_C void Delete(TInt aPos,TInt aLength);
	IMPORT_C TPtr8 Ptr(TInt aPos);
	IMPORT_C TPtr8 BackPtr(TInt aPos);
protected:
	IMPORT_C CBufSeg(TInt anExpandSize);
	void InsertIntoSegment(TBufSegLink* aSeg,TInt anOffset,const TAny* aPtr,TInt aLength);
	void DeleteFromSegment(TBufSegLink* aSeg,TInt anOffset,TInt aLength);
	void FreeSegment(TBufSegLink* aSeg);
    void SetSBO(TInt aPos);
	void AllocSegL(TBufSegLink* aSeg,TInt aNumber);
private:
	IMPORT_C void DoInsertL(TInt aPos,const TAny* aPtr,TInt aLength);
private:
    TDblQue<TBufSegLink> iQue;
	TBufSegLink* iSeg;
	TInt iBase;
	TInt iOffset;
	};
//
class TKeyArrayFix : public TKey
	{
public:
	IMPORT_C TKeyArrayFix(TInt anOffset,TKeyCmpText aType);
	IMPORT_C TKeyArrayFix(TInt anOffset,TKeyCmpText aType,TInt aLength);
	IMPORT_C TKeyArrayFix(TInt anOffset,TKeyCmpNumeric aType);
protected:
	IMPORT_C virtual void Set(CBufBase* aBase,TInt aRecordLength);
	IMPORT_C TAny* At(TInt anIndex) const;
protected:
	TInt iRecordLength;
	CBufBase* iBase;
	friend class CArrayFixBase;
	};
//
typedef CBufBase*(*TBufRep)(TInt anExpandSize);
class CArrayFixBase : public CBase
	{
public:
	IMPORT_C ~CArrayFixBase();
	inline TInt Count() const;
	inline TInt Length() const;
	IMPORT_C void Compress();
	IMPORT_C void Reset();
	IMPORT_C TInt Sort(TKeyArrayFix& aKey);
	IMPORT_C TAny* At(TInt anIndex) const;
	IMPORT_C TAny* End(TInt anIndex) const;
	IMPORT_C TAny* Back(TInt anIndex) const;
	IMPORT_C void Delete(TInt anIndex);
	IMPORT_C void Delete(TInt anIndex,TInt aCount);
	IMPORT_C TAny* ExpandL(TInt anIndex);
	IMPORT_C TInt Find(const TAny* aPtr,TKeyArrayFix& aKey,TInt& anIndex) const;
	IMPORT_C TInt FindIsq(const TAny* aPtr,TKeyArrayFix& aKey,TInt& anIndex) const;
	IMPORT_C void InsertL(TInt anIndex,const TAny* aPtr);
	IMPORT_C void InsertL(TInt anIndex,const TAny* aPtr,TInt aCount);
	IMPORT_C TInt InsertIsqL(const TAny* aPtr,TKeyArrayFix& aKey);
	IMPORT_C TInt InsertIsqAllowDuplicatesL(const TAny* aPtr,TKeyArrayFix& aKey);
	IMPORT_C void ResizeL(TInt aCount,const TAny* aPtr);
protected:
	IMPORT_C CArrayFixBase(TBufRep aRep,TInt aRecordLength,TInt aGranularity);
	IMPORT_C void InsertRepL(TInt anIndex,const TAny* aPtr,TInt aReplicas);
	IMPORT_C void SetKey(TKeyArrayFix& aKey) const;
	IMPORT_C void SetReserveFlatL(TInt aCount);
	IMPORT_C static TInt CountR(const CBase* aPtr);
	IMPORT_C static const TAny* AtR(const CBase* aPtr,TInt anIndex);
private:
	TInt iCount;
	TInt iGranularity;
	TInt iLength;
	TBufRep iCreateRep;
	CBufBase* iBase;
	};
//
template <class T>
class CArrayFix : public CArrayFixBase
	{
public:
	inline CArrayFix(TBufRep aRep,TInt aGranularity);
	inline const T& operator[](TInt anIndex) const;
	inline T& operator[](TInt anIndex);
	inline const T& At(TInt anIndex) const;
	inline const T* End(TInt anIndex) const;
	inline const T* Back(TInt anIndex) const;
	inline T& At(TInt anIndex);
	inline T* End(TInt anIndex);
	inline T* Back(TInt anIndex);
	inline void AppendL(const T& aRef);
	inline void AppendL(const T* aPtr,TInt aCount);
	inline void AppendL(const T& aRef,TInt aReplicas);
	inline T& ExpandL(TInt anIndex);
	inline T& ExtendL();
	inline TInt Find(const T& aRef,TKeyArrayFix& aKey,TInt& anIndex) const;
	inline TInt FindIsq(const T& aRef,TKeyArrayFix& aKey,TInt& anIndex) const;
	inline void InsertL(TInt anIndex,const T& aRef);
	inline void InsertL(TInt anIndex,const T* aPtr,TInt aCount);
	inline void InsertL(TInt anIndex,const T& aRef,TInt aReplicas);
	inline TInt InsertIsqL(const T& aRef,TKeyArrayFix& aKey);
	inline TInt InsertIsqAllowDuplicatesL(const T& aRef,TKeyArrayFix& aKey);
	inline void ResizeL(TInt aCount);
	inline void ResizeL(TInt aCount,const T& aRef);
	inline const TArray<T> Array() const;
	};
TEMPLATE_SPECIALIZATION class CArrayFix<TAny> : public CArrayFixBase
	{
public:
	inline CArrayFix(TBufRep aRep,TInt aRecordLength,TInt aGranularity);
	inline const TAny* At(TInt anIndex) const;
	inline const TAny* End(TInt anIndex) const;
	inline const TAny* Back(TInt anIndex) const;
	inline TAny* At(TInt anIndex);
	inline TAny* End(TInt anIndex);
	inline TAny* Back(TInt anIndex);
	inline void AppendL(const TAny* aPtr);
	inline void AppendL(const TAny* aPtr,TInt aCount);
	inline TAny* ExtendL();
	};
//
template <class T>
class CArrayFixFlat : public CArrayFix<T>
	{
public:
	inline CArrayFixFlat(TInt aGranularity);
	inline void SetReserveL(TInt aCount);
	};
TEMPLATE_SPECIALIZATION class CArrayFixFlat<TAny> : public CArrayFix<TAny>
	{
public:
	inline CArrayFixFlat(TInt aRecordLength,TInt aGranularity);
	inline void SetReserveL(TInt aCount);
	};
TEMPLATE_SPECIALIZATION class CArrayFixFlat<TInt> : public CArrayFix<TInt>
	{
public:
	IMPORT_C CArrayFixFlat(TInt aGranularity);
	IMPORT_C ~CArrayFixFlat();
	inline void SetReserveL(TInt aCount);
	};
TEMPLATE_SPECIALIZATION class CArrayFixFlat<TUid> : public CArrayFix<TUid>
	{
public:
	IMPORT_C CArrayFixFlat(TInt aGranularity);
	IMPORT_C ~CArrayFixFlat();
	inline void SetReserveL(TInt aCount);
	};
//
template <class T>
class CArrayFixSeg : public CArrayFix<T>
	{
public:
	inline CArrayFixSeg(TInt aGranularity);
	};
TEMPLATE_SPECIALIZATION class CArrayFixSeg<TAny> : public CArrayFix<TAny>
	{
public:
	inline CArrayFixSeg(TInt aRecordLength,TInt aGranularity);
	};
//
template <class T>
class CArrayPtr : public CArrayFix<T*>
	{
public:
	inline CArrayPtr(TBufRep aRep,TInt aGranularity);
    void ResetAndDestroy();
	};
//
template <class T>
class CArrayPtrFlat : public CArrayPtr<T>
	{
public:
	inline CArrayPtrFlat(TInt aGranularity);
	inline void SetReserveL(TInt aCount);
	};
//
template <class T>
class CArrayPtrSeg : public CArrayPtr<T>
	{
public:
	inline CArrayPtrSeg(TInt aGranularity);
	};
//
class TKeyArrayVar : public TKey
	{
public:
	IMPORT_C TKeyArrayVar(TInt anOffset,TKeyCmpText aType);
	IMPORT_C TKeyArrayVar(TInt anOffset,TKeyCmpText aType,TInt aLength);
	IMPORT_C TKeyArrayVar(TInt anOffset,TKeyCmpNumeric aType);
protected:
	IMPORT_C virtual void Set(CBufBase* aBase);
	IMPORT_C TAny* At(TInt anIndex) const;
protected:
	CBufBase* iBase;
	friend class CArrayVarBase;
	};
//
class CArrayVarBase : public CBase
	{
public:
	IMPORT_C ~CArrayVarBase();
	inline TInt Count() const;
	IMPORT_C TInt Length(TInt anIndex) const;
	IMPORT_C void Compress();
	IMPORT_C void Reset();
	IMPORT_C TInt Sort(TKeyArrayVar& aKey);
	IMPORT_C TAny* At(TInt anIndex) const;
	IMPORT_C void Delete(TInt anIndex);
	IMPORT_C void Delete(TInt anIndex,TInt aCount);
	IMPORT_C TAny* ExpandL(TInt anIndex,TInt aLength);
	IMPORT_C TInt Find(const TAny* aPtr,TKeyArrayVar& aKey,TInt& anIndex) const;
	IMPORT_C TInt FindIsq(const TAny* aPtr,TKeyArrayVar& aKey,TInt& anIndex) const;
	IMPORT_C void InsertL(TInt anIndex,const TAny* aPtr,TInt aLength);
	IMPORT_C TInt InsertIsqL(const TAny* aPtr,TInt aLength,TKeyArrayVar& aKey);
	IMPORT_C TInt InsertIsqAllowDuplicatesL(const TAny* aPtr,TInt aLength,TKeyArrayVar& aKey);
protected:
	IMPORT_C CArrayVarBase(TBufRep aRep,TInt aGranularity);
	IMPORT_C void SetKey(TKeyArrayVar& aKey) const;
	IMPORT_C static TInt CountR(const CBase* aPtr);
	IMPORT_C static const TAny* AtR(const CBase* aPtr,TInt anIndex);
private:
	TInt iCount;
	TInt iGranularity;
	TBufRep iCreateRep;
	CBufBase* iBase;
	};
//
template <class T>
class CArrayVar : public CArrayVarBase
	{
public:
	inline CArrayVar(TBufRep aRep,TInt aGranularity);
	inline const T& operator[](TInt anIndex) const;
	inline T& operator[](TInt anIndex);
	inline const T& At(TInt anIndex) const;
	inline T& At(TInt anIndex);
	inline void AppendL(const T& aRef,TInt aLength);
	inline T& ExpandL(TInt anIndex,TInt aLength);
	inline T& ExtendL(TInt aLength);
	inline TInt Find(const T& aRef,TKeyArrayVar& aKey,TInt& anIndex) const;
	inline TInt FindIsq(const T& aRef,TKeyArrayVar& aKey,TInt& anIndex) const;
	inline void InsertL(TInt anIndex,const T& aRef,TInt aLength);
	inline TInt InsertIsqL(const T& aRef,TInt aLength,TKeyArrayVar& aKey);
 	inline TInt InsertIsqAllowDuplicatesL(const T& aRef,TInt aLength,TKeyArrayVar& aKey);
	inline const TArray<T> Array() const;
	};
TEMPLATE_SPECIALIZATION class CArrayVar<TAny> : public CArrayVarBase
	{
public:
	inline CArrayVar(TBufRep aRep,TInt aGranularity);
	inline const TAny* At(TInt anIndex) const;
	inline TAny* At(TInt anIndex);
	inline void AppendL(const TAny* aPtr,TInt aLength);
	inline TAny* ExtendL(TInt aLength);
	};
//
template <class T>
class CArrayVarFlat : public CArrayVar<T>
	{
public:
	inline CArrayVarFlat(TInt aGranularity);
	};
//
template <class T>
class CArrayVarSeg : public CArrayVar<T>
	{
public:
	inline CArrayVarSeg(TInt aGranularity);
	};
//
class TKeyArrayPak : public TKeyArrayVar
	{
public:
	IMPORT_C TKeyArrayPak(TInt anOffset,TKeyCmpText aType);
	IMPORT_C TKeyArrayPak(TInt anOffset,TKeyCmpText aType,TInt aLength);
	IMPORT_C TKeyArrayPak(TInt anOffset,TKeyCmpNumeric aType);
protected:
	IMPORT_C virtual void Set(CBufBase* aBase);
	IMPORT_C TAny* At(TInt anIndex) const;
private:
	TInt iCacheIndex;
	TInt iCacheOffset;
	friend class CArrayPakBase;
	};
//
class CArrayPakBase : public CBase
	{
public:
	IMPORT_C ~CArrayPakBase();
	inline TInt Count() const;
	IMPORT_C TInt Length(TInt anIndex) const;
	IMPORT_C void Compress();
	IMPORT_C void Reset();
	IMPORT_C void SortL(TKeyArrayVar& aKey);
	IMPORT_C TAny* At(TInt anIndex) const;
	IMPORT_C void Delete(TInt anIndex);
	IMPORT_C void Delete(TInt anIndex,TInt aCount);
	IMPORT_C TAny* ExpandL(TInt anIndex,TInt aLength);
	IMPORT_C TInt Find(const TAny* aPtr,TKeyArrayPak& aKey,TInt& anIndex) const;
	IMPORT_C TInt FindIsq(const TAny* aPtr,TKeyArrayPak& aKey,TInt& anIndex) const;
	IMPORT_C void InsertL(TInt anIndex,const TAny* aPtr,TInt aLength);
	IMPORT_C TInt InsertIsqL(const TAny* aPtr,TInt aLength,TKeyArrayPak& aKey);
	IMPORT_C TInt InsertIsqAllowDuplicatesL(const TAny* aPtr,TInt aLength,TKeyArrayPak& aKey);
protected:
	IMPORT_C CArrayPakBase(TBufRep aRep,TInt aGranularity);
	IMPORT_C void SetKey(TKeyArrayPak& aKey) const;
	IMPORT_C TInt GetOffset(TInt anIndex) const;
	IMPORT_C void BuildVarArrayL(CArrayVarFlat<TAny>*& aVarFlat);
	IMPORT_C static TInt CountR(const CBase* aPtr);
	IMPORT_C static const TAny* AtR(const CBase* aPtr,TInt anIndex);
private:
	TInt iCount;
	TInt iGranularity;
	TBufRep iCreateRep;
	CBufBase* iBase;
	TInt iCacheIndex;
	TInt iCacheOffset;
	};
//
template <class T>
class CArrayPak : public CArrayPakBase
	{
public:
	inline CArrayPak(TBufRep aRep,TInt aGranularity);
	inline const T& operator[](TInt anIndex) const;
	inline T& operator[](TInt anIndex);
	inline const T& At(TInt anIndex) const;
	inline T& At(TInt anIndex);
	inline void AppendL(const T& aRef,TInt aLength);
	inline T& ExpandL(TInt anIndex,TInt aLength);
	inline T& ExtendL(TInt aLength);
	inline TInt Find(const T& aRef,TKeyArrayPak& aKey,TInt& anIndex) const;
	inline TInt FindIsq(const T& aRef,TKeyArrayPak& aKey,TInt& anIndex) const;
	inline void InsertL(TInt anIndex,const T& aRef,TInt aLength);
	inline TInt InsertIsqL(const T& aRef,TInt aLength,TKeyArrayPak& aKey);
	inline TInt InsertIsqAllowDuplicatesL(const T& aRef,TInt aLength,TKeyArrayPak& aKey);
	inline const TArray<T> Array() const;
	};
TEMPLATE_SPECIALIZATION class CArrayPak<TAny> : public CArrayPakBase
	{
public:
	inline CArrayPak(TBufRep aRep,TInt aGranularity);
	inline const TAny* At(TInt anIndex) const;
	inline TAny* At(TInt anIndex);
	inline void AppendL(const TAny* aPtr,TInt aLength);
	inline TAny* ExtendL(TInt aLength);
	};
//
template <class T>
class CArrayPakFlat : public CArrayPak<T>
	{
public:
	inline CArrayPakFlat(TInt aGranularity);
	};
//
class CObjectCon;
class CObject : public CBase
	{
public:
	IMPORT_C CObject();
	IMPORT_C ~CObject();
	IMPORT_C virtual TInt Open();
	IMPORT_C virtual void Close();
	IMPORT_C virtual TName Name() const;
	IMPORT_C virtual TFullName FullName() const;
	IMPORT_C TInt SetName(const TDesC* aName);
	IMPORT_C void SetNameL(const TDesC* aName);
	inline CObject* Owner() const;
	inline void SetOwner(CObject* anOwner);
	inline TInt AccessCount() const;
protected:
	inline TInt UniqueID() const;
	inline void Inc();
	inline void Dec();
private:
	TInt iAccessCount;
	CObject* iOwner;
	CObjectCon* iContainer;
	HBufC* iName;
	friend class CObjectCon;
	friend class CObjectIx;
	__DECLARE_TEST;
	};
//
struct SObjectIxRec
	{
	TInt16 instance;
	TInt16 uniqueID;
	CObject* obj;
	};
//
class CObjectIx : public CBase
	{
public:
	enum {ENoClose=KHandleNoClose,ELocalHandle=0x40000000};
public:
	IMPORT_C static CObjectIx* NewL();
	IMPORT_C ~CObjectIx();
	IMPORT_C TInt AddL(CObject* anObj);
	IMPORT_C void Remove(TInt aHandle);
	IMPORT_C CObject* At(TInt aHandle,TInt aUniqueID);
	IMPORT_C CObject* At(TInt aHandle);
	IMPORT_C CObject* AtL(TInt aHandle,TInt aUniqueID);
	IMPORT_C CObject* AtL(TInt aHandle);
	IMPORT_C TInt At(const CObject* anObject) const;
	IMPORT_C TInt Count(CObject* anObject) const;
	IMPORT_C CObject* operator[](TInt anIndex);
	inline TInt Count() const;
	inline TInt ActiveCount() const;
protected:
	IMPORT_C CObjectIx();
private:
	TInt iNumEntries;		// number of actual entries in the index
	TInt iHighWaterMark;	// 1+highest active index
	TInt iAllocated;		// max entries before realloc needed
	TInt iNextInstance;
	SObjectIxRec *iObjects;
	};
//
inline TBool IsLocalHandle(TInt aHandle)
	{return(aHandle&CObjectIx::ELocalHandle);}
inline void SetLocalHandle(TInt &aHandle)
	{aHandle|=CObjectIx::ELocalHandle;}
inline void UnSetLocalHandle(TInt &aHandle)
	{aHandle&=(~CObjectIx::ELocalHandle);}
//
//
class CObjectCon : public CBase
	{
protected:
	enum {ENotOwnerID};
public:
	IMPORT_C static CObjectCon* NewL();
	IMPORT_C ~CObjectCon();
	IMPORT_C void Remove(CObject* anObj);
	IMPORT_C void AddL(CObject* anObj);
	IMPORT_C CObject* operator[](TInt anIndex);
	IMPORT_C CObject* At(TInt aFindHandle) const;
	IMPORT_C CObject* AtL(TInt aFindHandle) const;
	IMPORT_C TInt CheckUniqueFullName(const CObject* anOwner,const TDesC& aName) const;
	IMPORT_C TInt CheckUniqueFullName(const CObject* anObject) const;
	IMPORT_C TInt FindByName(TInt& aFindHandle,const TDesC& aMatch,TName& aName) const;
	IMPORT_C TInt FindByFullName(TInt& aFindHandle,const TDesC& aMatch,TFullName& aFullName) const;
	inline TInt UniqueID() const;
	inline TInt Count() const;
protected:
	IMPORT_C CObjectCon(TInt aUniqueID);
	TBool NamesMatch(const CObject* anObject, const CObject* aCurrentObject) const;
	TBool NamesMatch(const CObject* anObject, const TName& anObjectName, const CObject* aCurrentObject) const;
public:
	TInt iUniqueID;
private:
	TInt iCount;
	TInt iAllocated;
	CObject** iObjects;
	friend class CObjectConIx;
	};
//
class CObjectConIx : public CBase
	{
public:
	IMPORT_C static CObjectConIx* NewL();
	IMPORT_C ~CObjectConIx();
	IMPORT_C CObjectCon* Lookup(TInt aUniqueID) const;
	IMPORT_C CObjectCon* CreateL();
	IMPORT_C void Remove(CObjectCon* aCon);
protected:
	IMPORT_C CObjectConIx();
	IMPORT_C void CreateContainerL(CObjectCon*& anObject);
private:
	TInt iCount;
	TInt iAllocated;
	TInt iNextUniqueID;
	CObjectCon** iContainers;
	};
//
class CBitMapAllocator : public CBase
	{
public:
	IMPORT_C static CBitMapAllocator* New(TInt aSize);
	IMPORT_C static CBitMapAllocator* NewL(TInt aSize);
	IMPORT_C ~CBitMapAllocator();
	IMPORT_C TInt Alloc();
	IMPORT_C TInt AllocFrom(TInt aPos);
	IMPORT_C TInt Alloc(TInt aCount, TInt& aConsecutive);
	IMPORT_C TInt AllocAligned(TInt anAlignment);
	IMPORT_C TInt AllocAlignedBlock(TInt anAlignment);
	IMPORT_C TInt AllocFromTop();
	IMPORT_C TInt AllocFromTopFrom(TInt aPos);
	IMPORT_C void AllocAt(TInt aPos);
	IMPORT_C void AllocAt(TInt aPos, TInt aCount);
	IMPORT_C TBool IsFree(TInt aPos);
	IMPORT_C TBool IsFree(TInt aPos, TInt aCount);
	IMPORT_C void Free(TInt aPos);
	IMPORT_C void Free(TInt aPos, TInt aCount);
	IMPORT_C TInt Avail();
	IMPORT_C TInt Size();
	IMPORT_C TInt ExtractRamPages(TInt aConsecutive,TInt& aPageNo);
protected:
	IMPORT_C CBitMapAllocator(TInt aSize,TInt aLength);
protected:
	TInt iAvail;
	TInt iSize;
	TInt iLength;
	TUint iMap[1];
	};
//
typedef void (*TCleanupOperation)(TAny*);
//
class TCleanupItem
	{
public:
	inline TCleanupItem(TCleanupOperation anOperation);
	inline TCleanupItem(TCleanupOperation anOperation,TAny* aPtr);
private:
	TCleanupOperation iOperation;
	TAny* iPtr;
	friend class TCleanupStackItem;
	};
//
class CCleanup : public CBase
	{
public:
	IMPORT_C static CCleanup* New();
	IMPORT_C static CCleanup* NewL();
	IMPORT_C ~CCleanup();
	IMPORT_C void NextLevel();
	IMPORT_C void PreviousLevel();
	IMPORT_C void PushL(TAny* aPtr);
	IMPORT_C void PushL(CBase* anObject);
	IMPORT_C void PushL(TCleanupItem anItem);
	IMPORT_C void Pop();
	IMPORT_C void Pop(TInt aCount);
	IMPORT_C void PopAll();
	IMPORT_C void PopAndDestroy();
	IMPORT_C void PopAndDestroy(TInt aCount);
	IMPORT_C void PopAndDestroyAll();
	IMPORT_C void Check(TAny* aExpectedItem);
protected:
	IMPORT_C void DoPop(TInt aCount,TBool aDestroy);
	IMPORT_C void DoPopAll(TBool aDestroy);
protected:
	IMPORT_C CCleanup();
protected:
	TCleanupStackItem* iBase;
	TCleanupStackItem* iTop;
	TCleanupStackItem* iNext;
	};
//
class TCleanupTrapHandler : public TTrapHandler
	{
public:
	TCleanupTrapHandler();
	virtual void Trap();
	virtual void UnTrap();
	virtual void Leave(TInt aValue);
	inline CCleanup& Cleanup();
private:
	CCleanup* iCleanup;
	friend class CTrapCleanup;
	};
//
template <class T>
class TAutoClose
	{
public:
	inline ~TAutoClose();
	inline void PushL();
	inline void Pop();
private:
	static void Close(TAny *aObj);
public:
	T iObj;
	};
//
class CTrapCleanup : public CBase
	{
public:
	IMPORT_C static CTrapCleanup* New();
	IMPORT_C ~CTrapCleanup();
protected:
	IMPORT_C CTrapCleanup();
private:
	TCleanupTrapHandler iHandler;
	TTrapHandler* iOldHandler;
	};
//
class CCirBufBase : public CBase
	{
public:
	IMPORT_C ~CCirBufBase();
	inline TInt Count() const;
	inline TInt Length() const;
	IMPORT_C void SetLengthL(TInt aLength);
	IMPORT_C void Reset();
protected:
	IMPORT_C CCirBufBase(TInt aSize);
	IMPORT_C TInt DoAdd(const TUint8* aPtr);
	IMPORT_C TInt DoAdd(const TUint8* aPtr,TInt aCount);
	IMPORT_C TInt DoRemove(TUint8* aPtr);
	IMPORT_C TInt DoRemove(TUint8* aPtr,TInt aCount);
protected:
	TInt iCount;
	TInt iSize;
	TInt iLength;
	TUint8* iPtr;
	TUint8* iPtrE;
	TUint8* iHead;
	TUint8* iTail;
	};
//
template <class T>
class CCirBuf : public CCirBufBase
	{
public:
	inline CCirBuf();
#if defined(__VC32__)
	inline ~CCirBuf() {}
#endif
	inline TInt Add(const T* aPtr);
	inline TInt Add(const T* aPtr,TInt aCount);
	inline TInt Remove(T* aPtr);
	inline TInt Remove(T* aPtr,TInt aCount);
	};
//
class CCirBuffer : public CCirBuf<TUint8>
	{
public:
	IMPORT_C CCirBuffer();
	IMPORT_C ~CCirBuffer();
	IMPORT_C TInt Get();
	IMPORT_C TInt Put(TInt aVal);
	};
//
class CSecurityEncryptBase : public CBase
	{
public:
	virtual TInt EncryptL(TDes8& aOutput,const TDesC8& aInput) =0;
	virtual TInt CompleteL(TDes8& aOutput,const TDesC8& aInput) =0;
protected:
	IMPORT_C CSecurityEncryptBase();
	};
//
class CSecurityDecryptBase : public CBase
	{
public:
	virtual TInt DecryptL(TDes8& aOutput,const TDesC8& aInput) =0;
protected:
	IMPORT_C CSecurityDecryptBase();
	};
//
class CSecurityBase : public CBase
	{
public:
// Encryption
	virtual void SetL(const TDesC& aOldPassword,const TDesC& aNewPassword) =0;
	virtual TPtrC8 SecurityData() const =0;
	virtual CSecurityEncryptBase* NewEncryptL(const TDesC8& aInit) const =0;  
// Decryption
	virtual void PrepareL(const TDesC& aPassword) =0;
	virtual CSecurityDecryptBase* NewDecryptL(const TDesC8& aInit) const =0;  
// 
	virtual TInt IsEnabled() const =0;
	virtual void SetEnabledL(const TDesC& aPassword,TBool aIsEnabled) =0;
protected:
	IMPORT_C CSecurityBase();
	};
//
class CBoundedSecurityBase : public CSecurityBase
	{
public:
	virtual TInt MaxCipherLength(TInt aPlainTextLength) const =0;
protected:
	inline CBoundedSecurityBase() {}
	};
//
class CActive : public CBase
	{
public:
enum TPriority
	{
	EPriorityIdle=-100,
	EPriorityLow=-20,
	EPriorityStandard=0,
	EPriorityUserInput=10,
	EPriorityHigh=20,
	};
public:
	IMPORT_C ~CActive();
	IMPORT_C void Cancel();
	IMPORT_C void Deque();
	IMPORT_C void SetPriority(TInt aPriority);
	inline TBool IsActive() const;
	inline TBool IsAdded() const;
	inline TInt Priority() const;
protected:
	IMPORT_C CActive(TInt aPriority);
	IMPORT_C void SetActive();
// Pure virtual
	virtual void DoCancel() =0;
	virtual void RunL() =0;
	IMPORT_C virtual TInt RunError(TInt aError);
public:
	TRequestStatus iStatus;
private:
	TBool iActive;
	TPriQueLink iLink;
	friend class CActiveScheduler;
	friend class CServer;
	};
//
class CIdle : public CActive
	{
public:
	IMPORT_C static CIdle* New(TInt aPriority);
	IMPORT_C static CIdle* NewL(TInt aPriority);
	IMPORT_C ~CIdle();
	IMPORT_C void Start(TCallBack aCallBack);
protected:
	IMPORT_C CIdle(TInt aPriority);
	IMPORT_C void RunL();
	IMPORT_C void DoCancel();
protected:
	TCallBack iCallBack;
	};
//
class CAsyncOneShot : public CActive
	{
public:
	IMPORT_C CAsyncOneShot(TInt aPriority);
	IMPORT_C virtual void DoCancel();
	IMPORT_C virtual void Call();
	IMPORT_C virtual ~CAsyncOneShot();
	inline RThread& Thread();
private:
	void Setup();
	RThread iThread;
	};

class CAsyncCallBack : public CAsyncOneShot
	{
public:
	IMPORT_C CAsyncCallBack(TInt aPriority);
	IMPORT_C CAsyncCallBack(TCallBack& aCallBack, TInt aPriority);
	IMPORT_C void Set(TCallBack& aCallBack);
	IMPORT_C void CallBack();
protected:
	virtual void RunL();
//
protected:
	TCallBack iCallBack;
	};
//
class TDeltaTimerEntry
	{
	friend class CDeltaTimer;
public:
	inline TDeltaTimerEntry(TCallBack& aCallback);
	inline TDeltaTimerEntry();
	inline void Set(TCallBack& aCallback);
private:
	TCallBack iCallBack; 
	TDeltaQueLink iLink;
	};
class CDeltaTimer : public CActive
	{
public:
	IMPORT_C virtual void Queue(TTimeIntervalMicroSeconds32 aTimeInMicroSeconds,TDeltaTimerEntry& aHandle);
	IMPORT_C virtual void Remove(TDeltaTimerEntry& anEntry);
	IMPORT_C static CDeltaTimer* NewL(TInt aPriority);
	IMPORT_C static CDeltaTimer* NewL(TInt aPriority,TTimeIntervalMicroSeconds32 aGranularity);
	virtual ~CDeltaTimer();
protected:
	IMPORT_C CDeltaTimer(TInt aPriority,TTimeIntervalMicroSeconds32 aGranularity);
	void DoCancel();
	void RunL();
	inline TTimeIntervalMicroSeconds32 Granularity() const;
protected:
	void Activate();
	RTimer iTimer;
	TDeltaQue<TDeltaTimerEntry> iQueue;
	TTimeIntervalMicroSeconds32 iGranularity;
	};
//
class CTimer : public CActive
	{
public:
	IMPORT_C ~CTimer();
	IMPORT_C void At(const TTime& aTime);
	IMPORT_C void After(TTimeIntervalMicroSeconds32 anInterval);
	IMPORT_C void Lock(TTimerLockSpec aLock);
	IMPORT_C void Inactivity(TTimeIntervalSeconds aSeconds);
protected:
	IMPORT_C CTimer(TInt aPriority);
	IMPORT_C void ConstructL();
	IMPORT_C void DoCancel();
private:
	RTimer iTimer;
	};
//
class CPeriodic : public CTimer
	{
public:
	IMPORT_C static CPeriodic* New(TInt aPriority);
	IMPORT_C static CPeriodic* NewL(TInt aPriority);
	IMPORT_C ~CPeriodic();
	IMPORT_C void Start(TTimeIntervalMicroSeconds32 aDelay,TTimeIntervalMicroSeconds32 anInterval,TCallBack aCallBack);
protected:
	IMPORT_C CPeriodic(TInt aPriority);
	IMPORT_C void RunL();
private:
	TTimeIntervalMicroSeconds32 iInterval;
	TCallBack iCallBack;
	};
//
class MBeating
	{
public:
	virtual void Beat() =0;
	virtual void Synchronize() =0;
	};
//
class CHeartbeat : public CTimer
	{
public:
	IMPORT_C static CHeartbeat* New(TInt aPriority);
	IMPORT_C static CHeartbeat* NewL(TInt aPriority);
	IMPORT_C ~CHeartbeat();
	IMPORT_C void Start(TTimerLockSpec aLock,MBeating *aBeating);
protected:
	IMPORT_C CHeartbeat(TInt aPriority);
	IMPORT_C void RunL();
private:
	TTimerLockSpec iLock;
	MBeating *iBeating;
	};
//
class CServer;
class CSharableSession : public CBase
	{
	friend class CServer;
public:
	IMPORT_C ~CSharableSession() =0;
	IMPORT_C virtual void CreateL(const CServer& aServer);
//
	inline const CServer* Server() const;
	inline const RMessage& Message() const;
	IMPORT_C void ResourceCountMarkStart();
	IMPORT_C void ResourceCountMarkEnd();
	IMPORT_C virtual TInt CountResources();
// Pure virtual
	virtual void ServiceL(const RMessage& aMessage) =0;
protected:
	IMPORT_C CSharableSession();
public:
	enum TPanicNo {ESesCountResourcesNotImplemented=1,ESesFoundResCountHeaven};
private:
	TInt iResourceCountMark;
	TDblQueLink iLink;
	const CServer* iServer;
	};

class CSession : public CSharableSession
	{
public:
	IMPORT_C ~CSession() =0;
//
	inline const RThread& Client() const;
	IMPORT_C void ReadL(const TAny* aPtr,TDes8& aDes) const;
	IMPORT_C void ReadL(const TAny* aPtr,TDes8& aDes,TInt anOffset) const;
	IMPORT_C void ReadL(const TAny* aPtr,TDes16& aDes) const;
	IMPORT_C void ReadL(const TAny* aPtr,TDes16& aDes,TInt anOffset) const;
	IMPORT_C void WriteL(const TAny* aPtr,const TDesC8& aDes) const;
	IMPORT_C void WriteL(const TAny* aPtr,const TDesC8& aDes,TInt anOffset) const;
	IMPORT_C void WriteL(const TAny* aPtr,const TDesC16& aDes) const;
	IMPORT_C void WriteL(const TAny* aPtr,const TDesC16& aDes,TInt anOffset) const;
	IMPORT_C void Panic(const TDesC& aCategory,TInt aReason) const;
	IMPORT_C void Kill(TInt aReason) const;
	IMPORT_C void Terminate(TInt aReason) const;
protected:
	IMPORT_C CSession(RThread aClient);
private:
	RThread iClient;
	};
//
class CServer : public CActive
	{
protected:
	enum TServerType {EUnsharableSessions,ESharableSessions};
public:
	IMPORT_C ~CServer() =0;
	IMPORT_C TInt Start(const TDesC& aName);
	IMPORT_C void StartL(const TDesC& aName);
//
	IMPORT_C void ReStart();
	inline const RMessage& Message() const;
protected:
	IMPORT_C CServer(TInt aPriority,TServerType aType=EUnsharableSessions);
	IMPORT_C void DoCancel();
	IMPORT_C void RunL();
private:
	virtual CSharableSession* NewSessionL(const TVersion& aVersion) const =0;
	void Connect();
private:
	const TServerType iSessionType;
	RServer iServer;
	TDblQue<CSharableSession> iSessionQ;
protected:
	TDblQueIter<CSharableSession> iSessionIter;
	};
//
class CActiveSchedulerWait : public CBase
	{
public:
	IMPORT_C ~CActiveSchedulerWait();
	IMPORT_C void Start();
	IMPORT_C void AsyncStop();
	IMPORT_C void AsyncStop(const TCallBack& aCallMeWhenStopped);
	IMPORT_C TBool IsStarted() const;
	IMPORT_C TBool CanStopNow() const;

private:
	friend class CActiveScheduler;
	class TOwnedSchedulerLoop
		{
	public:
		TOwnedSchedulerLoop(CActiveSchedulerWait* aWait);
	public:
		TInt iRunning;
		TCallBack iCb;
		TBool iLevelDropped;
		CActiveSchedulerWait* iWait;
		};
	TOwnedSchedulerLoop* iLoop;
	};
//
class CActiveScheduler : public CBase
	{
public:
	IMPORT_C CActiveScheduler();
	IMPORT_C ~CActiveScheduler();
	IMPORT_C static void Install(CActiveScheduler* aScheduler);
	IMPORT_C static CActiveScheduler* Current();
	IMPORT_C static void Add(CActive* anActive);
	IMPORT_C static void Start();
	IMPORT_C static void Stop();
	IMPORT_C static TBool RunIfReady(TInt& aError, TInt aMinimumPriority);
	IMPORT_C static CActiveScheduler* Replace(CActiveScheduler* aNewActiveScheduler);
	IMPORT_C virtual void WaitForAnyRequest();
	IMPORT_C virtual void Error(TInt anError) const;
private:
	void DoStart();
	void OwnedStartLoop(TInt& aRunning);
	IMPORT_C virtual void OnStarting();
	IMPORT_C virtual void OnStopping();
	IMPORT_C virtual void Reserved_1();
	IMPORT_C virtual void Reserved_2();
private:
	// private interface used through by CActiveSchedulerWait objects
	friend class CActiveSchedulerWait;
	static void OwnedStart(CActiveSchedulerWait& aOwner);
protected:
	inline TInt Level() const;
private:
	TInt iLevel;
	TPriQue<CActive> iActiveQ;
	};
//
class CleanupStack
	{
public:
	IMPORT_C static void PushL(TAny* aPtr);
	IMPORT_C static void PushL(CBase* aPtr);
	IMPORT_C static void PushL(TCleanupItem anItem);
	IMPORT_C static void Pop();
	IMPORT_C static void Pop(TInt aCount);
	IMPORT_C static void PopAndDestroy();
	IMPORT_C static void PopAndDestroy(TInt aCount);
	IMPORT_C static void Check(TAny* aExpectedItem);
	inline static void Pop(TAny* aExpectedItem);
	inline static void Pop(TInt aCount, TAny* aLastExpectedItem);
	inline static void PopAndDestroy(TAny* aExpectedItem);
	inline static void PopAndDestroy(TInt aCount, TAny* aLastExpectedItem);
	};
//
#ifndef __EPOC_CLEANUP_SUPPORT__
template <class T>
class CleanupDelete
	{
public:
	inline static void PushL(T* aPtr);
private:
	static void Delete(TAny *aPtr);
	};
template <class T>
inline void CleanupDeletePushL(T* aPtr);
//
template <class T>
class CleanupClose
	{
public:
	inline static void PushL(T& aRef);
private:
	static void Close(TAny *aPtr);
	};
template <class T>
inline void CleanupClosePushL(T& aRef);
//
template <class T>
class CleanupRelease
	{
public:
	inline static void PushL(T& aRef);
private:
	static void Release(TAny *aPtr);
	};
template <class T>
inline void CleanupReleasePushL(T& aRef);
#endif // __EPOC_CLEANUP_SUPPORT__
//
class CConsoleBase;
class Console
	{
public:
	IMPORT_C static CConsoleBase* NewL(const TDesC& aTitle,TSize aSize);
	};
//
class Security
	{
public:
	IMPORT_C static CBoundedSecurityBase* NewL();
	IMPORT_C static CBoundedSecurityBase* NewL(const TDesC8& aSecurityData);
	};
//
#include <e32base.inl>
#endif

