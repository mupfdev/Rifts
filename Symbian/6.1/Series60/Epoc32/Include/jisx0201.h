// JISX0201.H
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
//

#if !defined(__JISX0201_H__)
#define __JISX0201_H__

#if !defined(__E32STD_H__)
#include <E32STD.H>
#endif

#if !defined(__CHARCONV_H__)
#include <CHARCONV.H>
#endif

class CnvJisX0201 // only to be used by CHARCONV plug-in DLLs
	{
public:
	IMPORT_C static const SCnvConversionData& ConversionData();
	};

class CnvJisRoman // only to be used by CHARCONV plug-in DLLs
	{
public:
	IMPORT_C static const SCnvConversionData& ConversionData();
	};

class CnvHalfWidthKatakana8 // only to be used by CHARCONV plug-in DLLs
	{
public:
	IMPORT_C static const SCnvConversionData& ConversionData();
	};

#endif

