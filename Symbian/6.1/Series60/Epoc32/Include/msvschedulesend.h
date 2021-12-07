/////////////////////////////////////////////////////////////////////////////
//
//	MsvScheduleSend.H
//
//	Copyright (c) 1999 Symbian Ltd.  All rights reserved. 
//
/////////////////////////////////////////////////////////////////////////////

#ifdef _DEBUG
#undef _MSG_NO_LOGGING
#endif



#ifndef MSV_SCHEDULE_SEND_H_
#define MSV_SCHEDULE_SEND_H_

/////////////////////////////////////////////////////////////////////////////
//
//	Includes
//
/////////////////////////////////////////////////////////////////////////////

#include "MsvScheduledEntry.h"
#include "MsvSchedulePackage.h"

class RScheduler;
class CMsvScheduleSettings;
class TMsvEntryScheduleData;
class CMsvOffPeakTimes;
class TMsvSendErrorAction;
class CMsvSendErrorActions;
class CMsvSysAgentActions;
class CMsvScheduledEntry;

/////////////////////////////////////////////////////////////////////////////
//
//	Constants
//
/////////////////////////////////////////////////////////////////////////////

const TUid KUidMsvScheduledSendingDLL	= {0x100056A0};
const TInt KMsvSchsendArrayGrowth		= 10;

#ifdef _MSG_NO_LOGGING
#define SCHSENDLOG(a)
#else
_LIT(KSchSendLogDir, "schsend");
_LIT(KSchSendLogFile,"SchSend.txt");
#define SCHSENDLOG(a) a
#endif

/////////////////////////////////////////////////////////////////////////////
//
//	CMsvScheduleSend Declaration
//
/////////////////////////////////////////////////////////////////////////////

class CMsvScheduleSend : public CBase
	{
public:
	IMPORT_C ~CMsvScheduleSend();

	IMPORT_C void ScheduleL(const CMsvEntrySelection& aSelection, const TMsvSchedulePackage& aPackage);

	IMPORT_C void ReScheduleL(const CMsvEntrySelection& aSelection, const TMsvSchedulePackage& aPackage, const TMsvSendErrorAction* aErrorAction = NULL);

	IMPORT_C void CheckScheduleL(const CMsvEntrySelection& aSelection);
	IMPORT_C void DeleteScheduleL(const CMsvEntrySelection& aSelection);

	IMPORT_C void SendingCompleteL(TMsvEntry& aEntry, const TBool aChangeEntry = EFalse);
	IMPORT_C void SendingCompleteL(const CMsvEntrySelection& aSelection);

	IMPORT_C virtual void RestoreL(CMsvStore& aStore);
	//RestoreL restores iOffPeakTimes, iSettings and iErrorActions from streams in aStore.
	//The Server MTM may need to restore iOffPeakTimes, iSettings and/or iErrorActions
	//individually if either is specified in a resource file.

	inline CMsvOffPeakTimes& OffPeakTimes() const;
	inline CMsvScheduleSettings& ScheduleSettings() const;
	inline CMsvSendErrorActions& SendErrorActions() const;
	inline CMsvSysAgentActions& AgentActions() const;

	IMPORT_C static void CreateScheduleL(RScheduler& aScheduler, const CMsvScheduleSettings& aSettings, const TTime& aStartTime, const TTimeIntervalMinutes& aValitidyPeriod, TSchedulerItemRef& aRef);
	IMPORT_C static void FindScheduleL(RScheduler& aScheduler, const TTime& aStartTime, TSchedulerItemRef& aRef);
	IMPORT_C static void RoundUpToMinute(TTime& aTime);
	IMPORT_C static void ScheduleEntryL(RScheduler& aScheduler, const TSchedulerItemRef& aRef, const TMsvSchedulePackage& aPackage, TTaskInfo& aInfo);
	IMPORT_C static void UpdateEntryAfterSchedule(const TSchedulerItemRef& aRef, const TTaskInfo& aInfo, const TTime& aTime, TInt aFinalState, TMsvEntry& aEntry, TMsvEntryScheduleData& aData);
	IMPORT_C static void ConnectAndRegisterL(RScheduler& aScheduler, const CMsvScheduleSettings& aSettings);

protected:

//	--- Construction ---

	IMPORT_C CMsvScheduleSend(CMsvServerEntry& aServerEntry);
	IMPORT_C virtual void ConstructL();

	//Returns a pointer to a new CMsvScheduledEntry-derived object
	//which encapsulates the scheduling data for message identified by aId.
	virtual CMsvScheduledEntry* GetMessageL(const TMsvId aId) const = 0;

private:

	enum
		{
		EDefaultTaskPriority	= 1, //used when scheduling a task in the task scheduler
		EDefaultTaskRepeat		= 1	 //used when scheduling a task in the task scheduler
		};
	
	void SendingCompleteL(CMsvScheduledEntry& aScheduledEntry, const TBool aChangeEntry);

	//Note: GetNextRetry() does not change the sending state of the message
	TBool GetNextRetry(CMsvScheduledEntry& aMessage, const TMsvSendErrorAction& aErrorAction, TTimeIntervalSeconds& aInterval) const;

	void DoScheduleL(CMsvScheduledEntries& aSchEntries, const TInt aFinalState, const TTime& aFromTime);
	void DoReScheduleL(CMsvScheduledEntries& aSchEntries);
	
	void GetMessagesL(const CMsvEntrySelection& aSelection);

	void ConnectAndRegisterL();

	void ScheduleEntryL(CMsvScheduledEntry& aMessage, const TInt aFinalState, const TTime& aStartTime, const TSchedulerItemRef& aRef);
	void CreateScheduleL(const TTime& aStartTime, const TTimeIntervalMinutes& aValitidyPeriod, TSchedulerItemRef& aRef);

	void GetOffPeakL(TTime aFromTime, TTime& aStartTime, TTimeIntervalMinutes& aValidityPeriod) const;

	void DeleteScheduleForEntryL(CMsvScheduledEntry& aMessage, const TBool aChangeEntry);
	void SortByDateL(CMsvScheduledEntries& aScheduledEntries);
	TBool SetMessageStartTime(CMsvScheduledEntry& aMessage, const TTime& aFromTime, const TMsvSendErrorAction* aErrorAction = NULL);
	void FindScheduleL(const TTime& aStartTime, TSchedulerItemRef& aRef);

	TBool TaskAndMessageMatchL(const CMsvScheduledEntry& aMessage);
	TMsvId GetMessageIdForTaskL(TInt aTaskId);

#ifndef _MSG_NO_LOGGING
	void FLog(TRefByValue<const TDesC> aFormat, ...);
	void FLog(TRefByValue<const TDesC8> aFormat, ...);
#endif

protected:

//	--- Data Members which may be used by a derived class ---

	CMsvScheduleSettings*	iSettings;
	CMsvOffPeakTimes*		iOffPeakTimes;
	CMsvSendErrorActions*	iErrorActions;
	CMsvSysAgentActions*	iAgentActions;

	TBool					iRegistered;	//Whether registered with the task scheduler
	RScheduler				iScheduler;		//Task Scheduler resource
	CMsvServerEntry&		iServerEntry;
	TMsvSchedulePackage		iPackage;

	CMsvScheduledEntries*	iSchEntries;

	//Used by DeleteScheduleForEntryL()
	CArrayFixFlat<TScheduleEntryInfo>* iSchEntryInfo;
	CArrayFixFlat<TTaskInfo>* iSchTaskInfo;
	};

#include "MsvScheduleSend.inl"

#endif
