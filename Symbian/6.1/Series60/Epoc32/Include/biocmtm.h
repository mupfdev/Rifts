// BIOCMTM.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//

#if !defined(__CIOCMTM_H__)
#define __BIOCMTM_H__
#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif
#if !defined(__MTCLBASE_H__)
#include <mtclbase.h>
#endif

class CBIOClientMtm : public CBaseMtm
	{
public:
	IMPORT_C static CBIOClientMtm* NewL(CRegisteredMtmDll& aRegisteredMtmDll, CMsvSession& aSession);
	~CBIOClientMtm();
	// from MMsvEntryObserver
	void HandleEntryEvent(TMsvEntryEvent aEvent, TAny* aArg1, TAny* aArg2, TAny* aArg3);
	//
	// from CBaseMtm
	void SaveMessageL(); 
	void LoadMessageL();
	CMsvOperation* ReplyL  (TMsvId aDestination, TMsvPartList aPartlist, TRequestStatus& aCompletionStatus);
	CMsvOperation* ForwardL(TMsvId aDestination, TMsvPartList aPartList, TRequestStatus& aCompletionStatus);
	TMsvPartList ValidateMessage(TMsvPartList aPartList);
	TMsvPartList Find(const TDesC& aTextToFind, TMsvPartList aPartList);
	const CDesCArray& AddresseeList();
	void AddAddresseeL(const TDesC& aRealAddress);
	void AddAddresseeL(const TDesC& aRealAddress, const TDesC& aAlias);
	void RemoveAddressee(TInt aIndex);
	// --- RTTI functions ---
	TInt QueryCapability(TUid aCapability, TInt& aResponse);
	void InvokeSyncFunctionL(TInt aFunctionId,const CMsvEntrySelection& aSelection, TDes8& aParameter);
	CMsvOperation*  InvokeAsyncFunctionL(TInt aFunctionId,const CMsvEntrySelection& aSelection, TDes8& aParameter, TRequestStatus& aCompletionStatus);
protected:
	//
	// from CBaseMtm
	void ContextEntrySwitched();
	//
private:
	CBIOClientMtm(CRegisteredMtmDll& aRegisteredMtmDll, CMsvSession& aSession);
	//
	void FindInDescriptionL(const TDesC& aTextToFind, TMsvPartList aPartList,TMsvPartList& aFoundList);
	void FindInOriginatorL(const TDesC& aTextToFind, TMsvPartList aPartList,TMsvPartList& aFoundList);
	void FindInBodyL(const TDesC& aTextToFind, TMsvPartList aPartList,TMsvPartList& aFoundList);
	};


#endif