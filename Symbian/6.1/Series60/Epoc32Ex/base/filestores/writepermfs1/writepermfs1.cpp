// WritePermFS1.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.

// Example constructs and writes a network of objects to a permanent file store.
//
// Each object is then loaded back in, one at a time, its content displayed at the 
// console and then destroyed.
//
// The CClassR object is changed and stored back before it is destroyed 
//
// The order in which the objects are loaded from the store is different from the order
// in which they were initially created.
// The example creates an index of "top level" stream ids. The index is stored in its
// own stream and forms the root stream of the store. 
//
//
// The example:
//      creates a permanent file store (replacing any existing permanent 
//      file store of the same name)
//
//		constructs a TExampleIndex object
//
//      constructs a CClassP object, externalizes it in its own stream, 
//		saves the stream id in the index and then destroys the 
//      CClassP object
//				
//      constructs a CClassR object, externalizes it in its own stream, 
//		saves the stream id in the index and then destroys the 
//      CClassR object
//	
//		constructs a CClassABC container object containing a CClassA, 
//		a CClassB and a CClassC object and then completes the construction
//		of these contained objects.
//      The CClassB object is externalized in its own stream. The CClassA, the streamid of the
//      CClassB object and the CClassC object are externalized in a single
//      stream and this streamid is saved into the index
//
//		externalizes the TExampleIndex object in its own stream and makes
//		this stream the root stream of the file store.
//
//      closes the permanent file store.
//
//			========================================================
//
//      re-opens the permanent file store
//
//		restores the TExampleIndex object from the root stream
//
//		restores the CClassR object from its stream, displays the content,
//      changes the content, replaces the stream and then destroys the object from
//      memory
//
//		restores the CClassR object for a second time from its stream, displays 
//		the (updated) content and then destroys the object from memory again
//
//		restores the CClassABC container object; in effect, this restores 
//		its contained CClassA and CClassC objects and the stream id of its
//		CClassB object. The CClassB object is not restored into memory until 
//		it is needed. 
//
//		displays the content of the CClassA, CClassB and CClassC objects; it is
//	    at this time that the CClassB object is restored into memory.
//
//		restores the CClassP object from its stream and displays its contents
//		and then destroys it
//
//		(NB that the order in which the objects are restored is different to 
//      the order in which their corresponding streams were created)
//
//      closes the permanent file store.
//
// Notes:
//		The file name and extension of the permanent file store is 
//      "WritePermFS.dat"and will be created in c:\epoc32ex\data\ 
//
#include "WritePermFS1.h"

//***************************************************************
//
// Implementations
//
//***************************************************************


// The file name, extension and path for the file store
_LIT(KFullNameOfFileStore,"C:\\epoc32ex\\data\\WritePermFS.dat");

				//  Do the example
LOCAL_C void doExampleL()
    {
				// make sure directory exists
	fsSession.MkDirAll(KFullNameOfFileStore);
	doMakeL(KFullNameOfFileStore);
	doUseL(KFullNameOfFileStore);
	}
 

LOCAL_C void doMakeL(const TDesC& aName)
	{
				// Create (replace, if it exists) the permanent file store
	TParse	filestorename;
	fsSession.Parse(aName,filestorename);
	CFileStore* store = CPermanentFileStore::ReplaceLC(fsSession,filestorename.FullName(),EFileWrite);

				// Must say what kind of file store.
	store->SetTypeL(KPermanentFileStoreLayoutUid);

				// Create a TExampleIndex object to hold the stream ids of all
				// the component streams
	TExampleIndex theIndex;

				// Construct the CClassP object, putting some data into it, 
				// write it to its own stream and save the stream id in
				// the index.
				// Destroy the CClassP object after stream creation
	_LIT(KTxtDataForClassP,"Data for CClassP - PPPPP");
	CClassP* theP = CClassP::NewLC(KTxtDataForClassP,*store);
	theIndex.iPid = theP->StoreL();
	CleanupStack::PopAndDestroy();
	
				// Construct the CClassR object, put some data into it, 
				// write it to its own stream and save the stream id in
				// the index.
				// Destroy the CClassR object after stream creation
	_LIT(KTxtDataForClassR,"Data for the CClassR - RRRRR");
	CClassR* theR = CClassR::NewLC(KTxtDataForClassR,*store);
	theIndex.iRid = theR->StoreL();
	CleanupStack::PopAndDestroy();							
				
				// Construct the container object for CClassA,CClassB and CClassC.
				// Complete the construction of the contained CClassA, CClassB
				// and CClassC objects.
				//  
				// Write out this object network and save the top level stream id
				// in the index.
				// Destroy this object network after stream creation
	_LIT(KTxtDataForClassA,"Data for the CClassA - AAAAA");
	_LIT(KTxtDataForClassB,"Data for the CClassB - BBBBB");
	_LIT(KTxtDataForClassC,"Data for the CClassC - CCCCC");

	CClassABC* theABC = CClassABC::NewLC(*store);
	theABC->ConstructAL(KTxtDataForClassA,-1,2);
	theABC->ConstructB(KTxtDataForClassB,-3,4,5.6);
	theABC->ConstructC(KTxtDataForClassC);
	theIndex.iABCid = theABC->StoreL();
	CleanupStack::PopAndDestroy();							

				// Now write the index itself to its own stream ...
	TStreamId id  = theIndex.StoreL(*store);

				// ... and make this stream the root stream
	store->SetRootL(id);

				// Now commit all changes to the store
	store->CommitL();
			
				// Destroy the permanent file store object (closes the file)
	CleanupStack::PopAndDestroy();	
	}


LOCAL_C void doUseL(const TDesC& aName)
	{
				// Open the permanent file store
	TParse	filestorename;
	fsSession.Parse(aName,filestorename);
	CFileStore* store = CPermanentFileStore::OpenLC(fsSession,filestorename.FullName(),EFileRead|EFileWrite);

				// Restore the index of streamids so that we can access (restore)
				// all the other objects. The index is found in the root stream 
	TExampleIndex theIndex;
	theIndex.RestoreL(*store,store->Root());
				
				// Restore the CClassR object, display the content, make a change and
				// update the stream to reflect the changed content.
				// If updating the stream succeeds, commit the changes to the store
				// otherwise attempt to revert the store to its state at the last
				// commit point.
				// Destroy the CClassR object.
	CClassR* theR;

	_LIT(KTxtClassRContent,"CClassR content ...");
	_LIT(KTxtNewForClassR,"New data for the CClassR +++++++");

	theR = CClassR::NewLC(*store,theIndex.iRid);
	doShow(KTxtClassRContent,*theR);
	theR->ChangeDataL(KTxtNewForClassR);
	CleanupStack::PopAndDestroy();
				
				// Restore the CClassR object again, display the content and
				// then destroy it
	_LIT(KTxtUpadtedClassR,"Updated CClassR content ...");

	theR = CClassR::NewLC(*store,theIndex.iRid);
	doShow(KTxtUpadtedClassR,*theR);
	CleanupStack::PopAndDestroy();

				// Restore the CClassABC and display content of all contained objects.
				// Note that the loading of the CClassB object is deferred until it 
				// is needed.
				// Destroy the CClassABC 
	_LIT(KTxtShowClassA,"CClassA content ...");
	_LIT(KTxtShowClassB,"CClassB content ...");
	_LIT(KTxtShowClassC,"CClassC content ...");

	CClassABC* theABC = CClassABC::NewLC(*store,theIndex.iABCid);
	doShow(KTxtShowClassA,*theABC->PtrA());
	doShow(KTxtShowClassB,*theABC->PtrB());// CClassB object is loaded at this point
	doShow(KTxtShowClassC,*theABC->PtrC());	
	CleanupStack::PopAndDestroy();

				// Restore the CClassP object, display the content and
				// then destroy it;
	_LIT(KTxtShowClassP,"CClassP content ...");

	CClassP* theP = CClassP::NewLC(*store,theIndex.iPid);
	doShow(KTxtShowClassP,*theP);
	CleanupStack::PopAndDestroy();

				// Destroy the permanent file store object (closes the file) 
	CleanupStack::PopAndDestroy();
	} 

_LIT(KTxtNewLine,"\n");
_LIT(KFormatType1,"\n%S, ");
_LIT(KFormatType2,"%d, ");
_LIT(KFormatType3,"%u  ");
_LIT(KFormatType4,"%u, ");
_LIT(KFormatType5,"%f  ");
									
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

LOCAL_C void doShow(const TDesC& aHeading,const CClassP& aP)
	{
	console->Printf(KTxtNewLine);
	console->Printf(aHeading);
	console->Printf(KFormatType1,&aP.iFixBuf);
	console->Printf(KTxtNewLine);
	}

LOCAL_C void doShow(const TDesC& aHeading,const CClassR& aR)
	{
	console->Printf(KTxtNewLine);
	console->Printf(aHeading);
	console->Printf(KFormatType1,&aR.iFixBuf);
	console->Printf(KTxtNewLine);
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

CClassABC* CClassABC::NewLC(CStreamStore& aStore, TStreamId anId)
	{															
	CClassABC* self = new (ELeave) CClassABC(aStore,anId);
	CleanupStack::PushL(self);
	self->RestoreL();
	return self;
	}
		
void CClassABC::ConstructL()
	{
	iA = CClassA::NewL();
	iB = CClassB::NewL();// assigns CClassB* to TSwizzle<CClassB>. Uses TSwizzle operator=(T*)
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

//***************************************************************
//
// CClassP Implementation
//
//***************************************************************
CClassP::CClassP(CStreamStore& aStore)
	: iStore(aStore)
	{}

CClassP::CClassP(CStreamStore& aStore,TStreamId anId)
	: iStore(aStore), iId(anId)
	{}

CClassP* CClassP::NewLC(const TDesC& aData,CStreamStore& aStore)
	{
	CClassP* self = new (ELeave) CClassP(aStore);
	CleanupStack::PushL(self);
	self->Construct(aData);
	return self;
	}

CClassP* CClassP::NewLC(CStreamStore& aStore, TStreamId anId)
	{
	CClassP* self = new (ELeave) CClassP(aStore,anId);
	CleanupStack::PushL(self);
	self->RestoreL();
	return self;
	}

void CClassP::Construct(const TDesC& aData)
	{
	iFixBuf = aData;
	}

void CClassP::RestoreL()
	{
	RStoreReadStream instream;
	instream.OpenLC(iStore,iId);
	InternalizeL(instream);			// or we can say instream >> *this;
	CleanupStack::PopAndDestroy();	
	}

TStreamId CClassP::StoreL()
	{
	RStoreWriteStream outstream;
	TStreamId id = outstream.CreateLC(iStore);
	ExternalizeL(outstream);		// or we can say outstream << *this;
	outstream.CommitL();
	CleanupStack::PopAndDestroy();	
	return id;
	}

void CClassP::ExternalizeL(RWriteStream& aStream) const
	{
	aStream << iFixBuf;
	}  
 
void CClassP::InternalizeL(RReadStream& aStream)
	{
	aStream >> iFixBuf;
	}  


//***************************************************************
//
// CClassR Implementation
//
//***************************************************************
CClassR::CClassR(CStreamStore& aStore)
	: iStore(aStore)
	{}

CClassR::CClassR(CStreamStore& aStore,TStreamId anId)
	: iStore(aStore), iId(anId)
	{}

CClassR* CClassR::NewLC(const TDesC& aData,CStreamStore& aStore)
	{
	CClassR* self = new (ELeave) CClassR(aStore);
	CleanupStack::PushL(self);
	self->Construct(aData);
	return self;
	}

CClassR* CClassR::NewLC(CStreamStore& aStore, TStreamId anId)
	{
	CClassR* self = new (ELeave) CClassR(aStore,anId);
	CleanupStack::PushL(self);
	self->RestoreL();
	return self;
	}

void CClassR::Construct(const TDesC& aData)
	{
	iFixBuf = aData;
	}

_LIT(KTxtFailedMsg,"Failed to update CClassR stream\n");

void CClassR::ChangeDataL(const TDesC& aData)
	{
	iFixBuf = aData;
	TRAPD(error,UpdateStoreL());
	if (error!=KErrNone)
		{
		iStore.Revert();
		console->Printf(KTxtFailedMsg);
		User::Leave(error);
		}
	}
		
void CClassR::RestoreL()
	{
	RStoreReadStream instream;
	instream.OpenLC(iStore,iId);
	InternalizeL(instream);			// or we can say instream >> *this;
	CleanupStack::PopAndDestroy();	
	}

TStreamId CClassR::StoreL()
	{
	RStoreWriteStream outstream;
	TStreamId id = outstream.CreateLC(iStore);
	ExternalizeL(outstream);		// or we can say outstream << *this;
	outstream.CommitL();
	CleanupStack::PopAndDestroy();	
	return id;
	}

void CClassR::UpdateStoreL()
	{
	RStoreWriteStream outstream;
	outstream.ReplaceLC(iStore,iId);
	ExternalizeL(outstream);		// or we can say outstream << *this;
	outstream.CommitL();
	CleanupStack::PopAndDestroy();
	iStore.CommitL();// commit the changes to the store
	}

void CClassR::ExternalizeL(RWriteStream& aStream) const
	{
	aStream << iFixBuf;
	}  
 
void CClassR::InternalizeL(RReadStream& aStream)
	{
	aStream >> iFixBuf;
	}  

//***************************************************************
//
// TExampleIndex Implementation
//
//***************************************************************

TStreamId TExampleIndex::StoreL(CStreamStore& aStore)
	{
	RStoreWriteStream outstream;
	TStreamId id = outstream.CreateLC(aStore);
	ExternalizeL(outstream);		// or we can say outstream << *this;
	outstream.CommitL();
	CleanupStack::PopAndDestroy();	
	return id;
	}

void TExampleIndex::RestoreL(CStreamStore& aStore, TStreamId anId)
	{
	RStoreReadStream instream;
	instream.OpenLC(aStore,anId);
	InternalizeL(instream);
	CleanupStack::PopAndDestroy();	
	}

void TExampleIndex::ExternalizeL(RWriteStream& aStream) const
	{
	aStream << iPid;
	aStream << iRid;
	aStream << iABCid;
	}  

void TExampleIndex::InternalizeL(RReadStream& aStream)
	{
	aStream >> iPid;
	aStream >> iRid;
	aStream >> iABCid;
	}  
