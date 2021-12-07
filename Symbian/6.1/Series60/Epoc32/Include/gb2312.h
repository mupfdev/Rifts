// GB2312.H
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
//

#if !defined(__GB2312_H__)
#define __GB2312_H__

#if !defined(__E32STD_H__)
#include <E32STD.H>
#endif

#if !defined(__CHARCONV_H__)
#include <CHARCONV.H>
#endif

class CnvGb2312 // only to be used by CHARCONV plug-in DLLs and by locale-DLLs (Locl::FatUtilityFunctions)
	{
public:
	IMPORT_C static const TDesC8& ReplacementForUnconvertibleUnicodeCharacters();
	IMPORT_C static const SCnvConversionData& ConversionData();
	IMPORT_C static TBool IsCharGBBased(TInt& aConfidenceLevel, const TDesC8& aSample);
	};

#endif

