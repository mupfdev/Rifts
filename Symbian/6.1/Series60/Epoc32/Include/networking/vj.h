// VJ.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__VJ_H__)
#define __VJ_H__

#include <networking\in_tcp.h>
#include <networking\vjif.h>

const TUint8 KVJDiscard			= 1;

const TUint8 KMaxVjSlots		= 16;
const TUint8 KVjCompSlotId		= 1;
const TUint8 KVjCompMaskConn	= 0x40;
const TUint8 KVjCompMaskIp		= 0x20;
const TUint8 KVjCompMaskPush	= 0x10;
const TUint8 KVjCompMaskSeq		= 0x08;
const TUint8 KVjCompMaskAck		= 0x04;
const TUint8 KVjCompMaskWindow	= 0x02;
const TUint8 KVjCompMaskUrgent	= 0x01;
const TUint8 KVjCompMaskSpecialD = KVjCompMaskSeq 
								| KVjCompMaskAck 
								| KVjCompMaskWindow 
								| KVjCompMaskUrgent;
const TUint8 KVjCompMaskSpecials = KVjCompMaskSpecialD;
const TUint8 KVjCompMaskSpecialI = KVjCompMaskSeq 
								| KVjCompMaskWindow 
								| KVjCompMaskUrgent;


const TUint32 KUidVJCompDll		=  0x10000ba8;
const TUint32 KUidUnicodeVJCompDll		=  0x10003d43;

// moved from ncpip.h
const TUint KPppIdIp = 0x0021;
const TUint KPppIdVjCompTcp = 0x002d;
const TUint KPppIdVjUncompTcp = 0x002f;
//

class TVJCompHdr
	{
public:
	TVJCompHdr();
	void			StoreTCPIPHeader(ThdrIP * aHeader);
	void			RetrieveTCPIPHeader(ThdrIP* aIPHeader, ThdrTCP* aTCPHeader);
	void			SetNextPtr(TVJCompHdr * aNextPtr);
	TVJCompHdr*		NextPtr();
	void			SetConnectionNumber(TUint aConnection);
	TUint			ConnectionNumber();
private:
	TVJCompHdr*		iNextPtr;
	TUint			iConnectionId;
	ThdrIP			iIPHeader;
	ThdrTCP			iTCPHeader;
	};

class CVJDeCompressor : public CVJDeCompressorIf
	{
public:
	~CVJDeCompressor();
	//IMPORT_C static CVJDeCompressor* NewL(TUint aSlots);
	TBool	DecompVJUncomp(RMBufChain& aPacket);
	TBool	DecompVJComp(RMBufChain& aPacket);
	void	CRCError();
	void	ConstructL( CVJCompFactory* aFactory, TUint aSlots );
	CVJDeCompressor(TUint aSlots);
private:
	inline	void	SetFlag( const TUint aFlag);
	inline	void	ClearFlag( const TUint aFlag);
	inline	TBool	TestFlag( const TUint aFlag);
	void	DecompSWAU(const TUint aChanges, TUint8** aVJCompHeader, ThdrTCP* aTCPHeader, TUint16 aPreviousFrameLength);
	void	DecompPushFlag(const TUint aChanges, ThdrTCP* aHeader);
	void	DecompIPId(const TUint aChanges, TUint8** aVJCompHeader, ThdrIP* aIPHeader );
	TUint16	DecodeDelta( TUint8 ** aVJCompHeader );
	void	EncodeDelta(TUint8** aVJCompHeader, TUint16 aValue);
	void	DecompUrgent(TUint8** aVJCompHeader, ThdrTCP* aTCPHeader, TUint aChanges);
	void	DecompWindow(TUint8** aVJCompHeader, ThdrTCP* aTCPHeader);
	void	DecompAck(TUint8** aVJCompHeader, ThdrTCP* aTCPHeader);
	void	DecompSeq(TUint8** aVJCompHeader, ThdrTCP* aTCPHeader);
	TUint8*	GetVJPtr(RMBufChain &aChain, TUint16* aCurrentFrameLength);
	void	DecompressFrameL(RMBufChain& aPacket, TUint8 aConnection, TUint8 aChanges, TUint8* aInitialHeaderPtr, TUint Offset, TUint16 aCurrentFrameLength);
	void	CopyInNewHeaderL(RMBufChain* aPacket, ThdrIP * aIPHeader, ThdrTCP * aTCPHeader, TUint aCompressedHeaderLength, TUint16 aIPHeaderLength, TUint16 aTCPHeaderLength);
	ThdrIP*	GetIPHeader(RMBufChain &aChain);
	void	DoIPChecksum(ThdrIP* aIPHeader, TUint16 aIPHeaderLength);
	void	CopyRecvHeader(const TUint aConnectionNumber, ThdrIP * aHeader);
	void	GetStoredRxHeader(const TUint aConnectionNumber, ThdrIP * aIPHeader, ThdrTCP * aTCPHeader);
	
private:
	TUint		iNumVJSlots;
	TUint		iLastRxConn;
	TUint		iFlags;
	TVJCompHdr* iRxStates;
	//TVJCompHdr	iRxStates[KMaxVjSlots];
	};

#include <networking\vjdecomp.inl>

class CVJCompressor : public CVJCompressorIf
	{
public:

	~CVJCompressor();
	//IMPORT_C static CVJCompressor* NewL( TUint aSlots, TBool aCompressConnId );
	TInt	VJCompressFrame(RMBufChain& aPacket);
	void	ConstructL( CVJCompFactory* aFactory, TUint aSlots, TBool aCompressConnId );
	CVJCompressor(TUint aSlots, TBool aCompressConnId);
private:
	void	EncodeDelta(TUint8** aVJCompHeader, TUint16 aValue);
	TUint8*	GetVJPtr(RMBufChain &aChain, TUint16* aCurrentFrameLength);
	ThdrIP*	GetIPHeader(RMBufChain &aChain);
	void	DoIPChecksum(ThdrIP* aIPHeader, TUint16 aIPHeaderLength);
	TBool	SuitableForVJCompression(ThdrIP* aIPHeader, ThdrTCP* aTCPHeader, TUint* aConnection, ThdrIP* aRetrievedIPHdr, ThdrTCP* aRetrievedTCPHdr);
	TBool	CompressFrame(	RMBufChain& aPacket, 
							ThdrIP* aIPHeader, 
							ThdrTCP* aTCPHeader, 
							TUint aConnection,
							ThdrIP* aRetrievedIPHdr,
							ThdrTCP* aRetrievedTCPHdr);
	TBool	SendAsRawIP(ThdrIP* aIPHeader, ThdrTCP* aTCPHeader);
	TBool	IsIPCompressible( ThdrIP* aIPHeader, ThdrIP* aRetrievedIPHdr);
	TBool	IsTCPCompressible( ThdrTCP* aTCPHeader, ThdrTCP* aRetrievedTCPHdr);
	TBool	CompressUrgentPtr(TUint8** aVJPtr, TUint8* aChanges, ThdrTCP* aTCPHeader, ThdrTCP* aRetrievedTCPHdr);
	TBool	CompressWindow(TUint8** aVJPtr, TUint8* aChanges, ThdrTCP* aTCPHeader, ThdrTCP* aRetrievedTCPHdr);
	TBool	CompressAck(TUint8** aVJPtr, TUint8* aChanges, ThdrTCP* aTCPHeader, ThdrTCP* aRetrievedTCPHdr);
	TBool	CompressSeq(TUint8** aVJPtr, TUint8* aChanges, ThdrTCP* aTCPHeader, ThdrTCP* aRetrievedTCPHdr);
	TBool	CompressIPId(TUint8** aVJPtr, TUint8* aChanges, ThdrIP* aIPHeader, ThdrIP* aRetrievedIPHdr);
	TBool	CompressPush(TUint8* aChanges,  ThdrTCP* aTCPHeader);
	TBool	IsSameConnAsLast(TUint* aCompressedHdrLen, TUint aConnection);
	void	SetFirstFewBytes(TUint8* aChanges, TBool aNewConnection, TUint8** aVJHeader, ThdrTCP* aTCPHeader, TUint aConnection);
	void	CopyInNewTxHeader(RMBufChain& aPacket, TUint8* aCompressedHdr, TUint aOldHeaderLength, TUint aNewHeaderLength);
	void	DecrementPacketLen( RMBufChain& aPacket, TUint SizeDecrease );
	TBool	CompressSpecialCases(	TUint8** aVJPtr, 
									TUint8* aVJInitialDeltaPtr, 
									TUint8* aChanges, 
									ThdrTCP* aTCPHeader, 
									ThdrTCP* aRetrievedTCPHdr, 
									ThdrIP* aIPHeader,
									ThdrIP* aRetrievedIPHdr);
	void	ConvertFrameToUncompVJ(ThdrIP* aIPHeader, TUint aConnection);
	TUint8* GetTCPOpts(ThdrTCP* aTCPHeader);
	void	CopyTxHeader( ThdrIP* aIPHeader, TUint aConnection);
	TBool	GetStoredTxHeader(	TUint* aConnection, 
								ThdrIP * aIPHeader, 
								ThdrTCP* aTCPHeader, 
								ThdrIP* aRetrievedIPHdr, 
								ThdrTCP* aRetrievedTCPHdr);
	TBool	IPAddressesMatch(ThdrIP* aIPHeader,ThdrIP* aNotherIPHdr);	
	TBool	TCPPortsMatch(ThdrTCP* aHeader, ThdrTCP* aNotherHdr );
private:
	TUint		iMaxVJSlots;
	TBool		iCompressConnId;
	TUint		iLastTxConn;
	TVJCompHdr*	iLastTxHdr;

	TVJCompHdr*	iTxStates;
	//TVJCompHdr	iTxStates[KMaxVjSlots];
	};

class CVJFactory : public CVJCompFactory
	{
// Factory base for creating a concrete instance of a CSSLBase
public:
	CVJFactory();
	void InstallL();
	CVJCompressorIf* NewVJCompressorL( TInt aMaxVJSlots, TInt aCompressConnId);
	CVJDeCompressorIf* NewVJDeCompressorL(TInt aMaxVJSlots);
	};

#endif // __VJ_H__
