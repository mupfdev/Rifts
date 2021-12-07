// Connecting.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.


// NB. THE FOLLOWING CODE CREATES A DIRECTORY CALLED F32TEST IN THE DEFAULT 
// DIRECTORY AND DELETES IT BEFORE EXITING.

#include <f32file.h>
#include "CommonFramework.h"
	
LOCAL_D RFs fsSession;

LOCAL_C void doExampleL()
    {
	// Define descriptor constants using the _LIT macro 
	_LIT(KMessage1,"Default path for fsSession is %S\n");
	_LIT(KMessage2,"Session path for fsSession is %S\n");
	_LIT(KMessage3,"\\f32test\\");
	_LIT(KMessage4,"\\f32test\\");
	_LIT(KMessage5,"Default path for fsSession is %S\n");
	_LIT(KMessage6,"Session path for fsSession is %S\n");
	_LIT(KMessage7,"Session path for fsSession2 is %S\n");
	_LIT(KMessage8,"\\f32test\\");

	// Print system default path, then print session path. 
	// Should be the same.

	// open file server session
	User::LeaveIfError(fsSession.Connect()); // connect session
	TFileName path;
	User::LeaveIfError(fsSession.DefaultPath(path));
	// write out system default path
	console->Printf(KMessage1,&path);
	User::LeaveIfError(fsSession.SessionPath(path));
	// write out session path. Should be the system default path
	console->Printf(KMessage2,&path);

	// Make a directory. 
	// Set system default path to directory. 
	// Print the system default path and session path again. 
	// System path should have changed, session path should be unchanged.
 
	TInt err=fsSession.MkDir(KMessage3);
	if (err!=KErrAlreadyExists)  // Don't leave if it already exists
		User::LeaveIfError(err);

	// Change system default path to newly created directory
	User::LeaveIfError(fsSession.SetDefaultPath(KMessage4));
	User::LeaveIfError(fsSession.DefaultPath(path));
	console->Printf(KMessage5,&path);
	User::LeaveIfError(fsSession.SessionPath(path));
	// Session path should be unchanged
	console->Printf(KMessage6,&path);

	// Make another connection to the file server and print 
	// its session path. It should have picked up the 
	// new system default path.
	
	RFs fsSession2;
	User::LeaveIfError(fsSession2.Connect());
	// New connection's session path should be new system default path
	User::LeaveIfError(fsSession2.SessionPath(path));
	console->Printf(KMessage7,&path);
	User::LeaveIfError(fsSession.RmDir(KMessage8));
	fsSession2.Close();
	fsSession.Close(); // close session with file server 
	}
