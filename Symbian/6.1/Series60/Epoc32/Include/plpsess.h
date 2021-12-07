// PLPSESS.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined (__PLPSESS_H__)
#define __PLPSESS_H__

#if !defined(__C32COMM_H__)
#include <c32comm.h>
#endif

const TUint KPlpInterfaceAny      = 0;
const TUint KPlpInterfaceDevice0  = 1;
const TUint KPlpInterfaceDevice1  = 2;
const TUint KPlpInterfaceLoopback = 3;

class TRemoteLinkStatus
    {
public:
	enum TStatus { EDisabled, EDisconnected, EConnected };
    inline TRemoteLinkStatus();
public:
    TStatus iStatus;
    TUint iRemoteVersion;
    };

const TInt KPlpMaxServiceName = 16;
typedef TBuf8<KPlpMaxServiceName> TPlpServiceName;
typedef TPckgBuf<TRemoteLinkStatus> TRemoteLinkStatusBuf;

enum TPlpConfigType
	{
	EPlpConfigTypeSerial
	};

struct SPlpConfigPkgSerial
	{
	TVersion iPkgVersion;
	TBps iBaud;
	TBuf<KMaxPortName> iPortName;
	TBuf<KMaxFileName> iModuleName;
	};

class TPlpConfigPkgSerial : public TPckgBuf<SPlpConfigPkgSerial>
	{
public:
	IMPORT_C TPlpConfigPkgSerial();
	IMPORT_C TPlpConfigPkgSerial(TBps aBaud, const TDesC& aPort, const TDesC& aModule);
	IMPORT_C void SetConfig(TBps aBaud, const TDesC& aPort, const TDesC& aModule);
	IMPORT_C TBps Baud();
	IMPORT_C TPtrC PortName();
	IMPORT_C TPtrC ModuleName();
	IMPORT_C TVersion PkgVersion();
	};

typedef TInt32 TRemoteLinkConnectReason;

#define ERemoteLinkDefault		0	
#define ERemoteLinkSynchronise	1


class RRemoteLink : public RSessionBase
    {
public:
    IMPORT_C TInt Open(TUint aInterface=KPlpInterfaceDevice0);
    IMPORT_C void Connect(TRequestStatus& aStatus, TRemoteLinkStatusBuf& aBuf, TRemoteLinkConnectReason aReason = ERemoteLinkDefault);
	IMPORT_C TInt Disconnect();
//
    IMPORT_C TVersion Version() const;
	IMPORT_C TInt SetConfig(const TDesC8& aConfigPkg, TPlpConfigType aConfigType = EPlpConfigTypeSerial);
	IMPORT_C TInt Config(TDes8& aConfigPkg, TPlpConfigType aConfigType = EPlpConfigTypeSerial);
//
    IMPORT_C TInt Status(TRemoteLinkStatus& aState) const;
    IMPORT_C void NotifyStatusChange(TRequestStatus& aStatus, TRemoteLinkStatusBuf& aBuf);
    IMPORT_C void CancelNotifyStatusChange();
//
    IMPORT_C void LoadRemoteServer(TRequestStatus& aStatus, TPlpServiceName& aResult, const TDesC& aFileName, const TDesC& aArgs=TPtrC(), TInt aReserved = 0);
	IMPORT_C void LoadLocalServer(TRequestStatus& aStatus, TPlpServiceName& aResult, const TDesC& aFileName, const TDesC& aArgs=TPtrC(), TInt aReserved = 0);
    IMPORT_C void UnloadLocalServer(TRequestStatus& aStatus, const TDesC& aFileName);
    IMPORT_C void UnloadRemoteServer(TRequestStatus& aStatus, const TDesC& aFileName);
    IMPORT_C void CancelLoadRemoteServer();
	IMPORT_C void CancelLoadLocalServer();
	IMPORT_C void CancelUnloadLocalServer();
	IMPORT_C void CancelUnloadRemoteServer();
//
    IMPORT_C void CancelAll();
// Deprecated:
    inline TInt Enable(TBps aBaud, const TDesC& aPort, const TDesC& aModule, TBool aLowPowerMode=EFalse);
    inline TInt Disable();
    inline TInt Config(TBps* aBaud=NULL, TDesC* aPort=NULL, TDesC* aModule=NULL, TBool* aLowPowerMode=NULL);
    inline TInt LoadLocalServer(TPlpServiceName& aResult, const TDesC& aFileName, const TDesC& aArgs=TPtrC(), TInt aReserved = 0);
    inline TInt UnloadLocalServer(const TDesC& aFileName);
    inline TInt EnableFileAccess(TBool aEnable=ETrue);
    inline void WaitForConnect(TRequestStatus& aStatus, TRemoteLinkStatusBuf& aBuf);
private:
	TInt StartServerL();
    };

#ifdef __WINC__
// #include <plpcrac.h>
#define REMOTELINK_CONFIG_SEMAPHORE	KPlpRemoteLinkConfigSemaphore
#else
#define REMOTELINK_CONFIG_SEMAPHORE _L("__PLPREMOTELINKCONFIGSEMAPHORE_EPOC__")
#endif
//

#include <plpsess.inl>

#endif



