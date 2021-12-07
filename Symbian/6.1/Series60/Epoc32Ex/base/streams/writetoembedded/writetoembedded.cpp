// WriteToEmbedded.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.

// Example uses an embedded store.
//
// This example uses a permanent file store. It constructs a CMainClass object
// which has a CClassABC object as a component. The CClassABC object itself
// has other components and its structure is the same as found in the
// WriteToMany example.
//
// Here, the CClassABC component object network is stored in an embedded store.
//
// The example:
//      creates a permanent file store
//
//      constructs a CMainClass object. This results in the construction
//      of a CClassABC objet network which is stored in its own embedded
//      store (within the main store). 
//      
//      stores the CMainClass object in its own stream in the main store
//      and makes that stream the root stream.
//
//      closes the store and deletes the CMainClass object from memory
//
//			========================================================
//
//      re-opens the permanent file store
//
//		restores the CMainClass object and opens the embedded store. As the 
//      the contained CClassABC object itself has components which are only 
//      loaded in when needed, then the embedded store is kept open.
//
//      Displays the content of the CClassA, CClassB and CClassC objects.
//
//      Deletes the CClassABC object from CMainClass and deletes its representation
//      from the permanent file store. Note that knowledge of the detailed
//      structure of the CClassABC object network is not needed. 
//
//		Attempts to redisplay the content of the CClassA, CClassB and CClassC 
//      objects; this should fail as they have been deleted.
//
//      closes the store and deletes the CMainClass object from memory.
//
// Notes:
//		The file name and extension of the direct file store is "WriteToEmbedded.dat".
//      and will be created in c:\data\ 
//
#include "WriteToEmbedded.h"
	
//***************************************************************
//
// Implementations
//
//***************************************************************

// The file name, extension and path for the file store
_LIT(KFullNameOfFileStore,"C:\\epoc32ex\\data\\WriteToEmbedded.dat");

				//  Do the example
LOCAL_C void doExampleL()
    {
			    // make sure directory exists
	fsSession.MkDirAll(KFullNameOfFileStore);
	doMakeAndStoreL(KFullNameOfFileStore);
	doDeleteComponentL(KFullNameOfFileStore);
	}
 
LOCAL_C void doMakeAndStoreL(const TDesC& aName)
	{
				// Create (replace, if it exists) the permanent file store
	TParse	filestorename;
	fsSession.Parse(aName,filestorename);
	CFileStore* store = CPermanentFileStore::ReplaceLC(fsSession,filestorename.FullName(),EFileWrite);

				// Must say what kind of file store.
	store->SetTypeL(KPermanentFileStoreLayoutUid);
	
				// Construct a main object and its component
				// CClassABC object; the CClassABC component object
				// and its components are stored in an embedded store
				// within the main store.  
	CMainClass* theMain = CMainClass::NewLC(*store);

				// Store the CMainClass object in its own stream 
				// in the top level store
	TStreamId theId = theMain->StoreL();

				// Set this stream id as the root stream
	store->SetRootL(theId);

				// Commit theses changes to the top level store
	store->CommitL();

				// Destroy:
				//		the CMainClass object,
				//		the permanent file store object (closes the file)
	CleanupStack::PopAndDestroy(2);	
	}

LOCAL_C void doDeleteComponentL(const TDesC& aName)
	{
				// Open the permanent file store
	TParse	filestorename;
	fsSession.Parse(aName,filestorename);
	CFileStore* store = CPermanentFileStore::OpenLC(fsSession,filestorename.FullName(),EFileRead|EFileWrite);
				
				// Restore the main object
	CMainClass* theMain = CMainClass::NewLC(*store,store->Root());
	
				// Show the content of the classes contained by CClassABC,
				// loading as needed
	CClassABC* abc = theMain->PtrAbc();
	
	_LIT(KTxtClassAContent,"CClassA content ...");
	_LIT(KTxtClassBContent,"CClassB content ...");
	_LIT(KTxtClassCContent,"CClassC content ...");
	_LIT(KTxtClassABCDeleted,"CClassABC component deleted");

	if (abc)
		{
		doShow(KTxtClassAContent,*abc->PtrA());
		doShow(KTxtClassBContent,*abc->PtrB());					
		doShow(KTxtClassCContent,*abc->PtrC());
		}
	else
		doShow(KTxtClassABCDeleted);
		
				// remove the CClassABC component from CMainClass and
				// and remove its representation from the store
	theMain->RemoveAbcL();

				// Try and show the contents again; the pointer
				// abc should now be NULL
	abc = theMain->PtrAbc();
	if (abc)
		{
		doShow(KTxtClassAContent,*abc->PtrA());
		doShow(KTxtClassBContent,*abc->PtrB());					
		doShow(KTxtClassCContent,*abc->PtrC());
		}
	else
		doShow(KTxtClassABCDeleted);

				// Destroy:
				//		the CMainClass object, 
				//      the permanent file store object (closes the file) 
	CleanupStack::PopAndDestroy(2);
	}

_LIT(KTxtNewLine,"\n");
_LIT(KFormatType1,"\n%S, ");
_LIT(KFormatType2,"%d, ");
_LIT(KFormatType3,"%u  ");
_LIT(KFormatType4,"%u, ");
_LIT(KFormatType5,"%f  ");
 
LOCAL_C void doShow(const TDesC& aComment)
	{
	console->Printf(KTxtNewLine);
	console->Printf(aComment);
	console->Printf(KTxtNewLine);
	}
	
LOCAL_C void doShow(const TDesC& aHeading,const CClassA& anA)
	{
	console->Printf(KTxtNewLine);
	console->Printf(aHeading);
	console->Printf(KFormatType1,anA.iVarBuf);
	console->Printf(KFormatType2,anA.iIntValue);
	console->Printf(KFormatType3,anA.iUintValue);
	console->Printf(KTxtNewLine);
	}

LOCAL_C void doShow(const TDesC& aHeading,const CClassB& aB)
	{
	console->Printf(KTxtNewLine);
	console->Printf(aHeading);
	console->Printf(KFormatType1,&aB.iFixBuf);
	console->Printf(KFormatType2,aB.iIntValue);
	console->Printf(KFormatType4,aB.iUintValue);
	console->Printf(KFormatType5,aB.iRealValue);
	console->Printf(KTxtNewLine);
	}

LOCAL_C void doShow(const TDesC& aHeading,const CClassC& aC)
	{
	console->Printf(KTxtNewLine);
	console->Printf(aHeading);
	console->Printf(KFormatType1,&aC.iFixBuf);
	console->Printf(KTxtNewLine);
	}

//***************************************************************
//
// CMainClass Implementation
//
//***************************************************************
CMainClass* CMainClass::NewLC(CStreamStore& aStore)
	{
	CMainClass* self = new (ELeave) CMainClass(aStore);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CMainClass* CMainClass::NewLC(CStreamStore& aStore,TStreamId anId)
	{
	CMainClass* self = new (ELeave) CMainClass(aStore,anId);
	CleanupStack::PushL(self);
	self->RestoreL();
	return self;
	}

CMainClass::CMainClass(CStreamStore& aStore)
	: iStore(aStore)
	{}

CMainClass::CMainClass(CStreamStore& aStore,TStreamId anId)
	: iStore(aStore), iId(anId)
	{}

_LIT(KTxtMainData,"Main data");
_LIT(KTxtClassAData,"Data for the CClassA - AAAAA");
_LIT(KTxtClassBData,"Data for the CClassB - BBBBB");
_LIT(KTxtClassCData,"Data for the CClassC - CCCCC");

void CMainClass::ConstructL()
	{
	iSomeData = KTxtMainData;
				// create the stream to contain the embedded store
	RStoreWriteStream childStream;
				// we need to keep track of this stream id
	iEmbeddedStoreId = childStream.CreateLC(iStore);
				// construct the embedded store
	CPersistentStore* embeddedStore = CEmbeddedStore::NewLC(childStream);
				// construct the CClassABC and its containees. Note that
				// the store it uses is the embedded store.
	iAbc = CClassABC::NewL(*embeddedStore); 
	iAbc->ConstructAL(KTxtClassAData,-1,2);
	iAbc->ConstructB(KTxtClassBData,-3,4,5.6);
	iAbc->ConstructC(KTxtClassCData);
				// store the CClassABC and its containees in the
				// embedded store ...
	TStreamId idForAbc = iAbc->StoreL();
				// ... and set this stream id as the root 
				// stream of the embedded store
	embeddedStore->SetRootL(idForAbc);	
				// Commit changes to the embedded store
	embeddedStore->CommitL();
				// Commit changes to the stream containing the 
				// embedded store.
	childStream.CommitL();
				// Destroy the embedded store object
				// Cleanup the stream containing the emmbedded store 
	CleanupStack::PopAndDestroy(2);
	}

CMainClass::~CMainClass()
	{
	delete iEmbeddedStore;
	iChildStream.Release(); //stream cleanup
	delete iAbc;
	}

TStreamId CMainClass::StoreL()
	{
	RStoreWriteStream stream;
	TStreamId id = stream.CreateLC(iStore);
	ExternalizeL(stream);
	stream.CommitL();
	CleanupStack::PopAndDestroy();
	return id;
	}
	
void CMainClass::ExternalizeL(RWriteStream& aStream)
	{
	aStream << iSomeData; 
	aStream << iEmbeddedStoreId;
	}

void CMainClass::RestoreL()
	{
	RStoreReadStream stream;
	stream.OpenLC(iStore,iId);
				// restore the CMainClass object
	InternalizeL(stream);
				// clean up the stream
	CleanupStack::PopAndDestroy();
				// open stream containing the embedded store
				// (and keep it open)
	if (iEmbeddedStoreId != KNullStreamId)
		{
		iChildStream.OpenL(iStore,iEmbeddedStoreId);
				// construct the embedded store 
				// (and keep it open)
		iEmbeddedStore = CEmbeddedStore::FromL(iChildStream);
				// restore the CClassABC object network from the
				// embedded store. Note that not all of CClassABC's
				// containees are loaded in, hence the need to keep
				// the embedded store open 
		iAbc = CClassABC::NewL(*iEmbeddedStore,iEmbeddedStore->Root());
		}
	}

void CMainClass::InternalizeL(RReadStream& aStream)
	{
	aStream >> iSomeData; 
	aStream >> iEmbeddedStoreId;
	}

CClassABC* CMainClass::PtrAbc()
	{
	return iAbc;
	}

void CMainClass::RemoveAbcL()
	{
				// Remove the CClassABC component from memory an
				// from the store. 
				// To remove the CClassABC representation from the 
				// store, just delete the stream containing the
				// embedded store which contains the representation of
				// the CClassABC object network.
	if (!iAbc)
		return;
	delete iAbc;
	iAbc = NULL;
				// close the embedded store
	delete iEmbeddedStore;
	iEmbeddedStore = NULL;
				// cleanup the stream (this is in the top 
				// level store) containing the embedded store
	iChildStream.Release();
				// delete the stream from the top level store ...
	iStore.DeleteL(iEmbeddedStoreId);
				// ... and commit these changes to the top
				// level store
	iStore.CommitL();			
	iEmbeddedStoreId = KNullStreamId;
	}

//***************************************************************
//
// CClassABC Implementation
//
//***************************************************************
CClassABC::CClassABC(CStreamStore& aStore)
	: iStore(aStore)
	{}

CClassABC::CClassABC(CStreamStore& aStore,TStreamId anId)
	: iStore(aStore), iId(anId)
	{}

CClassABC* CClassABC::NewLC(CStreamStore& aStore)
	{
	CClassABC* self = new (ELeave) CClassABC(aStore);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CClassABC* CClassABC::NewL(CStreamStore& aStore)
	{
	CClassABC* self = CClassABC::NewLC(aStore);
	CleanupStack::Pop();
	return self;
	}

CClassABC* CClassABC::NewLC(CStreamStore& aStore, TStreamId anId)
	{															
	CClassABC* self = new (ELeave) CClassABC(aStore,anId);
	CleanupStack::PushL(self);
	self->RestoreL();
	return self;
	}

CClassABC* CClassABC::NewL(CStreamStore& aStore, TStreamId anId)
	{
	CClassABC* self = CClassABC::NewLC(aStore,anId);
	CleanupStack::Pop();
	return self;
	}
		
void CClassABC::ConstructL()
	{
	iA = CClassA::NewL();
	iB = CClassB::NewL();
	iC = CClassC::NewL();
	}

void CClassABC::ConstructAL(const TDesC& aData,TInt anInt,TUint aUint)
	{
	iA->iVarBuf    = aData.AllocL();	
	iA->iIntValue  = anInt;
	iA->iUintValue = aUint;
	}
			
void CClassABC::ConstructB(const TDesC& aData,TInt anInt,TUint aUint,TReal aReal)
	{
	iB->iFixBuf    = aData;
	iB->iIntValue  = anInt; 
	iB->iUintValue = aUint;
	iB->iRealValue = aReal;
	}
			
void CClassABC::ConstructC(const TDesC& aData)
	{
	iC->iFixBuf = aData;
	}


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
			// Destructor deletes the CClassB object only if it is in memory.
			// The IsPtr() function can be used to determine whether the 
			// CClassB object is memory. 
			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
CClassABC::~CClassABC()
	{
	delete iA;
	delete iC;
	if (iB.IsPtr())
		delete iB.AsPtr(); // can also "delete iB;" makes implicit call to "operator T*()"
	}

	
				// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
				// Stores the CClassB object in its own stream and
				// then stores:
				//		the CClassA object,
				//		the streamid of the CClassB object,
				//		the CClassC object
				// in a separate stream.
				// Returns the streamid of this last stream
				// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
TStreamId CClassABC::StoreL()
	{
				// Construct the output stream which is intended
				// to hold the CClassB object only.
	RStoreWriteStream outstream;
	TStreamId idForB = outstream.CreateLC(iStore);
				// Stream out the CClassB object.
				// Note that the right hand side returns a reference
				// to CClassB
	outstream  << *iB; 
				// Commit changes to the stream
	outstream.CommitL();
				// Cleanup the stream object
	CleanupStack::PopAndDestroy();	
				// Now construct the output stream which is intended
				// to hold:
				//		the CClassA object,
				//		the streamid of the CClassB object,
				//		the CClassC object
	TStreamId id = outstream.CreateLC(iStore);
				// Write out the CClassA object.
	outstream  << *iA; 
				// Write out the stream id of the CClassB object
	outstream  << idForB;
				// Write out the CClassC object.
	outstream  << *iC;
				// Commit changes to the stream
	outstream.CommitL();
				// Cleanup the stream object,
	CleanupStack::PopAndDestroy();	
				// Return this stream id
	return id;
	}

				
const CClassA* CClassABC::PtrA()
	{
	return iA;	// Return a pointer to the contained CClassA object
	}

				
const CClassB* CClassABC::PtrB()
	{
	if (iB.IsId())		// If the contained CClassB object is not in memory, it must
		RestoreBL();	// be loaded in before a pointer can be returned to the caller
	return iB.AsPtr();
	}

				
const CClassC* CClassABC::PtrC()
	{
	return iC;	//Returns a pointer to the contained CClassC object
	}
				
				// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
				// Restores the CClassA and CClassC objects and the streamid for the
				// CClassB object.
				// The swizzle for the CClassB object is constructed from the
				// streamid but the CClassB object itself is NOT restored at 
				// this time.
				// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
void CClassABC::RestoreL()
	{
				// Construct the input stream.
	RStoreReadStream instream;
	instream.OpenLC(iStore,iId);
				// Construct a CClassA object and restore from the stream
	iA = CClassA::NewL();
	instream >> *iA;
				// Construct the swizzle for the CClassB object. This
				// stream contains the id of the stream which 
				// actually contains the full CClassB object. The loading of
				// the CClassB object into memory is deferred until later.
				// The resulting swizzle represents the CClassB object as 
				// a streamid 
	instream >> iB;
				// Construct a CClassC object and restrore from the stream
	iC = CClassC::NewL();
	instream >> *iC;
				// Cleanup the stream object
	CleanupStack::PopAndDestroy();
	}


				// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
				// Loads the CClassB object into memory and changes the swizzle's
				// representation from "streamid" to "pointer".
				// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
void CClassABC::RestoreBL()
	{
				// Construct the input stream. Assumes we have the correct store (this
				// emphasizes the need to ensure that the store remain open)
	RStoreReadStream instream;
	instream.OpenLC(iStore,iB.AsId());
				// Construct a CClassB object and restore from the stream. The 
				// assignment: CClassB* to TSwizzle<CClassB> changes the
				// swizzle's representation of the CClassB object 
				// from "streamid" to "pointer"
	CClassB* ptrB = CClassB::NewLC();
	instream >> *ptrB;
	CleanupStack::Pop();
	iB = ptrB;
				// Cleanup the stream object			
	CleanupStack::PopAndDestroy();
	}	

//***************************************************************
//
// CClassA Implementation
//
//***************************************************************
CClassA* CClassA::NewL()
	{
	CClassA* self = CClassA::NewLC();
	CleanupStack::Pop();
	return self;
	}

CClassA* CClassA::NewLC()
	{
	CClassA* self = new (ELeave) CClassA;
	CleanupStack::PushL(self);
	return self;
	}

CClassA::~CClassA()
	{
	delete iVarBuf;
	}

void CClassA::ExternalizeL(RWriteStream& aStream) const
	{
	aStream.WriteInt32L(iVarBuf->Des().MaxLength());
	aStream << *iVarBuf;
	aStream.WriteInt32L(iIntValue);
	aStream.WriteUint32L(iUintValue);
	}  
 
void CClassA::InternalizeL(RReadStream& aStream)
	{
	TInt maxlen;
	maxlen     = aStream.ReadInt32L();
	iVarBuf    = HBufC::NewL(aStream,maxlen);
	iIntValue  = aStream.ReadInt32L();
	iUintValue = aStream.ReadUint32L();
	}  
	 	

//***************************************************************
//
// CClassB Implementation
//
//***************************************************************
CClassB* CClassB::NewLC()
	{
	CClassB* self = new (ELeave) CClassB;
	CleanupStack::PushL(self);
	return self;
	}

CClassB* CClassB::NewL()	
	{
	CClassB* self = CClassB::NewLC();
	CleanupStack::Pop();	
	return self;
	}

void CClassB::ExternalizeL(RWriteStream& aStream) const
	{
	aStream << iFixBuf;
	aStream.WriteInt32L(iIntValue);
	aStream.WriteUint32L(iUintValue);
	aStream.WriteReal64L(iRealValue);
	}  
 
void CClassB::InternalizeL(RReadStream& aStream)
	{
	aStream >> iFixBuf;
	iIntValue  = aStream.ReadInt32L();
	iUintValue = aStream.ReadUint32L();
	iRealValue = aStream.ReadReal64L();
	}  

//***************************************************************
//
// CClassC Implementation
//
//***************************************************************
CClassC* CClassC::NewL()
	{
	CClassC* self = CClassC::NewLC();
	CleanupStack::Pop();
	return self;
	}

CClassC* CClassC::NewLC()
	{
	CClassC* self = new (ELeave) CClassC;
	CleanupStack::PushL(self);
	return self;
	}

void CClassC::ExternalizeL(RWriteStream& aStream) const
	{
	aStream << iFixBuf;
	}  
 
void CClassC::InternalizeL(RReadStream& aStream)
	{
	aStream >> iFixBuf;
	}  
