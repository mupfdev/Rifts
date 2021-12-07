// PPPBASE.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __PPPBASE_INL__
#define __PPPBASE_INL__

#include <networking\ppplcp.h>

////////////////////////////////////////////////////////////////////////////////
// PPP Link Frame Checksum
////////////////////////////////////////////////////////////////////////////////

// 16 bit
inline TPppFcs16::TPppFcs16()
	{ Init(); }
inline TUint16 TPppFcs16::Fcs()
	{ return (TUint16)~iFcs; }
inline void TPppFcs16::Init()
	{ iFcs = KPppInitFcs16; }
inline TBool TPppFcs16::IsGood()
	{ return iFcs==KPppGoodFcs16; }

// 32 bit
inline TPppFcs32::TPppFcs32()
	{ Init(); }
inline TUint32 TPppFcs32::Fcs()
	{ return (TUint32)~iFcs; }
inline void TPppFcs32::Init()
	{ iFcs = KPppInitFcs32; }
inline TBool TPppFcs32::IsGood()
	{ return iFcs==KPppGoodFcs32; }

////////////////////////////////////////////////////////////////////////////////
// PPP Packet Receiver
////////////////////////////////////////////////////////////////////////////////

inline TInt MPppRecvr::SendFrame(RMBufChain& aPacket)
	{ return iPppLcp->PppLink()->Send(aPacket, iPppId); }
inline void MPppRecvr::SetId(TUint aPppId)
	{ iPppId  = aPppId; }
inline void MPppRecvr::SetPhase(TPppPhase aPhase)
	{ iActivePhase  = aPhase; }

////////////////////////////////////////////////////////////////////////////////
// PPP Link Protocol Support
////////////////////////////////////////////////////////////////////////////////

inline TPppLinkMode CPppLinkBase::LinkMode()
	{ return iLinkMode; }
inline void CPppLinkBase::NotifyLinkUp()
	{ iPppLcp->LinkLayerUp(); }
inline void CPppLinkBase::NotifyLinkDown(TInt aReason)
	{ iPppLcp->LinkLayerDown(aReason); }
inline void CPppLinkBase::DeliverToLcp(RMBufChain& aPacket)
	{ iPppLcp->LinkRecv(aPacket); }
inline void CPppLinkBase::NewCompressor(const CPppCompressor* aCompressor)
	{ 
	  iPppCompressor = (CPppCompressor*)aCompressor;
	}
inline void CPppLinkBase::NewDeCompressor(const CPppDeCompressor* aDeCompressor)
	{ 
		iPppDecompressor = (CPppDeCompressor*)aDeCompressor; 
	}
inline void CPppLcp::SetMaxTransferSize(TInt aLength)
	{ iMaxSendSize = aLength; }
inline TInt CPppLcp::MaxTransferSize()
	{ return iMaxSendSize; }


////////////////////////////////////////////////////////////////////////////////
// PPP Options Support
////////////////////////////////////////////////////////////////////////////////

inline RPppOption& RPppOption::Cast(RMBufChain& aChain)
	{ return *((RPppOption*)&aChain); }
inline const RPppOption& RPppOption::Cast(const RMBufChain& aChain)
	{ return *((const RPppOption*)&aChain); }
inline const RPppOption& RPppOption::operator=(const RMBufChain& aChain)
	{ iNext = (RMBuf*)aChain.First(); return *this; }

////////////////////////////////////////////////////////////////////////////////
// PPP FSM
////////////////////////////////////////////////////////////////////////////////

inline TBool MPppFsm::FsmIsThisLayerOpen()
	{ return iState==EPppFsmOpened; }

#endif

