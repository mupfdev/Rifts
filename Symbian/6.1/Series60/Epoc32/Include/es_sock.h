// ES_SOCK.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__ES_SOCK_H__)
#define __ES_SOCK_H__

#include <e32base.h>

#undef	_DEBUG_SOCKET_FUNCTIONS
#if (defined(__WINS__) && defined(_DEBUG))
#define	_DEBUG_SOCKET_FUNCTIONS
#endif

#define SOCKET_SERVER_NAME _L("SocketServer")
const TUint KESockDefaultMessageSlots=8;

struct SSockAddr
	{ TUint iFamily; TUint iPort; };

const TUint KMaxSockAddrSize=0x20;

class TSockAddr : public TBuf8<KMaxSockAddrSize>
	{
public:
	IMPORT_C TSockAddr();
	IMPORT_C TSockAddr(TUint aFamily);
	IMPORT_C TUint Family() const;
	IMPORT_C void SetFamily(TUint aFamily);
	IMPORT_C TUint Port() const;
	IMPORT_C void SetPort(TUint aPort);
	IMPORT_C TBool CmpPort(const TSockAddr& anAddr) const;
	IMPORT_C TInt GetUserLen();
protected:
	IMPORT_C void SetUserLen(TInt aLen);
	inline TUint8* UserPtr() const;
private:
	inline SSockAddr* BasePtr() const;
	};

// Address families (based upon protocol IDs used by ARP/REVARP)
const TUint KAFUnspec=0;

// Socket Types
const TUint KSockStream=1;
const TUint KSockDatagram=2;
const TUint KSockSeqPacket=3;
const TUint KSockRaw=4;

// constants for various socket calls - can't be enums cos they're largely defined by protocols
const TInt KSOLSocket=1;
const TInt KLevelUnspecified=0;

// Socket options defined by the server
const TUint KSODebug=1;
const TUint KSORecvBuf=2;
const TUint KSOSendBuf=3;
const TUint KSONonBlockingIO=4;
const TUint KSOBlockingIO=5;
const TUint KSOSelectPoll=6;
const TUint KSOReadBytesPending=7;
const TUint KSOUrgentDataOffset=8;
const TUint KSOSelectLastError=9;

const TInt  KSocketBufSizeUndefined=0;
const TInt  KSocketDefaultBufferSize=4096;
const TUint KSocketInternalOptionBit=0x80000000;	// Must not be set for client requests

// Ioctls
const TUint KInternalIoctlBit=0x80000000;	// Must not be set for client requests
const TUint KIOctlSelect=1;

// Select ioctl states
const TUint KSockSelectRead   =0x00000001;
const TUint KSockSelectWrite  =0x00000002;
const TUint KSockSelectExcept =0x00000004;
//
// Socket write flags
const TUint KSockWriteUrgent=0x00000001;	// AKA Out of band or unit data
const TUint KSocketInternalWriteBit=0x80000000;	// Must not be set for client requests

// Socket read flags
const TUint KSockReadPeek=0x00000001;		// read copy of data - reading again will retrieve same data
const TUint KSocketInternalReadBit=0x80000000;	// Must not be set for client requests

// Types

enum TByteOrder
	{
	EBigEndian,
	ELittleEndian,
	EOtherByteOrder,
	};
//
// Protocol Service info bitmasks
//
const TUint KSIConnectionLess=0x00000001;
const TUint KSIReliable=0x00000002;
const TUint KSIInOrder=0x00000004;
const TUint KSIMessageBased=0x00000008;
const TUint KSIDatagram=KSIMessageBased;
const TUint KSIStreamBased=0x00000010;
const TUint KSIPseudoStream=0x00000020;
const TUint KSIUrgentData=0x00000040;
const TUint KSIConnectData=0x00000080;
const TUint KSIDisconnectData=0x00000100;
const TUint KSIBroadcast=0x00000200;
const TUint KSIMultiPoint=0x00000400;
const TUint KSIQOS=0x00000800;
const TUint KSIWriteOnly=0x00001000;
const TUint KSIReadOnly=0x00002000;
const TUint KSIGracefulClose=0x00004000;
const TUint KSICanReconnect=0x00008000;
const TUint KSIPeekData=0x00010000;

//
// Naming services
//
const TUint KNSNameResolution=0x00000001;
const TUint KNSHeirarchicalNaming=0x00000002;
const TUint KNSRemoteDiscovery=0x00000004;
const TUint KNSServiceResolution=0x00000008;
const TUint KNSNameRegistration=0x00000010;
const TUint KNSServiceRegistration=0x00000020;
const TUint KNSDynamicAddressing=0x00000040;
const TUint KNSInfoDatabase=0x00000080;

// Security Schemes
const TUint KSocketNoSecurity=0x00000000;
const TUint KSecureSockets=0x00000001;

// Special message sizes
const TInt KSocketMessageSizeIsStream=0;
const TInt KSocketMessageSizeUndefined=1;				// Depends on lower layer or is dynamic
const TInt KSocketMessageSizeNoLimit=-1;

//
const TUint KUndefinedSockType=0xFFFFFFFF;
const TUint KUndefinedProtocol=0xFFFFFFFE;

typedef TBuf<0x20> TProtocolName;
typedef TBuf<0x20> TServiceName;
typedef TBuf<0x100> THostName;

struct TProtocolDesc
	{
public:
	TProtocolName iName;
	TUint iAddrFamily;
	TUint iSockType;
	TUint iProtocol;
	TVersion iVersion;
	TByteOrder iByteOrder;
	TUint iServiceInfo;
	TUint iNamingServices;
	TUint iSecurity;
	TInt iMessageSize;
	};

// socket errors
const TInt KErrWouldBlock=-1000;

typedef TPckgBuf<TInt> TSockXfrLength;

// IPC Data holder
class TSockIO
	{
public:
	const TSockXfrLength* iLength;
	TUint iFlags;
	TSockAddr* iAddr;
	};

class TSockIOBufC : public TPckgC<TSockIO>
	{
public:
	inline TSockIOBufC();
	TSockIO iArgs;
	};

// Classes
class RSocket;
class RSocketServ : public RSessionBase
	{
public:
    IMPORT_C RSocketServ();
	IMPORT_C TInt Connect(TUint aMessageSlots=KESockDefaultMessageSlots);
	IMPORT_C TVersion Version() const;
	IMPORT_C TInt NumProtocols(TUint& aCount);
	IMPORT_C TInt GetProtocolInfo(TUint anIndex,TProtocolDesc& aProtocol);
	IMPORT_C TInt FindProtocol(const TProtocolName& aName,TProtocolDesc& aProtocol);
	IMPORT_C void StartProtocol(TUint anAddrFamily,TUint aSockType,TUint aProtocol,TRequestStatus& aStatus);
	IMPORT_C void StopProtocol(TUint anAddrFamily,TUint aSockType,TUint aProtocol,TRequestStatus& aStatus);
	IMPORT_C TInt InstallExtension(const TDesC& aDllName, const TDesC& aArgs=TPtrC());
	IMPORT_C void SetExclusiveMode(TRequestStatus& aStatus);
	IMPORT_C void ClearExclusiveMode();
	IMPORT_C TInt __DbgMarkHeap();
	IMPORT_C TInt __DbgCheckHeap(TInt aCount);
	IMPORT_C TInt __DbgMarkEnd(TInt aCount);
	IMPORT_C TInt __DbgFailNext(TInt aCount);
	IMPORT_C TInt __DbgFailNextMbuf(TInt aCount);
	IMPORT_C TInt __DbgSetMbufPoolLimit(TInt asize);
	IMPORT_C TInt __DbgCheckMbuf(TInt asize);
	IMPORT_C TInt __DbgMbufFreeSpace();
	IMPORT_C TInt __DbgMbufTotalSpace();
	};
//
class RSocket : public RSubSessionBase
	{
friend class RSocketServ;
public:
	enum TShutdown {ENormal,EStopInput,EStopOutput,EImmediate};
public:
	IMPORT_C RSocket();
	IMPORT_C TInt Open(RSocketServ& aServer,TUint addrFamily,TUint sockType,TUint protocol);
	IMPORT_C TInt Open(RSocketServ &aServer,const TDesC& aName);
	IMPORT_C TInt Open(RSocketServ& aServer);
	IMPORT_C void Send(const TDesC8& aDesc,TUint someFlags,TRequestStatus& aStatus);
	IMPORT_C void Send(const TDesC8& aDesc,TUint someFlags,TRequestStatus& aStatus,TSockXfrLength& aLen);
	IMPORT_C void CancelSend();
	IMPORT_C void Recv(TDes8& aDesc,TUint flags,TRequestStatus& aStatus);
	IMPORT_C void Recv(TDes8& aDesc,TUint flags,TRequestStatus& aStatus,TSockXfrLength& aLen);
	IMPORT_C void RecvOneOrMore(TDes8& aDesc,TUint flags,TRequestStatus& aStatus,TSockXfrLength& aLen);
	IMPORT_C void CancelRecv();
	IMPORT_C void Read(TDes8& aDesc,TRequestStatus& aStatus);
	IMPORT_C void CancelRead();
	IMPORT_C void Write(const TDesC8& aDesc,TRequestStatus& aStatus);
	IMPORT_C void CancelWrite();
	IMPORT_C void SendTo(const TDesC8& aDesc,TSockAddr& anAddr,TUint flags,TRequestStatus& aStatus);
	IMPORT_C void SendTo(const TDesC8& aDesc,TSockAddr& anAddr,TUint flags,TRequestStatus& aStatus,TSockXfrLength& aLen);
	IMPORT_C void RecvFrom(TDes8& aDesc,TSockAddr& anAddr,TUint flags,TRequestStatus& aStatus);
	IMPORT_C void RecvFrom(TDes8& aDesc,TSockAddr& anAddr,TUint flags,TRequestStatus& aStatus,TSockXfrLength& aLen);
	IMPORT_C void Connect(TSockAddr& anAddr,TRequestStatus& aStatus);
	IMPORT_C void Connect(TSockAddr& anAddr,const TDesC8& aConnectDataOut,TDes8& aConnectDataIn,TRequestStatus& aStatus);
	IMPORT_C void CancelConnect();
	IMPORT_C TInt Bind(TSockAddr& anAddr);
	IMPORT_C TInt SetLocalPort(TInt aPort);
	IMPORT_C void Accept(RSocket& aBlankSocket,TRequestStatus& aStatus);
	IMPORT_C void Accept(RSocket& aBlankSocket,TDes8& aConnectData,TRequestStatus& aStatus);
	IMPORT_C void CancelAccept();
	IMPORT_C TInt Listen(TUint qSize);
	IMPORT_C TInt Listen(TUint qSize,const TDesC8& aConnectData);
	IMPORT_C TInt SetOpt(TUint anOptionName,TUint anOptionLevel,const TDesC8& anOption=TPtrC8(NULL,0));
	IMPORT_C TInt SetOpt(TUint anOptionName,TUint anOptionLevel,TInt anOption);
	IMPORT_C TInt GetOpt(TUint anOptionName,TUint anOptionLevel,TDes8& anOption);
	IMPORT_C TInt GetOpt(TUint anOptionName,TUint anOptionLevel,TInt &anOption);
	IMPORT_C void Ioctl(TUint aCommand,TRequestStatus& aStatus,TDes8* aDesc=NULL,TUint aLevel=KLevelUnspecified);
	IMPORT_C void CancelIoctl();
	IMPORT_C TInt GetDisconnectData(TDes8& aDesc);
	IMPORT_C void LocalName(TSockAddr& anAddr);
	IMPORT_C TUint LocalPort();
	IMPORT_C void RemoteName(TSockAddr& anAddr);
	IMPORT_C void Close();
	IMPORT_C void Shutdown(TShutdown aHow,TRequestStatus& aStatus);
	IMPORT_C void Shutdown(TShutdown aHow,const TDesC8& aDisconnectDataOut,TDes8& aDisconnectDataIn,TRequestStatus& aStatus);
	IMPORT_C void CancelAll();
	IMPORT_C TInt Info(TProtocolDesc& aProtocol);
	IMPORT_C TInt Name(TName& aName);
	IMPORT_C TInt Transfer(RSocketServ& aServer, const TDesC& aName);
private:
	TSockIOBufC iRecvArgPkg;
	TSockIOBufC iSendArgPkg;
	};

class TNameRecord
	{
public:
	inline TNameRecord();
	enum {EAlias=0x00000001,};
	THostName iName;
	TSockAddr iAddr;
	TInt iFlags;
	};

typedef TPckgBuf<TNameRecord> TNameEntry;

class RHostResolver : public RSubSessionBase
	{
public:
	IMPORT_C TInt Open(RSocketServ& aSocketServer,TUint anAddrFamily,TUint aProtocol);
	IMPORT_C void GetByName(const TDesC& aName,TNameEntry& aResult,TRequestStatus& aStatus);
	IMPORT_C TInt GetByName(const TDesC& aName,TNameEntry& aResult);
	IMPORT_C void Next(TNameEntry& aResult,TRequestStatus& aStatus);
	IMPORT_C TInt Next(TNameEntry& aResult);
	IMPORT_C void GetByAddress(const TSockAddr& anAddr,TNameEntry& aResult,TRequestStatus& aStatus);
	IMPORT_C TInt GetByAddress(const TSockAddr& anAddr,TNameEntry& aResult);
	IMPORT_C TInt GetHostName(TDes& aName);
	IMPORT_C void GetHostName(TDes& aName,TRequestStatus &aStatus);
	IMPORT_C TInt SetHostName(const TDesC& aNeme);
	IMPORT_C void Close();
	IMPORT_C void Cancel();
private:
	};

typedef TPckgBuf<TInt> TPortNum;

class RServiceResolver : public RSubSessionBase
	{
public:
	IMPORT_C TInt Open(RSocketServ& aSocketServer,TUint anAddrFamily,TUint sockType,TUint aProtocol);
	IMPORT_C void GetByName(const TDesC& aName,TPortNum& aPort,TRequestStatus& aStatus);
	IMPORT_C TInt GetByName(const TDesC& aName,TPortNum& aPort);
	IMPORT_C void GetByNumber(const TUint aPort,TDes& aName,TRequestStatus& aStatus);
	IMPORT_C TInt GetByNumber(const TUint aPort,TDes& aName);
	IMPORT_C void RegisterService(const TDesC& aName,const TUint& aPort,TRequestStatus& aStatus);
	IMPORT_C TInt RegisterService(const TDesC& aName,const TUint& aPort);
	IMPORT_C void RemoveService(const TDesC& aName,const TUint& aPort,TRequestStatus& aStatus);
	IMPORT_C TInt RemoveService(const TDesC& aName,const TUint& aPort);
	IMPORT_C void Close();
	IMPORT_C void Cancel();
private:
	};

class RNetDatabase: public RSubSessionBase
	{
public:
	IMPORT_C TInt Open(RSocketServ& aSocketServer,TUint anAddrFamily,TUint aProtocol);
	IMPORT_C void Query(const TDesC8& aQuery,TDes8& aResult,TRequestStatus& aStat);
	IMPORT_C TInt Query(const TDesC8& aQuery,TDes8& aResult);
	IMPORT_C void Add(const TDesC8& anItem,TRequestStatus& aStat);
	IMPORT_C TInt Add(const TDesC8& anItem);
	IMPORT_C void Remove(const TDesC8& anItem,TRequestStatus& aStat);
	IMPORT_C TInt Remove(const TDesC8& anItem);
	IMPORT_C void Close();
	IMPORT_C void Cancel();
private:
	};

class ByteOrder
	{
public:
	IMPORT_C static TUint32 Swap32(TUint32 aVal);
	IMPORT_C static TUint16 Swap16(TUint16 aVal);
	inline static TUint16 Swap16(TUint aVal);
	};

class BigEndian
	{
public:
	IMPORT_C static TUint32 Get32(const TUint8* aPtr);
	IMPORT_C static TUint16 Get16(const TUint8* aPtr);
	IMPORT_C static void Put32(TUint8* aPtr, TUint32 aVal);
	IMPORT_C static void Put16(TUint8* aPtr, TUint16 aVal);
	};

class LittleEndian
	{
public:
	IMPORT_C static TUint32 Get32(const TUint8* aPtr);
	IMPORT_C static TUint16 Get16(const TUint8* aPtr);
	IMPORT_C static void Put32(TUint8* aPtr, TUint32 aVal);
	IMPORT_C static void Put16(TUint8* aPtr, TUint16 aVal);
	};

#include "ES_SOCK.inl"
	
#endif	//__ES_SOCK_H__

