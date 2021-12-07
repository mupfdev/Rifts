//
// CHTTPManager.h
// Copyright © 1998-2000 Symbian Ltd.  All rights reserved. 
//
// Purpose:  This file provides the definition of the CHTTPManager class.
//
// Comments: The HTTP Manager class maintains a connection with the WAP Stack
//			 and provides the first point-of-call interface to clients wishing
//			 to use HTTP.
//
//			 It reads the WAP Access Point settings from the Comms Database
//			 and initiates a WAP Stack connection for either an IP or an SMS
//			 bearer, and for a connection-oriented or a connection-less mode
//			 of operation. It also performs the WTLS operations necessary to
//			 authenticate the WAP Gateway when a secure connection is in use.
//
//			 It creates URL handler plug-ins able to execute particular HTTP
//			 methods on a remote HTTP server.
//			 
//			 This class is a specialism of CProtocolManager (a non-active
//			 Plug-In) to deal with the HTTP Protocol.

//

#ifndef __CHTTPMANAGER_H__
#define __CHTTPMANAGER_H__


// System includes
//
#include <wapcli.h>	// defines WAP Stack client
#include <cdblen.h> // defines Comms DB field names
#include <protom.h> // defines protocol manager
#include <LogDef.h> // defines client to Logging server

#include <agentclient.h> //defines RGenericAgent

// Local includes
//
#include "CQueue.h" // defines a queue class
#include "CHTTPHandler.h" // defines HTTP Handler
#include "CHTTPResources.h" // defines HTTP Handler


const TUint32 KMinimumGWTimeout=90000000; // minimum gateway timeout in microseconds (90 seconds)

// Forward class declarations
//
class CHTTPHandler;
class MSecurityPolicy;
class CWspSessAdapter;
class CCacheServerItem;
#ifdef __LOGGING
class CLogClient;
#endif

// Class definition for CHTTPManager
//
class CHTTPManager : public CProtocolManager
	{

public:	// Methods

	// Factory method to construct this class.
	//
	// In:
	// aFs		- an connected file system handle for use by this plug-in.
	// aLibrary - a handle for the DLL in which this plug-in resides
	// aIndex	- the plug-in's DLL index number.
	//
	// Rtn: a new CHTTPManager object, by ptr. Ownership is transferred to the
	//      caller.
	//
    IMPORT_C
	static CHTTPManager* NewL(RFs& aFs, const RLibrary& aLibrary, TInt aIndex);

	// Destructor for this class. Removes this object and releases memory held
	// by it
	//
	IMPORT_C
	~CHTTPManager();

	// Create a URL Handler to execute the given HTTP on the supplied URL.
	//
	// In:
	// aUrl				- the URL specifying the remote object to handle
	// aMethod			- the HTTP method to be invoked on the remote object
	// aWmlFetchFlags	- flag for fetch information; eg reload.
	//
	// Rtn: a URL Handler (ie. an HTTP Method) packaged as a Plug-in Owner
	//
    IMPORT_C
	virtual CPluginOwner* CreateUrlHandlerL(const CUrl& aUrl,
											const TDesC& aMethod,
											TInt aWmlFetchFlags);

	// As above, creates a URL Handler for a given URL and Method, to be
	// transmitted with the supplied block of Tx data. (Typically used for POST)
	//
	// In:
	// aUrl				- the URL specifying the remote object to handle
	// aMethod			- the HTTP method to be invoked on the remote object
	// aDpTxData		- the object that the URL handler will use collect the data
	//					for transmission.
	// aWmlFetch Flags	- flag for fetch information; eg reload
	//
	// Rtn: a URL Handler (ie. an HTTP Method) packaged as a Plug-in Owner
	//
    IMPORT_C
	virtual CPluginOwner* CreateUrlHandlerL
								   (const CUrl& aUrl,
									const TDesC& aMethod,
									MDataProviderTransmissionData& aDpTxData,
									TInt aWmlFetchFlags);

	// Accessor method to the status of this HTTP Manager's connection to the
	// WAP Stack
	//
	// Rtn: ETrue if connected
	//
  	// NB THIS METHOD SHOULD BE 'CONST'. HOWEVER IT CAN NOT BE CHANGED SINCE
	// THAT WOULD AFFECT BINARY COMPATIBILITY.
	IMPORT_C
	TBool Connected() /*const*/;

	// Connect to the WAP Stack, using the default WAP Access Point
	// configuration found in the Comms DB. Leaves if there is a failure at any
	// point during the connection.
	//
	// In:
	// aWmlFetchFlags = falgs assoicated with this fetch
	//
	// Rtn: any error code from the WAP Stack
	//
	IMPORT_C
	virtual TInt ConnectL(TInt aWmlFetchFlags);

	IMPORT_C
	void CancelConnect();
	// Disconnect from the WAP Stack.  May cause a forcible disconnection of the 
	// bearer too.
	//
	// In:
	//	aForciblyDisconnect - if ETrue, and the bearer is EIP, then forcibly
	//						  cause RNif to terminate the datacall in use.
	//
    IMPORT_C
	virtual void Disconnect(TBool aForciblyDisconnect = EFalse);

	// Redirect the connection to a different WAP Gateway, possibly on a different
	// bearer and with different security or connection mode settings.  This
	// requires disconnecting from the WAP Stack and reestablishing a new WSP
	// session for the new Gateway.
	//
	// In:
	//	aRedirectAddress	- the bearer-specific address of the new WAP Gateway
	//	aRedirectPort		- the port on the redirected GW
	//	aRedirectBearer		- the bearer to use for the redirection
	//	aReuseWtlsSessFlag	- flag set to ETrue if the existing WTLS session may
	//						  be reused for the redirection
	//	aIsPermanentRedirectFlag
	//						- flag set to ETrue if the redirection details should
	//						  be stored by the client
    IMPORT_C
	void DoWspRedirect(HBufC8* aRedirectAddress,
					   TInt    aRedirectPort,
					   TBearer aRedirectBearer,
					   TBool   aReuseWtlsSessFlag,
					   TBool   aIsPermanentRedirectFlag);

	// Return a connection to the cache.
	//
	// Rtn: a pointer to cache. Ownership is NOT trasnfered.
	//
	IMPORT_C
	CCacheServerItem* GetCacheClient() const;

public:	// Methods inherited from CPluginBase

	// Obtain the version number, maj.min.bld of this class
	//
	// Rtn: a version triplet
	//
	IMPORT_C
	virtual TVersion Version() const;

	// Obtain the name of this class
	//
	// Rtn: a name string - ownership is passed to the caller
	//
	IMPORT_C
	virtual HBufC* NameL() const;

	// Obtain the data type handled by this class
	//
	// Rtn: a datatype string - ownership is passed to the caller
	//
	IMPORT_C
	virtual HBufC* DataL() const;

	// Accessor for the HTTP resources. Used to get resource values read from
	// the HTTPUTIL resource file.
	//
	// Rtn: the resources handler - ownership is NOT transferred
	//
  	// NB THIS METHOD SHOULD RETURN 'CONST'. HOWEVER IT CAN NOT BE CHANGED SINCE
	// THAT WOULD AFFECT BINARY COMPATIBILITY.
	IMPORT_C
	/*const*/ CHTTPResources& Resources() const;

	// Callback method for the gateway time-out timer to be cancelled, either when
	// a connection has been successfully established, or when the ongoing method
	// has been cancelled.
	//
	IMPORT_C
	void GatewayTimeoutCancel();

public:	// Methods required by the Plug-In Manager

	// Obtain the Name and Data-type of the Plug-In represented by this class.
	// The ownership of the returned descriptor passes to the caller.
	//
  	// NB THESE METHODS SHOULD BE REPLACED WITH LITs IN THE CPHTTPPluginManager
	// CLASS. HOWEVER THEY CAN NOT BE REMOVED SINCE THAT WOULD AFFECT BINARY
	// COMPATIBILITY.
	IMPORT_C
	static HBufC* KName();

	IMPORT_C
	static HBufC* KData();

protected:	// Methods

	// Normal constructor - do non-allocating creation of this class
	//
	// In:
	// aFs		- an connected file system handle for use by this plug-in.
	// aLibrary - a handle for the DLL in which this plug-in resides
	// aIndex	- the plug-in's DLL index number.
	//
    IMPORT_C
	CHTTPManager(RFs& aFs, const RLibrary& aLibrary, TInt aIndex);

	// Second phase construction - any allocation for this class must take place
	// here. Sets up the resources required by an HTTP Manager.
	//
	IMPORT_C
	void ConstructL();

protected: // Type definitions

	// A queue of CHTTPHandler's, held by pointer and owned by the HTTP Manager.
	//
	typedef CQueue<CHTTPHandler, ETrue> COwningHandlerQueue;

protected: // Attributes

	// A queue of currently active HTTP Handlers - each is owned by the queue
	// itself
	//
	COwningHandlerQueue iActiveHandlers;

	// The WSP session adapter for this HTTP Handler - permits
	// CO or CL sessions via polymorphism
	//
	CWspSessAdapter* iSessionAdapter;

	// Flag indicating whether the current session adapter is a CO one or a CL
	// one
	//
	TBool iSessAdapterIsConnOriented;

	// Flag that indicates if HTTP can create caching method Plug-ins (not
	// allowed when a secure connection is being used)
	//
	TBool iCanCache;

private: // Classes

	//
	// Class to implement a timeout on initial gateway connections - allows
	// HTTP to return an error code if the GW cannot be reached
	//
	class CGatewayTimeout : public CTimer
		{
		public:
			static CGatewayTimeout* NewL(TInt aTimeoutPeriodMs,
										 CHTTPManager& aManager);
			virtual ~CGatewayTimeout();
			void Start();
			virtual void RunL();
		private:
			CGatewayTimeout(TInt aTimeoutPeriodMs,
						    CHTTPManager& aManager);
			void ConstructL();
		private:
			TInt iTimeoutPeriod;
			CHTTPManager& iCallbackOwner;
		};

	class CGenConnStatus : public CActive
		{
		public:
			CGenConnStatus(CHTTPManager& aManager);
			virtual ~CGenConnStatus();
			void Start();
			virtual void RunL();
			virtual void DoCancel();
			TInt ErrCode(); 
		private:
			virtual void Complete();
			CHTTPManager& iCallbackOwner;
			TNifProgressBuf iProgress;
			RNifMonitor iMonitor;
			TInt iErr;
		};

private:	// Methods

	// Decide what time-out to apply to gateway connections
	// The minimum timeout is always KMinimumGWTimeout unless 0
	//
	// Rtn: TUint32 - the length of the time-out period, in microsec. (0 = never)
	//
	TUint32 CalculateGWTimeout() const;


	// Get the time-out to apply to gateway connections from commdb
	//
	// Rtn: TUint32 - the length of the time-out period, in microsec. (0 = never)
	//
	TUint32 GetCommDbGWTimeoutL() const;


	// Helper method for ConnectL() and for DoWspRedirect().
	//
	TInt DoWspConnectionL();

	// Instantiate, if necessary, a session adapter suitable for the type of WSP
	// session to be used (connection-oriented or connectionless)
	//
	// In:
	//	aConnOriented	- ETrue if the session adapter required should be for CO
	//
	void CreateSessionAdapterL(TBool aConnOriented);

	// Perform the secure connection to the WTLS server and exchange ciphers, in
	// accordance with the security policy defined by a plugin.  This may attempt
	// an anonymous as well as an authenticating handshake, if the plugin allows.
	//
	void DoSecureConnectionL();

	// Attempt a secure handshake, either authenticating or anonymous.
	//
	// In:
	//	aAnonymousHandshake	- ETrue for an anonymous handshake; EFalse for authenticating.
	//
	void TrySecureConnectionL();

	// Connect to the plug-in server, to load the plug-in that implements
	// security policy for HTTP. Leaves if the plug-in can't be loaded
	//
	void LoadSecurityPolicyPluginL();

	// Reads the Comms DB to locate WAP Access Point configuration data. The
	// data returned is for the default AP.
	//
	// Out:
	// aBearer			- enumeration of bearer type, IP or SMS
	// aGateway			- the gateway address (IP quadruplet aaa.bbb.ccc.ddd) if
	//					  the chosen bearer is IP
	// aSecureConn		- flag indicating whether a secure connection is to be
	//					  used or not
	// aSvcCentreAddr	- phone number for the SMSC to which SMS will be sent by
	//					  the WAP Stack for the SMS bearer (not actually used by
	//					  HTTP though)
	// aServiceNum		- number identifying the gateway when an SMS bearer is
	//					  used.
	// aConnOriented	- flag indicating the connection mode:
	//						ETrue  = Connection Oriented (CO)
	//						EFalse = Connection-less (CL)
	//
    void ReadWapAccessPointInfoL(TBearer& aBearer,
								 TBuf8<KCommsDbSvrMaxFieldLength>& aGateway,
								 TBool& aSecureConn,
								 TBuf8<KCommsDbSvrMaxFieldLength>& aSvcCentreAddr,
								 TBuf8<KCommsDbSvrMaxFieldLength>& aServiceNum,
								 TBool& aConnOriented);

	// Configures GenericAgent with a set of overrides so that it dials the WAP
	// Access Point without a IAP or ISP dialogue appearing on the client
	//
	// In:
	//
    void SetupGenericAgentOverridesL(TBool aShowDialog);

#ifdef _DEBUG
	// Debug-only method to read the Comms DB again and compare the settings
	// with those stored in the class from a previous read, in order to ensure
	// that they haven't changed.
	//
	TBool CheckWapAccessPointInfoL();
#endif 

	// Callback for the gateway timeout timer, used if a handshake with the
	// WAP Gateway can't be completed within a given period
	//
	void GatewayTimeoutCallback();


 	// Panic handler for this class - kills the process in the event of a panic
	//
	// In:
	// aPanicCode - a code enumerating the panic that has occurred
	//
    void Panic(THttpPanicCode aPanicCode) const;

#if defined _DEBUG
	// Debug-only method to allow class invariant testing. Called by the
	// standard macro __TEST_INVARIANT
	//
	void __DbgTestInvariant() const;
#endif

	// Spare methods for future BC. Any number of arguments or return values
	// can be packaged as a struct and supplied/obtained from this method.
	// Non-const and const versions supplied to increase flexibility for the
	// caller
	//
	IMPORT_C 
	virtual TAny* Extend_CHTTPManager(TAny* aArgs);

	IMPORT_C
	virtual TAny* Extend_CHTTPManager_const(TAny* aArgs) const;


	virtual void HideConnDialogL(CCommsDatabase* aCommDB);

private: // Attributes

	// Resource handler for the HTTPUTIL resource file
	//
	CHTTPResources* iResources;

	// The security policy provider that enables HTTP to decide how it deals
	// with WTLS
	//
	CPluginOwner* iSecurityPolicy;


	// Most recently created HTTP method plugin owner - NB: _NOT_ owned by this class!
	//
	CPluginOwner* iMostRecentMethodOwner;

	// WAP Access Point configuration data read from Comms DB

	// The bearer type - IP or SMS
	//
	TBearer								iBearer;

	// The gateway address (aaa.bbb.ccc.ddd quadruplet for IP bearer only)
	//
	TBuf8<KCommsDbSvrMaxFieldLength>	iGateway;

	// Flag indicating whether a secure connection is to be used or not
	//
	TBool								iSecureConn;

	// Service Centre address - the SMSC contacted by the SMS stack when an SMS
	// bearer is used (but not used by HTTP)
	//
	TBuf8<KCommsDbSvrMaxFieldLength>	iSvcCentreAddr;

	// The Service Number at which the gateway is located, when an SMS bearer is
	// used
	//
	TBuf8<KCommsDbSvrMaxFieldLength>	iServiceNum;

	// Flag indicating whether a Connection-Oriented WSP session is to be used
	//
	TBool								iConnOriented;

	// Flag indicating that an existing WTLS session may be reused
	//
	TBool iReuseWtlsSession;

	// GenericAgent handle - to establish Internet connection and keep it open;
	// also to receive status messages during and after connection
	//
	RGenericAgent iGenericAgentHnd;
	TBool iConnecting;
	// Status of requests made of GenericAgent
	//
	TRequestStatus iGenericAgentStatus;

	// A timeout timer, used to detect if contact with the Gateway has taken
	// too long
	friend class CGatewayTimeout;
	CGatewayTimeout* iGWTimer;

	// Declare the CLogClient pointer (debug only)
	//
	__DECLARE_LOG;

	// Reserved for future expansion
	//
	TAny* iExpansionData;

	// Connection to cache client. Owned.
	//
	CCacheServerItem* iCacheClient;

	CStoreableOverrideSettings* iOverrides;
};


#endif // __CHTTPMANAGER_H__
