// SS_PMAN.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __SS_PMAN_H__
#define __SS_PMAN_H__

#include <es_prot.h>

class CSocket;
class CSocketServer;
class CProtocolBase;
class CMBufManager;
class CHostResolver;
class CServiceResolver;
class CNetDatabase;
class CSockSession;
struct TProtocolDesc;
class CProtocolRef;
class CMBufManager;
class CDeltaTimer;
class CESockIniData;

//
// Housekeeping structures used internally by the Protocol manager.
//

class CProtocolFamilyBase;
class CProtocolBase;
class CProtocolFamilyRef : public CBase
	{
public:
	enum TManagerProtFamilyFlags
		{
		EInstalled=0x00000001,
		};
	TSglQueLink iLink;
public:
	~CProtocolFamilyRef();
	static CProtocolFamilyRef* GetProtocolFamilyL(TDesC& aName);
	void LoadL();
	CProtocolFamilyBase& ProtocolFamilyL(TBool aInstall=ETrue);
	inline void Close();
	inline void FamilyClosed();
private:
	CProtocolFamilyRef();
private:
	TInt iFlags;
	CProtocolFamilyBase *iProtocolFamily;
	HBufC *iLibFileName;
	};

class Nif;
class CProtocolRef : public CBase
	{ 
friend class Nif;
public:
	enum TManagerProtocolFlags
		{
		EInited=0x00000001,
		EStarted=0x00000002,
		EBound=0x00000004,
		};
	TSglQueLink iLink;
public:
	~CProtocolRef();
	TBool Matches(TUint anAddrFamily,TUint aSocketType,TUint aProtocol);
	static CProtocolRef* GetProtocolL(const TDesC& aName);
	static CProtocolRef* MakeRefL(const TDesC& aName,CProtocolFamilyRef* aFamily=NULL,TServerProtocolDesc* info=NULL);
	inline void LoadAndBindL();
	CProtocolBase* Protocol();
	inline CProtocolFamilyBase* Family();
	TServerProtocolDesc& Info();
	inline void ProtocolClosed();
	inline void Close();
	inline TPtrC Tag();
private:
	void StartL();
	void ResolveBindingL();
	void LoadL(TBool aLoadForBinding);
	CProtocolRef();
	void DoBindingL(CESockIniData& anIniFile);
	static void Cleanup(TAny* aFamily);
private:
	TUid iUid;
	HBufC *iTag;
	TUint iFlags;
	TServerProtocolDesc iInfo;
	CProtocolBase *iProtocol;
	CProtocolFamilyRef *iFamily;
	};

class SocketServer;
class CSocketServExtBase;
class CSocketServExtRef : public CBase
	{
	friend class SocketServer;	
public:
	CSocketServExtRef();
	virtual ~CSocketServExtRef();
	void InstallL(const TDesC& aDllName, const TDesC& aParam);
	void Remove();
	void Close();
private:
	TDblQueLink iExtLink;
	RLibrary iLibrary;
	CSocketServExtBase* iExtension;
	CAsyncCallBack* iDestructor;
public:
	inline CSocketServExtBase* Extension() { return iExtension; }
	};

typedef CSocketServExtBase* (*TSocketServExtInstallFn)();

#if !defined (__WINS__)
#define VERBOSE
#endif

#if defined (VERBOSE)
#define VERBOSE_ONLY(x) x
#else
#define VERBOSE_ONLY(x)
#endif

struct TServerProtocolDesc;
class ProtocolManager
	{
friend class SocketServer;
public:
	static CSocket* NewSocketL(TUint anAddrFamily,TUint aSocketType,TUint aProtocol,CSockSession* aSession);
	static CSocket* NewSocketL(CSockSession* aSession);
	static void LoadProtocolL(TUint anAddrFamily,TUint aSocketType,TUint aProtocol,CSockSession* aSession);
	static void UnLoadProtocolL(TUint anAddrFamily,TUint aSocketType,TUint aProtocol,CSockSession* aSession);
	static CHostResolver* NewHostResolverL(TUint anAddrFamily,TUint aSocketType,CSockSession* aSession);
	static CServiceResolver* NewServiceResolverL(TUint anAddrFamily,TUint aSocketType,TUint aProtocolId,CSockSession *aSession);
	static CNetDatabase* NewNetDatabaseL(TUint anAddrFamily,TUint aSocketType,CSockSession* aSession);
	static TUint NumProtocols(void);
	static TInt ProtocolInfo(TUint anIndex,TProtocolDesc &aProtocol);
	static TInt ProtocolInfo(const TDesC &aName,TProtocolDesc &aProtocol);
	static TInt ProtocolInfo(const TDesC &aName,TServerProtocolDesc &aProtocol);
	static CProtocolBase* FindAndLoadProtocolL(const TDesC& aName, TProtocolType aType=ENormalProtocol);
	static CSocket* TransferSocketL(const TDesC& aName, CSockSession* aSession);
private:
	static void InitL();
	static void ShutDown(void);
	static CProtocolRef* FindProtocolL(TInt anAddrFamily,TInt aSocketType,TInt aProtocol);
	static void CleanupProtocol(TAny* aProtocol);
	};

class SocketServer
	{
public:
	static void InitL(CSocketServer &aServer);
	static void ShutDown(void);
	static RHeap* Heap();
	static void InitMBufManagerL();
	static CMBufManager* GetMBufManager();
	static CDeltaTimer* GetTimer();
	static CSocketServer* GetSocketServer();
	static void NewSession();
	static void SessionClosing();
	static TBool IsShuttingDown();
	static void ShutdownExtensions();
	static void InstallExtensionL(const TDesC& aDllName, const TDesC& aArgs);
	static IMPORT_C void __DbgForceLoadMBufManagerL();
	static IMPORT_C void __DbgForceKillMBufManager();
	};

class CShutdownWatchDog : public CTimer
	{
private:
	CShutdownWatchDog();
	void RunL();
public:
	void Shutdown();
	static CShutdownWatchDog* NewL();
	};

#ifdef __MARM__
//const TInt KTimerGranularity = 100000;
const TInt KTimerGranularity = 15500;
#else
const TInt KTimerGranularity = 80000;
#endif

#include "ss_pman.inl"

#endif
