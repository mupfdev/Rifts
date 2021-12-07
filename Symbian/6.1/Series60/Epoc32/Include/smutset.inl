///////////////////////////////////////////////////////////////////////////////
//
// SMUTSET.INL
//
// Copyright (c) 2000 Symbian Ltd. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "smcmmain.h"
#include "smut.h"

inline TSmsProgress::TSmsProgress(TSmsProgressType aType):
	iError(KErrNone),
	iType(aType),
	iState(0),
	iRcpDone(0),
	iRcpCount(0),
	iMsgDone(0),
	iMsgCount(0),
	iEnumerateFolder(0)
	{
	iServiceCenterAddress.Zero();
	}

inline TInt CSmsSettings::NumSCAddresses() const
	{
	return iSCAddresses->Count();
	}

inline CSmsNumber& CSmsSettings::SCAddress(TInt aIndex) const
	{
	return *iSCAddresses->At(aIndex);
	}

inline TInt CSmsSettings::DefaultSC() const
	{
	return iDefaultSC;
	}

inline void CSmsSettings::SetDefaultSC(TInt aDefaultSC)
	{
	__ASSERT_DEBUG(aDefaultSC>=0, Panic(ESmscDefaultSCOutOfRange));
	__ASSERT_DEBUG(aDefaultSC<iSCAddresses->Count(), Panic(ESmscDefaultSCOutOfRange));

	iDefaultSC=aDefaultSC;
	}

inline const TTimeIntervalMinutes& CSmsMessageSettings::ValidityPeriod() const
	{
	return iValidityPeriod;
	}

inline void CSmsMessageSettings::SetValidityPeriod(TTimeIntervalMinutes aValidityPeriod)
	{
	__ASSERT_DEBUG(aValidityPeriod.Int()>=0 && aValidityPeriod.Int()<=ESmsVPMaximum,Panic(ESmscVPOutOfRange));
	iValidityPeriod=aValidityPeriod;
	}

inline TBool CSmsMessageSettings::CanConcatenate() const
	{
	return iMsgFlags&ESmsSettingsCanConcatenate;
	}

inline void CSmsMessageSettings::SetCanConcatenate(TBool aCanConcatenate)
	{
	iMsgFlags = (iMsgFlags & ~ESmsSettingsCanConcatenate) | (aCanConcatenate?ESmsSettingsCanConcatenate : ESmsSettingsNoFlags);
	}

inline TBool CSmsMessageSettings::RejectDuplicate() const
	{	
	return iMsgFlags&ESmsSettingsRejectDuplicate;
	}

inline void CSmsMessageSettings::SetRejectDuplicate(TBool aRejectDuplicate)
	{
	iMsgFlags = (iMsgFlags & ~ESmsSettingsRejectDuplicate) | (aRejectDuplicate?ESmsSettingsRejectDuplicate : ESmsSettingsNoFlags);
	}

inline TBool CSmsSettings::ReplyQuoted() const
	{
	return iSetFlags&ESmsSettingsReplyQuoted;
	}

inline void CSmsSettings::SetReplyQuoted(TBool aReplyQuoted)
	{
	iSetFlags = (iSetFlags & ~ESmsSettingsReplyQuoted) | (aReplyQuoted?ESmsSettingsReplyQuoted : ESmsSettingsNoFlags);
	}

inline TSmsDelivery CSmsSettings::Delivery() const
	{
	return iDelivery;
	}

inline void CSmsSettings::SetDelivery(TSmsDelivery aDelivery)
	{
	iDelivery=aDelivery;
	}

inline TBool CSmsMessageSettings::DeliveryReport() const
	{
	return iMsgFlags&ESmsSettingsDeliveryReport;
	}

inline void CSmsMessageSettings::SetDeliveryReport(TBool aDeliveryReport)
	{
	iMsgFlags = (iMsgFlags & ~ESmsSettingsDeliveryReport) | (aDeliveryReport?ESmsSettingsDeliveryReport : ESmsSettingsNoFlags);
	}

inline TBool CSmsMessageSettings::ReplyPath() const
	{
	return iMsgFlags&ESmsSettingsReplyPathRequested;
	}

inline void CSmsMessageSettings::SetReplyPath(TBool aReplyPathRequest)
	{
	iMsgFlags = (iMsgFlags & ~ESmsSettingsReplyPathRequested) | (aReplyPathRequest?ESmsSettingsReplyPathRequested : ESmsSettingsNoFlags);
	}

inline TSmsPIDConversion CSmsMessageSettings::MessageConversion() const
	{
	return iMessageConversion;
	}

inline void CSmsMessageSettings::SetMessageConversion(TSmsPIDConversion aMessageConversion)
	{
	iMessageConversion=aMessageConversion;
	}

inline TSmsDataCodingScheme::TSmsAlphabet CSmsMessageSettings::CharacterSet() const
	{
	return iAlphabet;
	}

inline void CSmsMessageSettings::SetCharacterSet(TSmsDataCodingScheme::TSmsAlphabet aAlphabet)
	{
	iAlphabet=aAlphabet;
	}

inline void CSmsMessageSettings::SetValidityPeriodFormat(TSmsFirstOctet::TSmsValidityPeriodFormat aValidityPeriodFormat)
	{
	iValidityPeriodFormat = aValidityPeriodFormat;
	}

inline const TSmsFirstOctet::TSmsValidityPeriodFormat CSmsMessageSettings::ValidityPeriodFormat() const
	{
	return iValidityPeriodFormat;
	}

inline CSmsSettings::TSmsReportHandling CSmsSettings::StatusReportHandling() const
	{
	return iStatusReportHandling;
	}

inline void CSmsSettings::SetStatusReportHandling(CSmsSettings::TSmsReportHandling aStatusReportHandling)
	{
	iStatusReportHandling = aStatusReportHandling;
	}

inline CSmsSettings::TSmsReportHandling CSmsSettings::SpecialMessageHandling() const
	{
	return iSpecialMessageHandling;
	}

inline void CSmsSettings::SetSpecialMessageHandling(CSmsSettings::TSmsReportHandling aSpecialMessageHandling)
	{
	iSpecialMessageHandling = aSpecialMessageHandling;
	}

inline void CSmsSettings::SetCommDbAction(CSmsSettings::TSmsSettingsCommDbAction aCommDbAction)
	{
	iCommDbAction = aCommDbAction;
	}

inline CSmsSettings::TSmsSettingsCommDbAction CSmsSettings::CommDbAction() const
	{
	return iCommDbAction;
	}

inline void CSmsSettings::SetSmsBearerAction(CSmsSettings::TSmsSettingsCommDbAction aSmsBearerAction)
	{
	iSmsBearerAction = aSmsBearerAction;
	}

inline CSmsSettings::TSmsSettingsCommDbAction CSmsSettings::SmsBearerAction() const
	{
	return iSmsBearerAction;
	}

inline void CSmsSettings::SetSmsBearer(RGprs::TSmsBearer aSmsBearer)
	{
	iSmsBearer = aSmsBearer;
	}

inline RGprs::TSmsBearer CSmsSettings::SmsBearer() const
	{
	return iSmsBearer;
	}

inline TLogId CSmsNumber::LogId() const
	{
	return iLogId;
	}

inline void CSmsNumber::SetLogId(TLogId aLogId)
	{
	iLogId = aLogId;
	}