/////////////////////////////////////////////////////////////////////////////
//
//	MsvEntryScheduleData.H
//
//	Copyright (c) 1999 Symbian Ltd.  All rights reserved. 
//
/////////////////////////////////////////////////////////////////////////////

#ifndef MSV_ENTRY_SCHEDULE_DATA_H_
#define MSV_ENTRY_SCHEDULE_DATA_H_

/////////////////////////////////////////////////////////////////////////////
//
//	Includes
//
/////////////////////////////////////////////////////////////////////////////

#include <msvstore.h>
#include <schinfo.h>
#include <csch_cli.h>
#include <schtask.h>

/////////////////////////////////////////////////////////////////////////////
//
//	Constants
//
/////////////////////////////////////////////////////////////////////////////

const TUid KUidMsvFileScheduleData			= {0x100056A2};	//Used by TMsvEntryScheduleData
const TInt16 KMsvEntryScheduleDataVersion	= 1;

/////////////////////////////////////////////////////////////////////////////
//
//	TMsvEntryScheduleData Declaration
//
/////////////////////////////////////////////////////////////////////////////

class TMsvEntryScheduleData
	{
public:
	IMPORT_C TMsvEntryScheduleData();

	IMPORT_C void RestoreL(CMsvStore& aStore);
	IMPORT_C void StoreL(CMsvStore& aStore) const;
	IMPORT_C void RemoveL(CMsvStore& aStore) const;

	IMPORT_C void Reset();
	IMPORT_C TBool IsReset() const;

	IMPORT_C TInt Retries() const;
	IMPORT_C void IncreaseRetries();
	IMPORT_C void ResetRetries();

	TInt				iTaskId;
	TSchedulerItemRef	iRef;

protected:
	TInt				iRetryCount;
	TInt16				iVersion;

	void ExternalizeL(RWriteStream&) const;
	void InternalizeL(RReadStream&);
	};

#endif