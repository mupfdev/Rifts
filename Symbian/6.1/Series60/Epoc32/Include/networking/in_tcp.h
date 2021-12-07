// IN_TCP.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __IN_TCP_H__
#define __IN_TCP_H__

#include <e32def.h>
#include <nifmbuf.h>

const TInt KTCPHeaderSize = 20;
const TInt KTCPMaxHeaderSize = 64;

class ThdrIP;
class ThdrTCP
	{
public:
	static ThdrTCP *GetHeader(RMBufChain &aChain);
	void SwapOrder();
	inline static ThdrTCP* Ptr(RMBufPacketBase& aPacket);
	inline static ThdrTCP* Ptr(ThdrIP* aHdr);
	inline static ThdrTCP* NetPtr(ThdrIP* aHdr);

	inline TUint NetGetHdrLen();
	inline TUint GetSrcPort();
	inline TUint GetDstPort();
	inline TUint NetGetSrcPort();
	inline TUint NetGetDstPort();
	inline TUint GetChecksum();
	inline TUint NetGetChecksum();
	inline void SetSrcPort(TUint aPort);
	inline void SetDstPort(TUint aPort);
	inline void SetChecksum(TUint aSum);
	inline void NetSetChecksum(TUint aSum);

//#ifdef VJCOMP
	inline	void VJSetChecksum(TUint aSum);
	void	Printf();
	inline	TUint	VJGetFlags();
	inline	void	VJSetFlags(TUint aLen);
	inline	TUint	NetGetSeqNum();
	inline	void	NetSetSeqNum(TUint aLen);
	inline	TUint	NetGetAckNum();
	inline	void	NetSetAckNum(TUint aLen);
	inline	void	NetSetUrgPtr(TUint aLen);
	inline	TUint16	NetGetUrgPtr();
	inline	TUint16	NetGetWindow();
	inline	void	NetSetWindow(TUint16 aLen);
//#endif

	inline TUint GetSeqNum();
	inline void SetSeqNum(TUint aLen);
	inline TUint GetAckNum();
	inline void SetAckNum(TUint aLen);
	inline TUint GetUrgPtr();
	inline void SetUrgPtr(TUint aLen);

	inline TUint GetFlags();
	inline void SetFlags(TUint aLen);

	inline TUint GetWindow();
	inline void SetWindow(TUint aLen);
	inline TUint GetHdrLen();
	inline void SetHdrLen(TUint aLen);


	TPtrC8 GetOptions();
	void SetOptions(const TDesC8& aDes);

private:
	union
		{
		TUint32 iData32[5];
		TUint16	iData16[10];
		TUint8  iData8[20];
		} u;
	};

#include <networking\in_tcp.inl>

#endif	// __IN_TCP_H__

