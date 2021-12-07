// MSVAPI.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//

#ifdef _DEBUG
#undef _NO_SESSION_LOGGING_
#endif

#if !defined(__MSVAPI_H__)
#define __MSVAPI_H__

#include <e32base.h>
#include <s32file.h>
#include <flogger.h>

#include "msvstd.h"
#include "msvstore.h"
#include "msvipc.h"
#include "msvarray.h"
#include "mclient.h"

// Forward declarations
class CMsvSession;
class CMsvEntry;
class CBaseMtm;
class CMsvClientEntry;
class CMsvEntryArray;
class CMsvServer;

// Remove these to remove client logging
//#define _NO_SESSION_LOGGING_
#define _NO_SESSION_LOGGING_SERIAL_

// Single export used to start the message server
IMPORT_C TInt StartMessageServer(TAny*);

// Create Message Server and return a server entry owned by caller
// This is all that is required to test server Mtm's
IMPORT_C CServer* CreateMessageServerL(CMsvServerEntry*& aServerEntry);

//**********************************
// CMsvOperation
//**********************************
//
// Abstract base class for operations controlling asynchronous functions
//

class CMsvOperation : public CActive
	{
public:
	IMPORT_C CMsvOperation(CMsvSession& aMsvSession, TInt aPriority, TRequestStatus& aObserverRequestStatus);
	IMPORT_C ~CMsvOperation();
	virtual const TDesC8& ProgressL()=0;
	IMPORT_C virtual const TDesC8& FinalProgress();
	IMPORT_C virtual TUid Mtm() const;
	//
	inline TMsvOp Id() const;
	inline TMsvId Service() const;
	//
protected:
	TMsvId iService;
	TUid iMtm;
	TRequestStatus& iObserverRequestStatus;
	CMsvSession& iMsvSession;
private:
	TMsvOp iId;
	};


//**********************************
// CMsvOperationWait
//**********************************
//
// Allows a synchronous wait on a operation
//

class CMsvOperationWait: public CActive
	{
public:
	IMPORT_C static CMsvOperationWait* NewLC(TInt aPriority=EPriorityStandard);
	IMPORT_C ~CMsvOperationWait();
	IMPORT_C void Start();
protected:
	CMsvOperationWait(TInt aPriority);
	void RunL();
	void DoCancel();
	};


//**********************************
// CMsvCompletedOperation
//**********************************
//
// An operation which is already completed on construction
//

class CMsvCompletedOperation : public CMsvOperation
	{
public:
	IMPORT_C static CMsvCompletedOperation* NewL(CMsvSession& aMsvSession, TUid aMtm, const TDesC8& aProgress, TMsvId aService, TRequestStatus& aObserverRequestStatus, TInt aErr=KErrNone);
	IMPORT_C ~CMsvCompletedOperation();
	//
	const TDesC8& ProgressL();
	const TDesC8& FinalProgress();
private:
	CMsvCompletedOperation(CMsvSession& aSession, TRequestStatus& aObserverRequestStatus);
	void ConstructL(TUid aMtm, TInt aError, const TDesC8& aProgress, TMsvId aService);
	// from CActive
	void DoCancel();
	void RunL();
	//
private:
	HBufC8* iProgress;
	};


//**********************************
// MMsvSessionObserver
//**********************************
//
// 
//

class MMsvSessionObserver
	{
public:
	enum TMsvSessionEvent { EMsvEntriesCreated,
							EMsvEntriesChanged,
							EMsvEntriesDeleted,
							EMsvEntriesMoved,
							EMsvMtmGroupInstalled,
							EMsvMtmGroupDeInstalled,
							EMsvGeneralError,
							EMsvCloseSession,
							EMsvServerReady,
							EMsvServerFailedToStart,
							EMsvCorruptedIndexRebuilt,
							EMsvServerTerminated,
							EMsvMediaChanged, // I assume the following four are in sequential order
							EMsvMediaUnavailable,
							EMsvMediaAvailable,
							EMsvMediaIncorrect,
							EMsvCorruptedIndexRebuilding
							};
public: 
	virtual void HandleSessionEventL(TMsvSessionEvent aEvent, TAny* aArg1, TAny* aArg2, TAny* aArg3)=0;
	};

//**********************************
// CMsvSession
//**********************************
//
// 
//

const TInt KMsvSessionObserverGranularity=4;  //???

class CMsvSession: public CActive
	{
public: 
	IMPORT_C static CMsvSession* OpenSyncL(MMsvSessionObserver& aObserver);
	IMPORT_C static CMsvSession* OpenAsyncL(MMsvSessionObserver& aObserver);
	IMPORT_C static CMsvSession* OpenAsObserverL(MMsvSessionObserver& aObserver);
	~CMsvSession();
	// --- Observer functions ---
	IMPORT_C void AddObserverL(MMsvSessionObserver& aObserver);
	IMPORT_C void RemoveObserver(MMsvSessionObserver& aObserver);
	IMPORT_C TInt SetReceiveEntryEvents(TBool aReceive);
	// --- Utility functions ---
	inline CMsvEntry* GetEntryL(TMsvId aEntId);
	inline TInt GetEntry(TMsvId aId, TMsvId& aService, TMsvEntry& aEntry);
	IMPORT_C CMsvOperation* TransferCommandL(const CMsvEntrySelection& aSelection, TInt aCommandId, const TDesC8& aParameter, TRequestStatus& aStatus);
	IMPORT_C void TransferCommandL(const CMsvEntrySelection& aSelection, TInt aCommandId, const TDesC8& aParameter, TDes8& aProgress);
	IMPORT_C void IncPcSyncCountL(const CMsvEntrySelection& aSelection);
	IMPORT_C void DecPcSyncCountL(const CMsvEntrySelection& aSelection);
	IMPORT_C void GetChildIdsL(TMsvId aId, const CMsvEntryFilter& aFilter, CMsvEntrySelection& aSelection);
	IMPORT_C void ChangeAttributesL(const CMsvEntrySelection& aSelection, TUint aSetAttributes, TUint aClearAttributes);
	IMPORT_C CMsvOperation* ChangeDriveL(TInt aDrive, TRequestStatus& aStatus);
	IMPORT_C TInt OutstandingOperationsL();
	// --- cleanup functions
	IMPORT_C static void CleanupEntry(TAny* aPtr);
	IMPORT_C void CleanupEntryPushL(TMsvId aId);
	IMPORT_C void CleanupEntryPop(TInt aCount=1);
	inline void RemoveEntry(TMsvId aId);
	/// MTM functions
	inline TInt InstallMtmGroup(const TDesC& aFullName);
	inline TInt DeInstallMtmGroup(const TDesC& aFullName); 
	//
	inline TInt StopService(TMsvId aServiceId);
	inline TBool ServiceActive(TMsvId aServiceId);
	inline TInt ServiceProgress(TMsvId aServiceId, TDes8& aProgress);
	//
	inline void CloseMessageServer();
	inline RFs& FileSession();
	//
protected:
	CMsvSession(MMsvSessionObserver& aObserver);
	void ConstructL(TBool aSyncOpening);
	void ConstructAsObserverL();
	//
	// used by friends
	inline TInt OperationId();
	inline RMsvServerSession& Session();
	void CheckDrive();
	//
	// from CActive
	void RunL();
	void DoCancel();
	//
private:
	void NotifyAllObserversL(MMsvSessionObserver::TMsvSessionEvent aEvent, TAny* aArg1, TAny* aArg2, TAny* aArg3);
	void CleanupEntryDelete();
  	void DoRunL(TMsvNotifBuffer& aBuffer);
 	void HandleNotifyL();
 	void DoHandleNotifyL(TMsvNotifBuffer& aBuffer);
	void GetMessageFolderL();
	//
private:
	TInt iOperationId;
	RFs	iFs;
	RMsvServerSession iSession;
	TMsvNotifBuffer iChange;	
	MMsvSessionObserver&	iMainObserver;
	CArrayPtrFlat<MMsvSessionObserver>* iObservers;
	CMsvEntrySelection* iCleanupList;
	TInt iSyncStart;
	HBufC* iMessageFolder;
	TDriveNumber iDrive;
	CMsvEntrySelection* iNotifSelection;
	TPckgBuf<TUint32> iSequenceBuf;
	TUint32 iNotifySequence;
	TBool iReceiveEntryEvents;
	//
#ifndef _NO_SESSION_LOGGING_
	void CreateSessionLogL();
	void Log(TRefByValue<const TDesC> aFmt, ...);
	mutable RFileLogger iLog;
#endif
	//
friend class CSendAs;
friend class CMsvEntry;
friend class CMsvOperation;
friend class CMsvEntryOperation;
friend class CObserverRegistry;
	//
	};




//**********************************
// MMsvEntryObserver
//**********************************
//
// 
//

class MMsvEntryObserver
	{
public:
	enum TMsvEntryEvent {	EMsvEntryChanged,
							EMsvNewChildren,
							EMsvDeletedChildren,
							EMsvChildrenChanged,
							EMsvEntryDeleted,
							EMsvContextInvalid,
							EMsvChildrenMissing,
							EMsvChildrenInvalid,
							EMsvEntryMoved};
public: 
	virtual void HandleEntryEventL(TMsvEntryEvent aEvent, TAny* aArg1, TAny* aArg2, TAny* aArg3)=0;
	};


//**********************************
// CMsvEntry
//**********************************
//
// 
//

class CMsvEntry: public CBase, public MMsvSessionObserver, public MMsvStoreObserver
	{
public: // Public member functions
	IMPORT_C static CMsvEntry* NewL(CMsvSession& aMsvSession, TMsvId aMsvId, const TMsvSelectionOrdering& aOrdering);
	IMPORT_C ~CMsvEntry();
	//
	// --- Observer functions ---
	IMPORT_C void AddObserverL(MMsvEntryObserver& aObserver);
	IMPORT_C void RemoveObserver(MMsvEntryObserver& aObserver);
	//
	// --- Accessor for associated session ---
	inline CMsvSession& Session(); 
	//
	// --- Accessors the associated message store ---
	IMPORT_C CMsvStore* ReadStoreL();
	IMPORT_C CMsvStore* EditStoreL();
	//
	// --- Synchronous Current Entry functions ---
	inline TMsvId EntryId() const; 
	inline const TMsvEntry& Entry() const; 
	inline const TMsvSelectionOrdering& SortType() const;
	inline TMsvId OwningService() const;
	IMPORT_C void SetSortTypeL(const TMsvSelectionOrdering& aSortType);
	IMPORT_C void SetMtmListL(const CArrayFix<TUid>& aMtmList);
	IMPORT_C void SetEntryL(TMsvId aMsvId);
	IMPORT_C void ChangeL(const TMsvEntry& aEntry);
	//
	// for binary files associated with an entry
	IMPORT_C TInt GetFilePath(TFileName& aDirectory) const;
	//
	// --- Asynchronous Current Entry functions ---
	IMPORT_C CMsvOperation* ChangeL(const TMsvEntry& aEntry, TRequestStatus& aStatus);
	//
	// --- Asynchronous Child Entry functions ---
	IMPORT_C CMsvOperation* CreateL(const TMsvEntry& aEntry, TRequestStatus& aStatus);
	IMPORT_C CMsvOperation* DeleteL(const CMsvEntrySelection& aSelection, TRequestStatus& aStatus);
	IMPORT_C CMsvOperation* DeleteL(TMsvId aMsvId, TRequestStatus& aStatus);
	IMPORT_C CMsvOperation* CopyL(const CMsvEntrySelection& aSelection, TMsvId aTargetId, TRequestStatus& aStatus);
	IMPORT_C CMsvOperation* CopyL(TMsvId aMsvId, TMsvId aTargetId, TRequestStatus& aStatus);
	IMPORT_C CMsvOperation* MoveL(const CMsvEntrySelection& aSelection, TMsvId aTargetId, TRequestStatus& aStatus);
	IMPORT_C CMsvOperation* MoveL(TMsvId aMsvId, TMsvId aTargetId, TRequestStatus& aStatus);
	//
	// --- Synchronous Child Entry functions ---
	IMPORT_C CMsvEntrySelection* ChildrenL() const;
	IMPORT_C CMsvEntrySelection* ChildrenWithServiceL(TMsvId aServiceId) const;
	IMPORT_C CMsvEntrySelection* ChildrenWithMtmL(TUid aMtm) const;
	IMPORT_C CMsvEntrySelection* ChildrenWithTypeL(TUid aEntryType) const;
	inline TInt Count() const;
	IMPORT_C const TMsvEntry& ChildDataL(TMsvId aMsvId) const;
	IMPORT_C const TMsvEntry& operator[](TInt aIndex) const;
	IMPORT_C CMsvEntry* ChildEntryL(TMsvId aMsvId) const;
	IMPORT_C void MoveL(TMsvId aMsvId, TMsvId aTargetId);
	IMPORT_C void MoveL(const CMsvEntrySelection& aSelection, TMsvId aTargetId, TMsvLocalOperationProgress& aProgress);
	IMPORT_C void CopyL(const CMsvEntrySelection& aSelection, TMsvId aTargetId, TMsvLocalOperationProgress& aProgress);
	IMPORT_C void CopyL(TMsvId aMsvId, TMsvId aTargetId);


	IMPORT_C void CreateL(TMsvEntry& aEntry);
	IMPORT_C void DeleteL(TMsvId aId);
	IMPORT_C void DeleteL(const CMsvEntrySelection& aSelection, TMsvLocalOperationProgress& aProgress);
	IMPORT_C void ChangeAttributesL(const CMsvEntrySelection& aSelection, TUint aSetAttributes, TUint aClearAttributes);
	//
	// from MMsvSessionObserver
	void HandleSessionEventL(TMsvSessionEvent aEvent, TAny* aArg1, TAny* aArg2, TAny* aArg3);
	// From MMsvStoreObserver
	void HandleStoreEvent(TMsvStoreEvent aEvent, TMsvId aId);
	//
	IMPORT_C TBool HasDirectoryL() const;
	IMPORT_C TBool HasStoreL() const;
	//
private: // Private members
	CMsvEntry(CMsvSession& aMsvSession, const TMsvSelectionOrdering& aOrdering);
	void ConstructL(TMsvId aMsvId);
	//
	void NotifyAllObserversL(MMsvEntryObserver::TMsvEntryEvent aEvent, TAny* aArg1, TAny* aArg2, TAny* aArg3);
	void ContextChangedL(MMsvEntryObserver::TMsvEntryEvent aEvent);
	void NewChildrenL(const CMsvEntrySelection& aSelection);
	CMsvEntrySelection* DoGetNewChildrenL(const CMsvEntrySelection& aSelection);
	void DeletedChildrenL(const CMsvEntrySelection& aSelection);
	void ChildrenChangedL(const CMsvEntrySelection& aSelection);
	void CheckNewGrandchildrenL(TMsvId aId);
	void CheckDeletedGrandchildrenL(TMsvId aId);
	void NotifyChildChangedL(TMsvId aId);
	CMsvEntrySelection* DoMakeSelectionL(TMsvId aId);
	void CheckIfContextMovedL(const CMsvEntrySelection& aSelection);
	//
	TBool IsAChild(TMsvId aId) const;
	TBool AreChildren(const CMsvEntrySelection& aSelection) const;
	//
	CMsvOperation* DoDeleteL(const CMsvEntrySelection& aSelection, TRequestStatus& aStatus);
	CMsvClientEntry* DoGetEntryLC(TMsvId aId, TMsvId& aOwningService);
	void DoGetChildrenL();
	CMsvEntryArray* GetNewSortedListL(const TMsvSelectionOrdering& aOrdering, const CArrayFix<TUid>& aMtmList);
	void DoSortTypeL(CMsvClientEntry* aContext);
	void ReplaceChildL(TInt pos, const TMsvEntry& aEntry);
	void DeleteChild(TInt aPosition);
	void HandleMediaChangeL();

	TInt MoveOneL(TMsvId aMsvId, TMsvId aTargetId);
	TInt CopyOneL(TMsvId aMsvId, TMsvId aTargetId);
	TInt DeleteOneL(TMsvId aMsvId);
	//
private:
	enum TEntryState {	EValid,
						EInvalidChangingContext,
						EInvalidDeletedContext,
						EInvalidOldContext,
						EInvalidMissingChildren};
	//
#ifndef _NO_SESSION_LOGGING_
	void Log(TRefByValue<const TDesC> aFmt, ...);
#endif
	//
private:
	TBool iOberserverAdded;
	TEntryState	iState;
	CMsvSession& iMsvSession;
	TMsvSelectionOrdering iOrdering;
	const TMsvEntry* iEntryPtr;
	CArrayPtrFlat<MMsvEntryObserver>* iObservers;
	CArrayPtrFlat<CMsvClientEntry>* iEntries;
	CMsvEntryArray* iSortedChildren;
	CMsvStore* iStore;
	CArrayFixFlat<TUid>* iMtmList;
	TMsvId iOwningService;
	TUint32 iNotifySequence;
	};

//**********************************
// MessageServer
//**********************************
//
// 
//

class MessageServer
	{
public:
	IMPORT_C static TVersion Version();
	IMPORT_C static TMsvId NullUidValue();
	//
	IMPORT_C static TBool DriveContainsStore(RFs& aFs, TInt aDrive);
	IMPORT_C static TInt CurrentDriveL(RFs& aFs);
	};

//**********************************
// MtmClientUtils
//**********************************
//
// 
//

class McliUtils
    {
public:
    IMPORT_C static TMsvLocalOperationProgress GetLocalProgressL(CMsvOperation& aOperation);
    IMPORT_C static TMsvLocalOperationProgress GetFinalLocalProgress(CMsvOperation& aOperation);
    };

#include "msvapi.inl"

#endif
