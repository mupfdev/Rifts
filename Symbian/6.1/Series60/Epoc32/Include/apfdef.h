// APFDEF.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __APFDEF_H__
#define __APFDEF_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

// generic file extensions etc.
_LIT(KAppFileExtension,".app");
_LIT(KAppInfoFileExtension,".aif");
_LIT(KIniFileExtension,".ini");
_LIT(KSystemControlFileExtension,".ctl");
_LIT(KApaCaptionFileSuffix,"_Caption");
_LIT(KAppResourceFileExtension,".rsc");

const TInt KApparcExtraLengthOfCaptionFileName=15;

//
// paths etc.
class Apfile
	{
public:
	IMPORT_C static TPtrC TempPath();
	};


#endif