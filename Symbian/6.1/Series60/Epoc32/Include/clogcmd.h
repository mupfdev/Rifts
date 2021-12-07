//
// CLOGCMD.H
// Copyright © 1997-99 Symbian Ltd. All rights reserved.
//

//
// Defines an enumeration for the Op codes for
// requesting Log Server services.
//
#if !defined(__CLOGCMD_H__)
#define __CLOGCMD_H__

//	The Op code enumeration.
enum TLogServerFunction
	{
	ELogOpen,					// Open a Log
	ELogClose,					// Close a Log
	ELogMessage,				// Add a log message
	ELogEnter,					// Add an enter function log message
	ELogReturn,					// Add a leave function log message
	ELogRDebugConfig,			// Enable/Disable RDebug::Print()s
	ELogNotifyOnChange,			// Request notifications on log changes
	ELogNotifyOnChangeCancel,	// Cancel log change notification.
#ifdef _DEBUG
	ELogDebugMarkEnd,			// Heap checking services for debug
	ELogDebugMarkHeap,
	ELogDebugMarkFailNext,
#endif
	};

// Define names for the Log server and its semaphore
_LIT(KLogServerName, "LogServer");
_LIT(KLogNameStartServerSemaphore, "StartLogServer");

// Also define version numbers for the server
const TInt KCLogMajorVN=1;
const TInt KCLogMinorVN=0;
const TInt KCLogBuildVN=6;

#endif	// __CLOGCMD_H__

