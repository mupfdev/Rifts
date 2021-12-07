// PPPCOMP.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __PPPCOMP_H__
#define __PPPCOMP_H__

#include <es_mbuf.h>

// Return value from call to compress module
enum TPppCompressReturnValue
	{ EPppCompressedOK, EPppCompressedNotOK, EPppCompressedFrameExpanded };

class CNifFactory;
class CPppCompressor : public CObject
	{
public:
	CPppCompressor(){};
	virtual ~CPppCompressor(){};

	virtual TPppCompressReturnValue Compress(RMBufChain& aPacket, TUint16 aPppId)=0;
	virtual TBool ResetCompressor(TInt aLength, RMBufChain& aPacket)=0;
protected:
	CNifFactory*	iFactory;
	};

class CPppDeCompressor : public CObject
	{
public:
	virtual TBool Decompress(RMBufQ& aBufferQ)=0;
	virtual void ResetDecompressor(TInt aLength, RMBufChain& aPacket)=0;

	CPppDeCompressor(){};
	virtual ~CPppDeCompressor(){};
protected:
	CNifFactory*	iFactory;
	};

#endif __PPPCOMP_H__
