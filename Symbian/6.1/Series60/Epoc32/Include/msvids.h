// MSVIDS.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//

#if !defined(__MSVIDS_H__)
#define __MSVIDS_H__
#if !defined(__MSVSTD_HRH__)
#include "msvstd.hrh"
#endif
#if !defined(__MSVSTD_H__)
#include "msvstd.h"
#endif

// Predefined entry ids - values #defined in MSVSTD.HRH
const TMsvId KMsvNullIndexEntryId=KMsvNullIndexEntryIdValue;//0
const TMsvId KMsvTempIndexEntryId=KMsvTempIndexEntryIdValue;//1
const TMsvId KMsvRootIndexEntryId=KMsvRootIndexEntryIdValue;//0x1000
const TMsvId KMsvLocalServiceIndexEntryId=KMsvLocalServiceIndexEntryIdValue;//0x1001
const TMsvId KMsvGlobalInBoxIndexEntryId=KMsvGlobalInBoxIndexEntryIdValue;//0x1002
const TMsvId KMsvGlobalOutBoxIndexEntryId=KMsvGlobalOutBoxIndexEntryIdValue;//0x1003
const TMsvId KMsvDraftEntryId=KMsvDraftEntryIdValue; //0x1004
const TMsvId KMsvSentEntryId=KMsvSentEntryIdValue; //0x1005
const TMsvId KMsvDeletedEntryFolderEntryId=KMsvDeletedEntryFolderEntryIdValue;//0x1006
const TMsvId KMsvUnknownServiceIndexEntryId=KMsvUnkownServiceIndexEntryIdValue; //0x1007
const TMsvId KFirstFreeEntryId=0x100000;

#endif