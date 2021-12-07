/* Copyright (c) 2001, Nokia. All rights reserved */
#ifndef __SyncServer_PAN__
#define __SyncServer_PAN__

/** Panic Category */
_LIT(KCSSyncServer, "CSSyncServer");

/** SyncServer panic codes */
enum TTimeServPanic
    {
    EBadRequest,
    EBadDescriptor,
    ESrvCreateServer,
    ECreateTrapCleanup
    };


#endif // __SyncServer_PAN__
