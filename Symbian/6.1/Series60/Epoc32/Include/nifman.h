// NIFMAN.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

//
// Interface Manager API
//

#if !defined(__NIFMAN_H__)
#define __NIFMAN_H__

#ifndef __ES_PROT_H__
#include <es_prot.h>
#endif

#ifndef __NIFVAR_H__
#include <nifvar.h>
#endif

#ifndef __CDBOVER_H__
#include <cdbover.h>
#endif

// Manager classes
class CNifMan;
class CNifFactory : public CObject
	{
friend class CNifMan;
public:
	IMPORT_C CNifFactory();
	IMPORT_C virtual TInt Open();
	IMPORT_C virtual void Close();
	IMPORT_C static void Cleanup(TAny* aObject);
    IMPORT_C static TInt ControlledDelete(TAny* aFactory);
	IMPORT_C void InitL(RLibrary& aLib, CObjectCon& aCon);

protected:
	IMPORT_C ~CNifFactory();
	virtual void InstallL()=0;
	RLibrary iLib;
	CAsyncCallBack* iAsyncDtor;
	};

// Progress reporting

class TNifProgress
	{	
public:
	inline TNifProgress();
	TInt iStage;
	TInt iError;
	};

typedef TPckgBuf<TNifProgress> TNifProgressBuf;

// Static internal API class
enum TNifSocketState { ENifBuffers2048=-4, ENifBuffers1024, ENifBuffers512, 
					   ENifSocketNull=-1,
                       ENifSocketCreated=0, ENifSocketOpen=3, ENifSocketConnected=4,
					   ENifSocketError=9 };

class MNifIfUser;
class CNifIfBase;
class Nif
	{
public:
	// Network protocol support
	IMPORT_C static void BindL(MNifIfUser& aUser, TAny* aId, TDes& aResult, const TDesC& aName=TPtrC(0,0));
	IMPORT_C static void NetworkLayerClosed(MNifIfUser& aUser);
	IMPORT_C static void StartL(TDes& aResult, const TDesC& aName=TPtrC());
	IMPORT_C static void Stop(const TDesC& aName=TPtrC());
	IMPORT_C static CNifIfBase* CreateInterfaceL(const TDesC& aName);
	IMPORT_C static void CheckInstalledMBufManagerL();
	IMPORT_C static CProtocolBase* IsProtocolLoaded(const TDesC& aName);
	IMPORT_C static void CheckInstalledL();
	IMPORT_C static TInt SetSocketState(TNifSocketState aState, CServProviderBase* aProvd);
	IMPORT_C static void ProgressL(TNifProgress& aProgress, const TDesC& aName=TPtrC());
	IMPORT_C static void Stop(TAny* aId, CNifIfBase* aIf=0);
	IMPORT_C static void ProgressL(TNifProgress& aProgress, TAny* aId, CNifIfBase* aIf=0);
	};

// Client side classes
const TInt KDefaultNifSlots = 1;	// async message for progress notifier

class TNifAgentInfo
	{
public:
	TVersion iVersion;
	TName iName;
	};

class RNif : public RSessionBase
	{
public:
	IMPORT_C TInt AgentInfo(TNifAgentInfo& aInfo);
	IMPORT_C TInt DisableTimers(TBool aDisable=ETrue);
	IMPORT_C TInt Stop();
	IMPORT_C void ProgressNotification(TNifProgressBuf& aProgress, TRequestStatus& aStatus);
	IMPORT_C void CancelProgressNotification();
	IMPORT_C TInt Progress(TNifProgress& aProgress);
	IMPORT_C TInt LastProgressError(TNifProgress& aProgress);
	IMPORT_C static TVersion Version();
	IMPORT_C TInt Open(const TDesC& aName=TPtrC(), TInt aSlots=KDefaultNifSlots);
	IMPORT_C TInt NetworkActive(TBool& aIsActive);
protected:
    IMPORT_C TInt Start(TAny *aPtr);
	};

class RNifMonitor : public RNif
	{
public:
	IMPORT_C TInt Open(const TDesC& aName=TPtrC(), TInt aSlots=KDefaultNifSlots);
	};

class Nifman
	{
public:
	IMPORT_C static TInt CheckIniConfig();
	};

enum TAgentConnectType 
	{
	EAgentStartDialOut,
	EAgentReconnect,
	EAgentStartCallBack,
	EAgentNone,
	EAgentStartDialIn
	};	

// Interface classes

// Inlines

inline TNifProgress::TNifProgress()
	{ iStage=0; iError=KErrNone; }

#endif