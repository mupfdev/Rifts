/////////////////////////////////////////////////////////////////////////////
//
//	ScheduleBaseServerMtm.H
//
//	Copyright (c) 1999 Symbian Ltd.  All rights reserved. 
//
/////////////////////////////////////////////////////////////////////////////

#ifndef SCHEDULE_BASE_SERVER_MTM_H_
#define SCHEDULE_BASE_SERVER_MTM_H_

/////////////////////////////////////////////////////////////////////////////
//
//	CScheduleBaseServerMtm Declaration
//
/////////////////////////////////////////////////////////////////////////////

#include <mtsr.h>
#include <barsc.h>
#include <saclient.h>

class CMsvScheduleSend;
class CMsvSysAgentActions;
class TMsvSendErrorAction;
class TMsvSchedulePackage;

class CScheduleBaseServerMtm : public CBaseServerMtm
	{
protected:

//	--- Construction ---

	IMPORT_C CScheduleBaseServerMtm(CRegisteredMtmDll& aRegisteredMtmDll, CMsvServerEntry* aServerEntry);

//	--- Send the Scheduled Messages ---

	IMPORT_C virtual void SendScheduledL(CMsvEntrySelection& aSelection, const TBool aMove, const TDesC8& aParameter, TRequestStatus& aStatus);
	IMPORT_C virtual void ScheduleL(CMsvEntrySelection& aSelection, const TBool aMove, const TDesC8& aParameter, TRequestStatus& aStatus);
	IMPORT_C virtual void ConstructL();
	IMPORT_C virtual void RestoreScheduleSettingsL(TBool aRestoreErrorsFromResource = EFalse, TInt aErrorsResourceId = 0);
	IMPORT_C void LoadResourceFileL(const TDesC& aResFileName);

// Other Schedule Commands

	IMPORT_C virtual void CheckScheduleL(const CMsvEntrySelection& aSelection, const TDesC8& /*aParameter*/, TRequestStatus& aStatus);
	IMPORT_C virtual void DeleteScheduleL(const CMsvEntrySelection& aSelection, const TDesC8& /*aParameter*/, TRequestStatus& aStatus);

//	--- Pure virtual functions that must be implemented in a derived class ---

	virtual void PopulateSchedulePackage(const TDesC8& aParameter, const TBool aMove, TMsvSchedulePackage& aPackage) const = 0;
	
	virtual void LoadResourceFileL() = 0;
	IMPORT_C void Queue(TRequestStatus& aStatus);

protected:

	IMPORT_C ~CScheduleBaseServerMtm();

private:

	void RequestComplete(TRequestStatus* aStatus, TInt aError);

protected:

//	--- Data Member ---

	CMsvScheduleSend* iScheduleSend; //Should be constructed and deleted by the derived class

	RResourceFile iResourceFile;
	RFs iFs;
	TRequestStatus* iReport;
	};

#endif
