// E32BASE.INL
//
// Copyright (c) 1994-1999 Symbian Ltd.  All rights reserved.
//


// Class CBase
inline TAny* CBase::operator new(TUint aSize, TAny* aBase)
	{Mem::FillZ(aBase,aSize);return(aBase);}
inline TAny* CBase::operator new(TUint aSize, TLeave)
	{return newL(aSize);}

// Class CBufBase
inline TInt CBufBase::Size() const
	{return(iSize);}

// Class CBufFlat
inline TInt CBufFlat::Capacity() const
	{return(iMaxSize);}

// Class CArrayFixBase
inline TInt CArrayFixBase::Count() const
	{return(iCount);}
inline TInt CArrayFixBase::Length() const
	{return(iLength);}

// Template class CArrayFix
template <class T>
inline CArrayFix<T>::CArrayFix(TBufRep aRep,TInt aGranularity)
	: CArrayFixBase(aRep,sizeof(T),aGranularity)
	{}
template <class T>
inline const T &CArrayFix<T>::operator[](TInt anIndex) const
	{return(*((const T *)CArrayFixBase::At(anIndex)));}
template <class T>
inline T &CArrayFix<T>::operator[](TInt anIndex)
	{return(*((T *)CArrayFixBase::At(anIndex)));}
template <class T>
inline const T &CArrayFix<T>::At(TInt anIndex) const
	{return(*((const T *)CArrayFixBase::At(anIndex)));}
template <class T>
inline const T *CArrayFix<T>::End(TInt anIndex) const
	{return((const T *)CArrayFixBase::End(anIndex));}
template <class T>
inline const T *CArrayFix<T>::Back(TInt anIndex) const
	{return((const T *)CArrayFixBase::Back(anIndex));}
template <class T>
inline T &CArrayFix<T>::At(TInt anIndex)
	{return(*((T *)CArrayFixBase::At(anIndex)));}
template <class T>
inline T *CArrayFix<T>::End(TInt anIndex)
	{return(((T *)CArrayFixBase::End(anIndex)));}
template <class T>
inline T *CArrayFix<T>::Back(TInt anIndex)
	{return(((T *)CArrayFixBase::Back(anIndex)));}
template <class T>
inline void CArrayFix<T>::AppendL(const T &aRef)
	{CArrayFixBase::InsertL(Count(),&aRef);}
template <class T>
inline void CArrayFix<T>::AppendL(const T *aPtr,TInt aCount)
	{CArrayFixBase::InsertL(Count(),aPtr,aCount);}
template <class T>
inline void CArrayFix<T>::AppendL(const T &aRef,TInt aReplicas)
	{CArrayFixBase::InsertRepL(Count(),&aRef,aReplicas);}
template <class T>
inline T &CArrayFix<T>::ExpandL(TInt anIndex)
	{return(*new(CArrayFixBase::ExpandL(anIndex)) T);}
template <class T>
inline T &CArrayFix<T>::ExtendL()
	{return(*new(CArrayFixBase::ExpandL(Count())) T);}
template <class T>
inline TInt CArrayFix<T>::Find(const T &aRef,TKeyArrayFix &aKey,TInt &anIndex) const
	{return(CArrayFixBase::Find(&aRef,aKey,anIndex));}
template <class T>
inline TInt CArrayFix<T>::FindIsq(const T &aRef,TKeyArrayFix &aKey,TInt &anIndex) const
	{return(CArrayFixBase::FindIsq(&aRef,aKey,anIndex));}
template <class T>
inline void CArrayFix<T>::InsertL(TInt anIndex,const T &aRef)
	{CArrayFixBase::InsertL(anIndex,&aRef);}
template <class T>
inline void CArrayFix<T>::InsertL(TInt anIndex,const T *aPtr,TInt aCount)
	{CArrayFixBase::InsertL(anIndex,aPtr,aCount);}
template <class T>
inline void CArrayFix<T>::InsertL(TInt anIndex,const T &aRef,TInt aReplicas)
	{CArrayFixBase::InsertRepL(anIndex,&aRef,aReplicas);}
template <class T>
inline TInt CArrayFix<T>::InsertIsqL(const T &aRef,TKeyArrayFix &aKey)
	{return(CArrayFixBase::InsertIsqL(&aRef,aKey));}
template <class T>
inline TInt CArrayFix<T>::InsertIsqAllowDuplicatesL(const T &aRef,TKeyArrayFix &aKey)
	{return(CArrayFixBase::InsertIsqAllowDuplicatesL(&aRef,aKey));}
template <class T>
inline void CArrayFix<T>::ResizeL(TInt aCount)
	{TUint8 b[sizeof(T)]; new(&b[0]) T; CArrayFixBase::ResizeL(aCount,&b[0]);}
template <class T>
inline void CArrayFix<T>::ResizeL(TInt aCount,const T &aRef)
	{CArrayFixBase::ResizeL(aCount,&aRef);}
template <class T>
inline const TArray<T> CArrayFix<T>::Array() const
	{return(TArray<T>(CountR,AtR,this));}
inline CArrayFix<TAny>::CArrayFix(TBufRep aRep,TInt aRecordLength,TInt aGranularity)
	: CArrayFixBase(aRep,aRecordLength,aGranularity)
	{}
inline const TAny *CArrayFix<TAny>::At(TInt anIndex) const
	{return(CArrayFixBase::At(anIndex));}
inline const TAny *CArrayFix<TAny>::End(TInt anIndex) const
	{return(CArrayFixBase::End(anIndex));}
inline const TAny *CArrayFix<TAny>::Back(TInt anIndex) const
	{return(CArrayFixBase::Back(anIndex));}
inline TAny *CArrayFix<TAny>::At(TInt anIndex)
	{return(CArrayFixBase::At(anIndex));}
inline TAny *CArrayFix<TAny>::End(TInt anIndex)
	{return(CArrayFixBase::End(anIndex));}
inline TAny *CArrayFix<TAny>::Back(TInt anIndex)
	{return(CArrayFixBase::Back(anIndex));}
inline void CArrayFix<TAny>::AppendL(const TAny *aPtr)
	{CArrayFixBase::InsertL(Count(),aPtr);}
inline void CArrayFix<TAny>::AppendL(const TAny *aPtr,TInt aCount)
	{CArrayFixBase::InsertL(Count(),aPtr,aCount);}
inline TAny *CArrayFix<TAny>::ExtendL()
	{return(CArrayFixBase::ExpandL(Count()));}

// Template class CArrayFixFlat
template <class T>
inline CArrayFixFlat<T>::CArrayFixFlat(TInt aGranularity)
	: CArrayFix<T>((TBufRep)CBufFlat::NewL,aGranularity)
	{}
template <class T>
inline void CArrayFixFlat<T>::SetReserveL(TInt aCount)
	{SetReserveFlatL(aCount);}
inline CArrayFixFlat<TAny>::CArrayFixFlat(TInt aRecordLength,TInt aGranularity)
	: CArrayFix<TAny>((TBufRep)CBufFlat::NewL,aRecordLength,aGranularity)
	{}
inline void CArrayFixFlat<TAny>::SetReserveL(TInt aCount)
	{SetReserveFlatL(aCount);}
inline void CArrayFixFlat<TInt>::SetReserveL(TInt aCount)
	{SetReserveFlatL(aCount);}
inline void CArrayFixFlat<TUid>::SetReserveL(TInt aCount)
	{SetReserveFlatL(aCount);}

// Template class CArrayFixSeg
template <class T>
inline CArrayFixSeg<T>::CArrayFixSeg(TInt aGranularity)
	: CArrayFix<T>((TBufRep)CBufSeg::NewL,aGranularity)
	{}
inline CArrayFixSeg<TAny>::CArrayFixSeg(TInt aRecordLength,TInt aGranularity)
	: CArrayFix<TAny>((TBufRep)CBufSeg::NewL,aRecordLength,aGranularity)
	{}

// Template class CArrayPtr
template <class T>
inline CArrayPtr<T>::CArrayPtr(TBufRep aRep,TInt aGranularity)
	: CArrayFix<T*>(aRep,aGranularity)
	{}
template <class T>
void CArrayPtr<T>::ResetAndDestroy()
	{
	for (TInt i=0;i<Count();++i)
		delete At(i);
	Reset();
	}

// Template class CArrayPtrFlat
template <class T>
inline CArrayPtrFlat<T>::CArrayPtrFlat(TInt aGranularity)
	: CArrayPtr<T>((TBufRep)CBufFlat::NewL,aGranularity)
	{}
template <class T>
inline void CArrayPtrFlat<T>::SetReserveL(TInt aCount)
	{SetReserveFlatL(aCount);}

// Template class CArrayPtrSeg
template <class T>
inline CArrayPtrSeg<T>::CArrayPtrSeg(TInt aGranularity)
	: CArrayPtr<T>((TBufRep)CBufSeg::NewL,aGranularity)
	{}

// Class CArrayVarBase
inline TInt CArrayVarBase::Count() const
	{return(iCount);}

// Template class CArrayVar
template <class T>
inline CArrayVar<T>::CArrayVar(TBufRep aRep,TInt aGranularity)
	: CArrayVarBase(aRep,aGranularity)
	{}
template <class T>
inline const T &CArrayVar<T>::operator[](TInt anIndex) const
	{return(*((const T *)CArrayVarBase::At(anIndex)));}
template <class T>
inline T &CArrayVar<T>::operator[](TInt anIndex)
	{return(*((T *)CArrayVarBase::At(anIndex)));}
template <class T>
inline const T &CArrayVar<T>::At(TInt anIndex) const
	{return(*((const T *)CArrayVarBase::At(anIndex)));}
template <class T>
inline T &CArrayVar<T>::At(TInt anIndex)
	{return(*((T *)CArrayVarBase::At(anIndex)));}
template <class T>
inline void CArrayVar<T>::AppendL(const T &aRef,TInt aLength)
	{CArrayVarBase::InsertL(Count(),&aRef,aLength);}
template <class T>
inline T &CArrayVar<T>::ExpandL(TInt anIndex,TInt aLength)
	{return(*new(CArrayVarBase::ExpandL(anIndex,aLength)) T);}
template <class T>
inline T &CArrayVar<T>::ExtendL(TInt aLength)
	{return(*new(CArrayVarBase::ExpandL(Count(),aLength)) T);}
template <class T>
inline TInt CArrayVar<T>::Find(const T &aRef,TKeyArrayVar &aKey,TInt &anIndex) const
	{return(CArrayVarBase::Find(&aRef,aKey,anIndex));}
template <class T>
inline TInt CArrayVar<T>::FindIsq(const T &aRef,TKeyArrayVar &aKey,TInt &anIndex) const
	{return(CArrayVarBase::FindIsq(&aRef,aKey,anIndex));}
template <class T>
inline void CArrayVar<T>::InsertL(TInt anIndex,const T &aRef,TInt aLength)
	{CArrayVarBase::InsertL(anIndex,&aRef,aLength);}
template <class T>
inline TInt CArrayVar<T>::InsertIsqL(const T &aRef,TInt aLength,TKeyArrayVar &aKey)
	{return(CArrayVarBase::InsertIsqL(&aRef,aLength,aKey));}
template <class T>
inline TInt CArrayVar<T>::InsertIsqAllowDuplicatesL(const T &aRef,TInt aLength,TKeyArrayVar &aKey)
	{return(CArrayVarBase::InsertIsqAllowDuplicatesL(&aRef,aLength,aKey));}
template <class T>
inline const TArray<T> CArrayVar<T>::Array() const
	{return(TArray<T>(CountR,AtR,this));}
inline const TAny *CArrayVar<TAny>::At(TInt anIndex) const
	{return(CArrayVarBase::At(anIndex));}
inline CArrayVar<TAny>::CArrayVar(TBufRep aRep,TInt aGranularity)
	: CArrayVarBase(aRep,aGranularity)
	{}
inline TAny *CArrayVar<TAny>::At(TInt anIndex)
	{return(CArrayVarBase::At(anIndex));}
inline void CArrayVar<TAny>::AppendL(const TAny *aPtr,TInt aLength)
	{CArrayVarBase::InsertL(Count(),aPtr,aLength);}
inline TAny *CArrayVar<TAny>::ExtendL(TInt aLength)
	{return(CArrayVarBase::ExpandL(Count(),aLength));}

// Template class CArrayVarFlat
template <class T>
inline CArrayVarFlat<T>::CArrayVarFlat(TInt aGranularity)
	: CArrayVar<T>((TBufRep)CBufFlat::NewL,aGranularity)
	{}

// Template class CArrayVarSeg
template <class T>
inline CArrayVarSeg<T>::CArrayVarSeg(TInt aGranularity)
	: CArrayVar<T>((TBufRep)CBufSeg::NewL,aGranularity)
	{}

// Class CArrayPakBase
inline TInt CArrayPakBase::Count() const
	{return(iCount);}

// Template class CArrayPak
template <class T>
inline CArrayPak<T>::CArrayPak(TBufRep aRep,TInt aGranularity)
	: CArrayPakBase(aRep,aGranularity)
	{}
template <class T>
inline const T &CArrayPak<T>::operator[](TInt anIndex) const
	{return(*((const T *)CArrayPakBase::At(anIndex)));}
template <class T>
inline T &CArrayPak<T>::operator[](TInt anIndex)
	{return(*((T *)CArrayPakBase::At(anIndex)));}
template <class T>
inline const T &CArrayPak<T>::At(TInt anIndex) const
	{return(*((const T *)CArrayPakBase::At(anIndex)));}
template <class T>
inline T &CArrayPak<T>::At(TInt anIndex)
	{return(*((T *)CArrayPakBase::At(anIndex)));}
template <class T>
inline void CArrayPak<T>::AppendL(const T &aRef,TInt aLength)
	{CArrayPakBase::InsertL(Count(),&aRef,aLength);}
template <class T>
inline T &CArrayPak<T>::ExpandL(TInt anIndex,TInt aLength)
	{return(*new(CArrayPakBase::ExpandL(anIndex,aLength)) T);}
template <class T>
inline T &CArrayPak<T>::ExtendL(TInt aLength)
	{return(*new(CArrayPakBase::ExpandL(Count(),aLength)) T);}
template <class T>
inline TInt CArrayPak<T>::Find(const T &aRef,TKeyArrayPak &aKey,TInt &anIndex) const
	{return(CArrayPakBase::Find(&aRef,aKey,anIndex));}
template <class T>
inline TInt CArrayPak<T>::FindIsq(const T &aRef,TKeyArrayPak &aKey,TInt &anIndex) const
	{return(CArrayPakBase::FindIsq(&aRef,aKey,anIndex));}
template <class T>
inline void CArrayPak<T>::InsertL(TInt anIndex,const T &aRef,TInt aLength)
	{CArrayPakBase::InsertL(anIndex,&aRef,aLength);}
template <class T>
inline TInt CArrayPak<T>::InsertIsqL(const T &aRef,TInt aLength,TKeyArrayPak &aKey)
	{return(CArrayPakBase::InsertIsqL(&aRef,aLength,aKey));}
template <class T>
inline TInt CArrayPak<T>::InsertIsqAllowDuplicatesL(const T &aRef,TInt aLength,TKeyArrayPak &aKey)
	{return(CArrayPakBase::InsertIsqAllowDuplicatesL(&aRef,aLength,aKey));}
template <class T>
inline const TArray<T> CArrayPak<T>::Array() const
	{return(TArray<T>(CountR,AtR,this));}
inline CArrayPak<TAny>::CArrayPak(TBufRep aRep,TInt aGranularity)
	: CArrayPakBase(aRep,aGranularity)
	{}
inline const TAny *CArrayPak<TAny>::At(TInt anIndex) const
	{return(CArrayPakBase::At(anIndex));}
inline TAny *CArrayPak<TAny>::At(TInt anIndex)
	{return(CArrayPakBase::At(anIndex));}
inline void CArrayPak<TAny>::AppendL(const TAny *aPtr,TInt aLength)
	{CArrayPakBase::InsertL(Count(),aPtr,aLength);}
inline TAny *CArrayPak<TAny>::ExtendL(TInt aLength)
	{return(CArrayPakBase::ExpandL(Count(),aLength));}

// Template class CArrayPakFlat
template <class T>
inline CArrayPakFlat<T>::CArrayPakFlat(TInt aGranularity)
	: CArrayPak<T>((TBufRep)CBufFlat::NewL,aGranularity)
	{}

// Class CObject
inline TInt CObject::UniqueID() const
	{return(iContainer->UniqueID());}
inline TInt CObject::AccessCount() const
	{return(iAccessCount);}
inline void CObject::Inc()
	{iAccessCount++;}
inline void CObject::Dec()
	{iAccessCount--;}
inline CObject * CObject::Owner() const
	{return(iOwner);}
inline void CObject::SetOwner(CObject *anOwner)
	{iOwner=anOwner;}

// class CObjectIx
inline TInt CObjectIx::Count() const
	{return iHighWaterMark;}
inline TInt CObjectIx::ActiveCount() const
	{return iNumEntries;}

// class CObjectCon
inline TInt CObjectCon::UniqueID() const
	{return iUniqueID;}
inline TInt CObjectCon::Count() const
	{return iCount;}

// class CCirBufBase
inline TInt CCirBufBase::Count() const
	{return(iCount);}
inline TInt CCirBufBase::Length() const
	{return(iLength);}

// Template class CCirBuf
template <class T>
inline CCirBuf<T>::CCirBuf()
	: CCirBufBase(sizeof(T))
	{}
template <class T>
inline TInt CCirBuf<T>::Add(const T *aPtr)
	{return(DoAdd((const TUint8 *)aPtr));}
template <class T>
inline TInt CCirBuf<T>::Add(const T *aPtr,TInt aCount)
	{return(DoAdd((const TUint8 *)aPtr,aCount));}
template <class T>
inline TInt CCirBuf<T>::Remove(T *aPtr)
	{return(DoRemove((TUint8 *)aPtr));}
template <class T>
inline TInt CCirBuf<T>::Remove(T *aPtr,TInt aCount)
	{return(DoRemove((TUint8 *)aPtr,aCount));}

// Class CActive
inline TBool CActive::IsActive() const
	{return(iActive);}
inline TBool CActive::IsAdded() const
	{return(iLink.iNext!=NULL);}
inline TInt CActive::Priority() const
	{return iLink.iPriority;}

// class CDeltaTimer
inline TDeltaTimerEntry::TDeltaTimerEntry(TCallBack& aCallback)
	{iCallBack=aCallback;}
inline TDeltaTimerEntry::TDeltaTimerEntry()
	{}
inline void TDeltaTimerEntry::Set(TCallBack& aCallback)
	{iCallBack=aCallback;}
inline TTimeIntervalMicroSeconds32 CDeltaTimer::Granularity() const
	{return iGranularity;}

// Class CServer
inline const RMessage &CServer::Message() const
	{return iServer.Message();}

// Class CSharableSession
inline const CServer *CSharableSession::Server() const
	{return iServer;}
inline const RMessage& CSharableSession::Message() const
	{return iServer->Message();}
// Class CSession
inline const RThread &CSession::Client() const
	{return iClient;}

// Class CAsyncOneShot
inline RThread& CAsyncOneShot::Thread()
	{ return iThread; }

// Class CActiveScheduler
inline TInt CActiveScheduler::Level() const
	{return(iLevel);}

// Class CleanupStack
#ifdef _DEBUG
inline void CleanupStack::Pop(TAny* aExpectedItem)
	{ CleanupStack::Check(aExpectedItem); CleanupStack::Pop(); }
inline void CleanupStack::Pop(TInt aCount, TAny* aLastExpectedItem)
	{
	if (--aCount)
		CleanupStack::Pop(aCount);
	CleanupStack::Check(aLastExpectedItem);
	CleanupStack::Pop();
	}
inline void CleanupStack::PopAndDestroy(TAny* aExpectedItem)
	{ CleanupStack::Check(aExpectedItem); CleanupStack::PopAndDestroy(); }
inline void CleanupStack::PopAndDestroy(TInt aCount, TAny* aLastExpectedItem)
	{
	if (--aCount)
		CleanupStack::PopAndDestroy(aCount);
	CleanupStack::Check(aLastExpectedItem);
	CleanupStack::PopAndDestroy();
	}
#else
inline void CleanupStack::Pop(TAny*)
	{ CleanupStack::Pop(); }
inline void CleanupStack::Pop(TInt aCount, TAny*)
	{ CleanupStack::Pop(aCount); }
inline void CleanupStack::PopAndDestroy(TAny*)
	{ CleanupStack::PopAndDestroy(); }
inline void CleanupStack::PopAndDestroy(TInt aCount, TAny*)
	{ CleanupStack::PopAndDestroy(aCount); }
#endif

// Class TCleanupItem
inline TCleanupItem::TCleanupItem(TCleanupOperation anOperation)
	: iOperation(anOperation)
	{}
inline TCleanupItem::TCleanupItem(TCleanupOperation anOperation,TAny *aPtr)
	: iOperation(anOperation), iPtr(aPtr)
	{}

// Class TCleanupTrapHandler
inline CCleanup &TCleanupTrapHandler::Cleanup()
	{return(*iCleanup);}

// Class TAutoClose
template <class T>
inline TAutoClose<T>::~TAutoClose()
	{iObj.Close();}
template <class T>
inline void TAutoClose<T>::PushL()
	{CleanupStack::PushL(TCleanupItem(Close, (TAny *)&iObj));}
template <class T>
inline void TAutoClose<T>::Pop()
	{CleanupStack::Pop();}
template <class T>
void TAutoClose<T>::Close(TAny *aObj)
	{((T *)aObj)->Close();}

#ifndef __EPOC_CLEANUP_SUPPORT__
#define __EPOC_CLEANUP_SUPPORT__
// Template class CleanupDelete
template <class T>
inline void CleanupDelete<T>::PushL(T* aPtr)
	{CleanupStack::PushL(TCleanupItem(&Delete,aPtr));}
template <class T>
void CleanupDelete<T>::Delete(TAny *aPtr)
	{delete STATIC_CAST(T*,aPtr);}
template <class T>
inline void CleanupDeletePushL(T* aPtr)
	{CleanupDelete<T>::PushL(aPtr);}

// Template class CleanupClose
template <class T>
inline void CleanupClose<T>::PushL(T& aRef)
	{CleanupStack::PushL(TCleanupItem(&Close,&aRef));}
template <class T>
void CleanupClose<T>::Close(TAny *aPtr)
	{(STATIC_CAST(T*,aPtr))->Close();}
template <class T>
inline void CleanupClosePushL(T& aRef)
	{CleanupClose<T>::PushL(aRef);}

// Template class CleanupRelease
template <class T>
inline void CleanupRelease<T>::PushL(T& aRef)
	{CleanupStack::PushL(TCleanupItem(&Release,&aRef));}
template <class T>
void CleanupRelease<T>::Release(TAny *aPtr)
	{(STATIC_CAST(T*,aPtr))->Release();}
template <class T>
inline void CleanupReleasePushL(T& aRef)
	{CleanupRelease<T>::PushL(aRef);}
#endif // __EPOC_CLEANUP_SUPPORT__



