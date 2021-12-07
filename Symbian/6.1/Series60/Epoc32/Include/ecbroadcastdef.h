//
//	ECBROADCASTDEF.H
//
//	Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//


#ifndef EC_ECBROADCASTDEF_H
#define EC_ECBROADCASTDEF_H

enum TECBroadcastNotifierEnum
{
	ECmdQueryVersion = 0x00,
	ECmdQuit = 0xff,
	ECmdAddNotificationRequest = 0x01,//depreciated
	ECmdRemoveNotificationRequest = 0x02,//depreciated
	ECmdFireNotification = 0x04,//depreciated
	ECmdWaitPendingNotification = 0x08,

	ECmdModifyRequest = 0x10,
	ECmdNull = 0x20,
};

const int KMaxECBroadcastBufferSize = 2048;
const int KECBroadcastMajorVer = 1;
const int KECBroadcastMinorVer = 0;
const int KECBroadcastBuildVer = 0;

#endif	//	EC_ECBROADCASTDEF_H

