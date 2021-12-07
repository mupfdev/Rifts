// S32STOR.INL
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//

// Class CStreamStore
inline TStreamId CStreamStore::ExtendL()
	{return DoExtendL();}
inline void CStreamStore::CommitL()
	{DoCommitL();}
inline void CStreamStore::RevertL()
	{DoRevertL();}

// Class CPersistentStore
inline CPersistentStore::CPersistentStore()
//	: iRoot(KNullStreamId)
	{}
inline TStreamId CPersistentStore::Root() const
	{return iRoot;}
inline void CPersistentStore::SetRootL(TStreamId anId)
	{DoSetRootL(anId);}

// Class RStoreReclaim
inline RStoreReclaim::RStoreReclaim()
	: iCol(NULL)
	{}
inline void RStoreReclaim::Close()
	{Release();}
inline TInt RStoreReclaim::Available() const
	{return CONST_CAST(TPckgBuf<TInt>&,iAvail)();}

// Class CEmbeddedStore
inline TStreamPos CEmbeddedStore::Position(TStreamId anId)
	{return TStreamPos(anId.Value());}
inline void CEmbeddedStore::Reattach(MStreamBuf* aHost)
	{iHost.Share(aHost);}
inline MStreamBuf* CEmbeddedStore::Host() const
	{return MUTABLE_CAST(TStreamExchange&,iHost).Host();}
inline TStreamPos CEmbeddedStore::Start() const
	{return iStart;}

// Class RDictionaryWriteStream
inline RDictionaryWriteStream::RDictionaryWriteStream(const MExternalizer<TStreamRef>& anExter)
	: RWriteStream(anExter)
	{}

// Class TStorePagePoolToken
inline TStorePagePoolToken::TStorePagePoolToken(TEmpty)
	: iHead(KNullStreamId),iAvail(KNullPageRef)
	{}
inline void TStorePagePoolToken::Touch()
	{iAvail=KNullPageRef;}
inline TBool TStorePagePoolToken::HasAvailable() const
	{return iAvail!=KNullPageRef;}
inline TBool TStorePagePoolToken::IsEmpty() const
	{return iHead==KNullStreamId;}

// Class RStorePagePool
inline void RStorePagePool::Release()
	{Purge();iStore=NULL;}
inline TBool RStorePagePool::IsDirty() const
	{return iDirty;}
inline void RStorePagePool::MarkCurrent()
	{iDirty=EFalse;}
inline void RStorePagePool::MarkDirty()	
	{iDirty=ETrue;}
inline TBool RStorePagePool::HasAvailable() const
	{return iAvail!=KNullPageRef;}
inline void RStorePagePool::Discard()
	{iAvail=KNullPageRef;}
inline TBool RStorePagePool::IsEmpty() const
	{return iHead==KNullStreamId;}

// Class MIncrementalCollector
inline void MIncrementalCollector::Close()
	{DoRelease();}
inline void MIncrementalCollector::Release()
	{DoRelease();}
inline void MIncrementalCollector::ResetL(TInt& aCount)
	{DoResetL(aCount);}
inline void MIncrementalCollector::NextL(TInt& aStep,TInt& aTotal)
	{DoNextL(aStep,aTotal);}
inline void MIncrementalCollector::NextL(TPckgBuf<TInt>& aStep,TRequestStatus& aStatus,TPckgBuf<TInt>& aTotal)
	{DoNextL(aStep,aStatus,aTotal);}

