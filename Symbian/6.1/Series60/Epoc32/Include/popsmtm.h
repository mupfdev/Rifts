// POPSMTM.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved. 
// 

#if !defined(__POPSMTM_H__)
#define __POPSMTM_H__



#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

#include "msvstd.h"
#include <mtsr.h>
#include <offop.h>

#include "pops.h"
#include "popsmbx.h"

//////////////////////////////////////

enum TPopsMtmState
	{
	EPopConnecting,
	EPopRefreshing,
	EPopCopying,
	EPopMoving,
	EPopDeleting,
	EPopQuitting,
	EPopTidying,
	EPopConnectedAndIdle,
	EPopDisconnected,
	EPopPopulating,
	EPopAddingOfflineOp,
	EPopFindingFirstOfflineOp,
	EPopCancellingOfflineOps
	};

//**********************************
// CImppServerMtm
//**********************************
// 
// POP3 server MTM

// package buffer for progress info.
typedef TPckgBuf<TPop3Progress> TPop3ProgressBuf;

#define KImPopsMTMResourcePath _L("c:\\system\\data\\imcv.r01")

//
// Forward declarations
class CImPop3Settings;
class CImOffLineOperation;
class CImPop3OfflineOperationFinder;
class CImPop3SetOfflineOps;
class CImLogMessage;
//
//

class CImppServerMtm : public CBaseServerMtm
{
public:
	IMPORT_C static CImppServerMtm* NewL(CRegisteredMtmDll& aPopServerMtmDll,
												  CMsvServerEntry* aEntry);
	~CImppServerMtm();
	//
	void CopyFromLocalL(const CMsvEntrySelection& aSelection, TMsvId aDestination, TRequestStatus& aStatus);
	void CopyToLocalL(const CMsvEntrySelection& aSelection, TMsvId aDestination, TRequestStatus& aStatus);
	void CopyWithinServiceL(const CMsvEntrySelection& aSelection,TMsvId aDestination, TRequestStatus& aStatus);
	void DeleteAllL(const CMsvEntrySelection& aSelection, TRequestStatus& aStatus);
	void CreateL(TMsvEntry aNewEntry, TRequestStatus& aStatus);
	void ChangeL(TMsvEntry aNewEntry, TRequestStatus& aStatus);
	//
	void StartCommandL(CMsvEntrySelection& aSelection, TInt aCommand, const TDesC8& aParameter, TRequestStatus& aStatus);
	//
	const TDesC8& Progress();

	TBool CommandExpected();
	//
	void MoveToLocalL(const CMsvEntrySelection& aSelection,TMsvId aDestination, TRequestStatus& aStatus);
	void MoveFromLocalL(const CMsvEntrySelection& aSelection,TMsvId aDestination, TRequestStatus& aStatus);
	void MoveWithinServiceL(const CMsvEntrySelection& aSelection,TMsvId aDestination, TRequestStatus& aStatus);

private:
	enum TImppCopyMethod
		{
		EImppCopy,
		EImppMove,
		EImppPopulate
		};

	CImppServerMtm(CRegisteredMtmDll& aPopServerMtmDll, CMsvServerEntry* aEntry);
	void ConstructL();

	void DoCancel();
	void DoRunL();
	void DoComplete(TInt aError);

	void DoConnectL(TRequestStatus& aStatus);
	void DoRefreshL();
	void DoCopyMoveL(const CMsvEntrySelection& aSelection, TMsvId aDestination, TRequestStatus& aStatus, TImppCopyMethod aCopyMethod);
	void DoQuitL(TRequestStatus& aStatus);

	void GetPopDetailsL(const CMsvEntrySelection& aSel);
	void QueueRemoteCleanup();  // tidy up if anything goes wrong with refresh

	void ResetProgress();

    //  Called from DoRun() sets TMsvEntry visible flag for each POP3 child. 
    void DoShowMessagesL( TBool aHide);
	void CommandComplete( TInt aErrorCode );
	CMsvEntrySelection* StripInvalidEntriesLC(const CMsvEntrySelection& aSelection) const;
	void FindFirstOfflineOperation(TBool aQuitting);
	inline void RunOfflineOperationL();
	inline TBool AcceptingOfflineOperations(const CMsvEntrySelection& aSelection);
	void AddOfflineOperationL(const CMsvEntrySelection& aSelection, TMsvId aDestination, CImOffLineOperation::TOffLineOpType aOperationType, TRequestStatus& aStatus);
	void CancelOfflineOperationsL(const CMsvEntrySelection& aSelection, TRequestStatus& aStatus);

	TBool PruneMessages(const CMsvEntrySelection& aSelection, TRequestStatus& aStatus);

private:

	struct TImPop3Status
		{
		TBool			iQuitting;
		TBool			iRunningOfflineOperations;
		TPopsMtmState	iCurrentOperation;
		TPopsMtmState	iLastCurrentOperation;
		};

	TImPop3Status				iState;

	CImPop3Session*				iPopSession;
	CImPop3RefreshMailBox*		iPopRefreshMailbox;
	CImPop3CopyMove*			iPopCopyMove;
	CImPop3Delete*				iPopDelete;

	CArrayFixFlat<TMsvId>*		iMsvIdArray;		// stores any failed refresh msgs
	TInt						iArrayCtr;
	TRequestStatus*				iReportStatus;
	// Pop3 settings
	CImPop3Settings*			iPopSettings;
	CImIAPPreferences*			iIAPPreferences;

	TPop3Progress				iPopProgress;
	TPop3ProgressBuf			iPopProgressBuf;

	TBool						iConnectedToPopMbox;
	TBool						iOperationActive;

	TMsvId						iServiceId;
	TUint						iPort;
	TInt						iDoCallShowMessages;

	TInt							iCurrentOfflineOp;
	CImPop3OfflineOperationFinder*	iOfflineOpFinder;
	CImPop3SetOfflineOps*			iOfflineOpSetter;
	CImLogMessage*					iLogMessage;
	};

#endif

