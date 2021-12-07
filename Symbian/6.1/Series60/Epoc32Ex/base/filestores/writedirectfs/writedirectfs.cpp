// WriteDirectFS.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.

// Example to demonstrate writing out a network of objects
// to a direct file store and then loading them all back in.
//
// Demonstrates the persistence of a direct file store and the idea
// of the root stream. 
//
// The example:
//		constructs three different types of object,
//
//      puts data into the objects,
//
//      displays the content of the objects,
//
//      creates a direct file store (replacing any existing direct 
//      file store of the same name),
//
//		writes the objects to a single stream,
//
//      makes this stream the root stream,
//
//		closes the store and deletes the objects (from memory),
//
//      re-opens the store and restores the objects from the root stream,
//
//		displays the contents of the restored objects
//
//
// Notes:
//		The file name and extension of the direct file store is 
// "WriteDirectFS.dat" and will be created in c:\data\ 


#include "CommonStreamStore.h"
#include <s32file.h>
	

				// Constructs objects of type CClassA, CClassB and CClassC,
				// externalizes them to a direct file store and then destroys the
				// CClassA, CClassB and CClassC objects. 
LOCAL_C void doMakeAndStoreL(const TDesC& aName);

				// Constructs "empty" CClassA, ClassB and CCLassC objects and
				// restores them from the direct file store.
LOCAL_C void doRestoreL(const TDesC& aName);

				// Displays the contents of a CClassA object
class CClassA;
LOCAL_C void doShow(const TDesC& aHeading,const CClassA& anA);

				// Displays the contents of a CClassB object
class CClassB;
LOCAL_C void doShow(const TDesC& aHeading,const CClassB& aB);

				// Displays the contents of a CClassB object
class CClassC;
LOCAL_C void doShow(const TDesC& aHeading,const CClassC& aC);

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

// definition of CClassC

#define KStdirectClassCGranularity 4

class CClassC : public CBase
	{
public :
	static CClassC* NewLC();
	~CClassC();
	void     ConstructL();
	void     AddNumberToArrayL(TInt aValue);
	void     ExternalizeL(RWriteStream& aStream) const;
	void     InternalizeL(RReadStream& aStream);
public :
	TBuf<32> iFixBuffer;
	CArrayFixFlat<TInt>* iArray;
	};



// The file name, extension and path for the file store
	_LIT(KFullNameOfFileStore,"C:\\epoc32ex\\data\\WriteDirectFS.dat");

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

				// Construct an object of type CClassC and put some 
				// data into it
	_LIT(KTxtForClassC,"Text for CClassC");
	CClassC* theC = CClassC::NewLC();
	theC->iFixBuffer = KTxtForClassC;	
	theC->AddNumberToArrayL(21);
	theC->AddNumberToArrayL(42);
	theC->AddNumberToArrayL(101);

				// Show contents of the CClassA object
	_LIT(KTxtClassAContent,"CClassA content ...");
	doShow(KTxtClassAContent,*theA);

				// Show contents of the CClassB object
	_LIT(KTxtClassBContent,"CClassB content ...");
	doShow(KTxtClassBContent,*theB);					

				// Show contents of the CClassC object
	_LIT(KTxtClassCContent,"CClassC content ...");
	doShow(KTxtClassCContent,*theC);					
				
				// Create (replace) the direct file store
	TParse	filestorename;
	fsSession.Parse(aName,filestorename);
	CFileStore* store = CDirectFileStore::ReplaceLC(fsSession,filestorename.FullName(),EFileWrite);

				// Must say what kind of file store.
	store->SetTypeL(KDirectFileStoreLayoutUid);
    	
				// Construct the output stream.
	RStoreWriteStream outstream;
	TStreamId id = outstream.CreateLC(*store);

				// Stream out the CClassA object, the
				// CClassB object and the CClassC object
	outstream  << *theA << *theB << *theC; 

				// Equally we could have done:
				//		outstream << *theA;
				//		outstream << *theB;
				//      outstream << *theC;
				// to the same effect
				
				// The order in which the objects are written out is
				// arbitrary, but it is important to note that 
				// THE ORDER IN WHICH THEY ARE WRITTEN OUT IS THE SAME
				// AS THE ORDER IN WHICH THEY WILL BE READ IN LATER !
				
				// Commit changes to the stream
	outstream.CommitL();

	            // Cleanup the stream object
    CleanupStack::PopAndDestroy();

				// Set this stream id as the root
	store->SetRootL(id);

				// Commit changes to the store
	store->CommitL();

				// Destroy the direct file store object (closes the file),
				// Destroy the CClassC object,
				// Destroy the CClassB object,
				// Destroy the CClassA object.
	CleanupStack::PopAndDestroy(4);	
	}

LOCAL_C void doRestoreL(const TDesC& aName)
	{
				// Construct "empty" CClassA, CClassB and CClassC objects
	CClassA* theA = CClassA::NewLC();
	CClassB* theB = CClassB::NewLC();
	CClassC* theC = CClassC::NewLC();
					
				// Open the direct file store
	TParse	filestorename;
	fsSession.Parse(aName,filestorename);
	CFileStore* store = CDirectFileStore::OpenLC(fsSession,filestorename.FullName(),EFileRead);

				// Construct and open the root stream which 
				// contains the representation of our objects.
	RStoreReadStream instream;
	instream.OpenLC(*store,store->Root());
	
				// Stream in the CClassA object, the
				// CClassB object and the CClassC object
	instream  >> *theA >> *theB >> *theC; 

				// Equally we could have done:
				//		instream >> *theA;
				//		instream >> *theB;
				//      instream >> *theC;
				// to the same effect

				// Cleanup the stream object
	CleanupStack::PopAndDestroy();

				// Show restored contents of the CClassA object
	_LIT(KTxtRestoredCClassA,"Restored CClassA content ...");
	doShow(KTxtRestoredCClassA,*theA);

				// Show restored contents of the CClassB object
	_LIT(KTxtRestoredCClassB,"Restored CClassB content ...");
	doShow(KTxtRestoredCClassB,*theB);					

				// Show restored contents of the CClassC object
	_LIT(KTxtRestoredCClassC,"Restored CClassC content ...");
	doShow(KTxtRestoredCClassC,*theC);	
				
				// Destroy the direct file store object (closes the file) 
				// Destroy the CClassC object, 
				// Destroy the CClassB object, 
				// Destroy the CClassA object, 
	CleanupStack::PopAndDestroy(4);
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
	console->Printf(KFormatType1,anA.iVarBuffer);
	console->Printf(KFormatType2,anA.iIntValue);
	console->Printf(KFormatType3,anA.iUintValue);
	console->Printf(KTxtNewLine);
	}

LOCAL_C void doShow(const TDesC& aHeading,const CClassB& aB)
	{
	console->Printf(KTxtNewLine);
	console->Printf(aHeading);
	console->Printf(KFormatType1,&aB.iFixBuffer);
	console->Printf(KFormatType2,aB.iIntValue);
	console->Printf(KFormatType4,aB.iUintValue);
	console->Printf(KFormatType5,aB.iRealValue);
	console->Printf(KTxtNewLine);
	}

_LIT(KTxtNoArrayItems,"<No array items>");
_LIT(KTxtColonsep,": ");
_LIT(KTxtCommasep,", ");
_LIT(KFormatType6,"%d array item(s)");
_LIT(KFormatType7,"%S%d");

LOCAL_C void doShow(const TDesC& aHeading,const CClassC& aC)
	{
	console->Printf(KTxtNewLine);
	console->Printf(aHeading);
	console->Printf(KFormatType1,&aC.iFixBuffer);
	
	TInt count = aC.iArray->Count();
	if (!count)
		console->Printf(KTxtNoArrayItems);
	else
		{
		TPtrC   ptr;
		ptr.Set(KTxtColonsep);
		console->Printf(KFormatType6,count);
		for (TInt index = 0; index < count; index++)
			{
			console->Printf(KFormatType7,&ptr,(*aC.iArray)[index]);
			ptr.Set(KTxtCommasep);		
			}
		}
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


//***************************************************************
//***************************************************************
CClassC* CClassC::NewLC()
	{
	CClassC* self = new (ELeave) CClassC;
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}
	
void CClassC::ConstructL()
	{
	iArray = new (ELeave) CArrayFixFlat<TInt>(KStdirectClassCGranularity);
	}

void CClassC::AddNumberToArrayL(TInt aValue)
	{
	iArray->AppendL(aValue);
	}

CClassC::~CClassC()
	{
	delete iArray;
	}

void CClassC::ExternalizeL(RWriteStream& aStream) const
	{
	aStream << iFixBuffer;

	TInt count;
	count = iArray->Count();
	aStream.WriteInt32L(count);
	for (TInt index = 0; index < count; index++)
		aStream.WriteInt32L((*iArray)[index]);
	}  
 
void CClassC::InternalizeL(RReadStream& aStream)
	{
	aStream >> iFixBuffer;

	TInt count;
	count  = aStream.ReadInt32L();
	
	for (TInt index = 0; index < count; index++)
		iArray->AppendL(aStream.ReadInt32L());
	}  
	 	

	 	



	
	
