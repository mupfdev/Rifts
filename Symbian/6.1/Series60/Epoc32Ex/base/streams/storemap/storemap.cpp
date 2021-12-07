// StoreMap.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.


// Example to demonstrate the streaming of a compound object to
// multiple streams with deferred loading.
// Also illustrates the use of a store map (CStoreMap) 

#include "CommonStreamStore.h"
#include <s32file.h>

//
// Format types and the newline character
//

_LIT(KTxtNewLine,"\n");
_LIT(KFormatType1,"\n%d");
_LIT(KFormatType2,"\n%S");
_LIT(KFormatType3,"\n%u");
_LIT(KFormatType4,"\n%f");

				// Constructs a CCompound object and externalizes
				// it and its components to separate streams.
LOCAL_C void doMakeAndExternalizeL(const TDesC& aName);        

				// Demonstrates deferred loading of
				// component objects.
LOCAL_C void doDeferredLoadingL(const TDesC& aName); 

				// Shows the content of the compound object 
class CCompound;
LOCAL_C void doShowAll(const TDesC& aHeading,const CCompound& aCompound);

				// Shows the content of the CLassA component
				// of the compound object.
class CClassA;
LOCAL_C void doShowComponent(const TDesC& aHeading,const CClassA& aComponent);

				// Shows the content of the CLassB component
				// of the compound object.
class CClassB;	
LOCAL_C void doShowComponent(const TDesC& aHeading,const CClassB& aComponent);

				// Shows the content of the CLassB component
				// of the compound object.
class CClassC;
LOCAL_C void doShowComponent(const TDesC& aHeading,const CClassC& aComponent);

				// Defintion of classes used by the example
class CClassA
	{
public :
	void		ExternalizeL(RWriteStream& aStream) const;
	void		InternalizeL(RReadStream& aStream);
	TStreamId	StoreL(CStreamStore& aStore) const;
	void		RestoreL(CStreamStore& aStore, TStreamId anId);
public :
	TBuf<32>	iBufferA;
	TInt		iXA;
	TUint		iYA;
	};


class CClassB
	{
public :
	void		ExternalizeL(RWriteStream& aStream) const;
	void		InternalizeL(RReadStream& aStream);
	TStreamId	StoreL(CStreamStore& aStore) const;
	void		RestoreL(CStreamStore& aStore, TStreamId anId);
public :
	TBuf<32>	iBufferB;
	};


class CClassC
	{
public :
	void		ExternalizeL(RWriteStream& aStream) const;
	void		InternalizeL(RReadStream& aStream);
	TStreamId	StoreL(CStreamStore& aStore) const;
	void		RestoreL(CStreamStore& aStore, TStreamId anId);
public :
	TReal		iZC;
	};

	
class CCompound : public CBase
	{
public :
	static		CCompound* NewLC(CStreamStore& aStore);
	static		CCompound* NewLC(CStreamStore& aStore,TStreamId anId);
public :
	CCompound(CStreamStore& aStore);
	CCompound(CStreamStore& aStore,TStreamId anId);
	~CCompound();
	void		InternalizeL(RReadStream& aStream);
	void		ExternalizeL(RWriteStream& aStream) const;
	TStreamId	StoreL() const;
	void		RestoreL();
	void		StoreComponentsL(CStoreMap& aMap) const;
	void		DisplayAL(const TDesC& aCommentary);
private:
    void		ConstructL();
public :
	TSwizzle<CClassA> iA;
	TSwizzle<CClassB> iB;
	TSwizzle<CClassC> iC;
	CStreamStore&     iStore; // Store to/Restore from this store
	TStreamId         iId;    // Restore from/replace this stream
	};


// The file name, extension and path for the file store
_LIT(KFullNameOfFileStore,"C:\\epoc32ex\\data\\StoreMapUse.dat");

	// Do the example
LOCAL_C void doExampleL()
    {
				    // make sure directory exists
	fsSession.MkDirAll(KFullNameOfFileStore);
				// Construct a CCompound object and externalize
				// it and its components to separate streams.
	doMakeAndExternalizeL(KFullNameOfFileStore);
			
				// Demonstrate deferred loading of component objects
	doDeferredLoadingL(KFullNameOfFileStore);
	}

LOCAL_C void doMakeAndExternalizeL(const TDesC& aName)
	{
	TParse	filestorename;
	fsSession.Parse(aName,filestorename);
				// construct file store object - the file to contain the
				// the store replaces any existing file of the same name.
	CFileStore* store = CPermanentFileStore::ReplaceLC(fsSession,filestorename.FullName(),EFileWrite);

				// Must say what kind of file store
    store->SetTypeL(KPermanentFileStoreLayoutUid);

					// Construct an object of type CCompound ... 
	CCompound* thecompound = CCompound::NewLC(*store);

				// ... and put some data into it.
				// Note that "iA->" achieves the same
				// as "iA->AsPtr()->"
	_LIT(KTxtClassAText,"CClassA text");
	_LIT(KTxtClassBText,"CClassB text");
	thecompound->iA.AsPtr()->iBufferA = KTxtClassAText;
	thecompound->iA.AsPtr()->iXA	  = -1; 
	thecompound->iA->iYA	          = 2; // see note above
	thecompound->iB.AsPtr()->iBufferB = KTxtClassBText;
	thecompound->iC.AsPtr()->iZC	  = 3.456;

				// Show contents of the CCompound object (and its
				// components).
	_LIT(KTxtInitialContent,"... Initial content of CCompound");
	doShowAll(KTxtInitialContent,*thecompound);

				// stores all components as separate streams and
				// then streams the store map
	TStreamId id = thecompound->StoreL();

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

LOCAL_C void doDeferredLoadingL(const TDesC& aName)
	{
	TParse	filestorename;
	fsSession.Parse(aName,filestorename);
				// construct file store object - specifying the file
				// containing the store.
	CFileStore* store = CPermanentFileStore::OpenLC(fsSession,filestorename.FullName(),EFileRead);
	
				// Construct an object of type CCompound.
				// The loading of its components is deferred 
				// until needed.
	CCompound* thecompound = CCompound::NewLC(*store,store->Root());
	
				// Display component A.
				// The component is loaded in from the 
				// stream if not already loaded.
	_LIT(KTxtFirstDisplay," (first display)");
	thecompound->DisplayAL(KTxtFirstDisplay);

				// Re-Display component A
				// The component should now be in memory.
	_LIT(KTxtSecondDisplay," (second display)");
	thecompound->DisplayAL(KTxtSecondDisplay);

	console->Printf(KTxtNewLine);

				// Destroy:
				// 1. the CCompound object
				// 2. the store object (this also closes 
				//    the file containing the store)
				// Remove both from the cleanup stack
	CleanupStack::PopAndDestroy(2);
	}

_LIT(KTxtComponentA,"... Component A");
_LIT(KTxtComponentB,"... Component B");
_LIT(KTxtComponentC,"... Component C");
_LIT(KTxtPressKey,"\n (press any key to continue)");

LOCAL_C void doShowAll(const TDesC& aHeading,const CCompound& aCompound)
	{ 
	console->Printf(KTxtNewLine);
	console->Printf(aHeading);
	if (aCompound.iA.IsPtr())
		doShowComponent(KTxtComponentA,*aCompound.iA.AsPtr());
	if (aCompound.iB.IsPtr())
		doShowComponent(KTxtComponentB,*aCompound.iB.AsPtr());
	if (aCompound.iB.IsPtr())
		doShowComponent(KTxtComponentC,*aCompound.iC.AsPtr());
	console->Printf(KTxtPressKey);
	console->Getch();
	}

LOCAL_C void doShowComponent(const TDesC& aHeading,const CClassA& aComponent)
	{
	console->Printf(KTxtNewLine);
	console->Printf(aHeading);
	console->Printf(KFormatType2,&aComponent.iBufferA);
	console->Printf(KFormatType1,aComponent.iXA);
	console->Printf(KFormatType3,aComponent.iYA);
	}

LOCAL_C void doShowComponent(const TDesC& aHeading,const CClassB& aComponent)
	{
	console->Printf(KTxtNewLine);
	console->Printf(aHeading);
	console->Printf(KFormatType2,&aComponent.iBufferB);
	}

LOCAL_C void doShowComponent(const TDesC& aHeading,const CClassC& aComponent)
	{
	console->Printf(KTxtNewLine);
	console->Printf(aHeading);
	console->Printf(KFormatType4,aComponent.iZC);
	}

//***************************************************************
//***************************************************************
CCompound::CCompound(CStreamStore& aStore)
	: iStore(aStore)
	{}

CCompound::CCompound(CStreamStore& aStore,TStreamId anId)
	: iStore(aStore), iId(anId)
	{}


				// Construct a plain CCompound object and
				// place on the cleanup stack.
CCompound* CCompound::NewLC(CStreamStore& aStore)
	{
	CCompound* self=new (ELeave) CCompound(aStore);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}


				// Construct a CCompound object. The
				// components are restored when needed; however
				// the streamids of the component streams
				// ARE restored.
CCompound* CCompound::NewLC(CStreamStore& aStore,TStreamId anId)
	{
	CCompound* self=new (ELeave) CCompound(aStore,anId);
	CleanupStack::PushL(self);
 	self->RestoreL();
	return self;
	}

				// Complete the construction of the 
				// plain CCompound object. Makes implicit 
				// use of  TSwizzle operators.
void CCompound::ConstructL()
	{
	iA = new (ELeave) CClassA;
	iB = new (ELeave) CClassB;
	iC = new (ELeave) CClassC;
	}

				// The CCompound destructor. Destroy the swizzled
				// contained objects only if they are in memory
CCompound::~CCompound()
	{
	if (iA.IsPtr())
		delete iA.AsPtr();
	if (iB.IsPtr())
		delete iB.AsPtr();
	if (iC.IsPtr())
		delete iC.AsPtr();
	}

void CCompound::RestoreL()
	{
	RStoreReadStream stream;
	stream.OpenLC(iStore,iId);
	InternalizeL(stream);
	CleanupStack::PopAndDestroy();
	}
				
void CCompound::InternalizeL(RReadStream& aStream)
	{
	aStream >> iA;	
	aStream >> iB;
	aStream >> iC;
	}
				// Display the content of the "A" component
				// object. The component is fully restored 
				// from the appropriate stream, if it has not
				// already been restored. 
void CCompound::DisplayAL(const TDesC& aCommentary)
	{
	if (iA.IsId())
		{
		CClassA* ptrA = new (ELeave) CClassA;
		CleanupStack::PushL(ptrA);
		ptrA->RestoreL(iStore,iA.AsId());
		iA = ptrA;
	    CleanupStack::Pop(); 
		}
	_LIT(KTxtRestoredComponent,"... Displaying restored component A");
	TBuf<96> heading(KTxtRestoredComponent);
	heading.Append(aCommentary); 
	doShowComponent(heading,*iA.AsPtr());
	}


		
void CCompound::ExternalizeL(RWriteStream& aStream) const
	{
	aStream << iA; // these are swizzles
	aStream << iB;
	aStream << iC;
	}

TStreamId CCompound::StoreL() const
	{
	CStoreMap* map=CStoreMap::NewLC(iStore);
	StoreComponentsL(*map);
//
	RStoreWriteStream stream(*map);
	TStreamId id=stream.CreateLC(iStore);
	ExternalizeL(stream);
	stream.CommitL();
//
	map->Reset();
	CleanupStack::PopAndDestroy(2);
	return id;
	}

void CCompound::StoreComponentsL(CStoreMap& aMap) const
	{
	TStreamId id;
	
	if (iA)
		{
		id = iA->StoreL(iStore);
		aMap.BindL(iA,id);
		}

	if (iB)
		{
		id = iB->StoreL(iStore);
		aMap.BindL(iB,id);
		}

	if (iC)
		{
		id = iC->StoreL(iStore);
		aMap.BindL(iC,id);
		}
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
void CClassA::ExternalizeL(RWriteStream& aStream) const
	{
	aStream << iBufferA;
	aStream.WriteInt32L(iXA);
	aStream.WriteUint32L(iYA);
	}  

TStreamId CClassA::StoreL(CStreamStore& aStore) const
	{
	RStoreWriteStream stream;
	TStreamId id=stream.CreateLC(aStore);
	ExternalizeL(stream);
	stream.CommitL();
	CleanupStack::PopAndDestroy();
	return id;
	}

void CClassA::RestoreL(CStreamStore& aStore, TStreamId anId)
	{
	RStoreReadStream stream;
	stream.OpenLC(aStore,anId);
	InternalizeL(stream);
	CleanupStack::PopAndDestroy();
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

TStreamId CClassB::StoreL(CStreamStore& aStore) const
	{
	RStoreWriteStream stream;
	TStreamId id=stream.CreateLC(aStore);
	ExternalizeL(stream);
	stream.CommitL();
	CleanupStack::PopAndDestroy();
	return id;
	}

void CClassB::RestoreL(CStreamStore& aStore, TStreamId anId)
	{
	RStoreReadStream stream;
	stream.OpenLC(aStore,anId);
	InternalizeL(stream);
	CleanupStack::PopAndDestroy();
	}


//***************************************************************
//***************************************************************

				// Write the data member(s) of the CClassC 
				// ob ject to the stream.
void CClassC::ExternalizeL(RWriteStream& aStream) const
	{
	aStream.WriteReal64L(iZC);
	}  
				// Read the data member(s) of the CClassC 
				// object from the stream.
void CClassC::InternalizeL(RReadStream& aStream)
	{
	iZC = aStream.ReadReal64L();
	}  
	 	
TStreamId CClassC::StoreL(CStreamStore& aStore) const
	{
	RStoreWriteStream stream;
	TStreamId id=stream.CreateLC(aStore);
	ExternalizeL(stream);
	stream.CommitL();
	CleanupStack::PopAndDestroy();
	return id;
	}


void CClassC::RestoreL(CStreamStore& aStore, TStreamId anId)
	{
	RStoreReadStream stream;
	stream.OpenLC(aStore,anId);
	InternalizeL(stream);
	CleanupStack::PopAndDestroy();
	}



	
	
