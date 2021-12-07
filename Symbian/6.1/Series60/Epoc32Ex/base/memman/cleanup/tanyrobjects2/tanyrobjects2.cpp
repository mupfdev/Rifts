// TAnyRObjects2.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.

// AIM: To provide examples for the documentation of exceptions & traps
// Situation3 - examples of cleanup-stack support for TAny* and RItems


#include "CommonFramework.h"

// Directory name and full path name
_LIT(KDirName,"C:\\epoc32ex\\data\\");
_LIT(KFileName,"C:\\epoc32ex\\data\\TAnyandRObjects2.dat");

// Test data (some ASCII characters) to be put into the file.
_LIT8(KTestData,"Test data for TAnyandRObjects2\n");

// #include specific files
#include <f32file.h>
#include "euhexdmp.h"


//////////////////////////////////////////////////////////////////////////////
//
// ----->  RFileWithCleanup(definition)
//
// Function Cleanup() and operator TCleanupItem() needed to provide 
// Cleanup Stack for RFile
//
//////////////////////////////////////////////////////////////////////////////
class RFileWithCleanup : public RFile
	{
private:
	static void Cleanup(TAny *aPtr);
public:
	operator TCleanupItem();
public:
	void OpenL(RFs &aFs,const TDesC &aName,TUint aMode);
	void OpenLC(RFs &aFs,const TDesC &aName,TUint aMode);
	};


//////////////////////////////////////////////////////////////////////////////
//
// ----->  RFileWithCleanup(implementation)
//
//////////////////////////////////////////////////////////////////////////////
void RFileWithCleanup::Cleanup(TAny *aPtr)
	{
	_LIT(KMsgDoingCleanup,"Doing cleanup of file.\n");
	console->Printf(KMsgDoingCleanup);						
	  // Invoke the Close member on the RItem at aPtr
	((RFileWithCleanup *)aPtr)->Close();
	}

RFileWithCleanup::operator TCleanupItem()
	{
	return TCleanupItem(Cleanup,this);
	}

void RFileWithCleanup::OpenL(RFs &aFs,const TDesC &aName,TUint aMode)
	{
	User::LeaveIfError(RFile::Open(aFs,aName,aMode));
	}

void RFileWithCleanup::OpenLC(RFs &aFs,const TDesC &aName,TUint aMode)
	{
	OpenL(aFs,aName,aMode);
	CleanupStack::PushL(*this);	// NB. 'this' would have been a TAny*
	}

LOCAL_C void createDataFileL()
	{
	  // utility function to create some data which we can later read
	RFs createFileSession;
	RFileWithCleanup createFile;

      // connect to filserver session		
	User::LeaveIfError(createFileSession.Connect());
	// make sure the main directory exists
	createFileSession.MkDirAll(KDirName);
	  // create euclnc2.bat and open for writing
	User::LeaveIfError(createFile.Replace(createFileSession,
		                                  KFileName,
					                      EFileWrite|EFileStreamText));

	  // write and commit text
	User::LeaveIfError(createFile.Write(KTestData));
	User::LeaveIfError(createFile.Flush());
	_LIT(KMsgDataWritten,"Data written to file\n");
	console->Printf(KMsgDataWritten);

	  // close file and session
	  // (NB. no LeaveIfError due to RFile.close and 
	  // RFs.close guaranteed to complete)
	createFile.Close();	                      // close file
	createFileSession.Close(); 	              // close file server session
	}

void useBufferL(TPtr8& bufferPtr)
	{
	printBuffer(0,bufferPtr);
	  // Remove following comment to force a leave
	  // while using the buffer
	//User::Leave(KErrGeneral);
	}


LOCAL_C void doExampleL()
    {
				// create the datafile for the example
	createDataFileL();
				// create a buffer 
	TText8* buffer=(TText8*) User::Alloc(100*sizeof(TText8));
				// push it to the cleanup stack: treated as TAny*
	CleanupStack::PushL(buffer);
				// create a pointer to the buffer
	TPtr8 bufferPtr(buffer,100);
				// the file session to be used
	RFs fsSession;
	_LIT(KMsgOpeningSession,"Opening session\n");
	console->Printf(KMsgOpeningSession);
				// open the file-server session
	User::LeaveIfError(fsSession.Connect());
				// the file instance myFile
	RFileWithCleanup myFile;
	_LIT(KMsgOpeningFile,"Opening file\n");
	console->Printf(KMsgOpeningFile);
			// open the file (and leave on cleanup stack)
	myFile.OpenLC(fsSession,KFileName,EFileStreamText|EFileRead);	
	
				// read stuff from the file to the buffer (may leave)
	_LIT(KMsgReadingFile,"Reading file into buffer.\n");
	console->Printf(KMsgReadingFile);
	User::LeaveIfError(myFile.Read(bufferPtr));
      // Remove following comment to force a leave
	  // while using the file
	//User::Leave(KErrGeneral);

				// destroy the file on the cleanup stack
	CleanupStack::PopAndDestroy();		

	fsSession.Close();

				// use the buffer
	useBufferL(bufferPtr);
				// destroy the buffer on the cleanup stack
	CleanupStack::PopAndDestroy();		
	}

