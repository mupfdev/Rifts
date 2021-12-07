// COEAUI.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__COEAUI_H__)
#define __COEAUI_H__

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

#if !defined(__W32STD_H__)
#include <w32std.h>
#endif

#if !defined(__VWSDEF_H__)
#include <vwsdef.h>
#endif

#if !defined(__COEDEF_H__)
#include <coedef.h>
#endif

#if !defined(__COEAUIB_H__)
#include <coeauib.h>
#endif

#if !defined(__COEHELP_H__)
#include <coehelp.h>
#endif

#if !defined(__COEVIEW_H__)
#include <coeview.h>
#endif

#if !defined(__COEINPUT_H__)
#include <coeinput.h>
#endif

class CCoeEnv;
class CCoeControl;

enum
	{
	ECoeStackPriorityDefault=0,
	ECoeStackPriorityMenu=10,
	ECoeStackPriorityDialog=50,
	ECoeStackPriorityCba=60,
	ECoeStackPriorityAlert=200,
	ECoeStackPriorityFep=250,
	ECoeStackPriorityEnvironmentFilter=300
	};

enum
	{
	ECoeStackFlagStandard			= 0, // the default value
	ECoeStackFlagRefusesAllKeys		= 0x01,
	ECoeStackFlagRefusesFocus		= 0x02,
	ECoeStackFlagOwnershipTransfered= 0x04,
	ECoeStackFlagSharable			= 0x08
	};

class CCoeControlStack;
class CCoeViewManager;
class MCoeViewDeactivationObserver;
class MCoeViewActivationObserver;
class MCoeViewObserver;

/**
 * The CCoeAppUi class is the standard, general purpose, application user interface class
 * used by most applications. 
 */
class CCoeAppUi : public CCoeAppUiBase
	{
public:
	IMPORT_C CCoeAppUi();
	IMPORT_C ~CCoeAppUi();
	IMPORT_C void ConstructL(CCoeAppUi* aPrevious=NULL);
public: // new functions
	IMPORT_C void AddToStackL(CCoeControl* aControl,TInt aPriority=ECoeStackPriorityDefault,TInt aStackingFlags=ECoeStackFlagStandard);
	IMPORT_C void RemoveFromStack(CCoeControl* aControl);
	IMPORT_C void UpdateStackedControlFlags(CCoeControl* aControl,TInt aFlags,TInt aMask);
	IMPORT_C void HandleStackChanged();
	IMPORT_C TBool IsDisplayingMenuOrDialog() const; 
	IMPORT_C TBool IsDisplayingDialog() const; 
	IMPORT_C TBool IsDisplayingControlBetweenPriorities(TInt aLowerPriority, TInt aHigherPriority) const;
	IMPORT_C CArrayFix<TCoeHelpContext>* AppHelpContextL() const;
	IMPORT_C virtual TCoeInputCapabilities InputCapabilities() const;
	IMPORT_C void HandleStackedControlsResourceChange(TInt aType);
	IMPORT_C void ActivateViewL(const TVwsViewId& aViewId);
	IMPORT_C void ActivateViewL(const TVwsViewId& aViewId,TUid aCustomMessageId,const TDesC8& aCustomMessage);
	IMPORT_C void RegisterViewL(MCoeView& aView);
	IMPORT_C void DeregisterView(const MCoeView& aView);
	IMPORT_C void SetDefaultViewL(const MCoeView& aView);
	IMPORT_C TInt GetDefaultViewId(TVwsViewId& aViewId) const;
	IMPORT_C TInt GetActiveViewId(TVwsViewId& aViewId) const;
	IMPORT_C void AddToStackL(const MCoeView& aView,CCoeControl* aControl,TInt aPriority=ECoeStackPriorityDefault,TInt aStackingFlags=ECoeStackFlagStandard);
public: // but not exported
	TBool IsControlOnStack(CCoeControl* aControl) const;
	void SetCurrentControlStackGroupId(TInt aGroupId);
public: // Internal to Symbian
	IMPORT_C void CreateActivateViewEventL(const TVwsViewId& aViewId,TUid aCustomMessageId,const TDesC8& aCustomMessage);
	IMPORT_C void ActivateTopViewL();
	IMPORT_C void DeactivateActiveViewL();
	IMPORT_C void RegisterApplicationViewL(TUid aAppUid);
	IMPORT_C void DeregisterApplicationView();
	IMPORT_C void CheckInitializeViewsL(TUid aAppUid);
	IMPORT_C void SetApplicationViewAsDefaultL();
	IMPORT_C void AddViewDeactivationObserverL(MCoeViewDeactivationObserver* aViewDeactivationObserver);
	IMPORT_C void RemoveViewDeactivationObserver(MCoeViewDeactivationObserver* aViewDeactivationObserver);
	IMPORT_C void NotifyNextDeactivation(const TVwsViewId& aViewId, MCoeViewDeactivationObserver& aViewDeactivationObserver);
	IMPORT_C void NotifyNextDeactivation(MCoeViewDeactivationObserver& aViewDeactivationObserver);
	IMPORT_C void AddViewActivationObserverL(MCoeViewActivationObserver* aViewActivationObserver);
	IMPORT_C void RemoveViewActivationObserver(MCoeViewActivationObserver* aViewActivationObserver);
	IMPORT_C void NotifyNextActivation(const TVwsViewId& aViewId, MCoeViewActivationObserver& aViewActivationObserver);
	IMPORT_C void NotifyNextActivation(MCoeViewActivationObserver& aViewActivationObserver);
	IMPORT_C void AddViewObserverL(MCoeViewObserver* aViewObserver);
	IMPORT_C void RemoveViewObserver(MCoeViewObserver* aViewObserver);
	IMPORT_C void WriteInternalStateOfStackedControlsL(RWriteStream& aWriteStream) const;
public: // deprecated
	IMPORT_C void RegisterViewAndAddStackL(MCoeView& aView);
	IMPORT_C void DeregisterViewAndRemoveStack(const MCoeView& aView);
	IMPORT_C void RemoveFromViewStack(const MCoeView& aView,CCoeControl* aControl);
	IMPORT_C void UpdateViewStackedControlFlags(const MCoeView& aView,CCoeControl* aControl,TInt aFlags,TInt aMask);
	IMPORT_C void AddToViewStackL(const MCoeView& aView,CCoeControl* aControl,TInt aPriority=ECoeStackPriorityDefault,TInt aStackingFlags=ECoeStackFlagStandard);
protected: // from CCoeAppUiBase
	IMPORT_C void HandleWsEventL(const TWsEvent& aEvent,CCoeControl* aDestination);
	IMPORT_C void Reserved_1();
	IMPORT_C void Reserved_2();
private: // new functions
	IMPORT_C virtual TKeyResponse HandleKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	IMPORT_C virtual void HandleForegroundEventL(TBool aForeground);
	IMPORT_C virtual void HandleSwitchOnEventL(CCoeControl* aDestination);
	IMPORT_C virtual void HandleSystemEventL(const TWsEvent& aEvent);
	IMPORT_C virtual void HandleApplicationSpecificEventL(TInt aType,const TWsEvent& aEvent);
	IMPORT_C virtual void SetAndDrawFocus(TBool aFocus);
	IMPORT_C virtual CArrayFix<TCoeHelpContext>* HelpContextL() const;
private:
	enum TRemoveCondition
		{
		ERemoveUnconditionally,
		ERemoveOnlyIfSharable
		};
private:
	CCoeControl* TopFocusableControl() const;
	CCoeControl* TopFocusedControl() const;
	TInt FindPos(CCoeControlStack* aStack,CCoeControl* aControl) const;
	void SetFocusToControl(CCoeControl* aControl,TBool aFocus);
	void DoAddToStackL(CCoeControlStack* aStack,CCoeControl* aControl,TInt aPriority,TInt aStackingFlags);
	void DoAddToStackL(CCoeControlStack* aStack,CCoeControl* aControl,TInt aPriority,TInt aStackingFlags, TInt aGroupId);
	void DoRemoveFromStack(CCoeControlStack* aStack,CCoeControl* aControl,TRemoveCondition aRemoveCondition=ERemoveUnconditionally);
	void DoUpdateStackedControlFlags(CCoeControlStack* aStack,CCoeControl* aControl,TInt aFlags,TInt aMask);
private:
	class CExtra;
	friend class CExtra;
	friend class CTestDriver;
protected:
	CCoeEnv* iCoeEnv;
private:
	CCoeViewManager* iViewManager;
	CCoeControlStack* iStack;
	CExtra* iExtra;
	};


/**
 * The MCoeViewDeactivationObserver class specifies an interface through which view deactivations can be
 * notified to an observer. Dialogs and other floating windows such as virtual keyboards which should be dismissed
 * when a view is deactivated can implement this interface and take any action required.
 *
 * @since Uikon1.2
 * @internal
 * Internal to Symbian
 */
class MCoeViewDeactivationObserver
	{
public:

	/**
	 * Handles the deactivation of the view identified by aViewIdToBeDeactivated before the newly activated
	 * view with id aNewlyActivatedViewId is marked as current.
	 */
	virtual void HandleViewDeactivation(const TVwsViewId& aViewIdToBeDeactivated,const TVwsViewId& aNewlyActivatedViewId)=0;

private:
	IMPORT_C virtual void MCoeViewDeactivationObserver_Reserved_1();
	IMPORT_C virtual void MCoeViewDeactivationObserver_Reserved_2();
	};


/**
 * The MCoeViewActivationObserver class specifies an interface through which view activations can be
 * notified to an observer.
 *
 * @since Uikon1.2
 * @internal
 * Internal to Symbian
 */
class MCoeViewActivationObserver
	{
public:

	/**
	 * Handles the activation of the view aNewlyActivatedViewId before the old view aViewIdToBeDeactivated is
	 * to be deactivated.
	 */
	virtual void HandleViewActivation(const TVwsViewId& aNewlyActivatedViewId,const TVwsViewId& aViewIdToBeDeactivated)=0;

private:
	IMPORT_C virtual void MCoeViewActivationObserver_Reserved_1();
	IMPORT_C virtual void MCoeViewActivationObserver_Reserved_2();
	};


/**
 * The MCoeViewObserver class specifies an interface through which view events can be notified to an observer.
 *
 * @since Uikon1.2
 * @internal
 * Internal to Symbian
 */
class MCoeViewObserver
	{
public:
	virtual void HandleViewEventL(const TVwsViewEvent& aEvent)=0;
	};


#endif
