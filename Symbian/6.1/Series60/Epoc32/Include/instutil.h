// INSTUTIL.H
// Copyright (c) 1997-1999 Symbian Ltd. All rights reserved.
//
// Installation software utilities static class
//

#if !defined(__INSTUTIL_H__)
#define __INSTUTIL_H__

// ===========================================================================
// INCLUDES
// ===========================================================================

#include <e32std.h>

// ===========================================================================
// CInstallUtils
// ===========================================================================

class CInstallUtils
	{
public:
	IMPORT_C static void AppendVersionString(TDes& aDes,TInt aMajor,TInt aMinor);
	};

#endif