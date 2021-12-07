/*
* ============================================================================
*  Name     : AknEnv.h
*  Part of  : Avkon
*
*  Description:
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/
#if !defined(__AVKON_ENV_H__)
#define __AVKON_ENV_H__

#include <eikenv.h>
#include <eiksbfrm.h>
#include <eikcba.h>
#include <eikmobs.h>
#include <eikmenub.h>
#include <coeaui.h>

class MAknEditingStateIndicator;
class MAknIntermediateState;
class CAknAppUi;
class CAknWaitDialog;
class CEikListBox;

class CAknEnv : public CBase
	{
public:
	IMPORT_C static CAknEnv* Static();
	IMPORT_C ~CAknEnv();
public:
	// this one creates an empty dialog. for list queries and popup lists with "No Data" in it.
	IMPORT_C void ExecuteEmptyPopupListL(const TDesC *aEmptyText=0);
	IMPORT_C void ExecuteEmptyPopupListL(const TDesC *aEmptyText, const TDesC *aTitle, TInt aSoftkeyId=0);

public:
	IMPORT_C void SetFepMenuObserver(MEikMenuObserver* aObserver);
	IMPORT_C MEikMenuObserver* FepMenuObserver();
	IMPORT_C MAknEditingStateIndicator* EditingStateIndicator();
	IMPORT_C MAknEditingStateIndicator* SwapEditingStateIndicator(MAknEditingStateIndicator* aIndicator);
	IMPORT_C static void ExitForegroundAppL();

public: // Intermediate states support
	IMPORT_C void RegisterIntermediateStateL(MAknIntermediateState *aState);
	IMPORT_C void UnRegisterIntermediateState(MAknIntermediateState *aState);
	IMPORT_C void CloseAllIntermediateStates();

public:
	IMPORT_C static void RunAppShutter();
	IMPORT_C static CAknAppUi* AppWithShutterRunning();
	IMPORT_C static void StopSchedulerWaitWithBusyMessage(CActiveSchedulerWait& aWait);

public:
	IMPORT_C void CreateCbaObserverL(CEikButtonGroupContainer *aCba, CEikListBox *aListBox);
	IMPORT_C void RemoveCbaObserver();
	IMPORT_C void InformCbaDeletion(CEikButtonGroupContainer *aCba);

private:
	static TInt RealCloseIntermediateStates(TAny *aEnv);
	static TInt SchedulerStoppedCallBack(TAny* aWaitNote);
	void DoSchedulerStoppedCallBack();

private:
	friend class CAknDllInitializer;
	IMPORT_C CAknEnv();
	IMPORT_C void ConstructL();

private:
	MEikMenuObserver* iFepMenuObserver;
	MAknEditingStateIndicator* iEditStateIndicator;
private:
	CArrayPtr<MAknIntermediateState> *iStateArray;
	CArrayPtr<CBase> *iDeleteArray;
	CIdle *iIdle;
	CAknWaitDialog* iBusyMsgDialog;
	TInt iBusyMsgCount;
	MEikCommandObserver *iCbaCommandObserver;
	};


#define iAvkonEnv (STATIC_CAST(CAknEnv*,iEikonEnv->Extension()))
#define AVKONENV (STATIC_CAST(CAknEnv*, CEikonEnv::Static()->Extension()))

#endif
