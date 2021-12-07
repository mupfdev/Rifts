// MTUDPAN.H
//
// Copyright (C) Symbian Ltd 1998
//

#if !defined(__MTUDPAN_H__)
#define __MTUDPAN_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

enum TMtudPanic
	{
	EMtudBadLibrary,
	EMtudIncorrectBitmapNumbers,
	EMtudWrongMtmType,
	EMtudSelectionOfMoreThanOneType,
	EMtudMoreThanOneLocationInFuntionFlags,
	EMturThreadStartPanic1,
	EMturThreadStartPanic2,
	EMturThreadStartPanic3
	};

GLREF_C void Panic(TMtudPanic aPanic);

#endif
