//
// LOGDEF.H
// Copyright © Symbian Ltd 1997-99, All rights reserved.
//

//
// Define Logging Service Constants, Macros and Definitions 
// intended for inclusion into any source file
// which define classes wishing to use log server services.
//

#if !defined(__LOGDEF_H__)
#define __LOGDEF_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

#if !defined(__ANSICOMP_H__)
#include "ANSIComp.h"	// Enforce ANSI compliance upon Microsoft Compilers
#endif

// This define removed for sanity and performance sake.  To enable logging in
// your component, redefine the __LOGGING macro in your own .cpp files, prior to
// the #include of this file.
// #define __LOGGING 1

// Define a constant to control the maximum length of a log message
const TInt KMaxLogEntrySize = KMaxFileName;

// Logging definitions
#if defined (__LOGGING) && 	defined (_DEBUG)		

// Logging activity is enabled
#if !defined(__CLOG_H__)
#include "CLog.h"
#endif

	// Define an error message for failed open calls
	_LIT(KLogOpenFailed,"No log available");

	// Define a set of macros to control logging activity
	// The log server client pointer
	#define __DECLARE_LOG					CLogClient* iLogPtr;

	// Open a connection to the log server for appended log messages
	#define __OPEN_LOG(aLogName)			{iLogPtr = NULL; TRAPD(logError,(iLogPtr = CLogClient::NewL(aLogName,EFalse))); if(logError !=KErrNone) __QINFO(KLogOpenFailed);}
	// Open a connection to the log server for log messages to go to a clean log
	#define __OPEN_CLEANLOG(aLogName)		{iLogPtr = NULL; TRAPD(logError,(iLogPtr = CLogClient::NewL(aLogName,ETrue))); if(logError !=KErrNone) __QINFO(KLogOpenFailed);}
	// Close the connection to the log server
	#define __CLOSE_LOG						{delete iLogPtr; iLogPtr = NULL;}
	// Push and pop the log onto the cleanup stack
	#define __PUSHLOGL						{CleanupStack::PushL(iLogPtr);}
	#define __POPLOG						{CleanupStack::Pop();}
	
	// Log a simple message
	#define __LOG(aText)					{if(iLogPtr != NULL) iLogPtr->Log(aText,CLogClient::ELogLight);}
	// Log a message with single parameter formatting.
	#define __LOG1(aText,aV1)				{if(iLogPtr != NULL) iLogPtr->Log(CLogClient::ELogLight,aText,aV1);}

	#if defined (__PROFILING__)
	// Define additional macros for logging profiling information
		#define __PROFILELOG(aText)			{if(iLogPtr != NULL) iLogPtr->Log(aText,CLogClient::ELogProfile);}
		#define __PROFILELOG1(aText,aV1)	{if(iLogPtr != NULL) iLogPtr->Log(CLogClient::ELogProfile,aText,aV1);}
	#else
	// Empty macros for non-profiling builds
		#define __PROFILELOG(aText);
		#define __PROFILELOG1(aText,aV1);
	#endif

	// A log method entry macro
	#define __LOG_ENTER(aText)			{if(iLogPtr != NULL) iLogPtr->LogEnter(aText,CLogClient::ELogProfile); }
	// A log method exit macro
	#define __LOG_RETURN				{if(iLogPtr != NULL) iLogPtr->LogReturn(); }
	// Log a simple message at a particular level of detail
	#define __LOGX(aLevel,aText)		{if(iLogPtr != NULL) iLogPtr->Log(aText,aLevel);}
	// Log a simple message at a particular level of detail with single parameter formatting.
	#define __LOGX1(aLevel,aText,aV1)	{if(iLogPtr != NULL) iLogPtr->Log(aLevel,aText,aV1);}
	// Log a simple message at trace level of detail
	#define __TRACELOG(aText)			{if(iLogPtr != NULL) iLogPtr->Log(aText,CLogClient::ELogTrace); }
	// Log a simple message at trace level of detail with single parameter formatting.
	#define __TRACELOG1(aText,aV1)		{if(iLogPtr != NULL) iLogPtr->Log(CLogClient::ELogTrace,aText,aV1);}
	// Show a simple message within the info window.
	#define __QINFO(aText)				{User::InfoPrint(aText);} 
	// Configuration of logging server behaviour
	// Turn on the RDebug::Print() when logging (Default setting)
	#define __ENABLE_LOGRDEBUG()		{if(iLogPtr != NULL) iLogPtr->RDebugConfig(ETrue);} 
	// Turn off the RDebug::Print() when logging
	#define __DISABLE_LOGRDEBUG()		{if(iLogPtr != NULL) iLogPtr->RDebugConfig(EFalse);} 

#else
  #if !defined (_DEBUG)
	// In Release builds we want no macro definition whatsoever
	#define __DECLARE_LOG

  #else	// In debug builds...
	// Empty macros for non-logging builds, except for __DECLARE_LOG - we want to ensure the
	// object sizes of classes are identical when headers are included in classes with a mixture
	// of __LOGGING turned on and off, to avoid nasty run-time linking errors.
	#define __DECLARE_LOG				void* iLogPtrNotInUse;
  #endif
	#define __OPEN_LOG(aLogName)
	#define __OPEN_CLEANLOG(aLogName)
	#define __CLOSE_LOG
	#define __PUSHLOGL
	#define __POPLOG
	#define __LOG_ENTER(aText)
	#define __LOG_RETURN 
	#define __LOG(aText)
	#define __LOG1(aText,aV1)
	#define __LOGX(aLevel,aText)
	#define __LOGX1(aLevel,aText,aV1)
	#define __PROFILELOG(aText)
	#define __PROFILELOG1(aText,aV1)
	#define __TRACELOG(aText)
	#define __TRACELOG1(aText,aV1)
	#define __QINFO(aText)
	#define __ENABLE_LOGRDEBUG()
	#define __DISABLE_LOGRDEBUG()

#endif	// __LOGGING

#endif	// __LOGDEF_H__