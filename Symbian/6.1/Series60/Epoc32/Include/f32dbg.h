// F32DBG.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__F32DBG_H__)
#define __F32DBG_H__
#include <e32std.h>

#define KFSYS       0x0001
#define KFSERV      0x0002
#define KFLDR       0x0004
#define KALLOC	0x0008

// #define _DEBUG_RELEASE

const TInt KAllocFailureOn=0;
const TInt KAllocFailureOff=-1;

#if defined(_DEBUG) || defined(_DEBUG_RELEASE)
const TInt KControlIoCancelNCNotifier=KMaxTInt-1;
const TInt KControlIoNCDebugNotifierOn=KMaxTInt-2;
const TInt KControlIoNCDebugNotifierOff=KMaxTInt-3;
const TInt KNCDebugNotifierValue=-500000;	// between 0 and 1 second
GLREF_D TInt DebugNCNotifier;
#endif

enum TLoaderHeapFunction
	{
	ELdrMarkStart,
	ELdrMarkCheck,
	ELdrMarkCheckAll,
	ELdrMarkEnd,
	ELdrMarkEndC,
	ELdrFailNext,
	ELdrSetFail,
	ELdrReset
	};

enum TFsDebugFunction
	{
	EFsSetAllocFailure,
	EFsSetErrorCondition,
	EFsSetDebugRegister,
	EFsDebugNotify
	};

#endif

