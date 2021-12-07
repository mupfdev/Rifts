// GSMUPDU.H
//
// Copyright (c) 1999-- Symbian Ltd.  All rights reserved.
// 

#if !defined (__GSMUPDU_H__)
#define __GSMUPDU_H__

// Includes

#if !defined (__GSMUELEM_H__)
#include "gsmuelem.h"
#endif 

// forwarded class declarations

class TSms;
class CSmsAddress;

class CSmsPDU : public CBase
	{
public:
	//Message's type
	enum TSmsPDUType
		{
		ESmsDeliver,
		ESmsDeliverReport,
		ESmsSubmit,
		ESmsSubmitReport,
		ESmsStatusReport,
		ESmsCommand
		};
public:
	IMPORT_C static CSmsPDU* NewL(RReadStream &aStream,CCnvCharacterSetConverter& aCharacterSetConverter,RFs& aFs);
	IMPORT_C static CSmsPDU* NewL(const TSms& aSms,CCnvCharacterSetConverter& aCharacterSetConverter,RFs& aFs,TBool aServiceCenterAddressPresent,TBool aIsRPError=EFalse,TBool aIsMobileTerminated=ETrue);
	IMPORT_C static CSmsPDU* NewL(TSmsPDUType aType,CCnvCharacterSetConverter& aCharacterSetConverter,RFs& aFs,TBool aIsRPError=EFalse);

	inline TSmsPDUType Type() const;

	IMPORT_C void ExternalizeL(RWriteStream& aStream) const; 

	IMPORT_C void EncodeMessagePDUL(TSms& aSms,TBool aServiceCenterAddressPresent) const;

	IMPORT_C TPtrC ServiceCenterAddress() const;
	IMPORT_C void SetServiceCenterAddressL(const TDesC& aAddress);
	IMPORT_C void ParsedServiceCenterAddress(TGsmTelNumber& aParsedAddress) const;
	IMPORT_C void SetParsedServiceCenterAddressL(const TGsmTelNumber& aParsedAddress);

	IMPORT_C TPtrC ToFromAddress() const;
	IMPORT_C void SetToFromAddressL(const TDesC& aAddress);
	IMPORT_C void ParsedToFromAddress(TGsmTelNumber& aParsedAddress) const;
	IMPORT_C void SetParsedToFromAddressL(const TGsmTelNumber& aParsedAddress);

//  Functions on data coding scheme
	IMPORT_C TSmsDataCodingScheme::TSmsDCSBits7To4 Bits7To4() const;
	IMPORT_C void SetBits7To4(TSmsDataCodingScheme::TSmsDCSBits7To4 aBits7To4);

	IMPORT_C TSmsDataCodingScheme::TSmsAlphabet Alphabet() const;
	IMPORT_C void SetAlphabet(TSmsDataCodingScheme::TSmsAlphabet aAlphabet);
	IMPORT_C TBool Class(TSmsDataCodingScheme::TSmsClass& aClass) const;
	IMPORT_C void SetClass(TBool aClassDefined,TSmsDataCodingScheme::TSmsClass aClass);
	IMPORT_C TBool TextCompressed() const;
	IMPORT_C void SetTextCompressed(TBool aCompressed);

	IMPORT_C TSmsDataCodingScheme::TSmsIndicationState IndicationState() const;
	IMPORT_C void SetIndicationState(TSmsDataCodingScheme::TSmsIndicationState aState);
	IMPORT_C TSmsDataCodingScheme::TSmsIndicationType IndicationType() const;
	IMPORT_C void SetIndicationType(TSmsDataCodingScheme::TSmsIndicationType aType);

//  Functions on concatenation user data information element
	IMPORT_C TBool TextConcatenated(TBool* aIs16Bit=NULL) const;
	IMPORT_C void SetTextConcatenatedL(TBool aConcatenated,TBool aIs16Bit=EFalse);
	IMPORT_C TInt ConcatenatedMessageReference() const;
	IMPORT_C void SetConcatenatedMessageReference(TInt aReference);
	IMPORT_C TInt NumConcatenatedMessagePDUs() const;
	IMPORT_C void SetNumConcatenatedMessagePDUs(TInt aNum);
	IMPORT_C TInt ConcatenatedMessagePDUIndex() const;
	IMPORT_C void SetConcatenatedMessagePDUIndex(TInt aIndex);

//  Functions for application port addressing
	IMPORT_C TBool ApplicationPortAddressing(TInt& aDestination,TInt& aOriginator,TBool* aIs16Bit=NULL) const;
	IMPORT_C void SetApplicationPortAddressingL(TBool aAddressing,TInt aDestination,TInt aOriginator,TBool aIs16Bit=EFalse);

//  Functions on protocol identifier
	IMPORT_C TSmsProtocolIdentifier::TSmsPIDType PIDType() const;
	IMPORT_C void SetPIDType(TSmsProtocolIdentifier::TSmsPIDType aSmsPIDType);
	IMPORT_C TSmsProtocolIdentifier::TSmsTelematicDeviceIndicator TelematicDeviceIndicator() const;
	IMPORT_C void SetTelematicDeviceIndicator(TSmsProtocolIdentifier::TSmsTelematicDeviceIndicator aIndicator);
	IMPORT_C TSmsProtocolIdentifier::TSmsTelematicDeviceType TelematicDeviceType() const;
	IMPORT_C void SetTelematicDeviceType(TSmsProtocolIdentifier::TSmsTelematicDeviceType aDeviceType);

//  Functions on parameter indicator
	IMPORT_C TBool UserDataPresent() const;
	IMPORT_C void SetUserDataPresent(TBool aPresent);
	IMPORT_C TBool DataCodingSchemePresent() const;
	IMPORT_C void SetDataCodingSchemePresent(TBool aPresent);
	IMPORT_C TBool ProtocolIdentifierPresent() const;
	IMPORT_C void SetProtocolIdentifierPresent(TBool aPresent);

	IMPORT_C CSmsUserData& UserData(); 
	IMPORT_C const CSmsUserData& UserData() const; 

protected:
	CSmsPDU(TSmsPDUType aSmsPDUType);

	virtual const TSmsDataCodingScheme* DataCodingScheme() const;  // Functions made const to avoid too many definitions
	virtual const TSmsProtocolIdentifier* ProtocolIdentifier() const;
	virtual const TSmsParameterIndicator* ParameterIndicator() const;
	virtual const CSmsUserData* UserDataPtr() const; 
	virtual const CSmsAddress* ToFromAddressPtr() const; 

	virtual void ConstructL(CCnvCharacterSetConverter& aCharacterSetConverter,RFs& aFs)=0;
	virtual TUint8* EncodeL(TUint8* aPtr) const=0;
	virtual const TUint8* DecodeL(const TUint8* aPtr,TInt aLength)=0;
	virtual void InternalizeMessagePDUL(RReadStream& aStream)=0;  
	virtual void ExternalizeMessagePDUL(RWriteStream& aStream) const=0; 

private:
	TBool DoTextConcatenated(TInt& aIndex,TBool* aIs16Bit) const;
	void DoSetTextConcatenatedL(TBool aIs16Bit);
	TBool DoApplicationPortAddressing(TInt& index,TInt& aDestination,TInt& aOriginator,TBool* aIs16Bit) const;
	void DoSetApplicationPortAddressingL(TInt aDestination,TInt aOriginator,TBool aIs16Bit);

private:
	const TSmsPDUType iSmsPDUType;

protected:
	CSmsAddress* iServiceCenterAddress; 
	};

class CSmsDeliver : public CSmsPDU
	{
public:
	 CSmsDeliver();
	~CSmsDeliver();

	IMPORT_C TBool MoreMessagesToSend() const;
	IMPORT_C void SetMoreMessagesToSend(TBool aMore);

	IMPORT_C TBool ReplyPath() const;
	IMPORT_C void SetReplyPath(TBool aReplyPath);

	IMPORT_C TBool StatusReportIndication() const;
	IMPORT_C void SetStatusReportIndication(TBool aIndication);

	IMPORT_C void ServiceCenterTimeStamp(TTime& aTime,TInt& aNumQuarterHours);
	IMPORT_C void SetServiceCenterTimeStamp(const TTime& aTime,TInt aNumQuarterHours=0);
	IMPORT_C const TSmsProtocolIdentifier* ProtocolIdentifier() const;

protected:
	const TSmsDataCodingScheme* DataCodingScheme() const;  	
	const CSmsUserData* UserDataPtr() const; 
	const CSmsAddress* ToFromAddressPtr() const; 

	void ConstructL(CCnvCharacterSetConverter& aCharacterSetConverter,RFs& aFs);
	TUint8* EncodeL(TUint8* aPtr) const;
	const TUint8* DecodeL(const TUint8* aPtr,TInt aLength);
	void InternalizeMessagePDUL(RReadStream& aStream);  
	void ExternalizeMessagePDUL(RWriteStream& aStream) const;

private:
	TSmsFirstOctet iFirstOctet;
	CSmsAddress* iOriginalAddress;
	TSmsProtocolIdentifier iProtocolIdentifier;
	TSmsDataCodingScheme iDataCodingScheme;
	TSmsServiceCenterTimeStamp iServiceCenterTimeStamp;
	CSmsUserData* iUserData; 
	};

class CSmsSubmit : public CSmsPDU
	{
public:
	CSmsSubmit();
	~CSmsSubmit();

	IMPORT_C TBool RejectDuplicates() const;
	IMPORT_C void SetRejectDuplicates(TBool aRejectDuplicates);

	IMPORT_C TSmsFirstOctet::TSmsValidityPeriodFormat ValidityPeriodFormat() const;
	IMPORT_C void SetValidityPeriodFormat(TSmsFirstOctet::TSmsValidityPeriodFormat aValidityPeriodFormat);

	IMPORT_C TBool ReplyPath() const;
	IMPORT_C void SetReplyPath(TBool aReplyPath);

	IMPORT_C TBool StatusReportRequest() const;
	IMPORT_C void SetStatusReportRequest(TBool aRequest);

	IMPORT_C TInt MessageReference() const;
	IMPORT_C void SetMessageReference(TInt aMessageReference);

	IMPORT_C const TTimeIntervalMinutes& ValidityPeriod() const;
	IMPORT_C void SetValidityPeriod(const TTimeIntervalMinutes& aTimeIntervalMinutes);

protected:
	const TSmsDataCodingScheme* DataCodingScheme() const;  
	const TSmsProtocolIdentifier* ProtocolIdentifier() const;
	const CSmsUserData* UserDataPtr() const; 
	const CSmsAddress* ToFromAddressPtr() const; 

	void ConstructL(CCnvCharacterSetConverter& aCharacterSetConverter,RFs& aFs);
	TUint8* EncodeL(TUint8* aPtr) const;
	const TUint8* DecodeL(const TUint8* aPtr,TInt aLength);
	void InternalizeMessagePDUL(RReadStream& aStream);  
	void ExternalizeMessagePDUL(RWriteStream& aStream) const; 

private:
	TSmsFirstOctet iFirstOctet;
	TSmsOctet iMessageReference;
	CSmsAddress* iDestinationAddress;
	TSmsProtocolIdentifier iProtocolIdentifier;
	TSmsDataCodingScheme iDataCodingScheme;
	TSmsValidityPeriod iValidityPeriod;
	CSmsUserData* iUserData; 
	};

class CSmsDeliverReport : public CSmsPDU
	{
public:
	CSmsDeliverReport(TBool aIsRPError=EFalse);
	~CSmsDeliverReport();

	inline TBool IsRPError() const;
	inline void SetIsRPError(TBool aIsRPError);
	
	IMPORT_C TInt FailureCause() const;
	IMPORT_C void SetFailureCause(TSmsFailureCause::TSmsFailureCauseError aFailureCause);

protected:
	const TSmsDataCodingScheme* DataCodingScheme() const;  
	const TSmsProtocolIdentifier* ProtocolIdentifier() const;
	const TSmsParameterIndicator* ParameterIndicator() const;
	const CSmsUserData* UserDataPtr() const; 

	void ConstructL(CCnvCharacterSetConverter& aCharacterSetConverter,RFs& aFs);
	TUint8* EncodeL(TUint8* aPtr) const;
	const TUint8* DecodeL(const TUint8* aPtr,TInt aLength);
	void InternalizeMessagePDUL(RReadStream& aStream);  
	void ExternalizeMessagePDUL(RWriteStream& aStream) const; 

private:
	TUint8 iIsRPError;

	TSmsFirstOctet iFirstOctet;
	TSmsFailureCause iFailureCause;
	TSmsParameterIndicator iParameterIndicator;
	TSmsProtocolIdentifier iProtocolIdentifier;
	TSmsDataCodingScheme iDataCodingScheme;
	CSmsUserData* iUserData; 
	};

class CSmsSubmitReport : public CSmsPDU
	{
public:
	CSmsSubmitReport(TBool aIsRPError=EFalse);
	~CSmsSubmitReport();

	inline TBool IsRPError() const;
	inline void SetIsRPError(TBool aIsRPError);
	
	IMPORT_C TInt FailureCause() const;
	IMPORT_C void SetFailureCause(TSmsFailureCause::TSmsFailureCauseError aFailureCause);

protected:
	const TSmsDataCodingScheme* DataCodingScheme() const;  
	const TSmsProtocolIdentifier* ProtocolIdentifier() const;
	const TSmsParameterIndicator* ParameterIndicator() const;
	const CSmsUserData* UserDataPtr() const; 

	void ConstructL(CCnvCharacterSetConverter& aCharacterSetConverter,RFs& aFs);
	TUint8* EncodeL(TUint8* aPtr) const;
	const TUint8* DecodeL(const TUint8* aPtr,TInt aLength);
	void InternalizeMessagePDUL(RReadStream& aStream);  
	void ExternalizeMessagePDUL(RWriteStream& aStream) const; 

private:
	TUint8 iIsRPError;

	TSmsFirstOctet iFirstOctet;
	TSmsFailureCause iFailureCause;
	TSmsParameterIndicator iParameterIndicator;
	TSmsServiceCenterTimeStamp iServiceCenterTimeStamp;
	TSmsProtocolIdentifier iProtocolIdentifier;
	TSmsDataCodingScheme iDataCodingScheme;
	CSmsUserData* iUserData; 
	};

class CSmsStatusReport : public CSmsPDU
	{
public:
	CSmsStatusReport();
	~CSmsStatusReport();

	inline TBool ParameterIndicatorPresent() const;
	inline void SetParameterIndicatorPresent(TBool aPresent);

	IMPORT_C TBool MoreMessagesToSend() const;
	IMPORT_C void SetMoreMessagesToSend(TBool aMore);

	IMPORT_C TSmsFirstOctet::TSmsStatusReportQualifier StatusReportQualifier() const;
	IMPORT_C void SetStatusReportQualifier(TSmsFirstOctet::TSmsStatusReportQualifier aQualifier);

	IMPORT_C TInt MessageReference() const;
	IMPORT_C void SetMessageReference(TInt aMessageReference);

	IMPORT_C void ServiceCenterTimeStamp(TTime& aTime,TInt& aNumQuarterHours);
	IMPORT_C void SetServiceCenterTimeStamp(const TTime& aTime,TInt& aNumQuarterHours);

	IMPORT_C void DischargeTime(TTime& aTime,TInt& aNumQuarterHours);
	IMPORT_C void SetDischargeTime(const TTime& aTime,TInt& aNumQuarterHours);

	IMPORT_C TSmsStatus::TSmsStatusValue Status() const;
	IMPORT_C void SetStatus(TSmsStatus::TSmsStatusValue aValue);

protected:
	const TSmsDataCodingScheme* DataCodingScheme() const;  
	const TSmsProtocolIdentifier* ProtocolIdentifier() const;
	const TSmsParameterIndicator* ParameterIndicator() const;
	const CSmsUserData* UserDataPtr() const; 
	const CSmsAddress* ToFromAddressPtr() const; 

	void ConstructL(CCnvCharacterSetConverter& aCharacterSetConverter,RFs& aFs);
	TUint8* EncodeL(TUint8* aPtr) const;
	const TUint8* DecodeL(const TUint8* aPtr,TInt aLength);
	void InternalizeMessagePDUL(RReadStream& aStream);  
	void ExternalizeMessagePDUL(RWriteStream& aStream) const; 

private:
	TUint8 iParameterIndicatorPresent;

	TSmsFirstOctet iFirstOctet;
	TSmsOctet iMessageReference;
	CSmsAddress* iRecipientAddress;
	TSmsServiceCenterTimeStamp iServiceCenterTimeStamp;
	TSmsServiceCenterTimeStamp iDischargeTime;
	TSmsStatus iStatus;
	TSmsParameterIndicator iParameterIndicator;
	TSmsProtocolIdentifier iProtocolIdentifier;
	TSmsDataCodingScheme iDataCodingScheme;
	CSmsUserData* iUserData; 
	};

class CSmsCommand : public CSmsPDU
	{
public:
	CSmsCommand();
	~CSmsCommand();

	IMPORT_C TBool StatusReportRequest() const;
	IMPORT_C void SetStatusReportRequest(TBool aRequest);

	IMPORT_C TInt MessageReference() const;
	IMPORT_C void SetMessageReference(TInt aMessageReference);

	IMPORT_C TInt CommandType() const;
	IMPORT_C void SetCommandType(TSmsCommandType::TSmsCommandTypeValue aCommandType);

	IMPORT_C TInt MessageNumber() const;
	IMPORT_C void SetMessageNumber(TInt aMessageNumber);

	IMPORT_C TInt NumInformationElements() const;
	IMPORT_C CSmsInformationElement& InformationElement(TInt aIndex) const;
	IMPORT_C TBool InformationElementIndex(CSmsInformationElement::TSmsInformationElementIdentifier aIdentifier,
		TInt& aIndex) const;
	IMPORT_C void AddInformationElementL(CSmsInformationElement::TSmsInformationElementIdentifier aIdentifier,
		TDesC8& aData);
	IMPORT_C void RemoveInformationElement(TInt aIndex);

	IMPORT_C TInt MaxCommandDataLength() const;
	IMPORT_C TPtrC8 CommandData() const;
	IMPORT_C void SetCommandDataL(const TDesC8& aData);

protected:
	const TSmsProtocolIdentifier* ProtocolIdentifier() const;
	const CSmsAddress* ToFromAddressPtr() const; 

	void ConstructL(CCnvCharacterSetConverter& aCharacterSetConverter,RFs& aFs);
	TUint8* EncodeL(TUint8* aPtr) const;
	const TUint8* DecodeL(const TUint8* aPtr,TInt aLength);
	void InternalizeMessagePDUL(RReadStream& aStream);  
	void ExternalizeMessagePDUL(RWriteStream& aStream) const; 
	void DoSetStatusReportRequest(TBool aRequest);

private:
	TSmsFirstOctet iFirstOctet;
	TSmsOctet iMessageReference;
	TSmsProtocolIdentifier iProtocolIdentifier;
	TSmsCommandType	iCommandType;
	TSmsOctet iMessageNumber;
	CSmsAddress* iDestinationAddress;
	CSmsCommandData* iCommandData;
	};

#include "gsmupdu.inl"



#endif // !defined __GSMUPDU_H__

