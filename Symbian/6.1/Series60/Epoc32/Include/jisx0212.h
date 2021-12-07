// JISX0212.H
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
//

#if !defined(__JISX0212_H__)
#define __JISX0212_H__

#if !defined(__E32STD_H__)
#include <E32STD.H>
#endif

#if !defined(__CHARCONV_H__)
#include <CHARCONV.H>
#endif

class CnvJisX0212 // only to be used by CHARCONV plug-in DLLs
	{
public:
	IMPORT_C static const SCnvConversionData& ConversionData();
	};

#endif

