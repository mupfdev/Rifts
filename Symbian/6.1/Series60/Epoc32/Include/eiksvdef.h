// EIKSVDEF.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKSVDEF_H__)
#define __EIKSVDEF_H__

enum
	{
	KExternalKeyModifier=0,
	KExternalKey1=EKeyDictaphoneStop,
	KExternalKey2=EKeyDictaphonePlay,
	KExternalKey3=EKeyDictaphoneRecord,
	KExternalKeyModifierMask=EAllStdModifiers|EModifierFunc
	};

const TUid KUidExternalKeyHandlerAppStream={0x10000117};
const TUid KUidDictaphoneFileStream={0x100001CF};

_LIT(__EIKON_SERVER_NAME,"EikonServer");

enum TEikServEvent
	{
	EEikServExit,
	EEikServChangePasswordMode,
	EEikServShowTaskList,
	EEikServHideTaskList,
	};

enum { KNumOfSideButtons=5, KNumOfAppButtons=9 };

_LIT(EIKON_SERVER_BACKDROP_WINDOW_GROUP_NAME,"EiksrvBackdrop");

const TInt KAknKeyboardRepeatInitialDelay = 600000;
const TInt KAknStandardKeyboardRepeatRate = (1000000/6);
const TInt KAknEditorKeyboardRepeatRate = (1000000/10);

#endif
