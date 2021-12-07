///////////////////////////////////////////////////////////////////////////////
//
// SMCMMAIN.H
//
// Copyright (c) 2000 Symbian Ltd. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////


#ifndef SMUTMAIN_H_
#define SMUTMAIN_H_

#include <e32base.h>

const TInt KSmscSessionPriority = CActive::EPriorityStandard;

_LIT(KSmcmDllName,"SMCM");


enum TSmcmPanic
	{
	ESmutPanicUnsupportedMsgType,
	ESmscEntryNotSet,
	ESmscWrongContextType,
	ESmscPanicUnexpectedCommand,
	ESmscUnrecognizedEntryType,
	ESmscAddresseeIndexOutOfRange,
	ESmscRecpAddresseeMiscount,
	ESmscDefaultSCOutOfRange,
	ESmscVPOutOfRange,
	ESmscRetryLimitOutOfRange,
	ESmscBioMsgIdTypeError,
	ESmscSettingsNotSet,
	ESmscServiceIdNotSet,
	ESmscSimParamWrongType,
	ESmscSimParamExistingOperation,
	ESmscSimParamInvalidProgressCount,
	ESmscWrongCommDbAction
	};

_LIT(KSmcmPanic, "SMCM");

inline void Panic(TSmcmPanic aPanic)
	{
	User::Panic(KSmcmPanic, aPanic);
	}

#endif

