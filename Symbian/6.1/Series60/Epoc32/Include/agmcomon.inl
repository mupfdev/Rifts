// AGMCOMON.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//


// --------------------------------------------------------------------
// -------------------------- TAgnLiteEntry ---------------------------
// --------------------------------------------------------------------
inline TAgnLiteEntry::TAgnLiteEntry(CAgnSortEntry* aSortEntry)
	: iEntry(aSortEntry)
	{}

inline CAgnEntry::TType TAgnLiteEntry::Type() const
	{
	__ASSERT_DEBUG(iEntry,Panic(_L("Null entry")));
	return (iEntry->Type());
	}

inline TAgnEntryId TAgnLiteEntry::Id() const
	{
	__ASSERT_DEBUG(iEntry,Panic(_L("Null entry")));
	return (iEntry->Id());
	}

inline TChar TAgnLiteEntry::EntrySymbol() const
	{
	__ASSERT_DEBUG(iEntry,Panic(_L("Null entry")));
	__ASSERT_DEBUG(HasEntrySymbol(),Panic(_L("Doesn't have an entry symbol")));
	return (iEntry->EntrySymbol());
	}


inline TTimeIntervalMinutes TAgnLiteEntry::DisplayTime() const
	{
	__ASSERT_DEBUG(iEntry,Panic(_L("Null entry")));
	return (iEntry->DisplayTime());
	}

inline const CAgnRptDef* TAgnLiteEntry::RptDef() const
	{
	__ASSERT_DEBUG(iEntry,Panic(_L("Null entry")));
	__ASSERT_DEBUG(IsRepeating(),Panic(_L("Isn't repeating")));
	return (iEntry->RptDef());
	}

inline TTimeIntervalDays TAgnLiteEntry::AlarmDaysWarning() const
	{
	__ASSERT_DEBUG(iEntry,Panic(_L("Null entry")));
	__ASSERT_DEBUG(HasAlarm(),Panic(_L("Isn't alarmed")));
	return (iEntry->AlarmDaysWarning());
	}

inline TTimeIntervalMinutes TAgnLiteEntry::AlarmTime() const
	{
	__ASSERT_DEBUG(iEntry,Panic(_L("Null entry")));
	__ASSERT_DEBUG(HasAlarm(),Panic(_L("Isn't alarmed")));
	return (iEntry->AlarmTime());
	}

inline TBool TAgnLiteEntry::IsCrossedOut() const
	{
	__ASSERT_DEBUG(iEntry,Panic(_L("Null entry")));
	return (iEntry->IsCrossedOut());
	}

inline TBool TAgnLiteEntry::IsRepeating() const
	{
	__ASSERT_DEBUG(iEntry,Panic(_L("Null entry")));
	return (iEntry->IsRepeating());
	}

inline TBool TAgnLiteEntry::HasExceptions() const
	{
	__ASSERT_DEBUG(iEntry,Panic(_L("Null entry")));
	return (iEntry->HasExceptions());
	}

inline TBool TAgnLiteEntry::HasAlarm() const
	{
	__ASSERT_DEBUG(iEntry,Panic(_L("Null entry")));
	return (iEntry->HasAlarm());
	}

inline TBool TAgnLiteEntry::IsStoredInline() const
	{
	__ASSERT_DEBUG(iEntry,Panic(_L("Null entry")));
	return (iEntry->IsStoredInline());
	}

//inline TBool TAgnLiteEntry::RichTextStoreIsOpen() const
//	{
//	__ASSERT_DEBUG(iEntry,Panic(_L("Null entry")));
//	return (iEntry->RichTextStoreIsOpen());
//	}

inline TBool TAgnLiteEntry::DisplayInYearView() const
	{
	__ASSERT_DEBUG(iEntry,Panic(_L("Null entry")));
	return (iEntry->DisplayInYearView());
	}

inline TBool TAgnLiteEntry::HasEntrySymbol() const
	{
	__ASSERT_DEBUG(iEntry,Panic(_L("Null entry")));
	return (iEntry->HasEntrySymbol());
	}

inline TBool TAgnLiteEntry::IsADayNote() const
	{
	__ASSERT_DEBUG(iEntry,Panic(_L("Null entry")));
	return (iEntry->IsADayNote());
	}

inline TBool TAgnLiteEntry::IsTentative() const
	{
	__ASSERT_DEBUG(iEntry,Panic(_L("Null entry")));
	return (iEntry->IsTentative());
	}

inline TBool TAgnLiteEntry::HasDefaultDisplayTime() const
	{
	__ASSERT_DEBUG(iEntry,Panic(_L("Null entry")));
	return (iEntry->HasDefaultDisplayTime());
	}

inline const CAgnSortEntry* TAgnLiteEntry::SortEntry() const
	{
	__ASSERT_DEBUG(iEntry,Panic(_L("Null entry")));
	return (iEntry);
	}


// --------------------------------------------------------------------
// -------------------------- TAgnAlarmDefaults -----------------------
// --------------------------------------------------------------------
inline TBool TAgnAlarmDefaults::HasAlarm() const
	{ return(iHasAlarm); }

inline TTimeIntervalDays TAgnAlarmDefaults::AlarmDaysWarning() const
	{ return(iDaysWarning); }

inline TTimeIntervalMinutes TAgnAlarmDefaults::AlarmTime() const
	{ return(iTimeOfDay); }

inline TPtrC TAgnAlarmDefaults::AlarmSoundName() const
	{ return(iSoundName); }

inline void TAgnAlarmDefaults::SetHasAlarm(TBool aHasAlarm)
	{ iHasAlarm=aHasAlarm; }

inline void TAgnAlarmDefaults::SetAlarmSoundName(const TDesC& aAlarmSoundName)
	{ iSoundName=aAlarmSoundName; }



// --------------------------------------------------------------------
// -------------------------- AgnModel --------------------------------
// --------------------------------------------------------------------
inline TAgnId AgnModel::NullId() 
	{ return (KNullStreamId); }

inline TAgnTodoListId AgnModel::NullTodoListId() 
	{ return TAgnTodoListId(KNullStreamId); }

inline TTime AgnModel::MinValidDate()
	{ return (AgnDateTime::MinDateAsTTime()); }

inline TTime AgnModel::MaxValidDate()
	{ return (AgnDateTime::MaxDateAsTTime()); }

inline TBool AgnModel::IsValidDate(const TTime& aDate)
	{ return (aDate != Time::NullTTime() && aDate >= MinValidDate() && aDate <= MaxValidDate()); }

inline TBool AgnModel::IsValidDate(TAgnDate aDate)
	{ return (aDate != AgnDateTime::NullDate()  && aDate >= AgnDateTime::MinDate() && aDate <= AgnDateTime::MaxDate()); }

inline TBool AgnModel::IsValidTime(TAgnTime aTime)
	{ return (aTime == AgnDateTime::NullTime() || aTime <= 1439); }

inline TBool AgnModel::IsValidTime(TTimeIntervalMinutes aTime)
	{ return (/*aTime == AgnDateTime::DefaultDisplayTime() || (*/aTime.Int() >= 0 && aTime.Int() <= 1439)/*)*/; }

inline TBool AgnModel::IsValidAlarmWarning(TTimeIntervalDays aDays)
	{ return (aDays.Int() >= 0 && aDays.Int() <= 1000); } //!!! any old figure for the moment

inline TUint AgnModel::MaxTodoListNameLength()
	{ return (KAgnMaxTodoListNameLength); }

inline TUint AgnModel::MaxSearchStringLength()
	{ return (KAgnMaxSearchStringLength); }


