// CompoundClass.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.

// Example to demonstrate the streaming of a compound object to
// a single stream.


#include "CommonStreamStore.h"
#include <s32file.h>

				// Constructs a CCompound object and externalizes
				// it to a single stream.
LOCAL_C void doMakeAndExternalizeL(const TDesC& aName);

				// Internalizes a CCompound object from
				// the stream
LOCAL_C void doInternalizeL(const TDesC& aName);

				// Displays content of a CCompound object
class CCompound;
LOCAL_C void doShow(const TDesC& aHeading,const CCompound& theSimple);

				// Defintion of classes used by the example
class CClassA
	{
public :
	void ExternalizeL(RWriteStream& aStream) const;
	void InternalizeL(RReadStream& aStream);
public :
	TBuf<32> iBufferA;
	TInt     iXA;
	TUint    iYA;
	};


class CClassB
	{
public :
	void ExternalizeL(RWriteStream& aStream) const;
	void InternalizeL(RReadStream& aStream);
public :
	TBuf<32> iBufferB;
	};


class TClassC
	{
public :
	void ExternalizeL(RWriteStream& aStream) const;
	void InternalizeL(RReadStream& aStream);
public :
	TReal iZC;
	};

	
class CCompound : public CBase
	{
public :
	~CCompound();
	static		CCompound* NewLC();
	static		CCompound* NewLC(CStreamStore& aStore,TStreamId anId);
	static		CCompound* NewL(CStreamStore& aStore,TStreamId anId);
	TStreamId	StoreL(CStreamStore& store);
	void		RestoreL(CStreamStore& aStore,TStreamId anId);
	void		InternalizeL(RReadStream& aStream);
	void		ExternalizeL(RWriteStream& aStream) const;
private:
    void		ConstructL();
	void		ConstructL(CStreamStore& aStore,TStreamId anId);
public :
	CClassA* iCa;
	CClassB* iCb;
	TClassC  iTc;
	};
	 
// The file name, extension and path for the file store
	_LIT(KFullNameOfFileStore,"C:\\epoc32ex\\data\\stcompnd.dat");


// Do the example
LOCAL_C void doExampleL()
    {
					    // make sure directory exists
	fsSession.MkDirAll(KFullNameOfFileStore);
	doMakeAndExternalizeL(KFullNameOfFileStore);
	doInternalizeL(KFullNameOfFileStore);
	}

LOCAL_C void doMakeAndExternalizeL(const TDesC& aName)
	{
	TParse	filestorename;

	fsSession.Parse(aName,filestorename);
				// construct file store object - the file to contain the
				// the store replaces any existing file of the same name.
	CFileStore* store = CDirectFileStore::ReplaceLC(fsSession,filestorename.FullName(),EFileWrite);

				// Must say what kind of file store
    store->SetTypeL(KDirectFileStoreLayoutUid);

				// Construct an object of type CCompound 
				// and put some data into it.
	CCompound* thecompound = CCompound::NewLC();

	_LIT(KTxtClassAText,"CClassA text");
	_LIT(KTxtClassBText,"CClassB text");

	thecompound->iCa->iBufferA = KTxtClassAText;
	thecompound->iCa->iXA      = -1;
	thecompound->iCa->iYA      = 2;
	thecompound->iCb->iBufferB = KTxtClassBText;
	thecompound->iTc.iZC       = 3.456;

				// Show contents of the CCompound object (and its
				// components)
	_LIT(KTxtInitialContent,"... Initial content of CCompound");
	doShow(KTxtInitialContent,*thecompound);
					
				// Store the compound object to a single stream
				// and save the stream id as the root id. 
	TStreamId  id = thecompound->StoreL(*store);

				// Set the stream id as the root
	store->SetRootL(id);

				// Commit changes to the store
	store->CommitL();

				// Destroy:
				// 1. the CCompound object
				// 2. the store object (this also closes 
				//    the file containing the store)
				// Remove both from the cleanup stack
	CleanupStack::PopAndDestroy(2);
	}

LOCAL_C void doInternalizeL(const TDesC& aName)
	{
	TParse	filestorename;
	
	fsSession.Parse(aName,filestorename);
				// construct file store object - specifying the file
				// containing the store.
	CFileStore* store = CDirectFileStore::OpenLC(fsSession,filestorename.FullName(),EFileRead);
	
				// Construct a CCompound object  
				// from the root stream created earlier.
	CCompound* thecompound = CCompound::NewL(*store,store->Root());

				// Show contents of the CCompound object (and its
				// components)
	_LIT(KTxtRestoredContent,"... Restored CCompound content.");
	doShow(KTxtRestoredContent,*thecompound);
				
				// destroy the store object (this also closes the file
				// containing the store) 
	CleanupStack::PopAndDestroy();

				// Now destroy the CCompound object
	delete thecompound;
	}

_LIT(KTxtNewLine,"\n");
_LIT(KFormatType1,"\n%d");
_LIT(KFormatType2,"\n%S");
_LIT(KFormatType3,"\n%u");
_LIT(KFormatType4,"\n%f");

LOCAL_C void doShow(const TDesC& aHeading,const CCompound& aCompound)
	{
	console->Printf(KTxtNewLine);
	console->Printf(aHeading);
	console->Printf(KFormatType2,&aCompound.iCa->iBufferA);
	console->Printf(KFormatType1,aCompound.iCa->iXA);
	console->Printf(KFormatType3,aCompound.iCa->iYA);
	console->Printf(KFormatType2,&aCompound.iCb->iBufferB);
	console->Printf(KFormatType4,aCompound.iTc.iZC);
	console->Printf(KTxtNewLine);
	}

//***************************************************************
//***************************************************************

				// The CCompound destructor
CCompound::~CCompound()
	{
	delete iCa;
	delete iCb;
	}

				// Construct a new plain CCompound object and
				// place on the cleanup stack.
CCompound* CCompound::NewLC()
	{
	CCompound* self=new (ELeave) CCompound;
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

				// Complete the construction of the 
				// plain CCompound object
void CCompound::ConstructL()
	{
	iCa = new (ELeave) CClassA;
	iCb = new (ELeave) CClassB;
	}

				// Construct a new CCompound object from 
				// the input stream.
CCompound* CCompound::NewL(CStreamStore& aStore,TStreamId anId)
	{
	CCompound* self=CCompound::NewLC(aStore,anId);
	CleanupStack::Pop();
	return self;
	}

				// Construct a new CCompound object from 
				// the root stream of the store and 
				// place on the cleanup stack.
CCompound* CCompound::NewLC(CStreamStore& aStore,TStreamId anId)
	{
	CCompound* self=new (ELeave) CCompound;
	CleanupStack::PushL(self);
	self->ConstructL(aStore,anId);
	return self;
	}

				// Complete the construction of the 
				// CCompound object
void CCompound::ConstructL(CStreamStore& aStore,TStreamId anId)
	{
	iCa = new (ELeave) CClassA;
	iCb = new (ELeave) CClassB;
	RestoreL(aStore,anId);
	}

void CCompound::RestoreL(CStreamStore& aStore,TStreamId anId)
	{
	RStoreReadStream instream;
	instream.OpenLC(aStore,anId);
	InternalizeL(instream);
					// Cleanup the stream object.
	CleanupStack::PopAndDestroy();			
	}

				// Read the components and data members 
				// of the CCompound object from the stream.
void CCompound::InternalizeL(RReadStream& aStream)
	{
	aStream >> *iCa;	
	aStream >> *iCb;
	aStream >> iTc;
	}

TStreamId CCompound::StoreL(CStreamStore& aStore)
	{
	RStoreWriteStream outstream;
	TStreamId id = outstream.CreateLC(aStore);
				// Stream out this CCompound object
	ExternalizeL(outstream);
				// Commit changes to the stream
	outstream.CommitL();
				// Cleanup the stream object.
	CleanupStack::PopAndDestroy();
	return id;
	}
				// Write the components and data members 
				// of the CCompound object to the stream
void CCompound::ExternalizeL(RWriteStream& aStream) const
	{
	aStream << *iCa;
	aStream << *iCb;
	aStream << iTc;
	}

//***************************************************************
//***************************************************************

				// Read the data members of the CClassA 
				// object from the stream.
void CClassA::InternalizeL(RReadStream& aStream)
	{
	aStream >> iBufferA;
  	iXA = aStream.ReadInt32L();
	iYA = aStream.ReadUint32L();
	}  
				// Write the data members of the CClassA 
				// object to the stream.
void CClassA::ExternalizeL(RWriteStream& aStream)const
	{
	aStream << iBufferA;
	aStream.WriteInt32L(iXA);
	aStream.WriteUint32L(iYA);
	}  

//***************************************************************
//***************************************************************

				// Read the data member(s) of the CClassB 
				// object from the stream.
void CClassB::InternalizeL(RReadStream& aStream)
	{
	aStream >> iBufferB;
  	}
				// Write the data member(s) of the CClassB 
				// object to the stream.
void CClassB::ExternalizeL(RWriteStream& aStream) const
	{
	aStream << iBufferB;
	}  

//***************************************************************
//***************************************************************

				// Write the data member(s) of the TClassC 
				// object to the stream.
void TClassC::ExternalizeL(RWriteStream& aStream) const
	{
	aStream.WriteReal64L(iZC);
	}  
				// Read the data member(s) of the TClassC 
				// object from the stream.
void TClassC::InternalizeL(RReadStream& aStream)
	{
	iZC = aStream.ReadReal64L();
	}  
	 	



	
	
