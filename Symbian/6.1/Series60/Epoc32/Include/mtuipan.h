// MTUIPAN.H
//
// Copyright (C) Symbian Ltd 1998
//

#if !defined(__MTUIPAN_H__)
#define __MTUIPAN_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

enum TMtuiPanic
	{
	EMtuiEmptySelection,
	EMtuiWrongMtm,
	EMtuiContextNotFolderOrService,
	EMtuiEntryNotMessage,
	EMtuiEntryNotService
	};

GLREF_C void Panic(TMtuiPanic aPanic);

#endif
