// IN_SOCK.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__IN_SOCK_H__)
#define __IN_SOCK_H__

#if !defined(__ES_SOCK_H__)
#include <es_sock.h>
#endif

// Address family ID
const TUint KAfInet				= 0x0800;

// IP Protocol IDs
const TUint KProtocolInetIcmp	= 1;
const TUint KProtocolInetTcp	= 6;
const TUint KProtocolInetUdp	= 17;
const TUint KProtocolInetIp		= 0x100;	// Psuedo protocol

// Socket option/ioctl levels
const TUint KSolInetIcmp		= 0x101;
const TUint KSolInetTcp			= 0x106;
const TUint KSolInetUdp			= 0x111;
const TUint KSolInetIp			= 0x100;
const TUint KSolInetIfCtrl		= 0x201;
const TUint KSolInetRtCtrl		= 0x202;
const TUint KSolInetDnsCtrl		= 0x204;
// Security specific
const TUint KSolInetSSL			= 0x205;  // SSL setopts/ioctls

// Maximum IPv4 address
const TInt KInetAddrMaxBits         = 32;
const TInt KMaxIP4DesSize			= 15;

// Port constants
const TUint KInetPortAny			= 0x0000;
const TUint KInetPortNone			= 0x0000;
const TUint KInetMinAutoPort		= 1024;
const TUint KInetMaxAutoPort		= 5000;

// Address constants and utilities
#define INET_ADDR(a,b,c,d) (TUint32)(((a)<<24)|((b)<<16)|((c)<<8)|(d))

const TUint32 KInetAddrAny				= INET_ADDR(0,0,0,0);
const TUint32 KInetAddrNone				= INET_ADDR(0,0,0,0);
const TUint32 KInetAddrAll				= INET_ADDR(255,255,255,255);
const TUint32 KInetAddrBroadcast		= INET_ADDR(255,255,255,255);
const TUint32 KInetAddrLoop				= INET_ADDR(127,0,0,1);

const TUint32 KInetAddrGroupUnspec		= INET_ADDR(224,0,0,0);
const TUint32 KInetAddrGroupAllHosts	= INET_ADDR(224,0,0,1);

const TUint32 KInetAddrMaskAll			= INET_ADDR(0,0,0,0);
const TUint32 KInetAddrMaskHost			= INET_ADDR(255,255,255,255);

const TUint32 KInetAddrNetMaskA			= INET_ADDR(255,0,0,0);
const TUint32 KInetAddrHostMaskA		= ~KInetAddrNetMaskA;
const TInt KInetAddrShiftA				= 24;
const TUint32 KInetAddrNetMaskB 		= INET_ADDR(255,255,0,0);
const TUint32 KInetAddrHostMaskB		= ~KInetAddrNetMaskB;
const TInt KInetAddrShiftB				= 16;
const TUint32 KInetAddrNetMaskC 		= INET_ADDR(255,255,255,0);
const TUint32 KInetAddrHostMaskC		= ~KInetAddrNetMaskC;
const TInt KInetAddrShiftC				= 8;

const TUint32 KInetAddrIdMaskA			= 0x80000000;
const TUint32 KInetAddrIdValA			= 0x00000000;
const TUint32 KInetAddrIdMaskB			= 0xc0000000;
const TUint32 KInetAddrIdValB			= 0x80000000;
const TUint32 KInetAddrIdMaskC			= 0xe0000000;
const TUint32 KInetAddrIdValC			= 0xc0000000;
const TUint32 KInetAddrIdMaskD			= 0xf0000000;
const TUint32 KInetAddrIdValD			= 0xe0000000;
const TUint32 KInetAddrIdMaskE			= 0xf8000000;
const TUint32 KInetAddrIdValE			= 0xf0000000;

enum TInetAddrClass
	{
	EInetClassUnknown = 0,
	EInetClassA,
	EInetClassB,
	EInetClassC,
	EInetClassD,
	EInetClassE,
	EInetMulticast = EInetClassD,
	EInetExperimental = EInetClassE
	};

struct SInetAddr
	{ TUint32 iAddr; };

class TInetAddr : public TSockAddr
	{
public:
	IMPORT_C TInetAddr();
	IMPORT_C TInetAddr(const TSockAddr& anAddr);
	IMPORT_C TInetAddr(TUint aPort);
	IMPORT_C TInetAddr(TUint32 anAddr, TUint aPort);
	//
	IMPORT_C void SetAddress(TUint32 anAddr);
	IMPORT_C TUint32 Address() const;
	//
	IMPORT_C TBool CmpAddr(const TInetAddr& anAddr) const;
	IMPORT_C TBool Match(const TInetAddr& aHost) const;
	IMPORT_C TBool Match(const TInetAddr& aNet, const TInetAddr& aMask) const;
	//
	IMPORT_C void Output(TDes &aBuf) const;
    IMPORT_C TInt Input(const TDesC &aBuf);	// Accepts a, a.b, a.b.c, a.b.c.d or 0xaabbccdd
	//
	IMPORT_C void NetMask(const TInetAddr& aAddr);
	IMPORT_C void Net(const TInetAddr& aAddr);
	IMPORT_C void NetBroadcast(const TInetAddr& aAddr);
	IMPORT_C void SubNet(const TInetAddr& aAddr, const TInetAddr& aMask);
	IMPORT_C void SubNetBroadcast(const TInetAddr& aAddr, const TInetAddr& aMask);
	//
	inline TBool IsClassA();
	inline TBool IsClassB();
	inline TBool IsClassC();
	inline TBool IsMulticast();
	inline TBool IsBroadcast();	// == 255.255.255.255
	inline TBool IsWildAddr();	// == 0.0.0.0
	inline TBool IsWildPort();	// == 0
	//
	inline static TInetAddr& Cast(const TSockAddr& anAddr);
	inline static TInetAddr& Cast(const TSockAddr* anAddr);
protected:
	inline SInetAddr *AddrPtr() const;
	inline static TInt AddrLen();
	};

// Send/Recv Flags (Datagram sockets only)
const TUint KIpDontFragment		= 0x010000;
const TUint KIpHeaderIncluded	= 0x020000;
const TUint KIpDontRoute		= 0x040000;

// Structure returned by KSoInetLastError/KIoctlInetLastError
class TSoInetLastErr
	{
public:
	TInt iStatus;			// ESock error code
	TInt iErrType;			// ICMP type
	TInt iErrCode;			// ICMP code
	TInetAddr iSrcAddr;		// Src of failed datagram
	TInetAddr iDstAddr;		// Dst of failed datagram
	TInetAddr iErrAddr;		// Addr of host that generated the error
	};

// Enumerating & Configuring Interfaces TPckgBuf<TSoInetInterfaceInfo>
// With a level of KSolInetIfCtrl
const TInt KSoInetEnumInterfaces = 0x211;
const TInt KSoInetNextInterface = 0x212;
const TInt KSoInetConfigInterface = 0x213;

enum TIfStatus
	{
	EIfPending,
	EIfUp,
	EIfBusy,
	EIfDown,
	};

class TSoInetInterfaceInfo
	{
public:
	TName iTag;				// Interface tag
	TName iName;			// Interface name
	TIfStatus iState;		// State
	TInt iMtu;				// max transmition size
	TInt iSpeedMetric;		// Metric - bigger is better
	TUint iFeatures;		// Feature flags
	TSockAddr iHwAddr;		// Hardware address (*)
	TInetAddr iAddress;		// Interface IP Address (*)
	TInetAddr iNetMask;		// IP netmask
	TInetAddr iBrdAddr;		// IP broadcast address
	TInetAddr iDefGate;		// IP default gateway or peer address (if known)
	TInetAddr iNameSer1;	// IP Primary name server (if any)
	TInetAddr iNameSer2;	// IP Secondary name server (if any)
	};

// Enumerating & Configuring Routes TPckgBuf<TSoInetRouteInfo>
// With a level of KSolInetRtCtrl
const TInt KSoInetEnumRoutes = 0x221;
const TInt KSoInetNextRoute = 0x222;
const TInt KSoInetAddRoute = 0x223;
const TInt KSoInetDeleteRoute = 0x224;
const TInt KSoInetChangeRoute = 0x225;

enum TRouteState
	{
	ERtNone,
	ERtPending,		// Interface has been started as a dialup, but no info available
	ERtBusy,		// Interface is up but flowed off
	ERtReady,		// Interface is up and ready
	ERtDown		    // Route is down and most likely to stay that way
	};

enum TRouteType
	{
	ERtNormal,		// Created when interface was started
	ERtUser,		// Created by user - ie via SetOpt()
	ERtIcmpAdd,		// Added by ICMP redirect
	ERtIcmpDel		// Replaced by an ICMP redirect
	};

class TSoInetRouteInfo
	{
public:
	TRouteType iType;		// Type of route (normal/icmp generated etc)
	TRouteState iState;		// State of route
	TInt iMetric;			// Smaller is better (less hops and/or faster link)
	TInetAddr iIfAddr;		// IP address of interface used for this route
	TInetAddr iGateway;		// IP address of gateway (might be the interface)
	TInetAddr iDstAddr;		// Destination network or host
	TInetAddr iNetMask;		// Destination mask of network (or host if KInetMaskHost)
	};

// Access to route cache TPckgBuf<TSoInetCachedRouteInfo>, set iDstAddr for required address
// With a level of KSolInetRtCtrl
const TInt KSoInetCachedRouteByDest = 0x225;

class TSoInetCachedRouteInfo : public TSoInetRouteInfo
	{
public:
	TInt iPathMtu;			// Set if used by DF datagram (incl TCP SYN), else 0
	TUint iPathRtt;			// Set if used by TCP, else 0
	};

// Flags returned from DNS records
enum TNameRecordFlags
	{
	EDnsAlias=0x00000001,		// Name is an Alias
	EDnsAuthoritive=0x00000002, // Answer is authoritive 
	EDnsHostsFile=0x00000004,   // Answer is from hosts file
	EDnsServer=0x00000008,      // Answer is from a DNS server
	EDnsHostName=0x00000010,    // Answer is host name for this host
	EDnsCache=0x00000020		// Answer is from the resolver cache
	};
const TUint KSoDnsCacheEnable = 0x600; // Get/Set
const TUint KSoDnsCacheFlush = 0x601; //Set

// TCP specific options and ioctls with a level of KSolInetTcp
// Ioclt
const TUint KIoctlTcpNotifyDataSent = 0x300;
// Options
const TUint KSoTcpSendWinSize = 0x301; // Get/Set before connect
const TUint KSoTcpRecvWinSize = 0x302; // Get/Set before connect
const TUint KSoTcpMaxSegSize = 0x303; // Get/Set before connect
const TUint KSoTcpNoDelay = 0x304; // Get/Set
const TUint KSoTcpKeepAlive = 0x305; // Get/Set
const TUint KSoTcpAsync2MslWait = 0x306; // Get/Set
const TUint KSoTcpSendBytesPending = 0x307; //Get
const TUint KSoTcpReadBytesPending = 0x308; //Get
const TUint KSoTcpListening = 0x309; //Get
const TUint KSoTcpNumSockets = 0x310; //Get
const TUint KSoTcpReadUrgentData = 0x311; //Get
const TUint KSoTcpPeekUrgentData = 0x312; //Get
const TUint KSoTcpRcvAtMark = 0x313; //Get
const TUint KSoTcpNextSendUrgentData = 0x314; //Get/Set
const TUint KSoTcpOobInline = 0x315; //Set
const TUint KSOTcpDebugMode = 0x11110000;
// SECURITY SPECIFIC STUFF
// At level KSolInetSSL
const TUint KSoSecureSocket = 0x400;          // set/clear secure socket
const TUint KSoSSLUnloadTimeout = 0x401;      // set/get SSL dll unload timeout
const TUint KSoCurrentCipherSuite = 0x402;    // set/get current cipher suite
const TUint KSoSSLServerCert = 0x403;	      // get current server cert
const TUint KSoDialogMode = 0x404;            // set/get current dialog mode
const TUint KSoAvailableCipherSuites = 0x405; // set/get supported cipher suites
const TUint KSoUseSSLv2Handshake = 0x406;	  // set/clear SSLv2 handshake convertion

// For KSoTcpSecureSocket
const TUint KSSLClearSecureStatus = 0x00; // disconnect SSL session
const TUint KSSLSetSecureStatus = 0x01;   // complete connect on SSL connect

// For KSoDialogMode
const TUint KSSLDialogUnattendedMode = 0x00; // dialogs
const TUint KSSLDialogAttendedMode = 0x01;   // no dialogs

// Generic with a level of KSolInetIp
const TUint KSoIpOptions = 0x401; // Set/Get
const TUint KSoRawMode = 0x402; // Set/Get
const TUint KSoHeaderIncluded = 0x403; // Set/Get
const TUint KSoIpTOS = 0x404; // Set/Get
const TUint KSoIpTTL = 0x405; // Set/Get
const TUint KSoReuseAddr = 0x406; //Set/Get
const TUint KSoNoInterfaceError = 0x407; //Set/Get
const TUint KSoInetLastError = 0x200; // Get Last ICMP error TPckgBuf<TSoInetLastErr>
const TUint KIoctlInetLastError = 0x200; // Exactly the same a the GetOpt

// UDP specific with a level of KSolInetUdp
const TUint KSoUdpReceiveICMPError = 0x500; //Set/Get

// Extended error codes
const TInt KErrNetUnreach = -190;
const TInt KErrHostUnreach = -191;
const TInt KErrNoProtocolOpt = -192;
const TInt KErrUrgentData = -193;

#include <in_sock.inl>

#endif
