///////////////////////////////////////////////////////////////////////////////
//
// SMSCLNT.H
//
// Copyright (c) 2000 Symbian Ltd. All Rights reserved.
//
///////////////////////////////////////////////////////////////////////////////


/*
-----------------------------------------------------------------------------

    DESCRIPTION

    This file contains the header file of the  class CSmsClientMtm.

-----------------------------------------------------------------------------
*/

#ifndef SMSCLNT_H_
#define SMSCLNT_H_

// Includes

#include <mtclbase.h>	// CBaseMtm

// Constants

const TInt KUidMsgSmsEditorAppVal=0x1000163f;
const TInt KSmcmMaxMessageNumber=0x32;
const TInt KSmcmMaxCharsInMessageConcatenated7Bit=0x99;
const TInt KSmcmMaxTotalMsgSize=160;
const TInt KSmcmRichTextConstant=256;

// Macros

// Enumerations

// Data Types

// External Data Structures

// Forward Declarations

class CSmsHeader;
class CSmsSettings;
class TSmsUtilities;
class CSmsSimParamOperation;

// Class Definitions

// CSmsClientMtm

class CSmsClientMtm : public CBaseMtm
	{
public:

	// NewL
	IMPORT_C static CSmsClientMtm* NewL(CRegisteredMtmDll& aRegisteredMtmDll,CMsvSession& aSession);
	// Destructor
	~CSmsClientMtm();

	void HandleEntryEvent(enum MMsvEntryObserver::TMsvEntryEvent,TAny*,TAny*,TAny*);	

	// Opening/closing message
	void SaveMessageL(); 
	void LoadMessageL();

	// Validate
	TMsvPartList ValidateMessage(TMsvPartList aPartList);
	// Find
	TMsvPartList Find(const TDesC& aTextToFind, TMsvPartList aPartList);
	
	// Replying/Forwarding
	CMsvOperation* ReplyL(TMsvId aDestination, TMsvPartList aPartlist, TRequestStatus& aCompletionStatus);
	CMsvOperation* ForwardL(TMsvId aDestination, TMsvPartList aPartList, TRequestStatus& aCompletionStatus);

	// Recipient Handling
	void AddAddresseeL(const TDesC& aRealAddress);
	void AddAddresseeL(const TDesC& aRealAddress, const TDesC& aAlias);
	void RemoveAddressee(TInt aIndex);

	// --- RTTI functions ---
	TInt QueryCapability(TUid aCapability, TInt& aResponse);
	void InvokeSyncFunctionL(TInt aFunctionId,const CMsvEntrySelection& aSelection, TDes8& aParameter);
	CMsvOperation* InvokeAsyncFunctionL(TInt aFunctionId,const CMsvEntrySelection& aSelection, TDes8& aParameter, TRequestStatus& aCompletionStatus);

	// Spesific for Sms client
	inline CSmsHeader& SmsHeader();
	inline const CSmsHeader& SmsHeader() const;
	inline CSmsSettings& ServiceSettings();
	inline const CSmsSettings& ServiceSettings() const;
	inline TInt ServiceId() const;

	IMPORT_C void BioTypeChangedL(TUid aBioTypeUid);

	//Restore iServiceSettings and set iServiceId, only if NULL
	IMPORT_C void RestoreServiceAndSettingsL();

	//Returns an operation that reads the Service Center addresses in the SIM params
	IMPORT_C CSmsSimParamOperation* ReadSimParamsL(TRequestStatus& aObserverRequestStatus);

	
	//Called by CSendAs::CreateMessageL() to create a new outgoing SMS message
	IMPORT_C void CreateMessageL(TMsvId aServiceId);


protected:
	CSmsClientMtm(CRegisteredMtmDll& aRegisteredMtmDll,CMsvSession& aSession);

	// Constructor
	void ConstructL();
	// Now we are pointing to another entry
	void ContextEntrySwitched(); 
	// Lets create a new entry
	void BasicReplyForwardEntry(TMsvEntry& aNewEntry) const;
	CMsvOperation* CreateNewEntryL(TMsvEntry& aNewEntry, TMsvId aDestination,CSmsHeader& aSmsHeader,const CRichText& aBody,TRequestStatus& aCompletionStatus);

	// Validating
	TBool ValidRecipients() const;
	TBool ValidNumber(const TDesC& aNumber) const;

private:

	//Recipient handling
	void DoAddAddresseeL(const TDesC& aRealAddress, const TDesC& aAlias);
	void AddRecipientL(const TDesC& aRealAddress, const TDesC& aAlias);
	void DoAddRecipientL(CSmsHeader* aSmsHeader, const TDesC& aRealAddress, const TDesC& aAlias);

	// Resetting addresseelist and richtext
	void ResetHeader();
	// Find
	TMsvPartList DoFindL(const TDesC& aTextToFind,TMsvPartList aPartList);
	void FindL(const TDesC& aTextToFind, const TMsvPartList aPartList,TMsvPartList& aFoundList);
	void FindInBodyL(const TDesC& aTextToFind, const TMsvPartList& aFoundList, TMsvPartList& aResult);

private:
	CSmsSettings* iServiceSettings;
	TMsvId	iServiceId;
	CSmsHeader* iSmsHeader;

	TChar iRealAddressOpen;
	TChar iRealAddressClose;
	};

#include "smsclnt.inl"

#endif
