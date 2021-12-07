// ES_MBUF.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

//
// Buffer Manager for Protocols
//

////////////////////////////////////////////////////////////////////////////////
// MBUF
////////////////////////////////////////////////////////////////////////////////

inline void RMBuf::FillZ()
	{ Mem::FillZ(iBuffer, iSize); }

inline TInt RMBuf::Size() const
	{ return iSize; }

inline TUint8 *RMBuf::Buffer()
	{ return iBuffer; }

inline TUint8 *RMBuf::Ptr()
	{ return iBuffer+iOffset; }

inline TUint8 *RMBuf::EndPtr()
	{ return Ptr()+iLength; }

inline const TUint8 *RMBuf::Buffer() const
	{ return iBuffer; }

inline const TUint8 *RMBuf::Ptr() const
	{ return iBuffer+iOffset; }

inline const TUint8 *RMBuf::EndPtr() const
	{ return Ptr()+iLength; }

inline TInt RMBuf::Offset() const
	{ return iOffset; }

inline TInt RMBuf::Length() const
	{ return iLength; }

inline TInt RMBuf::End() const
	{ return iOffset+iLength; }

inline TMBufType RMBuf::Type() const
	{ return iType; }

inline RMBuf* RMBuf::Next()
	{ return iNext; }

inline RMBufChain& RMBuf::NextPkt()
	{ return iNextPkt; }

inline const RMBuf* RMBuf::Next() const
	{ return iNext; }

inline const RMBufChain& RMBuf::NextPkt() const
	{ return iNextPkt; }

inline void RMBuf::Link(RMBuf* aBuf)
	{ iNext = aBuf; }

inline void RMBuf::Unlink()
	{ iNext = NULL; }

inline void RMBuf::LinkPkt(RMBufChain &aChain)
	{ iNextPkt = aChain; }

inline void RMBuf::UnlinkPkt()
	{ iNextPkt.Init(); }

inline void RMBuf::SetType(TMBufType aType)
	{ iType = aType; }

inline void RMBuf::SetOffset(TInt aOffset)
	{ iOffset = aOffset; }

inline void RMBuf::SetLength(TInt aLength)
	{ iLength = aLength; }

inline void RMBuf::SetData(TInt aOffset, TInt aLength)
	{ SetOffset(aOffset);  SetLength(aLength); }

inline void RMBuf::AdjustStart(TInt aLen)
	{ iOffset += aLen;  iLength -= aLen; }

inline void RMBuf::AdjustEnd(TInt aLen)
	{ iLength += aLen; }

#ifdef _DEBUG_SOCKET_FUNCTIONS
inline void RMBuf::Put(TUint8 aVal, TInt aOffset)
	{ __DbgPut(aVal, aOffset); }
inline TUint8 RMBuf::Get(TInt aOffset) const
	{ return __DbgGet(aOffset); }
#else
inline void RMBuf::Put(TUint8 aVal, TInt aOffset)
	{ *(Ptr()+aOffset) = aVal; }
inline TUint8 RMBuf::Get(TInt aOffset) const
	{ return *(Ptr()+aOffset); }
#endif

////////////////////////////////////////////////////////////////////////////////
// MBUF ITERATOR
////////////////////////////////////////////////////////////////////////////////

inline TMBufIter::TMBufIter(RMBuf* aChain)
	: iCurrent(aChain)
	{ }

inline TMBufIter::TMBufIter(RMBufChain &aChain)
	: iCurrent(aChain.First()) // depends upon RMBufChain::operator RMBuf* ()
	{ }

inline TMBufIter& TMBufIter::operator =(RMBuf* aChain)
	{ iCurrent = aChain; return *this; }

inline TMBufIter& TMBufIter::operator =(RMBufChain &aChain)
	{ iCurrent = aChain.First(); return *this; }

inline RMBuf* TMBufIter::operator ++(TInt)
	{ RMBuf* m; if (m = iCurrent, m!=NULL) iCurrent=iCurrent->Next(); return m; }

inline TMBufIter::operator RMBuf*()
	{ return iCurrent; }

inline TBool TMBufIter::More()
	{ return iCurrent!=NULL; }

inline RMBuf* TMBufIter::MBuf()
	{ return iCurrent; }

////////////////////////////////////////////////////////////////////////////////
// MBUF QUEUE
////////////////////////////////////////////////////////////////////////////////

inline RMBufQ::RMBufQ()
	{ Init(); }

inline TBool RMBufQ::IsEmpty()
	{ return iNext==NULL; }

inline RMBuf* RMBufQ::First()
	{ return iNext; }

inline RMBuf* RMBufQ::Last()
	{ return iLast; }

inline RMBufQ::RMBufQ(RMBuf* aFirst, RMBuf* aLast)
	{ iNext = aFirst; iLast = aLast; }

////////////////////////////////////////////////////////////////////////////////
// MBUF PACKET QUEUE
////////////////////////////////////////////////////////////////////////////////

inline TBool RMBufPktQ::IsEmpty() const
	{ return iNext.IsEmpty(); }

inline const RMBufChain& RMBufPktQ::First() const
	 { return iNext; }

inline const RMBufChain& RMBufPktQ::Last() const
	 { return iLast; }

////////////////////////////////////////////////////////////////////////////////
// MBUF PACKET QUEUE ITREATOR
////////////////////////////////////////////////////////////////////////////////

inline TMBufPktQIter::TMBufPktQIter(RMBufPktQ& aQueue)
	: iQueue(&aQueue), iCurrent(aQueue.First())
	{ }

inline void TMBufPktQIter::Set(RMBufPktQ& aQueue)
	{ iQueue = &aQueue; SetToFirst(); }

inline void TMBufPktQIter::SetToFirst()
	{ iCurrent = iQueue->First(); iPrev.Init(); }

inline TBool TMBufPktQIter::More() const
	{ return !iCurrent.IsEmpty(); }

inline const RMBufChain& TMBufPktQIter::Current() const
	{ return iCurrent; }

////////////////////////////////////////////////////////////////////////////////
// MBUF CHAIN
////////////////////////////////////////////////////////////////////////////////

inline RMBufChain::RMBufChain()
	{ iNext = NULL; }

inline RMBufChain::RMBufChain(RMBuf* aChain) : iNext(aChain)
	{ iNext = aChain; }

inline RMBuf* RMBufChain::First()
	{ return iNext; }

inline const RMBuf* RMBufChain::First() const
	{ return iNext; }

inline RMBufChain &RMBufChain::operator =(RMBuf* aChain)
	{ iNext = aChain; return *this; }

inline void RMBufChain::Init()
	{ iNext = NULL;	}

inline TBool RMBufChain::IsEmpty() const
	{ return iNext==NULL; }

inline void RMBufChain::Link(RMBufChain &aChain)
	{ if (!IsEmpty()) iNext->LinkPkt(aChain); }

inline void RMBufChain::Unlink()
	{ if (!IsEmpty()) iNext->UnlinkPkt(); }

inline RMBufChain& RMBufChain::Next()
	{ return IsEmpty() ? *this : iNext->NextPkt(); }

inline const RMBufChain& RMBufChain::Next() const
	{ return IsEmpty() ? *this : iNext->NextPkt(); }

inline TBool RMBufChain::Goto(TInt anOffset, RMBuf* &resBuf, TInt &resOffset, TInt &resLength) const
	{ RMBuf* prev;  return Goto(anOffset, resBuf, resOffset, resLength, prev); }
