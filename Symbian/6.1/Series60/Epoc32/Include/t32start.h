// T32START.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// Written by BLB, June 1995
//
//	This function is used to start the alarm and world
//	servers. Its is used by the system on machine switch on, 
//	and by test programs.
//
#if !defined(__T32START_H__)
#define __T32START_H__
#include <e32def.h>

IMPORT_C TPtrC NameEalwlStartSemaphore();
IMPORT_C TPtrC NameEalwlServerThread();
IMPORT_C TInt StartupEALWL();

#endif
