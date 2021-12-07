// ET_CLSVR.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined (__ET_CLISVR_H__)
#define __ET_CLISVR_H__

#define IPC_ETEL_CORE   (0)

enum
	{
//
// Open, Close and Debug
//
	EEtelOpenFromSession=IPC_ETEL_CORE,
	EEtelOpenFromSubSession,				// 01
	EEtelOpenByNameFromSession,				// 02
	EEtelOpenByNameFromSubSession,			// 03
	EEtelClose,								// 04
	EEtelCancelSubSession,					// 05
//
// Server
//
	EEtelServerOpen,						// 06
	EEtelServerLoadPhoneModule,				// 07
	EEtelServerClosePhoneModule,			// 08
	EEtelServerEnumeratePhones,				// 09
	EEtelServerPhoneInfoByIndex,			// 10
	EEtelServerSetPriorityClient,			// 11
	EEtelServerQueryTsyFunctionality,		// 12
	EEtelServerGetTsyName,					// 13
	EEtelServerSetExtendedErrorGranularity,	// 14
//
// Phone
//
	EEtelPhoneInitialise,					// 15
	EEtelPhoneInitialiseCancel,				// 16
	EEtelPhoneNotifyModemDetected,			// 17
	EEtelPhoneNotifyModemDetectedCancel,	// 18
	EEtelPhoneGetInfo,						// 19
	EETelPhoneCapsChangeNotification,		// 20
	EETelPhoneCapsChangeNotificationCancel,	// 21
	EEtelPhoneGetCaps,						// 22
	EEtelPhoneGetStatus,					// 23
	EEtelPhoneEnumerateLines,				// 24
	EEtelPhoneGetLineInfo,					// 25
//
// Line
//
	EEtelLineGetInfo,						// 26
	EEtelLineNotifyIncomingCall,			// 27
	EEtelLineNotifyIncomingCallCancel,		// 28
	EEtelLineNotifyHookChange,				// 29
	EEtelLineNotifyHookChangeCancel,		// 30
	EEtelLineNotifyStatusChange,			// 31
	EEtelLineNotifyStatusChangeCancel,		// 32
	EEtelLineNotifyCallAdded,				// 33
	EEtelLineNotifyCallAddedCancel,			// 34
	EETelLineCapsChangeNotification,		// 35
	EETelLineCapsChangeNotificationCancel,	// 36
	EEtelLineGetCaps,						// 37
	EEtelLineGetStatus,						// 38
	EEtelLineGetHookStatus,					// 39
	EEtelLineEnumerateCall,					// 40
	EEtelLineGetCallInfo,					// 41
//
// Call
//
	EEtelCallGetInfo,						// 42
	EEtelCallNotifyHookChange,				// 43
	EEtelCallNotifyStatusChange,			// 44
	EEtelCallNotifyDurationChange,			// 45
	EEtelCallCapsChangeNotification,		// 46
	EEtelCallAcquireOwnership,				// 47
	EEtelCallDial,							// 48
	EEtelCallConnect,						// 49
	EEtelCallAnswer,						// 50
	EEtelCallHangUp,						// 51

	EEtelCallNotifyHookChangeCancel,		// 52
	EEtelCallNotifyStatusChangeCancel,		// 53
	EEtelCallNotifyDurationChangeCancel,	// 54
	EEtelCallCapsChangeNotificationCancel,	// 55
	EEtelCallAcquireOwnershipCancel,		// 56
	EEtelCallDialCancel,					// 57
	EEtelCallConnectCancel,					// 58
	EEtelCallAnswerCancel,					// 59
	EEtelCallHangUpCancel,					// 60
	EEtelCallLoanDataPortCancel,			// 61

	EEtelCallGetStatus,						// 62
	EEtelCallGetCaps,						// 63
	EEtelCallLoanDataPort,					// 64
	EEtelCallRecoverDataPort,				// 65
	EEtelCallTransferOwnership,				// 66
	EEtelCallGetBearerServiceInfo,			// 67
	EEtelCallGetOwnershipStatus,			// 68
	EEtelCallGetCallParams,					// 69
	EEtelCallGetCallDuration,				// 70
	EEtelCallGetFaxSettings,				// 71
	EEtelCallSetFaxSettings,				// 72
//
// Etel Fax
//
	EEtelFaxRead,							// 73
	EEtelFaxWrite,							// 74
	EEtelFaxWaitForEndOfPage,				// 75
	EEtelFaxTerminateFaxSession,			// 76

#if defined (_DEBUG)
	EEtelDbgMarkHeap,						// 77
	EEtelDbgCheckHeap,						// 78
	EEtelDbgMarkEnd,						// 79
	EEtelDbgFailNext,						// 80
	EEtelDbgSetDebugPrintMask,				// 81
	EEtelDbgDoDumpDebugInfo,				// 82


#endif
	EEtelServerGetTsyVersionNo,				// 83
//
// ETel Call
// 
	EEtelCallReferenceCount				// 84
	};

#endif
