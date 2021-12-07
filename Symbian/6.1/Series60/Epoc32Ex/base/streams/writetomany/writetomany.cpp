// WriteToMany.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
//


// Example to demonstrate how a network of objects can be written 
// to more than one stream in a direct file store, and how the loading
// of an object from the store into memory may be deferred.
//
// The example:
//      creates a direct file store (replacing any existing direct 
//      file store of the same name)
//
//		constructs a CClassABC container object and then constructs a 
//      contained CClassA, CClassB and CClassC object.
//
//		Displays the content of the CClassA, CClassB and CClassC objects
//
//		externalizes the CClassB object in its own stream and  keeps hold of the
//      stream id. Externalizes the CClassA object, the streamid of the
//      CClassB object and the CClassC object in a single
//      stream. Makes this latter stream the root stream of the store
//
//		closes the store and deletes the container and its contained CClassA, 
//		CClassB and CCLassC objects (from memory)
//
//			========================================================
//
//      re-opens the direct file store
//
//		restores the CClassABC container object; in effect, this restores 
//		its contained CClassA and CClassC objects and the stream id of its
//		CClassB object. The CClassB object is not restored into memory until 
//		it is needed.
//
//		displays the content of the CClassA, CClassB and CClassC objects; it is
//	    at this time that the CClassB object is restored into memory. (This 
//		illustrates the necessity of keeping the store open.
//
//		closes the store and deletes the container and its contained CClassA, 
//		CClassB and CCLassC objects (from memory)
//
// Notes:
//		The file name and extension of the direct file store is "WriteToMany.dat".
//      and will be created in c:\data\ 
//
#include "WriteToMany.h"


//***************************************************************
//
// Implementations
//
//***************************************************************


// The file name, extension and path for the file store
_LIT(KFullNameOfFileStore,"C:\\epoc32ex\\data\\WriteToMany.dat");


				//  Do the example
LOCAL_C void doExampleL()
    {
			    // make sure directory exists
	fsSession.MkDirAll(KFullNameOfFileStore);
	doMakeAndStoreL(KFullNameOfFileStore);
	doRestoreL(KFullNameOfFileStore);
	}
 

LOCAL_C void doMakeAndStoreL(const TDesC& aName)
	{
				// Create (replace, if it exists) the direct file store
	TParse	filestorename;
	fsSession.Parse(aName,filestorename);
	CFileStore* store = CDirectFileStore::ReplaceLC(fsSession,filestorename.FullName(),EFileWrite);

				// Must say what kind of file store.
	store->SetTypeL(KDirectFileStoreLayoutUid);

				// Construct the container object for CClassA,CClassB and CClassC.
				// Complete the construction of the contained CClassA, CClassB
				// and CClassC objects.
	_LIT(KTxtDataForClassA,"Data for the CClassA - AAAAA");
	_LIT(KTxtDataForClassB,"Data for the CClassB - BBBBB");
	_LIT(KTxtDataForClassC,"Data for the CClassC - CCCCC");

	CClassABC* theABC = CClassABC::NewLC(*store);
	theABC->ConstructAL(KTxtDataForClassA,-1,2);
	theABC->ConstructB(KTxtDataForClassB,-3,4,5.6);
	theABC->ConstructC(KTxtDataForClassC);

				// Show contents of the CClassA, CClassB & CClassC objects
	_LIT(KTxtClassAContent,"CClassA content ...");
	_LIT(KTxtClassBContent,"CClassB content ...");
	_LIT(KTxtClassCContent,"CClassC content ...");

	doShow(KTxtClassAContent,*theABC->PtrA());
	doShow(KTxtClassBContent,*theABC->PtrB());					
	doShow(KTxtClassCContent,*theABC->PtrC());					

				// Store the object network by:
				// storing the CClassB object in its own stream and 
				// then storing:
				//		the CClassA object
				//		the streamid of the CClassB object
				//      the CClassC object
				// in a separate stream.
  	TStreamId id = theABC->StoreL();			
	
  				// Set this stream id as the root stream
	store->SetRootL(id);

				// Destroy:
				//		the container object.
				//		the direct file store object (closes the file),
				//		
	CleanupStack::PopAndDestroy(2);	
	}


LOCAL_C void doRestoreL(const TDesC& aName)
	{
				// Open the direct file store
	TParse	filestorename;
	fsSession.Parse(aName,filestorename);
	CFileStore* store = CDirectFileStore::OpenLC(fsSession,filestorename.FullName(),EFileRead);

				// Restore the container object from the root stream.
				// This constructs a CClassA and a CClassC object 
				// and restores them from the root stream. 
				// The swizzle for the CClassB object is
				// constructed from the streamid in the root stream.
				// Note that the CClassB object itself is not loaded into 
				// memory until it is needed.
	CClassABC* theABC = CClassABC::NewLC(*store,store->Root());

				// Show restored contents of the CClassA, CClassB and CClassC
				// objects. Note that the CClassB object may not be in memory and
				// will be loaded in when needed.
	_LIT(KTxtRestoredClassA,"Restored CClassA content ...");
	_LIT(KTxtRestoredClassB,"Restored CClassB content ...");
	_LIT(KTxtRestoredClassC,"Restored CClassC content ...");

	doShow(KTxtRestoredClassA,*theABC->PtrA());
	doShow(KTxtRestoredClassB,*theABC->PtrB());					
	doShow(KTxtRestoredClassC,*theABC->PtrC());	
				
				// Destroy:
				//		the CClassABC object, 
				//      the direct file store object (closes the file) 
	CleanupStack::PopAndDestroy(2);
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
