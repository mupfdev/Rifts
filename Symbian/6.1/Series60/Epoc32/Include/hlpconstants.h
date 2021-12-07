// HLPCONSTANTS.H
//
// Copyright (c) 1999 Symbian Ltd.  All rights reserved.
//
#ifndef __HLPCONSTANTS_H__
#define __HLPCONSTANTS_H__

// System includes
#include <e32std.h>

// Constants
const TUid KUidHlpApp		=	{ 0x0100052b3 };	// UID 3
const TUid KUidHlpFile		=	{ 0x0100052b4 };	// UID 2
const TUid KUidHlpDbStream	=	{ 0x0100052b5 };	// Database stream in the help file
const TUid KUidHlpUidStream	=	{ 0x0100052b6 };	// UID stream in the help file
//
const TInt KTitleColumn	= 1;
const TInt KIdColumn = 2;
const TInt KMaxTitleColumn = 120;
const TInt KHlpSQLMaxLength = 512;
const TInt KHlpMaxTextColLength = 200;
const TInt KHlpMaxContextColLength = 32;




#endif