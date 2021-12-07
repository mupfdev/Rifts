// SMTS.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved. 
//

//	This is the public API header file for SMTS.DLL - 
//	the transport driver which sends Imail using the 
//	SMTP Internet protocol.

#if !defined(__SMTS_H__)
#define __SMTS_H__
#if !defined(__MTSR_H__)
#include "mtsr.h"
#endif

#include <smtpset.h>
#include <commdb.h>

class CMsgImOutboxSend;


typedef TPckgBuf<TImSmtpProgress> TImSmtpProgressBuf;

class CSmtpSrvMtm : public CBaseServerMtm
	{
public:
	IMPORT_C static CSmtpSrvMtm* NewL(CRegisteredMtmDll& aRegisteredMtmDll, CMsvServerEntry* aEntry);
	~CSmtpSrvMtm();

	void CopyToLocalL(const CMsvEntrySelection& aSelection,TMsvId aDestination, TRequestStatus& aStatus);
	void MoveToLocalL(const CMsvEntrySelection& aSelection,TMsvId aDestination, TRequestStatus& aStatus);
	void CopyFromLocalL(const CMsvEntrySelection& aSelection,TMsvId aDestination, TRequestStatus& aStatus);
	void MoveFromLocalL(const CMsvEntrySelection& aSelection,TMsvId aDestination, TRequestStatus& aStatus);
	void CopyWithinServiceL(const CMsvEntrySelection& aSelection,TMsvId aDestination, TRequestStatus& aStatus);
	void MoveWithinServiceL(const CMsvEntrySelection& aSelection,TMsvId aDestination, TRequestStatus& aStatus);
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

protected:
	void DoCancel();
	void DoRunL();
	void DoComplete(TInt aError);

private:
	CSmtpSrvMtm(CRegisteredMtmDll& aRegisteredMtmDll, CMsvServerEntry*  aEntry);
	void ConstructL();
	void DoSendMessagesL(TRequestStatus& aStatus);
	void CopyToOurSelectionL(const CMsvEntrySelection& aSourceSelection);
	void AddWaitingInOutboxToSelectionL();
	TInt SetServiceToConnected(TBool aConnected);

private:

	TMsvId				iServiceId;
	CMsgImOutboxSend*	iOutboxSend;
	TRequestStatus*		iReport;
	TImSmtpProgressBuf	iProgressBuffer;
	TInt				iSessionError;
	TUint32				iIntrAddress;
	CMsvEntrySelection* iSendSelection;
	TCommDbDatabaseType iDbType;
	};

#endif
