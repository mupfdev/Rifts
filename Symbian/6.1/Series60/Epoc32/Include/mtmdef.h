// MTMDEF.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//

#if !defined(__MTMDEF_H__)
#define __MTMDEF_H__
#if !defined(__MTCLBASE_H__)
#include "mtclbase.h"
#endif
#if !defined(__MTMDEF_HRH__)
#include "mtmdef.hrh"
#endif

// no matching message parts
const TMsvPartList KMsvMessagePartNone			= 0x00000000;

// message parts
const TMsvPartList KMsvMessagePartBody			= 0x00000001;
const TMsvPartList KMsvMessagePartRecipient		= 0x00000002;
const TMsvPartList KMsvMessagePartOriginator	= 0x00000004;
const TMsvPartList KMsvMessagePartDescription	= 0x00000008;
const TMsvPartList KMsvMessagePartDate			= 0x00000010;
const TMsvPartList KMsvMessagePartAttachments	= 0x00000020;

// find attributes
const TMsvPartList KMsvFindCaseSensitive		= 0x80000000;
const TMsvPartList KMsvFindWholeWord			= 0x40000000;

// Maximum length (in characters) of find text
const TInt KMsvMaxFindTextLength = 500;

#endif
