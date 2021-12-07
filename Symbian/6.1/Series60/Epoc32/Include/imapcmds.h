// IMAPCMDS.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved. 
//

#if !defined (__IMAPCMDS_H__)
#define __IMAPCMDS_H__

#if !defined (__MSVSTD_HRH__)
#include <msvstd.hrh>
#endif

class TImap4RenameFolder
	{
public:
	TBuf<128> iNewName;
	};

enum TImap4Cmds {
	KIMAP4MTMIsConnected = KMtmFirstFreeMtmFunctionId,
	KIMAP4MTMConnect,
	KIMAP4MTMConnectAndSynchronise,
	KIMAP4MTMCancelBackgroundSynchronise,
	KIMAP4MTMStartBatch,
	KIMAP4MTMEndBatch,
	KIMAP4MTMBusy,
	KIMAP4MTMSelect,
	KIMAP4MTMSynchronise,
	KIMAP4MTMSyncTree,
	KIMAP4MTMReserved10,						// SyncSubscription
	KIMAP4MTMFullSync,
	KIMAP4MTMDisconnect,
    KIMAP4MTMLocalSubscribe,
    KIMAP4MTMLocalUnsubscribe,
	KIMAP4MTMReserved15,						// MakeRemoteMailboxesInvisible
	KIMAP4MTMReserved16,						// MakeRemoteMailboxesVisible
	KIMAP4MTMInboxNewSync,
	KIMAP4MTMFolderFullSync,
	KIMAP4MTMWaitForBackground,
	KIMAP4MTMRenameFolder,
	KIMAP4MTMUndeleteAll,
	KIMAP4MTMCancelOffLineOperations,
	KIMAP4MTMPopulate,
	KIMAP4MTMSyncSubscription,
	KIMAP4MTMConnectAndSyncCompleteAfterConnect,
	KIMAP4MTMConnectAndSyncCompleteAfterFullSync,
	KIMAP4MTMConnectAndSyncCompleteAfterDisconnect,
	KIMAP4MTMCancelSendOnNextConnection,
	
	// need to pass in destination in aParameter
	KIMAP4MTMCopyNewMailWhenAlreadyConnected,
	KIMAP4MTMConnectAndCopyNewMailAndStayOnline,
	KIMAP4MTMConnectAndCopyNewMailAndDisconnect,
	KIMAP4MTMMoveNewMailWhenAlreadyConnected,
	KIMAP4MTMConnectAndMoveNewMailAndStayOnline,
	KIMAP4MTMConnectAndMoveNewMailAndDisconnect,

	// need to pass in destination in aParameter
	KIMAP4MTMCopyMailSelectionWhenAlreadyConnected,
	KIMAP4MTMConnectAndCopyMailSelectionAndStayOnline,
	KIMAP4MTMConnectAndCopyMailSelectionAndDisconnect,
	KIMAP4MTMMoveMailSelectionWhenAlreadyConnected,
	KIMAP4MTMConnectAndMoveMailSelectionAndStayOnline,
	KIMAP4MTMConnectAndMoveMailSelectionAndDisconnect,

	// need to pass in destination in aParameter
	KIMAP4MTMCopyAllMailWhenAlreadyConnected,
	KIMAP4MTMConnectAndCopyAllMailAndStayOnline,
	KIMAP4MTMConnectAndCopyAllMailAndDisconnect,
	KIMAP4MTMMoveAllMailWhenAlreadyConnected,
	KIMAP4MTMConnectAndMoveAllMailAndStayOnline,
	KIMAP4MTMConnectAndMoveAllMailAndDisconnect,

	KIMAP4MTMPopulateMailSelectionWhenAlreadyConnected,
	KIMAP4MTMConnectAndPopulateMailSelectionAndStayOnline,
	KIMAP4MTMConnectAndPopulateMailSelectionAndDisconnect,
	KIMAP4MTMPopulateNewMailWhenAlreadyConnected,
	KIMAP4MTMPopulateAllMailWhenAlreadyConnected,
	KIMAP4MTMConnectAndPopulateNewMailAndStayOnline,
	KIMAP4MTMConnectAndPopulateNewMailAndDisconnect,
	KIMAP4MTMConnectAndPopulateAllMailAndStayOnline,
	KIMAP4MTMConnectAndPopulateAllMailAndDisconnect,
	KIMAP4MTMCreateNewEmailMessage,
	KIMAP4MTMCreateReplyEmailMessage,
	KIMAP4MTMCreateForwardEmailMessage,
	KIMAP4MTMCreateForwardAsAttachmentEmailMessage,
	KIMAP4MTMCreateReceiptEmailMessage
};

#endif
