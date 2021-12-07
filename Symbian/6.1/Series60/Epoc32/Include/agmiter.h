// AGMITER.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __AGMITER_H__
#define __AGMITER_H__

#include "agmutil.h"
#include "agmdate.h"

// ----------------------------------- Local classes ---------------------------
template<class T> class TFilter;
template<class T,class KeyValue> class TRange;
class TAgnIteratorBase;
class TAgnIterator;
class TAgnCompoundIteratorBase;

// ----------------------------------- Reference classes -----------------------
class CAgnIndex;
class CAgnSortEntry;



// ----------------------------------- TFilter<T>-------------------------------
//
// filter template
// 
template<class T>
class TFilter 
	{
public:
	virtual TBool Compare(const T& aElement) const = 0;
	};



// ----------------------------------- TAgnIteratorBase-------------------------
class TAgnIteratorBase
	{
public:
	TAgnIteratorBase() {}
	virtual void Start() = 0;
	virtual void Next() = 0;
	virtual void Previous() = 0;
	virtual TBool AtEnd() = 0;
	virtual TBool AtStart() = 0;
	virtual TBool Goto(TAgnDate& aKeyValue) = 0;
	virtual TBool GotoLessOrEqual(TAgnDate& aKeyValue) = 0;
	virtual const TAgnDate& CurrentKey() const = 0;
	virtual CAgnSortEntry* CurrentElement() = 0;
	};

// ----------------------------------- TAgnCompoundIteratorBase-------------------------
class TAgnCompoundIteratorBase : public TAgnIteratorBase
	{
public:
	IMPORT_C TAgnCompoundIteratorBase(TAgnIteratorBase** aIterators);
	IMPORT_C virtual void Start();
	IMPORT_C virtual void Next();
	IMPORT_C virtual void Previous();
	IMPORT_C virtual TBool AtEnd();
	IMPORT_C virtual TBool AtStart();
	IMPORT_C virtual TBool Goto(TAgnDate& aKeyValue);
	IMPORT_C virtual TBool GotoLessOrEqual(TAgnDate& aKeyValue);
	IMPORT_C virtual CAgnSortEntry* CurrentElement();
	IMPORT_C virtual const TAgnDate& CurrentKey() const;
	IMPORT_C void SetCount(TInt aCount);
protected:
	TAgnIteratorBase** iIterators;
private:
	TBool SetCurrent();
	TBool SetCurrentLessOrEqual();
	TInt iCount;
	TInt iCurrent;
	};


class TAgnIterator : public TAgnIteratorBase
	{
public:	
	IMPORT_C TAgnIterator(CAgnIndex* aArray,TFilter<CAgnSortEntry*>* aFilter = NULL);
	IMPORT_C void Start();
	IMPORT_C virtual void Next();
	IMPORT_C virtual void Previous();
	IMPORT_C virtual TBool Goto(TAgnDate& aKeyValue);
	IMPORT_C virtual TBool GotoLessOrEqual(TAgnDate& aKeyValue);
	IMPORT_C CAgnSortEntry* CurrentElement();
	IMPORT_C virtual const TAgnDate& CurrentKey() const;
	IMPORT_C virtual TBool AtEnd();
	IMPORT_C virtual TBool AtStart();
protected:
	TBool IsValidElement();			// Current element valid w.r.t. filter
	void SetCursor(TInt aCursor);
	TInt Cursor() const;
	const CAgnIndex* const Array() const;
	void SetCurrentKey(const TAgnDate& aKeyValue);
	TBool First(TAgnDate& aTargetKey);
	TBool FirstLessOrEqual(TAgnDate& aTargetKey);
	virtual TBool MovedForward(TAgnDate /*aTargetValue*/) {return ETrue;}
	virtual TBool MovedTo(TAgnDate /*aTargetValue*/) {return ETrue;}
	virtual TBool MovedBack(TAgnDate /*aTargetValue*/) {return ETrue;}
	virtual TBool MovedToLessOrEqual(TAgnDate /*aTargetValue*/) {return ETrue;}
	TAgnDate iCurrentKey;
	TAgnDate iPreviousKey;
private:
	TInt iCursor;
	TFilter<CAgnSortEntry*>* iFilter;
	CAgnIndex* iArray;
	};

#endif
// -------------------------------- EOF ----------------------------------------
