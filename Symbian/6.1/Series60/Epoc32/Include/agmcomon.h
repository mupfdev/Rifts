// AGMCOMON.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __AGMCOMON_H__
#define __AGMCOMON_H__

#include <t32alm.h> // for KMaxAlarmSoundName
#include "agmids.h"
#include "agmentry.h"
#include "agmxsort.h"

class CAgnModel;
class CAgnDeletedIndex;
class CAgnUniqueIdIndex;

LOCAL_D const TUint KAgnMaxTodoListNameLength=50; // max length for the name of a todo list
LOCAL_D const TUint KAgnMaxSearchStringLength=32; // max length of string when searching

// Index ids
#define KAgnEventIndexNum 0
#define KAgnApptNonRpt1DayIndexNum 1
#define KAgnApptNonRptNDayIndexNum 2
#define KAgnApptRptIndexNum 3
#define KAgnTodoNonRptIndexNum 4
#define KAgnAnnivRptIndexNum 5
#define KAgnTodoRptIndexNum 6
#define KAgnEventRptIndexNum 7


class TAgnLiteEntry
	{
public:
	inline TAgnLiteEntry(CAgnSortEntry* aSortEntry=NULL);

	inline CAgnEntry::TType Type() const;
	inline TAgnEntryId Id() const;

	inline TChar EntrySymbol() const;
	inline TTimeIntervalMinutes DisplayTime() const;
	inline const CAgnRptDef* RptDef() const;
	inline TTimeIntervalDays AlarmDaysWarning() const;
	inline TTimeIntervalMinutes AlarmTime() const;
	inline TBool IsCrossedOut() const;	
	inline TBool IsRepeating() const;  	
	inline TBool HasExceptions() const;
	inline TBool HasAlarm() const;
	inline TBool IsStoredInline() const;
	inline TBool RichTextStoreIsOpen() const;
	inline TBool DisplayInYearView() const;
	inline TBool HasEntrySymbol() const;
	inline TBool IsADayNote() const;
	inline TBool IsTentative() const;
	inline TBool HasDefaultDisplayTime() const;
	IMPORT_C TBool IsNull() const;

	IMPORT_C TBool IsDated() const;
	IMPORT_C TTime StartDate() const; // includes time portion for appts/day notes
	IMPORT_C TTime EndDate() const;	  // due date for todos, includes time for appts/day notes
	IMPORT_C TTimeIntervalDays Duration() const;
	
	// todo specific sutff:
	IMPORT_C TAgnTodoListId TodoListId() const;
	IMPORT_C TBool IsAlarmSetFromDueDate() const;
	IMPORT_C TBool IsAlarmSetFromStartDate() const;
	IMPORT_C TUint Priority() const;
	IMPORT_C TTime CrossedOutDate() const;

	inline const CAgnSortEntry* SortEntry() const;
private:
	CAgnSortEntry* iEntry;
	};		



class TAgnAlarmDefaults
	{
public:
	IMPORT_C TAgnAlarmDefaults();
	inline  void SetHasAlarm(TBool aHasAlarm);
	IMPORT_C void SetAlarmDateTime(TTimeIntervalDays aDaysWarning,TTimeIntervalMinutes aTime);
	inline void SetAlarmSoundName(const TDesC& aAlarmSoundName);
	inline TBool HasAlarm() const;
	inline TTimeIntervalDays AlarmDaysWarning() const;
	inline TTimeIntervalMinutes AlarmTime() const;
	inline TPtrC AlarmSoundName() const;
	IMPORT_C TBool operator==(const TAgnAlarmDefaults& aOther) const;

	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
private:
	TBool						iHasAlarm;
	TTimeIntervalDays			iDaysWarning;
	TTimeIntervalMinutes		iTimeOfDay;
	TBuf<KMaxAlarmSoundName>	iSoundName;
	};


class AgnModel
	{
public:
	enum TSynchronisationStatus {EOpen,EPrivate,ERestricted};
	IMPORT_C static void CastEntry(CAgnEntry* aEntry);
	IMPORT_C static CAgnEntry* CreateEntryL(CAgnEntry::TType aEntryType,const CParaFormatLayer* aParaFormatLayer,const CCharFormatLayer* aCharFormatLayer,CAgnEntry::TCreateHow aCreateHow = CAgnEntry::ECreateRichText);
	IMPORT_C static CAgnEntry* CreateEntryLC(CAgnEntry::TType aEntryType,const CParaFormatLayer* aParaFormatLayer,const CCharFormatLayer* aCharFormatLayer,CAgnEntry::TCreateHow aCreateHow = CAgnEntry::ECreateRichText);
	IMPORT_C static TAgnInstanceId CurrentInstanceIdL(CAgnModel* aModel,const CAgnEntry* aEntry,TTime& aDisplayDate,const TTime& aTodaysDate);
	inline static TBool IsValidDate(const TTime& aDate);
	inline static TBool IsValidDate(TAgnDate aDate);
	inline static TBool IsValidTime(TTimeIntervalMinutes aTime);
	inline static TBool IsValidTime(TAgnTime aTime);
	inline static TBool IsValidAlarmWarning(TTimeIntervalDays aDays);
	inline static TAgnId NullId();
	inline static TAgnTodoListId NullTodoListId();
	inline static TTime MinValidDate();
	inline static TTime MaxValidDate();
	inline static TUint MaxTodoListNameLength();
	inline static TUint MaxSearchStringLength();
	};
	
// "smart" lite entry class that provides access to the last changed date for entries
//  and provides information about deleted entries (which aren't in the index)
class TAgnSmartLiteEntry
	{
public:
	TAgnSmartLiteEntry(const TAgnUniqueId aUid, CAgnSortEntry* aSortEntry=NULL, CAgnUniqueIdIndex* aUniqueIdIndex=NULL, 
									CAgnDeletedIndex* aDeletedIndex=NULL);

	IMPORT_C CAgnEntry::TType Type() const;
	IMPORT_C TAgnEntryId Id() const;
	IMPORT_C TChar EntrySymbol() const;
	IMPORT_C TTimeIntervalMinutes DisplayTime() const;
	IMPORT_C const CAgnRptDef* RptDef() const;
	IMPORT_C TTimeIntervalDays AlarmDaysWarning() const;
	IMPORT_C TTimeIntervalMinutes AlarmTime() const;
	IMPORT_C TBool IsCrossedOut() const;	
	IMPORT_C TBool IsRepeating() const;  	
	IMPORT_C TBool HasExceptions() const;
	IMPORT_C TBool HasAlarm() const;
	IMPORT_C TBool DisplayInYearView() const;
	IMPORT_C TBool HasEntrySymbol() const;
	IMPORT_C TBool IsADayNote() const;
	IMPORT_C TBool IsTentative() const;
	IMPORT_C TBool HasDefaultDisplayTime() const;
	IMPORT_C TBool IsNull() const;
	IMPORT_C TBool IsDeleted() const;
	IMPORT_C TBool IsDated() const;
	IMPORT_C TTime StartDate() const; // includes time portion for appts/day notes
	IMPORT_C TTime EndDate() const;	  // due date for todos, includes time for appts/day notes
	IMPORT_C TTimeIntervalDays Duration() const;
	
	// todo specific stuff:
	IMPORT_C TAgnTodoListId TodoListId() const;
	IMPORT_C TBool IsAlarmSetFromDueDate() const;
	IMPORT_C TBool IsAlarmSetFromStartDate() const;
	IMPORT_C TUint Priority() const;
	IMPORT_C TTime CrossedOutDate() const;

	IMPORT_C const CAgnSortEntry* SortEntry() const;
	IMPORT_C TTime LastChangedDate() const;
private:
	CAgnSortEntry* iEntry;
	CAgnUniqueIdIndex* iUniqueIdIndex;
	CAgnDeletedIndex* iDeletedIndex;
	TAgnUniqueId iUid;
	TBool iHasBeenDeleted;
	};	

#include "agmcomon.inl"

#endif
