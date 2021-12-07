// BSCGSMCS.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined (__BSCGSMIPC_H__)
#define __BSCGSMIPC_H__

#if !defined (__ETELBGSM_H__)
#include "ETelBgsm.h"
#endif

#define IPC_GSM_BSC_EXT (1000)
									   
enum
	{
//
// Phone
//
	EGsmPhoneGetGsmPhoneId=IPC_GSM_BSC_EXT,			// 1000
	EGsmPhoneGetSignalStrength,						// 1001
	EGsmPhoneGetSignalStrengthCancel,				// 1002
	EGsmPhoneSignalStrengthNotification,			// 1003
	EGsmPhoneSignalStrengthNotificationCancel,		// 1004
	EGsmPhoneGetBer,								// 1005
	EGsmPhoneGetBerCancel,							// 1006
	EGsmPhoneBerNotification,						// 1007
	EGsmPhoneBerNotificationCancel,					// 1008
	EGsmPhoneGetSignalBerCaps,						// 1009
	EGsmPhoneSignalBerCapsChangeNotification,		// 1010
	EGsmPhoneSignalBerCapsChangeNotificationCancel,	// 1011
	EGsmPhoneGetBasicNetworkCaps,					// 1012
	EGsmPhoneEnumeratePhoneBooks,					// 1013
	EGsmPhoneGetPhoneBookInfo,						// 1014
	EGsmPhoneEnumerateDetectedNetwork,				// 1015
	EGsmPhoneEnumerateDetectedNetworkCancel,		// 1016
	EGsmPhoneGetNetworkInfo,						// 1017
	EGsmPhoneGetNetworkInfoCancel,					// 1018
	EGsmPhoneSetNetworkMode,						// 1019
	EGsmPhoneSetNetworkModeCancel,					// 1020
	EGsmPhoneRetrieveDetectedNetworksPhase1,		// 1021
	EGsmPhoneRetrieveDetectedNetworksPhase1Cancel,	// 1022
	EGsmPhoneRetrieveDetectedNetworksPhase2,		// 1023
	EGsmPhoneRetrieveDetectedNetworksPhase2Cancel,	// 1024
	EGsmPhoneSetManualNetwork,						// 1025
	EGsmPhoneSetManualNetworkCancel,				// 1026
	EGsmPhoneGetCurrentNetworkInfo,					// 1027
	EGsmPhoneNotifyChangeOfCurrentNetwork,			// 1028
	EGsmPhoneNotifyChangeOfCurrentNetworkCancel,	// 1029
	EGsmPhoneGetBatteryInfo,						// 1030
	EGsmPhoneGetBatteryInfoCancel,					// 1031
	EGsmPhoneBatteryInfoNotification,				// 1032
	EGsmPhoneBatteryInfoNotificationCancel,			// 1033
	EGsmPhoneGetBatteryAndPowerCaps,				// 1034
	EGsmPhoneIndicatorNotification,					// 1035
	EGsmPhoneIndicatorNotificationCancel,			// 1036
	EGsmPhoneGetIndicator,							// 1037
	EGsmPhoneGetIndicatorCaps,						// 1038
	EGsmPhoneReadClock,								// 1039
	EGsmPhoneEnumerateAlarm,						// 1040
	EGsmPhoneGetAlarm,								// 1041
	EGsmPhoneSetAlarm,								// 1042
	EGsmPhoneSetClock,								// 1043
	EGsmPhoneGetClockCaps,							// 1044
	EGsmPhoneClockCapsChangeNotification,			// 1045
	EGsmPhoneClockCapsChangeNotificationCancel,		// 1046
	EGsmPhoneGetInfoBasic,							// 1047
	EGsmPhoneGetNetworkRegistrationStatus,			// 1048
	EGsmPhoneNotifyChangeOfNetworkRegistrationStatus,		// 1049
	EGsmPhoneNotifyChangeOfNetworkRegistrationStatusCancel,	// 1050
	EGsmPhoneGetNetworkSearchMode,							// 1051
	EGsmPhoneNotifyChangeOfNetworkSearchMode,				// 1052
	EGsmPhoneNotifyChangeOfNetworkSearchModeCancel,			// 1053
//
// Call
//
	EGsmCallBasicGetCaps,							// 1054
	EGsmCallBasicCapsChangeNotification,			// 1055
	EGsmCallBasicCapsChangeNotificationCancel,		// 1056
	EGsmCallGetInfoBasic,							// 1057

//
// Gsm PhoneBook
//
	EGsmPhoneBookGetGsmCaps,						// 1058
	EGsmPhoneBookAddressAddedNotification,			// 1059
	EGsmPhoneBookAddressAddedNotificationCancel,	// 1060
	EGsmPhoneBookAddressRemovedNotification,		// 1061
	EGsmPhoneBookAddressRemovedNotificationCancel,	// 1062
	EGsmPhoneBookEntryChangedNotification, 			// 1063
	EGsmPhoneBookEntryChangedNotificationCancel,	// 1064
	EGsmPhoneBookGetInfo,							// 1065
	EGsmPhoneBookGetInfoCancel,						// 1066
	EGsmPhoneBookRead,								// 1067
	EGsmPhoneBookReadCancel,						// 1068
	EGsmPhoneBookReadFirst,							// 1069
	EGsmPhoneBookReadFirstCancel,					// 1070
	EGsmPhoneBookReadPrevious,						// 1071
	EGsmPhoneBookReadPreviousCancel,				// 1072
	EGsmPhoneBookReadNext,							// 1073
	EGsmPhoneBookReadNextCancel,					// 1074
	EGsmPhoneBookWrite,								// 1075
	EGsmPhoneBookWriteCancel,						// 1076
	EGsmPhoneBookDelete,							// 1077
	EGsmPhoneBookDeleteCancel,						// 1078
	EGsmPhoneBookSearchPhase1,						// 1079
	EGsmPhoneBookSearchPhase2,						// 1080
	EGsmPhoneBookSearchPhase1Cancel,				// 1081
	EGsmPhoneBookSearchPhase2Cancel,		   		// 1082

//
// Gsm Sms Storage
//
	ESmsStorageGetInfo,								// 1083
	ESmsStorageGetInfoCancel,						// 1084
	ESmsStorageReadSms,								// 1085
	ESmsStorageReadSmsCancel,						// 1086
	ESmsStorageWrite,								// 1087
	ESmsStorageWriteCancel,							// 1088
	ESmsStorageDelete,								// 1089
	ESmsStorageDeleteCancel,						// 1090
	ESmsStorageWriteNotification,					// 1091
	ESmsStorageWriteNotificationCancel,				// 1092

//
//	RSmsMessaging
//
	ESmsMessagingGetCaps,							// 1093
	ESmsMessagingSetMode,							// 1094
	ESmsMessagingGetMode,							// 1095
	ESmsMessagingGetSCAddress,						// 1096
	ESmsMessagingSetSCAddress,						// 1097
	ESmsMessagingSetSCAddressCancel,				// 1098
	ESmsMessagingSendMessage,						// 1099
	ESmsMessagingSendMessageCancel,					// 1100
	ESmsMessagingReadSmsMessage,					// 1101
	ESmsMessagingReadSmsMessageCancel,				// 1102
	ESmsMessagingNotifySmsMessageArrived,			// 1103
	ESmsMessagingNotifySmsMessageArrivedCancel,		// 1104
	ESmsMessagingEnumerateMessageStores,			// 1105
	ESmsMessagingGetMessageStoreInfo,				// 1106
	ESmsMessagingSetModeCancel,						// 1107		// added 29/1/99
	ESmsMessagingGetSCAddressCancel,				// 1108		// added 29/1/99
	ESmsMessagingGetMessageStoreInfoCancel,			// 1109		// added 29/1/99

	EGsmPhoneReadClockCancel,						// 1110		// added 1/2/99
	EGsmPhoneSetClockCancel,						// 1111		// added 1/2/99
	EGsmPhoneEnumerateAlarmCancel,					// 1112		// added 1/2/99
	EGsmPhoneGetAlarmCancel,						// 1113		// added 1/2/99
	EGsmPhoneSetAlarmCancel,						// 1114		// added 1/2/99
	EGsmPhoneGetPhoneBookInfoCancel,				// 1115		// added 1/2/99
//
// HSCSD Call Based, added 10/2/00
//
	EGsmCallGetHscsdCaps,							// 1116
	EGsmCallNotifyHscsdCaps,						// 1117
	EGsmCallNotifyHscsdCapsCancel,					// 1118
	EGsmCallSetHscsdParams,							// 1119
	EGsmCallGetHscsdParams,							// 1120
	EGsmCallGetDynamicHscsdParams,					// 1121
	EGsmCallNotifyDynamicHscsdParams,				// 1122
	EGsmCallNotifyDynamicHscsdParamsCancel,			// 1123
	EGsmCallSetDynamicHscsdParams,					// 1124
	EGsmCallSetDynamicHscsdParamsCancel				// 1125
	};

#endif
