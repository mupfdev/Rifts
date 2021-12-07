// COEMAIN.H
//
// Copyright (c) 1997-2000 Symbian Ltd.  All rights reserved.
//

#if !defined(__COEMAIN_H__)
#define __COEMAIN_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

#if !defined(__W32STD_H__)
#include <w32std.h>
#endif

#if !defined(__BARSC_H__)
#include <barsc.h>
#endif

#if !defined(__BADESCA_H__)
#include <badesca.h>
#endif

#if !defined(__BASCHED_H__)
#include <basched.h>
#endif

class CVwsSessionWrapper;
class MVwsSessionWrapperObserver;

class CCoeAppUiBase;
class CCoeEnv;
class TResourceReader;
class RGenericPointerArray;

enum TActivePriority
	{ // an alternative set to the TPriority in E32BASE.H
	EActivePriorityClockTimer=300,
	EActivePriorityIpcEventsHigh=200,
	EActivePriorityFepLoader=150,
	EActivePriorityWsEvents=100,
	EActivePriorityRedrawEvents=50,
	EActivePriorityDefault=0,
	EActivePriorityLogonA=-10
	};

class CCoeEnvExtra;
class CCoeStatic;

/**
 * The MCoeObserverOfLoadedFep class specifies the interface which
 * enables objects to be notified when a front-end processor is loaded.
 * This happens either on application start-up, or as a result of a
 * different front-end processor having been installed.
 */
class MCoeObserverOfLoadedFep
	{
public:
	virtual void HandleChangeInLoadedFep()=0;
private:
	IMPORT_C virtual void MCoeObserverOfLoadedFep_Reserved_1();
	IMPORT_C virtual void MCoeObserverOfLoadedFep_Reserved_2();
	};

/**
 * The MCoeFocusObserver class specifies the interface which enables front-end
 * processors to observe when the target control changes "under their feet".
 */
class TCoeInputCapabilities; // forward declaration of class defined in COEINPUT.H
class MCoeFocusObserver
	{
public:
	virtual void HandleChangeInFocus()=0;
	virtual void HandleDestructionOfFocusedItem()=0;
private:
	IMPORT_C virtual void MCoeFocusObserver_Reserved_1();
	IMPORT_C virtual void MCoeFocusObserver_Reserved_2();
	};

/**
 * The MCoeForegroundObserver specifies the interface which enables front-end
 * processors to observe when the application goes into the foreground/background.
 */
class MCoeForegroundObserver
	{
public:
	virtual void HandleGainingForeground()=0;
	virtual void HandleLosingForeground()=0;
private:
	IMPORT_C virtual void MCoeForegroundObserver_Reserved_1();
	IMPORT_C virtual void MCoeForegroundObserver_Reserved_2();
	};

/**
 * The MCoeMessageObserver specifies the interface which enables front-end
 * processors to keep their settings synchronized accross all running instances.
 */
class MCoeMessageObserver
	{
public:
	enum TMessageResponse
		{
		EMessageNotHandled,
		EMessageHandled
		};
public:
	virtual TMessageResponse HandleMessageL(TUint32 aClientHandleOfTargetWindowGroup, TUid aMessageUid, const TDesC8& aMessageParameters)=0;
private:
	IMPORT_C virtual void MCoeMessageObserver_Reserved_1();
	IMPORT_C virtual void MCoeMessageObserver_Reserved_2();
	};

// classes defined in FEPBASE, declared here
class MCoeFepObserver;
typedef void (*TCoeFepObserverFunction)(MCoeFepObserver& aFepObserver);
class CCoeFepParameters; // must derive from CBase
class CCoeFep; // must derive from CBase

/**
 * The CCoeScheduler class implements the active scheduler presupposed by the
 * control environment.
 */ 
class CCoeScheduler : public CBaActiveScheduler
	{
public:
	IMPORT_C CCoeScheduler(CCoeEnv* aCoeEnv);
	IMPORT_C virtual void WaitForAnyRequest();
	IMPORT_C virtual void DisplayError(TInt aError) const;
	inline CCoeEnv* CoeEnv() {return iCoeEnv;}
	TBool Flush() const; // not to be called from outside CONE
	void SetFlush(TBool aFlush); // not to be called from outside CONE
private:
	// from CBaActiveScheduler
	IMPORT_C virtual void Reserved_1();
	IMPORT_C virtual void Reserved_2();
private:
	CCoeEnv* iCoeEnv;
	TBool iFlush;
	};

/**
 * The CCoeEnv class provides an active environment for creating applications and working with controls.
 * It implements active objects and an active scheduler which provide access to the window server and it defines
 * the structure in which the UIs for application programs are realised. The CCoeEnv class also provides utility
 * functions that are useful to many applications. 
 */
class CCoeEnv : public CActive
	{
public:
	IMPORT_C ~CCoeEnv();
	IMPORT_C CCoeEnv();
	IMPORT_C virtual void DestroyEnvironment();
	IMPORT_C CCoeAppUiBase* SetAppUi(CCoeAppUiBase* aAppUi);
	IMPORT_C void ExecuteD();
	IMPORT_C void RunL();
	IMPORT_C void DoCancel();
	IMPORT_C virtual void HandleError(TInt aError);
	IMPORT_C void ConstructL();
	IMPORT_C void ConstructL(TBool aInitialFocusState);
	inline const TWsEvent& LastEvent() const;
	inline CCoeAppUiBase* AppUi() const;
	inline RFs& FsSession() const;
	inline RWsSession& WsSession() const;
	inline RWindowGroup& RootWin() const;
	inline CWindowGc& SystemGc() const;
	inline const CFont* NormalFont() const;
	inline CWsScreenDevice* ScreenDevice() const;

	IMPORT_C CWindowGc* CreateGcL();
	IMPORT_C void Flush(TTimeIntervalMicroSeconds32 aDelay=0);
	IMPORT_C CFbsFont* CreateDeviceFontL(CGraphicsDevice* aDevice,const TFontSpec& aFontSpec);
	IMPORT_C CFbsFont* CreateScreenFontL(const TFontSpec& aFontSpec);
	IMPORT_C void ReleaseScreenFont(CFont* aFont) const;
	IMPORT_C void CreateResourceReaderLC(TResourceReader& aReader,TInt aResourceId) const;
	inline void ReadResource(TDes& aDes,TInt aResourceId) const; 
	inline  HBufC* AllocReadResourceL(TInt aResourceId) const;
	inline HBufC* AllocReadResourceLC(TInt aResourceId) const;
	IMPORT_C TInt AddResourceFileL(const TDesC& aFileName);
	IMPORT_C void DeleteResourceFile(TInt aOffset);
	inline CDesCArrayFlat* ReadDesCArrayResourceL(TInt aResourceId);
	IMPORT_C void LeaveWithErrorText(const TDesC& aMsg,const TDesC* aContextText=NULL);
	IMPORT_C void Format128(TDes& aDes,TInt aResourceId,...);
	IMPORT_C void Format256(TDes& aDes,TInt aResourceId,...);
	IMPORT_C static TVersion Version();
	IMPORT_C static CCoeEnv* Static();
	IMPORT_C void SimulateKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	IMPORT_C TBool IsWservEventPending() const;
	IMPORT_C TBool IsRedrawEventPending() const;
	IMPORT_C void PrepareToExit();
	IMPORT_C void BringOwnerToFront();
	IMPORT_C void ReadResourceAsDes8(TDes8& aDes,TInt aResourceId) const;
	IMPORT_C HBufC8* AllocReadResourceAsDes8L(TInt aResourceId) const;
	IMPORT_C HBufC8* AllocReadResourceAsDes8LC(TInt aResourceId) const;
	IMPORT_C CDesC8ArrayFlat* ReadDesC8ArrayResourceL(TInt aResourceId);
	IMPORT_C void SuppressNextFlush();
	IMPORT_C void ReadResourceAsDes16(TDes16& aDes,TInt aResourceId) const; // not available before Release 005
	IMPORT_C HBufC16* AllocReadResourceAsDes16L(TInt aResourceId) const; // not available before Release 005
	IMPORT_C HBufC16* AllocReadResourceAsDes16LC(TInt aResourceId) const; // not available before Release 005
	IMPORT_C CDesC16ArrayFlat* ReadDesC16ArrayResourceL(TInt aResourceId); // not available before Release 005
	IMPORT_C void AddObserverOfLoadedFepL(MCoeObserverOfLoadedFep& aObserverOfLoadedFep); // not available before Release 005
	IMPORT_C void RemoveObserverOfLoadedFep(MCoeObserverOfLoadedFep& aObserverOfLoadedFep); // not available before Release 005
	IMPORT_C void AddFocusObserverL(MCoeFocusObserver& aFocusObserver); // not available before Release 005
	IMPORT_C void RemoveFocusObserver(MCoeFocusObserver& aFocusObserver); // not available before Release 005
	IMPORT_C void SyncNotifyFocusObserversOfChangeInFocus();
	void NotifyFocusObserversOfDestructionOfFocusedItem(); // not to be called from outside CONE
	IMPORT_C void AddForegroundObserverL(MCoeForegroundObserver& aForegroundObserver); // not available before Release 005
	IMPORT_C void RemoveForegroundObserver(MCoeForegroundObserver& aForegroundObserver); // not available before Release 005
	void NotifyForegroundObserversOfGainingForeground(); // not to be called from outside CONE
	void NotifyForegroundObserversOfLosingForeground(); // not to be called from outside CONE
	IMPORT_C void AddMessageObserverL(MCoeMessageObserver& aMessageObserver); // not available before Release 005
	IMPORT_C void RemoveMessageObserver(MCoeMessageObserver& aMessageObserver); // not available before Release 005
	IMPORT_C void AddFepObserverL(MCoeFepObserver& aFepObserver); // not available before Release 005
	IMPORT_C void RemoveFepObserver(MCoeFepObserver& aFepObserver); // not available before Release 005
	IMPORT_C void ForEachFepObserverCall(TCoeFepObserverFunction aFepObserverFunction); // not available before Release 005
	void LoadFepL(); // not to be called from outside CONE
	void LoadFepL(const TDesC& aFileNameOfFepDll); // not to be called from outside CONE
	IMPORT_C void InstallFepL(const TDesC& aFileNameOfFepDll); // not available before Release 005
	IMPORT_C HBufC* NameOfInstalledFepL(); // not available before Release 005
	IMPORT_C MDesCArray* FileNamesOfAvailableFepsL(); // not available before Release 005
	IMPORT_C void ExecuteFepSettingsDialogL(const TDesC& aFileNameOfFepDll); // not available before Release 005
	IMPORT_C CCoeFep* Fep() const; // not available before Release 005
	IMPORT_C TUid FepUid() const; // not available before Release 006
	IMPORT_C CWindowGc* SwapSystemGc(CWindowGc* aGc); // not available before Release 005
	IMPORT_C static CCoeStatic* Static(TUid aUid);
	IMPORT_C void DisableExitChecks(TBool aDisable);
	IMPORT_C void InputCapabilitiesChanged(); // not available before Release 6.1
public: // *** Do not use! API liable to change ***
	IMPORT_C CCoeFepParameters* FepParameters();
public: // Internal to Symbian
	IMPORT_C void GetMessageNotifyingObserversLC(TUint32 aClientHandleOfTargetWindowGroup, TUid& aMessageUid, TPtr8& aMessageParameters, const TWsEvent& aMessageEvent);
protected: // Internal to Symbian
	IMPORT_C void SetUpFepL(CCoeFepParameters* aFepParameters, const TDesC& aFileNameOfDefaultFepDll);
private: // reserved virtual function space
	IMPORT_C virtual void Reserved_1();
	IMPORT_C virtual void Reserved_2();
public: // but not exported
	void ReadEvent();
	CVwsSessionWrapper* InitViewServerSessionL(MVwsSessionWrapperObserver& aObserver);
	void AddStatic(CCoeStatic* aStatic);
	CCoeStatic* RemoveStatic(TUid aUid);
	void QueueNotificationToFocusObserversOfChangeInFocus();
	TInt FocusObserverNotificationIdentifier() const;
	TBool FocusObserverNotificationIsStillPending(TInt aFocusObserverNotificationIdentifier) const;
protected:
	IMPORT_C virtual void DestroyScreen();
	inline TDes& ErrorText();
	inline TDes& ErrorContextText();
private:
	IMPORT_C virtual void InitSystemFontsL();
	IMPORT_C virtual TInt ResourceFileVersionNumber() const;
	void CreateActiveSchedulerL();
	void ConnectToFileServerL();
	void ConnectToWindowServerL();
	void InitScreenL();
	void InitRootWindowL(TBool aInitialFocusState);
	void InitSystemGcL();
	RResourceFile& ResourceFileForId(TInt aResourceId) const;
	void DestroyAllResourceFiles();
	void AddObserverL(TAny* aObserver, RGenericPointerArray& aArray);
	void RemoveObserver(TAny* aObserver, RGenericPointerArray& aArray);
	inline TBool DisableShutdownChecks() const;
	void UpdateStatic(CCoeAppUiBase* aNewAppUi);
	void SetInitialHandleCount();
	inline TUint InitialHandleCount() const;
protected:
	CCoeAppUiBase* iAppUi;
	RFs iFsSession;
	RWsSession iWsSession;
	RWindowGroup iRootWin;
	CWindowGc* iSystemGc;
	const CFont* iNormalFont;
	CWsScreenDevice* iScreen;
	TWsEvent iLastEvent;
	CArrayFix<RResourceFile>* iResourceFileArray;
	enum {KErrorTextLength = 80};
private:
	enum TFlags
		{ ENoShutdownChecks	=0x01 };
private:
	TDes* iErrorText;
	TDes* iErrorContextText;
	CCoeEnvExtra* iExtra;
	CTrapCleanup* iCleanup;
	TUint iEnvFlags;
	};

/**
 * The CCoeStatic class provides a baseclass for creating singleton objects that will be stored by CCoeEnv.
 * Each object must have a unique uid
 */
class CCoeStatic : public CBase
	{
public:
	enum TScope
		{EThread,EApp};
public:
	IMPORT_C ~CCoeStatic();
protected:
	IMPORT_C CCoeStatic(TUid aUid,TScope=EThread);
private:
	TDblQueLink iCsLink;
	TUid iCsUid;
	CCoeAppUiBase* iCsAppUi;
	TScope iCsScope;
private:
	friend class CCoeEnv;
	friend class CCoeEnvExtra;
	};


/**
 * Returns the most recent standard event that was received by the application.
 */
inline const TWsEvent& CCoeEnv::LastEvent() const
	{ return(iLastEvent); }
/**
 * Returns a pointer to the app UI owned by the application.
 */
inline CCoeAppUiBase* CCoeEnv::AppUi() const
	{ return(iAppUi); }
/**
 * Returns a reference to the file server session opened by the application.
 */
inline RFs& CCoeEnv::FsSession() const
	{ return((RFs&)iFsSession); }
/**
 * Returns a reference to the window server session opened by the application. 
 */
inline RWsSession& CCoeEnv::WsSession() const
	{ return((RWsSession&)iWsSession); }
/**
 * Returns a reference to the window server session owned by the application. 
 */	
inline RWindowGroup& CCoeEnv::RootWin() const
	{ return((RWindowGroup&)iRootWin); }
/**
 * Returns a reference to the system graphics context.
 */		
inline CWindowGc& CCoeEnv::SystemGc() const
	{ return((CWindowGc&)*iSystemGc); }
/**
 * Returns a pointer to the normal environment font.
 */		
inline const CFont* CCoeEnv::NormalFont() const
	{ return(iNormalFont); }
/**
 * Returns a pointer to the default screen device owned by the application. Does not
 * imply transfer of ownership.
 */		
inline CWsScreenDevice* CCoeEnv::ScreenDevice() const
	{ return(iScreen); }
/**
 * Returns a reference to the current error message text. 
 */
inline TDes& CCoeEnv::ErrorText() 
	{ return *iErrorText; }
/**
 * Returns a reference to the current error context text. 
 */	
inline TDes& CCoeEnv::ErrorContextText() 
	{ return *iErrorContextText; }

#if defined(_UNICODE)
/**
 * Reads a resource identified by aResourceId into the descriptor aDes. The descriptor must
 * be long enough to contain the entire resource. No memory is allocated by this function.
 *
 * Leaves with an error code of KErrExtended, and sets the active scheduler’s extended
 * error number to KErrCoeFailedToReadFromProgDisk, if the read fails.
 */
inline void CCoeEnv::ReadResource(TDes& aDes,TInt aResourceId) const
	{ ReadResourceAsDes16(aDes,aResourceId); }
/**
 * Reads a resource identified by aResourceId into a heap descriptor, allocating memory as
 * required. Returns a pointer to the descriptor and transfers ownership. 
 */
inline  HBufC* CCoeEnv::AllocReadResourceL(TInt aResourceId) const
	{ return AllocReadResourceAsDes16L(aResourceId); }
/**
 * Reads a resource identified by aResourceId into a heap descriptor, allocating memory as
 * required. Returns a pointer to the descriptor and leaves the pointer on the clean up stack.
 */
inline HBufC* CCoeEnv::AllocReadResourceLC(TInt aResourceId) const
	{ return AllocReadResourceAsDes16LC(aResourceId); }
/**
 * Reads a resource identified by aResourceId into a a descriptor array.  Returns a pointer
 * to the descriptor array and transfers ownership. 
 */
inline CDesCArrayFlat* CCoeEnv::ReadDesCArrayResourceL(TInt aResourceId)
	{ return ReadDesC16ArrayResourceL(aResourceId); }
#else  // not UNICODE
inline void CCoeEnv::ReadResource(TDes& aDes,TInt aResourceId) const
	{ ReadResourceAsDes8(aDes,aResourceId); }
inline  HBufC* CCoeEnv::AllocReadResourceL(TInt aResourceId) const
	{ return AllocReadResourceAsDes8L(aResourceId); }
inline HBufC* CCoeEnv::AllocReadResourceLC(TInt aResourceId) const
	{ return AllocReadResourceAsDes8LC(aResourceId); }
inline CDesCArrayFlat* CCoeEnv::ReadDesCArrayResourceL(TInt aResourceId)
	{ return ReadDesC8ArrayResourceL(aResourceId); }
#endif // UNICODE

#endif
