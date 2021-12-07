#ifndef __ESTLIB_H__
#define __ESTLIB_H__

// ESTLIB.H
//
// Copyright (c) 1998-1999 Symbian Ltd.  All rights reserved.
//

// ESTLIB control for multi-thread and multi-process operation

#include <e32base.h>
#include <stddef.h>

IMPORT_C void PosixServerName(TDes& aBuffer);

// Support for multi-thread operation is achieved using a CPosixServer
// active object - this can be installed in an active scheduler in the current thread,
// or run in a separate thread.

IMPORT_C TInt InstallPosixServerActiveObject (TInt aPriority=CActive::EPriorityStandard);
IMPORT_C TInt SpawnPosixServerThread();

// Support for asynchronous ioctl
// There are no guarantees about when the parameters will be processed - some implementations may
// process the parameters in both the ioctl() and the ioctl_complete() functions.
// Do not wait on the TRequestStatus unless ioctl() returns 0. 

IMPORT_C int ioctl (int aFid, int aCmd, void* aParam, TRequestStatus& aStatus);
IMPORT_C int ioctl_complete (int aFid, int aCmd, void* aParam, TRequestStatus& aStatus);
IMPORT_C int ioctl_cancel (int aFid);

IMPORT_C int _ioctl_r (struct _reent *r, int aFid, int aCmd, void* aParam, TRequestStatus& aStatus);
IMPORT_C int _ioctl_complete_r (struct _reent *r, int aFid, int aCmd, void* aParam, TRequestStatus& aStatus);
IMPORT_C int _ioctl_cancel_r (struct _reent *r, int aFid);

// Support for crt0 variants
// Do whatever is necessary to get the command line arguments, environment etc.
// NB. This calls chdir(), so start the PosixServer before calling this if you want one.

IMPORT_C void __crt0(int& argc, char**& argv, char**& envp);
IMPORT_C void __crt0(int& argc, wchar_t**& argv, wchar_t**& envp);

#endif
