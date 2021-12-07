// PLPSVR.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

inline TInt CPlpSocketHandler::State() const
    { return iState; }

inline void CPlpSocketHandler::SetState(TInt aState)
    { iState = aState; }

inline RSocketServ& CPlpSocketHandler::SocketServ() const
    { return (RSocketServ&)iSS; }

inline TBool CPlpSocketHandler::IsSocketValid() const
    { return iSocket ? 1 : 0; }

inline TBool CPlpIo::IsWriting() const
    { return iWriter->IsActive(); }

inline TBool CPlpIo::IsReading() const
    { return IsActive(); }

inline TPlpTimerEntry::TPlpTimerEntry()
    { iTimer=0; }

inline TBool TPlpTimerEntry::IsQued() const
    { return iTimer != 0; }

inline void TPlpTimerEntry::Reset()
    { iTimer = 0; }

inline void TPlpTimerEntry::Deque()
    { iTimer->Remove(*this); iTimer=0; }

inline void TPlpTimerEntry::Enque(CDeltaTimer &aTimer, TTimeIntervalMicroSeconds32 aTimeInMicroSeconds)
    { iTimer = &aTimer; iTimer->Queue(aTimeInMicroSeconds, *this); }

// Client classes inlines
inline void MPlpIoNotifier::Write(TDes8 *aPdu)
    { iIO->Write(aPdu); }

inline TBool MPlpIoNotifier::IsWriting() const
    { return iIO->IsWriting(); }

inline void MPlpIoNotifier::CancelIo()
    { if(iIO) iIO->Cancel(); }

inline void MPlpIoNotifier::DeleteIo()
	{ if(iIO) {delete iIO;iIO=NULL;}; }

inline void MPlpIoNotifier::ReadIoL()
	{iIO->ReadL();}

inline void MPlpIoNotifier::SetIoSocketAndPriority(RSocket *aSocket,int aReaderPriority,int aWriterPriority)
	{
	iIO->SetSocket(aSocket);
	iIO->SetPriorities(aReaderPriority,aWriterPriority);
	}

inline void MPlpIoNotifier::NewIoL(TPlpIoNewL aNewL)
	{iIO = aNewL(*this);}


inline MPlpClientManager& CPlpClient::Manager() const
    { return *iManager; }

inline TPlpClientInfo& CPlpClient::Info() const
    { return *iInfo; }

// Server classes inlines
inline TInt CPlpServer::SessionCount() const
    { return iSessionCount; }

inline RLibrary& CPlpServer::Library() const
    { return (RLibrary&)iLib; }

inline MPlpServerManager& CPlpServer::Manager() const
    { return *iManager; }

inline void CPlpServer::SetLib(const RLibrary &aLib)
    { iLib = aLib; }

inline void CPlpServer::DeferredDelete()
    { iDeleter->Call(); }

inline TPlpServInfo& CPlpServer::Info() const
    { return *iInfo; }

inline CPlpServer& CPlpSession::Server() const
    { return *iServer; }

inline void CPlpSession::Cancel()
    { CancelIo(); }

//////////////////////////////////////////////////////////////////////////////
//
// TPlpSockInfo
//
//////////////////////////////////////////////////////////////////////////////

inline TPlpSockInfo::TPlpSockInfo(TUint aAddrFamily, TUint aSockType, TUint aProtocol)
    { iAddrFamily=aAddrFamily; iSockType=aSockType; iProtocol=aProtocol; }

inline TPlpSockInfo::TPlpSockInfo()
    {}

//////////////////////////////////////////////////////////////////////////////
//
// TRemSvPtr
//
//////////////////////////////////////////////////////////////////////////////

inline TRemSvPtr::TRemSvPtr()
    : TPtr8(0, 0)
    { }

inline TRemSvPtr::TRemSvPtr(TUint8* iBuf, TInt aLength)
    : TPtr8(iBuf, aLength, aLength)
    { }

inline void TRemSvPtr::WSet(TRemSvPtr& aPtr, TInt anOffset)
    { WSet(aPtr, anOffset, aPtr.MaxLength()-anOffset); }

inline TUint16 TRemSvPtr::GetWord(TInt anOffset) const
	{ return SiboUtil::Get16((TUint8 *)iPtr+anOffset); }

inline TUint32 TRemSvPtr::GetLong(TInt anOffset) const
	{ return SiboUtil::Get32((TUint8 *)iPtr+anOffset); }

inline void TRemSvPtr::PutLong(TInt anOffset, TUint32 aVal)
	{ SiboUtil::Put32((TUint8 *)iPtr+anOffset, aVal); }

inline void TRemSvPtr::PutWord(TInt anOffset, TUint16 aVal)
	{ SiboUtil::Put16((TUint8 *)iPtr+anOffset, aVal); }

// inline void SetStringZ(TPtrC8& aPtrC, const TText8* aString)
//    { aPtrC.Set(aString, User::StringLength(aString)); }


inline TInt64 TRemSvPtr::GetInt64(TInt aOffset)
    { return TInt64(GetLong(aOffset+4), GetLong(aOffset)); }

inline void TRemSvPtr::PutInt64(TInt aOffset, TInt64 aVal)
    { PutLong(aOffset, aVal.Low()); PutLong(aOffset+4, aVal.High()); }

void TRemSvPtr::SetDesLength32(TInt aOffset, TInt aLength)
    { PutWord(aOffset, (TUint16)aLength); }

