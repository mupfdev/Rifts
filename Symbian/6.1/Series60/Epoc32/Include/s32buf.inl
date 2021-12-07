// S32BUF.INL
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//

// Class TStreamPos
inline TStreamPos::TStreamPos(TInt anOffset)
	: iOff(anOffset)
	{}
inline TBool TStreamPos::operator==(TStreamPos aPos) const
	{return iOff==aPos.iOff;}
inline TBool TStreamPos::operator!=(TStreamPos aPos) const
	{return iOff!=aPos.iOff;}
inline TBool TStreamPos::operator<(TStreamPos aPos) const
	{return iOff<aPos.iOff;}
inline TBool TStreamPos::operator<=(TStreamPos aPos) const
	{return iOff<=aPos.iOff;}
inline TBool TStreamPos::operator>(TStreamPos aPos) const
	{return iOff>aPos.iOff;}
inline TBool TStreamPos::operator>=(TStreamPos aPos) const
	{return iOff>=aPos.iOff;}
inline TInt TStreamPos::operator-(TStreamPos aPos) const
	{return iOff-aPos.iOff;}
inline TStreamPos TStreamPos::operator+(TInt anOffset) const
	{return TStreamPos(iOff+anOffset);}
inline TStreamPos TStreamPos::operator-(TInt anOffset) const
	{return TStreamPos(iOff-anOffset);}
inline TStreamPos& TStreamPos::operator+=(TInt anOffset)
	{iOff+=anOffset;return *this;}
inline TStreamPos& TStreamPos::operator-=(TInt anOffset)
	{iOff-=anOffset;return *this;}
inline TInt TStreamPos::Offset() const
	{return iOff;}
inline TStreamPos operator+(TInt anOffset,TStreamPos aPos)
	{return aPos+anOffset;}

// Class TStreamTransfer
inline TStreamTransfer::TStreamTransfer(TInt aMaxLength)
	: iVal(aMaxLength)
	{
#if defined (_DEBUG)
	__DbgChkNonNegative(aMaxLength);
#endif
	}
inline TStreamTransfer::TStreamTransfer(TUnlimited)
	: iVal(-1)
	{}
inline TBool TStreamTransfer::operator==(TInt aLength) const
	{
#if defined (_DEBUG)
	__DbgChkNonNegative(aLength);
#endif
	return iVal==aLength;
	}
inline TBool TStreamTransfer::operator>(TInt aLength) const
	{
#if defined (_DEBUG)
	__DbgChkNonNegative(aLength);
#endif
	return TUint(iVal)>TUint(aLength);
	}
inline TStreamTransfer TStreamTransfer::operator-(TInt aLength) const
	{
#if defined (_DEBUG)
	__DbgChkNonNegative(aLength);
#endif
	return iVal<0?*this:TStreamTransfer(iVal-aLength);
	}
inline TInt TStreamTransfer::operator[](TInt aMaxLength) const
	{return *this>aMaxLength?aMaxLength:iVal;}
inline TStreamTransfer& TStreamTransfer::operator-=(TInt aLength)
	{
#if defined (_DEBUG)
	__DbgChkNonNegative(aLength);
#endif
	if (iVal>=0)
		{
		iVal-=aLength;
#if defined (_DEBUG)
		__DbgChkNonNegative(iVal);
#endif
		}
	return *this;
	}
inline TInt TStreamTransfer::Left() const
	{
#if defined (_DEBUG)
	__DbgChkNonNegative(iVal);
#endif
	return iVal;
	}
inline TBool operator==(TInt aLength,TStreamTransfer aTransfer)
	{return aTransfer==aLength;}
inline TBool operator<(TInt aLength,TStreamTransfer aTransfer)
	{return aTransfer>aLength;}

// Class MStreamBuf
inline void MStreamBuf::Release()
	{DoRelease();}
inline void MStreamBuf::SynchL()
	{DoSynchL();}
inline TInt MStreamBuf::ReadL(TAny* aPtr,TInt aMaxLength)
	{return DoReadL(aPtr,aMaxLength);}
inline TInt MStreamBuf::ReadL(TDes8& aDes,TInt aMaxLength,TRequestStatus& aStatus)
	{return DoReadL(aDes,aMaxLength,aStatus);}
inline TStreamTransfer MStreamBuf::ReadL(MStreamInput& anInput,TStreamTransfer aTransfer)
	{return DoReadL(anInput,aTransfer);}
inline void MStreamBuf::ReadL(MStreamInput& anInput)
	{DoReadL(anInput,KStreamUnlimited);}
inline void MStreamBuf::WriteL(const TAny* aPtr,TInt aLength)
	{DoWriteL(aPtr,aLength);}
inline TInt MStreamBuf::WriteL(const TDesC8& aDes,TInt aMaxLength,TRequestStatus& aStatus)
	{return DoWriteL(aDes,aMaxLength,aStatus);}
inline TStreamTransfer MStreamBuf::WriteL(MStreamOutput& anOutput,TStreamTransfer aTransfer)
	{return DoWriteL(anOutput,aTransfer);}
inline void MStreamBuf::WriteL(MStreamOutput& anOutput)
	{DoWriteL(anOutput,KStreamUnlimited);}
inline void MStreamBuf::SeekL(TMark aMark,TStreamPos aPos)
	{DoSeekL(aMark,EStreamBeginning,aPos.Offset());}
inline TStreamPos MStreamBuf::SeekL(TMark aMark,TStreamLocation aLocation,TInt anOffset)
	{return DoSeekL(aMark,aLocation,anOffset);}
inline TStreamPos MStreamBuf::SeekL(TRead,TStreamLocation aLocation,TInt anOffset)
	{return DoSeekL(ERead,aLocation,anOffset);}
inline TStreamPos MStreamBuf::SeekL(TWrite,TStreamLocation aLocation,TInt anOffset)
	{return DoSeekL(EWrite,aLocation,anOffset);}
inline TStreamPos MStreamBuf::SeekL(TRead,TInt anOffset)
	{return DoSeekL(ERead,EStreamMark,anOffset);}
inline TStreamPos MStreamBuf::SeekL(TWrite,TInt anOffset)
	{return DoSeekL(EWrite,EStreamMark,anOffset);}
inline TStreamPos MStreamBuf::TellL(TRead) const
	{return CONST_CAST(MStreamBuf*,this)->DoSeekL(ERead,EStreamMark,0);}
inline TStreamPos MStreamBuf::TellL(TWrite) const
	{return CONST_CAST(MStreamBuf*,this)->DoSeekL(EWrite,EStreamMark,0);}
inline TInt MStreamBuf::SizeL() const
	{return CONST_CAST(MStreamBuf*,this)->DoSeekL(0,EStreamEnd,0).Offset();}

// Class TStreamBuf
inline void TStreamBuf::SetBuf(TRead,TUint8* aPtr,TUint8* anEnd)
	{iRPtr=aPtr;iREnd=anEnd;}
inline void TStreamBuf::SetBuf(TWrite,TUint8* aPtr,TUint8* anEnd)
	{iWPtr=aPtr;iWEnd=anEnd;}
inline void TStreamBuf::SetPtr(TRead,TUint8* aPtr)
	{iRPtr=aPtr;}
inline void TStreamBuf::SetPtr(TWrite,TUint8* aPtr)
	{iWPtr=aPtr;}
inline void TStreamBuf::SetEnd(TRead,TUint8* anEnd)
	{iREnd=anEnd;}
inline void TStreamBuf::SetEnd(TWrite,TUint8* anEnd)
	{iWEnd=anEnd;}
inline TUint8* TStreamBuf::Ptr(TRead) const
	{return iRPtr;}
inline TUint8* TStreamBuf::Ptr(TWrite) const
	{return iWPtr;}
inline TUint8* TStreamBuf::End(TRead) const
	{return iREnd;}
inline TUint8* TStreamBuf::End(TWrite) const
	{return iWEnd;}
inline TInt TStreamBuf::Avail(TRead) const
	{return iREnd-iRPtr;}
inline TInt TStreamBuf::Avail(TWrite) const
	{return iWEnd-iWPtr;}

// Class TStreamFilter
inline void TStreamFilter::Set(MStreamBuf* aHost,TInt aMode)
	{
#if defined (_DEBUG)
	__DbgChkMode(aMode);
#endif
	iHost=aHost;iMode=aMode;
	}
inline void TStreamFilter::Committed()
	{iMode&=~EWrite;}
inline TBool TStreamFilter::IsCommitted() const
	{return iHost==NULL||!(iMode&EWrite);}

