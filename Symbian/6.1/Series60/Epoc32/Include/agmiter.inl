// AGMITER.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// --------------------------TAgnIterator<Entry,KeyValue>-------------------

template<class Entry,class KeyValue>
inline TAgnIterator<Entry,KeyValue>::TAgnIterator(CAgnIndex* aArray,TFilter<Entry*>* aFilter)
	{

	__ASSERT_ALWAYS(aArray != NULL,Panic(EAgmErrIteratorNullIndex));
	iArray = aArray;
	iFilter = aFilter;
	}


template<class Entry,class KeyValue>
inline const CAgnIndex* const TAgnIterator<Entry,KeyValue>::Array() const 
	{

	return (iArray);
	}

template<class Entry,class KeyValue>
inline void TAgnIterator<Entry,KeyValue>::SetCursor(TInt aCursor)
//
// set the current position of iterator
//
	{

	iCursor = aCursor;
	}

template<class Entry,class KeyValue>
inline TInt TAgnIterator<Entry,KeyValue>::Cursor() const
//
// return current position of iterator
//
	{

	return (iCursor);
	}

template<class Entry,class KeyValue>
inline void TAgnIterator<Entry,KeyValue>::SetCurrentKey(const KeyValue& aKeyValue)
//
// set the current key value
//
	{
	iCurrentKey = aKeyValue;
	}


template<class Entry,class KeyValue>
inline Entry* TAgnIterator<Entry,KeyValue>::CurrentElement()
	{

	return (iArray->Get(iCursor));
	}

template<class Entry,class KeyValue>
inline const KeyValue& TAgnIterator<Entry,KeyValue>::CurrentKey() const
	{

	return (iCurrentKey);
	}

template<class Entry,class KeyValue>
inline TBool TAgnIterator<Entry,KeyValue>::IsValidElement()
//
// Is current element valid w.r.t. filter?
//
	{
	__ASSERT_ALWAYS(iCursor>=0 && iCursor<iArray->Count(),Panic(EAgmErrOutsideArrayRange));
	if (iFilter)	// has a filter
		return (iFilter->Compare(CurrentElement()));
	return (ETrue);	// no filter => all elements valid
	}

template<class Entry,class KeyValue>
inline void TAgnIterator<Entry,KeyValue>::Next()
//
// position to next element which is valid w.r.t. filter?
//
	{
	if (iArray->Count() > 0)
		{
		TBool found = EFalse;
		iArray->Next(iCurrentKey, iCursor);

		while(!found && iCursor < iArray->Count()) 
			{
			found = IsValidElement();
			if (!found)
				iArray->Next(iCurrentKey, iCursor);
			}
		}
	}

template<class Entry,class KeyValue>
inline void TAgnIterator<Entry,KeyValue>::Previous()
//
// position to previous element which is valid w.r.t. filter?
//
	{
	if (iArray->Count() > 0)
		{
		TBool found = EFalse;
		iArray->Previous(iCurrentKey, iCursor);

		while(!found && iCursor > -1) 
			{
			found = IsValidElement();
			if (!found)
				iArray->Previous(iCurrentKey, iCursor);
			}
		}
	}

template<class Entry,class KeyValue>
inline void TAgnIterator<Entry,KeyValue>::Start() 
//
// Position to first valid element
//
	{ 

	SetCursor(0);	
	if (iArray->Count() > 0)
		{
		iArray->GetKeyValue(0,iCurrentKey);
		while(!AtEnd() && !IsValidElement())// iterate until entry matches filter
			Next();
		}
	}

template<class Entry,class KeyValue>
inline TBool TAgnIterator<Entry,KeyValue>::Goto(KeyValue& aKeyValue) 
//
// Position to the first element whose keyvalue is >= aKeyValue
//
	{ 

	TBool found = EFalse;
	if (iArray->Count() > 0)
		{
		found = ETrue;
		TInt pos = 0;

		found = iArray->First(aKeyValue,pos);
		SetCursor(pos);		
		iCurrentKey = aKeyValue;
		if (found) 
			{
			while(iCursor < iArray->Count() && !(found = IsValidElement())) // iterate until entry matches filter
				Next();
			aKeyValue = iCurrentKey;
			}
		}
	return (found);
	}

template<class Entry,class KeyValue>
inline TBool TAgnIterator<Entry,KeyValue>::GotoLessOrEqual(KeyValue& aKeyValue)
	{
	TBool found = EFalse;
	if (iArray->Count() > 0)
		{
		found = ETrue;
		TInt pos = 0;

		iArray->FirstLessOrEqual(aKeyValue,pos);
		SetCursor(pos);		
		iCurrentKey = aKeyValue;
		while(iCursor >= 0 && !(found = IsValidElement())) // iterate until entry matches filter
			Previous();
		aKeyValue = iCurrentKey;
		return (found);
		}
	return (EFalse);
	}

/*

template<class Entry,class KeyValue>
inline TBool TAgnIterator<Entry,KeyValue>::End() // is this method required ?
	{ 
	if (iArray->Count() > 0)
		SetCursor(iArray->Count() - 1); 
	}
*/


template<class Entry,class KeyValue>
inline TBool TAgnIterator<Entry,KeyValue>::AtEnd()
//
// Is the current position beyond the end of the array
//
	{

	return (iArray->Count() == 0 || iCursor >= iArray->Count());
	}

template<class Entry,class KeyValue>
inline TBool TAgnIterator<Entry,KeyValue>::AtStart()
//
// Is the current position before the start of the array
//
	{

	return (iArray->Count() == 0 || iCursor < 0);
	}


/*
template<class Entry,class KeyValue>
inline TBool TAgnIterator<Entry,KeyValue>::Find(TKey& aKey, T& aEntry)
//
// If entry found set cursor to position of entry. What if this out of set range?
//
	{

	TInt pos;
	if (iArray->FindIsq(aEntry&, aKey, pos) == 0) {
		SetPositionDefined();
		SetCursor(pos);
		iCurrentKey = aKey;
		return ETrue;
	}
	return EFalse;
	}
*/

// --------------------------TAgnCompoundIteratorBase<Entry,KeyValue>-----------

template<class Entry, class KeyValue>
TAgnCompoundIteratorBase<Entry,KeyValue>::TAgnCompoundIteratorBase(TAgnIteratorBase<Entry,KeyValue>** aIterators)
	{

	__ASSERT_ALWAYS(aIterators!=NULL,Panic(EAgmErrNullPtr));
	iIterators = aIterators;
	iCount = 0;
	}

template<class Entry, class KeyValue>
Entry* TAgnCompoundIteratorBase<Entry,KeyValue>::CurrentElement()
	{

	__ASSERT_ALWAYS(iCurrent>=0 && iCurrent<iCount,Panic(EAgmErrCompoundIteratorOutOfRange));
	return iIterators[iCurrent]->CurrentElement();
	}

template<class Entry, class KeyValue>
const KeyValue& TAgnCompoundIteratorBase<Entry,KeyValue>::CurrentKey() const
	{

	__ASSERT_ALWAYS(iCurrent>=0 && iCurrent<iCount,Panic(EAgmErrCompoundIteratorOutOfRange));
	return iIterators[iCurrent]->CurrentKey();
	}

template<class Entry, class KeyValue>
void TAgnCompoundIteratorBase<Entry,KeyValue>::SetCount(TInt aCount) 
	{iCount = aCount;}


template<class Entry, class KeyValue>
void TAgnCompoundIteratorBase<Entry,KeyValue>::Start()
//
// Position all iterator to their start
//
	{

	for(TInt ii = 0; ii < iCount; ii++)
		iIterators[ii]->Start();
	SetCurrent();
	}

template<class Entry, class KeyValue>
void TAgnCompoundIteratorBase<Entry,KeyValue>::Next()
//
// move position to the next element
//
	{
	__ASSERT_ALWAYS(iCurrent>=0 && iCurrent<iCount,Panic(EAgmErrCompoundIteratorOutOfRange));

	KeyValue currentKey = iIterators[iCurrent]->CurrentKey();
	iIterators[iCurrent]->Next();
	if (iIterators[iCurrent]->AtEnd() || currentKey < iIterators[iCurrent]->CurrentKey())
		SetCurrent();
	}

template<class Entry, class KeyValue>
void TAgnCompoundIteratorBase<Entry,KeyValue>::Previous()
//
// move position to previous element
//
	{

	__ASSERT_ALWAYS(iCurrent>=0 && iCurrent<iCount,Panic(EAgmErrCompoundIteratorOutOfRange));

	KeyValue currentKey = iIterators[iCurrent]->CurrentKey();
	iIterators[iCurrent]->Previous();
	if (iIterators[iCurrent]->AtStart() || currentKey > iIterators[iCurrent]->CurrentKey())
		SetCurrentLessOrEqual();
	}

template<class Entry, class KeyValue>
TBool TAgnCompoundIteratorBase<Entry,KeyValue>::AtEnd()
//
// Are all iterators positioned to beyond the end
//
	{

	TInt ii;
	for(ii = 0; ii < iCount && iIterators[ii]->AtEnd();ii++)
		;
	return (ii == iCount);
	}

template<class Entry, class KeyValue>
TBool TAgnCompoundIteratorBase<Entry,KeyValue>::AtStart()
//
// Are all iterators positioned to before the start
//
	{

	TInt ii;
	for(ii = 0; ii < iCount && iIterators[ii]->AtStart();ii++)
		;
	return (ii == iCount);
	}


template<class Entry, class KeyValue>
TBool TAgnCompoundIteratorBase<Entry,KeyValue>::Goto(KeyValue& aKeyValue)
//
// Position to the first element whose keyvalue is >= aKeyValue
//
	{

	for(TInt ii = 0; ii < iCount;ii++)
		{
		KeyValue wkKeyValue(aKeyValue);
		iIterators[ii]->Goto(wkKeyValue);
		}
	return SetCurrent();
	}

template<class Entry, class KeyValue>
TBool TAgnCompoundIteratorBase<Entry,KeyValue>::GotoLessOrEqual(KeyValue& aKeyValue)
//
// Position to the first element whose keyvalue is >= aKeyValue
//
	{

	for(TInt ii = 0; ii < iCount;ii++)
		{
		KeyValue wkKeyValue(aKeyValue);
		iIterators[ii]->GotoLessOrEqual(wkKeyValue);
		}
	return SetCurrentLessOrEqual();
	}

template<class Entry, class KeyValue>
TBool TAgnCompoundIteratorBase<Entry,KeyValue>::SetCurrent()
//
// Set the current iterator
//
	{

	KeyValue best(0);
	iCurrent = -1;
	for(TInt ii = 0; ii < iCount; ii++)
		{
		if (!iIterators[ii]->AtEnd() && (iCurrent == -1 || best > iIterators[ii]->CurrentKey()))
			{
			best = iIterators[ii]->CurrentKey();
			iCurrent = ii;
			}
		}
	if(iCurrent == -1)
		return (EFalse);
	return (ETrue);
	}


template<class Entry, class KeyValue>
TBool TAgnCompoundIteratorBase<Entry,KeyValue>::SetCurrentLessOrEqual()
//
// Set the current iterator
//
	{

	KeyValue best(0);
	iCurrent = -1;
	for(TInt ii = 0; ii < iCount; ii++)
		{
		if (!iIterators[ii]->AtStart() && (iCurrent == -1 || best < iIterators[ii]->CurrentKey()))
			{
			best = iIterators[ii]->CurrentKey();
			iCurrent = ii;
			}
		}
	if(iCurrent == -1)
		return (EFalse);
	return (ETrue);
	}


// -------------------------------- EOF ----------------------------------------
