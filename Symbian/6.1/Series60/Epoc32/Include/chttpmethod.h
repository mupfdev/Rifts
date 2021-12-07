//
// CHTTPMethod.h
// Copyright © 1998-2000 Symbian Ltd.  All rights reserved. 
//

//
// Purpose:  This file provides the definition of the CHTTPMethod class.
//
// Comments: The HTTP Method class is an abstract base class for all HTTP
//			 methods; e.g. GET, POST.  Further derivations may be made to add
//			 additional behaviour, e.g. caching.
//
//			 This class is an active plug-in specialism.
//

#if !defined(__CHTTPMETHOD_H__)
#define __CHTTPMETHOD_H__

// System includes
//
#if !defined(__URLHND_H__)
#include <UrlHnd.h>
#endif
#if !defined(__LOGDEF_H__)
#include <LogDef.h>
#endif
#if !defined(__HTTPSTD_H__)
#include <HttpStd.h>
#endif

// Local includes
//
#if !defined(__THTTPFIELDS_H__)
#include "THttpFields.h"
#endif

// Forward class declarations
//
class CHTTPHeader;
class CHTTPResponse;
class CHTTPHandler;
#ifdef __LOGGING
class CLogClient;
#endif

// Class definition for CHTTPMethod
//
class CHTTPMethod : public CUrlHandler
    {
public: // Enumerated types used in this class

	// Actions that might be taken following a remote server response to an
	// HTTP method invocation
    enum TActions
        {
        EAbort	  = 0,
		EContinue = 1,
		ERetry	  = 2,
		ECacheContinue = 3,
		EAbortWithErrorDeck = 4
        };

public:	// Methods

	//
	// Note: no factory NewL() method to construct this class, since it is
	// abstract
	//

	// Destructor
	//
    IMPORT_C
	virtual ~CHTTPMethod();

	// Creates a link to the HTTP Handler for the remote server this method is 
	// acting on
	//
	// In:
	// aHandler	- the HTTP handler. No ownership transfer.
	//
    IMPORT_C
	virtual void SetHTTPHandler(CHTTPHandler* aHandler);

	// Obtain the HTTP method type - this must be implemented in sub-classes
	//
	// Rtn: the descriptor that this method name is stored in
	//
    IMPORT_C
	virtual const TDesC& Method() const = 0;

	// Entry point for the HTTP method to deal with the HTTP response obtained
	// from the remote server. Breaks out to five methods that must be
	// implemented by sub-classes, according to the response status
	//
	// In:
	// aResponse	: the remote server's HTTP response. No ownership transfer.
	//
	// Rtn: an action type to be taken resulting from HTTP processing the
	//      server response
	// 
    IMPORT_C
	virtual TActions HeaderResponseL(CHTTPResponse& aResponse);

	// Entry point for the HTTP method to deal with the HTTP body. An empty
	// implementation is provided in this class which should be overridden in
	// sub-classes where the body is of interest.
	//
	// In:
	// aBody	: the body data obtained from the remote server. No ownership
	//			  transfer.
	//
    IMPORT_C
	virtual void BodyResponseL(HBufC8& aBody);

	// Allows this method to write into the headers sent to the remote server
	// at the start of an HTTP request
	//
	// In:
	// aHeader	: the header to be written into and transmitted. No ownership
	//			  transfer.
	//
    IMPORT_C
	virtual void HeaderL(CHTTPHeader& aHeader) const;

	// Accessor method to obtain the body of a previous HTTP response - should
	// a sub-class choose to store it. The default implementation does not
	// store the response, so returns an empty descriptor.
	//
	// Rtn: a descriptor containing the body data.
	//
    IMPORT_C
	virtual const TDesC8& BodyL() const;

	// Callback method invoked by the HTTP handler when this HTTP method is due
	// to complete. Allows HTTP method subclasses to do something before they
	// are removed. Default implementation does nothing.
	//
    IMPORT_C
	virtual void Completed();

		// Set some flags associated with this fetch
	IMPORT_C
	void SetFetchFlags(TInt aFlags);

	// Retrieve any flags associated with this fetch
	IMPORT_C
	TInt FetchFlags() const;

public: // Methods inherited from CUrlHandler/CActive

	// Begin this active object - should be called once, after the object is
	// constructed. Allows it to make initial async requests. In this case it
	// invokes the HTTP Handler's own AO BeginL().
	//
    IMPORT_C
	virtual void BeginL();

	// Run this active object - invoked by the active scheduler, when an async
	// request made by this object has completed.
	//
    IMPORT_C
	virtual void RunL();

	// NOTE THAT THIS CLASS COULD HAVE A DoCancel() METHOD, BUT ONE CAN'T BE
	// ADDED NOW SINCE IT WOULD BREAK BC.  IN ANY CASE, SUB-CLASSES MAY STILL
	// IMPLEMENT A DoCancel() IF THEY REQUIRE ONE. AN IMPLEMENTATION IS
	// INHERITED FROM CActivePluginBase FOR THOSE THAT DON'T.
    IMPORT_C
	virtual void DoCancel();

	// Entry point to allow protocol-specific commands to be issued; provided
	// for sub-class specialisation. Default implementation does nothing.
	//
    IMPORT_C
	virtual void ProtocolCommandL();

	// Provide a cancel signalling method
	// to allow cancellation of the active plugin
	// from within its RunL, when the CActive::Cancel()
	// call will not work
	IMPORT_C
	virtual void RequestCancel();

	// Method to propogate the HTTP status to the observer, as a status message
	// or as an error message. May be overridden by sub-classes for specific
	// or modified behaviour. (e.g. caching)
	//
	// In:
	//	aCode - the HTTP status code from the WAP gateway/origin server
	//
	IMPORT_C
	virtual void PropogateHTTPStatus(THttpStatusCode aCode);

	TInt MostRecentStatusMsg() const {return  iMostRecentStatusMsg;}
	void SetMostRecentStatusMsg(TInt aStatus)  {iMostRecentStatusMsg=aStatus;}
    CHTTPHandler* HTTPHandler() { return iHTTPHandler;}

protected: // Methods

	// Normal constructor - do non-allocating creation of this class
	//
	// In:
	// aFs		- the filesystem handle from which this active plug-in was made
	// aLibrary - handle to the DLL in which this active plug-in class is held
	// aIndex	- index of the plug-in in the DLL?
	//
    IMPORT_C
	CHTTPMethod(RFs& aFs, const RLibrary& aLibrary, TInt aIndex);
    
	// Methods associated with each general class of response codes. These
	// methods should be specialised in derived classes; i.e. a cached method
	// might handle ENotModified
	//
	// In:
	// aResponse	- the HTTP response. No ownership transfer
	//
	// Rtn: the resulting action to be taken by the HTTP handler.

	// Act on Informational (1xx series) HTTP status codes
	//
    IMPORT_C
	virtual CHTTPMethod::TActions HTTP_InformationalL(CHTTPResponse& aResponse);

	// Act on Successful (2xx series) HTTP status codes
	//
    IMPORT_C
	virtual CHTTPMethod::TActions HTTP_SuccessfulL(CHTTPResponse& aResponse);

	// Act on Redirection (3xx series) HTTP status codes
	//
    IMPORT_C
	virtual CHTTPMethod::TActions HTTP_RedirectionL(CHTTPResponse& aResponse);

	// Act on Client Error (4xx series) HTTP status codes
	//
    IMPORT_C
	virtual CHTTPMethod::TActions HTTP_ClientErrorL(CHTTPResponse& aResponse);

	// Act on Server Error (5xx series) HTTP status codes
	//
    IMPORT_C
	virtual CHTTPMethod::TActions HTTP_ServerErrorL(CHTTPResponse& aResponse);

	// Perform any special action required for authentication to the remote
	// server
	//
    IMPORT_C
	virtual CHTTPMethod::TActions HTTP_AuthenticateL(CHTTPResponse& aResponse);

	// Perform any special action required when an authentication dialog has
	// timed out
	//
    IMPORT_C
	virtual CHTTPMethod::TActions DialogTimeoutL(CHTTPResponse& aResponse);

	// Second phase construction - any allocation for this class must take place
	// here. Sets up the resources required by HTTP methods.
	//
	IMPORT_C
	void ConstructL();


	// Returns false if iAuthentication contains the same
	// authentication details as the URL, and true under all other
	// circumstances.
	TBool NotUsingAuthenticationFromUrlL() const;

protected: // Attributes

	// The HTTP Handler which owns and invokes this HTTP method. Not owned by
	// this class
    CHTTPHandler* iHTTPHandler;

	// An authentication string that may be appended to an HTTP request header
	// sent to the remote server. Not owned by this class.
    HBufC8* iAuthentication;

	// The content-type of data received in the HTTP response
	HBufC* iContentType;

	// Flag indicating whether the content-type has been sent to the observer
    TBool iContentTypeSet;

	// The charset used to encode data received in the HTTP response
	HBufC* iCharSet;

	// Most recently-sent status message
	TInt iMostRecentStatusMsg;

	// Most recent response to the received headers
	TActions iMostRecentHeaderResponse;

	// Flags associated with this fetch
	TInt iFetchFlags;

	// Declare the CLogClient pointer
   	__DECLARE_LOG;

private: // Methods

	// Kills the process in the event of a panic
	//
    void Panic(THttpPanicCode aPanicCode) const;

#if defined _DEBUG
	// Debug method definition to allow class invariant testing
	// Called by the standard macro __TEST_INVARIANT
	void __DbgTestInvariant() const;
#endif

	// Spare methods for future BC, for this class. IMPORT_C to reserve a vtbl
	// slot.
	//
	IMPORT_C
	virtual TAny* Extend_CHTTPMethod(TAny* aArgs);
	IMPORT_C
	virtual TAny* Extend_CHTTPMethod_const(TAny* aArgs) const;

private: // Attributes

	// For future expansion
	TAny* iExpansionData;
};


#endif // __CHTTPMETHOD_H__

