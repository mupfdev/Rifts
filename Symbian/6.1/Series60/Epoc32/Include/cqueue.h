//
// CQueue.h
// Copyright © 1998-2000 Symbian Ltd.  All rights reserved. 
//

// A template class to provide a classic queue like interface & functionality
// The class does by default does not own the data contained, if that is
// desired the use of the ClearAndDEstroy method should be used on destruction.

#ifndef __CQUEUE_H__
#define __CQUEUE_H__

// System includes
//
#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif


//
// Consts used by this class
//

// Queue's resize granularity
//
const TInt KQueueGranularity = 3;

// Head of a queue is at position 0
//
const TInt KHeadPos = 0;


//
// Class declaration for CQueue
//

template <class T, TBool Owner>
class CQueue : protected CArrayPtrFlat<T>
    {
public:
	inline CQueue() : CArrayPtrFlat<T>(KQueueGranularity) { Reset(); }
    inline ~CQueue() { Clear(); }

	inline void Clear() { if (Owner) ResetAndDestroy(); else Reset(); }
	inline TBool IsEmpty() const { return(Count() == KHeadPos); }
	inline TInt Length() const { return CArrayPtrFlat<T>::Count(); }
	inline void AddL(T* aItem) { AppendL(aItem); }
    inline void Remove(TInt anIndex) { T* item = At(anIndex); Delete(anIndex); if (Owner) delete item; }
	inline T* Front() { T* item = Head(); Delete(KHeadPos); return item; }
	inline T* Head() const { return (At(KHeadPos)); }
	inline T& operator[](TInt anIndex) const { return *At(anIndex); }
protected:
    };

#endif // __CQUEUE_H__
