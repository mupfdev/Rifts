// FAXC.CPP
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//


#if !defined (__FAXC_H__)
#define __FAXC_H__

#include <e32base.h>
#include <msvapi.h>
#include <mtclbase.h>
#include <msvuids.h>
#include <mtmdef.h>
#include <msvftext.h>
#include <fxut.h>

class CMsvEntry;
class CMtmDllRegistry;
class CRichText;
class TMsvEntry;
class CRegisteredMtmDll;
class CFaxHeader;

/***********************************************
***********************************************/
class CFaxMtmClient : public CBaseMtm
	{
public:
	IMPORT_C static CFaxMtmClient* NewL(CRegisteredMtmDll& aRegisteredMtmDll, CMsvSession& aMsvSession);
	~CFaxMtmClient();
	//
	// from CBaseMtm
//	void HandleEntryEvent(enum MMsvEntryObserver::TMsvEntryEvent,TAny*,TAny*,TAny*);
	void SaveMessageL();
	void LoadMessageL();
	CMsvOperation* ReplyL  (TMsvId aId, TMsvPartList aPartList, TRequestStatus& aCompletionStatus);
	CMsvOperation* CFaxMtmClient::ForwardL(TMsvId aId, TMsvPartList aPartList, TRequestStatus& aCompletionStatus);
	TMsvPartList ValidateMessage(TMsvPartList aPartList);
	TMsvPartList Find(const TDesC& aTextToFind, TMsvPartList aPartList);
	void AddAddresseeL(const TDesC& aRealAddress);
	void AddAddresseeL(const TDesC& aRealAddress, const TDesC& aAlias);
	void RemoveAddressee(TInt aIndex);
	TInt QueryCapability(TUid aCapability, TInt& aResponse);
	void InvokeSyncFunctionL(TInt aFunctionId, const CMsvEntrySelection& aSelection, TDes8& aParameter);
	CMsvOperation* InvokeAsyncFunctionL(TInt aFunctionId, const CMsvEntrySelection& aSelection, TDes8& aParameter, TRequestStatus& aCompletionStatus);
	
	//
	// specfic for Fax client
	inline CFaxHeader& FaxHeader();
	inline const CFaxHeader& FaxHeader() const;
	inline TMTMFaxSettings& FaxSettings();
	inline const TMTMFaxSettings& FaxSettings() const;
	//
protected:
	CFaxMtmClient(CRegisteredMtmDll& aRegisteredMtmDll, CMsvSession& aMsvSession);
	void ConstructL();
	//
	// from CBaseMtm
	void ContextEntrySwitched(); 
	//
private:
	TInt DoAddAddressee(const TDesC& aText);
	HBufC* AddresseeTextLC(const TDesC& aRealAddress, const TDesC& aAlias);
	void SetupAddresseeListL();
	TBool ValidNumber(const TDesC8& aNumber);
	TMsvPartList ValidRecipients();
	void ResetData();
	TFaxResolution GetDefaultResolutionL();
	void FindInFaxL(const TDesC& aTextToFind, TMsvPartList aPartList, TMsvPartList& rReturnList);
	TMsvPartList FindInBodyL(const TDesC& aTextToFind, CMsvFindText& aMsvFindText);
	TMsvPartList FindInRecipientsL(const TDesC& aTextToFind, CMsvFindText& aMsvFindText);
	//
private:
	CFaxHeader*	iFaxHeader;
	TMTMFaxSettings iFaxSettings;
	RFs iFs;
	CMsvSession& iSession;
	};


#include "faxc.inl"

#endif 
