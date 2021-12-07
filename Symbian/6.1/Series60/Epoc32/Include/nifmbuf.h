// NIFMBUF.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

//
// MBuf Manager Extensions
//

#ifndef __NIFMBUF_H__
#define __NIFMBUF_H__

#ifndef __ES_MBUF_H__
#include <es_mbuf.h>
#endif

#ifndef __ES_SOCK_H__
#include <es_sock.h>
#endif

////////////////////////////////////////////////////////////////////////////////
// Support for parsing of data in MBuf chains
////////////////////////////////////////////////////////////////////////////////

class TMBufMark
	{
public:
	IMPORT_C TMBufMark();
	IMPORT_C TMBufMark(const TMBufMark& aParser);
	IMPORT_C TMBufMark(const RMBufChain& aChain, TInt aOffset=0);
	IMPORT_C void Set(const RMBufChain& aChain, TInt aOffset=0);
	IMPORT_C void Skip(TInt aLength);
	IMPORT_C void Get(TDes8& aBuf);
	IMPORT_C void Get(TUint8* aPtr, TInt aLen);
	inline TUint8 Get8();
	inline TUint16 GetLE16();
	inline TUint32 GetLE32();
	inline TUint16 GetBE16();
	inline TUint32 GetBE32();
	inline TBool AtEnd();
protected:
	TInt iOffset;
	RMBuf* iMBuf;
	TInt iPtr;
	};

inline TUint8 TMBufMark::Get8()
	{ TUint8 val; Get((TUint8*)&val, sizeof(val)); return val; }
inline TUint16 TMBufMark::GetLE16()
	{ TUint16 val; Get((TUint8*)&val, sizeof(val)); return val; }
inline TUint32 TMBufMark::GetLE32()
	{ TUint32 val; Get((TUint8*)&val, sizeof(val)); return val; }
inline TUint16 TMBufMark::GetBE16()
	{ TUint16 val; Get((TUint8*)&val, sizeof(val)); return ByteOrder::Swap16(val); }
inline TUint32 TMBufMark::GetBE32()
	{ TUint32 val; Get((TUint8*)&val, sizeof(val)); return ByteOrder::Swap32(val); }

inline TBool TMBufMark::AtEnd()
	{ return iMBuf==NULL; }

////////////////////////////////////////////////////////////////////////////////
// Support to use single MBufs for containing C++ objects
////////////////////////////////////////////////////////////////////////////////

class RMBufCell
	{
public:
	IMPORT_C RMBufCell(RMBufCell* aPktHdr);
	IMPORT_C static TAny* operator new(TUint aSize, TLeave aLeave, TUint aExtra);
	IMPORT_C static void operator delete(TAny*);
	IMPORT_C RMBufCell* CopyL();
	//
	inline RMBufCell() {}	// to prevent statement has no effect
	static inline TAny* operator new(TUint aSize, TLeave aLeave)
		{ return operator new (aSize, aLeave, 0); }
	inline RMBuf* MBuf();
	//
private:
	RMBuf* iThisMBuf;
	};

inline RMBuf* RMBufCell::MBuf()
	{ return iThisMBuf; }

////////////////////////////////////////////////////////////////////////////////
// MBuf Stream Queue
////////////////////////////////////////////////////////////////////////////////

class RMBufStreamQ : public RMBufQ
	{
public:
	IMPORT_C RMBufStreamQ();
	IMPORT_C void TrimStart(TInt aOffset);
	IMPORT_C void CopyOut(TDes8& aDes);
	IMPORT_C void CopySegmentL(RMBufChain &aNewChain, TInt aOffset, TInt aLen);
	IMPORT_C void Append(RMBufChain& aPacket);
protected:
	inline RMBufChain& AsRMBufChain() { return *((RMBufChain*)this); }
protected:
	// Pointers cache
	TInt iPosition;
	RMBuf* iMBuf;
	TInt iOffset;
	TInt iLength;		
	};

////////////////////////////////////////////////////////////////////////////////
// Inter-Protocol Information carried in header MBuf
////////////////////////////////////////////////////////////////////////////////

class RMBufPktInfo : public RMBufCell
	{
public:
	TSockAddr iSrcAddr;	// Source address of packet according to iProtocol
	TSockAddr iDstAddr;	// Destination address of packet according to protocol
	TInt iProtocol;		// ID of protocol who is giving you this
	TInt iLength;		// Actual length of packet
	TUint iFlags;		// Packet flags
	};

////////////////////////////////////////////////////////////////////////////////
// Holder for MBuf Chain with inter-protocol header split off
////////////////////////////////////////////////////////////////////////////////

class RMBufPacketBase : public RMBufChain
	{
	__DECLARE_CLEANUP
public:
	IMPORT_C RMBufPacketBase();
	IMPORT_C void CopyInfoL(RMBufPacketBase& aNewPkt);
	IMPORT_C void CopyPackedL(RMBufChain& aPacket);
	IMPORT_C void Pack();
	IMPORT_C void SetInfo(RMBufPktInfo* iInfo);
	IMPORT_C void FreeInfo();
	IMPORT_C void Free();
	IMPORT_C void TrimStart(TInt aOffset);
	IMPORT_C void TrimEnd(TInt aOffset);
	IMPORT_C RMBufPktInfo* Unpack();
	IMPORT_C RMBufPktInfo* Info();
	IMPORT_C RMBufPktInfo* PeekInfo();
	IMPORT_C RMBufPktInfo* NewInfoL(TUint aMBufHdrSize);
	IMPORT_C static RMBufPktInfo* PeekInfoInChain(RMBufChain& aChain);
protected:
	IMPORT_C RMBufPktInfo* CreateL(RMBufQ& aPacket, TInt aLength, TUint aMBufHdrSize);
	IMPORT_C RMBufPktInfo* CreateL(TInt aLength, TUint aMBufHdrSize);
	IMPORT_C RMBufPktInfo* CreateL(const TDesC8 &aDesc, TInt aHdrSize, TUint aMBufHdrSize);
	IMPORT_C RMBufPktInfo* CreateCopyL(const RMBufQ& aPacket, TInt aOffset, TInt aLength, TInt aHdrSize, TUint aMBufHdrSize);
	IMPORT_C RMBufPktInfo* CreateCopyL(RMBufStreamQ& aStream, TInt aOffset, TInt aLength, TInt aHdrSize, TUint aMBufHdrSize);
	IMPORT_C RMBufPktInfo* CreateCopyL(const RMBufPktQ& aList, TInt aHdrSize, TUint aMBufHdrSize);
protected:
	RMBufPktInfo* iInfo;
	};

template <class T>
class RMBufInfoPacketBase : public RMBufPacketBase
	{
public:
	inline T* Unpack()
		{ return (T*)RMBufPacketBase::Unpack(); }
	inline T* Info()
		{ return (T*)RMBufPacketBase::Info(); }
	inline T* PeekInfo()
		{ return (T*)RMBufPacketBase::PeekInfo(); }
	inline static T* PeekInfoInChain(RMBufChain& aChain)
		{ return (T*)RMBufPacketBase::PeekInfoInChain(aChain); }
	inline T* NewInfoL()
		{ return (T*)RMBufPacketBase::NewInfoL(sizeof(T)); }
	inline T* CreateL(TInt aHdrSize)
		{ return (T*)RMBufPacketBase::CreateL(aHdrSize, sizeof(T)); };
	inline T* CreateL(const TDesC8 &aDesc, TInt aHdrSize=0)
		{ return (T*)RMBufPacketBase::CreateL(aDesc, aHdrSize, sizeof(T)); };
	inline T* CreateL(RMBufQ& aPacket, TInt aLength=0)
		{ return (T*)RMBufPacketBase::CreateL(aPacket, aLength, sizeof(T)); };
	inline T* CreateCopyL(const RMBufQ& aPacket, TInt aOffset, TInt aLength, TInt aHdrSize=0)
		{ return (T*)RMBufPacketBase::CreateCopyL(aPacket, aOffset, aLength, aHdrSize, sizeof(T)); };
	inline T* CreateCopyL(RMBufStreamQ& aStream, TInt aOffset, TInt aLength, TInt aHdrSize=0)
		{ return (T*)RMBufPacketBase::CreateCopyL(aStream, aOffset, aLength, aHdrSize, sizeof(T)); };
	inline T* CreateCopyL(const RMBufPktQ& aList, TInt aHdrSize=0)
		{ return (T*)RMBufPacketBase::CreateCopyL(aList, aHdrSize, sizeof(T)); };
	};

typedef class RMBufInfoPacketBase<RMBufPktInfo> RMBufPacket;

#endif
