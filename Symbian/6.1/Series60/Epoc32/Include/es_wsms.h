// ES_WSMS.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__ES_WSMS_H__)
#define __ES_WSMS_H__

#include <es_sock.h>

const TUint KWAPSMSAddrFamily=0x011;
const TUint KWAPSMSDatagramProtocol=0x01;
const TInt  KWAPSMSNumberSockets=0x100;
const TUint KWAPSMSDatagramServiceInfo = KSIConnectionLess | KSIMessageBased;

_LIT(KWAPSMSProtocolId,"WAPSMS Datagram");

//////////////////////////////////////////////////////////////////////////////
// Wap Address / Port Settings
//////////////////////////////////////////////////////////////////////////////

enum TWapPortNumber
	{
	EWapPortUnspecified =   -1,  // Unspecified
	EWapPortWsp         = 9200,  // Connectionless session protocol
	EWapPortWspWtp      = 9201,  // Connection oriented session protocol
	EWapPortWspWtls     = 9202,  // Secure connectionless session protocol
	EWapPortWspWtpWtls  = 9203,  // Secure connection oriented session protocol
	EWapPortVCard       = 9204,  // vCard
	EWapPortVCardWtls   = 9206,  // Secure vCard
	EWapPortVCal        = 9205,  // vCal
	EWapPortVCalWtls    = 9207   // Secure vCal
	};

class TWapAddr : public TSockAddr
	{
public:
	enum { EMaxWapAddressLength = 24 };
public:
	inline TWapPortNumber WapPort() const;
	inline void SetWapPort(TWapPortNumber aPort);
	inline void SetWapAddress(const TDesC8& aTel);
	inline TPtrC8 WapAddress() const;
	inline TBool operator==(const TWapAddr& anAddr) const;
	};

//////////////////////////////////////////////////////////////////////////////
// Option Settings
//////////////////////////////////////////////////////////////////////////////

const TInt KWapSmsOptionLevel = KSOLSocket + 1;
const TInt KWapSmsOptionNameDCS      = 0x01;
const TInt KWapSmsOptionSmartMessage = 0x02;
const TInt KWapSmsOptionWapDatagram  = 0x03;

enum TWapSmsDataCodingScheme
	{
	EWapSms7BitDCS,
	EWapSms8BitDCS
	};

#include <es_wsms.inl>

#endif