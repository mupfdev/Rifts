// OBEX.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__OBEX_INL__)
#define __OBEX_INL__

// CObexBaseObject
inline void CObexBaseObject::SetHeaderMask(const TObexHeaderMask aHeaderMask)
/**
	Sets the header mask. aHeaderMask is built up by bit-wise ‘or’ing any of 
	the KObexHeader... constants.
	For example, if it is set to KObexHeaderName | KObexHeaderLength, only 
	these two headers will be specified in transfer operations with the remote 
	machine, even if there are other valid attributes which could be used. In 
	effect, this mask is bit-wise ‘and’ed with the "valid headers" mask when 
	determining which headers are valid for the purposes of transfers.
**/
	{iHeaderMask=aHeaderMask;}


inline TInt CObexBaseObject::BytesSent()
/**
	Returns the number of bytes of the body of the object transferred so far 
	while sending this object.
**/
	{return(iSendBytes);}

inline TInt CObexBaseObject::BytesReceived()
/**
	Returns the number of bytes of the body of the object transferred while 
	receiving an object.
**/
	{return(iRecvBytes);}

inline TObexHeaderMask CObexBaseObject::HeaderMask()
/**
	Returns the currently set header mask. This defaults to 0xFF (i.e. allow 
	everything) when Reset () or InitFromFileL is called. This does not specify 
	which headers currently contain valid data – merely which headers will be 
	transferred if they do contain valid data.
**/
	{return iHeaderMask;}

inline TObexHeaderMask CObexBaseObject::ValidHeaders()
/**
 	Returns the current valid header mask. This allows inspection of the current
 	set of valid headers, particularly useful for determining whether a put
 	object contained a body header (important for deleting files as part of file
 	transfer).
**/
	{return iValidHeaders;}

// TObexConnectInfo
inline TObexConnectInfo::TObexConnectInfo() 
	{iVersion = KObexVersion; iFlags = 0;}

inline TUint8 TObexConnectInfo::VersionMajor() const 
	{ return(STATIC_CAST(TUint8,(iVersion & 0xF0) >> 4));}

inline TUint8 TObexConnectInfo::VersionMinor() const 
	{ return(STATIC_CAST(TUint8,(iVersion & 0x0F)));}

inline CObex::TSetPathInfo::TSetPathInfo() 
	{iFlags = 0; iConstants = 0; iNamePresent = EFalse;}

inline TBool CObex::TSetPathInfo::Parent() const 
	{ return(iFlags & KObexSetPathParent);}

// CObex
inline TBool CObex::IsConnected() const 
/**
	Returns @c ETrue if this CObex is connected at an OBEX level, merely having
	a transport connected does not satisfy this condition. I.e. the two devices
	must have completed the OBEX connection request/response . All other states
	return @c EFalse. This will be unreliable if either the server blindly 
	returns the client’s who header (always reporting ETrue), or if neither
	supply "who" headers (always reporting EFalse).
**/
	{return(ConnectState() == EConnObex);}

inline TBool CObex::IsStrictPeer() const 
/**	
	Returns true if the "who" header specified in the server’s connect response 
	matched that of the client’s connect request, and both had a length greater 
	than 0 (i.e. both specified a "who" field). Undefined if @c IsConnected() 
	== @c EFalse. 
**/
	{return((iLocalInfo.iWho.Length()>0) && (iLocalInfo.iWho==iRemoteInfo.iWho));}

inline const TObexConnectInfo& CObex::LocalInfo() const 
/**
	Use this member to gain access to (and alter, if necessary) the 
	CObex::TConnectInfo structure which will be sent to the OBEX peer as part 
	of the connection process. Only alter the contents of this having read and 
	understood the purpose of the fields, as defined in the OBEX spec. Altering 
	this structure after a connection has been made will have no effect on the
	current session, but will be used for future connection attempts.
**/
	{return(iLocalInfo);}


inline const TObexConnectInfo& CObex::RemoteInfo() const 
/**
	Use this member to read the details of the remote machine’s connection 
	information, as specified by it in during OBEX connection. This data can 
	not be altered, as this serves no purpose.
	The content of this structure is undefined when @c IsConnected () == @c 
	EFalse. 
**/
	{return(iRemoteInfo);}

inline CObex::TConnectState CObex::ConnectState() const 
	{return (iConnectState);};

// CObexServer
inline TBool CObexServer::IsStarted() 
/**
	@retval ETrue	server has had a Start issued, and as is available to 
					accept connections
	@retval EFalse	otherwise
**/
	{return iEnabled;}

inline CObex::TOperation CObexServer::CurrentOperation() const 
/**
	Returns the operation currently being performed by the remote client, or 
	EOpIdle if between operations. Note that there is no implication of whether 
	the server is currently connected; EOpIdle will be returned regardless of 
	connection state, if no operation is currently being performed. Use 
	CObex::IsConnected () to find connection staus.
**/
	{ return (iCurrentOperation);};

#endif
