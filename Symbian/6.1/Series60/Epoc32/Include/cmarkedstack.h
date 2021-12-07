// CMarkedStack.h
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved. 
//

// Template class to implement a marked stack. Conatins a stack itself of marks 
// providing basic marking functionality.

#ifndef __CMARKEDSTACK_H__
#define __CMARKEDSTACK_H__

// includes
#include <e32base.h>
#include <CStack.h>

template <class T, TBool Owner>
class CMarkedStack : public CStack<T, Owner>
{
protected:
class TMarkPoint
{
public:
	TMarkPoint(TInt aMarkType
		   , TInt aIndex)
	  : iMarkType(aMarkType)
	  , iStackIndex(aIndex)
	{}
	TInt iMarkType;
	TInt iStackIndex;
};
typedef CStack<TMarkPoint, ETrue> CMarks;
public:
	inline virtual ~CMarkedStack();

	inline void MarkL(TInt aMarkType);
	inline TInt RemoveMark(TInt aMarkType);
	inline void DeleteToMark(TInt aMarkType);
	inline void ResetToMark(TInt aMarkType);
protected:
	CMarks iMarks;
};

#include "CMarkedStack.inl"

#endif // __CMARKEDSTACK_H__
