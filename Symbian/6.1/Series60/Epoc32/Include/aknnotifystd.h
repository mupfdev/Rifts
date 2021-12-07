/*
* ============================================================================
*  Name     : AknNotify.Std.h
*  Part of  : Avkon
*
*  Description:
* 
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNNOTIFYSTD_H
#define AKNNOTIFYSTD_H

#include <e32std.h>
#include <e32base.h>
#include <eiknotapi.h>

// UIDs reserved from Uid list
const TUid KAknPopupNotifierUid={0x100059DC};
const TUid KAknSignalNotifierUid={0x100059AB};
const TUid KAknBatteryNotifierUid={0x100059AC};
const TUid KAknSmallIndicatorUid={0x100059AD};
const TUid KAknAsyncDemoNotifierUid={0x100059AE};
const TUid KAknTestNoteUid={0x100059AF};
const TUid KAknKeyLockNotifierUid={0x100059B0};
const TUid KAknGlobalNoteUid={0x100059B1};
const TUid KAknSoftNotificationUid={0x100059B2};
const TUid KAknIncallBubbleUid={0x100059B3};
const TUid KAknGlobalListQueryUid={0x100059B4}; 
const TUid KAknGlobalMsgQueryUid={0x100059CB};
const TUid KAknGlobalConfirmationQueryUid={0x100059DB};
const TUid KAknGlobalProgressDialogUid={0x10005A04};

const TUid EAknNotifierChannelKeyLock = {0};
const TUid EAknNotifierChannelNote = {1};
const TUid EAknNotifierChannelList = {2};
const TUid EAknNotifierChannelMsgQuery = {3};
const TUid EAknNotifierChannelConfirmationQuery = {4};
const TUid EAknNotifierChannelProgressDialog = {5};

struct SAknSignalNotifyParams
	{
    TInt iGprsState;
	TInt iValue;
	};

struct SAknBatteryNotifyParams
	{
	enum { ERecharge, EStopRecharge, ENoRecharge, ESetValue } iType;
	TInt iValue;
	};

struct SAknSmallIndicatorParams
	{
    TUid iSmallIndicatorUid;
	TInt iValue;
	};

struct SAknIncallBubbleParams
	{
	TInt iIncallBubbleFlags;
	};

// KeyLock reason
enum TKeyLockNotifierReason
	{
	ELockEnabled,
	ELockDisabled,
	EAllowNotifications,
	EStopNotifications,
	EInquire,
	EOfferKeylock,
	ECancelAllNotifications
	};

struct SAknSoftNoteNotifierParams
	{
	TInt iNoteResource;
	TInt iNoteCbaResource;
	TInt iResponse;
	};

struct SAknKeyLockNotifierParams
	{
	TKeyLockNotifierReason iReason;
	TBool iEnabled;
	};

enum TAknGlobalNoteType
	{
	EAknGlobalInformationNote = 1,
	EAknGlobalWarningNote,
	EAknGlobalConfirmationNote,
	EAknGlobalErrorNote,
	EAknGlobalChargingNote,
	EAknGlobalWaitNote,
	EAknGlobalPermanentNote,
	EAknGlobalNotChargingNote,
	EAknGlobalBatteryFullNote,
	EAknGlobalBatteryLowNote,
	EAknGlobalRechargeBatteryNote,
	EAknCancelGlobalNote
	};

struct SAknGlobalNoteParams
	{
	TAknGlobalNoteType iType;
	TPtrC iText;
	TInt iPriority;
	TInt iSoftkeys;
	TInt iGraphic;
	TInt iGraphicMask;
	TInt iAnimation;
	};

struct SAknGlobalNoteReturnParams
	{
	TInt iNoteId;
	};


enum TAknGlobalQueryCmd
    {
    EAknShowGlobalQuery=1,
    EAknCancelGlobalQuery,
    EAknUpdateGlobalQuery,
    // list query cmds,
    EAknMoveDownGlobalListQuery,
    EAknMoveUpGlobalListQuery,
    EAknSelectGlobalListQuery,
    // Progess dialog cmds
    EAknFinishGlobalProgressDialog
    };

struct SAknGlobalListQueryParams
    {
    TAknGlobalQueryCmd iCmd;
    TInt iIndex;
    };

struct SAknGlobalMsgQueryParams
	{
    TAknGlobalQueryCmd iCmd;
	TInt iSoftkeys;
	};

struct SAknGlobalProgressDialogParams
	{
    TAknGlobalQueryCmd iCmd;
	TInt iValue;
	TInt iFinalValue;
	};

enum TAknSoftNotificationType
	{
	ENoSoftNotification = -1,
	ENetworkInformationNotification=0,
	ESelectNetworkNotification,
	EUnstructuredSSDataNotification,
	EVoiceMailNotification,
	ESeparateVoiceMailOnLine1Notification,
	ESeparateVoiceMailOnLine2Notification,
	ECellBroadcastNotification,

	EDeliveryReportNotification,
	EClass0SmsNotification,

	EMissedCallsNotification,
	ENewMessagesNotification,
	ENewMailNotification,

	EShowActiveNotifications,

	EShowGroupedNotification,
    ECustomSoftNotification,
	EMaxSoftNotification,
	ESetIdleState = 100
	};

struct SAknSoftNotificationParams
	{
	//The type of the soft notification, see above
	TAknSoftNotificationType iType;	
	//iIsCancel is used to decide whether to spawn a new (or add the number on an existing)
	//soft notification or to cancel a type of soft notification. Please note that
	//calling a cancel on a certain type of soft notification cancels all soft notifications
	//of that type.
	TBool iIsCancel;

    //This parameter is intended only to be used when setting the number of new messages.
    //Stay clear otherwise!
    TInt iCount;
	};

enum TAknSignalStates
    {
    EAknSignalGprsStateOff = 0,
    EAknSignalGprsStateOn = 1,
    EAknSignalGprsStateNotChanged = -1,
    EAknSignalStateNotChanged = -2,
    };

const TInt KAknSignalNumberOfGprsStates = 5;

#endif // AKNNOTIFYSTD_H
