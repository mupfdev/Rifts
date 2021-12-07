// AGMLISTS.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//


// --------------------------- CAgnList<InstanceItem> --------------------------
template<class InstanceItem>
inline void CAgnList<InstanceItem>::Reset()
	{ iInstances->Reset(); }

template<class InstanceItem>
inline TInt CAgnList<InstanceItem>::Count() const
	{ return (iInstances->Count()); }

template<class InstanceItem>
inline void CAgnList<InstanceItem>::Delete(TInt aIndex)
	{ 
	__ASSERT_DEBUG(aIndex >= 0 && aIndex < iInstances->Count(),Panic(_L("Invalid index")));
	iInstances->Delete(aIndex); 
	}

template<class InstanceItem>
inline void CAgnList<InstanceItem>::AppendL(const InstanceItem& aElement)
	{ iInstances->AppendL(aElement); }

template<class InstanceItem>
inline void CAgnList<InstanceItem>::InsertL(TInt aIndex,const InstanceItem& aElement)
	{ 
	__ASSERT_DEBUG(aIndex >= 0 && aIndex < iInstances->Count(),Panic(_L("Invalid index")));
	iInstances->InsertL(aIndex,aElement);
	}

template<class InstanceItem>
inline TInt CAgnList<InstanceItem>::Find(const InstanceItem& aItem,TKeyArrayFix& aKey,TInt& aPos) const
	{ return (iInstances->Find(aItem,aKey,aPos)); }


template<class InstanceItem>
inline void CAgnList<InstanceItem>::ConstructL(TInt aGranularity)	
	{ iInstances=new(ELeave)CArrayFixFlat<InstanceItem>(aGranularity); }

template<class InstanceItem>
inline const InstanceItem& CAgnList<InstanceItem>::operator[](TInt aIndex) const
//
// Index into the list
//
	{ 
	
	__ASSERT_DEBUG(aIndex < Count(),Panic(_L("Instance List Index Out Of Range")));
	return ((*iInstances)[aIndex]);
	}


template<class InstanceItem>
CAgnList<InstanceItem>::~CAgnList()
//
// Destructor
//
	{
	
	delete iInstances;
	}

// --------------------------- CAgnDayList<InstanceItem> -----------------------
template<class InstanceItem>
inline CAgnDayList<InstanceItem>::CAgnDayList(const TTime& aDay)
	: iDay(aDay)
	{
	}

template<class InstanceItem>
inline void CAgnDayList<InstanceItem>::SetDay(const TTime& aDay)
	{ iDay=aDay; }

template<class InstanceItem>
inline TTime CAgnDayList<InstanceItem>::Day() const
	{ return(iDay); }


template<class InstanceItem>
inline CAgnDayList<InstanceItem>* CAgnDayList<InstanceItem>::NewL(const TTime& aDay)
//
// Create a CAgnDayList object
//
	{

	CAgnDayList* Self=new(ELeave)CAgnDayList(aDay);
	CleanupStack::PushL(Self);
	Self->ConstructL(EGranularity);
	CleanupStack::Pop();
	return (Self);
	}

// ------------------------------- CAgnDayDateTimeInstanceList --------------------
inline CAgnDayDateTimeInstanceList::CAgnDayDateTimeInstanceList(const TTime& aDay)
	:CAgnDayList<TAgnInstanceDateTimeId>(aDay)
	{
	}

// -------------------------- CAgnMonthInstanceList ------------------------------------
inline CAgnMonthInstanceList::CAgnMonthInstanceList(TTimeIntervalYears aYear,TMonth aMonth)
	: iYear(aYear),iMonth(aMonth)
	{
	}

inline void CAgnMonthInstanceList::SetYear(TTimeIntervalYears aYear)
	{ iYear=aYear; }

inline void CAgnMonthInstanceList::SetMonth(TMonth aMonth)
	{ iMonth=aMonth; }

inline TTimeIntervalYears CAgnMonthInstanceList::Year() const
	{ return (iYear); }

inline TMonth CAgnMonthInstanceList::Month() const
	{ return (iMonth); }




// -------------------------- CAgnTodoInstanceList -----------------------------------
inline CAgnTodoInstanceList::CAgnTodoInstanceList(TAgnTodoListId aTodoListId)
	: iTodoListId(aTodoListId)
	{
	}

inline void CAgnTodoInstanceList::SetTodoListId(TAgnTodoListId aTodoListId)
	{ iTodoListId=aTodoListId; }

inline TAgnTodoListId CAgnTodoInstanceList::TodoListId() const
	{ return (iTodoListId); }

inline CAgnTodoList::TSortOrder CAgnTodoInstanceList::SortOrder() const
	{ return (iSortOrder); }

inline void CAgnTodoInstanceList::SetSortOrder(CAgnTodoList::TSortOrder aSortOrder)
	{ iSortOrder=aSortOrder; }


inline const TAgnInstanceId& CAgnTodoInstanceList::Id(TInt aIndex) const
	{
	__ASSERT_DEBUG(aIndex >= 0 && aIndex < Count(),Panic(_L("Invalid index")));
	return ((*this)[aIndex]);
	}


// ----------------------------- CAgnSymbolList -----------------------------------
inline TUint CAgnSymbolList::TListItem::DayNumber() const
	{ return (iDayNumber); }

inline TUint 	CAgnSymbolList::TListItem::NumSymbols() const
	{ return (iNumSymbols); }

inline TBool 	CAgnSymbolList::TListItem::MoreSymbols() const
	{ return (iMoreSymbols); }

inline TChar CAgnSymbolList::TListItem::FirstSymbol() const
	{ return (iFirstSymbol); }

inline TChar CAgnSymbolList::TListItem::SecondSymbol() const
	{ return (iSecondSymbol); }

inline TRgb CAgnSymbolList::TListItem::FirstSymbolColor() const
	{ return (iFirstSymbolColor); }

inline void CAgnSymbolList::TListItem::SetNumSymbols(TUint aNumSymbols)
	{ iNumSymbols=(TUint8)aNumSymbols; }

inline void		CAgnSymbolList::TListItem::SetMoreSymbols(TBool aMoreSymbols)
	{ iMoreSymbols=aMoreSymbols; }

inline void		CAgnSymbolList::TListItem::SetFirstSymbol(TChar aSymbol)
	{ iFirstSymbol=aSymbol; }

inline void 	CAgnSymbolList::TListItem::SetSecondSymbol(TChar aSymbol)
	{ iSecondSymbol=aSymbol; }

inline void 	CAgnSymbolList::TListItem::SetFirstSymbolColor(const TRgb& aColor)
	{ iFirstSymbolColor=aColor; }

inline TTimeIntervalYears CAgnSymbolList::Year() const
	{ return (iYear); }

inline TMonth CAgnSymbolList::Month() const
	{ return (iMonth); }

inline TInt CAgnSymbolList::Count() const
	{ return (iSymbols->Count()); }


