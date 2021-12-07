// HelloWorld_CExampleApplication.cpp
// ----------------------------------
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
//

////////////////////////////////////////////////////////////////////////
//
// Source file for the implementation of the 
// application class - CExampleApplication
//
////////////////////////////////////////////////////////////////////////

#include "HelloWorld.h"

const TUid KUidHelloWorld = { 0X10008ACE }; 

//             The function is called by the UI framework to ask for the
//             application's UID. The returned value is defined by the
//             constant KUidHelloWorlde and must match the second value
//             defined in the project definition file.
// 
TUid CExampleApplication::AppDllUid() const
	{
	return KUidHelloWorld;
	}

//             This function is called by the UI framework at
//             application start-up. It creates an instance of the
//             document class.
//
CApaDocument* CExampleApplication::CreateDocumentL()
	{
	return new (ELeave) CExampleDocument(*this);
	}