// S32FILE.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//
#if !defined(__S32FILE_H__)
#define __S32FILE_H__
#if !defined(__F32FILE_H__)
#include <f32file.h>
#endif
#if !defined(__S32STOR_H__)
#include <s32stor.h>
#endif

const TInt KDefaultFileBufSize=0x600;
//
template <class T>
class TCapture;
class RFileBuf : public TStreamBuf
	{
public:
	IMPORT_C RFileBuf();
	IMPORT_C RFileBuf(TInt aSize);
	RFileBuf(TCapture<RFileBuf> aCapture);
	IMPORT_C void Reset();
	inline void Reset(TInt aSize);
//
	IMPORT_C TInt Open(RFs& aFs,const TDesC& aName,TUint aFileMode);
	IMPORT_C TInt Create(RFs& aFs,const TDesC& aName,TUint aFileMode);
	IMPORT_C TInt Replace(RFs& aFs,const TDesC& aName,TUint aFileMode);
	IMPORT_C TInt Temp(RFs& aFs,const TDesC& aPath,TFileName& aName,TUint aFileMode);
	IMPORT_C void Attach(RFile& aFile,TInt aPos=0);
	IMPORT_C void Close();
	inline void Detach();
	inline void Reattach(RFile& aFile);
//
	IMPORT_C void SetSizeL(TInt aSize);
	inline RFile& File() const;
protected:
	IMPORT_C TInt UnderflowL(TInt aMaxLength);
	IMPORT_C void OverflowL();
	IMPORT_C void DoRelease();
	IMPORT_C void DoSynchL();
	IMPORT_C TInt DoReadL(TAny* aPtr,TInt aMaxLength);
	IMPORT_C TInt DoReadL(TDes8& aDes,TInt aMaxLength,TRequestStatus& aStatus);
	IMPORT_C void DoWriteL(const TAny* aPtr,TInt aLength);
	IMPORT_C TInt DoWriteL(const TDesC8& aDes,TInt aMaxLength,TRequestStatus& aStatus);
	IMPORT_C TStreamPos DoSeekL(TMark aMark,TStreamLocation aLocation,TInt anOffset);
//
	inline void SetBuf(TRead,TUint8* aPtr,TUint8* anEnd);
	inline void SetBuf(TWrite,TUint8* aPtr,TUint8* anEnd);
	inline void SetBuf(TArea anArea,TUint8* aPtr,TUint8* anEnd);
private:
	TUint8* AllocL();
	void Free();
//
	void SetPos(TMark aMark,TInt aPos);
	inline void SetPos(TRead,TInt aPos);
	inline void SetPos(TWrite,TInt aPos);
	inline TInt Pos(TRead) const;
	inline TInt Pos(TWrite) const;
	inline TInt MovePos(TRead,TInt anOffset);
	inline TInt MovePos(TWrite,TInt anOffset);
	TInt FileReadL(TAny* aPtr,TInt aMaxLength);
	void FileWriteL(const TAny* aPtr,TInt aLength,TInt aSeek);
	void FileWriteL(const TAny* aPtr,TInt aLength);
	TInt EndL();
//
	inline TInt Lag(TRead) const;
	inline TInt Lag(TWrite) const;
	TInt Mark(TMark aMark) const;
	inline TInt Mark(TRead) const;
	inline TInt Mark(TWrite) const;
	inline TUint8* Limit(TWrite) const;
	inline void SetLimit(TWrite,TUint8* aLimit);
	inline TInt Span(TWrite) const;
	inline TInt Reach(TWrite) const;
private:
	TUint8* iBase;
	TInt iSize;
	__MUTABLE RFile iFile;
	TInt iRPos;
	TInt iWPos;
	TInt iExt;
	TUint8* iWLim;
	};
//
class RFileReadStream : public RReadStream
	{
public:
	RFileReadStream() {}
	IMPORT_C RFileReadStream(RFile& aFile,TInt aPos=0);
	IMPORT_C TInt Open(RFs& aFs,const TDesC& aName,TUint aFileMode);
	IMPORT_C void Attach(RFile& aFile,TInt aPos=0);
private:
	RFileBuf iSource;
	};
class RFileWriteStream : public RWriteStream
	{
public:
	RFileWriteStream() {}
	inline RFileWriteStream(const MExternalizer<TStreamRef>& anExter);
	IMPORT_C RFileWriteStream(RFile& aFile,TInt aPos=0);
	IMPORT_C TInt Open(RFs& aFs,const TDesC& aName,TUint aFileMode);
	IMPORT_C TInt Create(RFs& aFs,const TDesC& aName,TUint aFileMode);
	IMPORT_C TInt Replace(RFs& aFs,const TDesC& aName,TUint aFileMode);
	IMPORT_C TInt Temp(RFs& aFs,const TDesC& aPath,TFileName& aName,TUint aFileMode);
	IMPORT_C void Attach(RFile& aFile,TInt aPos=0);
private:
	RFileBuf iSink;
	};
//
class CFileStore;
class FileStoreFactory
	{
public:
	IMPORT_C static CFileStore* DirectLC(RFileBuf& aBuf,const TUidType& aType);
	IMPORT_C static CFileStore* PermanentLC(RFileBuf& aBuf,const TUidType& aType);
	};
//
const TInt KDirectFileStoreLayoutUidValue=268435511;
const TInt KPermanentFileStoreLayoutUidValue=268435536;
const TUid KDirectFileStoreLayoutUid={KDirectFileStoreLayoutUidValue};
const TUid KPermanentFileStoreLayoutUid={KPermanentFileStoreLayoutUidValue};
//
typedef CFileStore* (*TFileStoreFactoryFunction)(RFileBuf& aBuf,const TUidType& aType);
//
#define KDirectFileStoreFactoryFunction (&FileStoreFactory::DirectLC)
#define KPermanentFileStoreFactoryFunction (&FileStoreFactory::PermanentLC)
//
class CFileStore : public CPersistentStore
	{
public:
	IMPORT_C static CFileStore* OpenL(RFs& aFs,const TDesC& aName,TUint aFileMode);
	IMPORT_C static CFileStore* OpenLC(RFs& aFs,const TDesC& aName,TUint aFileMode);
	IMPORT_C static CFileStore* FromL(RFile& aFile);
	IMPORT_C static CFileStore* FromLC(RFile& aFile);
//
	IMPORT_C static CFileStore* OpenL(RFs& aFs,const TDesC& aName,TUint aFileMode,const TFileStoreFactoryFunction aFactory[]);
	IMPORT_C static CFileStore* OpenLC(RFs& aFs,const TDesC& aName,TUint aFileMode,const TFileStoreFactoryFunction aFactory[]);
	IMPORT_C static CFileStore* FromL(RFile& aFile,const TFileStoreFactoryFunction aFactory[]);
	IMPORT_C static CFileStore* FromLC(RFile& aFile,const TFileStoreFactoryFunction aFactory[]);
//
	inline const TUidType& Type() const;
	IMPORT_C void SetTypeL(const TUidType& aType);
	virtual TUid Layout() const=0;
//
	inline void Reset();
	inline void Reset(TInt aSize);
	inline void Detach();
	inline void Reattach(RFile& aFile);
	inline RFile& File() const;
//
	IMPORT_C void MarshalL();
	IMPORT_C ~CFileStore();
protected:
	typedef CFileStore* (*TNewFunction)(RFile& aFile);
protected:
	IMPORT_C static CFileStore* OpenL(RFs& aFs,const TDesC& aName,TUint aFileMode,TFileStoreFactoryFunction aFunction);
	IMPORT_C static CFileStore* OpenLC(RFs& aFs,const TDesC& aName,TUint aFileMode,TFileStoreFactoryFunction aFunction);
	IMPORT_C static CFileStore* CreateL(RFs& aFs,const TDesC& aName,TUint aFileMode,TNewFunction aFunction);
	IMPORT_C static CFileStore* CreateLC(RFs& aFs,const TDesC& aName,TUint aFileMode,TNewFunction aFunction);
	IMPORT_C static CFileStore* ReplaceL(RFs& aFs,const TDesC& aName,TUint aFileMode,TNewFunction aFunction);
	IMPORT_C static CFileStore* ReplaceLC(RFs& aFs,const TDesC& aName,TUint aFileMode,TNewFunction aFunction);
	IMPORT_C static CFileStore* TempL(RFs& aFs,const TDesC& aPath,TFileName& aName,TUint aFileMode,TNewFunction aFunction);
	IMPORT_C static CFileStore* TempLC(RFs& aFs,const TDesC& aPath,TFileName& aName,TUint aFileMode,TNewFunction aFunction);
//
	IMPORT_C static CFileStore* FromL(RFile& aFile,TFileStoreFactoryFunction aFunction);
	IMPORT_C static CFileStore* FromLC(RFile& aFile,TFileStoreFactoryFunction aFunction);
	IMPORT_C static CFileStore* NewL(RFile& aFile,TNewFunction aFunction);
	IMPORT_C static CFileStore* NewLC(RFile& aFile,TNewFunction aFunction);
//
	IMPORT_C CFileStore(RFile& aFile);
	IMPORT_C CFileStore(RFileBuf& aBuf,const TUidType& aType);
	IMPORT_C void Destruct();
//
	inline TStreamExchange& Host() const;
	inline TBool IsHost(const MStreamBuf* aBuf) const;
	IMPORT_C void SynchL();
	inline void SetSizeL(TInt aSize);
	IMPORT_C void ChangedL();
	IMPORT_C void RefreshL();
//
	IMPORT_C void DoCommitL();
	IMPORT_C void DoRevertL();
private:
	virtual void ExternalizeL(RWriteStream& aStream) const=0;
	virtual void InternalizeL(RReadStream& aStream)=0;
//
	static CFileStore* DoNewL(RFile& aFile,TNewFunction aFunction);
private:
	RFileBuf iBuf;
	TUidType iType;
	__MUTABLE TStreamExchange iHost;
	};
const TInt KFileStoreStartOffset=sizeof(TCheckedUid);
#if defined(__NO_CLASS_CONSTS__)
#define KFileStoreStart TStreamPos(KFileStoreStartOffset)
#else
const TStreamPos KFileStoreStart=TStreamPos(KFileStoreStartOffset);
#endif
//
class CDirectFileStore : public CFileStore
	{
public:
	inline static CDirectFileStore* OpenL(RFs& aFs,const TDesC& aName,TUint aFileMode);
	inline static CDirectFileStore* OpenLC(RFs& aFs,const TDesC& aName,TUint aFileMode);
	inline static CDirectFileStore* CreateL(RFs& aFs,const TDesC& aName,TUint aFileMode);
	inline static CDirectFileStore* CreateLC(RFs& aFs,const TDesC& aName,TUint aFileMode);
	inline static CDirectFileStore* ReplaceL(RFs& aFs,const TDesC& aName,TUint aFileMode);
	inline static CDirectFileStore* ReplaceLC(RFs& aFs,const TDesC& aName,TUint aFileMode);
	inline static CDirectFileStore* TempL(RFs& aFs,const TDesC& aPath,TFileName& aName,TUint aFileMode);
	inline static CDirectFileStore* TempLC(RFs& aFs,const TDesC& aPath,TFileName& aName,TUint aFileMode);
//
	inline static CDirectFileStore* FromL(RFile& aFile);
	inline static CDirectFileStore* FromLC(RFile& aFile);
	inline static CDirectFileStore* NewL(RFile& aFile);
	inline static CDirectFileStore* NewLC(RFile& aFile);
//
	IMPORT_C TUid Layout() const;
//
	IMPORT_C CDirectFileStore(RFile& aFile);
	IMPORT_C CDirectFileStore(RFileBuf& aBuf,const TUidType& aType);
protected:
	IMPORT_C MStreamBuf* DoReadL(TStreamId anId) const;
	IMPORT_C MStreamBuf* DoCreateL(TStreamId& anId);
private:
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void DoSetRootL(TStreamId anId);
//
	IMPORT_C static CFileStore* DoNewL(RFile& aFile);
	};
//
class CPermanentStoreCoord;
class CPermanentFileStore : public CFileStore
	{
public:
	inline static CPermanentFileStore* OpenL(RFs& aFs,const TDesC& aName,TUint aFileMode);
	inline static CPermanentFileStore* OpenLC(RFs& aFs,const TDesC& aName,TUint aFileMode);
	inline static CPermanentFileStore* CreateL(RFs& aFs,const TDesC& aName,TUint aFileMode);
	inline static CPermanentFileStore* CreateLC(RFs& aFs,const TDesC& aName,TUint aFileMode);
	inline static CPermanentFileStore* ReplaceL(RFs& aFs,const TDesC& aName,TUint aFileMode);
	inline static CPermanentFileStore* ReplaceLC(RFs& aFs,const TDesC& aName,TUint aFileMode);
	inline static CPermanentFileStore* TempL(RFs& aFs,const TDesC& aPath,TFileName& aName,TUint aFileMode);
	inline static CPermanentFileStore* TempLC(RFs& aFs,const TDesC& aPath,TFileName& aName,TUint aFileMode);
//
	inline static CPermanentFileStore* FromL(RFile& aFile);
	inline static CPermanentFileStore* FromLC(RFile& aFile);
	inline static CPermanentFileStore* NewL(RFile& aFile);
	inline static CPermanentFileStore* NewLC(RFile& aFile);
//
	IMPORT_C TUid Layout() const;
//
	IMPORT_C CPermanentFileStore(RFile& aFile);
	IMPORT_C CPermanentFileStore(RFileBuf& aBuf,const TUidType& aType);
	IMPORT_C void MarshalL();
	IMPORT_C ~CPermanentFileStore();
protected:
	IMPORT_C MStreamBuf* DoReadL(TStreamId anId) const;
	IMPORT_C MStreamBuf* DoCreateL(TStreamId& anId);
	IMPORT_C MStreamBuf* DoWriteL(TStreamId anId);
	IMPORT_C MStreamBuf* DoReplaceL(TStreamId anId);
private:
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void DoSetRootL(TStreamId anId);
	IMPORT_C TStreamId DoExtendL();
	IMPORT_C void DoDeleteL(TStreamId anId);
	IMPORT_C void DoCommitL();
	IMPORT_C void DoRevertL();
	IMPORT_C MIncrementalCollector* DoReclaimL();
	IMPORT_C MIncrementalCollector* DoCompactL();
//
	inline CPermanentStoreCoord& Coord() const;
	CPermanentStoreCoord& CoordL() const;
	CPermanentStoreCoord& TrimL();
//
	IMPORT_C static CFileStore* DoNewL(RFile& aFile);
private:
	__MUTABLE CPermanentStoreCoord* iCoord;
	};
//
class CDictionaryFileStore : public CDictionaryStore
	{
public:
	IMPORT_C static CDictionaryFileStore* SystemL(RFs& aFs);
	IMPORT_C static CDictionaryFileStore* SystemLC(RFs& aFs);
	IMPORT_C static CDictionaryFileStore* OpenL(RFs& aFs,const TDesC& aName,TUid aUid3);
	IMPORT_C static CDictionaryFileStore* OpenLC(RFs& aFs,const TDesC& aName,TUid aUid3);
private:
	void ConstructL(RFs& aFs,const TDesC& aName,TUid aUid3);
	void CreateStoreL(RFile& aFile,const TUidType& aType);
	};
//
class RFilePagePool : public TCachePagePool
	{
public:
	IMPORT_C RFilePagePool();
	IMPORT_C RFilePagePool(CPageCache& aCache);
//
	inline TInt Open(RFs& aFs,const TDesC& aName,TUint aFileMode);
	inline TInt Create(RFs& aFs,const TDesC& aName,TUint aFileMode);
	inline TInt Replace(RFs& aFs,const TDesC& aName,TUint aFileMode);
	inline TInt Temp(RFs& aFs,const TDesC& aPath,TFileName& aName,TUint aFileMode);
	inline void Attach(RFile& aFile);
	IMPORT_C void Close();
	IMPORT_C void Release();
	IMPORT_C TInt Flush();
	IMPORT_C void FlushL();
	inline void Detach();
//
	inline RFile& File() const;
protected:
	IMPORT_C TPageRef ExtendL(const TAny* aPage,TPageReclamation aReclamation);
	IMPORT_C void WriteL(TPageRef aRef,const TAny* aPage,TPageChange aChange);
	IMPORT_C void ReadL(TPageRef aRef,TAny* aPage);
private:
	__MUTABLE RFile iFile;
	};

#include <s32file.inl>
#endif
