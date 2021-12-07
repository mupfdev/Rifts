// LOGENG.H
//
// Copyright (c) 2002 Symbian Ltd.  All rights reserved.
//

#ifndef __LOGENG_H__
#define __LOGENG_H__

#include <e32std.h>
#include "logwrap.h"
#include "logwrap.hrh"

// Event types
const TUid KLogCallEventTypeUid = {KLogCallEventType};
const TUid KLogDataEventTypeUid = {KLogDataEventType};
const TUid KLogFaxEventTypeUid = {KLogFaxEventType};
const TUid KLogShortMessageEventTypeUid = {KLogShortMessageEventType};
const TUid KLogMailEventTypeUid = {KLogMailEventType};
const TUid KLogTaskSchedulerEventTypeUid = {KLogTaskSchedulerEventType};
const TUid KLogPacketDataEventTypeUid = {KLogPacketDataEventType};

// Duration Types
const TLogDurationType KLogDurationNone = 0;
const TLogDurationType KLogDurationValid = 1;
const TLogDurationType KLogDurationData = 2;

// Flags
const TLogFlags KLogEventRead = 0x1;
const TLogFlags KLogEventContactSearched = 0x2;

// The following should be used to store SMS PDU info in event data
class TLogSmsPduData
	{
public:
	TInt iType; // message type;
	TInt iTotal;   //  total number of parts
	TInt iSent;   //  total number of parts sent
	TInt iDelivered;  //  total number of parts delivered to destination
	TInt iFailed;  //  total number of parts failed to be delivered to destination
	TInt iReceived;  //  total number of parts received for DELIVERs or SUBMITs read from the phone/SIM 
	};

#endif
