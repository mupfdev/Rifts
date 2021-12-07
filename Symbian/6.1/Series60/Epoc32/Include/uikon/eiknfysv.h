// EIKNFYSV.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKNFYSV_H__)
#define __EIKNFYSV_H__

#include <e32base.h>
#include <w32std.h>
#include <eiknotapi.h>
#include <eiksvfty.h>

//
// class CEikServNotifyServer
//

class CEikSrvNotifierManager;
class CEikServNotifyAlert;
class CEikInfoMsgWin;
class MEikSrvNotifierBase;
class CChannelMonitor;
class CActivityMonitor;
class CEikNotifierQueue;
class CQueueItem;

/**
 * @internal
 * Internal to Symbian
 */
class CEikServNotifyServer : public CServer
	{
public:
	IMPORT_C ~CEikServNotifyServer();
	static CEikServNotifyServer* NewL(MEikServNotifyAlert* aAlert);
public: // from CServer
	virtual CSharableSession* NewSessionL(const TVersion &aVersion) const;
public:
	IMPORT_C TInt DisplayNotifier(const TDesC& aTitle, const TDesC& aLabel, const TDesC& aBut1, const TDesC& aBut2);
	IMPORT_C void DisplayInfoPrint(const TDesC& aDes);
	IMPORT_C CEikServNotifyServer(TInt aPriority);
	inline CEikSrvNotifierManager* Manager() const;
public:
	void SetIsExiting();
	TBool IsExiting() const;
private:
	void ConstructL();
private:
	MEikServNotifyAlert* iAlert;
	class MEikSrvNotifierBase;
	CEikInfoMsgWin* iInfoMsg;
	RWindowGroup iInfoMsgGroupWin;
	CEikSrvNotifierManager* iManager;
	TBool iExiting;
	};

//
// class CEikServNotifySession
//
class CEikServNotifySession : public CSession
	{
public:
	CEikServNotifySession(RThread aClient,const CEikServNotifyServer& aServer);
	~CEikServNotifySession();
public: // from CSession
	virtual void ServiceL(const RMessage &aMessage);
private:
	void DisplayAlert(const RMessage& aMessage);
	void DisplayInfoMsg(const RMessage& aMessage);
	void DoStartNotifierL(const RMessage& aMessage);
	void DoUpdateNotifierL(const RMessage& aMessage);
	TInt StartNotifierAndGetResponseL(const RMessage& aMessage,TBool& aCleanupComplete);
private:
	const CEikServNotifyServer* iServer;
	TInt iClientId;
	};

#ifndef __WINS__
class CLcdPartialMode;
#endif

class CEikSrvNotifierManager: public CBase, public MEikSrvNotifierManager
	{
public:
	static CEikSrvNotifierManager* NewL();
	~CEikSrvNotifierManager();
	void RegisterL(RFs& aFs);
	TInt NotifierStartL(TUid aNotifierUid,const TDesC8& aBuffer,TDes8& aResponse,TInt aClientId);
	TInt NotifierUpdateL(TUid aNotifierUid,const TDesC8& aBuffer,TDes8& aResponse,TInt aClientId);
	TInt NotifierCancel(TUid aNotifierUid);
	TInt NotifierStartAndGetResponseL(TUid aNotifierUid,const TDesC8& aBuffer,const TAny* aResponse,
										const RMessage& aMessage,TInt aClientId,TBool& aCleanupComplete);
	void HandleClientExit(TInt aClientId);
	TInt NotifierStartAndGetResponseL(TUid aNotifierUid,TUid aChannelUid,const TDesC8& aBuffer,const TAny* aResponse,
										const RMessage& aMessage,TInt aClientId,TBool& aCleanupComplete);
public: // from MEikSrvNotifierManager
	void StartNotifierL(TUid aNotifierUid,const TDesC8& aBuffer,TDes8& aResponse);
	void CancelNotifier(TUid aNotifierUid);
	void UpdateNotifierL(TUid aNotifierUid,const TDesC8& aBuffer,TDes8& aResponse);

public:
	void ActivateDisplayIfNeeded();

private:
	void DoAddPlugInL(const TDesC& aPath,const TDesC& aFileName,const TUidType& aUidType);
	CEikSrvNotifierManager();
	void ConstructL();
	void StartFromQueueL(CQueueItem* aItem);
private:
	CArrayPtr<MEikSrvNotifierBase>* iObservedList;
	CArrayFix<RLibrary>* iLibraries;
	CChannelMonitor* iChannelMonitor;
	CActivityMonitor* iActivityMonitor;
	CEikNotifierQueue* iQueue;

#ifndef __WINS__
	CLcdPartialMode* iLcd;
#endif
	};

class TChannelActivity
	{
public:
	inline TChannelActivity(TUid aChannel,TInt aHighestPriorityRunning);
public:
	TUid iChannel;
	TInt iHighestPriorityRunning;
	};
	
class CChannelMonitor: public CBase
	{
public:
	static CChannelMonitor* NewL();
	inline void AddNewChannelL(TUid aChannel);
	TBool AlreadyHasChannel(TUid aChannel) const;
	TInt ActivityLevel(TUid aChannel) const;
	void UpdateChannel(TUid aChannel,TInt aLevel);
private:
	CChannelMonitor();
private:
	CArrayFixFlat<TChannelActivity> iMonitor;
	};

class CNotifierActivity : public CBase
	{
public:
	static CNotifierActivity* NewLC(const MEikSrvNotifierBase::TNotifierInfo& aInfo,TInt aClientId);
	~CNotifierActivity();
	TInt Find(TInt aClientId) const;
private:
	CNotifierActivity(const MEikSrvNotifierBase::TNotifierInfo& aInfo);
	void ConstructL(TInt aClientId);
public:
	const MEikSrvNotifierBase::TNotifierInfo iInfo;
	CArrayFixFlat<TInt> iClientArray;
	};

class CActivityMonitor : public CBase
	{
public:
	static CActivityMonitor* NewL();
	~CActivityMonitor();
	void AddL(const MEikSrvNotifierBase::TNotifierInfo& aInfo,TInt aClientId);
	void Remove(TUid aNotifierUid,TInt aClientId);
	void RemoveNotifier(TUid aNotifierUid,TUid aChannel);
	void RemoveClient(TInt aClientId);
	TBool IsNotifierActive(TUid aNotifierUid,TUid aChannel) const;
	TBool IsChannelActive(TUid aChannel,TUid& aNotifier,MEikSrvNotifierBase::TNotifierPriority& aHighestPriority) const;
	TBool IsClientPresent(TUid aNotifierUid,TUid aChannel,TInt aClientId) const;
	TBool NotifierForClient(TUid& aNotifier,TInt aClientId) const;
private:
	CActivityMonitor();
	TInt Find(TUid aNotifierUid) const;
	TInt Find(TUid aNotifierUid,TUid aChannel) const;
private:
	CArrayPtrFlat<CNotifierActivity> iMonitor;
	};

class CQueueItem: public CBase
	{
public:
	static CQueueItem* NewL(const MEikSrvNotifierBase::TNotifierInfo& aInfo,const TDesC8& aBuffer,
										const TAny* aPtr,const RMessage& aMessage,TInt aClientId); //Asynchronous
	static CQueueItem* NewL(const MEikSrvNotifierBase::TNotifierInfo& aInfo,const TDesC8& aBuffer,
										TDes8& aResponse,TInt aClientId); //synchronous
	~CQueueItem();
private:
	CQueueItem(const MEikSrvNotifierBase::TNotifierInfo& aInfo);
	void ConstructL(const TDesC8& aBuffer,TDes8& aResponse,TInt aClientId);
	void ConstructL(const TDesC8& aBuffer,const RMessage& aMessage,TInt aClientId,const TAny* aPtr);
public:
	const MEikSrvNotifierBase::TNotifierInfo iInfo;
	HBufC8* iBuffer;
	HBufC8* iResponse;
	TBool iAsynchronous;
	RMessage iMessage;
	TInt iClientId;
	const TAny* iPtr;
	};
	
class CEikNotifierQueue: public CBase
	{
public:
	static CEikNotifierQueue* NewL();
	inline void QueueItemL(CQueueItem* aItem);
	CQueueItem* FetchItem(TUid aChannel);
	TBool IsAlreadyQueued(TUid aNotifier,TUid aChannel) const;
	void RemoveClient(TInt aClientId);
	TInt GetHighestQueuePriority(TUid aChannel);
private:
	inline CEikNotifierQueue();
private:
	CArrayPtrFlat<CQueueItem> iQueue;
	};


inline TChannelActivity::TChannelActivity(TUid aChannel, TInt aHighestPriorityRunning)
	:iChannel(aChannel),iHighestPriorityRunning(aHighestPriorityRunning)
	{}

inline void CChannelMonitor::AddNewChannelL(TUid aChannel)
	{iMonitor.AppendL(TChannelActivity(aChannel,0));}

inline CEikSrvNotifierManager* CEikServNotifyServer::Manager() const
	{return iManager;}

inline void CEikNotifierQueue::QueueItemL(CQueueItem* aItem)
	{iQueue.AppendL(aItem);}
inline CEikNotifierQueue::CEikNotifierQueue()
	:iQueue(3)
	{}

#endif
