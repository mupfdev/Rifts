// Basics.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.

//	Example demonstrates a simple use of the clipboard.
		
#include <baclipb.h>	

#include "CommonToResourceFilesEx.h"
#include "Basics.h"


////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// Do the example(s)

LOCAL_C void doExampleL()
    {
	doCopyL();
	doPasteL();
	}

////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


LOCAL_C void doCopyL()
	{
	_LIT(KSomeText,"Some text");
	_LIT(KContentOfTheCClassAObject,"Content of the CClassA object ...");

	// Construct an object of type CClassA
	CClassA*  item = new (ELeave) CClassA;
	CleanupStack::PushL(item);

	// Put some data into it
	item->iBuffer = KSomeText;
	item->iXA     = -1;
	item->iYA     = 2;

	// Show contents of the CClassA object
	doShow(KContentOfTheCClassAObject,item);

	// Construct the clipboard object and prepare the 
	// clipboard for writing
	CClipboard* cb = CClipboard::NewForWritingLC(fsSession);

	// Now put the object onto the clipboard and identify the data with
	// the uid KExampleClipUid. In a real app, this would typically be 
	// done in response to a request from the user interface to cut or copy.
	//
	// Note that the value of KExampleClipUid is arbitrary and is used
	// solely for the purpose oif demonstration
	RStoreWriteStream  stream;
	TStreamId stid = stream.CreateLC(cb->Store());
	stream << *item;
	stream.CommitL();
	(cb->StreamDictionary()).AssignL(KExampleClipUid,stid);
	CleanupStack::PopAndDestroy(); //the stream
	
	// commit the clipboard - this writes the stream dictionary to the
	// store as the root stream and commits all changes to the store 
	cb->CommitL();

	// Delete the clipboard object - this closes the clipboard file store
	// and delete the CClassA object
	CleanupStack::PopAndDestroy(2);
	}

////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

LOCAL_C void doPasteL()
	{
	_LIT(KNothingToPaste,"Nothing to paste");
	_LIT(KTheCClassAObjectAfterPastingIn,"The CClassA object after pasting in ...");

	CClipboard* cb = NULL;

	// Construct the clipboard object and prepare the 
	// clipboard for reading.
	TRAPD(ret,cb=CClipboard::NewForReadingL(fsSession));
	CleanupStack::PushL(cb);
    if (ret!=KErrNone)
		{
		doShow(KNothingToPaste,NULL);
		User::Leave(ret);
		}
		
	// Construct an object of type CClassA
	CClassA*  item = new (ELeave) CClassA;
	CleanupStack::PushL(item);

	// Check whether there is a CClassA object on the clipboard
	TStreamId stid = (cb->StreamDictionary()).At(KExampleClipUid);
	if (stid == KNullStreamId)
		{
		doShow(KNothingToPaste,NULL);
		User::Leave(0);
		}
	
	// Fetch the CClassA object from the clipboard
	RStoreReadStream stream;
	stream.OpenLC(cb->Store(),stid);
	stream >> *item;
	CleanupStack::PopAndDestroy();  // the stream
	
	// Show contents of the CClassA object as pasted in
	// from the  clipboard.
	doShow(KTheCClassAObjectAfterPastingIn,item);

	// delete:
	// 1. the CClassA object
	// 2. the clipboard object
	CleanupStack::PopAndDestroy(2);
	}

////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

LOCAL_C void doShow(const TDesC& aHeading,const CClassA* anItem)
	{
	_LIT(KNewline,"\n");
	_LIT(KFormatS,"\n%S");
	_LIT(KFormatD,"\n%d");
	_LIT(KFormatU,"\n%u");

	console->Printf(KNewline);
	console->Printf(aHeading);
	if (anItem)
		{
		console->Printf(KFormatS,&anItem->iBuffer);
		console->Printf(KFormatD,anItem->iXA);
		console->Printf(KFormatU,anItem->iYA);
		console->Printf(KNewline);
		}
	}

////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

CClassA::CClassA()
	{
	_LIT(KDefault,"DEFAULT");
	iBuffer = KDefault;
	}

void CClassA::ExternalizeL(RWriteStream& aStream) const
	{
	aStream << iBuffer;
	aStream.WriteInt32L(iXA);
	aStream.WriteUint32L(iYA);
	}  
 
void CClassA::InternalizeL(RReadStream& aStream)
	{
	aStream >> iBuffer;
  	iXA  = aStream.ReadInt32L();
	iYA  = aStream.ReadUint32L();
	}  
	
		

	
	 

