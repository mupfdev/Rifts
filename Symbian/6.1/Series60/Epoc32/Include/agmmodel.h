// AGMMODEL.H
//
// Copyright (c) 1997-2002 Symbian Ltd.  All rights reserved.
//

#pragma warning (disable: 4239 4663)


#ifndef __AGMMODEL_H__
#define __AGMMODEL_H__

#include <e32base.h>
#include <vcal.h>
#include "agmiedit.h"
#include "agmentry.h"
#include "agmsets.h"
#include "agmupact.h"
#include "agmstore.h"
#include "agmfilts.h"
#include "agmlists.h"
#include "agmcomon.h"
#include "agmxsort.h"
#include "agmactiv.h"
#include "agmxiter.h"
#include "agmver.h"
#include "agmobsrv.h"
#include "agmextrc.h"
#include "agclient.h"
#include "agmcfilt.h"


class TAgnEntryDateIterator;
class CAgnEntryStore;
class TAgnTodoListStore;
class CAgnAnonStore;
class TAgnEntryGroupId;
class TAgnTodoListId;
class CAgnEntryGroup;
class CAgnTodoList;
class TAgnTidyFlags;
class CAgnTodoListIds;
class TAgnEntryIter;
class TAgnSortInstance;
class CAgnActive;
class CAgnAlarm;
class TAgnTodoListMapItem;
class CParaFormatLayer;
class CCharFormatLayer;
class MPictureFactory;
class MAgnModelStateCallBack;
class MAgnProgressCallBack;
class CAgnGlobalIdIndex;
class CAgnObsController;
class CAgnTodoListIdIndex;


class CAgnEntryModel : public CBase, public MAgnActiveStep
//
// Interface to the agenda data
//
	{
public:
	friend class TAgnEntryIter;
	friend class CAgnUniqueView;
	enum TState	{ENoFile,EBlocked,EOk};
	enum TSaveAsCallBackFrequency {ESaveAsCallBackHigh=1,ESaveAsCallBackMedium=3,ESaveAsCallBackLow=4};
	enum {EAddTodoListAtEnd=0xFFFF}; // Indicates that a new todo list should be added to the end of the todo list list
	enum TUseExistingUniqueId {EUseExistingUniqueId,EDontUseExistingUniqueId};
	enum TCommit {ECommit,EDontCommit}; 
	enum TModelMode {ENormal, EClient, EServer};
	enum TOpenFrequency {EOpenCallBackHigh=1,EOpenCallBackMedium=2,EOpenCallBackLow=4};

	IMPORT_C static CAgnEntryModel* NewL(MAgnModelStateCallBack* aStateCallBack=NULL); 
	IMPORT_C virtual ~CAgnEntryModel();

	IMPORT_C void OpenL(CStreamStore& aStore,
						TStreamId aId,
						TTimeIntervalMinutes aDefaultEventDisplayTime = 0,
						TTimeIntervalMinutes aDefaultAnnivDisplayTime = 0,
						TTimeIntervalMinutes aDefaultDayNoteDisplayTime = 0);

	IMPORT_C void OpenL(const TDesC& aFileName,
						TTimeIntervalMinutes aDefaultEventDisplayTime = 0,
						TTimeIntervalMinutes aDefaultAnnivDisplayTime = 0,
						TTimeIntervalMinutes aDefaultDayNoteDisplayTime = 0);

	IMPORT_C TStreamId CreateL(CStreamStore& aStore,
								const TDesC& aDefaultTodoListName,
								const CParaFormatLayer* aParaFormatLayer,
								const CCharFormatLayer* aCharFormatLayer);  

	IMPORT_C TStreamId SaveAsL(CStreamStore& aStoreToSaveTo,MAgnProgressCallBack* aProgressCallBack,
						TSaveAsCallBackFrequency aSaveAsCallBackFrequency = ESaveAsCallBackMedium) const;

	IMPORT_C TStreamId SaveTodoListsL(CStreamStore& aStoreToSaveTo) const;

// Entry operations
	TAgnEntryId AddEntryL(CAgnEntry* aEntry,TAgnEntryId aTodoPositionReferenceId,TCommit aCommit,TUseExistingUniqueId aUseExistingUniqueId = EDontUseExistingUniqueId);
	IMPORT_C TAgnEntryId AddEntryL(CAgnEntry* aEntry,TAgnEntryId aTodoPositionReferenceId = AgnModel::NullId());
	IMPORT_C void DeleteEntryL(CAgnEntry* aEntry);
	IMPORT_C virtual void DeleteEntryL(TAgnEntryId aEntryId);
	virtual void DeleteEntryL(CAgnEntry* aEntry,TCommit aCommit);
	IMPORT_C void UpdateEntryL(CAgnEntry* aEntry,TAgnEntryId aTodoPositionReferenceId = AgnModel::NullId());
	void UpdateEntryL(CAgnEntry* aEntry,TAgnEntryId aTodoPositionReferenceId,TCommit aCommit);
	IMPORT_C CAgnEntry* FetchEntryL(TAgnEntryId aId) const;
	IMPORT_C CAgnEntry* FetchEntryL(TAgnGlobalId aId) const;
	IMPORT_C CAgnEntry* FetchEntryL(TAgnUniqueId aId) const;
	IMPORT_C void ChangeTodoOrderL(TAgnTodoListId aTodoListId,TAgnEntryId aTodoId,TAgnEntryId aTodoPositionReferenceId= AgnModel::NullId());
	IMPORT_C void ChangeTodoOrderL(CAgnTodoList* aTodoList,TAgnEntryId aTodoId,TAgnEntryId aTodoPositionReferenceId= AgnModel::NullId());
	IMPORT_C void CutEntryL(TAgnEntryId aEntryId);
	IMPORT_C void CutEntryL(CAgnEntry* aEntry);
	IMPORT_C void PasteEntryL(CAgnEntry* aEntry, TAgnEntryId aTodoPositionReferenceId = AgnModel::NullId());

// Todo list operations
	IMPORT_C CAgnTodoList* FetchTodoListL(TAgnTodoListId aTodoListId) const;
	IMPORT_C CAgnTodoList* FetchTodoListL(TAgnUniqueId aUniqueId) const;
	IMPORT_C virtual TAgnTodoListId AddTodoListL(CAgnTodoList* aTodoList,TInt aPosition=EAddTodoListAtEnd);
	IMPORT_C virtual void DeleteTodoListL(CAgnTodoList* aTodoList);  
	IMPORT_C virtual void DeleteTodoListL(TAgnTodoListId aTodoListId);
	IMPORT_C virtual void UpdateTodoListL(CAgnTodoList* aTodoList);
	IMPORT_C TInt TodoListCount() const;
	IMPORT_C void ChangeTodoListOrderL(TInt aOldPosition,TInt aNewPosition);
	IMPORT_C void PopulateTodoListNamesL(CAgnTodoListNames* aList) const;
	inline const CAgnTodoListList* PeekAtTodoListList() const;
	inline const CAgnDeletedTodoListList* PeekAtDeletedTodoListList() const; //  for synchronisation users
	IMPORT_C CArrayFixFlat<TAgnTodoListId>* TodoListIdsL() const; // for synchronisation users

// Misc 
	inline void SetDefaultEventDisplayTime(TTimeIntervalMinutes aDefaultEventDisplayTime);
	inline void SetDefaultAnnivDisplayTime(TTimeIntervalMinutes aDefaultAnnivDisplayTime);
	inline void SetDefaultDayNoteDisplayTime(TTimeIntervalMinutes aDefaultDayNoteDisplayTime);
	inline TTimeIntervalMinutes DefaultEventDisplayTime() const;
	inline TTimeIntervalMinutes DefaultAnnivDisplayTime() const;
	inline TTimeIntervalMinutes DefaultDayNoteDisplayTime() const;
	IMPORT_C TTimeIntervalMinutes DefaultDisplayTime(CAgnEntry::TType aType,TAgnTodoListId = AgnModel::NullId()) const;
	inline TState State() const;
	inline void RegisterAlarm(CAgnAlarm* aAlarm);
	inline CAgnAlarm* RegisteredAlarm() const;
	inline const CParaFormatLayer* ParaFormatLayer() const;
	inline const CCharFormatLayer* CharFormatLayer() const;
	IMPORT_C void SetParaAndCharFormatLayersL(const CParaFormatLayer* aParaFormatLayer,const CCharFormatLayer* aCharFormatLayer);
	inline void SetPictureFactory(MPictureFactory* aPictureFactory);
	inline MPictureFactory* PictureFactory() const;
	inline CAgnSortEntryTable* RegisteredIndex() const;
	inline CStreamStore& StreamStore() const;
	IMPORT_C TAgnVersion ModelVersion() const; // the version of the model object
	inline TAgnVersion FileVersion() const; // the version of the model that was used to create the currently loaded file
	inline CAgnGlobalIdIndex* GlobalIdIndex() const;
	inline CAgnUniqueIdIndex* UniqueIdIndex() const;
	inline CAgnTodoListIdIndex* TodoListIdIndex() const;
	inline CAgnDeletedIndex* DeletedIndex() const;
	IMPORT_C TTime LastSynchronizedDateL() const;
	IMPORT_C void SetLastSynchronizedDateL(const TTime& aTime) const;
	IMPORT_C TInt IsValidL(CStreamStore& aStore,TStreamId aId) const;
	void SetDefaultDisplayTime(CAgnEntry* aEntry) const;
	IMPORT_C void Cancel(); // cancel an active object driven operation

// Observer stuff
	IMPORT_C void RegisterObserverL(const TFileName& aObserverName,const CAgnObserver* aObserver);	// Regiser a new observer
	IMPORT_C void UnregisterObserverL(const TFileName& aObserverName);
	IMPORT_C void UseObserverController(TBool aUse);
	IMPORT_C TBool IsInUseObserverController() const;
	IMPORT_C TInt NumberOfObserversRegistered() const;
	IMPORT_C TInt NumberOfObserversLoaded() const;
	void UpdateObserverControllerL();
	inline CAgnObsController* ObserverController() const;

// Don't call these unless you know what you're doing
	IMPORT_C TBool BufferedStoring() const;
	IMPORT_C void SetBufferedStoring(TBool aSetting);
	IMPORT_C TBool BufferedDeleting() const;
	IMPORT_C void SetBufferedDeleting(TBool aSetting);	
	IMPORT_C void CommitL();
	IMPORT_C void FlushAndCommitL();
	void FlushL();
	IMPORT_C void RollbackL();
	inline void SetState(TState aState); 

	IMPORT_C TStreamId CreateL(CStreamStore& aStore,
								const TDesC& aDefaultTodoListName,
								const CParaFormatLayer* aParaFormatLayer,
								const CCharFormatLayer* aCharFormatLayer,
								TBool aCreateTodoList);

	IMPORT_C void CreateL(RFs& aFs, TFileName aFileName,
							const TDesC& aDefaultTodoListName,
							const CParaFormatLayer* aParaFormatLayer,
							const CCharFormatLayer* aCharFormatLayer);


	// Addition functions required for server interface
	IMPORT_C TStreamId StreamId(TUid aUid);
	IMPORT_C RReadStream& GetReadStreamL(TStreamId aStreamId);
	IMPORT_C void SetMode(TModelMode aMode);
	TBool PrepareForIndexBuilderL();
	void CleanupIndexBuilder();
	TInt DoIndexBuildStepL();
	CAgnSortEntryTable* ModelIndex();
	IMPORT_C TAgnInstanceExtractor* GetInstanceExtractorL(TAgnDate aToday, TAgnFilter& aFilter);
	IMPORT_C void GetDayListFromExtractorL(TAgnInstanceExtractor* aExtractor, TAgnDate aDay, CArrayFixFlat<TAgnSortInstance>* aDayInfoList, TAgnDate aToday);
	TAgnLiteEntry GetLiteEntryFromServerL(TAgnEntryId aId,CAgnSortEntryAllocator* aAllocator) const;
	CAgnSortEntry* GetLiteEntryForServer(TAgnEntryId aId);
	IMPORT_C void GetSymbolInstanceListL(CAgnSymbolList* aList,TTime& aToday, TAgnFilter& aFilter);
	void ExternalizeSymbolListL(CAgnSymbolList* aSymbolList, RWriteStream& aStream);
	void InternalizeSymbolListL(CAgnSymbolList* aSymbolList, RReadStream& aStream);
	IMPORT_C void SetServer(RAgendaServ* aServer);
	IMPORT_C RAgendaServ* Server() const;
	TAgnEntryId AddEntryForServerL(CAgnEntry* aEntry,TAgnEntryId aTodoPositionReferenceId,TCommit aCommit,TUseExistingUniqueId aUseExistingUniqueId = EDontUseExistingUniqueId);
	IMPORT_C void ServerLog(TPtrC& aMessage);
	IMPORT_C TBool IsClient() const;
	IMPORT_C CStreamStore* GetEmbeddedStore(TStreamId aId);
	IMPORT_C TStreamId SaveTodoListsL(TFileName aFileName) const;
	void ExternalizeTodoListListL(RWriteStream aWriteStream);
	void NextAlarmL(const TTime& aNow,CArrayFixFlat<TAgnSortInstance>* aAlarmedIds);
	void NextFewAlarmsL(const TTime& aNow,CArrayFixFlat<TAgnSortInstance>* aAlarmedIds,const TInt aMaxNumberOfAlarms,const TInt aMaxNumberOfDays);
	void NextAlarmForServerL(const TTime& aNow,CArrayFixFlat<TAgnSortInstance>* aAlarmedIds);
	void NextFewAlarmsForServerL(const TTime& aNow,CArrayFixFlat<TAgnSortInstance>* aAlarmedIds,const TInt aMaxNumberOfAlarms,const TInt aMaxNumberOfDays);
	TTime NextDayWithInstanceFromServer(const TTime& aToday, const TAgnFilter& aFilter,const TTime& aStartDate) const;
	TTime PreviousDayWithInstanceFromServer(const TTime& aToday, const TAgnFilter& aFilter,const TTime& aStartDate) const;
	inline CAgnModelStreamIdSet* ModelStreamIdSet() const;
	IMPORT_C void SetEntryServer(CAgnEntry* aEntry);
	IMPORT_C TBool CheckNotifier();
	IMPORT_C CAgnSortEntryAllocator* SortEntryAllocator();
	void DeleteIndex(TBool aDeleteModelIndex, TBool aDeleteUidIndex);
	IMPORT_C void DeleteLiteEntry(const CAgnSortEntry* aSortEntry);
	void CleanupLiteEntry(TAny* aPtr);
	IMPORT_C void UpdateDefaultEntryTimes();

	// VCal Support
	IMPORT_C void ImportVCalL(RReadStream& aReadStream, CArrayPtr<CAgnEntry>* aEntryArray);
	IMPORT_C void ExportVCalL(RWriteStream& aWriteStream, CAgnEntry* aEntry, const Versit::TVersitCharSet aCharSet = Versit::EUTF8CharSet);
	IMPORT_C void ExportVCalL(RWriteStream& aWriteStream, CArrayFixFlat<TAgnEntryId>* aEntryIdList, const Versit::TVersitCharSet aCharSet = Versit::EUTF8CharSet);

	// new connectivity requirements
	void GetEntryUidsSinceDateL(CArrayFix<TAgnUniqueId>* aUniqueIdList, const TAgnConnectivityFilter& aFilter, const TFileName& aFilterLibraryName);
	IMPORT_C TInt GenerateSyncUidL();
	IMPORT_C void SetLastSyncDateL(TInt aSyncUid, const TTime& aSyncDate);
	IMPORT_C TTime GetLastSyncDateL(TInt aSyncUid) const;
	IMPORT_C void GetFileIdL(TInt64& aFileId) const;
	IMPORT_C void UpdateVCalL(RReadStream& aReadStream, TInt& aNumFailedToImport);
protected: 
	enum TActiveAction {ENone,ESaveAs,ECompact}; 
	void virtual Reset();		
	inline CAgnEntryModel(MAgnModelStateCallBack* aStateCallBack);
	void ConstructL();
	void DoOpenL(CStreamStore& aStore, TStreamId aId);
	TAgnEntryId DoAddEntryL(CAgnEntry* aEntry,TAgnEntryId aTodoPositionReferenceId,TCommit aCommit,TUseExistingUniqueId aUseExistingUniqueId = EDontUseExistingUniqueId);
	void DoUpdateEntryL(CAgnEntry* aEntry,TAgnEntryId aTodoPositionReferenceId,TBool& aHadAlarm,TCommit aCommit);
	void DoDeleteEntryL(CAgnEntry* aEntry,TCommit aCommit);
	void DoChangeTodoOrderL(CAgnTodoList* aTodoList,TAgnEntryId aTodoId,TAgnEntryId aTodoPositionReferenceId);
//	inline CAgnModelStreamIdSet* ModelStreamIdSet() const;
	CAgnTodoList* CreateDefaultTodoListL(const TDesC& aTodoListName);
	inline CAgnTodoListList* TodoListList();
	inline const CAgnTodoListList* TodoListList() const;
	inline CAgnDeletedTodoListList* DeletedTodoListList();
	void UpdateTodoListListL();
	void UpdateDeletedTodoListListL();
	inline void RegisterIndex(CAgnSortEntryTable* aIndex);
	inline CAgnEntryStore* EntryStore(); 
	inline const CAgnEntryStore* EntryStore() const;
	inline const TAgnTodoListStore& TodoListStore() const;
	inline TAgnTodoListStore& TodoListStore();
	TAgnTodoListId DoAddTodoListL(CAgnTodoList* aTodoList,TInt aPosition);
	void DoUpdateTodoListL(CAgnTodoList* aTodoList);
	void DoDeleteTodoListL(CAgnTodoList* aTodoList);
	void DoChangeTodoListOrderL(TInt aOldPosition,TInt aNewPosition);
	TStreamId DoSaveTodoListsL(CStreamStore& aStoreToSaveTo);
	void UpdateNextUniqueEntryIdL();
	virtual TInt DoStepL(); // inherited from  MAgnActiveStep
	virtual void StepCompleted(TInt aError); // inherited from MAgnActiveStep
	void SetUpSaveAsL(CStreamStore& aStoreToSaveTo,TStreamId& aStreamIdOfOtherModel/*,const TDesC& aDefaultTodoListName*/);
	TInt DoSaveAsStepL();
	void SaveAsCompleted(TInt aError);
	void EnteringBlockedState(TInt aAction);
	void ExitingBlockedState(TState aState = EOk);
	void SetReplicatedEntryAsDeleted(CAgnEntry* aEntry);

	void ExternalizeEntryStoreL();
	CAgnEntry* FetchEntryFromServerL(TAgnEntryId aId) const;
	void PopulateMonthOfDayListsL(TAgnDate aStartDate,TAgnDate aEndDate,TAgnDate aToday,TAgnFilter& aFilter,CArrayFixFlat<TAgnSortInstance>** aDayList) const;
	void PopulateSymbolInstanceListFromDayListL(TAgnDate aToday,TAgnDate aStartDate,CAgnSymbolList* aList,CArrayFixFlat<TAgnSortInstance>** aDayList) const;
	void RefreshTodoListListL();
	void UpdateAlarmListL(CArrayFixFlat<TAgnSortInstance>* aAlarmedIds,CArrayFixFlat<TAgnSortInstance>* aDayInfoList,
										TAgnDate aCurrentDate, const TAgnDateTime& aNow,TAgnDateTime& aNextAlarm);
	void AddToAlarmListL(CArrayFixFlat<TAgnSortInstance>* aAlarmedIds,CArrayFixFlat<TAgnSortInstance>* aDayInfoList, const TAgnDateTime& aNow);
	void BuildTodoListsL();
protected:
	class TTodoListMapItem  
		{  
	public:	
		TAgnTodoListId	iOldId;
		TAgnTodoListId	iNewId;
		TBool			iTodoListCreated;
		}; 
	TInt									iActiveAction;
	MAgnModelStateCallBack*					iStateCallBack;
	MAgnProgressCallBack*					iProgressCallBack;
	CArrayFixFlat<TTodoListMapItem>*		iTodoListMap; 
	CAgnEntryModel*							iOtherModel;
	CAgnFileActive*							iActive;	
	TAgnEntryIter*							iEntryIter;	
	TBool									iThereAreEntriesToProcess;
	TInt									iNumStreamsProcessed; 
	TKeyArrayFix							iTodoListMapKey;
private:
	TState									iState;
	CAgnTodoListList*						iTodoListList;	
	CAgnDeletedTodoListList*				iDeletedTodoListList; 
	CAgnModelStreamIdSet*					iModelStreamIdSet;
	CAgnEntryStore* 						iEntryStore;  
	TAgnTodoListStore						iTodoListStore; 
	CStreamStore*							iStreamStore;
	CAgnSortEntryTable*						iRegisteredIndex;
	CAgnAlarm*								iRegisteredAlarm;
	TTimeIntervalMinutes					iDefaultEventDisplayTime;
	TTimeIntervalMinutes					iDefaultAnnivDisplayTime;
	TTimeIntervalMinutes					iDefaultDayNoteDisplayTime;
	CParaFormatLayer*						iParaFormatLayer;
	CCharFormatLayer*						iCharFormatLayer;
	MPictureFactory*						iPictureFactory;
	TUint									iNextUniqueIdValue;
	TSaveAsCallBackFrequency				iSaveAsCallBackFrequency;
	CAgnObsController*						iObserverController;
	TAgnUniqueId							iUniqueIdOfLastCutEntry;
	TAgnEntryId								iEntryIdOfLastCutEntry;

	// Temporary stuff for server index builder
	CAgnAppt*								iIndexBuildAppt;
	CAgnEvent*								iIndexBuildEvent;
	CAgnAnniv*								iIndexBuildAnniv;
	CAgnTodo*								iIndexBuildTodo;

	CAgnSortEntryTable*						iModelIndex;
	CAgnGlobalIdIndex*						iGlobalIdIndex;
	CAgnUniqueIdIndex*						iUniqueIdIndex;
	CAgnTodoListIdIndex*					iTodoListIdIndex;
	CAgnDeletedIndex*						iDeletedIndex;
	RAgendaServ*							iAgnServer;
	TModelMode								iMode; // Client, Server, None
private:
	IMPORT_C virtual void CAgnEntryModel_Reserved1();
	TAny* CAgnEntryModel_Reserved;
};


class CAgnIndexedModel : public CAgnEntryModel
//
// Model used to iterate through entries 
//
	{
public:
	enum TOpenCallBackFrequency {EOpenCallBackHigh=1,EOpenCallBackMedium=2,EOpenCallBackLow=4};
	enum TMergeCallBackFrequency {EMergeCallBackHigh=1,EMergeCallBackMedium=2,EMergeCallBackLow=4};
	enum TTidyByDateCallBackFrequency {ETidyByDateCallBackHigh=16,ETidyByDateCallBackMedium = 24,ETidyByDateCallBackLow=48}; 
	enum TTidyByTodoListCallBackFrequency {ETidyByTodoListCallBachHigh=1,ETidyByTodoListCallBackMedium=2,ETidyByTodoListCallBackHow=3};
	enum TMergeTodoListSettings {EMergeTodoListSettings,EDontMergeTodoListSettings};

	enum TTidyDirective		{
							EDelete,		// delete entries from the current model when tidying
							ECopy,			// copy entries to a file 
							ECopyAndDelete	// copy entries to a file and delete from current file
							};

	enum TTidyTodoListHow	{
							EAll,				// tidy all (todo) entries 
							ECrossedOut,		// tidy only crossed-out (todo) entries
							EExceptCrossedOut	// tidy all (todo) entries except crossed-out ones
							};
							
						
	IMPORT_C static CAgnIndexedModel* NewL(MAgnModelStateCallBack* aStateCallBack);
	IMPORT_C virtual ~CAgnIndexedModel();

	IMPORT_C TBool OpenL(CStreamStore& aStore,
						TStreamId aId,
						TTimeIntervalMinutes aDefaultEventDisplayTime,
						TTimeIntervalMinutes aDefaultAnnivDisplayTime,
						TTimeIntervalMinutes aDefaultDayNoteDisplayTime,
						MAgnProgressCallBack* aProgressCallBack,
						TBool aOpenSynchronously = EFalse,
						TOpenCallBackFrequency aCallBackFrequency = EOpenCallBackMedium); 

	IMPORT_C TBool OpenL(const TDesC& aFileName,
						TTimeIntervalMinutes aDefaultEventDisplayTime,
						TTimeIntervalMinutes aDefaultAnnivDisplayTime,
						TTimeIntervalMinutes aDefaultDayNoteDisplayTime,
						MAgnProgressCallBack* aProgressCallBack,
						TBool aOpenSynchronously = EFalse,
						TOpenCallBackFrequency aCallBackFrequency = EOpenCallBackMedium);

	IMPORT_C void OpenL(const TDesC& aFileName,
						TTimeIntervalMinutes aDefaultEventDisplayTime,
						TTimeIntervalMinutes aDefaultAnnivDisplayTime,
						TTimeIntervalMinutes aDefaultDayNoteDisplayTime);


	IMPORT_C TBool BuildIndexL(MAgnProgressCallBack* aProgressCallBack,
						TBool aOpenSynchronously = EFalse,
						TOpenCallBackFrequency aCallBackFrequency = EOpenCallBackMedium);


	IMPORT_C TBool MergeL(CStreamStore& aStoreToMergeFrom,
						TStreamId aSrcStreamId,
						MAgnProgressCallBack* aProgressCallBack,
						TMergeTodoListSettings aMergeSettings = EDontMergeTodoListSettings,
						TMergeCallBackFrequency aCallBackFrequency = EMergeCallBackHigh); 

	inline TBool TidyByDateL(const TAgnFilter& aFilter,
						const TTime& aTodaysDate,
						const TTime& aStartDate,
						const TTime& aEndDate,
						MAgnProgressCallBack* aProgressCallBack,
						TTidyDirective aDirective);

	inline TBool TidyByDateL(const TAgnFilter& aFilter,
						const TTime& aTodaysDate,
						const TTime& aStartDate,
						const TTime& aEndDate,
						MAgnProgressCallBack* aProgressCallBack,
						TTidyDirective aDirective,
						CStreamStore* aStoreToTidyTo);

	IMPORT_C TBool TidyByDateL(const TAgnFilter& aFilter,
						const TTime& aTodaysDate,
						const TTime& aStartDate,
						const TTime& aEndDate,
						MAgnProgressCallBack* aProgressCallBack,
						TTidyDirective aDirective,
						CStreamStore* aStoreToTidyTo,
						TStreamId& aStoreStreamId,
						TTidyByDateCallBackFrequency aCallBackFrequency = ETidyByDateCallBackMedium);

	inline TBool TidyByTodoListL(const CArrayFixFlat<TAgnTodoListId>* aList,
						MAgnProgressCallBack* aProgressCallBack,
						TTidyDirective aDirective,
						TTidyTodoListHow aTidyHow);

	inline TBool TidyByTodoListL(const CArrayFixFlat<TAgnTodoListId>* aList,
						MAgnProgressCallBack* aProgressCallBack,
						TTidyDirective aDirective,
						TTidyTodoListHow aTidyHow,
						CStreamStore* aStoreToTidyTo);

	IMPORT_C TBool TidyByTodoListL(const CArrayFixFlat<TAgnTodoListId>* aList,
						MAgnProgressCallBack* aProgressCallBack,
						TTidyDirective aDirective,
						TTidyTodoListHow aTidyHow,
						CStreamStore* aStoreToTidyTo,
						TStreamId& aStoreStreamId,
						TTidyByTodoListCallBackFrequency aCallBackFrequency = ETidyByTodoListCallBackMedium);

	IMPORT_C TInt EntryCount() const;
	IMPORT_C TAgnLiteEntry GetLiteEntryL(TAgnEntryId aId) const;
	IMPORT_C TInt IndexCount(TInt aIndexNumber) const;
	inline CAgnSortEntryTable* Indexes() const;	
protected:
	enum TIndexedActiveAction {ELoad=ECompact+1,EMerge=ECompact+2,ETidyByDate=ECompact+3,ETidyByTodoList=ECompact+4};

	inline CAgnIndexedModel(MAgnModelStateCallBack* aStateCallBack);
	void ConstructL();
	virtual TInt DoStepL(); 
	virtual void StepCompleted(TInt aError); 
	void virtual Reset();
private:
	TInt DoLoadStepL();
	void LoadCompleted(TInt aError);
	void SetUpMergeL(CStreamStore& aStoreToMergeFrom,TStreamId aSrcStreamId);
	TInt DoMergeStepL();
	void MergeEntriesStepL();
	void MergeTodoListsStepL();
	void MergeCompleted(TInt aError);
	TBool SetUpTidyByDateL(const TAgnFilter& aFilter,const TTime& aTodaysDate,CStreamStore* aStoreToTidyTo,TStreamId& aStoreStreamId,TTidyDirective aDirective/*,const TDesC& aDefaultTodoListName*/);
	TInt DoTidyByDateStepL();
	void TidyByDateCompleted(TInt aError);
	void DeleteTidiedEntriesL();
	TBool IsEntryValidToTidy(const CAgnSortEntry* aSortEntry);
	void SetUpTidyByTodoListL(CStreamStore* aStoreToTidyTo,TStreamId& aStoreStreamId,TTidyDirective aDirective/*,const TDesC& aDefaultTodoListName*/);
	TInt DoTidyByTodoListStepL();
	void TidyByTodoListCompleted(TInt aError);
	void TidyEntryL(CAgnSortEntry* aSortEntry,TAgnDate aStartDate,TAgnDate aEndDate);
	TBool CheckDateIteratorEnd(TAgnDate& aKey);
	IMPORT_C /*virtual*/ void CAgnEntryModel_Reserved1();
private:
	class TStreamIdKey : public TKeyArrayFix
		{
	public:
		inline TStreamIdKey(): TKeyArrayFix(0,ECmpTUint32){};
		virtual TInt Compare(TInt aLeft,TInt aRight) const;	
		};
	TOpenCallBackFrequency					iOpenCallBackFrequency;
	TMergeCallBackFrequency					iMergeCallBackFrequency;
	TInt									iTidyCallBackFrequency;
	CAgnSortEntryTable*						iIndexes;
	CAgnTodoListNames*						iTodoListNames;
	CArrayFixFlat<TAgnEntryId>*				iPossibleMergeMatches; 
	CArrayFixFlat<TAgnEntryId>*				iTidyDeleteArray; 
	CArrayFixFlat<TAgnEntryId>*				iAlreadyTidied;
	CArrayFixFlat<TAgnEntryId>*				iAlreadyTidiedForDay;
	TAgnEntryDateIterator*					iTidyIter;
	TAgnDate								iTidyStartDate;
	TAgnDate								iTidyEndDate;
	TAgnDate								iTidyDate;
	TAgnDate								iTodaysDate;
	TTidyDirective							iTidyDirective;
	TInt									iNumEntriesProcessed;
	TInt									iNumEntriesToProcess;
	TAgnEntryInfoFilter						iTidyInfoFilter;
	TInt									iTidyTodoListIndex;	
	TTidyTodoListHow						iTidyTodoListsHow;
	const CArrayFixFlat<TAgnTodoListId>*	iTidyTodoListIds;
	TMergeTodoListSettings					iMergeTodoListSettings;	
	CAgnAppt*								iAppt;
	CAgnEvent*								iEvent;
	CAgnAnniv*								iAnniv;
	CAgnTodo*								iTodo;
	};


class CAgnModel : public CAgnIndexedModel
//
// Full interface to an Agenda instance model
//
	{
public:
	IMPORT_C static CAgnModel* NewL(MAgnModelStateCallBack* aStateCallBack);

	IMPORT_C CAgnEntry* FetchInstanceL(const TAgnInstanceId& aInstanceId) const; // fetch an instance i.e. an entry with an instance date	
	IMPORT_C CAgnEntry* FetchInstanceLC(const TAgnInstanceId& aInstanceId) const;

	IMPORT_C TAgnEntryId AddEntryL(CAgnEntry* aEntry,TAgnEntryId aTodoPositionReferenceId = AgnModel::NullId());
	IMPORT_C TAgnEntryId UpdateInstanceL(CAgnEntry* aInstance,TAgnWhichInstances aWhichInstances=EAllInstances,TAgnEntryId aTodoPositionReferenceId = AgnModel::NullId()); 
	IMPORT_C TAgnEntryId DeleteInstanceL(CAgnEntry* aInstance,TAgnWhichInstances aWhichInstances=EAllInstances);	
	IMPORT_C TAgnEntryId DeleteInstanceL(const TAgnInstanceId& aInstanceId,TAgnWhichInstances aWhichInstances=EAllInstances);
	IMPORT_C TAgnEntryId CutInstanceL(const TAgnInstanceId& aInstanceId,TAgnWhichInstances aWhichInstances=EAllInstances);
	IMPORT_C TAgnEntryId CutInstanceL(CAgnEntry* aInstance,TAgnWhichInstances aWhichInstances=EAllInstances);


	IMPORT_C virtual TAgnTodoListId AddTodoListL(CAgnTodoList* aTodoList,TInt aPosition=EAddTodoListAtEnd);
	IMPORT_C virtual void DeleteTodoListL(CAgnTodoList* aTodoList);  
	IMPORT_C virtual void DeleteTodoListL(TAgnTodoListId aTodoListId);
	IMPORT_C virtual void UpdateTodoListL(CAgnTodoList* aTodoList);

	IMPORT_C void PopulateDayInstanceListL(CAgnDayList<TAgnInstanceId>* aList,const TAgnFilter& aFilter,const TTime& aTodaysDate) const;
	IMPORT_C void PopulateDayDateTimeInstanceListL(CAgnDayDateTimeInstanceList* aList,const TAgnFilter& aFilter,const TTime& aTodaysDate) const;
	IMPORT_C void PopulateMonthInstanceListL(CAgnMonthInstanceList* aList,const TAgnFilter& aFilter,const TTime& aTodaysDate) const;
	IMPORT_C void PopulateTodoInstanceListL(CAgnTodoInstanceList* aList,const TTime& aTodaysDate) const;
	IMPORT_C void PopulateSymbolInstanceListL(CAgnSymbolList* aList,const TAgnFilter& aFilter,const TTime& aTodaysDate) const;

	IMPORT_C TTime NextDayWithInstance(const TTime& aToday, const TAgnFilter& aFilter,const TTime& aStartDate) const;
	IMPORT_C TTime PreviousDayWithInstance(const TTime& aToday, const TAgnFilter& aFilter,const TTime& aStartDate) const;

	// Find methods
	IMPORT_C void FindNextInstanceL(CAgnDayList<TAgnInstanceId>* aMatchedInstanceList, const TDesC& aSearchText, const TTime& aStartDate, const TTime& aEndDate, const TAgnFilter& aFilter, const TTime& aToday) const;
	IMPORT_C void FindPreviousInstanceL(CAgnDayList<TAgnInstanceId>* aMatchedInstanceList, const TDesC& aSearchText, const TTime& aStartDate, const TTime& aEndDate, const TAgnFilter& aFilter, const TTime& aToday) const;
protected:
	void ConstructL();
	inline CAgnModel(MAgnModelStateCallBack* aStateCallBack);
	void NormaliseWhichInstances(const CAgnEntry* aInstance,TAgnWhichInstances& aWhichInstances) const;
	void PopulateSymbolInstanceListFromDayListL(TAgnDate aToday,TAgnDate aStartDate,CAgnSymbolList* aList,CArrayFixFlat<TAgnSortInstance>** aDayList) const;
	void PopulateMonthOfDayListsL(TAgnDate aStartDate,TAgnDate aEndDate,TAgnDate aToday,TAgnFilter& aFilter,CArrayFixFlat<TAgnSortInstance>** aDayList) const;
	virtual TInt DoStepL(); 
	virtual void StepCompleted(TInt aError); 
protected:
	TAgnInstanceEditor 	iInstanceEditor;
private:
	IMPORT_C /*virtual*/ void CAgnEntryModel_Reserved1();
	};


#include "agmmodel.inl"

#endif
