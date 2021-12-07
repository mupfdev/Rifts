// StreamInStore.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.


// Example to demonstrate stream creation in a non persistent store. 
//
// The example:
//		constructs two different types of object,
//
//		writes them to a single stream contained in
//		the in-memory store (a CBufStore),
//
//      displays the contents of the objects,
//
//		deletes them from memory,
//
//		restores them from the store,
//  
//		displays the contents of the restored objects



#include "CommonStreamStore.h"
#include <s32file.h>
#include <s32mem.h>

//
// Format types and the newline character
//
_LIT(KTxtNewLine,"\n");
_LIT(KFormatType1,"\n%S, ");
_LIT(KFormatType2,"%d, ");
_LIT(KFormatType3,"%u, ");
_LIT(KFormatType4,"%u  ");
_LIT(KFormatType5,"%f  ");

				// Constructs an object of type CClassA and an object
				// of type CClassB, externalizes them to a
				// non-persistent store and then destroys the
				// CClassA object. 
LOCAL_C void doMakeAndStoreL(CStreamStore& aStore,TStreamId& anId);

				// Constructs "empty" CClassA and CClassB objects and
				// restores them from the in-memory store.
LOCAL_C void doRestoreL(CStreamStore& aStore,const TStreamId& anId);

				// Displays the contents of a CClassA object
class CClassA;
LOCAL_C void doShow(const TDesC& aHeading,const CClassA& anA);

				// Displays the contents of a CClassB object
class CClassB;
LOCAL_C void doShow(const TDesC& aHeading,const CClassB& aB);

				// definition of CClassA
class CClassA : public CBase
	{
public :
	static CClassA* NewLC();
	~CClassA();
	void     SetTextL(const TDesC& aData);
	void     ExternalizeL(RWriteStream& aStream) const;
	void     InternalizeL(RReadStream& aStream);
public :
	HBufC*   iVarBuffer;
	TInt     iIntValue;
	TUint    iUintValue;
	};

				// definition of CClassB
class CClassB : public CBase
	{
public :
	static CClassB* NewLC();
	void ExternalizeL(RWriteStream& aStream) const;
	void InternalizeL(RReadStream& aStream);
public :
	TBuf<32> iFixBuffer;
	TUint    iUintValue;
	TInt     iIntValue;
	TReal    iRealValue;
	};

//  Do the example
LOCAL_C void doExampleL()
    {
				// The stream id, kept in memory and used
				// to access the (one and only stream) in the
				// non-persistent store
	TStreamId theId;

				// construct a CBufStore, an in-memory 
				// non-persistent store.
	CStreamStore* store = CBufStore::NewLC(2 /*granularity*/);

	doMakeAndStoreL(*store,theId);
	doRestoreL(*store,theId);

				// destroy the CBufStore object
	CleanupStack::PopAndDestroy();
	}

LOCAL_C void doMakeAndStoreL(CStreamStore& aStore,TStreamId& anId)
	{
				// Construct an object of type CClassA and put some 
				// data into it
	_LIT(KTxtForClassA,"Text for CClassA");
	CClassA* theA = CClassA::NewLC();
	theA->SetTextL(KTxtForClassA);	
	theA->iIntValue  = -1;
	theA->iUintValue = 2;

				// Construct an object of type CClassB and put some 
				// data into it
	_LIT(KTxtForClassB,"Text for CClassB");
	CClassB* theB = CClassB::NewLC();
	theB->iFixBuffer = KTxtForClassB;
	theB->iIntValue  = -3;
	theB->iUintValue = 4; 
	theB->iRealValue = 5.6;

				// Show contents of the CClassA object
	_LIT(KTxtClassAContent,"CClassA content ...");
	doShow(KTxtClassAContent,*theA);

				// Show contents of the CClassB object
	_LIT(KTxtClassBContent,"CClassB content ...");
	doShow(KTxtClassBContent,*theB);					

				// Construct the output stream.
				// The stream id (there is only one) is kept
				// in memory.
	RStoreWriteStream outstream;
	anId = outstream.CreateLC(aStore);

				// Stream out the CClassA object first
	outstream  << *theA; 
				
				// Stream out the CClassB object second
	outstream  << *theB;

				// Equally we could have done:
				//		outstream << *theA << *theB;
				// to the same effect

				// Commit changes to the stream
	outstream.CommitL();

				// Cleanup the stream object.
				// Destroy the CClassB object,
				// Destroy the CClassA object,
	CleanupStack::PopAndDestroy(3);
	}

LOCAL_C void doRestoreL(CStreamStore& aStore,const TStreamId& anId)
	{
				// Construct "empty" CClassA and CClassB objects
	CClassA* theA = CClassA::NewLC();
	CClassB* theB = CClassB::NewLC();
	
				// Construct and open the input stream.
				// We want to access the one and only 
				// stream from the in-memory store.
	RStoreReadStream instream;
	instream.OpenLC(aStore,anId);

				// Stream in the CClassA object first and 
				// then stream in the CClassB object. This is the order
				// in which the objects were streamed out.
				//
				// NB the order in which the objects are streamed OUT to 
				// a single stream is arbitrary BUT, whatever the order 
				// chosen, the objects must be streamed in, in the SAME order
				// 
				// In this example, streaming in has assignment semantics.

	instream >> *theA;
	instream >> *theB; 

				// Equally we could have done:
				//		outstream >> *theA >> *theB;
				// to the same effect
	
				// Cleanup the stream object
	CleanupStack::PopAndDestroy();

				// Show restored contents of the CClassA object
	_LIT(KTxtRestoredClassA,"Restored CClassA content ...");
	doShow(KTxtRestoredClassA,*theA);

				// Show restored contents of the CClassB object
	_LIT(KTxtRestoredClassB,"Restored CClassB content ...");
	doShow(KTxtRestoredClassB,*theB);					

				// Destroy the CClassB object, 
				// Destroy the CClassA object, 
	CleanupStack::PopAndDestroy(2);
	}
									
LOCAL_C void doShow(const TDesC& aHeading,const CClassA& anA)
	{
	console->Printf(KTxtNewLine);
	console->Printf(aHeading);
	console->Printf(KFormatType1,anA.iVarBuffer);
	console->Printf(KFormatType2,anA.iIntValue);
	console->Printf(KFormatType4,anA.iUintValue);
	console->Printf(KTxtNewLine);
	}

LOCAL_C void doShow(const TDesC& aHeading,const CClassB& aB)
	{
	console->Printf(KTxtNewLine);
	console->Printf(aHeading);
	console->Printf(KFormatType1,&aB.iFixBuffer);
	console->Printf(KFormatType2,aB.iIntValue);
	console->Printf(KFormatType3,aB.iUintValue);
	console->Printf(KFormatType5,aB.iRealValue);
	console->Printf(KTxtNewLine);
	}


//***************************************************************
//***************************************************************
CClassA* CClassA::NewLC()
	{
	CClassA* self = new (ELeave) CClassA;
	CleanupStack::PushL(self);
	return self;
	}
	
CClassA::~CClassA()
	{
	delete iVarBuffer;
	}

void CClassA::SetTextL(const TDesC& aData)
	{
	iVarBuffer = aData.AllocL();	
	}

void CClassA::ExternalizeL(RWriteStream& aStream) const
	{
	aStream.WriteInt32L(iVarBuffer->Des().MaxLength());
	aStream << *iVarBuffer;
	aStream.WriteInt32L(iIntValue);
	aStream.WriteUint32L(iUintValue);
	}  
 
void CClassA::InternalizeL(RReadStream& aStream)
	{
	TInt maxlen;
	maxlen     = aStream.ReadInt32L();
	iVarBuffer = HBufC::NewL(aStream,maxlen);
	iIntValue  = aStream.ReadInt32L();
	iUintValue = aStream.ReadUint32L();
	}  
	 	

//***************************************************************
//***************************************************************
CClassB* CClassB::NewLC()
	{
	CClassB* self = new (ELeave) CClassB;
	CleanupStack::PushL(self);
	return self;
	}

void CClassB::ExternalizeL(RWriteStream& aStream) const
	{
	aStream << iFixBuffer;
	aStream.WriteInt32L(iIntValue);
	aStream.WriteUint32L(iUintValue);
	aStream.WriteReal64L(iRealValue);
	}  
 
void CClassB::InternalizeL(RReadStream& aStream)
	{
	aStream >> iFixBuffer;
	iIntValue  = aStream.ReadInt32L();
	iUintValue = aStream.ReadUint32L();
	iRealValue = aStream.ReadReal64L();
	}  
	 	



	
	
