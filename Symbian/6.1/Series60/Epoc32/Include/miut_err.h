// MIUT_ERR.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved. 
// 

#if !defined(__MIUT_ERR_H__)
#define __MIUT_ERR_H__

// Minimum value for an MTM-specific error
const TInt KMiutErrorBase						= (-170);

// POP3-specific error codes
const TInt KPop3ErrorBase						= KMiutErrorBase;
const TInt KPop3CannotConnect					= KPop3ErrorBase;
const TInt KPop3InvalidUser						= KPop3ErrorBase-1;
const TInt KPop3InvalidLogin					= KPop3ErrorBase-2;
const TInt KPop3CannotCreateApopLogonString		= KPop3ErrorBase-3;
const TInt KPop3ProblemWithRemotePopServer		= KPop3ErrorBase-4;
const TInt KPop3CannotOpenServiceEntry			= KPop3ErrorBase-5;
const TInt KPop3CannotSetRequiredFolderContext	= KPop3ErrorBase-6;
const TInt KPop3InvalidApopLogin				= KPop3ErrorBase-7;
const TInt KPopTopError							= (-179);

// IMSK-specific error code
const TInt KImskBaseError						= (-180);
const TInt KImskErrorDNSNotFound				= KImskBaseError;
const TInt KImskErrorControlPanelLocked			= KImskBaseError-1;
const TInt KImskErrorISPOrIAPRecordNotFound		= KImskBaseError-2;
const TInt KImskErrorActiveSettingIsDifferent	= KImskBaseError-3;
const TInt KImskSecuritySettingsFailed			= KImskBaseError-4;
const TInt KImskTopError						= (-190);

// error codes -190 to -199 are used by Sockets

// IMAP-specific error codes
const TInt KImapBaseError						= (-200);
const TInt KErrImapConnectFail					= KImapBaseError;
const TInt KErrImapServerFail					= KImapBaseError-1;
const TInt KErrImapServerParse					= KImapBaseError-2;
const TInt KErrImapServerBusy					= KImapBaseError-3;
const TInt KErrImapServerVersion				= KImapBaseError-4;
const TInt KErrImapSendFail						= KImapBaseError-5;
const TInt KErrImapBadLogon						= KImapBaseError-6;
const TInt KErrImapSelectFail					= KImapBaseError-7;
const TInt KErrImapWrongFolder					= KImapBaseError-8;
const TInt KErrImapServerNoSecurity				= KImapBaseError-9;
const TInt KErrImapServerLoginDisabled			= KImapBaseError-10;
const TInt KErrImapTLSNegotiateFailed  			= KImapBaseError-11;
const TInt KErrImapCantDeleteFolder  			= KImapBaseError-12;
const TInt KImapTopError						= (-219);

// DMSS-specific error codes
const TInt KDmssBaseError						= (-220);
const TInt KDmssUnknownErr						= (KDmssBaseError-1);
const TInt KDmssMailboxUnavailableErr			= (KDmssBaseError-2);
const TInt KDmssActionAbortedErr				= (KDmssBaseError-3);
const TInt KDmssActionNotTakenErr				= (KDmssBaseError-4);
const TInt KDmssCmdUnrecognisedErr				= (KDmssBaseError-5);
const TInt KDmssSyntaxErrorErr					= (KDmssBaseError-6);
const TInt KDmssCmdNotImplementedErr			= (KDmssBaseError-7);
const TInt KDmssBadSequenceErr					= (KDmssBaseError-8);
const TInt KDmssParamNotImplementedErr			= (KDmssBaseError-9);
const TInt KDmssMailboxNoAccessErr				= (KDmssBaseError-10);
const TInt KDmssExceededStorageErr				= (KDmssBaseError-11);
const TInt KDmssMailboxNameErr					= (KDmssBaseError-12);
const TInt KDmssTransactionFailedErr			= (KDmssBaseError-13);
const TInt KDmssTimeOutErr						= (KDmssBaseError-14);
const TInt KDmssTopError						= (-239);

// SMTP client-specific error codes
const TInt KSmtpBaseError						= (-240);
const TInt KSmtpNoMailFromErr					=  KSmtpBaseError;
const TInt KSmtpUnknownErr						= (KSmtpBaseError-1);
const TInt KSmtpBadMailFromAddress				= (KSmtpBaseError-2);
const TInt KSmtpBadRcptToAddress				= (KSmtpBaseError-3);
const TInt KSmtpLoginRefused					= (KSmtpBaseError-4);
const TInt KSmtpNoMsgsToSendWithActiveSettings	= (KSmtpBaseError-5);
const TInt KErrSmtpTLSNegotiateFailed 			= (KSmtpBaseError-6);
const TInt KSmtpTopError					    = (-249);

// IMCM error codes
const TInt KImcmBaseError						= (-250);
const TInt KImcmHTMLPartNotPopulated			=  KImcmBaseError;
const TInt KImcmInvalidMessageStructure			= (KImcmBaseError-1);

// POPS error codes
const TInt KPop3BaseError						= (-260);
const TInt KErrPop3TLSNegotiateFailed			=  KPop3BaseError;

enum TImcmPanic
	{
	EOffOpNoBodyText,
	EOffOpBadMtmTypeUid,
	EOffOpNoCMsvEntrySet,
	EOffOpEntryShouldBeFolder,
	EOffOpTwoSameLinesNotAllowed,
	EOffOpNoMemory,
	EOffOpInvalidConstruction,
	EOffOpListOutOfSync,
	EOffOpNoMtmParameters,
	EMiutBadStreamVersion,
	EEntryIsNotMessage,
	EMiutArrayHasOddNumberOfElements,		// ie there should be even number of entries in array
	EMiutLocalServiceIdSet,				// iServiceId should not be set to Local
	EPopcMTMNoBodyText,
	EPopcMTMBadMtmTypeUid,
	EPopcMTMNoCMsvEntrySet,
	EPopcMTMOperationNULL,
	EPopcMTMNotAServiceEntry,
	EPopcUnknownNewEmailType,
	EPopcUnknownSyncFunction,
	ESmtcMTMNoBodyText,
	ESmtcMTMBadMtmTypeUid,
	ESmtcMTMNoCMsvEntrySet,
	ESmtcMTMOperationNULL,
	ESmtcMTMNotAServiceEntry,
	ESmtcUnknownNewEmailType,
	ESmtcUnknownSyncFunction,
	ESmtcMTMStoringBadEntryType,
	ESmtcMTMRestoringBadEntryType,
	ESmtcMTMNotAMessageEntry,
	EMiutActiveInFinalProgress,
	EImpcNoBodyText,
	EImpcBadMtmTypeUid,
	EImpcNoCMsvEntrySet,
	EImpcEntryShouldBeFolder,
	EImpcTwoSameLinesNotAllowed,
    EImpcNoMemory,
    EImpcInvalidConstruction,
    EImpcBadServiceEntry,
    EImpcNoBaseMtm,
    EImpcNoAddresseeList,
	EImpcInvalidProgress,
	EImpcNotSupported,
	EImpcMTMNotAMessageEntry,
	EImpcMTMNotAServiceEntry,
	EImcmMessageEntryHasMoreThanOneFolder,
	EImcmUnknownState,
	EImcmFinalProgressFailed,
	EImcmNoEikonEnvironment,
	EImcmSetVersionNotSupported,
	EImcmSystemDefaultCharsetNotSupported
	};

GLREF_C void gPanic(TImcmPanic aPanic);

#endif
