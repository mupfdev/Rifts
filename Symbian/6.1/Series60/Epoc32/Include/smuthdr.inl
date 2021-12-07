///////////////////////////////////////////////////////////////////////////////
//
// SMUTHDR.INL
//
// Copyright (c) 2000 Symbian Ltd. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "smcmmain.h"
#include <gsmumsg.h>

inline CSmsSubmit& CSmsHeader::Submit()
	{
	__ASSERT_DEBUG( Type() == CSmsPDU::ESmsSubmit, Panic(ESmutPanicUnsupportedMsgType));
	return (CSmsSubmit&)(iMessage->SmsPDU());
	}

inline const CSmsSubmit& CSmsHeader::Submit() const
	{
	__ASSERT_DEBUG( Type() == CSmsPDU::ESmsSubmit, Panic(ESmutPanicUnsupportedMsgType));
	return (CSmsSubmit&)(iMessage->SmsPDU());
	}

inline CSmsDeliver& CSmsHeader::Deliver()
	{
	__ASSERT_DEBUG( Type() == CSmsPDU::ESmsDeliver, Panic(ESmutPanicUnsupportedMsgType));
	return (CSmsDeliver&)(iMessage->SmsPDU());
	}

inline const CSmsDeliver& CSmsHeader::Deliver() const
	{
	__ASSERT_DEBUG( Type() == CSmsPDU::ESmsDeliver, Panic(ESmutPanicUnsupportedMsgType));
	return (CSmsDeliver&)(iMessage->SmsPDU());
	}

inline CSmsCommand& CSmsHeader::Command()
	{
	__ASSERT_DEBUG( Type() == CSmsPDU::ESmsCommand, Panic(ESmutPanicUnsupportedMsgType));
	return (CSmsCommand&)(iMessage->SmsPDU());
	}

inline const CSmsCommand& CSmsHeader::Command() const
	{
	__ASSERT_DEBUG( Type() == CSmsPDU::ESmsCommand, Panic(ESmutPanicUnsupportedMsgType));
	return (CSmsCommand&)(iMessage->SmsPDU());
	}

inline CSmsStatusReport& CSmsHeader::StatusReport()
	{
	__ASSERT_DEBUG( Type() == CSmsPDU::ESmsStatusReport, Panic(ESmutPanicUnsupportedMsgType));
	return (CSmsStatusReport&)(iMessage->SmsPDU());
	}

inline const CSmsStatusReport& CSmsHeader::StatusReport() const
	{
	__ASSERT_DEBUG( Type() == CSmsPDU::ESmsStatusReport, Panic(ESmutPanicUnsupportedMsgType));
	return (CSmsStatusReport&)(iMessage->SmsPDU());
	}

inline CSmsPDU::TSmsPDUType CSmsHeader::Type() const
	{
	return iMessage->SmsPDU().Type();
	}

inline const CArrayPtrFlat<CSmsNumber>& CSmsHeader::Recipients() const
	{
	return iRecipients;
	}

inline CArrayPtrFlat<CSmsNumber>& CSmsHeader::Recipients()
	{
	return iRecipients;
	}

inline CSmsMessage& CSmsHeader::Message()
	{
	return *iMessage;
	}
	
inline const CSmsMessage& CSmsHeader::Message() const
	{
	return *iMessage;
	}

inline TBool CSmsHeader::ReplyPathProvided() const
	{
	return iFlags & ESmsHeaderReplyPathProvided;
	}

inline void CSmsHeader::SetReplyPathProvided(TBool aReplyPathProvided)
	{
	iFlags = (iFlags & ~ESmsHeaderReplyPathProvided) | (aReplyPathProvided ? ESmsHeaderReplyPathProvided : ESmsHeaderNoFlags);
	}

inline void CSmsHeader::SetFromAddressL(const TDesC& aAddress)
	{
	Message().SmsPDU().SetToFromAddressL(aAddress);
	}

inline TPtrC CSmsHeader::FromAddress() const
	{
	switch(Type())
		{
		case(CSmsPDU::ESmsSubmit):
										return Submit().ToFromAddress();
		case(CSmsPDU::ESmsDeliver):
										return Deliver().ToFromAddress();
		default: 
										return TPtrC(0,0);
		}
	}

inline TPtrC CSmsHeader::ServiceCenterAddress() const
	{
	return Submit().ServiceCenterAddress();
	}

inline void CSmsHeader::SetServiceCenterAddressL(const TDesC& aAddress)
	{
	Submit().SetServiceCenterAddressL(aAddress);
	}

inline void CSmsHeader::ParsedServiceCenterAddress(TGsmTelNumber& aParsedAddress) const
	{
	Submit().ParsedServiceCenterAddress(aParsedAddress);
	}

inline void CSmsHeader::SetParsedServiceCenterAddressL(const TGsmTelNumber& aParsedAddress)
	{
	Submit().SetParsedServiceCenterAddressL(aParsedAddress);
	}

inline TBioMsgIdType CSmsHeader::BioMsgIdType() const
	{
	return iBioMsgIdType;
	}

inline void CSmsHeader::SetBioMsgIdType(TBioMsgIdType aBioMsgIdType)
	{
	iBioMsgIdType = aBioMsgIdType;
	}
