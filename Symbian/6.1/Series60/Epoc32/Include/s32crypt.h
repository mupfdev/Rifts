// S32CRYPT.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//
#if !defined(__S32CRYPT_H__)
#define __S32CRYPT_H__
#if !defined(__S32BUF_H__)
#include <s32buf.h>
#endif
#if !defined(__S32STOR_H__)
#include <s32stor.h>
#endif

const TInt KEncryptionFilterBufSize=160;

class TSecureFilter : public TStreamFilter
	{
protected:
	TSecureFilter();
	void Set(MStreamBuf* aHost,TInt aMode=EWrite);
protected:
	IMPORT_C TInt Capacity(TInt aMaxLength);
	IMPORT_C TInt FilterL(TAny* aPtr,TInt aMaxLength,const TUint8*& aFrom,const TUint8* anEnd);
	IMPORT_C void DoSynchL();
	TInt EmitL(const TDesC8& aDes);
private:
	virtual TInt CryptL(TDes8& aTarget,const TDesC8& aSource) =0;
	virtual void CompleteL(TDes8& aTarget,const TDesC8& aSource) =0;
private:
	TBuf8<KEncryptionFilterBufSize> iIn;
	TPtrC8 iOut;
	TUint8 iBuf[KEncryptionFilterBufSize];
	};

class TEncryptFilter : public TSecureFilter
	{
public:
	IMPORT_C TEncryptFilter();
	IMPORT_C void Set(MStreamBuf* aHost,CSecurityEncryptBase* aKey,TInt aMode=EWrite);
protected:
	IMPORT_C void DoRelease();
private:
	IMPORT_C TInt CryptL(TDes8& aTarget,const TDesC8& aSource);
	IMPORT_C void CompleteL(TDes8& aTarget,const TDesC8& aSource);
private:
	CSecurityEncryptBase* iKey;
	};

class TDecryptFilter : public TSecureFilter
	{
public:
	IMPORT_C TDecryptFilter();
	IMPORT_C void Set(MStreamBuf* aHost,CSecurityDecryptBase* aKey,TInt aMode=ERead);
protected:
	IMPORT_C void DoRelease();
private:
	IMPORT_C TInt CryptL(TDes8& aTarget,const TDesC8& aSource);
	IMPORT_C void CompleteL(TDes8& aTarget,const TDesC8& aSource);
private:
	CSecurityDecryptBase* iKey;
	};
//
class RDecryptStream : public RReadStream
	{
public:
	RDecryptStream() {}
	IMPORT_C void OpenL(RReadStream& aHost,const CSecurityBase& aKey,const TDesC8& aInit);
	IMPORT_C void OpenLC(RReadStream& aHost,const CSecurityBase& aKey,const TDesC8& aInit);
	IMPORT_C void AttachL(RReadStream& aHost,const CSecurityBase& aKey,const TDesC8& aInit);
	IMPORT_C void AttachLC(RReadStream& aHost,const CSecurityBase& aKey,const TDesC8& aInit);
private:
	TDecryptFilter iFilter;
	};
class REncryptStream : public RWriteStream
	{
public:
	REncryptStream() {}
	inline REncryptStream(const MExternalizer<TStreamRef>& anExter);
	IMPORT_C void OpenL(RWriteStream& aHost,const CSecurityBase& aKey,const TDesC8& aInit);
	IMPORT_C void OpenLC(RWriteStream& aHost,const CSecurityBase& aKey,const TDesC8& aInit);
	IMPORT_C void AttachL(RWriteStream& aHost,const CSecurityBase& aKey,const TDesC8& aInit);
	IMPORT_C void AttachLC(RWriteStream& aHost,const CSecurityBase& aKey,const TDesC8& aInit);
private:
	TEncryptFilter iFilter;
	};
//
class CSecureStore : public CStreamStore
	{
public:
	IMPORT_C static CSecureStore* NewL(CStreamStore& aHost,const CSecurityBase& aKey);
	IMPORT_C static CSecureStore* NewLC(CStreamStore& aHost,const CSecurityBase& aKey);
//
	IMPORT_C CSecureStore(CStreamStore& aHost,const CSecurityBase& aKey);
protected:
	IMPORT_C MStreamBuf* DoReadL(TStreamId anId) const;
	IMPORT_C MStreamBuf* DoCreateL(TStreamId& anId);
private:
	inline CStreamStore& Host();
	inline const CStreamStore& Host() const;
	inline const CSecurityBase& Key() const;
private:
	CStreamStore* iHost;
	const CSecurityBase* iKey;
	};
//
class RSecureStorePagePool : public RStorePagePool
	{
public:
	IMPORT_C RSecureStorePagePool(const CBoundedSecurityBase& aKey);
	IMPORT_C RSecureStorePagePool(CPageCache& aCache,const CBoundedSecurityBase& aKey);
protected:
	IMPORT_C TPageRef ExtendL(const TAny* aPage,TPageReclamation aReclamation);
	IMPORT_C void WriteL(TPageRef aRef,const TAny* aPage,TPageChange aChange);
	IMPORT_C void ReadL(TPageRef aRef,TAny* aPage);
	IMPORT_C void DoDeleteL(TPageRef aRef);
private:
	const CBoundedSecurityBase* iKey;
	};

#include <s32crypt.inl>
#endif
