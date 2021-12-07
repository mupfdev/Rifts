//////////////////////////////////////////////////////////////////////////
//
//	SmutSimParam.h
//
//	Copyright (c) 2000 Symbian Ltd.  All rights reserved.
//
//////////////////////////////////////////////////////////////////////////

#include <msvapi.h>
#include <smsuaddr.h>

typedef TPckgBuf<TInt> TIntBuf;
const TUid KUidMsvSimSmsParams = {0x100081BC};

class CAdvGsmSmspList;

class CSmsSimParamOperation : public CMsvOperation
	{
public:
	static CSmsSimParamOperation* ReadSimParamsL(TUid aMtm, TMsvId aService, CMsvSession& aMsvSession, TRequestStatus& aObserverRequestStatus);
	~CSmsSimParamOperation();

	inline const CAdvGsmSmspList& SmspList() const;

	IMPORT_C CAdvGsmSmspList* ServiceCentersLC() const;

	IMPORT_C const TDesC8& ProgressL();

private:

	CSmsSimParamOperation(TUid aMtm, TMsvId aService, CMsvSession& aMsvSession, TRequestStatus& aObserverRequestStatus);

	void RunL();
	void DoCancel();

	TInt RunError(TInt aError);

	void DoReadSimParamsL();
	void Complete();

	void RestoreSimParamsL(CMsvStore& aStore);

private:

	enum TReadSimParamsState
		{
		EStateWaiting,
		EStateReadingSimParams,
		} iState;

	CAdvGsmSmspList* iSimParams;
	TInt iError;
	TIntBuf iProgressBuf;
	CMsvOperation* iOperation;
	};

const CAdvGsmSmspList& CSmsSimParamOperation::SmspList() const
	{
	return *iSimParams;
	}