// IN_TCP.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __IN_TCP_INL__
#define __IN_TCP_INL__

#include <networking\in_ip.h>

inline ThdrTCP* ThdrTCP::Ptr(RMBufPacketBase& aPacket)
	{ return (ThdrTCP*)aPacket.First()->Ptr(); }

inline ThdrTCP* ThdrTCP::Ptr(ThdrIP* aHdr)
	{ return (ThdrTCP*)aHdr->EndPtr(); }

inline ThdrTCP* ThdrTCP::NetPtr(ThdrIP* aHdr)
	{ return (ThdrTCP*)aHdr->NetEndPtr(); }

inline TUint ThdrTCP::NetGetSrcPort()
	{ return ByteOrder::Swap16(u.iData16[0]); }
inline TUint ThdrTCP::NetGetDstPort()
	{ return ByteOrder::Swap16(u.iData16[1]); }

inline TUint ThdrTCP::GetSrcPort()
	{ return u.iData16[1]; }
inline void ThdrTCP::SetSrcPort(TUint aPort)
	{ u.iData16[1] = (TUint16)aPort; }

inline TUint ThdrTCP::GetDstPort()
	{ return u.iData16[0]; }
inline void ThdrTCP::SetDstPort(TUint aPort)
	{ u.iData16[0] = (TUint16)aPort; }

inline TUint ThdrTCP::GetChecksum()
	{ return u.iData16[9]; }
inline void ThdrTCP::SetChecksum(TUint aSum)
	{ u.iData16[9] = (TUint16)aSum; }
inline TUint ThdrTCP::NetGetChecksum()
	{ return u.iData16[8]; }
inline void ThdrTCP::NetSetChecksum(TUint aSum)
	{ u.iData16[8] = (TUint16)aSum; }

inline TUint ThdrTCP::GetSeqNum()
	{ return u.iData32[1]; }
inline void ThdrTCP::SetSeqNum(TUint aVal)
	{ u.iData32[1] = aVal; }
inline TUint ThdrTCP::GetAckNum()
	{ return u.iData32[2]; }
inline void ThdrTCP::SetAckNum(TUint aVal)
	{ u.iData32[2] = aVal; }

//#ifdef VJCOMP
/*
*       Take parameters in Little Endian form
*/
inline TUint ThdrTCP::NetGetSeqNum()
	{ return BigEndian::Get32((const TUint8*)&u.iData32[1]); }
inline void ThdrTCP::NetSetSeqNum(TUint aVal)
	{ BigEndian::Put32((TUint8 *)&u.iData32[1], aVal); }
inline TUint ThdrTCP::NetGetAckNum()
	{ return BigEndian::Get32((const TUint8*)&u.iData32[2]); }
inline void ThdrTCP::NetSetAckNum(TUint aVal)
	{ BigEndian::Put32((TUint8 *)&u.iData32[2], aVal); }
inline void ThdrTCP::NetSetUrgPtr(TUint aVal)
	{ BigEndian::Put16((TUint8 *)&u.iData16[9], (TUint16)aVal); }
inline TUint16 ThdrTCP::NetGetUrgPtr()
	{ return BigEndian::Get16((TUint8 *)&u.iData16[9]);}
inline TUint16 ThdrTCP::NetGetWindow()
	{ return BigEndian::Get16((TUint8 *)&u.iData16[7]);}
inline void ThdrTCP::NetSetWindow(TUint16 aVal)
	{ BigEndian::Put16((TUint8 *)&u.iData16[7], aVal); }
inline void ThdrTCP::VJSetChecksum(TUint aVal)
	{ BigEndian::Put16((TUint8 *)&u.iData16[8], (TUint16)aVal); }
inline TUint ThdrTCP::VJGetFlags()
	{ return u.iData8[13]; }
inline void ThdrTCP::VJSetFlags(TUint aVal)
	{ u.iData8[13] = (TUint8)aVal; }
//#endif


inline TUint ThdrTCP::GetUrgPtr()
	{ return u.iData16[8]; }
inline void ThdrTCP::SetUrgPtr(TUint aVal)
	{ u.iData16[8] = (TUint16)aVal; }
inline TUint ThdrTCP::GetWindow()
	{ return u.iData16[6]; }
inline void ThdrTCP::SetWindow(TUint aVal)
	{ u.iData16[6] = (TUint16)aVal; }
inline TUint ThdrTCP::GetHdrLen()
	{ return (u.iData8[15]>>4)<<2; }
inline void ThdrTCP::SetHdrLen(TUint aVal) // Safe because other bits should be 0
	{ u.iData8[15] = (TUint8)((aVal>>2)<<4); }
inline TUint ThdrTCP::NetGetHdrLen()
	{ return (u.iData8[12]>>4)<<2; }
inline TUint ThdrTCP::GetFlags()
	{ return u.iData8[14]; }
inline void ThdrTCP::SetFlags(TUint aVal)
	{ u.iData8[14] = (TUint8)aVal; }

#endif

