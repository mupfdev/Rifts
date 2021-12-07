/* Copyright (c) 2002, Nokia. All rights reserved */

#include <eikappui.h>
#include <eikenv.h>
#include <eikapp.h>
#include <s32file.h>
#include <aknnotewrappers.h>

#include "EikonEnvironment.h"


TFileName NEikonEnvironment::AppFullName()
	{
	return EikAppUi().Application()->AppFullName();
	}


TFileName NEikonEnvironment::ApplicationDriveAndPath()
	{
	TParse parse;
//On WINS the application is on the z drive
#ifdef __WINS__
	TFileName appfullname = AppFullName(); 
	parse.Set(_L("c:"), &appfullname, NULL);
#else
	parse.Set(AppFullName(), NULL, NULL);
#endif
	return parse.DriveAndPath();
	}


TFileName NEikonEnvironment::AddPath(const TDesC& aFileName)
	{
#ifdef _DEBUG //check that we have not been sent a file name with the drive included
	TParse theFile;
	theFile.Set(aFileName, NULL, NULL);
	ASSERT(theFile.Drive().Length() == 0);
#endif

	TParse thePath;
	thePath.Set(ApplicationDriveAndPath(),  &aFileName,  NULL);
	return thePath.FullName();

	}


CEikonEnv& NEikonEnvironment::EikEnv()
	{
	return *CEikonEnv::Static();
	}


CEikAppUi& NEikonEnvironment::EikAppUi()
	{
	return *(EikEnv().EikAppUi());
	}


CEikDocument& NEikonEnvironment::EikDocument()
	{
	return *(EikAppUi().Document());
	}


void NEikonEnvironment::AddToStackL(CCoeControl& aControl, TInt aPriority, TInt aStackingFlags)
	{
	RemoveFromStack(aControl);
	EikAppUi().AddToStackL(&aControl, aPriority, aStackingFlags);
	}


void NEikonEnvironment::AddToStackL(CCoeControl& aControl)
	{
	RemoveFromStack(aControl);
	EikAppUi().AddToStackL(&aControl);
	}


void NEikonEnvironment::RemoveFromStack(CCoeControl& aControl)
	{
	EikAppUi().RemoveFromStack(&aControl);
	}


void NEikonEnvironment::MessageBox(const TDesC&  aMessage)
	{
	TRAPD(err, 
		  CAknInformationNote* informationNote = new (ELeave) CAknInformationNote;
          informationNote->ExecuteLD(aMessage); );
	if (err != KErrNone)
		{
		User::Panic (_L("Helper"), 1);
		}
	}


void NEikonEnvironment::FlushWindowServer()
	{
	CCoeEnv::Static()->WsSession().Flush();
	}


RFs& NEikonEnvironment::TheRFs()
	{
	return CCoeEnv::Static()->FsSession();
	}

