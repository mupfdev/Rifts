// EIKSRV.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKSRV_H__)
#define __EIKSRV_H__

#if !defined(__EIKAPPUI_H__)
#include <eikappui.h>
#endif

#if !defined(__EIKENV_H__)
#include <eikenv.h>
#endif

#if !defined(__APGTASK_H__)
#include <apgtask.h>
#endif

#if !defined(_EIKUNDER_H__)
#include <eikunder.h>
#endif

class CEikServAppUiBase;
class CDictionaryFileStore;
class CEikServStatusPane;
class CEikServAppStarter;
class CVwsSessionWrapper;
class CEikServExtra;
class CEikServAppUiSession;
class CEikSgcServer;

class CEikServAppUiServer :public CServer
	{
	friend CEikServAppUiSession;
public:
	enum {EPriority=EPriorityAbsoluteHigh};
	IMPORT_C static CEikServAppUiServer* NewL();
	virtual CSharableSession* NewSessionL(const TVersion &aVersion) const;
	inline void SessionDied();
	static TInt ThreadFunction(TAny* aStarted);
private:
	CEikServAppUiServer(TInt aPriority=EPriority);
	void ConstructL();
private:
	CEikServAppUiBase* iAppUi;
	CEikServAppUiSession* iSession;
	};

class CEikServAppUiSession : public CSession
	{
public:
	 CEikServAppUiSession(RThread aClient, CEikServAppUiServer * aServer);
	 static CEikServAppUiSession* NewL(RThread aClient, CEikServAppUiServer * aServer);
	~CEikServAppUiSession();
	void ConstructL();
	virtual void ServiceL(const RMessage &aMessage);
	void Write(const TAny* aPtr,const TDesC8& aDes,TInt anOffset=0);
protected:
	CEikServAppUiServer* iAppUiServer;
	TBool iScreenBlanked;
	};

inline void CEikServAppUiServer::SessionDied() { iSession=NULL; }

/**
 * @internal
 * Internal to Symbian
 */
class CEikPasswordModeCategory : public CBase
	{
public:
	IMPORT_C static CEikPasswordModeCategory* NewLC(RFs& aFs);
	IMPORT_C ~CEikPasswordModeCategory();
	IMPORT_C void GetPasswordModeL(TPasswordMode& aMode) const; 
	IMPORT_C void SetPasswordModeL(TPasswordMode aMode);
private:
	CEikPasswordModeCategory();
	void ConstructL(RFs& aFs);
private:
	CDictionaryFileStore* iStore;
	};

//
// CEikServAppUiBase
//

class CEikServNotifyServer;
class CNotifierServerExtended;
class CEikServBackupServer;
class CEikServAlarmAlertServer;
class CEikKeyWindow;
class CEikUndertaker;
class CEikPasswordControl;
class CEikTaskListDialog;
class MEikServNotifyAlert;
class MEikServAlarmFactory;
class CEikServDllClose;
class CEikServBlankWin;

/**
 * @internal
 * Internal to Symbian
 */
class TEikServCtrlFactories
	{
public:
	inline TEikServCtrlFactories();
	inline TEikServCtrlFactories(MEikServNotifyAlert* aAlert,MEikServAlarmFactory* aAlarmAlert);
public:
	MEikServNotifyAlert* iAlert;
	MEikServAlarmFactory* iAlarmAlert;
	};


/**
 * @internal
 * Internal to Symbian
 */
class CEikServAppUiBase : public CEikAppUi, public MEikUndertakerObserver
    {
public:
	enum TTaskCycleDirection { EBackwards, EForwards };
	enum TEikServServers { EAlwlSvr=0x01, EApaSvr=0x02, EBackupSvr=0x04 };
	enum TEikSrvShutdownState {	EShutdownWaitingForApps=0, EShutdownKillingRogueApps };
public:
	IMPORT_C static CEikServAppUiBase* NewLC();
	IMPORT_C ~CEikServAppUiBase();
	IMPORT_C void NotifyAlarmServerOfTaskChange() const;
	IMPORT_C virtual void EnableTaskListL();
	IMPORT_C virtual void LaunchTaskListL() const;
	IMPORT_C void CycleTasks(TTaskCycleDirection aDirection) const;
	IMPORT_C void SetStatusPaneFlags(TInt aFlags) const;
	IMPORT_C void SetStatusPaneLayoutL(TInt aLayoutResId) const;
	IMPORT_C virtual void BlankScreenL();
	IMPORT_C virtual void UnblankScreen();
	IMPORT_C void ShutdownAppsL(const TUid aRequesterUID, const RMessage& aShutdownMessage, const TInt aTimeoutInMicroseconds);
	static TInt ShutdownTimeoutL(TAny* aPtr);
	IMPORT_C void HandleForegroundEventL(TBool aForeground);
	IMPORT_C void SetSgcParamsL(TInt aWgId, TBool aFullScreen, TInt aSpLayout, TInt aSpFlags);
	IMPORT_C void PrepareForAppExitL(TInt aWgId);

public:
	inline RWindowGroup& AlertGroupWin() const;
	IMPORT_C void BringAlertGroupWinForwards(TBool aForwards);

protected:
	IMPORT_C void ConstructL();
	IMPORT_C void InitializeL(TEikServCtrlFactories& aCtrlFactories);
	IMPORT_C CEikServAppUiBase();
	IMPORT_C void HandleWsEventL(const TWsEvent& aEvent,CCoeControl* aDestination);
protected: // from MEikUndertakerObserver
	IMPORT_C void HandleThreadExitL(RThread& aThread);
private: // framework
	IMPORT_C void HandleSystemEventL(const TWsEvent& aEvent);
	IMPORT_C void HandleApplicationSpecificEventL(TInt aType,const TWsEvent& aEvent);
    IMPORT_C TKeyResponse HandleKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	IMPORT_C void HandleSwitchOnEventL(CCoeControl* aDestination);
	IMPORT_C void HandleResourceChangeL(TInt aType);
private: // specific
	void SetSystemTime() const;
	static TInt RestartServerCallback(TAny* aObj);
	void RestartServer();
	TInt CEikServAppUiBase::DoShutdownTimeoutL();
	void ProceedWithShutdown();

protected:
	RWindowGroup iAlertGroupWin;
	TInt iAlertGroupForwardsCount;
	TInt iResourceFileOffset;
	CEikServNotifyServer* iNotifyServer;
	CEikServBackupServer* iBackupRestoreServer;
	CEikServAlarmAlertServer* iAlarmAlertServer;
	CEikUndertaker* iUndertaker;
	RWindowGroup iBackdropWindowGroup;
	CEikServStatusPane* iStatusPane;
	CEikServBlankWin* iBlankWin;
	TInt iBlankWinRefCount;
private:
	//class CAppThreadWatcher
	//Exits / Kills a running task & notifies when complete
	class CAppExitNotifier : public CActive
		{
	public:
		enum TAppExitMethod
			{
			EAppExitNormal,
			EAppExitForced
			};
	public: // Constructors and destructor
		static CAppExitNotifier* NewL(TApaTask* aTask,	CEikServAppUiBase* aObserver);
		~CAppExitNotifier();
		void ExitTask();		//The nice way, exits a task cleanly
		void KillTask();		//The nasty way, kills a task. For use when ExitTask doesn't work
		TBool IsDead();
		const TApaTask& Task() const;
		const TThreadId ThreadId() const;
	private:
		void ConstructL();
		void RunL();
		void DoCancel();
		CAppExitNotifier(TApaTask* aTask, CEikServAppUiBase* aObserver);

	private:  // Data
		CEikServAppUiBase* iObserver;	    // Pointer to CEikServAppUiBase for callbacks
		TBool iIsDead;						// flag indicating the status of the thread
		TApaTask* iTask;						// Task being exited
		RThread iThread;					// iTask's thread
		TThreadId iThreadId;				// iTask's threadID
		TAppExitMethod iExitMethod;			// How the app is closed
		};
public:
	void AppExitNotifierL(const CAppExitNotifier* aNotifier,CAppExitNotifier::TAppExitMethod aHowClosed);
private:
	CEikServExtra* iEikServExtra;
	TInt iServerToRestart;
	CEikServAppStarter* iAppStarter;
	CVwsSessionWrapper* iVwsSession;
	};

/**
 * @internal
 * Internal to Symbian
 */
class CEikServEnv : public CEikonEnv
	{
public:
	IMPORT_C CEikServEnv();
	IMPORT_C ~CEikServEnv();
public:
	void SetEikServer(CEikServAppUiServer* aServer);
	void SetUiDll(RLibrary& aDll);
private:
	RLibrary iUiDll;
	CEikServAppUiServer* iServer;
	};

inline TEikServCtrlFactories::TEikServCtrlFactories()
	: iAlert(NULL), iAlarmAlert(NULL)
	{}
inline TEikServCtrlFactories::TEikServCtrlFactories(MEikServNotifyAlert* aAlert,MEikServAlarmFactory* aAlarmAlert)
	: iAlert(aAlert), iAlarmAlert(aAlarmAlert)
	{}

inline RWindowGroup& CEikServAppUiBase::AlertGroupWin() const
	{ return((RWindowGroup&)iAlertGroupWin); }
      
#endif
