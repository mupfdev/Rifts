// CONVPLUG.H
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
//

#if !defined(__CONVPLUG_H__)
#define __CONVPLUG_H__

#if !defined(__E32STD_H__)
#include <E32STD.H>
#endif

#if !defined(__CHARCONV_H__)
#include <CHARCONV.H>
#endif

IMPORT_C const TDesC8& ReplacementForUnconvertibleUnicodeCharacters();
IMPORT_C TInt ConvertFromUnicode(CCnvCharacterSetConverter::TEndianness aDefaultEndiannessOfForeignCharacters, const TDesC8& aReplacementForUnconvertibleUnicodeCharacters, TDes8& aForeign, const TDesC16& aUnicode, CCnvCharacterSetConverter::TArrayOfAscendingIndices& aIndicesOfUnconvertibleCharacters);
IMPORT_C TInt ConvertToUnicode(CCnvCharacterSetConverter::TEndianness aDefaultEndiannessOfForeignCharacters, TDes16& aUnicode, const TDesC8& aForeign, TInt& aState, TInt& aNumberOfUnconvertibleCharacters, TInt& aIndexOfFirstByteOfFirstUnconvertibleCharacter);
IMPORT_C TBool IsInThisCharacterSetL(TBool& aSetToTrue, TInt& aConfidenceLevel, const TDesC8& aSample);
IMPORT_C void Reserved_2();
IMPORT_C void Reserved_3();
IMPORT_C void Reserved_4();
IMPORT_C void Reserved_5();
IMPORT_C void Reserved_6();
IMPORT_C void Reserved_7();
IMPORT_C void Reserved_8();

#endif

