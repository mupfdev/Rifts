// T32ALM.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// Written by BLB, June 1995
//
#if !defined(__T32ALM_H__)
#define __T32ALM_H__
#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif
//
const TInt KAlarmServerMajorVN=1;
const TInt KAlarmServerMinorVN=1;
const TInt KAlarmServerBuildVN=80;
//
const TInt KNullAlarmID=-1;
const TInt KMaxClockAlarms=8;
const TInt KMaxAlarmMessage=0x80;
const TInt KMaxAlarmSoundName=0x20;
const TInt KMaxAcknowledgeReviewAlarms=8;
const TInt KDefaultSoundPlayOffsetInSeconds=0;
const TInt KDefaultSoundPlayDurationInSeconds=60;
//
typedef CArrayFixFlat<TInt> CAlarmIdArray;
typedef TBuf<KMaxAlarmMessage> TAlarmMessage;
typedef TBuf<KMaxAlarmSoundName> TAlarmSoundName;
//
enum TAlarmType 
	{
	EAlarmTypeDay,
	EAlarmTypeClock,
	EAlarmTypeTimed,
	EAlarmTypeOrphan,
	EAlarmTypeSnoozed // Must be last type
	};
enum TAlarmClockRepeat 
	{
	EAlarmClockOnce,
	EAlarmClockNext24hours,
	EAlarmClockDaily,
	EAlarmClockWeekly,
	EAlarmClockWorkday // Must be last type
	};
enum TAlarmSetState
	{
	EAlarmNotSet,
	EAlarmSet,
	EAlarmDisabled
	};
enum TAlarmSoundState
	{
	EAlarmSoundOn,
	EAlarmSoundOff,
	EAlarmQuietPeriod,
	};
//
class TAlarmInfo
	{
public:
	TInt iAlarmId;
	TTime iDueTime;
	TTime iAlarmTime;
	TAlarmType iType;
	TAlarmMessage iMessage;
	TAlarmSoundName iSound;
	TAlarmClockRepeat iRepeat;
	};
//
class TAlmSoundPlay
	{
public:
	inline TAlmSoundPlay();
	inline TAlmSoundPlay(TTimeIntervalMinutes aOffset, TTimeIntervalSeconds aDuration);
public:
	TTimeIntervalMinutes iOffset;		// from the time an alarm is first displayed
	TTimeIntervalSeconds iDuration;		// how long the alarm playing lasts
	};
//
class RAlarmServer : public RSessionBase
	{
public:
	enum TSessionType { ESessionTypeDay,ESessionTypeTimed };
	enum TArrayCategory { EArrayNext,EArrayReview,EArrayOrphan,EArraySnooze };
	enum TInfoCategory { EInfoById,EInfoClock,EInfoNext,EInfoSession };
	enum TCountCategory { ECountNext,ECountReview,ECountOrphan,ECountSnooze,ECountUnacknowledged };
public:
	IMPORT_C TInt Connect();
	IMPORT_C TVersion Version() const;
	IMPORT_C void NotifyOnChangeCancel();
	IMPORT_C void NotifyOnChange(TRequestStatus& aStatus);
public:
	IMPORT_C void CancelSessionAlarm();
	IMPORT_C TInt OrphanSessionAlarm();
	IMPORT_C void SetClockAlarm(TInt aClockAlarmIndex,const TTime& aAlarmTime,const TAlarmMessage& aMessage,const TAlarmSoundName& aSound,TAlarmClockRepeat aRepeat);
	IMPORT_C void SetAgendaAlarm(const TTime& aAlarmTime,const TAlarmMessage& aMessage,const TAlarmSoundName& aSound,const TTime& aDueDateTime,TSessionType aType);
	IMPORT_C void SetSessionAlarm(TRequestStatus& aStatus,const TTime& aAlarmTime,const TAlarmMessage& aMessage,const TAlarmSoundName& aSound,const TTime& aDueDateTime,TSessionType aType);
	//
	IMPORT_C TInt AlarmDelete(TInt aAlarmId);
	IMPORT_C TInt DeleteAllOrphanAlarms();
	IMPORT_C TInt AlarmEnable(TBool aShouldEnable,TInt aAlarmId);
	//
	IMPORT_C TAlarmSetState AlarmState(TInt aAlarmId) const;
	IMPORT_C TInt AlarmCount(TCountCategory aCategory) const;
	IMPORT_C TInt AlarmType(TAlarmType& aType,TInt aAlarmId) const;
	IMPORT_C TInt AlarmOwner(TFullName& aName,TInt aAlarmId) const;
	IMPORT_C void AlarmArrayPopulateL(CAlarmIdArray& aArray,TArrayCategory aCategory,TInt aMaxNumber=64) const;
	IMPORT_C TInt AlarmInfo(TAlarmInfo& anAlarm,TInfoCategory aCategory,TInt aAlarmId=KNullAlarmID) const;
	//
	IMPORT_C void QuietPeriodCancel();
	IMPORT_C TTime QuietPeriodUntil() const;
	IMPORT_C TInt QuietPeriodSet(TTimeIntervalMinutes aQuietInterval);
	IMPORT_C void SetAlarmSoundOn(TBool aSetSoundOn);
	IMPORT_C TAlarmSoundState AlarmSoundState() const;
	//
	IMPORT_C TInt SetAlarmPlayIntervals(const CArrayFix<TAlmSoundPlay>& aIntervals);
	IMPORT_C TInt GetAlarmPlayIntervalsL(CArrayFix<TAlmSoundPlay>& aIntervals);

public:
	IMPORT_C void __DbgShutDownServer();
	IMPORT_C void __DbgFailAlloc(TInt aCount);
	IMPORT_C void __DbgPreventUserNotify(TBool aShouldStop);
	IMPORT_C TInt __DbgSnoozeAlarm(TInt aAlarmId,const TTime& aNewTime);

private:
	TPckgBuf<TAlarmInfo> iPckgAlarmInfo;
	};





// 	class TAlmSoundPlay
inline TAlmSoundPlay::TAlmSoundPlay()
:	iOffset(KDefaultSoundPlayOffsetInSeconds), iDuration(KDefaultSoundPlayDurationInSeconds)
	{}
inline TAlmSoundPlay::TAlmSoundPlay(TTimeIntervalMinutes aOffset, TTimeIntervalSeconds aDuration)
:	iOffset(aOffset), iDuration(aDuration)
	{}


#endif
