// T32ALRT.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// Started by BLB, November 1995
//
//	Header for the alarm alert server
//
//	This is the interface definition for the alert provider,
//	and is not necessary for users of the alarm or world servers.
//
#if !defined(__T32ALRT_H__)
#define __T32ALRT_H__

#define KNameAlarmAlertServer _L("AlarmAlertServer")

const TInt KAlmAlertMajVN=1;
const TInt KAlmAlertMinVN=0;
const TInt KAlmAlertBldVN=66;
const TInt KAlmMessageSlots=5;

enum TAlmOpCode
    {
    EAlmOpCodeNotify,
    EAlmOpCodeCancel,
	EAlmOpCodeVisible,
    EAlmOpCodeSetState,
    EAlmOpCodeSetAlarm,
	EAlmOpCodeSetDeferTime,
	EAlmOpCodeGetUserTime,
	EAlmOpCodeLogon,
	EAlmOpCodeStartPlayingSound,
	EAlmOpCodeStopPlayingSound
    };

enum TAlmAlertResponse
	{
	EAlertResponseSilence,
	EAlertResponseQuietPeriod,
	EAlertResponseClear,
	EAlertResponseClearAll,
	EAlertResponseSnooze,
	EAlertResponsePauseSound
	};	

enum TAlarmServerStateFlag
	{
	EAlmSvrSoundOff=0x0001,
	EAlmSvrQuietPeriod=0x0002,
	EAlmSvrManyDueAlarms=0x0004,
	EAlmSvrNoSnoozeMemory=0x0008,
	EAlmSvrNoSoundToPlay=0x0010,
	EAlmSvrSoundPaused=0x0020
	};	

#endif
