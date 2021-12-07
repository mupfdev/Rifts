// MSVUIDS.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//

#if !defined(__MSVUIDS_H__)
#define __MSVUIDS_H__
#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif
#if !defined(__MSVSTD_HRH__)
#include "msvstd.hrh"
#endif

// Entry type Uids
const TUid KUidMsvNullEntry={0};
const TUid KUidMsvRootEntry={KUidMsvRootEntryValue};
const TUid KUidMsvServiceEntry={KUidMsvServiceEntryValue};
const TUid KUidMsvFolderEntry={KUidMsvFolderEntryValue};
const TUid KUidMsvMessageEntry={KUidMsvMessageEntryValue};
const TUid KUidMsvAttachmentEntry={KUidMsvAttachmentEntryValue};

// Local Service Uid
const TUid KUidMsvLocalServiceMtm={KUidMsvLocalServiceMtmValue};
const TUid KUidMsvServerMtm={KUidMsvServerMtmValue};
#endif