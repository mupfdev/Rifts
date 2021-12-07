// PPPSOCK.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__PPPSOCK_H__)
#define __PPPSOCK_H__

#include <es_prot.h>

////////////////////////////////////////////////////////////////////////////////
// PPP Socket address - used by link protocols
////////////////////////////////////////////////////////////////////////////////

enum TPppPhase
	{
	EPppPhaseTerminate,
	EPppPhaseEstablish,
	EPppPhaseEarlyCallback,
	EPppPhaseAuthenticate,
	EPppPhaseLateCallback,
	EPppPhaseNetwork,
	EPppPhaseAll = EPppPhaseTerminate
	};

struct SPppLinkAddr
	{
	TPppPhase iPhase;
	TUint iProtocol;
	TUint iAddress;
	TUint iControl;
	TBool iCRCError;  // Need to propagate CRC errors for VJ Compression
	};

class TPppAddr : public TSockAddr
	{
public:
	IMPORT_C TPppAddr();
	IMPORT_C TPppAddr& operator = (const TSockAddr& aAddr);
	inline static TPppAddr& Cast(const TSockAddr& aAddr);
	inline static TPppAddr& Cast(const TSockAddr* aAddr);
	inline TPppPhase GetPhase();
	inline void SetPhase(TPppPhase aPhase);
	inline TUint GetProtocol();
	inline void SetProtocol(TUint aProtocol);
	inline TUint GetAddress();
	inline void SetAddress(TUint aAddress);
	inline TUint GetControl();
	inline void SetControl(TUint aControl);
	inline void  SetCRCError(TBool anError);
	inline TBool CRCError();


protected:
	inline SPppLinkAddr *InfoPtr() const;
	};

////////////////////////////////////////////////////////////////////////////////
// PPP Constants
////////////////////////////////////////////////////////////////////////////////

const TUint KAfPpp = 0xc021;
const TUint KSOLPpp = 0xc021;

// Protocol IDs
const TUint KPppIdEsock = 0x10000;	// Normally 0
const TUint KPppIdLcp = 0xc021;
const TUint KPppIdPap = 0xc023;
const TUint KPppIdChap = 0xc223;

const TUint KPppIdMsCbcp = 0xc029;	// CSW

// LCP Codes
const TUint8 KPppLcpConfigRequest = 1;
const TUint8 KPppLcpConfigAck = 2;
const TUint8 KPppLcpConfigNak = 3;
const TUint8 KPppLcpConfigReject = 4;
const TUint8 KPppLcpTerminateRequest = 5;
const TUint8 KPppLcpTerminateAck = 6;
const TUint8 KPppLcpCodeReject = 7;
const TUint8 KPppLcpProtocolReject = 8;
const TUint8 KPppLcpEchoRequest = 9;
const TUint8 KPppLcpEchoReply = 10;
const TUint8 KPppLcpDiscardRequest = 11;

// LCP Extended Codes
const TUint8 KPppLcpIdentication = 12;
const TUint8 KPppLcpTimeRemaining = 13;

// LCP Options
const TUint8 KPppLcpOptMaxRecvUnit = 1;
const TUint8 KPppLcpOptEscapeCharMap = 2;
const TUint8 KPppLcpOptAuthenticationProtocol = 3;
const TUint8 KPppLcpOptQualityProtocol = 4;
const TUint8 KPppLcpOptMagicNumber = 5;
const TUint8 KPppLcpOptProtocolCompress = 7;
const TUint8 KPppLcpOptAddrCtrlCompress = 8;
const TUint8 KPppLcpOptMRRU = 17;
const TUint8 KPppLcpOptMultiLinkEndPointDescriminator = 19; // RFC1717

// LCP Extended Options
const TUint8 KPppLcpOptFcsType = 9;
const TUint8 KPppLcpOptPadding = 10;
const TUint8 KPppLcpOptCallback = 13;
const TUint8 KPppLcpOptCompoundFrames = 15;

const TUint KPppIdUnknown = 0x80000000;
const TUint KPppIdCopyAll = 0x80000001;
const TUint KPppIdAsIs = 0x80000002;

#include <networking\pppsock.inl>

#endif
