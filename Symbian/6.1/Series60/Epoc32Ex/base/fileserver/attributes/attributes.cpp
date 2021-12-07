// Attributes.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.

// This code creates several files and directories inside
// \f32examp\ on the default drive. Before the program terminates,
// all files and directories created will be deleted.

#include <f32file.h>
#include "CommonFramework.h"		

LOCAL_D RFs fsSession;

// example functions
void DoDirectoryAttribsL();
void PrintDirectoryLists();	
void DeleteAll();

// utility functions
void FormatEntry(TDes& aBuffer, const TEntry& aEntry);
void FormatAtt(TDes& aBuffer, const TUint aValue);
void MakeSmallFile(const TDesC& aFileName);

void WaitForKey()
	{
	_LIT(KMessage,"Press any key to continue\n");
	console->Printf(KMessage);
	console->Getch();
	}

LOCAL_C void doExampleL()
    {
	// connect to file server
	User::LeaveIfError(fsSession.Connect());
	DoDirectoryAttribsL();
	WaitForKey();
	PrintDirectoryLists();
	WaitForKey();
	DeleteAll();
	fsSession.Close(); // close session with file server
	}

void DoDirectoryAttribsL()
	{
	// Define descriptor constants using the _LIT macro 
	_LIT(KAttsMsg,"\nAttributes and entry details\n");
	_LIT(KDirName,"\\f32examp\\");
	_LIT(KPathName,"\\f32examp\\tmpfile.txt");
	_LIT(KDateString,"%D%M%Y%/0%1%/1%2%/2%3%/3 %-B%:0%J%:1%T%:2%S%:3%+B");
	_LIT(KDateMsg,"Using Entry():\nModification time of %S is %S\n");
	_LIT(KSizeMsg,"Size = %d bytes\n");
	_LIT(KBuffer,"%S");
	_LIT(KEntryMsg,"Using Modified():\nModification time of %S is %S\n");
	_LIT(KAttMsg,"Using Att():\n%S");

	// Create a file. 
	// Display its entry details, its modification time 
	// and its attributes.
	// Then change some attributes and print them again.
	console->Printf(KAttsMsg);
	// When referring to a directory rather than a file, 
	// a backslash must be appended to the path.
	TInt err=fsSession.MkDir(KDirName);
	if (err!=KErrAlreadyExists)  // Don't leave if it already exists
		User::LeaveIfError(err);
	TFileName path(KPathName);
	// Create a file in \f32examp\ 
	MakeSmallFile(path);
	// Get entry details for file and print them	
	TEntry entry;	
	User::LeaveIfError(fsSession.Entry(path,entry)); 
	TBuf<30> dateString;
	entry.iModified.FormatL(dateString,KDateString);
 	// Modification date and time = time of file's creation
    console->Printf(KDateMsg,&entry.iName,&dateString);
	// Print size of file 
	console->Printf(KSizeMsg,entry.iSize);
	TBuf<80> buffer;
	FormatEntry(buffer,entry); // Archive attribute should be set
	console->Printf(KBuffer,&buffer);
	buffer.Zero();

	// get the entry details using Att() and Modified()
	TTime time;
	User::LeaveIfError(fsSession.Modified(path,time));
	time.FormatL(dateString,KDateString);
 	// Modification date and time = time of file's creation
    console->Printf(KEntryMsg,
                &entry.iName,&dateString);
	TUint value;
	User::LeaveIfError(fsSession.Att(path,value));
	FormatAtt(buffer,value); // get and print file attributes
	console->Printf(KAttMsg,&buffer);
	buffer.Zero();

	// Change entry details using SetEntry() to clear archive
	User::LeaveIfError(fsSession.SetEntry(path,time,
			NULL,KEntryAttArchive));
	}

void PrintDirectoryLists()
	{
	// Define descriptor constants using the _LIT macro 
	_LIT(KListMsg,"\nDirectory listings\n");
	_LIT(KDir1,"\\f32examp\\tmpdir1\\");
	_LIT(KDir2,"\\f32examp\\tmpdir2\\");
	_LIT(KFile2,"\\f32examp\\tmpfile2.txt");
	_LIT(KDirName,"\\f32examp\\*");
	_LIT(KListMsg2,"Directories and files:\n");
	_LIT(KDirList,"%S\n");
	_LIT(KDirs,"Directories:\n");
	_LIT(KFilesSizes,"Files and sizes:\n");
	_LIT(KBytes," %d bytes\n");
	_LIT(KNewLine,"\n");

	// Create some directories and files in \f32examp\. 
	// List them using GetDir(), then list files and 
	// directories in separate lists. 

	console->Printf(KListMsg);

	// When referring to a directory rather than a file, 
	// append backslash to path
	TInt err=fsSession.MkDir(KDir1);
	if (err!=KErrAlreadyExists)
		User::LeaveIfError(err); // Don't leave if it already exists 
	err=fsSession.MkDir(KDir2);
	if (err!=KErrAlreadyExists)
		User::LeaveIfError(err);
	TFileName path(KFile2);
	MakeSmallFile(path);
	// List all files and directories in \f32examp\ 
	// in alphabetical order.
	CDir* dirList;
	User::LeaveIfError(fsSession.GetDir(KDirName,
		KEntryAttMaskSupported,ESortByName,dirList));
	console->Printf(KListMsg2);
	TInt i;
	for (i=0;i<dirList->Count();i++)
		console->Printf(KDirList,&(*dirList)[i].iName);
	delete dirList;
	// List files and directories in \f32examp\ separately
	CDir* fileList;
	User::LeaveIfError(fsSession.GetDir(KDirName,KEntryAttNormal,
		ESortByName,fileList,dirList));
	console->Printf(KDirs);
	for (i=0;i<dirList->Count();i++)
		console->Printf(KDirList,&(*dirList)[i].iName);
	console->Printf(KFilesSizes);
	for (i=0;i<fileList->Count();i++)
		{
		console->Printf(KDirList,&(*fileList)[i].iName);
		console->Printf(KBytes,(*fileList)[i].iSize);
		}
	console->Printf(KNewLine);
	delete dirList;
	delete fileList;
	}

void DeleteAll()
// Delete all the files and directories which have been created
	{
	// Define descriptor constants using the _LIT macro 
	_LIT(KDeleteMsg,"\nDeleteAll()\n");
	_LIT(KFile2,"\\f32examp\\tmpfile2.txt");
	_LIT(KDir1,"\\f32examp\\tmpdir1\\");
	_LIT(KDir2,"\\f32examp\\tmpdir2\\");
	_LIT(KFile1,"\\f32examp\\tmpfile.txt");
	_LIT(KTopDir,"\\f32examp\\");
	console->Printf(KDeleteMsg);
	User::LeaveIfError(fsSession.Delete(KFile2));
	User::LeaveIfError(fsSession.RmDir(KDir1));
	User::LeaveIfError(fsSession.RmDir(KDir2));
	User::LeaveIfError(fsSession.Delete(KFile1));
	User::LeaveIfError(fsSession.RmDir(KTopDir));
	}

void MakeSmallFile(const TDesC& aFileName)
	{
	_LIT8(KFileData,"Some data");
	//TBuf8<10> From16To8Data;//
	//From16To8Data.Copy(KFileData());//
 	RFile file;
 	User::LeaveIfError(file.Replace(fsSession,aFileName,EFileWrite));
	User::LeaveIfError(file.Write(KFileData));
	User::LeaveIfError(file.Flush()); // Commit data
	file.Close(); // close file having finished with it
	}
	 	 
void FormatEntry(TDes& aBuffer, const TEntry& aEntry)
	{
	_LIT(KEntryDetails,"Entry details: ");
	_LIT(KReadOnly," Read-only");
	_LIT(KHidden," Hidden");
	_LIT(KSystem," System");
	_LIT(KDirectory," Directory");
	_LIT(KArchive," Archive");
	_LIT(KNewLIne,"\n");
	aBuffer.Append(KEntryDetails);
	if(aEntry.IsReadOnly())
		aBuffer.Append(KReadOnly);
	if(aEntry.IsHidden())
		aBuffer.Append(KHidden);
	if(aEntry.IsSystem())
		aBuffer.Append(KSystem);
	if(aEntry.IsDir())
		aBuffer.Append(KDirectory);
	if(aEntry.IsArchive())
		aBuffer.Append(KArchive);		
	aBuffer.Append(KNewLIne);
	}

void FormatAtt(TDes& aBuffer, const TUint aValue)
	{
	_LIT(KAttsMsg,"Attributes set are:");
	_LIT(KNormal," Normal");
	_LIT(KReadOnly," Read-only");
	_LIT(KHidden," Hidden");
	_LIT(KSystem," System");
	_LIT(KVolume," Volume");
	_LIT(KDir," Directory");
	_LIT(KArchive," Archive");
	_LIT(KNewLine,"\n");
	aBuffer.Append(KAttsMsg);
	if (aValue & KEntryAttNormal)
		{
	 	aBuffer.Append(KNormal);
	 	return;
	 	}
	if (aValue & KEntryAttReadOnly)
	 	aBuffer.Append(KReadOnly);
	if (aValue & KEntryAttHidden)
		aBuffer.Append(KHidden);
	if (aValue & KEntryAttSystem)
		aBuffer.Append(KSystem);
	if (aValue & KEntryAttVolume)
		aBuffer.Append(KVolume);
	if (aValue & KEntryAttDir)
		aBuffer.Append(KDir);
	if (aValue & KEntryAttArchive)
		aBuffer.Append(KArchive);
	aBuffer.Append(KNewLine);
	}

