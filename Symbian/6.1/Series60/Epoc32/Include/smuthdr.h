///////////////////////////////////////////////////////////////////////////////
//
// SMUTHDR.H
//
// Copyright (c) 2000 Symbian Ltd. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

/*
-----------------------------------------------------------------------------

    DESCRIPTION

    This file contains the header file of the  class CSmsHeader.

-----------------------------------------------------------------------------
*/

#ifndef SMUTHDR_H_
#define SMUTHDR_H_

// Includes

#include <e32base.h>	// CBase etc.
#include <gsmubuf.h>	// CEditableText
#include <bif.h>		// TBioMsgIdType
#include <gsmupdu.h>

// Forward Declarations

class CSmsMessage;
class CSmsMessageSettings;
class CSmsNumber;
class RMsvReadStream;
class RMsvWriteStream;
class CMsvStore;

// Enumerations

// Class Definitions

// CSmsHeader

class CSmsHeader : public CBase
	{
public:
	// For creating a new outgoing 'Submit' Message
	IMPORT_C static CSmsHeader* NewL(CSmsPDU::TSmsPDUType aType,CEditableText& aText);

	// For creating a new incoming 'Deliver' Message
	IMPORT_C static CSmsHeader* NewL(CSmsMessage* aMessage);

	// Destructor
	IMPORT_C ~CSmsHeader();

	// Returns the type of the message
	inline CSmsPDU::TSmsPDUType Type() const;

	// the PDU Types
	inline CSmsSubmit& Submit();
	inline const CSmsSubmit& Submit() const;
	inline CSmsDeliver& Deliver();
	inline const CSmsDeliver& Deliver() const;
	inline CSmsCommand& Command();
	inline const CSmsCommand& Command() const;
	inline CSmsStatusReport& StatusReport();
	inline const CSmsStatusReport& StatusReport() const;
	
	// The Real Message
	inline CSmsMessage& Message();
	inline const CSmsMessage& Message() const;

	inline TBool ReplyPathProvided() const;
	inline void SetReplyPathProvided(TBool aReplyPathProvided);

	//Access to the BioMsgIdType
	inline TBioMsgIdType BioMsgIdType() const;
	inline void SetBioMsgIdType(TBioMsgIdType aBioMsgIdType = EBioMsgIdNbs);
	
	// Service center handling
	inline TPtrC ServiceCenterAddress() const;
	inline void SetServiceCenterAddressL(const TDesC& aAddress);
	inline void ParsedServiceCenterAddress(TGsmTelNumber& aParsedAddress) const;		// are these needed?
	inline void SetParsedServiceCenterAddressL(const TGsmTelNumber& aParsedAddress);

	// Sms Settings handling
	IMPORT_C void SetSmsSettingsL(const CSmsMessageSettings& aSettings);
	IMPORT_C void GetSmsSettingsL(CSmsMessageSettings& aSettings) const;

	// Recipients handling
	inline const CArrayPtrFlat<CSmsNumber>& Recipients() const;
	inline CArrayPtrFlat<CSmsNumber>& Recipients();

	// Who's the sender
	inline void SetFromAddressL(const TDesC& aAddress);
	inline TPtrC FromAddress() const;

	// externalize/internalize
	IMPORT_C void InternalizeL( RMsvReadStream& aStream);
	IMPORT_C void ExternalizeL( RMsvWriteStream& aStream) const;

	// restore/store
	IMPORT_C void RestoreL(CMsvStore& aStore);
	IMPORT_C void StoreL(CMsvStore& aStore) const;

private:
	CSmsHeader(CSmsMessage* aSmsMessage = NULL);
	void ConstructL(CSmsPDU::TSmsPDUType aType, CEditableText& aText);

	enum TSmsHeaderFlags
		{
		ESmsHeaderNoFlags			= 0x00,
		ESmsHeaderReplyPathProvided = 0x01,
		ESmsHeaderCanConcatenate	= 0x02
		};

	TBool CanConcatenate() const;
	void SetCanConcatenate(TBool aCanConcatenate);
	
private:
	CArrayPtrFlat<CSmsNumber> iRecipients;
	CSmsMessage* iMessage;
	TUint32 iFlags;

	//iBioMsgIdType is only used during sending
	//and will be ignored if the TMsvEntry.iBioType == 0.
	//Default is EBioMsgIdNbs.
	TBioMsgIdType iBioMsgIdType; 
	};

#include "smuthdr.inl"

#endif // !defined SMUTHDR_H_

