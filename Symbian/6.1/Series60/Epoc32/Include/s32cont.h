// S32CONT.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//
#if !defined(__S32CONT_H__)
#define __S32CONT_H__
#if !defined(__S32BTREE_H__)
#include <s32btree.h>
#endif

class TPagedSetToken : public TBtreeToken
	{
public:
	TPagedSetToken() {}
	inline TPagedSetToken(TEmpty);
//
	inline TInt Count() const;
//
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	IMPORT_C void InternalizeL(RReadStream& aStream);
protected:
	IMPORT_C void Clear();
private:
	inline TPagedSetToken(const TBtreeToken& aTree,TInt aCount);
private:
	TInt iCount;
private:
	friend class TPagedSetBase;
	};
#define KEmptyPagedSetToken TPagedSetToken(TPagedSetToken::EEmpty)
//
class TPagedSetBase
	{
public:
	IMPORT_C void Connect(MPagePool* aPool);
	IMPORT_C void Set(const TPagedSetToken& aToken);
	IMPORT_C TPagedSetToken Token() const;
//
	inline TBool IsDirty() const;
	inline void MarkCurrent();
	inline void MarkDirty();
//
	inline TBool IsBroken() const;
	inline TBool IsIntact() const;
	inline void MarkBroken();
	IMPORT_C TInt RepairL();
//
	inline TInt Count() const;
	inline TBool IsEmpty() const;
	IMPORT_C void ClearL();
//
	IMPORT_C TBool ContainsL(const TAny* aPtr) const;
	IMPORT_C void InsertL(const TAny* aPtr);
	IMPORT_C void DeleteL(const TAny* aPtr);
protected:
	IMPORT_C TPagedSetBase(TInt anEntrySize);
	IMPORT_C TPagedSetBase(const TPagedSetToken& aToken,TInt anEntrySize);
	IMPORT_C void InsertAllowDuplicatesL(const TAny* aPtr);
private:
	TBtreeFix<TAny,TAny> iTree;
	TBtreeKey iKey;
	TInt iCount;
private:
	friend class TPagedSetIterBase;
	friend class TPagedSetBiIterBase;
	};
class TPagedMultisetBase : public TPagedSetBase
	{
public:
	inline void InsertL(const TAny* aPtr);
protected:
	inline TPagedMultisetBase(TInt anEntrySize);
	inline TPagedMultisetBase(const TPagedSetToken& aToken,TInt anEntrySize);
	};
//
template <class T>
class TPagedSet : public TPagedSetBase
	{
public:
	inline TPagedSet();
	inline TPagedSet(const TPagedSetToken& aToken);
//
	inline TBool ContainsL(const T& anObject) const;
	inline void InsertL(const T& anObject);
	inline void DeleteL(const T& anObject);
	};
TEMPLATE_SPECIALIZATION class TPagedSet<TAny> : public TPagedSetBase
	{
public:
	inline TPagedSet(TInt anEntrySize);
	inline TPagedSet(const TPagedSetToken& aToken,TInt anEntrySize);
	};
template <class T>
class TPagedMultiset : public TPagedMultisetBase
	{
public:
	inline TPagedMultiset();
	inline TPagedMultiset(const TPagedSetToken& aToken);
//
	inline TBool ContainsL(const T& anObject) const;
	inline void InsertL(const T& anObject);
	inline void DeleteL(const T& anObject);
	};
TEMPLATE_SPECIALIZATION class TPagedMultiset<TAny> : public TPagedMultisetBase
	{
public:
	inline TPagedMultiset(TInt anEntrySize);
	inline TPagedMultiset(const TPagedSetToken& aToken,TInt anEntrySize);
	};
//
class TPagedSetIterBase
	{
public:
	IMPORT_C TBool ResetL();
	IMPORT_C TBool NextL();
	IMPORT_C void ExtractAtL(TAny* aPtr) const;
protected:
	inline TPagedSetIterBase(const TPagedSetBase& aSet);
private:
	const TBtreeFixBase* iTree;
	TBtreeMark iMark;
	};
template <class T>
class TPagedSetIter : public TPagedSetIterBase
	{
public:
	inline TPagedSetIter(const TPagedSet<T>& aSet);
	inline TPagedSetIter(const TPagedMultiset<T>& aSet);
	inline T AtL() const;
	inline void ExtractAtL(T& anObject) const;
	};
TEMPLATE_SPECIALIZATION class TPagedSetIter<TAny> : public TPagedSetIterBase
	{
public:
	inline TPagedSetIter(const TPagedSetBase& aSet);
	};
//
class TPagedSetBiIterBase
	{
public:
	IMPORT_C TBool FirstL();
	IMPORT_C TBool LastL();
	IMPORT_C TBool NextL();
	IMPORT_C TBool PreviousL();
	IMPORT_C void ExtractAtL(TAny* aPtr) const;
protected:
	inline TPagedSetBiIterBase(const TPagedSetBase& aSet);
private:
	const TBtreeFixBase* iTree;
	TBtreePos iPos;
	};
template <class T>
class TPagedSetBiIter : public TPagedSetBiIterBase
	{
public:
	inline TPagedSetBiIter(const TPagedSet<T>& aSet);
	inline TPagedSetBiIter(const TPagedMultiset<T>& aSet);
	inline T AtL() const;
	inline void ExtractAtL(T& anObject) const;
	};
TEMPLATE_SPECIALIZATION class TPagedSetBiIter<TAny> : public TPagedSetBiIterBase
	{
public:
	inline TPagedSetBiIter(const TPagedSetBase& aSet);
	};
//
class TPagedSetRIterBase
	{
public:
	inline TBool ResetL();
	inline TBool NextL();
	inline void ExtractAtL(TAny* aPtr) const;
protected:
	inline TPagedSetRIterBase(const TPagedSetBase& aSet);
private:
	TPagedSetBiIter<TAny> iIter;
	};
template <class T>
class TPagedSetRIter : public TPagedSetRIterBase
	{
public:
	inline TPagedSetRIter(const TPagedSet<T>& aSet);
	inline TPagedSetRIter(const TPagedMultiset<T>& aSet);
	inline T AtL() const;
	inline void ExtractAtL(T& anObject) const;
	};
TEMPLATE_SPECIALIZATION class TPagedSetRIter<TAny> : public TPagedSetRIterBase
	{
public:
	inline TPagedSetRIter(const TPagedSetBase& aSet);
	};

#include <s32cont.inl>
#endif
