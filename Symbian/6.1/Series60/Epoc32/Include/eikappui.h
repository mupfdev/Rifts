// EIKAPPUI.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKAPPUI_H__)
#define __EIKAPPUI_H__

#if !defined(__COEAUI_H__)
#include <coeaui.h>
#endif

#if !defined(__COEMAIN_H__)
#include <coemain.h>
#endif

#if !defined(__EIKMOBS_H__)
#include <eikmobs.h>
#endif

#if !defined(__APADEF_H__)
#include <apadef.h>
#endif

#if !defined(__VWSDEF_H__)
#include <vwsdef.h>
#endif

#if !defined(__EIKDEF_H__)
#include <eikdef.h>
#endif

#if !defined(__BAERRHAN_H__)
#include <baerrhan.h>
#endif

#if !defined(__EIKAUFTY_H__)
#include <eikaufty.h>
#endif

#if !defined(__AKNWSEVENTOBSERVER_H__)
#include <AknWsEventObserver.h>
#endif

#include <coemop.h>

class MEikMenuBar;
class MEikMenuPane;
class CEikDocument;
class CEikApplication;
class MApaEmbeddedDocObserver;
struct SExtendedError;
class MEikAppUiFactory;
class CAknKeySoundSystem;

const TUid KUidEikColorSchemeStore={0x1};
const TUid KUidEikColorSchemeStream={0x1};

class CEikAppUi : public CCoeAppUi, public MEikMenuObserver, public MCoeMessageObserver, public MObjectProvider
	{
public:
	IMPORT_C ~CEikAppUi();
	IMPORT_C CEikAppUi();
public: // new functions
	IMPORT_C virtual void ConstructL();
	IMPORT_C virtual void HandleModelChangeL();
	IMPORT_C void LaunchPopupMenuL(TInt aResourceId,const TPoint& aTargetPos,TPopupTargetPosType aTargetType,const CEikHotKeyTable* aHotKeyTable=NULL);
	inline CEikAppUi* ContainerAppUi() const;
	IMPORT_C void SetDocument(CEikDocument* aDocument);
	IMPORT_C void SetEmbeddedDocInfo(MApaEmbeddedDocObserver* aObserver,TBool aReadOnly);
	IMPORT_C virtual TBool ProcessCommandParametersL(TApaCommand aCommand,TFileName& aDocumentName,const TDesC8& aTail);
	IMPORT_C CEikDocument* Document() const;
	IMPORT_C CEikApplication* Application() const;
	IMPORT_C TRect ClientRect() const;
	IMPORT_C TRect ApplicationRect() const;
	IMPORT_C virtual void StopDisplayingMenuBar();
	IMPORT_C TBool FadeWhenInBackground();
	IMPORT_C void SetFaded(TBool aFade);
	IMPORT_C TBool IsFaded() const;
public: // new function
	IMPORT_C void ReportResourceChangedToAppL(TInt aType);
	IMPORT_C virtual void HandleCommandL(TInt aCommand);
	IMPORT_C virtual void ProcessMessageL(TUid aUid,const TDesC8& aParams);
	IMPORT_C virtual void OpenFileL(const TDesC& aFileName);
	IMPORT_C virtual void CreateFileL(const TDesC& aFileName);
	IMPORT_C virtual TErrorHandlerResponse HandleError(TInt aError,const SExtendedError& aExtErr,TDes& aErrorText,TDes& aContextText);
	IMPORT_C virtual void HandleResourceChangeL(TInt aType);
	IMPORT_C TBool IsForeground() const;
	IMPORT_C TBool IsPartialForeground() const;
	IMPORT_C TBool IsFullScreenApp() const;
// Added for Avkon. Access method for the event monitor
	IMPORT_C CAknWsEventMonitor* EventMonitor() const;
	IMPORT_C CAknKeySoundSystem* KeySounds() const;
public: // from CCoeAppUiBase
	IMPORT_C void PrepareToExit();
protected: // new functions
	IMPORT_C void BaseConstructL(TInt aAppUiFlags=0);
	IMPORT_C void ReadAppInfoResourceL(TInt aResourceFileOffset=0);
	IMPORT_C void CreateHotKeyControlL(TInt aResourceId);
	IMPORT_C void SetDocChanged();
	IMPORT_C void SaveAnyChangesL();
	IMPORT_C void Exit();
	IMPORT_C void SaveL();
	IMPORT_C void ClosePopup();
	IMPORT_C TBool ProcessCommandParametersL(TApaCommand aCommand,TFileName& aDocumentName);
	IMPORT_C void SetFullScreenApp(TBool aIsFullScreen);
protected: // from MEikMenuObserver
	IMPORT_C void HandleSideBarMenuL(TInt aResourceId,const TPoint& aPos,TInt aModifiers,const CEikHotKeyTable* aTable);
protected: // from CCoeAppUi
	IMPORT_C void HandleApplicationSpecificEventL(TInt aType,const TWsEvent& aEvent); // not available before ER5u
	IMPORT_C void HandleForegroundEventL(TBool aForeground);
	IMPORT_C void HandleWsEventL(const TWsEvent& aEvent, CCoeControl* aDestination);
	IMPORT_C void HandleSystemEventL(const TWsEvent& aEvent);
private: // from MEikCommandObserver
	IMPORT_C void ProcessCommandL(TInt aCommand);
private: // from MEikMenuObserver
	IMPORT_C void SetEmphasis(CCoeControl* aMenuWindow,TBool aEmphasis);
protected: // from MCoeMessageObserver
	IMPORT_C MCoeMessageObserver::TMessageResponse HandleMessageL(TUint32 aClientHandleOfTargetWindowGroup, TUid aMessageUid, const TDesC8& aMessageParameters);
protected: // from MObjectProvider
	IMPORT_C TTypeUid::Ptr MopSupplyObject(TTypeUid aId);
	IMPORT_C MObjectProvider* MopNext();
private: // from CCoeAppUiBase
	IMPORT_C void Reserved_1();
	IMPORT_C void Reserved_2();
private: // new functions
	IMPORT_C virtual TBool ValidFileType(TUid aFileUid) const;
	IMPORT_C virtual void Reserved_3();
	IMPORT_C virtual void Reserved_4();
	void SimulateWsEventL(TInt aEvent);
	TInt FindAppWgIdBelowMeL();
	TInt EventForForegroundState(TBool aPartialFg, TBool aForeground);
	TBool ThreadIsForeground() const;
public:
	enum
		{
		EStandardApp			= 0x00,
		ENoAppResourceFile		= 0x01,
		ENonStandardResourceFile= 0x02,
		ENoScreenFurniture		= 0x04,
		ELastReservedEikAppUiFlag = 0x08
		};
private: // new functions
	void CreateResourceIndependentFurnitureL();
	TBool ValidFileExists(const TDesC& aFileName);
protected:
	CEikDocument* iDocument;
	CEikAppUi* iContainerAppUi;
	MApaEmbeddedDocObserver* iDoorObserver;
	TBool iEmbeddedAndReadOnly;
	TBitFlags iFlags;
	// Added for Avkon. Provides access to keysound server
	CAknKeySoundSystem* iKeySounds;	// Moved from CAknAppUi, because CEikSrvUi needs it as well
private:
	// Added for Avkon. Monitor events for emergency call support
	CAknWsEventMonitor* iEventMonitor;
	MEikAppUiFactory* iFactory;
	TInt iSpare2;	// formerly iFadeCount
	TInt iSpare;
	};

inline CEikAppUi* CEikAppUi::ContainerAppUi() const
	{ return iContainerAppUi; }

#endif
