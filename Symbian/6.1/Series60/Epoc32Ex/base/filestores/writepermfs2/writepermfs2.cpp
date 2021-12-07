// WritePermFS2.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.

// Example to demonstrate use of CPermanentFileStore


// The Store root stream is an example of a persistent data structure
// The internal representation is the class CItemArray


#include "CommonStreamStore.h"
#include <s32file.h>
	
				// Create a permanent file store
				// and initialise its stream structure
LOCAL_C void doMakeStoreL(const TDesC& aName);

				// Use the store, preserving the stream structure
LOCAL_C void doUseStoreL(const TDesC& aName);

				// Update the data in the store
LOCAL_C void doUpdateStoreL(CPersistentStore& aStore);

				// Display the store contents
LOCAL_C void doShowL(const TDesC& aHeading,CPersistentStore& aStore);


typedef TBuf<100> TItem;

				// The main object's in-memory representation
class CItemArray : public CBase
	{
public:
	static TStreamId CreateL(CStreamStore& aStore);
		//
	~CItemArray();
	static CItemArray* NewLC(CStreamStore& aStore,TStreamId anId);
	void RestoreL();
	void StoreL() const;
	void ExternalizeL(RWriteStream& aStream) const;
		//
	void AddItemL(const TItem& anItem);
	void RemoveItemL(TInt anIndex);
	TInt Count() const;
	void GetItemL(TItem& anItem,TInt anIndex) const;
protected:
	CItemArray(CStreamStore& aStore);
	void ConstructL();
	void InternalizeL(RReadStream& aStream);
private:
	CStreamStore& iStore;
	TStreamId iMyId;
	CArrayFixFlat<TStreamId>* iArray;
	};


// The file name, extension and path for the file store
_LIT(KFullNameOfFileStore,"C:\\epoc32ex\\data\\WritePermFS2.dat");


//  Do the example
LOCAL_C void doExampleL()
    {
			    // make sure directory exists
	fsSession.MkDirAll(KFullNameOfFileStore);
	doMakeStoreL(KFullNameOfFileStore);
	doUseStoreL(KFullNameOfFileStore);
	}


LOCAL_C void doMakeStoreL(const TDesC& aName)
	{
	TParse	filestorename;
	fsSession.Parse(aName,filestorename);
				// construct file store object - the file to contain the
				// the store replaces any existing file of the same name.
	CFileStore* store = CPermanentFileStore::ReplaceLC(fsSession,filestorename.FullName(),EFileRead|EFileWrite);
				// Easy way to set the layout type
    store->SetTypeL(store->Layout());
		
				// create the required stream for CItemArray
	TStreamId id=CItemArray::CreateL(*store);

				// make it the root
	store->SetRootL(id);
			
				// Commit changes to the store
	store->CommitL();

				// Show contents of the store
	_LIT(KTxtStoreContent,"Store content ...");
	doShowL(KTxtStoreContent,*store);

				// Cleanup the store
	CleanupStack::PopAndDestroy();
	}


LOCAL_C void doUseStoreL(const TDesC& aName)
	{
	TParse	filestorename;
	fsSession.Parse(aName,filestorename);
				// construct file store object - specifying the file
				// containing the store.
				// Do not need to specify the file store type, this is
				// specified by the file itself
	CFileStore* store = CFileStore::OpenL(fsSession,filestorename.FullName(),EFileRead|EFileWrite);

				// The standard form for using permanent file stores:
				// 1. The store object is not owned by the updating code
				// 2  Failure at any point during update, including the
				//    final commit, should result in Revert() being called
				//    on the store (before destruction).

	_LIT(KTxtErrorOccurred,"\n** Error %d occured during store update");

	TRAPD(error,doUpdateStoreL(*store));
	if (error!=KErrNone)
		{
		store->Revert();
		console->Printf(KTxtErrorOccurred);
		}

				// the store is not on the cleanup stack
	delete store;
	}


LOCAL_C void doUpdateStoreL(CPersistentStore& aStore)
	{
				// get the root stream into memory
	CItemArray* array=CItemArray::NewLC(aStore,aStore.Root());

				// Add some items
	_LIT(KTxtHello,"hello");
	_LIT(KTxtWorld," world!");

	TItem item;
	item = KTxtHello;
	array->AddItemL(item);
	item = KTxtWorld;
	array->AddItemL(item);
				// Re-write the root stream with new data
	array->StoreL();
				// commit all changes
	aStore.CommitL();

	_LIT(KTxtAfterAdding,"After adding...");
	doShowL(KTxtAfterAdding,aStore);

				// remove an item
	array->RemoveItemL(1);		// " world!"
				// Re-write the root stream with new data
	array->StoreL();
				// commit all changes
	aStore.CommitL();

	_LIT(KTxtAfterRemoving,"After removing...");
	doShowL(KTxtAfterRemoving,aStore);

				// Add an item
	_LIT(KTxtCapWorld," WORLD!");
	item= KTxtCapWorld;
	array->AddItemL(item);
				// Re-write the root stream with new data
	array->StoreL();
				// Discard all changes since last store commit
	aStore.Revert();

	_LIT(KTxtAfterRevert,"After revert...");
	doShowL(KTxtAfterRevert,aStore);

				// array and aStore are not in snych after revert...
				// restore in-memory version to match store version
	array->RestoreL();

					// Add the item again
	array->AddItemL(item);
				// Re-write the root stream with new data
	array->StoreL();
				// commit all changes
	aStore.CommitL();

	_LIT(KTxtAfterCommit,"After commit...");
	doShowL(KTxtAfterCommit,aStore);

				// cleanup array
	CleanupStack::PopAndDestroy();
	}

_LIT(KTxtNewLine,"\n");
_LIT(KFormatType1,"\n%d item(s):");
_LIT(KFormatType2,"\n  %S");
_LIT(KFormatType3,"\n[any key to continue]\n");


LOCAL_C void doShowL(const TDesC& aHeading,CPersistentStore& aStore)
	{
				// Get an in-memory representation of the root stream
	CItemArray* array=CItemArray::NewLC(aStore,aStore.Root());

	console->Printf(KTxtNewLine);
	console->Printf(aHeading);
	console->Printf(KFormatType1,array->Count());
	for (TInt ii=0;ii<array->Count();++ii)
		{
				// for each item in the array
				//    get the item
		TItem item;
		array->GetItemL(item,ii);
				//    display the data
		console->Printf(KFormatType2,&item);
		}
				// cleanup the array
	CleanupStack::PopAndDestroy();

	console->Printf(KFormatType3);
	console->Getch();
	}


//***************************************************************
//***************************************************************

CItemArray::~CItemArray()
	{
	delete iArray;
	}

CItemArray::CItemArray(CStreamStore& aStore)
	: iStore(aStore)
	{}

TStreamId CItemArray::CreateL(CStreamStore& aStore)
// create the stream representation of the class
	{
				// use a temporary CItemArray
	CItemArray* self=new(ELeave) CItemArray(aStore);
	CleanupStack::PushL(self);
				// construct object
	self->ConstructL();
				// create new stream
	RStoreWriteStream outstream;
	TStreamId id=outstream.CreateLC(aStore);
				// write  external rep
	self->ExternalizeL(outstream);
				// commit stream
	outstream.CommitL();
				// cleanup stream and temporary self
	CleanupStack::PopAndDestroy(2);
	return id;
	}

CItemArray* CItemArray::NewLC(CStreamStore& aStore,TStreamId anId)
// construct a CItemArray from persistent storage
	{
	CItemArray* self=new(ELeave) CItemArray(aStore);
	CleanupStack::PushL(self);
				// construct object
	self->ConstructL();
				// set the stream id for StoreL/RestoreL
	self->iMyId=anId;
				// restore the internal rep.
	self->RestoreL();
	return self;
	}

void CItemArray::StoreL() const
// replace external rep. with internal one
	{
	RStoreWriteStream outstream;
	outstream.ReplaceLC(iStore,iMyId);
	ExternalizeL(outstream);
	outstream.CommitL();
	CleanupStack::PopAndDestroy();
	}

void CItemArray::RestoreL()
// replace internal rep with external one
	{
	iArray->Reset();
	RStoreReadStream instream;
	instream.OpenLC(iStore,iMyId);
	InternalizeL(instream);
	CleanupStack::PopAndDestroy();
	}

void CItemArray::AddItemL(const TItem& anItem)
// add item to the collection
	{
				// write external rep of item
	RStoreWriteStream outstream;
	TStreamId id=outstream.CreateLC(iStore);
	outstream<<anItem;
	outstream.CommitL();
	CleanupStack::PopAndDestroy();
				// add new stream id to the internal array
	iArray->AppendL(id);
	}

void CItemArray::RemoveItemL(TInt anIndex)
// remove an item from the collection
	{
				// remove the stream from the store
	iStore.DeleteL((*iArray)[anIndex]);
				// remove the entry from the internal array
	iArray->Delete(anIndex);
	}

TInt CItemArray::Count() const
	{
	return iArray->Count();
	}

void CItemArray::GetItemL(TItem& anItem,TInt anIndex) const
// retrieve an item from the store
	{
	RStoreReadStream instream;
	instream.OpenLC(iStore,(*iArray)[anIndex]);
	instream>>anItem;
	CleanupStack::PopAndDestroy();
	}

void CItemArray::ConstructL()
	{
	iArray=new(ELeave) CArrayFixFlat<TStreamId>(8);
	}

void CItemArray::ExternalizeL(RWriteStream& aStream) const
	{
				// stream out the array
	aStream<<*iArray;
	}

void CItemArray::InternalizeL(RReadStream& aStream)
	{
				// stream in the array
	aStream>>*iArray;
	}
