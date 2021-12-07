// CSCH_CLI.H
//
// Copyright (c) 1997-2000 Symbian Ltd.  All rights reserved.
//
//	RScheduler class
//	Client Interface to Scheduler
//

#if !defined(__CSCH_CLI_H__)
#define __CSCH_CLI_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif

#if !defined(__SCHINFO_H__)
#include <schinfo.h>
#endif

#include <e32cons.h>

IMPORT_C TInt StartSch32();
//starts scheduler under EPOC32

// Constants
const TUint KESchMajorVersionNumber=1;
const TUint KESchMinorVersionNumber=0;
const TUint KESchBuildVersionNumber=50;
const TInt KMaxScheduleName=50;
_LIT(KScheduleServerName, "TaskScheduler");

class RScheduler : public RSessionBase
	{//client-side session with the scheduler
public:
		//ctor
	IMPORT_C RScheduler();
		//connect to the scheduler
	IMPORT_C TInt Connect();
		//returns version of scheduler
	IMPORT_C TVersion Version() const;
		//register with filename of task executor DLL, priority for this client, ordinal (in DLL) of factory fn. returning instance of executor
		//scheduler deregisters automatically
	IMPORT_C TInt Register(const TFileName& aFileName,const TInt aPriority);
	//schedule editing
		//creates schedule with no tasks: pass in schedule info, flags, entries; schedule handle written back
	IMPORT_C TInt CreatePersistentSchedule(TSchedulerItemRef& aRef, 
											const CArrayFixFlat<TScheduleEntryInfo>& aEntryList);
		//delete schedule at aScheduleHandle. Returns KErrNotFound if not found, KErrArgument if schedule has tasks
	IMPORT_C TInt DeleteSchedule(const TInt aScheduleHandle) const;
		//disable a schedule at aScheduleHandle. Returns KErrNotFound if not found
	IMPORT_C TInt DisableSchedule(const TInt aScheduleHandle) const;
		//enable schedule at aScheduleHandle. Returns KErrNotFound if not found
	IMPORT_C TInt EnableSchedule(const TInt aScheduleHandle) const;
		//give schedule at aScheduleHandle a new list of entries
	IMPORT_C TInt EditSchedule(const TInt aScheduleHandle, const CArrayFixFlat<TScheduleEntryInfo>& aEntryList);
	//task business
		//schedule a task with info aTaskInfo with schedule at aScheduleHandle. Returns KErrNotFound if not found
		//Writes new task Id into aTaskInfo.iTaskId
		//PANICS CLIENT IF CLIENT IS NOT REGISTERED
	IMPORT_C TInt ScheduleTask(TTaskInfo& aTaskInfo, HBufC& aTaskData, const TInt aScheduleHandle);
		//create a new, transient schedule with the specified parameters & schedule the specifed task with it
		//schedule handle written back into aScheduleHandle, task ID into aTaskInfo
		//PANICS CLIENT IF CLIENT IS NOT REGISTERED
	IMPORT_C TInt ScheduleTask(TTaskInfo& aTaskInfo, HBufC& aTaskData, TSchedulerItemRef& aRef,
								const CArrayFixFlat<TScheduleEntryInfo>& aEntryList);
		//delete task with aTaskId: Returns KErrNotFound if not found
	IMPORT_C TInt DeleteTask(const TInt aTaskId) const;
	//retrieving
		//get name & handle for all schedules, or just pending ones
	IMPORT_C TInt GetScheduleRefsL(CArrayFixFlat<TSchedulerItemRef>& aScheduleRefArray,const TScheduleFilter aFilter);
		//get all schedule data for schedule with aScheduleHandle
		//leaves if aScheduleRefArray.ResizeL() fails
	IMPORT_C TInt GetScheduleL(const TInt aScheduleHandle, TScheduleState& aState, 
			CArrayFixFlat<TScheduleEntryInfo>& aEntries, CArrayFixFlat<TTaskInfo>& aTasks, TTime& aDueTime);
		//get name & id for:	all tasks
					//		 or pending tasks (i.e. tasks on pending schedules
					//		 or all tasks scheduled by this client
					//		 or pending tasks scheduled by this client
		//leaves if aEntries.ResizeL() or aTaskInfo.ResizeL() fail
	IMPORT_C TInt GetTaskRefsL(CArrayFixFlat<TSchedulerItemRef>& aTasks,
			const TScheduleFilter aScheduleFilter, const TTaskFilter aTaskFilter);
		//get info for the task with aTaskId
		//leaves if aTasks.ResizeL() fails
	IMPORT_C TInt GetTaskInfoL(const TInt aTaskId, TTaskInfo& aTaskInfo, TPtr& aTaskData, TSchedulerItemRef& aRef, TTime& aNextDue);

	IMPORT_C TInt GetTaskDataSize(const TInt aTaskId, TInt& aSize);
//debug
//these functions are included in rel for rel/deb compatibility, 
//but only do stuff in debug builds
	IMPORT_C TInt __DbgMarkHeap();
	IMPORT_C TInt __DbgCheckHeap(TInt aCount);
	IMPORT_C TInt __DbgMarkEnd(TInt aCount);
	IMPORT_C TInt __DbgFailNext(TInt aCount);
	IMPORT_C TInt __DbgResetHeap();
	IMPORT_C TInt __FaultServer();//kill the server!
//up to here...
private:
	TInt CreateSchedule(TSchedulerItemRef& aRef, const CArrayFixFlat<TScheduleEntryInfo>& aEntryList, 
				TScheduleSettings& aSettings);
	TInt GetScheduleInfoL(const TInt aScheduleHandle, TScheduleInfo& aInfo, TTime& aNextDue);
	TInt GetScheduleDataL(const TInt aScheduleHandle, const TScheduleInfo& aInfo,
			CArrayFixFlat<TScheduleEntryInfo>& aEntries, CArrayFixFlat<TTaskInfo>& aTasks);
	TBool ScheduleEntriesAreBad(const CArrayFixFlat<TScheduleEntryInfo>& aEntries);
	};

#endif
