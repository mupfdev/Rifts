// GSMUELEM.H
//
// Copyright (c) 1999-2000 Symbian Ltd.  All rights reserved.
// 

/**
 *
 * @file gsmuelem.h   This file define the classes for the different PDU elements
 *
 */

#if !defined (__GSMUELEM_H__)
#define __GSMUELEM_H__

// Includes

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif
#if !defined(__E32SBASE_H__)
#include <e32base.h>
#endif

#include "etools.h"

class RFs;
#if !defined (__CHARCONV_H__)
#include <charconv.h>
#endif


class RReadStream;
class RWriteStream;
struct TGsmTelNumber;

// class declarations

// TSmsOctet - the base class of the units of a sms message

class TSmsOctet
	{
public:
	TSmsOctet(TInt aValue=0);
	inline operator TInt() const;
	const TSmsOctet& operator = (TInt aValue);
	inline void FillSemiOctets(TInt aNum);
	inline TInt SemiOctetsToNum() const;
	TUint8* EncodeL(TUint8* aPtr) const;
	const TUint8* DecodeL(const TUint8* aPtr);
	inline void InternalizeL(RReadStream& aStream);
	inline void ExternalizeL(RWriteStream& aStream) const;
protected:
	TUint8 iValue;
	};

// TSmsFirstOctet - the first octet of sms pdu

class TSmsFirstOctet : public TSmsOctet
	{
public:
	//  enums for first octet of all SMS PDUs
	enum TSmsMTI
		{
		ESmsMTIDeliverOrDeliverReport=0x00,
		ESmsMTISubmitOrSubmitReport=0x01,
		ESmsMTIStatusReportOrCommand=0x02,

		ESmsMTIMask=0x03
		};
	// Found in first octet of Submit and Deliver and possibly Submit Report, DeliverReport ans SmsStatusReport
	enum TSmsUDHI   		
		{
		ESmsUDHIHeaderNotPresent=0x00,
		ESmsUDHIHeaderPresent=0x40,

		ESmsUDHIMask=0x40
		};
	// Found in first octet of Submit and Deliver  
	enum TSmsReplyPath   		
		{
		ESmsReplyPathNone=0x00,
		ESmsReplyPathExists=0x080,

		ESmsReplyPathMask=0x80
		};
	//  Found in Deliver and SatusReport
	enum TSmsMoreMessagesToSend
		{
		ESmsMoreMessagesToSend=0x00,
		ESmsNoMoreMessagesToSend=0x04,

		ESmsMoreMessagesToSendMask=0x04,
		};
	//	Found in Status Report 
	enum TSmsStatusReportIndicator
		{
		ESmsStatusReportNotReturned=0x00,
		ESmsStatusReportReturned=0x20,

		ESmsStatusReportIndicatorMask=0x20
		};
	//  Found in Submit
	enum TSmsRejectDuplicates
		{
		ESmsAcceptDuplicates=0x00,
		ESmsRejectDuplicates=0x04,

		ESmsRejectDuplicatesMask=0x04
		};
	// Found in Status Report
	enum TSmsStatusReportQualifier
		{
		ESmsStatusReportResultOfSubmit=0x00,
		ESmsStatusReportResultOfCommand=0x20,

		ESmsStatusReportQualifierMask=0x20
		};
	// Sms Validity Period Format
	enum TSmsValidityPeriodFormat
		{
		ESmsVPFNone=0x00,
		ESmsVPFEnhanced=0x08,	// was ESmsVPFReserved, the new GSM spec!
		ESmsVPFInteger=0x10,    // relative validity period
		ESmsVPFSemiOctet=0x18,  // absolute validity period

		ESmsVPFMask=0x18
		};
	// Found in SmsSubmit and SmsCommand
	enum TSmsStatusReportRequest
		{
		ESmsStatusReportNotRequested=0x00,
		ESmsStatusReportRequested=0x20,

		ESmsStatusReportRequestMask=0x20
		};
public:
	TSmsFirstOctet(TInt aValue=0);
	const TSmsFirstOctet& operator = (TInt aValue);  //  Review
	};

// TSmsFailureCause - in deliver and submit errors

class TSmsFailureCause : public TSmsOctet
	{
public:
	enum TSmsFailureCauseError
		{
//  Reserved values
//		....
//		....
//  PID errors
		ESmsPIDErrorTelematicInterworkingNotSupported=0x80,
		ESmsPIDErrorShortMessageType0NotSupported=0x81,
		ESmsPIDErrorCannotReplaceShortMessage=0x82,
		ESmsPIDErrorReserved1=0x83,
		ESmsPIDErrorReserved2=0x84,
		ESmsPIDErrorReserved3=0x85,
		ESmsPIDErrorReserved4=0x86,
		ESmsPIDErrorReserved5=0x87,
		ESmsPIDErrorReserved6=0x88,
		ESmsPIDErrorReserved7=0x89,
		ESmsPIDErrorReserved8=0x8A,
		ESmsPIDErrorReserved9=0x8B,
		ESmsPIDErrorReserved10=0x8C,
		ESmsPIDErrorReserved11=0x8D,
		ESmsPIDErrorReserved12=0x8E,
		ESmsPIDErrorUnspecified=0x8F,
//  DCS errors
		ESmsDCSErrorAlphabetNotSupported=0x90,
		ESmsDCSErrorMessageClassNotSupported=0x91,
		ESmsDCSErrorReserved1=0x92,
		ESmsDCSErrorReserved2=0x93,
		ESmsDCSErrorReserved3=0x94,
		ESmsDCSErrorReserved4=0x95,
		ESmsDCSErrorReserved5=0x96,
		ESmsDCSErrorReserved6=0x97,
		ESmsDCSErrorReserved7=0x98,
		ESmsDCSErrorReserved8=0x99,
		ESmsDCSErrorReserved9=0x9A,
		ESmsDCSErrorReserved10=0x9B,
		ESmsDCSErrorReserved11=0x9C,
		ESmsDCSErrorReserved12=0x9D,
		ESmsDCSErrorReserved13=0x9E,
		ESmsDCSErrorUnspecified=0x9F,
//  CommandErrors
		ESmsCommandErrorCannotBeActioned=0xA0,
		ESmsCommandErrorUnsupported=0xA1,
		ESmsCommandErrorReserved1=0xA2,
		ESmsCommandErrorReserved2=0xA3,
		ESmsCommandErrorReserved3=0xA4,
		ESmsCommandErrorReserved4=0xA5,
		ESmsCommandErrorReserved5=0xA6,
		ESmsCommandErrorReserved6=0xA7,
		ESmsCommandErrorReserved7=0xA8,
		ESmsCommandErrorReserved8=0xA9,
		ESmsCommandErrorReserved9=0xAA,
		ESmsCommandErrorReserved10=0xAB,
		ESmsCommandErrorReserved11=0xAC,
		ESmsCommandErrorReserved12=0xAD,
		ESmsCommandErrorReserved13=0xAE,
		ESmsCommandErrorUnspecified=0xAF,
//
		ESmsErrorPDUNotSupported=0xB0,
//  Reserved values
//		....
//		....
		ESmsErrorSCBusy=0xC0,
		ESmsErrorNoSCSubscription=0xC1,
		ESmsErrorNoSCSystemFailure=0xC2,
		ESmsErrorInvalidSMEAddress=0xC3,
		ESmsErrorDestinationSMEBarred=0xC4,
		ESmsErrorSMRejectedDuplicateSM=0xC5,
		ESmsErrorVPFNotSupported=0xC6,
		ESmsErrorVPNotSupported=0xC7,
//  Reserved values
//		....
//		....
		ESmsErrorSIMSMSStorageFull=0xD0,
		ESmsErrorNoSMSStorageCapabilityOnSIM=0xD1,
		ESmsErrorErrorInMS=0xD2,
		ESmsErrorMemoryCapacityExceded=0xD3,
		ESmsErrorSIMApplicationToolkitBusy=0xD4,
		ESmsErrorSIMDataDownloadError=0xD5,
//  Reserved values
//		....
//		....
		ESmsApplicationError1=0xE0,
		ESmsApplicationError2=0xE1,
		ESmsApplicationError3=0xE2,
		ESmsApplicationError4=0xE3,
		ESmsApplicationError5=0xE4,
		ESmsApplicationError6=0xE5,
		ESmsApplicationError7=0xE6,
		ESmsApplicationError8=0xE7,
		ESmsApplicationError9=0xE8,
		ESmsApplicationError10=0xE9,
		ESmsApplicationError11=0xEA,
		ESmsApplicationError12=0xEB,
		ESmsApplicationError13=0xEC,
		ESmsApplicationError14=0xED,
		ESmsApplicationError15=0xEE,
		ESmsApplicationError16=0xEF,
		ESmsApplicationError17=0xF0,
		ESmsApplicationError18=0xF1,
		ESmsApplicationError19=0xF2,
		ESmsApplicationError20=0xF3,
		ESmsApplicationError21=0xF4,
		ESmsApplicationError22=0xF5,
		ESmsApplicationError23=0xF6,
		ESmsApplicationError24=0xF7,
		ESmsApplicationError25=0xF8,
		ESmsApplicationError26=0xF9,
		ESmsApplicationError27=0xFA,
		ESmsApplicationError28=0xFB,
		ESmsApplicationError29=0xFC,
		ESmsApplicationError30=0xFD,
		ESmsApplicationError31=0xFE,
//
		ESmsErrorUnspecified=0xFF
		};
public:
	TSmsFailureCause();
	inline TInt Error() const;
	inline void SetError(TSmsFailureCauseError aError);
	};

// TSmsStatus - in status report

class TSmsStatus : public TSmsOctet
	{	
public:
	enum TSmsStatusValue
		{
//  Short message transaction completed
		ESmsShortMessageReceivedBySME=0x00,
		ESmsShortMessageForwardedBySCToSMEButUnconfirmedBySC=0x01,
		ESmsShortMessageReplacedBySC=0x02,
//  Reserved values
//		....
//		....
//  Temporary error, SC still trying to transfer SM
		ESmsTempError1StatusCongestion=0x20,
		ESmsTempError1StatusSMEBusy=0x21,
		ESmsTempError1StatusNoResponseFromSME=0x22,
		ESmsTempError1StatusServiceRejected=0x23,
		ESmsTempError1StatusQualityOfServiceNotAvailable=0x24,
		ESmsTempError1StatusErrorInSME=0x25,
//  Reserved values
//		....
//		....
//  Permanent error, SC is not making any more transfer attempts
		ESmsPermErrorRemoteProcedureError=0x40,
		ESmsPermErrorIncompatibleDestination=0x41,
		ESmsPermErrorConnectionRejectedBySME=0x42,
		ESmsPermErrorNotObtainable=0x43,
		ESmsPermErrorQualityOfServiceNotAvailable2=0x44,
		ESmsPermErrorNoInterworkingAvailable=0x45,
		ESmsPermErrorSMValidityPeriodExpired=0x46,
		ESmsPermErrorSMDeletedByOriginatingSME=0x47,
		ESmsPermErrorSMDeletedBySCAdministration=0x48,
		ESmsPermErrorDoesNotExist=0x49,
//  Reserved values
//		....
//		....
//  Temporary error, SC is not making any more transfer attempts
		ESmsTempError2Congestion=0x60,
		ESmsTempError2SMEBusy=0x61,
		ESmsTempError2NoResponseFromSME=0x62,
		ESmsTempError2ServiceRejected=0x63,
		ESmsTempError2QualityOfServiceNotAvailable=0x64,
		ESmsTempError2ErrorInSME=0x65,
//  Reserved values
//		....
//		....
		};
public:
	TSmsStatus();
	inline TSmsStatus::TSmsStatusValue Status() const;
	inline void SetStatus(TSmsStatusValue aValue);
	};

// TSmsPI - in reports and command

class TSmsParameterIndicator : public TSmsOctet
	{
public:
	enum TSmsPIBits
		{
		ESmsPIDProtocolIdentifierPresent=0x01,
		ESmsPIDDataCodingSchemePresent=0x02,
		ESmsPIDUserDataPresent=0x04,
		ESmsPIDReserved1=0x08,
		ESmsPIDReserved2=0x10,
		ESmsPIDReserved3=0x20,
		ESmsPIDReserved4=0x40,
		ESmsPIDExtension=0x80
		};
public:
	TSmsParameterIndicator();
	inline TBool Extension() const;
	inline void SetExtension(TBool aExtension);
	inline TBool UserDataPresent() const;
	inline void SetUserDataPresent(TBool aPresent);
	inline TBool DataCodingSchemePresent() const;
	inline void SetDataCodingSchemePresent(TBool aPresent);
	inline TBool ProtocolIdentifierPresent() const;
	inline void SetProtocolIdentifierPresent(TBool aPresent);
	};

// TSmsPID - conversion (None, Fax, Mail, etc.)

class TSmsProtocolIdentifier : public TSmsOctet
	{
public:
	enum TSmsPIDType
		{
		ESmsPIDTelematicInterworking=0x00,	
		ESmsPIDShortMessageType=0x40,
		ESmsPIDReserved=0x80,
		ESmsPIDSCSpecificUse=0xC0,

		ESmsPIDTypeMask=0xC0
		};
//  For interworking info
	enum TSmsTelematicDeviceIndicator
		{
		ESmsNoTelematicDevice=0x00,
		ESmsTelematicDevice=0x20,

		EPIDTelematicDeviceIndicatorMask=0x20
		};
	// not in use at the moment
	enum TSmsTelematicDeviceType
		{
		ESmsSCSpecificDevice=0x00,
		ESmsTelex=0x01,
		ESmsGroup3TeleFax=0x02,
		ESmsGroup4TeleFax=0x03,
		ESmsVoiceTelephone=0x04,
		ESmsERMES=0x05,
		ESmsNationalPagingSystem=0x06,
		ESmsVideotex=0x07,
		ESmsTeletexCarrierUnspecified=0x08,
		ESmsTeletexPSPDN=0x09,
		ESmsTeletexCSPDN=0x0A,
		ESmsTeletexAnaloguePSTN=0x0B,
		ESmsTeletexDigitalISDN=0x0C,
		ESmsUCI=0x0D,
		ESmsReserved1=0x0E,
		ESmsReserved2=0x0F,
		ESmsMessageHandlingFacility=0x10,
		ESmsX400MessageHandlingSystem=0x11,
		ESmsInternetElectronicMail=0x12,
		ESmsReserved3=0x13,
		ESmsReserved4=0x14,
		ESmsReserved5=0x15,
		ESmsReserved6=0x16,
		ESmsReserved7=0x17,
		ESmsSCSpecific1=0x18,
		ESmsSCSpecific2=0x19,
		ESmsSCSpecific3=0x1A,
		ESmsSCSpecific4=0x1B,
		ESmsSCSpecific5=0x1C,
		ESmsSCSpecific6=0x1D,
		ESmsSCSpecific7=0x1E,
		ESmsGsmMobileStation=0x1F,

		ESmsTelematicDeviceTypeMask=0x1F
		};
//  For no interworking info
	enum TSmsShortMessageALProtocol
		{
		ESmsShortMessageALProtocolMask=0x0F
		};
	

//  For short message type
	enum TSmsShortMessageType
		{
		ESmsShortMessageType0=0x00,
		ESmsReplaceShortMessageType1=0x01,
		ESmsReplaceShortMessageType2=0x02,
		ESmsReplaceShortMessageType3=0x03,
		ESmsReplaceShortMessageType4=0x04,
		ESmsReplaceShortMessageType5=0x05,
		ESmsReplaceShortMessageType6=0x06,
		ESmsReplaceShortMessageType7=0x07,
//  Reserved values
//		....
//		....
		ESmsReturnCallMesage=0x1F,
//  Reserved values
//		....
//		....
		ESmsMEDepersonalizationShortMessage=0x3E,
		ESmsSIMDataDownLoad=0x3F,

		//ESmsShortMessageTypeMask=0x1F
		ESmsShortMessageTypeMask=0x3F
		};
public:
	TSmsProtocolIdentifier();
	inline TSmsPIDType PIDType() const;
	inline void SetPIDType(TSmsPIDType aSmsPIDType);
	TSmsTelematicDeviceIndicator TelematicDeviceIndicator() const;
	void SetTelematicDeviceIndicator(TSmsTelematicDeviceIndicator aIndicator);
	TSmsTelematicDeviceType TelematicDeviceType() const;
	void SetTelematicDeviceType(TSmsTelematicDeviceType aDeviceType);
	TInt ShortMessageALProtocol() const;
	void SetShortMessageALProtocol(TSmsShortMessageALProtocol aProtocol); 
	TInt ShortMessageType() const;
	void SetShortMessageType(TSmsShortMessageType aShortMessageType);
	};

// TSmsDCS - 7, 8bits or unicode.. and class, too

class TSmsDataCodingScheme : public TSmsOctet
	{
public:
	enum TSmsDCSBits7To4
		{
		ESmsDCSTextUncompressedWithNoClassInfo=0x00,
		ESmsDCSTextUncompressedWithClassInfo=0x10,
		ESmsDCSTextCompressedWithNoClassInfo=0x20,
		ESmsDCSTextCompressedWithClassInfo=0x30,

		ESmsDCSReserved1=0x40,
		ESmsDCSReserved2=0x50,
		ESmsDCSReserved3=0x60,
		ESmsDCSReserved4=0x70,
		ESmsDCSReserved5=0x80,
		ESmsDCSReserved6=0x90,
		ESmsDCSReserved7=0xA0,
		ESmsDCSReserved8=0xB0,

		ESmsDCSMessageWaitingIndicationDiscardMessage=0xC0,

		ESmsDCSMessageWaitingIndication7Bit=0xD0,  //  7 bit User data 
		ESmsDCSMessageWaitingIndicationUCS2=0xE0,  //  unicode User data 

		ESmsDCSTextUncompressed7BitOr8Bit=0xF0,

		ESmsDCSBits7To4Mask=0xF0
		};
	
	enum TSmsAlphabet
		{
		ESmsAlphabet7Bit=0x00,
		ESmsAlphabet8Bit=0x04,
		ESmsAlphabetUCS2=0x08,
		ESmsAlphabetReserved=0x0C,

		ESmsAlphabetMask=0x0C,
		};
	enum TSmsClass
		{
		ESmsClass0=0x00,
		ESmsClass1=0x01,
		ESmsClass2=0x02,
		ESmsClass3=0x03,

		ESmsClassMask=0x03,
		};

	enum TSmsIndicationState
		{
		ESmsIndicationInactive=0x00,
		ESmsIndicationActive=0x08,

		ESmsIndicationStateMask=0x08
		};
	enum TSmsIndicationType
		{
		ESmsVoicemailMessageWaiting=0x00,
		ESmsFaxMessageWaiting=0x01,
		ESmsElectronicMailMessageWaiting=0x02,
		ESmsFaxOtherMessageWaiting=0x03,

		ESmsIndicationTypeMask=0x03
		};
public:
	TSmsDataCodingScheme();
	inline TSmsDCSBits7To4 Bits7To4() const;
	inline void SetBits7To4(TSmsDCSBits7To4 aBits7To4);
//  Normal SMS settings
	TBool TextCompressed() const;
	void SetTextCompressed(TBool aCompressed);
	TSmsAlphabet Alphabet() const;
	void SetAlphabet(TSmsAlphabet aAlphabet);
	TBool Class(TSmsClass& aClass) const;
	void SetClass(TBool aClassDefined,TSmsClass aClass);
//  Message waiting settings 
	TSmsIndicationState IndicationState() const;
	void SetIndicationState(TSmsIndicationState aState);
	TSmsIndicationType IndicationType() const;
	void SetIndicationType(TSmsIndicationType aType);
	};

//
// CSmsAlphabetConverter - piecewise character set conversion to / from
// unpacked user data elements.
//

class CSmsAlphabetConverter : public CBase
	{
public:
// Construction and destruction methods
	IMPORT_C static CSmsAlphabetConverter* NewLC(CCnvCharacterSetConverter& aCharacterSetConverter,RFs& aFs,TSmsDataCodingScheme::TSmsAlphabet aSmsAlphabet,TBool aIsBinary);
	IMPORT_C ~CSmsAlphabetConverter();

// Enumerated types and structs
	enum TSmsAlphabetWidthConversion
		{
		ESmsAlphabetWidthConversionFixed,
		ESmsAlphabetWidthConversionVariable
		};

	struct TSmsAlphabetConversionProperties
		{
		TSmsAlphabetWidthConversion iWidthConversion;
		TInt iUDElementsPerNativeCharacter;
		};

// Conversion methods
	void ConversionPropertiesL(TSmsAlphabetConversionProperties& aConversionProperties) const;
	IMPORT_C TPtrC8 ConvertFromNativeL(const TDesC& aNativeCharacters);
	IMPORT_C TPtrC ConvertToNativeL(const TDesC8& aUDElements);
	TBool IsSupportedL(TChar aChar);

// Unconverted buffer methods
	inline void ResetUnconvertedNativeCharacters();
	inline void ResetUnconvertedUDElements();
	inline TPtrC UnconvertedNativeCharacters();
	inline TPtrC8 UnconvertedUDElements();

// Getter / setters
	inline TSmsDataCodingScheme::TSmsAlphabet Alphabet() const;

private:
// Private construction methods
	CSmsAlphabetConverter(CCnvCharacterSetConverter& aCharacterSetConverter,RFs& aFs,TSmsDataCodingScheme::TSmsAlphabet aSmsAlphabet,TBool aIsBinary);
	void ConstructL();

// Private conversion preparation methods
	void PrepareForConversionFromNativeL();
	void PrepareForConversionToNativeL();

// Private buffer helper methods
	TPtr16 CheckAllocBufferL(HBufC16** aBuffer,TInt aMaxLength,TInt aUsedLength);
	TPtr8 CheckAllocBufferL(HBufC8** aBuffer,TInt aMaxLength,TInt aUsedLength);

// Private constants
	enum
		{
		KMaxSmsAlphabetConversionRetries=4
		};

	enum
		{
		KMinSmsAlphabetConversionAllocIncrement=4
		};

private:
	CLASSNAMEDECL(CSmsAlphabetConverter);
	CCnvCharacterSetConverter& iCharacterSetConverter;
	RFs& iFs;
	TSmsDataCodingScheme::TSmsAlphabet iSmsAlphabet;
	TBool iIsBinary;
	HBufC* iConvertedNativeCharacters;
	HBufC8* iConvertedUDElements;
	HBufC* iUnconvertedNativeCharacters;
	TPtr iUnconvertedNativeCharactersPtr;
	HBufC8* iUnconvertedUDElements;
	TPtr8 iUnconvertedUDElementsPtr;
	};

// CSmsAddress - address of the recipient or SC

class CSmsAddress : public CBase
	{
public:
	enum TSmsFirstBit
		{
		ESmsFirstBitMask=0x80
		};
	//type of number
	enum TSmsTypeOfNumber
		{
		ESmsTONUnknown=0x00,
		ESmsTONInternationalNumber=0x10,
		ESmsTONNationalNumber=0x20,
		ESmsTONNetworkSpecificNumber=0x30,
		ESmsTONSubscriberNumber=0x40,
		ESmsTONAlphaNumeric=0x50,
		ESmsTONAbbreviatedNumber=0x60,
		ESmsTONReserverved=0x70,

		ESmsTONMask=0x70
		};
	enum TSmsNumberingPlanIdentification
		{
		ESmsNPIUnknown=0x00,
		ESmsNPIISDNTelephoneNumberingPlan=0x01,
		ESmsNPIDataNumberingPlan=0x03,
		ESmsNPITelexNumberingPlan=0x04,
		ESmsNPINationalNumberingPlan=0x08,
		ESmsNPIPrivateNumberingPlan=0x09,
		ESmsNPIERMESNumberingPlan=0x0A,
		ESmsNPIReservedForExtension=0x0F,

		ESmsNPIMask=0x0F
		};
	enum
		{
		KSmsAddressMaxAddressValueLength=10	// octets
		};
public:
	static CSmsAddress* NewL(CCnvCharacterSetConverter& aCharacterSetConverter,RFs& aFs);
	~CSmsAddress();
	TPtrC Address() const;
	void SetAddressL(const TDesC& aAddress);
	void ParsedAddress(TGsmTelNumber& aParsedAddress) const;
	void SetParsedAddressL(const TGsmTelNumber& aParsedAddress);

	inline TInt TypeOfNumber() const;
	inline void SetTypeOfNumber(TSmsTypeOfNumber aTypeOfNumber);
	TInt NumberPlanIdentification() const;
	void SetNumberPlanIdentification(TSmsNumberingPlanIdentification aNumberingPlanIdentification);

	TUint8* EncodeL(TUint8* aPtr) const;
	const TUint8* DecodeL(const TUint8* aPtr);
	void InternalizeL(RReadStream& aStream);
	void ExternalizeL(RWriteStream& aStream) const;
private:
	CSmsAddress(CCnvCharacterSetConverter& aCharacterSetConverter,RFs& aFs);
	void NewBufferL(TInt aLength);	
	void DoSetParsedAddressL(const TDesC& aAddress);
private:
	CLASSNAMEDECL(CSmsAddress);
	CCnvCharacterSetConverter& iCharacterSetConverter;
	RFs& iFs;
	TSmsOctet iTypeOfAddress;
	HBufC* iBuffer;	
	};

//TSmsServiceCenterTimeStamp - SC time stamp

class TSmsServiceCenterTimeStamp
	{
public:
	enum {KSmsMaxTimeZoneNumQuarterHours=79};
	enum TSmsTimeZoneSignBit
		{
		ESmsTimeZonePositive=0x00,
		ESmsTimeZoneNegative=0x08,

		ESmsTimeZoneSignBitMask=0x08
		};
public:
	TSmsServiceCenterTimeStamp();
	inline TInt TimeOffset() const;
	void SetTimeOffset(TInt aNumQuarterHours);
	inline const TTime& Time() const;
	inline void SetTime(const TTime& aTime);
	TUint8* EncodeL(TUint8* aPtr) const;
	const TUint8* DecodeL(const TUint8* aPtr);
	void InternalizeL(RReadStream& aStream);
	void ExternalizeL(RWriteStream& aStream) const;
private:
	TTime iTime;
	TInt iTimeZoneNumQuarterHours;
	};

// TSmsValidityPeriod - validity period of the sms message

class TSmsValidityPeriod
	{
public:
	enum TValidityPeriodUnitInMinutes
		{
		EFiveMinuteUnitInMinutes=5,
		EHalfHourUnitInMinutes=30,
		EOneDayUnitInMinutes=1440,
		EOneWeekUnitInMinutes=7*EOneDayUnitInMinutes
		};
	enum TValidityPeriodUnitLimitInMinutes
		{
		EFiveMinuteUnitLimitInMinutes=24*EHalfHourUnitInMinutes,
		EHalfHourUnitLimitInMinutes=EOneDayUnitInMinutes,
		EOneDayUnitLimitInMinutes=30*EOneDayUnitInMinutes,
		EOneWeekUnitLimitInMinutes=63*EOneWeekUnitInMinutes
		};
	enum TValidityPeriodLimit
		{
		EFiveMinuteUnitLimit=143,
		EHalfHourUnitLimit=167,
		EOneDayUnitLimit=196,
		EOneWeekUnitLimit=255
		};
public:
	TSmsValidityPeriod(TSmsFirstOctet& aFirstOctet);
	inline TSmsFirstOctet::TSmsValidityPeriodFormat ValidityPeriodFormat() const;
	inline void SetValidityPeriodFormat(TSmsFirstOctet::TSmsValidityPeriodFormat aValidityPeriodFormat);
	inline const TTimeIntervalMinutes& TimeIntervalMinutes() const;
	inline void SetTimeIntervalMinutes(const TTimeIntervalMinutes& aTimeIntervalMinutes);
	TTime Time() const;
	TUint8* EncodeL(TUint8* aPtr) const;
	const TUint8* DecodeL(const TUint8* aPtr);
	void InternalizeL(RReadStream& aStream);
	void ExternalizeL(RWriteStream& aStream) const;
private:
	TSmsFirstOctet& iFirstOctet;
	TTimeIntervalMinutes iTimeIntervalMinutes;
	};

// CSmsInformationElement - 

class CSmsInformationElement : public CBase
	{
public:
	enum TSmsInformationElementIdentifier
		{
		ESmsIEIConcatenatedShortMessages8BitReference=0x00,
		ESmsIEISpecialSMSMessageIndication=0x01,
		ESmsIEIReserved=0x02,
		ESmsIEIValueNotUsed=0x03,
		ESmsIEIApplicationPortAddressing8Bit=0x04,
		ESmsIEIApplicationPortAddressing16Bit=0x05,
		ESmsIEISMSCControlParameters=0x06,
		ESmsIEIUDHSourceIndicator=0x07,
		ESmsIEIConcatenatedShortMessages16BitReference=0x08,
		ESmsIEIWirelessControlMessageProtocol=0x09,
//  Reserved values
//		....
//		....
		ESmsIEISIMToolkitSecurityHeaders1=0x70,
		ESmsIEISIMToolkitSecurityHeaders2=0x71,
		ESmsIEISIMToolkitSecurityHeaders3=0x72,
		ESmsIEISIMToolkitSecurityHeaders4=0x73,
		ESmsIEISIMToolkitSecurityHeaders5=0x74,
		ESmsIEISIMToolkitSecurityHeaders6=0x75,
		ESmsIEISIMToolkitSecurityHeaders7=0x76,
		ESmsIEISIMToolkitSecurityHeaders8=0x77,
		ESmsIEISIMToolkitSecurityHeaders9=0x78,
		ESmsIEISIMToolkitSecurityHeaders10=0x79,
		ESmsIEISIMToolkitSecurityHeaders11=0x7A,
		ESmsIEISIMToolkitSecurityHeaders12=0x7B,
		ESmsIEISIMToolkitSecurityHeaders13=0x7C,
		ESmsIEISIMToolkitSecurityHeaders14=0x7D,
		ESmsIEISIMToolkitSecurityHeaders15=0x7E,
		ESmsIEISIMToolkitSecurityHeaders16=0x7F,
		ESmsIEISMEToSMESpecificUse1=0x80,
		ESmsIEISMEToSMESpecificUse2=0x81,
		ESmsIEISMEToSMESpecificUse3=0x82,
		ESmsIEISMEToSMESpecificUse4=0x83,
		ESmsIEISMEToSMESpecificUse5=0x84,
		ESmsIEISMEToSMESpecificUse6=0x85,
		ESmsIEISMEToSMESpecificUse7=0x86,
		ESmsIEISMEToSMESpecificUse8=0x87,
		ESmsIEISMEToSMESpecificUse9=0x88,
		ESmsIEISMEToSMESpecificUse10=0x89,
		ESmsIEISMEToSMESpecificUse11=0x8A,
		ESmsIEISMEToSMESpecificUse12=0x8B,
		ESmsIEISMEToSMESpecificUse13=0x8C,
		ESmsIEISMEToSMESpecificUse14=0x8D,
		ESmsIEISMEToSMESpecificUse15=0x8E,
		ESmsIEISMEToSMESpecificUse16=0x8F,
		ESmsIEISMEToSMESpecificUse17=0x90,
		ESmsIEISMEToSMESpecificUse18=0x91,
		ESmsIEISMEToSMESpecificUse19=0x92,
		ESmsIEISMEToSMESpecificUse20=0x93,
		ESmsIEISMEToSMESpecificUse21=0x94,
		ESmsIEISMEToSMESpecificUse22=0x95,
		ESmsIEISMEToSMESpecificUse23=0x96,
		ESmsIEISMEToSMESpecificUse24=0x97,
		ESmsIEISMEToSMESpecificUse25=0x98,
		ESmsIEISMEToSMESpecificUse26=0x99,
		ESmsIEISMEToSMESpecificUse27=0x9A,
		ESmsIEISMEToSMESpecificUse28=0x9B,
		ESmsIEISMEToSMESpecificUse29=0x9C,
		ESmsIEISMEToSMESpecificUse30=0x9D,
		ESmsIEISMEToSMESpecificUse31=0x9E,
		ESmsIEISMEToSMESpecificUse32=0x9F,
//  Reserved values
//		....
//		....
		ESmsIEISCSpecificUse1=0xC0,
		ESmsIEISCSpecificUse2=0xC1,
		ESmsIEISCSpecificUse3=0xC2,
		ESmsIEISCSpecificUse4=0xC3,
		ESmsIEISCSpecificUse5=0xC4,
		ESmsIEISCSpecificUse6=0xC5,
		ESmsIEISCSpecificUse7=0xC6,
		ESmsIEISCSpecificUse8=0xC7,
		ESmsIEISCSpecificUse9=0xC8,
		ESmsIEISCSpecificUse10=0xC9,
		ESmsIEISCSpecificUse11=0xCA,
		ESmsIEISCSpecificUse12=0xCB,
		ESmsIEISCSpecificUse13=0xCC,
		ESmsIEISCSpecificUse14=0xCD,
		ESmsIEISCSpecificUse15=0xCE,
		ESmsIEISCSpecificUse16=0xCF,
		ESmsIEISCSpecificUse17=0xD0,
		ESmsIEISCSpecificUse18=0xD1,
		ESmsIEISCSpecificUse19=0xD2,
		ESmsIEISCSpecificUse20=0xD3,
		ESmsIEISCSpecificUse21=0xD4,
		ESmsIEISCSpecificUse22=0xD5,
		ESmsIEISCSpecificUse23=0xD6,
		ESmsIEISCSpecificUse24=0xD7,
		ESmsIEISCSpecificUse25=0xD8,
		ESmsIEISCSpecificUse26=0xD9,
		ESmsIEISCSpecificUse27=0xDA,
		ESmsIEISCSpecificUse28=0xDB,
		ESmsIEISCSpecificUse29=0xDC,
		ESmsIEISCSpecificUse30=0xDD,
		ESmsIEISCSpecificUse31=0xDE,
		ESmsIEISCSpecificUse32=0xDF,
		};
public:
	static CSmsInformationElement* NewL(TSmsInformationElementIdentifier aIdentifier,const TDesC8& aData);
	static CSmsInformationElement* NewL();
	~CSmsInformationElement();

	inline TInt Identifier() const;
	inline TPtr8 Data();

	TUint8* EncodeL(TUint8* aPtr) const;
	const TUint8* DecodeL(const TUint8* aPtr);
	void InternalizeL(RReadStream& aStream);
	void ExternalizeL(RWriteStream& aStream) const;
private:
	CSmsInformationElement(TSmsInformationElementIdentifier aInformationElementIdentifier);
	void ConstructL(const TDesC8& aData);
	void NewDataL(TInt aLength);
private:
	TSmsOctet iIdentifier;
	HBufC8* iData;
	};

// CSmsCommandData - in command
class CSmsCommandData : public CBase
	{
public:
	enum {KSmsMaxDataSize=157};
public:
	static CSmsCommandData* NewL(TSmsFirstOctet& aFirstOctet);
	~CSmsCommandData();

	inline TInt NumInformationElements() const;
	CSmsInformationElement& InformationElement(TInt aIndex) const;
	TBool InformationElementIndex(CSmsInformationElement::TSmsInformationElementIdentifier aIdentifier,
		TInt& aIndex) const;
	void AddInformationElementL(CSmsInformationElement::TSmsInformationElementIdentifier aIdentifier,
		const TDesC8& aData);
	void RemoveInformationElement(TInt aIndex);

	inline TInt MaxDataLength() const;
	TPtrC8 Data() const;
	void SetDataL(const TDesC8& aData);

	TUint8* EncodeL(TUint8* aPtr) const;
	const TUint8* DecodeL(const TUint8* aPtr);
	void InternalizeL(RReadStream& aStream);
	void ExternalizeL(RWriteStream& aStream) const;
private:
	CSmsCommandData(TSmsFirstOctet& aFirstOctet);

	TInt HeaderLength() const;
	TInt TotalHeaderLengthInUDLUnits() const;

	TBool HeaderPresent() const;
	void SetHeaderPresent(TBool aHeaderPresent);

private:
	TSmsFirstOctet& iFirstOctet;
	CArrayPtrFlat<CSmsInformationElement> iInformationElementArray;
	HBufC8* iBuffer;	
	};

// TSmsCommandType - in command

class TSmsCommandType : public TSmsOctet
	{	
public:
	enum TSmsCommandTypeValue
		{	
		ESmsCommandTypeEnquiry=0x00,
		ESmsCommandTypeCancel=0x01,
		ESmsCommandTypeDelete=0x02,
		ESmsCommandTypeEnableStatusReportRequest=0x03
//  Reserved values
//		....
//		....
		};
public:
	TSmsCommandType();
	inline TInt CommandType() const;
	inline void SetCommandType(TSmsCommandTypeValue aType);
	};

// CSmsUserData - this class has the user data

class CSmsUserData : public CBase
	{
public:
	enum {KSmsMaxUserDataSize=140};

public:
	static CSmsUserData* NewL(CCnvCharacterSetConverter& aCharacterSetConverter,RFs& aFs,TSmsFirstOctet& aFirstOctet,const TSmsDataCodingScheme& aDataCodingScheme);
	~CSmsUserData();

	inline TInt NumInformationElements() const;
	IMPORT_C CSmsInformationElement& InformationElement(TInt aIndex) const;
	IMPORT_C TBool InformationElementIndex(CSmsInformationElement::TSmsInformationElementIdentifier aIdentifier,TInt& aIndex) const;
	IMPORT_C void AddInformationElementL(CSmsInformationElement::TSmsInformationElementIdentifier aIdentifier,const TDesC8& aData);
	IMPORT_C void RemoveInformationElement(TInt aIndex);

	TInt MaxPackedUDUnitsInBody() const;
	IMPORT_C TInt MaxBodyLengthInChars() const;
	IMPORT_C TPtrC8 Body() const;
	IMPORT_C void SetBodyL(const TDesC8& aBody);

	IMPORT_C TBool IsSupportedL(TChar aChar);
	TBool IsBinaryData() const;

	TUint8* EncodeL(TUint8* aPtr) const;
	const TUint8* DecodeL(const TUint8* aPtr);
	void InternalizeL(RReadStream& aStream);
	void ExternalizeL(RWriteStream& aStream) const;
private:
	CSmsUserData(CCnvCharacterSetConverter& aCharacterSetConverter,RFs& aFs,TSmsFirstOctet& aFirstOctet,const TSmsDataCodingScheme& aDataCodingScheme);
	void ConstructL();
	TInt HeaderLength() const;
	TInt TotalHeaderLengthInUDLUnits() const;
	TInt BodyLengthInUDLUnits() const;
	void NewBodyL(TInt aLengthInChars);
	TBool HeaderPresent() const;
	void SetHeaderPresent(TBool aHeaderPresent);

private:
	CLASSNAMEDECL(CSmsUserData);
	CCnvCharacterSetConverter& iCharacterSetConverter;
	RFs& iFs;

	TSmsFirstOctet& iFirstOctet;
	const TSmsDataCodingScheme& iDataCodingScheme;
	CArrayPtrFlat<CSmsInformationElement> iInformationElementArray;
	HBufC8* iBody;
	};

#include "gsmuelem.inl"

#endif // !defined __GSMUELEM_H__
