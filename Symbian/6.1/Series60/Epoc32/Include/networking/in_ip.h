// IN_IP.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __IN_IP_H__
#define __IN_IP_H__

#include <nifmbuf.h>

const TUint KIPFragListTTL			= 60*1000000;
const TUint KIPMinHeaderSize		= 20;
const TUint KIPMaxHeaderSize		= 60;	// Max length of an IP header with options
const TUint KIPDefaultTOS			= 0;
const TInt KIPDefaultTTL			= 255;
const TUint KIPVersion				= 4;

// Option Values
const TUint KIPOptionEOL			= 0x00;
const TUint KIPOptionNOP			= 0x01;
const TUint KIPOptionRecRoute		= 0x07;
const TUint KIPOptionTimeStamp		= 0x44;
const TUint KIPOptionSecurity		= 0x82;
const TUint KIPOptionLooseSrcRt		= 0x83;
const TUint KIPOptionSatNetId		= 0x88;
const TUint KIPOptionStrictSrcRt	= 0x89;
// Flag bits
const TUint KIPOptionIsCopiedFlag	= 0x80;
// Offsets to field within an IP option
const TInt	KIPOptionValByte		= 0;
const TInt	KIPOptionLenByte		= 1;
const TInt	KIPOptionOffset			= 2;
const TInt	KIPOptionMinOffset		= 4;

class ThdrICMP;

// IP Protocol Header
// Host byte order is assumed
class ThdrIP
	{
public:
	static	ThdrIP*	GetHeader(RMBufChain &aChain);
	static	ThdrIP*	NetGetHeader(RMBufChain &aChain);
	inline	static	ThdrIP*	Ptr(RMBufPacketBase& aPacket);
	inline	static	ThdrIP*	Ptr(ThdrICMP* aHdr);
	inline	static	ThdrIP*	NetPtr(ThdrIP* aHdr);
	inline	TUint8*	EndPtr();
	inline	TUint8*	NetEndPtr();
	inline	TUint8*	OptPtr();
	void	SwapOrder();
	TInt	CopyOptionsCount();
	TInt	CopyOptions(ThdrIP* aDstPtr);
	inline	static	TBool	IsOptCopied(TUint8* aBuf);
	inline	TUint	GetVersion();
	inline	void	SetVersion(TUint aVal);
	inline	TUint	NetGetVersion();
	inline	TUint	GetHdrLen();
	inline	void	SetHdrLen(TUint aVal);
	inline	TUint	NetGetHdrLen();
	inline	TUint	GetTOS();
	inline	void	SetTOS(TUint aVal);
	inline	TUint	GetLength();
	inline	void	SetLength(TUint aVal);
//#ifdef VJCOMP
	inline	TUint	NetGetId();
	inline	void	NetSetId(TUint aVal);
	inline	TUint16	NetGetLength();
	inline	void	NetSetLength(TUint16 aVal);
	inline	void	VJSetChecksum(TUint16 aVal);
	inline	void	NetSetProtocol(TUint aVal);
	inline	TUint	NetGetFragment();
	inline	TUint16	Word0();
	inline	TUint16	Word3();
	inline	TUint16	Word4();
	inline   TUint8*	GetOptions();
//#endif
	inline TUint GetId();
	inline void SetId(TUint aVal);
	inline TUint GetMF();
	inline void SetMF(TUint aVal);
	inline TUint GetDF();
	inline void SetDF(TUint aVal);
	inline TUint GetOffset();
	inline void SetOffset(TUint aVal);
	inline TUint GetFragment();
	inline void SetFragment(TUint aVal);
	inline void SetFragment(TUint aOffset, TUint aMF);
	inline TUint GetTTL();
	inline void SetTTL(TUint aVal);
	inline TUint GetProtocol();
	inline TUint NetGetProtocol();
	inline void SetProtocol(TUint aVal);
	inline TUint GetChecksum();
	inline void SetChecksum(TUint aVal);
	inline TUint NetGetChecksum();
	inline void NetSetChecksum(TUint aVal);
	inline TUint32 GetSrcAddr();
	inline TUint32 NetGetSrcAddr();
	inline void SetSrcAddr(TUint32 aAddr);
	inline TUint32 GetDstAddr();
	inline TUint32 NetGetDstAddr();
	inline void SetDstAddr(TUint32 aAddr);
	inline void SetWord0(TUint aHdrLen, TUint aTOS, TUint aLen);
	inline void SetWord1(TUint aId);
	inline void SetWord1(TUint aId, TUint aDF);
	inline void SetWord1(TUint aId, TUint aMF, TUint aOffset);
	inline void SetWord2(TUint aTTL, TUint aProtocol); // Checksum invariably set afterwards
private:
	union
		{
		TUint32 iData32[3];
		TUint16	iData16[6];
		TUint8  iData8[12];
		} u;
	TUint32	iSrcAddr;
	TUint32 iDstAddr;
	};


// ICMP Type and Code values
const TUint KICMPTypeEchoReply			= 0;
const TUint		KICMPCode						= 0;
const TUint KICMPTypeUnreachable		= 3;
const TUint		KICMPCodeUnreachNet				= 0;
const TUint		KICMPCodeUnreachHost			= 1;
const TUint		KICMPCodeUnreachProtocol		= 2;
const TUint		KICMPCodeUnreachPort			= 3;
const TUint		KICMPCodeUnreachNeedFrag		= 4;
const TUint		KICMPCodeUnreachSrcRouteFail	= 5;
const TUint		KICMPCodeUnreachNetUnknown		= 6;
const TUint		KICMPCodeUnreachHostUnknown		= 7;
const TUint		KICMPCodeUnreachSrcHostIsolated	= 8;	// Obsolete
const TUint		KICMPCodeUnreachNetProhibited	= 9;
const TUint		KICMPCodeUnreachHostProhibited	= 10;
const TUint		KICMPCodeUnreachNetTOS			= 11;
const TUint		KICMPCodeUnreachHostTOS			= 12;
const TUint		KICMPCodeUnreachProhibited		= 13;
const TUint		KICMPCodeUnreachPrecVolation	= 14;
const TUint		KICMPCodeUnreachPrecCutoff		= 15;
const TUint KICMPTypeSourceQuench		= 4;
const TUint KICMPTypeRedirect			= 5;
const TUint		KICMPCodeRedirectNet			= 0;
const TUint		KICMPCodeRedirectHost			= 1;
const TUint		KICMPCodeRedirectNetTOS			= 2;
const TUint		KICMPCodeRedirectHostTOS		= 3;
const TUint KICMPTypeEchoRequest		= 8;
const TUint KICMPTypeRouterAdvert		= 9;
const TUint KICMPTypeRouterSolicit		= 10;
const TUint KICMPTypeTimeExceeded		= 11;
const TUint		KICMPCodeExceedInTransit		= 0;
const TUint		KICMPCodeExceedInReasm			= 1;
const TUint KICMPTypeBadParameter		= 12;
const TUint KICMPTypeTimeRequest		= 13;
const TUint KICMPTypeTimeReply			= 14;
const TUint KICMPTypeInfoRequest		= 15;	// Obsolete
const TUint KICMPTypeInfoReply			= 16;	// Obsolete
const TUint KICMPTypeMaskRequest		= 17;
const TUint KICMPTypeMaskReply			= 18;

class ThdrICMP
{
public:
//	void SwapOrder();
//	static ThdrICMP* GetHeader(RMBufChain &aChain);
//	static ThdrICMP* NetGetHeader(RMBufPacketBase& aPacket);
	inline static ThdrICMP* Ptr(RMBufPacketBase& aPacket);
	inline static ThdrICMP* Ptr(ThdrIP* aHdr);
	inline static ThdrICMP* NetPtr(ThdrIP* aHdr);
	inline ThdrIP* IpPtr();
	inline TUint NetGetType();
	inline void NetSetType(TInt aVal);
	inline TUint NetGetCode();
	inline void NetSetCode(TInt aVal);
	inline void NetSet(TUint aType, TUint aCode);
	inline TInt NetGetChecksum();
	inline void NetSetChecksum(TInt aSum);
private:
// ICMP Base Protocol Header
	union
		{
		TUint8	iData8[4];
		TUint16	iData16[2];
		TUint32	iData32[1];
		} u;
};

/*
	Type of service
	Bits
	0-2	Precedence
		000	Routine
		001	Priority
		010	Immediate
		011	Flash
		100	Flash override
		101	CRITIC/ECP
		110	Internetwork control
		111	Network control
	3		0=Normal delay			1=Low delay
	4		0=Normal throughput		1=High throughput
	5		0=Normal reliability	1=High reliablity
	6	Reserved
	7	Reserved

	Flags
	Bits
	0	Reserved (must be zero)
	1	DF	0=May fragment			1=Dont fragment
	2	MF	0=Last fragement  		1=More fragments

	Options
	Two types:
		1. Single byte of optin type
		2. Option type byte, option length byte (including type and length bytes), option data bytes
	Type as follows:
		1 bit	Copy to each fragment flag
		2 bits	Option class
			0 = control
			1 = reserved
			2 = debugging and measurement
			3 = reserved
		5 bits	Option number
	Class	Number	Length	Description
		0		0		-	End of options list
		0		1		-	NOP for alignment padding
		0		2		11	Security
		0		3		var	Loose source routing
		0		9		var	Strict source routing
		0		7		var	Record route
		2		4		var	Internet timestamp
 */

#include "networking\in_ip.inl"

#endif

