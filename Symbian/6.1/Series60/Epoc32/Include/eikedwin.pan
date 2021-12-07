// EIKEDWIN.PAN
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKEDWIN_PAN__)
#define __EIKEDWIN_PAN__

enum TEikEdwinPanic
	{
	EEikPanicEdwinNoWidth,
	EEikPanicEdwinNoHeight,
	EEikPanicEdwinNotRichText,
	EEikPanicEdwinNotOwnCharFormat,
	EEikPanicEdwinNotOwnParaFormat,
	EEikPanicEdwinNoView,
	EEikPanicEdwinBadAttribute,
	EEikPanicEdwinBadClipboardFunc,
	EEikPanicEdwinNoText,
	EEikPanicEdwinNoLayout,
	EEikPanicEdwinNoWindow,
	EEikPanicEdwinInvalidTextLimit,
	EEikPanicEdwinInvalidInsertPos,
	EEikPanicEdwinInvalidFlagCombination,
	EEikPanicEdwinHeightGreaterThanMaximum,
	EEikPanicEdwinMaxHeightWithoutBaseline
	};

GLREF_C void Panic(TEikEdwinPanic aPanic);

#endif
