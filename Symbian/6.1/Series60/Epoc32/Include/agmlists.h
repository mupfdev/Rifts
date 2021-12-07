// AGMLISTS.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __AGMLISTS_H__
#define __AGMLISTS_H__

#include <e32base.h>
#include "agmids.h"
#include "agmtodos.h"

template<class InstanceItem>
class CAgnList : public CBase
//
// Interface to a list of instance ids
//
	{
public:
	CAgnList(){};
	virtual ~CAgnList();

	inline TInt Count() const;
	inline const InstanceItem& operator[](TInt aIndex) const;
	inline void Reset();
	inline void Delete(TInt aIndex);
	inline void AppendL(const InstanceItem& aElement);
	inline void InsertL(TInt aIndex,const InstanceItem& aElement);
	inline TInt Find(const InstanceItem& aItem,TKeyArrayFix& aKey,TInt& aPos) const;
//protected:
	inline void ConstructL(TInt aGranularity);
private:
	inline CAgnList<InstanceItem>& operator=(const CAgnList<InstanceItem>&);	// not defined
private:
	CArrayFixFlat<InstanceItem>* iInstances;
	};



template<class InstanceItem>
class CAgnDayList : public CAgnList<InstanceItem>
//
// Contains a list of entry instance ids for a particular day.
//
// Note that the instance date of an instance DOES NOT have to be the same as the date of the
// day list i.e. 	
//					day 1	|	day 2	|  day 3			
//			   <--- inst 1----->  <----- inst 2 -->			(a repeating entry spanning midnight)
//
// If a day list is fetched for day2 then there are 2 instances of the same entry for that day 
// (this is only the case with  appointments, todos will have been hoovered first). Instance 1
// will therefore have an instance date of day1, while instance 2 will have an instace date of day2.
	{
public:
	virtual ~CAgnDayList() {}
	inline static CAgnDayList* NewL(const TTime& aDay); 
	inline void SetDay(const TTime& aDay);
	inline TTime Day() const;
protected:
	enum {EGranularity=4};
	inline CAgnDayList(const TTime& aDay);
private:
	CAgnDayList(const CAgnDayList<InstanceItem>&);			// not defined
	CAgnDayList<InstanceItem>& operator=(const CAgnDayList<InstanceItem>&);	// not defined
private:
	TTime iDay;
	};


class CAgnDayDateTimeInstanceList : public CAgnDayList<TAgnInstanceDateTimeId>
//
// Adds the start date/time and end date time from an instance to a day instance list
//
	{
public:
	IMPORT_C static CAgnDayDateTimeInstanceList* NewL(const TTime& aDay);
	IMPORT_C virtual ~CAgnDayDateTimeInstanceList();
protected:
	inline CAgnDayDateTimeInstanceList(const TTime& aDay);
private:
	CAgnDayDateTimeInstanceList(const CAgnDayDateTimeInstanceList&);			// not defined
	CAgnDayDateTimeInstanceList& operator=(const CAgnDayDateTimeInstanceList&);	// not defined
private:
	};


class CAgnMonthInstanceList : public CAgnList<TAgnInstanceId>
//
// Contains a list of entry instance ids for a month
//
	{
public:
	IMPORT_C static CAgnMonthInstanceList* NewL(TTimeIntervalYears aYear,TMonth aMonth);
	inline void SetYear(TTimeIntervalYears aYear);
	inline void SetMonth(TMonth aMonth);
	inline TTimeIntervalYears Year() const;
	inline TMonth Month() const;
protected:
	enum {EGranularity=8};
	inline CAgnMonthInstanceList(TTimeIntervalYears aYear,TMonth aMonth);
private:
	CAgnMonthInstanceList(const CAgnMonthInstanceList&); 	// not defined
	CAgnMonthInstanceList& operator=(const CAgnMonthInstanceList&); // not defined
private:
	TTimeIntervalYears	iYear;
	TMonth 				iMonth;
	};



class CAgnTodoInstanceList : public CAgnList<TAgnInstanceId>
//
// Contains a list of entry instance ids for a todo category
//
	{
public:
	IMPORT_C static CAgnTodoInstanceList* NewL(TAgnTodoListId aTodoListId=AgnModel::NullTodoListId());
	inline void SetTodoListId(TAgnTodoListId aTodoListId);
	inline TAgnTodoListId TodoListId() const; 
	inline CAgnTodoList::TSortOrder SortOrder() const;	
	inline void SetSortOrder(CAgnTodoList::TSortOrder aSortOrder);
	IMPORT_C TInt Find(TAgnInstanceId aId,TInt& aPos); 
	inline const TAgnInstanceId& Id(TInt aIndex) const;
protected:
	enum {EGranularity=8};
	inline CAgnTodoInstanceList(TAgnTodoListId aTodoListId);
private:
	CAgnTodoInstanceList(const CAgnTodoInstanceList&); // not defined
	CAgnTodoInstanceList& operator=(const CAgnTodoInstanceList&); // not defined
private:
	TAgnTodoListId				iTodoListId;
	CAgnTodoList::TSortOrder	iSortOrder;
	};




class CAgnSymbolList : public CBase
//
// Contains a list of entry symbols for a month, there can be a maximum of two symbols per day
// stored in the list with MoreSymbols(a day) being true is there exist more than 2 that could 
// have been stored.
//
	{
public:
	class TListItem
		{
	public:
		friend class CAgnSymbolList; // CAgnSymbolList's iKey uses _FOFF which requires access to iDayNumber
		inline TUint 	DayNumber() const;
		inline TUint 	NumSymbols() const;
		inline TBool 	MoreSymbols() const;
		inline TChar	FirstSymbol() const;
		inline TChar	SecondSymbol() const;
		inline TRgb		FirstSymbolColor() const;
		void SetDayNumber(TUint aDayNumber);
		inline void		SetNumSymbols(TUint aNumSymbols);
		inline void		SetMoreSymbols(TBool aMoreSymbols);
		inline void		SetFirstSymbol(TChar aSymbol);
		inline void 	SetSecondSymbol(TChar aSymbol);
		inline void 	SetFirstSymbolColor(const TRgb& aColor);
		void ExternalizeL(RWriteStream& aStream);
		void InternalizeL(RReadStream& aStream);
	private:
		TBool		iMoreSymbols;	// True if there are more symbols for the day than iNumSymbols
		TChar		iFirstSymbol;		
		TChar		iSecondSymbol;	
		TUint8		iDayNumber; 	// 0 - 30
		TUint8		iNumSymbols;	// The number of symbols in this item
		TUint16		iFiller;
		TRgb		iFirstSymbolColor;
		};

	IMPORT_C static CAgnSymbolList* NewL(TTimeIntervalYears aYear,TMonth aMonth);
	IMPORT_C virtual ~CAgnSymbolList();

	IMPORT_C void SetYearAndMonth(TTimeIntervalYears aYear,TMonth aMonth);
	IMPORT_C void SetYear(TTimeIntervalYears aYear);
	IMPORT_C void SetMonth(TMonth aMonth);
	inline TTimeIntervalYears Year() const;
	inline TMonth Month() const;
	inline TInt Count() const;

	IMPORT_C TUint 	DayNumber(TInt aIndex) const;
	IMPORT_C TUint 	NumSymbols(TInt aIndex) const;
	IMPORT_C TBool 	MoreSymbols(TInt aIndex) const;
	IMPORT_C TChar	FirstSymbol(TInt aIndex) const;
	IMPORT_C TChar	SecondSymbol(TInt aIndex) const;

	IMPORT_C TBool NextDay(TUint& aDayNum);
	IMPORT_C TBool PreviousDay(TUint& aDayNum);
	IMPORT_C void SetIteratorToStart();

	IMPORT_C TUint NumSymbolsForDay(TUint aDayNum,TInt& aIndex);
	IMPORT_C const TListItem& operator[](TInt aIndex) const;

	// Not to be called from outside the model:
	void Reset();
	void InsertIsqL(const TListItem* aItem);

	void ExternalizeL(RWriteStream& aStream);
	void InternalizeL(RReadStream& aStream);
protected:
	enum {EGranularity=8};
	void ConstructL();
	CAgnSymbolList(TTimeIntervalYears aYear,TMonth aMonth);

private:
	CAgnSymbolList(const CAgnSymbolList&);				// not defined
	CAgnSymbolList& operator=(const CAgnSymbolList&);	// not defined

private:
	enum TSymbol{EFirstSymbol,ESecondSymbol}; // states used by the iterator

	TKeyArrayFix 				iKey;	// TListItems are inserted in sequence with iDayNumber as the key
	CArrayFixFlat<TListItem>* 	iSymbols;
	TMonth						iMonth; 
	TTimeIntervalYears			iYear; // may be better to use a different type, this will do for now
	TSymbol						iCurrentSymbol; // cursor over the symbols in a day
	TUint						iCurrentDay; // cursor over the days (i.e. elements of the list)
	};



#include "agmlists.inl"

#endif
