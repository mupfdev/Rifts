// S32BUF.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//
#if !defined(__S32BUF_H__)
#define __S32BUF_H__
#if !defined(__E32STD_H__)
#include <e32std.h>
#endif

enum TStreamLocation {EStreamBeginning,EStreamMark,EStreamEnd};
//
class TStreamPos
	{
public:
	TStreamPos() {}
	inline TStreamPos(TInt anOffset);
//
	inline TBool operator==(TStreamPos aPos) const;
	inline TBool operator!=(TStreamPos aPos) const;
	inline TBool operator<(TStreamPos aPos) const;
	inline TBool operator<=(TStreamPos aPos) const;
	inline TBool operator>(TStreamPos aPos) const;
	inline TBool operator>=(TStreamPos aPos) const;
//
	inline TInt operator-(TStreamPos aPos) const;
	inline TStreamPos operator+(TInt anOffset) const;
	inline TStreamPos operator-(TInt anOffset) const;
//
	inline TStreamPos& operator+=(TInt anOffset);
	inline TStreamPos& operator-=(TInt anOffset);
//
	inline TInt Offset() const;
private:
	TInt iOff;
	};
inline TStreamPos operator+(TInt anOffset,TStreamPos aPos);
#if defined(__NO_CLASS_CONSTS__)
#define KStreamBeginning TStreamPos(0)
#else
const TStreamPos KStreamBeginning=TStreamPos(0);
#endif
//
class TStreamTransfer
	{
public:
	enum TUnlimited {EUnlimited};
public:
	TStreamTransfer() {}
	inline TStreamTransfer(TInt aMaxLength);
	inline TStreamTransfer(TUnlimited);
//
	inline TBool operator==(TInt aLength) const;
	inline TBool operator>(TInt aLength) const;
	inline TStreamTransfer operator-(TInt aLength) const;
	inline TInt operator[](TInt aMaxLength) const;
//
	inline TStreamTransfer& operator-=(TInt aLength);
//
	inline TInt Left() const;
private:
	TInt iVal;
private:
	IMPORT_C static void __DbgChkNonNegative(TInt aLength);
	};
inline TBool operator==(TInt aLength,TStreamTransfer aTransfer);
inline TBool operator<(TInt aLength,TStreamTransfer aTransfer);
#if defined(__NO_CLASS_CONSTS__)
#define KStreamUnlimited TStreamTransfer(TStreamTransfer::EUnlimited)
#else
const TStreamTransfer KStreamUnlimited=TStreamTransfer::EUnlimited;
#endif
//
class MStreamInput;
class MStreamOutput;
class MStreamBuf
	{
public:
	enum TRead {ERead=0x01};
	enum TWrite {EWrite=0x02};
	typedef TInt TMark;
public:
	IMPORT_C void Close();
	inline void Release();
	IMPORT_C TInt Synch();
	inline void SynchL();
//
	IMPORT_C void PushL();
//
	inline TInt ReadL(TAny* aPtr,TInt aMaxLength);
	IMPORT_C TInt Read(TDes8& aDes,TRequestStatus& aStatus);
	IMPORT_C TInt Read(TDes8& aDes,TInt aMaxLength,TRequestStatus& aStatus);
	IMPORT_C TInt ReadL(TDes8& aDes,TRequestStatus& aStatus);
	inline TInt ReadL(TDes8& aDes,TInt aMaxLength,TRequestStatus& aStatus);
	inline TStreamTransfer ReadL(MStreamInput& anInput,TStreamTransfer aTransfer);
	IMPORT_C TInt ReadL(MStreamInput& anInput,TInt aMaxLength);
	inline void ReadL(MStreamInput& anInput);
//
	inline void WriteL(const TAny* aPtr,TInt aLength);
	IMPORT_C TInt Write(const TDesC8& aDes,TRequestStatus& aStatus);
	IMPORT_C TInt Write(const TDesC8& aDes,TInt aMaxLength,TRequestStatus& aStatus);
	IMPORT_C TInt WriteL(const TDesC8& aDes,TRequestStatus& aStatus);
	inline TInt WriteL(const TDesC8& aDes,TInt aMaxLength,TRequestStatus& aStatus);
	inline TStreamTransfer WriteL(MStreamOutput& anOutput,TStreamTransfer aTransfer);
	IMPORT_C TInt WriteL(MStreamOutput& anOutput,TInt aMaxLength);
	inline void WriteL(MStreamOutput& anOutput);
//
	inline void SeekL(TMark aMark,TStreamPos aPos);
	inline TStreamPos SeekL(TMark aMark,TStreamLocation aLocation,TInt anOffset=0);
	inline TStreamPos SeekL(TRead,TStreamLocation aLocation,TInt anOffset=0);
	inline TStreamPos SeekL(TWrite,TStreamLocation aLocation,TInt anOffset=0);
	inline TStreamPos SeekL(TRead,TInt anOffset);
	inline TStreamPos SeekL(TWrite,TInt anOffset);
//
	inline TStreamPos TellL(TRead) const;
	inline TStreamPos TellL(TWrite) const;
	inline TInt SizeL() const;
protected:
	MStreamBuf() {}
private:
	MStreamBuf(const MStreamBuf&);
	MStreamBuf& operator=(const MStreamBuf&);
//
	virtual IMPORT_C void DoRelease();
	virtual IMPORT_C void DoSynchL();
	virtual IMPORT_C TInt DoReadL(TAny* aPtr,TInt aMaxLength);
	virtual IMPORT_C TInt DoReadL(TDes8& aDes,TInt aMaxLength,TRequestStatus& aStatus);
	virtual IMPORT_C TStreamTransfer DoReadL(MStreamInput& anInput,TStreamTransfer aTransfer);
	virtual IMPORT_C void DoWriteL(const TAny* aPtr,TInt aLength);
	virtual IMPORT_C TInt DoWriteL(const TDesC8& aDes,TInt aMaxLength,TRequestStatus& aStatus);
	virtual IMPORT_C TStreamTransfer DoWriteL(MStreamOutput& anOutput,TStreamTransfer aTransfer);
	virtual IMPORT_C TStreamPos DoSeekL(TMark aMark,TStreamLocation aLocation,TInt anOffset);
	};
//
class MStreamInput
	{
public:
	virtual TInt PushL(const TAny* aPtr,TInt aMaxLength)=0;
	virtual	TStreamTransfer ReadFromL(MStreamBuf& aSource,TStreamTransfer aTransfer)=0;
	};
class MStreamOutput
	{
public:
	virtual TInt PullL(TAny* aPtr,TInt aMaxLength)=0;
	virtual TStreamTransfer WriteToL(MStreamBuf& aSink,TStreamTransfer aTransfer)=0;
	};
//
class TStreamBuf : public MStreamBuf
	{
protected:
	typedef TInt TArea;
protected:
	IMPORT_C TStreamBuf();
//
	IMPORT_C void SetBuf(TArea anArea,TUint8* aPtr,TUint8* anEnd);
	IMPORT_C void SetPtr(TArea anArea,TUint8* aPtr);
	IMPORT_C void SetEnd(TArea anArea,TUint8* anEnd);
	IMPORT_C TUint8* Ptr(TArea anArea) const;
	IMPORT_C TUint8* End(TArea anArea) const;
	IMPORT_C TInt Avail(TArea anArea) const;
//
	IMPORT_C TInt DoReadL(TAny* aPtr,TInt aMaxLength);
	IMPORT_C TStreamTransfer DoReadL(MStreamInput& anInput,TStreamTransfer aTransfer);
	IMPORT_C void DoWriteL(const TAny* aPtr,TInt aLength);
	IMPORT_C TStreamTransfer DoWriteL(MStreamOutput& anOutput,TStreamTransfer aTransfer);
//
	inline void SetBuf(TRead,TUint8* aPtr,TUint8* anEnd);
	inline void SetBuf(TWrite,TUint8* aPtr,TUint8* anEnd);
	inline void SetPtr(TRead,TUint8* aPtr);
	inline void SetPtr(TWrite,TUint8* aPtr);
	inline void SetEnd(TRead,TUint8* anEnd);
	inline void SetEnd(TWrite,TUint8* anEnd);
	inline TUint8* Ptr(TRead) const;
	inline TUint8* Ptr(TWrite) const;
	inline TUint8* End(TRead) const;
	inline TUint8* End(TWrite) const;
	inline TInt Avail(TRead) const;
	inline TInt Avail(TWrite) const;
private:
	virtual TInt UnderflowL(TInt aMaxLength)=0;
	virtual void OverflowL()=0;
private:
	TUint8* iRPtr;
	TUint8* iREnd;
	TUint8* iWPtr;
	TUint8* iWEnd;
	};
//
class TStreamFilter : public MStreamBuf
	{
public:
	enum {EAttached=0x10};
protected:
	IMPORT_C TStreamFilter();
	inline void Set(MStreamBuf* aHost,TInt aMode);
	inline void Committed();
	inline TBool IsCommitted() const;
	IMPORT_C void EmitL(const TAny* aPtr,TInt aLength);
//
	IMPORT_C void DoRelease();
	IMPORT_C void DoSynchL();
	IMPORT_C TInt DoReadL(TAny* aPtr,TInt aMaxLength);
	IMPORT_C void DoWriteL(const TAny* aPtr,TInt aLength);
private:
	virtual TInt Capacity(TInt aMaxLength)=0;
	virtual TInt FilterL(TAny* aPtr,TInt aMaxLength,const TUint8*& aFrom,const TUint8* anEnd)=0;
private:
	MStreamBuf* iHost;
	TInt iMode;
private:
	friend class TFilterInput;
	friend class TFilterOutput;
private:
	IMPORT_C static void __DbgChkMode(TInt aMode);
	};

#include <s32buf.inl>
#endif
