// WriteToFile.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.

// This example writes the text "hello world!" to a file
// Use it as the basis of all examples which depend on just E32 and F32

#include "CommonFramework.h"
#include <f32file.h>

_LIT(KDirName,"C:\\epoc32ex\\data\\");
_LIT(KFileName,"C:\\epoc32ex\\data\\WriteToFile.dat");
_LIT(KGreetingText,"Hello World!\n");

// Do the example
LOCAL_C void doExampleL()
    {
		// open file server session
	RFs fsSession; // session to write to
	User::LeaveIfError(fsSession.Connect()); // connect session
	fsSession.MkDirAll(KDirName);
		// open file
	RFile file; // file to write to
	User::LeaveIfError(file.Replace(fsSession,KFileName,EFileWrite|EFileStreamText));
		// write and commit text
		//
		// For UNICODE build we choose to write out double byte characters.
		// Note that Write() requires a TDesC8 type so we need to construct an explicit
		// TDesC8 type to represent the data contained in the 16 bit descriptor.
		// The length of this TDesC8 is twice the length of the TDesC16 because 
		// we are treating double byte data as a sequence of single bytes.	
	TPtrC8 representation((TUint8*)(&KGreetingText)->Ptr(), (&KGreetingText)->Size());
	User::LeaveIfError(file.Write(representation)); // write text
	// Commit the data
	User::LeaveIfError(file.Flush());
	
	_LIT(KTxt1,"Data written to file\n");
	console->Printf(KTxt1);
		// close file
	file.Close(); 
		// delete file
	User::LeaveIfError(fsSession.Delete(KFileName));
		// close file server session
	fsSession.Close(); 
	}
