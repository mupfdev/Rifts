// CStack.inl
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved. 
//

#ifndef __CSTACK_INL__
#define __CSTACK_INL__

// constants
const TInt KStackGranularity=32;

enum TCStackPanic
	{
	ECStackErrStackIsEmpty,
	ECStackDeleteWhenNotOwner,
	ECStackPopsWhenOwner
	};

_LIT(KCStackPanicName, "CStack");

inline void Panic(TCStackPanic aPanic)
	{
	User::Panic(KCStackPanicName, aPanic);
	}

//
// CStack
//

template <class T, TBool StackOwnsEntry>
inline CStack<T, StackOwnsEntry>::CStack()
: CArrayPtrSeg<T>(KStackGranularity)
	{
	Reset();
	}

template <class T, TBool StackOwnsEntry>
inline CStack<T, StackOwnsEntry>::~CStack()
	{ 
	Clear();
	}

template <class T, TBool StackOwnsEntry>
inline void CStack<T, StackOwnsEntry>::Clear() 
	{ 
	if (StackOwnsEntry) 
		ResetAndDestroy(); 
	else 
		Reset(); 
	}

template <class T, TBool StackOwnsEntry>
inline TBool CStack<T, StackOwnsEntry>::IsEmpty() const 
	{ 
	return Count()==0;
	}

template <class T, TBool StackOwnsEntry>
inline void CStack<T, StackOwnsEntry>::PushL(T* aItem) 
	{
	if (StackOwnsEntry)
		CleanupStack::PushL(aItem); 
	AppendL(aItem); 
	if (StackOwnsEntry)
		CleanupStack::Pop();
	}

template <class T, TBool StackOwnsEntry>
inline T* CStack<T, StackOwnsEntry>::Pop() 
	{
	__ASSERT_DEBUG(!IsEmpty(), Panic(ECStackErrStackIsEmpty));
	T* item=Head(); 
	Delete(Count()-1);
	return item;
	}

template <class T, TBool StackOwnsEntry>
inline T* CStack<T, StackOwnsEntry>::Head() const 
	{
	__ASSERT_DEBUG(!IsEmpty(), Panic(ECStackErrStackIsEmpty));
	return At(Count()-1);
	}

template <class T, TBool StackOwnsEntry>
inline T* CStack<T, StackOwnsEntry>::Last() const 
	{
	__ASSERT_DEBUG(!IsEmpty(), Panic(ECStackErrStackIsEmpty));
	return At(0);
	}
	

#endif // __CSTACK_INL__