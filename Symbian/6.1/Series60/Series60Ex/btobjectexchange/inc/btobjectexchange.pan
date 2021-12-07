/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __BTOBJECTEXCHANGE_PAN__
#define __BTOBJECTEXCHANGE_PAN__

#include <e32std.h>

/** BTObjectExchange application panic codes */
enum TBTObjectExchangePanics 
    {
    EBTObjectExchangeBasicUi = 1,
    EBTObjectExchangeReceiverInvalidState,
    EBTObjectExchangeSenderExists,
    EBTObjectExchangeReceiverExists,
    EBTObjectExchangeSenderInvalidState,
    EBTObjectExchangeNoSender,
    EBTObjectExchangeAddMessage,
    EBTObjectExchangeNextRecordRequestComplete,
    EBTObjectExchangeAttributeRequestResult,
    EBTObjectExchangeAttributeRequestComplete,
    EBTObjectExchangeInvalidControlIndex,
    EBTObjectExchangeProtocolRead,
    EBTObjectExchangeAttributeRequest,
    EBTObjectExchangeSdpRecordDelete,
    EBTObjectExchangeUnexpectedState,
    EBTObjectExchangeUnexpectedLogicState
    };

inline void Panic(TBTObjectExchangePanics aReason)
    { 
    User::Panic(_L("BTOBEX"), aReason);
    }

#endif // __BTOBJECTEXCHANGE_PAN__
