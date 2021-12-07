// SMTPCMDS.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved. 
//

#if !defined (__SMTPCMDS_H__)
#define __SMTPCMDS_H__

#if !defined (__MSVSTD_HRH__)
#include <msvstd.hrh>
#endif

enum TSmtpCmds 
	{
	KSMTPMTMIsConnected = KMtmFirstFreeMtmFunctionId,
	KSMTPMTMSendOnNextConnection,
	KSMTPMTMCreateNewEmailMessage,
	KSMTPMTMCreateReplyEmailMessage,
	KSMTPMTMCreateForwardEmailMessage,
	KSMTPMTMCreateForwardAsAttachmentEmailMessage,
	KSMTPMTMCreateReceiptEmailMessage
	};

#endif