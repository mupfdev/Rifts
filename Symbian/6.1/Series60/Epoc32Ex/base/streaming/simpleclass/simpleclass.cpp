// SimpleClass.cpp
//
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.

// Example to demonstrate simple use of Streaming


#include "CommonStreamStore.h"
#include <s32file.h>

				// Constructs a TSimple object and 
				// externalizes it to a single stream.
LOCAL_C void doMakeAndExternalizeL(const TDesC& aName);

				// Internalizes a TSimple object from
				// the stream
LOCAL_C void doInternalizeL(const TDesC& aName);

				// Displays content of a TSimple object
class TSimple;
LOCAL_C void doShow(const TDesC& aHeading,const TSimple& theSimple);

				// enumeration used by the TSimple class
enum  TXxx {EX1,EX2,EX3};

				// definition of the TSimple class
class TSimple
	{
public :
	void ExternalizeL(RWriteStream& aStream) const;
	void InternalizeL(RReadStream& aStream);
public :
	TXxx     iTheEnum;
	TBuf<32> iBuffer;
	TInt     iIntValue;
	TUint    iUintValue;
	TReal    iRealValue;
	};


// The file name, extension and path for the file store
_LIT(KFullNameOfFileStore,"C:\\epoc32ex\\data\\SimpleClassToSimpleStream.dat");


//  Do the example
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
		
				// Construct an object of type TSimple and put some 
				// data into it
	_LIT(KTxtSomeText,"Some text");
	TSimple thesimple;
	thesimple.iTheEnum   = EX3;
	thesimple.iBuffer    = KTxtSomeText;
	thesimple.iIntValue  = -1;
	thesimple.iUintValue = 2; 
	thesimple.iRealValue = 3.4;

				// Show contents of the TSimple object
	_LIT(KTxtTSimpleContent,"TSimple content ...");
	doShow(KTxtTSimpleContent,thesimple);
					
				// Construct and create the output stream
				// object. 
				// The stream id (there is only one) will
				// be saved (later) in the store as the 
				// root stream id
	RStoreWriteStream outstream;
	TStreamId id = outstream.CreateLC(*store);
	
				// Stream out the TSimple object
	outstream  << thesimple; 

				// Commit changes to the stream
	outstream.CommitL();

				// Cleanup the stream object
	CleanupStack::PopAndDestroy();
				
				// Set the stream id as the root
	store->SetRootL(id);

				// Commit changes to the store
	store->CommitL();

				// destroy the store object (this also closes
				// the file containing the store) 
	CleanupStack::PopAndDestroy();
	}

LOCAL_C void doInternalizeL(const TDesC& aName)
	{
	TParse	filestorename;
	fsSession.Parse(aName,filestorename);
				// construct file store object - specifying the file
				// containing the store.
	CFileStore* store = CDirectFileStore::OpenLC(fsSession,filestorename.FullName(),EFileRead);
	
				// Construct and open the input stream object. We want 
				// to access the root stream from the store
				// in this example. 
	RStoreReadStream instream;
	instream.OpenLC(*store,store->Root());

				// Stream in the TSimple object
	TSimple thesimple;
	instream >> thesimple;

				// Cleanup the stream object
	CleanupStack::PopAndDestroy();

				// destroy the store object (this also closes the file
				// containing the store) 
	CleanupStack::PopAndDestroy();

				// Show contents of the TSimple object
	_LIT(KTxtRestoredTSimpleContent,"Restored TSimple content ...");
	doShow(KTxtRestoredTSimpleContent,thesimple);
	}
									
_LIT(KTxtNewLine,"\n");
_LIT(KFormatType1,"\n%d");
_LIT(KFormatType2,"\n%S");
_LIT(KFormatType3,"\n%u");
_LIT(KFormatType4,"\n%f");

LOCAL_C void doShow(const TDesC& aHeading,const TSimple& aSimple)
	{
	console->Printf(KTxtNewLine);
	console->Printf(aHeading);
	console->Printf(KFormatType1,aSimple.iTheEnum);
	console->Printf(KFormatType2,&aSimple.iBuffer);
	console->Printf(KFormatType1,aSimple.iIntValue);
	console->Printf(KFormatType3,aSimple.iUintValue);
	console->Printf(KFormatType4,aSimple.iRealValue);
	console->Printf(KTxtNewLine);
	}

//***************************************************************
//***************************************************************

// Explicit versions of the << and >> operators written to handle the
// enumerator type TXxx	

RWriteStream& operator<<(RWriteStream& aStream, const TXxx& anXxx)
	{
	aStream.WriteInt8L(anXxx);
	return aStream;
	}

RReadStream&  operator>>(RReadStream&  aStream, TXxx& anXxx)
	{
	anXxx = TXxx(aStream.ReadInt8L());
	return aStream;
	}

//***************************************************************
//***************************************************************

void TSimple::ExternalizeL(RWriteStream& aStream) const
	{
	aStream << iTheEnum;
	aStream << iBuffer;
	aStream.WriteInt32L(iIntValue);
	aStream.WriteUint32L(iUintValue);
	aStream.WriteReal64L(iRealValue);
	}  
 
void TSimple::InternalizeL(RReadStream& aStream)
	{
	aStream >> iTheEnum;
	aStream >> iBuffer;
  	iIntValue  = aStream.ReadInt32L();
	iUintValue = aStream.ReadUint32L();
	iRealValue = aStream.ReadReal64L();
	}  
	 	



	
	
