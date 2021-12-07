// CHARCONV.H
//
// Copyright (c) 1997-2000 Symbian Ltd.  All rights reserved.
//

#if !defined(__CHARCONV_H__)
#define __CHARCONV_H__

#if !defined(__E32STD_H__)
#include <E32STD.H>
#endif

#if !defined(__E32BASE_H__)
#include <E32BASE.H>
#endif

const TInt KMaximumLengthOfReplacementForUnconvertibleUnicodeCharacters=50;

const TUint KCharacterSetIdentifierUtf7=0x1000582c;
const TUint KCharacterSetIdentifierUtf8=0x1000582d;
const TUint KCharacterSetIdentifierImapUtf7=0x1000582e;
const TUint KCharacterSetIdentifierJavaConformantUtf8=0x1000582f;
const TUint KCharacterSetIdentifierCodePage1252=0x100012b6;
const TUint KCharacterSetIdentifierIso88591=0x10003b10;
const TUint KCharacterSetIdentifierIso88592=0x1000507e;
const TUint KCharacterSetIdentifierIso88593=0x10008a28;
const TUint KCharacterSetIdentifierIso88594=0x1000507f;
const TUint KCharacterSetIdentifierIso88595=0x10005080;
const TUint KCharacterSetIdentifierIso88596=0x10008a29;
const TUint KCharacterSetIdentifierIso88597=0x10005081;
const TUint KCharacterSetIdentifierIso88598=0x10008a2a;
const TUint KCharacterSetIdentifierIso88599=0x10005082;
const TUint KCharacterSetIdentifierIso885910=0x10008a2b;
const TUint KCharacterSetIdentifierIso885913=0x10008a2c;
const TUint KCharacterSetIdentifierIso885914=0x10008a2d;
const TUint KCharacterSetIdentifierIso885915=0x10008a2e;
const TUint KCharacterSetIdentifierAscii=0x10004cc6;
const TUint KCharacterSetIdentifierSms7Bit=0x100053ab;
const TUint KCharacterSetIdentifierGb2312=0x10000fbe;
const TUint KCharacterSetIdentifierHz=0x10006065;
const TUint KCharacterSetIdentifierGb12345=0x1000401a;
const TUint KCharacterSetIdentifierGbk=0x10003ecb;
const TUint KCharacterSetIdentifierBig5=0x10000fbf;
const TUint KCharacterSetIdentifierShiftJis=0x10000fbd;
const TUint KCharacterSetIdentifierIso2022Jp=0x100066a0;
const TUint KCharacterSetIdentifierIso2022Jp1=0x100066a3;
const TUint KCharacterSetIdentifierJis=0x10006066;
const TUint KCharacterSetIdentifierEucJpPacked=0x10006067;
// note that other character sets than those listed above may be available at run-time, and also that none of the above are necessarily available at run-time

struct SCnvConversionData;
class CDeepDestructingArrayOfCharactersSets;
class CFileReader;
class CStandardNamesAndMibEnums;
class RFs;

class CCnvCharacterSetConverter : public CBase
	{
public:
	enum TAvailability
		{
		EAvailable,
		ENotAvailable
		};
	enum TError
		{
		EErrorIllFormedInput=KErrCorrupt
		};
	enum TEndianness
		{
		ELittleEndian,
		EBigEndian
		};
	enum TDowngradeForExoticLineTerminatingCharacters
		{
		EDowngradeExoticLineTerminatingCharactersToCarriageReturnLineFeed,
		EDowngradeExoticLineTerminatingCharactersToJustLineFeed
		};
	enum
		{
		EInputConversionFlagAppend										=0x00010000,
		EInputConversionFlagAllowTruncatedInputNotEvenPartlyConsumable	=0x00020000,
		EInputConversionFlagStopAtFirstUnconvertibleCharacter			=0x00040000
		};
	enum
		{
		EOutputConversionFlagInputIsTruncated							=0x01000000
		};
	enum {KStateDefault=0};
	enum 
		{
		ELowestThreshold = 25
		};
	struct SCharacterSet
		{
		inline TUint Identifier() const {return iIdentifier;}
		inline TBool NameIsFileName() const {return iFlags&EFlagNameIsFileName;}
		inline TPtrC Name() const {return *iName;}
	private:
		enum
			{
			EFlagNameIsFileName					=0x00000001,
			EFlagFileIsConversionPlugInLibrary	=0x00000002
			};
	private:
		inline TBool FileIsConversionPlugInLibrary() const {return iFlags&EFlagFileIsConversionPlugInLibrary;}
	private:
		TUint iIdentifier;
		TUint iFlags;
		HBufC* iName;
	private:
		friend class CCnvCharacterSetConverter;
		friend class CDeepDestructingArrayOfCharactersSets;
		};
	class TArrayOfAscendingIndices
		{
	public:
		enum TAppendResult
			{
			EAppendFailed,
			EAppendSuccessful
			};
	public:
		inline TArrayOfAscendingIndices() :iArrayOfIndices(0) {}
		IMPORT_C TAppendResult AppendIndex(TInt aIndex);
		inline void Remove(TInt aIndexOfIndex) {iArrayOfIndices.Delete(aIndexOfIndex, 1);}
		inline void RemoveAll() {iArrayOfIndices.SetLength(0);}
		inline TInt NumberOfIndices() const {return iArrayOfIndices.Length();}
		inline TInt operator[](TInt aIndexOfIndex) const {return iArrayOfIndices[aIndexOfIndex];}
	private:
		enum {KMaximumNumberOfIndices=25};
	private:
		TBuf16<KMaximumNumberOfIndices> iArrayOfIndices;
		};
public:
	IMPORT_C static CCnvCharacterSetConverter* NewL();
	IMPORT_C static CCnvCharacterSetConverter* NewLC();
	IMPORT_C virtual ~CCnvCharacterSetConverter();
	IMPORT_C static CArrayFix<SCharacterSet>* CreateArrayOfCharacterSetsAvailableL(RFs& aFileServerSession);
	IMPORT_C static CArrayFix<SCharacterSet>* CreateArrayOfCharacterSetsAvailableLC(RFs& aFileServerSession);
	IMPORT_C TUint ConvertStandardNameOfCharacterSetToIdentifierL(const TDesC8& aStandardNameOfCharacterSet, RFs& aFileServerSession);
	IMPORT_C HBufC8* ConvertCharacterSetIdentifierToStandardNameL(TUint aCharacterSetIdentifier, RFs& aFileServerSession);
	IMPORT_C TUint ConvertMibEnumOfCharacterSetToIdentifierL(TInt aMibEnumOfCharacterSet, RFs& aFileServerSession);
	IMPORT_C TInt ConvertCharacterSetIdentifierToMibEnumL(TUint aCharacterSetIdentifier, RFs& aFileServerSession);
	IMPORT_C void PrepareToConvertToOrFromL(TUint aCharacterSetIdentifier, const CArrayFix<SCharacterSet>& aArrayOfCharacterSetsAvailable, RFs& aFileServerSession);
	IMPORT_C TAvailability PrepareToConvertToOrFromL(TUint aCharacterSetIdentifier, RFs& aFileServerSession);
	// the following attribute-setting functions should be called (if at all) after calling PrepareToConvertToOrFromL and before calling ConvertFromUnicode and/or ConvertToUnicode
	IMPORT_C void SetDefaultEndiannessOfForeignCharacters(TEndianness aEndianness);
	IMPORT_C void SetDowngradeForExoticLineTerminatingCharacters(TDowngradeForExoticLineTerminatingCharacters aDowngradeForExoticLineTerminatingCharacters); // by default this attribute is set to EDowngradeExoticLineTerminatingCharactersToCarriageReturnLineFeed
	IMPORT_C void SetReplacementForUnconvertibleUnicodeCharactersL(const TDesC8& aReplacementForUnconvertibleUnicodeCharacters); // must be a single character preceded by its escape sequence (if any), and must be little-endian if the endianness of the character-set is unspecified, otherwise in the same endianness as the character-set
	// the conversion functions return either one of the TError values above, or the number of unconverted elements left at the end of the input descriptor
	IMPORT_C TInt ConvertFromUnicode(TDes8& aForeign, const TDesC16& aUnicode) const;
	IMPORT_C TInt ConvertFromUnicode(TDes8& aForeign, const TDesC16& aUnicode, TInt& aNumberOfUnconvertibleCharacters) const;
	IMPORT_C TInt ConvertFromUnicode(TDes8& aForeign, const TDesC16& aUnicode, TInt& aNumberOfUnconvertibleCharacters, TInt& aIndexOfFirstUnconvertibleCharacter) const;
	IMPORT_C TInt ConvertFromUnicode(TDes8& aForeign, const TDesC16& aUnicode, TArrayOfAscendingIndices& aIndicesOfUnconvertibleCharacters) const;
	IMPORT_C TInt ConvertToUnicode(TDes16& aUnicode, const TDesC8& aForeign, TInt& aState) const;
	IMPORT_C TInt ConvertToUnicode(TDes16& aUnicode, const TDesC8& aForeign, TInt& aState, TInt& aNumberOfUnconvertibleCharacters) const;
	IMPORT_C TInt ConvertToUnicode(TDes16& aUnicode, const TDesC8& aForeign, TInt& aState, TInt& aNumberOfUnconvertibleCharacters, TInt& aIndexOfFirstByteOfFirstUnconvertibleCharacter) const;
	IMPORT_C static void AutoDetectCharacterSetL(TInt& aConfidenceLevel, TUint& aCharacterSetIdentifier, const CArrayFix<SCharacterSet>& aArrayOfCharacterSetsAvailable, const TDesC8& aSample);
	// the following functions are only to be called by conversion plug-in libraries
	IMPORT_C static TInt DoConvertFromUnicode(const SCnvConversionData& aConversionData, TEndianness aDefaultEndiannessOfForeignCharacters, const TDesC8& aReplacementForUnconvertibleUnicodeCharacters, TDes8& aForeign, const TDesC16& aUnicode, TArrayOfAscendingIndices& aIndicesOfUnconvertibleCharacters);
	IMPORT_C static TInt DoConvertFromUnicode(const SCnvConversionData& aConversionData, TEndianness aDefaultEndiannessOfForeignCharacters, const TDesC8& aReplacementForUnconvertibleUnicodeCharacters, TDes8& aForeign, const TDesC16& aUnicode, TArrayOfAscendingIndices& aIndicesOfUnconvertibleCharacters, TUint& aOutputConversionFlags, TUint aInputConversionFlags);
	IMPORT_C static TInt DoConvertToUnicode(const SCnvConversionData& aConversionData, TEndianness aDefaultEndiannessOfForeignCharacters, TDes16& aUnicode, const TDesC8& aForeign, TInt& aNumberOfUnconvertibleCharacters, TInt& aIndexOfFirstByteOfFirstUnconvertibleCharacter);
	IMPORT_C static TInt DoConvertToUnicode(const SCnvConversionData& aConversionData, TEndianness aDefaultEndiannessOfForeignCharacters, TDes16& aUnicode, const TDesC8& aForeign, TInt& aNumberOfUnconvertibleCharacters, TInt& aIndexOfFirstByteOfFirstUnconvertibleCharacter, TUint& aOutputConversionFlags, TUint aInputConversionFlags);
	IMPORT_C static const SCnvConversionData& AsciiConversionData();
private:
	enum
		{
		EStoredFlagOwnsConversionData				=0x00000001,
		EStoredFlagConversionPlugInLibraryIsLoaded	=0x00000002
		};
	enum TCharacterSetSearch
		{
		EStopCharacterSetSearch,
		EContinueCharacterSetSearch
		};
	enum TConversionPlugInFunctionOrdinals
		{
		EReplacementForUnconvertibleUnicodeCharacters=1,
		EConvertFromUnicode=2,
		EConvertToUnicode=3,
		EIsInThisCharacterSet=4
		};
	typedef const TDesC8& (*FReplacementForUnconvertibleUnicodeCharacters)();
	typedef TInt (*FConvertFromUnicode)(TEndianness aDefaultEndiannessOfForeignCharacters, const TDesC8& aReplacementForUnconvertibleUnicodeCharacters, TDes8& aForeign, const TDesC16& aUnicode, TArrayOfAscendingIndices& aIndicesOfUnconvertibleCharacters);
	typedef TInt (*FConvertToUnicode)(TEndianness aDefaultEndiannessOfForeignCharacters, TDes16& aUnicode, const TDesC8& aForeign, TInt& aState, TInt& aNumberOfUnconvertibleCharacters, TInt& aIndexOfFirstByteOfFirstUnconvertibleCharacter);
	typedef TBool (*FIsInThisCharacterSetL)(TBool& aSetToTrue, TInt& aConfidenceLevel, const TDesC8& aSample); // added in 6.1 as the 4th-ordinal exported function in the CONVPLUG interface
private:
	CCnvCharacterSetConverter();
	void ConstructL();
	static CArrayFix<SCharacterSet>* DoCreateArrayOfCharacterSetsAvailableLC(RFs& aFileServerSession, TUint aIdentifierOfOnlyCharacterSetOfInterest);
	static TCharacterSetSearch AppendHardCodedCharacterSetIfRequiredL(CArrayFix<SCharacterSet>& aArrayOfCharacterSets, TUint aIdentifierOfOnlyCharacterSetOfInterest, TUint aIdentifierOfHardCodedCharacterSet, const TDesC& aNameOfHardCodedCharacterSet);
	void ScanForStandardNamesAndMibEnumsL(RFs& aFileServerSession);
	TAvailability DoPrepareToConvertToOrFromL(TUint aCharacterSetIdentifier, const CArrayFix<SCharacterSet>* aArrayOfCharacterSetsAvailable, RFs& aFileServerSession);
	static void DeleteConversionData(const SCnvConversionData* aConversionData);
	static void DeleteConversionData(TAny* aConversionData);
	static TEndianness EndiannessOfForeignCharacters(const SCnvConversionData& aConversionData, TEndianness aDefaultEndiannessOfForeignCharacters);
private:
	TUint iStoredFlags;
	TUint iCharacterSetIdentifierOfLoadedConversionData; // 0 or a UID
	TInt iIndexOfConversionPlugInLibrary;
	RLibrary iConversionPlugInLibrary[2];
	const SCnvConversionData* iConversionData;
	TEndianness iDefaultEndiannessOfForeignCharacters;
	TDowngradeForExoticLineTerminatingCharacters iDowngradeForExoticLineTerminatingCharacters;
	TBuf8<KMaximumLengthOfReplacementForUnconvertibleUnicodeCharacters> iReplacementForUnconvertibleUnicodeCharacters;
	CStandardNamesAndMibEnums* iStandardNamesAndMibEnums;
	};

#endif

