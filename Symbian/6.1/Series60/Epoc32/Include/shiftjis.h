// SHIFTJIS.H
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
//

#if !defined(__SHIFTJIS_H__)
#define __SHIFTJIS_H__

#if !defined(__E32STD_H__)
#include <E32STD.H>
#endif

#if !defined(__CHARCONV_H__)
#include <CHARCONV.H>
#endif

class CnvShiftJis // only to be used by CHARCONV plug-in DLLs and by locale-DLLs (Locl::FatUtilityFunctions)
	{
public:
	IMPORT_C static const TDesC8& ReplacementForUnconvertibleUnicodeCharacters();
	IMPORT_C static TInt ConvertFromUnicode(CCnvCharacterSetConverter::TEndianness aDefaultEndiannessOfForeignCharacters, const TDesC8& aReplacementForUnconvertibleUnicodeCharacters, TDes8& aForeign, const TDesC16& aUnicode, CCnvCharacterSetConverter::TArrayOfAscendingIndices& aIndicesOfUnconvertibleCharacters);
	IMPORT_C static TInt ConvertToUnicode(CCnvCharacterSetConverter::TEndianness aDefaultEndiannessOfForeignCharacters, TDes16& aUnicode, const TDesC8& aForeign, TInt& aNumberOfUnconvertibleCharacters, TInt& aIndexOfFirstByteOfFirstUnconvertibleCharacter);
private:
	static void DummyConvertFromIntermediateBufferInPlace(TInt aStartPositionInDescriptor, TDes8& aDescriptor, TInt& aNumberOfCharactersThatDroppedOut);
	static void ConvertFromJisX0208ToShiftJisInPlace(TInt aStartPositionInDescriptor, TDes8& aDescriptor, TInt& aNumberOfCharactersThatDroppedOut);
	static TInt NumberOfBytesAbleToConvertToJisX0201(const TDesC8& aDescriptor);
	static TInt NumberOfBytesAbleToConvertToJisX0208(const TDesC8& aDescriptor);
	static void DummyConvertToIntermediateBufferInPlace(TDes8& aDescriptor);
	static void ConvertToJisX0208FromShiftJisInPlace(TDes8& aDescriptor);
	};

#endif

