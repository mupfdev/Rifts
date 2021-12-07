// GSMUELEM.INL
//
// Copyright (c) 1999 Symbian Ltd.  All rights reserved.
//

#include <s32strm.h>
#include <badesca.h>

inline TSmsOctet::operator TInt() const
	{
	return iValue;
	}

inline void TSmsOctet::FillSemiOctets(TInt aNum)
	{
	*this=(aNum/10)|((aNum%10)<<4);
	}

inline TInt TSmsOctet::SemiOctetsToNum() const
	{
	return ((iValue&0x0F)*10) + ((iValue&0xF0)>>4);
	}

inline void TSmsOctet::InternalizeL(RReadStream& aStream)
	{
	aStream >> iValue;
	}

inline void TSmsOctet::ExternalizeL(RWriteStream& aStream) const
	{
	aStream << iValue;
	}

inline TInt TSmsFailureCause::Error() const
	{
	return iValue;
	}

inline void TSmsFailureCause::SetError(TSmsFailureCauseError aError)
	{
	iValue=(TUint8) aError;
	}

TSmsStatus::TSmsStatusValue TSmsStatus::Status() const
	{
	return (TSmsStatusValue) iValue;
	}

inline void TSmsStatus::SetStatus(TSmsStatusValue aValue)
	{
	iValue=(TUint8) aValue;
	}

inline TInt TSmsCommandType::CommandType() const
	{
	return iValue;
	}

inline void TSmsCommandType::SetCommandType(TSmsCommandTypeValue aType)
	{
	iValue=(TUint8) aType;
	}

inline TBool TSmsParameterIndicator::Extension() const
	{
	return iValue&ESmsPIDExtension;
	}

inline void TSmsParameterIndicator::SetExtension(TBool aExtension)
	{
	iValue=(TUint8) (aExtension? iValue|ESmsPIDExtension: (iValue&(~ESmsPIDExtension))|ESmsPIDExtension);
	}

inline TBool TSmsParameterIndicator::UserDataPresent() const
	{
	return iValue&ESmsPIDUserDataPresent;
	}

inline void TSmsParameterIndicator::SetUserDataPresent(TBool aPresent)
	{
	iValue=(TUint8) (aPresent? iValue|ESmsPIDUserDataPresent: iValue&(~ESmsPIDUserDataPresent));
	}

inline TBool TSmsParameterIndicator::DataCodingSchemePresent() const
	{
	return iValue&ESmsPIDDataCodingSchemePresent;
	}

inline void TSmsParameterIndicator::SetDataCodingSchemePresent(TBool aPresent)
	{
	iValue=(TUint8) (aPresent? iValue|ESmsPIDDataCodingSchemePresent: iValue&(~ESmsPIDDataCodingSchemePresent));
	}

inline TBool TSmsParameterIndicator::ProtocolIdentifierPresent() const
	{
	return iValue&ESmsPIDProtocolIdentifierPresent;
	}

inline void TSmsParameterIndicator::SetProtocolIdentifierPresent(TBool aPresent)
	{
	iValue=(TUint8) (aPresent? iValue|ESmsPIDProtocolIdentifierPresent: iValue&(~ESmsPIDProtocolIdentifierPresent));
	}

inline TSmsProtocolIdentifier::TSmsPIDType TSmsProtocolIdentifier::PIDType() const
	{
	return (TSmsPIDType) (iValue&ESmsPIDTypeMask);
	}

inline void TSmsProtocolIdentifier::SetPIDType(TSmsPIDType aSmsPIDType)
	{
	iValue=(TUint8) aSmsPIDType;
	}

inline TSmsDataCodingScheme::TSmsDCSBits7To4 TSmsDataCodingScheme::Bits7To4() const
	{
	return (TSmsDCSBits7To4) (iValue&ESmsDCSBits7To4Mask);
	}

inline void TSmsDataCodingScheme::SetBits7To4(TSmsDCSBits7To4 aBits7To4)
	{
	iValue=(TUint8) (aBits7To4);
	}

inline TInt CSmsAddress::TypeOfNumber() const
	{
	return iTypeOfAddress&ESmsTONMask;
	}

inline void CSmsAddress::SetTypeOfNumber(TSmsTypeOfNumber aTypeOfNumber)
	{
	iTypeOfAddress=(iTypeOfAddress&(~ESmsTONMask))|aTypeOfNumber;
	}

inline TInt TSmsServiceCenterTimeStamp::TimeOffset() const
	{
	return iTimeZoneNumQuarterHours;
	}

inline const TTime& TSmsServiceCenterTimeStamp::Time() const
	{
	return iTime;
	}

inline void TSmsServiceCenterTimeStamp::SetTime(const TTime& aTime)
	{
	iTime=aTime;
	}

inline TSmsFirstOctet::TSmsValidityPeriodFormat TSmsValidityPeriod::ValidityPeriodFormat() const
	{
	return (TSmsFirstOctet::TSmsValidityPeriodFormat) (iFirstOctet&TSmsFirstOctet::ESmsVPFMask);
	}

inline void TSmsValidityPeriod::SetValidityPeriodFormat(TSmsFirstOctet::TSmsValidityPeriodFormat aValidityPeriodFormat)
	{
	iFirstOctet=(iFirstOctet&(~TSmsFirstOctet::ESmsVPFMask)|aValidityPeriodFormat);
	}

inline const TTimeIntervalMinutes& TSmsValidityPeriod::TimeIntervalMinutes() const
	{
	return iTimeIntervalMinutes;
	}

inline void TSmsValidityPeriod::SetTimeIntervalMinutes(const TTimeIntervalMinutes& aTimeIntervalMinutes)
	{
	iTimeIntervalMinutes=aTimeIntervalMinutes;
	}

inline void CSmsAlphabetConverter::ResetUnconvertedNativeCharacters()
	{
	iUnconvertedNativeCharactersPtr.Zero();
	}

inline void CSmsAlphabetConverter::ResetUnconvertedUDElements()
	{
	iUnconvertedUDElementsPtr.Zero();
	}

inline TPtrC CSmsAlphabetConverter::UnconvertedNativeCharacters()
	{
	return iUnconvertedNativeCharactersPtr;
	}

inline TPtrC8 CSmsAlphabetConverter::UnconvertedUDElements()
	{
	return iUnconvertedUDElementsPtr;
	}

inline TSmsDataCodingScheme::TSmsAlphabet CSmsAlphabetConverter::Alphabet() const
	{
	return iSmsAlphabet;
	}

inline TInt CSmsInformationElement::Identifier() const
	{
	return iIdentifier;
	}

inline TPtr8 CSmsInformationElement::Data()
	{
	return iData->Des();
	}

inline TInt CSmsUserData::NumInformationElements() const
	{
	return iInformationElementArray.Count();
	}

inline TInt CSmsCommandData::NumInformationElements() const
	{
	return iInformationElementArray.Count();
	}

inline TInt CSmsCommandData::MaxDataLength() const
	{
	return KSmsMaxDataSize-iBuffer->Des().Length();
	}
