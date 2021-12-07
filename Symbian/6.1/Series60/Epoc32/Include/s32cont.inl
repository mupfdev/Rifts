// S32CONT.INL
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//

// Class TPagedSetToken
inline TPagedSetToken::TPagedSetToken(TEmpty)
	{Clear();}
inline TInt TPagedSetToken::Count() const
	{return iCount;}

// Class TPagedSetBase
inline TBool TPagedSetBase::IsDirty() const
	{return iTree.IsDirty();}
inline void TPagedSetBase::MarkCurrent()
	{iTree.MarkCurrent();}
inline void TPagedSetBase::MarkDirty()
	{iTree.MarkDirty();}
inline TBool TPagedSetBase::IsBroken() const
	{return iTree.IsBroken();}
inline TBool TPagedSetBase::IsIntact() const
	{return iTree.IsIntact();}
inline void TPagedSetBase::MarkBroken()
	{iTree.MarkBroken();}
inline TInt TPagedSetBase::Count() const
	{return iCount;}
inline TBool TPagedSetBase::IsEmpty() const
	{return iTree.IsEmpty();}

// Class TPagedMultisetBase
inline void TPagedMultisetBase::InsertL(const TAny* aPtr)
	{TPagedSetBase::InsertAllowDuplicatesL(aPtr);}
inline TPagedMultisetBase::TPagedMultisetBase(TInt anEntrySize)
	: TPagedSetBase(anEntrySize)
	{}
inline TPagedMultisetBase::TPagedMultisetBase(const TPagedSetToken& aToken,TInt anEntrySize)
	: TPagedSetBase(aToken,anEntrySize)
	{}

// Template class TPagedSet
template <class T>
inline TPagedSet<T>::TPagedSet()
	: TPagedSetBase(sizeof(T))
	{}
template <class T>
inline TPagedSet<T>::TPagedSet(const TPagedSetToken& aToken)
	: TPagedSetBase(aToken,sizeof(T))
	{}
template <class T>
inline TBool TPagedSet<T>::ContainsL(const T& anObject) const
	{return TPagedSetBase::ContainsL(&anObject);}
template <class T>
inline void TPagedSet<T>::InsertL(const T& anObject)
	{TPagedSetBase::InsertL(&anObject);}
template <class T>
inline void TPagedSet<T>::DeleteL(const T& anObject)
	{TPagedSetBase::DeleteL(&anObject);}
inline TPagedSet<TAny>::TPagedSet(TInt anEntrySize)
	: TPagedSetBase(anEntrySize)
	{}
inline TPagedSet<TAny>::TPagedSet(const TPagedSetToken& aToken,TInt anEntrySize)
	: TPagedSetBase(aToken,anEntrySize)
	{}

// Template class TPagedMultiset
template <class T>
inline TPagedMultiset<T>::TPagedMultiset()
	: TPagedMultisetBase(sizeof(T))
	{}
template <class T>
inline TPagedMultiset<T>::TPagedMultiset(const TPagedSetToken& aToken)
	: TPagedMultisetBase(aToken,sizeof(T))
	{}
template <class T>
inline TBool TPagedMultiset<T>::ContainsL(const T& anObject) const
	{return TPagedMultisetBase::ContainsL(&anObject);}
template <class T>
inline void TPagedMultiset<T>::InsertL(const T& anObject)
	{TPagedMultisetBase::InsertL(&anObject);}
template <class T>
inline void TPagedMultiset<T>::DeleteL(const T& anObject)
	{TPagedMultisetBase::DeleteL(&anObject);}
inline TPagedMultiset<TAny>::TPagedMultiset(TInt anEntrySize)
	: TPagedMultisetBase(anEntrySize)
	{}
inline TPagedMultiset<TAny>::TPagedMultiset(const TPagedSetToken& aToken,TInt anEntrySize)
	: TPagedMultisetBase(aToken,anEntrySize)
	{}

// Class TPagedSetIterBase
inline TPagedSetIterBase::TPagedSetIterBase(const TPagedSetBase& aSet)
	: iTree(&aSet.iTree)
	{}

// Class TPagedSetIter
template <class T>
inline TPagedSetIter<T>::TPagedSetIter(const TPagedSet<T>& aSet)
	: TPagedSetIterBase(aSet)
	{}
template <class T>
inline TPagedSetIter<T>::TPagedSetIter(const TPagedMultiset<T>& aSet)
	: TPagedSetIterBase(aSet)
	{}
template <class T>
inline T TPagedSetIter<T>::AtL() const
	{T t;TPagedSetIterBase::ExtractAtL(&t);return t;}
template <class T>
inline void TPagedSetIter<T>::ExtractAtL(T& anObject) const
	{TPagedSetIterBase::ExtractAtL(&anObject);}
inline TPagedSetIter<TAny>::TPagedSetIter(const TPagedSetBase& aSet)
	: TPagedSetIterBase(aSet)
	{}

// Class TPagedSetBiIterBase
inline TPagedSetBiIterBase::TPagedSetBiIterBase(const TPagedSetBase& aSet)
	: iTree(&aSet.iTree)
	{}

// Class TPagedSetBiIter
template <class T>
inline TPagedSetBiIter<T>::TPagedSetBiIter(const TPagedSet<T>& aSet)
	: TPagedSetBiIterBase(aSet)
	{}
template <class T>
inline TPagedSetBiIter<T>::TPagedSetBiIter(const TPagedMultiset<T>& aSet)
	: TPagedSetBiIterBase(aSet)
	{}
template <class T>
inline T TPagedSetBiIter<T>::AtL() const
	{T t;TPagedSetBiIterBase::ExtractAtL(&t);return t;}
template <class T>
inline void TPagedSetBiIter<T>::ExtractAtL(T& anObject) const
	{TPagedSetBiIterBase::ExtractAtL(&anObject);}
inline TPagedSetBiIter<TAny>::TPagedSetBiIter(const TPagedSetBase& aSet)
	: TPagedSetBiIterBase(aSet)
	{}

// Class TPagedSetRIterBase
inline TBool TPagedSetRIterBase::ResetL()
	{return iIter.LastL();}
inline TBool TPagedSetRIterBase::NextL()
	{return iIter.PreviousL();}
inline void TPagedSetRIterBase::ExtractAtL(TAny* aPtr) const
	{iIter.ExtractAtL(aPtr);}
inline TPagedSetRIterBase::TPagedSetRIterBase(const TPagedSetBase& aSet)
	: iIter(aSet)
	{}

// Class TPagedSetRIter
template <class T>
inline TPagedSetRIter<T>::TPagedSetRIter(const TPagedSet<T>& aSet)
	: TPagedSetRIterBase(aSet)
	{}
template <class T>
inline TPagedSetRIter<T>::TPagedSetRIter(const TPagedMultiset<T>& aSet)
	: TPagedSetRIterBase(aSet)
	{}
template <class T>
inline T TPagedSetRIter<T>::AtL() const
	{T t;TPagedSetRIterBase::ExtractAtL(&t);return t;}
template <class T>
inline void TPagedSetRIter<T>::ExtractAtL(T& anObject) const
	{TPagedSetRIterBase::ExtractAtL(&anObject);}
inline TPagedSetRIter<TAny>::TPagedSetRIter(const TPagedSetBase& aSet)
	: TPagedSetRIterBase(aSet)
	{}

