// 
// CWapGCtx.h
// Copyright © 1997-1999 Symbian Ltd. All rights reserved.
// 

//
// Comments: Client side of the WapGCtx server.
//			a prospective client of the WapGCtx server creates
//			a CWapGCtxClient object to handle the negotiation with the server.
//

#if !defined(__CWAPGCTX_H__)
#define __CWAPGCTX_H__

#if !defined (__E32DEF_H__)
#include <e32def.h>
#endif
#if !defined (__E32STD_H__)
#include <e32std.h>
#endif
#if !defined (__E32BASE_H__)
#include <e32base.h>
#endif
#if !defined (__E32TEST_H__)
#include <e32test.h>
#endif
#if !defined (__F32FILE_H__)
#include <f32file.h>
#endif

#if !defined (__CWAPGCTXCMD_H__)
#include "CWapGCtxCmd.h"
#endif

// Forward declaration of the client class
class CWapGCtxClient;

/////////////////////////////////////////////////////////////////////////////// 
// CWapGCtxNotificationObserver is the active object class supporting the
// asynchronous notification interface.
// (See CWapGCtxClient::NotifyOnChange() and NotifyOnChangeCancel()).
//
class CWapGCtxNotificationObserver : public CActive
	{
public:
	// Construct an instance of the CWapGCtxNotificationObserver on the heap
	// Leaving if it fails at any stage
	// It requires a reference to the initialised client it is to notify, if its
	// RunL method executes.
	static CWapGCtxNotificationObserver* NewL(CWapGCtxClient& aClient, TPriority aPriority = EPriorityHigh);

	// The default d'tor
	// Calls the base class cancel method to stop any active
	// notifications before destruction.
	~CWapGCtxNotificationObserver();

	// The startup method
	void Activate();

protected:
	// CActive required methods
	// Called from CActive::Cancel() is called,
	// allowing this object to provide specific cleanup activity.
	void DoCancel();

	// Called when the CWapGCtxNotificationObserver activates
	// leaving upon any error.
	// Calls the CLogClient::Notification() method passing the status of the object
	// which contains the notification reason.
	void RunL();

private:
	// Default C'tor
	CWapGCtxNotificationObserver(CWapGCtxClient& aClient, TPriority aPriority);
	// Completes the initialisation of the object instance
	// leaving if initialisation cannot be completed successfully.
	void ConstructL();

private:
	// The owner of this notification object requiring the notification
	CWapGCtxClient* iClient;
	};

/////////////////////////////////////////////////////////////////////////////// 
// RWapGCtxSession maintains the Client side session with 
// the CWapGCtxServer
//
class RWapGCtxSession : public RSessionBase		// For the Client side session 
    {
	friend class CWapGCtxClient;					// To allow access to the SendRecieve method
public:
    TInt Connect();								//	Connect with the WapGCtx server
	void Close();								//	Break the server connection.

    static TVersion Version();					// Give the current version number of the WapGCtx client side.

	};

/////////////////////////////////////////////////////////////////////////////// 
//
// CWapGCtxClient is the class that provides the communication of the
// client requests to the WapGCtxserver.
// It also provides the packing / unpacking of
// any parameters passing accross the process boundary
//

class CWapGCtxClient : public CBase 
	{
public:
	// Construct an instance of the CWapGCtxClient on the heap
	// Leaving if it fails at any stage
	IMPORT_C static CWapGCtxClient* NewL();

	// Default d'tor
	IMPORT_C virtual ~CWapGCtxClient();

	// Close the connection to the WapGCtx Server
	IMPORT_C void Close();

	// Notification message initiation and cancellation
	IMPORT_C void NotifyOnChange();
	IMPORT_C void NotifyOnChange(CWapGCtxNotificationObserver* aObserver);
	IMPORT_C void NotifyOnChangeCancel();

	// Services
	IMPORT_C TInt BeginTransactionL();
	IMPORT_C TInt BeginTransactionLC();
	IMPORT_C void EndTransactionL(TBool aCommit = TRUE);
	IMPORT_C void SetVariableL(const TDesC& aName, const TDesC& aValue);
	IMPORT_C void SetVariableL(const TDesC& aName, const TInt aValue);
	IMPORT_C HBufC* GetVariableLC(const TDesC& aName);
	IMPORT_C TInt GetVariableL(const TDesC& aName, TInt& aValue);

	IMPORT_C void DebugMarkHeap();
	IMPORT_C void DebugMarkEnd();

private:
	// Default c'tor
	CWapGCtxClient();

	// Complete the initialisation of the instance here
	// Leave upon any error.
	void ConstructL();


	// Connect to the WapGCtx Server
	// Leave upon any error.
	void ConnectL();

	// Server service request method
	void ServiceL(TServerFunction aFunction);

	// Notification callback method
	// Called by the CWapGCtxNotificationObserver::RunL() instance
	// passing accross the completed TRequestStatus for
	// completion reason checking.
	void Notification(TRequestStatus& aStatus);

	//Private services
	TInt GetLengthL(const TDesC& aName);

	static void CleanupCommandCloseTransaction(TAny* aPtr);

private:
	// The argument buffer for the Inter-Process Request transfer
	TAny* iMessageArgs[KMaxMessageArguments];
	// The WapGCtx server session	
	RWapGCtxSession* iConnection;
	// The active object for notifications
	CWapGCtxNotificationObserver* iObserver;
	// Allow the notification observer access
	// So that it may call the Notification() method.
	friend class CWapGCtxNotificationObserver;
	// A flag to indicate if the server connection is open
	TBool iConnected;
	// The transaction assosiated with this client
	TInt iTransactionID;

	void __DbgTestInvariant() const;	// Debug method definition to allow class invariant tesing

	// BC -proofing
	IMPORT_C void CWapGCtxClient_Reserved1();

	TAny* CWapGCtxClient_Reserved;
	};


// Simple transaction API 
IMPORT_C void   GCSetSingleVariableL(const TDesC& aName, const TDesC& aValue);
IMPORT_C void	GCSetSingleVariableL(const TDesC& aName, TInt aValue);
IMPORT_C HBufC* GCGetSingleVariableLC(const TDesC& aName);
IMPORT_C TInt	GCGetSingleVariableL(const TDesC& aName, TInt& aValue);


#endif // __CWAPGCTX_H__
