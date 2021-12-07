// EIKSRVS.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKSRVS_H__)
#define __EIKSRVS_H__

#if !defined(__EIKAPPUI_H__)
#include <eikappui.h>
#endif

#if !defined(__EIKENV_H__)
#include <eikenv.h>
#endif

#if !defined(__EIKSRV_PAN__)
#include <eiksrv.pan>
#endif

#if !defined(__APGTASK_H__)
#include <apgtask.h>
#endif

#if !defined(__EIKSRV_H__)
#include <eiksrv.h>
#endif

class CDictionaryFileStore;
_LIT(EIKAPPUI_SERVER_NAME,"EikAppUiServer");
_LIT(EIKAPPUI_SERVER_SEMAPHORE,"EikAppUiServerStartSemaphore");
const TUint KEikSrvDefaultHeapSize=0x10000; 



enum TEikUiOpCode
    {
	EEikAppUiNotifyAlarmServerOfTaskChange,
	EEikAppUiLaunchTaskList,
	EEikAppUiCycleTasks,
	EEikAppUiAddToStack,
	EEikAppUiRemoveFromStack,
	EEikAppUiExecuteD,
	EEikAppUiSetStatusPaneFlags,
	EEikAppUiSetStatusPaneLayout,
	EEikAppUiNotifer,
	EEikAppUiBlankScreen,
	EEikAppUiUnblankScreen,
	EEikAppUiShutdownApps,
	EEikAppUiEnableTaskList,
	EEikAppUiSetSgcParams,
	EEikAppUiBlockServerStatusPaneRedraws,
	EEikAppUiRedrawServerStatusPane,
	EEikAppUiPrepareForAppExit,
	EEikAppUiSetSystemFaded,
	EEikAppUiIsSystemFaded
	};
enum TEikAppUiServPanic
	{
	EEikSrvDefault,
	EEikSrvSvrCreateServer,
	EEikSrvSvrStartServer,
	EEikSrvSrvNotFound
	};
	
struct SStartThreadArg
	{
	//empty
	};


// function to panic the server
GLREF_C void PanicServer(TEikAppUiServPanic aPanic);

class TLaunchServer
	{
public:
	virtual void LaunchL(RLibrary* aLibrary)=0;
	};
      
#endif
