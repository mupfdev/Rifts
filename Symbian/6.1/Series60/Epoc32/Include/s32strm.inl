// S32STRM.INL
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//

// Class RReadStream
inline RReadStream::RReadStream()
	: iSrc(NULL)
	{}
inline RReadStream::RReadStream(MStreamBuf* aSource)
	: iSrc(aSource)
	{}
inline MStreamBuf* RReadStream::Source()
	{return iSrc;}
inline void RReadStream::Close()
	{Release();}
inline void RReadStream::ReadL(RWriteStream& aStream)
	{aStream.WriteL(*this);}
inline void RReadStream::ReadL(RWriteStream& aStream,TInt aLength)
	{aStream.WriteL(*this,aLength);}
inline void RReadStream::Pop()
	{CleanupStack::Pop();}
inline void RReadStream::Attach(MStreamBuf* aSource)
	{iSrc=aSource;}
inline void RReadStream::Detach()
	{iSrc=NULL;}

// Class RWriteStream
inline RWriteStream::RWriteStream()
	: iSnk(NULL),iExterL(NULL)
	{}
inline RWriteStream::RWriteStream(const MExternalizer<TStreamRef>& anExter)
	: iSnk(NULL),iExterL(&anExter)
	{}
inline RWriteStream::RWriteStream(MStreamBuf* aSink)
	: iSnk(aSink),iExterL(NULL)
	{}
inline MStreamBuf* RWriteStream::Sink()
	{return iSnk;}
inline void RWriteStream::Pop()
	{CleanupStack::Pop();}
inline void RWriteStream::Attach(MStreamBuf* aSink)
	{iSnk=aSink;}
inline void RWriteStream::Detach()
	{iSnk=NULL;}

// Class TCardinality
inline TCardinality::TCardinality(TInt aCount)
	:iCount(aCount)
	{
#if defined (_DEBUG)
	__DbgChkRange(aCount);
#endif
	}
inline TCardinality::operator TInt() const
	{
#if defined (_DEBUG)
	__DbgChkRange(iCount);
#endif
	return iCount;
	}

// Template class TExternalizer
template <class T>
inline void TExternalizer<T>::operator()(const T& anObject,RWriteStream& aStream) const
	{aStream<<anObject;}
template <class T>
inline TExternalizeFunction TExternalizer<T>::Function()
	{return &ExternalizeAsL;}
template <class T>
void TExternalizer<T>::ExternalizeAsL(const TAny* aPtr,RWriteStream& aStream)
	{aStream<<*((const T*)aPtr);}
inline TExternalizer<TAny>::TExternalizer(TExternalizeFunction aFunction)
	: iFunc(aFunction)
	{}
inline void TExternalizer<TAny>::operator()(const TAny* aPtr,RWriteStream& aStream) const
	{(*iFunc)(aPtr,aStream);}
inline TExternalizeFunction TExternalizer<TAny>::Function() const
	{return iFunc;}

// Template class TInternalizer
template <class T>
inline void TInternalizer<T>::operator()(T& anObject,RReadStream& aStream) const
	{aStream>>anObject;}
template <class T>
inline TInternalizeFunction TInternalizer<T>::Function()
	{return &InternalizeAsL;}
template <class T>
void TInternalizer<T>::InternalizeAsL(TAny* aPtr,RReadStream& aStream)
	{aStream>>*((T*)aPtr);}
inline TInternalizer<TAny>::TInternalizer(TInternalizeFunction aFunction)
	: iFunc(aFunction)
	{}
inline void TInternalizer<TAny>::operator()(TAny* aPtr,RReadStream& aStream) const
	{(*iFunc)(aPtr,aStream);}
inline TInternalizeFunction TInternalizer<TAny>::Function() const
	{return iFunc;}

// Template class MExternalizer
template <class T>
inline void MExternalizer<T>::operator()(const T& anObject,RWriteStream& aStream) const
	{ExternalizeL(anObject,aStream);}

// Template class MInternalizer
template <class T>
inline void MInternalizer<T>::operator()(T& anObject,RReadStream& aStream) const
	{InternalizeL(anObject,aStream);}

// Class TStreamRef
inline TStreamRef::TStreamRef(const TAny* aPtr,TExternalizeFunction aFunction)
	: iPtr(aPtr),iFunc(aFunction)
	{}
inline const TAny* TStreamRef::Ptr() const
	{return iPtr;}
inline TExternalizeFunction TStreamRef::Function() const
	{return iFunc;}
inline void TStreamRef::ExternalizeL(RWriteStream& aStream) const
	{aStream.WriteRefL(*this);}

// Externalization and internalization functions
IMPORT_C void ExternalizeL(TInt64 anInt64,RWriteStream& aStream);
IMPORT_C void InternalizeL(TInt64& anInt64,RReadStream& aStream);

IMPORT_C void ExternalizeL(const TDesC8& aDes8,RWriteStream& aStream);
IMPORT_C void ExternalizeL(const TDesC16& aDes16,RWriteStream& aStream);
IMPORT_C void InternalizeL(TDes8& aDes8,RReadStream& aStream);
IMPORT_C void InternalizeL(TDes16& aDes16,RReadStream& aStream);

IMPORT_C void ExternalizeL(const TCheckedUid& aUid,RWriteStream& aStream);
IMPORT_C void InternalizeL(TCheckedUid& aUid,RReadStream& aStream);

IMPORT_C void ExternalizeL(TPoint aPoint,RWriteStream& aStream);
IMPORT_C void ExternalizeL(TSize aSize,RWriteStream& aStream);
IMPORT_C void ExternalizeL(const TRect& aRect,RWriteStream& aStream);
IMPORT_C void InternalizeL(TPoint& aPoint,RReadStream& aStream);
IMPORT_C void InternalizeL(TSize& aSize,RReadStream& aStream);
IMPORT_C void InternalizeL(TRect& aRect,RReadStream& aStream);

IMPORT_C void ExternalizeL(const CBufBase& aBuf,RWriteStream& aStream);
IMPORT_C void InternalizeL(CBufBase& aBuf,RReadStream& aStream);

IMPORT_C void ArrayExternalizeCountL(TInt aCount,RWriteStream& aStream);
IMPORT_C void DoExternalizeAllL(const CArrayFixBase& anArray,RWriteStream& aStream,TExternalizer<TAny> anExter);
IMPORT_C TInt ArrayInternalizeCountL(RReadStream& aStream);
IMPORT_C void DoInternalizeAllL(CArrayFixBase& anArray,RReadStream& aStream,TInternalizer<TAny> anInter);

template <class T>
inline void ExternalizeCountL(const CArrayFix<T>& anArray,RWriteStream& aStream)
	{ArrayExternalizeCountL(anArray.Count(),aStream);}
template <class T>
inline void ExternalizeAllL(const CArrayFix<T>& anArray,RWriteStream& aStream)
	{DoExternalizeAllL(anArray,aStream,TExternalizer<T>::Function());}
template <class T>
void InternalizeCountL(CArrayFix<T>& anArray,RReadStream& aStream)
	{
	TInt n=ArrayInternalizeCountL(aStream);
	anArray.ResizeL(n);
	}
template <class T>
inline void InternalizeAllL(CArrayFix<T>& anArray,RReadStream& aStream)
	{DoInternalizeAllL(anArray,aStream,TInternalizer<T>::Function());}

template <class T>
void ExternalizeL(const CArrayFix<T>& anArray,RWriteStream& aStream)
	{
	ExternalizeCountL(anArray,aStream);
	ExternalizeAllL(anArray,aStream);
	}
template <class T>
void InternalizeL(CArrayFix<T>& anArray,RReadStream& aStream)
	{
	InternalizeCountL(anArray,aStream);
	InternalizeAllL(anArray,aStream);
	}

#if defined(__GCC32__)
template <class T>
inline void ExternalizeL(const CArrayFixFlat<T>& anArray,RWriteStream& aStream)
	{ExternalizeL((const CArrayFix<T>&)anArray,aStream);}
template <class T>
inline void ExternalizeL(const CArrayFixSeg<T>& anArray,RWriteStream& aStream)
	{ExternalizeL((const CArrayFix<T>&)anArray,aStream);}
template <class T>
inline void InternalizeL(CArrayFixFlat<T>& anArray,RReadStream& aStream)
	{InternalizeL((CArrayFix<T>&)anArray,aStream);}
template <class T>
inline void InternalizeL(CArrayFixSeg<T>& anArray,RReadStream& aStream)
	{InternalizeL((CArrayFix<T>&)anArray,aStream);}
#endif

template <class T>
inline void ExternalizeL(const T* aPtr,RWriteStream& aStream)
	{aStream<<TStreamRef(aPtr,TExternalizer<T>::Function());}

template <class T>
inline void DoExternalizeL(const T& anObject,RWriteStream& aStream,Externalize::Member)
	{anObject.ExternalizeL(aStream);}
template <class T>
inline void DoInternalizeL(T& anObject,RReadStream& aStream,Internalize::Member)
	{anObject.InternalizeL(aStream);}

template <class T>
inline void DoExternalizeL(const T& anObject,RWriteStream& aStream,Externalize::Function)
	{ExternalizeL(anObject,aStream);}
template <class T>
inline void DoInternalizeL(T& anObject,RReadStream& aStream,Internalize::Function)
	{InternalizeL(anObject,aStream);}

// Externalization and internalization selectors
inline Externalize::Member Externalization(const TAny*)
	{return Externalize::Member();}
inline Internalize::Member Internalization(TAny*)
	{return Internalize::Member();}

inline Externalize::Function Externalization(const TDesC8*)
	{return Externalize::Function();}
inline Externalize::Function Externalization(const TDesC16*)
	{return Externalize::Function();}
inline Internalize::Function Internalization(TDes8*)
	{return Internalize::Function();}
inline Internalize::Function Internalization(TDes16*)
	{return Internalize::Function();}

inline Externalize::Function Externalization(const CBufBase*)
	{return Externalize::Function();}
inline Externalize::Function Externalization(const CArrayFixBase*)
	{return Externalize::Function();}
inline Internalize::Function Internalization(CBufBase*)
	{return Internalize::Function();}
inline Internalize::Function Internalization(CArrayFixBase*)
	{return Internalize::Function();}

template <class T>
inline Externalize::Function Externalization(T*const*)
	{return Externalize::Function();}

// Input and output operators
template <class T>
inline RWriteStream& operator<<(RWriteStream& aStream,const T& anObject)
	{DoExternalizeL(anObject,aStream,Externalization(&anObject));return aStream;}
template <class T>
inline RReadStream& operator>>(RReadStream& aStream,T& anObject)
	{DoInternalizeL(anObject,aStream,Internalization(&anObject));return aStream;}

inline RWriteStream& operator<<(RWriteStream& aStream,const TInt8& anInt8)
	{aStream.WriteInt8L(anInt8);return aStream;}
inline RWriteStream& operator<<(RWriteStream& aStream,const TInt16& anInt16)
	{aStream.WriteInt16L(anInt16);return aStream;}
inline RWriteStream& operator<<(RWriteStream& aStream,const TInt32& anInt32)
	{aStream.WriteInt32L(anInt32);return aStream;}
inline RWriteStream& operator<<(RWriteStream& aStream,const TUint8& aUint8)
	{aStream.WriteUint8L(aUint8);return aStream;}
inline RWriteStream& operator<<(RWriteStream& aStream,const TUint16& aUint16)
	{aStream.WriteUint16L(aUint16);return aStream;}
inline RWriteStream& operator<<(RWriteStream& aStream,const TUint32& aUint32)
	{aStream.WriteUint32L(aUint32);return aStream;}
inline RWriteStream& operator<<(RWriteStream& aStream,const TReal32& aReal32)
	{aStream.WriteReal32L(aReal32);return aStream;}
inline RWriteStream& operator<<(RWriteStream& aStream,const TReal64& aReal64)
	{aStream.WriteReal64L(aReal64);return aStream;}

inline RReadStream& operator>>(RReadStream& aStream,TInt8& anInt8)
	{anInt8=aStream.ReadInt8L();return aStream;}
inline RReadStream& operator>>(RReadStream& aStream,TInt16& anInt16)
	{anInt16=aStream.ReadInt16L();return aStream;}
inline RReadStream& operator>>(RReadStream& aStream,TInt32& anInt32)
	{anInt32=aStream.ReadInt32L();return aStream;}
inline RReadStream& operator>>(RReadStream& aStream,TUint8& aUint8)
	{aUint8=aStream.ReadUint8L();return aStream;}
inline RReadStream& operator>>(RReadStream& aStream,TUint16& aUint16)
	{aUint16=aStream.ReadUint16L();return aStream;}
inline RReadStream& operator>>(RReadStream& aStream,TUint32& aUint32)
	{aUint32=aStream.ReadUint32L();return aStream;}
inline RReadStream& operator>>(RReadStream& aStream,TReal32& aReal32)
	{aReal32=aStream.ReadReal32L();return aStream;}
inline RReadStream& operator>>(RReadStream& aStream,TReal64& aReal64)
	{aReal64=aStream.ReadReal64L();return aStream;}

inline RWriteStream& operator<<(RWriteStream& aStream,const TInt64& anInt64)
	{ExternalizeL(anInt64,aStream);return aStream;}
inline RReadStream& operator>>(RReadStream& aStream,TInt64& anInt64)
	{InternalizeL(anInt64,aStream);return aStream;}

inline RWriteStream& operator<<(RWriteStream& aStream,const TUid& aUid)
	{return aStream<<aUid.iUid;}
inline RWriteStream& operator<<(RWriteStream& aStream,const TCheckedUid& aUid)
	{ExternalizeL(aUid,aStream);return aStream;}
inline RReadStream& operator>>(RReadStream& aStream,TUid& aUid)
	{return aStream>>aUid.iUid;}
inline RReadStream& operator>>(RReadStream& aStream,TCheckedUid& aUid)
	{InternalizeL(aUid,aStream);return aStream;}

inline RWriteStream& operator<<(RWriteStream& aStream,const TPoint& aPoint)
	{ExternalizeL(aPoint,aStream);return aStream;}
inline RWriteStream& operator<<(RWriteStream& aStream,const TSize& aSize)
	{ExternalizeL(aSize,aStream);return aStream;}
inline RWriteStream& operator<<(RWriteStream& aStream,const TRect& aRect)
	{ExternalizeL(aRect,aStream);return aStream;}
inline RReadStream& operator>>(RReadStream& aStream,TPoint& aPoint)
	{InternalizeL(aPoint,aStream);return aStream;}
inline RReadStream& operator>>(RReadStream& aStream,TSize& aSize)
	{InternalizeL(aSize,aStream);return aStream;}
inline RReadStream& operator>>(RReadStream& aStream,TRect& aRect)
	{InternalizeL(aRect,aStream);return aStream;}

inline RWriteStream& operator<<(RWriteStream& aStream,const TStreamRef& aRef)
	{aRef.ExternalizeL(aStream);return aStream;}

