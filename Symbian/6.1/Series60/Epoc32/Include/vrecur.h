// VRECUR.H
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//
 
#if !defined(__VRECUR_H__)
#define __VRECUR_H_

#if !defined(__VERSIT_H__)
#include "versit.h"
#endif

//
// CWeekDayArray
//

/**
 * An array of the days in the week on which a weekly repeat event
 * occurs.
 *
 * Days are specified using the <code>TDay</code> enumeration. An object
 * of this class is owned by the <code>CVersitRecurrenceWeekly</code>
 * class.
 *
 * @since 5.0
 * @lib " versit.lib "
 */
class CWeekDayArray : public CBase
	{
public:
	IMPORT_C CWeekDayArray();
	IMPORT_C ~CWeekDayArray();
	IMPORT_C void ExternalizeL(RWriteStream& aStream);
public:	
	CArrayFix<TDay>* iArray;
	};

//
// CVersitRecurrence
//
/**
 * Abstract base class for all versit recurrence classes.
 *
 * A pointer to a derived class object is owned by the
 * <code>CParserPropertyValueRecurrence</code> class and is used to
 * contain the recurrence details for a repeating event.
 *
 * @since 5.0
 * @lib " versit.lib "
 */
class CVersitRecurrence : public CBase
	{
public:
	IMPORT_C CVersitRecurrence(TInt aInterval,TInt aDuration,TVersitDateTime* aEndDate);
	IMPORT_C ~CVersitRecurrence();
	virtual void ExternalizeOccurrenceListsL(RWriteStream& aStream) const=0;
	/** Repeat type */
	enum TType
		{
		EDaily=1,			/** Daily repeat.*/
		EWeekly,			/** Weekly repeat.*/
		EMonthlyByPos,		/** Monthly repeat, by relative position within the month.*/
		EMonthlyByDay,		/** Monthly repeat, by day number within the month.*/
		EYearlyByMonth,		/** Yearly repeat, by specific months within the year.*/
		EYearlyByDay 		/** Yearly repeat, by specific days within the year.*/
		};
public:
	TType iRepeatType;
	TInt iInterval;
	TInt iDuration; //0 indicates forever
	TVersitDateTime* iEndDate;
	};

//
// CVersitRecurrenceDaily
//
/**
 * Recurrence details specific to a daily repeat event in a vCalendar.
 * @since 5.0
 * @lib " versit.lib "
 */
class CVersitRecurrenceDaily : public CVersitRecurrence
	{
public:
	IMPORT_C CVersitRecurrenceDaily(TInt aInterval,TInt aDuration,TVersitDateTime* aEndDate);
public: //from CVersitRecurrence
	IMPORT_C void ExternalizeOccurrenceListsL(RWriteStream& /*aStream*/) const;
	};

//
//	CVersitRecurrenceWeekly
//
/**
 * Recurrence details specific to a weekly repeat event in a vCalendar.
 * @since 5.0
 * @lib " versit.lib "
 */
class CVersitRecurrenceWeekly : public CVersitRecurrence
	{
public:
	IMPORT_C CVersitRecurrenceWeekly(TInt aInterval,TInt aDuration,TVersitDateTime* aEndDate,CWeekDayArray* aArrayOfWeekDayOccurrences);
	IMPORT_C ~CVersitRecurrenceWeekly();
public: //from CVersitRecurrence
	IMPORT_C void ExternalizeOccurrenceListsL(RWriteStream& aStream) const;
public:
	CWeekDayArray* iArrayOfWeekDayOccurrences;		//Mon-Sun
	};

//
// CVersitRecurrenceMonthlyByPos
//
/**
 * Recurrence details specific to a monthly repeat event in a vCalendar.
 *
 * The days on which the repeat occurs are identified by their occurrence
 * within the month (e.g. the second Monday, the last Friday etc.).
 *
 * @since 5.0
 * @lib " versit.lib "
 */
class CVersitRecurrenceMonthlyByPos : public CVersitRecurrence
	{
public:
	/**
	  * Indicates the days on which a monthly repeat event occurs.
	  *
	  * This class is nested within the
	  * <code>CVersitRecurrenceMonthlyByPos</code> class.Contains a week day
	  * array (<code>CWeekDayArray</code>), the numeric occurrence of the day
	  * within the month (between 1 and 5 inclusive) and whether the
	  * occurrence is calculated by counting from the start or the end of the
	  * month.
	  *
	  * @lib " versit.lib "
	  */
	class CMonthPosition : public CBase
		{
	public:
		IMPORT_C ~CMonthPosition();
	public:
		/** Flags that define whether the week number is from start or end of month.*/
		enum TSign 
				{
				EWeeksFromStartOfMonth, /** Indicates that the <code>iWeekNo</code> member specifies a number
											counting forwards from the start of the month.*/
				EWeeksFromEndOfMonth	/** Indicates that the <code>iWeekNo</code> member specifies a number
											counting backwards from the end of the month.*/
				};
	public:
		TSign iSign;
		TInt iWeekNo; //1-5
		CWeekDayArray* iArrayOfWeekDays;
		};
	IMPORT_C CVersitRecurrenceMonthlyByPos(TInt aInterval,TInt aDuration,TVersitDateTime* aEndDate,CArrayPtrFlat<CMonthPosition>* aMonthPositions);
	IMPORT_C ~CVersitRecurrenceMonthlyByPos();
public: //framework
	IMPORT_C void ExternalizeOccurrenceListsL(RWriteStream& aStream) const;
public:
	CArrayPtrFlat<CMonthPosition>* iMonthPositions;
	};

//
// CVersitRecurrenceMonthlyByDay
//
/**
 * Recurrence details specific to a monthly repeat event in a vCalendar.
 *
 * The days on which the repeat occurs are identified by their day
 * number, counting either from the start or the end of the month.
 *
 * @since 5.0
 * @lib " versit.lib "
 */
class CVersitRecurrenceMonthlyByDay : public CVersitRecurrence
	{
public:
	IMPORT_C CVersitRecurrenceMonthlyByDay(TInt aInterval,TInt aDuration,TVersitDateTime* aEndDate,	CArrayFix<TInt>* aArrayOfOccurrencesInDaysFromStartOfMonth
		,CArrayFix<TInt>* aArrayOfOccurrencesInDaysFromEndOfMonth,TBool aLastDay);
	IMPORT_C ~CVersitRecurrenceMonthlyByDay();
public: //framework
	IMPORT_C void ExternalizeOccurrenceListsL(RWriteStream& aStream) const;
public:
	CArrayFix<TInt>* iArrayOfOccurrencesInDaysFromStartOfMonth; //1-31
	CArrayFix<TInt>* iArrayOfOccurrencesInDaysFromEndOfMonth; //1-31
	TBool iLastDay;
	};

//
// CVersitRecurrenceYearlyByMonth
//
/**
 * Recurrence details for a yearly repeat event in a vCalendar.
 *
 * The months in which the repeat occurs are identified by an array of
 * <code>TMonth</code> values (between <code>EJanuary</code> and
 * <code>EDecember</code> inclusive).
 *
 * @since 5.0
 * @lib " versit.lib "
 */
class CVersitRecurrenceYearlyByMonth : public CVersitRecurrence
	{
public:
	IMPORT_C CVersitRecurrenceYearlyByMonth(TInt aInterval,TInt aDuration,TVersitDateTime* aEndDate,CArrayFix<TMonth>* aArrayOfMonthsInYearOccurrences);
	IMPORT_C ~CVersitRecurrenceYearlyByMonth();
public: //framework
	IMPORT_C void ExternalizeOccurrenceListsL(RWriteStream& aStream) const;
public:
	CArrayFix<TMonth>* iArrayOfMonthsInYearOccurrences; //Jan-Dec
	};

//
// CVersitRecurrenceYearlyByDay
//
/**
 * Recurrence details for a yearly repeat event in a vCalendar.
 *
 * The days on which the repeat occurs are identified by their day number
 * in the year (between 1 and 366 inclusive).
 *
 * @since 5.0
 * @lib " versit.lib "
 */
class CVersitRecurrenceYearlyByDay : public CVersitRecurrence
	{
public:
	IMPORT_C CVersitRecurrenceYearlyByDay(TInt aInterval,TInt aDuration,TVersitDateTime* aEndDate,CArrayFix<TInt>* aArrayOfDaysInYearOccurrences);
	IMPORT_C ~CVersitRecurrenceYearlyByDay();
public: //framework
	IMPORT_C void ExternalizeOccurrenceListsL(RWriteStream& aStream) const;
public:
	CArrayFix<TInt>* iArrayOfDaysInYearOccurrences; //1-366
	};

//
// CParserPropertyValueRecurrence
//
/**
 * A property value which contains the recurrence information for a
 * repeating vEvent or vTodo.
 *
 * The value is stored as a pointer to a <code>CVersitRecurrence</code>
 * object.To find out the property value type, use <code>Uid()</code>
 * defined in the base class <code>CParserPropertyValue</code>. A
 * recurrence rule property UID has the value
 * <code>KVCalPropertyRecurrenceUid</code>.The class defines an
 * <code>ExternalizeL()</code> function which has not been documented. It
 * is invoked by the parser's <code>ExternalizeL()</code> function.
 *
 * @since 5.0
 * @lib " versit.lib "
 */
class CParserPropertyValueRecurrence : public CParserTimePropertyValue
	{
public:
	IMPORT_C CParserPropertyValueRecurrence(CVersitRecurrence* aValue);
	IMPORT_C ~CParserPropertyValueRecurrence();
	inline CVersitRecurrence* Value() const;
public: // from CParserTimePropertyValue
	IMPORT_C void ConvertAllDateTimesToUTCL(const TTimeIntervalSeconds& aIncrement,const CVersitDaylight* aDaylight);
	IMPORT_C void ConvertAllUTCDateTimesToMachineLocalL(const TTimeIntervalSeconds& aIncrement);
public: // from CParserPropertyValue
	IMPORT_C void ExternalizeL(RWriteStream& aStream,const Versit::TEncodingAndCharset& /*aEncodingCharset*/,TInt /*aLengthOutput*/);
protected:
	CVersitRecurrence* iValue;
	};

//
// CRecurrenceParser
//
/**
 *
 * Base class used in the derivation of <code>CParserVCalEntity</code>.
 *
 * It has no user accessible functions.
 *
 * @since 5.0
 * @lib "versit.lib"
 */
class CRecurrenceParser : public CVersitParser
	{
public:
	IMPORT_C CRecurrenceParser(TBool aHasVersion);
	IMPORT_C CParserPropertyValue* MakePropertyValueRecurrenceL(TDes& aRecurringEntity);
private:	
	static void ResetAndDestroyArrayOfMonthPositions(TAny* aObject);	
	void GetFrequencyAndIntervalL(CVersitRecurrence::TType& aFrequency,TInt& aInterval, const TDesC& aRecurrenceType);
	CVersitRecurrence* GetFrequencyModifiersL(const CVersitRecurrence::TType& aRepeatType,TInt aInterval, const TDesC& aListDates);
	CWeekDayArray* GetListOfWeekDayOccurrencesL(const TDesC& aListDays);
private: // from CVersitParser
	IMPORT_C virtual void Reserved1();
	IMPORT_C virtual void Reserved2();
	};

#include "vrecur.inl"

#endif