// APADEF.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __APADEF_H__
#define __APADEF_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

// comand line tokens
const TUint KApaCommandLetterOpen='O';
const TUint KApaCommandLetterCreate='C';
const TUint KApaCommandLetterRun='R';
const TUint KApaCommandLetterBackground='B';
const TUint KApaCommandLetterViewActivate='V';
const TUint KApaCommandLetterRunWithoutViews='W';

enum TApaCommand
	{
	EApaCommandOpen,
	EApaCommandCreate,
	EApaCommandRun,
	EApaCommandBackground,
	EApaCommandViewActivate,
	EApaCommandRunWithoutViews
	};

//
const TInt KApaMaxAppCaption=0x100;	// Default name is a file name, so the same limit is used
typedef TBuf<KApaMaxAppCaption> TApaAppCaption; // current language name of the app (for task lists, dialogs etc)
//
const TInt KApaMaxCommandLine=0x100;	
typedef TBuf<KApaMaxCommandLine> TApaCommandLine;
//
const TInt KApaMaxAppFileName=0x10;	// Length of App's filename without path or extension (not it's caption)
typedef TBuf<KApaMaxAppFileName> TApaAppFileName;

const TInt KApaMaxAppGroupName=0x10; // Length of App's logical groupname
typedef TBuf<KApaMaxAppGroupName> TApaAppGroupName;

//
// 2nd Uid's for app dll's
const TInt KAppUidValue8 = 0x1000006c;
const TUid KUidApp8={KAppUidValue8};
const TInt KAppUidValue16 = 0x100039CE;
const TUid KUidApp16={KAppUidValue16};
//
// 2nd Uid for app doc files
const TUid KUidAppDllDoc8={268435565}; 
const TUid KUidAppDllDoc16={0x10003A12};
//
// Uid in picture headers that identifies the contained picture as a door
const TUid KUidPictureTypeDoor8={268435537};
const TUid KUidPictureTypeDoor16={0x10003A33};
//
// Uid's for streams in stream dictionaries
const TUid KUidSecurityStream8={268435661};
const TUid KUidSecurityStream16={0x10003A40};
const TUid KUidAppIdentifierStream8={268435593}; // stream containing a TApaAppIdentifier
const TUid KUidAppIdentifierStream16={0x10003A34};

#ifdef _UNICODE
#define KUidApp KUidApp16
#define KAppUidValue KAppUidValue16
#define KUidAppDllDoc KUidAppDllDoc16
#define KUidPictureTypeDoor KUidPictureTypeDoor16
#define KUidAppIdentifierStream KUidAppIdentifierStream16
#define KUidSecurityStream KUidSecurityStream16
#else
#define KUidApp KUidApp8
#define KAppUidValue KAppUidValue8
#define KUidAppDllDoc KUidAppDllDoc8
#define KUidPictureTypeDoor KUidPictureTypeDoor8
#define KUidAppIdentifierStream KUidAppIdentifierStream8
#define KUidSecurityStream KUidSecurityStream8
#endif

#endif
