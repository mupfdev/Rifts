// AGMTODOS.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//


// ---------------------------- TAgnTodoDefaults ----------------------------
inline void TAgnTodoDefaults::SetIsDated(TBool aIsDated)
	{ iIsDated = aIsDated; }

inline void TAgnTodoDefaults::SetDaysWarning(TTimeIntervalDays aDaysWarning)
	{ 
	iDaysWarning=aDaysWarning; 
	}

inline void TAgnTodoDefaults::SetDisplayDueDateAs(CAgnTodo::TDisplayDueDateAs aDisplayAs)
	{ iDisplayDueDateAs = aDisplayAs; }

inline void TAgnTodoDefaults::SetAlarmDefaults(const TAgnAlarmDefaults& aAlarmDefaults)
	{ iAlarmDefaults = aAlarmDefaults; }

inline void TAgnTodoDefaults::SetEntrySymbol(TChar aEntrySymbol)
	{ iEntrySymbol = aEntrySymbol; }

inline TBool TAgnTodoDefaults::IsDated() const
	{ return(iIsDated); }

inline TTimeIntervalDays TAgnTodoDefaults::DaysWarning() const
	{ return(iDaysWarning); }

inline CAgnTodo::TDisplayDueDateAs TAgnTodoDefaults::DisplayDueDateAs() const
	{ return(iDisplayDueDateAs); }

inline const TAgnAlarmDefaults& TAgnTodoDefaults::AlarmDefaults() const
	{ return(iAlarmDefaults); }

inline TChar TAgnTodoDefaults::EntrySymbol() const
	{ return(iEntrySymbol); }

inline void TAgnTodoDefaults::SetReplicationStatus(TAgnReplicationData::TStatus aStatus)
	{ 
	__ASSERT_DEBUG(aStatus == TAgnReplicationData::EOpen || aStatus == TAgnReplicationData::EPrivate ||
					aStatus == TAgnReplicationData::ERestricted,Panic(_L("Invalid emun value")));
	iReplicationStatus = aStatus; 
	}

inline TAgnReplicationData::TStatus TAgnTodoDefaults::ReplicationStatus() const
	{ return (iReplicationStatus); }

inline TBool TAgnTodoDefaults::HasEntrySymbol() const
	{ return (iHasEntrySymbol); }

inline void TAgnTodoDefaults::SetHasEntrySymbol(TBool aSetting)
	{ iHasEntrySymbol = aSetting; }

inline void TAgnTodoDefaults::SetBackgroundColor(const TRgb& aColor)
	{ iBackgroundColor = aColor; }

inline TRgb TAgnTodoDefaults::BackgroundColor() const
	{ return (iBackgroundColor); }

// ----------------------------------- TAgnTodoDisplaySettings ------------------------------
inline TAgnTodoDisplaySettings::TAgnTodoDisplaySettings()
	: iSettings(0) 
	{}

inline TBool TAgnTodoDisplaySettings::DisplayEntries() const
	{ return (iSettings & EDisplayInOtherViewsMask); }

inline TBool TAgnTodoDisplaySettings::DisplayCrossedOutEntries() const
	{ return (iSettings & EDisplayCrossedOutMask); } 

inline TTimeIntervalMinutes TAgnTodoDisplaySettings::DefaultDisplayTime() const
	{ return (iSettings & ETimeMask); }

inline void TAgnTodoDisplaySettings::ClearAllSettings()
	{ iSettings = 0; }

inline TBool TAgnTodoDisplaySettings::operator==(const TAgnTodoDisplaySettings& aOther) const
	{ return (iSettings == aOther.iSettings); }



// --------------------------------- CAgnTodoListList ---------------------------
inline void CAgnTodoListList::InsertL(TInt aPosition,const TListItem* aItem)
	{ iTodoLists->InsertL(aPosition,*aItem); }

inline void CAgnTodoListList::AppendL(const TListItem* aItem)
	{ iTodoLists->AppendL(*aItem); }

inline TInt CAgnTodoListList::Count() const
	{ return (iTodoLists->Count()); }

inline void CAgnTodoListList::Delete(TInt aPosition)
	{
	__ASSERT_DEBUG(aPosition >=0 && aPosition < Count(),Panic(_L("TodoListListIndexOutOfRange")));
	iTodoLists->Delete(aPosition);
	}



// ------------------------ CAgnDeletedTodoListList ---------------------------------------
inline TInt CAgnDeletedTodoListList::Count() const
	{ return (iTodoListIds->Count()); }

inline void CAgnDeletedTodoListList::AppendL(const TAgnTodoListId* aItem)
	{ iTodoListIds->AppendL(*aItem); }

inline void CAgnDeletedTodoListList::Delete(TInt aPosition)
	{
	__ASSERT_DEBUG(aPosition >=0 && aPosition < Count(),Panic(_L("DeletedTodoListListIndexOutOfRange")));
	iTodoListIds->Delete(aPosition);
	}

inline TAgnTodoListId CAgnDeletedTodoListList::TodoListId(TInt aIndex) const	
	{
	__ASSERT_DEBUG(aIndex >=0 && aIndex < Count(),Panic(_L("DeletedTodoListListIndexOutOfRange")));
	return (((*iTodoListIds)[aIndex]));
	}



// --------------------------- CAgnTodoList ------------------------------
inline TPtrC CAgnTodoList::Name() const
	{ return (iName); };

inline CAgnTodoList::TSortOrder CAgnTodoList::SortOrder() const
	{ return (iSortOrder); }

inline TBool CAgnTodoList::DisplayCrossedOutEntries() const
	{ return (iDisplayCrossedOutEntries); }

inline TBool CAgnTodoList::DisplayCrossedOutEntriesInOtherViews() const
	{ return (iHowTodosAreDisplayedInViewsOtherThanTheTodoView.DisplayCrossedOutEntries()); }

inline TTimeIntervalMinutes CAgnTodoList::DefaultDisplayTimeInOtherViews() const
	{ return (iHowTodosAreDisplayedInViewsOtherThanTheTodoView.DefaultDisplayTime()); }

inline TBool CAgnTodoList::DisplayEntriesInOtherViews() const
	{ return (iHowTodosAreDisplayedInViewsOtherThanTheTodoView.DisplayEntries()); }

inline TInt CAgnTodoList::Count() const
	{ return (iTodos->Count()); }

inline  TAgnTodoListId CAgnTodoList::Id() const
	{ return (iId);}

void CAgnTodoList::InsertL(TInt aPosition,TAgnEntryId aItem)
	{ iTodos->InsertL(aPosition,aItem); }

inline void CAgnTodoList::AppendL(TAgnEntryId aItem)
	{ iTodos->AppendL(aItem); }

inline void CAgnTodoList::Delete(TInt aPos)
	{ 
	__ASSERT_DEBUG(aPos >=0 && aPos < Count(),Panic(_L("Todo list item out of range")));
	iTodos->Delete(aPos);
	}
	
inline const TAgnEntryId& CAgnTodoList::At(TInt aIndex) 
	{
	__ASSERT_DEBUG(aIndex >= 0 && aIndex < Count(),Panic(_L("TodoListIndexOutOfRange")));
	return ((*iTodos)[aIndex]);
	}

inline TAgnEntryId& CAgnTodoList::operator[](TInt aIndex) const
	{
	__ASSERT_DEBUG(aIndex >= 0 && aIndex < Count(),Panic(_L("TodoListIndexOutOfRange")));
	return ((*iTodos)[aIndex]);
	}

inline void CAgnTodoList::Reset()
	{ iTodos->Reset(); }

inline void CAgnTodoList::SetId(TAgnTodoListId aId)
	{ iId=aId; }
	
inline const TAgnTodoDefaults& CAgnTodoList::TodoDefaults() const
	{ return (iTodoDefaults); }

inline const TAgnTodoDisplaySettings& CAgnTodoList::TodoDisplaySettings() const
	{ return (iHowTodosAreDisplayedInViewsOtherThanTheTodoView); }

inline void CAgnTodoList::SetTodoDisplaySettings(const TAgnTodoDisplaySettings& aSettings)
	{ iHowTodosAreDisplayedInViewsOtherThanTheTodoView = aSettings; }

inline const TAgnReplicationData& CAgnTodoList::ReplicationData() const
	{ return (iReplicationData); }

inline TAgnReplicationData& CAgnTodoList::ReplicationData()
	{ return (iReplicationData); }

inline void CAgnTodoList::SetReplicationData(const TAgnReplicationData& aReplicationData)
	{ iReplicationData = aReplicationData; }

inline void CAgnTodoList::SetUniqueId(TAgnUniqueId aUId)
	{ iUniqueId = aUId; }

inline TAgnUniqueId CAgnTodoList::UniqueId() const
	{ return (iUniqueId); }



// ----------------------------- CAgnTodoListNames ------------------------------------------
inline CAgnTodoListNames::CAgnTodoListNames()
	{
	}

inline void CAgnTodoListNames::Reset()
	{ iTodoNameList->Reset(); }

inline TInt CAgnTodoListNames::Count() const
	{ return (iTodoNameList->Count()); }

inline void CAgnTodoListNames::AppendL(const TListItem& aItem)
	{ iTodoNameList->AppendL(aItem); }

inline void CAgnTodoListNames::InsertL(TInt aPosition,const TListItem& aItem)
	{  iTodoNameList->InsertL(aPosition,aItem); }
	

//
inline const TDesC& CAgnTodoListNames::TListItem::Name() const
	{ return (iName); }

inline void CAgnTodoListNames::TListItem::SetName(const TDesC& aName)
	{ iName=aName; }

inline TAgnTodoListId CAgnTodoListNames::TListItem::TodoListId() const
	{ return (iTodoListId); }

inline void CAgnTodoListNames::TListItem::SetTodoListId(TAgnTodoListId aTodoListId)
	{ iTodoListId=aTodoListId; }

inline CAgnTodoList::TSortOrder CAgnTodoListNames::TListItem::SortOrder() const
	{ return (iSortOrder); }

inline void CAgnTodoListNames::TListItem::SetSortOrder(CAgnTodoList::TSortOrder aSortOrder)
	{ iSortOrder = aSortOrder; }








