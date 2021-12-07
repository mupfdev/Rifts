// Notify.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.

#include "Notify.h"

_LIT(KStarted,"Copy started\n");
_LIT(KComplete,"Copy complete\n");
_LIT(KProgress,"%d bytes copied\n");

// 
// TFileCopyProgressMonitor
// 

TFileCopyProgressMonitor::TFileCopyProgressMonitor(CFileMan& aFileMan)
:iFileMan(aFileMan)
	{	
	}

// Called when copy operation started
MFileManObserver::TControl TFileCopyProgressMonitor::NotifyFileManStarted()
	{
	console->Printf(KStarted);
	return EContinue;
	}

// Called when copy operation is in progress
MFileManObserver::TControl TFileCopyProgressMonitor::NotifyFileManOperation()
	{
	console->Printf(KProgress,iFileMan.BytesTransferredByCopyStep());
	return EContinue;
	}

// Called when copy operation is complete
MFileManObserver::TControl TFileCopyProgressMonitor::NotifyFileManEnded()
	{
	console->Printf(KComplete);
	return EContinue;
	}
	

//
// Do the example
//

LOCAL_C void doExampleL()
    {
	_LIT(KSourcePath,"c:\\dataFile");
	_LIT(KDestinationPath,"c:\\dataFileCopy");

	// Connect session
	RFs fsSession;
	User::LeaveIfError(fsSession.Connect()); 
	
	// Create file management object
	CFileMan* fileMan = CFileMan::NewL(fsSession);
	CleanupStack::PushL(fileMan); 

	// Create file management notification object and set to observe
	TFileCopyProgressMonitor fileCopyProgressMonitor(*fileMan);
	fileMan->SetObserver(&fileCopyProgressMonitor);
	
	// Do copy (here synchronously)
	fileMan->Copy(KSourcePath,KDestinationPath);
	
	// Clean up
	CleanupStack::PopAndDestroy(); 
	fsSession.Close(); // close file server session
	}

