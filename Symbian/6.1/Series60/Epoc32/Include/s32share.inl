// S32SHARE.INL
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//

// Class TStreamMark
inline TStreamMark::TStreamMark()
	: iPos(KStreamBeginning-1)
	{}
inline TStreamMark::TStreamMark(TStreamPos aPos)
	: iPos(aPos)
	{
#if defined (_DEBUG)
	__DbgChkPos(aPos);
#endif
	}
inline TStreamMark& TStreamMark::operator=(TStreamPos aPos)
	{
#if defined (_DEBUG)
	__DbgChkPos(aPos);
#endif
	iPos=aPos;
	return *this;
	}
inline TStreamMark::operator TStreamMark*()
	{return this;}
inline TStreamMark::operator const TStreamMark*() const
	{return this;}
inline TBool TStreamMark::operator==(const TStreamMark& aMark) const
	{return this==&aMark;}
inline TBool TStreamMark::operator==(const TStreamMark* aPtr) const
	{return this==aPtr;}
inline TBool TStreamMark::operator!=(const TStreamMark& aMark) const
	{return this!=&aMark;}
inline TBool TStreamMark::operator!=(const TStreamMark* aPtr) const
	{return this!=aPtr;}
inline TBool TStreamMark::IsEmpty() const
	{return iPos<KStreamBeginning;}
inline void TStreamMark::Clear()
	{iPos=KStreamBeginning-1;}
inline TStreamPos TStreamMark::Position() const
	{
#if defined (_DEBUG)
	__DbgChkPos(iPos);
#endif
	return iPos;
	}
inline TBool TStreamMark::IsWith(TStreamExchange& aHost) const
	{return aHost.RefersTo(*this);}
inline TBool TStreamMark::RelatesTo(TStreamExchange& aHost) const
	{return iPos>=KStreamBeginning||aHost.RefersTo(*this);}
inline void TStreamMark::Withdraw(TStreamExchange& aHost)
	{aHost.Drop(*this);}
inline void TStreamMark::ExtractL(TStreamExchange& aHost)
	{aHost.GetL(*this);}
inline TInt TStreamMark::ReadL(TStreamExchange& aHost,TAny* aPtr,TInt aMaxLength)
	{return aHost.DoReadL(aPtr,aMaxLength,*this);}
inline TInt TStreamMark::ReadL(TStreamExchange& aHost,TDes8& aDes,TInt aMaxLength,TRequestStatus& aStatus)
	{return aHost.DoReadL(aDes,aMaxLength,aStatus,*this);}
inline TStreamTransfer TStreamMark::ReadL(TStreamExchange& aHost,MStreamInput& anInput,TStreamTransfer aTransfer)
	{return aHost.DoReadL(anInput,aTransfer,*this);}
inline TInt TStreamMark::ReadL(TStreamExchange& aHost,MStreamInput& anInput,TInt aMaxLength)
	{return aMaxLength-aHost.DoReadL(anInput,TStreamTransfer(aMaxLength),*this).Left();}
inline void TStreamMark::ReadL(TStreamExchange& aHost,MStreamInput& anInput)
	{aHost.DoReadL(anInput,KStreamUnlimited,*this);}
inline void TStreamMark::WriteL(TStreamExchange& aHost,const TAny* aPtr,TInt aLength)
	{aHost.DoWriteL(aPtr,aLength,*this);}
inline TInt TStreamMark::WriteL(TStreamExchange& aHost,const TDesC8& aDes,TInt aMaxLength,TRequestStatus& aStatus)
	{return aHost.DoWriteL(aDes,aMaxLength,aStatus,*this);}
inline TStreamTransfer TStreamMark::WriteL(TStreamExchange& aHost,MStreamOutput& anOutput,TStreamTransfer aTransfer)
	{return aHost.DoWriteL(anOutput,aTransfer,*this);}
inline TInt TStreamMark::WriteL(TStreamExchange& aHost,MStreamOutput& anOutput,TInt aMaxLength)
	{return aMaxLength-aHost.DoWriteL(anOutput,TStreamTransfer(aMaxLength),*this).Left();}
inline void TStreamMark::WriteL(TStreamExchange& aHost,MStreamOutput& anOutput)
	{aHost.DoWriteL(anOutput,KStreamUnlimited,*this);}
inline void TStreamMark::SeekL(TStreamExchange& aHost,TStreamPos aPos)
	{aHost.DoSeekL(*this,EStreamBeginning,aPos.Offset());}
inline TStreamPos TStreamMark::SeekL(TStreamExchange& aHost,TStreamLocation aLocation,TInt anOffset)
	{return aHost.DoSeekL(*this,aLocation,anOffset);}
inline TStreamPos TStreamMark::SeekL(TStreamExchange& aHost,TInt anOffset)
	{return aHost.DoSeekL(*this,EStreamMark,anOffset);}
inline TStreamPos TStreamMark::TellL(TStreamExchange& aHost) const
	{return aHost.DoSeekL(CONST_CAST(TStreamMark&,*this),EStreamMark,0);}
inline TBool operator==(const TStreamMark* aPtr,const TStreamMark& aMark)
	{return aMark==aPtr;}
inline TBool operator!=(const TStreamMark* aPtr,const TStreamMark& aMark)
	{return aMark!=aPtr;}

// Class TStreamExchange
inline TStreamExchange::TStreamExchange()
	: iHost(NULL),iRMrk(NULL),iWMrk(NULL)
	{}
inline TStreamExchange::TStreamExchange(MStreamBuf* aHost)
	: iHost(aHost),iRMrk(NULL),iWMrk(NULL)
	{}
inline void TStreamExchange::Share(MStreamBuf* aHost)
	{iHost=aHost;}
inline TBool TStreamExchange::IsActive() const
	{return iHost!=NULL;}
	
// Class RShareBuf
inline void RShareBuf::Open(TStreamExchange& aHost,TInt aMode)
	{Open(aHost,KStreamBeginning,aMode);}

// Class RShareWriteStream
inline RShareWriteStream::RShareWriteStream(const MExternalizer<TStreamRef>& anExter)
	: RWriteStream(anExter)
	{}

