// SMTCPMTM.CPP
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//

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
#include <miuthdr.h>
#endif
#if !defined (__MIUTPARS_H__)
#include <miutpars.h>		//TImMessageField
#endif
#if !defined (__SMTPSET_H__)
#include <smtpset.h>
#endif
#if !defined (__SMTPCMDS_H__)
#include <smtpcmds.h>
#endif


class CMsvEntry;
class CMtmDllRegistry;
class CRichText;
class TMsvEntry;
class CRegisteredMtmDll;
class CImSmtpSettings;
class SmtpClientMTM_MSO;
class CMsvSession;

const TUint KSmtcAddresseeListResizeGranularity = 5;
const TInt KSmtcMaxTextMessageSize = 0xFFFF;

//#define KResourceFileName _L("C:\\system\\data\\IMCV.R01") // CHANGE Hardcoded to UK

class CSynClientMtm_MSO;  // foreward dec/n

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Active object to handle new entry creation callbacks from the message suite. Change any PCmails set to <default> to the default directory.

class CSynSetToDefault : public CActive
	{
public:
	static CSynSetToDefault* NewL(CSynClientMtm_MSO& aCSynClientMtm_MSO, CMsvSession& aSession);
	~CSynSetToDefault();
	void AddEntriesToProcessL(TMsvId aParentID, CMsvEntrySelection* aNewSelection);
private:
	void Start();
	CSynSetToDefault(CSynClientMtm_MSO& aCSynClientMtm_MSO, CMsvSession& aSession);
	virtual void DoCancel();
	virtual void RunL();
	void  GetDefaultServiceL();
	TBool DefaultServiceL(TMsvId& DefaultService) const;
//	TBool SetDefaultServiceL(TMsvId aId, TBool aSetAsDefault) const;
private:
	CSynClientMtm_MSO& iCSynClientMtm_MSO;
	CMsvSession& iSession;

	CMsvEntry*							iCurrentParent;
	CArrayPtrFlat<CMsvEntry>*			iParentArray;
	CMsvEntrySelection*					iCurrentSelection;
	CArrayPtrFlat<CMsvEntrySelection>*	iSelectionArray;
	TInt								iCurrentSelectionCount;
	TInt iCurrentChild;
	CMsvOperation* iMsvOperation;  // Current ChangeL operation;

	TMsvId  iDefaultAccount;
	};

///////  Session Observer for the Smtp Client MTM  ////////////////////////////////////////////////////
class CSynClientMtm_MSO : public CBase , public MMsvSessionObserver
	{
public:
	CSynClientMtm_MSO(CMsvSession& aSession);
	~CSynClientMtm_MSO();
	void HandleSessionEventL(TMsvSessionEvent aEvent, TAny* aArg1, TAny* aArg2, TAny* aArg3);
	void deleteICSynSetToDefault();
private:
	CMsvSession& iSession;
	CSynSetToDefault* iCSynSetToDefault;  // Active object to convert new messages to "default"
	};

///////  Smtp Client MTM  /////////////////////////////////////////////////////////////////////////////
class CSynClientMtm : public CBaseMtm
	{
public:
IMPORT_C static CSynClientMtm* NewL(CRegisteredMtmDll& aRegisteredMtmDll, CMsvSession& aMsvSession);
	~CSynClientMtm();

//	void HandleEntryEventL(enum MMsvEntryObserver::TMsvEntryEvent,TAny*,TAny*,TAny*);

	void SaveMessageL();
	void LoadMessageL();

	void StoreL(); // uses a CMsvStore from the Session
	void RestoreL();

	void StoreEmailMessageL(); // NEEDS to be compatible with email version.
	void RestoreEmailMessageL();
	void GetBodyTextL(CImEmailMessage& aMessage, TMsvId aMsvId);
	void SetAddresseeListL();
IMPORT_C void SetSubjectL(const TDesC& aSubject);
IMPORT_C const TPtrC SubjectL() const;
	TInt32 GetAttachmentSizeL(CImEmailMessage& aMessage, TMsvId aMsvId);

	CMsvOperation* ReplyL  (TMsvId aDestination, TMsvPartList aPartlist, TRequestStatus& aCompletionStatus);
	CMsvOperation* ForwardL(TMsvId aDestination, TMsvPartList aPartList, TRequestStatus& aCompletionStatus);

	TUint ValidateMessage(TMsvPartList aPartList);
	TMsvPartList Find(const TDesC& aTextToFind, TMsvPartList aPartList);

	// addresssee list (used by objects with no MTM knowledge)
	void AddAddresseeL(const TDesC& aRealAddress);
	void AddAddresseeL(const TDesC& aRealAddress, const TDesC& aAlias);
	void RemoveAddressee(TInt aIndex);

	// --- Generic message functions (not already in TMsvEntry) ---
	CDesCArray& AddresseeList();
//	IMPORT_C void SetSettingsL(const CImSmtpSettings& aSettings);
//	IMPORT_C const CImSmtpSettings& Settings() const; 

	// --- RTTI functions ---
	TInt QueryCapability(TUid aCapability, TInt& aResponse);
	void InvokeSyncFunctionL(TInt aFunctionId,const CMsvEntrySelection& aSelection, TDes8& aParameter);
	CMsvOperation* InvokeAsyncFunctionL(TInt aFunctionId,const CMsvEntrySelection& aSelection, TDes8& aParameter, TRequestStatus& aCompletionStatus);

	/////////////////////////////////////////////////////////
	// Extra methods required post ER5 for new message support. Given to us by Twm Davies, presumably from the email mtm.
	void CreateMessageL(TMsvId /*aServiceId*/);
	void CreateAttachmentL(TMsvId& aAttachmentId, TFileName& aDirectory);
	void DeleteAttachmentL(TMsvId aMessageId, TMsvId aAttachmentId);

protected:
	CSynClientMtm(CRegisteredMtmDll& aRegisteredMtmDll, CMsvSession& aMsvSession);
	void ConstructL();
	
	void ContextEntrySwitched(); // called after the context of this instance has been changed to another entry
private:
//	TBool ValidateAddress(const TPtrC& anAddress);
//	CImSmtpSettings* iImSmtpSettings;
//	TImMessageField iTImMessageField;
//	CMsvEntrySelection* iMsvEntrySelection;
	CSynClientMtm_MSO* iSynClientMTM_MSO;
//	CMsvSession* iMsvSession;

	CImHeader* iHeader;
	CMsvOperationWait* iWait;

	HBufC* iSubject;

//	HBufC* iForwardFormattingString;	// defines format of email address used by "Forward" API eg _L("Fw:")
//	HBufC* iReplyFormattingString;		// defines format of email address used by "Reply" API eg _L("Re:")
//	HBufC* iReceiptFormattingString;	// defines format of email address used by "Receipt" API eg L("Receipt:")
//	HBufC* iEmailAddressFormatString;	// defines format of email address used by "Send as" API eg _L("/"%S/" <%S>")
//	CMsvEntrySelection* iEntrySelection;
	};


#endif // __SMTCMTM_H__
