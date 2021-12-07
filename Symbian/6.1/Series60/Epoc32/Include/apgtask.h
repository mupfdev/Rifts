// APGTASK.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__APGTASK_H__)
#define __APGTASK_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

class RWsSession;
struct TKeyEvent;

enum TApaSystemEvent
	{
	EApaSystemEventShutdown=1,
	EApaSystemEventBackupStarting,
	EApaSystemEventBackupComplete,
	EApaSystemEventBroughtToForeground
	};

#ifdef _UNICODE
#define KUidApaMessageSwitchOpenFile KUidApaMessageSwitchOpenFile16
#define KUidApaMessageSwitchCreateFile KUidApaMessageSwitchCreateFile16
#define KUidApaMessageSwitchOpenFileValue KUidApaMessageSwitchOpenFileValue16
#define KUidApaMessageSwitchCreateFileValue KUidApaMessageSwitchCreateFileValue16
#else
#define KUidApaMessageSwitchOpenFile KUidApaMessageSwitchOpenFile8
#define KUidApaMessageSwitchCreateFile KUidApaMessageSwitchCreateFile8
#define KUidApaMessageSwitchOpenFileValue KUidApaMessageSwitchOpenFileValue8
#define KUidApaMessageSwitchCreateFileValue KUidApaMessageSwitchCreateFileValue8
#endif

const TInt KUidApaMessageSwitchOpenFileValue8=0x10000163;
const TUid KUidApaMessageSwitchOpenFile8={KUidApaMessageSwitchOpenFileValue8};
const TInt KUidApaMessageSwitchOpenFileValue16=0x10003A39;
const TUid KUidApaMessageSwitchOpenFile16={KUidApaMessageSwitchOpenFileValue16};

const TInt KUidApaMessageSwitchCreateFileValue8=0x10000164;
const TUid KUidApaMessageSwitchCreateFile8={KUidApaMessageSwitchCreateFileValue8};
const TInt KUidApaMessageSwitchCreateFileValue16=0x10003A3A;
const TUid KUidApaMessageSwitchCreateFile16={KUidApaMessageSwitchCreateFileValue16};

class TApaTask
	{
public:
	IMPORT_C TApaTask(RWsSession& aWsSession);
	IMPORT_C void SetWgId(TInt aWgId);
	IMPORT_C TInt WgId() const;
	IMPORT_C TBool Exists() const;
	IMPORT_C TThreadId ThreadId() const;
	IMPORT_C void BringToForeground();
	IMPORT_C void SendToBackground();
	IMPORT_C void EndTask();
	IMPORT_C void KillTask();
	IMPORT_C void SendKey(TInt aKeyCode,TInt aModifiers);
	IMPORT_C void SendKey(const TKeyEvent& aKey);
	IMPORT_C void SendSystemEvent(TApaSystemEvent aEvent);
	IMPORT_C TInt SwitchOpenFile(const TDesC& aFilename);
	IMPORT_C TInt SwitchCreateFile(const TDesC& aFilename);
	IMPORT_C TInt SendMessage(TUid aUid, const TDesC8& aParams);
private:
	TInt CheckSwitchFile() const;
private:
	RWsSession& iWsSession;
	TInt iWgId;
	};
	
class TApaTaskList
	{
public:
	enum TCycleDirection {EForwards,EBackwards};
public:
	IMPORT_C TApaTaskList(RWsSession& aWsSession);
	IMPORT_C TApaTask FindApp(const TDesC& aAppName);
	IMPORT_C TApaTask FindDoc(const TDesC& aDocName);
	IMPORT_C TApaTask FindByPos(TInt aPos);
	IMPORT_C TApaTask FindApp(TUid aAppUid);
	IMPORT_C TInt CycleTasks(TUid aAppUid,TCycleDirection aDirection=EForwards);
private:
	void FindByPosL(TApaTask& aTask,TInt aPos);
private:
	RWsSession& iWsSession;
	};


#endif
