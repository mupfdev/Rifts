// PLPBAKMS.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__PLPBAKMS_H__)
#define __PLPBAKMS_H__

#define __BACKUP_SERVER_NAME _L("BackupServer")

const TInt KBakMajorVN		=0;
const TInt KBakMinorVN		=1;
const TInt KBakBuildVN		=1; // ??
const TInt KBakMessageSlots	=0;		// no async messages to backup server

enum TBakOpCode
	{
	EBakOpCodePrepareForBackup,
	EBakOpCodeBackupComplete,
	//
	EBakOpCodeAppListOpen,
	EBakOpCodeAppListRead,
	EBakOpCodeAppListClose,
	//
	EBakOpCodeDocStop,
	EBakOpCodeDocIsOpen,
	//
	EBakOpCodeStartDocument,
	EBakOpCodeStartApplication,
	//
	EBakOpCodeOwnerInfo,
	EBakOpCodeAppStop,
	EBakOpCodeAppIsRunning,
	EBakOpCodeDetailsFromApp,
	};
								
#endif