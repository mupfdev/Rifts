// MSVUTILS.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//

#include "msvstd.h"

#if !defined(__MSVUTILS_H__)
#define __MSVUTILS_H__

_LIT(KMsvUtilsNewExtension,".new");

class MsvUtils
	{
public:
	enum TNameMode {EStore, EFolder, EPath};
	IMPORT_C static TBool ValidEntry(const TMsvEntry& aEntry);
	IMPORT_C static void ConstructEntryName(TMsvId aService, TMsvId aEntry, TDes& aName, TNameMode aMode);
	IMPORT_C static TInt HasDirectory(const RFs& aFs, const TDesC& aMessageFolder, TMsvId aService, TMsvId aEntry);
	IMPORT_C static TInt HasStore(const RFs& aFs, const TDesC& aMessageFolder, TMsvId aService, TMsvId aEntry);
	static TBool ValidEntry(const TMsvEntry& aEntry, TBool aCreate);
	};

#endif
