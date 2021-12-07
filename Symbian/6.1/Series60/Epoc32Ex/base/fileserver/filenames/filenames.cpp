// Filenames.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.


#include <f32file.h>
#include "CommonFramework.h"
	
LOCAL_D RFs fsSession;

// example functions
void CreatePaths(); // sets up the paths to parse
void ParseNames(const TDesC& aFullName); // does the parsing

void WaitForKey()
	{
	_LIT(KMessage,"Press any key to continue\n\n");
	console->Printf(KMessage);
	console->Getch();
	}

LOCAL_C void doExampleL()
    {
	// Connect to file server
	User::LeaveIfError(fsSession.Connect()); // Start session
	CreatePaths();
	fsSession.Close(); // close session
	}

void CreatePaths()
	{
	// Define descriptor constants using the _LIT macro 
	_LIT(KFuncName,"\nDoParsing()\n");
	_LIT(KParse1,"d:\\path\\fn.ext");
	_LIT(KParse2,"autoexec.bat");
	_LIT(KParse3,"c:readme");
	_LIT(KParse4,"c:\\include\\stdio.h");
	_LIT(KParse5,".profile");
	_LIT(KParse6,"autoexec.*");
	console->Printf(KFuncName);
	// Parse a full path, then paths with various components missing 
	// to show the results of using a default path and related path
	// to fill in missing path components.
	ParseNames(KParse1);
	WaitForKey();
	ParseNames(KParse2);
	WaitForKey();
	ParseNames(KParse3);
	WaitForKey();
	ParseNames(KParse4);
	WaitForKey();
	ParseNames(KParse5);
	WaitForKey();
	ParseNames(KParse6);
	WaitForKey();
	}

void ParseNames(const TDesC& aFullName)
	{
	_LIT(KFullName,"Full name=%S\n");
	_LIT(KPathComponents,"Drive=%S  path=%S  name=%S  ext=%S\n");
	_LIT(KFullNameText,"Full name against session path=%S\n");
	_LIT(KExtension,".txt");
	_LIT(KParsedPath,"Full name against session path and default extension .txt=%S\n");

	// Set up parse using TParse::Set(). Print whole path, then each path
	// component in turn.
	// Parse path using the default session path, using RFs::Parse 
	// then additionally with a related path.
	TParse p;
	// do isolated parse
	User::LeaveIfError(p.Set(aFullName,NULL,NULL));
	console->Printf(KFullName, &p.FullName());
	TFileName drivename(p.Drive());
	TFileName pathname(p.Path());
	TFileName filename(p.Name());
	TFileName extension(p.Ext());
	console->Printf(KPathComponents,&drivename,&pathname,&filename,&extension);
	// do parse including session path
	User::LeaveIfError(fsSession.Parse(aFullName,p));
	console->Printf(KFullNameText,&(p.FullName()));
	// add default extension
	User::LeaveIfError(fsSession.Parse(aFullName,KExtension,p));
	console->Printf(KParsedPath,&(p.FullName()));
	}




