///////////////////////////////////////////////////////////////////////////////
//
// SMUTSET.H
//
// Copyright (c) 2000 Symbian Ltd. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

/*
-----------------------------------------------------------------------------

    DESCRIPTION

    This file contains the header files of the  classes CSmsHeader and CSmsNumber.

-----------------------------------------------------------------------------
*/


#ifndef SMUTSET_H_
#define SMUTSET_H_

// Includes

#include <gsmumsg.h>	// Enums like TSmsValidityPeriod
#include <msvrcpt.h>	// CMsvRecipient
#include <msvstore.h>	// RMsvReadStream
#include <smsuaddr.h>	// TSmsServiceCenterAddress
#include <logwrap.h>
#include <etelgprs.h>

// Forward declarations

class CSmsNumber;

// Constants

// Both the recipient's number  and SC number (TP-Destination-Address and RP-Destination-Address) 
// can be 12 octets which means that there can be 21 characters (including + sign) in the number string. 

const TInt KSmcmSmsNumberMaxNumberLength = 21;
const TInt KSmcmSmsNumberMaxNameLength = 256;

// Macros

// Enumerations

enum TSmsPIDConversion
		{
		ESmsConvPIDNone	= TSmsProtocolIdentifier::ESmsNoTelematicDevice,
		ESmsConvFax		= TSmsProtocolIdentifier::ESmsGroup3TeleFax,
		ESmsConvX400	= TSmsProtocolIdentifier::ESmsX400MessageHandlingSystem,
		ESmsConvPaging	= TSmsProtocolIdentifier::ESmsNationalPagingSystem,
		ESmsConvMail	= TSmsProtocolIdentifier::ESmsInternetElectronicMail,
		ESmsConvErmes	= TSmsProtocolIdentifier::ESmsERMES,
		ESmsConvSpeech	= TSmsProtocolIdentifier::ESmsVoiceTelephone
		};

enum TSmcmValidityPeriod
	{
	ESmsVPHour			= TSmsValidityPeriod::EHalfHourUnitInMinutes*2,
	ESmsVPSixHours		= TSmsValidityPeriod::EHalfHourUnitInMinutes*12,
	ESmsVP24Hours		= TSmsValidityPeriod::EOneDayUnitInMinutes,
	ESmsVPWeek			= TSmsValidityPeriod::EOneWeekUnitInMinutes,
	ESmsVPMaximum		= TSmsValidityPeriod::EOneWeekUnitInMinutes*63, //check this!
	ESmsVPNotSupported	= KErrNotSupported, //-5,
	ESmsVPDefault		= ESmsVPWeek
	}; 

enum TSmsDelivery
	{
	ESmsDeliveryImmediately,
	ESmsDeliveryUponRequest,
	ESmsDeliveryScheduled
	};

enum TSmsSettingsFlags
	{	
	ESmsSettingsNoFlags					=0,
	ESmsSettingsCanConcatenate			=0x00000001,
	ESmsSettingsReplyQuoted				=0x00000002,
	ESmsSettingsRejectDuplicate			=0x00000004,
	ESmsSettingsDeliveryReport			=0x00000008,
	ESmsSettingsReplyPathRequested		=0x00000010,
	ESmsSettingsMask					=0x0000001F	
	};

// Class Definitions

// TSmsProgress

class TSmsProgress 
	{
public:
	enum TSmsProgressType
		{
		ESmsProgressTypeDefault,
		ESmsProgressTypeReadingServiceCenterAddress,
		ESmsProgressTypeWritingServiceCenterAddress,
		ESmsProgressTypeReadSimParams,
		ESmsProgressTypeSending,
		ESmsProgressTypeScheduling,
		ESmsProgressTypeEnumeratingSim,
		ESmsProgressTypeCopyFromSim,
		ESmsProgressTypeMoveFromSim,
		ESmsProgressTypeDeleteFromSim,
		ESmsProgressTypeDeleteSchedule,
		ESmsProgressTypeCheckSchedule,
		ESmsProgressTypeDeleteAll,
		ESmsProgressTypeCopyToSim
		};
	
	inline TSmsProgress(TSmsProgressType aType = ESmsProgressTypeDefault);

public:
	TInt iError; 
	TSmsProgressType iType;
	TInt iState;
	TInt iRcpDone;
	TInt iRcpCount; // how many recipients for this message in all
	TInt iMsgDone;
	TInt iMsgCount; // how many messages there are in all to be sent
	TSmsServiceCenterAddress iServiceCenterAddress;
	TMsvId iEnumerateFolder;
	};

typedef TPckgBuf<TSmsProgress> TSmsProgressBuf;

///////////////////////////////////////////////////////////////////////////////
//
// Class CSmsMessageSettings
//
// The settings that are relevant on a per message basis
//
///////////////////////////////////////////////////////////////////////////////

class CSmsMessageSettings : public CBase
	{
public:
	// Internalize/externalize
	IMPORT_C virtual void InternalizeL(RMsvReadStream& aReadStream);
	IMPORT_C virtual void ExternalizeL(RMsvWriteStream& aWriteStream) const;

	// Validity Period
	inline const TTimeIntervalMinutes& ValidityPeriod() const;
	inline void SetValidityPeriod(TTimeIntervalMinutes);

	inline void SetValidityPeriodFormat(TSmsFirstOctet::TSmsValidityPeriodFormat aValidityPeriodFormat);
	inline const TSmsFirstOctet::TSmsValidityPeriodFormat ValidityPeriodFormat() const;

	// Reject duplicate
	inline TBool RejectDuplicate() const;
	inline void SetRejectDuplicate(TBool);

	// Delivery Report
	inline TBool DeliveryReport() const;
	inline void SetDeliveryReport(TBool);

	// Reply path
	inline TBool ReplyPath() const;
	inline void SetReplyPath(TBool);

	// Message Conversion
	inline TSmsPIDConversion MessageConversion() const;
	inline void SetMessageConversion(TSmsPIDConversion);

	// Can concatenate?
	inline TBool CanConcatenate() const;
	inline void SetCanConcatenate(TBool);

	// Character Set
	inline enum TSmsDataCodingScheme::TSmsAlphabet CharacterSet() const;
	inline void SetCharacterSet(TSmsDataCodingScheme::TSmsAlphabet);

    // Assigns
    IMPORT_C virtual void CopyL(const CSmsMessageSettings& aSmsSettings);

protected:	// methods

	CSmsMessageSettings();

private:	// data

	TUint32 iMsgFlags;
	TSmsPIDConversion iMessageConversion;
	TSmsDataCodingScheme::TSmsAlphabet iAlphabet;
	TTimeIntervalMinutes iValidityPeriod;
	TSmsFirstOctet::TSmsValidityPeriodFormat iValidityPeriodFormat;
	};


///////////////////////////////////////////////////////////////////////////////
//
// Class CSmsMessageSettings
//
// The settings that for the SMS Service only
//
///////////////////////////////////////////////////////////////////////////////

class CSmsSettings : public CSmsMessageSettings
	{
public:
	enum TSmsReportHandling
		{
		EMoveReportToInboxInvisible,
		EMoveReportToInboxVisible,
		EDiscardReport,
		EDoNotWatchForReport
		};

	enum TSmsSettingsCommDbAction
		{
		ENone,
		EStoreToCommDb
		};

public:
	// NewL
	IMPORT_C static CSmsSettings* NewL();

	// Destructor
	IMPORT_C ~CSmsSettings();

	// Internalize/externalize
	IMPORT_C void InternalizeL(RMsvReadStream& aReadStream);
	IMPORT_C void ExternalizeL(RMsvWriteStream& aWriteStream) const;

	// Restore/store
	IMPORT_C void RestoreL(CMsvStore& aMessageStore);
	IMPORT_C void StoreL(CMsvStore& aMessageStore) const;

	// SC address handling
	inline TInt NumSCAddresses() const;
	inline CSmsNumber& SCAddress(TInt aIndex) const;
	IMPORT_C void AddSCAddressL(const TDesC& aName,const TDesC& aNumber);
	IMPORT_C void RemoveSCAddress(TInt aIndex);
	inline TInt DefaultSC() const;
	inline void SetDefaultSC(TInt);

	// Delivery
	inline TSmsDelivery Delivery() const;
	inline void SetDelivery(TSmsDelivery);

	// Reply quoted
	inline TBool ReplyQuoted() const;
	inline void SetReplyQuoted(TBool);

    // Assigns
    IMPORT_C void CopyL(const CSmsSettings& aSmsSettings);

	//How to handle Special Messages and Status Reports
	inline TSmsReportHandling StatusReportHandling() const;
	inline void SetStatusReportHandling(TSmsReportHandling aStatusReportHandling);
	inline TSmsReportHandling SpecialMessageHandling() const;
	inline void SetSpecialMessageHandling(TSmsReportHandling aSpecialMessageHandling);

	inline void SetCommDbAction(TSmsSettingsCommDbAction aCommDbAction);
	inline TSmsSettingsCommDbAction CommDbAction() const;

	inline void SetSmsBearerAction(TSmsSettingsCommDbAction aSmsBearerAction);
	inline TSmsSettingsCommDbAction SmsBearerAction() const;

	inline void SetSmsBearer(RGprs::TSmsBearer aSmsBearer);
	inline RGprs::TSmsBearer SmsBearer() const;

private:	// methods

	CSmsSettings();

	void ConstructL();

	//Write default SC, validity period and delivery report to CommDb.
	void StoreToCommDbL() const;

private:	// data

	TUint32 iSetFlags;
	CArrayPtrFlat<CSmsNumber> *iSCAddresses;
	TSmsDelivery iDelivery;
	TInt iDefaultSC;
	TSmsReportHandling iStatusReportHandling;
	TSmsReportHandling iSpecialMessageHandling;
	TSmsSettingsCommDbAction iCommDbAction;
	TSmsSettingsCommDbAction iSmsBearerAction;
	RGprs::TSmsBearer iSmsBearer;
	};


///////////////////////////////////////////////////////////////////////////////
//
// Class CSmsNumber - for storing SC address and name
//
///////////////////////////////////////////////////////////////////////////////

class CSmsNumber : public CMsvRecipient 
	{
public:
	// NewL
	IMPORT_C static CSmsNumber* NewL();
    // Allocates memory new members when copying
	IMPORT_C static CSmsNumber* NewL(const CSmsNumber& aSmsNumber);

    // Destructor
	IMPORT_C ~CSmsNumber();
	// Internalize/externalize
	IMPORT_C void InternalizeL( RReadStream& aStream);
	IMPORT_C void ExternalizeL( RWriteStream& aStream) const;

	// Address handling
	IMPORT_C TPtrC Address() const;
	IMPORT_C void SetAddressL(const TDesC& aAddress);

	// Name handling
	IMPORT_C TPtrC Name() const;
	IMPORT_C void SetNameL(const TDesC& aName);

	//LogId handling
	inline TLogId LogId() const;
	inline void SetLogId(TLogId aLogId);

    // Assigns
	IMPORT_C CSmsNumber& CopyL(const CSmsNumber& aSmsNumber);

private:
	CSmsNumber();
	void ConstructL();
	TPtrC LimitStringSize(const TPtrC& aString, TInt aMaxLength) const;

	private:
	HBufC* iNumber;
	HBufC* iName;
	TLogId iLogId;
	};

#include "smutset.inl"

#endif // !defined SMUTSET_H_
