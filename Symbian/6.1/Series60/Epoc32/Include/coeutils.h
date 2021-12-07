// COEUTILS.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__COEUTILS_H__)
#define __COEUTILS_H__

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif

/**
 * The ConeUtils class implements utility functions for use by Cone applications.
 */
class ConeUtils
	{
public:
	IMPORT_C static TBool FileExists(const TDesC& aFileName);
	IMPORT_C static void EnsurePathExistsL(const TPtrC& aFileName);
	};

#endif
