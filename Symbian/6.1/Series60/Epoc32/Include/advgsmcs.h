// ADVGSMCS.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined (__ADVGSMIPC_H__)
#define __ADVGSMIPC_H__

#if !defined (__ETELAGSM_H__)
#include "ETelAgsm.h"
#endif

#define IPC_GSM_ADV_EXT (2000)

_LIT(KMainCallGroupName,"Main");
_LIT(KHoldCallGroupName,"Hold");
_LIT(KWaitingCallGroupName,"Waiting");
									   
enum
	{
//
// Phone
//
	EGsmPhoneGetOwnNumberInfo=IPC_GSM_ADV_EXT,		// 2000
	EGsmPhoneGetOwnNumberInfoCancel,				// 2001
	EGsmPhoneGetOwnNumberEntry,						// 2002
	EGsmPhoneGetOwnNumberEntryCancel,				// 2003
	EGsmPhoneSetOwnNumberEntry,						// 2004
	EGsmPhoneSetOwnNumberEntryCancel,				// 2005
	EGsmPhoneNotifyOwnNumberChanged,				// 2006
	EGsmPhoneNotifyOwnNumberChangedCancel,			// 2007
	EGsmPhoneGetCurrentNITZInfo,					// 2008
	EGsmPhoneNotifyNITZInfoChange,					// 2009
	EGsmPhoneNotifyNITZInfoChangeCancel,			// 2010

	// MAdvGsmLineIdentity
	EGsmPhoneGetClipMode,							// 2011
	EGsmPhoneGetClipModeCancel,						// 2012
	EGsmPhoneClipModeNotification,					// 2013
	EGsmPhoneClipModeNotificationCancel,			// 2014
	EGsmPhoneGetClirMode,							// 2015
	EGsmPhoneGetClirModeCancel,						// 2016
	EGsmPhoneClirModeNotification,					// 2017
	EGsmPhoneClirModeNotificationCancel,			// 2018
	EGsmPhoneGetColpMode,							// 2019
	EGsmPhoneGetColpModeCancel,						// 2020
	EGsmPhoneColpModeNotification,					// 2021
	EGsmPhoneColpModeNotificationCancel,			// 2022
	EGsmPhoneGetColrMode,							// 2023
	EGsmPhoneGetColrModeCancel,						// 2024
	EGsmPhoneColrModeNotification,					// 2025
	EGsmPhoneColrModeNotificationCancel,			// 2026
	EGsmPhoneGetNetworkSetCaps,						// 2027
	EGsmPhoneNetworkSetCapsChangeNotification,		// 2028
	EGsmPhoneNetworkSetCapsChangeNotificationCancel,// 2029
	EGsmPhoneRetrievePrefNetworksPhase1,			// 2030
	EGsmPhoneRetrievePrefNetworksPhase1Cancel,		// 2031
	EGsmPhoneRetrievePrefNetworksPhase2,			// 2032
	EGsmPhoneRetrievePrefNetworksPhase2Cancel,		// 2033
	EGsmPhoneStorePrefNetworks,						// 2034
	EGsmPhoneStorePrefNetworksCancel,				// 2035
	EGsmPhoneNotifyPreferredNetworksChanged,		// 2036
	EGsmPhoneNotifyPreferredNetworksChangedCancel,	// 2037
	EGsmPhoneGetHomeNetworkInfo,					// 2038
	EGsmPhoneGetHomeNetworkInfoCancel,				// 2039
	EGsmPhoneNetworkMultipleRead,					// 2040
	EGsmPhoneNetworkMultipleReadCancel,				// 2041
	EGsmPhoneGetLockInfo,							// 2042
	EGsmPhoneGetLockInfoCancel,						// 2043
	EGsmPhoneChangeLockSetting,						// 2044
	EGsmPhoneChangeLockSettingCancel,				// 2045
	EGsmPhoneNotifyLockInfoChanged,					// 2046
	EGsmPhoneNotifyLockInfoChangedCancel,			// 2047
	EGsmPhoneChangePassword,						// 2048
	EGsmPhoneChangePasswordCancel,					// 2049
	EGsmPhoneGetSecurityCaps,						// 2050
	EGsmPhoneSecurityCapsChangeNotification,		// 2051
	EGsmPhoneSecurityCapsChangeNotificationCancel,	// 2052
	EGsmPhoneSecurityEventNotification,				// 2053
	EGsmPhoneSecurityEventNotificationCancel,		// 2054
	EGsmPhoneSendSecurityCode,						// 2055
	EGsmPhoneSendSecurityCodeCancel,				// 2056
	EGsmPhoneSendUnblockCode,						// 2057
	EGsmPhoneSendUnblockCodeCancel,					// 2058
	EGsmPhoneAbortSecurityCode,						// 2059
	EGsmPhoneAbortSecurityCodeCancel,				// 2060
	EGsmPhoneAbortUnblockCode,						// 2061
	EGsmPhoneAbortUnblockCodeCancel,				// 2062
	EGsmPhoneClearAcm,								// 2063
	EGsmPhoneClearAcmCancel,						// 2064
	EGsmPhoneSetAcmMax,								// 2065
	EGsmPhoneSetAcmMaxCancel,						// 2066
	EGsmPhoneSetAcmMaxWithUnits,					// 2067
	EGsmPhoneSetAcmMaxWithUnitsCancel,				// 2068
	EGsmPhoneSetPuct,								// 2069
	EGsmPhoneSetPuctCancel,							// 2070
	EGsmPhoneGetAocSimInfo,							// 2071
	EGsmPhoneGetAocSimInfoCancel,					// 2072
	EGsmPhoneNotifyAocSimInfoChanged,				// 2073
	EGsmPhoneNotifyAocSimInfoChangedCancel,			// 2074
	EGsmPhoneGetAocDynamicInfo,						// 2075
	EGsmPhoneGetAocDynamicInfoCancel,				// 2076
	EGsmPhoneNotifyAocInfoChanged,					// 2077
	EGsmPhoneNotifyAocInfoChangedCancel,			// 2078
	EGsmPhoneGetAocCaps,							// 2079
	EGsmPhoneGetAocCapsCancel,						// 2080
	EGsmPhoneSetFdnMode,							// 2081
	EGsmPhoneSetFdnModeCancel,						// 2082
	EGsmPhoneGetFdnMode,							// 2083
	EGsmPhoneGetFdnModeCancel,						// 2084
	EGsmPhoneNotifyFdnModeChanged,					// 2085
	EGsmPhoneNotifyFdnModeChangedCancel,			// 2086
	EGsmPhoneGetAirTimeDuration,					// 2087
	EGsmPhoneGetAirTimeDurationCancel,				// 2088
	EGsmPhoneAirTimeDurationChangeNotification,		// 2089
	EGsmPhoneAirTimeDurationChangeNotificationCancel,// 2090
	EGsmPhoneGetInfoAdv,							// 2091
	EGsmPhoneGetInfoAdvCancel,						// 2092
	EGsmPhoneGetAdvGsmLineInfo,						// 2093
	EGsmPhoneGetCallForwardingInfo,					// 2094
	EGsmPhoneGetCallForwardingInfoCancel,			// 2095
	EGsmPhoneSetCallForwardingInfo,					// 2096
	EGsmPhoneSetCallForwardingInfoCancel,			// 2097
	EGsmPhoneCallForwardingStatusNotification,		// 2098
	EGsmPhoneCallForwardingStatusNotificationCancel,// 2099
	EGsmPhoneGetForwardingCaps,						// 2100
	EGsmPhoneGetForwardingCapsCancel,				// 2101
	EGsmPhoneGetCallBarringMode,					// 2102
	EGsmPhoneGetCallBarringModeCancel,				// 2103
	EGsmPhoneSetCallBarringMode,					// 2104
	EGsmPhoneSetCallBarringModeCancel,				// 2105
	EGsmPhoneNotifyCallBarringModeChange,			// 2106
	EGsmPhoneNotifyCallBarringModeChangeCancel,		// 2107
	EGsmPhoneChangeBarringPassword,					// 2108
	EGsmPhoneChangeBarringPasswordCancel,			// 2109
	EGsmPhoneGetBarringCaps,						// 2110
	EGsmPhoneGetBarringCapsCancel,					// 2111
	EGsmPhoneGetCallWaitingMode,					// 2112
	EGsmPhoneGetCallWaitingModeCancel,				// 2113
	EGsmPhoneSetCallWaitingMode,					// 2114
	EGsmPhoneSetCallWaitingModeCancel,				// 2115
	EGsmPhoneNotifyCallWaitingModeChange,			// 2116
	EGsmPhoneNotifyCallWaitingModeChangeCancel,		// 2117
	EGsmPhoneSendSSString,							// 2118
	EGsmPhoneSendSSStringCancel,					// 2119
	EGsmPhoneSendDTMFTones,							// 2120
	EGsmPhoneSendDTMFTonesCancel,					// 2121
	EGsmPhoneReadDTMFTones,							// 2122
	EGsmPhoneReadDTMFTonesCancel,					// 2123
	EGsmPhoneDTMFEventNotification,					// 2124
	EGsmPhoneDTMFEventNotificationCancel,			// 2125
	EGsmPhoneStartDTMFTone,							// 2126
	EGsmPhoneStartDTMFToneCancel,					// 2127
	EGsmPhoneStopDTMFTone,							// 2128
	EGsmPhoneStopDTMFToneCancel,					// 2129
	EGsmPhoneSkipDTMFPause,							// 2130
	EGsmPhoneSkipDTMFPauseCancel,					// 2131
	EGsmPhoneEnumerateMasterListNetworks,			// 2132
	EGsmPhoneEnumerateMasterListNetworksCancel,		// 2133
	EGsmPhoneGetMasterListNetworkInfo,				// 2134
	EGsmPhoneGetMasterListNetworkInfoCancel,		// 2135
	EGsmPhoneRetrieveSimEmergencyListPhase1,		// 2136
	EGsmPhoneRetrieveSimEmergencyListPhase2,		// 2137
	EGsmPhoneRetrieveSimEmergencyListPhase1Cancel,	// 2138
	EGsmPhoneRetrieveSimEmergencyListPhase2Cancel,	// 2139
	EGsmPhoneGetAlternatingModeCaps,				// 2140
	EGsmPhoneSetALSLine,							// 2141
	EGsmPhoneSetALSLineCancel,						// 2142
	EGsmPhoneGetALSLine,							// 2143
	EGsmPhoneGetALSLineCancel,						// 2144
	EGsmPhoneNotifyALSLineChange,					// 2145
	EGsmPhoneNotifyALSLineChangeCancel,				// 2146
	EGsmPhoneDeactivateAllCcbs,						// 2147
	EGsmPhoneDeactivateAllCcbsCancel,				// 2148
	EGsmPhoneGetCcbsStatus,							// 2149
	EGsmPhoneGetCcbsStatusCancel,					// 2150
	EGsmPhoneRetrieveCcbsRequestsPhase1,			// 2151
	EGsmPhoneRetrieveCcbsRequestsPhase2,			// 2152
	EGsmPhoneRetrieveCcbsRequestsPhase1Cancel,		// 2153
	EGsmPhoneRetrieveCcbsRequestsPhase2Cancel,		// 2154
	EGsmPhoneRetrievePrefLanguagePhase1,			// 2155
	EGsmPhoneRetrievePrefLanguagePhase2,			// 2156
	EGsmPhoneRetrievePrefLanguagePhase1Cancel,		// 2157
	EGsmPhoneRetrievePrefLanguagePhase2Cancel,		// 2158
	EGsmPhoneStorePrefLanguages,					// 2159
	EGsmPhoneStorePrefLanguagesCancel,				// 2160
	EGsmPhoneNotifyPrefLanguagesChanged,			// 2161
	EGsmPhoneNotifyPrefLanguagesChangedCancel,		// 2162
	EGsmPhoneGetCsp,								// 2163
	EGsmPhoneGetCspCancel,							// 2164
	EGsmPhoneGetSst,								// 2165
	EGsmPhoneGetSstCancel,							// 2166
	EGsmPhoneGetSubscriberId,						// 2167
	EGsmPhoneGetSubscriberIdCancel,					// 2168
//
// Line
//
	EGsmLineGetGsmStatus,							// 2169
	EGsmLineGsmStatusNotification,					// 2170
	EGsmLineGsmStatusNotificationCancel,			// 2171
	EGsmLineGetAdvCallInfo,							// 2172
	EGsmLineGetAdvGsmLineCaps,						// 2173
	EGsmLineGetBarringMode,							// 2174
	EGsmLineGetBarringModeCancel,					// 2175
	EGsmLineSetBarringMode,							// 2176
	EGsmLineSetBarringModeCancel,					// 2177
	EGsmLineBarringModeNotification,				// 2178
	EGsmLineBarringModeNotificationCancel,			// 2179
	EGsmLineGetCallForwardingInfo,					// 2180
	EGsmLineGetCallForwardingInfoCancel,			// 2181
	EGsmLineGetCallForwardingStatus,				// 2182
	EGsmLineGetCallForwardingStatusCancel,			// 2183
	EGsmLineSetCallForwardingStatus,				// 2184
	EGsmLineSetCallForwardingStatusCancel,			// 2185
	EGsmLineCallForwardingStatusNotification,		// 2186
	EGsmLineCallForwardingStatusNotificationCancel,	// 2187
	EGsmLineCallForwardingActiveNotification,		// 2188
	EGsmLineCallForwardingActiveNotificationCancel,	// 2189
	EGsmLineGetCallWaitingMode,						// 2190
	EGsmLineGetCallWaitingModeCancel,				// 2191
	EGsmLineSetCallWaitingMode,						// 2192
	EGsmLineSetCallWaitingModeCancel,				// 2193
	EGsmLineCallWaitingNotification,				// 2194
	EGsmLineCallWaitingNotificationCancel,			// 2195
	EGsmLineTransfer,								// 2196
	EGsmLineCallSwap,								// 2197
	EGsmLineCallSwapCancel,							// 2198
	EGsmLineGetInfoAdv,								// 2199
	EGsmLineAutoRetry,								// 2200
	EGsmLineAutoRetryCancel,						// 2201

//
// Call
//
	EGsmCallGetGsmStatus,							// 2202
	EGsmCallGsmStatusNotification,					// 2203
	EGsmCallGsmStatusNotificationCancel,			// 2204
	EGsmCallHold,									// 2205
	EGsmCallHoldCancel,								// 2206
	EGsmCallToggleHold,								// 2207
	EGsmCallToggleHoldCancel,						// 2208
	EGsmCallOneToOne,								// 2209
	EGsmCallOneToOneCancel,							// 2210
	EGsmCallECT,									// 2211
	EGsmCallECTCancel,								// 2212
	EGsmCallResume,									// 2213
	EGsmCallResumeCancel,							// 2214
	EGsmCallDeflectCall,							// 2215
	EGsmCallDeflectCallCancel,						// 2216
	EGsmCallEventNotification,						// 2217
	EGsmCallEventNotificationCancel,				// 2218
	EGsmCallGetCallInformationCaps,					// 2219
	EGsmCallGetCallId,								// 2220
	EGsmCallGetCallIdCancel,						// 2221
	EGsmCallNotifyCallIdChanged,					// 2222
	EGsmCallNotifyCallIdChangedCancel,				// 2223
	EGsmCallGetCallStartTime,						// 2224
	EGsmCallGetCallStartTimeCancel,					// 2225
	EGsmCallGetCallGroup,							// 2226
	EGsmCallGetCallGroupCancel,						// 2227
	EGsmCallNotifyCallGroupChanged,					// 2228
	EGsmCallNotifyCallGroupChangedCancel,			// 2229
	EGsmCallGetRemotePartyInfo,						// 2230
	EGsmCallGetRemotePartyInfoCancel,				// 2231
	EGsmCallNotifyRemotePartyInfoChanged,			// 2232
	EGsmCallNotifyRemotePartyInfoChangedCancel,		// 2233
	EGsmCallGetDialledNumberInfo,					// 2234
	EGsmCallGetDialledNumberInfoCancel,				// 2235
	EGsmCallGetLastExitCode,						// 2236
	EGsmCallGetLastExitCodeCancel,					// 2237
	EGsmCallGetSSStringPrefix,						// 2238
	EGsmCallGetSSStringPrefixCancel,				// 2239
	EGsmCallGetControlCaps,							// 2240
	EGsmCallControlCapsChangeNotification,			// 2241
	EGsmCallControlCapsChangeNotificationCancel,	// 2242
	EGsmCallGetGsmCallParams,						// 2243
	EGsmCallSetGsmCallParams,						// 2244
	EGsmCallGetCallMeter,							// 2245
	EGsmCallGetCallMeterCancel,						// 2246
	EGsmCallNotifyCallMeterChanged,					// 2247
	EGsmCallNotifyCallMeterChangedCancel,			// 2248
	EGsmCallSetAlternatingCallMode,					// 2249
	EGsmCallGetAlternatingCallMode,					// 2250
	EGsmCallNotifyAlternatingCallModeChanged,		// 2251
	EGsmCallNotifyAlternatingCallModeChangedCancel,	// 2252
	EGsmCallWaitForCallModeSwitch,					// 2253
	EGsmCallWaitForCallModeSwitchCancel,			// 2254
	EGsmCallSwitchCallMode,							// 2255
	EGsmCallSwitchCallModeCancel,					// 2256
	EGsmCallNotifyRemoteCallModeSwitch,				// 2257
	EGsmCallNotifyRemoteCallModeSwitchCancel,		// 2258
	EGsmCallActivateCCBS,							// 2259
	EGsmCallActivateCCBSCancel,						// 2260
	EGsmCallRejectCCBS,								// 2261
	EGsmCallRejectCCBSCancel,						// 2262
	EGsmCallAcceptCCBSRecall,						// 2263
	EGsmCallAcceptCCBSRecallCancel,					// 2264
	EGsmCallDeactivateCCBS,							// 2265
	EGsmCallDeactivateCCBSCancel,					// 2266
	EGsmCallMakeEmergencyCall,						// 2267
	EGsmCallMakeEmergencyCallCancel,				// 2268
	EGsmCallGetInfoAdv,								// 2269
	EGsmCallGetInfoAdvCancel,						// 2270
	EGsmCallGetDTMFInDialString,					// 2271
	EGsmCallGetDTMFInDialStringCancel,				// 2272
	EGsmCallGetEmergencyCallFlag,					// 2273
	EGsmCallGetForwardedCallFlag,					// 2274
	EGsmCallGetAutoRetryCallFlag,					// 2275
	EGsmCallGetCcbsActiveFlag,						// 2276


//
// Call Groups
//
	EGsmCallGroupEnumerateCalls,					// 2277
	EGsmCallGroupGetCallInfo,						// 2278
	EGsmCallGroupSwap,								// 2279
	EGsmCallGroupSwapCancel,						// 2280
	EGsmCallGroupHangUp,							// 2281
	EGsmCallGroupHangUpCancel,						// 2282
	EGsmCallGroupJoin,								// 2283
	EGsmCallGroupJoinCancel,						// 2284
	EGsmCallGroupHoldAndAnswer,						// 2285
	EGsmCallGroupHoldAndAnswerCancel,				// 2286
	EGsmCallGroupHangUpAndAnswer,					// 2287
	EGsmCallGroupHangUpAndAnswerCancel,				// 2288
	EGsmCallGroupChangeNotification,				// 2289
	EGsmCallGroupChangeNotificationCancel,			// 2290
	EGsmCallGroupGetCaps,							// 2291
	EGsmCallGroupCapsChangeNotification,			// 2292
	EGsmCallGroupCapsChangeNotificationCancel,		// 2293

//
// Phone Book
//
	EAdvGsmPhoneBookGetFirstEmpty,					// 2294
	EAdvGsmPhoneBookGetFirstEmptyCancel,			// 2295
	EAdvGsmPhoneBookIsSlotUnused,					// 2296
	EAdvGsmPhoneBookIsSlotUnusedCancel,				// 2297
	EAdvGsmPhoneBookMultipleRead,					// 2298
	EAdvGsmPhoneBookMultipleReadCancel,				// 2399
	EAdvGsmPhoneBookSearchBasicPhase1,				// 2300 - used if search order is alphanumeric - this isn't basic GSM functionality
	EAdvGsmPhoneBookSearchBasicPhase1Cancel,		// 2301
	EAdvGsmPhoneBookSearchAnyTextPhase1,			// 2302
	EAdvGsmPhoneBookSearchAnyTextPhase1Cancel,		// 2303
	EAdvGsmPhoneBookSearchAnyTextPhase2,			// 2304
	EAdvGsmPhoneBookSearchAnyTextPhase2Cancel,		// 2305
	EAdvGsmPhoneBookSearchBasicPhase2,				// 2306
	EAdvGsmPhoneBookSearchBasicPhase2Cancel,		// 2307
	EAdvGsmPhoneBookSearchByNumberPhase1,			// 2308
	EAdvGsmPhoneBookSearchByNumberPhase1Cancel,		// 2309
	EAdvGsmPhoneBookSearchByNumberPhase2,			// 2310
	EAdvGsmPhoneBookSearchByNumberPhase2Cancel,		// 2311
	EAdvGsmPhoneBookWrite,							// 2312
	EAdvGsmPhoneBookWriteCancel,					// 2313
	EAdvGsmPhoneBookDelete,							// 2314
	EAdvGsmPhoneBookDeleteCancel,					// 2315

	// SMS Messaging
	EAdvSmsMessagingGetSmsReportCaps,				// 2316
	EAdvSmsMessagingGetSmsReportResp,				// 2317
	EAdvSmsMessagingSetSmsReportResp,				// 2318
	EAdvSmsMessagingSendAdvSmsMessage,				// 2319
	EAdvSmsMessagingSendAdvSmsMessageCancel,		// 2320
	EAdvSmsMessagingAckSmsMessageWithPdu,			// 2321
	EAdvSmsMessagingAckSmsMessageWithPduCancel,		// 2322
	EAdvSmsMessagingAckSmsMessage,					// 2323
	EAdvSmsMessagingAckSmsMessageCancel,			// 2324
	EAdvSmsMessagingNackSmsMessage,					// 2325
	EAdvSmsMessagingNackSmsMessageCancel,			// 2326
	EAdvSmsMessagingRequestSmsResend,				// 2327
	EAdvSmsMessagingRequestSmsResendCancel,			// 2328
	EAdvSmsMessagingNotifySmsMessageArrived,		// 2329
	EAdvSmsMessagingNotifySmsMessageArrivedCancel,	// 2330
	EAdvSmsMessagingNotifySmsEvent,					// 2331
	EAdvSmsMessagingNotifySmsEventCancel,			// 2332
	EAdvSmsMessagingReadUssdMessage,				// 2333
	EAdvSmsMessagingReadUssdMessageCancel,			// 2334
	EAdvSmsMessagingSendUssdMessage,				// 2335
	EAdvSmsMessagingSendUssdMessageCancel,			// 2336
	EAdvSmsMessagingReadCbsMessage,					// 2337
	EAdvSmsMessagingReadCbsMessageCancel,			// 2338
	EAdvSmsMessagingNotifyCbsMessageArrived,		// 2339
	EAdvSmsMessagingNotifyCbsMessageArrivedCancel,	// 2340
	EAdvSmsMessagingGetCbsReceiveMode,				// 2341
	EAdvSmsMessagingSetCbsReceiveMode,				// 2342
	EAdvSmsMessagingNotifyCbsReceiveMode,			// 2343
	EAdvSmsMessagingNotifyCbsReceiveModeCancel,		// 2344
	EAdvSmsMessagingRetrieveCbmiListPhase1,			// 2345
	EAdvSmsMessagingRetrieveCbmiListPhase1Cancel,	// 2346
	EAdvSmsMessagingRetrieveCbmiListPhase2,			// 2347
	EAdvSmsMessagingRetrieveCbmiListPhase2Cancel,	// 2348
	EAdvSmsMessagingStoreCbmiList,					// 2349
	EAdvSmsMessagingStoreCbmiListCancel,			// 2350
	EAdvSmsMessagingNotifyCbmiListChanged,			// 2351
	EAdvSmsMessagingNotifyCbmiListChangedCancel,	// 2352
	EAdvSmsMessagingRetrieveSmspListPhase1,			// 2353
	EAdvSmsMessagingRetrieveSmspListPhase1Cancel,	// 2354
	EAdvSmsMessagingRetrieveSmspListPhase2,			// 2355
	EAdvSmsMessagingRetrieveSmspListPhase2Cancel,	// 2356
	EAdvSmsMessagingStoreSmspList,					// 2357
	EAdvSmsMessagingStoreSmspListCancel,			// 2358
	EAdvSmsMessagingNotifySmspListChanged,			// 2359
	EAdvSmsMessagingNotifySmspListChangedCancel,	// 2360

	//	SMS Storage
	EAdvSmsStorageReadCbs,							// 2361
	EAdvSmsStorageReadCbsCancel,					// 2362
	EAdvSmsStorageSendFromStorage,					// 2363
	EAdvSmsStorageSendFromStorageCancel,			// 2364

	// Encryption
	EGsmCallGetEncryptionStatus,					// 2365
	EGsmCallGetEncryptionStatusCancel,				// 2366
	EGsmCallNotifyEncryptionStatusChanged,			// 2367
	EGsmCallNotifyEncryptionStatusChangedCancel,	// 2368
	
	EGsmPhoneGetMsgWaitingFlag,						// 2369
	EGsmPhoneGetMsgWaitingFlagCancel,				// 2370
	EGsmPhoneSetMsgWaitingFlag,						// 2371
	EGsmPhoneSetMsgWaitingFlagCancel,				// 2372
	EGsmPhoneNotifyMsgWaitingFlag,		   		    // 2373
	EGsmPhoneNotifyMsgWaitingFlagCancel				// 2374

	};

#endif
