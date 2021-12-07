// E32STD.INL
//
// Copyright (c) 1994-1999 Symbian Ltd.  All rights reserved.
//

// Global operator new
inline TAny* operator new(TUint /*aSize*/, TAny* aBase)
	{return(aBase);}
inline TAny* operator new(TUint aSize, TLeave)
	{return User::AllocL(aSize);}

#ifdef __GCC32__
inline TAny* operator new[](TUint aSize, TLeave)
	{return User::AllocL(aSize);}
#endif

// Class TInt64
inline TInt64::TInt64()
	{}
inline TInt64::TInt64(TUint aVal)
	: iLow(aVal),iHigh(0)
	{}
inline TInt64::TInt64(TUint aHigh,TUint aLow)
	: iLow(aLow),iHigh(aHigh)
	{}
inline void TInt64::Set(TUint aHigh,TUint aLow)
	{iLow=aLow;iHigh=aHigh;}
inline TUint TInt64::Low() const
	{return(iLow);}
inline TUint TInt64::High() const
	{return(iHigh);}
inline TInt64 &TInt64::operator=(TUint aVal)
	{iLow=aVal;iHigh=0;return(*this);}

// Class TRefByValue
template <class T>
inline TRefByValue<T>::TRefByValue(T &aRef)
	: iRef(aRef)
	{}
template <class T>
inline TRefByValue<T>::operator T &()
	{return(iRef);}

// Class TCallBack
inline TCallBack::TCallBack()
	{iFunction=NULL;}
inline TCallBack::TCallBack(TInt (*aFunction)(TAny *aPtr))
	: iFunction(aFunction),iPtr(NULL)
	{}
inline TCallBack::TCallBack(TInt (*aFunction)(TAny *aPtr),TAny *aPtr)
	: iFunction(aFunction),iPtr(aPtr)
	{}
inline TInt TCallBack::CallBack() const
	{ return (iFunction ? (*iFunction)(iPtr) : 0); }

// Class TSglQue
template <class T>
inline TSglQue<T>::TSglQue()
	{}
template <class T>
inline TSglQue<T>::TSglQue(TInt anOffset)
	: TSglQueBase(anOffset)
	{}
template <class T>
inline void TSglQue<T>::AddFirst(T &aRef)
	{DoAddFirst(&aRef);}
template <class T>
inline void TSglQue<T>::AddLast(T &aRef)
	{DoAddLast(&aRef);}
template <class T>
inline TBool TSglQue<T>::IsFirst(const T *aPtr) const
	{return(PtrAdd(aPtr,iOffset)==(T *)iHead);}
template <class T>
inline TBool TSglQue<T>::IsLast(const T *aPtr) const
	{return(PtrAdd(aPtr,iOffset)==(T *)iLast);}
template <class T>
inline T *TSglQue<T>::First() const
	{return(PtrSub((T *)iHead,iOffset));}
template <class T>
inline T *TSglQue<T>::Last() const
	{return(PtrSub((T *)iLast,iOffset));}
template <class T>
inline void TSglQue<T>::Remove(T &aRef)
	{DoRemove(&aRef);}

// Class TDblQue
template <class T>
inline TDblQue<T>::TDblQue()
	{}
template <class T>
inline TDblQue<T>::TDblQue(TInt anOffset)
	: TDblQueBase(anOffset)
	{}
template <class T>
inline void TDblQue<T>::AddFirst(T &aRef)
	{DoAddFirst(&aRef);}
template <class T>
inline void TDblQue<T>::AddLast(T &aRef)
	{DoAddLast(&aRef);}
template <class T>
inline TBool TDblQue<T>::IsHead(const T *aPtr) const
	{return(PtrAdd(aPtr,iOffset)==(T *)&iHead);}
template <class T>
inline TBool TDblQue<T>::IsFirst(const T *aPtr) const
	{return(PtrAdd(aPtr,iOffset)==(T *)iHead.iNext);}
template <class T>
inline TBool TDblQue<T>::IsLast(const T *aPtr) const
	{return(PtrAdd(aPtr,iOffset)==(T *)iHead.iPrev);}
template <class T>
inline T *TDblQue<T>::First() const
	{
#if defined (_DEBUG)
	__DbgTestEmpty();
#endif
    return(PtrSub((T *)iHead.iNext,iOffset));
    }
template <class T>
inline T *TDblQue<T>::Last() const
	{
#if defined (_DEBUG)
	__DbgTestEmpty();
#endif
	return(PtrSub((T *)iHead.iPrev,iOffset));
	}

// Class TPriQue
template <class T>
inline TPriQue<T>::TPriQue()
	{}
template <class T>
inline TPriQue<T>::TPriQue(TInt anOffset)
	: TDblQueBase(anOffset)
	{}
template <class T>
inline void TPriQue<T>::Add(T &aRef)
	{DoAddPriority(&aRef);}
template <class T>
inline TBool TPriQue<T>::IsHead(const T *aPtr) const
	{return(PtrAdd(aPtr,iOffset)==(T *)&iHead);}
template <class T>
inline TBool TPriQue<T>::IsFirst(const T *aPtr) const
	{return(PtrAdd(aPtr,iOffset)==(T *)iHead.iNext);}
template <class T>
inline TBool TPriQue<T>::IsLast(const T *aPtr) const
	{return(PtrAdd(aPtr,iOffset)==(T *)iHead.iPrev);}
template <class T>
inline T *TPriQue<T>::First() const
	{return(PtrSub((T *)iHead.iNext,iOffset));}
template <class T>
inline T *TPriQue<T>::Last() const
	{return(PtrSub((T *)iHead.iPrev,iOffset));}

// Class TDeltaQue
template <class T>
inline TDeltaQue<T>::TDeltaQue()
	{}
template <class T>
inline TDeltaQue<T>::TDeltaQue(TInt anOffset)
	: TDeltaQueBase(anOffset)
	{}
template <class T>
inline void TDeltaQue<T>::Add(T &aRef,TInt aDelta)
	{DoAddDelta(&aRef,aDelta);}
template <class T>
inline void TDeltaQue<T>::Remove(T &aRef)
	{DoRemove(&aRef);}
template <class T>
inline T *TDeltaQue<T>::RemoveFirst()
	{return((T *) DoRemoveFirst());}

// Class TSglQueIter
template <class T>
inline TSglQueIter<T>::TSglQueIter(TSglQueBase &aQue)
	: TSglQueIterBase(aQue)
	{}
template <class T>
inline void TSglQueIter<T>::Set(T &aLink)
	{DoSet(&aLink);}
template <class T>
inline TSglQueIter<T>::operator T *()
	{return((T *)DoCurrent());}
template <class T>
inline T *TSglQueIter<T>::operator++(TInt)
	{return((T *)DoPostInc());}

// Class TDblQueIter
template <class T>
inline TDblQueIter<T>::TDblQueIter(TDblQueBase &aQue)
	: TDblQueIterBase(aQue)
	{}
template <class T>
inline void TDblQueIter<T>::Set(T &aLink)
	{DoSet(&aLink);}
template <class T>
inline TDblQueIter<T>::operator T *()
	{return((T *) DoCurrent());}
template <class T>
inline T *TDblQueIter<T>::operator++(TInt)
	{return((T *) DoPostInc());}
template <class T>
inline T *TDblQueIter<T>::operator--(TInt)
	{return((T *) DoPostDec());}

// Class TKey
inline void TKey::SetPtr(const TAny *aPtr)
	{iPtr=aPtr;}

// Class THeapWalk
inline TInt THeapWalk::Value() const
	{return(iValue);}
inline void THeapWalk::SetValue(TInt aValue)
	{iValue=aValue;}

// Class TChar
inline TChar::TChar()
	{}
inline TChar::TChar(TUint aChar)
	: iChar(aChar)
	{}
inline void TChar::SetChar(TUint aChar)
	{iChar=aChar;}
inline TChar& TChar::operator-=(TUint aChar)
	{iChar-=aChar;return(*this);}
inline TChar& TChar::operator+=(TUint aChar)
	{iChar+=aChar;return(*this);}
inline TChar TChar::operator-(TUint aChar)
	{return(iChar-aChar);}
inline TChar TChar::operator+(TUint aChar)
	{return(iChar+aChar);}
inline TChar::operator TUint() const
	{return(iChar);}
inline void TChar::Fold()
	{iChar=User::Fold(iChar);}
inline void TChar::LowerCase()
	{iChar=User::LowerCase(iChar);}
inline void TChar::UpperCase()
	{iChar=User::UpperCase(iChar);}
#ifdef _UNICODE
inline void TChar::Fold(TInt aFlags)
	{iChar=User::Fold(iChar,aFlags);}
inline void TChar::TitleCase()
	{iChar=User::TitleCase(iChar);}
#endif
inline TBool TChar::Eos() const
	{return(iChar==0);}

// Class TCharF
inline TCharF::TCharF(TUint aChar)
	: TChar(User::Fold(aChar))
	{}
inline TCharF::TCharF(const TChar& aChar)
	: TChar(User::Fold(aChar))
	{}
inline TCharF& TCharF::operator=(TUint aChar)
	{SetChar(User::Fold(aChar));return(*this);}
inline TCharF& TCharF::operator=(const TChar& aChar)
	{SetChar(User::Fold(aChar));return(*this);}

// Class TCharLC
inline TCharLC::TCharLC(TUint aChar)
	: TChar(User::LowerCase(aChar))
	{}
inline TCharLC::TCharLC(const TChar& aChar)
	: TChar(User::LowerCase(aChar))
	{}
inline TCharLC& TCharLC::operator=(TUint aChar)
	{SetChar(User::LowerCase(aChar));return(*this);}
inline TCharLC& TCharLC::operator=(const TChar& aChar)
	{SetChar(User::LowerCase(aChar));return(*this);}

// Class TCharUC
inline TCharUC::TCharUC(TUint aChar)
	: TChar(User::UpperCase(aChar))
	{}
inline TCharUC::TCharUC(const TChar& aChar)
	: TChar(User::UpperCase(aChar))
	{}
inline TCharUC& TCharUC::operator=(TUint aChar)
	{SetChar(User::UpperCase(aChar));return(*this);}
inline TCharUC& TCharUC::operator=(const TChar& aChar)
	{SetChar(User::UpperCase(aChar));return(*this);}

// Class TDesC8
inline TInt TDesC8::operator<(const TDesC8 &aDes) const
	{return(Compare(aDes)<0);}
inline TInt TDesC8::operator<=(const TDesC8 &aDes) const
	{return(Compare(aDes)<=0);}
inline TInt TDesC8::operator>(const TDesC8 &aDes) const
	{return(Compare(aDes)>0);}
inline TInt TDesC8::operator>=(const TDesC8 &aDes) const
	{return(Compare(aDes)>=0);}
inline TInt TDesC8::operator==(const TDesC8 &aDes) const
	{return(Compare(aDes)==0);}
inline TInt TDesC8::operator!=(const TDesC8 &aDes) const
	{return(Compare(aDes)!=0);}
inline const TUint8 &TDesC8::operator[](TInt anIndex) const
	{return(AtC(anIndex));}
inline TInt TDesC8::Length() const
	{
#if defined(__DESC_NO_BIT_FIELDS__)
	return(iLength&KMaskDesLength8);
#else
	return(iLength);
#endif
	}
inline TInt TDesC8::Size() const
	{return(Length());}
inline void TDesC8::DoSetLength(TInt aLength)
	{
#if defined(__DESC_NO_BIT_FIELDS__)
	iLength=(iLength&(~KMaskDesLength8))|aLength;
#else
	iLength=aLength;
#endif
	}

// Class TPtrC8
inline void TPtrC8::Set(const TUint8 *aBuf,TInt aLength)
	{new(this) TPtrC8(aBuf,aLength);}
inline void TPtrC8::Set(const TDesC8 &aDes)
	{new(this) TPtrC8(aDes);}
inline void TPtrC8::Set(const TPtrC8& aPtr)
	{new(this) TPtrC8(aPtr);}

// class TBufCBase8
inline TPtr8 TBufCBase8::DoDes(TInt aMaxLength)
	{return TPtr8(*this,aMaxLength);}

// Template class TBufC8
template <TInt S>
inline TBufC8<S>::TBufC8()
	: TBufCBase8()
	{}
template <TInt S>
inline TBufC8<S>::TBufC8(const TUint8 *aString)
	: TBufCBase8(aString,S)
	{}
template <TInt S>
inline TBufC8<S>::TBufC8(const TDesC8 &aDes)
	: TBufCBase8(aDes,S)
	{}
template <TInt S>
inline TBufC8<S> &TBufC8<S>::operator=(const TUint8 *aString)
	{Copy(aString,S);return(*this);}
template <TInt S>
inline TBufC8<S> &TBufC8<S>::operator=(const TDesC8 &aDes)
	{Copy(aDes,S);return(*this);}
template <TInt S>
inline TPtr8 TBufC8<S>::Des()
	{return DoDes(S);}

// Class HBufC8
inline HBufC8 &HBufC8::operator=(const HBufC8 &aLcb)
	{return *this=static_cast<const TDesC8&>(aLcb);}

// Class TDes8
inline TDes8 &TDes8::operator=(const TUint8 *aString)
    {Copy(aString);return(*this);}
inline TDes8 &TDes8::operator=(const TDesC8 &aDes)
    {Copy(aDes);return(*this);}
inline TDes8 &TDes8::operator=(const TDes8 &aDes)
    {Copy(aDes);return(*this);}
inline TDes8 &TDes8::operator+=(const TDesC8 &aDes)
	{Append(aDes);return(*this);}
inline const TUint8 &TDes8::operator[](TInt anIndex) const
	{return(AtC(anIndex));}
inline TUint8 &TDes8::operator[](TInt anIndex)
	{return((TUint8 &)AtC(anIndex));}
inline TInt TDes8::MaxLength() const
	{return(iMaxLength);}
inline TInt TDes8::MaxSize() const
	{return(iMaxLength);}
inline TUint8 * TDes8::WPtr() const
	{return((TUint8 *)Ptr());}

// Class TPtr8
inline TPtr8 &TPtr8::operator=(const TUint8 *aString)
	{Copy(aString);return(*this);}
inline TPtr8 &TPtr8::operator=(const TDesC8 &aDes)
	{Copy(aDes);return(*this);}
inline TPtr8 &TPtr8::operator=(const TPtr8 &aDes)
	{Copy(aDes);return(*this);}
inline void TPtr8::Set(TUint8 *aBuf,TInt aLength,TInt aMaxLength)
	{new(this) TPtr8(aBuf,aLength,aMaxLength);}
inline void TPtr8::Set(const TPtr8 &aPtr)
	{new(this) TPtr8(aPtr);}

// Template class TBuf8
template <TInt S>
inline TBuf8<S>::TBuf8()
	: TBufBase8(S)
	{}
template <TInt S>
inline TBuf8<S>::TBuf8(TInt aLength)
	: TBufBase8(aLength,S)
	{}
template <TInt S>
inline TBuf8<S>::TBuf8(const TUint8 *aString)
	: TBufBase8(aString,S)
	{}
template <TInt S>
inline TBuf8<S>::TBuf8(const TDesC8 &aDes)
	: TBufBase8(aDes,S)
	{}
template <TInt S>
inline TBuf8<S> &TBuf8<S>::operator=(const TUint8 *aString)
	{Copy(aString);return(*this);}
template <TInt S>
inline TBuf8<S> &TBuf8<S>::operator=(const TDesC8 &aDes)
	{Copy(aDes);return(*this);}
template <TInt S>
inline TBuf8<S>& TBuf8<S>::operator=(const TBuf8<S>& aBuf)
	{Copy(aBuf);return *this;}

// Template class TLitC8
template <TInt S>
inline const TDesC8* TLitC8<S>::operator&() const
	{return REINTERPRET_CAST(const TDesC8*,this);}
template <TInt S>
inline const TDesC8& TLitC8<S>::operator()() const
	{return *operator&();}
template <TInt S>
inline TLitC8<S>::operator const TDesC8&() const
	{return *operator&();}
template <TInt S>
inline TLitC8<S>::operator const __TRefDesC8() const
	{return *operator&();}

// Class TDesC16
inline TInt TDesC16::operator<(const TDesC16 &aDes) const
	{return(Compare(aDes)<0);}
inline TInt TDesC16::operator<=(const TDesC16 &aDes) const
	{return(Compare(aDes)<=0);}
inline TInt TDesC16::operator>(const TDesC16 &aDes) const
	{return(Compare(aDes)>0);}
inline TInt TDesC16::operator>=(const TDesC16 &aDes) const
	{return(Compare(aDes)>=0);}
inline TInt TDesC16::operator==(const TDesC16 &aDes) const
	{return(Compare(aDes)==0);}
inline TInt TDesC16::operator!=(const TDesC16 &aDes) const
	{return(Compare(aDes)!=0);}
inline const TUint16 &TDesC16::operator[](TInt anIndex) const
	{return(AtC(anIndex));}
inline TInt TDesC16::Length() const
	{
#if defined(__DESC_NO_BIT_FIELDS__)
	return(iLength&KMaskDesLength16);
#else
	return(iLength);
#endif
	}
inline TInt TDesC16::Size() const
	{return(Length()<<1);}
inline void TDesC16::DoSetLength(TInt aLength)
	{
#if defined(__DESC_NO_BIT_FIELDS__)
	iLength=(iLength&(~KMaskDesLength16))|aLength;
#else
	iLength=aLength;
#endif
	}

// Class TPtrC16
inline void TPtrC16::Set(const TUint16 *aBuf,TInt aLength)
	{new(this) TPtrC16(aBuf,aLength);}
inline void TPtrC16::Set(const TDesC16 &aDes)
	{new(this) TPtrC16(aDes);}
inline void TPtrC16::Set(const TPtrC16& aPtr)
	{new(this) TPtrC16(aPtr);}

// class TBufCBase16
inline TPtr16 TBufCBase16::DoDes(TInt aMaxLength)
	{return TPtr16(*this,aMaxLength);}

// Template class TBufC16
template <TInt S>
inline TBufC16<S>::TBufC16()
	: TBufCBase16()
	{}
template <TInt S>
inline TBufC16<S>::TBufC16(const TUint16 *aString)
	: TBufCBase16(aString,S)
	{}
template <TInt S>
inline TBufC16<S>::TBufC16(const TDesC16 &aDes)
	: TBufCBase16(aDes,S)
	{}
template <TInt S>
inline TBufC16<S> &TBufC16<S>::operator=(const TUint16 *aString)
	{Copy(aString,S);return(*this);}
template <TInt S>
inline TBufC16<S> &TBufC16<S>::operator=(const TDesC16 &aDes)
	{Copy(aDes,S);return(*this);}
template <TInt S>
inline TPtr16 TBufC16<S>::Des()
	{return(DoDes(S));}

// Class HBufC16
inline HBufC16 &HBufC16::operator=(const HBufC16 &aLcb)
	{return *this=static_cast<const TDesC16&>(aLcb);}

// Class TDes16
inline TDes16 &TDes16::operator=(const TUint16 *aString)
    {Copy(aString);return(*this);}
inline TDes16 &TDes16::operator=(const TDesC16 &aDes)
    {Copy(aDes);return(*this);}
inline TDes16 &TDes16::operator=(const TDes16 &aDes)
    {Copy(aDes);return(*this);}
inline TDes16 &TDes16::operator+=(const TDesC16 &aDes)
	{Append(aDes);return(*this);}
inline const TUint16 &TDes16::operator[](TInt anIndex) const
	{return(AtC(anIndex));}
inline TUint16 &TDes16::operator[](TInt anIndex)
	{return((TUint16 &)AtC(anIndex));}
inline TInt TDes16::MaxLength() const
	{return(iMaxLength);}
inline TInt TDes16::MaxSize() const
	{return(iMaxLength<<1);}
inline TUint16 * TDes16::WPtr() const
	{return((TUint16 *)Ptr());}

// Class TPtr16
inline TPtr16 &TPtr16::operator=(const TUint16 *aString)
	{Copy(aString);return(*this);}
inline TPtr16 &TPtr16::operator=(const TDesC16 &aDes)
	{Copy(aDes);return(*this);}
inline TPtr16 &TPtr16::operator=(const TPtr16 &aDes)
	{Copy(aDes);return(*this);}
inline void TPtr16::Set(TUint16 *aBuf,TInt aLength,TInt aMaxLength)
	{new(this) TPtr16(aBuf,aLength,aMaxLength);}
inline void TPtr16::Set(const TPtr16 &aPtr)
	{new(this) TPtr16(aPtr);}

// Template class TBuf16
template <TInt S>
inline TBuf16<S>::TBuf16()
	: TBufBase16(S)
	{}
template <TInt S>
inline TBuf16<S>::TBuf16(TInt aLength)
	: TBufBase16(aLength,S)
	{}
template <TInt S>
inline TBuf16<S>::TBuf16(const TUint16 *aString)
	: TBufBase16(aString,S)
	{}
template <TInt S>
inline TBuf16<S>::TBuf16(const TDesC16 &aDes)
	: TBufBase16(aDes,S)
	{}
template <TInt S>
inline TBuf16<S> &TBuf16<S>::operator=(const TUint16 *aString)
	{Copy(aString);return(*this);}
template <TInt S>
inline TBuf16<S> &TBuf16<S>::operator=(const TDesC16 &aDes)
	{Copy(aDes);return(*this);}
template <TInt S>
inline TBuf16<S>& TBuf16<S>::operator=(const TBuf16<S>& aBuf)
	{Copy(aBuf);return *this;}

// Template class TLitC16
template <TInt S>
inline const TDesC16* TLitC16<S>::operator&() const
	{return REINTERPRET_CAST(const TDesC16*,this);}
template <TInt S>
inline const TDesC16& TLitC16<S>::operator()() const
	{return *operator&();}
template <TInt S>
inline TLitC16<S>::operator const TDesC16&() const
	{return *operator&();}
template <TInt S>
inline TLitC16<S>::operator const __TRefDesC16() const
	{return *operator&();}

// Template class TBufC
#ifdef _UNICODE
template <TInt S>
inline TBufC<S>::TBufC()
	: TBufCBase16()
	{}
template <TInt S>
inline TBufC<S>::TBufC(const TText *aString)
	: TBufCBase16(aString,S)
	{}
template <TInt S>
inline TBufC<S>::TBufC(const TDesC &aDes)
	: TBufCBase16(aDes,S)
	{}
#endif
template <TInt S>
inline TBufC<S> &TBufC<S>::operator=(const TText *aString)
	{Copy(aString,S);return(*this);}
template <TInt S>
inline TBufC<S> &TBufC<S>::operator=(const TDesC &aDes)
	{Copy(aDes,S);return(*this);}
template <TInt S>
inline TPtr TBufC<S>::Des()
	{return(DoDes(S));}

// Template class TBuf
#ifdef _UNICODE
template <TInt S>
inline TBuf<S>::TBuf()
	: TBufBase16(S)
	{}
template <TInt S>
inline TBuf<S>::TBuf(TInt aLength)
	: TBufBase16(aLength,S)
	{}
template <TInt S>
inline TBuf<S>::TBuf(const TText *aString)
	: TBufBase16(aString,S)
	{}
template <TInt S>
inline TBuf<S>::TBuf(const TDesC &aDes)
	: TBufBase16(aDes,S)
	{}
#endif
template <TInt S>
inline TBuf<S> &TBuf<S>::operator=(const TText *aString)
	{Copy(aString);return(*this);}
template <TInt S>
inline TBuf<S> &TBuf<S>::operator=(const TDesC &aDes)
	{Copy(aDes);return(*this);}
template <TInt S>
inline TBuf<S> &TBuf<S>::operator=(const TBuf<S> &aBuf)
	{Copy(aBuf);return(*this);}

// Template class TLitC
template <TInt S>
inline const TDesC* TLitC<S>::operator&() const
	{return REINTERPRET_CAST(const TDesC*,this);}
template <TInt S>
inline const TDesC& TLitC<S>::operator()() const
	{return *operator&();}
template <TInt S>
inline TLitC<S>::operator const TDesC&() const
	{return *operator&();}
template <TInt S>
inline TLitC<S>::operator const __TRefDesC() const
	{return *operator&();}

// Template class TPckgC
template <class T>
inline TPckgC<T>::TPckgC(const T &aRef)
	: TPtrC8((const TUint8 *)&aRef,sizeof(T))
	{}
template <class T>
inline const T &TPckgC<T>::operator()() const
	{return(*((const T *)iPtr));}

// Template class TPckg
template <class T>
inline TPckg<T>::TPckg(const T &aRef)
	: TPtr8((TUint8 *)&aRef,sizeof(T),sizeof(T))
	{}
template <class T>
inline T &TPckg<T>::operator()()
	{return(*((T *)iPtr));}

// Template class TPckgBuf
template <class T>
inline TPckgBuf<T>::TPckgBuf()
	: TBuf8<sizeof(T)>(sizeof(T))
	{new(&iBuf[0]) T;}
template <class T>
inline TPckgBuf<T>::TPckgBuf(const T &aRef)
	: TBuf8<sizeof(T)>(sizeof(T))
	{new(&iBuf[0]) T(aRef);}
template <class T>
inline TPckgBuf<T> &TPckgBuf<T>::operator=(const TPckgBuf<T> &aRef)
	{Copy(aRef);return(*this);}
template <class T>
inline T &TPckgBuf<T>::operator=(const T &aRef)
	{Copy((TUint8 *)&aRef,sizeof(T));return(*((T *)&iBuf[0]));}
template <class T>
inline T &TPckgBuf<T>::operator()()
	{return(*((T *)&iBuf[0]));}

// Class TDateTime
inline TDateTime::TDateTime()
	{}           
inline TInt TDateTime::Year() const
	{return(iYear);}
inline TMonth TDateTime::Month() const
	{return(iMonth);}
inline TInt TDateTime::Day() const
	{return(iDay);}
inline TInt TDateTime::Hour() const
	{return(iHour);}
inline TInt TDateTime::Minute() const
	{return(iMinute);}
inline TInt TDateTime::Second() const
	{return(iSecond);}
inline TInt TDateTime::MicroSecond() const
	{return(iMicroSecond);}

// Class TTimeIntervalMicroSeconds
inline TTimeIntervalMicroSeconds::TTimeIntervalMicroSeconds()
	{}
inline TTimeIntervalMicroSeconds::TTimeIntervalMicroSeconds(const TInt64& aInterval)
	: iInterval(aInterval)
	{}
inline TTimeIntervalMicroSeconds& TTimeIntervalMicroSeconds::operator=(const TInt64& aInterval)
	{iInterval=aInterval;return(*this);}
inline TBool TTimeIntervalMicroSeconds::operator==(const TTimeIntervalMicroSeconds& aInterval) const
	{return(iInterval==aInterval.iInterval);}
inline TBool TTimeIntervalMicroSeconds::operator!=(const TTimeIntervalMicroSeconds& aInterval) const
	{return(iInterval!=aInterval.iInterval);}
inline TBool TTimeIntervalMicroSeconds::operator>=(const TTimeIntervalMicroSeconds& aInterval) const
	{return(iInterval>=aInterval.iInterval);}
inline TBool TTimeIntervalMicroSeconds::operator<=(const TTimeIntervalMicroSeconds& aInterval) const
	{return(iInterval<=aInterval.iInterval);}
inline TBool TTimeIntervalMicroSeconds::operator>(const TTimeIntervalMicroSeconds& aInterval) const
	{return(iInterval>aInterval.iInterval);}
inline TBool TTimeIntervalMicroSeconds::operator<(const TTimeIntervalMicroSeconds& aInterval) const
	{return(iInterval<aInterval.iInterval);}
inline const TInt64& TTimeIntervalMicroSeconds::Int64() const
	{return(iInterval);}

// Class TTimeIntervalBase
inline TTimeIntervalBase::TTimeIntervalBase()
	{}
inline TTimeIntervalBase::TTimeIntervalBase(TInt aInterval)
	: iInterval(aInterval)
	{}
inline TInt TTimeIntervalBase::operator==(TTimeIntervalBase aInterval) const
	{return(iInterval==aInterval.iInterval);}
inline TInt TTimeIntervalBase::operator!=(TTimeIntervalBase aInterval) const
	{return(iInterval!=aInterval.iInterval);}
inline TInt TTimeIntervalBase::operator>=(TTimeIntervalBase aInterval) const
	{return(iInterval>=aInterval.iInterval);}
inline TInt TTimeIntervalBase::operator<=(TTimeIntervalBase aInterval) const
	{return(iInterval<=aInterval.iInterval);}
inline TInt TTimeIntervalBase::operator>(TTimeIntervalBase aInterval) const
	{return(iInterval>aInterval.iInterval);}
inline TInt TTimeIntervalBase::operator<(TTimeIntervalBase aInterval) const
	{return(iInterval<aInterval.iInterval);}
inline TInt TTimeIntervalBase::Int() const
	{return(iInterval);}

// Class TTimeIntervalMicroSeconds32
inline TTimeIntervalMicroSeconds32::TTimeIntervalMicroSeconds32()
	{}
inline TTimeIntervalMicroSeconds32::TTimeIntervalMicroSeconds32(TInt aInterval)
    : TTimeIntervalBase(aInterval)
	{}
inline TTimeIntervalMicroSeconds32& TTimeIntervalMicroSeconds32::operator=(TInt aInterval)
	{iInterval=aInterval;return(*this);}

// Class TTimeIntervalSeconds
inline TTimeIntervalSeconds::TTimeIntervalSeconds()
	{}
inline TTimeIntervalSeconds::TTimeIntervalSeconds(TInt aInterval)
	: TTimeIntervalBase(aInterval)
	{}
inline TTimeIntervalSeconds& TTimeIntervalSeconds::operator=(TInt aInterval)
	{iInterval=aInterval;return(*this);}

// Class TTimeIntervalMinutes
inline TTimeIntervalMinutes::TTimeIntervalMinutes()
	{}
inline TTimeIntervalMinutes::TTimeIntervalMinutes(TInt aInterval)
	: TTimeIntervalBase(aInterval)
	{}
inline TTimeIntervalMinutes& TTimeIntervalMinutes::operator=(TInt aInterval)
	{iInterval=aInterval;return(*this);}

// Class TTimeIntervalHours
inline TTimeIntervalHours::TTimeIntervalHours()
	{}
inline TTimeIntervalHours::TTimeIntervalHours(TInt aInterval)
	: TTimeIntervalBase(aInterval)
	{}
inline TTimeIntervalHours& TTimeIntervalHours::operator=(TInt aInterval)
	{iInterval=aInterval;return(*this);}

// Class TTimeIntervalDays
inline TTimeIntervalDays::TTimeIntervalDays()
	{}
inline TTimeIntervalDays::TTimeIntervalDays(TInt aInterval)
	: TTimeIntervalBase(aInterval)
	{}
inline TTimeIntervalDays& TTimeIntervalDays::operator=(TInt aInterval)
	{iInterval=aInterval;return(*this);}

// Class TTimeIntervalMonths
inline TTimeIntervalMonths::TTimeIntervalMonths()
	{}
inline TTimeIntervalMonths::TTimeIntervalMonths(TInt aInterval)
	: TTimeIntervalBase(aInterval)
	{}
inline TTimeIntervalMonths& TTimeIntervalMonths::operator=(TInt aInterval)
	{iInterval=aInterval;return(*this);}

// Class TTimeIntervalYears
inline TTimeIntervalYears::TTimeIntervalYears()
	{}
inline TTimeIntervalYears::TTimeIntervalYears(TInt aInterval)
	: TTimeIntervalBase(aInterval)
	{}
inline TTimeIntervalYears& TTimeIntervalYears::operator=(TInt aInterval)
	{iInterval=aInterval;return(*this);}

// Class TTime
inline TTime::TTime()
	{}
inline TTime::TTime(const TInt64& aTime)
	: iTime(aTime)
	{}
inline TTime &TTime::operator=(const TInt64& aTime)
	{iTime=aTime;return(*this);}
inline TBool TTime::operator==(TTime aTime) const
	{return(iTime==aTime.iTime);}
inline TBool TTime::operator!=(TTime aTime) const
	{return(iTime!=aTime.iTime);}
inline TBool TTime::operator>=(TTime aTime) const
	{return(iTime>=aTime.iTime);}
inline TBool TTime::operator<=(TTime aTime) const
	{return(iTime<=aTime.iTime);}
inline TBool TTime::operator>(TTime aTime) const
	{return(iTime>aTime.iTime);}
inline TBool TTime::operator<(TTime aTime) const
	{return(iTime<aTime.iTime);}
inline const TInt64& TTime::Int64() const
	{return(iTime);}

// Class TLexMark8
inline TLexMark8::TLexMark8()
	: iPtr(NULL)
	{}
inline TLexMark8::TLexMark8(const TUint8 *aString) 
	: iPtr(aString)
	{}

// Class TLex8
inline TLex8::TLex8(const TUint8 *aString)
	{Assign(TPtrC8(aString));}
inline TLex8::TLex8(const TDesC8 &aDes)
	{Assign(aDes);}
inline TLex8& TLex8::operator=(const TUint8* aString)
	{Assign(TPtrC8(aString));return(*this);}
inline TLex8& TLex8::operator=(const TDesC8& aBuf)
	{Assign(aBuf);return(*this);}
inline TBool TLex8::Eos() const
	{return(iNext==iEnd);}
inline void TLex8::Mark()
	{Mark(iMark);}
inline void TLex8::Mark(TLexMark8& aMark) const
	{aMark.iPtr=iNext;}
inline void TLex8::UnGetToMark()
    {UnGetToMark(iMark);}
inline void TLex8::SkipAndMark(TInt aNumber)
    {SkipAndMark(aNumber,iMark);}
inline void TLex8::SkipSpaceAndMark()
    {SkipSpaceAndMark(iMark);}
inline TInt TLex8::TokenLength() const
	{return(iNext-iMark.iPtr);}
inline TInt TLex8::MarkedOffset() const
    {return(iMark.iPtr-iBuf);}
inline TInt TLex8::Val(TInt &aVal)
	{return(Val((TInt32&)aVal));}
inline TInt TLex8::Val(TUint &aVal,TRadix aRadix)
	{return(Val((TUint32&)aVal,aRadix));}
inline void TLex8::Assign(const TLex8& aLex)
	{new(this) TLex8(aLex);}

// Class TLexMark16
inline TLexMark16::TLexMark16()
	: iPtr(NULL)
	{}
inline TLexMark16::TLexMark16(const TUint16 *aString) 
	: iPtr(aString)
	{}

// Class TLex16
inline TLex16::TLex16(const TUint16 *aString)
	{Assign(TPtrC16(aString));}
inline TLex16::TLex16(const TDesC16 &aDes)
	{Assign(aDes);}
inline TLex16& TLex16::operator=(const TUint16* aString)
	{Assign(TPtrC16(aString));return(*this);}
inline TLex16& TLex16::operator=(const TDesC16& aBuf)
	{Assign(aBuf);return(*this);}
inline TBool TLex16::Eos() const
	{return(iNext==iEnd);}
inline void TLex16::Mark(TLexMark16& aMark) const
	{aMark.iPtr=iNext;}
inline void TLex16::Mark()
	{iMark.iPtr=iNext;}
inline void TLex16::UnGetToMark()
    {UnGetToMark(iMark);}
inline void TLex16::SkipAndMark(TInt aNumber)
    {SkipAndMark(aNumber,iMark);}
inline void TLex16::SkipSpaceAndMark()
    {SkipSpaceAndMark(iMark);}
inline TInt TLex16::TokenLength() const
	{return(iNext-iMark.iPtr);}
inline TInt TLex16::MarkedOffset() const
    {return(iMark.iPtr-iBuf);}
inline TInt TLex16::Val(TInt &aVal)
	{return(Val((TInt32&)aVal));}
inline TInt TLex16::Val(TUint &aVal,TRadix aRadix)
	{return(Val((TUint32&)aVal,aRadix));}
inline void TLex16::Assign(const TLex16& aLex)
	{new(this) TLex16(aLex);}

// Class TLocale
inline TInt TLocale::CountryCode() const
	{return(iCountryCode);}
inline void TLocale::SetCountryCode(TInt aCode)
	{iCountryCode=aCode;}
inline TTimeIntervalSeconds TLocale::UniversalTimeOffset() const
	{return(iUniversalTimeOffset);}
inline void TLocale::SetUniversalTimeOffset(const TTimeIntervalSeconds& anOffset)
	{iUniversalTimeOffset=anOffset;}
inline TDateFormat TLocale::DateFormat() const
	{return(iDateFormat);}
inline void TLocale::SetDateFormat(TDateFormat aFormat)
	{iDateFormat=aFormat;}
inline TTimeFormat TLocale::TimeFormat() const
	{return(iTimeFormat);}
inline void TLocale::SetTimeFormat(TTimeFormat aFormat)
	{iTimeFormat=aFormat;}
inline TLocalePos TLocale::CurrencySymbolPosition() const
	{return(iCurrencySymbolPosition);}
inline void TLocale::SetCurrencySymbolPosition(TLocalePos aPos)
	{iCurrencySymbolPosition=aPos;}
inline TBool TLocale::CurrencySpaceBetween() const
	{return(iCurrencySpaceBetween);}
inline void TLocale::SetCurrencySpaceBetween(TBool aSpace)
	{iCurrencySpaceBetween=aSpace;}
inline TInt TLocale::CurrencyDecimalPlaces() const
	{return(iCurrencyDecimalPlaces);}
inline void TLocale::SetCurrencyDecimalPlaces(TInt aPlaces)
	{iCurrencyDecimalPlaces=aPlaces;}
inline TBool TLocale::CurrencyNegativeInBrackets() const				// These two functions are deprecated                 
	{return((TBool)iNegativeCurrencyFormat);}							// They should not be used, The two new 
inline void TLocale::SetCurrencyNegativeInBrackets(TBool aBool)			// NegativeCurrencyFormat functions should be used instead
	{iNegativeCurrencyFormat=(aBool)?EInBrackets:ELeadingMinusSign;}	// These functions are for compatibility...
inline TBool TLocale::CurrencyTriadsAllowed() const
	{return(iCurrencyTriadsAllowed);}
inline void TLocale::SetCurrencyTriadsAllowed(TBool aBool)
	{iCurrencyTriadsAllowed=aBool;}
inline TChar TLocale::ThousandsSeparator() const
	{return(iThousandsSeparator);}
inline void TLocale::SetThousandsSeparator(const TChar& aChar)
	{iThousandsSeparator=aChar;}
inline TChar TLocale::DecimalSeparator() const
	{return(iDecimalSeparator);}
inline void TLocale::SetDecimalSeparator(const TChar& aChar)
	{iDecimalSeparator=aChar;}
inline TChar TLocale::DateSeparator(TInt aIndex) const
	{return(iDateSeparator[aIndex]);}
inline void TLocale::SetDateSeparator(const TChar& aChar,TInt aIndex)
	{__ASSERT_DEBUG(aIndex>=0 && aIndex<KMaxDateSeparators,User::Invariant());
	iDateSeparator[aIndex]=aChar;}
inline TChar TLocale::TimeSeparator(TInt aIndex) const
	{return(iTimeSeparator[aIndex]);}
inline void TLocale::SetTimeSeparator(const TChar& aChar,TInt aIndex)
	{__ASSERT_DEBUG(aIndex>=0 && aIndex<KMaxTimeSeparators,User::Invariant());
	iTimeSeparator[aIndex]=aChar;}
inline TLocalePos TLocale::AmPmSymbolPosition() const
	{return(iAmPmSymbolPosition);}
inline void TLocale::SetAmPmSymbolPosition(TLocalePos aPos)
	{iAmPmSymbolPosition=aPos;}
inline TBool TLocale::AmPmSpaceBetween() const
	{return(iAmPmSpaceBetween);}
inline void TLocale::SetAmPmSpaceBetween(TBool aSpace)
	{iAmPmSpaceBetween=aSpace;}
inline TUint TLocale::DaylightSaving() const
	{return(iDaylightSaving);} 
inline void TLocale::SetDaylightSaving(TUint aDaylightSaving)
	{iDaylightSaving=aDaylightSaving;} 
inline TBool TLocale::QueryHomeHasDaylightSavingOn() const
	{return((iHomeDaylightSavingZone|EDstHome) & iDaylightSaving);}
inline TDaylightSavingZone TLocale::HomeDaylightSavingZone() const
	{return(iHomeDaylightSavingZone);}
inline void TLocale::SetHomeDaylightSavingZone(TDaylightSavingZone aZone)
	{iHomeDaylightSavingZone=aZone;}
inline TUint TLocale::WorkDays() const
	{return(iWorkDays);}
inline void TLocale::SetWorkDays(TUint aMask)
	{iWorkDays=aMask;}
inline TDay TLocale::StartOfWeek() const
	{return(iStartOfWeek);}
inline void TLocale::SetStartOfWeek(TDay aDay)
	{iStartOfWeek=aDay;}
inline TClockFormat TLocale::ClockFormat() const
	{return(iClockFormat);}
inline void TLocale::SetClockFormat(TClockFormat aFormat)
	{iClockFormat=aFormat;}
inline TUnitsFormat TLocale::UnitsGeneral() const
	{return(iUnitsGeneral);}
inline void TLocale::SetUnitsGeneral(TUnitsFormat aFormat)
	{iUnitsGeneral=aFormat;}
inline TUnitsFormat TLocale::UnitsDistanceShort() const
	{return(iUnitsDistanceShort);}
inline void TLocale::SetUnitsDistanceShort(TUnitsFormat aFormat)
	{iUnitsDistanceShort=aFormat;}
inline TUnitsFormat TLocale::UnitsDistanceLong() const
	{return(iUnitsDistanceLong);}
inline void TLocale::SetUnitsDistanceLong(TUnitsFormat aFormat)
	{iUnitsDistanceLong=aFormat;}
inline TLocale::TNegativeCurrencyFormat TLocale::NegativeCurrencyFormat() const
	{return(iNegativeCurrencyFormat);}
inline void TLocale::SetNegativeCurrencyFormat(TLocale::TNegativeCurrencyFormat aNegativeCurrencyFormat)
	{iNegativeCurrencyFormat = aNegativeCurrencyFormat;}
inline TBool TLocale::NegativeLoseSpace() const
	{ 
	if((iExtraNegativeCurrencyFormatFlags|EFlagNegativeLoseSpace)==iExtraNegativeCurrencyFormatFlags)
		return ETrue;
	else
		return EFalse;
	}
inline void TLocale::SetNegativeLoseSpace(TBool aBool)
	{
	if(aBool)
		iExtraNegativeCurrencyFormatFlags |= EFlagNegativeLoseSpace;
	else
		iExtraNegativeCurrencyFormatFlags &= ~EFlagNegativeLoseSpace;
	}
inline TBool TLocale::NegativeCurrencySymbolOpposite() const
	{
	if((iExtraNegativeCurrencyFormatFlags|EFlagNegativeCurrencySymbolOpposite)==iExtraNegativeCurrencyFormatFlags)
		return ETrue;
	else
		return EFalse;
	}
inline void TLocale::SetNegativeCurrencySymbolOpposite(TBool aBool)
	{
	if (aBool)
		iExtraNegativeCurrencyFormatFlags |= EFlagNegativeCurrencySymbolOpposite;
	else
		iExtraNegativeCurrencyFormatFlags &= ~EFlagNegativeCurrencySymbolOpposite;
	}

// Class TPoint
inline TPoint::TPoint()
	: iX(0),iY(0)
	{}
inline TPoint::TPoint(TInt aX,TInt aY)
	: iX(aX),iY(aY)
	{}

// Class TSize
inline TSize::TSize()
	: iWidth(0),iHeight(0)
	{}
inline TSize::TSize(TInt aWidth,TInt aHeight)
	: iWidth(aWidth),iHeight(aHeight)
	{}

// Class TRequestStatus
inline TRequestStatus::TRequestStatus()
	{}
inline TRequestStatus::TRequestStatus(TInt aVal)
	: iStatus(aVal)
	{}
inline TInt TRequestStatus::operator=(TInt aVal)
	{return(iStatus=aVal);}
inline TInt TRequestStatus::operator==(TInt aVal) const
	{return(iStatus==aVal);}
inline TInt TRequestStatus::operator!=(TInt aVal) const
	{return(iStatus!=aVal);}
inline TInt TRequestStatus::operator>=(TInt aVal) const
	{return(iStatus>=aVal);}
inline TInt TRequestStatus::operator<=(TInt aVal) const
	{return(iStatus<=aVal);}
inline TInt TRequestStatus::operator>(TInt aVal) const
	{return(iStatus>aVal);}
inline TInt TRequestStatus::operator<(TInt aVal) const
	{return(iStatus<aVal);}
inline TInt TRequestStatus::Int() const
	{return(iStatus);}

// Class TFindHandleBase
inline TInt TFindHandleBase::Handle() const
	{return(iFindHandle);}

// Class RHandleBase
inline RHandleBase::RHandleBase()
	: iHandle(0)
	{}
inline RHandleBase::RHandleBase(TInt aHandle)
	: iHandle(aHandle)
	{}
inline void RHandleBase::SetHandle(TInt aHandle)
	{iHandle=aHandle;}
inline TInt RHandleBase::Handle() const
	{return(iHandle);}

// Class TFindSemaphore
inline TFindSemaphore::TFindSemaphore()
    : TFindHandleBase()
    {}
inline TFindSemaphore::TFindSemaphore(const TDesC &aMatch)
    : TFindHandleBase(aMatch)
    {}

// Class TFindMutex
inline TFindMutex::TFindMutex()
    : TFindHandleBase()
    {}
inline TFindMutex::TFindMutex(const TDesC &aMatch)
    : TFindHandleBase(aMatch)
    {}

// Class TFindChunk
inline TFindChunk::TFindChunk()
    : TFindHandleBase()
    {}
inline TFindChunk::TFindChunk(const TDesC &aMatch)
    : TFindHandleBase(aMatch)
    {}

// Class TFindThread
inline TFindThread::TFindThread()
    : TFindHandleBase()
    {}
inline TFindThread::TFindThread(const TDesC &aMatch)
    : TFindHandleBase(aMatch)
    {}

// Class TFindProcess
inline TFindProcess::TFindProcess()
    : TFindHandleBase()
    {}
inline TFindProcess::TFindProcess(const TDesC &aMatch)
    : TFindHandleBase(aMatch)
    {}

// Class TFindLogicalDevice
inline TFindLogicalDevice::TFindLogicalDevice()
    : TFindHandleBase()
    {}
inline TFindLogicalDevice::TFindLogicalDevice(const TDesC &aMatch)
    : TFindHandleBase(aMatch)
    {}

// Class TFindPhysicalDevice
inline TFindPhysicalDevice::TFindPhysicalDevice()
    : TFindHandleBase()
    {}
inline TFindPhysicalDevice::TFindPhysicalDevice(const TDesC &aMatch)
    : TFindHandleBase(aMatch)
    {}

// Class TFindLogicalChannel
inline TFindLogicalChannel::TFindLogicalChannel()
    : TFindHandleBase()
    {}
inline TFindLogicalChannel::TFindLogicalChannel(const TDesC &aMatch)
    : TFindHandleBase(aMatch)
    {}

// Class TFindServer
inline TFindServer::TFindServer()
    : TFindHandleBase()
    {}
inline TFindServer::TFindServer(const TDesC &aMatch)
    : TFindHandleBase(aMatch)
    {}

// Class TFindLibrary
inline TFindLibrary::TFindLibrary()
    : TFindHandleBase()
    {}
inline TFindLibrary::TFindLibrary(const TDesC &aMatch)
    : TFindHandleBase(aMatch)
    {}

// Class RDevice
inline TInt RDevice::Open(const TFindLogicalDevice& aFind,TOwnerType aType)
	{return(RHandleBase::Open(aFind,aType));}

// Class RSemaphore
inline TInt RSemaphore::Open(const TFindSemaphore& aFind,TOwnerType aType)
	{return(RHandleBase::Open(aFind,aType));}

// Class RCriticalSection
inline TBool RCriticalSection::IsBlocked() const
	{return(iBlocked!=1);}

// Class RMutex
inline TInt RMutex::Open(const TFindMutex& aFind,TOwnerType aType)
	{return(RHandleBase::Open(aFind,aType));}

// Class RChunk
inline TInt RChunk::Open(const TFindChunk& aFind,TOwnerType aType)
	{return(RHandleBase::Open(aFind,aType));}
inline TBool RChunk::IsReadable() const
	{return (Attributes()&RHandleBase::EDirectReadAccess); }
inline TBool RChunk::IsWritable() const
	{return (Attributes()&RHandleBase::EDirectWriteAccess); }

// Class TThreadId
inline TThreadId::TThreadId()
	{}
inline TThreadId::TThreadId(TUint aId)
	: iId(aId)
	{}
inline TThreadId::operator TUint()
	{ return iId; }
inline TInt TThreadId::operator==(TThreadId aId)
	{return iId==aId.iId;}
inline TInt TThreadId::operator!=(TThreadId aId)
	{return iId!=aId.iId;}

// Class RThread
inline RThread::RThread()
	: RHandleBase(KCurrentThreadHandle)
	{}
inline TInt RThread::Open(const TFindThread& aFind,TOwnerType aType)
	{return(RHandleBase::Open(aFind,aType));}

// Class TProcessId
inline TProcessId::TProcessId()
	{}
inline TProcessId::TProcessId(TUint aId)
	: iId(aId)
	{}
inline TProcessId::operator TUint()
	{ return iId; }
inline TInt TProcessId::operator==(TProcessId aId)
	{return iId==aId.iId;}
inline TInt TProcessId::operator!=(TProcessId aId)
	{return iId!=aId.iId;}

// Class RProcess
inline RProcess::RProcess()
	: RHandleBase(KCurrentProcessHandle)
	{}
inline RProcess::RProcess(TInt aHandle)
	: RHandleBase(aHandle)
	{}
inline TInt RProcess::Open(const TFindProcess& aFind,TOwnerType aType)
	{return(RHandleBase::Open(aFind,aType));}

// Class RMessagePtr
inline RMessagePtr::RMessagePtr()
	: iHandle(0)
	{}
inline RMessagePtr::RMessagePtr(const RMessage& aMessage)
	: iHandle(aMessage.iHandle)
	{}
inline TBool RMessagePtr::IsNull()
	{return iHandle==0;}
inline TBool operator==(RMessagePtr aLeft,RMessagePtr aRight)
	{return aLeft.iHandle==aRight.iHandle;}
inline TBool operator!=(RMessagePtr aLeft,RMessagePtr aRight)
	{return !(aLeft==aRight);}

// Class RMessage
inline TInt RMessage::Function() const
	{return(iFunction);}
inline const RThread &RMessage::Client() const
	{return(iClient);}
inline TInt RMessage::Int0() const
	{return(iArgs[0]);}
inline TInt RMessage::Int1() const
	{return(iArgs[1]);}
inline TInt RMessage::Int2() const
	{return(iArgs[2]);}
inline TInt RMessage::Int3() const
	{return(iArgs[3]);}
inline const TAny *RMessage::Ptr0() const
	{return((const TAny *)iArgs[0]);}
inline const TAny *RMessage::Ptr1() const
	{return((const TAny *)iArgs[1]);}
inline const TAny *RMessage::Ptr2() const
	{return((const TAny *)iArgs[2]);}
inline const TAny *RMessage::Ptr3() const
	{return((const TAny *)iArgs[3]);}
inline const RMessagePtr RMessage::MessagePtr() const
	{return(RMessagePtr(*this));}

// Class RServer
inline const RMessage &RServer::Message() const
	{return iMessage;}

inline TInt RSessionBase::CreateSession(const TDesC& aServer,const TVersion& aVersion)
	{return CreateSession(aServer,aVersion,-1);}

// Class RSubSessionBase
inline RSubSessionBase::RSubSessionBase()
	: iSubSessionHandle(0)
	{}
inline TInt RSubSessionBase::SubSessionHandle()
	{return iSubSessionHandle;}
inline RSessionBase& RSubSessionBase::Session()
	{return iSession;}

// Class RRefBase
inline RRefBase::RRefBase()
	: iPtr(NULL)
	{}
inline RRefBase::RRefBase(const RRefBase &aRef)
	{Copy(aRef);}

// Class RRef
template <class T>
inline RRef<T>::RRef()
	{}
template <class T>
inline RRef<T>::RRef(const RRef<T> &anObject)
	{Copy(anObject);}
template <class T>
inline void RRef<T>::operator=(const RRef<T> &anObject)
	{Copy(anObject);}
template <class T>
inline T *RRef<T>::operator->()
	{return((T *)iPtr);}
template <class T>
inline RRef<T>::operator T*()
	{return((T *)iPtr);}
template <class T>
void RRef<T>::Alloc(const T &anObject)
	{DoAlloc(&anObject,sizeof(T));}
template <class T>
void RRef<T>::Alloc(const T &anObject,TInt aSize)
	{DoAlloc(&anObject,aSize);}
template <class T>
void RRef<T>::AllocL(const T &anObject)
	{DoAllocL(&anObject,sizeof(T));}
template <class T>
void RRef<T>::AllocL(const T &anObject,TInt aSize)
	{DoAllocL(&anObject,aSize);}

// Class TRegion
inline TBool TRegion::CheckError() const
	{return(iError);}
inline TInt TRegion::Count() const
	{return(iCount);}
inline const TRect *TRegion::RectangleList() const
	{return(((TRegion *)this)->RectangleListW());}
inline TRegion::TRegion()
	{}

// Class RRegion
inline TInt RRegion::CheckSpare() const
	{return(iAllocedRects-iCount);}

// Class TRegionFix
template <TInt S>
inline TRegionFix<S>::TRegionFix() : TRegion(-S)
	{}
template <TInt S>
inline TRegionFix<S>::TRegionFix(const TRect &aRect) : TRegion(-S)
	{AddRect(aRect);}
template <TInt S>
inline TRegionFix<S>::TRegionFix(const TRegionFix<S> &aRegion)
	{*this=aRegion;}

template <TInt S>
inline RRegionBuf<S>::RRegionBuf() : RRegion(-S&(~ERRegionBuf),S)
	{}
template <TInt S>
inline RRegionBuf<S>::RRegionBuf(const RRegion &aRegion) 
	{*this=aRegion;}
template <TInt S>
inline RRegionBuf<S>::RRegionBuf(const TRect &aRect) : RRegion(-S&(~ERRegionBuf),S)
	{AddRect(aRect);}
template <TInt S>
inline RRegionBuf<S>::RRegionBuf(const RRegionBuf<S> &aRegion)
    {*this=aRegion;}

// Class TTrap
inline TTrap::TTrap()
	{}

// enum TTimerLockSpec
inline TTimerLockSpec &operator++(TTimerLockSpec &aLock)
	{
	return aLock=((aLock==ETwelveOClock) ? EOneOClock : (TTimerLockSpec)((TInt)aLock+1));
	}
inline TTimerLockSpec operator++(TTimerLockSpec &aLock, TInt)
	{
	TTimerLockSpec l=aLock;
	aLock=((aLock==ETwelveOClock) ? EOneOClock : (TTimerLockSpec)((TInt)aLock+1));
	return l;
	}

// Class TUid
inline TUid TUid::Uid(TInt aUid)
	{TUid uid={aUid};return uid;}
inline TUid TUid::Null()
	{TUid uid={KNullUidValue};return uid;}

// Class TCheckedUid
inline const TUidType& TCheckedUid::UidType() const
    {return(iType);}

// Template class TArray
template <class T>
inline TArray<T>::TArray(TInt (*aCount)(const CBase *aPtr),const TAny *(*anAt)(const CBase *aPtr,TInt anIndex),const CBase *aPtr)
	: iPtr(aPtr),iCount(aCount),iAt(anAt)
	{}
template <class T>
inline TInt TArray<T>::Count() const
	{return((*iCount)(iPtr));}
template <class T>
inline const T &TArray<T>::operator[](TInt anIndex) const
	{return(*((const T *)(*iAt)(iPtr,anIndex)));}

// Array deletion support, uses CBase deletion (virtual d'tor) for all C-classes
template <class T>
void _DeleteArray(T** aBegin,T** aEnd)
	{for (;;) if (aBegin<aEnd) delete *aBegin++; else return;}
template <class T>
struct _ArrayUtil
	{
	static inline void Delete(T* aBegin,T* aEnd,CBase*)
		{::_DeleteArray((CBase**)aBegin,(CBase**)aEnd);}
	static inline void Delete(T* aBegin,T* aEnd,TAny*)
		{::_DeleteArray(aBegin,aEnd);}
	static inline void Delete(T* aArray,TInt aCount)
		{Delete(aArray,aArray+aCount,*aArray);}
	};

// Template class TFixedArray
IMPORT_C void PanicTFixedArray();

template <class T,TInt S>
inline TFixedArray<T,S>::TFixedArray()
	{}
template <class T,TInt S>
inline void TFixedArray<T,S>::Copy(const T* aList,TInt aLength)
	{__ASSERT_DEBUG(TUint(aLength)<=TUint(S),PanicTFixedArray());Mem::Copy(iRep,aList,aLength*sizeof(T));}
template <class T,TInt S>
inline TFixedArray<T,S>::TFixedArray(const T* aList,TInt aLength)
	{Copy(aList,aLength);}
template <class T,TInt S>
inline void TFixedArray<T,S>::Reset()
	{Mem::FillZ(iRep,sizeof(iRep));}
template <class T,TInt S>
inline TInt TFixedArray<T,S>::Count() const
	{return S;}
template <class T,TInt S>
inline TInt TFixedArray<T,S>::Length() const
	{return sizeof(T);}
template <class T,TInt S>
inline TBool TFixedArray<T,S>::InRange(TInt aIndex)
	{return TUint(aIndex)<S;}
template <class T,TInt S>
inline T& TFixedArray<T,S>::operator[](TInt aIndex)
	{__ASSERT_DEBUG(InRange(aIndex),PanicTFixedArray());return iRep[aIndex];}
template <class T,TInt S>
inline const T& TFixedArray<T,S>::operator[](TInt aIndex) const
	{return CONST_CAST(ThisClass&,*this)[aIndex];}
template <class T,TInt S>
inline T& TFixedArray<T,S>::At(TInt aIndex)
	{__ASSERT_ALWAYS(InRange(aIndex),PanicTFixedArray());return iRep[aIndex];}
template <class T,TInt S>
inline const T& TFixedArray<T,S>::At(TInt aIndex) const
	{return CONST_CAST(ThisClass&,*this).At(aIndex);}
template <class T,TInt S>
inline T* TFixedArray<T,S>::Begin()
	{return &iRep[0];}
template <class T,TInt S>
inline T* TFixedArray<T,S>::End()
	{return &iRep[S];}
template <class T,TInt S>
inline const T* TFixedArray<T,S>::Begin() const
	{return &iRep[0];}
template <class T,TInt S>
inline const T* TFixedArray<T,S>::End() const
	{return &iRep[S];}
template <class T,TInt S>
inline TInt TFixedArray<T,S>::CountFunctionR(const CBase*)
	{return S;}
template <class T,TInt S>
inline const TAny* TFixedArray<T,S>::AtFunctionR(const CBase* aThis,TInt aIndex)
	{return &REINTERPRET_CAST(const ThisClass&,*aThis)[aIndex];}
template <class T,TInt S>
inline TArray<T> TFixedArray<T,S>::Array() const
	{return TArray<T>(CountFunctionR,AtFunctionR,REINTERPRET_CAST(const CBase*,this));}
template <class T,TInt S>
inline void TFixedArray<T,S>::DeleteAll()
	{_ArrayUtil<T>::Delete(iRep,S);}

// Class TIdentityRelation<T>
template <class T>
inline TIdentityRelation<T>::TIdentityRelation( TBool(*anIdentity)(const T&, const T&) )
	{ iIdentity=(TGeneralIdentityRelation)anIdentity; }
template <class T>
inline TIdentityRelation<T>::operator TGeneralIdentityRelation() const
	{ return iIdentity; }

// Class TLinearOrder<T>
template <class T>
inline TLinearOrder<T>::TLinearOrder( TInt(*anOrder)(const T&, const T&) )
	{ iOrder=(TGeneralLinearOrder)anOrder; }
template <class T>
inline TLinearOrder<T>::operator TGeneralLinearOrder() const
	{ return iOrder; }

// Class RPointerArray<T>
template <class T>
inline RPointerArray<T>::RPointerArray()
	: RPointerArrayBase()
	{}
template <class T>
inline RPointerArray<T>::RPointerArray(TInt aGranularity)
	: RPointerArrayBase(aGranularity)
	{}
template <class T>
inline RPointerArray<T>::RPointerArray(T** aEntries, TInt aCount)
	: RPointerArrayBase((TAny **)aEntries, aCount)
	{}
template <class T>
inline void RPointerArray<T>::Close()
	{RPointerArrayBase::Close();}
template <class T>
inline TInt RPointerArray<T>::Count() const
	{ return RPointerArrayBase::Count(); }
template <class T>
inline const T*& RPointerArray<T>::operator[](TInt anIndex) const
	{return (const T*&)At(anIndex);}
template <class T>
inline T*& RPointerArray<T>::operator[](TInt anIndex)
	{return (T*&)At(anIndex);}
template <class T>
inline TInt RPointerArray<T>::Append(const T* anEntry)
	{ return RPointerArrayBase::Append(anEntry); }
template <class T>
inline TInt RPointerArray<T>::Insert(const T* anEntry, TInt aPos)
	{ return RPointerArrayBase::Insert(anEntry,aPos); }
template <class T>
inline void RPointerArray<T>::Remove(TInt anIndex)
	{RPointerArrayBase::Remove(anIndex);}
template <class T>
inline void RPointerArray<T>::Compress()
	{RPointerArrayBase::Compress();}
template <class T>
inline void RPointerArray<T>::GranularCompress()
	{RPointerArrayBase::GranularCompress();}
template <class T>
inline void RPointerArray<T>::Reset()
	{RPointerArrayBase::Reset();}
template <class T>
inline TInt RPointerArray<T>::Find(const T* anEntry) const
	{ return RPointerArrayBase::Find(anEntry); }
template <class T>
inline TInt RPointerArray<T>::Find(const T* anEntry, TIdentityRelation<T> anIdentity) const
	{ return RPointerArrayBase::Find(anEntry,anIdentity); }
template <class T>
inline TInt RPointerArray<T>::FindInAddressOrder(const T* anEntry) const
	{ return RPointerArrayBase::FindIsqUnsigned((TUint)anEntry); }
template <class T>
inline TInt RPointerArray<T>::FindInOrder(const T* anEntry, TLinearOrder<T> anOrder) const
	{ return RPointerArrayBase::FindIsq(anEntry,anOrder); }
template <class T>
inline TInt RPointerArray<T>::FindInAddressOrder(const T* anEntry, TInt& anIndex) const
	{ return RPointerArrayBase::BinarySearchUnsigned((TUint)anEntry,anIndex); }
template <class T>
inline TInt RPointerArray<T>::FindInOrder(const T* anEntry, TInt& anIndex, TLinearOrder<T> anOrder) const
	{ return RPointerArrayBase::BinarySearch(anEntry,anIndex,anOrder); }
template <class T>
inline TInt RPointerArray<T>::InsertInAddressOrder(const T* anEntry)
	{ return RPointerArrayBase::InsertIsqUnsigned((TUint)anEntry,EFalse); }
template <class T>
inline TInt RPointerArray<T>::InsertInOrder(const T* anEntry, TLinearOrder<T> anOrder)
	{ return RPointerArrayBase::InsertIsq(anEntry,anOrder,EFalse); }
template <class T>
inline TInt RPointerArray<T>::InsertInAddressOrderAllowRepeats(const T* anEntry)
	{ return RPointerArrayBase::InsertIsqUnsigned((TUint)anEntry,ETrue); }
template <class T>
inline TInt RPointerArray<T>::InsertInOrderAllowRepeats(const T* anEntry, TLinearOrder<T> anOrder)
	{ return RPointerArrayBase::InsertIsq(anEntry,anOrder,ETrue); }
template <class T>
inline void RPointerArray<T>::SortIntoAddressOrder()
	{ HeapSortUnsigned(); }
template <class T>
inline void RPointerArray<T>::Sort(TLinearOrder<T> anOrder)
	{ HeapSort(anOrder); }
template <class T>
inline TArray<T> RPointerArray<T>::Array() const
	{ return TArray<T>(GetCount,GetElementPtr,(const CBase*)this); }

template <class T>
void RPointerArray<T>::ResetAndDestroy()
	{
	TInt c=Count();
	T** pE=(T**)Entries();
	ZeroCount();
	TInt i;
	for (i=0; i<c; i++)
		{
		delete *pE;
		pE++;
		}
	Reset();
	}

template <class T>
inline RArray<T>::RArray()
	: RArrayBase(sizeof(T))
	{}
template <class T>
inline RArray<T>::RArray(TInt aGranularity)
	: RArrayBase(sizeof(T),aGranularity)
	{}
template <class T>
inline RArray<T>::RArray(TInt aGranularity, TInt aKeyOffset)
	: RArrayBase(sizeof(T),aGranularity,aKeyOffset)
 	{}
template <class T>
inline RArray<T>::RArray(TInt aEntrySize,T* aEntries, TInt aCount)
 	: RArrayBase(aEntrySize,aEntries,aCount)
	{}
template <class T>
inline void RArray<T>::Close()
	{RArrayBase::Close();}
template <class T>
inline TInt RArray<T>::Count() const
	{return RArrayBase::Count();}
template <class T>
inline const T& RArray<T>::operator[](TInt anIndex) const
	{return *(const T*)At(anIndex); }
template <class T>
inline T& RArray<T>::operator[](TInt anIndex)
	{return *(T*)At(anIndex); }
template <class T>
inline TInt RArray<T>::Append(const T& anEntry)
	{return RArrayBase::Append(&anEntry);}
template <class T>
inline TInt RArray<T>::Insert(const T& anEntry, TInt aPos)
	{return RArrayBase::Insert(&anEntry,aPos);}
template <class T>
inline void RArray<T>::Remove(TInt anIndex)
	{RArrayBase::Remove(anIndex);}
template <class T>
inline void RArray<T>::Compress()
	{RArrayBase::Compress();}
template <class T>
inline void RArray<T>::GranularCompress()
	{RArrayBase::GranularCompress();}
template <class T>
inline void RArray<T>::Reset()
	{RArrayBase::Reset();}
template <class T>
inline TInt RArray<T>::Find(const T& anEntry) const
	{return RArrayBase::Find(&anEntry);}
template <class T>
inline TInt RArray<T>::Find(const T& anEntry, TIdentityRelation<T> anIdentity) const
	{return RArrayBase::Find(&anEntry,anIdentity);}
template <class T>
inline TInt RArray<T>::FindInSignedKeyOrder(const T& anEntry) const
	{return RArrayBase::FindIsqSigned(&anEntry);}
template <class T>
inline TInt RArray<T>::FindInUnsignedKeyOrder(const T& anEntry) const
	{return RArrayBase::FindIsqUnsigned(&anEntry);}
template <class T>
inline TInt RArray<T>::FindInOrder(const T& anEntry, TLinearOrder<T> anOrder) const
	{return RArrayBase::FindIsq(&anEntry,anOrder);}
template <class T>
inline TInt RArray<T>::FindInSignedKeyOrder(const T& anEntry, TInt& anIndex) const
	{return RArrayBase::BinarySearchSigned(&anEntry,anIndex);}
template <class T>
inline TInt RArray<T>::FindInUnsignedKeyOrder(const T& anEntry, TInt& anIndex) const
	{return RArrayBase::BinarySearchUnsigned(&anEntry,anIndex);}
template <class T>
inline TInt RArray<T>::FindInOrder(const T& anEntry, TInt& anIndex, TLinearOrder<T> anOrder) const
	{return RArrayBase::BinarySearch(&anEntry,anIndex,anOrder);}
template <class T>
inline TInt RArray<T>::InsertInSignedKeyOrder(const T& anEntry)
	{return RArrayBase::InsertIsqSigned(&anEntry,EFalse);}
template <class T>
inline TInt RArray<T>::InsertInUnsignedKeyOrder(const T& anEntry)
	{return RArrayBase::InsertIsqUnsigned(&anEntry,EFalse);}
template <class T>
inline TInt RArray<T>::InsertInOrder(const T& anEntry, TLinearOrder<T> anOrder)
	{return RArrayBase::InsertIsq(&anEntry,anOrder,EFalse);}
template <class T>
inline TInt RArray<T>::InsertInSignedKeyOrderAllowRepeats(const T& anEntry)
	{return RArrayBase::InsertIsqSigned(&anEntry,ETrue);}
template <class T>
inline TInt RArray<T>::InsertInUnsignedKeyOrderAllowRepeats(const T& anEntry)
	{return RArrayBase::InsertIsqUnsigned(&anEntry,ETrue);}
template <class T>
inline TInt RArray<T>::InsertInOrderAllowRepeats(const T& anEntry, TLinearOrder<T> anOrder)
	{return RArrayBase::InsertIsq(&anEntry,anOrder,ETrue);}
template <class T>
inline void RArray<T>::SortSigned()
	{HeapSortSigned();}
template <class T>
inline void RArray<T>::SortUnsigned()
	{HeapSortUnsigned();}
template <class T>
inline void RArray<T>::Sort(TLinearOrder<T> anOrder)
	{HeapSort(anOrder);}
template <class T>
inline TArray<T> RArray<T>::Array() const
	{ return TArray<T>(GetCount,GetElementPtr,(const CBase*)this); }

inline RArray<TInt>::RArray()
	: RPointerArrayBase()
	{}
inline RArray<TInt>::RArray(TInt aGranularity)
	: RPointerArrayBase(aGranularity)
	{}
inline void RArray<TInt>::Close()
	{RPointerArrayBase::Close();}
inline TInt RArray<TInt>::Count() const
	{ return RPointerArrayBase::Count(); }
inline const TInt& RArray<TInt>::operator[](TInt anIndex) const
	{return (const TInt&)At(anIndex);}
inline TInt& RArray<TInt>::operator[](TInt anIndex)
	{return (TInt&)At(anIndex);}
inline TInt RArray<TInt>::Append(TInt anEntry)
	{ return RPointerArrayBase::Append((const TAny*)anEntry); }
inline TInt RArray<TInt>::Insert(TInt anEntry, TInt aPos)
	{ return RPointerArrayBase::Insert((const TAny*)anEntry,aPos); }
inline void RArray<TInt>::Remove(TInt anIndex)
	{RPointerArrayBase::Remove(anIndex);}
inline void RArray<TInt>::Compress()
	{RPointerArrayBase::Compress();}
inline void RArray<TInt>::GranularCompress()
	{RPointerArrayBase::GranularCompress();}
inline void RArray<TInt>::Reset()
	{RPointerArrayBase::Reset();}
inline TInt RArray<TInt>::Find(TInt anEntry) const
	{ return RPointerArrayBase::Find((const TAny*)anEntry); }
inline TInt RArray<TInt>::FindInOrder(TInt anEntry) const
	{ return RPointerArrayBase::FindIsqSigned(anEntry); }
inline TInt RArray<TInt>::FindInOrder(TInt anEntry, TInt& anIndex) const
	{ return RPointerArrayBase::BinarySearchSigned(anEntry,anIndex); }
inline TInt RArray<TInt>::InsertInOrder(TInt anEntry)
	{ return RPointerArrayBase::InsertIsqSigned(anEntry,EFalse); }
inline TInt RArray<TInt>::InsertInOrderAllowRepeats(TInt anEntry)
	{ return RPointerArrayBase::InsertIsqSigned(anEntry,ETrue); }
inline void RArray<TInt>::Sort()
	{ HeapSortSigned(); }
inline TArray<TInt> RArray<TInt>::Array() const
	{ return TArray<TInt>(GetCount,GetElementPtr,(const CBase*)this); }

inline RArray<TUint>::RArray()
	: RPointerArrayBase()
	{}
inline RArray<TUint>::RArray(TInt aGranularity)
	: RPointerArrayBase(aGranularity)
	{}
inline void RArray<TUint>::Close()
	{RPointerArrayBase::Close();}
inline TInt RArray<TUint>::Count() const
	{return RPointerArrayBase::Count(); }
inline const TUint& RArray<TUint>::operator[](TInt anIndex) const
	{return (const TUint&)At(anIndex);}
inline TUint& RArray<TUint>::operator[](TInt anIndex)
	{return (TUint&)At(anIndex);}
inline TInt RArray<TUint>::Append(TUint anEntry)
	{ return RPointerArrayBase::Append((const TAny*)anEntry); }
inline TInt RArray<TUint>::Insert(TUint anEntry, TInt aPos)
	{ return RPointerArrayBase::Insert((const TAny*)anEntry,aPos); }
inline void RArray<TUint>::Remove(TInt anIndex)
	{RPointerArrayBase::Remove(anIndex);}
inline void RArray<TUint>::Compress()
	{RPointerArrayBase::Compress();}
inline void RArray<TUint>::Reset()
	{RPointerArrayBase::Reset();}
inline TInt RArray<TUint>::Find(TUint anEntry) const
	{ return RPointerArrayBase::Find((const TAny*)anEntry); }
inline TInt RArray<TUint>::FindInOrder(TUint anEntry) const
	{ return RPointerArrayBase::FindIsqUnsigned(anEntry); }
inline TInt RArray<TUint>::FindInOrder(TUint anEntry, TInt& anIndex) const
	{ return RPointerArrayBase::BinarySearchUnsigned(anEntry,anIndex); }
inline TInt RArray<TUint>::InsertInOrder(TUint anEntry)
	{ return RPointerArrayBase::InsertIsqUnsigned(anEntry,EFalse); }
inline TInt RArray<TUint>::InsertInOrderAllowRepeats(TUint anEntry)
	{ return RPointerArrayBase::InsertIsqUnsigned(anEntry,ETrue); }
inline void RArray<TUint>::Sort()
	{ HeapSortUnsigned(); }
inline TArray<TUint> RArray<TUint>::Array() const
	{ return TArray<TUint>(GetCount,GetElementPtr,(const CBase*)this); }

