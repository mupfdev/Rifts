// IMAPSET.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved. 
//

#if !defined (__IMAPSET_H__)
#define __IMAPSET_H__

#if !defined (__MSVUIDS_H__)
#include <MSVUIDS.H>
#endif

#if !defined (__MIUTSET_H__)
#include "miutset.h"
#endif


const TUint16 KImImapSettingsVersion = 3;	// identify which version of this class has been stored
const TUint32 KIMAPDefaultPortNumber = 143;


const TInt32 KImImapSynchroniseAll	 = -1;	// negative values of sync limit mean "sync all"
const TInt32 KImImapSynchroniseNone	 = 0;	// zero values of sync limit mean "do not sync"
											// positive vales of sync limit mean "sync N most recent messages"

class CMsvStore;
class RMsvWriteStream;
class RMsvReadStream;

// Types of folder list sync
enum TFolderSyncType
	{
	EUseCombination=0,
	EUseLocal,
	EUseRemote
	};

// What to do with new subscription data
enum TFolderSubscribeType
	{
	EUpdateNeither=0,
	EUpdateLocal,
	EUpdateRemote,
	EUpdateBoth
	};

enum TImap4GetMailOptions
	{
	EGetImap4EmailHeaders,
	EGetImap4EmailBodyText,
	EGetImap4EmailBodyTextAndAttachments,
	EGetImap4EmailAttachments
	};

enum TImap4ProgressType
	{
	EImap4GenericProgressType,
	EImap4SyncProgressType
	};

//	Progress from copy/move/subscribe
//	create operations.
//
class TImap4GenericProgress
	{
public:
	// What operation is currently in progress
	enum TImap4GenericProgressOp
		{
		EConnect,				// with these three, then there
		EDisconnect,			// is more information in the 
		ESync,					// SyncProgress of some kind

		ESelect,				// SelectFolder
		
		ECopyToLocal,
		ECopyWithinService,
		ECopyFromLocal,
		EMoveToLocal,
		EMoveWithinService,
		EMoveFromLocal,
		EPopulate,
		
		EDelete,
		
		EOffLineDelete,
		EOffLineUndelete,
		EOffLineCopyToLocal,
		EOffLineMoveToLocal,
		EOffLineCopyFromLocal,
		EOffLineMoveFromLocal,
		EOffLineCopyWithinService,
		EOffLineMoveWithinService,
		EOffLinePopulate
		};

	// what state it's at
	enum TImap4GenericProgressState
		{
		EDisconnected,
		EConnecting,
		EIdle,
		ESelecting,				// folder to use
		EFetching,				// to mirror
		EAppending,				// from local
		ECopying,				// to local or within service
		EDeleting,				// including expunging folder
		ESyncing,				// folder after op
		EDisconnecting,
		EBusy,

		EMoving,
		ECopyNewMail,
		EMoveNewMail,
		ECopyMailSelection,
		EMoveMailSelection,
		ECopyAllMail,
		EMoveAllMail,
		EPopulateNewMail,
		EPopulateAllMail,
		EPopulateMailSelection
		};

	TImap4ProgressType iType;			//	Should always be EImapGenericProgressType
	TImap4GenericProgressOp iOperation;	//	Break down any given command into an Operation...
	TImap4GenericProgressState iState;	//	...and the stage of the operation 
	TImap4GenericProgressState iImap4SubStateProgress;

	// Message count for generic operations
	TInt		iMsgsToDo;
	TInt		iMsgsDone;

	// Fetching counts for generic operations
	TInt		iPartsToDo;
	TInt		iPartsDone;
	TInt		iBytesToDo;	// This is for *whole* multipart fetch in a single op
	TInt		iBytesDone;

	TInt		iErrorCode;	// client side needs to be informed of an error
	TMsvId		iReturnedMsvId;
	};


//	Progress structure returned from Connection/
//	ConnectAndSync operations and Disconnection
//	Operations.
//
class TImap4SyncProgress
	{
public:
	// Sync State
	enum TImap4SyncProgressState
		{
		EIdle,
		EBusy,
		EConnecting,
		EDisconnecting,
		ESyncInbox,
		ESyncFolderTree,
		ECheckRemoteSubscription,
		EUpdateRemoteSubscription,
		ESyncOther,
		EDeleting,
		EProcessingPendingOps
		};

	TImap4ProgressType iType;		//	will always be EImapSyncProgressType
	TImap4SyncProgressState iState;	//	Where is the sync up to?

	// Folder count for synchronisation
	// meaningful during ESyncOther and EDeleting
	TInt		iFoldersToDo;
	TInt		iFoldersDone;

	// Message count for synchronisation
	// meaningful during ESyncInbox, ESyncOther, EProcessingPendingOps
	TInt		iMsgsToDo;
	TInt		iMsgsDone;

	// Overall sync stats
	// increment thoughout
	TInt		iHeadersFetched;
	TInt		iOrphanedFolders;
	TInt		iNewFolders;
	TInt		iOrphanedMessages;
	TInt		iRemoteMessagesDeleteTagged;

	// Overall queued op stats
	// increment thoughout
	TInt		iMessagesFetchedOK;
	TInt		iMessagePartsFetchedOK;
	TInt		iMessagePartsNotFound;
	TInt		iFoldersNotFound;		// SELECT's that failed

	TInt		iErrorCode; 	// client side needs to be informed of an error
	};

class TImap4CompoundProgress
	{
public:
	TImap4GenericProgress	iGenericProgress;
	TImap4SyncProgress		iSyncProgress;
	};

class CImImap4Settings : public CImBaseEmailSettings
	{
public:
	IMPORT_C CImImap4Settings();
	IMPORT_C ~CImImap4Settings();
	IMPORT_C void Reset();

	// streaming operations
	IMPORT_C void InternalizeL(RMsvReadStream& aWriteStream);
	IMPORT_C void ExternalizeL(RMsvWriteStream& aReadStream) const;
	IMPORT_C void RestoreL(CMsvStore& aMessageStore);
	IMPORT_C void StoreL(CMsvStore& aMessageStore) const;

	// User name
	IMPORT_C const TPtrC8 LoginName() const;
	IMPORT_C void SetLoginNameL(const TDesC8& aLoginName);

	// Password
	IMPORT_C const TPtrC8 Password() const;
	IMPORT_C void SetPasswordL(const TDesC8& aPassword);

	// Folder path
	IMPORT_C const TPtrC8 FolderPath() const;
	IMPORT_C void SetFolderPathL(const TDesC8& aFolderPath);

	// Path separator
	IMPORT_C const TText8 PathSeparator() const;
	IMPORT_C void SetPathSeparator(const TText8 aPathSeparator);

	IMPORT_C const TBool DisconnectedUserMode() const;
	IMPORT_C void SetDisconnectedUserMode(TBool aFlag);

	// Synchronise strategy
	IMPORT_C void SetSynchronise(const TFolderSyncType aType);
	IMPORT_C const TFolderSyncType Synchronise() const;

	// Subscription strategy
	IMPORT_C void SetSubscribe(const TFolderSubscribeType aType);
	IMPORT_C const TFolderSubscribeType Subscribe() const;

	// Auto send on connection or not
	IMPORT_C const TBool AutoSendOnConnect() const;
	IMPORT_C void SetAutoSendOnConnect(TBool aFlag);

	IMPORT_C const TUint MaxEmailSize() const;
	IMPORT_C void SetMaxEmailSize(const TUint aMaxEmailSize);

	// Delete emails when disconnecting or not
	IMPORT_C const TBool DeleteEmailsWhenDisconnecting() const;
	IMPORT_C void SetDeleteEmailsWhenDisconnecting(TBool aFlag);

	// Acknowledge Receipts or not
	IMPORT_C const TBool AcknowledgeReceipts() const;
	IMPORT_C void SetAcknowledgeReceipts(TBool aFlag);

	// Get Mail options
	IMPORT_C const TImap4GetMailOptions GetMailOptions() const;
	IMPORT_C void SetGetMailOptions(TImap4GetMailOptions aGetMailOptions);

	// Inbox synchronisation limit
	IMPORT_C const TInt32 InboxSynchronisationLimit() const;
	IMPORT_C void SetInboxSynchronisationLimit(const TInt32 aInboxSyncLimit);

	// Mailbox (other folders) synchronisation limit
	IMPORT_C const TInt32 MailboxSynchronisationLimit() const;
	IMPORT_C void SetMailboxSynchronisationLimit(const TInt32 aMailboxSyncLimit);

	IMPORT_C CImImap4Settings& CopyL(const CImImap4Settings& aCImImap4Settings);
	IMPORT_C TBool operator==(const CImImap4Settings& aCImImap4Settings) const;

private:
	enum TImImap4EmailSettings
		{
		KImap4EmailSettingsClearFlag				= 0x00000000,
		KImap4BaseEmailSettingsLastUsedFlag			= CImBaseEmailSettings::EBaseEmailSettingsLastUsedFlag,
		KImap4EmailDisconnectedModeFlag				= KImap4BaseEmailSettingsLastUsedFlag << 1,
		KImap4EmailAutoSendFlag						= KImap4EmailDisconnectedModeFlag << 1,
		KImap4EmailDeleteEmailsWhenDisconnecting	= KImap4EmailAutoSendFlag << 1,
		KImap4EmailAcknowledgeReceipts				= KImap4EmailDeleteEmailsWhenDisconnecting << 1,
		KImap4EmailSettingsLastUsedFlag				= KImap4EmailAcknowledgeReceipts
		};

	HBufC8* iLoginName;
	HBufC8* iPassword;
	HBufC8* iFolderPath;
	TText8 iPathSeparator;
	TFolderSyncType iSynchroniseStrategy;
	TFolderSubscribeType iSubscriptionStrategy;
	TUint32	iMaxEmailSize;
	TImap4GetMailOptions iGetMailOptions;
	};

class TImImap4GetMailInfo
	{
public:
	TInt32					iMaxEmailSize;		// only need to get mail if iMaxEmailSize < KMaxTUint
	TImap4GetMailOptions	iGetMailBodyParts;
	TMsvId					iDestinationFolder;	// specifies the destination folder for get mail
	};

#endif // #define __IMAPSET_H__
