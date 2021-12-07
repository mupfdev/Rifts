// SMSUADDR.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__SMSUADDR_H__)
#define __SMSUADDR_H__

#if !defined(__ES_SOCK_H__)
#include <es_sock.h>
#endif

#if !defined(__ETELBGSM_H__)
#include <etelbgsm.h>
#endif

const TUint KSMSAddrFamily=0x010;
const TUint KSMSDatagramProtocol=0x02;
const TInt KSMSNumberSockets=0x100;
const TUint KSMSDatagramServiceInfo = KSIConnectionLess | KSIMessageBased ;

_LIT(KSmsDatagram,"SMS Datagram");


const TUint KSolSmsProv			= 0x100;            //  Ioctl level

const TUint KIoctlDeleteSmsMessage = 0x300;         //  Ioctl command
const TUint KIoctlEnumerateSmsMessages = 0x301;     //  Ioctl command
const TUint KIoctlGetServiceCenterAddress = 0x302;  //  Ioctl command
const TUint KIoctlSetServiceCenterAddress = 0x303;  //  Ioctl command
const TUint KIoctlReadMessageSucceeded = 0x304;     //  Ioctl command
const TUint KIoctlReadMessageFailed = 0x305;        //  Ioctl command
const TUint KIoctlSendSmsMessage = 0x306;           //  Ioctl command
const TUint KIoctlWriteSmsMessage = 0x307;           //  Ioctl command

const TUint KIoctlSelectModemPresent = 0x400;       //  KIOctlSelect completeion status
const TUint KIoctlSelectModemNotPresent = 0x401;    //  KIOctlSelect completion status

typedef TBuf<KGsmMaxTelNumberSize> TSmsServiceCenterAddress;
typedef TPckgBuf<TSmsServiceCenterAddress> TSmsServiceCenterAddressBuf;


enum TSmsAddrFamily
	{
	ESmsAddrUnbound,
	ESmsAddrSendOnly,
	ESmsAddrMessageIndication,  //  Matches on IEI 0x01 and DCS 0x1100xxxx, 0x1101xxxx and 0x1110xxxx, 
	ESmsAddrMatchIEI,
	ESmsAddrMatchText,
	ESmsAddrRecvAny,
	ESmsAddrStatusReport,
	ESmsAddrLocalOperation	// For local SIM operations
	};

class TSmsAddr : public TSockAddr
	{
public:
	enum { EMaxTextMatchLength = 24 };
public:
	IMPORT_C TSmsAddr();
	IMPORT_C TSmsAddrFamily SmsAddrFamily() const;
	IMPORT_C void SetSmsAddrFamily(TSmsAddrFamily aFamily);
	IMPORT_C TInt IdentifierMatch() const;
	IMPORT_C void SetIdentifierMatch(TInt aIdentifier);
	IMPORT_C TPtrC8 TextMatch() const;
	IMPORT_C void SetTextMatch(const TDesC8& aText);
	IMPORT_C TBool operator==(const TSmsAddr& aAddr) const;
	};

#endif