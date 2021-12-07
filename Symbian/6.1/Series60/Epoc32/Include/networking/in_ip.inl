// IN_IP.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __IN_IP_INL__
#define __IN_IP_INL__

inline ThdrIP* ThdrIP::Ptr(RMBufPacketBase& aPacket)
	{ return (ThdrIP*)aPacket.First()->Ptr(); }

inline ThdrIP* ThdrIP::Ptr(ThdrICMP* aHdr)
	{ return (ThdrIP*)aHdr->IpPtr(); }

inline TUint8* ThdrIP::EndPtr()
	{ return ((TUint8*)this)+GetHdrLen(); }

inline TUint8* ThdrIP::NetEndPtr()
	{ return ((TUint8*)this)+NetGetHdrLen(); }

inline TUint8* ThdrIP::OptPtr()
	{ return ((TUint8*)this)+KIPMinHeaderSize; }

inline TBool ThdrIP::IsOptCopied(TUint8* aBuf)
	{ return aBuf[KIPOptionValByte] & KIPOptionIsCopiedFlag; }

inline TUint ThdrIP::GetVersion()
	{ return u.iData8[3]>>4; }
inline void ThdrIP::SetVersion(TUint aVal)
	{ u.iData8[3] = (TUint8)((u.iData8[3] & 0x0f) | (aVal<<4)); }
inline TUint ThdrIP::NetGetVersion()
	{ return u.iData8[0]>>4; }

inline TUint ThdrIP::GetHdrLen()
	{ return (u.iData8[3] & 0x0f)<<2; }
inline void ThdrIP::SetHdrLen(TUint aVal)
	{ u.iData8[3] = (TUint8)((u.iData8[3] & 0xf0) | (aVal>>2)); }
inline TUint ThdrIP::NetGetHdrLen()
	{ return (u.iData8[0] & 0x0f)<<2; }

inline TUint ThdrIP::GetTOS()
	{ return u.iData8[2]; }
inline void ThdrIP::SetTOS(TUint aVal)
	{ u.iData8[2] = (TUint8)aVal; }

inline TUint ThdrIP::GetLength()
	{ return u.iData16[0]; }
inline void ThdrIP::SetLength(TUint aVal)
	{ u.iData16[0] = (TUint16)aVal; }


inline TUint ThdrIP::GetId()
	{ return u.iData16[3]; }
inline void ThdrIP::SetId(TUint aVal)
	{ u.iData16[3] = (TUint16)aVal; }

//#ifdef VJCOMP
/*
*       Little Endian not swapped
*/
inline TUint ThdrIP::NetGetId()
	{ return BigEndian::Get16((const TUint8 *)&u.iData16[2]);}
inline void ThdrIP::NetSetId(TUint aVal)
	{ BigEndian::Put16((TUint8 *)&u.iData16[2],(TUint16)aVal); }
inline TUint16 ThdrIP::NetGetLength()
	{ return BigEndian::Get16((const TUint8*)&u.iData16[1]); }
inline void ThdrIP::NetSetLength(TUint16 aVal)
	{ BigEndian::Put16((TUint8*)&u.iData16[1],aVal); }
inline void ThdrIP::NetSetProtocol(TUint aVal)
	{ u.iData8[9] = (TUint8)aVal; }
inline void ThdrIP::VJSetChecksum(TUint16 aVal)
        { BigEndian::Put16((TUint8 *)&u.iData16[5], aVal);}
inline TUint ThdrIP::NetGetFragment()
	{ return u.iData16[3] & 0x3fff; } // just offset and MF flag
inline TUint16 ThdrIP::Word0()
	{ return u.iData16[0];}
inline TUint16 ThdrIP::Word3()
	{ return u.iData16[3];}
inline TUint16 ThdrIP::Word4()
	{ return u.iData16[4];}
inline TUint8* ThdrIP::GetOptions()
	{ return (&u.iData8[0])+KIPMinHeaderSize; }
//#endif


inline TUint ThdrIP::GetMF()
	{ return (u.iData8[5] & 0x20) >> 5; }
inline void ThdrIP::SetMF(TUint aVal)
	{ u.iData8[5] = (TUint8) ((u.iData8[5] & ~0x20) | (aVal<<5)) ; }

inline TUint ThdrIP::GetDF()
	{ return (u.iData8[5] & 0x40) >> 6; }
inline void ThdrIP::SetDF(TUint aVal)
	{ u.iData8[5] = (TUint8) ((u.iData8[5] & ~0x40) | (aVal<<6)) ; }

inline TUint ThdrIP::GetOffset()
	{ return (u.iData16[2] & 0x1fff) << 3; }
inline void ThdrIP::SetOffset(TUint aVal)
	{ u.iData16[2] = (TUint16)((u.iData16[2] & 0x1fff) | (aVal>>3)); }

inline TUint ThdrIP::GetFragment()
	{ return u.iData16[2] & 0x3fff; } // just offset and MF flag
inline void ThdrIP::SetFragment(TUint aVal)
	{ u.iData16[2] = (TUint16)aVal; }
inline void ThdrIP::SetFragment(TUint aOffset, TUint aMF)
	{ u.iData16[2] = (TUint16)(aOffset>>3 | aMF << 13); }

inline TUint ThdrIP::GetTTL()
	{ return u.iData8[11]; }
inline void ThdrIP::SetTTL(TUint aVal)
	{ u.iData8[11] = (TUint8)aVal; }

inline TUint ThdrIP::GetProtocol()
	{ return u.iData8[10]; }
inline TUint ThdrIP::NetGetProtocol()
	{ return u.iData8[9]; }
inline void ThdrIP::SetProtocol(TUint aVal)
	{ u.iData8[10] = (TUint8)aVal; }

inline TUint ThdrIP::GetChecksum()
	{ return u.iData16[4]; }
inline void ThdrIP::SetChecksum(TUint aVal)
	{ u.iData16[4] = (TUint16)aVal; }

inline TUint ThdrIP::NetGetChecksum()
	{ return u.iData16[5]; }
inline void ThdrIP::NetSetChecksum(TUint aVal)
	{ u.iData16[5] = (TUint16)aVal; }
	
inline TUint32 ThdrIP::GetSrcAddr()
	{ return iSrcAddr; }
inline TUint32 ThdrIP::NetGetSrcAddr()
	{ return ByteOrder::Swap32(iSrcAddr); }
inline void ThdrIP::SetSrcAddr(TUint32 aAddr)
	{ iSrcAddr = aAddr; }

inline TUint32 ThdrIP::GetDstAddr()
	{ return iDstAddr; }
inline TUint32 ThdrIP::NetGetDstAddr()
	{ return ByteOrder::Swap32(iDstAddr); }
inline void ThdrIP::SetDstAddr(TUint32 aAddr)
	{ iDstAddr = aAddr; }

inline void ThdrIP::SetWord0(TUint aHdrLen, TUint aTOS, TUint aLen)
	{ u.iData32[0] = 0x40000000 | (aHdrLen<<22) | (aTOS<<16) | aLen; }
inline void ThdrIP::SetWord1(TUint aId)
	{ u.iData32[1] = aId<<16; }
inline void ThdrIP::SetWord1(TUint aId, TUint aDF)
	{ u.iData32[1] = (aId<<16) | (aDF<<14); }
inline void ThdrIP::SetWord1(TUint aId, TUint aMF, TUint aOffset)
	{ u.iData32[1] = (aId<<16) | (aMF<<13) | (aOffset>>3); }
inline void ThdrIP::SetWord2(TUint aTTL, TUint aProtocol) // Checksum invariably set afterwards
	{ u.iData32[2] = (aTTL<<24) | (aProtocol<<16); }

inline ThdrICMP* ThdrICMP::Ptr(RMBufPacketBase& aPacket)
	{ return (ThdrICMP*)aPacket.First()->Ptr(); }

inline ThdrICMP* ThdrICMP::Ptr(ThdrIP* aHdr)
	{ return (ThdrICMP*)aHdr->EndPtr(); }

inline ThdrICMP* ThdrICMP::NetPtr(ThdrIP* aHdr)
	{ return (ThdrICMP*)aHdr->NetEndPtr(); }

inline ThdrIP* ThdrICMP::IpPtr()
	{ return (ThdrIP*)(((TUint8*)this)+8); }

inline TUint ThdrICMP::NetGetType()
	{ return u.iData8[0]; }
inline void ThdrICMP::NetSetType(TInt aVal)
	{ u.iData8[0] = (TUint8)aVal; }
inline TUint ThdrICMP::NetGetCode()
	{ return u.iData8[1]; }
inline void ThdrICMP::NetSetCode(TInt aVal)
	{ u.iData8[1] = (TUint8)aVal; }
inline void ThdrICMP::NetSet(TUint aType, TUint aCode)
	{ u.iData8[0] = (TUint8)aType; u.iData8[1] = (TUint8)aCode; }
inline TInt ThdrICMP::NetGetChecksum()
	{ return u.iData16[1]; }
inline void ThdrICMP::NetSetChecksum(TInt aSum)
	{ u.iData16[1] = (TUint16)aSum; }

#endif
