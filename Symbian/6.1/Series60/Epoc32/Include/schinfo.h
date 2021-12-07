// SCHINFO.H
//
// Copyright (c) 1997-2000 Symbian Ltd.  All rights reserved.
//
// Various T-classes for client input to scheduler, scheduler output to client	
// These classes comprise part of the interface (the rest is defined in RScheduler)
//

#if !defined (__SCHINFO_H__)
#define __SCHINFO_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

#include <s32strm.h>

class TTaskInfo
	{
public:
	//ctors
	IMPORT_C TTaskInfo (TInt aTaskId, TName& aName, TInt aPriority, TInt aRepeat);
	IMPORT_C TTaskInfo();//
	//assignment
	IMPORT_C TTaskInfo& operator=(const TTaskInfo& aTaskInfo);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	IMPORT_C void InternalizeL(RReadStream& aStream);
	//needs a copy ctor
	//TTaskInfo (TTaskInfo& aTaskInfo);
	//data
	TInt iRepeat;//how many times to execute task (0 or negative = forever)
	TInt iTaskId;
	TName iName;
	TInt iPriority;
	};

enum TTaskFilter
	{
	EAllTasks,
	EMyTasks
	};

enum TScheduleFilter
	{
	EAllSchedules,
	EPendingSchedules
	};

enum TIntervalType
	{
	EHourly,
	EDaily,
	EMonthly,
	EYearly
	};

class TSchedulerItemRef
	{
public:
	TInt iHandle;
	TName iName;
	};

class TScheduleEntryInfo
	{
public:
	void ExternalizeL(RWriteStream& aStream) const;
	void InternalizeL(RReadStream& aStream);
	TIntervalType iIntervalType;
	TTime iStartTime;
	TInt iInterval;//interpreted differently by different types: default(minutes), EMonthly, EYearly  
	TTimeIntervalMinutes iValidityPeriod;
	};

class TScheduleState
	{
public:
	TName iName;
	TTime iDueTime;
	TBool iPersists;
	TBool iEnabled;
	};

//these classes isn't used directly by clients
class TScheduleInfo	
	{
public:
	TScheduleState iState;
	TInt iEntryCount;
	TInt iTaskCount;
	};

class TScheduleSettings
	{
public:
	TBool iPersists;
	TInt iEntryCount;
	};

#endif