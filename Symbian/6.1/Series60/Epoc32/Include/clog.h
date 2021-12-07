// 
// CLog.h
// Copyright © 1997-99 Symbian Ltd. All rights reserved.
//

// 
// Comments: Client side of the Log server
//			a prospective client of the Log server creates
//			a CLogClient object to handle the negotiation with the server.
//

#if !defined(__CLOG_H__)
#define __CLOG_H__

#if !defined(__E32DEF_H__)
#include <e32def.h>
#endif
#if !defined(__E32STD_H__)
#include <e32std.h>
#endif
#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif
#if !defined(__E32TEST_H__)
#include <e32test.h>
#endif
#if !defined(__F32FILE_H__)
#include <f32file.h>
#endif

#if !defined(__CLOGCMD_H__)
#include "CLogCmd.h"
#endif

// Forward declaration of the client class
class CLogClient;

/////////////////////////////////////////////////////////////////////////////// 
// CLogNotificationObserver is the active object class supporting the
// asynchronous notification interface. (See CLogClient NotifyOnChange()
// and NotifyOnChangeCancel()).
//
class CLogNotificationObserver : public CActive
	{
public:
	// Construct an instance of the CLogNotificationObserver on the heap
	// Leaving if it fails at any stage
	// It requires a reference to the initialised client it is to notify, if its
	// RunL method executes.
	static CLogNotificationObserver* NewL(CLogClient& aClient, TPriority aPriority = EPriorityStandard);

protected:
	// CActive required methods
	// Called from CActive::Cancel() is called,
	// allowing this object to provide specific cleanup activity.
	void DoCancel();

	// Called when the CLogNotificationObserver activates
	// leaving upon any error.
	// Calls the CLogClient::Notification() method passing the status of the object
	// which contains the notification reason.
	void RunL();

private:
	// Default C'tor
	CLogNotificationObserver(CLogClient& aClient, TPriority aPriority);
	// Completes the initialisation of the object instance
	// leaving if initialisation cannot be completed successfully.
	void ConstructL();

private:
#if defined _DEBUG
	CLogClient* iClient;			// The owner of this active object requiring the notification
#endif
	};

/////////////////////////////////////////////////////////////////////////////// 
// RLogSession maintains the Client side session with 
// the CLogServer
//
class RLogSession : public RSessionBase			// For the Client side session 
    {
	friend class CLogClient;					// To allow access to the SendRecieve method by the client
public:
    TInt Connect();								//	Connect with the Log server
	void Close();								//	Break the server connection.

    static TVersion Version();					// Give the current version number of the Log client side.

private:
	};

/////////////////////////////////////////////////////////////////////////////// 
//
// CLogClient is the class that provides the communication of the
// client requests to the Log server, including the packing / unpacking of
// any parameters passing accross the process boundary.
// Note, that it is intended that this class is only called via the
// macros defined in the LogDef.h header file
//
class CLogClient : public CBase
	{
public:
	// Define the logging detail level
	enum TLogLevel
	{
	ELogNone	= 0,
	ELogLight	= 0x10,
	ELogTrace	= 0x20,
	ELogProfile = 0x40,
	ELogAll		= 0x70
	};

	// Construct an instance of the CLogClient on the heap
	// Leaving if it fails at any stage
	// Requires the name of the log file to open/create and a flag
	// indicating if this open is for append or clean log file.
	// Returns a fully initialised instance of the log client.
	IMPORT_C static CLogClient* NewL(const TDesC& aLogName,TBool aClean);
	IMPORT_C virtual ~CLogClient();											// Destruction

	IMPORT_C void Close();													// Close the connection to the Log Server

	// Notification message initiation and cancellation
	IMPORT_C void NotifyOnChange();
	IMPORT_C void NotifyOnChangeCancel();

	// A simple message logging services
	IMPORT_C void Log(const TDesC& aMessage, TLogLevel aLevel);				// Log a simple message at a particular level of detail	
	IMPORT_C void Log(TLogLevel aLevel, TRefByValue<const TDesC> aFmt, ...);// Log a simple message at a particular level of detail
																			// with formatting of arbitrary parameters. (a la printf).
	IMPORT_C void LogEnter(const TDesC& aMessage, TLogLevel aLevel);		// Log a method entry
	IMPORT_C void LogReturn();												// Log a method exit

	IMPORT_C void RDebugConfig(TBool aEnable);								// Enable/Disable the output of the log messages to RDebug::Printf()

private:
	// Default c'tor made explicit to avoid unintentional
	// conversion construction by the compiler
	explicit CLogClient(TBool aClean);

	// Completes the initialisation of the object instance
	// leaving if initialisation cannot be completed successfully.
	void ConstructL(const TDesC& aLogName);

	TBool Connect();														// Connect to the Log server.

	// Server service request method.
	virtual void ServiceL(TLogServerFunction aFunction);

	// Notification callback method used by CLogNotificationObserver
	virtual void Notification(TRequestStatus& aStatus);

private:
#if defined _DEBUG
	TAny* iMessageArgs[KMaxMessageArguments];		// The argument buffer for the Inter-Process Request transfer
	RLogSession* iConnection;						// The server session
	CLogNotificationObserver* iObserver;				// The active object for notifications
	TBool iConnected;								// A flag to indicate if the server connection is open
	HBufC* iLogName;								// The log name
	TInt iIndent;									// Log message indent level
	TBool iClean;									// Flag for creating a clean log file
#endif

	friend class CLogNotificationObserver;				// Allow the CLogNotificationObserver access to the Notification method.

#if defined _DEBUG
	void __DbgTestInvariant() const;				// Debug method definition to allow class invariant testing
#endif
	};

#endif // __CLOG_H__
