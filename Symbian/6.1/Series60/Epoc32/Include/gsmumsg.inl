// GSMUMSG.INL
//
// Copyright (c) 1999 Symbian Ltd.  All rights reserved.
// Adapted by Mikko Rintala



inline CSmsPDU::TSmsPDUType CSmsMessage::Type() const
	{
	return iSmsPDU->Type();
	}

inline TBool CSmsMessage::IsComplete() const
	{
	return iFlags&ESmsFlagIsComplete;
	}

inline TBool CSmsMessage::IsDecoded() const
	{
	return iFlags&ESmsFlagIsDecoded;
	}

inline CSmsMessage::TSmsStorage CSmsMessage::Storage() const
	{
	return (TSmsStorage) (iFlags&ESmsStorageMask);
	}

inline void CSmsMessage::SetStorage(TSmsStorage aStorage)
	{
	iFlags=aStorage|(iFlags&(~ESmsStorageMask));
	}

inline RSmsStorage::TStatus CSmsMessage::Status() const
	{
	return iStatus;
	}

inline void CSmsMessage::SetStatus(RSmsStorage::TStatus aStatus)
	{
	iStatus=aStatus;
	}

inline TInt CSmsMessage::LogServerId() const
	{
	return iLogServerId;
	}

inline void CSmsMessage::SetLogServerId(TInt aId)
	{
	iLogServerId=aId;
	}

inline const TTime& CSmsMessage::Time() const
	{
	return iTime;
	}

inline void CSmsMessage::SetTime(const TTime& aTime)
	{
	iTime=aTime;
	}

inline CSmsPDU& CSmsMessage::SmsPDU()
	{
	return *iSmsPDU;
	}

inline const CSmsPDU& CSmsMessage::SmsPDU() const
	{
	return *iSmsPDU;
	}

inline TPtrC CSmsMessage::ServiceCenterAddress() const
	{
	return iSmsPDU->ServiceCenterAddress();
	}

inline void CSmsMessage::SetServiceCenterAddressL(const TDesC& aAddress)
	{
	iSmsPDU->SetServiceCenterAddressL(aAddress);
	}

inline void CSmsMessage::ParsedServiceCenterAddress(TGsmTelNumber& aParsedAddress) const
	{
	iSmsPDU->ParsedServiceCenterAddress(aParsedAddress);
	}

inline void CSmsMessage::SetParsedServiceCenterAddressL(const TGsmTelNumber& aParsedAddress)
	{
	iSmsPDU->SetParsedServiceCenterAddressL(aParsedAddress);
	}

inline TPtrC CSmsMessage::ToFromAddress() const
	{
	return iSmsPDU->ToFromAddress();
	}

inline void CSmsMessage::SetToFromAddressL(const TDesC& aAddress)
	{
	iSmsPDU->SetToFromAddressL(aAddress);
	}

inline void CSmsMessage::ParsedToFromAddress(TGsmTelNumber& aParsedAddress) const
	{
	iSmsPDU->ParsedToFromAddress(aParsedAddress);
	}

inline void CSmsMessage::SetParsedToFromAddressL(const TGsmTelNumber& aParsedAddress)
	{
	iSmsPDU->SetParsedToFromAddressL(aParsedAddress);
	}

inline CSmsBufferBase& CSmsMessage::Buffer()
	{
	return *iBuffer;
	}

inline const CSmsBufferBase& CSmsMessage::Buffer() const
	{
	return *iBuffer;
	}

inline void CSmsMessage::SetIsComplete(TBool aIsComplete)
	{
	iFlags=aIsComplete? iFlags|ESmsFlagIsComplete: iFlags&(~ESmsFlagIsComplete);
	}

inline void CSmsMessage::SetIsDecoded(TBool aIsDecoded)
	{
	iFlags=aIsDecoded? iFlags|ESmsFlagIsDecoded: iFlags&(~ESmsFlagIsDecoded);
	}

inline TBool CSmsMessage::BinaryData() const
	{
	return iSmsPDU->UserData().IsBinaryData();
	}