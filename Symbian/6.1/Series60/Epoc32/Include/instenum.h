// INSTENUM.H
// Copyright (c) 1997-1999 Symbian Ltd. All rights reserved.
//
// Installer engine enumeration values used throughout:
// - install engine
// - EPOC install application (AppInst.app)
// - PC based installer (EPOCInstall.exe)
//

#if !defined(__INSTENUM_H__)
#define __INSTENUM_H__

enum TInstQuestionDialogType
	{ 
	EInstUIReplaceExisting,
	EInstUIContinuePartial,
	EInstUIShuttingDownApps,
	EInstUIConfirmCancel,	// Note: the install engine doesn't actually use this
	EInstUIIncompatibleApp	// Added for dependency check warning
	};

enum TInstErrorDialogType
	{
	EInstUIAlreadyInRom,
	EInstUIMissingDependency,
	EInstUIMsgRequireVer,
	EInstUIMsgRequireVerOrGreater,
	EInstUIMsgFileCorrupt,
	EInstUIMsgIncompatibleInstaller,
	EInstUIMsgFileUnicode,
	EInstUIMsgFileAscii,
	EInstUIMsgDiskNotPresent,
	EInstUIMsgCannotRead,
	EInstUIMsgCannotDelete,
	EInstUIMsgInvalidFileName
	};

enum TInstallEngineEvent
	{
	EInstallEngineSetProgressBarFinalValue,
	EInstallEngineUpdateProgressBar,
	EInstallEngineSetDeletingFilesLabel,
	EInstallEngineRemovingFiles,
	EInstallEngineShuttingDownApps,
	EInstallEngineCopyingFiles,
	EInstallEngineAborted,
	EInstallEngineCompletedInstall,
	EInstallEngineCompletedUnInstall,
	EInstallEngineCompletedNoMessage,
	EInstallEngineLeave,
	};

enum TSignatureValidationResult
	{
	EValidationSuceeded,
	ENoCertificate,
	ECertificateValidationException,
	ECertificateValidationError,
	ESignatureNotPresent,
	ESignatureCouldNotBeDecrypted,
	ESignatureCouldNotBeValidated,
	EPartialInstall
	};

enum TInstAbortRetrySkip
	{
	EInstAbort,
	EInstRetry,
	EInstSkip,
	};

#endif
