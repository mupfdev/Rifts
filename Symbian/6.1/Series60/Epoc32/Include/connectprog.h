// CONNECTPROG.H
//
// Copyright (c) 1997-2000 Symbian Ltd.  All rights reserved.
//

// Connection progress enums

#ifndef __CONNECTPROG_H__
#define __CONNECTPROG_H__

#include <e32def.h>

enum TNetDialProgress				// Stages in establishing a connection with NetDial
	{
	EStartingSelection=2,
	EFinishedSelection,	
	EStartingDialling,
	EFinishedDialling,
	EScanningScript,
	EScannedScript,
	EGettingLoginInfo,
	EGotLoginInfo,
	EStartingConnect,				// 10
	EFinishedConnect,
	EStartingLogIn,
	EFinishedLogIn,
	EConnectionOpen,
	EStartingHangUp,
	EFinishedHangUp,
	EStartingAnswer,
	EAnswered,						// 18
	ESettingOverrides
	};

#endif

