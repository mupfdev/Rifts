// VIEWCLI.H
//
// Copyright (c) 1999 Symbian Ltd.  All rights reserved.
//

#ifndef __VIEWCLI_H__
#define __VIEWCLI_H__

#include <e32base.h>
#include <vwsdef.h>

//
// Forward declarations.
//

class RVwsSession;
class CVwsSessionEventHandler;
class MVwsAppStarter;


/** 
 * The MVwsSessionObserver specifies an interface through which server events to be handled by the owner of
 * a client session are notified
 *
 * @internal
 * Internal to Symbian
 *
 */
class MVwsSessionWrapperObserver
	{
public:	// Internal to Symbian

	/**
	 * Handles the view event aEvent for a view added through the client session being observed.
	 * Handles events for all the views added by the client.
	 */
	virtual void HandleViewEventL(const TVwsViewEvent& aEvent)=0;
	};


/**
 * The CVwsSessionWrapper class mediates access to the view server client session which it creates, and wraps in
 * support for notification of server events. A session observer will be called back with server events if
 * it maintains an outstanding request for asynchronous event notification.
 *
 * @internal
 * Internal to Symbian
 *
 */
class CVwsSessionWrapper : public CBase
	{
public:	// Internal to Symbian
	IMPORT_C static CVwsSessionWrapper* NewL();
	IMPORT_C static CVwsSessionWrapper* NewLC();
	IMPORT_C static CVwsSessionWrapper* NewL(MVwsSessionWrapperObserver& aObserver);
	IMPORT_C static CVwsSessionWrapper* NewLC(MVwsSessionWrapperObserver& aObserver);
	IMPORT_C ~CVwsSessionWrapper();
	IMPORT_C static TInt StartViewServer(MVwsAppStarter& aAppStarter);
	IMPORT_C TInt ShutdownViewServer();
	IMPORT_C TInt AddView(const TVwsViewId& aViewId);
	IMPORT_C TInt RemoveView(const TVwsViewId& aViewId) const;
	IMPORT_C TInt SetSystemDefaultView(const TVwsViewId& aViewId,TInt aMode);
	IMPORT_C TInt SetSystemDefaultView(const TVwsViewId& aViewId);
	IMPORT_C TInt ActivateView(const TVwsViewId& aViewId,TUid aCustomMessageId,const TDesC8& aCustomMessage);
	IMPORT_C TInt ActivateViewViaViewEvent(const TVwsViewIdAndMessage& aViewIdAndMessage);
	IMPORT_C TInt RequestCustomMessage(TDes8& aMessageBufPtr) const;
	IMPORT_C void QueueAsyncRequest();
	IMPORT_C TInt StartApp(TUid aAppToStart);
	IMPORT_C TInt DeactivateActiveView();
	IMPORT_C TInt NotifyNextDeactivation(const TVwsViewId& aViewId);
	IMPORT_C TInt NotifyNextDeactivation();
	IMPORT_C TInt NotifyNextActivation(const TVwsViewId& aViewId);
	IMPORT_C TInt NotifyNextActivation();
	IMPORT_C TInt SetDefaultView(const TVwsViewId& aViewId,TInt aMode) const;
	IMPORT_C TInt SetDefaultView(const TVwsViewId& aViewId) const;
	IMPORT_C TInt CreateActivateViewEvent(const TVwsViewId& aViewId,TUid aCustomMessageId,const TDesC8& aCustomMessage);
	IMPORT_C TInt SetClientRequestTimeOut(TTimeIntervalMicroSeconds32 aDuration);
	IMPORT_C TInt SetServerEventTimeOut(TTimeIntervalMicroSeconds32 aDuration);
	IMPORT_C TInt EnableServerEventTimeOut(TBool aEnable);
private:
	CVwsSessionWrapper();
	CVwsSessionWrapper(MVwsSessionWrapperObserver& aObserver);
	void ConstructL();
	TInt CheckCreateViewServerSession();
	TBool IsSchedulerRunning();
private:
	RVwsSession* iVwsSession;
	CVwsSessionEventHandler* iViewEventHandler;
	MVwsSessionWrapperObserver* iObserver;
	};


//
// Panic.
//

enum TVwsPanic
	{
	EVwsCreateScheduler=1,
	EVwsThreadRename
	};

GLREF_C void Panic(TVwsPanic aPanic);


//
// Server thread start.
//

GLDEF_C TInt ViewServerThreadStart(TAny* aPtr);

/**
 * @internal
 * Internal to Symbian
 */
struct SVwsCommandLine
	{
	MVwsAppStarter* iAppStarter;
	};


#endif

