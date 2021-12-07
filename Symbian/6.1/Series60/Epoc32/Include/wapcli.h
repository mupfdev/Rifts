// WAPCLI.H
//
//

#if !defined(__WAPCLI_H__)
#define __WAPCLI_H__

#include <e32base.h>



struct TCrCertAddParameters;
// Client panic reasons
enum TWAPClientPanic
	{
	EBadRequest,
	EBadDescriptor,
	EBadConnectionRemove, 
	EBadSubsessionHandle 
	};

enum {KDefaultMessageSlots = 10};


enum TCertType
	{
	EClCert,
	EServCert
	};


//**********************************
//RWAPServ
//**********************************
// The client class. 
// The connect function starts the server, if it not already running.
// An RSessionBase sends messages to the server with the function 
// RSessionBase::SendReceive() specifying an opcode (TWAPServRqst) and an 
// array of argument pointers. 

class RWAPServ : public RSessionBase
	{
	public:
		IMPORT_C RWAPServ();
		IMPORT_C TInt Connect(TInt aDefaultMessageSlots = KDefaultMessageSlots);
		IMPORT_C void ResourceCountMarkStart();
		IMPORT_C void ResourceCountMarkEnd();
		IMPORT_C TInt ResourceCount();
		IMPORT_C TVersion Version() const;
		IMPORT_C void Close();
	};

// The message array to pass parameters in between client and server.
typedef TAny* MsgArray[KMaxMessageArguments];

enum TBearer
	{
	EAll,
	EIP,
	ESMS7,
	ESMS,
	EWAPSMS7,
	EWAPSMS
	};

//**********************************
//RWAPConn
//**********************************
// Represents a subsession with the server. Each RWAPConn corresponds to a
// specific CWAPConn in the server. A RWAPConn stores a handle from it's 
// server side CWAPConn, and uses this to identify the CWAPConn during 
// communication.

class RWAPConn : public RSubSessionBase
	{
	public:
		typedef TUint16 TPort;


		IMPORT_C virtual TInt Close();
		// Close a connection.

		enum 
			{
			ERetCodeBase      = -5500,
			EWSPCORetCodeBase = ERetCodeBase + 25,
			EWSPCLRetCodeBase = ERetCodeBase + 50,
			EWTPRetCodeBase   = ERetCodeBase + 75,
			EWDPRetCodeBase   = ERetCodeBase + 100,
			EWTLSRetCodeBase  = ERetCodeBase + 125,
			ERetCodeTop       = ERetCodeBase + 200
			};
		enum TReturnCodes
			{  
			EMoreData           = ERetCodeBase + 0,
			EBearerError        = ERetCodeBase + 1,
			EPortAlreadyBound   = ERetCodeBase + 2,
			ECannotOpenPort     = ERetCodeBase + 3,
			ETooManyConnections = ERetCodeBase + 4,
			EBadConnection      = ERetCodeBase + 5,
			EBufferTooSmall     = ERetCodeBase + 6
			};

		IMPORT_C class RWTLS Wtls();

		IMPORT_C void GetRemoteAddress(TDes8& aAddress, TPort& aPort) const;
		// Get the address and port of the server.

		IMPORT_C void GetBearer(TBearer& aBearer) const;
		// Get the current bearer for this connection.
		
		IMPORT_C TInt GetLocalPort(TPort& aPort) const;
		// Get the local port of this endpoint.
		
		IMPORT_C void CancelAll();
		// Cancels all outstanding operations for this connection.

		enum TMethod 
			{
			EGet = 0x40,
			EOptions = 0x41,
			EHead = 0x42,
			EDelete = 0x43,
			ETrace = 0x44,
			EPost = 0x60,
			EPut = 0x61
			};

		
	protected:

		TInt Open(RWAPServ& aServer, // the WAP server thread session.
			const TDesC8& aRemoteHost, // bearer dependent name or address
			TPort aRemotePort,
			TPort aLocalPort,
			TBearer aBearer, // an enum
			TBool aSecureConn,
			TInt aFunction);

	};

class RWTLS : public RSubSessionBase
	{
	public:
		
		enum TReturnCodes
			{
			EOutOfMemory            = RWAPConn::EWTLSRetCodeBase + 0,
			ESocketError            = RWAPConn::EWTLSRetCodeBase + 1,
			EBadParameters          = RWAPConn::EWTLSRetCodeBase + 2,
			ESocketError2           = RWAPConn::EWTLSRetCodeBase + 3,
			EResumeIDNotFound       = RWAPConn::EWTLSRetCodeBase + 4,
			EResumeError            = RWAPConn::EWTLSRetCodeBase + 5,
			ERenegotiationRequest   = RWAPConn::EWTLSRetCodeBase + 6,
			EIllegalCall            = RWAPConn::EWTLSRetCodeBase + 7,
			EConnectionCloseNotify  = RWAPConn::EWTLSRetCodeBase + 8,
			ESessionCloseNotify     = RWAPConn::EWTLSRetCodeBase + 9,
			ENoConnection           = RWAPConn::EWTLSRetCodeBase + 10,
			EUnexpectedMessage      = RWAPConn::EWTLSRetCodeBase + 11,
			EBadRecordMac           = RWAPConn::EWTLSRetCodeBase + 12,
			EDecryptionFailed       = RWAPConn::EWTLSRetCodeBase + 13,
			ERecordOverflow         = RWAPConn::EWTLSRetCodeBase + 14,
			EHandshakeFailure       = RWAPConn::EWTLSRetCodeBase + 15,
			EDecompressionFailure   = RWAPConn::EWTLSRetCodeBase + 16,
			EBadCertificate         = RWAPConn::EWTLSRetCodeBase + 17,
			EUnsupportedCertificate = RWAPConn::EWTLSRetCodeBase + 18,
			ECertificateRevoked     = RWAPConn::EWTLSRetCodeBase + 19,
			ECertificateExpired     = RWAPConn::EWTLSRetCodeBase + 20,
			ECertificateUnknown     = RWAPConn::EWTLSRetCodeBase + 21,
			EIllegalParameter       = RWAPConn::EWTLSRetCodeBase + 22,
			EUnknownCA              = RWAPConn::EWTLSRetCodeBase + 23,
			EAccessDenied           = RWAPConn::EWTLSRetCodeBase + 24,
			EDecodeError            = RWAPConn::EWTLSRetCodeBase + 25,
			EDecryptError           = RWAPConn::EWTLSRetCodeBase + 26,
			EUnknownKeyId           = RWAPConn::EWTLSRetCodeBase + 27,
			EDisableKeyId           = RWAPConn::EWTLSRetCodeBase + 28,
			EKeyExchangeDisabled    = RWAPConn::EWTLSRetCodeBase + 29,
			ESessionNotReady        = RWAPConn::EWTLSRetCodeBase + 30,
			EUnknownParameterIndex  = RWAPConn::EWTLSRetCodeBase + 31,
			EDuplicateFinishedRecv  = RWAPConn::EWTLSRetCodeBase + 32,
			EExportRestriction      = RWAPConn::EWTLSRetCodeBase + 33,
			EProtocolVersion        = RWAPConn::EWTLSRetCodeBase + 34,
			EInsufficientSecurity   = RWAPConn::EWTLSRetCodeBase + 35,
			EInternalError          = RWAPConn::EWTLSRetCodeBase + 36,
			EUserCanceled           = RWAPConn::EWTLSRetCodeBase + 37,
			ENoRenegotiation        = RWAPConn::EWTLSRetCodeBase + 38,

			EErrGeneral             = RWAPConn::EWTLSRetCodeBase + 39,
			EErrBulk                = RWAPConn::EWTLSRetCodeBase + 40,
			EErrMac                 = RWAPConn::EWTLSRetCodeBase + 41,
			EErrSequenceNumberMode  = RWAPConn::EWTLSRetCodeBase + 42,
			EErrKeyRefreshRate      = RWAPConn::EWTLSRetCodeBase + 43,

			};

		enum TIdType 
			{
			EIdNull,
			EText, 
			EBinary, 
			EKeyHashSha = 254, 
			EX509Name = 255
			};

		enum TKeyExchangeSuite 
			{
			ETakeFromWIM = 0,
			ESharedSecret = 1,
			EDHAnon,
			EDHAnon512,
			EDHAnon768,
			ERsaAnon,
			ERsaAnon512,
			ERsaAnon768,
			ERsa,
			ERsa512,
			ERsa768,
			EEcdhAnon,
			EEcdhAnon113,
			EEcdhAnon131,
			EEcdhEcdsa
			};

		IMPORT_C TInt SetKeyExchangeSuite(
			TKeyExchangeSuite aSuite, 
			TIdType IdType, 
			const TDesC8& aKeyId);

		enum TBulkEncryptionAlgorithm
			{
			EBulkNull     = 0x00,
			ERc5_cbc_40   = 0x01,
			ERc5_cbc_56   = 0x02,
			ERc5_cbc      = 0x03,
			EDes_cbc_40   = 0x04,
			EDes_cbc      = 0x05,
			E3Des_cbc_ede = 0x06,
			EIdea_cbc_40  = 0x07,
			EIdea_cbc_56  = 0x08,
			EIdea_cbc     = 0x09
			};
	
		enum TMacAlgorithm
			{
			ESha_0         = 0x00,
			ESha_40        = 0x01,
			ESha_80        = 0x02,
			ESha           = 0x03,
			ESha_xor_40    = 0x04,
			EMd5_40        = 0x05,
			EMd5_80        = 0x06,
			EMd5           = 0x07
			};
		
		struct TCipherSuite
			{
			TBulkEncryptionAlgorithm iBulkEncryptionAlgorithm;
			TMacAlgorithm            iMacAlgorithm;
			};
	
		typedef CArrayFixFlat<TCipherSuite> CipherSuiteArray;
	
		IMPORT_C TInt SetCipherSuites(const CipherSuiteArray& aCipherSuites);
				
		enum TSequenceNumberMode 
			{
			ENotUsed = 0, 
			EImplicit, 
			EExplicit
			};
		
		IMPORT_C TInt SetSequenceNumberMode(TSequenceNumberMode aMode);
		IMPORT_C TInt SetKeyRefreshRate(TUint8 aRate);
		IMPORT_C TInt SetSharedSecret(const TDesC8& aSharedSecret);
		IMPORT_C TInt SetRecordLengthUsage(TBool aUsage);
		// Set suggested security parameters before (re)negotiating with the server. 
		// Use the getters to see which values where agreed upon.
		// These return ETrue on success otherwise EFalse.

		// This is returned in the TRequestStatus on completion in 
		// Connect and ConnectPhaseTwo.
		enum HandshakeResult
			{
			EServerCertificateValid,
      EServerCertificateNotValid,
			ECertificateRequested,
			EHandshakeOk,
			EHandshakeError,
			EHandshakeUserAbort,
      EClCertificateNotSelected,
			EWimClosed,
			EConnClosed,
			EConnNone,
      EWtlsUnexpectedMessage,
      EClientBadCertificate ,
      EClientUnsupportedCertificate ,
      EClientRevokedCertificate ,
      EClientExpiredCertificate,
      EClientUnknownCertificate,
      EClientUnknownCA ,
      EClientAccessDenied ,
      EServerDecodeError ,
      EServerDecryptError ,
      EServerExportRestriction ,
      EServerProtocolVersion,
      EInternalWTlsError
			};


		IMPORT_C void Connect(TRequestStatus&, TBool aTwoPhaseHandshake);
		// Make the handshake with the server to agree on the security parameters.
		// The connection must be Opened (in secure mode) before this. 
		// Optionally the parameter setters may precede this call. 
		// If called more than once a renegotiation is done with possibly 
		// new parameters.
		// aTwoPhaseHandshake may be set to ETrue to return half way through to check
		// the server certificate. CancelConnect() or ConnectPhaseTwo() should succeed
		// this call if two phase connect is used.

		IMPORT_C void Connect(TRequestStatus& );

		IMPORT_C void CancelConnect();
		// Cancels the secure handshake. May be called after the first phase.
		IMPORT_C TInt ConnectPhaseTwo(TRequestStatus&);
		// Continue the secure handshake after the first phase has completed.
		IMPORT_C void CancelConnectPhaseTwo();
		
		IMPORT_C TInt GetCipherSuite(TCipherSuite& aCipherSuite) const;
		
		IMPORT_C TInt GetSequenceNumberMode(TSequenceNumberMode& aMode) const;
		IMPORT_C TInt GetKeyRefreshRate(TUint8& aRate) const;
		IMPORT_C TInt GetKeyExchangeSuite(TKeyExchangeSuite& aSuite) const;

		IMPORT_C class RCertificate ServerCert();

		IMPORT_C class RCertificate ClCert();

		IMPORT_C HandshakeResult GetConnectionStatus();
		
	private:
		friend class RWAPConn;

		RWTLS(const RSubSessionBase& aSubSession) 
			: RSubSessionBase(aSubSession)
			{}
		HandshakeResult iHandshakeResult;
};

class RCertificate : public RSubSessionBase
	{
	public:
		typedef TUint16 TCertId;
		typedef TDesC8 TCertificate; // binary format

		IMPORT_C TInt Load(const TDesC8& aSubject);
		// Load a new certificate from persistent storage. Identified by subject.
		// NB: Not currently supported - returns KErrNotSupported

		IMPORT_C TInt LoadById(const TCertId& aId);
		// Load a new certificate from persistent storage. Identified by id.
		// NB: Not currently supported - returns KErrNotSupported

		IMPORT_C TInt Delete(const TDesC8& aSubject);
		// Delete certificate identified by subject from the certificate store.

		IMPORT_C TInt Save(const TCertificate& aCertificate, TDes8& aSubject);
		// Save this cert to persistent storage

    IMPORT_C TInt Save(const TDesC8& aCertificate ,
                                          TCrCertAddParameters& params, TDes8& aSubject);
    // Save this cert to persistent storage


		IMPORT_C TInt FindFirst(TDes8& aSubject, TCertId& aId) const;
		// Find subject of first cert in persistent storage. Use aId to find next.
		// NB: Not currently supported - returns KErrNotSupported

		IMPORT_C TInt FindNext(TDes8& aSubject, TCertId& aId) const;
		// Find subject of next cert
		// NB: Not currently supported - returns KErrNotSupported

		enum TStatus
			{
			EOk, 
			ENotYetValid, 
			EExpired, 
			EUnknownCA, 
			EPermanentStorageReadError
			};


		struct TInfo
			{
			TUint32 iValidNotBefore;     //  is first valid date of the cert (unix GMT). 
			TUint32 iValidNotAfter;      //  is last valid date of the cert (unix GMT)
			TUint16 iSubjectCharacterSet;//  is an IANA defined number.
			TUint16 iIssuerCharacterSet; //  is an IANA defined number.
			TDes8*  iSubject;             
			TDes8*  iIssuer;             
			TStatus iServerCertificateStatus;
			TDes8*  iFingerPrint;
			};

		IMPORT_C TInt Info(TInfo& aInfo) const;
		// Get the details of the server certificate of this secure connection OR the 
		// certificate explicitly loaded from persistent storage.

	private:
		friend class RWTLS;
		RCertificate(const RSubSessionBase& aSubSession) 
			: RSubSessionBase(aSubSession)
			{}
	private:
		TCertType iCertType;

	};

class RWSPCOTrans : public RSubSessionBase
	{
	public:
		IMPORT_C RWSPCOTrans();
		IMPORT_C ~RWSPCOTrans();

		IMPORT_C TInt Acknowledge(const TDesC8& aAckHeaders);
		// Acknowledges a transaction. This must be used to accept a
		// confirmed push from the server. 
		
		enum TDataType
			{
			EPushBody = 0,
			EPushHeaders,
			EResultStatus,
			EResultBody,
			EResultHeaders,
			EInvokeUri,
			EInvokeMethod,
			EInvokeHeaders,
			EInvokeBody,
			EAckHeaders,
			EAbortReason
			};
	
		IMPORT_C TInt GetData(TDes8& aBuffer, TDataType aDataType, TInt* aSizeLeft = 0) const;
		// Retrieves the data associated to a transaction.
		
		enum TState 
			{
			EInit = 0,
			ERequesting,
			EReplying,
			EDone,
			EAborted,
			EPushing
			};

		typedef TPckgBuf<TState> TStatePckg;
		typedef TPckgBuf<TInt> THandlePckg;
	
		IMPORT_C TInt GetState(TState& aState) const;
		// Retrieve the state the transaction is in.

		typedef TUint8 TAbortReason;

		IMPORT_C TInt Abort(TAbortReason aReason);
		// Aborts a method invoke or push transaction.

		IMPORT_C TInt Release();

		typedef TInt TTransID;
		IMPORT_C TInt Id(TTransID& aId);

	private:
		friend class RWSPCOConn;

		RWSPCOTrans(const RSubSessionBase& aSubSession); 

		THandlePckg iHandlePckg;
	};

class RWSPCOConn : public RWAPConn
	{
	public:
		IMPORT_C TInt Open(RWAPServ& aServer,
			const TDesC8& aRemoteHost,
			TPort aRemotePort,
			TPort aLocalPort,
			TBearer aBearer,
			TBool aSecureConn);
		// Open fully defined

		// Note: no bound Open in this layer!

		IMPORT_C virtual TInt Close();

		IMPORT_C TInt Connect(const TDesC8& aClientHeaders, class CCapCodec* aCap = 0);
		
		// Aborts a method invoke or push transaction. 
		// State of transaction can be INIT or REQUESTING.
		
		IMPORT_C TInt Disconnect();
		
		IMPORT_C TInt Suspend();
		IMPORT_C TInt Resume(RWSPCOConn& aBlankConn,
			const TDesC8& aHeaders);
		// The blank connection in Resume() could be using another bearer.
		
		enum TSessionState
			{
			EInit = 0,
			EConnecting,
			EConnected,
			ESuspended,
			EResuming,
			EReplying,
			EDisconnected
			};
	
		IMPORT_C TInt GetSessionState(TSessionState& aState) const;
		// Get the state this session is in.

		enum TSessionDataType 
			{
			EServerHeaders = 12,
			EClientHeaders,
			ECapabilities,
			ERedirectOptions,
			ERedirectAddresses,
			EQueueLen,
			EErrorHeaders,
			EErrorBody,
			EDisconReason,
			ESuspendReason
			};

		enum TReturnCodes
			{
			EBufferTooSmall      = EWSPCORetCodeBase + 0,
			EInvalidSession      = EWSPCORetCodeBase + 1,
			EInvalidTransaction  = EWSPCORetCodeBase + 2,
			EParameterError      = EWSPCORetCodeBase + 3,
			ESessionNotConnected = EWSPCORetCodeBase + 4,
			ENotSupported        = EWSPCORetCodeBase + 5,
			EInvalidState        = EWSPCORetCodeBase + 6,
			ESessionClosed       = EWSPCORetCodeBase + 7,
			EMRUExceeded         = EWSPCORetCodeBase + 8,
			EInvalidBufferSize   = EWSPCORetCodeBase + 9,
			EDataNotAvailable    = EWSPCORetCodeBase + 10,
			EErrorTimeout        = EWSPCORetCodeBase + 11
			};
			
	
		IMPORT_C TInt GetSessionData(TDes8& aData, TSessionDataType aType) const;

		IMPORT_C TInt CreateTransaction(TMethod aMethod, 
			const TDesC& aURI, 
			const TDesC8& aHeaders, 
			const TDesC8& aBody,
			RWSPCOTrans& aTrans);
	
	
		enum TEventType
			{    
			// session events
			EDisconnect_ind_s = 0,
			ESuspend_ind_s,
			EResume_cnf_s,
			EConnect_cnf_s,
			ERedirect_ind_s,
				
			// transaction events
			EMethodInvoke_cnf_t,
			EMethodResult_ind_t,
			EAbort_ind_t,
			EPush_ind_t,
			EConfirmedPush_ind_t,
				
			// exception events
			EException_ind_e,
			};

		typedef TPckgBuf<TInt> TEvent;
	
		IMPORT_C void GetEvent(TEvent& aEvent, 
			RWSPCOTrans& aTrans, 
			TRequestStatus& aStatus) const;
		// Gets next session or transaction event on this session.
		
		IMPORT_C void CancelGetEvent();
		// Cancel the asynchronous GetEvent operation.

		IMPORT_C TInt GetEvent(TEvent& aEvent, RWSPCOTrans& aTrans) const; 
		// Synchronous version
		
		IMPORT_C TInt GetNrOfEvents(TUint& aNrOfEvents) const;
		// Return the number of events pending for the session.
		
	};
	
class RWSPCLConn : public RWAPConn
	{
	public:
		IMPORT_C TInt Open(RWAPServ& aServer,
			const TDesC8& aRemoteHost,
			TPort aRemotePort,
			TPort aLocalPort,
			TBearer aBearer,
			TBool aSecureConn);
		// Fully defined Open.

		IMPORT_C TInt Open(RWAPServ& aServer, TPort aLocalPort);
		// Bound Open.
	
		typedef TPckgBuf<TUint8> TTransID;
	
		IMPORT_C TInt UnitInvoke(TMethod aMethod, 
			const TDesC& aURI, 
			const TDesC8& aBody, 
			const TDesC8& aHeaders, 
			TTransID aID);
		// Invoke a method on the server.
	
		typedef TPckgBuf<TUint8> TWSPStatus;

		IMPORT_C void UnitWaitResult(TDes8& aBody, 
			TDes8& aHeaders,
			TTransID& aID,
			TWSPStatus& aWSPStatus,
			TRequestStatus& aRequestStatus);
		// Wait for result from the server possibly caused by a UnitInvoke. 
		// Assumes a bound RWSPCLConn object.
		
		IMPORT_C void CancelUnitWaitResult();
		// Cancel the asynchronous UnitWaitResult operation.
		
		IMPORT_C TInt UnitWaitResult(TDes8& aBody, 
			TDes8& aHeaders,
			TTransID& aID,
			TWSPStatus& aWSPStatus);
		// The synchronous version

		typedef TTransID TPushID;
		
		IMPORT_C void UnitWaitPush(TDes8& aBody,
			TDes8& aHeaders,
			TPushID& aID,
			TRequestStatus& aStatus);
		// Wait for push from the server.
		// Assumes a bound RWSPCLConn object.
		
		IMPORT_C void CancelUnitWaitPush();
		// Cancel the asynchronous UnitWaitPush operation.
		
		IMPORT_C TInt UnitWaitPush(TDes8& aBody,
			TDes8& aHeaders,
			TPushID& aID);
		// The synchronous version

		enum TReturnCodes
			{			
			EBufferTooSmall      = EWSPCLRetCodeBase + 0,
			EInvalidSession      = EWSPCLRetCodeBase + 1,
			EParameterError      = EWSPCLRetCodeBase + 2,
			ESessionNotConnected = EWSPCLRetCodeBase + 3,
			ENotSupported        = EWSPCLRetCodeBase + 4,
			EInvalidState        = EWSPCLRetCodeBase + 5,
			ESessionClosed       = EWSPCLRetCodeBase + 6,
			EMRUExceeded		 = EWSPCLRetCodeBase + 7,	
			EInvalidBufferSize   = EWSPCLRetCodeBase + 8,
			EDataNotAvailable    = EWSPCLRetCodeBase + 9,
			EErrorTimeout        = EWSPCLRetCodeBase + 10
			};
		
		struct T2ByteBufs
			{
			TTransID* iTransactionId;
			TWSPStatus* iWSPStatus;
			};
		
		private:
			TPckgBuf<T2ByteBufs> iIdAndStatusBuf;
	};

class RWTPConn : public RWAPConn
	{
	public:
		enum TReturnCodes
			{
			ENoMemory                 = EWTPRetCodeBase + 0,
			EBadArgument              = EWTPRetCodeBase + 1,
			EProviderProtoErr         = EWTPRetCodeBase + 2,
			EProviderAbortInvalidTID  = EWTPRetCodeBase + 3,
			EProviderAbortNoClass2    = EWTPRetCodeBase + 4,
			EProviderAbortNoSAR       = EWTPRetCodeBase + 5,
			EProviderAbortNoUACK      = EWTPRetCodeBase + 6,
			EProviderAbortVers1       = EWTPRetCodeBase + 7,
			EProviderAbortNoResponse  = EWTPRetCodeBase + 8,
			EProviderAbortMsgTooLarge = EWTPRetCodeBase + 9,
			EProviderAbortGeneral     = EWTPRetCodeBase + 10,
			EShutdownError            = EWTPRetCodeBase + 11
			};

		enum TTransactionClass 
			{
			EClass0 = 0, 
			EClass1 = 1, 
			EClass2 = 2
			};
	
		IMPORT_C TInt Open(RWAPServ& aServer,  // the session with the WAP server thread. 
			const TDesC8& aRemoteHost,  // bearer dependent name or address
			TPort aRemotePort, 
			TPort aLocalPort, 
			TBearer aBearer, // an enum
			TBool aSecureConn,
			TTransactionClass aClass, 
			TBool aAck);
		// Creates a new fully specified transaction.

		IMPORT_C TInt Open(RWAPServ& aServer, TPort aLocalPort);
		// Creates a bound transaction. Intended to be used with Accept.

		typedef TUint8 TReason;

		IMPORT_C TInt Abort(TReason aReason);
		// Aborts the transaction.
		
		IMPORT_C void Accept(class RWTPConn& aBlankConn,
			TTransactionClass& aClass, 
			TBool& aAck, // is WTP user acknowledgement is used?
			TRequestStatus& aStatus);
		// Accepts a new transaction from a bound connection.
		
		IMPORT_C void CancelAccept();
		// Cancels the asynchronous Accept operation.
		
		IMPORT_C TInt Accept(class RWTPConn& aBlankConn,
			TTransactionClass& aClass, 
			TBool& aAck); // is WTP user acknowledgement is used?

		IMPORT_C TInt AckInvoke();
		// Send an ack requested by the initiator from the WTP responder.
		
		IMPORT_C TInt AckResult();
		// Send an ack requested by the responder from the WTP initiator.
		
		enum TTPItemType
			{
			EError = 0x00,
			EInfo = 0x01,
			EOption = 0x02,
			EPSN = 0x03
			};
		
		IMPORT_C TInt AddTPItem(const TDesC8& aTPItemData, TTPItemType aType);
		// Add transport protocol item to be transferred with the last ack.
		// May be called repeatedly to add more items.
		
		IMPORT_C TInt GetLastError() const;
		// Returns the last error.
		
		enum TSelector
			{
			EWaitTimer =      0,
			ERetransmissionTimer =       1,
			EAckTimer =       2,
			EUAckTimer =      3,
			EMaxRetransmissionCounter =  4,
			EMaxAckCounter =  5
			};
		
		IMPORT_C TInt Ioctl(TSelector aSelector, TUint aValue);
		// Sets the operating parameters of a transaction.
		
		IMPORT_C void Read(TDes8& aBuffer, TRequestStatus& aStatus);
		IMPORT_C TInt Read(TDes8& aBuffer);
		// Reads a buffer from a bound connection.
		
		IMPORT_C void CancelRead();
		// Cancel the asynchronous Read operation.
		
		IMPORT_C TInt Write(const TDesC8& aBuffer);
		// Writes a buffer. This is used to send Invoke Req amongst others.
	};

class RWDPConn : public RWAPConn
	{
	public:
		enum TReturnCodes 
			{
			EInvalidParameter = EWDPRetCodeBase + 0
			};

		IMPORT_C TInt Open(RWAPServ& aServer,  
			const TDesC8& aRemoteHost,  
			TPort aRemotePort, 
			TPort aLocalPort, 
			TBearer aBearer, // an enum
			TBool aSecureConn);
		// Creates a fully specified RWDPConn object.

		IMPORT_C TInt Open(RWAPServ& aServer, TPort aLocalPort);
		// Creates a not fully pecified RWDPConn object. 

		IMPORT_C void Recv(TDes8& aRemoteAddress,
			TPckg<TPort>& aRemotePort,
			TDes8& aBuffer,
			TRequestStatus& aStatus);
		// Receives a buffer.
		
		IMPORT_C void CancelRecv();
		// Cancel the asynchronous RecvFrom operation.
		
		IMPORT_C TInt Send(const TDesC8& aBuffer);
		// Sends a buffer to a destination.
		// Assumes a fully defined endpoint.

		IMPORT_C TInt SendTo(const TDesC8& aRemoteAddress,
			TPort aRemotePort,
			const TDesC8& aBuffer,
			TBearer aBearer);

		IMPORT_C void RWDPConn::RecvSize(
			TPckg<TUint16>& aDataSize,	
			TRequestStatus& aStatus);
		// Waits until a datagram is received and returns the size
		// The data can be retrieved with Recv().
	};

#endif

