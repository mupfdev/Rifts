// ImapConnectionObserver.H
//
// Copyright (c) 1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__IMAPCONNECTIONOBSERVER_H__)
#define __IMAPCONNECTIONOBSERVER_H__

enum TImapConnectionEvent
	{
	EConnectingToServer,
	ESynchronisingFolderList,
	ESynchronisingInbox,
	ESynchronisingFolders,
	ESynchronisationComplete,
	EDisconnecting,
	EConnectionCompleted
	};

//	Mix-in class to allow observation of the stages of an IMAP operation
//
class MMsvImapConnectionObserver
	{
public:
	virtual void HandleImapConnectionEvent(TImapConnectionEvent aConnectionState)=0;
	};

#endif