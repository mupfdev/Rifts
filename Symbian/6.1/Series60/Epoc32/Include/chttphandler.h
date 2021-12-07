//
// CHTTPHandler.h
// Copyright © 1998-2000 Symbian Ltd.  All rights reserved. 
//

//
// Purpose:  This file provides the definition of the CHTTPHandler class.
//
// Comments: The HTTP Handler class encapsulates the state machine required for
//           a sequence of HTTP transactions.  It also coordinates the queuing
//           of pending HTTP methods, creating the appropriate plug-ins and
//           executing them in sequence.
//
//			 A separate HTTP Handler is instantiated for each origin server to
//			 which an HTTP connection is made.
//
//           The HTTP state machine iterates a cycle:
//
//             InitiateConnection -> OnConnection -> OnInvocation
//											^			|
//											|			V
//									  CompletedL  <- OnResult
//
//			 Responses from the WAP Gateway are used to drive the state machine.
//
//			 This class is an active object specialism.
//

#ifndef __CHTTPHANDLER_H__
#define __CHTTPHANDLER_H__

// System includes
//
#if !defined(__F32FILE_H__)
#include <f32file.h> // defines file system
#endif
#if !defined(__WAPCLI_H__)
#include <wapcli.h>	// defines WAP Stack client
#endif
#if !defined(__URLHND_H__)
#include <urlhnd.h>	// defines URL Handler
#endif
#if !defined(__LOGDEF_H__)
#include <LogDef.h>	// defines client for Logging server
#endif
#if !defined(__HTTPSTD_H__)
#include <HttpStd.h>	// defines standard error/return/panic codes for HTTP
#endif

// Local includes
//
#if !defined(__CHTTPMANAGER_H__)
#include "CHTTPManager.h" // defines HTTP Manager
#endif
#if !defined(__CHTTPMETHOD_H__)
#include "CHTTPMethod.h" // defines HTTP method
#endif
#if !defined(__CHTTPRESPONSE_H__)
#include "CHTTPResponse.h" // defines HTTP response
#endif
#if !defined(__CQUEUE_H_)
#include "CQueue.h" // defines a queue class
#endif
#if !defined(__CWSPTRANSADAPTER_H_)
#include "CWspTransAdapter.h" // defines an abstract transaction
							  // adapter
#endif

// Forward class declarations
//
class CPluginOwner;
class CHTTPManager;
class CWspSessAdapter;
class CHTTPMethodStarter;
#ifdef __LOGGING
class CLogClient;
#endif

// Class definition for CHTTPHandler
//
class CHTTPHandler : public CActive
	{
	 	// Method starter class needs to be a friend to access the handler's RunError().
 	friend class CHTTPMethodStarter;
 
public:	// Methods

	// Factory method to construct this class.
	//
	// In:
	// aHTTPManager	 - the HTTP manager that owns the WAP stack connection.
	// aUrl			 - a URL containing the origin server for which this HTTP
	//				   Handler is created.
	// aSessAdapter  - a session adapter - the specific class passed in
	//				   will be a sub-class, to support CO or CL sessions. It
	//				   is used by this class to manufacture an appropriate
	//				   transactions adapter.
	//
	// Rtn: a new CHTTPManager object, by ptr. Ownership is _not_ transferred to
	//      the caller.
	//
    IMPORT_C
	static CHTTPHandler* NewL(CHTTPManager& aHTTPManager,
							  const CUrl& aUrl,
							  CWspSessAdapter* aSessAdapter);

	// Destructor for this class. Removes this object and releases memory held
	// by it
	//
	IMPORT_C
	virtual ~CHTTPHandler();

	// Add an HTTP Method plug-in, to execute a particular HTTP method on the
	// specified URL, which targets the HTTP server handled by this class.
	//
	// In:
	// aUrl		-		the Url identifying the remote object to be targetted
	// aMethod	-		the HTTP method to be executed on the remote object
	// aCaching	-		a flag specifying whether local caching should be used or not
	// aWmlFetchFlags -	flag for fetch infomration; eg reload
	//
    IMPORT_C 
	CPluginOwner* AddL(const CUrl& aUrl, const TDesC& aMethod, 
					   TBool aCaching = EFalse, TInt aWmlFetchFlags = EWmlFetchNoFlag);

	// Remove, by de-queuing, the specified method from this HTTP Handler
	//
	// In:
	// aMethod	- the HTTP method to be removed. It is not destroyed.
	//
    IMPORT_C
	TBool RemoveMethod(CHTTPMethod* aMethod);

	// Accessor to the URL for which this handler was initially created
	//
	// Rtn: the URL held by the handler, which may not be modified.
	//
    IMPORT_C
	const CUrl& URL() const;

	// Suspend the HTTP state machine embodied by this HTTP handler
	//
	IMPORT_C
	void SuspendL();

	// Resume this HTTP Handler, assuming it has been previously suspended
	//
	IMPORT_C
	void ResumeL();

  	// Allows protocol specific commands, e.g. HTTP Meta tags, to be executed
  	// NB THIS METHOD IS NOT USED AND HAS A DUMMY IMPLEMENTATION. HOWEVER IT
	// CAN NOT BE REMOVED IN ORDER TO PRESERVE BINARY COMPATIBILITY. IT WILL
	// PANIC IF INVOKED.
  	IMPORT_C
  	virtual void ProtocolCommandL();

	// Add an authentication record for the HTTP server targetted by this
	// HTTP handler. Each record matches a username/password pair with a named
	// realm on the server, of which there may be several.
	//
	// In:
	// aRealm		- the name of the realm, specified in narrow (8-bit) format
	// aUsername	- a user-name with access to the realm, in narrow format.
	// aPassword	- a password for the authorised user, in narrow format.
	//
    IMPORT_C
	void AddRequestAuthenticationL(const TDesC8& aRealm,
                                   const TDesC8& aUsername,
                                   const TDesC8& aPassword);

	// Creates a WSP authentication string from the username and password
	//
	// In:
	// aRealm		- the name of the realm, specified in narrow (8-bit) format
	// aUsername	- a user-name with access to the realm, in narrow format.
	// aPassword	- a password for the authorised user, in narrow format.
	static HBufC8* CreateRequestAuthenticationStringLC(const TDesC8& aUsername,
													  const TDesC8& aPassword);
 
	// Obtain the WSP-encoded authentication record for the named realm on the
	// HTTP server targetted by this handler.
	//
	// In:
	// aRealm		- the name of the realm, specified in narrow (8-bit) format
	//
	// Rtn: a narrow string containing the encoded user-name/password pair.
	//		Ownership of the HBufC is _not_ transferred to the caller
	//
	IMPORT_C
	HBufC8* GetRequestAuthentication(const TDesC8& aRealm);

 	// Remove the authentication for the given realm
 	//
 	// In:
 	// aRealm		- the name of the realm, specified in narrow (8-bit) format
 	void RemoveRequestAuthentication(const TDesC8& aRealm);
 
	// Obtain the storage to the most recently-received response 
	// from the HTTP server.
	//
	// Rtn: a reference to the iHTTPResponse storage member - allows the
	//		Response to be substituted for another.  The ownership is always
	//		retained by CHTTPHandler.
	//
	IMPORT_C 
	CHTTPResponse*& HTTPResponse();

	// Accessor to the HTTP Manager 
	//
	// Rtn: a reference to the iHTTPResponse storage member
	//
	IMPORT_C 
	CHTTPManager& HTTPManager();

	// Callback for HTTP Methods to use when they are cancelled by their owning Data
	// Collector
	//
	IMPORT_C
	void MethodCancelCallback(const CHTTPMethod* aCancelledMethod);

  	// Obtain the version number, maj.min.bld of this class
  	// NB THIS METHOD IS NOT USED AND HAS A DUMMY IMPLEMENTATION. HOWEVER IT
	// CAN NOT BE REMOVED IN ORDER TO PRESERVE BINARY COMPATIBILITY. IT WILL
	// PANIC IF INVOKED.
  	//
  	// Rtn: a version triplet
  	//
  	IMPORT_C 
  	virtual TVersion Version() const;
   
  	// Obtain the name of this class
  	// NB THIS METHOD IS NOT USED AND HAS A DUMMY IMPLEMENTATION. HOWEVER IT
	// CAN NOT BE REMOVED IN ORDER TO PRESERVE BINARY COMPATIBILITY. IT WILL
	// PANIC IF INVOKED.
  	//
  	// Rtn: a name string - ownership is passed to the caller
  	//
  	IMPORT_C
  	virtual HBufC* NameL() const;
  
  	// Obtain the data type handled by this class
  	// NB THIS METHOD IS NOT USED AND HAS A DUMMY IMPLEMENTATION. HOWEVER IT
	// CAN NOT BE REMOVED IN ORDER TO PRESERVE BINARY COMPATIBILITY. IT WILL
	// PANIC IF INVOKED.
  	//
  	// Rtn: a datatype string - ownership is passed to the caller
  	//
  	IMPORT_C
  	virtual HBufC* DataL() const; 

public:	// Methods inherited from CActive

	// Begin the state machine embodied by this active object class
	//
	IMPORT_C
	void BeginL();

protected:
	// Do the next chunk of processing of the state machine embodied by this
	// active object class - invoked when a requested asynchronous event has
	// completed.
	//
	IMPORT_C
	void RunL();

	// Callback provided for the active scheduler, to be used in instances where
	// the RunL() method leaves. Allows the active object to handle the leaving
	// condition, eg. by freeing memory
	//
	// In:
	//	aError - the error code with which RunL left
	//
	IMPORT_C
	virtual TInt RunError(TInt aError);

	// Cancel this active object, removing any outstanding asynchronous request
	//
	IMPORT_C
	void DoCancel();


protected: // Methods

	// Normal constructor - do non-allocating creation of this class
	//
	// In:
	// aManager	- the HTTP manager that owns the WAP stack connection.
	//
	IMPORT_C
	CHTTPHandler(CHTTPManager& aHTTPManager);

	// Second phase construction - any allocation for this class must take place
	// here. Sets up the resources required by an HTTP Handler.
	//
	// In:
	// aUrl			 - a URL containing the origin server for which this HTTP
	//				   Handler is created.
	// aSessAdapter  - a session adapter - the specific class passed in
	//				   will be a sub-class, to support CO or CL sessions. It
	//				   is used by this class to manufacture an appropriate
	//				   transactions adapter.
	IMPORT_C
	void ConstructL(const CUrl& aUrl,
					CWspSessAdapter* aSessAdapter);

	// Perform a look-up from method name to corresponding plug-in name
	//
	// In:
	// aMethod - descriptor containing the method name
	//
	// Rtn: the corresponding plug-in name
	//
	IMPORT_C
	virtual const TDesC& FindHTTPMethodL(const TDesC& aMethod) const;

	// Perform a look-up from caching flag to corresponding plug-in datatype
	//
	// In:
	// aMethod - a flag specifying whether caching is required or not
	//
	// Rtn: the corresponding plug-in data type
	//
	IMPORT_C
	virtual const TDesC& FindHTTPCachingFlagL(TBool aCachingFlag) const;

	// Called upon successful completion of a connection to the WAP Stack, this
	// method extracts server headers and the negotiated capabilities
	//
	IMPORT_C
	void CompleteConnectionL();

	// Submit to the WAP Stack an initial transaction for the execution of the
	// next queued HTTP method for this handler.
	//
	IMPORT_C
	void InitiateTransactionL();

	// Creates and sends to the WAP Stack a new transaction for the WSP method
	// represented by the item at the head of the HTTP method queue.
	//
	IMPORT_C
	void SendTransactionL();

	// Start waiting (asynchronously) for a WAP Stack event resulting from the
	// most recently-submitted transaction.
	//
	IMPORT_C
	void WaitForEvent();

	// Perform HTTP Handler state machine actions associated with receiving
	// the EConnect_cnf event from the WAP Stack, after a connection has
	// been made.
	//
    IMPORT_C
	virtual void OnConnectionL();

	// Perform HTTP Handler state machine actions associated with the
	// EMethodInvoke_cnf event arising from the WAP Stack, which confirms that
	// a WSP method has been invoked.
	//
    IMPORT_C
	virtual void OnInvokationL();

	// Perform HTTP Handler state machine actions associated with the event
	// arising from the WAP Stack after HTTP server response headers have been
	// received.
	//
    IMPORT_C
	virtual void OnResultL();

	// Error code converter from stack errors to HTTP errors
	//
	// In:
	// aErrorCode - an error code obtained from some invocation of the WAP Stack
	//
	// Rtn: THttpReturnCode - the corresponding error code for HTTP 
	//
	IMPORT_C
    static THttpReturnCode StackErrToHttpErr(TInt aStackErr);

protected: // Attributes

	// The most recently-received response from the HTTP server (owned by this
	// class)
	//
    CHTTPResponse* iHTTPResponse;

private: // Methods

	// Perform HTTP Handler state machine actions associated with completion
	// of a WAP Stack transaction.
	//
	void CompletedL();

	// Search for an authentication token for the specified realm, returning an
	// index into the array of realms/tokens.
	//
	// In:
	// aMethod	- the realm name (as a narrow (8-bit) string)
	//
	// Rtn: realm/token index value
	//
    TInt FindAuthentication(const TDesC8& aRealm) const;

	// Handle EDisconnect_ind_s stack session event
	//
	void OnDisconnectionL();

	// Handle ESuspend_ind_s stack session event
	//
	void OnSuspendL();

	// Handle EResume_cnf_s stack session event
	//
	void OnResumeL();

	// Handle ERedirect_ind_s stack session event
	//
	void OnRedirectL();

	// Handle EAbort_ind_t stack transaction event
	//
	void OnAbortL();

	// Handle EPush_ind_t stack transaction event
	//
	void OnPushL();

	// Handle EConfirmedPush_ind_t stack transaction event
	//
	void OnConfirmedPushL();

	// Handle EException_ind_e stack exception event
	//
	void OnExceptionL();

	// Search the queued HTTP methods for the specified item.
	//
	// In:
	//	aMethod	- pointer to the required method object
	//
	// Rtn: TInt - its index in the queue or KErrNotFound if it isn't queued
	//
	TInt FindMethod(const CHTTPMethod* aMethod);

	// Panic handler for this class - kills the process in the event of a panic
	//
	// In:
	// aPanicCode - a code enumerating the panic that has occurred
	//
    void Panic(THttpPanicCode aPanicCode) const;

#if defined _DEBUG
	// Debug-only method definition to allow class invariant testing
	// Called by the standard macro __TEST_INVARIANT
	//
	void __DbgTestInvariant() const;

	// Debug-only method to dump to log a chunk of binary data
	//
	void DumpToLog(HBufC8& aData) const;
#endif

	// Spare methods for future BC. Any number of arguments or return values
	// can be packaged as a struct and supplied/obtained from this method.
	// Non-const and const versions supplied to increase flexibility for the
	// caller
	//
	IMPORT_C
	virtual TAny* Extend_CHTTPHandler(TAny* aArgs);

	IMPORT_C
	virtual TAny* Extend_CHTTPHandler_const(TAny* aArgs) const;

private: // Type definitions

	// A queue of CPluginOwner's, held by pointer but not owned by the HTTP
	// Handler. Used to hold HTTP Method plug-ins.
	//
	typedef CQueue<CPluginOwner, EFalse> CMethodQ;

private: // Attributes

	// Flag indicating whether this handler is suspended or active
	//
	TBool	iSuspend;

 	// Count of the number of missed events
 	TBool	iMissedSomething;
   
	// Flag indicating whether the handler is currently doing
	// anything. (i.e. can a new method be started immediately)
	TBool	iAmInUse;

	// The HTTP manager that owns this handler
	//
	CHTTPManager& iHTTPManager;

	// The queue of pending HTTP methods (not owned)
	//
	CMethodQ iQueuedMethods;

	// A pair of arrays of holding realms and user-name/password tokens used in
	// HTTP authentication
	//
	CArrayPtrSeg<HBufC8>* iAuthenticationRealm;
    CArrayPtrSeg<HBufC8>* iAuthenticationString;

	// The transaction adapter for this HTTP Handler - permits
	// CO or CL transactions via polymorphism
	//
	CWspTransAdapter* iTransactionAdapter;
	
	// The transaction adapters current event
	CWspTransAdapter::TEventType iEvent;

	// The currently active HTTP Method - not owned by the HTTP Handler
	//
	CPluginOwner* iMethod;
	
	// Flag indicating whether HTTP Headers have been recieved yet for the
	// current transaction
	//
	TBool iHeadersReceived;

	// The Url for which this HTTP Handler was initially created - owned by the
	// HTTP Handler
	//
	CUrl* iUrl;


	// Declare the CLogClient pointer (debug builds only)
   	__DECLARE_LOG;

	// Reserved for future expansion
	//
	TAny* iExpansionData;
	 
 	// Active object used to start the next fetch in cases of cancellation - owned.
 	//
 	CHTTPMethodStarter*	iMethodStarter;
 
};


#endif // __CHTTPHANDLER_H__
