/*
* ============================================================================
*  Name     : AknAppUi.h
*  Part of  : Avkon
*
*  Description:
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/
#ifndef __AKNAPPUI_H__
#define __AKNAPPUI_H__

#include <eikappui.h>
#include <Eikspane.h>
#include <eikcba.h>
#include <avkon.hrh>

class CEikButtonGroupContainer;
class CAknAppShutter;

#define iAvkonAppUi ((CAknAppUi*)CEikonEnv::Static()->EikAppUi())


class CAknAppUi : public CEikAppUi, MEikStatusPaneObserver, public MCoeViewDeactivationObserver
    {
public:
	IMPORT_C void BaseConstructL(TInt aAppUiFlags=0);
	IMPORT_C ~CAknAppUi();

	IMPORT_C CEikStatusPane* StatusPane();
	IMPORT_C CEikButtonGroupContainer* Cba();

	IMPORT_C void ProcessCommandL(TInt aCommand);
	IMPORT_C CAknKeySoundSystem* KeySounds();

    IMPORT_C TErrorHandlerResponse HandleError (TInt aError, const SExtendedError& aExtErr, TDes& aErrorText, TDes& aContextText); 

	IMPORT_C void RunAppShutter();
	IMPORT_C TBool IsAppShutterRunning() const;

public: // MCoeViewDeactivationObserver
	IMPORT_C virtual void HandleViewDeactivation(const TVwsViewId& aViewIdToBeDeactivated, const TVwsViewId &aNewlyActivatedViewId);

public: // from CCoeAppUiBase
	IMPORT_C void PrepareToExit();

protected:
	// from MEikStatusPaneObserver
	IMPORT_C void HandleStatusPaneSizeChange();

	// from CCoeAppUi
	IMPORT_C void HandleSystemEventL(const TWsEvent& aEvent);

protected: // formerly from MTopSetMember<CEikMenuBar>, now reserved
	IMPORT_C virtual void Reserved_MtsmPosition();
	IMPORT_C virtual void Reserved_MtsmObject();
protected:
    IMPORT_C void HandleForegroundEventL(TBool aForeground);
	IMPORT_C void HandleWsEventL(const TWsEvent& aEvent,CCoeControl* aDestination);

	IMPORT_C void SetKeyBlockMode(TAknKeyBlockMode aMode);

#ifdef _DEBUG
	void DumpControl(CCoeControl* aControl, TInt aLevel, RDebug& aDebug);
#endif
    void DecideWsClientBufferSizesL();

private:
	void UpdateKeyBlockMode();
	void HandleErrorL(TInt aError);

private:
	TBool iDumpNextControl;
	CAknAppShutter* iAppShutter;	// May be set to NULL by the app shutter itself
	TAknKeyBlockMode iBlockMode;
	TInt iSpare;
    };


#endif







