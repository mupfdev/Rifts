// AGMENTRY.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//


//------------------------------ CAgnEntry -------------------------------------------
inline const CStreamStore& CAgnEntry::OriginatingStore() const
	{ return (*iOriginatingStore); }

inline void CAgnEntry::SetId(TAgnEntryId aId)
	{ iInstanceId.SetId(aId); }

inline TAgnEntryId CAgnEntry::EntryId() const
	{ return (iInstanceId.Id()); }

inline TAgnInstanceId CAgnEntry::InstanceId() const
	{ return (iInstanceId); }

inline void CAgnEntry::SetInstanceDate(TAgnDate aDate)
	{ iInstanceId.SetDate(aDate); }

inline TAgnDate CAgnEntry::InstanceDate() const
	{ return (iInstanceId.Date()); }

inline void CAgnEntry::SetIdAndInstanceDate(TAgnEntryId aId,TAgnDate aDate)
	{ iInstanceId.SetIdAndDate(aId,aDate); }

inline void CAgnEntry::SetIdAndInstanceDate(const TAgnInstanceId& aInstanceId)
	{ iInstanceId=aInstanceId; }

inline void CAgnEntry::SetInstanceId(const TAgnInstanceId& aInstanceId)
	{ iInstanceId=aInstanceId; }


//inline void CAgnEntry::IncReplicatedCount()
//	{ iReplicatedCount++; }	  

//inline void CAgnEntry::DecReplicatedCount()
//	{ 
//	__ASSERT_DEBUG(iReplicatedCount>0,Panic(_L("Decrementing past zero")));
//	iReplicatedCount--; 
//	}

//inline TUint CAgnEntry::ReplicatedCount() const
//	{ return iReplicatedCount; }

inline void CAgnEntry::SetUniqueId(TAgnUniqueId aUId)
	{ iUniqueId=aUId; }

inline TAgnUniqueId CAgnEntry::UniqueId() const
	{ return iUniqueId; }

//inline TBool CAgnEntry::RichTextStoreIsOpen() const
//	{ return (iRichTextStoreIsOpen); }

//inline void CAgnEntry::SetRichTextStoreIsOpen(TBool aIsOpen)
//	{  iRichTextStoreIsOpen = aIsOpen; }


inline const TAgnReplicationData& CAgnEntry::ReplicationData() const
	{ return (iReplicationData); }

inline TAgnReplicationData& CAgnEntry::ReplicationData()
	{ return (iReplicationData); }

inline void CAgnEntry::SetReplicationData(const TAgnReplicationData& aReplicationData)
	{ iReplicationData = aReplicationData; }

inline void CAgnEntry::SetRichTextStreamId(TStreamId aId)
	{ iRichTextStreamId = aId; }

inline TStreamId CAgnEntry::RichTextStreamId() const
	{ return (iRichTextStreamId); }



//------------------------------ CAgnAppt -------------------------------------------
inline const TAgnBasicAppt& CAgnAppt::BasicAppt() const
	{ return (iBasicAppt); }


//------------------------------ CAgnEvent -------------------------------------------
inline const TAgnBasicEvent& CAgnEvent::BasicEvent() const
	{ return (iBasicEvent); }


//------------------------------ CAgnAnniv -------------------------------------------
inline TTimeIntervalYears CAgnAnniv::BaseYear() const
	{ return (iBaseYear); }

inline CAgnAnniv::TDisplayAs CAgnAnniv::DisplayAs() const
	{ return (iDisplayAs); }

inline TBool CAgnAnniv::HasBaseYear() const
	{ return (iHasBaseYear); }

inline void CAgnAnniv::SetHasBaseYear(TBool aHasBaseYear)
	{ iHasBaseYear = aHasBaseYear; }


//------------------------------ CAgnTodo -------------------------------------------
inline TAgnTodoListId CAgnTodo::TodoListId() const
	{ return (iBasicTodo.TodoListId()); }

inline CAgnTodo::TDisplayDueDateAs CAgnTodo::DisplayDueDateAs() const
	{ return (iDisplayDueDateAs); }

inline TUint CAgnTodo::Priority() const
	{ return (iBasicTodo.Priority()); }

inline TTimeIntervalDays CAgnTodo::Duration() const
	{ return (iBasicTodo.Duration()); }

inline const TAgnBasicTodo& CAgnTodo::BasicTodo() const
	{ return (iBasicTodo); }

inline TBool CAgnTodo::IsAlarmSetFromDueDate() const
	{ return (iBasicTodo.IsAlarmSetFromDueDate()); }

inline TBool CAgnTodo::IsAlarmSetFromStartDate() const
	{ return (iBasicTodo.IsAlarmSetFromStartDate()); }



