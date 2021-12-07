// AGCLIENT.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __AGCLIENT_H__
#define __AGCLIENT_H__

#pragma warning (disable: 4239)
#pragma warning (disable: 4706) // Assignment within conditional expression

#include <e32base.h>
#include <s32std.h>
#include <s32mem.h>

#include "agmmodel.h"
#include "agmcomon.h"
#include "agmtodos.h"
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
#include "agmextrc.h"
#include "agmxentr.h"
#include "agmsiter.h"
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

class CAgnModel;
class CAgnSyncIter;

enum TAgnClientPanic
	{
	ELockError =	-1,
	EBufferError =	-2,
	EStreamIdError =-3,
	EUnknownType =	-4,
	ENullEntry   =  -5,
	EBadModel	 =  -6,
	EServerDeath =  -7
	};

// Frequency that the server is asked if the UI needs to update (approx 5 secs)
const TUint KNotifierUpdateFrequency = 5000000;

//#define LOGGING

#ifdef LOGGING
#define LOGC(text) Log(_L(text));
#else
#define LOGC(x)
#endif

class TMaxAlarmsDays
	{
public:
	TInt	iMaxNumberOfAlarms;
	TInt	iMaxNumberOfDays;
	};

#define LINE {TBuf<20> _zout; _zout.AppendFormat(_L("Line: %d"),__LINE__); User::InfoPrint(_zout);}

class CAgnservNotifyActive : public CActive
	{
public:
	static CAgnservNotifyActive* NewL(RAgendaServ& aClient, TInt aFrequency);
	void ConstructL(RAgendaServ& aClient, TInt aFrequency);
	void BeginNotifier();
	void CancelRequest();
	~CAgnservNotifyActive();
private:
	inline CAgnservNotifyActive(TInt aPriority = EPriorityStandard) : CActive(aPriority){};
	void DoCancel();
	void RunL();
private:
	RAgendaServ* iClient;
	TInt iFrequency;
	TCallBack iUpdateCallback;	// callback to update the UI
	TBool iCancelled;
	CPeriodic*				iUpdateTimer;
	};


class RAgendaServ : public RSessionBase
	{
public:
	enum  TLock{EUnlocked, ELocked, EExclusive, EWriteOnly};
	enum TNotifyType {ENone, EEntry, ETodoList};
	enum TIndexType {EModelIndex = 0x01, EUidIndex = 0x02};
	// Server Connection functions
	IMPORT_C static RAgendaServ* NewL();
	IMPORT_C ~RAgendaServ();
	IMPORT_C TInt Connect();
	TVersion Version() const;

	IMPORT_C void OpenAgendaL(TDesC& aFileName);
	IMPORT_C void CloseAgenda();
	IMPORT_C void BuildIndex(TInt aIndex);

	// Server Utility functions
	IMPORT_C void Log(TPtrC& aMessage) const;
	void SetPictureFactory(MPictureFactory* aFactory);
	MPictureFactory* PictureFactory();
	TInt PercentageLoadedL(TBool aPause = EFalse);
	IMPORT_C TBool CompactFile();

	// Update Notification functions
	IMPORT_C void StartNotifierL(TInt aFrequency = KNotifierUpdateFrequency);
	IMPORT_C void StartNotifierL(TCallBack aCallback, TInt aFrequency = KNotifierUpdateFrequency);
	static TInt UpdateNotifier(TAny* aPtr);
	TInt DoUpdateNotifier();
	TNotifyType CheckNotifier();
	void SetNotifier(TRequestStatus& aStatus);

	// File / Stream Access functions
	TStreamId StreamId(TUid aUid);
	RReadStream& GetReadStreamL(TStreamId aStreamId);
	CEmbeddedStore* GetEmbeddedStoreL(TStreamId aStreamId);
	IMPORT_C TStreamId CreateNewStreamL(TUid aStreamUid);
	IMPORT_C RWriteStream& GetWriteStreamL(TStreamId aStreamId);
	IMPORT_C void CloseWriteStreamL();
	IMPORT_C TBool FileLoaded();
	IMPORT_C TBool FileIsReadOnly();

	// Entry Fetch / Update functions
	CAgnEntry* FetchEntryL(TAgnEntryId aId,CParaFormatLayer* aParaLayer, CCharFormatLayer* aCharLayer) const;
	CAgnEntry* FetchEntryL(TAgnGlobalId aId,CParaFormatLayer* aParaLayer, CCharFormatLayer* aCharLayer) const;
	CAgnEntry* FetchEntryL(TAgnUniqueId aId,CParaFormatLayer* aParaLayer, CCharFormatLayer* aCharLayer) const;
	TAgnLiteEntry GetLiteEntryL(TAgnEntryId aId, CAgnSortEntryAllocator* aAllocator) const;
	void UpdateEntryL(CAgnEntry *aEntry, TAgnEntryId aTodoPosition);
	TAgnEntryId AddEntryL(CAgnEntry *aEntry, TAgnEntryId aTodoPosition, TInt aCommit, TBool aUseExistingId);
	void DeleteEntryL(CAgnEntry *aEntry);

	// Entry Filter / Extraction functions
	void GetInstanceExtractorL(TAgnDate aToday, const TAgnFilter& aFilter) const;
	void GetDayListFromExtractorL(TAgnDate aDay, CArrayFixFlat<TAgnInstanceId>* aDayInfoList) const;
	IMPORT_C void GetDayDateTimeListFromExtractorL(TAgnDate aDay, CAgnDayDateTimeInstanceList* aDayInfoList) const;
	IMPORT_C void PopulateSymbolInstanceListL(CAgnSymbolList* aList,const TAgnFilter& aFilter,const TTime& aTodaysDate, CAgnEntryModel *aModel) const;

	// Model Utility functions
	void Commit();
	void Rollback();
	void SetParaAndCharFormatLayersL(const CParaFormatLayer* aParaFormatLayer,
														const CCharFormatLayer* aCharFormatLayer);
	void GetModelTextFormattingL(CParaFormatLayer* aParaFormatLayer, CCharFormatLayer* aCharFormatLayer);
	void NextAlarmL(const TTime& aNow,CArrayFixFlat<TAgnSortInstance>* aAlarmedIds,CAgnSortEntryAllocator* aAllocator);
	void NextFewAlarmsL(const TTime& aNow,CArrayFixFlat<TAgnSortInstance>* aAlarmedIds,CAgnSortEntryAllocator* aAllocator,const TInt aMaxNumberOfAlarms,const TInt aMaxNumberOfDays);
	TTime PreviousDayWithInstance(const TTime& aToday, const TAgnFilter& aFilter,const TTime& aStartDate) const;
	TTime NextDayWithInstance(const TTime& aToday, const TAgnFilter& aFilter,const TTime& aStartDate) const;
	void SetLastSynchronizedDateL(const TTime& aTime) const;
	TTime LastSynchronizedDateL() const;
	TStreamId GetObserverControllerStreamId();

	IMPORT_C CAgnEntry::TType TypeByUniqueId(TAgnUniqueId aUniqueId);
	IMPORT_C TBool HasUniqueIdBeenDeleted(TAgnUniqueId aUniqueId);
	IMPORT_C TAgnDateTime UniqueIdLastChangedDate(TAgnUniqueId aUniqueId);
	IMPORT_C TAgnUniqueId GetUniqueId(TAgnEntryId aEntryId);
	IMPORT_C TAgnUniqueId GetUniqueId(TAgnTodoListId aTodoId);
	IMPORT_C TInt DeleteEntry(TAgnUniqueId aUid);
	IMPORT_C TInt DeleteTodoList(TAgnUniqueId aUid);


	// ToDo List functions
	CAgnTodoList* FetchTodoListL(TAgnTodoListId aId);
	CAgnTodoList* FetchTodoListL(TAgnUniqueId aId);
	TStreamId SaveTodoListsL(TFileName aFileName);
	void RefreshTodoListListL(CAgnTodoListList* aTodoListList, CAgnDeletedTodoListList* aDeletedTodoListList);
	void UpdateTodoListL(CAgnTodoList* aTodoList);
	TAgnTodoListId AddTodoListL(CAgnTodoList* aTodoList, TInt aPosition);
	void DeleteTodoListL(CAgnTodoList* aTodoList);
	void ChangeTodoListOrder(TInt aOldPosition, TInt aNewPosition);

	// Entry / Date Iterator functions
	IMPORT_C TBool CreateEntryIterator();
	IMPORT_C TBool EntryIteratorNext();
	IMPORT_C TAgnEntryId EntryIteratorPosition();
	IMPORT_C TInt EntryIteratorStreamCount();
	IMPORT_C TInt EntryIteratorStreamCurrent();

	IMPORT_C void CreateDateIterator(TTime aToday, TAgnFilter* aFilter, TAgnDate aTidyStartDate);
	void CreateDateIteratorL(TTime aToday, TAgnFilter* aFilter, TAgnDate aTidyStartDate);
	IMPORT_C void DateIteratorPrevious();
	IMPORT_C void DateIteratorNext();
	IMPORT_C TBool DateIteratorAtStart();
	IMPORT_C TBool DateIteratorAtEnd();
	IMPORT_C TAgnDate DateIteratorCurrentKey();
	IMPORT_C CAgnSortEntry* DateIteratorCurrentElement(CAgnSortEntryAllocator* aAllocator);
	IMPORT_C void DateIteratorGoto(TAgnDate aDate);
	IMPORT_C void DateIteratorGotoLessOrEqual(TAgnDate aDate);
	void UpdateSyncIterL(CAgnSyncIter& aIter);
	void GetNumEntriesToTidyL(TAgnDate aStartDate, TAgnDate aEndDate, TInt& aNumEntries, TInt& aNumTodos);
	void SetDefaultDisplayTimes(TTimeIntervalMinutes aDefaultEventDisplayTime,
										  TTimeIntervalMinutes aDefaultAnnivDisplayTime,
										  TTimeIntervalMinutes aDefaultDayNoteDisplayTime);

	TInt EntryCount();
	TInt IndexCount(TInt aIndex);
	IMPORT_C void WaitUntilLoaded();
	void SetBufferedStoring(TInt aSetting);
	TInt BufferedStoring();
	void SetBufferedDeleting(TInt aSetting);
	TInt BufferedDeleting();
	void Flush();
	void CommitAndCompact();
	// new connectivity sync functionality
	IMPORT_C void DecEntryRefCountL(const TAgnUniqueId aUniqueId);
	IMPORT_C void IncEntryRefCountL(const TAgnUniqueId aUniqueId);
	IMPORT_C void DecEntryRefCountsL(const CArrayFix<TAgnUniqueId>& aListOfUniqueIds);
	IMPORT_C void IncEntryRefCountsL(const CArrayFix<TAgnUniqueId>& aListOfUniqueIds);
	IMPORT_C void GetEntryUidsSinceDateL(CArrayFix<TAgnUniqueId>& aUids, const TAgnConnectivityFilter& aFilter, const TFileName& aFilterLibrary=KAgnDefaultFilter());
	IMPORT_C TInt FreeSpaceAvailable() const;
	IMPORT_C void StartCompactionL();
	IMPORT_C void StopCompactionL();
	TInt GenerateSyncUidL();
	void SetLastSyncDateL(TInt aSyncUid, const TTime& aSyncDate);
	TTime GetLastSyncDateL(TInt aSyncUid) const;
	void GetFileIdL(TInt64& aFileId) const;
	IMPORT_C TAgnEntryId GetEntryId(TAgnUniqueId aUniqueId);
private:
	RAgendaServ();	// private constructor
	void Panic(TAgnClientPanic aPanic) const;
	TInt DoConnect();
	TInt ServerRequestL(TInt aCommand, TAny* aArg1 = NULL, TAny* aArg2 = NULL, TAny* aArg3 = NULL, TAny* aArg4 = NULL) const;
	CBufFlat* CreateTransmitBufferL(TInt aBufferSize) const;
	RReadStream& GetEmbeddedReadStreamL(TStreamId aStreamId);

	
	void ExternalizeFilterL(const TAgnFilter& aFilter, RWriteStream& aStream) const;
	CAgnSortEntry* InternalizeSortEntryL(RReadStream& aStream, CAgnSortEntryAllocator* aAllocator) const;
	void LogMemoryUsage();
	CEmbeddedStore* OpenEmbeddedStoreL(TStreamId aStreamId);
	CAgnTodoList* ReadTodoListL(TInt aBufferSize);
	CBufBase* WriteTodoListLC(const CAgnTodoList& aTodoList);
	CAgnEntry* ReadEntryFromServerSession(CParaFormatLayer* aParaLayer, CCharFormatLayer* aCharLayer, TInt aBufferSize) const;
private:
	TFileName				iFileName;
	TBool					iIsReadOnly;
	TBool					iIsLoaded;
	CBufFlat*				iBuffer;
	MPictureFactory*		iPictureFactory;
	TNotifyType				iUpdateStatus;
	CAgnservNotifyActive*	iNotifier;
	TCallBack				iUiCallback;	// callback to notify the UI
	TBool					iUiCallbackInstalled;


	// The cached stream is used for caching read and write streams
	// to/from the server. 

	// The embedded stream is used to keep a copy of the data being
	// read from an embedded object, and may have a longer lifespan
	// than the last stream read.

	TStreamId				iCachedStreamId;	// id of the currently cached stream
	CBufFlat*				iCachedStream;
	RBufReadStream*			iCachedReadStream;
	RBufWriteStream*		iWriteStream;

	TStreamId				iEmbeddedStreamId;
	CBufFlat*				iEmbeddedStream;
	RBufReadStream*			iEmbeddedReadStream;
	CEmbeddedStore*			iEmbeddedStore;
	};





#endif
