// EIKDIALG.PAN
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKDIALG_PAN__)
#define __EIKDIALG_PAN__

enum TEikDialogPanic
	{
	EEikDialogPanicNoSuchControl,
	EEikDialogPanicWrongAutoType,
	EEikDialogPanicWrongLatencySwitch,
	EEikDialogPanicFocusableLineWithIdZero,
	EEikDialogPanicControlIsBiggerThanPage,
	EEikDialogPanicErrorDuringAddingLine,
	EEikDialogPanicIllegalOption
	};

GLREF_C void Panic(TEikDialogPanic aPanic);

#endif
