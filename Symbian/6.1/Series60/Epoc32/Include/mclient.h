// MCLIENT.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//

#if !defined(__MCLIENT_H__)
#define __MCLIENT_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

#if !defined(__MSVSTD_H__)
#include "msvstd.h"
#endif

#if !defined(__MSVIPC_H__)
#include "msvipc.h"
#endif

#if !defined(__MSVREG_H__)
#include "msvreg.h"
#endif


// Forward declarations
class CMsvClientEntry;

//**********************************
//RMsvSession
//**********************************
//
// NOTE most functions are exported for test purposes only
//

class RMsvServerSession : public RSessionBase, public MRegisteredMtmDllObserver
	{
public:
	IMPORT_C RMsvServerSession();
	IMPORT_C virtual ~RMsvServerSession();
	IMPORT_C TInt Connect(RFs& aFs);
	IMPORT_C TVersion Version() const;
	// Synchronous message
	IMPORT_C TInt GetEntry(TMsvId aId, TMsvId& aService, TMsvEntry& aEntry);
	IMPORT_C TInt GetChildren(TMsvId aId, CArrayPtrFlat<CMsvClientEntry>& aEntries, const TMsvSelectionOrdering& aOrdering);
	IMPORT_C TInt LockEntry(TMsvId aId);
	IMPORT_C TInt ReleaseEntry(TMsvId aId);
	IMPORT_C TInt ReadStore(TMsvId aId);
	IMPORT_C TInt LockStore(TMsvId aId);
	IMPORT_C TInt ReleaseStore(TMsvId aId);
	TInt DecStoreReaderCount(TMsvId aId);
	IMPORT_C TInt OperationProgress(TMsvOp aId, TDes8& aProgress);
	IMPORT_C TInt OperationCompletion(TMsvOp aId, TDes8& aProgress);
	IMPORT_C TInt CancelOperation(TMsvOp aId, TDes8& aProgress);
	IMPORT_C TInt CancelSessionEventRequest();
	IMPORT_C TInt OperationMtmL(TMsvId aId1, TMsvId aId2, TUid& aMtm, TMsvId& aService);
	IMPORT_C TInt LocalStoreDeleted(TMsvId aId);
	inline TInt OperationMtmL(TMsvId aId1, TUid& aMtm, TMsvId& aService);
	IMPORT_C void CreateEntryL(const TMsvEntry& aEntry, TMsvOp aOperationId);
	IMPORT_C void ChangeEntryL(const TMsvEntry& aEntry, TMsvOp aOperationId);
	IMPORT_C void MoveEntriesL(const CMsvEntrySelection& aSelection, TMsvId aTarget, TMsvOp aOperationId);
	IMPORT_C void CopyEntriesL(const CMsvEntrySelection& aSelection, TMsvId aTarget, TMsvOp aOperationId);
	IMPORT_C void DeleteEntriesL(const CMsvEntrySelection& aSelection, TMsvOp aOperationId);
	IMPORT_C void ChangeAttributesL(const CMsvEntrySelection& aSelection, TUint aSetAttributes, TUint aClearAttributes);
	IMPORT_C void GetChildIdsL(TMsvId aId, const CMsvEntryFilter& aFilter, CMsvEntrySelection& aSelection);
	TInt OutstandingOperationsL();
	// Asynchronous messages
	IMPORT_C void CreateEntryL(const TMsvEntry& aEntry, TMsvOp aOperationId, TRequestStatus& aRequestStatus);
	IMPORT_C void ChangeEntryL(const TMsvEntry& aEntry, TMsvOp aOperationId, TRequestStatus& aRequestStatus);
	IMPORT_C void DeleteEntriesL(const CMsvEntrySelection& aSelection, TMsvOp aOperationId, TRequestStatus& aRequestStatus);
	IMPORT_C void MoveEntriesL(const CMsvEntrySelection& aSelection, TMsvId aTarget, TMsvOp aOperationId, TRequestStatus& aRequestStatus);
	IMPORT_C void CopyEntriesL(const CMsvEntrySelection& aSelection, TMsvId aTarget, TMsvOp aOperationId, TRequestStatus& aRequestStatus);
	IMPORT_C void TransferCommandL(const CMsvEntrySelection& aSelection, TInt aCommandId, const TDesC8& aParameter, TMsvOp aOperationId, TRequestStatus& aStatus);
	IMPORT_C TInt TransferCommandL(const CMsvEntrySelection& aSelection, TInt aCommandId, const TDesC8& aParameter, TMsvOp aOperationId);
	IMPORT_C void QueueSessionEventRequest(TDesC8& aChange, TDesC8& aSequence, TRequestStatus& aRequestStatus);
	void ChangeDriveL(TInt aDrive, TMsvOp aOperationId, TRequestStatus& aRequestStatus);
	// MTM 
	IMPORT_C TInt FillRegisteredMtmDllArray(TUid aMtmDllTypeUid,CRegisteredMtmDllArray& aRegisteredMtmDllArray,TTimeIntervalMicroSeconds32 aTimeoutMicroSeconds32);  // Fill array with Dlls whose second uid is aMtmDllTypeUid
	IMPORT_C TInt InstallMtmGroup(const TDesC& aFullName);
	IMPORT_C TInt DeInstallMtmGroup(const TDesC& aFullName); 
	IMPORT_C TInt UseMtmGroup(TUid aMtmTypeUid);
	IMPORT_C TInt ReleaseMtmGroup(TUid aMtmTypeUid);  
	IMPORT_C CMtmGroupData* GetMtmGroupDataL(TUid aMtmTypeUid);  
	// Server
	IMPORT_C void CloseMessageServer();
	IMPORT_C void RemoveEntry(TMsvId aId);
	IMPORT_C TInt GetMessageDirectory(TDesC& aDirectory);
	TInt SetSessionAsObserver();
	TUint32 NotifySequenceL();
	IMPORT_C TInt GetMtmPath(const TUidType& aType, TDes& aName) const;
	IMPORT_C TInt SetMtmPath(const TUidType& aType, const TDesC& aName);
	IMPORT_C TInt DelMtmPath(const TUidType& aType);
	IMPORT_C TInt SetReceiveEntryEvents(TBool aReceive);
	// Services
	IMPORT_C TInt StopService(TMsvId aServiceId);
	IMPORT_C TBool ServiceActive(TMsvId aServiceId);
	IMPORT_C TInt ServiceProgress(TMsvId aServiceId, TDes8& aProgress);
	//
	IMPORT_C void SetFailure(TInt aType, TInt aArg1 = 0, TInt aArg2 = 0, TInt aArg3 = 0);

	TInt GetMessageDrive();
	//
private:
	void DoGetChildrenL(TMsvId aId, CArrayPtrFlat<CMsvClientEntry>& aEntries, const TMsvSelectionOrdering& aOrdering);
	void DoGetRemainingChildrenL(TPckgBuf<TMsvChildrenDetails>& aDetails, CArrayPtrFlat<CMsvClientEntry>& aEntries);
	void PackEntryIntoBufferL(const TMsvEntry& aEntry);
	void SendEntryDataL(TMsvOp aOperationId, const TMsvEntry& aEntry);
	void SendOperationDataL(TMsvOp aOperationId, const CMsvEntrySelection& aSelection, TInt aParameter1=0, TInt aParameter2=0);
	void SendCommandDataL(TMsvOp aOperationId, const CMsvEntrySelection& aSelection, TInt aCommand, const TDesC8& aParameter);
	void TestSlotAvailableL();
	void PackOperationDataL(const CMsvEntrySelection& aSelection, TInt aParameter1, TInt aParameter2);
	void DoGetEntryL(TMsvId aId, TMsvId& aService, TMsvEntry& aEntry);
	//
private:
	HBufC8* iBuffer;
	};

inline TInt RMsvServerSession::OperationMtmL(TMsvId aId1, TUid& aMtm, TMsvId& aService)
	{
	return OperationMtmL(aId1, aId1, aMtm, aService);
	}

#endif

