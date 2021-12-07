// S32MEM.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//
#if !defined(__S32MEM_H__)
#define __S32MEM_H__
#if !defined(__S32BUF_H__)
#include <s32buf.h>
#endif
#if !defined(__S32STOR_H__)
#include <s32stor.h>
#endif

class TMemBuf : public TStreamBuf
	{
public:
	IMPORT_C TMemBuf();
	IMPORT_C void Set(TUint8* aPtr,TUint8* anEnd,TInt aMode=ERead|EWrite);
protected:
	IMPORT_C TInt UnderflowL(TInt aMaxLength);
	IMPORT_C void OverflowL();
	IMPORT_C TStreamPos DoSeekL(TMark aMark,TStreamLocation aLocation,TInt anOffset);
private:
	inline TUint8* Base() const;
	inline TUint8* End() const;
private:
	TUint8* iBase;
	};
class TDesBuf : public TStreamBuf
	{
public:
	IMPORT_C TDesBuf();
	IMPORT_C void Set(TDes8& aDes,TInt aMode=ERead|EWrite);
protected:
	IMPORT_C TInt UnderflowL(TInt aMaxLength);
	IMPORT_C void OverflowL();
	IMPORT_C void DoSynchL();
	IMPORT_C TStreamPos DoSeekL(TMark aMark,TStreamLocation aLocation,TInt anOffset);
private:
	inline TDes8& Des() const;
	inline TUint8* Base() const;
 	void Consolidate();
private:
	TDes8* iDes;
	};
//
class TBufBuf : public TStreamBuf
	{
public:
	enum {ETruncate=0x10,EInsert=0x20};
public:
	IMPORT_C TBufBuf();
	IMPORT_C void Set(CBufBase& aBuf,TInt aPos,TInt aMode=ERead|EWrite);
protected:
	IMPORT_C TInt UnderflowL(TInt aMaxLength);
	IMPORT_C void OverflowL();
	IMPORT_C void DoSynchL();
	IMPORT_C void DoWriteL(const TAny* aPtr,TInt aLength);
	IMPORT_C TStreamPos DoSeekL(TMark aMark,TStreamLocation aLocation,TInt anOffset);
private:
	inline CBufBase& Buf() const;
 	void Consolidate();
//
	void SetPos(TMark aMark,TInt aPos);
	inline void SetPos(TRead,TInt aPos);
	inline void SetPos(TWrite,TInt aPos);
	TInt Pos(TMark aMark) const;
	inline TInt Pos(TRead) const;
	inline TInt Pos(TWrite) const;
	inline TInt MovePos(TRead,TInt anOffset);
	inline TInt MovePos(TWrite,TInt anOffset);
	inline TInt Mark(TRead) const;
	inline TInt Mark(TWrite) const;
private:
	CBufBase* iBuf;
	TInt iRPos;
	TInt iWPos;
	TInt iMode;
	};
//
class RMemReadStream : public RReadStream
	{
public:
	RMemReadStream() {}
	IMPORT_C RMemReadStream(const TAny* aPtr,TInt aLength);
	IMPORT_C void Open(const TAny* aPtr,TInt aLength);
private:
	TMemBuf iSource;
	};
class RMemWriteStream : public RWriteStream
	{
public:
	RMemWriteStream() {}
	inline RMemWriteStream(const MExternalizer<TStreamRef>& anExter);
	IMPORT_C RMemWriteStream(TAny* aPtr,TInt aMaxLength);
	IMPORT_C void Open(TAny* aPtr,TInt aMaxLength);
private:
	TMemBuf iSink;
	};
//
class RDesReadStream : public RReadStream
	{
public:
	RDesReadStream() {}
	IMPORT_C RDesReadStream(const TDesC8& aDes);
	IMPORT_C void Open(const TDesC8& aDes);
private:
	TMemBuf iSource;
	};
class RDesWriteStream : public RWriteStream
	{
public:
	RDesWriteStream() {}
	inline RDesWriteStream(const MExternalizer<TStreamRef>& anExter);
	IMPORT_C RDesWriteStream(TDes8& aDes);
	IMPORT_C void Open(TDes8& aDes);
private:
	TDesBuf iSink;
	};
//
class RBufReadStream : public RReadStream
	{
public:
	RBufReadStream() {}
	IMPORT_C RBufReadStream(const CBufBase& aBuf,TInt aPos=0);
	IMPORT_C void Open(const CBufBase& aBuf,TInt aPos=0);
private:
	TBufBuf iSource;
	};
class RBufWriteStream : public RWriteStream
	{
public:
	RBufWriteStream() {}
	inline RBufWriteStream(const MExternalizer<TStreamRef>& anExter);
	IMPORT_C RBufWriteStream(CBufBase& aBuf,TInt aPos=0);
	IMPORT_C void Open(CBufBase& aBuf,TInt aPos=0);
	IMPORT_C void Truncate(CBufBase& aBuf,TInt aPos=0);
	IMPORT_C void Insert(CBufBase& aBuf,TInt aPos);
	inline void Append(CBufBase& aBuf);
private:
	TBufBuf iSink;
	};
//
class CBufStore : public CStreamStore
	{
public:
	IMPORT_C static CBufStore* NewL(TInt anExpandSize);
	IMPORT_C static CBufStore* NewLC(TInt anExpandSize);
	IMPORT_C CBufStore(TInt anExpandSize);
	IMPORT_C ~CBufStore();
protected:
	IMPORT_C TStreamId DoExtendL();
	IMPORT_C void DoDeleteL(TStreamId anId);
	IMPORT_C MStreamBuf* DoReadL(TStreamId anId) const;
	IMPORT_C MStreamBuf* DoCreateL(TStreamId& anId);
	IMPORT_C MStreamBuf* DoWriteL(TStreamId anId);
	IMPORT_C MStreamBuf* DoReplaceL(TStreamId anId);
private:
	CBufSeg& BufL(TStreamId anId) const;
private:
	CArrayFixFlat<CBufSeg*> iBufArray;
	TInt iExpandSize;
	};		

#include <s32mem.inl>
#endif
