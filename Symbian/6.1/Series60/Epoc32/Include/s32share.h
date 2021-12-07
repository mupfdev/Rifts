// S32SHARE.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//
#if !defined(__S32SHARE_H__)
#define __S32SHARE_H__
#if !defined(__S32BUF_H__)
#include <s32buf.h>
#endif
#if !defined(__S32STRM_H__)
#include <s32strm.h>
#endif

class TStreamExchange;
class TStreamMark
	{
public:
	inline TStreamMark();
	inline TStreamMark(TStreamPos aPos);
	inline TStreamMark& operator=(TStreamPos aPos);
	inline operator TStreamMark*();
	inline operator const TStreamMark*() const;
//
	inline TBool operator==(const TStreamMark& aMark) const;
	inline TBool operator==(const TStreamMark* aPtr) const;
	inline TBool operator!=(const TStreamMark& aMark) const;
	inline TBool operator!=(const TStreamMark* aPtr) const;
//
	inline TBool IsEmpty() const;
	inline void Clear();
	inline TStreamPos Position() const;
//
	inline TBool IsWith(TStreamExchange& aHost) const;
	inline TBool RelatesTo(TStreamExchange& aHost) const;
	inline void Withdraw(TStreamExchange& aHost);
	inline void ExtractL(TStreamExchange& aHost);
//
	inline TInt ReadL(TStreamExchange& aHost,TAny* aPtr,TInt aMaxLength);
	IMPORT_C TInt ReadL(TStreamExchange& aHost,TDes8& aDes,TRequestStatus& aStatus);
	inline TInt ReadL(TStreamExchange& aHost,TDes8& aDes,TInt aMaxLength,TRequestStatus& aStatus);
	inline TStreamTransfer ReadL(TStreamExchange& aHost,MStreamInput& anInput,TStreamTransfer aTransfer);
	inline TInt ReadL(TStreamExchange& aHost,MStreamInput& anInput,TInt aMaxLength);
	inline void ReadL(TStreamExchange& aHost,MStreamInput& anInput);
//
	inline void WriteL(TStreamExchange& aHost,const TAny* aPtr,TInt aLength);
	IMPORT_C TInt WriteL(TStreamExchange& aHost,const TDesC8& aDes,TRequestStatus& aStatus);
	inline TInt WriteL(TStreamExchange& aHost,const TDesC8& aDes,TInt aMaxLength,TRequestStatus& aStatus);
	inline TStreamTransfer WriteL(TStreamExchange& aHost,MStreamOutput& anOutput,TStreamTransfer aTransfer);
	inline TInt WriteL(TStreamExchange& aHost,MStreamOutput& anOutput,TInt aMaxLength);
	inline void WriteL(TStreamExchange& aHost,MStreamOutput& anOutput);
//
	inline void SeekL(TStreamExchange& aHost,TStreamPos aPos);
	inline TStreamPos SeekL(TStreamExchange& aHost,TStreamLocation aLocation,TInt anOffset=0);
	inline TStreamPos SeekL(TStreamExchange& aHost,TInt anOffset);
//
	inline TStreamPos TellL(TStreamExchange& aHost) const;
private:
	TStreamMark(const TStreamMark&);
	TStreamMark& operator=(const TStreamMark&);
private:
	TStreamPos iPos;
private:
	inline TBool IsTracking(TStreamMark*const& aRef) const;
	inline void Track(TStreamMark*const& aRef);
private:
	friend class TStreamExchange;
private:
	IMPORT_C static void __DbgChkPos(TStreamPos aPos);
	};
inline TBool operator==(const TStreamMark* aPtr,const TStreamMark& aMark);
inline TBool operator!=(const TStreamMark* aPtr,const TStreamMark& aMark);
//
class TStreamExchange
	{
public:
	inline TStreamExchange();
	inline TStreamExchange(MStreamBuf* aHost);
	inline void Share(MStreamBuf* aHost);
	inline TBool IsActive() const;
	IMPORT_C MStreamBuf* Host();
	IMPORT_C MStreamBuf* HostL();
	IMPORT_C void Release();
//
	IMPORT_C TInt SizeL() const;
private:
	typedef MStreamBuf::TMark TMark;
private:
	TStreamExchange(const TStreamExchange&);
	TStreamExchange& operator=(const TStreamExchange&);
//
	IMPORT_C TBool RefersTo(const TStreamMark& aMark);
	IMPORT_C void Drop(const TStreamMark& aMark);
	IMPORT_C void GetL(TStreamMark& aMark);
	IMPORT_C TInt DoReadL(TAny* aPtr,TInt aMaxLength,TStreamMark& aMark);
	IMPORT_C TInt DoReadL(TDes8& aDes,TInt aMaxLength,TRequestStatus& aStatus,TStreamMark& aMark);
	IMPORT_C TStreamTransfer DoReadL(MStreamInput& anInput,TStreamTransfer aTransfer,TStreamMark& aMark);
	IMPORT_C void DoWriteL(const TAny* aPtr,TInt aLength,TStreamMark& aMark);
	IMPORT_C TInt DoWriteL(const TDesC8& aDes,TInt aMaxLength,TRequestStatus& aStatus,TStreamMark& aMark);
	IMPORT_C TStreamTransfer DoWriteL(MStreamOutput& anOutput,TStreamTransfer aTransfer,TStreamMark& aMark);
	IMPORT_C TStreamPos DoSeekL(TStreamMark& aMark,TStreamLocation aLocation,TInt anOffset);
//
	void PrepareForReadingL(TStreamMark& aMark);
	void PrepareForWritingL(TStreamMark& aMark);
//
	TInt PrepareAndReadL(TAny* aPtr,TInt aMaxLength,TStreamMark& aMark);
	TInt PrepareAndReadL(TDes8& aDes,TInt aMaxLength,TRequestStatus& aStatus,TStreamMark& aMark);
	TStreamTransfer PrepareAndReadL(MStreamInput& anInput,TStreamTransfer aTransfer,TStreamMark& aMark);
	void PrepareAndWriteL(const TAny* aPtr,TInt aLength,TStreamMark& aMark);
	TInt PrepareAndWriteL(const TDesC8& aDes,TInt aMaxLength,TRequestStatus& aStatus,TStreamMark& aMark);
	TStreamTransfer PrepareAndWriteL(MStreamOutput& anOutput,TStreamTransfer aTransfer,TStreamMark& aMark);
	TStreamPos MarkSeekL(TStreamMark& aMark,TStreamLocation aLocation,TInt anOffset);
//
	inline MStreamBuf& BufL() const;
	inline MStreamBuf& Buf() const;
private:
	MStreamBuf* iHost;
	TStreamMark* iRMrk;
	TStreamMark* iWMrk;
private:
	friend class TStreamMark;
	};
//
class RShareBuf : public MStreamBuf
	{
public:
	IMPORT_C RShareBuf();
	IMPORT_C void Open(TStreamExchange& aHost,TStreamPos aPos,TInt aMode=ERead|EWrite);
	inline void Open(TStreamExchange& aHost,TInt aMode=ERead|EWrite);
protected:
	IMPORT_C void DoRelease();
	IMPORT_C TInt DoReadL(TAny* aPtr,TInt aMaxLength);
	IMPORT_C TInt DoReadL(TDes8& aDes,TInt aMaxLength,TRequestStatus& aStatus);
	IMPORT_C TStreamTransfer DoReadL(MStreamInput& anInput,TStreamTransfer aTransfer);
	IMPORT_C void DoWriteL(const TAny* aPtr,TInt aLength);
	IMPORT_C TInt DoWriteL(const TDesC8& aDes,TInt aMaxLength,TRequestStatus& aStatus);
	IMPORT_C TStreamTransfer DoWriteL(MStreamOutput& anOutput,TStreamTransfer aTransfer);
	IMPORT_C TStreamPos DoSeekL(TMark aMark,TStreamLocation aLocation,TInt anOffset);
private:
	inline TStreamExchange& Host() const;
private:
	TStreamExchange* iHost;
	TStreamMark iRMark;
	TStreamMark iWMark;
	};
//
class RShareReadStream : public RReadStream
	{
public:
	RShareReadStream() {}
	IMPORT_C RShareReadStream(TStreamExchange& aHost,TStreamPos aPos=KStreamBeginning);
	IMPORT_C void Open(TStreamExchange& aHost,TStreamPos aPos=KStreamBeginning);
private:
	RShareBuf iSource;
	};
class RShareWriteStream : public RWriteStream
	{
public:
	RShareWriteStream() {}
	inline RShareWriteStream(const MExternalizer<TStreamRef>& anExter);
	IMPORT_C RShareWriteStream(TStreamExchange& aHost,TStreamPos aPos=KStreamBeginning);
	IMPORT_C void Open(TStreamExchange& aHost,TStreamPos aPos=KStreamBeginning);
private:
	RShareBuf iSink;
	};

#include <s32share.inl>
#endif
