
// IMCMMAIN.H
//
// Copyright (c) 1999 Symbian Ltd.  All rights reserved. 
//

#if !defined (__IMCMMAIN_H__)
#define __IMCMMAIN_H__

#if !defined (__E32STD_H__)
#include <e32std.h>
#endif

#if !defined (__BARSC_H__)
#include <barsc.h>		// RResourceFile
#endif



GLREF_C void OpenResourceFileL(RResourceFile& aFile, RFs& anFs);

GLDEF_C void CloseResourceFile( TAny* aResourceFile );


#endif