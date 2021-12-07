// SMSUSTRM.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//



/*
-----------------------------------------------------------------------------

    DESCRIPTION

    This file contains the header file of the CSmsBuffers.

-----------------------------------------------------------------------------
*/

#if !defined (__SMSUSTRM_H__)
#define __SMSUSTRM_H__

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif

#if !defined(__S32BUF_H__)
#include <s32buf.h>
#endif

#if !defined(__S32STRM_H__)
#include <s32strm.h>
#endif


class RSocket;

const TInt KSmsMaxSegmentLength=0x100;

class RSmsSocketBuf : public TStreamBuf
	{
public:
	RSmsSocketBuf(RSocket& aSocket);
private:
// from TStreamBuf
	TInt UnderflowL(TInt aMaxLength);
	void OverflowL();
	void DoSynchL();
private:
	void SocketWriteL();
//
	inline TInt Lag(TRead) const;
	inline TInt Lag(TWrite) const;
private:
	RSocket& iSocket;
	TUint8 iBuffer[KSmsMaxSegmentLength];
	};

class RSmsSocketReadStream : public RReadStream
	{
public:
	IMPORT_C RSmsSocketReadStream(RSocket& aSocket);
private:
	RSmsSocketBuf iBuf;
	};

class RSmsSocketWriteStream : public RWriteStream
	{
public:
	IMPORT_C RSmsSocketWriteStream(RSocket& aSocket);
private:
	RSmsSocketBuf iBuf;
	};

#include "smsustrm.inl"

#endif // !defined __SMSUSTRM_H__
