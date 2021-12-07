// EPOCMSG.CPP
// Copyright (c) 1997-1999 Symbian Ltd. All rights reserved.
//
// Messages sent between EPOC InstSrv class and PC based installer (EPOCInstall)
//

#if !defined(__INSTMSGS_H__)
#define __INSTMSGS_H__

// messages sent by instsrv
enum TInstEPOCMsg 
	{
	EInstEPOCMsgHello,
	EInstEPOCMsgGetSISFile,
	EInstEPOCMsgInstallDialog,
	EInstEPOCMsgLanguageDialog,
	EInstEPOCMsgDriveDialog,
	EInstEPOCMsgQuestionDialog,
	EInstEPOCMsgTextDialog,
	EInstEPOCMsgOptionsDialog,
	EInstEPOCMsgErrorDialog,
	EInstEPOCMsgAbortRetrySkipDialog,
	EInstEPOCMsgInUseDialog,
	EInstEPOCMsgSecWarningDialog,
	EInstEPOCMsgEvent,
	EInstEPOCMsgExiting,
	};

#define EInstEPOCMsgInstallSigned				1<<0
#define EInstEPOCMsgInstallValidationProblem	1<<1

// messages sent by epocinst
enum TInstPCMsg 
	{
	EInstPCMsgHello,
	EInstPCMsgStart,
	EInstPCMsgReady,
	EInstPCMsgSelectDrive,
	EInstPCMsgSelectLanguage,
	EInstPCMsgSelectQuestion,
	EInstPCMsgSelectOptions,
	EInstPCMsgSelectDelDepend,
	EInstPCMsgSelectText,
	EInstPCMsgSelectAbortRetrySkip,
	EInstPCMsgSelectInUse,
	EInstPCMsgSelectSecWarning,
	EInstPCMsgSISData,
	EInstPCMsgGoodBye
	};

#endif