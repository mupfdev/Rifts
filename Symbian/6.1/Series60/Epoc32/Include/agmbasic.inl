// AGMBASIC.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//


// --------------------- TAgnAlarmPreTime -----------------------------------
inline TBool TAgnAlarmPreTime::operator==(const TAgnAlarmPreTime& aOther) const
	{ return (iAlarmPreTime == aOther.iAlarmPreTime); }

inline TBool TAgnAlarmPreTime::operator!=(const TAgnAlarmPreTime& aOther) const
	{ return (iAlarmPreTime != aOther.iAlarmPreTime); }



// ---------------------------- CAgnBasicEntry ----------------------------
inline CAgnBasicEntry::CAgnBasicEntry()
	{}

inline TBool CAgnBasicEntry::IsCrossedOut() const
	{ return (iAttributes & EIsCrossedOut); }

inline TBool CAgnBasicEntry::IsRepeating() const  	
	{ return (iAttributes & EIsRepeating); }

inline TBool CAgnBasicEntry::HasExceptions() const
	{ return (iAttributes & EHasExceptions); }

inline TBool CAgnBasicEntry::IsStoredInline() const
	{ return (iAttributes & EIsStoredInline); }

inline TBool CAgnBasicEntry::DisplayInYearView() const
	{ return (iAttributes & EDisplayInYearView); }

inline TBool CAgnBasicEntry::HasEntrySymbol() const
	{ return (iAttributes & EHasEntrySymbol); } 

inline TBool CAgnBasicEntry::IsADayNote() const
	{ return (iAttributes & EIsADayNote); }

inline TBool CAgnBasicEntry::HasDefaultDisplayTime() const
	{ return (iAttributes & EHasDefaultDisplayTime); }

//inline TBool CAgnBasicEntry::HasBeenDeleted() const 
//	{ return (iAttributes & EHasBeenDeleted); }

//inline TBool CAgnBasicEntry::IsRestricted() const
//	{ return (iAttributes & EIsRestricted); }

//inline TBool CAgnBasicEntry::IsPrivate() const
//	{ return (iAttributes & EIsPrivate); }

inline TBool CAgnBasicEntry::IsTentative() const 
	{ return (iAttributes & EIsTentative); }

inline TBool CAgnBasicEntry::IsSketch() const
	{ return (iAttributes & EIsSketch); }

inline TBool CAgnBasicEntry::HasExtended() const
	{ return (iAttributes & EHasExtended); }

inline void CAgnBasicEntry::ClearAllAttributes()
	{ iAttributes=0; }

inline TChar CAgnBasicEntry::EntrySymbol() const
	{ return (iEntrySymbol); }
		
inline TAgnAlarmPreTime CAgnBasicEntry::AlarmPreTime() const
	{ return (iAlarmPreTime); }; 

inline CAgnRptDef* CAgnBasicEntry::RptDef() 
	{ return (iRptDef);}

inline const CAgnRptDef* CAgnBasicEntry::RptDef() const
	{ return (iRptDef); }

// ---------------------------------- TAgnBasicAppt -------------------------------------------
inline TAgnDateTime TAgnBasicAppt::StartDateTime() const
	{ return (iStartDateTime); }

inline TAgnDateTime TAgnBasicAppt::EndDateTime() const
	{ return (iEndDateTime); }

// --------------------------------- TAgnBasicEvent ------------------------------------------
//inline TAgnBasicEvent::TAgnBasicEvent() /*: iDisplayTime((TAgnTime)AgnDateTime::DefaultDisplayTime().Int()) */
//	{}

inline TAgnDate TAgnBasicEvent::StartDate() const
	{ return (iStartDate); }

inline TAgnDate TAgnBasicEvent::EndDate() const
	{ return (iEndDate); }

inline TAgnTime TAgnBasicEvent::DisplayTime() const
	{ return (iDisplayTime); }

inline void TAgnBasicEvent::SetDisplayTime(TAgnTime aDisplayTime)
	{  iDisplayTime=(TAgnTime)aDisplayTime; } 


// -------------------------------------- TAgnBasicTodo ------------------------------------------
//inline TAgnBasicTodo::TAgnBasicTodo() /*: iDisplayTime((TAgnTime)AgnDateTime::DefaultDisplayTime().Int()) */
//	{
//	SetHasDefaultDisplayTime(ETrue);
//	}

inline TAgnDate TAgnBasicTodo::DueDate() const
	{ return (iDueDate); }

void TAgnBasicTodo::SetDueDate(TAgnDate aDueDate)
	{ iDueDate=aDueDate; }

inline TAgnDate TAgnBasicTodo::CrossedOutDate() const
	{ return (iCrossedOutDate); }

inline TAgnTime TAgnBasicTodo::DisplayTime() const
	{ return (iDisplayTime); }

inline void TAgnBasicTodo::SetDisplayTime(TAgnTime aDisplayTime)
	{ iDisplayTime=(TAgnTime)aDisplayTime; }

inline TAgnTodoListId TAgnBasicTodo::TodoListId() const
	{ return (iTodoListId); }

inline void TAgnBasicTodo::SetTodoListId(TAgnTodoListId aTodoListId)
	{ iTodoListId=aTodoListId; }

inline TAgnDurationDays TAgnBasicTodo::Duration() const
	{ return (iDuration); }

inline void TAgnBasicTodo::SetDuration(TAgnDurationDays aDuration)
	{ iDuration=aDuration; }

inline TUint TAgnBasicTodo::Priority() const
	{ return (iPriority); }

inline void TAgnBasicTodo::SetPriority(TUint aPriority)
	{ 
	__ASSERT_DEBUG(SafeToCast(sizeof(TUint8),aPriority),Panic(_L("Unsafe cast"))); 
	iPriority=(TUint8)aPriority; 
	}

inline void TAgnBasicTodo::SetAlarmFromDueDate()
	{ iAlarmFrom = EDueDate; }

inline void TAgnBasicTodo::SetAlarmFromStartDate()
	{ iAlarmFrom = EStartDate; }

inline TBool TAgnBasicTodo::IsAlarmSetFromDueDate() const
	{ return (iAlarmFrom == EDueDate); }

inline TBool TAgnBasicTodo::IsAlarmSetFromStartDate() const
	{ return (iAlarmFrom == EStartDate); }
