// POP3CMDS.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved. 
//

#if !defined (__POP3CMDS_H__)
#define __POP3CMDS_H__

#if !defined (__MSVSTD_HRH__)
#include <msvstd.hrh>
#endif

enum TPop3Cmds 
	{
	KPOP3MTMIsConnected = KMtmFirstFreeMtmFunctionId,
	KPOP3MTMConnect,
	KPOP3MTMDisconnect,
	KPOP3MTMCreateReceipt,

	// need to pass in destination in aParameter
	KPOP3MTMCopyNewMailWhenAlreadyConnected,
	KPOP3MTMConnectAndCopyNewMailAndStayOnline,
	KPOP3MTMConnectAndCopyNewMailAndDisconnect,
	KPOP3MTMMoveNewMailWhenAlreadyConnected,
	KPOP3MTMConnectAndMoveNewMailAndStayOnline,
	KPOP3MTMConnectAndMoveNewMailAndDisconnect,

	// need to pass in destination in aParameter
	KPOP3MTMCopyMailSelectionWhenAlreadyConnected,
	KPOP3MTMConnectAndCopyMailSelectionAndStayOnline,
	KPOP3MTMConnectAndCopyMailSelectionAndDisconnect,
	KPOP3MTMMoveMailSelectionWhenAlreadyConnected,
	KPOP3MTMConnectAndMoveMailSelectionAndStayOnline,
	KPOP3MTMConnectAndMoveMailSelectionAndDisconnect,

	// need to pass in destination in aParameter
	KPOP3MTMCopyAllMailWhenAlreadyConnected,
	KPOP3MTMConnectAndCopyAllMailAndStayOnline,
	KPOP3MTMConnectAndCopyAllMailAndDisconnect,
	KPOP3MTMMoveAllMailWhenAlreadyConnected,
	KPOP3MTMConnectAndMoveAllMailAndStayOnline,
	KPOP3MTMConnectAndMoveAllMailAndDisconnect,

	KPOP3MTMCancelOfflineOperations,
	KPOP3MTMCancelSendOnNextConnection,
	KPOP3MTMCreateNewEmailMessage,
	KPOP3MTMCreateReplyEmailMessage,
	KPOP3MTMCreateForwardEmailMessage,
	KPOP3MTMCreateForwardAsAttachmentEmailMessage,
	KPOP3MTMCreateReceiptEmailMessage
	};

#endif