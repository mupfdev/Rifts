// POPCMTM.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved. 
// 

// Client MTM for the POP3 protocol


#if !defined (__POPCMTM_H__)
#define __POPCMTM_H__

#if !defined (__MIUTMSG_H__)
#include "miutmsg.h"
#endif
#if !defined (__MIUTPARS_H__)
#include "miutpars.h"		//TImMessageField
#endif
#if !defined (__POP3CMDS_H__)
#include "pop3cmds.h"		// KPOP3MTMConnect etc
#endif
#if !defined (__POP3SET_H__)
#include "pop3set.h"		// KPOP3MTMConnect etc
#endif

class CImPOP3GetMail;
class CImEmailAutoSend;
 
///////  Pop3 Client MTM  /////////////////////////////////////////////////////////////////////////////
class CPop3ClientMtm : public CBaseMtm
	{

public:
	enum TImPopcNewEmailHeaderType
		{
		EForwardedEmail,
		EReplyToEmail,
		EReceiptToEmail
		};

public:
	IMPORT_C static CPop3ClientMtm* NewL(CRegisteredMtmDll& aRegisteredMtmDll, CMsvSession& aMsvSession);
	~CPop3ClientMtm();

	void SaveMessageL();
	void LoadMessageL();

	IMPORT_C void StoreSettingsL();
	IMPORT_C void RestoreSettingsL();

	CMsvOperation* ReplyL  (TMsvId aId, TMsvPartList aPartlist, TRequestStatus& aCompletionStatus);
	CMsvOperation* ForwardL(TMsvId aId, TMsvPartList aPartList, TRequestStatus& aCompletionStatus);

	TUint ValidateMessage(TMsvPartList aPartList);
	TMsvPartList Find(const TDesC& aTextToFind, TMsvPartList aPartList);

	void AddAddresseeL(const TDesC& aRealAddress);
	void AddAddresseeL(const TDesC& aRealAddress, const TDesC& aAlias);
	void RemoveAddressee(TInt aIndex);

	IMPORT_C void SetSettingsL(const CImPop3Settings& aSettings);
	IMPORT_C const CImPop3Settings& Settings() const; 

	// --- RTTI functions ---
	TInt QueryCapability(TUid aCapability, TInt& aResponse);
	void InvokeSyncFunctionL(TInt aFunctionId, const CMsvEntrySelection& aSelection, TDes8& aParameter);
	CMsvOperation* InvokeAsyncFunctionL(TInt aFunctionId, const CMsvEntrySelection& aSelection, TDes8& aParameter, TRequestStatus& aCompletionStatus);

	// Attachment functions to support the SendAs API
	IMPORT_C virtual void CreateAttachmentL(TMsvId& aAttachmentId, TFileName& aDirectory);
	IMPORT_C virtual void DeleteAttachmentL(TMsvId aMessageId, TMsvId aAttachmentId);
	IMPORT_C virtual void CreateMessageL(TMsvId aServiceId);

protected:
	CPop3ClientMtm(CRegisteredMtmDll& aRegisteredMtmDll, CMsvSession& aMsvSession);
	void ConstructL();
	void ContextEntrySwitched();

private:
	TBool ValidateAddress(const TPtrC& anAddress);
	void SendOnNextConnectionL();
	TMsvPartList DoFindL(const TDesC& aTextToFind, TMsvPartList aPartList);

#ifdef __WINS__
	TThreadFunction AutoSendExeL(RLibrary& aLib) const; //places aLib on the cleanup stack
#endif

private:
	CImPop3Settings* iImPop3Settings;
	TImMessageField iTImMessageField;
	CMsvEntrySelection* iMsvEntrySelection;
	CImHeader* iHeader;

	HBufC* iEmailAddressFormatString;	// defines format of email address used by "Send as" API eg _LIT("/"%S/" <%S>")
	CImEmailOperation* iImEmailOperation;
	CImPOP3GetMail* iImPOP3GetMail;
	};


class CImPOP3GetMail : public CMsvOperation
	{
public:
	enum TImPOP3GetMailType
	{
		EConnectAndCopyNewMailAndStayOnline,
		EConnectAndCopyNewMailAndDisconnect,
		EConnectAndMoveNewMailAndStayOnline,
		EConnectAndMoveNewMailAndDisconnect,
		EConnectAndCopyMailSelectionAndStayOnline,
		EConnectAndCopyMailSelectionAndDisconnect,
		EConnectAndMoveMailSelectionAndStayOnline,
		EConnectAndMoveMailSelectionAndDisconnect,
		EConnectAndCopyAllMailAndStayOnline,
		EConnectAndCopyAllMailAndDisconnect,
		EConnectAndMoveAllMailAndStayOnline,
		EConnectAndMoveAllMailAndDisconnect
	};

public:
	IMPORT_C CMsvOperation* GetMailL(CPop3ClientMtm& aPop3ClientMtm, TRequestStatus& aObserverRequestStatus, const CMsvEntrySelection& aMsvEntrySelection, TDes8& aPop3GetMailInfo, TImPOP3GetMailType aPOP3GetMailType);
	IMPORT_C const TDesC8& FinalProgress();
	IMPORT_C ~CImPOP3GetMail();
	void DoCancel();
	void RunL();
	const TDesC8& ProgressL();
private:
	CImPOP3GetMail(CMsvSession& aMsvSession, TRequestStatus& aObserverRequestStatus, CPop3ClientMtm& aPop3ClientMtm, TImPOP3GetMailType aPOP3GetMailType);
	void ConstructL(const CMsvEntrySelection& aMsvEntrySelection, TDes8& aPop3GetMailInfo);
	void SelectNextStateL();					// selects next state to go to
	void ChangeStateL();					// initiates the next state operation
	void SelectAndChangeToNextStateL();
	void RequestComplete(TInt aError);
	void Complete();
	void ConnectToMailboxL();
	void CopyMoveNewMessagesL(TBool aCopy);
	void CopyMoveMessageSelectionL(TBool aCopy);
	void CopyMoveAllMessagesL(TBool aCopy);
	void DisconnectFromMailboxL();
	void ResetProgress();
	void StoreProgressL();
private:
	enum TImPOP3GetMailState
		{
		EConnectToMailbox,
		ECopyNewMessages,
		EMoveNewMessages,
		ECopyMessageSelection,
		EMoveMessageSelection,
		ECopyAllMessages,
		EMoveAllMessages,
		EDisconnectFromMailbox,
		EFinished
		};
	
	CPop3ClientMtm& iPop3ClientMtm;
	CMsvEntrySelection* iMsvEntrySelection;
	CMsvOperation* iMsvOperation;

	TPop3Progress iProgress;
	TPop3Progress iErrorProgress;
	TImPOP3GetMailState iState;
	TImPOP3GetMailType iPOP3GetMailType;
	TPckgBuf<TPop3Progress> iProgressBuf;
	TPckgBuf<TImPop3GetMailInfo> iPop3GetMailInfo;
	};

#endif // __POPCMTM_H__
