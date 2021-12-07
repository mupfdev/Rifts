// SAVEPRIV.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__SAVEPRIV_H__)
#define __SAVEPRIV_H__

_LIT(__SHUTDOWN_SERVER_NAME,"ShutdownServer");

const TInt KShutdownMajorVN			=6;
const TInt KShutdownMinorVN			=0;
const TInt KShutdownBuildVN			=1;
const TInt KShutdownMessageSlots	=1;

const TUid KUidNotifierSaveFail		={123456};

enum TSaveNotifierOpCode
	{
	TSaveOpCodeNotify,
	TSaveOpCodeNotifyCancel,
	TSaveOpCodeHandleError,
	};

#endif
