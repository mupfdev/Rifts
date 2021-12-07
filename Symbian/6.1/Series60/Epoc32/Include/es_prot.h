// ES_PROT.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__ES_PROT_H__)
#define __ES_PROT_H__

#if !defined(__ES_SOCK_H__)
#include <es_sock.h>
#endif

enum TESOCKActivePriority
	{
	ESSExclusivePriority=100000,
	ECommReceivePriority=200,		// Must always run.
	ECommTransmitPriority=100,
	ECAsyncImmediatePriority=75,	// I.e. before a timer event goes off.
	ESocketTimerPriority=50,
	EActiveIpcPriority=20,
	EActiveHighPriority=10,
	EActiveMedPriority=0,
	EActiveLowPriority=-10,
	ECAsyncDeferredPriority=-20,
	};

const TUint KNewDataEndofData = 0xFFFFFFFF;

class CServProviderBase;
class CSocket;
class MSocketNotify
	{
public:
	enum TDelete {EDelete,EDetach};
	enum TOperationBitmasks
		{
		EErrorSend=0x0000001,
		EErrorRecv=0x0000002,
		EErrorConnect=0x0000004,
		EErrorClose=0x00000008,
		EErrorIoctl=0x00000010,
		EErrorFatal=0x10000000,
		EErrorAllOperations=0x7fffffff,
		};
	virtual IMPORT_C void NewData(TUint aCount)=0;
	virtual IMPORT_C void CanSend()=0;
	virtual IMPORT_C void ConnectComplete()=0;
	virtual IMPORT_C void ConnectComplete(const TDesC8& aConnectData)=0;
    virtual IMPORT_C void ConnectComplete(CServProviderBase& aSSP)=0;
	virtual IMPORT_C void ConnectComplete(CServProviderBase& aSSP,const TDesC8& aConnectData)=0;
	virtual IMPORT_C void CanClose(TDelete aDelete=EDelete)=0;
	virtual IMPORT_C void CanClose(const TDesC8& aDisconnectData,TDelete aDelete=EDelete)=0;
	virtual IMPORT_C void Error(TInt anError,TUint anOperationMask=EErrorAllOperations)=0;
	virtual IMPORT_C void Disconnect(void)=0;
	virtual IMPORT_C void Disconnect(TDesC8& aDisconnectData)=0;
	virtual IMPORT_C void IoctlComplete(TDesC8 *aBuf)=0;

//
private:
	};
//
enum TProtocolServiceInfo
	{
	ESocketSupport=0x00000001,		// Can make sockets
	ETransport=0x00000002,			// Can act as a transport - ie can be bound to
	EPreferMBufChains=0x00000004,	// Will process MBufChains (I.e. won't convert them to descriptors)
	EPreferDescriptors=0x00000008,	// Will process Descriptors (I.e. won't convert them to MBufChains)
	ECantProcessMBufChains=0x00000010,	// Will Panic if asked to process an MBufChain
	ENeedMBufs=0x00000020,			// Uses MBufChains internally.
	EUseCanSend=0x00000040,			// Uses the inter-protocol CanSend upcall.
	EInterface=0x00000080,			// Is a CInterfaceBase rather than CProtocolBase
	};
//
enum TProtocolType
	{
	ENormalProtocol,				// Normal protocol
	EInterfaceProtocol				// Has EInterface flags set and supports GetBinderL()
	};
//
const TInt KUnlimitedSockets=-1;
struct TServerProtocolDesc : public TProtocolDesc
	{
	TInt iServiceTypeInfo;
	TInt iNumSockets;
	};

//
class MResolverNotify
	{
public:
	virtual void QueryComplete(TInt anError)=0;
	};

class CServProviderBase : public CBase
	{
	friend class ProtocolManager;
public:
	enum TCloseType {ENormal,EStopInput,EStopOutput,EImmediate};
	IMPORT_C CServProviderBase();
	IMPORT_C virtual ~CServProviderBase();
	inline void SetNotify(MSocketNotify* aSocket);
public:
// pure virtual
	virtual void Start()=0;
	virtual void LocalName(TSockAddr& anAddr) const =0;
	virtual TInt SetLocalName(TSockAddr& anAddr)=0;
	virtual void RemName(TSockAddr& anAddr) const =0;
	virtual TInt SetRemName(TSockAddr& anAddr)=0;
	virtual TInt GetOption(TUint level,TUint name,TDes8& anOption)const =0;
	virtual void Ioctl(TUint level,TUint name,TDes8* anOption)=0;
	virtual void CancelIoctl(TUint aLevel,TUint aName)=0;
	virtual TInt SetOption(TUint level,TUint name,const TDesC8 &anOption)=0;
	virtual TUint Write(const TDesC8& aDesc,TUint options, TSockAddr* anAddr=NULL)=0;
	virtual void GetData(TDes8& aDesc,TUint options,TSockAddr* anAddr=NULL)=0;
	virtual void ActiveOpen()=0;
	virtual void ActiveOpen(const TDesC8& aConnectionData)=0;
	virtual TInt PassiveOpen(TUint aQueSize)=0;
	virtual TInt PassiveOpen(TUint aQueSize,const TDesC8& aConnectionData)=0;
	virtual void Shutdown(TCloseType option)=0;
	virtual void Shutdown(TCloseType option,const TDesC8& aDisconnectionData)=0;
	virtual void AutoBind()=0;
protected:
	MSocketNotify* iSocket;
	};
//
class CProtocolBase;
class CResolverProvdBase : public CBase
	{
	friend class ProtocolManager;
public:
	inline void SetNotify(MResolverNotify* aNotifier);
	virtual void CancelCurrentOperation()=0;
protected:
	MResolverNotify* iNotify;
private:
	CProtocolBase* iProtocol;
	};

class CHostResolvProvdBase : public CResolverProvdBase
	{
	friend class ProtocolManager;
public:
	virtual void GetByName(TNameRecord& aName)=0;
	virtual void GetByAddress(TNameRecord& aName)=0;
	virtual void SetHostName(TDes& aNameBuf)=0;
	virtual void GetHostName(TDes& aNameBuf)=0;
	};

class CServiceResolvProvdBase : public CResolverProvdBase
	{
	friend class ProtocolManager;
public:
	virtual void GetByName(const TDesC& aNameBuf,TInt32& aPortNum)=0;
	virtual void GetByNumber(TDes &aNameBuf,TInt32 aPortNum)=0;
	virtual void RegisterService(const TDesC& aNameBuf,TInt32 aPortNum)=0;
	virtual void RemoveService(const TDesC& aNameBuf,TInt32 aPortNum)=0;
	};

class CNetDBProvdBase : public CResolverProvdBase
	{
	friend class ProtocolManager;
public:
	virtual void Query(TDes8& aBuffer)=0;
	virtual void Add(TDes8& aBuffer)=0;
	virtual void Remove(TDes8& aBuffer)=0;
	};
//
class CProtocolFamilyBase;
class RMBufChain;
class CProtocolRef;
class CProtocolBase : public CBase
	{
	friend class ProtocolManager;
	friend class CProtocolRef;

public:
	IMPORT_C virtual CServProviderBase* NewSAPL(TUint aProtocol);
	IMPORT_C virtual CHostResolvProvdBase* NewHostResolverL();
	IMPORT_C virtual CServiceResolvProvdBase* NewServiceResolverL();
	IMPORT_C virtual CNetDBProvdBase* NewNetDatabaseL();
	IMPORT_C CProtocolBase();
	IMPORT_C virtual ~CProtocolBase();
	CProtocolFamilyBase* ProtocolFamily();
	IMPORT_C virtual void Close();
	IMPORT_C virtual void Open();
	IMPORT_C virtual void CloseNow();
	IMPORT_C virtual void StartSending(CProtocolBase* aProtocol);	// Up
	IMPORT_C TPtrC Tag();

	IMPORT_C virtual void InitL(TDesC &aTag);	// From ProtocolManager before all binding.
	IMPORT_C virtual void StartL();	// From Protocol Manager - after all binding

	IMPORT_C virtual void BindL(CProtocolBase* protocol, TUint id);	// From higher protocol
	IMPORT_C virtual void BindToL(CProtocolBase* protocol);	// From Protocol Manager
	IMPORT_C virtual TInt Send(RMBufChain& aPDU,CProtocolBase* aSourceProtocol=NULL);	// Down
	IMPORT_C virtual TInt Send(TDes8& aPDU,TSockAddr* to,TSockAddr* from=NULL,CProtocolBase* aSourceProtocol=NULL);	// Done
	IMPORT_C virtual void Process(RMBufChain &,CProtocolBase* aSourceProtocol=NULL);	// Up
	IMPORT_C virtual void Process(TDes8& aPDU,TSockAddr *from,TSockAddr *to=NULL,CProtocolBase* aSourceProtocol=NULL);	// Up
	IMPORT_C virtual TInt GetOption(TUint level,TUint name,TDes8& option,CProtocolBase* aSourceProtocol=NULL);	// Down
	IMPORT_C virtual TInt SetOption(TUint level,TUint name,const TDesC8& option,CProtocolBase* aSourceProtocol=NULL);	// Down
	IMPORT_C virtual void Error(TInt anError,CProtocolBase* aSourceProtocol=NULL);	// Up

// Pure virtual
	virtual void Identify(TServerProtocolDesc* aProtocolDesc)const =0;	// from anyone.

	inline TInt RefCount() const;
protected:
	IMPORT_C void CanClose();	// Up
private:
	void TryDelete();
protected:
//	TProtocolDesc iDesc;
private:
	CProtocolRef* iManagerRef;
	TInt iRefCount;
	};
//
class CProtocolFamilyRef;
class CLibUnloader;
class CProtocolFamilyBase : public CBase
	{
friend class ProtocolManager;
friend class CProtocolFamilyRef;
public:
	IMPORT_C virtual ~CProtocolFamilyBase();
	IMPORT_C CProtocolFamilyBase();
	IMPORT_C virtual void Close();
	IMPORT_C virtual void Open();
	IMPORT_C virtual TInt Remove();
	IMPORT_C virtual TBool QueryVersionSupported(const TVersion &aVer) const;
	void SetLibraryL(RLibrary& aLib);
// Pure virtual
	virtual TInt Install()=0;
	virtual CProtocolBase * NewProtocolL(TUint aSockType,TUint aProtocol)=0;
	virtual TUint ProtocolList(TServerProtocolDesc*& aProtocolList)=0;
protected:
	TVersion iVersion;
private:
	TInt iRefCount;
	CLibUnloader* iLibUnloader;
	CProtocolFamilyRef* iManagerRef;
	};

typedef CProtocolFamilyBase* (*TProtocolNew)();


class SocketTimer 
	{
public:
	IMPORT_C static void Queue(TTimeIntervalMicroSeconds32 aTimeInMicroSeconds,TDeltaTimerEntry& aTimer);
	IMPORT_C static void Remove(TDeltaTimerEntry& aTimer);
	};

class SocketServExt
    {
public:
	IMPORT_C static CProtocolBase* FindAndLoadProtocolL(const TDesC& aName, TProtocolType=ENormalProtocol);
	IMPORT_C static void InstallExtensionL(const TDesC& aDllName, const TDesC& aArgs);
	IMPORT_C static void OpenSession();
	IMPORT_C static void CloseSession();
	IMPORT_C static void InstallSchedulerWaitHook(TCallBack* aCall);
	};

// Base class for extensions
class CSocketServExtBase : public CBase
	{
public:
	IMPORT_C virtual ~CSocketServExtBase();
protected:
	IMPORT_C CSocketServExtBase();
public:	
	virtual void InstallL(const TDesC& aArgs)=0;
	virtual void Remove()=0;
	//
private:
	friend class CSocketServExtRef;
	CSocketServExtRef* iExtRef;
	};

const TInt KUidProtocolModule = 0x1000004A;
const TInt KUidUnicodeProtocolModule = 0x10003d38;
const TInt KUidEsockExtension = 0x10000387;

#include "es_prot.inl"

#endif
