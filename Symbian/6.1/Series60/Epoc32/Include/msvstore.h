// MSVSTORE.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//

#if !defined(__MSVSTORE_H__)
#define __MSVSTORE_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

#if !defined(__S32FILE_H__)
#include <s32file.h>
#endif

#if !defined(__MSVSTD_H__)
#include "msvstd.h"
#endif

class CMsvCachedStore;

//**********************************
// MMsvStoreObserver
//**********************************
//
// 
//

class MMsvStoreObserver
	{
public:
	enum TMsvStoreEvent {	EMsvReadStoreClosed,	// read only CMsvStore closed
							EMsvEditStoreClosed,		// edit only CMsvStore closed
							EMsvFileStoreDeleted};	// actual filestore deleted
public:
	virtual void HandleStoreEvent(TMsvStoreEvent aEvent, TMsvId aId)=0;
	};


//**********************************
// CMsvStore
//**********************************
//
// The entry structure that the client uses
//

// Uid which are not neeed to be known outside CMsvStore
const TUid KMsvEntryRichTextBody={0x10000F70};

class CMsvStore : public CBase
	{
public:
	IMPORT_C ~CMsvStore();
	//
	IMPORT_C void StoreBodyTextL(const CRichText& aRichTextBody);
	IMPORT_C void RestoreBodyTextL(CRichText& aRichTextBody);
	IMPORT_C void DeleteBodyTextL();
	IMPORT_C TBool HasBodyTextL() const;
	//
	IMPORT_C void DeleteL(); // deletes the message store
	IMPORT_C TInt SizeL(); // the size of the store
	//
	// The following give the Dictionary store interface
	IMPORT_C TBool IsNullL() const;
	IMPORT_C TBool IsPresentL(TUid aUid) const;
	IMPORT_C void Remove(TUid aUid);
	IMPORT_C void RemoveL(TUid aUid);
	IMPORT_C void Revert();
	IMPORT_C void RevertL();
	IMPORT_C TInt Commit(); 
	IMPORT_C void CommitL();
	//
protected:
	IMPORT_C CMsvStore(MMsvStoreObserver& aObserver, RFs& aFs, TMsvId aId);
	IMPORT_C static CMsvStore* OpenForReadL(MMsvStoreObserver& aObserver, RFs& aFs, const TDesC& aFileName, TMsvId aId);
	IMPORT_C static CMsvStore* OpenForWriteL(MMsvStoreObserver& aObserver, RFs& aFs, const TDesC& aFileName, TMsvId aId);
private:
	void ConstructL(const TDesC& aFileName);
	void Lock();
	inline const CMsvCachedStore& Store() const;
	inline CMsvCachedStore& Store();
	//
private:
	enum {EMsvStoreUnlocked, EMsvStoreLocked} iLockStatus;
	RFs& iFs;
	MMsvStoreObserver& iObserver;
	HBufC* iFileName;
	const TMsvId iId;
	CMsvCachedStore* iStore;
	TBool iConstructed;
	//
friend class CMsvEntry;
friend class CMsvServerEntry;
friend class RMsvReadStream;
friend class RMsvWriteStream;
	};


/**

The RMsvReadStream  class

 The message server version of RReadStream

*/
class RMsvReadStream : public RReadStream
	{
public:
	IMPORT_C void OpenL(const CMsvStore& aMsvStore, TUid aUid);
	IMPORT_C void OpenLC(const CMsvStore& aMsvStore,TUid aUid);
	void OpenLC(CMsvCachedStore& aStore,TUid aUid);
	};


/**

The RMsvWriteStream  class

  The message server version of RWriteStream

*/
class RMsvWriteStream : public RWriteStream
	{
public:
	IMPORT_C void AssignLC(CMsvStore &aMsvStore, TUid aUid);
	IMPORT_C void AssignL(CMsvStore &aMsvStore, TUid aUid);
	void AssignLC(CMsvCachedStore &aStore, TUid aUid);
	};



#endif
