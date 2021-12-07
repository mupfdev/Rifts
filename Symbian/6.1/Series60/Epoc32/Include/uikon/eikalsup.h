// EIKALSUP.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKALSUP_H__)
#define __EIKALSUP_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

#if !defined(__T32ALRT_H__)
#include <t32alrt.h>
#endif

#if !defined(__EIKSVFTY_H__)
#include <eiksvfty.h>
#endif

const TInt KAlarmSnoozeIncrement=5;

/**
 * @internal
 * Internal to Symbian
 */
class CEikAlmControlSupervisor : public CBase
	{
public:
	enum TFlags
		{
		EHasMessageRequest		=0x00000002,
		EShouldCompleteMessage	=0x00000004,
		EHasMessageLogon		=0x00000008
		};
	enum TPriority 
		{ 
		ESnoozeCountDownPriority=0x00000001
		};
public:
	IMPORT_C CEikAlmControlSupervisor();
    IMPORT_C void ConstructL(MEikServAlarmFactory* aAlarmControl);
	~CEikAlmControlSupervisor();
	void CancelTimeCountDown();
	void SynchronizeCountDownTimer();
	inline TInt PauseSoundMinutes() const;
	inline TTime QuietPeriodEndTime() const;
public:
	IMPORT_C void CmdAcknowledgeAlarm();
	IMPORT_C void CmdPauseAlarmSound(TInt aNumMinutes=KAlarmSnoozeIncrement);
	IMPORT_C void CmdSilenceAlarmSound();
	IMPORT_C TBool CmdTaskAwayFromAlarm();
public:
	void ServiceL(const RMessage& aMessage);
private:
    void NotifyClient(TAlmAlertResponse aFlag);
	void UpdateDisplay();
	void StartTimeCountDown();
	static TInt CallbackSnoozeDecrement(TAny *aAlarmAlert);
	void DecrementSnoozeMinutes();
	void UpdateAlarmInfo(const RMessage& aMessage);
	void UpdateSoundDeferTime(const RMessage& aMessage);
	TInt StartPlayAlarm(const RMessage& aMessage);
	void StopPlayAlarm();
	void ReturnTimeToSnooze(const RMessage& aMessage);
	void SetAlertState(TInt aAlarmServerStateFlags);
private:
	TInt iAlarmControlState;
	TInt iPauseSoundMinutes;
	TTime iPauseSoundDueTime;
	TTime iQuietPeriodEndTime;
	RMessage iMsgPtr;
	RMessagePtr iLogonPtr;
	MEikServAlarm* iAlarmAlert;
	CPeriodic* iMinuteCountDown;
	};

inline TInt CEikAlmControlSupervisor::PauseSoundMinutes() const
	{
	return(iPauseSoundMinutes);
	}

inline TTime CEikAlmControlSupervisor::QuietPeriodEndTime() const
	{
	return(iQuietPeriodEndTime);
	}

#endif
