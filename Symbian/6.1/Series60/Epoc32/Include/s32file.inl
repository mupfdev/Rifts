// S32FILE.INL
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//

// Class RFileBuf
inline void RFileBuf::Reset(TInt aSize)
	{Reset();iSize=aSize;}
inline void RFileBuf::Detach()
	{iFile=RFile();}
inline void RFileBuf::Reattach(RFile& aFile)
	{iFile=aFile;}
inline RFile& RFileBuf::File() const
	{return MUTABLE_CAST(RFile&,iFile);}

// Class RFileWriteStream
inline RFileWriteStream::RFileWriteStream(const MExternalizer<TStreamRef>& anExter)
	: RWriteStream(anExter)
	{}

// Class CFileStore
inline const TUidType& CFileStore::Type() const
	{return iType;}
inline void CFileStore::Reset()
	{iBuf.Reset();}
inline void CFileStore::Reset(TInt aSize)
	{iBuf.Reset(aSize);}
inline void CFileStore::Detach()
	{iBuf.Detach();}
inline void CFileStore::Reattach(RFile& aFile)
	{iBuf.Reattach(aFile);}
inline RFile& CFileStore::File() const
	{return iBuf.File();}
inline TStreamExchange& CFileStore::Host() const
	{return MUTABLE_CAST(TStreamExchange&,iHost);}
inline TBool CFileStore::IsHost(const MStreamBuf* aBuf) const
	{return aBuf==&iBuf;}
inline void CFileStore::SetSizeL(TInt aSize)
	{iBuf.SetSizeL(aSize);}

// Class CDirectFileStore
inline CDirectFileStore* CDirectFileStore::OpenL(RFs& aFs,const TDesC& aName,TUint aFileMode)
	{return STATIC_CAST(CDirectFileStore*,CFileStore::OpenL(aFs,aName,aFileMode,KDirectFileStoreFactoryFunction));}
inline CDirectFileStore* CDirectFileStore::OpenLC(RFs& aFs,const TDesC& aName,TUint aFileMode)
	{return STATIC_CAST(CDirectFileStore*,CFileStore::OpenLC(aFs,aName,aFileMode,KDirectFileStoreFactoryFunction));}
inline CDirectFileStore* CDirectFileStore::CreateL(RFs& aFs,const TDesC& aName,TUint aFileMode)
	{return STATIC_CAST(CDirectFileStore*,CFileStore::CreateL(aFs,aName,aFileMode,&DoNewL));}
inline CDirectFileStore* CDirectFileStore::CreateLC(RFs& aFs,const TDesC& aName,TUint aFileMode)
	{return STATIC_CAST(CDirectFileStore*,CFileStore::CreateLC(aFs,aName,aFileMode,&DoNewL));}
inline CDirectFileStore* CDirectFileStore::ReplaceL(RFs& aFs,const TDesC& aName,TUint aFileMode)
	{return STATIC_CAST(CDirectFileStore*,CFileStore::ReplaceL(aFs,aName,aFileMode,&DoNewL));}
inline CDirectFileStore* CDirectFileStore::ReplaceLC(RFs& aFs,const TDesC& aName,TUint aFileMode)
	{return STATIC_CAST(CDirectFileStore*,CFileStore::ReplaceLC(aFs,aName,aFileMode,&DoNewL));}
inline CDirectFileStore* CDirectFileStore::TempL(RFs& aFs,const TDesC& aPath,TFileName& aName,TUint aFileMode)
	{return STATIC_CAST(CDirectFileStore*,CFileStore::TempL(aFs,aPath,aName,aFileMode,&DoNewL));}
inline CDirectFileStore* CDirectFileStore::TempLC(RFs& aFs,const TDesC& aPath,TFileName& aName,TUint aFileMode)
	{return STATIC_CAST(CDirectFileStore*,CFileStore::TempLC(aFs,aPath,aName,aFileMode,&DoNewL));}
inline CDirectFileStore* CDirectFileStore::FromL(RFile& aFile)
	{return STATIC_CAST(CDirectFileStore*,CFileStore::FromL(aFile,KDirectFileStoreFactoryFunction));}
inline CDirectFileStore* CDirectFileStore::FromLC(RFile& aFile)
	{return STATIC_CAST(CDirectFileStore*,CFileStore::FromLC(aFile,KDirectFileStoreFactoryFunction));}
inline CDirectFileStore* CDirectFileStore::NewL(RFile& aFile)
	{return STATIC_CAST(CDirectFileStore*,CFileStore::NewL(aFile,&DoNewL));}
inline CDirectFileStore* CDirectFileStore::NewLC(RFile& aFile)
	{return STATIC_CAST(CDirectFileStore*,CFileStore::NewLC(aFile,&DoNewL));}

// Class CPermanentFileStore
inline CPermanentFileStore* CPermanentFileStore::OpenL(RFs& aFs,const TDesC& aName,TUint aFileMode)
	{return STATIC_CAST(CPermanentFileStore*,CFileStore::OpenL(aFs,aName,aFileMode,KPermanentFileStoreFactoryFunction));}
inline CPermanentFileStore* CPermanentFileStore::OpenLC(RFs& aFs,const TDesC& aName,TUint aFileMode)
	{return STATIC_CAST(CPermanentFileStore*,CFileStore::OpenLC(aFs,aName,aFileMode,KPermanentFileStoreFactoryFunction));}
inline CPermanentFileStore* CPermanentFileStore::CreateL(RFs& aFs,const TDesC& aName,TUint aFileMode)
	{return STATIC_CAST(CPermanentFileStore*,CFileStore::CreateL(aFs,aName,aFileMode,&DoNewL));}
inline CPermanentFileStore* CPermanentFileStore::CreateLC(RFs& aFs,const TDesC& aName,TUint aFileMode)
	{return STATIC_CAST(CPermanentFileStore*,CFileStore::CreateLC(aFs,aName,aFileMode,&DoNewL));}
inline CPermanentFileStore* CPermanentFileStore::ReplaceL(RFs& aFs,const TDesC& aName,TUint aFileMode)
	{return STATIC_CAST(CPermanentFileStore*,CFileStore::ReplaceL(aFs,aName,aFileMode,&DoNewL));}
inline CPermanentFileStore* CPermanentFileStore::ReplaceLC(RFs& aFs,const TDesC& aName,TUint aFileMode)
	{return STATIC_CAST(CPermanentFileStore*,CFileStore::ReplaceLC(aFs,aName,aFileMode,&DoNewL));}
inline CPermanentFileStore* CPermanentFileStore::TempL(RFs& aFs,const TDesC& aPath,TFileName& aName,TUint aFileMode)
	{return STATIC_CAST(CPermanentFileStore*,CFileStore::TempL(aFs,aPath,aName,aFileMode,&DoNewL));}
inline CPermanentFileStore* CPermanentFileStore::TempLC(RFs& aFs,const TDesC& aPath,TFileName& aName,TUint aFileMode)
	{return STATIC_CAST(CPermanentFileStore*,CFileStore::TempLC(aFs,aPath,aName,aFileMode,&DoNewL));}
inline CPermanentFileStore* CPermanentFileStore::FromL(RFile& aFile)
	{return STATIC_CAST(CPermanentFileStore*,CFileStore::FromL(aFile,KPermanentFileStoreFactoryFunction));}
inline CPermanentFileStore* CPermanentFileStore::FromLC(RFile& aFile)
	{return STATIC_CAST(CPermanentFileStore*,CFileStore::FromLC(aFile,KPermanentFileStoreFactoryFunction));}
inline CPermanentFileStore* CPermanentFileStore::NewL(RFile& aFile)
	{return STATIC_CAST(CPermanentFileStore*,CFileStore::NewL(aFile,&DoNewL));}
inline CPermanentFileStore* CPermanentFileStore::NewLC(RFile& aFile)
	{return STATIC_CAST(CPermanentFileStore*,CFileStore::NewLC(aFile,&DoNewL));}

// Class RFilePagePool
inline TInt RFilePagePool::Open(RFs& aFs,const TDesC& aName,TUint aFileMode)
	{return iFile.Open(aFs,aName,aFileMode);}
inline TInt RFilePagePool::Create(RFs& aFs,const TDesC& aName,TUint aFileMode)
	{return iFile.Create(aFs,aName,aFileMode);}
inline TInt RFilePagePool::Replace(RFs& aFs,const TDesC& aName,TUint aFileMode)
	{return iFile.Replace(aFs,aName,aFileMode);}
inline TInt RFilePagePool::Temp(RFs& aFs,const TDesC& aPath,TFileName& aName,TUint aFileMode)
	{return iFile.Temp(aFs,aPath,aName,aFileMode);}
inline void RFilePagePool::Attach(RFile& aFile)
	{iFile=aFile;}
inline void RFilePagePool::Detach()
	{iFile=RFile();}
inline RFile& RFilePagePool::File() const
	{return MUTABLE_CAST(RFile&,iFile);}

