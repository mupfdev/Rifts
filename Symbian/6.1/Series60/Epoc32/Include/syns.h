//	SYNS.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//

#if !defined(__SYNS_H__)
#define __SYNS_H__
#if !defined(__MTSR_H__)
#include "mtsr.h"
#endif

//#include <smtpset.h>

//#include <synu.h>

//typedef TPckgBuf<TImSmtpProgress> TImSmtpProgressBuf;
//typedef TPckgBuf<CSynSrvMtm::TSyncMtmOperations> TSyncProgressBuf;




class CSynSrvMtm : public CBaseServerMtm
	{
public:
	enum TSyncMtmOperations
		{
		ESyncMtmNullOp,
		ESyncMtmUiNullOp,
		ESyncMtmUiEditing,
		ESyncMtmUiChoseSend,
		ESyncMtmUiDelServiceOp
		};

public:
	IMPORT_C static CSynSrvMtm* NewL(CRegisteredMtmDll& aRegisteredMtmDll, CMsvServerEntry*  aEntry);
	~CSynSrvMtm();

	void CopyToLocalL(const CMsvEntrySelection& aSelection,TMsvId aDestination, TRequestStatus& aStatus);
	void MoveToLocalL(const CMsvEntrySelection& aSelection,TMsvId aDestination, TRequestStatus& aStatus);
	void CopyFromLocalL(const CMsvEntrySelection& aSelection,TMsvId aDestination, TRequestStatus& aStatus);
	void MoveFromLocalL(const CMsvEntrySelection& aSelection,TMsvId aDestination, TRequestStatus& aStatus);
	void CopyWithinServiceL(const CMsvEntrySelection& aSelection,TMsvId aDestination, TRequestStatus& aStatus);
	void MoveWithinServiceL(const CMsvEntrySelection& aSelection,TMsvId aDestination, TRequestStatus& aStatus);
	void DeleteL(const CMsvEntrySelection& aSelection, TRequestStatus& aStatus);
	void DeleteAllL(const CMsvEntrySelection& aSelection, TRequestStatus& aStatus);
	void CreateL(TMsvEntry aNewEntry, TRequestStatus& aStatus);
	void ChangeL(TMsvEntry aNewEntry, TRequestStatus& aStatus);
	//
	void StartCommandL(CMsvEntrySelection& aSelection, TInt aCommand, const TDesC8& aParameter, TRequestStatus& aStatus);
	//
	TBool CommandExpected();
	//
	const TDesC8& Progress();
	//
//	void SetInitialEntry(CMsvServerEntry* aEntry);

protected:
	void DoCancel();
	void DoRunL();
	void DoComplete(TInt aError);

private:
	CSynSrvMtm(CRegisteredMtmDll& aRegisteredMtmDll, CMsvServerEntry* aEntry);
	void ConstructL();

private:

//	CMsvServerEntry*	iEntry;	
//	CSynOutboxSend*		iOutboxSend;
	TRequestStatus*		iReport;
//  TMsvId              iServiceId;

	//	On the stack default size = ??
//	TImSmtpProgressBuf	iProgressBuffer;
//	TImSmtpProgress		iProgress;
//	TDesC8* iMyProgress;
	TPckgBuf<TSyncMtmOperations>  iSendProgress;
	};

#endif  // __SYNS_H__