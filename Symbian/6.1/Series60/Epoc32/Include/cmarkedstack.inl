// CMStack.inl
//
// Copyright (c) 1999 Symbian Ltd.  All rights reserved. 
//

#include "CMarkedStack.h"

template <class T, TBool Owner>
inline CMarkedStack<T, Owner>::~CMarkedStack()
{
	iMarks.Clear();
}

template <class T, TBool Owner>
void 
inline CMarkedStack<T, Owner>::MarkL(TInt aMarkType)
	{
	TMarkPoint* point = new (ELeave) TMarkPoint(aMarkType, Count());
	iMarks.PushL(point);
	}

template <class T, TBool Owner>
TInt 
inline CMarkedStack<T, Owner>::RemoveMark(TInt aMarkType)
	{
	TMarkPoint* point = NULL;
	do
		{
		delete point;
		point = iMarks.Pop();
		} while (point->iMarkType != aMarkType);
	TInt stackIndex = point->iStackIndex;
	delete point;
	return stackIndex;
	}

template <class T, TBool Owner>
void 
inline CMarkedStack<T, Owner>::DeleteToMark(TInt aMarkType)
	{
	TInt lastMark = RemoveMark(aMarkType);
	while (Count() > lastMark)
		delete Pop();
	}

template <class T, TBool Owner>
void 
inline CMarkedStack<T, Owner>::ResetToMark(TInt aMarkType)
	{
	TInt lastMark = RemoveMark(aMarkType);
	while (Count() > lastMark)
		Pop();
	}
