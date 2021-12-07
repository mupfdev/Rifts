//
//	CWAPGCTXCMD.H
// Copyright © 1997-1999 Symbian Ltd. All rights reserved.
//

//
// Comments: Define a enumeration for the Op codes requesting WapGCtx server services.
//
#if !defined(__CWAPGCTXCMD_H__)
#define __CWAPGCTXCMD_H__

#ifndef __FILE__LINE__
#	define __FILE__LINE__ __FILE__
#endif

// Define the enumeration for the service op codes
// For each additional asynchronous service added
// Provide an extra service request and cancellation enumeration value
// here and add 2 to the KServerMessageSlots value in CWapGCtxStd.h.
// NOTE : Each synchronous server service only requires a single enumeration
// value addition.
enum TServerFunction
	{
	ESetVariable,				// TDesC Name, TDesC Value, TInt TransactionId
	EGetVariable,				// TDesC Name, TDes  Value, TInt TransactionId
	EGetLength,					// TDesC Name, TInt TransactionId, TPkgBuf<TInt> Length
	EBeginTransaction,			// TPkgBuf<TInt> TransactionId
	EEndTransaction,			// TInt TransactionId, TBool Commit

	ENotifyOnChange,			// Request notifications on WapGCtx changes
	ENotifyOnChangeCancel,		// Cancel WapGCtx change notification.
#ifdef _DEBUG
	EDebugMarkEnd,				// Heap checking services for debug
	EDebugMarkHeap,
	EDebugMarkFailNext,
#endif
	};

// Definitions for location & startup of the WapGCtx server
// Define the WapGCtx server name
_LIT(KWapGCtxServerName, "WapGCtxServer");

// and the semaphore name
_LIT(KWapGCtxStartServerSemaphore, "StartWapGCtxServer");

//Define the filename to be used for storing the status of the server
_LIT(KFullNameOfFileStore,"C:\\system\\data\\wapgc.dat");

// Few magic numbers
const TInt KGlobalContextServerInvalidTransaction = -1;

// Define the WapGCtx server version number
#if defined(__NO_CLASS_CONSTS__)
#define KCWapGCtxMajorVN	1
#define KCWapGCtxMinorVN	0
#define KCWapGCtxBuildVN	0
#else
const TInt KCWapGCtxMajorVN=1;
const TInt KCWapGCtxMinorVN=0;
const TInt KCWapGCtxBuildVN=0;
#endif

#endif	// __CWAPGCTXCMD_H__

