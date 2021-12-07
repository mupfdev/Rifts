// AGMMODEL.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// -------------------------------- CAgnEntryModel -----------------------------------
inline CAgnEntryModel::CAgnEntryModel(MAgnModelStateCallBack* aStateCallBack)
	: iStateCallBack(aStateCallBack), 
	iTodoListMapKey (_FOFF(TTodoListMapItem,iOldId),ECmpNormal8,sizeof(TAgnTodoListId))
	{
	}

inline CAgnObsController* CAgnEntryModel::ObserverController() const
	{ return (iObserverController); }

inline CStreamStore& CAgnEntryModel::StreamStore() const
	{ return (*iStreamStore); }

inline CAgnModelStreamIdSet* CAgnEntryModel::ModelStreamIdSet() const
	{ return (iModelStreamIdSet); }

// this is public
inline const CAgnTodoListList* CAgnEntryModel::PeekAtTodoListList() const
	{ return (iTodoListList);}

// but these two are protected
inline CAgnTodoListList* CAgnEntryModel::TodoListList() 
	{ return (iTodoListList); }

inline const CAgnTodoListList* CAgnEntryModel::TodoListList() const
	{ return (iTodoListList); }

inline const CAgnDeletedTodoListList* CAgnEntryModel::PeekAtDeletedTodoListList() const
	{ return (iDeletedTodoListList); }

inline CAgnDeletedTodoListList* CAgnEntryModel::DeletedTodoListList() 
	{ return (iDeletedTodoListList); }

inline const CAgnEntryStore* CAgnEntryModel::EntryStore() const
	{ return (iEntryStore); }

inline CAgnEntryStore* CAgnEntryModel::EntryStore() 
	{ return (iEntryStore); }

inline const TAgnTodoListStore& CAgnEntryModel::TodoListStore() const
	{ return (iTodoListStore); }

inline TAgnTodoListStore& CAgnEntryModel::TodoListStore() 
	{ return (iTodoListStore); }

inline void CAgnEntryModel::SetDefaultEventDisplayTime(TTimeIntervalMinutes aDefaultEventDisplayTime)
	{ iDefaultEventDisplayTime=aDefaultEventDisplayTime; }

inline void CAgnEntryModel::SetDefaultAnnivDisplayTime(TTimeIntervalMinutes aDefaultAnnivDisplayTime)
	{ iDefaultAnnivDisplayTime=aDefaultAnnivDisplayTime; }

inline void CAgnEntryModel::SetDefaultDayNoteDisplayTime(TTimeIntervalMinutes aDefaultDayNoteDisplayTime)
	{ iDefaultDayNoteDisplayTime=aDefaultDayNoteDisplayTime; }

inline TTimeIntervalMinutes CAgnEntryModel::DefaultEventDisplayTime() const
	{ return (iDefaultEventDisplayTime); }

inline TTimeIntervalMinutes CAgnEntryModel::DefaultAnnivDisplayTime() const
	{ return (iDefaultAnnivDisplayTime); }

inline TTimeIntervalMinutes CAgnEntryModel::DefaultDayNoteDisplayTime() const
	{ return (iDefaultDayNoteDisplayTime); }

inline CAgnEntryModel::TState CAgnEntryModel::State() const
	{ return (iState); }

inline void CAgnEntryModel::SetState(CAgnEntryModel::TState aState)
	{ iState = aState; }

inline void CAgnEntryModel::RegisterIndex(CAgnSortEntryTable* aIndex)
	{ iRegisteredIndex = aIndex; }

inline CAgnSortEntryTable* CAgnEntryModel::RegisteredIndex() const
	{ return (iRegisteredIndex); }

inline void CAgnEntryModel::RegisterAlarm(CAgnAlarm* aAlarm)
	{ iRegisteredAlarm = aAlarm; }

inline CAgnAlarm* CAgnEntryModel::RegisteredAlarm() const
	{ return (iRegisteredAlarm); }

inline const CParaFormatLayer* CAgnEntryModel::ParaFormatLayer() const
	{ return (iParaFormatLayer); }

inline const CCharFormatLayer* CAgnEntryModel::CharFormatLayer() const
	{ return (iCharFormatLayer); }

inline MPictureFactory* CAgnEntryModel::PictureFactory() const
	{ return (iPictureFactory); }

inline void CAgnEntryModel::SetPictureFactory(MPictureFactory* aPictureFactory)
	{ iPictureFactory = aPictureFactory; }

inline TAgnVersion CAgnEntryModel::FileVersion() const
	{ return (ModelStreamIdSet()->Version()); }

inline CAgnGlobalIdIndex* CAgnEntryModel::GlobalIdIndex() const
	{ return iGlobalIdIndex; }

inline CAgnUniqueIdIndex* CAgnEntryModel::UniqueIdIndex() const
	{ return iUniqueIdIndex; }

inline CAgnTodoListIdIndex* CAgnEntryModel::TodoListIdIndex() const
	{ return iTodoListIdIndex; }

inline CAgnDeletedIndex* CAgnEntryModel::DeletedIndex() const
	{ return iDeletedIndex; }

// -------------------------------- CAgnIndexedModel ----------------------------------
inline TBool CAgnIndexedModel::TidyByDateL(const TAgnFilter& aFilter,const TTime& aTodaysDate,const TTime& aStartDate,
						const TTime& aEndDate,MAgnProgressCallBack* aProgressCallBack,TTidyDirective aDirective)
	{
	CStreamStore* store=NULL;
	TStreamId id=KNullStreamId;
	return TidyByDateL(aFilter,aTodaysDate,aStartDate,aEndDate,aProgressCallBack,aDirective,store,id);
	}

inline TBool CAgnIndexedModel::TidyByDateL(const TAgnFilter& aFilter,const TTime& aTodaysDate,const TTime& aStartDate,
						const TTime& aEndDate,MAgnProgressCallBack* aProgressCallBack,
						TTidyDirective aDirective,CStreamStore* aStoreToTidyTo)
	{
	TStreamId id=KNullStreamId;
	return TidyByDateL(aFilter,aTodaysDate,aStartDate,aEndDate,aProgressCallBack,aDirective,aStoreToTidyTo,id);
	}

inline TBool CAgnIndexedModel::TidyByTodoListL(const CArrayFixFlat<TAgnTodoListId>* aList,
						MAgnProgressCallBack* aProgressCallBack,TTidyDirective aDirective,TTidyTodoListHow aTidyHow)
	{
	CStreamStore* store=NULL;
	TStreamId id=KNullStreamId;
	return TidyByTodoListL(aList,aProgressCallBack,aDirective,aTidyHow,store,id);
	}

inline TBool CAgnIndexedModel::TidyByTodoListL(const CArrayFixFlat<TAgnTodoListId>* aList,
						MAgnProgressCallBack* aProgressCallBack,TTidyDirective aDirective,
						TTidyTodoListHow aTidyHow,CStreamStore* aStoreToTidyTo)
	{
	TStreamId id=KNullStreamId;
	return TidyByTodoListL(aList,aProgressCallBack,aDirective,aTidyHow,aStoreToTidyTo,id);
	}
	
inline CAgnIndexedModel::CAgnIndexedModel(MAgnModelStateCallBack* aStateCallBack)
	: CAgnEntryModel(aStateCallBack)
	{
	}

inline CAgnSortEntryTable* CAgnIndexedModel::Indexes() const  
	{ return iIndexes; }

// -------------------------------- CAgnModel ----------------------------------
inline CAgnModel::CAgnModel(MAgnModelStateCallBack* aStateCallBack)
	: CAgnIndexedModel(aStateCallBack)
	{
	}

