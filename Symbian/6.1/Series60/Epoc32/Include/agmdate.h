// AGMDATE.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __AGMDATE_H__
#define __AGMDATE_H__

#include <e32std.h>
#include <s32stor.h>
#include "agmutil.h"
#include "agmpanic.h"


typedef TUint16 TAgnDate; 
typedef TUint16 TAgnTime;
typedef	TUint32 TAgnDurationMinutes;
typedef TUint16 TAgnDurationDays;

class TAgnDateTime
	{
public:
	inline TAgnDateTime(); // default constructor sets iDate to AgnDateTime::NullDate()
	inline TAgnDateTime(TAgnDate aDate);
	IMPORT_C TAgnDateTime(const TTime& aDateTime);
	inline operator TTime() const;
	inline operator TAgnDate() const;
	inline TAgnDateTime(TAgnDate aDate,TAgnTime aTime);
	inline TAgnDate Date() const;
	inline TAgnTime Time() const;
	inline void SetDate(TAgnDate aDate);
	inline void SetTime(TAgnTime aTime);
	TBool operator==(TAgnDateTime aDateTime) const;
	TBool operator<(TAgnDateTime aDateTime) const;
	TBool operator>(TAgnDateTime aDateTime) const;
	TBool operator<=(TAgnDateTime aDateTime) const;
	TBool operator>=(TAgnDateTime aDateTime) const;

	void InternalizeL(RReadStream& aStream);
	void ExternalizeL(RWriteStream& aStream) const;
private:
	TAgnDate iDate;
	TAgnTime iTime;
	};


class AgnDateTime
//
// Utility class for converting between a TTime and a TAgnDate and a TAgnTime and also
// between a TTimeIntervalDays and a TAgnDate
//	
	{
public:
	IMPORT_C static TAgnDate 			TTimeToAgnDate(const TTime&  aDate);
	IMPORT_C static TTime 				AgnDateToTTime(TAgnDate aDate);
	IMPORT_C static TAgnDateTime 		TTimeToAgnDateTime(const TTime& aDateTime);
	IMPORT_C static TTime 				AgnDateTimeToTTime(TAgnDateTime aDateTime);
	IMPORT_C static TAgnDate 			TTimeIntervalDaysFrom0ADToAgnDate(TTimeIntervalDays);
	IMPORT_C static TTimeIntervalDays 	AgnDateToTTimeIntervalDaysFrom0AD(TAgnDate aDate);
	IMPORT_C static TDateTime			AgnDateToTDateTime(TAgnDate aDate);
	IMPORT_C static TDay				DayNoInWeek(TAgnDate aDate);
	IMPORT_C static void				AddTo(TDateTime& aDate, TTimeIntervalYears aYears);
	IMPORT_C static void				AddTo(TDateTime& aDate, TTimeIntervalMonths aMonths);
	IMPORT_C static TTimeIntervalMonths	MonthsFrom(const TDateTime& aStartDate, const TDateTime& aEndDate);
	IMPORT_C static TTimeIntervalYears	YearsFrom(const TDateTime& aStartDate, const TDateTime& aEndDate);
	IMPORT_C static TInt	 			TDateTimeToAgnDate(const TDateTime&  aDate);
	IMPORT_C static TBool				IsLessThan(const TDateTime& aDateLeft, const TDateTime& aDateRight);
	// model limits
	IMPORT_C static TTime MinDateAsTTime(); // start of range for agenda entries
	IMPORT_C static TTime MaxDateAsTTime(); // end of range for agenda entries

	inline static TAgnDate	MinDate();  	// the number of days since KAgnFirstValidDateAsTTime
	inline static TAgnDate	MaxDate();
	inline static TAgnDate	NullDate(); // largest figure that can be stored in a TUint16
	inline static TAgnTime	NullTime();
	inline static TUint		MaxTime();

	inline static TTimeIntervalDays MinDateAsTTimeIntervalDaysFrom0AD();
	inline static TTimeIntervalDays MaxDateAsTTimeIntervalDaysFrom0AD();
	static TBool IsValidAgendaTTime(const TTime& aDate);
private:
	};

#include "agmdate.inl"

#endif
