// Mda\Client\Utility.h 
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __MDA_CLIENT_UTILITY_H__
#define __MDA_CLIENT_UTILITY_H__

/*
Notes:
Defines general client side utility classes

Classes:
CMdaServer
Used to manage a connection to the media server. Handles the return of
events from objects within the server

MMdaObjectEventListener
Used to listen for events returned by CMdaServer

MMdaObjectStateChangeObserver
General prototype for a state change observing interface

CMdaController
Used to manage a controller

MMdaSrcPort/MMdaDstPort
Interfaces for objects that manage media server ports
Used with CMdaController when making connections

CMdaResource
Base class for resource object managing classes.

*/

// Standard EPOC32 includes
#include <e32base.h>

// Media Server includes
#include <Mda\Client\Base.h>
#include <Mda\Client\Controller.h>

enum TMdaCliUtilPanic
	{
	EMdaUtilServerListenerListNotEmpty=0,
	EMdaUtilControllerNotReady=1,
	EMdaUtilControllerCannotSetPriorityInCurrentState=2,
	EMdaUtilControllerCannotConnectInCurrentState=3,
	EMdaUtilControllerCannotPrepareInCurrentState=4,
	EMdaUtilControllerCannotPrimeInCurrentState=5,
	EMdaUtilControllerCannotPlayInCurrentState=6,
	EMdaUtilControllerCannotPauseInCurrentState=7,
	EMdaUtilControllerCannotStopInCurrentState=7,
	EMdaUtilControllerCannotUnprepareInCurrentState=7,
	EMdaUtilControllerCannotResetInCurrentState=8
	};


class MMdaObjectEventListener
	{
public:
	virtual const RMdaObject& MoelObject() const =0;
	virtual void MoelEvent(const TMdaEvent& aEvent) =0;
	virtual void MoelEventMissed() =0;
private:
	TSglQueLink iMoelLink;
	friend class CMdaServer;
	};

class CMdaServer : public CActive
	{
public:
	IMPORT_C static CMdaServer* NewL();
	IMPORT_C ~CMdaServer();
	IMPORT_C void AddListenerL(MMdaObjectEventListener& aListener);
	IMPORT_C void RemoveListener(MMdaObjectEventListener& aListener);
	inline const RMdaRegistry& Registry();
private:
	CMdaServer();
	void ConstructL();
	// From CActive
	virtual void RunL();
	virtual void DoCancel();
private:
	RMdaSession iSession;
	RMdaRegistry iRegistry;
	TMdaEventPackageBuf<4> iEvent[2]; // Double buffered
	TInt iBuf;
	TSglQue<MMdaObjectEventListener> iListeners;
	};

class MMdaObjectStateChangeObserver
	{
public:
	virtual void MoscoStateChangeEvent(CBase* aObject, TInt aPreviousState, TInt aCurrentState, TInt aErrorCode)=0;
	};

class MMdaSrcPort
	{
public:
	virtual const RMdaSrcPort& MspSrcPort()=0;
	};

class MMdaDstPort
	{
public:
	virtual const RMdaDstPort& MdpDstPort()=0;
	};

enum TMdaControllerObjectState
	{
	EMdaControllerObjectNotReady=0,
	EMdaControllerObjectIdle,
	EMdaControllerObjectUnprepared,
	EMdaControllerObjectPrepared,
	EMdaControllerObjectPrimed,
	EMdaControllerObjectPlaying
	};

class CMdaController : public CActive, public MMdaObjectEventListener
	{
public:

	IMPORT_C static CMdaController* NewL(CMdaServer* aServer, MMdaObjectStateChangeObserver& aObserver);
	IMPORT_C virtual ~CMdaController();
	//
	IMPORT_C void SetPriorityL(TInt aPriority, TMdaPriorityPreference aPref);
	//
	IMPORT_C void ConnectL(MMdaSrcPort* aSrcPort, MMdaDstPort* aDstPort, TUid aType);
	IMPORT_C void Prepare();
	IMPORT_C void Prime();
	IMPORT_C void Play();
	IMPORT_C void Pause();
	IMPORT_C void Stop();
	IMPORT_C void Unprepare();
	IMPORT_C void Reset();
	inline TMdaControllerObjectState State() { return iState; }
private:
	CMdaController(CMdaServer* aServer, MMdaObjectStateChangeObserver& aObserver);
	void ConstructL();
	// From CActive
	virtual void RunL();
	virtual void DoCancel();
	// From MMdaObjectEventListener
	virtual const RMdaObject& MoelObject() const;
	virtual void MoelEvent(const TMdaEvent& aEvent);
	virtual void MoelEventMissed();
	//
	TMdaControllerObjectState UpdateState(TMdaControllerState aState);
private:
	TMdaControllerObjectState iState;
	CMdaServer* iServer;
	MMdaObjectStateChangeObserver& iObserver;
	TBool iIsConnected;
	TMdaControllerObjectState iTargetState;
	RMdaController iController;
	TInt iErrorEventReason;
	TUint iIgnoreEventId;
	};

class CMdaResource : public CActive, public MMdaSrcPort, public MMdaDstPort
	{
protected:
	IMPORT_C CMdaResource(TInt aPriority);
	};

// Inlines

inline const RMdaRegistry& CMdaServer::Registry()
	{
	return iRegistry;
	}

#endif
