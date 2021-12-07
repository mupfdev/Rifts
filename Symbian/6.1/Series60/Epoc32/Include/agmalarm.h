// AGMALARM.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __AGMALARM_H__
#define __AGMALARM_H__

#include <e32base.h>
#include <t32alm.h>
#include "agmdate.h"
#include "agmxsort.h"

class CAgnModel;
class CAgnAlarmActive;
class CAgnAlarmServerTerminationActive;

class MAgnAlarmServerTerminationCallBack
	{
public:
	virtual void AlarmServerTerminated() = 0;
	};


class CAgnAlarm : public CBase
	{
public:
	IMPORT_C static CAgnAlarm* NewL(CAgnModel* aModel,MAgnAlarmServerTerminationCallBack* aCallBack=NULL);
	IMPORT_C virtual ~CAgnAlarm();
	IMPORT_C void FindAndQueueNextAlarmL();
	IMPORT_C void FindAndQueueNextFewAlarmsL(const TInt aMaxNumberOfAlarms=10,const TInt aMaxNumberOfDays=31);
	IMPORT_C void SetModel(CAgnModel* aModel);
	IMPORT_C void SetDefaultTitleL(const TDesC& aDefaultTitle);
	IMPORT_C TPtrC DefaultTitle() const;
	IMPORT_C TInt Connect();
	IMPORT_C void CAgnAlarm::RestartL();
	IMPORT_C void RequestServerTerminationNotification(TRequestStatus& aStatus);
	IMPORT_C void CancelServerTerminationNotification();
	IMPORT_C void OrphanAlarm(); 
	inline RAlarmServer& AlarmServer() { return (iAlarmServer); }// for test code
private:
	void ConstructL(CAgnModel* aModel,MAgnAlarmServerTerminationCallBack* aCallBack);
	CAgnAlarmActive*					iAlarm;
	CAgnAlarmServerTerminationActive*	iNotifier;
	RAlarmServer						iAlarmServer;
	};


struct TAgnAlarmEntry
	{
	TAgnDateTime	iDueDateTime;
	TTime			iAlarmTime;
	TAlarmMessage	iMessage;
	TAlarmSoundName iSound;
	TAgnInstanceId	iInstanceId;
	};

class CAgnAlarmActive : public CActive
 	{
public:	
	static CAgnAlarmActive* NewL(CAgnModel* aModel,RAlarmServer& aAlarmServer);
	virtual ~CAgnAlarmActive();
	virtual void RunL();
	void FindAndQueueNextAlarmL();
	void FindAndQueueNextFewAlarmsL(const TInt aMaxNumberOfAlarms,const TInt aMaxNumberOfDays);
	void RequestNotification();
	inline void SetModel(CAgnModel* aModel) { iModel = aModel; };
	void SetDefaultTitleL(const TDesC& aDefaultTitle);
	TPtrC DefaultTitle() const;
	void OrphanAlarm();
private:
	void NextAlarmL(const TTime& aNow,CArrayFixFlat<TAgnSortInstance>* aAlarmedIds);
	CAgnAlarmActive(TInt aPriority,RAlarmServer& aAlarmServer);
	void UpdateAlarmListL(CArrayFixFlat<TAgnSortInstance>* aAlarmedIds,
							CArrayFixFlat<TAgnSortInstance>* aDayInfoList,
							TAgnDate aCurrentDate, const TAgnDateTime& aNow,TAgnDateTime& aNextAlarm);
	virtual void DoCancel();
private:
	enum {EPriority=100,EGranularity=2};
	RAlarmServer&					iAlarmServer;
	CArrayFixFlat<TAgnAlarmEntry>*	iAlarmList;	
	TInt							iAlarmListIndex; //index of the currently queued alarm 	
	CAgnModel*						iModel; // pointer to owning CAgnModel class
	HBufC*							iDefaultTitle;
	};


class CAgnAlarmServerTerminationActive : public CActive
	{
public:
	static CAgnAlarmServerTerminationActive* NewL(RAlarmServer& aAlarmServer,MAgnAlarmServerTerminationCallBack* aCallBack,CAgnAlarm* aOwningObject);
	virtual ~CAgnAlarmServerTerminationActive();
	virtual void RunL();
	void Start();
	void RequestServerTerminationNotification(TRequestStatus& aStatus);
	void CancelServerTerminationNotification();
private:
	CAgnAlarmServerTerminationActive(TInt aPriority,RAlarmServer& aAlarmServer,CAgnAlarm* aOwningObject);	
	virtual void DoCancel();
private:
	enum {EPriority = 100};
	RAlarmServer&		iAlarmServer;
	MAgnAlarmServerTerminationCallBack*	iCallBack;
	TRequestStatus*		iUserRequestStatus;
	CAgnAlarm*			iOwningObject;
	};

#endif
