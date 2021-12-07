// AGMBASIC.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __AGMBASIC_H__
#define __AGMBASIC_H__

#include "agmutil.h"
#include "agmrptd.h"
#include "agmdate.h"
#include "agmids.h"
#include "agmpanic.h"
#include "agmexcpt.h"

// ------------------------------------- Local clases ------------------------------------
class CAgnBasicEntry;
class TAgnBasicAppt;
class TAgnBasicTodo;
class TAgnBasicEvent;
class TAgnBasicAnniv;


class TAgnAlarmPreTime
	{
public:
	void SetAlarm(TTimeIntervalDays aDaysWarning,TTimeIntervalMinutes aTime,const TAgnDateTime& aAlarmOrigin);
	TAgnTime AlarmTime(const TAgnDateTime& aAlarmOrigin) const;
	TAgnDateTime AlarmInstanceDateTime(const TAgnDateTime& aAlarmOrigin) const;
	TTimeIntervalDays AlarmDaysWarning(const TAgnDateTime& aAlarmOrigin) const;
	inline TBool operator==(const TAgnAlarmPreTime& aOther) const;
	inline TBool operator!=(const TAgnAlarmPreTime& aOther) const;
	void InternalizeL(RReadStream& aStream);
	void ExternalizeL(RWriteStream& aStream) const;
private:
	TAgnDurationMinutes iAlarmPreTime;
	};


class CAgnBasicEntry : public CBase
//
// Contains the basic details for an entry
//
	{
public:
	friend class TAgnSortInstance;
	virtual ~CAgnBasicEntry();
 
//	enum TSynchronisationStatus {EOpen, EPrivate, ERestricted};

	inline TChar EntrySymbol() const;
	IMPORT_C void SetEntrySymbol(TChar aEntrySymbol);
	inline CAgnRptDef* RptDef();  
	inline const CAgnRptDef* RptDef() const;
	IMPORT_C void ClearRepeat();
	TBool operator==(const CAgnBasicEntry& aBasicEntry) const;
	void CopyBasicEntryL(const CAgnBasicEntry* aBasicEntry);

	// alarm date/time stuff
	IMPORT_C void SetAlarm(TTimeIntervalDays aDaysWarning,TTimeIntervalMinutes aTime); 
	IMPORT_C TTime AlarmInstanceDateTime() const;  
	IMPORT_C TTimeIntervalDays AlarmDaysWarning() const;
	IMPORT_C TTimeIntervalMinutes AlarmTime() const;

	// Synchronisation stuff
	IMPORT_C virtual void SetLastChangedDate();	

	// other attributes
	inline TBool IsCrossedOut() const;	
	inline TBool IsRepeating() const;  	  
	inline TBool HasExceptions() const;
	inline TBool IsStoredInline() const;
	IMPORT_C TBool HasAlarm() const;
	inline TBool DisplayInYearView() const;
	inline TBool HasEntrySymbol() const;
	inline TBool IsADayNote() const;
	inline TBool HasDefaultDisplayTime() const;
	inline TBool IsTentative() const;
	inline TBool IsSketch() const;
	inline TBool HasExtended() const;
	inline void ClearAllAttributes(); // not to be called by a view 
	IMPORT_C void SetIsCrossedOut(TBool aIsCrosedOut);// if a todo call CAgnTodo::CrossOut/UnCrossOut instead	
	IMPORT_C void SetIsRepeating(TBool aIsRepeating); // not to be called by a view 
	IMPORT_C void SetHasExceptions(TBool aHasExceptions); // not to be called by a view 
	void SetIsStoredInline(TBool aIsStoredInline);	// not to be called by a view
	IMPORT_C void SetHasAlarm(TBool aHasAlarm);	
	IMPORT_C void SetDisplayInYearView(TBool aDisplayInYearView);
	IMPORT_C void SetHasEntrySymbol(TBool aHasEntrySymbol);
	IMPORT_C void SetIsADayNote(TBool aIsADayNote);  // not to be called by a view
	IMPORT_C void SetHasDefaultDisplayTime(TBool aHasDefaultDisplayTime);
	IMPORT_C void SetIsTentative(TBool aIsTentative);
	IMPORT_C void SetIsSketch(TBool aIsSketch);
	IMPORT_C void SetHasExtended(TBool aHasExtended);

	IMPORT_C void SetRptStartDate(TAgnDate aRptStartDate); // not to be called by a view 
	IMPORT_C void SetRptEndDate(TAgnDate aRptEndDate);	// not to be called by a view 
	IMPORT_C void AddExceptionL(const TAgnException& aException); // not to be called by a view 
	IMPORT_C TBool RemoveException(const TAgnException& aException); // not to be called by a view 
	IMPORT_C TBool FindException(TAgnException& aException) const; // not to be called by a view 
	IMPORT_C const CAgnExceptionList* Exceptions() const;  // not to be called by a view 
	IMPORT_C void RemoveAllExceptions(); // not to be called by a view 
	IMPORT_C void PruneExceptions(); // not to be called by a view
protected:
	inline CAgnBasicEntry();
	virtual TAgnDateTime AlarmOrigin() const;
	inline TAgnAlarmPreTime AlarmPreTime() const;
private:
	void CreateExceptionListL(const CAgnExceptionList* aExceptions=NULL);
protected:
	enum 
		{
		EIsCrossedOut			=EBit1,
		EIsRepeating			=EBit2,
		EHasExceptions			=EBit3,
		EIsStoredInline			=EBit4,
		EHasAlarm				=EBit5,
		EDisplayInYearView		=EBit6,	// needed ?
		EHasChanged				=EBit7,
		EHasEntrySymbol			=EBit8,
		EIsADayNote				=EBit9, // In here and not in TAgnBasicAppt to save space
		EHasDefaultDisplayTime	=EBit10,
		EIsTentative			=EBit11,
		EIsSketch				=EBit12,
		EHasExtended			=EBit13	// Does the entry have entended attributes
		};

	CAgnRptDef* 		iRptDef; // contains the repeat definition plus exceptions
	TAgnAlarmPreTime	iAlarmPreTime;
	TUint16				iAttributes;
	TUint16				iEntrySymbol; 
	};



class TAgnBasicAppt
//
// The basic appointment entry details
//
	{
public:
	inline TAgnDateTime StartDateTime() const;
	TAgnDateTime EndDateTime() const;
	void SetStartAndEndDateTime(TAgnDateTime aStartDateTime,TAgnDateTime aEndDateTime);

	TBool operator==(const TAgnBasicAppt& aBasicAppt) const;

	void InternalizeL(RReadStream& aStream);
	void ExternalizeL(RWriteStream& aStream) const;
private:
	TAgnDateTime	iStartDateTime; 	
	TAgnDateTime	iEndDateTime;
	};


class TAgnBasicEvent
//
// The basic event entry details
//
	{
public:
	inline TAgnDate StartDate() const;
	inline TAgnDate EndDate() const;
	void SetStartAndEndDate(TAgnDate aStartDate,TAgnDate aEndDate);
	inline TAgnTime DisplayTime() const;
	inline void SetDisplayTime(TAgnTime aDisplayTime);
	TBool operator==(const TAgnBasicEvent& aBasicEvent) const;

	void InternalizeL(RReadStream& aStream);
	void ExternalizeL(RWriteStream& aStream) const;
private:
	TAgnDate 	iStartDate;
	TAgnDate 	iEndDate;
	TAgnTime	iDisplayTime; // the time an entry is displayed in dated
								  // views in minutes from midnight
	TUint16		iFiller;
	};


class TAgnBasicTodo
//
// The basic todo entry details
//
	{
public:
	enum TStreamCrossedOutDate {EStreamCrossedOutDate,EDontStreamCrossedOutDate};

	inline TAgnDate DueDate() const;
	inline void SetDueDate(TAgnDate aDueDate);
	inline TAgnDate CrossedOutDate() const;
	void SetCrossedOutDate(TAgnDate aCrossedOutDate);
	inline TAgnTime DisplayTime() const;
	inline void SetDisplayTime(TAgnTime aDisplayTime);
	inline TAgnTodoListId TodoListId() const;
	inline void SetTodoListId(TAgnTodoListId aTodoListId);
	inline TAgnDurationDays Duration() const;
	inline void SetDuration(TAgnDurationDays aDuration);
	inline TUint Priority() const;
	inline void SetPriority(TUint aPriority);
	inline void SetAlarmFromDueDate();
	inline void SetAlarmFromStartDate();
	inline TBool IsAlarmSetFromDueDate() const;
	inline TBool IsAlarmSetFromStartDate() const;
	TBool IsDated() const;
	TBool operator==(const TAgnBasicTodo& aBasicTodo) const;

	void InternalizeL(RReadStream& aStream,
					TStreamCrossedOutDate aRestoreCrossedOutDate=EDontStreamCrossedOutDate);
	void ExternalizeL(RWriteStream& aStream,
					TStreamCrossedOutDate aStoreCrossedOutDate=EDontStreamCrossedOutDate) const;
private:
	enum TAlarmFrom {EDueDate=0,EStartDate};

	TAgnTodoListId 	iTodoListId; // The id of the todo list to which the todo belongs
	TAgnDurationDays iDuration;	
	TAgnDate 		iDueDate;
	TAgnDate		iCrossedOutDate;
	TAgnTime 		iDisplayTime;
	TUint8 			iPriority; 
	TInt8			iAlarmFrom; // the alarm has been set relative to the due date or start date
	TInt16			iFiller;
	};

#include "agmbasic.inl"

#endif
