// S32STRM.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//
#if !defined(__S32STRM_H__)
#define __S32STRM_H__
#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

const TInt KMaxCardinality=0x1fffffff;
//
class MStreamBuf;
class RWriteStream;
class RReadStream
	{
public:
	inline RReadStream();
	inline RReadStream(MStreamBuf* aSource);
	inline MStreamBuf* Source();
	inline void Close();
	IMPORT_C void Release();
//
	IMPORT_C void PushL();
	inline void Pop();
//
	IMPORT_C void ReadL(TDes8& aDes);
	IMPORT_C void ReadL(TDes8& aDes,TInt aLength);
	IMPORT_C void ReadL(TDes8& aDes,TChar aDelim);
	IMPORT_C void ReadL(TUint8* aPtr,TInt aLength);
	IMPORT_C void ReadL(TInt aLength);
	inline void ReadL(RWriteStream& aStream);
	inline void ReadL(RWriteStream& aStream,TInt aLength);
//
	IMPORT_C void ReadL(TDes16& aDes);
	IMPORT_C void ReadL(TDes16& aDes,TInt aLength);
	IMPORT_C void ReadL(TDes16& aDes,TChar aDelim);
	IMPORT_C void ReadL(TUint16* aPtr,TInt aLength);
//
	IMPORT_C TInt8 ReadInt8L();
	IMPORT_C TInt16 ReadInt16L();
	IMPORT_C TInt32 ReadInt32L();
	IMPORT_C TUint8 ReadUint8L();
	IMPORT_C TUint16 ReadUint16L();
	IMPORT_C TUint32 ReadUint32L();
	IMPORT_C TReal32 ReadReal32L();
	IMPORT_C TReal64 ReadReal64L();
protected:
	inline void Attach(MStreamBuf* aSource);
	inline void Detach();
private:
	MStreamBuf* iSrc;
private:
	friend class RWriteStream;
	};
template <class T>
class MExternalizer;
class TStreamRef;
class RWriteStream
	{
public:
	inline RWriteStream();
	inline RWriteStream(const MExternalizer<TStreamRef>& anExter);
	inline RWriteStream(MStreamBuf* aSink);
	inline MStreamBuf* Sink();
	IMPORT_C void Close();
	IMPORT_C void Release();
	IMPORT_C void CommitL();
//
	IMPORT_C void PushL();
	inline void Pop();
//
	IMPORT_C void WriteL(const TDesC8& aDes);
	IMPORT_C void WriteL(const TDesC8& aDes,TInt aLength);
	IMPORT_C void WriteL(const TUint8* aPtr,TInt aLength);
	IMPORT_C void WriteL(RReadStream& aStream);
	IMPORT_C void WriteL(RReadStream& aStream,TInt aLength);
//
	IMPORT_C void WriteL(const TDesC16& aDes);
	IMPORT_C void WriteL(const TDesC16& aDes,TInt aLength);
	IMPORT_C void WriteL(const TUint16* aPtr,TInt aLength);
//
	IMPORT_C void WriteInt8L(TInt aValue);
	IMPORT_C void WriteInt16L(TInt aValue);
	IMPORT_C void WriteInt32L(TInt32 aValue);
	IMPORT_C void WriteUint8L(TUint aValue);
	IMPORT_C void WriteUint16L(TUint aValue);
	IMPORT_C void WriteUint32L(TUint32 aValue);
	IMPORT_C void WriteReal32L(TReal aValue);
	IMPORT_C void WriteReal64L(TReal64 aValue);
protected:
	inline void Attach(MStreamBuf* aSink);
	inline void Detach();
private:
	IMPORT_C void WriteRefL(TStreamRef aRef);
private:
	MStreamBuf* iSnk;
	const MExternalizer<TStreamRef>* iExterL;
private:
	friend class TStreamRef;
	};
//
template <class T>
inline RWriteStream& operator<<(RWriteStream& aStream,const T& anObject);
template <class T>
inline RReadStream& operator>>(RReadStream& aStream,T& anObject);
//
class TCardinality
	{
public:
	TCardinality() {}
	inline TCardinality(TInt aCount);
	inline operator TInt() const;
//
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	IMPORT_C void InternalizeL(RReadStream& aStream);
private:
	TInt iCount;
private:
	IMPORT_C static void __DbgChkRange(TInt aCount);
	};
//
typedef void (*TExternalizeFunction)(const TAny* aPtr,RWriteStream& aStream);
typedef void (*TInternalizeFunction)(TAny* aPtr,RReadStream& aStream);
//
template <class T>
class TExternalizer
	{
public:
	inline void operator()(const T& anObject,RWriteStream& aStream) const;
	inline static TExternalizeFunction Function();
private:
	static void ExternalizeAsL(const TAny* aPtr,RWriteStream& aStream);
	};
TEMPLATE_SPECIALIZATION class TExternalizer<TAny>
	{
public:
	TExternalizer() {}
	inline TExternalizer(TExternalizeFunction aFunction);
	inline void operator()(const TAny* aPtr,RWriteStream& aStream) const;
	inline TExternalizeFunction Function() const;
private:
	TExternalizeFunction iFunc;
	};
template <class T>
class TInternalizer
	{
public:
	inline void operator()(T& anObject,RReadStream& aStream) const;
	inline static TInternalizeFunction Function();
private:
	static void InternalizeAsL(TAny* aPtr,RReadStream& aStream);
	};
TEMPLATE_SPECIALIZATION class TInternalizer<TAny>
	{
public:
	TInternalizer() {}
	inline TInternalizer(TInternalizeFunction aFunction);
	inline void operator()(TAny* aPtr,RReadStream& aStream) const;
	inline TInternalizeFunction Function() const;
private:
	TInternalizeFunction iFunc;
	};
//
template <class T>
class MExternalizer
	{
public:
	inline void operator()(const T& anObject,RWriteStream& aStream) const;
private:
	virtual void ExternalizeL(const T& anObject,RWriteStream& aStream) const=0;
	};
template <class T>
class MInternalizer
	{
public:
	inline void operator()(T& anObject,RReadStream& aStream) const;
private:
	virtual void InternalizeL(T& anObject,RReadStream& aStream) const=0;
	};
//
class TStreamRef
	{
public:
	inline TStreamRef(const TAny* aPtr,TExternalizeFunction aFunction);
	inline const TAny* Ptr() const;
	inline TExternalizeFunction Function() const;
//
	inline void ExternalizeL(RWriteStream& aStream) const;
private:
	const TAny* iPtr;
	TExternalizeFunction iFunc;
	};
//
class Externalize
	{
public:
	class Member {};
	class Function {};
	};
class Internalize
	{
public:
	class Member {};
	class Function {};
	};

#include <s32strm.inl>
#endif
