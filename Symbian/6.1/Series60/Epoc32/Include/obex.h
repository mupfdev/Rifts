// OBEX.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__OBEX_H__)
#define __OBEX_H__

#include <e32std.h>
#include <f32file.h>
#include <es_sock.h>
#include <ir_sock.h>
#include <bt_sock.h>
#include <utf.h>
#include <e32des8.h>
#include <e32des16.h>

//common to request & resp digests
const TInt KChallResponseSize = 58;
const TInt KMinChallResponseSize = 18; //Nonce(16) + tag(1) + size(1)
const TInt KObexNonceSize = 16;
const TUint8 KObexRequireUID = 0x01;
//request or chall
const TUint KObexChallNonceTag = 0;
const TUint8 KObexChallOptionsTag = 0x01;
const TUint8 KObexChallRealmTag = 0x02;
const TInt KObexChallOptionSize = 1; //this can't be changed from one without making
const TUint KObexChallHeaderSize = 23; //assuming no Realm data
//response
const TUint KObexRespTag = 0;
const TInt KObexRespSize = 16;
const TUint8 KObexRespUserIDTag = 0x01;
const TUint8 KObexRespNonceTag = 0x02;

#ifdef _UNICODE
const TInt KUidOBEXTransportModule = 0x10003d56;
#else
const TInt KUidOBEXTransportModule = 0x1000169c;
#endif

const TUint8 KObexConnectionIDLength = 4;

typedef TUint16 TObexHeaderMask;
const TUint8 KObexHdrName			= 0x01;
const TUint8 KObexHdrType			= 0x02;
const TUint8 KObexHdrLength			= 0x04;
const TUint8 KObexHdrTime			= 0x08;
const TUint8 KObexHdrDescription	= 0x10;
const TUint8 KObexHdrTarget			= 0x20;
const TUint8 KObexHdrConnectionID	= 0x40;
const TUint8 KObexHdrBody			= 0x80;
const TUint16 KObexHdrEndOfBody		= 0x0100;

const TUint8 KObexVersion           = 0x10;		///< Version 1.0 (still correct for Obex spec v 1.2)

const TUint8 KObexObjectFieldSize   = 127;
const TUint8 KObexObjectDescriptionSize = 255;

//Extended Errors for IrObex
const TInt KErrIrObexClientNoDevicesFound = -5501;
const TInt KErrIrObexClientPeerDoesNotHaveObex = -5502;
const TInt KErrIrObexClientPutPeerAborted = -5503;
const TInt KErrIrObexServerPutPeerAborted = -5507;
const TInt KErrIrObexConnectChallRejected = -5512; 
// Flags used by Connect
// ...None in OBEX 1.0

// Flags used by SetPath
const TUint8 KObexSetPathParent	= 0x01;

typedef TUint8 TObexOpcode;
typedef TBuf8<KObexConnectionIDLength> TConnId;
typedef TBuf8<16> TNonce;
typedef TBuf8<16> TRequestDigest;

class TObexPacket;



/**
	@class CObexBaseObject
	Objects of this class are used to describe the objects to be transferred. 
	Consists of a number of attributes describing the object, along with 
	methods to set them. CObexBaseObject is an abstract base class, which defines 
	attribute setting and transferring functionality, but does not specify the 
	storage mechanism for the data part (called the object body) of the object. 
	This body part is defined in derived classes.

	Object description attributes are tracked for validity automatically, so 
	that only valid attributes are sent to the remote machine. Also has the 
	concept of "header masks". This selects which of the various attributes 
	will actually be sent out/read in when the object is used in an operation 
	with the remote machine. Objects default to transferring all valid 
	attributes, use the header mask if restriction is required on the headers 
	exchanged.

	See the various derived classes for description of object body 
	representation.

	The common attributes are defined to be as close to the underlying OBEX 
	headers as usefully possible, hence any OBEX header specified as a Unicode 
	string (e.g. Name) translate to TDes (variant) EPOC descriptors, "byte 
	sequences" (e.g. Type) are TDes8 (or ASCII invariant), and byte and 32 bit 
	integers (e.g. Length) are TUint32s.

	@par  Deriving Classes from CObexBaseObject
	This class is not designed for user derivation.
**/
class CObexBaseObject : public CBase
	{
friend class CObexClient;
friend class CObexServer; 
public:
	virtual ~CObexBaseObject();
	inline void SetHeaderMask(const TObexHeaderMask aHeaderMask);
	IMPORT_C void SetNameL(const TDesC& aDesc);
	IMPORT_C void SetTypeL(const TDesC8& aDesc);
	IMPORT_C void SetLengthL(const TUint32 aLength);
	IMPORT_C void SetTimeL(const TTime aTime);
	IMPORT_C void SetDescriptionL(const TDesC& aDesc);
	IMPORT_C void SetTargetL(const TDesC8& aDesc);
	inline TInt BytesSent();
	inline TInt BytesReceived();
	inline TObexHeaderMask HeaderMask();
		inline TObexHeaderMask ValidHeaders();
	IMPORT_C const TDesC& Name();
	IMPORT_C const TDesC8& Type();
	IMPORT_C const TUint32 Length();
	IMPORT_C const TTime Time();
	IMPORT_C const TDesC& Description();
	IMPORT_C const TDesC8& Target();
	IMPORT_C void Reset();
protected:
	CObexBaseObject();
	void GuessTypeFromExtL(const TDesC& aExt);
	void ResetHeaders();
	// Pure virtuals that all derived objects must implement
	virtual void GetData(TInt aPos, TDes8& aDes) =0;
	virtual void NewData(TInt aPos, TDes8& aDes) =0;
	virtual TInt DataSize() =0;
	virtual void ResetData() =0;
private:
	enum TProgress { EContinue,EComplete,EError };
	TInt InitSend(TObexOpcode aOpcode);
	TProgress PrepareNextSendPacket(TObexPacket& aPacket);
	TInt InitReceive();
	TProgress ParseNextReceivePacket(TObexPacket& aPacket);
	void PrepareConnectionHeader( TObexPacket& aPacket );
	void SetConnectionIdL(const TDesC8& aDesc);
	TDesC8& ConnectionID();
// Data
protected:
	TObexHeaderMask iHeaderMask;
	TObexHeaderMask iValidHeaders;
	HBufC* iName;	
	HBufC8* iType;
	TInt iLength;
	TTime iTime;
	HBufC* iDescription;
	HBufC8* iTarget;
	HBufC8* iConnectionID; 
private:
	// Members used while transfering the object
	TProgress iSendProgress;
	TObexOpcode iSendOpcode;
	TObexHeaderMask iSendHeaders;
	TInt iSendBytes;
	TProgress iRecvProgress;
	TInt iRecvBytes;
	};

/** @class CObexFileObject
	This class is a concrete derivation of the CObexBaseObject class. Use it to 
	store and transfer OBEX objects with the body part stored in an EPOC file. 
	Hence this class is particularly suited to OBEX "file" beaming applications 
	(c.f. arbitrary object beaming), although there is in reality no 
	restriction in what it is used to transfer. Acces to the body is acheived 
	through an additional attribute to the object; the data file. This is the 
	file-system name of the file used to store the body of the object. Note 
	that there is no explicit relation between this and the Name of the object, 
	although it is expected that most applications would attempt to relate the 
	two.
	When ever a valid data file is set (i.e. DataFile().Length > 0), this file 
	is effectively open, hence stopping any other application from opening it 
	with exclusive rights. Therefore, it is recommended that Reset () be called 
	on the object as soon as it is no longer required, and definitely before 
	(conceptually) passing ownership of the data file to any other object or 
	user.
	CObexFileObject is also suited to situations where an object is expected to 
	be received, but no information about the purpose of this object is known. 
	This is due to CObexFileObject’s ability to create temporary files "on the 
	fly" to store received data into, when a specific file is not provided by 
	the application.

	@par  Deriving Classes from CObexFileObject
	This class is not designed for user derivation.
**/

class CObexFileObject : public CObexBaseObject
	{
public:
	static IMPORT_C CObexFileObject* NewL(const TDesC &aDataFile = TPtrC(NULL, 0));
	virtual IMPORT_C ~CObexFileObject();
	IMPORT_C void InitFromFileL(const TDesC& aFile);

	IMPORT_C void HurricaneSetStub(const TDesC& aDesc);
	IMPORT_C const TDesC& HurricaneGetStub();

private:
	void ConstructL(const TDesC &aDataFile);
	void SetDataFileL(const TDesC& aDesc);
	const TDesC& DataFile();
	TBool RenameFile(const TDesC& aDesC);
	void SetTempFilePath(const TDesC& aPath);
	void QueryTempFilePath(TDes& aPath);
	// From CObexBaseObject
	virtual void GetData(TInt aPos, TDes8& aDes);
	virtual void NewData(TInt aPos, TDes8& aDes);
	virtual TInt DataSize();
	virtual void ResetData();
// Data
private:
	RFs iFs;
	TParse iDataFile;
	RFile iFile;
	TBuf<KObexObjectDescriptionSize> iTempFilePath;
	};

/** @class CObexBufObject
	Use this class to hold objects where the body part is stored in a CBufBase
	derived class (e.g. CBufFlat or CBufSeg class). At no point does the
	CObexBufObject create, or take ownership of any CBaseBuf onject it uses - it
	is always the responsibility of the creator/owner of the CBaseBuf to free it
	when no longer required.

	As this class does not take ownership of the buffers it uses, it equally can
	not create its own buffers ad-hoc for storing new data into. Hence at no 
	time is it valid for a CObexBufObject to exist with out it having a valid 
	data buffer set. If such a situation arises, where it is required that 
	received information should be discarded, consider using a CObexNullObject 

	@par  Deriving Classes from CObexBufObject
	This class is not designed for user derivation.
**/
class CObexBufObject : public CObexBaseObject
	{
public:
	static IMPORT_C CObexBufObject* NewL(CBufBase* aDataBuf);
	virtual IMPORT_C ~CObexBufObject();
	IMPORT_C TInt WriteToFile(const TPtrC& aFileName);
	IMPORT_C void SetDataBufL(CBufBase* aDataBuf);
	IMPORT_C void SetDataBufL(const TPtrC& aFilename);
	IMPORT_C void SetDataBufL(const TPtrC& aFilename, CBufBase* aDataBuf);
	CBufBase* DataBuf();
	HBufC* FileName();

	IMPORT_C void HurricaneSetStub(CBufBase* aStub);
	IMPORT_C CBufBase* HurricaneGetStub();

private:
	CObexBufObject();
	void ConstructL(CBufBase* aDataBuf);

	void CopyFileL(const TDesC& aFilename);
	void NewFileData(TInt aPos, TDes8& aDes);
	void GetFileData(TInt aPos, TDes8& aDes);

	// From CObexBaseObject
	virtual void GetData(TInt aPos, TDes8& aDes);
	virtual void NewData(TInt aPos, TDes8& aDes);
	virtual TInt DataSize();
	virtual void ResetData();

	inline void CloseDataFile();
	inline TInt OpenDataFile(const TDesC& aFilename);
	inline void CloseFileServer();
	inline TInt OpenFileServer();
	inline void WriteBufferToFile();

// Data
private:
	CBufBase* iBuf;
	HBufC* iFilename;
	RFs* iFileServ;
	RFile* iFile;
	TInt iBufOffset;
	TInt iBuffered;
	};

/**	@class CObexNullObject
	Concrete OBEX object with NULL data representation. Use when only the 
	headers of an object are required, and the data (if any) can safely be 
	discarded.
**/
class CObexNullObject : public CObexBaseObject
	{
public:
	IMPORT_C static CObexNullObject* NewL ();
private:
	// From CObexBaseObject
	virtual void GetData (TInt aPos, TDes8& aDes);
	virtual void NewData (TInt aPos, TDes8& aDes);
	virtual TInt DataSize ();
	virtual void ResetData ();
	};


/** @class TObexProtocolInfo
	TObexProtocolInfo is derived for each underlying transport protocol OBEX 
	runs over. 

	At this time, IrTinyTP and Rfcomm are supported. Use @c TObexIrProtocolInfo 
	whenever running over TinyTP, and @c TObexBluetoothProtocolInfo when 
	running over Rfcomm.

	The @c iTransport member holds the unique name for the transport, for TinyTP
	this is @p "IrTinyTP", and for Rfcomm, it is @p "RFCOMM". 
**/
class TObexProtocolInfo
	{
public:
	TBuf<60> iTransport;
	};


/** @class TObexIrProtocolInfo
	
	@c iAddr holds IrDA address information about this 
	connection, as used in the IrDA sockets interface. Refer to the SDK for 
	more information about this. It’s main use is for setting the port that the
	local machine will listen on.
	
	@c iClassName and iAttributeName set the IAS class and attribute values 
	that the OBEX session will register its listener port, or request remote 
	port with. To access the default OBEX server, these should be @p "OBEX" and 
	@p "IrDA:TinyTP:LsapSel" respectively. 
**/

class TObexIrProtocolInfo : public TObexProtocolInfo
	{
public:
	TIrdaSockAddr iAddr;
	TBuf8<KIASClassNameMax> iClassName;
	TBuf8<KIASAttributeNameMax> iAttributeName;
	};

class TObexBluetoothProtocolInfo : public TObexProtocolInfo
	{
public:
	TRfcommSockAddr iAddr;
	};

struct TObexConnectionInfo;

/** @class TObexConnectInfo
	This structure contains information used during OBEX connection. iVersion
	holds the encoded OBEX version of the machine, use @c VersionMajor() and
	@c VersionMinor() to extract the parts of the version number (each having a
	value from 0 to 15). @c iFlags holds OBEX connection flags. @c iWho holds 
	the Who attribute from the connect packet, if any was specified, or 
	otherwise has a length of 0. 
	It is recommended that this class is only ever allocated on the heap as it is quite big.
**/
class TObexConnectInfo
	{
public:
	inline TObexConnectInfo();
	inline TUint8 VersionMajor() const;
	inline TUint8 VersionMinor() const;
public:
	TUint8 iVersion; ///< Encoded OBEX version of the machine
	TUint8 iFlags; ///< iFlags holds OBEX connection flags
	TBuf8<KObexObjectDescriptionSize> iWho; ///< the Who attribute from the connect packet, if any was specified
	TBuf8<KObexObjectDescriptionSize> iTargetHeader; ///< the Target header from the connect packet, if any was specified

	};



class MObexNotify
//---------------
// Provides the call back interface for anything using CObexTransport (ie CObex)
	{
public:
	virtual void Process(TObexPacket &aPacket) =0;
	virtual void Error(TInt aError) =0;
	virtual void TransportUp(TObexConnectionInfo& aInfo) =0;			// Call back to start the obex session
	virtual void TransportDown() =0;			//   "   "      stop       "	 "
	};

/** @class MObexAuthChallengeHandler
	This class is the common base class for any object which wishes
	to use the Obex Server or Client. 
	The class which owns a CObexClient or CObexServer must be derived
	from this class and must handle the call from the Server/Client for a request
	for a Password.
**/
class MObexAuthChallengeHandler
	{
public:

	virtual void GetUserPasswordL(const TDesC& aRealm) = 0;
	};


class CObexTransport;
class CObexSocketConnector;
class TObexHeader;
class CObexAuthenticator;

/** @class CObex
	This class is the common base class for CObexClient and CObexServer. It is 
	an abstract class and cannot be instantiated in itself. However, it does 
	contain user functionality common to both client and server connections.

	Provides the basic OBEX transport functionallity (sending and receiving 
	files)
	Client and server provide the more specialied APIs for
		@li initiation or response to puts & gets
		@li (possible) handling of more generalised 'objects' (prob. with data
			buffered through a file).

	@par Deriving classes from CObex
	This class is not designed for user derivation
**/

class CObex : public CBase, protected MObexNotify
//-----------------------------------------------
//
	{
public:
/** @class TSetPathInfo
	Describes the information set of received in a SETPATH command.
**/
	class TSetPathInfo
		{
	public:
		inline TSetPathInfo();
		inline TBool Parent() const;
		TUint8 iFlags;
		TUint8 iConstants;
		TBuf<KObexObjectDescriptionSize> iName;
		TBool iNamePresent;	///< Whether @c iName is present in this SETPATH info
		};
	// Current obex connection state
	enum TConnectState 
		{ 
		EConnIdle,					//nothing is happening
		EConnTransport,				//Transport Link connected not yet established true Link
		EConnObex,					//full connection established
		ESimpleConnRequest,			//Connect without Auth has been sent by ClientReceived by Server
		EConnChallRxed,				// Server has issued a challenge, to a Client cionnect
		ESimpleConnChallIssued,		//Server, received Simple Connect but Server Challenge issued
		EChallConnRequested,		//Connect with Auth has been sent by Client\Received by Server
		EChallConnChallIssued,		//Server has sent a Challenge & Resp to a Client EChallConnRequest
		EWaitForFinalResponse,		//Client, waiting for final success/fail not chall-response expected
									//Server, Waiting for final Resp fromm Client to Challenge
		EFinalResponseReceived,		//Server, the final response has been received
		EFinalChallRxed,			//Server, Client connect with challenge, Server responds with challenge, Client re-issued original/new challenge
		EWaitForUserInput,			//waiting for the user
		EDropLink					//drop the link 
		};
	enum TOperation 
		{ 
		EOpConnect		= 0x00,
		EOpDisconnect	= 0x01,
		EOpPut			= 0x02,
		EOpGet			= 0x03,
		EOpSetPath		= 0x05,
		EOpAbort		= 0xFF,	// - abort must fit in one pkt so final bit is always set
		EOpAbortNoFBit	= 0x7F,
		EOpIdle			= 0xFE	// Not actually an obex operation. 
		};
	virtual ~CObex();
	IMPORT_C void SetCallBack(MObexAuthChallengeHandler& aCallBack);
	inline TBool IsConnected() const;
	inline TBool IsStrictPeer() const;
	inline const TObexConnectInfo& LocalInfo() const;
	IMPORT_C TInt SetLocalWho(const TDesC8& aInfo); 
    inline const TObexConnectInfo& RemoteInfo() const;
	// Implementation of MObexNotify Interface
	virtual void Process(TObexPacket& aPacket);
	virtual void Error(TInt aError) ;
	virtual void TransportUp(TObexConnectionInfo& aInfo);			// Call back to start the obex session
	virtual void TransportDown();			//   "   "      stop       "	 "
	virtual void UserPasswordL( const TDesC& aPassword) = 0; 
	IMPORT_C void RemoteAddr(TSockAddr& anAddr); 
protected:
	CObex();
	virtual void ConstructL(TObexProtocolInfo& aObexProtocolInfoPtr);
	virtual TBool ParseConnectPacket(TObexPacket& aPacket) = 0;	
	void NewConnectorL(TObexProtocolInfo& aObexProtocolInfoPtr);
	void DeleteConnector();
	void NewTransportL(TObexConnectionInfo& aInfo);
	void DeleteTransport();
	void SetConnectState(TConnectState aNewState);
	inline TConnectState ConnectState() const;
	virtual void OnPacketReceive(TObexPacket& aPacket) =0;
	virtual void OnError(TInt aError) =0;
	virtual void OnTransportUp() =0;
	virtual void OnTransportDown() =0;
	void ProcessChallengeL(const TObexHeader& hdr);			//process the received challenge
	void ProcessChallResponseL(const TObexHeader& hdr);		//process the response to challenge
	TInt GenerateChallenge(TObexPacket& aPacket);			//generate a challenge 
	void PrepareChallResponseL(const TDesC& aPassword);			//generate a response a respose to challenge
															//after user Password input

private: 												   
	TConnectState iConnectState;
protected:
	RSocketServ iSocketServ;
	RSocket iSocket;
	CObexSocketConnector* iConnector;
	CObexTransport* iTransport;
	TObexConnectInfo iLocalInfo;
	TObexConnectInfo iRemoteInfo;
	MObexAuthChallengeHandler* iCallBack;
	TNonce iOutgoingNonce; //nonce used when challenging
	TNonce iIncomingNonce; //nonce used when receiving a challenge
	HBufC8* iChallPassword;	//password used when challenging
	HBufC8* iRespPassword;	//password used when responding to a challenge
	HBufC8* iRxChallenge;
	TBuf8<KChallResponseSize> iOutgoingChallResp;//response to the previously issued challenge
								//16 nonce, 16 digest resp, 20 UserID, 3*(tag+size)
	TBuf8<KChallResponseSize> iIncomingChallResp;//response received from previous challenge
	TBuf8<KObexRespSize> iIncomingRequestDigest;
	HBufC* iRemoteUID;	//UID of remote device
	HBufC* iRemoteRealm;//Realm of remote device
	CObexAuthenticator* iAuthEngine;
	TBool iChallenge;	//to challenge or not to challenge?
	TBool iUserIDRequested; //does the challenge insist that a UserID is returned
	TBool iResponseVerified; //keep track if the EAuthResponse header has been received 
								//and has been verified as correct
	};

/** @class CObexClient
	Client side functionality. Connection based.
	Supports ... @li Opening IrDA TTP sockets for the OBEX session.
		@li Opening an OBEX session over a connected socket
		@li Standard OBEX operations. No support for OBEX 'command' (dropped
			from OBEX spec.)

	@par  Deriving Classes from CObexClient
	This class is not designed for user derivation.

*/
class CObexClient : public CObex
	{
public:
	IMPORT_C ~CObexClient();
	IMPORT_C static CObexClient* NewL(TObexProtocolInfo& aObexProtocolInfoPtr);
	IMPORT_C void Connect(TRequestStatus& aStatus);
	IMPORT_C void Connect(CObexBaseObject& aObject, TRequestStatus& aStatus);	
	IMPORT_C void ConnectL(CObexBaseObject& aObject, const TDesC& aPassword, 
													TRequestStatus& aStatus);
	IMPORT_C void ConnectL(const TDesC& aPassword, TRequestStatus& aStatus);
	IMPORT_C void Disconnect(TRequestStatus& aStatus);						
	IMPORT_C void Put(CObexBaseObject& aObject, TRequestStatus& aStatus);
	IMPORT_C void Get(CObexBaseObject& aObject, TRequestStatus& aStatus);		
	IMPORT_C void SetPath(TSetPathInfo& aPathInfo, TRequestStatus& aStatus);
	IMPORT_C void Abort();					
	IMPORT_C void UserPasswordL( const TDesC& aPassword); 
	
private:
	CObexClient();
	void ConstructL(TObexProtocolInfo& aObexProtocolInfoPtr);
	TBool AlreadyActive(TRequestStatus& aStatus);
	void ClientCommandL(TOperation aOp, TAny* aParam, TRequestStatus& aStatus);
	// Implementation of CObex Events
	virtual void OnPacketReceive(TObexPacket& aPacket);
	virtual void OnError(TInt aError);
	virtual void OnTransportUp();
	virtual void OnTransportDown();
	void SetRequest(TRequestStatus& aStatus, TOperation aOperation);
	void CompleteRequest(const TInt aCompletion);
	TInt PrepareConnectPacket(TObexPacket& aPacket);	// Should be members of TConnectInfo
	TBool ParseConnectPacket(TObexPacket& aPacket);	
private: 
	TRequestStatus* iPendingRequest;
	TOperation iCurrentOperation;
	CObexBaseObject* iCurrentObject;
	TBuf8<KObexObjectFieldSize> iConnectionID; 
	};

class MObexServerNotify;

/** @class CObexServer
	CObexServer provides the framework for servicing requests from remote 
	clients. It is designed to be able to act as either a "default" application 
	(in IrDA terms, registering on the IrDA:OBEX IAS class), or as a 
	application specific server (registering itself on a private IAS class). 
	All behaviour is defined by the user of the CObexServer (the EPOC side 
	client of the server, as it were), and implemented through a mixin.
	In order to implement the desired functionality, a class should be defined,
	derived from MObexServerNotify, and passed as a parameter into the
	CObexServer. The functions within this mixin will be called to notify of
	server events, on which specific implementations can act (or ignore) as
	appropriate.

	@par  Deriving Classes from CObexServer
	This class is not designed for user derivation.

**/
class CObexServer : public CObex
	{
public:
	IMPORT_C static CObexServer* NewL(TObexProtocolInfo& aObexProtocolInfoPtr);
	IMPORT_C ~CObexServer();
	IMPORT_C TInt Start(MObexServerNotify* aOwner);
	IMPORT_C void Stop();
	inline TBool IsStarted();
	inline TOperation CurrentOperation() const;
	IMPORT_C void SetChallengeL(const TDesC& aPassword);
	IMPORT_C void ResetChallenge();
	IMPORT_C void UserPasswordL( const TDesC& aPassword); 

private:
	CObexServer();
	void ConstructL(TObexProtocolInfo& aObexProtocolInfoPtr);
	TInt AcceptConnection();
	// Implementation of CObex Events
	virtual void OnPacketReceive(TObexPacket& aPacket);
	virtual void OnError(TInt aError);
	virtual void OnTransportUp();
	virtual void OnTransportDown();
	TInt PrepareConnectPacket(TObexPacket& aPacket);	
	TBool ParseConnectPacket(TObexPacket& aPacket);	
	TInt AddConnectionIDHeader(TObexPacket& aPacket);
	TInt PrepareFinalChallResponse(TObexPacket& aPacket, TConnectState& aNextState);
	TBool CheckForConnectionID(CObexBaseObject& aObject);
private:
	MObexServerNotify* iOwner;
	TBool iEnabled;
	TOperation iCurrentOperation;
	CObexBaseObject* iTransObject;
	CObexBaseObject* iSpecObject;
	TBool iSpecDone;
	TBool iTargetReceived;
	TConnId iConnectionID;	
	};

/** @class MObexServerNotify
	This class is used by CObexServer to provide indication of asynchornous
	events occuring within the server. Any service whiching to provide
	OBEX server functionality should implement a class derived from this
	interface.

	@par  Deriving Classes from MObexServerNotify
	Derive a class from this mixin to provide a CObexServer notification
	implementation. The CObexServer object handles the protocol side of an OBEX
	server session, this class provides the server policy for a particular
	session. 
**/
class MObexServerNotify
	{
friend class CObexServer;

private:
	// Function dox in obex.cpp
	virtual void ErrorIndication(TInt aError) =0;
	virtual void TransportUpIndication() =0;
	virtual void TransportDownIndication() =0;
	virtual TInt ObexConnectIndication(const TObexConnectInfo& aRemoteInfo, const TDesC8& aInfo) =0;
	virtual void ObexDisconnectIndication(const TDesC8& aInfo) =0;
	virtual CObexBufObject* PutRequestIndication() =0;
	virtual TInt PutPacketIndication() =0;
	virtual TInt PutCompleteIndication() =0;
	virtual CObexBufObject* GetRequestIndication(CObexBaseObject *aRequiredObject) =0;
	virtual TInt GetPacketIndication() =0;
	virtual TInt GetCompleteIndication() =0;
	virtual TInt SetPathIndication(const CObex::TSetPathInfo& aPathInfo, const TDesC8& aInfo) =0;
	virtual void AbortIndication() =0;
	};





enum TObexResponse  
	{ 
	ERespContinue			= 0x10,
	ERespSuccess			= 0x20,
	ERespCreated			= 0x21,
	ERespAccepted			= 0x22,
	ERespBadRequest			= 0x40,
	ERespUnauthorized		= 0x41,
	ERespPaymentRequired	= 0x42,
	ERespForbidden			= 0x43,
	ERespNotFound			= 0x44,
	ERespMethodNotAllowed	= 0x45,
	ERespNotAcceptable		= 0x46,
	ERespTimedOut			= 0x48,
	ERespConflict			= 0x49,
	ERespInternalError		= 0x50,
	ERespNotImplemented		= 0x51,
	ERespServiceUnavailable = 0xD3,
	};



#include "obex.inl"

#endif // __OBEX_H__
