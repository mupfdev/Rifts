// SENDAS.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//


#if !defined (__SENDAS_H__)
#define __SENDAS_H__

#include <e32base.h>
#include <mtclreg.h>
#include <mtclbase.h>
#include <txtmrtsr.h>

//**********************************
// MSendAsObserver
//**********************************
//
// 
//

class MSendAsObserver
	{
public:
	virtual TBool CapabilityOK(TUid aCapabilty, TInt aResponse)=0;
	IMPORT_C virtual TInt RenderImage(TUid aPrinterUid, const TDesC& aFileName);
	IMPORT_C virtual TInt RenderImage(TUid aPrinterUid, const TDesC& aFileName, TRequestStatus& aRequestStatus);
	IMPORT_C virtual void CancelRendering();
	};

//**********************************
// CSendAsStoreResolver
//**********************************
//
//
//

class CSendAsStoreResolver : public CBase, public MRichTextStoreResolver
	{
public:
	CSendAsStoreResolver(CStreamStore* aStore);
	~CSendAsStoreResolver();
	//
private:
	const CStreamStore& StreamStoreL(TInt aPos)const;
	//
private:
	CStreamStore* iStore;
	};

//**********************************
// CSendAs
//**********************************
//
// 
//

class CSendAs : public CActive, public MMsvSessionObserver
	{
public:
	IMPORT_C static CSendAs* NewL(MSendAsObserver& aObserver);
	IMPORT_C ~CSendAs();
	//
	// MTM selection
	inline const CDesCArray& AvailableMtms() const;
	IMPORT_C void AddMtmCapabilityL(TUid aCapabilityId, TBool aResponseExpected=EFalse);
	IMPORT_C void ResetMtmCapabilitiesL();
	IMPORT_C void SetMtmL(TInt aMtmIndex);
	IMPORT_C void SetMtmL(TUid aMtmUid);
	//
	// Service selection
	inline const CDesCArray& AvailableServices() const;
	IMPORT_C void SetService(TInt aServiceIndex);
	//
	// Message creation / deletion
	IMPORT_C void CreateMessageL();
	IMPORT_C void CreateMessageL(TMsvId aId);
	IMPORT_C void SaveMessageL(TBool aMakeVisible=ETrue);
	IMPORT_C void SaveMessageL(TRequestStatus& aStatus, TBool aMakeVisible=ETrue);
	IMPORT_C void AbandonMessage();
	inline TMsvId MessageId();
	//
	// Message definition
	IMPORT_C const CDesCArray& RecipientList() const;
	IMPORT_C void AddRecipientL(const TDesC& aRealAddress);
	IMPORT_C void AddRecipientL(const TDesC& aRealAddress, const TDesC& aAlias);
	IMPORT_C void RemoveRecipient(TInt aIndex);
	IMPORT_C void SetSubjectL(const TDesC& aSubject);
	IMPORT_C void SetBodyL(const CRichText& aMessageBody);
	IMPORT_C TMsvPartList ValidateMessage();
	IMPORT_C TInt QueryMessageCapability(TUid aCapabilityId, TBool aResponseExpected=EFalse);
	IMPORT_C void SetBioTypeL(TUid aBioTypeUid);
	//
	// Attachment functions
	IMPORT_C void CreateAttachmentL(TMsvId& aAttachmentId, TFileName& aDirectory);
	IMPORT_C void DeleteAttachmentL(TMsvId aAttachmentId);
	IMPORT_C void SetAttachmentL(TMsvId aAttachmentId, const TDesC& aAttachmentName);
	//
	// Accessor to underlying messaging components
	inline CClientMtmRegistry& ClientRegistry();
	inline CBaseMtm& ClientMtm();
	//
	// from MMsvSessionObserver
	void HandleSessionEventL(TMsvSessionEvent aEvent, TAny* aArg1, TAny* aArg2, TAny* aArg3);
	//
	// from CActive
	void RunL();
	void DoCancel();
	//
protected:
	CSendAs(MSendAsObserver& aObserver);
	void ConstructL();
	//
private:
	void CreateMtmArrayL();
	void DoResetMtmCapabilitiesL();
	//
	void CreateServiceArrayL();
	void DoCreateServiceArrayL();
	TMsvId FindServiceIdL();
	TInt GetDefaultServiceL(TUid aMtm, TMsvId& aService);
	//
	void DoSaveMessageL();
	void SetupRenderingL(TUid& aUid, TFileName& aFileName);
	//
	TBool AttachmentCountL(TMsvId aEntryId);
private:
	enum TSendAsState {	EDefault=1,
						EMtmChosen,
						EMessageCreated,
						EMessageSaved,
						EMessageAbandoned,
						EMessageBeingRendered};
private:
	MSendAsObserver& iObserver;
	CMsvSession* iSession;
	CClientMtmRegistry* iClientRegistry;
	CArrayPtrFlat<CBaseMtm>* iMainMtmArray;
	CArrayPtrFlat<CBaseMtm>* iAvailMtmArray;
	CDesCArrayFlat* iMainNameArray;
	CDesCArrayFlat* iAvailNameArray;
	CBaseMtm* iClientMtm;
	CMsvEntry* iEntry;
	CDesCArrayFlat* iServiceNameArray;
	TSendAsState iState;
	TInt iServiceIndex;
	TMsvId iMessageId;
	TRequestStatus* iCompletionStatus;
	TBool iMakeVisible;
	TBool iHasAttachment;
	TUid iBioTypeUid;
	CSendAsStoreResolver* iStoreResolver;
	TMsvEntry iTempEntry;
	};


#include "sendas.inl"

#endif
