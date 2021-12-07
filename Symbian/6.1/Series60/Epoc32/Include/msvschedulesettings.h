/////////////////////////////////////////////////////////////////////////////
//
//	MsvScheduleSettings.H
//
//	Copyright (c) 1999 Symbian Ltd.  All rights reserved. 
//
/////////////////////////////////////////////////////////////////////////////

#ifndef MSV_SCHEDULE_SETTINGS_H_
#define MSV_SCHEDULE_SETTINGS_H_

#include <msvrcpt.h>
#include <schinfo.h>
#include "MsvSendErrorAction.h"

/////////////////////////////////////////////////////////////////////////////
//
//	Constants
//
/////////////////////////////////////////////////////////////////////////////

const TUid KUidMsvFileScheduleSettings	= {0x100056BB}; //Used by CMsvScheduleSettings
const TInt16 KMsvScheduleSettingsVersion	= 1;

#if defined(__WINS__)
_LIT(KMsvDefaultSendExe, "z:\\system\\programs\\schsendexe.dll");
#else
_LIT(KMsvDefaultSendExe, "z:\\system\\programs\\schsendexe.exe");
#endif

/////////////////////////////////////////////////////////////////////////////
//
//	CMsvScheduleSettings Declaration
//
/////////////////////////////////////////////////////////////////////////////

class CMsvScheduleSettings : public CBase
	{
public:

	IMPORT_C static CMsvScheduleSettings* NewL();
	IMPORT_C ~CMsvScheduleSettings();

public:

	IMPORT_C void StoreL(CMsvStore& aStore) const;
	IMPORT_C void RestoreL(CMsvStore& aStore);

	IMPORT_C void Reset();

	IMPORT_C void SetSendExe(const TDesC& aSendExe);
	IMPORT_C const TDesC& SendExe() const;

	IMPORT_C void SetPriority(const TInt aPriority);
	IMPORT_C const TInt Priority() const;

	IMPORT_C void SetValidityPeriod(const TTimeIntervalMinutes& aValidityPeriod);
	IMPORT_C const TTimeIntervalMinutes& ValidityPeriod() const;

	IMPORT_C void SetIntervalType(const TIntervalType aIntervalType);
	IMPORT_C const TIntervalType IntervalType() const;

	IMPORT_C void SetLongInterval(const TTimeIntervalSeconds& aInterval);
	IMPORT_C const TTimeIntervalSeconds& LongInterval() const;
	
	IMPORT_C void SetShortInterval(const TTimeIntervalSeconds& aInterval);
	IMPORT_C const TTimeIntervalSeconds& ShortInterval() const;

	IMPORT_C const CArrayFixFlat<TTimeIntervalSeconds>& VariableIntervals() const;
	IMPORT_C void SetVariableIntervalsL(const CArrayFixFlat<TTimeIntervalSeconds>& aIntervals);

	IMPORT_C const TTimeIntervalMicroSeconds32& Latency() const;
	IMPORT_C void SetLatency(const TTimeIntervalMicroSeconds32& aLatency);
	
	enum
		{
		EDefaultPriority		= 27,
		EDefaultValidityPeriod	= 10080,	/* 10080 Minutes in 1 week */
		EDefaultIntervalType	= 3,		/* EYearly */
		EDefaultShortInterval	= 5,
		EDefaultLongInterval	= 120,
		EDefaultLatency			= 1500000
		};

/*
	Private and Protected Members
*/

private:
	CMsvScheduleSettings();

	void ConstructL();

	void ExternalizeL (RWriteStream& aWriteStream) const;
    void InternalizeL (RReadStream& aReadStream);

	TInt16					iVersion;
	TFileName				iSendExe;		//EXE that will be called by the Task Scheduler
	TInt					iPriority;		//Priority of the schedules on the task scheduler
	TTimeIntervalMinutes	iValidityPeriod;//Validity period of message on the task scheduler
	TIntervalType			iIntervalType;	//See TIntervalType declaration and Task Scheduler user documentation
	TTimeIntervalMicroSeconds32 iLatency;		//Minimum amount of time between now and when the message is scheduled for. Cannot be negative.

	TTimeIntervalSeconds iLongInterval;
	TTimeIntervalSeconds iShortInterval;
	CArrayFixFlat<TTimeIntervalSeconds>* iVariableIntervals;
	};

#endif
