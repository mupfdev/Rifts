/* Copyright (c) 2002, Nokia. All rights reserved */
#ifndef __BTSERVICE_SEARCHER_PAN__
#define __BTSERVICE_SEARCHER_PAN__

#include <e32std.h>

/** BTServiceSearcher application panic codes */
enum TBTServiceSearcherPanics 
    {
    EBTServiceSearcherNextRecordRequestComplete = 1,
    EBTServiceSearcherAttributeRequestResult,
    EBTServiceSearcherAttributeRequestComplete,
    EBTServiceSearcherInvalidControlIndex,
    EBTServiceSearcherProtocolRead,
    EBTServiceSearcherAttributeRequest,
    EBTServiceSearcherSdpRecordDelete
    };

inline void Panic(TBTServiceSearcherPanics aReason)
    { 
    User::Panic(_L("ServiceSearcher"), aReason);
    }

#endif // __BTSERVICE_SEARCHER_PAN__
