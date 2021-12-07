// COEDEF.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__COEDEF_H__)
#define __COEDEF_H__

#if !defined(__GULDEF_H__)
#include <guldef.h> // only requried for linited source compatability with releases prior to 250
#endif

enum TKeyResponse
	{
	EKeyWasNotConsumed,
	EKeyWasConsumed
	};

enum TDrawNow
	{
	ENoDrawNow,
	EDrawNow
	};

enum TCoeWinPriority
	{
	ECoeWinPriorityNeverAtFront		=-1000,
	ECoeWinPriorityLow				=-750,
	ECoeWinPriorityNormal			=0,
	ECoeWinPriorityMedium			=500,
	ECoeWinPriorityHigh				=750,
	ECoeWinPriorityFep				=900,
	ECoeWinPriorityAlwaysAtFront	=1000
	};

#if defined(_DEBUG)
#define __DEBUG_CHECK_HEAP_INTEGRITY User::Heap().Check()
#else
#define __DEBUG_CHECK_HEAP_INTEGRITY
#endif

#define CTRL(x) ((x)-'a'+1) // not an inline function since that can't be put as the case of a switch statement

#define EAllStdModifiers (EModifierFunc|EModifierCtrl|EModifierShift)

#endif
