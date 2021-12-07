/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __BTPOINTTOPOINT_PAN__
#define __BTPOINTTOPOINT_PAN__

/** BTPointToPoint application panic codes */
enum TBTPointToPointPanics 
    {
    EBTPointToPointBasicUi = 1,
    EBTPointToPointReceiverInvalidState,
    EBTPointToPointSenderExists,
    EBTPointToPointReceiverExists,
    EBTPointToPointSenderInvalidState,
    EBTPointToPointNoSender,
    EBTPointToPointAddMessage,
    EBTPointToPointNextRecordRequestComplete,
    EBTPointToPointAttributeRequestResult,
    EBTPointToPointAttributeRequestComplete,
    EBTPointToPointInvalidControlIndex,
    EBTPointToPointProtocolRead,
    EBTPointToPointAttributeRequest,
    EBTPointToPointSdpRecordDelete,
    EBTPointToPointServerStop,
	EBTPointToPointInvalidLogicState,
	EBTPointToPointUnableToDisconnect
    };

inline void Panic(TBTPointToPointPanics aReason)
    { 
    User::Panic(_L("BTPointToPoint"), aReason);
    }


#endif // __BTPOINTTOPOINT_PAN__
