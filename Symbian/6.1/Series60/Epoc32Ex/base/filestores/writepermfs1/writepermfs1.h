// WritePermFS1.h
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
//

//***************************************************************
//
// Function and class definitions used in the 
// WriteObjectsToPermanentFileStore1 example
//
//***************************************************************
#ifndef __WritePermFS1_H
#define __WritePermFS1_H

#include "CommonStreamStore.h"
#include <s32file.h>

LOCAL_C void doMakeL(const TDesC& aName);
LOCAL_C void doUseL(const TDesC& aName);

class CClassA;
LOCAL_C void doShow(const TDesC& aHeading,const CClassA& anA);

class CClassB;
LOCAL_C void doShow(const TDesC& aHeading,const CClassB& aB);

class CClassC;
LOCAL_C void doShow(const TDesC& aHeading,const CClassC& aC);

class CClassP;
LOCAL_C void doShow(const TDesC& aHeading,const CClassP& aP);

class CClassR;
LOCAL_C void doShow(const TDesC& aHeading,const CClassR& aR);

class CClassA : public CBase
	{
public :
	static CClassA* NewL();
	static CClassA* NewLC();
public :
	~CClassA();
	void     ExternalizeL(RWriteStream& aStream) const;
	void     InternalizeL(RReadStream& aStream);
public :
	HBufC*   iVarBuf;
	TInt     iIntValue;
	TUint    iUintValue;
	};

class CClassB : public CBase
	{
public :
	static CClassB* NewL();
	static CClassB* NewLC();
public :
	void     ExternalizeL(RWriteStream& aStream) const;
	void     InternalizeL(RReadStream& aStream);
public :
	TBuf<32> iFixBuf;
	TUint    iUintValue;
	TInt     iIntValue;
	TReal    iRealValue;
	};

class CClassC : public CBase
	{
public  :
	static CClassC* NewL();
	static CClassC* NewLC();
public  :
	void     ExternalizeL(RWriteStream& aStream) const;
	void     InternalizeL(RReadStream& aStream);
public :
	TBuf<32> iFixBuf;
	};

class CClassP : public CBase
	{
public  :
	static CClassP* NewLC(const TDesC& aData,CStreamStore& aStore);
	static CClassP* NewLC(CStreamStore& aStore, TStreamId anId);
public  :
	CClassP(CStreamStore& aStore);
	CClassP(CStreamStore& aStore,TStreamId anId);
public  :
	TStreamId     StoreL();
	void          RestoreL();
	void          ExternalizeL(RWriteStream& aStream) const;
	void          InternalizeL(RReadStream& aStream);
private :
	void          Construct(const TDesC& aData);
public :
	TBuf<32>      iFixBuf;
	CStreamStore& iStore; // Store to/Restore from this store
	TStreamId     iId;    // Restore from/replace this stream
	};


class CClassR : public CBase
	{
public  :
	static CClassR* NewLC(const TDesC& aData,CStreamStore& aStore);
	static CClassR* NewLC(CStreamStore& aStore, TStreamId anId);
public  :
	CClassR(CStreamStore& aStore);
	CClassR(CStreamStore& aStore,TStreamId anId);
public  :
	TStreamId     StoreL();
	void          UpdateStoreL();
	void          RestoreL();
	void          ExternalizeL(RWriteStream& aStream) const;
	void          InternalizeL(RReadStream& aStream);
	void          ChangeDataL(const TDesC& aData);
private :
	void          Construct(const TDesC& aData);
public :
	TBuf<32>      iFixBuf;
	CStreamStore& iStore; // Store to/Restore from this store
	TStreamId     iId;    // Restore from/replace this stream
	};


class TExampleIndex
	{
public :
	TStreamId StoreL(CStreamStore& aStore);
	void      RestoreL(CStreamStore& aStore, TStreamId anId);
	void      ExternalizeL(RWriteStream& aStream) const;
	void      InternalizeL(RReadStream& aStream);
public :
	TStreamId iPid;
	TStreamId iRid;
	TStreamId iABCid;
	};


class CClassABC : public CBase
	{
public :
	static CClassABC* NewLC(CStreamStore& aStore);
	static CClassABC* NewLC(CStreamStore& aStore, TStreamId anId);
public :
	CClassABC(CStreamStore& aStore);
	CClassABC(CStreamStore& aStore,TStreamId anId);
	~CClassABC();
	TStreamId         StoreL();
	void              RestoreL();
	void              ConstructAL(const TDesC& aData,TInt anInt,TUint aUint);
	void              ConstructB(const TDesC& aData,TInt anInt,TUint aUint,TReal aReal);
	void              ConstructC(const TDesC& aData);
	const CClassA*    PtrA();
	const CClassB*    PtrB();
	const CClassC*    PtrC();
private :
	void              ConstructL();
	void              RestoreBL();
private :
	CClassA*          iA;
	TSwizzle<CClassB> iB;     // Note use of swizzle here
	CClassC*          iC;
	CStreamStore&     iStore; // Store to/Restore from this store
	TStreamId         iId;    // Restore from/replace this stream
	};

#endif
