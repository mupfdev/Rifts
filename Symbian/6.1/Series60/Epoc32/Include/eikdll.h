// EIKDLL.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKDLL_H__)
#define __EIKDLL_H__

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif

#if !defined(__APACMDLN_H__)
#include <apacmdln.h>
#endif

class EikDll
	{
public: // Internal to Symbian
	IMPORT_C static void StartDocL(const TDesC& aDocName);
	IMPORT_C static TThreadId StartExeL(const TDesC& aName);
	IMPORT_C static TThreadId StartAppL(const CApaCommandLine& aCommandLine);
public:
	IMPORT_C static void RunAppInsideThread(CApaCommandLine* aCommandLine);
	};

#endif
