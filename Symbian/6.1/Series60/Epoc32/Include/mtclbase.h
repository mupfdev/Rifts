// MTCLBASE.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//


#if !defined __MTCLBASE_H__
#define __MTCLBASE_H__

#if !defined (__E32BASE_H__)
#include <e32base.h>		
#endif

#if !defined(__BADESCA_H__)
#include <badesca.h>
#endif

#if !defined (__MSVAPI_H__)
#include "msvapi.h"
#endif

typedef TUint TMsvPartList;

class CParaFormatLayer;
class CCharFormatLayer;

////////////////////////////////////////////////////////
// Prototype of expected factory function

typedef CBaseMtm* MtmFactoryFunctionL(CRegisteredMtmDll&, CMsvSession&);


/***********************************************
***********************************************/
class CBaseMtm : public CBase, public MMsvEntryObserver
	{
public:
	IMPORT_C ~CBaseMtm();
	inline TUid Type() const;
	//
	// context related
	IMPORT_C void SetCurrentEntryL(CMsvEntry* aEntry);
	IMPORT_C void SwitchCurrentEntryL(TMsvId aId);
	inline CMsvEntry& Entry() const;
	inline TBool HasContext() const;
	//
	//
	virtual void SaveMessageL()=0; 
	virtual void LoadMessageL()=0;
	virtual TMsvPartList ValidateMessage(TMsvPartList aPartList)=0;
	virtual TMsvPartList Find(const TDesC& aTextToFind, TMsvPartList aPartList)=0;
	//
	//
	virtual CMsvOperation* ReplyL(TMsvId aDestination, TMsvPartList aPartlist, TRequestStatus& aCompletionStatus)=0;
	virtual CMsvOperation* ForwardL(TMsvId aDestination, TMsvPartList aPartList, TRequestStatus& aCompletionStatus)=0;
	//
	// addresssee list (used by objects with no MTM knowledge)
	inline const CDesCArray& AddresseeList() const;
	virtual void AddAddresseeL(const TDesC& aRealAddress)=0;
	virtual void AddAddresseeL(const TDesC& aRealAddress, const TDesC& aAlias)=0;
	virtual void RemoveAddressee(TInt aIndex)=0;
	//
	// standard data accessor/mutators
	inline CRichText& Body();
	inline const CRichText& Body() const;
	IMPORT_C virtual void SetSubjectL(const TDesC& aSubject); // default leaves with KErrNotSupported
	IMPORT_C virtual const TPtrC SubjectL() const; // default leaves with KErrNotSupported
	//
	// RTTI functions
	IMPORT_C virtual TInt QueryCapability(TUid aCapability, TInt& aResponse); // default returns KErrNotSupported
	virtual void InvokeSyncFunctionL(TInt aFunctionId,const CMsvEntrySelection& aSelection, TDes8& aParameter)=0;
	virtual CMsvOperation* InvokeAsyncFunctionL(TInt aFunctionId,const CMsvEntrySelection& aSelection, TDes8& aParameter, TRequestStatus& aCompletionStatus)=0;
	//
	inline CMsvSession& Session();
	//
	// Attachment functions to support the SendAs API
	IMPORT_C virtual void CreateAttachmentL(TMsvId& aAttachmentId, TFileName& aDirectory);
	IMPORT_C virtual void DeleteAttachmentL(TMsvId aMessageId, TMsvId aAttachmentId);
	IMPORT_C virtual void CreateMessageL(TMsvId aServiceId);

	// BIO functions to support the SendAs API
	// Entry().Entry().iBioType will be set by SendAs if this function does not leave.
	// The default implementation in CBaseMtm is to do nothing.
	IMPORT_C virtual void BioTypeChangedL(TUid aBioTypeUid);

protected:
	IMPORT_C CBaseMtm(CRegisteredMtmDll& aRegisteredMtmDll, CMsvSession& aSession);
	//
	IMPORT_C void StoreBodyL(CMsvStore& aStore);
	IMPORT_C void RestoreBodyL(CMsvStore& aStore);
	//
	virtual void ContextEntrySwitched()=0; // called after the context of this instance has been changed to another entry
	//
	IMPORT_C void HandleEntryEventL(TMsvEntryEvent aEvent, TAny*, TAny*, TAny*);
private:
	void DeleteEntry();
	//
protected:
	CMsvEntry*		iMsvEntry;
	CDesCArrayFlat* iAddresseeList;
	CParaFormatLayer* iParaFormatLayer;
	CCharFormatLayer* iCharFormatLayer;
private:
	TMsvId	iEntryId;
	CRichText* iRichTextBody;
	CRegisteredMtmDll& iRegisteredMtmDll;
	CMsvSession& iSession;
	};

#include "mtclbase.inl"

#endif // __MTCLBASE_H__
