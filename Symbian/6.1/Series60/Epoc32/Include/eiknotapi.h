// EIKNOTAPI.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKNOTAPI_H__)
#define __EIKNOTAPI_H__

#include <e32std.h>
#include <e32base.h>
#include <f32file.h>

const TUid KUidNotifierPlugIn={0x10005522}; 
_LIT(EIKNOTEXT_SERVER_NAME,"ExtendedNotifierServer");
_LIT(EIKNOTEXT_SERVER_SEMAPHORE,"ExtendedNotifierSemaphore");
const TUint KNotifierDefaultHeapSize = 0x100000;

_LIT8(KEikNotifierPaused,"Eik_Notifier_Paused");
_LIT8(KEikNotifierResumed,"Eik_Notifier_Resumed");

enum TEikNotExtStatus
	{
	EEikNotExtRequestCompleted =0,
	EEikNotExtRequestQueued =1
	};

/**
 * Interface to allow notifiers to manage their own startup/shutdown.  This class is likely to be of most
 * interest to notifiers that observe engines using publically available APIs rather than those that are run
 * via RNotifier.
 */
class MEikSrvNotifierManager
	{
public:
	virtual void StartNotifierL(TUid aNotifierUid,const TDesC8& aBuffer,TDes8& aResponse)=0;
	virtual void CancelNotifier(TUid aNotifierUid)=0;
	virtual void UpdateNotifierL(TUid aNotifierUid,const TDesC8& aBuffer,TDes8& aResponse)=0;
	};

/**
 * Plug-in format for server side notifiers.  Any number of MEikSrvNotifierBases can be included in a single
 * dll.  All notifiers will be loaded during device startup and won't be destroyed until the eikon server
 * closes down.
 *
 * All notifiers run in the eikon server thread so are able to directly access server side status panes but 
 * can't call any REikAppUiSession methods.
 */
class MEikSrvNotifierBase
	{
public:
	enum TNotifierPriority
		{
		ENotifierPriorityAbsolute=500,
		ENotifierPriorityVHigh=400,	
		ENotifierPriorityHigh=300,	
		ENotifierPriorityLow=200,	
		ENotifierPriorityVLow=100,	
		ENotifierPriorityLowest=0	
		};
public:
	class TNotifierInfo
		{
	public:
		TUid iUid;
		TUid iChannel;
		TInt iPriority;
		};
public:
	/**
	 * Called when all resources allocated by notifiers shoudl be freed.
	 */
	virtual void Release()=0;
	/**
	 * Called when a notifier is first loaded to allow any initial construction that is required.
	 */
	virtual TNotifierInfo RegisterL()=0;
	/**
	 * Return the priority a notifier takes and the channels it acts on.  The return value may be varied 
	 * at run-time.
	 */
	virtual TNotifierInfo Info() const=0;
	/**
	 * Start the notifier with data aBuffer and return an initial response.
	 */
	virtual TPtrC8 StartL(const TDesC8& aBuffer)=0;
	/**
	 * Start the notifier with data aBuffer.  aMessage should be completed when the notifier is deactivated.
	 * May be called multiple times if more than one client starts the notifier.  The notifier is immediately
	 * responsible for completing aMessage.
	 */
	virtual void StartL(const TDesC8& aBuffer, const TAny* aReturnVal, RMessage aMessage)=0;
	/**
	 * The notifier has been deactivated so resources can be freed and outstanding messages completed.
	 */
	virtual void Cancel()=0;
	/**
	 * Update a currently active notifier with data aBuffer.
	 */
	virtual TPtrC8 UpdateL(const TDesC8& aBuffer)=0;
public:
	void SetManager(MEikSrvNotifierManager* aManager);
protected:
	MEikSrvNotifierManager* iManager;
private:
	IMPORT_C virtual void MEikSrvNotifierBase_Reserved_1();
private:
	TInt iNotBSpare;
	};

#endif
