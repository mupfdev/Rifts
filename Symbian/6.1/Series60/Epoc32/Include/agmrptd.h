// AGMRPTD.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//
#ifndef __AGMRPT_H__
#define __AGMRPT_H__

#include <e32base.h>
#include "agmexcpt.h"

// --------------------------------------- Local classes -----------------------------
class TAgnRpt;
class TAgnDailyRpt;
class TAgnWeeklyRpt;
class TAgnMonthlyByDatesRpt;
class TAgnMonthlyByDaysRpt;
class TAgnYearlyByDateRpt;
class TAgnYearlyByDayRpt;
class CAgnRptDef;


class TAgnRpt
//
// Stores data common to all repeating entry types
//
	{
public:
	friend class CAgnRptDef;
	enum TWeekInMonth{EFirst=0,ESecond,EThird,EFourth,ELast}; // crap implementation requires EFirst to be 0

	IMPORT_C TAgnRpt();
	IMPORT_C TAgnRpt(const TAgnRpt& aRpt);
	IMPORT_C TTime StartDate() const;
	IMPORT_C TTime EndDate() const;
	inline TAgnDate StartDateAsAgnDate() const;
	inline TAgnDate EndDateAsAgnDate() const;
	inline TInt Interval() const;
	inline TBool DisplayNextOnly() const;
	inline TBool RepeatForever() const;
	inline void SetInterval(TUint aInterval);
	inline void SetDisplayNextOnly(TBool aDisplayNextOnly);
	IMPORT_C void SetStartDate(const TTime& aStartdate);
	IMPORT_C void SetEndDate(const TTime& aEndDate);
	inline void SetStartDate(TAgnDate aStartdate);
	inline void SetEndDate(TAgnDate aEndDate);
	virtual TUint InstanceCount() const = 0;
	IMPORT_C void SetRepeatForever(TBool aRepeatForever);
	IMPORT_C void ClearAll();
	IMPORT_C TBool operator==(const TAgnRpt& aRpt) const;
	IMPORT_C virtual TTime FindRptEndDate(TUint aCount) const = 0;
	IMPORT_C virtual void InternalizeL(RReadStream& aStream);
	IMPORT_C virtual void ExternalizeL(RWriteStream& aStream) const; 
protected:
	virtual TInt Invariant() const;	 // self testing
	virtual TBool IsAligned(TAgnDate aDate,TBool aDummy=EFalse) const;
	virtual TAgnDate NudgeNextInstance(TAgnDate aDay,TBool aDummy=EFalse) const = 0;
	virtual TAgnDate NudgePreviousInstance(TAgnDate aDay) const = 0;

	TUint MapToBits(TDay aDay) const;
	TUint MapToBits(TUint aNum) const;

private:
	TAgnDate	iStartDate;	
	TAgnDate	iEndDate; 
	TUint16		iInterval;
	TUint8		iDisplayNextOnly; 	// if true then the repeat should only appear once in
									// the dated views on the 1st occurence after today
	TUint8		iRepeatForever; 	// is true if the repeat has no end date 
	};



class TAgnDailyRpt : public TAgnRpt
//
// i,e. repeat every x days 
//
	{
public:
	IMPORT_C TAgnDailyRpt();
	IMPORT_C TAgnDailyRpt(const TAgnRpt& aRpt);
	IMPORT_C TAgnDailyRpt(const TAgnDailyRpt& aRpt);
	IMPORT_C virtual TUint InstanceCount() const;
	IMPORT_C virtual TTime FindRptEndDate(TUint aCount) const;
protected:
	virtual TBool IsAligned(TAgnDate aDate,TBool aDummy=EFalse) const;
	virtual TAgnDate NudgeNextInstance(TAgnDate aDay,TBool aDummy=EFalse) const;
	virtual TAgnDate NudgePreviousInstance(TAgnDate aDay) const;
	};
	


class TAgnWeeklyRpt	: public TAgnRpt
//
// Holds the days in a week that a weekly repeat entry can repeat on in addition 
// to the the start day of the week.
// i.e.repeat every x weeks on days Monday and Thursday with Tuesday as the 
// first day of the week
//
	{
public:
	IMPORT_C TAgnWeeklyRpt();
	IMPORT_C TAgnWeeklyRpt(const TAgnRpt& aRpt);
	IMPORT_C TAgnWeeklyRpt(const TAgnWeeklyRpt& aRpt);
	IMPORT_C void SetDay(TDay aDay);
	IMPORT_C void UnsetDay(TDay aDay);
	IMPORT_C TBool IsDaySet(TDay aDay) const;
	inline void ClearDays();
	IMPORT_C TBool operator==(const TAgnWeeklyRpt& aRpt) const;
	IMPORT_C void SetFirstDayOfWeek(TDay aDay);//this function is for testing purposes - the start day is
	IMPORT_C TDay FirstDayOfWeek() const;	 	// set automatically from the operating system
	IMPORT_C TUint NumDaysSet() const;
	IMPORT_C virtual TUint InstanceCount() const;
	IMPORT_C virtual TTime FindRptEndDate(TUint aCount) const;
	virtual TInt Invariant() const;	  // self testing
	IMPORT_C virtual void InternalizeL(RReadStream& aStream);
	IMPORT_C virtual void ExternalizeL(RWriteStream& aStream) const; 
protected:
	virtual TBool IsAligned(TAgnDate aDate,TBool aDummy=EFalse) const;
	virtual TAgnDate NudgeNextInstance(TAgnDate aDay,TBool aDummy=EFalse) const;
	virtual TAgnDate NudgePreviousInstance(TAgnDate aDay) const;
	TInt DayAtStartOfWeek(TAgnDate aDay) const;
	TInt IsDateInValidWeek(TInt aDate) const;
	TInt WeekNo(TInt aDate) const;
private:
	TUint8 	iWeeklyRptDays; //stores the days of the week in the lowest 7 bits (bit 1 = Monday)
	TUint8 	iFirstDayOfWeek; // stores the start day of the week in the lowest 7 bits
	TUint16 iFiller2;
	};


class TAgnMonthlyRpt : public TAgnRpt
//
// Abstract class providing common functionality shared by monthly repeats
//
	{ 	
public:
	IMPORT_C virtual TUint InstanceCount() const;
	IMPORT_C virtual TTime FindRptEndDate(TUint aCount) const;
protected:
	inline TAgnMonthlyRpt(){};
	inline TAgnMonthlyRpt(const TAgnRpt& aRpt);
	virtual TInt NumInstancesPerMonth() const = 0;
	TBool DateFallsInAlignedMonth(const TDateTime& aDate) const;
	void NudgeNextMonth(TInt& aDate) const;
	void NudgePreviousMonth(TAgnDate& aDate) const;
	virtual TAgnDate NudgeNextInstance(TAgnDate aDay,TBool aIgnoreMonthAlignment=EFalse) const;
	virtual TAgnDate NudgePreviousInstance(TAgnDate aDay) const;
	virtual TTimeIntervalDays NumDaysToNextInstanceFrom(TAgnDate aDate) const = 0;
	};


class TAgnMonthlyByDaysRpt : public TAgnMonthlyRpt
//
// Stores the days in a month that a repeat entry can repeat on. i.e.  Tuesday of the first week
// and Sunday of the last week.
// i.e. repeat every x months on Tuesday of the 1st week of the month and Wednesday of the 3rd week
// 
	{
public:
	IMPORT_C TAgnMonthlyByDaysRpt();
	IMPORT_C TAgnMonthlyByDaysRpt(const TAgnRpt& aRpt);
	IMPORT_C TAgnMonthlyByDaysRpt(const TAgnMonthlyByDaysRpt& aRpt);
	IMPORT_C void ClearAllDays();
	IMPORT_C void ClearWeek(TWeekInMonth aWeek);
	IMPORT_C void SetDay(TDay aDay,TWeekInMonth aWeek);
	IMPORT_C void UnsetDay(TDay aDay,TWeekInMonth aWeek);
	IMPORT_C TBool IsDaySet(TDay aDay,TWeekInMonth aWeek) const;
	IMPORT_C TBool operator==(const TAgnMonthlyByDaysRpt& aRpt) const;
	IMPORT_C TInt NumDaysSet() const;
	virtual TInt Invariant() const;	  // self testing
	IMPORT_C virtual void InternalizeL(RReadStream& aStream);
	IMPORT_C virtual void ExternalizeL(RWriteStream& aStream) const;
protected:
	virtual TInt NumInstancesPerMonth() const;
	virtual TBool IsAligned(TAgnDate aDate,TBool aIgnoreMonthAlignment=EFalse) const;
	virtual TTimeIntervalDays NumDaysToNextInstanceFrom(TAgnDate aDate) const;
private:
	TUint8 iMonthlyRptDays[8]; // stores the days of the week for 5 weeks - EFirst to ELast. (8 is for alignmnet)
	};



class TAgnMonthlyByDatesRpt : public TAgnMonthlyRpt
//
// Stores the dates in a month that an entry can repeat on i.e the 2nd and the 31st
// i.e. repeat every x months on the 3rd, 5th and 9th
//
	{
public:
	IMPORT_C TAgnMonthlyByDatesRpt();
	IMPORT_C TAgnMonthlyByDatesRpt(const TAgnRpt& aRpt);
	IMPORT_C TAgnMonthlyByDatesRpt(const TAgnMonthlyByDatesRpt& aRpt);
	inline void ClearAllDates();
	IMPORT_C void SetDate(TUint aDateInMonth);
	IMPORT_C void UnsetDate(TUint aDateInMonth);
	IMPORT_C TBool IsDateSet(TUint aDateInMonth) const;
	IMPORT_C TInt NumDatesSet() const;
	IMPORT_C TBool operator==(const TAgnMonthlyByDatesRpt& aRpt) const;
	IMPORT_C virtual void InternalizeL(RReadStream& aStream);
	IMPORT_C virtual void ExternalizeL(RWriteStream& aStream) const;
	virtual TInt Invariant() const; // self testing
protected:
	virtual TInt NumInstancesPerMonth() const;
	virtual TBool IsAligned(TAgnDate aDate,TBool aIgnoreMonthAlignment=EFalse) const;
	virtual TTimeIntervalDays NumDaysToNextInstanceFrom(TAgnDate aDate) const;
private:
	TUint32 iMonthlyRptDates;// stores the dates of a month i.e. bit 2 = the 2nd 
	};


class TAgnYearlyByDateRpt : public TAgnRpt
//
// i.e. repeat every year on the 3rd of October
//
	{
public:
	IMPORT_C TAgnYearlyByDateRpt();
	IMPORT_C TAgnYearlyByDateRpt(const TAgnRpt& aRpt);
	IMPORT_C TAgnYearlyByDateRpt(const TAgnYearlyByDateRpt& aRpt);
	IMPORT_C virtual TUint InstanceCount() const;
	IMPORT_C virtual TTime FindRptEndDate(TUint aCount) const;
protected:
	virtual TBool IsAligned(TAgnDate aDate,TBool aDummy=EFalse) const;
	virtual TAgnDate NudgeNextInstance(TAgnDate aDay,TBool aDummy=EFalse) const;
	virtual TAgnDate NudgePreviousInstance(TAgnDate aDay) const;
	};

class TAgnYearlyByDayRpt : public TAgnRpt
//
// i.e. repeat every year on wednesday of the third week of november
//
	{
public:
	IMPORT_C TAgnYearlyByDayRpt();
	IMPORT_C TAgnYearlyByDayRpt(const TAgnRpt& aRpt);
	IMPORT_C TAgnYearlyByDayRpt(const TAgnYearlyByDayRpt& aRpt);
	IMPORT_C virtual TUint InstanceCount() const;
	IMPORT_C virtual TTime FindRptEndDate(TUint aCount) const;
	IMPORT_C void SetStartDay(TDay aDay,TWeekInMonth aWeek,TMonth aMonth,TInt aYear);	
	IMPORT_C void GetStartDay(TDay& aDay,TWeekInMonth& aWeek,TMonth& aMonth,TInt& aYear) const;
	IMPORT_C virtual void InternalizeL(RReadStream& aStream);
	IMPORT_C virtual void ExternalizeL(RWriteStream& aStream) const;
	virtual TInt Invariant() const; 
protected:
	virtual TBool IsAligned(TAgnDate aDate,TBool aDummy=EFalse) const;
	virtual TAgnDate NudgeNextInstance(TAgnDate aDay,TBool aDummy=EFalse) const;
	virtual TAgnDate NudgePreviousInstance(TAgnDate aDay) const;
	TInt GetFirstDayInWeek(TWeekInMonth aWeekInMonth,TMonth aMonth,TInt aYear) const;
	void SetDateAccordingToDay(TTime& aDate,TDay aDay,TWeekInMonth aWeekInMonth) const;
private:
	TWeekInMonth	iWeekInMonth;
	TDay			iDay;
	};

class CAgnRptDef : public CBase
//
// Contains the repeat details including exceptions
//
	{		
public:
	enum TType 
		{
		EDaily=1,		// i,e. repeat every x days 
		EWeekly,		// i.e.	repeat every x weeks on days Monday and Thursday with Tuesday as the first day of the week
		EMonthlyByDates,// i.e. repeat every x months on the 3rd, 5th and 9th
		EMonthlyByDays,	// i.e. repeat every x months on Tuesday of the 1st week of the month and Wednesday of the 3rd week
		EYearlyByDate,	// i.e. repeat every year on the 3rd of October
		EYearlyByDay	// i.e. repeat every year on Wednesday of the 4th week of November
		};

	IMPORT_C static CAgnRptDef* NewL();
	IMPORT_C virtual ~CAgnRptDef();

	inline TType Type() const;
	IMPORT_C TTime StartDate() const;
	IMPORT_C TAgnDate StartDateAsAgnDate() const;
	IMPORT_C TTime EndDate() const;
	IMPORT_C TAgnDate EndDateAsAgnDate() const;
	IMPORT_C void SetStartDate(const TTime& aStartDate); 
	IMPORT_C void SetStartDate(TAgnDate aStartDate);  
	IMPORT_C void SetEndDate(const TTime& aEndDate);
	IMPORT_C void SetEndDate(TAgnDate aEndDate);
	IMPORT_C TInt Interval() const;
	IMPORT_C TBool DisplayNextOnly() const;
	IMPORT_C void SetInterval(TUint aInterval);
	IMPORT_C void SetDisplayNextOnly(TBool aDisplayNextOnly);
	IMPORT_C TBool RepeatForever() const;
	IMPORT_C void SetRepeatForever(TBool aRepeatForever);
	inline const TAgnRpt* RptDef() const;
 
 	IMPORT_C TAgnDailyRpt Daily() const;
	IMPORT_C TAgnWeeklyRpt Weekly() const;
	IMPORT_C TAgnMonthlyByDaysRpt MonthlyByDays() const;
	IMPORT_C TAgnMonthlyByDatesRpt MonthlyByDates() const;
	IMPORT_C TAgnYearlyByDateRpt YearlyByDate() const;
	IMPORT_C TAgnYearlyByDayRpt YearlyByDay() const;

	IMPORT_C void SetDaily(const TAgnDailyRpt& aRpt);
	IMPORT_C void SetWeekly(const TAgnWeeklyRpt& aRpt);
	IMPORT_C void SetMonthlyByDates(const TAgnMonthlyByDatesRpt& aRpt);
	IMPORT_C void SetMonthlyByDays(const TAgnMonthlyByDaysRpt& aRpt);
	IMPORT_C void SetYearlyByDate(const TAgnYearlyByDateRpt& aRpt);
	IMPORT_C void SetYearlyByDay(const TAgnYearlyByDayRpt& aRpt);

	IMPORT_C TTime FindRptEndDate(TUint aCount) const;
	IMPORT_C TUint InstanceCount() const;

	IMPORT_C TBool NudgeNextInstance(TAgnDate aDay,TAgnDate& aNext) const;// not intended to be called by a view 	
	IMPORT_C TBool NudgePreviousInstance(TAgnDate aDay,TAgnDate& aPrev) const;// not intended to be called by a view 	  
	IMPORT_C TBool NudgeNextUnexceptedInstance(TAgnDate aDay,TAgnDate& aNext) const;// not intended to be called by a view 	
	IMPORT_C TBool NudgePreviousUnexceptedInstance(TAgnDate aDay,TAgnDate& aPrev) const;// not intended to be called by a view 
	IMPORT_C TBool IsAnUnexceptedInstance(TAgnDate aDate) const;// not intended to be called by a view 
	IMPORT_C TBool IsAnInstance(TAgnDate aDate) const;// not intended to be called by a view 

	IMPORT_C void AddExceptionL(const TAgnException& aException); // not to be called by a view 
	IMPORT_C TBool RemoveException(const TAgnException& aException); // not to be called by a view 
	IMPORT_C TBool FindException(const TAgnException& aException) const; // not to be called by a view 
	IMPORT_C void RemoveAllExceptions(); // not to be called by a view 
	inline const CAgnExceptionList* Exceptions() const;	// not to be called by a view 

	IMPORT_C void CopyL(const CAgnRptDef* aRpt);
	IMPORT_C TBool operator==(const CAgnRptDef& aRpt) const;

	virtual TInt Invariant() const;	// self testing

	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
protected:
	void CreateExceptionListL(const CAgnExceptionList* aExceptions=NULL);
	void CreateRptObject(TAgnRpt* aRpt=NULL);
	inline CAgnRptDef();
private:	
	TType 		iType; 
	TUint8 		iBuf[sizeof(TAgnMonthlyByDaysRpt)]; // used instead of a union 
	TAgnRpt* 	iRpt; // iRpt is allocated within iBuf using the new-in-place operator
	CAgnExceptionList* iExceptions;
	__DECLARE_TEST;
	};

#include "agmrptd.inl"

#endif
