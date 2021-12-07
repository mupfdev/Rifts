// VJIF.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __VJIF_H__
#define __VJIF_H__

#include <nifman.h>

class CVJCompressorIf : public CObject
	{
public:
	CVJCompressorIf(){};
	virtual ~CVJCompressorIf(){};
	virtual TInt VJCompressFrame(RMBufChain& aPacket)=0;
protected:
	CNifFactory*	iFactory;
	};

class CVJDeCompressorIf : public CObject
	{
public:
	CVJDeCompressorIf(){};
	virtual ~CVJDeCompressorIf(){};
	virtual TBool DecompVJUncomp(RMBufChain& aPacket)=0;
	virtual TBool DecompVJComp(RMBufChain& aPacket)=0;
	virtual void CRCError()=0;
protected:
	CNifFactory*	iFactory;
	};

class CVJCompFactory : public CNifFactory
	{
// Factory base for creating a concrete instance of a CVJCompressor
public:
	virtual void InstallL()=0;
	virtual CVJCompressorIf* NewVJCompressorL( TInt aMaxVJSlots, TInt aCompressConnId)=0;
	virtual CVJDeCompressorIf* NewVJDeCompressorL(TInt aMaxVJSlots)=0;
	};

#endif __VJIF_H__
