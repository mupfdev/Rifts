// EIKSRV.PAN
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//
#if !defined(__EIKSRV_PAN__)
#define __EIKSRV_PAN__

#define __EIKON_SERVER _L("Eikon server")

enum TEikServPanic
	{
	EEikServPanicNotifyServiceNotSupported,
	EEikServPanicNotifyBadDescriptor,
	EEikServPanicAlarmAlertServiceNotSupported,
	EEikServPanicNoTaskListDialog,
	EEikServPanicTaskNull,
	EEsPanicAlarmAlert,
	EEikServPanicAlarmAlertServerAlreadyConnected,
	EEikServEnvPanicNullAppUi,
	EEikServPanicNoSuchLabelInAlarm
	};

GLREF_C void Panic(TEikServPanic aPanic);
#endif
