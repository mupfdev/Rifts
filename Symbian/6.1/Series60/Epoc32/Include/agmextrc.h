// AGMEXTRC.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __AGMEXTRC_H__
#define __AGMEXTRC_H__

#include "agmxiter.h"

// local classes ---------------------------------------------------------------


// -----------------------------------------------------------------------------
class TAgnApptRptIterator;
class TAgnApptNonRpt1dayIterator;
class TAgnApptNonRptNdayIterator;
class TAgnApptIterator;
class TAgnTodoNonRptIterator;
class TAgnTodoRptIterator;

// ----------------------------TAgnInstanceExtractor----------------------------
// Instance Extractor 
//
class TAgnInstanceExtractorBase
	{
public:	
	TAgnInstanceExtractorBase(CAgnSortEntryTable* aEntryInfoTable, TAgnDate aToday, const TAgnFilter* aFilter = NULL);
	virtual ~TAgnInstanceExtractorBase();
	virtual void GetDayListL(TAgnDate aDate, CArrayFixFlat<TAgnSortInstance>* aList) = 0;
	virtual TBool NextDay(TAgnDate& aDate,TAgnDate aEndDate=AgnDateTime::MaxDate()) = 0;				
	virtual TBool PreviousDay(TAgnDate& aDate,TAgnDate aStartDate=AgnDateTime::MinDate()) = 0;
protected:
	const TAgnFilter* Filter() const { return iFilter; }
	TAgnDate Today() const { return iToday; }
	CAgnSortEntryTable* InfoTable() {return iTable;}

private:
	CAgnSortEntryTable* iTable;
	const TAgnFilter* iFilter;
	TAgnDate iToday;
	};
// ----------------------------TAgnInstanceExtractorSingleBase----------------------
class TAgnInstanceExtractorSingleBase : public TAgnInstanceExtractorBase
	{
public:
	TAgnInstanceExtractorSingleBase(CAgnSortEntryTable* aEntryInfoTable, TAgnDate aToday, const TAgnFilter* aFilter = NULL)
		: TAgnInstanceExtractorBase(aEntryInfoTable,aToday,aFilter) {}
	virtual void GetDayListL(TAgnDate aDate, CArrayFixFlat<TAgnSortInstance>* aList);
	virtual TBool NextDay(TAgnDate& aDate,TAgnDate aEndDate=AgnDateTime::MaxDate());				
	virtual TBool PreviousDay(TAgnDate& aDate,TAgnDate aStartDate=AgnDateTime::MinDate());
protected:
	virtual void GetDayListBaseL(TAgnIteratorBase& aIter, TAgnDate aDate, CArrayFixFlat<TAgnSortInstance>* aList) const = 0;
	virtual TBool NextDayBase(TAgnIteratorBase& aIter, TAgnDate& aDate,TAgnDate aEndDate=AgnDateTime::MaxDate()) const = 0;				
	virtual TBool PreviousDayBase(TAgnIteratorBase& aIter, TAgnDate& aDate,TAgnDate aStartDate=AgnDateTime::MinDate()) const = 0;				
	virtual TAgnIteratorBase& Iterator() = 0;
	};

// ----------------------------TAgnInstanceExtractorCompoundBase----------------------
class TAgnInstanceExtractorCompoundBase : public TAgnInstanceExtractorBase
	{
public:	
	TAgnInstanceExtractorCompoundBase(CAgnSortEntryTable* aEntryInfoTable, TAgnDate aToday, const TAgnFilter* aFilter = NULL)
		: TAgnInstanceExtractorBase(aEntryInfoTable,aToday,aFilter) {}
	virtual void GetDayListL(TAgnDate aDate, CArrayFixFlat<TAgnSortInstance>* aList);
	virtual TBool NextDay(TAgnDate& aDate,TAgnDate aEndDate=AgnDateTime::MaxDate());				
	virtual TBool PreviousDay(TAgnDate& aDate,TAgnDate aStartDate=AgnDateTime::MinDate());
protected:
	TBool NextDayFromList(TAgnDate& aDate, TAgnInstanceExtractorBase** Extractors,TAgnDate aEndDate=AgnDateTime::MaxDate());
	TBool PreviousDayFromList(TAgnDate& aDate, TAgnInstanceExtractorBase** Extractors,TAgnDate aStartDate=AgnDateTime::MinDate());
	void GetDayListFromListL(TAgnDate aDate, CArrayFixFlat<TAgnSortInstance>* aDayList, TAgnInstanceExtractorBase** Extractors);
	virtual TAgnInstanceExtractorBase** Extractors() = 0;
private:
	};

// ----------------------------TAgnNonRptInstanceExtractor----------------------
// Instance Extractor - For all non repeating entries
//
class TAgnNonRptInstanceExtractor : public TAgnInstanceExtractorSingleBase
	{
public:	
	TAgnNonRptInstanceExtractor(CAgnSortEntryTable* aEntryInfoTable, TAgnDate aToday, const TAgnFilter* aFilter = NULL)
		: TAgnInstanceExtractorSingleBase(aEntryInfoTable,aToday,aFilter) {}
protected:
	virtual void GetDayListBaseL(TAgnIteratorBase& aIter, TAgnDate aDate, CArrayFixFlat<TAgnSortInstance>* aList) const;
	virtual TBool NextDayBase(TAgnIteratorBase& aIter, TAgnDate& aDate,TAgnDate aEndDate=AgnDateTime::MaxDate()) const;				
	virtual TBool PreviousDayBase(TAgnIteratorBase& aIter, TAgnDate& aDate,TAgnDate aStartDate=AgnDateTime::MinDate()) const;				
private:
	};

// ----------------------------TAgnNonRptNdayInstanceExtractor------------------
// Instance Extractor - For all non repeating entries
//
class TAgnNonRptNdayInstanceExtractor : public TAgnNonRptInstanceExtractor
	{
public:	
	TAgnNonRptNdayInstanceExtractor(CAgnSortEntryTable* aEntryInfoTable, TAgnDate aToday, const TAgnFilter* aFilter = NULL)
		: TAgnNonRptInstanceExtractor(aEntryInfoTable,aToday,aFilter) {}
protected:
	virtual TBool PreviousDayBase(TAgnIteratorBase& aIter, TAgnDate& aDate,TAgnDate aStartDate=AgnDateTime::MinDate()) const;				
	};


// ----------------------------TAgnApptNonRpt1dayInstanceExtractor--------------
// Instance Extractor - For non repeating appts that don't span midnight
//
class TAgnApptNonRpt1dayInstanceExtractor : public TAgnNonRptInstanceExtractor
	{
public:	
	TAgnApptNonRpt1dayInstanceExtractor(CAgnSortEntryTable* aEntryInfoTable, TAgnDate aToday, const TAgnFilter* aFilter = NULL);
protected:
	virtual TAgnIteratorBase& Iterator();
private:
	TAgnEntryInfoFilter iFilter;
	TAgnApptNonRpt1dayIterator iIter;
	};


// ----------------------------TAgnApptNonRptNdayInstanceExtractor--------------
// Instance Extractor - For non repeating appts that do span midnight
//
class TAgnApptNonRptNdayInstanceExtractor : public TAgnNonRptNdayInstanceExtractor
	{
public:	
	TAgnApptNonRptNdayInstanceExtractor(CAgnSortEntryTable* aEntryInfoTable, TAgnDate aToday, const TAgnFilter* aFilter = NULL);
protected:
	virtual TAgnIteratorBase& Iterator();
private:
	TAgnEntryInfoFilter iFilter;
	TAgnApptNonRptNdayIterator iIter;
	};

// --------------------------TAgnApptNonRptInstanceExtractor--------------------
// Instance Extractor - For all non repeating appts 
//
class TAgnApptNonRptInstanceExtractor : public TAgnInstanceExtractorCompoundBase
	{
public:	
	TAgnApptNonRptInstanceExtractor(CAgnSortEntryTable* aEntryInfoTable, TAgnDate aToday, const TAgnFilter* aFilter = NULL);
protected:
	virtual TAgnInstanceExtractorBase** Extractors();
private:
	TAgnInstanceExtractorBase* iExtractors[3];
	TAgnApptNonRpt1dayInstanceExtractor iApptNonRpt1dayExtrctr;
	TAgnApptNonRptNdayInstanceExtractor iApptNonRptNdayExtrctr;
	};



// ----------------------------TAgnRptInstanceExtractor-------------------------
// Instance Extractor - For all non repeating appts 
//
class TAgnRptInstanceExtractor : public TAgnInstanceExtractorSingleBase
	{
public:	
	TAgnRptInstanceExtractor(CAgnSortEntryTable* aEntryInfoTable, TAgnDate aToday, const TAgnFilter* aFilter = NULL)
		: TAgnInstanceExtractorSingleBase(aEntryInfoTable,aToday,aFilter) {}
protected:
	virtual void GetDayListBaseL(TAgnIteratorBase& aIter, TAgnDate aDate, CArrayFixFlat<TAgnSortInstance>* aList) const;
	virtual TBool NextDayBase(TAgnIteratorBase& aIter, TAgnDate& aDate,TAgnDate aEndDate=AgnDateTime::MaxDate()) const;				
	virtual TBool PreviousDayBase(TAgnIteratorBase& aIter, TAgnDate& aDate,TAgnDate aStartDate=AgnDateTime::MinDate()) const;				
private:
	TBool FindNextDate(CAgnSortEntry* info, TAgnDate aFromDate, TAgnDate& aNextDate,TAgnDate aEndDate=AgnDateTime::MaxDate()) const;
	TBool FindPreviousDate(CAgnSortEntry* info, TAgnDate aFromDate, TAgnDate& aPrevDate,TAgnDate aStartDate=AgnDateTime::MinDate()) const;
	TBool FindPreviousInstanceOnDate(CAgnSortEntry* info, TAgnDate aFrom, TAgnDate aTarget, TAgnDate& aPrev) const;
	};


// ----------------------------TAgnRptApptInstanceExtractor---------------------
// Instance Extractor - For all repeating appts 
//
class TAgnApptRptInstanceExtractor : public TAgnRptInstanceExtractor
	{
public:	
	TAgnApptRptInstanceExtractor(CAgnSortEntryTable* aEntryInfoTable, TAgnDate aToday, const TAgnFilter* aFilter = NULL);
protected:
	virtual TAgnIteratorBase& Iterator();
private:
	TAgnEntryInfoFilter iFilter;
	TAgnApptRptIterator iIter;
	};

// ----------------------------TAgnApptInstanceExtractor------------------------
// Instance Extractor - For all appts 
//
class TAgnApptInstanceExtractor : public TAgnInstanceExtractorCompoundBase
	{
public:	
	TAgnApptInstanceExtractor(CAgnSortEntryTable* aEntryInfoTable, TAgnDate aToday, const TAgnFilter* aFilter = NULL);
protected:
	virtual TAgnInstanceExtractorBase** Extractors();
private:
	TAgnInstanceExtractorBase* iExtractors[3];
	TAgnApptNonRptInstanceExtractor iApptNonRptExtrctr;
	TAgnApptRptInstanceExtractor iApptRptExtrctr;
	};


// ----------------------------TAgnEventInstanceExtractor-----------------------
// Instance Extractor - For all non-repeating events
//
class TAgnEventInstanceExtractor : public TAgnNonRptNdayInstanceExtractor
	{
public:	
	TAgnEventInstanceExtractor(CAgnSortEntryTable* aEntryInfoTable, TAgnDate aToday, const TAgnFilter* aFilter = NULL);
protected:
	virtual TAgnIteratorBase& Iterator();
private:
	TAgnEntryInfoFilter iFilter;
	TAgnEventIterator iIter;
	};

// ----------------------------TAgnEventRptInstanceExtractor-----------------------
// Instance Extractor - For all repeating events
//
class TAgnEventRptInstanceExtractor : public TAgnRptInstanceExtractor
	{
public:	
	TAgnEventRptInstanceExtractor(CAgnSortEntryTable* aEntryInfoTable, TAgnDate aToday, const TAgnFilter* aFilter = NULL);
protected:
	virtual TAgnIteratorBase& Iterator();
private:
	TAgnEntryInfoFilter iFilter;
	TAgnEventRptIterator iIter;
	};


// ----------------------------TAgnAnnivInstanceExtractor-----------------------
// Instance Extractor - For all non repeating annivs
//
class TAgnAnnivRptInstanceExtractor : public TAgnRptInstanceExtractor
	{
public:	
	TAgnAnnivRptInstanceExtractor(CAgnSortEntryTable* aEntryInfoTable, TAgnDate aToday, const TAgnFilter* aFilter = NULL);
protected:
	virtual TAgnIteratorBase& Iterator();
private:
	TAgnEntryInfoFilter iFilter;
	TAgnAnnivRptIterator iIter;
	};



class TAgnTodoSelector
	{
public:
	virtual TBool IsValid(CAgnSortEntry* aInfo, TAgnDate aDate) = 0;
private:
	};

class TAgnTodoTodaySelector : public TAgnTodoSelector
	{
public:
	TAgnTodoTodaySelector(TAgnDate aDate) { iToday = aDate; }
	virtual TBool IsValid(CAgnSortEntry* aInfo, TAgnDate aDate);
private:
	TAgnDate iToday;
	};

class TAgnTodoBeforeTodaySelector : public TAgnTodoSelector
	{
public:
	virtual TBool IsValid(CAgnSortEntry* aInfo, TAgnDate aDate);
	};

class TAgnTodoAfterTodaySelector : public TAgnTodoSelector
	{
public:
	virtual TBool IsValid(CAgnSortEntry* aInfo, TAgnDate aDate);
	};

class TAgnTodoListSelector : public TAgnTodoSelector
	{
public:
	TAgnTodoListSelector(const TAgnEntryId& aId) {iTodoListId = aId;}
	virtual TBool IsValid(CAgnSortEntry* aInfo, TAgnDate aDate);
private:
	TAgnEntryId iTodoListId;
	};

// ----------------------------TAgnTodoNonRptInstanceExtractor------------------
// Extractor of single todos
//
class TAgnTodoNonRptInstanceExtractor : public TAgnInstanceExtractorBase
	{
public:	
	TAgnTodoNonRptInstanceExtractor(CAgnSortEntryTable* aEntryInfoTable, TAgnDate aToday, const TAgnFilter* aFilter = NULL);
	virtual void GetDayListL(TAgnDate aDate, CArrayFixFlat<TAgnSortInstance>* aList);
	virtual TBool NextDay(TAgnDate& aDate,TAgnDate aEndDate=AgnDateTime::MaxDate());				
	virtual TBool PreviousDay(TAgnDate& aDate,TAgnDate aStartDate=AgnDateTime::MinDate());
	void GetTodoListL(const TAgnEntryId& aId, CArrayFixFlat<TAgnSortInstance>* aList);
private:
	void GetTodoListL(TAgnTodoSelector* const aSelector, TAgnDate aTargetDate, TAgnDate aStartDate, TAgnDate aEndDate,CArrayFixFlat<TAgnSortInstance>* aDayList);
	TBool NextDay(TAgnTodoSelector* const aSelector, TAgnDate aStartDate, TAgnDate aEndDate,TAgnDate& aNextDate);
	TBool PreviousDay(TAgnTodoSelector* const aSelector, TAgnDate aStartDate, TAgnDate aEndDate,TAgnDate& aPrevDate);
	};

// ----------------------------TAgnTodoRptInstanceExtractor---------------------
// Instance Extractor - For all repeating todos
//
class TAgnTodoRptInstanceExtractor : public TAgnInstanceExtractorBase
	{
public:	
	TAgnTodoRptInstanceExtractor(CAgnSortEntryTable* aEntryInfoTable, TAgnDate aToday, const TAgnFilter* aFilter = NULL)
		: TAgnInstanceExtractorBase(aEntryInfoTable,aToday,aFilter) {}
	virtual void GetDayListL(TAgnDate aDate, CArrayFixFlat<TAgnSortInstance>* aList);
	virtual TBool NextDay(TAgnDate& aDate,TAgnDate aEndDate=AgnDateTime::MaxDate());				
	virtual TBool PreviousDay(TAgnDate& aDate,TAgnDate aStartDate=AgnDateTime::MinDate());
private:
	};


// ----------------------------TAgnInstanceExtractor----------------------------
// Instance extractor for all entry types
//
class TAgnInstanceExtractor : public TAgnInstanceExtractorCompoundBase
	{
public:	
	TAgnInstanceExtractor(CAgnSortEntryTable* aEntryInfoTable, TAgnDate aToday, const TAgnFilter* aFilter = NULL);
protected:
	virtual TAgnInstanceExtractorBase** Extractors();
private:
	TAgnInstanceExtractorBase* iExtractors[8];
	TAgnApptInstanceExtractor iApptExtrctr;
	TAgnTodoNonRptInstanceExtractor iTodoNonRptExtrctr;
	TAgnTodoRptInstanceExtractor iTodoRptExtrctr;
	TAgnEventInstanceExtractor iEventExtrctr;
	TAgnAnnivRptInstanceExtractor iAnnivRptExtrctr;
	TAgnEventRptInstanceExtractor iEventRptExtrctr;
	};

class TAgnInstIter
	{
public:
	TAgnInstIter(CAgnSortEntry* aSortEntry, TAgnDate aToday);
	TBool NextInstanceOnDate(TAgnDate aDate, TAgnDate& aInstStartDate, TAgnDate& aInstEndDate, TBool aNextInstOnly);
	TBool NextInstance(TAgnDate aFromDate, TAgnDate& aInstStartDate, TAgnDate& aInstEndDate, TBool aNextInstOnly);
protected:
	CAgnSortEntry* iSortEntry;
	};

class TAgnTodoInstIter
	{
public:
	TAgnTodoInstIter(CAgnSortEntry* aEntry, TAgnDate aToday);
	TBool NextInstanceOnDate(TAgnDate aDate,TAgnDate& aInstStartDate,TAgnDate& aInstEndDate, TBool aNextInstOnly);
	TBool NextInstance(TAgnDate aFromDate,TAgnDate& aAppearanceDate,TAgnDate& aInstStartDate, TAgnDate& aInstEndDate, TBool aNextInstOnly);
	TBool PreviousInstance(TAgnDate aDate,TAgnDate& aAppearanceDate,TAgnDate& aInstStartDate,TAgnDate& aInstEndDate, TBool aNextInstOnly);
private:
	TAgnDate InstanceStartDate(TAgnDate aInstDueDate, TAgnDurationDays aDuration, TAgnDate aPrevInstDueDate) const;
	CAgnSortEntry* iSortEntry;
	TAgnDate iToday;
	TAgnDate Today() const { return iToday; }
	TBool FindNextDate(TAgnDate aFromDate,TAgnDate& aAppearanceDate,TAgnDate& aNextDate,TAgnDate& aNextEndDate,TBool aNextOnly) const;
	};


#endif

// -------------------------------- EOF ----------------------------------------
