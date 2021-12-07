/* Copyright (c) 2001, Nokia. All rights reserved */
#ifndef __AsyncServer_PAN__
#define __AsyncServer_PAN__

/** Panic Category */
_LIT(KCSAsyncServer, "CSAsyncServer");

/** AsyncServer panic codes */
enum TTimeServPanic
    {
    EBadRequest = 1,
    EBadDescriptor = 2,
    ESrvCreateServer = 3,
    EMainSchedulerError = 4,
    ECreateTrapCleanup = 5,
    ESrvSessCreateTimer = 6,
	EReqAlreadyPending = 7		//	A request is already pending
    };

#endif // __AsyncServer_PAN__
