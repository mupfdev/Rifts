// SMTCPMTM.CPP
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved. 
// 

// Client MTM for the SMTP protocol

#if !defined (__SMTCMTM_H__)
#define __SMTCMTM_H__

#if !defined (__E32BASE_H__)
#include <e32base.h>		// CActive, TFileName)
#endif

#if !defined(__BADESCA_H__)
#include <badesca.h>
#endif

#if !defined (__MSVAPI_H__)
#include <msvapi.h>
#endif

#if !defined (__MTCLBASE_H__)
#include <mtclbase.h>
#endif

#if !defined (__MIUTHDR_H__)
#include "miuthdr.h"
#endif

#if !defined (__MIUTPARS_H__)
#include "miutpars.h"		//TImMessageField
#endif

#if !defined (__MIUTMSG_H__)
#include "miutmsg.h"		//CImEmailMessage
#endif

#if !defined (__SMTPSET_H__)
#include "smtpset.h"
#endif

#if !defined (__SMTPCMDS_H__)
#include "smtpcmds.h"
#endif

class CMsvEntry;
class CMtmDllRegistry;
class CRichText;
class TMsvEntry;
class CRegisteredMtmDll;
class CImSmtpSettings;
class CMsvSession;

///////  Smtp Client MTM  /////////////////////////////////////////////////////////////////////////////
class CSmtpClientMtm : public CBaseMtm
	{
public:
	IMPORT_C static CSmtpClientMtm* NewL(CRegisteredMtmDll& aRegisteredMtmDll, CMsvSession& aMsvSession);
	~CSmtpClientMtm();

	void SaveMessageL();
	void LoadMessageL();

	IMPORT_C void StoreSettingsL();
	IMPORT_C void RestoreSettingsL();

	CMsvOperation* ReplyL  (TMsvId aReplyEntryId, TMsvPartList aPartlist, TRequestStatus& aCompletionStatus);
	CMsvOperation* ForwardL(TMsvId aForwardEntryId, TMsvPartList aPartList, TRequestStatus& aCompletionStatus);

	TMsvPartList ValidateMessage(TMsvPartList aPartList);
	TMsvPartList Find(const TDesC& aTextToFind, TMsvPartList aPartList);

	// addresssee list (used by objects with no MTM knowledge)
	void AddAddresseeL(const TDesC& aRealAddress);
	void AddAddresseeL(const TDesC& aRealAddress, const TDesC& aAlias);
	void RemoveAddressee(TInt aIndex);

	IMPORT_C void SetSettingsL(const CImSmtpSettings& aSettings);
	IMPORT_C const CImSmtpSettings& Settings() const; 
	IMPORT_C void SetSubjectL(const TDesC& aSubject);
	IMPORT_C const TPtrC SubjectL() const;

	// --- RTTI functions ---
	TInt QueryCapability(TUid aCapability, TInt& aResponse);
	void InvokeSyncFunctionL(TInt aFunctionId,const CMsvEntrySelection& aSelection, TDes8& aParameter);
	CMsvOperation* InvokeAsyncFunctionL(TInt aFunctionId,const CMsvEntrySelection& aSelection, TDes8& aParameter, TRequestStatus& aCompletionStatus);

	// Attachment functions to support the SendAs API
	IMPORT_C virtual void CreateAttachmentL(TMsvId& aAttachmentId, TFileName& aDirectory);
	IMPORT_C virtual void DeleteAttachmentL(TMsvId aMessageId, TMsvId aAttachmentId);
	IMPORT_C virtual void CreateMessageL(TMsvId aServiceId);

protected:
	CSmtpClientMtm(CRegisteredMtmDll& aRegisteredMtmDll, CMsvSession& aMsvSession);
	void ConstructL();
	
	void ContextEntrySwitched(); // called after the context of this instance has been changed to another entry
private:
	TBool ValidateAddress(const TPtrC& anAddress);
	void ResetData();

	void RestoreEmailMessageL();
	void StoreEmailMessageL();
	void SetAddresseeListL();
	void GetBodyTextL(CImEmailMessage& aMessage, TMsvId aMsvId);
	TInt32 GetAttachmentSizeL(CImEmailMessage& aMessage, TMsvId aMsvId);

private:
	CMsvOperationWait* iWait;
	CImSmtpSettings* iImSmtpSettings;
	CImHeader* iHeader;
	HBufC* iSubject;

	TImMessageField iTImMessageField;
	HBufC* iEmailAddressFormatString;	// defines format of email address used by "Send as" API eg _LIT("/"%S/" <%S>")
	CMsvEntrySelection* iEntrySelection;
	CImEmailOperation*	iImEmailOperation;
	};


#endif // __SMTCMTM_H__
