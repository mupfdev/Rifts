// S32STD.INL
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//

// Class TStreamId
inline TStreamId::TStreamId(TUint32 aValue)
	: iVal(aValue)
	{
#if defined (_DEBUG)
	__DbgChkRange(aValue);
#endif
	}
inline TBool TStreamId::operator==(TStreamId anId) const
	{return iVal==anId.iVal;}
inline TBool TStreamId::operator!=(TStreamId anId) const
	{return iVal!=anId.iVal;}
inline void TStreamId::ExternalizeL(RWriteStream& aStream) const
	{
#if defined (_DEBUG)
	__DbgChkRange(iVal);
#endif
	aStream<<iVal;
	}
inline TUint32 TStreamId::Value() const
	{
#if defined (_DEBUG)
	__DbgChkRange(iVal);
#endif
	return iVal;
	}

// Class RStoreWriteStream
inline RStoreWriteStream::RStoreWriteStream(const MExternalizer<TStreamRef>& anExter)
	: RWriteStream(anExter)
	{}

// Class TSwizzleCBase
inline TSwizzleCBase::TSwizzleCBase(TStreamRef aRef)
	: iPtr(aRef.Ptr())
	{
#if defined (_DEBUG)
	__DbgChkRef(aRef);
#endif
    }
inline TBool TSwizzleCBase::operator==(const TSwizzleCBase& aSwizzle) const
	{return iPtr==aSwizzle.iPtr;}
inline TBool TSwizzleCBase::operator==(const TAny* aPtr) const
	{return iPtr==aPtr;}
inline TBool TSwizzleCBase::operator!=(const TSwizzleCBase& aSwizzle) const
	{return iPtr!=aSwizzle.iPtr;}
inline TBool TSwizzleCBase::operator!=(const TAny* aPtr) const
	{return iPtr!=aPtr;}
inline TBool TSwizzleCBase::IsPtr() const
	{return IsPtrRep(iPtr);}
inline TBool TSwizzleCBase::IsId() const
	{return IsIdRep(iPtr);}
inline TSwizzleCBase::TSwizzleCBase(const TAny* aPtr)
	: iPtr(aPtr)
	{
#if defined (_DEBUG)
	__DbgChkPtr(aPtr);
#endif
    }
inline const TAny* TSwizzleCBase::Ptr() const
	{
#if defined (_DEBUG)
	__DbgChkPtr(iPtr);
#endif
	return iPtr;
	}
inline TBool operator==(const TAny* aPtr,const TSwizzleCBase& aSwizzle)
	{return aSwizzle==aPtr;}
inline TBool operator!=(const TAny* aPtr,const TSwizzleCBase& aSwizzle)
	{return aSwizzle!=aPtr;}

// Class TSwizzleBase
inline TSwizzleBase::TSwizzleBase(TAny* aPtr)
	: TSwizzleCBase(aPtr)
	{}
inline TSwizzleBase::TSwizzleBase(TStreamId anId)
	: TSwizzleCBase(anId)
	{}
inline TAny* TSwizzleBase::Ptr() const
	{return (TAny*)TSwizzleCBase::Ptr();}

// Template class TSwizzle
template <class T>
inline TSwizzle<T>::TSwizzle(T* aPtr)
	: TSwizzleBase(aPtr)
	{}
template <class T>
inline TSwizzle<T>::TSwizzle(TStreamId anId)
	: TSwizzleBase(anId)
	{}
template <class T>
inline TSwizzle<T>& TSwizzle<T>::operator=(T* aPtr)
	{return *this=TSwizzle<T>(aPtr);}
template <class T>
inline T* TSwizzle<T>::AsPtr() const
	{return (T*)Ptr();}
template <class T>
inline TSwizzle<T>::operator T*() const
	{return AsPtr();}
template <class T>
inline T& TSwizzle<T>::operator*() const
	{return *AsPtr();}
template <class T>
inline T* TSwizzle<T>::operator->() const
	{return AsPtr();}
template <class T>
inline void TSwizzle<T>::ExternalizeL(RWriteStream& aStream) const
	{TSwizzleBase::DoExternalizeL(aStream,TExternalizer<T>::Function());}
inline TSwizzle<TAny>::TSwizzle(TAny* aPtr)
	: TSwizzleBase(aPtr)
	{}
inline TSwizzle<TAny>::TSwizzle(TStreamId anId)
	: TSwizzleBase(anId)
	{}
inline TSwizzle<TAny>::TSwizzle(const TSwizzleBase& aSwizzle)
	: TSwizzleBase(aSwizzle)
	{}
inline TSwizzle<TAny>& TSwizzle<TAny>::operator=(TAny* aPtr)
	{return *this=TSwizzle<TAny>(aPtr);}
inline TSwizzle<TAny>& TSwizzle<TAny>::operator=(const TSwizzleBase& aSwizzle)
	{return *this=TSwizzle<TAny>(aSwizzle);}
inline TAny* TSwizzle<TAny>::AsPtr() const
	{return Ptr();}
inline TSwizzle<TAny>::operator TAny*() const
	{return AsPtr();}

// Template class TSwizzleC
template <class T>
inline TSwizzleC<T>::TSwizzleC(const T* aPtr)
	: TSwizzleCBase(aPtr)
	{}
template <class T>
inline TSwizzleC<T>::TSwizzleC(TStreamId anId)
	: TSwizzleCBase(anId)
	{}
template <class T>
inline TSwizzleC<T>::TSwizzleC(TSwizzle<T> aSwizzle)
	: TSwizzleCBase(aSwizzle)
	{}
template <class T>
inline TSwizzleC<T>& TSwizzleC<T>::operator=(const T* aPtr)
	{return *this=TSwizzleC<T>(aPtr);}
template <class T>
inline const T* TSwizzleC<T>::AsPtr() const
	{return (const T*)Ptr();}
template <class T>
inline TSwizzleC<T>::operator const T*() const
	{return AsPtr();}
template <class T>
inline const T& TSwizzleC<T>::operator*() const
	{return *AsPtr();}
template <class T>
inline const T* TSwizzleC<T>::operator->() const
	{return AsPtr();}
template <class T>
inline void TSwizzleC<T>::ExternalizeL(RWriteStream& aStream) const
	{TSwizzleCBase::DoExternalizeL(aStream,TExternalizer<T>::Function());}
inline TSwizzleC<TAny>::TSwizzleC(const TAny* aPtr)
	: TSwizzleCBase(aPtr)
	{}
inline TSwizzleC<TAny>::TSwizzleC(TStreamId anId)
	: TSwizzleCBase(anId)
	{}
inline TSwizzleC<TAny>::TSwizzleC(const TSwizzleCBase& aSwizzle)
	: TSwizzleCBase(aSwizzle)
	{}
inline TSwizzleC<TAny>::TSwizzleC(TStreamRef aRef)
	: TSwizzleCBase(aRef)
 	{}
inline TSwizzleC<TAny>& TSwizzleC<TAny>::operator=(const TAny* aPtr)
	{return *this=TSwizzleC<TAny>(aPtr);}
inline TSwizzleC<TAny>& TSwizzleC<TAny>::operator=(const TSwizzleCBase& aSwizzle)
	{return *this=TSwizzleC<TAny>(aSwizzle);}
inline const TAny* TSwizzleC<TAny>::AsPtr() const
	{return Ptr();}
inline TSwizzleC<TAny>::operator const TAny*() const
	{return AsPtr();}

